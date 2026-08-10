# companion.md — Robot Team Orchestrator

**This file is the single source of truth for the robot_team project.** It knows
everything about the fleet and orchestrates a swarm of simpler **A32 agents**.
Read it first, every session. When something here is wrong or stale, fix *this
file* — it is the brain, not a logbook.

> **Source-of-truth rule (2026-07-13):** project knowledge — state, decisions,
> milestones, field findings — lives **here** (§6, the fleet table, the §7
> knowledge map). The cross-session memory store
> (`~/.claude/projects/c--git-robot-team/memory/`) holds only **thin one-line
> pointers back to this file**, never divergent full-text copies, so the two can
> never disagree. Build/hardware gotchas belong in `CLAUDE.md` (also
> repo-canonical). Record a project fact here first; leave at most a pointer in
> memory.

> Modeled on the `companion-arc` pattern from the ARC Prize project: one
> orchestrator that holds the whole picture and dispatches simpler, focused
> agents. There, the simpler agents were per-instance solvers. Here they are
> **A32 agents** — the ESP32 robots and the build-time subagents that own them.

---

## 1. What this project is

`robot_team` is **a team of ESP32 robots** that sense, reason, and act
*without* cloud LLMs or neural inference. Each robot is an **A32 agent**: a
deterministic device whose entire mind is a Toot-Toot Database (TTDB) markdown
file (see `RFCs/A32-RFC-0001-Architecture.md`). The robots form a
range-adaptive mesh (ESP-NOW in range, LoRa long-haul) and are coordinated by a
laptop **orchestrator** running the Locus reasoning loop and Dream Cycle.

- **The robots are dumb-but-deterministic.** Intelligence lives in their TTDB.
- **The companion (laptop) is smart.** It authors TTDB, reconciles beliefs,
  and dispatches commands. It is the only LLM in the system.
- **One protocol, the "toot."** Every message is a 250-byte toot frame, HMAC
  signed, dedup-keyed on `(src_node_id, toot_seq)`. See
  `toot_network_architecture.md`.
- **The primary hypothesis is SEMANTIC POSITIONING** (adopted 2026-07-07, spec:
  `ttn-semantic-positioning.md`): the fleet can infer its own physical
  arrangement from umwelt overlap, and prove it three ways — **verified**
  (position beliefs within their stated `sigma` of the T-Deck's GPS ground
  truth, BLE as the near-range approximation tier), **actuated** (proximity
  beliefs auto-switch each link between ESP-NOW and LoRa), and **rendered**
  (network + node status drawn as TTCP on the laptop *and* the T-Deck screen —
  the end goal). Everything verified so far is the floor this proof stands on.
  Build order: PLAN.md **Act II**.

---

## 2. The fleet — the A32 agents it orchestrates

Each row is one A32 agent. The companion owns the contract; the agent owns its
firmware + TTDB. (Specs: `hardware_specs.md`; mesh roles:
`toot_network_architecture.md`.)

| Agent | Board | Role | Spine pos | Links | Power | Sketch | Status |
|-------|-------|------|-----------|-------|-------|--------|--------|
| **V4-A** | Heltec V4 | Bridge / head — laptop ↔ mesh gateway | head | USB-CDC + LoRa + ESP-NOW | mains, never sleeps | `firmware/v4a_bridge` | ✅ on-device verified (boots, ESP-NOW up, byte-exact pull + HMAC auth; OLED status; **`want_ack` ACK + time-sync: adopts `TIME_SYNC`, answers `TIME_REQ`, appends its own sync log**; LoRa gated off). **2026-07-30: answers `CMD_GET_INTERO` (21 B body, die temp now in STATUS too) and `CMD_DUET` — it led a verified double-time duet with V4-B.** **reads its own pack: 4.096 V / 89% / rising** (GPIO1 behind an ACTIVE-HIGH GPIO37, measured); ⚠ pull it over its own cable, the bridged path is broken |
| **V4-B** | Heltec V4 | Relay / mid — store-and-forward long hops | mid | LoRa + ESP-NOW | solar + battery | `firmware/v4b_relay` | ✅ on-device verified as the **3rd mesh node + Dream-Cycle participant** (2026-06-25): standalone byte-exact pull + self-heal + `negchecks` (COM9); then through the V4-A bridge over ESP-NOW — adopts `TIME_SYNC` (`@LAT99` self-write), folds into 3-node `reconcile` (id:3/4 `agree:yes`), and adopts a pushed belief byte-exact (`@LAT98`, 1373 B/crc match). Stores+attests beliefs (no DIRECTIVE action — no agent cadence). relay-forward + LoRa gated off. **2026-07-30: answers `CMD_GET_INTERO` and `CMD_DUET` — harmonised a double-time duet after being invited entirely over the air.** **reads its own pack: 3.831 V / 52% / rising** — the solar+battery node can finally report its state of charge; ⚠ its 54 KB TTDB no longer pulls through the bridge — use COM9 direct |
| **V4-C** | Heltec V4 | Edge / tail — remote cluster gateway, GNSS stamp | tail | LoRa + ESP-NOW | solar, off-grid | `firmware/v4c_edge` | 🟨 firmware at **full Dream-Cycle parity** (built from the verified V4-B: deferred+paced TTDB serve, `want_ack`/re-ACK, `TIME_SYNC`+`@LAT99`, belief `TTDB_PUT`+`@LAT98`, SP0 link/entity/BLE percepts, remote lane-clear, OLED, MAX98357A amp + band **offbeat hi-hat**), **2026-07-30: answers `CMD_GET_INTERO` and `CMD_DUET` too — the whole LoRa spine is now at parity, and its pack read 3.841 V / 54% on the FIRST flash because it was built with the measured GPIO37 polarity instead of the published one**; compile-verified 94% flash — ✅ **built + flashed + on-device verified (2026-07-16, COM13)**: `ping` ACK on attempt 1, `pull` byte-exact + self-appended `@LAT96` WiFi entity windows on first boot, adopted conductor 0x10 over ESP-NOW, band-tight ±6.5 ms, **hi-hat AUDIBLE by ear** (hand-wired amp confirmed); LoRa/GNSS gated off |
| **K10-1** | UNIHIKER K10 | Percept node — camera/mic/accel, `@PERCEPT` capture, UI | leaf | ESP-NOW / WiFi | battery | `firmware/k10_percept` | ⏸ **PARKED 2026-07-31 — temporarily excluded from the fleet; depend on nothing here.** Code kept and unmodified (`firmware/k10_percept`, `NODE_K10_1`, the `.vscode` K10 tasks); it is only out of the *defaults* — `--node k10_1` still works the moment it is plugged back in. Was already off the band roster and off the T-Deck's mesh map (2026-07-29) on v1 firmware; this finishes that. Previously ✅ on-device verified (boots from TTDB, Agent32 loop, LCD records + cursor/WARM, "toot toot"; TTDB-share over ESP-NOW & USB; **`want_ack` ACK + re-ACK, chunk reassembly, time-sync with runtime TTDB self-write of `@LAT99` sync records**; **band lead** — Ode-to-Joy melody, boots silent, `CMD_PLAY`/`CMD_STOP`) |
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

## 4. How the companion orchestrates

The companion wears two hats. Both dispatch "A32 agents," at different times.

### 4a. Build-time — Claude Code subagents
When building/maintaining a node, the companion spawns a focused subagent that
owns exactly one row of the fleet table: its firmware (`src/`, `lib/`), its TTDB
(`data/<node>.md`), and its native tests. The companion hands it:
- the **A32 agent contract** (§3),
- the node's **role + hardware constraints** (§2 row, `hardware_specs.md`),
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

## 5. Sources of truth (the companion reads these; it does not duplicate them)

| Topic | File |
|-------|------|
| A32 framework, layers, design principles | `RFCs/A32-RFC-0001-Architecture.md` |
| TTDB storage, streaming parser, index | `RFCs/A32-RFC-0002-TTDB-Storage.md` |
| Sense-reason-act loop, HAL registries | `RFCs/A32-RFC-0003-Agent-Loop.md` |
| Claude Code project layout, CLAUDE.md, PlatformIO | `RFCs/A32-RFC-0004-Claude-Code-Setup.md` |
| TBEW parser extension ([ew] blocks) | `RFCs/A32-RFC-0002-Amendment-A-TBEW.md` |
| TTDB file format / edges / weights | `RFCs/TTDB-RFC-000{1..8}` |
| Mesh transport, toot frame, bring-up order | `toot_network_architecture.md` |
| **Semantic positioning — the primary hypothesis** | `ttn-semantic-positioning.md` (build plan) + `RFCs/TTN-RFC-0011-Semantic-Positioning.md` (normative half, Experimental) |
| Cardputer sensory-representor mode (proposal) | `cardputer-sensorium.md` |
| TTCP rendering (records, globe, URIs) | `RFCs/TTCP-RFC-000{1..3}`; live reference viewer: [antfriend.github.io](https://github.com/antfriend/antfriend.github.io) |
| Board specs, GPIO maps, gotchas | `hardware_specs.md` |
| Build plan & milestones | `PLAN.md` |
| RFC catalog | `RFCs/INDEX.md` |

If a fact lives in one of these, link to it from here — don't copy it.

---

## 6. Current state & next action

- **State:** **Phase 0 is done on the K10.** Toolchain installed (winget
  `arduino-cli` + DFRobot `UNIHIKER:esp32:k10` core); firmware *and* the LittleFS
  TTDB image are flashed via the `.vscode/tasks.json` path; the Agent32
  sense→reason→act loop is **verified on real hardware** — the LCD shows the TTDB
  id, both records (`@LAT0LON0`, `@LAT10LON0`), live cursor + WARM/cool state, and
  the startup "toot toot" plays. The native `g++`/`make` tests were skipped
  (device-first). Only **one** physical K10 exists. V4 spine + LoRa: untouched.
- **`companion.py pull` over USB-CDC works (Phase 1 positive case ✅).** The laptop
  reassembles a byte-identical copy of the K10's TTDB (1114 B, sha256 `ec17aee2…`)
  on COM3. Two fixes made this work: (1) firmware must be flashed with
  **`CDCOnBoot=cdc`** or `Serial`/the toot link binds to UART0 and the pull gets
  zero bytes; (2) `companion.py` waits 2.5 s after opening the port because the
  open resets the S3 and it must finish booting before the request lands.
- **Two nodes verified on-device (K10 leaf + V4-A bridge).** Each pulls a byte-exact
  copy of its TTDB over USB-CDC and rejects wrong-key / tampered toots (HMAC). The
  V4-A path also needed `CDCOnBoot=cdc` + the `scripts/Upload-V4-FS.ps1` image
  (spiffs @0x290000). Reproduce auth with `orchestrator/negchecks.py`.
- **Dedup is RADIO-ONLY (decided 2026-06-20).** `(src,seq)` dedup guards the
  ESP-NOW/LoRa path against replay + forwarding loops; the trusted USB-CDC link is
  intentionally NOT deduped so the laptop can retry. K10 reflashed to match the V4
  (2026-06-20) and re-verified with `negchecks.py` — both nodes now radio-only.
- **Phase 1b complete — the mesh works.** `companion.py pull --node k10_1 --port
  COM6` reassembles the K10's TTDB **byte-exact through the V4-A bridge over ESP-NOW**
  (laptop→USB→V4-A→air→K10 and back), repeatably. `orchestrator/radio_replay.py`
  confirms an over-the-air duplicate `(src,seq)` is dropped by the K10's radio dedup.
  Firmware lessons: a node must **serve a reply from `loop()`, not the recv
  callback** (else its WiFi task starves its own TX), and **pace ESP-NOW bursts**
  (send-complete callback + small inter-frame gap); the laptop uses a **fresh
  `toot_seq` per request** so a non-reset target won't dedup-drop it.
- **Phase 2 + Phase 2.5 are ✅ on-device verified (2026-06-22, K10 COM3 + V4-A
  COM6).** Both RFCs built, flashed, and run on real hardware:
  - **TTN-RFC-0007 (reliability):** `companion.py ping --node k10_1` ACKed on attempt
    1; `reltest --size 500` delivered a 3-chunk toot and **recovered 2 air-dropped
    chunks by selective retransmit**, completing the set. Built on `Toot` ACK helpers
    + a portable `Reassembler` (per-chunk dedup, completed ring, TTL evict) and the
    K10 re-ACK-on-dedup path.
  - **TTN-RFC-0008 (time-sync):** `companion.py sync` → both nodes adopt + ACK on
    attempt 1; `verify --sync-id 2` → all three carry `**SYNC** id:2` and skew is
    **v4a_bridge −2.4 ms, k10_1 −30.6 ms** (within ±50 ms; the −30 ms is the honest
    one-way delivery delay). The K10's on-flash TTDB grew 1114→1426 B with two
    `@LAT99LON<n>` records, pulled back byte-exact — **first runtime TTDB self-write.**
    `sync_id`-gated exactly-once adoption (incl. the bridge's un-deduped USB path);
    `sync`/`verify` open the bridge without the DTR/RTS reset so it keeps its offset.
  - **Tests:** `tests/test_ack_py.py` (17 checks) passes in-session; `test_toot.cpp`
    extended (ACK + reassembly + time payloads) for the native/g++ gate.
  - **Two laptop-side timing bugs found + fixed during bring-up** (firmware was
    correct): sample `epoch_ms` *after* the settle, and probe with a non-blocking
    read — the first `verify` showed ~−600 ms, all harness latency.
- **Phase 5 down-payment ✅ — the laptop drives + observes the fleet.** `CMD` carries a
  verb set (`Toot.h` `CmdOp`: `ping` / `set-led RRGGBB` / `clear-led` / `beep` /
  `set-interval`); the K10 acts only on a CMD addressed to it and ACKs it (`want_ack`),
  `set-led` overriding the warm/cool indicator until `clear-led`. `companion.py cmd
  --op set-led --rgb 0000FF` + `clear-led` ACKed attempt 1 (K10 USB); bridge-relayed
  CMD proven by `ping` over COM6. **Telemetry:** `CMD_GET_STATUS` → a node answers a
  STATUS `PERCEPT` (cursor, temp, warm/led/synced flags, epoch); `companion.py monitor`
  prints a live table — verified on the K10 over COM3 (`@L10L0`, 31.9 °C, warm).
- **Phase 6 Dream-Cycle seed ✅ — `reconcile` consolidates fleet sync logs.** The minimal
  first instance of the Dream Cycle (TTDB-RFC-0007): `companion.py reconcile` pulls each
  node's TTDB, folds the `@LAT99` sync records each node self-authored into one
  `master/consolidated.md` with provenance (per-source `recv_ms`/`offset_ms`), and exits
  non-zero on any `t_ms` disagreement. Verified on the K10 over COM3 — `id:1`/`id:2` both
  `agree:yes` (its two `@LAT99` records survived every reflash; the LittleFS data
  partition is untouched by app flashing). Episodic node records → a semantic master one.
- **Phase 6 push-back ✅ (2026-06-24) — `push` distributes a re-authored belief
  (TTN-RFC-0009).** The propagation half of the Dream Cycle: `companion.py push`
  re-authors `master/belief.md` from the consolidated sync knowledge, streams it as
  offset-addressed `want_ack TTDB_PUT` slices (reliable, CRC-32 whole-object integrity),
  and the node writes it to a separate `/belief.md`, CRC-verifies, and appends a
  `BELIEF-ADOPTED` record to its own live TTDB (`@LAT98` lane). Verified on the K10 over
  COM3 — belief `978 B` / `crc 65118C32`, all 6 slices ACKed first try, `bytes`/`crc`
  round-trip MATCH; a monotonic `belief_id` gives exactly-once adoption (`id:1`→`@LAT98LON0`,
  `id:2`→`@LAT98LON1`, no duplicate on re-ACK). Push log in `master/belief-log.md`.
- **Bridge-relayed push ✅ (2026-06-24) — `push` reaches an over-air node through the
  V4-A bridge.** `companion.py push --port COM6 --node k10_1` delivered a `978 B` belief
  to the K10 *over ESP-NOW via the bridge*, all 6 `want_ack TTDB_PUT` slices ACKed, the
  K10 CRC-verified and adopted (`id:4` → `@LAT98LON4`, `bytes`/`crc` MATCH), and the
  in-band verify pull confirmed it. One firmware fix made this safe: the K10 now **defers
  a radio `TTDB_PUT` to `loop()`** (like `TTDB_REQ`) — `handlePutSlice`'s flash write must
  not run in the ESP-NOW recv callback (the Phase 1b lesson). Two `companion.py` fixes made
  the in-`push` verify pull reliable: drain the OS buffer + use a fresh frame reader before
  it (the push burst left the reader mid-frame, desyncing the un-ACKed `TTDB_DATA` stream),
  and ms-resolution `toot_seq` so back-to-back retries get distinct `(src,seq)`.
  **Subtlety found:** the exactly-once adoption gate (`gBeliefAdopted`/`gBeliefId`) is
  RAM-only, so it does NOT survive a node reboot — a re-push of a *reused* `belief_id` after
  a reset re-adopts (saw a duplicate `id:3` when an out-of-band COM3 pull reset the K10).
  Safe in normal operation because `belief_id` is monotonic from `master/belief-log.md` and
  never reused; the in-band (bridge) verify never resets the node.
- **Dream Cycle CLOSED ✅ (2026-06-24) — a pushed belief changes node behavior.** The
  re-authored belief now carries a `**DIRECTIVE** sense_interval_ms:<N>` record (`@LAT0LON1`);
  on a CRC-verified commit the K10 parses `/belief.md`, retunes its sense→reason→act
  cadence (`Agent32::setInterval`, floored at 100 ms), and records the effective rate as
  `applied:interval_ms` in its `BELIEF-ADOPTED` attestation. Verified live through the V4-A
  bridge (COM6): cadence went **1000 ms (boot) → 300 ms → 700 ms** across successive
  pushes, measured over COM3 *without resetting the node* (`scratchpad/cadence.py` times
  the `[cycle]` log), each `push` confirming the change in-band (`behavior changed: node
  retuned sense cadence -> N ms`). This is PLAN.md Phase 6's "Done when." Two fixes made it
  solid: the K10 parses the directive in `loop()` (not the recv callback), and `push` runs
  its verify pull in a **fresh link session** (re-opening resets the bridge to the clean
  state a standalone pull relies on; reusing the burst-session pull came back empty).
- **Belief readback ✅ (2026-06-24) — `push` verifies the stored bytes, not just the CRC.**
  A new `TTDB_REQ_BELIEF` request mode makes the K10 stream its `/belief.md` back as the
  same offset-addressed `TTDB_DATA` slices as a normal pull (`TtdbShare::handleBufferRequest`,
  TTN-RFC-0009 §3.1). `push` now reads it back and asserts byte-for-byte equality with what
  was sent (`stored /belief.md byte-exact (1121 B) — full readback MATCH`), over both USB
  and the bridge. Also exposed as `pull --file belief`. Found + fixed a side issue: git
  `autocrlf` was CRLF-mangling the byte-exact `master/*.md` + `data/*.md` artifacts on
  checkout; `.gitattributes` now pins them `eol=lf` so the repo copy matches the on-flash/
  on-wire bytes.
- **Pull-stream reliability ✅ on-device verified (2026-06-25, K10 COM3 + bridged COM6).** The `TTDB_DATA`
  pull stream is now self-healing: `request_ttdb` takes the EOF marker's offset as the true
  total length, detects any gap in offset coverage (`missing_ranges`), and selectively
  re-requests just the missing byte ranges via `TTDB_REQ_RANGE` until the object is
  byte-complete (`rounds=4`) — the receiver-driven analogue of `reltest`'s per-chunk
  retransmit, closing the old ~1/6 bridged-pull frame drop. **Zero firmware change**: the
  K10/V4-A `handleRequest` already serves `TTDB_REQ_RANGE` (the offset-index path); the
  companion's 13-byte `mode|target|start|end` payload matches it exactly, and `serveTtdbReq`
  already routes mode 1 → `handleRequest`. Applies to the live TTDB only (belief readback
  streams the whole buffer via `handleBufferRequest`, which has no range path). Gated offline
  by `tests/test_pull_py.py`. **On-device confirm:** `pull --drop` discards chosen data slices
  on the first pass (companion-side induced loss, live TTDB only), forcing the self-heal to run
  deterministically. Two patterns over COM3 each recovered byte-exact vs a clean baseline (2843
  B, sha256 `ce3ca723…`): `--drop 1,3` (interior slices) and `--drop 0,14` (first + the 15-B
  partial tail) — **the firmware `TTDB_REQ_RANGE` branch ran live for the first time** and the
  selective re-request reassembled identically. Also confirmed **bridged over COM6** (through
  the V4-A bridge over ESP-NOW): `--drop 1,3` re-requested the two gaps *over the air* and
  recovered the same byte-exact 2843 B / `ce3ca723…` — the relay path serves `TTDB_REQ_RANGE`
  transparently (the bridge forwards any `TTDB_REQ` without inspecting the mode).
- **3-node Dream Cycle ✅ on-device verified (2026-06-25) — a 2nd Heltec V4 joins as V4-B and the
  fleet runs across three nodes for the first time.** `firmware/v4b_relay/v4b_relay.ino` is a full
  **ESP-NOW Dream-Cycle participant** (not yet the LoRa forwarder): TTDB serve deferred to `loop()`
  + paced bursts (K10's Phase-1b/burst lessons), `want_ack` ACK + dedup re-ACK (TTN-RFC-0007 §5),
  TIME_SYNC adopt + `@LAT99` append + TIME_REQ answer (TTN-RFC-0008), belief `TTDB_PUT` adopt +
  `@LAT98` attestation (TTN-RFC-0009; stores+attests — no DIRECTIVE action, no agent cadence), OLED
  status. Promiscuous store-and-forward gated behind `USE_RELAY_FORWARD` (off, so it doesn't
  re-broadcast the bridge's traffic in one room) and LoRa behind `USE_LORA` (off). Companion needed
  **zero changes** (`sync`/`verify`/`reconcile` already take node lists; `v4b_relay` = id `0x11`).
  Built blind from the K10 + V4-A patterns; **worked first try on hardware.** Verified: standalone
  byte-exact pull (858 B) + self-heal + `negchecks` (COM9); then through the V4-A bridge over
  ESP-NOW — `sync id=4` all three adopt+ACK (attempt 1); `verify id=4` all three carry the `@LAT99`
  record within ±50 ms (v4a −2.0, v4b −45.0, k10 −45.3); `reconcile` folds **4 sources**
  (k10_1/laptop/v4a_bridge/v4b_relay), id:3 & id:4 `agree:yes`; `push --node v4b_relay` lands belief
  id=9 (1373 B/crc `9EFD9530`), 8/8 slices ACK attempt 1, byte-exact readback MATCH. Also hardened
  `verify` to **retry the has_record pull 3×** (a transient bridged-pull miss read v4b as missing on
  the first run). **Operational rule reconfirmed:** `reconcile`/`push` open the bridge WITH a
  DTR/RTS reset, wiping V4-A's RAM clock offset — so a `verify` after them needs a fresh `sync`
  first (`sync`/`verify` open without reset; the `@LAT99` records persist in flash regardless).
- **Fleet pulse — K10 lead ✅ on-device verified (2026-06-26), the band time-base
  (TTN-RFC-0010).** A self-synchronizing ~1 Hz heartbeat designed as the basis for a
  small band of musicians: the **first node up conducts** (lowest live id keeps the
  baton, `era`-numbered handoff), joiners adopt the chart and fall into phase, and the
  beat is **computed from a shared pulse clock** (`millis()` + an adopted offset, its own
  register separate from the laptop wall clock) — **not** messaged per beat. New toot
  type `PULSE = 13` (28-B chart beacon: conductor/era/conductor_epoch/downbeat/period/
  meter/flags; `Toot::buildPulse`/`parsePulse`) carried **rarely** — drift-paced
  (`PULSE_RESYNC_PERIOD_MS` 30 s, §5 ceiling-safe) plus an on-join fast-lock — broadcast,
  **not** want_ack (a miss is corrected by the next). The portable **`Pulse` engine**
  (`firmware/libraries/Pulse`) owns the election + beat detector; the sketch supplies
  transport + instrument. On the K10 (COM3, `USE_PULSE 1`): self-conducts after the 3 s
  listen window, sounds a toot + RGB flash on **every** beat with the **downbeat accented**
  (C5/cyan vs G4/blue → "ONE-two-three-four"), hit scheduled a small humanize jitter after
  the boundary (the ±50 ms is **swing**, not slop). **Measured:** beat intervals 999–1001
  ms (mean 1000), and **51 beats elapsed with exactly ONE beacon on the wire** — the
  "optimize for timing like musicians, use only as much traffic as needed" requirement,
  proven. Adoption runs in the recv path (accurate `recv_ms`); the toot/LED render is
  deferred to `loop()` (playTone blocks — Phase 1b discipline).
- **All three pulse parts ✅ flashed + individually on-device verified (2026-06-26).** Same
  `Pulse` engine, three instruments: **K10** lead (COM3 — toot + RGB every beat, downbeat
  accented), **V4-A** timekeeper (COM6 — LED + OLED dot every beat), **V4-B** backbeat (COM9
  — LED + dot on beats 2 & 4). Each verified pulsing at 1000 ms with **~1 beacon / 15 s**
  (the minimal-traffic design). Each self-conducted because the bench's single USB lead
  powers one at a time, so they booted alone (K10 `cond=0x100`, V4-A `0x10`, V4-B `0x11`,
  all `era=1`). **V4 LED is GPIO35** (assumed Heltec white LED — confirm vs pinmap; OLED dot
  is the fallback). The **ensemble** (three locked together) is now purely a power step: with
  all three powered simultaneously they converge to V4-A conducting (lowest id, via the
  on-join HELLO→beacon→better() yield path) within a few HELLO intervals, then play the 4/4
  groove. Convergence reasoned through but **not yet observed live** (needs separate power on
  two nodes while the third holds USB).
- **`companion.py band` ✅ built + smoke-tested on hardware (2026-06-26).** The
  measured-tightness verifier (TTN-RFC-0010 §8): probes each node with `CMD_GET_STATUS`,
  reads a new **PULSE telemetry tail** appended to the STATUS payload (conductor_id/era/
  beat_period/pulse_epoch/downbeat/beat/pstate — backward-compatible, so `monitor` still
  reads the 15-B prefix; `STATUS_PULSE_PAYLOAD_LEN=43`), min-RTT NTP-lite projects every
  node's beat phase to one laptop instant, and prints `node | conductor | era | bpm | beat
  | phase_ms | skew_ms | rtt` with a PASS/FAIL on "one shared conductor + all within
  ±bound" (`--watch` for a live table). **Smoke-tested against V4-A solo on COM6**:
  `0x10*` conductor, 60 bpm, **skew +0.0 ms, rtt 2 ms, PASS** — validates the whole path
  (firmware tail → bridge → probe → projection). **All three (V4-A, K10, V4-B) now reflashed
  with the telemetry tail** — pulse parts unaffected, only the STATUS tail is new.
- **FULL 3-NODE ENSEMBLE ✅ on-device verified (2026-06-26) — the band plays in sync.**
  `companion.py band --port COM6 --nodes v4a_bridge,v4b_relay,k10_1` (all three powered,
  V4-A bridging) printed every node on **one shared chart (conductor `0x11`, era 4, 60 bpm)**
  with measured inter-node phase **skew V4-A +0.5 ms / V4-B 0 (ref) / K10 +10.4 ms → PASS,
  band tight to ±10.4 ms** (well inside the ±50 ms swing budget). Skew tracks transport
  delay honestly (rtt V4-A 1 ms direct USB, V4-B 11 ms one hop, K10 34 ms two hops via the
  bridge). **Conductor election + handoff also exercised live:** physically plugging the USB
  lead **reset V4-A**, which dropped its era-3 chart and restarted at era 1; the followers
  correctly **ignored the lower-era beacon** and free-ran on era 3 (V4-B↔K10 stayed 10 ms
  apart throughout), then the conductor-timeout promoted **V4-B to era 4** (keeping the
  era-3 downbeat, no lurch) and rebooted V4-A adopted it — the baton moves to whoever is
  counting (corrected §3: lowest-id is a tie-break, not a continuous coup). TTN-RFC-0010 is
  now end-to-end verified on hardware. **Known rough edge:** a conductor reboot causes a
  reconvergence gap bounded by `PULSE_CONDUCTOR_TIMEOUT_MS` (90 s) — long because the era is
  RAM-only; tightening the beacon/timeout or persisting era in NVS would shrink it.
- **Parts & melodies layer ✅ built (2026-06-26) — the band plays a tune.** A sequencer on
  top of the pulse: `Pulse::stepTick` adds a sixteenth-note step clock
  (`PULSE_STEPS_PER_BEAT=4`), and a new header-only **`Score`** lib (in the Pulse library)
  defines `Note`/`Phrase` data tables + `noteAt()`. Each node now plays a **data-driven
  part** off the shared clock — swap a note table to re-voice the band (TTN-RFC-0010 §7, the
  seam for purpose-built instruments): **K10 = lead melody** (its speaker is the only pitched
  instrument — default "Ode to Joy" PD, 4 bars/64 steps; tones via the deferred-beep path,
  RGB color mapped by pitch), **V4-A = timekeeper** (four-on-the-floor, LED+OLED every beat),
  **V4-B = backbeat** (beats 2 & 4). **V4-A + K10 flashed + verified on-device — melody is AUDIBLE.** V4-A's
  timekeeper fires steps 0/4/8/12 (DOWNBEAT on 0, 1000 ms). **The K10 plays the melody ✅**
  (COM3, confirmed audible 2026-06-26): once locked it sounds `E4 E4 F4 G4 G4 F4 E4 D4 C4 C4 D4 …` — the Ode to Joy opening,
  each note on its beat, RGB colored by pitch. The capture also caught the K10 **joining the
  running band live over ESP-NOW** mid-tune: it booted self-conducting (`cond 0x100 era 1`),
  then adopted the band's chart (`cond 0x11 era 6`), snapping from step 24 → step 54 onto the
  band's phrase. So pulse → election/handoff → data-driven parts → melody → live join is the
  full verified stack, three nodes playing together. (V4-B still runs the pre-Score backbeat —
  identical behavior; reflash for code consistency whenever its cable is free.)
- **K10 audio gotcha fixed (2026-06-26): GPIO45 is the I2S speaker, not the backlight.** The
  melody was silent at first (only the startup toot played) because the sketchbook TFT_eSPI
  `User_Setup.h` had `TFT_BL 45` — GPIO45 is the K10's `IIS_DOUT` (speaker), so `tft.begin()`
  in `initScreen()` seized it and clamped the speaker; the startup toot survived because it
  plays before `initScreen`. Fix: removed `TFT_BL`/`TFT_BACKLIGHT_ON` from User_Setup.h
  (backlight is lib-driven via `eLCD_BLK`, so the screen still renders). NOT a WiFi power-save
  issue (that red herring's `WIFI_PS_NONE` was kept anyway — good for ESP-NOW latency).
  Documented in CLAUDE.md + memory [[k10-gpio45-speaker-vs-tft-bl]].
- **T-Deck console added ✅ network floor on-device verified (2026-07-06, COM10).** A LilyGo
  T-Deck joins the fleet as **T-DECK-1** (`firmware/tdeck_console`, node id `0x200`, map
  `@LAT10LON0`) — the handheld **operator console**: keyboard injects CMD toots, 320×240 screen
  shows the fleet, so the swarm can be driven without the laptop. Built from the V4-B
  participant pattern; the network floor is **verified on real hardware**: boots from TTDB,
  `companion.py pull --node tdeck_1` reassembled a **byte-exact 1351 B (sha `fd95360b…`)** and
  `negchecks.py` gave **wrong-key/tampered → 0 frames** (HMAC reject), served-replay by design
  (radio-only dedup). It's a full Dream-Cycle participant (pull/HMAC/dedup, `TIME_SYNC`+`@LAT99`,
  belief `TTDB_PUT`+`@LAT98` store-and-attest, STATUS, PULSE follower), so `sync`/`reconcile`/
  `push`/`monitor`/`band` should work over the air once it's on the mesh with the bridge.
  companion.py node map + `RobotTeamConfig` updated. **Flashing gotchas hit + recorded:** the
  T-Deck's native-USB auto-reset is flaky — flashing needed a **manual bootloader entry** (hold
  the trackball-click = GPIO0/BOOT, tap RST) which re-enumerates the port (COM11→COM10), and
  after flashing it needed a **clean RST tap** (not touching the trackball) to leave download
  mode and boot the app; asserting DTR+RTS together drops it back into the bootloader. The LCD
  (ST7789, **its own** TFT_eSPI setup — must NOT reuse the K10's `User_Setup.h`) + keyboard (I²C
  `0x55`) + the keyboard→CMD operator loop are gated behind `USE_TDECK_HW` (default 0); `GPIO10`
  gates the peripheral rail. Carries an SX1262 (LoRa-spine-capable, `USE_LORA`). FS via
  `scripts/Upload-V4-FS.ps1 -Node tdeck_console`.
- **T-Deck console UI ✅ on-device verified (2026-07-06, `USE_TDECK_HW 1`).** On boot it
  sounds a **"toot toot"** (two rising tones G3→C4) and renders a **320×240 fleet view**
  (id/channel/sync, TTDB size, drive-target, live cmd/rx/reply counters). Both confirmed by
  the user on hardware. Audio: the speaker is an **I²S MAX98357A amp** (no analog/PWM path
  like the K10 `Music`), so `toneI2S()` synthesizes a 16-bit sine over `ESP_I2S` (BCLK 7 / WS
  5 / DOUT 6, 16 kHz stereo L=R). Display: **Adafruit_ST7789 with runtime pins** (SPI SCLK 40
  / MISO 38 / MOSI 41 / CS 12, DC 11, RST -1, BL 42) — deliberately NOT TFT_eSPI, so it never
  touches the K10's shared `User_Setup.h`; `init(240,320)` + **`setRotation(3)`** is
  right-side-up (rotation 1 was upside-down on this panel). Flicker-free draw (static title
  once, rows overwritten in place — the K10 canvas-blink lesson). Keyboard (I²C `0x55`) →
  `emitCmd` maps s=get-status / p=ping / b=beep at `gCmdTarget` (default V4-A). Libs:
  `arduino-cli lib install "Adafruit ST7735 and ST7789 Library"` (+GFX +BusIO); `ESP_I2S`
  ships with the esp32 core. See [[tdeck-flashing-manual-bootloader]].
- **T-Deck live on the mesh ✅ + fleet-remote firmware (2026-07-06).** Verified over the air
  through the V4-A bridge (COM6): **bridged pull byte-exact** (1351 B), **STATUS via bridge**
  (all of v4a/v4b/tdeck report), and **`sync` id=5 adopted+ACKed by all three attempt 1** — the
  T-Deck self-wrote its `@LAT99` record (pulled back, `has_record: yes`; skew −53 ms = honest
  one-hop air delay, matches v4b −53). Keyboard **confirmed driving CMDs** (the `cmd` counter
  ticks per press). Learned: the **V4-A bridge only forwards replies** (`TTDB_DATA`/`PERCEPT`/
  `ACK`/`BELIEF`/`TIME_RESP`) up to USB, **not `HELLO`/`CMD`** ([v4a_bridge.ino:216](firmware/v4a_bridge/v4a_bridge.ino#L216)) — so a laptop sniff can't see raw T-Deck TX,
  and a CMD aimed at the bridge gets no mesh reply (it answers CMDs only over USB). Reflashed
  the T-Deck as a **proper fleet remote**: default target **V4-B** (answers over the air), **`t`**
  cycles target (V4-B→K10→V4-A), **`s`**=get-status, **`p`**=ping, **`b`**=beep, **`g`**=play,
  **`x`**=stop; screen shows the target name + a key legend + last reply. New `CmdOp`s
  **`CMD_PLAY=6` / `CMD_STOP=7`** (Toot.h + `companion.py cmd --op play/stop`).
- **K10 song start/stop ✅ flashed + verified (2026-07-06, COM3).** The K10 melody now **boots
  silent** (`gPlayEnabled=false`) and only sounds between `CMD_PLAY` and `CMD_STOP` — the step
  clock keeps running while stopped so it stays in band phase; only the audible/LED hit is muted.
  `companion.py cmd --op play/stop --node k10_1 --port COM3` both **ACKed APPLIED attempt 1**.
  (Caveat: `cmd` over USB resets the K10 on port-open, so the clean no-reset control is the
  T-Deck over the air — `t`→K10 then `g`/`x`.) Firmware-only flash; the TTDB on the `model`
  partition persists.
- **Two-part Ode to Joy ✅ built + flashed (2026-07-06).** The K10 plays the **lead** (part 1,
  `kLeadNotes`) and the **T-Deck plays a harmony a third below** (part 2, `kHarmNotes` — C–C–D–E–
  E–D–C–B–A–A–B–C…) on its I²S speaker, locked to the shared pulse step grid so the voices align.
  Tempo is **120 BPM** (`PULSE_DEFAULT_BEAT_MS 500`). The T-Deck defaults its target to **K10**
  and **`g`** starts *both* voices (local harmony + `CMD_PLAY` to the K10), **`x`** stops both;
  screen shows `song: PLAYING part 2`. Both boot silent.
- **Tempo-change gotcha found + fixed (2026-07-06) — set the tempo in `Pulse.h`, not a sketch
  `#define`.** `PULSE_DEFAULT_BEAT_MS` in a sketch does NOT reach `Engine::selfAppoint()`
  (`Pulse.cpp` is a separate TU with no `-D`), so earlier "75 BPM" reflashes silently stayed at
  60. Fixed by setting the default in `Pulse.h` (now **500 ms = 120 BPM**) and removing the dead
  per-sketch defines. **Also:** the `era` latch keeps the old tempo across a reflash (a running
  node's higher-era chart wins), so changing tempo means **reflash the conductor + cold-start the
  fleet**. Verified: `band --port COM3 --nodes k10_1` → K10 conducts `era 1, bpm 120`. See
  [[pulse-tempo-lives-in-pulse-cpp]]. **V4-A/V4-B/T-Deck still run pre-fix firmware** (60 BPM if
  they conduct) — for the 120 duet keep the V4s off (K10 conducts); reflash them to bring the
  whole band to 120.
- **Duet ✅ confirmed at 120 BPM by the user; power-cycle-rejoin fixed (2026-07-06).** Two fixes
  so a power-cycled T-Deck rejoins the song on its own: (1) the T-Deck **persists the song on/off
  in NVS** (`Preferences`, `setLocalPlay`) so it resumes after a reboot, and its harmony now plays
  **only as an in-phase follower** (`gLocalPlay && !gPulse.conductor()`) — silent while
  self-appointed/re-locking, so it never plays out of phase; (2) the K10 (conductor) **fast-locks
  a *returning* neighbor**, not just a brand-new one — `neighborNeedsLock()` tracks per-neighbor
  last-seen and beacons immediately when one reappears after a >3 s gap (a power-cycle), instead of
  making it wait up to `PULSE_RESYNC_PERIOD` (30 s). Steady-state traffic unchanged (a
  steadily-present neighbor doesn't retrigger it). Both flashed; K10 verified conducting `era 1,
  bpm 120`. Pending: user confirms the rejoin.
- **PROJECT REORIENTED (2026-07-07) — SEMANTIC POSITIONING is now the primary hypothesis to
  prove** (`ttn-semantic-positioning.md`, promoted from draft to governing spec; build order
  PLAN.md **Act II**, SP0–SP6). The claim: the fleet infers its own physical arrangement from
  umwelt overlap (link RSSI percepts, shared-entity co-occurrence, **BLE as the near-range
  approximation tier**, environmental TDoA), consolidated by the Dream Cycle into
  `@BELIEF:PROXIMITY` / `@BELIEF:POSITION`. Three proof legs: **verified** (beliefs within
  their stated `sigma` of ground truth, the **T-Deck GPS as the roaming verification
  instrument** — verifier only, never an input, or the proof is circular); **actuated**
  (proximity beliefs **auto-switch each link between ESP-NOW and LoRa** with k·sigma
  hysteresis — this is what finally un-gates `USE_LORA`); **rendered** (the end goal:
  **network + node status as TTCP on both the laptop and the T-Deck** — the laptop leg
  re-uses the existing [antfriend.github.io](https://github.com/antfriend/antfriend.github.io)
  viewer over the master TTDB, so it's authoring discipline, not renderer code; the T-Deck
  leg grows the console fleet view into a native TTCP mini-renderer with trackball cursor
  navigation per TTCP-RFC-0002). Everything verified so far — toots/HMAC, self-healing pull,
  time-sync, reconcile/push, pulse — is the instrumentation floor for this proof.
- **SP0 first increment BUILT + compile-verified (2026-07-07) — link-percept capture.**
  New portable lib **`firmware/libraries/LinkPercept`**: the ESP-NOW recv callback logs every
  **HMAC-verified** frame's RSSI (before dedup — a retried duplicate is a real reception) into
  fixed per-peer histograms (~1.5 KB RAM, exact min/med/max, zero per-packet flash writes);
  once per 60 s window `loop()` appends one **`@LAT97LON<n>`** record (`**LINKWIN**` context +
  one `**LINK**` line per peer/proto), lane-capped at 48 until SP1 pruning.
  `ESPNOW_RECV_CB_INFO` + `tootEspNowRssi` (TootEspNow.h) expose the 3.x `rx_ctrl->rssi`;
  wired into **V4-A, V4-B, T-Deck** (all three + the untouched K10 compile clean). **K10
  capture deferred** (2.x recv cb has no RX metadata — promiscuous-RX trick later; the K10 is
  still observed one-directionally by the other three). Companion: **`companion.py percepts
  --node <n> --port <p>`** pulls and prints the lane. Format pinned by
  `tests/test_linkpercept.cpp` (no g++ on this machine — device-first, as ever). T-Deck
  confirmed **Plus variant (has GPS)** — the SP2 anchor/verifier hardware is real.
  **SP0 gate ✅ ACHIEVED on-device (2026-07-07).** All three flashed (V4-A COM6, V4-B COM9,
  T-Deck COM10 — the T-Deck's auto-reset worked first try, no manual BOOT/RST needed this
  round), each hash-verified and byte-exact-pull regression-checked (the new instrumentation
  didn't disturb the floor). `percepts` over the V4-A bridge shows **every node logging real,
  asymmetric RSSI** for every peer in one ~60 s window: V4-A sees T-Deck n=33 (-60/-46/-36)
  and V4-B n=15 (-44/-34/-33); V4-B sees V4-A n=27 (-47/-34/-32) and T-Deck n=33
  (-53/-29/-26); T-Deck sees V4-A n=12+26 (-49…-59/-42…-50/-37…-44) and V4-B n=29
  (-38/-34/-30). This is the spec's "distance measurement in disguise," live for the first
  time — three nodes, six directional links, all logged with zero per-packet flash writes.
- **SP1 consolidation BUILT + FIRST FLEET PROXIMITY MAP ✅ (2026-07-07).** New
  **`companion.py proximity`** pulls the fleet and fuses each pair's directional `@LAT97`
  windows into **`@BELIEF:PROXIMITY`** records (`master/proximity.md`, spec §2.1 format):
  median of per-window `rssi_max` per direction, directions averaged; sigma from spread +
  asymmetry, ×2 while uncalibrated; the **orchestrator pseudo-peer `0x1` excluded** (the
  laptop's own bridged pulls show up as receptions — real physics, meaningless range; found
  live, filtered by design). Offline gate `tests/test_prox_py.py` (21 checks). **First live
  run over the bridge (937 obs):** V4-A↔V4-B **0.34 m ±0.18** (n=282), V4-A↔T-Deck
  **1.21 m ±1.78** (n=303), V4-B↔T-Deck **0.26 m ±0.15** (n=352). The triangle-inequality
  violation (0.34+0.26 < 1.21) is the predicted uncalibrated-RSSI distortion, honestly inside
  the wide sigma — SP2's solver weighs by sigma, so it absorbs this. Bonus: two pulls
  air-dropped frames and the `TTDB_REQ_RANGE` self-heal recovered both transparently.
- **SP1 CALIBRATION ✅ (2026-07-07, the "walking range test").** V4-A fixed (workroom),
  V4-B walked 4 stations (3.75 / 9 / 19.5 NLOS / 37.5 m — strides ×0.75), ~3 min each,
  both directions logged; V4-A's clock wall-anchored by a timed reset (15:19:53). Fused
  station RSSI −33 / −54.8 / −67.5 / −82.5 → **`companion.py calibrate` fit: RSSI(d) =
  −6.3 − 48.4·log₁₀(d), n = 4.84, rmse 1.4 dB** (`master/calibration.md`,
  `@BELIEF:CALIBRATION`; valid 3.75–37.5 m — the intercept is extrapolation, and this is
  **through-wall home propagation**, not open air). `proximity` auto-loads it (no ×2
  sigma penalty, conf cap 0.85). **Measured ESP-NOW envelope ≈ −90 dBm** (frame counts
  collapse 30→4/min at the yard's edge) → **link death ~54 m through-house** per the
  model — SP5's auto-switch threshold, from data. Walk lessons: added `proximity --last
  N` (recency filter — a moved node's stale windows pollute the fuse; found because the
  walk IS a moving node), and **V4-B hit the 48-lane cap** on its final return window —
  its `@LAT97` lane is full and it records nothing new until reset (FS reflash, or build
  a remote lane-clear CMD).
- **REMOTE PRUNE + FIRST CALIBRATED FLEET MAP ✅ (2026-07-07).** `CMD_CLEAR_PERCEPTS`
  (op 8) + **`Ttdb::removeLane(97)`** (streaming TTDB compaction; idempotent; ACK gated on
  success; radio path deferred to `loop()`); `companion.py cmd --op clear-percepts` and
  **`proximity --clear`** = the whole Dream-Cycle loop in one command: pull → consolidate →
  **prune the consumed lanes over the air**. All three nodes reflashed + verified (every
  clear ACK attempt 1; V4-B/T-Deck took it **through the bridge over ESP-NOW**; V4-B
  un-wedged from its 48-lane cap; compaction is surgical — V4-A back to its 2-record base
  TTDB). **First calibrated 6-pair bench map:** V4-A↔V4-B 4.0 m, V4-A↔K10 3.1, V4-A↔T-Deck
  2.9, V4-B↔K10 2.2, V4-B↔T-Deck 3.0, K10↔T-Deck 3.9 (sigma 0.3–0.7 m, conf up to 0.8) —
  **the K10 entered the map with zero firmware change**, one-directionally observed by the
  3.x nodes. Caveat: bench pairs sit just below the fit's 3.75 m valid-range floor.
- **SP2 EMBEDDING ✅ — THE FLEET DREW ITS FIRST MAP OF ITSELF (2026-07-07).**
  `companion.py positions`: weighted spring relaxation (conf/sigma² weights, 8 random
  restarts — the fold local-minimum bit during testing and restarts fixed it) embeds the
  proximity matrix into **`@BELIEF:POSITION`** records (`master/positions.md`) in a
  canonical relative frame (V4-A origin, 2nd node on +x, `flip_resolved: false` until the
  T-Deck GPS pins the mirror), with an ASCII fleet map. Gated by `tests/test_embed_py.py`
  (10 checks incl. exact square recovery + outlier immunity). **First live embed: 4 nodes /
  6 pairs, stress 0.01 m, worst pair-fit 4 cm** — six independent calibrated distances agree
  on one 2D layout: V4-A(0,0), K10(3.1,0), T-Deck(0.4,2.9), V4-B(3.3,2.2), a ~4.3 × 3.9 m
  bench. Umwelt overlap → geometry, live, end to end.
- **SP2 GPS anchor — NMEA read + `anchor` BUILT + offline-verified (2026-07-10), awaiting
  the sky.** The roaming ground-truth leg (proof leg 1) is coded end to end and ready for a
  cable+sky-view session. **Firmware:** new portable **`firmware/libraries/Gps`** (NMEA-0183
  GGA parser — checksum-validated, allocation-free, hemisphere-signed; `tests/test_nmea.cpp`
  27/27 under `zig c++`); the T-Deck reads its **u-blox on UART1 (GPIO44 RX / 43 TX**, freed
  by native-USB CDC), auto-probes the NMEA baud (38400 default), shows the live fix on its
  screen, and answers the new **`CMD_GET_GPS`** (op 9) with a 24-B **GPS PERCEPT** (lat/lon
  1e7, alt, quality, sats, HDOP, epoch — a PERCEPT payload convention, no new toot type/RFC).
  Compiles at **78% flash; not yet flashed.** **Companion:** `companion.py gps --node tdeck_1
  [--at <static-node>]` reads a fix and records it as a ground-truth tie in
  `master/gps-fixes.md`; `companion.py anchor` fits the relative `positions.md` map onto the
  GPS ties by a closed-form 2D Procrustes (scale+rotation+translation, **reflection allowed**)
  → absolute-lat/lon `@BELIEF:POSITION` in `master/anchored.md`, **resolving the mirror when
  ≥3 non-collinear ties exist** (2 ties fix rotation+translation but leave flip ambiguous —
  emitted honestly as `flip_resolved: false`). `tests/test_anchor_py.py` 20/20: a 3-tie fit
  recovers synthetic geo within **0.3 cm** incl. the non-tie node, flip resolves at 3, and a
  scale far from 1.0 warns (calibration guard). GPS stays verifier+anchor only, never an
  inference input (keeps the proof non-circular).
- **GPS READ ✅ LIVE ON HARDWARE (2026-07-10, T-Deck COM10) — first fix decoded, first try.**
  Flashed the GPS firmware (auto-reset cooperated — no manual BOOT/RST this round; FS untouched,
  TTDB persists). `companion.py gps --node tdeck_1 --port COM10` returned a clean **12-satellite
  lock indoors** (`43.6524992, -116.3364675  alt 806.1 m  HDOP 1.1`) — the u-blox is on UART1,
  the auto-baud found it, the NMEA GGA parser decodes real signal, and `CMD_GET_GPS` → 24-B GPS
  PERCEPT round-trips over USB-CDC. The roaming anchor instrument works. **Remaining for the
  anchor:** collect ≥2 (ideally ≥3 non-collinear) ties — stand the T-Deck beside each static
  node and `gps --at <node>`, then `anchor`. Caveat: GPS ~1–3 m accuracy vs a ~4 m bench means
  the ties mainly resolve rotation + the **mirror** (the SP2 goal); sub-GPS pair *distances*
  still come from the calibrated RSSI embedding, not GPS.
- **SP2 GPS ANCHOR CLOSED ON HARDWARE + FIRST GPS-SCORED VERIFICATION ✅ (2026-07-10) —
  proof leg 1 is operational, and it immediately earned its keep.** Ran the full SP1→SP2
  loop at real outdoor scale: cleared bench percepts, spread the 4 nodes across a garden
  (V4-A desk / K10 "nutrient station" / V4-B "greenhouse seating" / T-Deck "back 40",
  ~6–17 m apart by GPS), accumulated ~10 link-percept windows, rebuilt `proximity`→
  `positions` (a ~35 m relative quad), then took **4 DGPS ties (HDOP 0.6–0.7, 12 sats)** by
  carrying the T-Deck to each node and `gps --at`, and ran `anchor`. **Result:
  `flip_resolved: True`** — 4 non-collinear ties pinned rotation + mirror; absolute lat/lon
  written to `master/anchored.md`. **The verifier then did its real job:** `anchor`
  auto-flagged `scale 0.2768 (WARN)` / `tie_rmse 4.98 m` — the RSSI map is **2–7× too large**
  vs GPS truth, and worse, **RSSI is decorrelated from distance here** (the *closest* pair,
  V4-A↔T-Deck 6.0 m, had nearly the *weakest* signal, −84.8 dBm ≈ 30 dB excess loss; a fresh
  GPS-truth path-loss fit gave a nonsense n=0.53, rmse 6.6 dB). **Root cause:** the SP1
  calibration is *through-house* (n=4.84) and doesn't transfer outdoors, and 2.4 GHz among
  ground-level nodes + vegetation is **shadowing-limited, not distance-limited** — per-link
  excess loss swamps the range signal. **This is exactly what proof leg 1 exists to catch:**
  GPS independently scored the emergent RSSI belief and quantified where it fails, honestly
  and automatically (the scale-guard fired on its own). Takeaways: (1) the GPS anchoring
  *mechanism* (flip resolution, coordinate transform, tie recording) is verified end-to-end
  on hardware; (2) RSSI-only ranging needs per-environment recalibration (low payoff here —
  the correlation is gone) or, better, the **SP0 multi-tier evidence** (BLE near-range,
  entity co-occurrence, TDoA) to survive obstructed real sites; (3) `master/gps-fixes.md`
  now holds DGPS ground truth for all 4 nodes — the map's true geometry, GPS-scored.
- **SP0 BLE near-range tier BUILT + compile-verified (2026-07-10) — a second, independent
  ranging radio, motivated directly by the garden RSSI failure above.** New portable advert
  codec in Toot (`buildBleAdvert`/`parseBleAdvert`: a 10-byte manufacturer-data blob =
  company+magic+version+node_id + a 2-byte **key-derived tag** so only key-holders count as
  evidence; a beacon is replayable so it's key-possession, not per-message auth — native-tested,
  `test_toot` 10 new checks). New ESP32-only glue lib **`firmware/libraries/BleLink`** wraps the
  core BLE stack: each node advertises its fleet id and **passively, duty-cycled** scans for
  peers (37% window so ESP-NOW/WiFi coexist via the radio arbiter), decoding each fleet advert
  and feeding **`(peer, rssi, PROTO_BLE)`** into the *same* `LinkPercept` histogram as ESP-NOW.
  **Zero new pipeline:** LinkPercept already had `PROTO_BLE`, `consolidate_proximity` already
  keys beliefs by `(pair, proto)`, and `calibrate --proto ble` already exists — so BLE windows
  flow straight through to `@BELIEF:PROXIMITY proto:ble` (added a BLE path-loss default:
  −59 dBm@1 m, n≈2). Wired into **V4-A/V4-B/T-Deck** behind `USE_BLE`; **all compile on the
  default partition** (V4-A 90%, V4-B ~90%, **T-Deck 95%** — Bluedroid fits with 64 KB to
  spare, so no NimBLE/partition change and the FS/TTDB offset is untouched). K10 deferred (2.x
  core, same as its ESP-NOW SP0 deferral).
- **BLE TIER ✅ ON-DEVICE (2026-07-10) — first proto:ble percept, + a T-Deck OOM crash found
  & fixed.** Flashed the T-Deck (COM10) and V4-A (COM6). With the T-Deck beside V4-A, a fresh
  60 s window on V4-A logged **`peer:0x200 proto:ble n:56 rssi -81/-43/-40`** — V4-A's passive
  scan caught the T-Deck's advert 56×, verified the key tag, decoded id 0x200, logged PROTO_BLE
  through the existing @LAT97 pipeline. Clean negative control: only the T-Deck appears over BLE
  (K10/V4-B not advertising). BLE reads weaker than ESP-NOW (med −43 vs −29); the estimator uses
  `rssi_max` (−40). **Crash found + fixed:** the memory-tight T-Deck crash-looped with BLE on —
  `abort() on core 0`, backtrace `operator new`→bad_alloc→`std::terminate` (C++ exceptions are
  OFF) inside the core's `BLEAdvertisedDevice::parseAdvertisement` (a `vector<BLEUUID>`
  push_back), which parses **every** advert in range (all the neighborhood phones/beacons) →
  heap exhaustion. Fixed in `BleLink`: register the scan **`shouldParse=false`** and parse the
  manufacturer field (AD type 0xFF) from the **raw payload** ourselves — zero per-advert heap
  allocation. Reflashed; **30 s + 60 s clean, no abort** (was `rst:0xc`, not brownout — the core
  BLE lib is NimBLE-backed, per the backtrace). V4-A didn't crash (far more free heap) but shares
  the fixed lib. **Gotcha:** old percept windows persist across an app-flash and fill the
  48-record @LAT97 cap, dropping new BLE windows until `cmd --op clear-percepts`. **Still to do:**
  reflash V4-A/V4-B with the fixed lib, flash V4-B (3rd advertiser), then `proximity` emits
  proto:ble beliefs vs ESP-NOW + GPS truth — the point being BLE's short range should hold up
  where far ESP-NOW ranging decorrelated.
- **BLE FLEET COMPLETE (3 nodes) + K10 BLE BLOCKED by its 2.x core (2026-07-10).** Reflashed
  V4-A + V4-B with the crash-fixed lib and flashed all three; **all 3 BLE pairs confirmed
  on-device** (V4-A↔T-Deck, V4-A↔V4-B, V4-B↔T-Deck — V4-B hears both peers at n:57/63) and
  `proximity` produced the **first `proto:ble` @BELIEF:PROXIMITY records** (`master/
  proximity-ble.md`), separate from espnow, same pipeline. **K10 BLE attempted + reverted:**
  it compiles (30% of the K10's 5 MB partition) and flashes, but **crash-loops** — `abort()
  on core 1` in `BLEDevice::init → btStart → esp_bt_controller_enable → coex_core_enable`:
  the **DFRobot UNIHIKER 2.x core has no software WiFi/BT coexistence**, so BLE can't run
  alongside ESP-NOW. Not a code bug — needs a **3.x core** on the K10. Reverted to `USE_BLE 0`
  (K10 verified stable: agent + pulse running); the BLE scaffolding stays gated in the sketch,
  one flag from a future core bump. The cross-core BleLink fix (std::string vs String) is kept.
  K10 remains ESP-NOW-only, mapped one-directionally. See [[ble-near-range-tier]].
- **SP6-T — THE T-DECK DRAWS THE FLEET AS A GLOBE ✅ on-device verified (2026-07-11), the
  end-goal render leg is live.** The console screen is now a native **TTCP mini-renderer**
  (PLAN.md SP6-T): a trackball-navigable **globe** (top half, off-screen `GFXcanvas16` in the
  8 MB PSRAM, block-pushed flicker-free) + **record view** (bottom half) + a **console log pane**
  (SPACE/`n` toggles it — the non-touch "swipe" analog). Nodes are drawn at their believed
  `@LATxLONy` with name labels, **sigma uncertainty rings**, `relates:` edges **coloured by
  transport** (green ESP-NOW / amber LoRa), a faint **graticule**, and 3 **zoom** levels
  (TTCP-RFC-0002). The enabler was the **huge_app repartition** (3 MB APP, build ~40% full);
  the FS moved to the huge_app spiffs at **0x310000 / 0xE0000**, flashed with the new
  **`scripts/Upload-Tdeck-FS.ps1`** — **not** `Upload-V4-FS.ps1` (which writes 0x290000; wrong
  offset silently drops the LittleFS superblock → the node boots to an empty globe /
  "(no record selected)"). Trackball reads via falling-edge ISRs (roll→rotate, click→select-
  next-node). Verified first try: huge_app boots + PSRAM inits, FS mounts at 0x310000 (pull
  byte-exact 1351 B, sha `fd95360b…` — repartition didn't disturb the floor), and the PSRAM
  globe canvas allocates + renders (user confirmed the globe + record text, not the low-RAM text
  fallback). See CLAUDE.md T-Deck FS note, [[tdeck-flash-partition-ceiling]].
- **`companion.py fleetmap` ✅ (2026-07-11) — the map the mesh draws of itself.** Generates the
  T-Deck's on-flash `data/ttdb.md` from the fleet's real beliefs: `master/positions.md` (node
  `@LATxLONy` + `sigma_m`) + `master/proximity.md` (per-pair links + transport) → one TTDB
  record per node with `relates:` edges. So the laptop viewer
  ([antfriend.github.io](https://github.com/antfriend/antfriend.github.io)) and the T-Deck
  render **one TTDB lineage** — rearrange the bench, re-run SP1→SP2→`fleetmap`→re-flash-FS and
  both screens show the new geometry (the SP6 "Done when").
- **On-device RFC browser ✅ (2026-07-11) — the T-Deck carries its own governing specs.** A
  **second globe view** (`VIEW_RFC`, `n`/toggle cycles VIEW_FLEET "SemPos" ↔ VIEW_RFC "RFC")
  renders `RFCs/rfc.ttdb.md` — the 8.4:1-compressed RFC corpus (one node per RFC, `depends_on`
  edge graph) — as a browsable globe + record view on the handheld. View-only: the RFC globe
  **never touches the mesh** (`gRfcDb` is a separate reader from the shared/synced `gDb`). A
  robot now literally holds and displays its own rulebook.
- **SEMANTIC POSITIONING promoted to a normative RFC ✅ (2026-07-12) — `TTN-RFC-0011`
  (Experimental).** The adopted primary hypothesis (`ttn-semantic-positioning.md`) now has its
  formal/normative half: `RFCs/TTN-RFC-0011-Semantic-Positioning.md` states the Semantic
  Positioning Hypothesis formally, the umwelt-overlap measure + embedding procedure, and —
  critically — the two conditions under which it fails. **Status: Experimental** — the evidence
  + verification layers are live (SP0 RSSI histograms → `@LAT97`, the T-Deck GPS verifier with
  DGPS lock, flip-resolution + scale-guard firing = proof leg 1 mechanics), but the central
  claim (Ω ↓ distance, semantic overlap beats RSSI-only) is **not yet confirmed**: the
  2026-07-10 garden run returned a partial negative on the RSSI leg (§9 field note), and §8.1
  spacetime entanglement is the blocking open problem. Numbered 0011 (0009/0010 were taken by
  Push-Back/Pulse); it is in `RFCs/INDEX.md` and its on-flash `rfc.ttdb.md` record is synced so
  the T-Deck browser carries it. `ttn-semantic-positioning.md` stays the operative build plan;
  this RFC is its normative half.
- **SP2 publish-positions-back BUILT + offline-verified (2026-07-12) — `push --positions`.**
  The last open SP2 item: `companion.py push --positions` (relative `master/positions.md`) /
  `push --anchored` (geo `master/anchored.md`) re-authors the fleet's `@BELIEF:POSITION` map as
  a belief and ships it over the **existing TTN-RFC-0009 `TTDB_PUT` → `/belief.md` rails** — so
  **zero new toot type** (RFC-before-code convention respected) and it works against the
  **already-flashed nodes** (they store byte-exact + CRC-attest, the same path the sync belief
  proved). Each record is tagged `node_id: 0x…` so a node can later find its OWN coordinate by
  matching its numeric id (the SP4 hook; the publish itself doesn't yet make a node *act* on its
  position — that's SP4). New `author_position_belief()` reuses the `push_belief` slice
  delivery, belief-log, and byte-exact readback verification unchanged; the DIRECTIVE cadence
  assertion is skipped for a position belief (it carries coordinates, not policy). Gated by
  `tests/test_position_belief_py.py` (19 checks, all pass); smoke-authored from the real
  `master/anchored.md` → a 2097 B / 4-node belief, crc `6C9FF6BB`. **Pending:** one live bridge
  round-trip (`push --anchored --node <n> --port COM6`) to confirm on-device adoption — no
  reflash needed. (Aside: `tests/test_prox_py.py` has a **pre-existing** failure — "unknown
  proto → no distance", present on clean HEAD, unrelated to this change; worth a look.)
- **SP0 entity co-occurrence tier BUILT + offline-verified (2026-07-12) — WiFi-scan percepts.**
  The second SP0 evidence tier (the sibling of LinkPercept/BLE): new portable lib
  `firmware/libraries/EntityPercept` accumulates per-window WiFi BSSID sightings (dedup by MAC,
  sighting count + strongest RSSI) and flushes one `@LAT96` record per window (`**ENTWIN**`
  context + one `**ENTITY**` line per AP) — same fixed-buffer, no-per-sighting-flash, lane-cap
  discipline as the `@LAT97` link lane. Two nodes seeing the same APs are probably near each
  other; `companion.py` folds the **Jaccard overlap of their BSSID sets** into a coarse distance
  **bound** (`consolidate_entity_jaccard`, down-payment on SP1's entity cap). Wired into **V4-A +
  V4-B behind `USE_WIFI_SCAN`** (default off): a **non-blocking async `WiFi.scanNetworks`** every
  10 min that folds results into the log and **re-asserts the ESP-NOW channel** afterward (the
  scan hops channels). New `companion.py entities --node <n>` dumps the lane. Gated by
  `tests/test_entitypercept.cpp` (20 checks, zig c++) + `tests/test_entity_py.py` (16 checks).
  **✅ ON-DEVICE VERIFIED 2026-07-12 (V4-A COM6):** flashed with `USE_WIFI_SCAN 1` (firmware-only,
  TTDB persisted — no FS reflash), and `companion.py entities --node v4a_bridge` returned a
  **`@LAT96` window with 8 real WiFi APs** (RSSI −31 to −97 dBm) — the SP0 entity 'Done when',
  live. **ALL FOUR NODES flashed + verified** (V4-A COM6 / V4-B COM9 / K10 COM3 / T-Deck COM10 —
  8/8/5/6 real APs). **The K10 is a first-class positioning contributor for the first time** — a
  WiFi scan is pure WiFi, NOT the BT coexistence its 2.x core lacks (the thing that crash-looped
  BLE), so the entity tier runs on the K10 where BLE and per-frame RSSI can't; it was only ever
  observed one-directionally before ([[k10-wifi-scan-entity-tier]]). **First live COMPLETE fleet
  co-occurrence graph — all 6 pairs** (Jaccard): K10↔T-Deck 0.83, T-Deck↔V4-A/V4-B 0.75, K10↔V4-A/
  V4-B 0.62, V4-A↔V4-B 0.60 → every pair bound ≤ ~58 m (honest upper bounds at ~0.3 m bench spacing —
  the entity term *caps* distance, doesn't refine it). The whole fleet's physical proximity now
  falls out of shared WiFi APs, independent of RSSI. T-Deck kept on (roaming node — richest
  co-occurrence source). **Tradeoff:** the ~2 s scan hop every 10 min briefly pauses V4-A's bridge
  relay (masked by the pull self-heal, but note it if a scan lands mid-band).
- **SP1 entity cap BUILT + offline-verified (2026-07-12) — shared APs clamp the RSSI estimate.**
  `companion.py proximity` now pulls each node's `@LAT96` lane alongside `@LAT97`, fuses the
  pairwise **WiFi-AP Jaccard** into a distance **bound** (`consolidate_entity_jaccard`), and folds
  it into `consolidate_proximity`: shared APs **cap the RSSI estimate from above** (never refine
  below — spec §2.2). Each `@BELIEF:PROXIMITY` now carries a **`sources:` evidence mix**
  (`{ rssi, entity_jaccard }`) + `entity_jaccard`/`entity_bound_m`/`entity_capped` fields, and the
  `proximity` table gained `entJ`/`cap` columns. At bench range the RSSI estimate sits under the
  bound so it's uncapped (mix only, no clamp); **the cap fires in the field** when RSSI over-ranges
  a pair that clearly shares APs — the exact garden failure (RSSI 2–7× too large). Gated by
  `tests/test_prox_py.py` (now 41 checks: over-range clamps to bound, no-refine-below, sources mix),
  smoke-verified end to end (`proximity --no-pull` on a crafted 2-lane node file).
- **SP1 BLE second bound BUILT + offline-verified (2026-07-12) — the tighter near-range cap.**
  `apply_ble_bound` folds each pair's `proto:ble` estimate in as a second, tighter cap: BLE is a
  ~10–30 m radio, so a pair heard over BLE is bounded tighter than by WiFi entity overlap. Bound =
  the BLE estimate's upper confidence edge (`dist + k·sigma`); caps the espnow distance from above,
  never refines below, and adds a `ble` term to the now-**three-way `sources:` mix**. **Layered,
  verified end to end:** a −90 dBm espnow pair over-ranges → entity caps to ~30 m (WiFi covisibility)
  → BLE caps tighter to ~5 m → `sources: { rssi: 0.59, entity_jaccard: 0.24, ble: 0.18 }`. Gated by
  `tests/test_prox_py.py` (now 51 checks). The SP0/SP1 evidence stack is now complete: RSSI (ranging)
  → entity Jaccard (loose cap) → BLE (tight cap), each honest about what it does.
- **MULTI-TIER FIELD RE-RUN ✅ RAN (2026-07-13) — the hypothesis-crux test; the stack did NOT
  yet beat RSSI-only, but the BLE tier scored its first clean-path bullseye.** Same garden
  stations as 07-10 (V4-A desk / K10 nutrient / V4-B greenhouse / T-Deck back-40; GPS truth
  reused from `master/gps-fixes.md`, 6–17 m spread). Cleared V4-A's link lane, accumulated ~10
  fresh outdoor windows, built the full multi-tier `proximity` (espnow + proto:ble + entity
  Jaccard) → `positions` → `anchor`. **Headline: scale 0.2166 (WARN), tie_rmse 7.31 m,
  flip_resolved True** — same failure class as 07-10 (was 0.2768 / 4.98 m), NOT better; the
  embedding collapsed near-1D (26×2 m) vs the true ~17 m quad. **Why it didn't improve:** (a)
  the BLE near-range tier is genuinely right where the path is clean — **v4a↔tdeck BLE 5.96 m
  vs 5.9 m GPS truth**, the exact near pair ESP-NOW botched (15.56 m, 2.6× over); but (b) it is
  *destructively wrong* on a strong-reflection far path — **v4b↔tdeck read −50 dBm BLE / −39
  espnow → 0.35–0.6 m despite 14.6 m truth** (greenhouse↔back-40 has a reflective/LOS path V4-A
  is shadowed from), and SP1 treats BLE as a *tight* bound so it **clamps the estimate to the
  wrong small value with high confidence** — worse than no BLE. Net: BLE helped one pair, hurt
  another more. (c) **Data-collection floor failed for the far nodes:** V4-B's full TTDB pull is
  impossible over the shadowed air (ACKs a single ping, "no data" on any multi-frame stream) —
  it contributed observed-only (2 constraints, no k10↔v4b pair); the T-Deck couldn't be cleared
  over air (lane never pruned) and its pull partially corrupted. So this run tested mesh
  self-collection (which broke for the weak nodes) as much as the SPH. **Mechanisms all fired
  honestly** (4-tie flip resolution, scale-guard WARN, anchor Procrustes) — proof leg 1 caught
  the failure again and quantified it. Two concrete fixes fall out: a **BLE saturation/
  consistency guard** (don't let a saturated BLE read clamp a pair below what a *co-measured*
  espnow/entity says; treat BLE-strong-but-espnow-weak as a reflection flag, not a tight bound)
  and a **non-mesh far-node collection path** (dump each field node's flash over USB — carry to
  cable — for a clean test, since the mesh can't pull the very nodes it's measuring).
- **USB-COLLECTION CLEAN RE-RUN ✅ done same day (2026-07-13) — the definitive version, and it
  turns the morning's soft negative into a sharp one.** Carried V4-B + T-Deck to the cable and
  pulled both **byte-exact over USB** (V4-B 31.6 KB, T-Deck 34.5 KB, **zero corruption** — the
  mesh delivered neither; both were **capped at 48**, mostly bench, so `--last 12` filtered to
  each node's 12–14 garden windows and their lanes were cleared/un-capped over USB — reliable
  ACK where the over-air clear never landed), and refreshed V4-A (40 garden windows). Rebuilt on
  clean *bidirectional* data: **scale 0.4122, tie_rmse 6.71 m, flip_resolved True** — strictly
  better-formed than the morning dirty run (proper 2D **22×9 m** vs collapsed 26×2 m; scale
  0.22→0.41 toward 1.0; the catastrophic **v4b↔tdeck fixed 0.6 m→10.4 m** vs 14.6 m truth once
  V4-B's real weak side (−80) fused with the T-Deck's strong side (−35), asym 31 dB), and the
  espnow distance *ordering* is now **monotonic with truth** (v4a↔tdeck 12 < v4a↔k10 22 < v4a↔v4b
  39; true order 5.9<8.0<12.3). **Yet it still does NOT beat July RSSI-only (4.98 m) and stays
  ~2.4× mis-scaled.** With corruption, staleness, and BLE saturation all removed, the residual is
  **genuine per-link multipath**: 30–40 dB *directional* asymmetries on fixed paths (T-Deck↔V4-A
  −44 one way vs −87 the other on the same 5.9 m; K10↔T-Deck reads strong −41 at 13.4 m).
  **Conclusion: amplitude-based ranging (RSSI *and* BLE) is decorrelated from distance in this
  obstructed garden regardless of data quality or fusion logic** — the honest verifier (proof leg
  1: 4-tie flip resolution + scale-guard WARN) quantified it a third time. The productive direction
  is the **non-amplitude tiers** — entity co-occurrence (topological, already working), SP3
  environmental TDoA (timing), or ToF hardware (SP1280-class) — **not** further tuning the
  RSSI/BLE amplitude fusion. (Field note: the T-Deck was **hot / in direct sun** — shade it next
  time; heat shifts the S3 RF front-end + crystal and stresses the LiPo/GPS.)
  See [[rssi-ranging-shadowing-limited]], [[ble-near-range-tier]], [[multitier-field-rerun-jul13]].
- **SP1 BLE saturation/consistency guard ✅ BUILT + offline-verified (2026-07-14) — the first of
  the two 07-13 crux fixes, software-only.** `apply_ble_bound` no longer lets a saturated BLE
  spike clamp a pair below what a co-measured espnow tier measured — the exact 07-13 failure
  (v4b↔tdeck BLE 0.6 m clamping a 14.6 m pair with high confidence). The discriminator is
  **explicitly NOT asymmetry**: the clean USB run measured **30–40 dB directional asym on every
  path, good and bad alike** (v4a↔tdeck −44/−87 on the same 5.9 m), so asym can't separate the
  one BLE win (v4a↔tdeck 5.96 m, plausible) from the failure — an asym trigger would have thrown
  away the good reading too. The guard is the field's own signature, **"BLE-strong-but-espnow-
  weak"**: a BLE bound is suppressed only when it is **near-field-SATURATED** (point estimate
  `< BLE_SATURATION_DIST_M = 1.5 m`) **AND** a co-measured espnow says the pair is **far**
  (`espnow_dist > bound × BLE_CONSISTENCY_RATIO = 3`). Suppressed pairs are FLAGGED
  (`ble_reflection_suspect` + `ble_saturated` in the record, `ble?` in the table's cap column)
  and keep their espnow measurement; a *plausible* mid-range BLE (not saturated)
  still legitimately caps an over-ranging espnow, so the one BLE win survives. Wide-sigma
  saturated reads self-regulate (a loose bound can't clamp catastrophically, so `far_conflict`
  correctly declines to fire). Gated by `tests/test_prox_py.py` (now **63 checks**: failure
  signature suppressed, the BLE win preserved, the agreeing-bench near pair not flagged).
  **Not yet exercised on fresh field data** — the payoff needs the clean re-run below (this mixed
  bench+garden `master/*.md` has no tight-clamp-vs-far conflict, so 0 suppressed today, correctly).
- **V4 speaker (MAX98357A) added to firmware ✅ compile-verified, not yet flashed (2026-07-14) —
  the LoRa spine gets a voice.** New hardware on hand: the **Adafruit MAX98357A I²S 3W amp**
  (adafru.it/3006 — same chip the T-Deck already uses), to be wired to each Heltec V4. Wiring is
  captured in the repo-local **`max98357a-v4-wiring.html`** (Fritzing-style diagram, committed) +
  `hardware_specs.md` §2: **VIN→3V3** (not 5V — the 3V3 rail is live on USB *or* battery, so every
  V4 wires identically and a field node keeps its voice off-grid; ~1.3 W into 4 Ω, enough for a
  toot), GND→GND, **LRC→GPIO5, BCLK→GPIO7, DIN→GPIO6** (mirrors the T-Deck's I²S pins; free on the
  V4 — LoRa SPI is 8–14, OLED 17/18/21), **GAIN + SD float** (9 dB, amp-on mono). All three V4
  sketches got the same `USE_SPEAKER` block — the `ESP_I2S` `toneI2S()`/`playStartupToot()` lifted
  from `tdeck_console`, tone synthesized from loop()/setup() only (never a callback, the deferred-
  tone discipline). **This finally un-silences the fleet's timekeeper:** V4-A's Pulse part was all
  `REST` ("the V4 has no speaker") — now **V4-A sounds a low C3 kick on every beat** and **V4-B a G4
  accent on beats 2 & 4** (notes live in the `Score.h` phrase tables → re-voicing is a one-line
  edit). **V4-C gets the amp + boot toot only** (it has no Pulse membership yet — no engine/LED/OLED;
  joining the band is a separate change). All three compile clean under `esp32:esp32:esp32s3:
  CDCOnBoot=cdc` (**V4-A 92% / V4-B 93% / V4-C 72%** flash). **Not yet flashed or heard** — the
  audio path (I²S pins, amp wiring) can only be proven on the bench once an amp is soldered to a
  board; flash + confirm the boot toot and that the kick/backbeat lock to the band.
- **V4-C promoted to a full band member ✅ compile-verified (2026-07-14) — the rhythm section is
  complete.** The edge sketch had no Pulse membership (boot toot only); it now carries the shared
  `Pulse` engine + `Score` part like V4-A/V4-B, playing the **offbeat hi-hat — a C5 tick on the
  "&" of each beat** (steps 2/6/10/14), completing the kit under V4-A's kick (every beat) and
  V4-B's snare (2 & 4). Added: PULSE-beacon adopt + HELLO neighbor fast-lock in the recv callback,
  `gPulse.update`/`stepTick` servicing + HELLO beacon in loop(), GPIO35 LED flash, and a
  `buildStatus` **PULSE telemetry tail** answered on `CMD_GET_STATUS` (single-frame PERCEPT over the
  mesh, like V4-B) so **`companion.py band --nodes …,v4c_edge` can measure its phase** — the node is
  already mapped there (0x12 / "V4-C"). Band phase reads from the pulse clock, so it's measurable
  even though V4-C has no wall-clock time-sync (fields reported 0, honestly). Compiles at **72%
  flash**. **Known pre-existing caveat (unchanged):** V4-C still serves a TTDB burst *inline in the
  recv callback* (the scaffold's shortcut, not the deferred-to-loop() discipline V4-B uses) — fine
  for pulse/band, but a bridged `pull --node v4c_edge` could drop frames until that's refactored.
  **Not yet flashed** (V4-C hardware is unbuilt — see §2). **[Superseded below — full parity done.]**
- **V4-C brought to FULL fleet parity ✅ compile-verified (2026-07-14) — the edge is now a
  first-class Dream-Cycle participant, uniform with V4-B for a clean bench test.** Rebuilt
  `firmware/v4c_edge` from the *verified* V4-B relay so every node answers a bench test
  identically. It now carries the whole participant contract it was missing: **deferred + paced
  TTDB serve** (burst from loop() behind the TX-complete callback — this **resolves the "inline
  serve" caveat above**, so a bridged `pull --node v4c_edge` self-heals like the others),
  `want_ack` ACK + **dedup re-ACK** (TTN-RFC-0007 §5), **TIME_SYNC adopt + `@LAT99`** self-write
  (TTN-RFC-0008), belief **`TTDB_PUT` adopt + `@LAT98`** attestation (TTN-RFC-0009, store-and-attest
  like V4-B — no DIRECTIVE), **SP0 percepts** (LinkPercept `@LAT97` via the INFO recv callback +
  RSSI, BLE `proto:ble`, WiFi-scan entity `@LAT96`), **remote `CMD_CLEAR_PERCEPTS`**, `CMD_GET_STATUS`
  with the PULSE tail, and the **OLED status page** — plus the MAX98357A amp and its band **offbeat
  hi-hat** (C5 on steps 2/6/10/14). So `sync`/`reconcile`/`push`/`monitor`/`band`/`proximity`/
  `positions`/`anchor` will all treat V4-C exactly like V4-B once it's on the mesh. The edge role is
  preserved (LoRa long-haul + a PERCEPT-aggregation stub gated for Phase 3; it does NOT promiscuously
  re-broadcast — no `USE_RELAY_FORWARD`, unlike the mid-relay). Compiles clean at **93% flash**
  (same as V4-B — near-identical code). **Companion needs zero changes** (v4c_edge already mapped
  0x12 / "V4-C"). **Still hardware-unbuilt / not flashed** — this is firmware parity so a future
  third V4 drops straight in; worked-first-try is the expectation given it's a line-for-line adaptation
  of the on-device-verified V4-B.
- **V4-A speaker audio fixed on-device (2026-07-14, COM6) — square wave @ 8 kHz is the solution.**
  The hand-wired **MAX98357A on V4-A would not reproduce a sine** — startup toot + beat kick came
  out as clicks / plops / one blip / "finger-drumming," inconsistent boot-to-boot. Ruled out, in
  order: amplitude (max 32000 sine still blipped), the toot pitch (raised G3/C4→C5/G5), a
  **BCLK↔LRC swap** (firmware-swapped the pins as a no-rewire test — got silence, so wiring matches
  the doc), a **piezo** (it's a real 4 Ω 3 W dynamic speaker), and **firmware** (byte-identical to
  the on-device-verified T-Deck; GPIO5/6/7 are free on the V4). Resoldering every amp-header joint
  moved it plop→clean-blip (connection quality mattered) but didn't sustain. **Sample-rate sweep
  was diagnostic:** 44.1 kHz = silence, 16 kHz = one blip, **8 kHz = works** — higher BCLK degrades
  over the jumper wiring (a 12 s test tone delayed the OLED boot by 12 s, **proving the ESP32
  streams valid I2S the whole time** — the amp just wasn't reproducing it). The decider: a **440 Hz
  square** sustained loud and clean where every sine failed. **Shipped:** `toneI2S` now emits a
  **50 % square wave** (snaps ±22000) at **`I2S_RATE = 8000`**; startup toot, the C5 beat kick, and
  the T-Deck beep are all loud + clean. **Also added the missing `CMD_BEEP` handler on V4-A** (the
  K10 had one, V4-A didn't) — parsed in both the ESP-NOW recv path and the serial-CMD path, played
  **deferred from `loop()`** (toneI2S blocks, never call it from the recv callback). Root cause is
  still **marginal BCLK/LRC signal integrity**; shortening/soldering those two clock wires (off the
  breadboard) would allow smooth sine at 16 kHz again — but square-wave chiptune fits the fleet, so
  it's left as-is. **v4b_relay + v4c_edge carry the identical sine-based audio → same fix needed**
  (convert to square + 8 kHz, add `CMD_BEEP`) before their speakers work. Not yet committed.
- **Fleet boots SILENT — one T-Deck press plays/stops the whole band (2026-07-14).** The V4s
  used to auto-play their part on boot; now all three mirror the K10's `gPlayEnabled` gate (boots
  false, the step-clock keeps running for phase lock, only the audible/LED hit is muted). Play/stop
  is now **band-wide via a broadcast**: added `NODE_BROADCAST = 0xFFFFFFFF` (RobotTeamConfig.h); the
  T-Deck's `g`/`x` send `CMD_PLAY`/`CMD_STOP` to it (`emitCmdTo`), and every node honors a
  PLAY/STOP addressed to **its own id OR broadcast** (targeted ops — get-status/set-led/beep — still
  require an exact id, so a broadcast never storms replies/ACKs). Backward-compatible: an old T-Deck
  targeting a single node still starts just that node. V4-A flashed + verified (boots silent: 0
  `[part]` logs, `[pulse]` beacon still runs). Also this session: V4 audio **volume 22000→11000**
  (was super loud) and **all V4 tones dropped one octave** (toot C5/G5→C4/G4; kicks C5→C4, V4-B
  backbeat G4→G3) — square-wave harmonics carry the lower notes fine. **All six sketches compile
  clean** (K10 20%, T-Deck 39% huge_app, V4s 92%); only V4-A flashed — **flash T-Deck + K10 + V4-B/C
  to get the one-press-fleet behavior end-to-end.**
- **T-Deck audio matched to the V4 band voice (2026-07-14, flashed COM10).** The T-Deck kept its
  sine `toneI2S` after the V4 square-wave fix (its integrated MAX98357A on the LilyGo PCB reproduces
  sine fine — no marginal-wiring issue). Converted it to the same **square wave @ 8 kHz, amp 11000**,
  and its boot toot to **C4→G4**, so the whole band shares one timbre. Its Ode-to-Joy harmony
  (`kHarmNotes`, C4/D4/E4/A3/B3) was already in the register of the octave-dropped V4 parts, so the
  melody was left unchanged. Flashed + verified booting (globe + GPS intact; firmware-only). Note:
  T-Deck flashing still needs the manual bootloader dance when its native-USB port drops (hold
  trackball-click + tap RST → re-enumerates → flash → tap RST to boot).
- **K10 brought to fleet audio parity + flashed ✅ (2026-07-15, COM3) — the lead now shares the
  band's voice and the T-Deck's loudness.** The K10 was the last node still on DFRobot's
  `Music::playTone` — a **fixed full-scale sine (amp 32767)** with **no volume control** (amplitude
  lives in the library, not the sketch), so it couldn't be matched to the fleet. Replaced it with a
  local **`k10Tone()`** helper that writes I2S_NUM_0 directly (the same driver `k10.begin()`→`initI2S`
  installs, data_out = IIS_DOUT/GPIO45) as a **50 % square wave @ 8 kHz, amp 22000** — byte-for-byte
  the T-Deck's `toneI2S` timbre + amplitude (the T-Deck deliberately runs 22000, not the V4s' 11000,
  because its integrated speaker is ~half as loud; the K10's onboard speaker is closer to the T-Deck's
  class, so 22000 is the right match). Startup toot, the Ode-to-Joy melody hits, and `CMD_BEEP` all
  route through it; the dead `Music` object was removed. **This flash also lands the K10's
  one-press-fleet behavior** (broadcast `CMD_PLAY`/`CMD_STOP` on `NODE_BROADCAST` — was in the sketch,
  never flashed). Compiles 20% flash; flashed COM3 (auto-reset cooperated, FS/TTDB untouched — 40
  records intact) and **verified booting** (TTDB 13976 B, agent loop, WiFi scan, pulse all up; startup
  toot audible as the new square voice). Firmware-only — no FS reflash. **Not yet committed.** Pending:
  user confirms the K10 melody/toot loudness now matches the T-Deck by ear, and a live 2-node duet
  (K10 lead + T-Deck harmony) to confirm the shared square timbre locks.
- **Startup toots softened fleet-wide ✅ (2026-07-15) — boot signature 75% quieter, running
  audio unchanged.** The user judged the fleet's general loudness good but wanted the boot "toot
  toot" quieter. Each node's `playStartupToot` now passes an explicit amp at **25% of that node's
  fleet baseline** (K10 & T-Deck 22000→5500, the three V4s 11000→2750) via a per-sketch
  `STARTUP_TOOT_AMP` constant; the melody / kick / backbeat / hi-hat / beep keep the full baseline
  amp, so only the startup signature is softened. All five compile clean (K10 20%, T-Deck 39%
  huge_app, V4-A/B/C 92%). **K10 flashed COM3** (user confirmed it "sounds great") and **T-Deck
  flashed COM10** (auto-reset cooperated, only the huge_app APP region rewritten — FS/globe at
  0x310000 untouched); both confirmed good by ear. **V4-A flashed COM6** (boot toot C4→G4 @ 2750,
  beat kick keeps 11000) and **V4-B flashed COM9** — both hash-verified, K10/T-Deck/V4-A all
  confirmed good by ear. **Every built node now carries the quieter boot toot.** **V4-C flashed
  COM13 (2026-07-16)** — the fleet is now complete; no node remains compile-only.
- **V4-C hardware is REAL and flashed ✅ (2026-07-16) — the A-B-C spine is physically whole.** The
  third Heltec V4 arrived built; flashed on **COM13** (Espressif native USB, VID 303A/PID 1001 —
  note the fleet's other ports were absent this session, so identify by VID/PID, not by a
  remembered COM number). Firmware `esp32:esp32:esp32s3:CDCOnBoot=cdc` + TTDB image via
  `scripts/Upload-V4-FS.ps1 -Node v4c_edge -Port COM13` (default 4 MB spiffs @0x290000 — the V4
  script, *not* the T-Deck one); both hash-verified. Source needed **zero changes** — the
  fleet-wide square-wave/8 kHz audio and quarter-amp `STARTUP_TOOT_AMP` 2750 had already landed in
  `v4c_edge.ino`; LoRa + GNSS still gated (`USE_LORA 0` / `USE_GNSS 0`). Verified on hardware:
  `ping --node v4c_edge` **ACKed on attempt 1**, and `pull --node v4c_edge` returned **1840 B** vs
  the flashed 842 B — the base bytes byte-exact plus **two live `@LAT96` ENTWIN windows the node
  appended itself** (8 and 6 WiFi BSSIDs, strongest `f83eb025d3d2` at −33/−38 dBm). So the
  LittleFS mount, the TTDB serve, *and* the SP0 entity tier are all confirmed working on first
  boot — V4-C is producing positioning evidence unprompted. **Not yet exercised:** the inline-serve
  path over the *bridged* mesh, band phase (`band --nodes …,v4c_edge`), and audio by ear.
- **The four-piece band plays in time with V4-C in it ✅ measured on hardware (2026-07-16).** With
  V4-A back on the USB lead (**COM6** — it re-enumerated to its historical port, but V4-C had come
  up on COM13, so keep identifying by VID/PID) and V4-B / V4-C / T-Deck live on ESP-NOW,
  `companion.py band --probes 5` measured **three consecutive PASSes at ±8.5 / ±6.5 / ±7.6 ms**
  against the ±50 ms bound. All four report **conductor 0x10 (V4-A), era 1, 120 bpm** — V4-C
  adopted the fleet's pulse clock rather than self-appointing, on first boot. **V4-C's offbeat
  hi-hat is in the pocket** (+4.5 / −6.5 / −6.5 ms across the three runs).
- **Band phase needs a settle window — early samples lie (2026-07-16).** The *first three* runs
  after the nodes were engaged FAILed (±72.0, ±50.2, ±48.6) and looked like a **V4-B defect**: it
  read −72.0 then −50.2 while V4-C/T-Deck sat near zero. **That reading was wrong.** Three runs
  later V4-B was **−7.7 / −3.7 / −7.6** and every node passed; one run even showed V4-B dropping to
  `(no reply)` while V4-C *and* the T-Deck both swung to ≈−45 **together**. Nodes moving together
  is the tell — that's the shared reference/settle shifting, not per-node drift, since a genuine
  single-node fault can't move two other nodes in lockstep. **Practice: don't diagnose a node from
  one band sample taken right after power-up/join; take ≥3 with `--probes 5` and only trust a skew
  that persists.** A node whose skew tracks its neighbours' is not the problem.
- **K10 removed from the band roster (2026-07-16, user request).** `band --nodes` default was the
  stale `v4a_bridge,v4b_relay,k10_1` (predating V4-C + T-Deck joining); now
  **`v4a_bridge,v4b_relay,v4c_edge,tdeck_1`**. **Scope was deliberately limited to `band`** —
  `sync --expect`, `verify --nodes`, `monitor --nodes`, `reconcile --nodes` still list `k10_1`
  because K10 is still a **fleet** node (percept leaf); it left the *band*, not the fleet. **K10
  firmware untouched** — it keeps the Ode-to-Joy lead and rejoins if powered + probed explicitly.
  Consequence to remember: **the band is now percussion + harmony with no pitched lead** (kick /
  backbeat / offbeat hi-hat / T-Deck harmony) whenever the K10 is off.
- **V4-C's amp is AUDIBLE — the four-piece band sounds good, user-confirmed by ear (2026-07-16).**
  The last unverified thing about V4-C was whether its **hand-wired MAX98357A** actually moves air
  (an ACK only proves `toneI2S` ran). It does: the **offbeat hi-hat is audible** and the band
  "sounded pretty good" playing as kick + backbeat + hi-hat + T-Deck harmony (no pitched lead — K10
  was off, see the roster bullet). **V4-C is now fully verified end-to-end: flash → mesh → pulse →
  sound.**
- **⚠️ `cmd --op play` reports FALSE NEGATIVES on nodes with blocking audio (2026-07-16).** Sending
  `companion.py cmd --op play` per-node to `v4c_edge` / `tdeck_1` printed **"no ACK after 4
  attempts → NOT applied"** — **and yet both nodes had applied it and were playing.** `toneI2S`
  **blocks**, so once a node starts its part its ACK misses the retry window (RTO maxes at ~4 s)
  even though the CMD arrived. **Do not trust "NOT applied" from play/beep** — and do not re-send
  or start debugging the node's reachability on the strength of it (I did: chased a nonexistent
  V4-C fault while it was audibly playing). Confirm by **ear**, or with `ping` (which ACKs fine —
  V4-C ACKed a ping mid-episode).
- **Use the T-Deck's `g`/`x` to start/stop the band — it's the designed path (2026-07-16).** One
  keypress **broadcasts** CMD_PLAY/STOP to `NODE_BROADCAST`, so every member starts on the same
  toot and **no per-node ACK is needed** — it sidesteps the false-negative trap entirely. The
  companion's per-node `cmd --op play` is the awkward path: **the bridge does NOT rebroadcast**
  (`v4a_bridge` sets only its own `gPlayEnabled`), so starting the band from the laptop means one
  CMD per member, in a sequence whose ACKs are unreliable. **User confirmed `g`/`x` works.**
- **Stopping the conductor triggers a re-election + era bump (2026-07-16, observed).** `cmd --op
  stop` to **V4-A** (then conductor, era 1) handed the pulse clock to **V4-B (0x11) at era 2**;
  afterwards `band` showed `v4c_edge`/`tdeck_1` as `(no reply)` to status probes **while `ping`
  still ACKed**. Not diagnosed further (the band was playing fine by ear, so it was cosmetic here) —
  but **don't read a post-stop `(no reply)` as a dead node**, and remember the era latch survives
  reflash, so **cold-start the fleet** if the era/conductor looks stuck ([[pulse-tempo-lives-in-pulse-cpp]]).
- **PULSE chart carries a SCENE ✅ built + native-verified, all five sketches compile-clean
  (2026-07-18) — the chart now says WHAT to play, not just how fast.** The keystone for a
  multi-part song: `scene_id` (u16) joins the pulse chart (`TTN-RFC-0010 §4.1`, payload
  **28 B → 30 B**), so the band shares a position in a piece the same way it already shares
  a tempo. Putting it on the chart rather than in a message of its own is the whole point —
  it inherits both chart properties for free: it rides the **rare drift-paced beacon** (no
  per-scene chatter), and it **survives conductor handoff**, because `selfAppoint(takeover)`
  keeps the chart and only bumps the era. *Kill the node that is counting and the band keeps
  its place in the song* — that is the property the extension exists for, and it is asserted
  directly in `tests/test_pulse.cpp` (**38 checks, all pass** under `zig c++`), along with the
  beat not lurching across the handoff and a **cold start restarting at scene 0** (a takeover
  inherits; a cold band starts from the top). **Wire compatibility is two-way** (the fleet is
  flashed one cable at a time): a v1 28-B beacon parses as scene 0, and a v2 beacon parses on
  v1 firmware because its length check is `>= 28` — a half-reflashed band still shares one
  time-base, it just has no shared scene until the conductor is on v2. Same additive trick on
  the STATUS pulse tail (**43 B → 45 B**), so `monitor`/`band` keep working against an
  un-reflashed node. **Engine API:** `Chart.scene_id`, `setScene()` (conductor-only — a
  follower declines rather than forking the band; idempotent, so re-issuing doesn't churn the
  era; bumps the era + beacons immediately so everyone turns the page together) and
  `sceneChanged()`, an edge detector in the style of `tick`/`stepTick` that also fires on
  first adopting a chart, so **a node joining a running band selects the scene already in
  progress**. **Score.h** gained `Part`/`ScenePhrase`/`phraseForScene()` — a scene→phrase
  lookup where **nullptr means this node is SILENT in that scene**, a first-class state (it is
  what lets an ensemble enter progressively) plus a `kAllScenes` wildcard for a line that
  doesn't change. **New `CMD_SET_SCENE` (op 10)** drives it: only the conductor applies + ACKs,
  which is exactly why `--node broadcast` is safe (at most one node answers, so no ACK storm,
  and the operator needn't know who holds the baton); `companion.py cmd --op set-scene --scene N`,
  and the ACK reflects the *achieved* scene so a repeat still ACKs instead of looking like a
  failure. `band` gained a **scene column** and now **fails on a split scene** the same way it
  fails on two conductors. **Compile-verified at unchanged flash** (V4-A/B/C 92%, T-Deck 39%
  huge_app, K10 20%) — the change is essentially free. **Deliberately behavior-neutral: every
  node's part is still single-scene, so nothing sounds different until a song is authored.**
  (Toolchain note: the previous
  session's `zig` in `%TEMP%` had been **partially cleaned by Windows** — `libcxx/src` down to
  6 of 57 files, presenting as "unable to find zig installation directory"; re-downloaded to
  this session's scratchpad. Invoke it via PowerShell with native backslash paths; MSYS-style
  `/c/...` paths break its lib-dir resolution.)
- **SCENE ✅ ON-DEVICE VERIFIED END-TO-END — the whole band turned the page together
  (2026-07-18).** Flashed all four band members to v2 in one session (**V4-A COM6, V4-B COM9,
  V4-C COM13, T-Deck COM10** — ports identified by VID_303A&PID_1001 and each confirmed by a
  `ping` ACK *before* overwriting; firmware-only, every TTDB untouched, each node
  hash-verified + regression-pulled byte-exact afterwards: 52104 / 54290 / 36951 / 52026 B.
  The T-Deck's auto-reset cooperated — no manual BOOT/RST — and its FS at 0x310000 still
  mounts). **The proof:** `cmd --op set-scene --scene 1 --node broadcast --port COM6` →
  laptop → USB → V4-A bridge → ESP-NOW → the conductor (V4-B) applied it, bumped **era 8 → 9**,
  fast-beaconed, and **all four nodes reported `scene 1` at era 9, PASS ±10.9 ms**; the return
  trip to `scene 0` (era 10) landed the same way. So chart-scene authorship, conductor-only
  gating, the immediate re-beacon, and follower adoption are all confirmed on real hardware.
  **Bonus, unplanned:** before V4-B was flashed, a v2 V4-A ran as a follower of V4-B's **v1
  28-byte beacon**, reading scene 0 and staying tight — the two-way wire compatibility proven
  live in a genuinely half-reflashed fleet, not just in the test harness. K10 left on v1 (off
  the band roster, unpowered).
- **Two operational gotchas found while running the above (2026-07-18).** (1) **`cmd` resets
  whichever node holds the USB lead** (DTR/RTS on port-open; `band`/`sync` open cleanly), so
  **never command the conductor over its own cable** — the reset demotes it to a follower and
  it then correctly *declines* its own scene change. Drive the band **over the air through the
  V4-A bridge with `--node broadcast`** instead: only the conductor applies, so at most one
  node answers and the operator needn't track who holds the baton (which moved 0x10→0x12→0x200
  →0x11 across this session's cable shuffling — exactly why broadcast is the right path).
  Give the bridge a long `--settle` (35 s) so it re-adopts the live chart before relaying,
  otherwise it briefly self-appoints at era 1 and applies the scene to its own stale chart.
  (2) **`--node broadcast` silently never ACKed** — `send_reliable` filtered ACKs on
  `src == target`, and a broadcast's responder is the conductor's real id, not 0xFFFFFFFF.
  Found because the band *did* move to scene 1 while the CLI reported "NOT applied" (the
  [[band-play-ack-false-negative]] pattern, different cause). **Fixed** in `send_reliable`:
  skip the src filter for broadcast — the echoed `(src,seq,chunk)` still proves the ACK is
  ours — and print which node answered. Re-verified: `ACK from 0x00000011 (answered the
  broadcast) … APPLIED`.
- **V4 pulse rejoin is slow — the V4s never got the K10's returning-neighbor fast-lock
  (2026-07-18, pre-existing).** A reflashed/power-cycled V4 **self-appoints at era 1 and
  free-runs as its own conductor for up to a full `PULSE_RESYNC_PERIOD_MS` (30 s)** before it
  hears the real conductor and yields. Cause: the V4 sketches use `neighborIsNew()`, which
  fast-locks only a *brand-new* neighbor, whereas the K10 got `neighborNeedsLock()`
  (per-neighbor last-seen, re-beacons when one reappears after a >3 s gap — the power-cycle
  case) in the 2026-07-06 rejoin fix. Observed three times today (V4-C, the T-Deck, and V4-A
  after each `cmd` reset), each time resolving itself within a beacon period. Practical
  consequence: **a `band` sample taken within ~30 s of any reflash or power-cycle will show a
  split conductor/era and mean nothing** — the [[band-phase-settle-window]] rule, with a
  mechanism behind it.
- **Fast-lock ported to the V4s + T-Deck ✅ compile-verified (2026-07-18) — the
  "faster pulse reconvergence" backlog item is closed in code.** `neighborNeedsLock()` (the
  K10's per-neighbor last-seen + `NEIGHBOR_REJOIN_GAP_MS` 3000 re-lock) replaces
  `neighborIsNew()` in **v4a_bridge, v4b_relay, v4c_edge** *and* **tdeck_console**. The
  console was included deliberately even though it is normally a follower: it **held the baton
  at era 7 during this session's cable shuffling**, so leaving it on the old logic would
  recreate the bug whenever it conducts. Steady-state traffic is unchanged (a neighbor
  HELLOing every ~2 s never retriggers the lock); only a peer returning after a >3 s gap does.
  Costs **+52 B flash** per sketch (V4s 92%, T-Deck 39% huge_app). **V4-A + V4-B flashed
  (COM6 / COM9); V4-C + T-Deck still on the old build.**
- **⚠️ The fast-lock port did NOT measurably help — negative result, cause not yet
  confirmed (2026-07-18).** With V4-A conducting (era 11) *and carrying the fix*, V4-B was
  reset on the cable and its rejoin timed by polling `band` over its own USB (which uses
  `open_serial_no_reset`, so the polling itself does not disturb it): **app up by 2.8 s,
  self-appointed `0x11` era 1 at 8.0 s, adopted V4-A's era 11 at 17.5 s.** A working
  fast-lock should land ~4–6 s (right after V4-B's first HELLO at ~2.5 s); **17.5 s is
  instead exactly what catching V4-A's next *periodic* 30 s beacon looks like** (uniform
  0–30 s, mean 15 s), and an earlier run had it still unlocked at 10 s. So the extra beacon
  is probably not firing at all. **Two candidate causes, both untested:** (a)
  **`NEIGHBOR_REJOIN_GAP_MS` 3000 is marginal** — the V4 HELLO period is 2 s and a V4 boots
  in well under a second, so the observed HELLO gap across a reboot is only ~2.5–4 s and
  straddles the threshold, firing at best half the time (the K10, where this logic was
  proven, boots much slower — LittleFS + LCD — so its gap was reliably >3 s); (b) **radio
  dedup across a reboot** — a rebooted node restarts `toot_seq` at 1, so the conductor's
  `(src,seq)` dedup cache, still holding the previous boot's low seqs, **silently drops the
  returning node's HELLOs** — precisely the frames the fast-lock depends on. Note V4-B was
  reset twice in quick succession during this test, which makes (b) more likely, and
  `companion.py` already dodges this exact class of bug by using ms-resolution `toot_seq`.
  **Suggested robust fix, avoiding both:** have the conductor **beacon immediately when it
  hears a PULSE advertising an inferior chart** (a self-appointed era-1 node broadcasts one
  every few seconds; V4-A currently just ignores it via `better()`). That is a direct
  "someone out there needs correcting" signal rather than an inference from HELLO timing.
  Until this is resolved, **the [[band-phase-settle-window]] rule still stands unchanged** —
  the port is committed but must be treated as unproven, not as a fix.
- **Dedup-across-reboot RULED OUT by measurement (2026-07-18).** Hypothesis (b) above was
  testable: V4-A's `gDedup` is a **128-entry ring shared across all sources** (~60–85 s of
  fleet history at ~1.5–2 frames/s), and [v4a_bridge.ino:354](firmware/v4a_bridge/v4a_bridge.ino#L354)
  `return`s on a dedup hit **before** HELLO reaches `neighborNeedsLock` — so a returning
  node's replayed low seqs really could swallow exactly the frames the fast-lock needs.
  Two-condition test: **COLD** (V4-B left running 3 min first, so its post-boot low seqs had
  aged out of the ring) vs **WARM** (reset again ~30 s later, low seqs freshly re-cached).
  Prediction if dedup were the blocker: cold ≈ 5 s, warm ≈ 15 s. **Measured: COLD 17.5 s,
  WARM 15.2 s — no difference**, both just the periodic beacon. So dedup is NOT the cause.
  (The seq-restart-on-reboot exposure is real and worth remembering for other paths, it
  simply isn't what's biting here.) Remaining suspect is the marginal 3 s threshold: steady
  state gap is ~2 s and the reboot gap only ~2.3–4.5 s, so the trigger straddles it and fires
  at best coin-flip often. **Not chased further — replaced by the mechanism below.**
- **Conductor now corrects a stale chart ON SIGHT ✅ built + native-verified (2026-07-18) —
  evidence-triggered instead of timing-triggered.** New rule in `Engine::onBeacon`
  (`Pulse.cpp`): when a chart arrives that is **worse than ours and we hold the baton**, set
  `fastlock_` so the next `update()` beacons immediately. A rebooted node self-appoints at
  era 1 and **emits one beacon straight away** (`selfAppoint` sets `next_beacon_tx_ms_ = now`),
  so a single frame getting through is enough to pull it back in — no guessing from HELLO
  gaps, no dependence on a threshold that sits awkwardly close to the 2 s HELLO period.
  Guards: a conductor ignores **its own echoed chart** (the existing early return), and a
  **follower stays silent** so only one voice corrects. **This is a library-level change, so
  all five sketches inherit it with no per-sketch edit** — all five compile clean (V4s 92%,
  T-Deck 39%, K10 20%). `tests/test_pulse.cpp` now **45 checks**, incl. the correction
  beacon firing, the echo not firing it, and the follower staying quiet. **V4-B flashed
  (COM9).**
- **⚠️ The correction beacon ALSO did not work — n=9, and BOTH pulse fixes are now
  unproven (2026-07-18).** Rig: two USB ports available at last (V4-A COM6, V4-C COM13, both
  flashed with the correction build); **V4-B held the baton at era 12 and also carries it**
  (flashed earlier the same session), T-Deck absent/no-reply. Reset V4-C on its own cable and
  timed the rejoin nine times: **>40, 6.5, 14.5, 23.4, 17.5, 5.7, 21.9, 15.3, 27.0 s** —
  mean ~16.5 s, spread 5.7–27+. A working correction beacon predicts a tight cluster at
  ~5 s; this is **indistinguishable from a uniform 0–30 s wait for the periodic beacon**
  (expected mean 15 s), and the two fast samples are just the periodic beacon happening to
  be near-due. **Do not read 6.5 s as a success — n=9 is what killed the earlier n=1 and n=3
  readings that looked encouraging.**
- **Methodological warning that also undermines the earlier dedup "ruling out" (2026-07-18).**
  Both pulse fixes depend on a frame *from the rebooting node* reaching the conductor (its
  HELLO, or its self-appointed era-1 beacon). **The trial loop reboots the same node every
  ~60 s, so it re-induces the very dedup-across-reboot condition it was meant to test** — the
  rebooted node replays `toot_seq` 1,2,3… into a conductor ring that may still hold them.
  The earlier COLD/WARM test assumed a ~60–85 s ring-eviction time that was **estimated from
  traffic rates, never measured**, so it is not a sound refutation. Treat the dedup
  hypothesis as **open again, not eliminated.**
- **Next step is INSTRUMENTATION, not another guess.** Every result so far is indirect
  timing; nothing has ever observed the conductor deciding whether to beacon. The decisive
  test needs **the conductor on a cable**, watching its serial log while another node
  reboots. With both V4-A and V4-C cabled, that means **powering off V4-B** so the baton
  falls to V4-A (lowest id) — then reset V4-C on COM13 and watch COM6 for the extra
  `[pulse] beacon`. Add a temporary print of the `neighborNeedsLock` gap and the `fastlock_`
  decision before flashing. **Until then both fixes stay in as unproven** (native-tested,
  +52 B and a few lines, harmless) and **[[band-phase-settle-window]] stands unchanged**.
- **HERO'S-ARC SONG AUTHORED ✅ + flashed to the two cabled nodes (2026-07-20) — track ①
  built; the fleet's own history is now a six-scene score.** New
  **`firmware/libraries/Pulse/src/HeroArc.h`** holds the ENTIRE song as `score::Part`
  tables — one file is the whole score, so re-arranging the song is a data edit there,
  never a sketch or protocol change. The scenes replay the build history: **0 ALONE**
  (V4-A's kick keeping time by itself) → **1 ALLY** (V4-B's G3 backbeat answers) →
  **2 GROOVE** (V4-C's offbeat hats complete it — and still no pitched voice, audibly) →
  **3 ORDEAL** (everything falls away except V4-B's lub-dub heartbeat; this is where the
  conductor is killed live, and the chart — the song's place — survives the handoff, the
  property the scene extension exists to prove) → **4 RETURN** (the T-Deck back with the
  Ode-to-Joy harmony, the song's first pitched voice) → **5 FINALE** (the T-Deck carries
  the lead over the full groove; a K10 harmony row is pre-authored so its rejoin is a
  reflash, not a rewrite). All four band sketches now select their phrase per scene via
  `score::phraseForScene` (each sketch's `kPart` is a reference into HeroArc): **no row =
  SILENT in that scene**, the step clock runs while silent so every entrance lands on the
  grid, and mixed loop lengths (16-step grooves under 64-step melodies) stay locked
  because step-in-phrase is absolute-step mod length. The T-Deck is the storyteller's
  remote: **`o` = onward one scene** (capped at the finale; re-issuing is idempotent),
  **`r` = restart the tale** — both broadcast `CMD_SET_SCENE` (conductor-only apply, at
  most one responder) AND call `setScene` locally in case the console itself holds the
  baton; the status bar and every node's `[scene]` serial log now show the scene NAME.
  Compile-verified all four (V4s 92%, T-Deck 40% huge_app — the song is flash-free);
  **V4-A (COM6) + T-Deck (COM10) flashed** (ping ACK attempt 1 before and after;
  regression pulls byte-count-exact 52104 / 52026 B, FS intact). **V4-B + V4-C still run
  the single-scene build — they play their old part in EVERY scene until the cable visits
  them**, so the progressive-entry story is not performable until both are reflashed.
  Performance runbook (after their reflash): **cold-start the whole fleet** (a cold band
  starts at scene 0; the era latch keeps an old chart alive across reflashes), wait the
  settle window, `g` to play, walk the story with `o`, kill the conductor during the
  ORDEAL, `x` to stop. The 07-18 design choices — distributed finale score over
  `TtdbShare`, presence/proximity-gated scene advance, position-derived parts — remain
  the follow-on increments (the last is what makes the song serve `@LAT90LON50`).
- **FIRST PERFORMANCE ✅ — the hero's arc walked end-to-end on hardware, measured
  (2026-07-20).** V4-B (COM9) + V4-C (COM13) reflashed the same session (hash-verified,
  ping ACK attempt 1, regression pulls clean — V4-C's TTDB grew 36951→48599 B, all of it
  self-logged `@LAT96`/`@LAT97` percept windows, the SP0 tiers working as designed), so
  all four members carry the score; the user committed the code and performed with V4-A
  back on the cable. A laptop watcher (`band --probes 2` every ~10 s through the bridge)
  recorded the story: **scene 0→1→2→3→4→5 over ~2.5 min, each `o` press bumping the era
  exactly once (era 1→6 tracks scene+1), every full-reply sample showing all four nodes
  on the same scene, conductor V4-A (`0x10`) throughout, typical tightness ±5–12 ms
  (PASS on every all-reply sample)** — chart-scene authorship from the T-Deck keys,
  broadcast conductor-apply, and follower page-turns are now *performance*-verified, not
  just set-scene-verified. Scattered single-node `(no reply)`s are the known transient
  bridged-probe misses, not defects. **Not exercised this run:** the ORDEAL
  conductor-kill — `0x10` held the baton across the whole log and scene 3 was passed
  through in ~10 s, so the handoff-survival moment of the story is still to be staged
  live. Audio is confirmed by ear only ([[band-play-ack-false-negative]]); the watcher
  went silent at 17:02:57, consistent with the bench being powered down after the finale.
- **THE LAPTOP CAN CONDUCT ✅ (2026-07-20) — second performance, driven end-to-end from
  `orchestrator/conduct.py`.** One serial session on the bridge, opened **without** the
  DTR/RTS reset, runs the whole show: per-node `CMD_PLAY`/`CMD_STOP` (the bridge doesn't
  rebroadcast those), broadcast `CMD_SET_SCENE` walking the scenes on a musical schedule
  (ALONE/ALLY/GROOVE 8 s each, ORDEAL held 12 s, RETURN 16 s, FINALE 24 s), and a fresh
  **ms-resolution `toot_seq` per send** so consecutive cues aren't dedup-dropped at the
  far nodes. Ran 17:09–17:11: 4/4 play ACKs (V4-C/T-Deck on attempt 2 — the blocking-tone
  delay), all six scene changes ACKed attempt 1–2, 4/4 stops, tale reset to scene 0.
  **Role clarification the run surfaced: every scene ACK came from `0x11` — V4-B holds
  the baton now** (the bench re-power after the first performance re-elected; V4-A is
  currently bridge-only follower). Bridge ≠ conductor: the laptop always enters through
  V4-A's USB, and the broadcast conductor-apply makes conducting work no matter where
  the baton sits — which is exactly why broadcast is the designed path.
- **▶ START HERE (handoff written 2026-07-18).** *One-line state:* the pulse chart now
  carries a **scene**, verified on hardware; **V4-A / V4-B / V4-C / T-Deck are all flashed**
  with that build and playing as one band (K10 is on the old build, off the band roster,
  usually unpowered). Everything below is committed on `main`. **Three tracks, in the order
  I'd take them:**
  - **① Author the hero's-arc song — ✅ DONE 2026-07-20 (bullet above): HeroArc.h authored,
    all four sketches scene-wired, V4-A + T-Deck flashed. Remaining: reflash V4-B/V4-C
    (cable visit) and perform it; design choices (a)/(b)/(c) below are the follow-ons.**
    This was the live creative thread the scene work was built for. The originating idea: a multi-part
    song shaped as a **hero's arc**, where the fleet's own history is the story (V4-A alone
    keeping time → V4-B's backbeat → V4-C's hi-hat completes the groove but there is still
    **no pitched voice** → the *ordeal* is the conductor dying and the song surviving the
    handoff → the roaming T-Deck returns with harmony *and* the map → **Ode to Joy** with
    everyone playing). Write it as `score::Part` tables (one `ScenePhrase` row per scene per
    node); **`nullptr` = silent in that scene** is the mechanism for members entering
    progressively. Three design choices worth keeping from the session that produced this:
    (a) **make the finale's score DISTRIBUTED** — split its phrase tables across the nodes as
    offset-addressed fragments assembled over the proven `TtdbShare` path, so "all must be
    present" is a mechanical truth and a missing member is *heard* as a hole rather than
    reported as an error; (b) **gate scene advance on presence/proximity**, so you walk the
    story forward by carrying nodes into the room — and with semantic positioning that gate
    is a measured belief, not a boolean; (c) **derive each node's part from its believed
    `@BELIEF:POSITION`** rather than its identity (Levin's positional-information idea), which
    makes the song an **audible renderer for the position belief** — a wrong map is something
    you can hear from across the room. That last one is the move that makes this serve the
    primary hypothesis instead of competing with it (see ③).
  - **② The pulse rejoin lag — OPEN, and it needs hands + instrumentation, not another
    guess.** See the 2026-07-18 entries above and [[pulse-rejoin-unsolved]]. **Power off
    V4-B** so the baton falls to V4-A (lowest id), flash V4-A with temporary prints of the
    `neighborNeedsLock` gap and the `fastlock_` decision, then reset V4-C on its cable and
    watch whether the extra beacon is emitted **at all**. Two fixes are already committed and
    **both are unproven** — do not add a third from timing inference. Two USB ports were
    available at the end of this session (V4-A COM6, V4-C COM13), which makes this practical.
  - **③ The standing primary hypothesis — still the highest-EPS thing in the project**
    (§7: @LAT90LON50, EPS 125). Unchanged by this session: the load-bearing move is a **clean
    multi-tier field re-run with USB far-node collection** (carry each garden node to the
    cable so its percepts pull byte-exact and its lane clears reliably), then
    `proximity`→`positions`→`anchor` against the DGPS ties, to see whether the BLE
    saturation guard + clean data finally beat RSSI-only (4.98 m).
  - **Operational reminders that cost time this session:** identify ports by
    **VID_303A&PID_1001**, never by a remembered COM number; **`cmd` resets whichever node
    holds the USB lead** (`band`/`sync` do not), so drive the band with **`--node broadcast`**
    through the V4-A bridge; and **wait 30–60 s after any reflash/power-cycle before trusting
    a `band` sample** ([[band-phase-settle-window]]).
- **Feelings globe + self-walking hero's-arc song ✅ BUILT + the auto-walk is ON-DEVICE
  VERIFIED (2026-07-24).** Two coupled features, all five sketches compile clean (T-Deck 40%
  huge_app, V4-A/B/C 92/93/92%, K10 20%). **V4-A, V4-B, V4-C, and the T-Deck flashed with the new
  firmware (K10 not yet); one `g` press walked the whole story autonomously** — captured on V4-B's
  serial as `scene 0 ALONE → 1 ALLY → 2 GROOVE → 3 ORDEAL` (V4-A conducting `0x10`, auto-advancing
  ~6 s/scene, era 10→13) then `→ 4 RETURN → 5 FINALE` (the T-Deck driving the turn: RETURN 5.7 s
  after ORDEAL = its `ORDEAL_HOLD_MS`, FINALE 9.6 s later = `RETURN_HOLD_MS`). So the conductor
  auto-advances 0→3 and **holds at grief**, and the T-Deck is the **only** actor past the gate —
  proving the grief-hold-until-roamer-returns behavior. **Bench lesson:** the conductor is whoever
  holds the baton, and the baton does NOT return to the lowest id on a reflash (era wins, lowest-id
  is only a tie-break) — a stale-firmware node (V4-C at era 8) kept conducting after V4-A/T-Deck
  were flashed, so the auto-walk didn't run until V4-C was reflashed and V4-A (new fw) reclaimed the
  baton at era 9. Followers on OLD firmware still follow the scene + play their part; only the
  CONDUCTOR needs the new code (plus the T-Deck for 3→5). **BOTH remaining checks then PASSED on
  hardware (user-confirmed 2026-07-24):** the feelings-globe screen renders the band eyeballs +
  live status, and the **explicit grief-gate power-cycle worked** — with the T-Deck powered off
  the band held at ORDEAL, and it jumped to RETURN→FINALE when the T-Deck returned. So the whole
  feature is end-to-end verified except the K10 (still on old fw — it follows scenes + plays its
  part fine as a follower; reflash it for the full six-instrument arc). Also added + verified: the
  T-Deck globe zoom now has **5 levels** (was 3) — two closer steps (`z4` 4.05×, `z5` 5.75×), and
  the node dots + eyeballs scale with `gZoom` so magnified globes keep proportional marks.
  - **Third T-Deck globe = the feelings landscape, now the DEFAULT power-up view.** The trackball
    click cycles **Feelings → Semantic Position → RFC** (`VIEW_FEELINGS=0`, skips any globe that
    didn't load). New TTDB `firmware/tdeck_console/data/feelings.ttdb.md` (the repo's
    `feelings_ttdb.md` + a band overlay), loaded as a view-only globe `gFeelDb` from
    `/feelings.ttdb.md` — **flash it with `scripts/Upload-Tdeck-FS.ps1`** (it's in `data/`, so
    mklittlefs picks it up). On this globe the **three other band members (V4-A/V4-B/V4-C) are
    always-on eyeballs** carrying a live status label (name + `*` if it holds the baton + "2s"/
    "LOST" from the HELLO last-seen) — parsed from each record's `name:`/`node:` lines
    (`gNodeMeshId`), repainted at 1 Hz; the affective records are dim, unlabeled dots. The globe
    never touches the mesh (like the RFC one).
  - **`g` now plays the whole hero's-arc song on its own, with a grief gate for the roamer.** New
    `Pulse::armSong/disarmSong/serviceSong` (RAM `song_armed_` + per-scene `scene_entered_ms_`):
    a **CMD_PLAY arms every node**, and whoever conducts auto-advances the early scenes on
    `heroarc::SCENE_HOLD_MS` (6 s) but **HOLDS at `SCENE_ORDEAL` (grief)** — so a mid-song T-Deck
    power-cycle leaves the band waiting at grief (V4-B's heartbeat loops there). The **T-Deck is
    the only actor past the gate**: when present + playing + locked at ORDEAL it dwells, then
    `emitSetScene(RETURN)`, then `(FINALE)` — so `g` plays end-to-end when it's present, and a
    returned T-Deck (gLocalPlay restored from NVS + the adopted ORDEAL chart) picks up right at
    the turn. Because every node arms on CMD_PLAY, the walk even **survives a conductor handoff**.
    Story pacing lives in `HeroArc.h` (`SCENE_HOLD_MS`/`ORDEAL_HOLD_MS`/`RETURN_HOLD_MS`).
    `o`/`r` still work for manual scene walking. **Needs the whole fleet reflashed** (shared
    `Pulse` engine change) + an on-device run to confirm the auto-walk timing and the grief-gate
    rejoin by ear/eye.
- **Next action — earn TTN-RFC-0011 its "confirmed" status (or falsify it).** The floor and all
  three render/verify mechanisms are built; what's unproven is the *hypothesis itself*. The
  load-bearing **multi-tier field re-run ran 2026-07-13 (bullet above) and did NOT yet confirm**
  (tie_rmse 7.31 m, no better than RSSI-only — BLE saturated on a reflective far pair even as it
  nailed the clean near pair). Of the two refined crux fixes, the **BLE saturation/consistency
  guard is now done ✅ (software, bullet above)**; the remaining one needs hardware: a **clean
  re-run with USB far-node collection** — carry each field node to the cable so its garden
  percepts pull byte-exact + its lane clears reliably (the mesh can't collect its own weak
  nodes), then `proximity`→`positions`→`anchor` and see whether the guard + clean data finally
  beat RSSI-only. `anchor` still scores against the DGPS ties in `master/gps-fixes.md`.
  Software-only moves I can do solo, in order: (a) **publish `@BELIEF:POSITION` back to nodes**
  (last SP2 item — ride the TTN-RFC-0009 `push` path, or a compact POSITION toot with the
  RFC-before-code convention); (b) the **SP6 laptop render leg** (author the master TTDB so the
  antfriend.github.io viewer renders it — discipline, not new code); (c) remaining SP0 tiers:
  **WiFi-scan `@PERCEPT:ENTITY`** co-occurrence, beacon RSSI piggyback, K10 RSSI via a 3.x core
  bump (BLE + promiscuous-RSSI both blocked on the K10's 2.x core). Then SP3 (env TDoA) → SP4
  (address loop) → **SP5 transport auto-switch** (proof leg 2, un-gates `USE_LORA`, needs a node
  walked out of ESP-NOW range). **Band/maintenance backlog (secondary):** confirm the T-Deck
  power-cycle rejoin; exercise the trackball roll/click/console-pane interactively; more
  tunes/parts; faster pulse reconvergence; V4 GPIO35 LED; V4-B relay forwarding; run the
  prepared **RFC-corpus round-trip demo** — flash `RFCs/rfc.ttdb.md` (33 recs, 31726 B) as a
  node's `/ttdb.md` and pull it back byte-diff (key gotcha: `TTDB_REQ` only pulls the
  *configured* file, so host it AS `/ttdb.md` — don't invent a request type; restore with
  `git checkout firmware/<node>/data/ttdb.md`; prepared 2026-07-08, not yet on hardware).

- **CARDPUTER ADV JOINS THE FLEET ✅ on-device verified (2026-07-27, COM14) — a 6th node,
  and the fleet's first NON-RADIO SENSES.** An M5Stack Cardputer ADV (`firmware/cardputer_console`,
  node id `0x300`) came up as a second handheld console — everything the T-Deck is (full
  Dream-Cycle participant + keyboard→CMD + TTCP globe screen) — plus two evidence tiers no
  other node has. Built from `tdeck_console.ino`, **compiled clean first try** (40% flash /
  22% RAM on `huge_app`) and worked on hardware with one fix.
  **Verified on the bench:** boots from TTDB with all three globes (`ttdb.md` 4166 B /
  `rfc.ttdb.md` 34 recs / `feelings.ttdb.md` 45 recs); **byte-exact pull** (4166 B, sha
  `c764ae3b…`); `negchecks.py` **wrong-key + tampered → 0 frames** (HMAC reject), serial replay
  served by design (radio-only dedup); `cmd --op beep` **ACK APPLIED attempt 1**; and it is
  **already on the mesh** — its first `@LAT97` window logged V4-A (`peer:0x00000010`) at
  −32 dBm over ESP-NOW, i.e. it authenticated real fleet traffic before anyone told it to.
  **Two NEW percept tiers, both live on first boot:**
  - **`@LAT94` ACOUSTIC** (`firmware/libraries/AcousticPercept`) — the ES8311 codec's MEMS mic,
    read as 8 kHz PCM through the same I2S port that drives the speaker. First window:
    **2706 blocks, rms_mean 122 / rms_max 300 / peak 638, transients 0** (a quiet room, honestly
    reported). The record carries the **fleet-clock timestamp of the loudest transient** — that
    is the SP Phase-3 TDoA datum: sound at 343 m/s makes ~10 ms of time-sync worth ~3.4 m, an
    error bounded by CLOCK quality rather than by foliage. This is the first tier that is not
    an amplitude measurement, which is exactly what the 2026-07-10 garden run said we needed.
  - **`@LAT95` MOTION** (`firmware/libraries/MotionPercept`) — a BMI270 sampled at 20 Hz, folded
    into a per-window `still|moving` verdict. It makes the assumption every earlier tier quietly
    relied on **checkable**: a window whose observer was walking is evidence about several
    places at once (the reason `proximity --last N` had to exist).
  - Also carries the existing `@LAT97` link + `@LAT96` entity tiers, so `CMD_CLEAR_PERCEPTS`
    on this node prunes **four** lanes (94-97), all-or-nothing so a partial prune fails loudly.
  **The one hardware fix:** the **BMI270 answers at the SECONDARY I2C address (0x69)**, not the
  `0x68` the ADV's published pin map implies — first boot printed `BMI270 NOT FOUND`. The sketch
  now tries both and, on failure, **scans and prints the whole I2C bus**, so the next missing
  device on that shared bus (keyboard 0x34 / codec 0x18 / IMU 0x69) is a one-line answer at the
  bench instead of a guess.
  **New shared code:** `firmware/libraries/Es8311` (the codec bring-up — nothing is heard or
  sounded until those registers are written; distilled from the Espressif MIT driver to the one
  configuration this board uses: I2S slave, 16-bit, **MCLK derived from BCLK** because the ADV
  routes no MCLK), plus `heroarc::kNewcomer` — the Cardputer's part in the hero's-arc song is to
  be **silent through the whole story and join only the finale**, because listening is its job.
  **A REAL PERFORMANCE BUG, found by measuring instead of guessing (2026-07-27).** The first
  `verify` **FAILED**: skew −254.6 ms at **rtt 419 ms**, when every other node reads 1–34 ms.
  Instead of chaining hypotheses off that timing, the sketch was instrumented to print its
  worst loop pass — which said **render 767 ms, worst pass 1022 ms**. Mechanism: `Ttdb::edgesAt()`
  **re-opens the TTDB file on every call**, and the globe called it once per record per frame, so
  a repaint of the 45-record feelings globe cost ~45 LittleFS opens. The toot link is serviced
  once per loop pass, so the slowest pass IS the node's response time. Fix: cache each record's
  edges in `parseNodeAttrs()`, which already reads that same header line — **zero extra I/O**.
  Re-measured: **render 767 → 68 ms, worst pass 1022 → 104 ms**, and `verify` now **PASSES at
  skew +10.6 ms / rtt 65 ms**. The loop profiler was left in (prints every 30 s) so the next
  node that goes sluggish on the mesh explains itself.
  **⚠ The T-Deck shares this defect** — same globe code, same 45-record feelings TTDB, and it is
  the node whose timing the band measurements lean on. Its sketch has NOT been patched or
  reflashed; that is a one-cable job whenever it is next on the bench.
  **Confirmed by the user at the bench (2026-07-27):** it **sounds and looks right** — the ES8311
  audio path works by ear (the blind codec bring-up was correct) and the screen renders. One
  correction needed: **`setRotation(1)` was UPSIDE-DOWN; it is `setRotation(3)`** — the identical
  correction the T-Deck's ST7789 needed, so treat 3 as the fleet default for these panels.
  Reflashed and confirmed.
  **Still unexercised (not broken — just not yet driven):** the 56-key TCA8418 map is
  *transcribed from published sources, not derived*, so each binding (`t`/`s`/`p`/`b`/`g`/`x`/
  `o`/`r`/arrows/ENTER/space/±) is unverified until pressed; likewise tilt-to-roll the globe.
  **Not built on purpose:** LoRa and GPS — the T-Deck stays the roaming GPS anchor and the
  SX1262 handheld.

- **The Cardputer has a resting face (2026-07-28).** First piece of
  [cardputer-sensorium.md](cardputer-sensorium.md) built: the **REPRESENTOR eyeball**, and the
  node now **boots into it** (`t` toggles back to the three globes). Gaze tracks gravity, so the
  eye looks downhill when the deck is tipped; the **gyro** — free all along, the SparkFun driver
  enables both BMI270 features in `begin()`, we were reading half the sensor — displaces the
  pupil on a flick and springs it back; a hard tap blinks it, and it blinks idly every 4–8 s.
  Pupil dilation is a **stand-in** for the arbiter's summed EPS (two raw terms, motion and sound,
  each against its own baseline) until phase S1 lands the real one.
  **Tuned at the bench the same day** (all five on request): gaze axes **inverted** — the eye ran
  uphill, so the chip's accelerometer frame is the opposite of the blind assumption, and the
  saccade is now scaled by the same constants so one flip fixes an axis end to end; eye **+15%**
  (R 64→74, so it is now *taller than the screen* and crops top and bottom, which reads as a
  close-up rather than a ball on a panel); iris **+15% on top of that** (26→34); the **corner beat
  dot is gone — the beat is now the pupil**, which widens on every beat and hardest on the
  downbeat; and the catchlight is **bigger and fixed in room coordinates**, so the iris slides
  under it instead of dragging it around (a specular highlight belongs to the light source, not
  the eye).
  **A second bench pass** made the blink **twice as fast and half as often** (one frame shut,
  idle every 8–16 s), the eyelid **black**, the iris ring **thick black**, and the catchlight
  3×. The 100 ms frame grid is the **floor on blink speed** — a blink is quantized to it
  whatever `BLINK_MS` says, so a partial-closure phase would have eaten the whole blink.
  **The budget was the design constraint, and it held — but the growth was not free.** Measured
  on hardware: **worst render 24 ms** (budget ≤25) for the most expensive recurring frame, the
  full-sclera repaint when a blink opens; **worst loop pass 37 ms** (budget ≤40, and it was
  **104 ms** before); `companion.py ping --node cardputer_1` **DELIVERED on attempt 1**. A frame
  where the deck sits still writes **zero pixels**.
  **Third bench pass — the face now runs on the BEAT, not on a frame clock.** Rendering happens
  only inside a ~220 ms pulse at the head of each beat (4 frames), and between beats the eye is
  entirely still: no gaze update, no repaint, nothing on the SPI bus. Every change it has to show
  is consolidated into those frames. With no other sensory input the beat is a **one-pixel**
  pupil dilation — you have to look to see it; arousal is what opens the swing up (to 7 px).
  Blinks now land ON a beat, one frame shut, and `BLINK_MS` is **derived from the frame interval**
  rather than set in absolute time, because a blink is quantized to the render grid regardless.
  When the band has no chart the face falls back to a **free-running local pulse** at
  `PULSE_DEFAULT_BEAT_MS` — the face's clock must never stop, or the eye freezes and looks broken.
  Visible consequence, and intended: the gaze now moves in **beat-quantized steps**, so the eye
  tracks a tilt rhythmically rather than smoothly.
- **The blocking microphone read: 30 ms → gone (fixed 2026-07-28). Worst loop pass 54 → 22 ms.**
  With the append fixed, the mic was the node's widest loop section. **Pacing it did not work,
  and the reason is the mechanism, not the tuning:** ESP_I2S configures the RX DMA with
  **`dma_frame_num = 240`**, and nothing is readable until a whole descriptor completes — at
  8 kHz that descriptor is exactly **30 ms** of audio, which is precisely what the section
  measured. A 128-frame (16 ms) request therefore waited for the full descriptor *no matter when
  it was asked*, so a poll gate was a no-op (and worse: with a 29 ms read, `now - lastRead` was
  always past any gate shorter than that).
  **Fix — align the READ to the DMA, keep what the TIER sees identical.** `serviceMic` now reads
  **exactly one descriptor** (240 frames) once per descriptor period, so the audio has already
  landed when we ask and the read returns at once. The samples then pass through a small carry
  buffer and reach `@LAT94` in the **same 128-frame blocks at the same 16 ms spacing as before**,
  each block's fleet-clock timestamp derived from how many frames still sit behind it. **The TDoA
  datum is unchanged** — only what waits for what.
  **Result:** worst loop pass **22 ms**, and the widest section is now the **render** (the
  blink-open frame). The loop is finally bounded by the face itself, which is where a display
  node's time should go. `mic` no longer appears in the profile at all.
  **AND IT WAS NOT ONLY A LATENCY FIX — THE ACOUSTIC TIER HAD BEEN SILENTLY DROPPING ~35% OF ITS
  AUDIO.** Verified after a `CMD_CLEAR_PERCEPTS` refilled the lanes (they were all at their cap of
  48, so the tiers had gone silent). Blocks captured per 60 s window, against a theoretical
  maximum of 60000/16 = **3750**:
  - **Before:** 1955, 2501, 2591, 2871, 2927, 2958 — **52-79%** of the stream.
  - **After:** 3198 (boot window), then **3732, 3720, 3742, 3615** — **99.2-99.8%**.

  The mechanism follows directly from the descriptor: the old code consumed 128 frames (16 ms)
  per call but *waited a whole 240-frame (30 ms) descriptor* to get them, so it drained barely
  half the stream and the rest was overwritten in the DMA ring. **Transient detection was
  therefore sampling roughly half the timeline** — any transient landing in a dropped span was
  simply invisible, and two nodes could disagree about whether a clap happened at all. For the
  tier that is supposed to deliver the fleet's first non-amplitude ranging measurement, that is a
  much more serious defect than the 30 ms it also cost the loop.
  **Timestamps confirmed against fresh records:** every `**TRANSIENT** t_ms` falls inside its own
  window (44686 / 63408 / 164436 / 198254 / 262930 against windows starting 0 / 60000 / 120000 /
  180000 / 240000), so the carry buffer's back-derived per-block timestamps are correct.
  **Residual:** the percept flush is now just the LittleFS write itself, observed **43-185 ms**
  depending on file state — once per 60 s per tier, and no longer O(file).
  Byte-exact backups of the pre-prune TTDB are in the session scratchpad (`card_ttdb.md`,
  `card_ttdb2.md`, 84061 B / 89157 B).
- **The percept-window flash append: 3.1 s → 43 ms (fixed 2026-07-28).** The spike this node had
  been carrying all along — and the reason it was growing session over session (676 ms at a 68 KB
  TTDB, **3111 ms at 81 KB**) — was never the flash write. `Ttdb::appendRecord` ended with
  `return begin(*fs_, path_)`: **a full re-scan and re-parse of the entire file on every append.**
  Two compounding costs underneath it, and the second is a defect the fleet has met before:
  1. `begin()` pass 2 called `readLine()` once per record, and **`readLine()` opens and closes the
     file on every call** — ~190 file opens per append. This is the *same defect class* as the
     `edgesAt()` per-frame trap (§6 above): the per-call open, not the bytes.
  2. `appendRecord` did not need to re-index at all. It knows exactly what it wrote and where it
     landed, so the index update is O(1); the re-scan was O(file), on a file that grows every
     window across four tiers.
  **Fixes:** `begin()` now does both passes through **one open handle** (new private
  `readLineFrom(File&, ...)`; `readLine()` keeps its signature for single-line callers like
  `edgesAt`), and `appendRecord` **indexes the appended block incrementally** — parsing the
  header(s) out of the text it just wrote and appending to the record table. Anything unexpected
  (a block starting with `@`, a header that will not parse, a full record table, or a file whose
  real size disagrees with the cached one) **falls back to the authoritative full scan**, so the
  index cannot silently drift from the file.
  **Verified on hardware, three ways** — there is no native test for `TTDB.cpp` (it needs Arduino
  `FS`; only `TtdbParse.cpp` is covered), so this was checked on the device: flush pass
  **3111 → 43 ms**; a `companion.py pull` reassembles **84061 B / 190 record headers**, matching
  the node's own `fileSize()` and its boot record count exactly; and the `@LAT96` lane numbers run
  **34, 35, 36, 37, 38, 39** across an append, a reboot and another append — consecutive, no gaps
  or repeats, which is the direct test that `laneCount()` is reading a correct in-memory index.
  **This helps every node**, not just this one — `begin()` runs at boot everywhere.
  **⚠ Now the largest remaining spike, and it is NOT the append:** the boot `[wifi] scan` blocks
  the loop for **~2.0 s** (widest section `entity`, which contains `serviceWifiScan()`). Once per
  10 minutes, pre-existing, untouched.
  **A visible artifact with a real cause, reported from the bench and fixed:** the iris showed
  momentary **vertical black bars** on every pupil change. Cause: `Adafruit_GFX::fillCircle` fills
  with **vertical spans**, and `drawIris` painted a full black disc and then covered it with red —
  so the black infill was visible sweeping through before the red landed. Filling a circle you are
  about to cover costs the pixels twice *and* you can see it. Two fixes: the limbal ring is drawn
  as a **ring** (`drawRing`, horizontal spans, batched), and a **pupil-only change no longer
  touches the iris at all** — it paints just the circumference between the old and new radius,
  black outward to dilate and iris-red inward to constrict. That is the resting case (a one-pixel
  ring on the beat), so it is now the cheapest thing the face does. Worst render **24 → 22 ms**.
  **⚠ THE REAL LOOP-BUDGET CULPRIT IS THE MICROPHONE, NOT THE SCREEN (found 2026-07-28).** The
  beat change appeared to blow the budget — worst pass 41–54 ms at n=8, against ≤40. It did not.
  The profiler was made to report **which section** of the pass was widest (and the render cost
  *of that same pass*, since "worst pass 53 ms / worst render 24 ms" never said whether they were
  the same pass). Answer, every window: **`mic` 29 ms**, with the render only 11–15 ms of it.
  Root cause in `serviceMic`: **`I2SClass::available()` is a stub that returns the constant 1920**
  regardless of what is buffered, so the `if (avail < sizeof(block)) return;` guard has never once
  fired — it is dead code. `readBytes()` then **loops until it has the full request**, blocking on
  the DMA for a whole 512-byte block = 128 stereo frames @ 8 kHz = **16 ms of audio** (~29 ms
  observed with DMA granularity). The node is pacing its main loop on the microphone: it waits
  for sound to happen in real time, once per pass.
  **Not fixed, deliberately — this is a decision about the primary hypothesis's instrument.** The
  obvious fix (read a smaller chunk per pass) changes the block size the `@LAT94` tier computes
  per-block RMS and transient timestamps over, which is the TDoA datum. That is not a drive-by
  change. Options: smaller blocks + re-verify the tier, or drain in a task/callback. **This is now
  the #1 thing standing between this node and the ≤40 ms budget** — the face costs 24 ms worst.
  **The section profiler was left in** (five `millis()` stamps, reports the widest section of the
  worst pass), on the same reasoning as the loop profiler: the number that explains the next
  slowdown should already be on the wire.
  **The budget caught a real breach and the fix was ordering, not cutting the feature.** Adding
  the limbal ring took the blink-open frame to **26 ms** — over. `renderEye` now works out the
  geometry *before* painting anything, so both expensive repaints skip the disc the iris is
  about to cover: **never paint a pixel you are about to paint over.** Back to 24 ms with the
  ring kept. (`IRIS_OUTER` is now what the gaze reach and the erase radius derive from — the
  ring is the outermost thing that moves, so deriving either from the iris leaves a crescent
  behind it or pushes the ring off the sclera at full tilt.)
  **A profiler lesson worth keeping:** the loop report printed the *last* render, which for a
  paint-only-what-changed view is almost always **0 ms** and proves nothing. It now prints the
  **worst** render per window — which is what exposed the 47 ms entry frame below.
  **Two things measurement changed, not taste.** (1) Entry into the face did `fillScreen` +
  sclera, painting over half the panel twice: **47 ms**. Now one pass writing every pixel once.
  (2) Every shape was ~150 separate `drawFastHLine` calls, each opening and closing its own SPI
  transaction; batched under one `startWrite`/`endWrite` the entry frame is **36 ms**. It is still
  over the ≤25 ms *per-frame* budget, but it happens **once on entry / on `t`**, and the loop pass
  the mesh actually feels stays at 37 ms. Left there deliberately rather than spent more on it.
  (Unchanged and pre-existing: the loop still spikes to **~1.2 s** on a percept-window **flash
  append**, and that spike GROWS with the TTDB — 68 KB then, 73 KB now. That is every node's cost,
  not the face's, but it is far and away the next thing that will hurt this node's rtt.)
  **`t` was reassigned** (sensorium §5): `t` = face ↔ globes, **`n` inherits next-node / next
  comm-target**, SPACE keeps the console pane. Nothing was lost in the move.
  **What the laptop cannot check — needs your eyes at the bench:** whether the gaze runs downhill
  or uphill, and whether the axes are swapped. That is deliberately **three constants**
  (`EYE_GAZE_X`, `EYE_GAZE_Y`, `EYE_SWAP_AXES`) at the top of the eyeball block, not arithmetic
  buried in the renderer — this board's IMU already lied once about its I2C address.
  **Also landed, half of phase S0:** our own speaker now sets `gToneUntilMs`, so the node's own
  notes cannot dilate its own pupil. **S0 still owes the same gate to the `@LAT94` transient log**
  — that is a live data-quality bug in the acoustic tier, and it is the cheapest next thing here.

- **The fleet's beat skew, measured properly (2026-07-28). n=18, two independent runs.**
  Node-to-node agreement is **~2–4 ms sd, worst 5.5 ms = 1.9 m of sound** — and it reproduced
  (1.93 m, then 1.89 m). For scale, this fleet's **best ever** ranging result is 4.98 m
  (RSSI-only, 07-10), with the garden re-runs at 6.71 and 7.31 m, so acoustic timing is worth
  roughly **2.5× the best amplitude number**, and it is the non-amplitude physics the RSSI work
  concluded to chase.
  **The raw `band` skew column flatters and damns nodes unfairly, and must not be read directly.**
  Raw spreads are 17–38 ms, but most of that is COMMON MODE: the whole fleet swings together by
  15–25 ms in some runs. Removing the per-run mean leaves the residual, and only the residual
  bounds ranging. **Exclude the conductor when computing that mean** — its skew is 0.0 *by
  construction*, so averaging it in drags the mean and then charges the difference back to the
  reference as though it were the noisiest node on the fleet. It is the one node that cannot be.
  Harness: `scratchpad/band_skew.py` (n≥9, jittered gap, prints metres).
  ⚠ **The 15–25 ms common-mode excursion is UNEXPLAINED.** I proposed it was my sampler beating
  against the 30 s resync beacon, jittered the gap to decorrelate them — and it came back just as
  strong. So it is a property of the fleet, not of the measurement. It is the only thing between
  "probably 1.9 m" and "measured 1.9 m", and chasing it wants a serial print at the moment of an
  excursion, not another round of indirect timing.

- **Beat-scheduled fleet recording — BUILT and verified end-to-end on hardware (2026-07-28).**
  `CMD_RECORD` (op 11, args `start_band_epoch_ms u64 | dur_beats u16`, broadcast) makes every node
  capture the SAME window of wall-clock time off the band clock; `TTDB_REQ_RECORDING` (mode 3)
  reads it back over the existing pull path; `companion.py record` schedules it, pulls, and writes
  per-node WAVs. **No new toot type and no new RFC** — both are payload conventions over existing
  types, exactly as `TTDB_REQ_BELIEF` is.
  *Why schedule instead of threshold:* the `@LAT94` transient timestamps fire at a different point
  on the waveform depending on distance and gain, so their error is the **shape of the sound**
  rather than the geometry (sensorium §6). A scheduled capture has no threshold anywhere in the
  path, so two nodes that heard one clap cross-correlate directly.
  **Verified:** `[rec] armed` → `[rec] captured 16000 samples`, **`late_ms 0`** (first sample landed
  exactly on the requested instant), 16000 samples = **2.000 s** at 8 kHz. `--self-test` beeps
  1 kHz for 200 ms at the window midpoint; the DFT of the capture shows **1000 Hz + 3000 Hz and
  nothing else** — fundamental plus the only harmonic under Nyquist, i.e. the square wave
  `toneI2S` actually synthesizes — and the self-noise flag fired. Bytes arriving proves the
  transport; a known tone at a known instant proves the *timing*, which is the whole claim.
  **The design answer to the unexplained common mode: every node stamps what it BELIEVED.** RECHDR
  carries the node's band epoch at sample 0, the instant it was asked for (the difference is its
  own lateness — a measurement, not an unknown), its adopted pulse offset, its fleet epoch, and
  the chart era. A shared clock wobble becomes a correction the companion can apply instead of
  error baked into the audio. Do not "fix" this by trusting the clocks.
  **One bar fits in RAM, and that is why there is no filesystem in this feature at all.** 4 beats
  at 120 BPM = 2 s = 32,000 B, against a *measured* ~45 KB largest contiguous block once WiFi and
  BLE are up. Static buffer, not allocated: a feature whose allocation can fail is a feature that
  can vanish (the oscilloscope's canvas was refused at exactly this size — see below).
  ⚠ **The multi-node payoff is UNEXERCISED: only the Cardputer has a microphone.** The mechanism is
  fleet-wide and correct, but TDoA needs a second listening node and this fleet has one. Everything
  measured above is single-node.

- **Runtime RAM on the Cardputer is ~45 KB contiguous, not the ~245 KB the free-heap number
  suggests.** `[mem] heap 246192 free, maxalloc 204788, psram 0` at boot, but the profiler's
  `maxalloc` reads **~45 KB** in steady state once WiFi, BLE (Bluedroid), ESP-NOW and the 36 KB
  globe canvas are up. **No PSRAM** — the sketch's assertion was right. This refutes
  cardputer-sensorium.md §6's budget line for a 64,800 B full-screen canvas: that allocation was
  tried and **failed on hardware**. Size buffers against `maxalloc`, never against free heap.

- **`rst:0x15 (USB_UART_CHIP_RESET)` is NOT a firmware crash.** The Cardputer went into a reboot
  cycle for a while; every boot reported that cause, reached "online" cleanly, and showed no Guru
  Meditation, no watchdog and no brownout. It cycled on battery too, so USB was not the cause
  either. **A full power-off then replug cleared it** — a wedged state, nothing on flash. Two
  lessons: (1) read the reset cause before suspecting code — a code fault fails in the same place
  every time, and this one moved earlier as it went; (2) **observing costs something**: opening
  the port with DTR asserted resets an S3 native-USB board, so use `open_serial_no_reset` (or
  `scratchpad/rec_watch.py`, which watches a node's console while a command runs against it).

- **The Cardputer can look at itself now — INTEROCEPTION, the third representor view
  (`3`), built + flashed + verified 2026-07-28.** Phase S4 of
  [cardputer-sensorium.md](cardputer-sensorium.md) §4.5, and the first view on this node
  that points inward rather than outward: **BAT** (pack volts + a fill/drain trend arrow,
  bar = % of a 1S Li-ion curve), **DIE** (`temperatureRead()`, 20–80 °C), **MEM**
  (`maxalloc`, 0–64 KB — never free heap), a footer carrying uptime · **`lp`, the worst
  loop pass** · tempo · conductor · `clk±`, and a heartbeat on the eye's never-stopping
  clock. `lp` matters more than it looks: it is the number the mesh feels as rtt, and
  until now the node could only be *told* by the laptop that it had gone sluggish.
  **The fleet's STATUS temperature field is no longer 0 on this node** — `monitor` reads
  **`cardputer_1  47.6C`**, which was S4's stated done-when. Toot.h calls that field
  "ambient" and a die reading is not that; it is still a real measurement of a real body,
  and it says "the Cardputer is warm", which was previously unsayable.
  ⚠ **The bug that mattered was found by the fleet, not by the compiler:** the first build
  put *tenths* of a degree in a field documented as *hundredths*, and `monitor` printed
  `4.8C` for a 48 °C die. Nothing on the node itself looked wrong. **End-to-end is the
  only check that catches a units error at a protocol boundary.**
  **Budget (§3.4), measured:** worst render **15 ms on entry, 7–8 ms steady**, worst loop
  pass **7–9 ms** (≤25 / ≤40) — the cheapest of the three views, and the only one whose
  *entry* frame is inside the per-frame budget (the eye's is 31 ms). 300 frames per 30 s =
  exactly the 10 Hz cap. `ping --node cardputer_1` DELIVERED on attempt 1 with the view
  held. It is cheap for the eye's reason, not the scope's: nothing here changes between
  frames, so each element is compared against what is already on the panel — **on its
  rendered string, not its number** — and skipped if it matches. At rest only the heart
  paints. A new `intero` profiler section carries the sampler's own cost (four ADC reads
  + a die read per 2 s) rather than hiding it in a neighbour's.
  ⚠ **What the laptop cannot check — needs a meter at the bench:** `BAT_DIVIDER` = 2.0
  (a 1:1 divider on G10) is what M5's own code uses for this family; nothing on hand
  proves it for the ADV. The node prints the raw pin millivolts beside the derived pack
  voltage on its first sample — `[intero] pin 2091mV x2.00 = pack 4182mV (98%) | die
  45.6C | maxalloc 30K` — so a meter on the JST lead settles it, and it is one constant.
  Also: **with the cable in, the bar reads the charger, not the pack** (~4.2 V ≈ 100%);
  a real state-of-charge reading needs it unplugged. No VBUS sense pin exists on this
  board, so no charge state is *claimed* — the arrow reports only which way the voltage
  is actually moving against a ~2-minute EMA.
  Sensorium §4.5 previously argued interoception should be ambient colouring and never a
  view. Half of that stands: the battery ring on the sclera and the low-power alert are
  still owed, and both want the arbiter (S1) first, since "take the screen once" is a
  salience claim.

- **The T-Deck can look INTO another node now — interoception became a mesh service, and the
  mesh map lost the K10 and gained the Cardputer (2026-07-29, built + flashed + laptop-verified
  end to end).** Four changes, one idea: a body is data, so a body can be sent.
  - **`CMD_GET_INTERO` (op 12) → a 21-byte INTERO PERCEPT** (`Toot.h`): bat_mv · bat_pct ·
    bat_trend · die_c_x10 · maxalloc_kb · uptime_s · worst_loop_ms · beat_period_ms ·
    conductor_id · flags. **No new toot type and no new RFC** — a payload convention over
    PERCEPT, distinguished by LENGTH (15/43/45 STATUS · 24 GPS · **21 INTERO**), exactly as
    `TTDB_REQ_BELIEF` and the GPS percept are. So the V4-A bridge already forwards it.
    It reads **nothing** in the reply path (every field is the last sample the node's own 2 s
    interoception cadence took), which is what makes it cheap enough to *poll*.
  - **The T-Deck's record pane is now a body view.** Select a node on the mesh map and the
    bottom half stops being record text and becomes that node's BAT/DIE/MEM gauges + a footer
    (uptime · `lp` worst loop pass · bpm · conductor · clk). Its OWN record draws from a new
    local sampler; every other node's arrives over the air, polled every 3 s **only while its
    record is selected and the main pane is showing** — one small toot each way, and it stops
    the moment you navigate away. A peer body carries its freshness (`live` / `no reply Ns`) and
    goes grey when stale: a body heard about 40 s ago must not look live.
    **Semantic data only** — numbers, never pixels. The receiver has a different panel, palette
    and amount of room, which is the whole reason this is a TTCP render and not a framebuffer copy.
  - **Mesh map (`firmware/tdeck_console/data/ttdb.md`): K10 out, Cardputer in.** The K10 is on v1
    firmware and off the band roster; the Cardputer took its place with radii from its own real
    `@LAT97` window (rssi_max −34 T-Deck / −35 V4-B / −40 V4-A) through the SP1 calibration.
    ⚠ **The record says outright that the resulting triangle is inconsistent** — its radii are
    BENCH scale while the three static nodes still carry GARDEN coordinates (embedding_rev 4,
    2026-07-13), and 3.7 + 5.0 cannot also be 41.8. **Owed: a fresh
    `proximity`→`positions`→`fleetmap` with the whole fleet powered and the bridge cabled.**
  - **The T-Deck also picked up the firmware it had been missing**, having sat unflashed since the
    feelings-globe commit: the **`edgesAt` per-frame fix** (edges cached at view load — it was the
    last node still paying one LittleFS open per record per frame, measured at 321–767 ms/repaint
    elsewhere), TTDB's incremental append indexing, `NODE_CARDPUTER_1`, and a **non-zero STATUS
    temperature** (die reading ×10 — the field is HUNDREDTHS and the sampler is TENTHS, the exact
    trap that made the Cardputer print `4.8C` for a 48 °C die).
  - **`companion.py intero --node <n> --port <p>`** reads any node's body from the laptop. Built
    for verification, not convenience: a units error at a protocol boundary is invisible on the
    node itself, and this is where it shows.
  **Verified on hardware** (Cardputer COM14, T-Deck COM10; both compile ~40/41% flash):
  `intero --node cardputer_1` → **4.106 V 90% · 47.6 C die · 29 KB maxalloc · 120 bpm**, every
  field matching what that node draws for itself and no units error; `intero --node tdeck_1` →
  **43.8 C · 71 KB · lp 105 ms steady**; the T-Deck's TTDB **pulls back with the new mesh map as a
  byte-exact 3005-byte prefix** (4 node records: T-Deck/V4-A/V4-B/**Card**, K10 gone) with its own
  `@LAT96`/`@LAT97` lanes appended on top — the floor survived the reflash.
  ⚠ **First thing the new view found, and it is not about batteries: `lp` (worst loop pass) reads
  ~2007 ms on the Cardputer and ~4221 ms on the T-Deck inside the FIRST 10 s window after boot**,
  falling to 11 ms / 105 ms in steady state. Bracketed between 6 s and 29 s of uptime, repeatable.
  It is a **pre-existing, fleet-wide** several-second stall that the mesh feels as rtt, and nothing
  could see it before.
  **LOCALISED 2026-07-29 — and NOT to the WiFi scan, which is what I had guessed here.** The
  Cardputer's own section profiler named it while a duet capture happened to be listening:
  `[loop] worst pass 4011ms (render 1ms, widest section pulse 2000ms)`. So it is inside the
  **`pulse` section** — the band clock / voice block — for ~2000 ms of a ~4000 ms pass, with the
  renderer innocent at 1 ms. Still unexplained (a 2 s figure in a section whose longest intended
  block is a 180 ms tone is suspicious in itself), but the search space is now one section instead
  of the whole loop. A reminder that the node's own instrumentation answers this and a plausible
  story does not — [[verify-before-believing]].
  ⚠ **SUPERSEDED 2026-07-30 — "it is inside the `pulse` section" does NOT hold up, and the WiFi
  scan is now positively EXONERATED rather than merely doubted.** A 12-minute Cardputer console
  capture (`scratchpad/console_tail.py` on COM14, pure listener) caught the stall with a shape
  the earlier single observation did not have:
  `[loop] worst pass 2009ms (render 0ms, widest section render 6ms)`.
  **A 2009 ms pass whose widest instrumented section is 6 ms.** The nine sections do not account
  for the time at all — so it is not *in* any of them, and the one reading that put it in `pulse`
  cannot be generalised from. That is the signature of the loop task being **descheduled between
  iterations**, not of slow code: the pass is measured wall-clock end-to-end, so a preemption that
  lands outside the marked region inflates the pass while every section still measures only its
  own few milliseconds. Which also explains why the two V4s show the same ~2000 ms with a
  completely different, far simpler loop — it is not anybody's loop body.
  ✅ **WiFi scan cleared, by direct observation rather than by argument:** the capture caught
  `[wifi] scan: 11 AP(s) folded into @LAT96 window` at 15:42:37 with the loop reporting **10 ms
  in the windows on BOTH sides of it**. The async scan costs the loop nothing. That retires the
  suspect this entry has carried since it was written.
  📎 **Not periodic, on the evidence so far.** It is reliable at boot on every node. One
  occurrence was measured at **539 s** of uptime, which looked like it might imply a ~600 s
  period (the WiFi scan interval) — but the very next run read **9 ms at 540 s**, and 8.5 minutes
  after boot were clean throughout. So: reliable at boot, occasional afterwards, no established
  period.
  🔎 **BEST REMAINING HYPOTHESIS — the USB CDC host attaching, not anything on the node.** Every
  observation fits it and none contradicts it:
  - During the 12-minute capture the port was **held open the whole time**: one stall at the very
    start (the moment the listener attached) and **none for the following 8.5 minutes**.
  - The "at boot" stalls are really "just after a host attached" — `companion.py` opens the port
    and resets the node, so boot and attach are the same instant and have never been separated.
  - Later stalls cluster around times a laptop command ran, each of which opens and closes the
    port. The Cardputer read `lp 2030 ms` immediately after a run of `intero` calls.
  - The magnitude is ~2000 ms on **all four nodes across two very different sketches**, which
    suits a shared stack far better than any application code. `Serial` on S3 native USB is known
    to behave badly around host attach/detach ([[usb-uart-chip-reset-not-a-crash]]).
  ⚠ **Unproven, and the fleet has never once been measured without a USB host attached** — which
  is precisely the blind spot, because the measuring instrument is the suspect. **The decisive
  test needs one cable move:** power a V4 bridge on USB, run the **Cardputer on battery only with
  no USB host**, and poll its `lp` over the mesh through the bridge. If it stays in single digits
  with nobody attached, this is the answer and the "fleet-wide stall" is an artefact of being
  watched. If it still stalls, the hypothesis dies cleanly and FreeRTOS-level tracing is next.
  ⚠ **The T-Deck's battery divider assumption does NOT hold: it reads 4.71 V**, above the 4.20 V
  1S Li-ion ceiling. `PIN_BAT_ADC 4` / `BAT_DIVIDER 2.0` come from LilyGo's `utilities.h`, not
  from a meter on this unit, and with the cable in it may simply be measuring the charge rail with
  no pack on it. Handled honestly rather than silently: above the ceiling the node **withholds the
  percentage** (255) and the pane shows the volts with an empty bar and neutral colour, so a
  charge rail cannot read as a beautifully full battery. **A meter on the JST lead settles it, and
  it is one constant.** The Cardputer's 4.106 V is in range, so its own divider looks right.
  ✅ **THE PANE ON THE GLASS IS CONFIRMED BY THE USER (2026-07-29)** — the mesh map's record area
  draws the Cardputer's live body over the air *and* the T-Deck's own, so the whole chain
  (poll → INTERO PERCEPT → decode → render) works on hardware. Only eyes prove a render, the way
  only ears prove a speaker (@LAT90LON70), and now they have.
  📎 **Gotcha found while trying to verify it without eyes: a no-reset serial tail reads NOTHING
  from these native-USB S3 boards.** `open_serial_no_reset` deasserts DTR, and the ESP32-S3 USB
  CDC only transmits when the host asserts it — so the sketch's `Serial` output is silently
  dropped. `open_serial_no_reset` is still right for what it was built for (preserving a node's
  RAM clock offset between `sync` and `verify`, which needs no console output), but it is **not** a
  way to watch a node. To read a node's console you must accept the reset.
- **The two handhelds can play a DUET on a key press — `d` on the T-Deck, with whoever it is
  looking at (2026-07-29, built + flashed + the partner's half verified from the laptop).**
  The finale already scored this pair (T-Deck `kOdeLead` + Cardputer `kOdeHarm`, HeroArc.h), so
  the music needed nothing new. Two things stood in the way, and both were worth fixing properly:
  - **A duet must NOT be a chart scene.** A scene is the whole band's shared position in the
    song, so putting the pair into `SCENE_FINALE` would pull in every powered member and produce
    a *finale*, not a duet. So **`CMD_DUET` (op 13, args `partner_node_id u32 | role u8`)**
    overrides only the two participants' **parts**, leaves the chart's scene exactly where it was,
    and rides the pulse step clock the band already shares. It changes **what** each node plays,
    never **when** — which is what makes the two voices land together. Roles ride on the wire
    (`DUET_LEAD` / `DUET_HARM` / `DUET_OFF`), so who leads is data, not a rule in firmware, and
    either node can be the inviter. `CMD_STOP` and a second `d` both end it. Not persisted in NVS
    (unlike the song): a console that resumed a duet on boot would sing the lead at a partner that
    may not be there.
  - ⚠ **The `!gPulse.conductor()` play gate would have made the duet a SOLO, every time.** Both
    voices are silent while conducting — a guard added so a just-rebooted, self-appointed node
    can't play out of phase against a band it hasn't found yet. But with only the two handhelds
    powered, one of them *necessarily* conducts, and it is the T-Deck (`0x200` is the lower live
    id) — i.e. the lead. **A duet is now the documented exception**: a conductor *is* the phase
    reference, and the operator asked for exactly these two voices, so the out-of-phase risk the
    guard exists for cannot arise. The hero's-arc gate is untouched. **Measured, not assumed:**
    the Cardputer reported `conductor=False` at rest, so the T-Deck did hold the baton.
  - **New `INTERO_VOICING` flag (bit 3) — "am I singing", which `INTERO_PLAYING` never said**
    (that only means the node has a chart, and most parts are silent in most scenes). This is how
    a duet gets confirmed: **not by an ACK**, which a blocking tone call swallows (@LAT90LON70),
    but by the partner's own body report — and the record pane is already polling it, so the
    footer shows `SINGING` for the node you are looking at. Reported as the *state* that would
    sound a note rather than the instant of one, so a poll can't fall between two notes and read
    false. The interoception view built earlier the same day turns out to be the duet's
    instrument; that composition was not planned.
  **Verified from the laptop** (`scratchpad/duet_check.py`, driving the Cardputer over COM14 with
  the same invitation `d` sends): voicing **False → True** on the invitation, and **back to
  False** on `DUET_OFF`. Both sketches compile clean (40% / 41%) and are flashed.
  ✅ **2026-07-30: user-confirmed working from the T-Deck against BOTH V4s.** That closes the two
  things the laptop could not check — the real `d` key path (not just the same wire protocol
  driven from COM6) and audibility on the hand-wired MAX98357A amps. The duet is now a
  four-node capability: either console can pair with either V4.
  ✅ **The duet is user-confirmed working on hardware.** `d` is contextual — mesh map (SemPos),
  a remote node selected — and says why on screen when the precondition isn't met rather than
  failing silently.
- **The duet plays in DOUBLE TIME (2026-07-29) — a part property, not a tempo change.** `speed`
  rides on `CMD_DUET` beside the roles (additive byte; an older sender means "as written"), and
  the whole mechanism is two lines: wrap the phrase in `steps/speed` slots and look the note up
  at `sip*speed`. **The band's beat period is untouched**, so the pair covers the written phrase
  in half the steps and reads as twice as fast while staying locked to the pulse the rest of the
  fleet counts. That is why this is a part property: a chart tempo change would drag the whole
  band along and needs a fleet cold-start (`PULSE_DEFAULT_BEAT_MS`, [[pulse-tempo-lives-in-pulse-cpp]]).
  Articulation scales with it (`tone_ms / speed`, floor 80 ms), which keeps double time staccato
  and halves the blocking duty cycle of a tone call that would otherwise fill 72% of a note slot.
  To go back to the written tempo set `DUET_DEFAULT_SPEED` to 1 in the T-Deck sketch — one line.
  ⚠ **`score::noteAt` is an exact step match, so a speed must not land a note between slots.**
  `kOdeLead`/`kOdeHarm` have a tied note at step **54**, which survives ÷2 and would be
  **silently dropped at ÷4** — so participants validate the requested speed against their own
  phrase (`validDuetSpeed`) and fall back to 1 rather than mangle the melody. `DUET_SPEED_MAX` 4.
  **Verified by measuring the node's own sequencer, not by ear or by inference**
  (`scratchpad/duet_speed.py`): step-0 → step-0 wall gaps **3947 / 4098 / 3997 ms** against the
  predicted 32 steps × 125 ms = **4.0 s** (the written tempo measures 8.00 s), the scaled step
  set is exactly `[0,2,4,6,8,10,12,14,16,18,20,22,24,27,28]` (the tied note at 27 = 54÷2 intact),
  all five harmony pitches present, and **every phrase cycle complete at 15/15 notes**.
  📎 **A wrong diagnosis worth remembering: dividing note-count by notes-per-phrase to infer a
  period is invalid unless the capture window aligns to phrase boundaries.** Doing that read
  "5.11 s instead of 4.0, notes being dropped", which sent me into the sequencer after a defect
  that did not exist. Measuring the **step-0 → step-0 interval directly** — one number, immune to
  window alignment and to serial-arrival jitter — settled it instantly. The per-note serial gaps
  are *also* junk for this (median 217 ms, min 100 ms on a 125 ms grid — CDC buffering, not the
  clock). Observe the mechanism ([[verify-before-believing]]); this is the same lesson as
  @LAT90LON70, arrived at from the other direction.
  The `score::noteForCrossedSteps` catch-up added during that chase was **kept but re-labelled
  defensive**: `stepTick` genuinely reports only the step it lands on, and the 60-220 ms percept
  flush genuinely exceeds a 125 ms step, so the hazard is real — it just was not what was
  happening. Its comment says so, rather than citing a measurement that was my arithmetic.
- ⚠ **A SINGLE `CMD_DUET` GETS DROPPED — the invitation needs re-asserting, not acknowledging
  (found + fixed 2026-07-29, on a user report of "half time ping pong").** The duet was
  fire-and-forget by design, on the reasoning that a want_ack would false-negative because the
  tone call blocks (@LAT90LON70). That reasoning was about the **reply** and quietly ignored the
  **delivery**: ESP-NOW drops frames — the reason every other reliable path here either wants an
  ACK or repeats itself — so a lost invitation leaves the console singing the lead at a partner
  that never heard the ask. **Caught by listening to both consoles while the user pressed the
  key** (`scratchpad/listen_both.py`, a pure listener that sends nothing): the T-Deck logged
  `we LEAD, they HARMONISE, speed x2` and played four clean phrases, and the Cardputer printed
  **nothing at all** — no `invited to HARM`, no `[part]`. The dismissal at the end *did* arrive,
  which is what makes it obviously a drop rather than a decode bug.
  **Fix — the PULSE chart's pattern, not a retry:** a live duet is **re-asserted every 2 s**
  (`serviceDuet` / `DUET_ASSERT_MS`), and a dismissal is repeated 3× rather than sent once (a
  dropped OFF would leave the partner singing forever). Idempotent state on a slow timer beats a
  delivered event, and it buys three things a want_ack retry would not: a partner that missed the
  invitation joins on the next tick, a partner that **reboots mid-duet rejoins by itself**, and
  any transient disagreement about the SPEED self-corrects within one interval. Receipt logging is
  change-only on both nodes, so a repeat is silent. Nice consequence: because the assert fires on
  the first pass after a duet turns on, telling **either** node forms the pair — the invited node
  propagates it to its partner.
  **Verified by telling ONLY the T-Deck and never addressing the Cardputer at all:** it was
  invited over the air at **116 ms**, and both then played **60 notes each on the identical step
  set, in unison**, 4 phrases in 16 s (= the 4.0 s double-time period).
  ✅ **DOUBLE-TIME DUET CONFIRMED RIGHT BY THE USER + measured over 85 s of continuous play**
  (2026-07-29, both nodes captured together during a real `d` press): **320 notes each**, labels
  `duet-lead` / `duet-harm`, speed x2, wrap 32, **identical step sets with zero node-only steps**
  (true unison), and **21 consecutive phrase periods all within 3887-4093 ms** of the 4.0 s
  target. The re-assert was the fix.
  📎 **The two-voice "half time ping pong" was never reproduced directly, and one run after the
  fix still sounded wrong before a reboot made it right.** So the residual suspicion is **stale
  state, not the sequencer**: the T-Deck's song flag `gLocalPlay` **persists in NVS** and the chart
  `era`/scene latch survives in a running fleet, and a Cardputer playing `kNewcomer`'s `kOdeHarm`
  at the WRITTEN tempo against a `duet-lead` at DOUBLE is exactly half-rate on alternating slots.
  Unproven — but **if the duet ever sounds wrong again, cold-start both handhelds first**; that is
  the same first move the era latch already demands ([[pulse-tempo-lives-in-pulse-cpp]]).
- **The LoRa spine can be looked inside and can SING — V4-A and V4-B answer `CMD_GET_INTERO`
  and `CMD_DUET` (built + flashed + verified on hardware 2026-07-30, COM6/COM9).** Both mesh
  services had been console-only, which made the T-Deck's record pane a view that worked for two
  of the four nodes on its own mesh map, and `d` an offer it could only make to one partner. The
  V4s now carry the same 21-byte INTERO PERCEPT and the same duet part-override as both consoles
  — deliberately line-for-line, so the four copies stay comparable rather than drifting.
  **Verified end to end from the laptop:** `companion.py intero` reads both bodies (V4-B *through
  the V4-A bridge*), and a scripted duet — V4-A leading `kOdeLead`, V4-B harmonising `kOdeHarm`,
  double time, the invitation re-asserted every 2 s exactly as `serviceDuet` does — brought
  both `INTERO_VOICING` bits True and both back False on the 3× dismissal. Confirmed by the
  voicing bit, never an ACK (@LAT90LON70). The band floor is unharmed: `band` across
  V4-A/V4-B/Cardputer is **±0.7 ms**, era 2, all on one chart.
  ✅ **The load-bearing evidence is V4-B's OWN SEQUENCER, captured on COM9 by a pure listener
  while the duet was driven from COM6** (`scratchpad/console_tail.py`) — because the polled flag
  turned out to be the noisier instrument (below). V4-B printed `[duet] invited to HARM by
  0x00000010 (speed x2)`, then **108 notes** on exactly the 15-note `kOdeHarm` step set
  `[0,2,4,6,8,10,12,14,16,18,20,22,24,27,28]` — **the tied note at 27 (= 54÷2) intact**, which is
  the thing `validDuetSpeed` exists to protect — over **8 consecutive step-0 → step-0 phrase
  periods, every one 4 s** against the predicted 32 steps × 125 ms, and closed with
  `[duet] dismissed`. Measured step-0 to step-0, never by dividing note-count by phrase length,
  which is the arithmetic that sent the original duet work chasing a defect that did not exist.
  📎 **`INTERO_VOICING` polling is the weaker witness of the two, and it should not be the last
  word again.** Across three runs it produced several `no reply` misses and, once, a decoded
  `False` for V4-A in the middle of a duet the sequencer shows never stopped. Both are consistent
  with a mesh that is currently lossy enough to break a bridged pull outright (below) — a probe
  is two frames over that same air. **Poll the flag to see a duet START; read the node's `[part]`
  prints to know what it actually played.** The one unexplained decoded `False` is recorded here
  rather than smoothed over: it has no mechanism yet.
  ✅ **V4-C joined them the same day, and it is the cheap one — the whole LoRa spine is now at
  parity.** Ported from V4-B (its structure is V4-B's), flashed to COM13 at 94% flash, and
  verified the same way: `[duet] invited to HARM ... (speed x2)` followed by the exact 15-note
  `kOdeHarm` step set `[0,2,4,6,8,10,12,14,16,18,20,22,24,27,28]` — tied note at 27 intact — over
  **step-0 → step-0 phrase periods of 4 s**, the double-time target. It then re-locked to V4-B's
  chart over the air (**conductor 0x11, era 17, skew +0.0 ms**) with V4-B running on battery.
  📎 **Its battery read 3.841 V / 54% on the FIRST flash**, because it was built with the
  *measured* GPIO37 polarity rather than the published one. That is the whole return on having
  swept the board instead of guessing: the second and third nodes cost nothing.
  ⚠ **One thing did NOT port verbatim, and copying it would have been a silent regression.**
  V4-A and V4-B derive the duet's note length from `PULSE_PART_TONE_MS / speed` with an 80 ms
  floor, which is harmless there (130 ms and 120 ms are both already above the floor). V4-C's
  part is a **60 ms hi-hat tick**, so the same line would have hit the floor in the ordinary
  non-duet case and **tripled the hi-hat to 80 ms** — changing the groove of a node nobody was
  listening to at the time. It carries its own `DUET_TONE_MS` (160) instead, and the tick is
  untouched. A duet note is melodic and a 60 ms blip cannot carry a pitch, so the two lengths
  genuinely want to be different numbers. (Verified by construction, not by measurement — the
  serial log cannot show tone duration.)
  Two V4-specific judgements worth keeping:
  - **No `!conductor()` term in their VOICING, and no duet exception needed** — unlike the
    consoles, a V4's voice has never been gated on holding the baton, so the guard the duet has
    to bypass on the T-Deck simply does not exist here. Fewer special cases, not more.
  - **`STATUS`'s temperature field is no longer 0 on either V4**: it carries the die reading, the
    same fill the Cardputer made. `monitor` showing 54 C for `v4a_bridge` is true and was
    previously unsayable.
- ⚠ **A MEASUREMENT IS NOT ITS OWN VALIDITY FLAG — and this one is still live in both consoles.**
  Ported straight from the console sketches, `serviceIntero` used `gBatMv != 0` to mean "have I
  sampled yet". On a V4 with no pack on the JST lead the ADC reads a perfectly legitimate **0 mV**,
  so the sampler re-ran *and re-printed its one-time boot line* on **every loop pass**. The
  resulting serial flood showed up as the node's own **worst loop pass: 4035 ms on V4-A, 2041 ms
  on V4-B**. Fixed with a separate `gBatSampled` flag; both V4s then measured a **steady 34–40 ms
  over n=12 and n=10 samples spanning ~90 s and ~73 s**.
  📎 **The number nearly lied twice.** Those 2 s / 4 s readings sit right on top of the
  unexplained multi-second stall recorded above for the two consoles, and it would have been very
  easy to file them as "confirmed fleet-wide". They were self-inflicted and had nothing to do with
  it. Separately, **`companion.py intero` resets the node on port open**, so invoking it in a loop
  can never observe a profiler window past the ~8 s settle — six consecutive calls all read
  `up 8s, lp 0 ms`. Watching a windowed number needs ONE open connection and many probes
  (`scratchpad/intero_watch.py`); the instrument has to outlive the thing it measures
  ([[verify-before-believing]]).
  ✅ **The latent half is now closed too — all four nodes carry `gBatSampled` (2026-07-30).** The
  T-Deck and Cardputer were flashed the same day and **behaved identically before and after**,
  which is the correct result for a defensive fix and is why it was worth stating plainly rather
  than dressing up as an improvement: neither console has ever read 0 mV, so neither was flooding.
  They were one unplugged pack or one wrong ADC pin away from it — which is exactly what the V4
  turned out to be, so this was not a hypothetical.
  ⚠ **CORRECTION to what this entry first claimed.** It read: "two V4s hold 34–40 ms, which argues
  the ~2000 ms stall is not in the shared Pulse engine." **That was wrong, and wrong in the
  dangerous direction** — it would have sent the next session hunting in console-only code. The
  V4 samples that supported it began at uptime **77 s and 315 s**, i.e. entirely *after* the
  window the stall lives in. Watching V4-A from **55 s** instead caught it: `lp 2034 ms` in one
  window, then **35 ms in all 13 following samples** out to 159 s.
  **So the V4s REPRODUCE the phenomenon, they do not clear anything.** It is now seen on **4/4
  powered nodes** — Cardputer ~2007 ms, T-Deck ~4221 ms, V4-A 2034/4035 ms, V4-B 2041 ms — across
  two very different loop structures (a 3400-line console with a screen, and a 900-line headless
  bridge), always **once, early**, then gone. That it survives that much structural difference
  makes the shared floor (Pulse engine, ESP-NOW/WiFi bring-up, BLE scan start) a *better* suspect
  than before, not a worse one. The recurring ~2 s figure across four nodes is the strongest clue
  on the table.
  📎 The methodological trap is the same one twice in one session: **a windowed number sampled
  late reads clean**, and clean is indistinguishable from fixed unless you know when to look. Any
  future claim about this stall must state the uptime range it sampled.
- ⚠ **BRIDGED PULL OF V4-B IS BROKEN, AND IT IS PRE-EXISTING — control-tested, not assumed
  (2026-07-30).** `pull --port COM6 --node v4b_relay` (laptop → V4-A → air → V4-B and back)
  returned, across six attempts, *no data* / *4848 B* / *54290 B with a 202 B gap after 4 rounds*
  / *no data*. The same pull **direct over V4-B's own USB (COM9) is 54290 B, twice, identical**,
  so the node and its TTDB are fine — the loss is entirely in the bridged path.
  **It is not the intero/duet work.** I stashed both sketches, reflashed **both V4s from HEAD**,
  and re-ran the identical pull: *no data* / *5252 B* / *no data* — the same failure, if anything
  slightly worse. Doing the control cost two flashes and bought the only thing that could have
  been claimed honestly either way.
  **The likely cause is size, and it indicts the lane-growth problem below.** The byte-exact
  bridged pull recorded on 2026-06-25 was of an **858 B** TTDB. V4-B's is now **54290 B — 63×
  bigger**, ~270 ESP-NOW frames, against a mesh that now also carries a Cardputer and a T-Deck.
  Unverified, and the next thing to instrument here (per-round gap counts against file size, and
  against a pruned lane). **Until then: pull a V4 over its own cable, not through the bridge**,
  which is also the lesson the 2026-07-13 field re-run reached from the other direction
  ([[multitier-field-rerun-jul13]]).
- ✅ **THE V4s CAN READ THEIR OWN PACKS — the bug was ONE INVERTED BIT, found by sweeping the
  board rather than guessing (2026-07-30). `PIN_ADC_CTRL` (GPIO37) is ACTIVE HIGH on the V4, not
  active LOW as on the V3.** Both V4s first reported `energy: 0.000 V`, and the appealing story
  was "no pack on the lead, so 0 mV is correct". The operator's bench test killed that: both had
  been run **disconnected on their battery packs**, so the packs were present and functional and
  0 mV was simply wrong.
  **The fix came from a measurement, not a second guess.** Having already been wrong once by
  trusting Heltec's V3 map, guessing a different pin from the same source would likely just be
  wrong again — so a throwaway sketch (`scratchpad/v4_adc_probe/`) swept **every ADC1 pin
  (GPIO1–10)** against **each candidate divider-enable in LOW / HIGH / floating**, with WiFi,
  LoRa, I2S and the OLED all left uninitialised so every pin was free to read. The tell is not
  the absolute number, it is **which pin MOVES with a control line**: GPIO1 read **827 mV with
  GPIO37 HIGH and a flat 0 mV in all four other states**, repeatably. So the *pin* was right all
  along (the operator independently found an online sample also naming GPIO1) — **only the
  polarity was inverted, and driving it LOW is exactly the state that disconnects the divider.**
  ✅ **Verified on both boards after the fix, and this is what makes it convincing: they disagree,
  plausibly. V4-A reads 4.096 V (89%), V4-B reads 3.831 V (52%), both "rising" on USB charge.**
  Two independent boards giving two *different* sensible numbers moving in the expected direction
  is much stronger evidence than one board reading something believable.
  ⚠ **`BAT_DIVIDER 4.9` is still inherited and unmetered.** It turns 827 mV into 4.05 V, a
  textbook 1S pack on charge, so it is at worst close — but plausible is not checked, and the raw
  pin millivolts still print on the first `[intero]` line for whenever a meter is handy. The
  withhold-the-percentage guard (255 above the 4.20 V ceiling) stays regardless.
  📎 The general lesson, which cost two hours the hard way: **a datasheet-derived constant that
  produces a plausible-looking wrong answer is worse than one that produces an obvious one.**
  0 mV was obvious. The polarity was not — and the same source supplied both.
- **The Cardputer was ~12 dB quieter than its hardware allows, in TWO places at once, and the
  codec half was a misread register (2026-07-30, on the operator's report that it is very quiet
  next to the rest of the band).** It is the fleet's smallest voice — an 8 Ω 1 W speaker behind
  an NS4150B — so it had the least level to spare and was giving away the most:
  - **ES8311 DAC volume (reg 0x32) sat at 178, which is −6.5 dB, not "70%".** The register is
    **0.5 dB per step with unity at 0xBF**, not a linear 0..255 loudness control — so the old
    `setVolume()` mapping was wrong at both ends: `70` meant −6.5 dB, and `100` would have
    meant **+32 dB of digital gain**, i.e. pure clipping, not loudness. `setVolume()` now scales
    to **unity (0xBF)** and `begin()` asks for 100; `setVolumeRaw()` exists for anyone who
    deliberately wants to push past unity with a source that is well below full scale.
  - **The synthesized square sat at 16000/32767 (−6.2 dB).** Now **30000**, and deliberately not
    32767: a square through the DAC reconstruction filter overshoots its edges ~9% (Gibbs), so
    nominal full scale would clip on every transition and buzz. 30000 puts the overshoot at the
    rail instead of through it — 1 dB given away to buy a clean edge.
  The beep and boot toot were scaled with it (12000→22000, 6000→11000) so the intended mix
  survives: the boot toot is *meant* to be softer than a band note.
  ✅ **Verified the register rather than the write:** the codec is read back at boot and prints
  `[codec] DAC vol reg 0x32 = 0xBF (0xBF = unity/0dB), tone amp 30000/32767`. That line exists
  because **a volume that silently failed to take looks exactly like a speaker that is just
  small** — which is the whole reason this went unnoticed.
  ⚠ **The amplitude half (+5.5 dB) is arithmetic and certain; the codec half (+6.5 dB) depends on
  the 0.5 dB/step reading of reg 0x32 being right.** Under a linear reading, 178→191 would be
  worth only +0.6 dB. Ears arbitrate, and the operator's do: if it is now loud but *buzzy*, the
  source is too hot; if it is louder but still modest, the register is linear and there is
  another ~2.5 dB at 0xFF. **The definitive test is available on this node and nobody else:** it
  has a mic, so it can measure its own output at two volume settings and report the actual ratio.
  📎 Side effect worth knowing before it surprises someone: a 4× louder speaker feeds 4× more of
  its own voice into `gSndAmb`, the acoustic tier's slow room baseline. The time-based self-noise
  gate (`gToneUntilMs`) still suppresses `gSndHot` while a note sounds, so transient detection is
  protected — but the @LAT94 baseline now sits higher whenever the band is playing.
- ⚠ **The Cardputer's TTDB is growing ~1 record/min and `TTDB_MAX_RECORDS` is 256.** It went
  51 → 181 records (63 KB) in a single session. Nothing has overflowed yet, but there is no prune
  policy and the percept-window flash append already spikes the loop 60–220 ms, growing with the
  file. This is the next thing that will bite, on every node. **It already has**: the broken
  bridged pull above is the first capability this growth has actually cost the fleet.

- **REPO RESHAPED FOR PUBLICATION (2026-07-31) — `RFCs/` now lives at `replicate/RFCs/`.**
  The specs moved under a new **`replicate/`** folder that is the open-source front door
  (`replicate/README.md` — "Universal Agent Memory & Learning System", a recipe per use case;
  `replicate/agent-memory-system_ttdb.md` — the semantically-compressed spec store that is *an
  instance of the thing it specifies*). New spec: **`TTDB-RFC-0009 Counter-Story and Narrative
  Morphospace`** (479 lines), which argues the fleet's *heterogeneity* — mic+IMU only on the
  Cardputer, GNSS only on the T-Deck, long-haul only on the V4s — is the thing that lets the
  collection know something no member could; it is also aimed squarely at the spec's own
  highest-EPS gap, **Learning from Action** (`@LAT20LON3`), which is deliberately unimplemented.
  (`TTX-0004-counter-story.md` was folded into that RFC and deleted.)
  ⚠ **32 `RFCs/…` links across 12 files are now stale** — `companion.md` §5 (14), `PLAN.md` (5),
  `CLAUDE.md`, `README.md`, `ttn-semantic-positioning.md`, `cardputer-sensorium.md`,
  `tests/Makefile`, `tests/test_rfc_ttdb.cpp`, `firmware/libraries/Pulse/src/Pulse.h`,
  `firmware/tdeck_console/tdeck_console.ino`. Docs degrade quietly; **`tests/Makefile` +
  `test_rfc_ttdb.cpp` will actually break** on the next `make`.
  ⚠ **Both handhelds' RFC globe is 2 records behind:** `replicate/RFCs/rfc.ttdb.md` is **36
  records / 38014 B**, while `firmware/{tdeck,cardputer}_console/data/rfc.ttdb.md` are both
  **34 / 34047 B** — TTDB-RFC-0009 is not on the glass. Re-copy + re-flash the FS to catch up.
- **K10 PARKED — temporarily excluded from the fleet (2026-07-31, operator's call).** It runs v1
  firmware and was already off the band roster and off the T-Deck's mesh map (2026-07-29); this
  finishes the job so **nothing depends on it**. Changed: `companion.py` gained `DEFAULT_FLEET`
  (`v4a_bridge,v4b_relay,v4c_edge,tdeck_1,cardputer_1`) and `sync --expect` / `verify --nodes` /
  `monitor --nodes` / `reconcile --nodes` now default to it instead of `…,k10_1` (`reconcile` had
  defaulted to **`k10_1` alone**, so it was reconciling a node that isn't there); the Cardputer's
  `kTargets` no longer cycles `t` onto it (source edit — **takes effect on its next flash**).
  **Kept, untouched:** `firmware/k10_percept`, `NODE_K10_1`/`NODE_IDS["k10_1"]`, the display-name
  map, the `.vscode` K10 tasks, and the K10 `User_Setup.h` note in CLAUDE.md. It is out of the
  *defaults*, not out of the repo — `--node k10_1` works the moment it is plugged back in.
- **Bench geometry as of 2026-07-31 (operator-stated ground truth, one room + hallway):**
  **V4-A and the T-Deck cabled and ~2 ft apart**, **Cardputer across the room**, **V4-B by the
  front door**, **V4-C on the dining table**. V4-A holds USB as the bridge, so the whole fleet is
  reachable without moving a cable. This is a *stated* layout spanning ~0.6 m to ~10 m in four
  distinct distance classes — the discriminating test it affords is **rank ordering**
  (V4-A↔T-Deck must come out nearest by a wide margin), not absolute metres, which is the honest
  claim indoor RSSI can carry ([[rssi-ranging-shadowing-limited]]).

- ⚠⚠ **A BRIDGED PULL CAN REPORT SUCCESS AND RETURN A FILE MIXED FROM TWO GENERATIONS — the
  gap detector cannot see it (found 2026-07-31, and this is worse than the known gappy failure).**
  Chasing the TTDB-growth blocker produced the size confirmation *and* a silent-corruption mode
  nobody had looked for. **The dose-response is clean and confirms size is the mechanism** for the
  bridged-pull failure recorded on 2026-07-30: V4-B at **54290 B** needed 4 self-heal rounds and
  still ended with **5, then 4, ranges missing**, twice; after its `@LAT97` lane was pruned to
  **30637 B** the same bridged pull completed **first pass, zero gaps, zero re-request rounds**.
  ⚠ **But that "clean" 30637 B pull is not a valid TTDB.** Its last record, `@LAT96LON46`, carries
  an `ENTITY`/`ENTWIN` body **with `LINKWIN`/`LINK` content appended after it** — stale `@LAT97`
  bytes from the *pre-compaction* file, at exactly the offset a stale tail would land. The other
  three files pulled this session (V4-B before, T-Deck before/after) are internally consistent, so
  this is not an analysis artefact: `@LAT96` is `EntityPercept`'s lane and `LINK*` is
  `LinkPercept`'s format — one record can never hold both.
  **Mechanism: the pull is offset-addressed, and nothing pins the file's generation.** `removeLane`
  rewrites and shortens the file; the percept lanes also append a window every ~60 s. A bridged
  pull takes minutes. So the reassembled object can be stitched from slices that referred to
  different generations of the file, and **`missing_ranges` only checks offset *coverage*, not that
  the covered bytes came from one version** — full coverage of a moving target reads as success.
  📎 **This retroactively weakens every "byte-exact bridged pull" claim taken while a node was
  mutating its TTDB.** Direct-cable pulls are much less exposed (one shot, seconds — the T-Deck's
  39789 B came back in a single pass), which is probably why this went unseen: the 2026-06-25
  byte-exact result was an 858 B file that took no time to move. **Do not trust a bridged pull as
  a source of truth until the object is generation-stamped** (a version/CRC in the EOF marker that
  the reassembler checks, or a serve-time snapshot) — that is the fix, and it is a real one, not a
  retry.
- ⚠ **LOOPING `companion.py` POWER-CYCLES THE BRIDGE ONCE PER PROBE — and that fabricated a
  two-node outage that did not exist (2026-07-31).** A shell loop of `ping --port COM6` over the
  five nodes reported **V4-C and the Cardputer UNDELIVERED** after 4 attempts each, twice, and
  was written up here as "only three nodes are on the mesh, probably flat batteries". **Wrong.**
  Every invocation opens the port with DTR/RTS asserted, so **each probe rebooted V4-A and then
  measured the mesh through a bridge that was still settling.** The operator saw it directly —
  *"V4-A is power cycling"* — which is the only reason it was caught.
  ✅ **One held connection, opened with `open_serial_no_reset`, reaches everything: 15/15 over 3
  rounds** (`scratchpad/reach.py`) — V4-A 1,1,1 · V4-B 1,2,1 · V4-C 1,2,1 · T-Deck 2,1,1 ·
  Cardputer 2,1,1 attempts, 100–650 ms. **The full five-node fleet is up and the stated bench
  geometry IS collectable.**
  ⚠ **This also retracts the "over-air CMDs are marginal, 4 attempts is sometimes not enough"
  claim** made from the same runs: on a held connection nothing ever needed more than 2. The
  `clear-percepts` no-ACKs that looked like radio loss were mostly self-inflicted for the same
  reason. What *does* survive: an already-empty-lane clear still ACKs `APPLIED` over USB, so
  **`removeLane` is genuinely idempotent** and a no-ACK never meant a rejected command.
  📎 This is [[verify-before-believing]] and the `intero`-resets-the-node note generalised:
  **any looped `companion.py` invocation measures a freshly-rebooted bridge.** The instrument has
  to outlive the thing it measures — hold ONE connection and probe many times. The dose-response
  result above is unaffected (single invocation on both sides, internally controlled), and so is
  the two-generation corruption finding (a content check on a file, not a timing claim).
- **Prune done where it could be, and `@LAT96` is now the lane that matters.** `@LAT97` cleared on
  **V4-A** (USB), **V4-B** (over air), **T-Deck** (USB — verified by pull, 39789 → **26301 B**,
  48 records gone). **V4-C and the Cardputer are still unpruned** — not because they were
  unreachable (they were not; see the retraction above) but because the probe that said so was
  broken, and the clear was never re-attempted against them. Do that first next session. ⚠ **`CMD_CLEAR_PERCEPTS`
  drops `@LAT97` ONLY** — the `@LAT96` entity lane has **no prune command at all** and is now the
  dominant consumer on every node (T-Deck 48 records ≈ 26 KB after the `@LAT97` clear; V4-B 29).
  Both nodes were sitting at the **48-record lane cap on both lanes**, i.e. saturated and silently
  dropping new evidence. A lane argument on op 8 is the obvious next increment.

- **SP1/SP2 RUN IN A STATED INDOOR GEOMETRY (2026-07-31) — ORDERING PASSES, METRIC FAILS, AND
  THE EMBEDDING DEGENERATES.** First positioning collect since the lanes were pruned, against an
  operator-stated layout (V4-A + T-Deck ~2 ft apart and cabled, Cardputer across the room, V4-B at
  the front door, V4-C on the dining table). Collected with `scratchpad/collect.py`, which pulls
  the two cabled nodes over **their own cables** and only bridges the rest, then checks each file
  for the two-generation stitch before `proximity --no-pull` consumes it.
  ✅ **The rank ordering is CORRECT on both tiers, and that is the honest claim.** espnow:
  V4-A↔T-Deck **3.83 m** (nearest, and by ~2× over the next pair), T-Deck↔Cardputer 7.27,
  V4-A↔Cardputer 7.62, V4-C↔T-Deck 7.62, V4-A↔V4-C 14.15, V4-A↔V4-B 23.88, V4-B↔T-Deck **27.55 m**
  (farthest). BLE ranks identically (0.33 → 25.12 m). **The 2 ft pair is picked out as nearest and
  the front-door node as farthest, from umwelt overlap alone.**
  ⚠ **The metric is badly wrong, exactly where the model says it should be.** ~0.6 m of true
  separation reads **3.83 m on espnow — 6× over** — that pair sits far below the calibration fit's
  **3.75 m valid floor**, so it is pure extrapolation. **BLE is much better near (0.33 m vs a true
  ~0.6 m) and much worse far** (1.0 m for a room crossing of ~4–5 m), which is precisely the
  "near-range approximation tier" role it was given. The two tiers disagree by **2–7× on the same
  pair**.
  ⚠ **Triangle inequality violated beyond what sigma absorbs:** V4-A and T-Deck are ~0.6 m apart
  yet their distances to V4-C differ 2× (14.15 vs 7.62 m, sigma 4.09 / 2.46).
  ⚠ **`positions` collapsed to ~1D — 32.6 m wide × 1.5 m tall, every y ≈ 0.** Under-determined:
  only **7 pairs from 3 observers**, all the V4-B/Cardputer pairs **one-directional** (their own
  windows were unreachable, so `asym_db` reads 0.0 and understates the real uncertainty), and 3
  pairs — V4-B↔V4-C, V4-B↔Cardputer, V4-C↔Cardputer — **missing entirely**. The solver is also
  fed **both tiers as separate constraints per pair** with 2–7× disagreement, so it splits the
  difference and cannot recover lateral structure. **Do not read `master/positions.md` from this
  run as a map**; the pair table is the result, the embedding is not.
  **The blocker is now specific and mechanical:** a bidirectional 5-node run needs V4-B's and the
  Cardputer's own `@LAT97` windows, which needs their TTDBs to pull, which needs the **`@LAT96`
  lane pruned** — and op 8 cannot do it. **A lane argument on `CMD_CLEAR_PERCEPTS` is the single
  next increment**, and it costs a reflash of all five nodes.
  📎 Two collection hazards worth keeping: `master/v4b_relay.md` and `master/cardputer_1.md` on
  disk were from **2026-07-13 (the garden run) and 07-27** — feeding those to `--no-pull` would
  have silently mixed a different field layout into today's map (moved to
  `scratchpad/stale_master/`). And `proximity --nodes` had been defaulting to a **stale 3-node
  list**; it now uses `DEFAULT_FLEET`.

- ✅ **`CMD_CLEAR_PERCEPTS` TAKES A LANE, AND THE DEFAULT IS NOW *ALL* PERCEPT LANES — built,
  flashed and verified on two nodes (2026-07-31).** The increment the SP1/SP2 run identified as
  its own blocker. Op 8 gains an **optional lane byte at `payload[5]`** (`toot::cmdClearLane`,
  the additive-byte convention `CMD_DUET`'s `speed` already uses): **0 or absent = every percept
  lane 94–97**, else exactly that lat. Absent meaning *all* is deliberate — the `@LAT96` entity
  lane previously had **no way to be cleared at all** on four of five nodes, and it is what grew a
  TTDB past what its own bridged pull can carry.
  **`Ttdb::removeLaneRange(lo, hi)` does it in ONE rewrite**, with `removeLane` now a thin wrapper.
  That is a real fix, not tidying: the Cardputer had been calling `removeLane` **four times**, so a
  prune cost four whole-file rewrites *and opened four separate windows in which the file moved
  under a concurrent reader* — the stitched-pull hazard above, self-inflicted four times per clear.
  🔒 **`Ttdb::removePerceptLanes(lane)` is the guard, and it lives in the library, not in five
  sketches.** Anything outside 94–97 is **refused, not clamped** — a caller asking for @LAT99 has a
  bug or bad intent, and pruning a different lane than the one requested would be worse than saying
  no. This is what stops op 8 being a general remote-delete for `@LAT0` identity, `@LAT98` belief
  attestations and `@LAT99` sync logs.
  ✅ **Verified on hardware, including the negative case** (V4-A COM6, T-Deck COM10, both flashed):
  `--lane 96` dropped **only** @LAT96 (48 records gone, 41 @LAT97 and the @LAT0 records untouched);
  the **default** clear took the T-Deck from ~36 KB to **3011 B / 4 records**; a raw
  `lane=99` on the wire (bypassing companion.py's own check, `scratchpad/lane_guard.py`) got
  **no ACK across 3 attempts — refused** — and the **control matters as much**: `lane=97` over that
  same raw path ACKed on attempt 1, so the refusal is specific to the protected lane and not the
  extra byte breaking the parse.
  **Laptop side:** `cmd --op clear-percepts [--lane 94|95|96|97]` (0/omitted = all, validated
  client-side too so a doomed CMD does not cost 4 attempts to learn nothing), and
  `proximity --clear` now sends lane 0 — correct, because that consolidation consumes @LAT96
  co-occurrence as well as @LAT97 windows.
  ✅ **V4-B flashed too, and it is the node that PROVED the guard on real data (2026-07-31).** On
  V4-A and the T-Deck an all-lanes clear could not demonstrate anything about protected lanes —
  neither node had an `@LAT98` or `@LAT99` record to lose. V4-B did: it went **65818 B / 101
  records → 1504 B / 5 records**, and the survivors are exactly **3× `@LAT99` sync + 1× `@LAT98`
  belief + `@LAT0` identity**. The prune is surgical on a node that actually had something to
  protect.
  📎 Its pre-flash capture (front-door position, direct over COM9, **no stitching**) is kept at
  `scratchpad/v4b_frontdoor_capture.md` — the first time V4-B's own `@LAT97` windows have ever been
  collected. **Not fused into a map**: V4-B was at the bench to be flashed, so those windows and
  the other nodes' current ones describe two different geometries, and mixing them is the exact
  error the stale `master/*.md` files nearly caused.
  ⚠ **`@LAT97` refills to its 48-record cap in well under an hour** — V4-B was back at the cap ~2 h
  after the earlier clear. **Pruning is not a one-time fix**; the cap is hit continuously, so any
  node left running is dropping evidence between collections. That is now the growth story, not the
  file size.
  ✅ **Cardputer flashed too — and it is where LANE SELECTIVITY was proven, being the only node
  with all four tiers.** `--lane 94` dropped **exactly** the 48 acoustic records and left `@LAT97`
  48, `@LAT95` 48, `@LAT96` 5 and `@LAT99` 2 standing; the default clear then took it **63502 B /
  155 records → 3601 B / 6**, again keeping both `@LAT99` sync records and its `@LAT0`/`@LAT32`/
  `@LAT35` map records. Pre-flash capture (direct, COM14, no stitching) at
  `scratchpad/cardputer_preflash_capture.md`.
  📎 **CORRECTION to the record-count worry recorded earlier today.** §6 said the Cardputer "is
  growing ~1 record/min and `TTDB_MAX_RECORDS` is 256... the next thing that will bite". Measured:
  it sat at **155 records with three lanes already pinned at their 48-record cap**. The per-lane
  caps bound the total — 4 lanes × 48 = 192 percept records plus a handful of base/sync records,
  ~200, **under 256 by construction**. It was never going to overflow that way. The real growth
  problem is the one above (a lane that refills its cap in under an hour), not the record ceiling.
  ✅ **V4-C flashed — the WHOLE FLEET now carries the lane-aware prune (all five nodes,
  2026-07-31).** 63991 B / 97 records → **848 B / 1** (its `@LAT0` identity record), and the guard
  refused **lane 98** (the belief lane) the same way V4-A refused 99. Pre-flash capture at
  `scratchpad/v4c_preflash_capture.md`.
  📎 V4-C's earlier *bridged* pull read 7474 B against 63991 B direct here. That is **consistent
  with lane refill** (its `@LAT97` had just been cleared, and ~39 `@LAT96` windows at ~1/min fills
  the gap over the intervening hours), **not** evidence of a truncated pull — recorded because the
  two explanations are genuinely indistinguishable from what was kept, and the earlier file was
  overwritten before the question came up. Keep the pre-clear file next time.
  **Guard coverage as flashed:** refusal verified on **@LAT98 (V4-C) and @LAT99 (V4-A)**, with the
  `lane=97` control ACKing on attempt 1 so the refusal is specific; survival of real protected
  records verified on **V4-B (3× @LAT99 + 1× @LAT98)** and the **Cardputer (2× @LAT99)**; lane
  selectivity verified on the **Cardputer** (`--lane 94` of four lanes) and **V4-A** (`--lane 96`).
  📎 All five sketches compile: V4-A/V4-B/V4-C **94%**, T-Deck 40%, Cardputer 41%.
- **Repo-move breakage fixed where it was real (2026-07-31).** `tests/test_rfc_ttdb.cpp` +
  `tests/Makefile` now point at `replicate/RFCs/rfc.ttdb.md`, and both handhelds'
  `data/rfc.ttdb.md` were re-synced from the canonical corpus (34 → **36 records / 38014 B**, so
  TTDB-RFC-0009 is in the flashable image — **it reaches the glass only on the next FS flash**,
  which was deliberately NOT run: `Upload-Tdeck-FS.ps1` images the whole `data/` dir and would
  overwrite the live on-device TTDB).
  ⚠ **`test_rfc_ttdb` was failing on a stale hardcoded record count (33 vs 36)** — every
  structural check passed, only the count was stale. Bumped to 36 behind a named
  `kExpectedRecords` with a note that it is exact **on purpose**: it is the one check that catches
  a *truncated* corpus, which every other check in that file would happily pass.
  ⚠ **The native suite could not be rebuilt this session — there is no g++ and no `zig` on this
  machine** (the portable `zig c++` from an earlier session lived in the scratchpad, which is
  session-scoped and gone). The prebuilt `tests/*.exe` still run; the source fixes above are
  therefore **compile-unverified** and the next session with a toolchain should run `make`
  ([[no-host-cpp-toolchain]]).

- ⚠ **PRUNING DID NOT UNLOCK THE BIDIRECTIONAL COLLECT — the bridged pull fails at ~30 KB too,
  and the operative limit is now DWELL TIME (2026-07-31).** After the whole fleet was cleared in
  position and left 25 min to refill, **all three bridged pulls returned "no data"** while the two
  cabled nodes came back fine at **28791 B (V4-A, 34 windows)** and **29980 B (T-Deck)**. The three
  silent nodes were cleared at the same instant, so they are the same size.
  **Two candidate explanations were tested and BOTH eliminated**, which is the only reason the
  third is worth stating:
  - **Not the settle.** The stock 2.5 s post-open wait was raised to 6 s with a retry at 9 s
    (a bridged pull must wait out the *bridge's* boot too, and the bridge has the multi-second
    early-boot stall). No change — still no data on all three.
  - **Not the DTR reset.** `reach.py` and `clear_all.py` both work over the bridge and both open
    with `open_serial_no_reset`, so the pull was re-run the same way (`scratchpad/pull_noreset.py`).
    Still no data. The reset is not the discriminator.
  ⚠⚠ **VOLUME WAS ALSO WRONG — and this entry said otherwise for an hour, so read the end, not the
  middle.** It first concluded "what is left is volume", reasoning that a bridged CMD is one frame
  where a 30 KB TTDB is ~150. **The decisive test killed it:** the T-Deck is cabled *and* on the
  mesh, so the same node can be pulled both ways within a minute. Direct: **10232 B, clean, first
  pass.** Bridged, same minute: **no data.** Then, minutes later, bridged again: **14389 B (3 gaps
  after 4 rounds).** A size ceiling cannot fail at 10 KB and succeed at 14 KB.
  **So the bridged pull is INTERMITTENT, and after four eliminations the cause is still unknown:**
  not the settle, not the DTR reset, not volume, and **not the firmware flashed today** — the
  `v4a_bridge` diff is six lines entirely inside the `CMD_CLEAR_PERCEPTS` branch and cannot reach
  TTDB_REQ forwarding. Bridged **CMDs** (ping, clear) succeed against all five nodes throughout.
  The mesh is simply flakier this evening than this morning, unexplained.
  📎 **The lane prune was necessary but NOT sufficient, and dwell-time tuning is NOT the lever it
  looked like.** Trading sample size for a smaller file does not buy reliability from a link whose
  failures are not size-driven. **Do not spend another session tuning dwell or retry counts** —
  that is the "chase a flaky measurement" pattern this file already warns about three times.
  **Next move is the transport itself: the generation-stamped / snapshot serve** the stitched-pull
  finding already called for. It is now blocking the science, not just data integrity. Until then
  **a node's own cable is the only trustworthy collection path** — 100% reliable on every node,
  every attempt, all day.

- ⚠ **FOOTGUN I WALKED INTO: `scratchpad/lane_guard.py <port> <node> 97` is a REAL CLEAR, not a
  probe.** It was written to prove the firmware refuses a protected lane, and its *valid-lane
  control* genuinely prunes. Reaching for it as a "ping-like contrast" during the collect **wiped
  the T-Deck's `@LAT97` lane mid-experiment** and threw away the 8-minute dwell it had just
  accumulated — caught red-handed by the passive tail: `[link] percept lane 97 cleared (TTDB now
  3711B, 6r)`. Its success message is also inverted for the control case, which is how it read as
  reassuring. **Use `scratchpad/reach.py` when you want a harmless probe**; lane_guard mutates.
- **WHERE THIS SESSION STOPPED (2026-07-31, paused for the night).**
  **Done and solid:** K10 parked out of all defaults (code kept); the lane-aware prune built,
  compiled, flashed and verified on **all five nodes**; repo-move breakage fixed in the tests;
  RFC corpus re-synced to both handhelds' `data/`.
  **Open, in priority order:**
  1. **Generation-stamped / snapshot TTDB serve** — the one fix that unblocks both the silent
     two-generation stitch and the intermittent bridged pull. Everything else waits on it.
  2. **The bidirectional 5-node SP1/SP2 run** — still not achieved. The last completed fuse
     (ordering ✅, metric ✗, embedding degenerate) came from **3 observers, one-directional**.
  3. **`@LAT96` has no consolidation consumer yet** — it is pruned by lane 0 but only feeds
     `entity_bounds`; worth deciding whether it should survive a prune longer than `@LAT97`.
  4. Native test suite unrun (no g++/zig this machine); T-Deck FS not reflashed, so TTDB-RFC-0009
     is in the repo image but not on its glass.
  **Fleet as left:** all five powered and reachable; every percept lane recently cleared and
  refilling, so nothing on any node is a usable sample yet. V4-A on **COM6** (bridge), T-Deck on
  **COM10**; V4-B, V4-C, Cardputer on battery in the stated positions. Working tree has
  uncommitted changes across firmware, orchestrator, tests and docs.

- **2026-08-01 — SPEC SYNC + THE TRANSITION FORM (`percept-learning-handoff.md`, Stage A).**
  Worked the handoff staged in `toot-toot-engineering` (TTE). Two halves, one blocked.
  **① Spec sync — done in the repo, NOT on the glass.** All five drifted RFC files pulled from
  TTE (verified by content, not timestamp: TTE was newer on all five and every change was
  purely additive), plus `replicate/agent-memory-system_ttdb.md` → Draft 06. `cmp` across the
  whole corpus is now silent. The headline is **TTDB-RFC-0003 v1.1 §7: `opposes`**, a
  *symmetric* type for **semantic polarity** — explicitly NOT the epistemic `contradicts`
  (under `opposes` **both endpoints may be true**: *Joy* and *Grief* both exist and the store
  is not thereby inconsistent). §7.1: implementations MUST NOT infer the reverse edge, so the
  author writes **both** directions; every existing parser stays correct unmodified.
  **② The feelings globes were MERGED, not overwritten**, per handoff §1.3, by script
  (`scratchpad/merge_feelings.py`): canonical TTE store as the base, then each device's own
  header paragraph and its `type:band` overlay records re-applied. Result: T-Deck 46 records,
  Cardputer 47, **22 `opposes` edges each**. The two device copies differ *deliberately* —
  each console draws the OTHER band members and never itself — so that drift was left alone,
  not "fixed". The canonical `agent_note` (which is the only written record of the `opposes`
  work and of the deliberate `sal:0` policy) now travels with them.
  📎 The globes grew 44→46 / 45→47 records and the worst record went to 5 edges, still under
  `NODE_EDGE_MAX 6`, so nothing new truncates. **Pre-existing and untouched:** `@LAT0LON0`
  carries **17** edges and has always been silently cut to 6 by the globe cache.
  **③ Stage A shipped: `MotionPercept` now writes the difference down (`@LAT93`).** The tier
  already computed both sides of a `still → moving` edge and threw the pairing away; it now
  emits a paired `@PERCEPT:before` → `@PERCEPT:after` record on a verdict **change** (never on
  a repeat, so a node on a shelf writes none). Three findings worth more than the code:
  1. ⚠ **The pair must be ONE record, not two.** TTDB-RFC-0006 §7.1 calls an orphaned `before`
     an *error*, and `Ttdb::appendRecord` has no transaction — two appends means power loss
     between them creates exactly that orphan. **A single atomic append is the only way a
     fixed-RAM streaming writer can keep §7.1's promise.** That is a spec answer, not a
     workaround, and Part 4 owes it to TTE.
  2. ⚠ **`@PERCEPT:` COLLIDES WITH TTDB-RFC-0001 §3.** A record header is *any line whose first
     character is `@`* (`TTDB.cpp:24`), so an unindented `@PERCEPT:before` in a body is indexed
     as a record header, fails to parse, and becomes a **phantom (0,0) record**. The two lines
     are **indented two spaces** and must stay that way; the native test asserts it.
  3. The pair is **also** written as real `derived_from` edges to each half's `@LAT95` record,
     because the same lesson RFC-0003 §7.3 draws about polarity applies: what is encoded only
     positionally (or only in a body) is invisible to a consumer reading the edge list, which
     is what the renderer actually traverses. Those edges CAN dangle once the `@LAT95` lane
     wraps, which is why both state blocks are duplicated inline — the record stays
     self-sufficient without them.
  A measured pair is **589 B**. `MOTIONPERCEPT_TRANSITION_BUF` is **768** deliberately: a
  pair that does not fit renders **0 bytes rather than a truncated `before`**, so an
  under-sized buffer loses transitions *silently* — a first pass at 512 did exactly that and
  only the test caught it. Lane `@LAT93` is deliberately **outside** the 94–97 block
  `CMD_CLEAR_PERCEPTS` drops: percept windows are cheap raw evidence, a transition is the
  thing the node learns from. Cap `MOTIONPERCEPT_MAX_TRANSITION_LANE 32`, and a full lane
  **says so on serial** — silently dropping transitions looks identical to a node that never
  moved, which is the opposite claim.
  📎 **A discarded window BREAKS the chain** (`reset()` clears it) rather than pairing across
  the gap: the sketch throws a window away when the `@LAT95` lane is full, and pairing over it
  would assert an edge across a window nobody measured.
  **④ Tests — the suite now BUILDS, which it did not.** `tests/test_motionpercept.cpp` (48
  checks) pins the `@LAT95` format that `MotionPercept.h` had admitted was *"verified only on
  hardware"*, plus the whole transition contract. `tests/test_symmetric_edges.cpp` (7 checks)
  is RFC-0003 §7.1's "validators SHOULD report one-directional symmetric edges", run against
  the globes the handhelds actually carry; it also **fails if it finds no symmetric edges at
  all**, which is what a bad merge against canonical would produce. ⚠ **`test_linkpercept` had
  not compiled for some time** — it asserts on `windowStartMs()`, which did not exist (no
  `.exe` in the repo is the tell), so `cd tests && make` failed at *build* for every test.
  Added the one-line accessor; **all 8 tests now build and pass** (48/·/·/48/10/7/27/45).
  Built with portable **zig** (`zig c++`, no host g++ on this machine — see the memory note);
  `scratchpad/t.sh` is the one-test wrapper.
  **⑤ Cardputer sketch wired and compiling** — `41%` flash / `34%` RAM on
  `huge_app,FlashSize=8M`. **Not flashed.**
- ✅ **2026-08-02 — THE TRANSITION FORM RUNS ON HARDWARE. Stage A is on-device verified.**
  Cardputer (0x300) on **COM14** (identified by `VID_303A&PID_1001`, never by remembered COM
  number). Firmware + FS both flashed; new globes confirmed by the boot line — **RFC globe
  38819 B / 36 records** (was 34047 / 34) and **feelings 35816 B / 47 records** (was 32522 /
  45), i.e. the v1.1 corpus with §7 `opposes` and the merged globe are now **on the glass**.
  📎 **The pre-flash pull is itself the cleanest confirmation of `@LAT98LON6` this project can
  offer.** The node's TTDB was pulled before being overwritten (41400 B, 114 records, kept at
  `master/preflash-2026-08-02/cardputer_ttdb.md`): **34 `@LAT95` motion-state records and
  ZERO `@PERCEPT:` markers.** Thirty-four windows of a device noticing its own motion, and not
  one recorded difference. That is the representational gap, measured on this fleet's own
  hardware rather than argued.
  **The run.** Held ONE serial connection for 7 min (`scratchpad/watch_motion.py` — no reset,
  per the looping-companion.py lesson) while the device was left still, carried/waved, then
  set down. Nine 60 s windows; **two transitions, both directions**:
  ```
  [  246.7s] [motion] still -> moving TRANSITION -> @LAT93LON0 (559B, TTDB 6226B)
  **TRANSITION** t_ms:300010 synced:0 node:0x300 from:still to:moving dt_ms:60000
    @PERCEPT:before state:still  moving_permille:52  dev_mean_mg:22  lane:@LAT95LON3
    @PERCEPT:after  state:moving moving_permille:735 dev_mean_mg:227 lane:@LAT95LON4
  **DELTA** edge:became d_permille:683 d_dev_mean_mg:205 d_dev_max_mg:620
  ```
  plus `@LAT93LON1` `from:moving to:still` (`derived_from@LAT95LON6,@LAT95LON7`). **559 B on
  flash — exactly the native test's measured 559 B**, so the format is pinned end to end.
  TTDB 3267 → 8773 B over the run; the two pairs are 1118 B of it.
  ✅ **The `@PERCEPT:`/RFC-0001 §3 collision is real AND the two-space indent resolves it, on
  device.** The node's own reader reports **`TTDB loaded: 8773 bytes, 26 records`** and the file
  contains exactly **26** lines beginning with `@` — all of them `@LAT`. **Zero phantom (0,0)
  records** from four `@PERCEPT:` markers. Unindent them and this number would have been 30.
  📎 **New finding the native test could not have produced: the transition is QUANTIZED TO THE
  WINDOW.** The device was set down partway through `@LAT95LON6`, which still scored 129
  permille — just over the 100 threshold — so it was judged `moving` and the `moving -> still`
  edge did not fire until the *next* window closed. **A transition's timestamp is therefore
  accurate to ±1 window (60 s), not to the physical event.** Fine for Stage B/C; it is a
  problem for anything that wants to order transitions finely across nodes, and it compounds
  with the unresolved loop stall rather than replacing it. (Worst pass over this 7-minute run
  was a benign **200 ms**, widest section `entity` 111 ms — the multi-second stall did not
  appear in this window, which per the `lp` lesson proves nothing about its absence.)
  📎 Node was alone, so **`synced:0` and `created:0`** throughout: transitions carry local
  `millis()` and correctly refuse to claim cross-node orderability. `dt_ms:60000` on both, by
  construction (consecutive windows).
- 🔇 **2026-08-02 — THE FLEET NOW BOOTS SILENTLY (`STARTUP_TOOT 0`).** One switch for all six
  nodes, in **`RobotTeamConfig.h`** (every sketch already includes it); flip to 1 and reflash
  to get the "toot toot" signature back everywhere. **Only the automatic play at boot is
  gated** — I2S/codec bring-up is untouched, because the speaker still has to be ready for
  band notes, `CMD_BEEP` and the duet, and on the Cardputer the same I2S bus feeds the mic.
  ⚠ **The `playStartupToot()` functions and their tone paths are deliberately left COMPILED,
  not `#if`-d out.** Each board's audio was hard-won in a different way (K10 GPIO45-vs-TFT_BL,
  the V4s' square-wave-only 8 kHz MAX98357A, the T-Deck's rail behind `PIN_POWERON`, the
  Cardputer's ES8311 with no MCLK and a dB-not-linear volume register) and **the boot toot is
  the fleet's audio smoke test**. Keeping it compiled stops it rotting when a tone signature
  changes; the linker drops it, so a silent build costs nothing. The K10's call stays *before*
  `initScreen()` on purpose — a toot that plays there while later tones are silent is the
  signature of a bad `TFT_BL 45`, and that diagnostic only exists if the code does.
  All six compile clean (K10 20%, V4s 94%, T-Deck 40%, Cardputer 41%).
  **Flashed + verified silent on the two that were on the cable: T-Deck (COM10) and Cardputer
  (COM14).** ⚠ **The three V4s and the K10 still carry the tooting firmware** — they were not
  attached. Reflash them when they are next on a cable, or the fleet is only half quiet.
- ✅ **The T-Deck's FS is now reflashed too** (same session, COM10): boot reports **RFC globe
  38819 B / 36 records** (was 34047 / 34) and **feelings 34939 B / 46 records** (was 31664 /
  44). **Both handhelds are finally off the v1.0 spec globe** — §7 `opposes` is on both
  screens. Its pre-flash TTDB (17500 B, 37 records) is kept at
  `master/preflash-2026-08-02/tdeck_ttdb.md`.
  📎 The T-Deck's flaky native-USB auto-reset **worked unattended this time** — no BOOT/RST
  dance was needed for either the app or the FS. Do not rely on that; CLAUDE.md's manual
  procedure stands as the fallback.
  📎 The Cardputer's `@LAT93` records **survived the firmware reflash** (LittleFS is untouched
  by an app upload): both transitions still read back after re-pulling, TTDB now 17307 B / 60
  records and still accumulating.
- ✅ **2026-08-02 — STAGES B + C RUN ON HARDWARE. The node now PREDICTS and TESTIFIES.**
  New portable lib `firmware/libraries/PerceptLearn/` (39 native checks) + `@LAT92` outcome
  lane on the Cardputer. Rule 1: a `still` @LAT95 window is a positive claim that the node
  was anchored, so it arms an expectation that each peer's median RSSI will hold within a
  band next window — falsifiable in 60 s against `@LAT97`, which already existed. Rule 2:
  the verdict is APPENDED to a side lane and **nothing in the live loop edits any `[ew]`**.
  Device-written record:
  ```
  @LAT92LON0 | ... relates:testifies_about@LAT95LON44,derived_from@LAT97LON28,senses@LAT0LON0
  **OUTCOME** t_ms:122007 synced:0 node:0x300 acting:@LAT95LON44 observed_in:@LAT97LON28
              band_dbm:6 met:2 violated:0 unobserved:0 streak:0
  **EXPECTED** peer:0x00000200 proto:ble    predicted_med:-53 band:6
  **OBSERVED** peer:0x00000200 proto:ble    observed_med:-53 delta:0 verdict:met
  **EXPECTED** peer:0x00000200 proto:espnow predicted_med:-37 band:6
  **OBSERVED** peer:0x00000200 proto:espnow observed_med:-37 delta:0 verdict:met
  **PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 basis:motion_state:still ...
  ```
  4 outcomes / 8 claims, **all met, delta 0 every time** — both handhelds flat on a desk.
  📎 **THE BAND IS THE FIRST CONSTANT IN THIS SYSTEM WITH AN EMPIRICAL BASIS.** 6 dBm is the
  **p90 of consecutive-window median drift across 33 link windows the node had already
  written while all 34 motion windows read `still`** (median drift 0–2 dBm, p90 1–6, max 27).
  Derived from `master/preflash-2026-08-02/cardputer_ttdb.md`, not guessed like `+2/−16`.
  📎 **Rule 3's asymmetry has a computable break-even, and it is 1/9.** Expected drift per
  window is `(1-p)(+2) + p(-16) = 2 - 18p`, zero at **p = 11.1%**. So `+2/−16` encodes "a
  claim must hold at least 8 times in 9 to be worth keeping." Setting the band at p90 puts a
  perfectly anchored node at ~10% — just inside break-even — deliberately, so Rule 3 is not
  flattered by construction. ⚠ **Widening the band would make Rule 3 look good and prove
  nothing; say so if you change it.**
  📎 ⚠ **A violation does NOT mean "this node moved."** RSSI cannot say which end of a pair
  moved, and the T-Deck is the roamer. The claim under test is "this link was stable."
- ⚠ **2026-08-02 — THE LEARNING LOOP WENT SILENT AFTER 4 OUTCOMES, AND NOTHING SAID SO.**
  `@LAT95` hit **48/48** (`MOTIONPERCEPT_MAX_LANE`) after ~48 min. That path just called
  `reset()` — no print — so every later window was discarded and `gLearn.disarm()` fired
  forever while `[link]` lines kept scrolling and the node looked perfectly healthy.
  **The motion lane fills ~2× faster than the link lane** (motion flushes with no peers in
  range; link needs an observation), so it is always the first cap to bite. Now logged, rate
  limited to once per 5 min. This is the third instance of the same lesson in two days:
  **on this fleet the dangerous failure is always the silent one, and only a test or a print
  catches it.**
- 🔬 **2026-08-02 — THE MOVING RUN. First evidence anyone has about `+2/−16` and `K = 3`.**
  Cardputer flat and untouched on the desk; T-Deck carried to another room and back over
  ~10 min. 7 outcomes, **14 claims: 9 met, 5 violated**. Raw, per (peer,proto):
  ```
        espnow                    ble
  LON17 -41  d=-1  met      LON17 -55  d= 0  met     <- both on the desk
  LON18 -45  d=-4  met      LON18 -56  d=-1  met
  LON19 -83  d=-38 VIOLATED LON19 -93  d=-37 VIOLATED  <- being carried away
  LON20 -83  d= 0  met      LON20 -92  d= 1  met     <- PARKED far away
  LON21 -82  d= 1  met      LON21 -86  d= 6  met     <- still parked (d=6 == band edge)
  LON22 -54  d=28  VIOLATED LON22 -69  d=17  VIOLATED  <- being carried back
  LON23 -50  d= 4  met      LON23 -59  d=10  VIOLATED  <- settling
  ```
  ✅ **THE HEADLINE: violations track CHANGE, not distance.** The two windows where the
  T-Deck sat parked in another room at **−83 / −93 dBm** were **MET** — the link was far
  but stable, which is exactly what the expectation claims to test. Only the transit
  windows failed. The prediction measures what it says it measures, and a 40 dB gap does
  not fool it. (The band edge was genuinely exercised too: `d=6` == 6 read as met.)
  📊 **Rule 3, applied by hand from these records** (start `conf:128`, met +2 sat, violated
  −16 floor 0 / sal +8): **espnow 128 → 106** (−22, sal 16), **ble 128 → 88** (−40, sal 24,
  contradiction flag raised on 2 consecutive). Pooled: **128 → 66**.
  Violation rate **35.7%**, which is **3.2× the 1/9 break-even** — so Rule 3 drives
  confidence hard down, as designed.
  ⚠ **VERDICT ON `+2/−16`: the asymmetry assumes violations are EXCEPTIONAL, and in this
  fleet they are ROUTINE.** Recovery costs 8 met windows per violated one, so a roamer that
  moves even once an hour keeps every link belief permanently depressed. That is not
  "self-regulating", it is **self-extinguishing**. Either the belief is mis-framed or the
  constants are wrong for a domain where change is normal rather than anomalous.
  📎 And note *why* it is arguably mis-framed: the node is penalised for **its peer's**
  behaviour. RSSI cannot say which end moved, the Cardputer never moved at all, and it still
  lost 22–40 conf. A belief the agent cannot act on is a strange thing to punish it for.
  ⚠ **VERDICT ON `K = 3`: it would NOT have fired.** Device-reported window streaks were
  `0,0,1,0,0,1,2` — **max 2**, one short. A *complete relocation of the peer* did not trip
  the abort. At 60 s windows, K=3 demands **three minutes of continuous geometry change**,
  and ordinary movement between two places does not last that long — the roamer arrives and
  stops. So on this observable **K=3 never fires**, and Stage E would keep asserting a stale
  distance straight through a relocation. K must drop to 2, or the window must shorten, or
  Rule 4 needs a different trigger. **K and the window length are not independent knobs.**
  ✅ **The lane-full logging fix paid off inside one run.** `@LAT92` hit its 24 cap and
  **said so** — 2 outcomes dropped loudly instead of silently. That is the same failure that
  went unnoticed for 44 windows earlier the same day.
- 🏁 **2026-08-02 — STAGE D RUNS. THE STORE RECONCILES ITSELF.** The Cardputer's Dream
  Cycle (`DREAM_RECONCILE_MS` 3 min, `reconcileBeliefs()`) re-reads its own `@LAT92`
  outcome lane **off flash**, folds every claim through Rule 3 from a fixed baseline, and
  rewrites an `@LAT91` LINK-STABLE belief lane. Device-written:
  ```
  @LAT91LON1 | ... relates:believes_about@LAT0LON0,reconciles@LAT92LON0,...
  [ew]
  conf:140   rev:1   sal:16   touched:0
  [/ew]
  **LINK-STABLE** peer:0x00000200 proto:espnow node:0x300
  **TALLY** met:22 violated:2 unobserved:0 baseline_conf:128 rule:+2/-16 max_streak:1
            contradiction:0
  **PROVENANCE** rule:LearningFromAction/Rule3 src:@LAT20LON3 recomputed_from:@LAT92
                 lane_records:24 method:sequential_fold_from_baseline
  ```
  plus `@LAT91LON0` ble **conf:122 sal:24, met 21 / violated 3, contradiction:1**.
  ✅ **These are the FIRST records on this fleet carrying a TBEW `[ew]` block at all.**
  ✅ **VERIFIED BY INDEPENDENT RECOMPUTATION.** The same 24 `@LAT92` records were re-folded
  on the laptop, in lane order, from the same baseline: **ble 122/24, espnow 140/16 — exact
  match on conf, sal, met, violated, max_streak and the contradiction flag.** Two different
  implementations, same evidence, same answer.
  📎 **That check is the whole reason the belief is recomputed from baseline each cycle
  instead of accumulated.** A running total would have produced the identical two numbers
  and proved nothing — it would be the node REMEMBERING. Re-reading the lane makes it the
  store RECONCILING, and it means anyone holding the `@LAT92` records can audit the node's
  arithmetic. **TTE Draft 06's standing caveat — "the reconciliation was performed BY HAND,
  by an outside reader" — is discharged.**
  📎 Two properties to carry back to the spec: **(1) pruning the outcome lane resets the
  belief toward baseline** — not a bug, the belief is exactly as strong as the testimony
  still retained, but it means Rule 3's `conf` describes *retained evidence*, not history,
  and a store that prunes forgets what it concluded. **(2) Folding must be SEQUENTIAL**:
  `+2` saturates at 255 and `−16` floors at 0, and a clamp does not commute with a sum, so
  tallying met/violated and applying the arithmetic once is subtly wrong over long runs.
  📎 The rewrite is **skipped when nothing changed** (`[dream] ... no change (conf steady)`)
  — a lane rewrite is a whole-TTDB flash operation, and re-running a pure function to write
  identical bytes is just flash wear.
- 🚧 **STILL OPEN after 2026-08-02.**
  1. ⚠ **STAGE D IS BLOCKED ON TWO STRUCTURAL FACTS, both discovered today and both worth
     reporting to TTE regardless of when D gets built:**
     a. **The node's own TTDB carries ZERO `[ew]` blocks.** Rule 3 moves `conf`/`sal` — and
        there is nothing on this node that has either. The globes that do (`rfc.ttdb.md` 36,
        `feelings.ttdb.md` 46) are read-only reference corpora in separate files. **Stage D
        must first CREATE the thing it reconciles** — proposed: an `@LAT91` per-(peer,proto)
        LINK-STABLE belief carrying `[ew]`, starting at `conf:128` (mid-range, so movement
        is visible both ways: 64 windows to saturate at +2, 8 to floor at −16).
     b. **`Ttdb` has NO in-place update** — only `appendRecord`, `removeLane`,
        `removeLaneRange`. Moving a `conf` means rewriting the whole lane, which is a
        Dream-Cycle-scale flash operation, not a per-window one. That is *consistent* with
        Rule 2 (the live loop must not mutate) but it means reconciliation has to be a real
        Dream Cycle pre-phase, not a counter.
     📎 To answer TTE's actual question — *"its only reconciliation was performed by hand, by
     an outside reader"* — Stage D should recompute the tally **by reading the `@LAT92`
     records back off flash**, the way an outside reader would, NOT from a RAM counter kept
     during scoring. A running total would be cheaper and would not prove the thing.
  2. 📎 **A stationary pair cannot test the constants.** 8/8 claims met with delta 0 is a 0%
     violation rate, far under the 1/9 break-even, so Rule 3 would simply saturate `conf`.
     **The interesting run needs the T-Deck carried away and back** while the Cardputer sits
     still. Plan the motion before building D, or D will produce a monotone graph.
  3. **The three V4s and the K10 are unflashed** for the silent-boot change (above), and the
     V4 sketches sit at **94% of the default app partition** — the next feature added to them
     probably needs `huge_app` first.
  4. **Stages D–E are untouched.** A writes the difference down; B and C predict and
     testify. **Nothing reconciles anything yet**, so `+2/−16` and `K = 3` are **still
     unrun — exactly as unproven as in TTE Draft 06.** D is the actual experiment; do not
     let A–C become the deliverable.
  3. Only the Cardputer has an IMU, so the transition tier is single-node. Multi-node
     transition ordering is unexercised and, per the quantization finding above, needs a
     sub-window timestamp before it would mean anything.

- 📋 **THE HANDOFF: [timestream-handoff.md](timestream-handoff.md)** (written 2026-08-02
  against `33a7a02`). Three parts, and the order matters:
  ✅ **Part 1 (the VERIFICATION GATE) IS COMPLETE — 1.1 through 1.6 all pass**, later the
  same day; see the four entries below for the results and the two defects it flushed out.
  **`percept-learning-return.md` is now CLEARED to go to TTE**, and **no §0b verdict
  changed**: `+2/−16` and `K = 3` both survived re-testing at n≥3.
  *(Historical, for the record — the two things the gate was most worried about:
  `reconcileBeliefs()`'s untimed whole-TTDB rewrite, now measured at 150 ms→1757 ms and
  O(file); and the `+2/−16` / `K = 3` verdicts resting on n=1, now n≥3 with a control
  group.)*
  **Part 2 is the team time stream** — `stream:<id>` + `wall:<0|1>` replacing the single
  `synced` bit, riding on Pulse's existing era/conductor rather than a new subsystem. The
  headline reason: **`touched:0` makes TBEW recency inert**, so `@LAT91`'s `sal:24` can
  never decay and EPS has no time term. The epistemic-weight machinery cannot work on-device
  without a clock — and that is a spec gap, since **Rule 3 says how `sal` rises and never
  says what makes it fall.**
  **Part 3 is change-triggered logging**, which **depends on Part 2** (event logs cannot
  infer time from record position) and must obey three rules: heartbeat-or-change so absence
  is never ambiguous; correct for STATE but WRONG for EVIDENCE (a tally needs its
  denominator — leave `@LAT92` periodic or make it run-length); and thresholds DERIVED from
  each signal's measured noise floor, the way the 6 dBm band was.

- ✅ **2026-08-02 (later) — THE VERIFICATION GATE: Parts 1.1, 1.2 and 1.3 PASS.**
  Worked [timestream-handoff.md](timestream-handoff.md) Part 1 on hardware. Cardputer on
  **COM14**, V4-A bridge on **COM6**, T-Deck on battery as the roamer, V4-B and V4-C powered
  mid-session (all identified by `VID_303A&PID_1001`, never by remembered COM number).
  **① 1.1 — the Dream Cycle's flash cost is MEASURED, and it is a SCALING LAW, not a
  number.** `reconcileBeliefs()` now times itself in three phases and prints them
  (`[dream] TIMING fold Xms rewrite Yms append Zms TOTAL Wms (aB -> bB, n records)`), on the
  CHANGING path — the path that had never been observed. Measured across 9 cycles from 8.6 KB
  to 74 KB:
  ```
  bytes   fold  rewrite  append  TOTAL
   8652     14        1     135    150     (belief lane empty: nothing to remove)
  28511     31      265     291    587
  45054     45      443     325    813
  53347    110      537     442   1089
  61979     66      703     445   1214
  74272    197      999     561   1757
  ```
  **`removeLane` is O(whole file) at ~10-13 µs/byte** — and `appendRecord` is O(file) TOO
  (~50 ms each at 60 KB, because it re-runs the offset index), so a changing cycle costs
  **1 rewrite + N appends = 9 full-file passes at 8 beliefs**. It crosses **1 s at ~53 KB**
  and reached **1757 ms at 74 KB**. So the handoff's worry was right: this IS in the
  multi-second class, it fires every 3 min whenever a belief moves, and **at 120 BPM a 1.2 s
  stall is two and a half missed beats on a node that plays in the band.** Fix candidates
  unchanged: move the rewrite off `loop()`, or make the belief lane append-with-supersede
  (O(1)) instead of rewrite-in-place. **Not done — decide before Part 2 adds more writers.**
  🔎 **AND THE PROFILER WAS BLIND TO EXACTLY THIS.** `worst pass` was guarded by
  `if (loopStart)` with `loopStart` starting at 0, so **the FIRST loop pass was never
  measured** — and the boot Dream Cycle runs on precisely that pass (`last_dream == 0`). The
  profiler covering a window containing a 1089 ms pass serenely reported **`worst pass
  18ms`**. Fixed to measure from `gSectMark[0]` (the stamp taken at the top of *this* pass);
  it now reports `worst pass 1097ms widest section linkperc 1089ms` against a `TIMING ...
  TOTAL 1089ms` print from the same pass — **two independent instruments agreeing to 8 ms.**
  ⚠ This does NOT explain the older unexplained multi-second stall (that one was caught by
  the profiler, so it was never in the first pass), but any boot-time cost measured before
  today was invisible by construction.
  **② 1.2 — THE SHAPE CLAIM IS CONFIRMED WITH OPERATOR LABELS, and the separation is 23×.**
  Two runs. The first was unlabelled (the operator's timings drifted and the V4s came up
  mid-run), so its *shape* is uninterpretable — **but it accidentally supplied a CONTROL
  GROUP**, which the 2026-08-02 n=1 run never had: final beliefs `rev:9` after 24 outcomes
  were V4-B **172 (22 met, 0 violated)**, V4-C **170 (21/0)**, V4-A **140 (22/2)** versus the
  carried T-Deck at **44 ble / 40 espnow, 7 violated each, both CONTRADICTION**. The one
  device that was picked up is the only belief that collapsed, on both radios independently,
  in the same windows. Its violation rate **37%** against the earlier run's **35.7%**.
  The second run was labelled by the operator at each transition (walking → parked → back).
  The T-Deck's espnow link, window by window:
  ```
  LON13  walk starts 30s in    -5   met
  LON14  FULL TRANSIT         -36   VIOLATED
  LON16..LON20  PARKED FAR    +1,-1,0,+1,0   met x5   <- 36 dB away, |delta| <= 1
  LON21  set off to fetch it  +17   VIOLATED
  LON22  carrying it back     +26   VIOLATED
  LON23  settled on the desk   +1   met
  ```
  ✅ **Five consecutive windows at a distance that had moved the signal 36 dB, every one
  `met` to within 1 dBm — then violating again the moment the geometry changed.** The
  internal control over the whole run: **stationary peers 2 violations / 144 claims (1.4%)
  vs the roamer 12 / 37 (32.4%)** — same node, same windows, same 6 dBm band. The prediction
  measures what it says it measures.
  📎 **The 6 dBm band's false-positive rate is ~1.4%, and it is COMMON MODE when it fires**:
  the one bad parked window had **two stationary peers violating together** (−7 and +8, both
  barely past the band). Per `@LAT90LON70`, peers moving in lockstep is a shared-reference
  effect, not per-node drift.
  📎 **BLE contributes NOTHING at distance** — 9 windows with no claim armed at all once the
  T-Deck was parked. Correct for a 10–30 m radio, but the near-range tier is absent exactly
  when the espnow tier is most stressed.
  ⚠ **`K = 3` STILL NEVER FIRES — now across three independent runs.** Max streak **2** every
  time, including a full relocation and return. The written verdict hardens: at 60 s windows
  K=3 is unreachable by ordinary movement. **K and the window length are not independent.**
  ⚠ **`+2/−16` verdict unchanged and now n≥2 with a control**: the roamer's conf fell to
  40/44 and never recovered in 24 windows, because recovery costs 8 met windows per
  violation. Self-extinguishing, as recorded.
  📎 **The pre-walk period of the labelled run is NOT a still baseline** and must not be read
  as one — the operator was handling the roamer during it (trying the field-mark key), which
  shows as −15/−25/+37 dB swings. The first analysis pass labelled it "still" and produced a
  bogus **7% baseline violation rate** that would have buried the real result;
  `scratchpad/shape.py` now calls it `unlabelled`, because that is what it is. **Only label
  what the operator actually labelled.**
  **③ 1.3 — MULTI-NODE PASSES, all four bullets, three of them from the unlabelled run.**
  4 peers × 2 protos = **8 beliefs, EXACTLY `PERCEPTLEARN_MAX_BELIEFS`**, nothing dropped;
  a belief moved across cycles to **`rev:9`**; and the **`unobserved` verdict fired on
  hardware for the first time** (`unobs:1` on both T-Deck protos when it went out of range)
  and correctly did **not** count as violated. The handoff expected to force that by powering
  a peer off; walking one out of range did it, which is the more realistic case.
  ⚠ Hardware reached the 8-claim boundary but never crossed it, so **over-cap behaviour is
  still native-tested only** (a 9th pair needs a 5th node — the K10 is parked).
  📎 Subtlety worth keeping: a peer heard in NO window gets **no claim armed at all**, which
  is distinct from `unobserved` and is invisible in the tally (T-Deck espnow totalled 20
  windows against V4-B's 22).
  **④ TWO SILENT FAILURES FOUND AND FIXED IN THE CODE 1.3 WAS ABOUT TO EXERCISE.**
  `Loop::stage()` past `PERCEPTLEARN_MAX_CLAIMS` was a bare `return` — and the overflowed
  peer is still in `claims_`, so `score()` finds nothing staged and records
  **`VERDICT_UNOBSERVED`**, byte-identical to a peer that genuinely went quiet. A buffer
  overflow that reads as a plausible WRONG ANSWER, not a gap — and 4 nodes × 2 protos sits
  exactly on the cap. `Reconciler::slotFor()` past `MAX_BELIEFS` dropped a claim with no
  trace, folding `conf` from a subset of the lane while looking like a complete
  reconciliation. Both now counted (`stagedOverflow()`, `claimsDropped()`) and printed by the
  sketch. **This is the fourth instance in three days of "the dangerous failure is the silent
  one".**
  **⑤ Cross-check: `scratchpad/refold.py` re-folds `@LAT92` on the laptop** and compared 8
  pairs × 7 fields against the device's `@LAT91` — **0 mismatches**. Far stronger than the
  2-pair check of the morning; two implementations, same records off flash, same answer.
  **⑥ Tooling that should survive this session:**
  - **Portable `zig` now lives at `c:\tmp\toolchain\` — NOT the session scratchpad**, which is
    wiped between sessions and is why it had been re-downloaded three times. **There is no
    `make` on this box either**, so `scratchpad/t.sh [name...]` builds and runs the suite
    directly. All 9 tests build and pass (0 failures), including 11 new checks pinning the two
    caps above.
  - ⚠ **`tests/Makefile` never defined `PL_SRCS`** — the `test_perceptlearn` recipe invoked the
    compiler with no input files, so `make` could not have built that test at all. Fixed.
  - **`scratchpad/gate_watch.py`** holds one no-reset connection and tees to a log (optional
    `reset` 4th arg when the thing being measured happens AT BOOT); **`scratchpad/shape.py`**
    builds the per-(peer,proto) verdict matrix against operator labels; **`scratchpad/refold.py`**
    is the independent Rule 3 fold.
  - **`CMD_PING` is now a FIELD MARKER**: the Cardputer prints `[mark] FIELD MARK from 0x...`
    on a ping. The T-Deck's `p` key already defaults to the Cardputer, so **the operator can
    label a walk from anywhere in the house** without returning to the laptop — which is the
    thing that made the first labelled attempt fail. Verified from both the laptop (`0x1`) and
    the T-Deck (`0x200`).
  📎 **Operational note that cost a run:** `@LAT92` caps at 24 (~24 min of testimony) and
  **`CMD_CLEAR_PERCEPTS` deliberately cannot touch it** (the guard allows only lanes 94–97).
  So the reset between experiments is a **FS reflash** (`scripts/Upload-Cardputer-FS.ps1`),
  which also resets the belief toward baseline — correct for independent trials, but it means
  every run is capped at ~24 windows and must be planned to fit.
  📎 Pre-flash captures kept at `master/gate-2026-08-02/` (`cardputer_preflash.md` 61093 B /
  175 records, `cardputer_walkrun.md`, `cardputer_labelled.md`).
  **⑦ Gate status: 1.1 ✅ · 1.2 ✅ · 1.3 ✅ · 1.5 PARTIAL** (negchecks PASS on the T-Deck
  post-change, direct pull byte-clean 25253 B; radio_replay, bridged pull, band/intero/gps
  still to run) **· 1.4 and 1.6 NOT STARTED.** `percept-learning-return.md` still must not go
  to TTE until 1.4–1.6 pass, but **no §0b verdict changed** — `+2/−16` and `K = 3` both
  survived the n≥3 re-test, so the report's conclusions stand as written.

- ✅ **2026-08-02 (evening) — GATE PARTS 1.4 AND 1.5: THE WHOLE FLEET IS NOW QUIET, AND THE
  FLOOR SURVIVED IT.**
  **① 1.4 — all six nodes carry `STARTUP_TOOT 0`, and every speaker was proven by EAR.**
  V4-A (COM6, 94%), V4-B (COM9), V4-C (COM13) and the **K10 (COM3, 20%)** flashed; both
  consoles were already done this morning. Each was reset by the `cmd` port-open and then
  sent `CMD_BEEP`: **all four ACKed APPLIED on attempt 1 and all four were CONFIRMED AUDIBLE
  by the operator**, with silence at boot. That double check is the point — an ACK only
  proves `toneI2S` ran (`@LAT90LON70`), and **a silent boot and a silent node look
  identical**, which is exactly the failure this change could have introduced on four boards
  whose audio was each hard-won differently.
  📎 **The K10 is un-parked as a flashable node** (it stays out of the fleet defaults). It had
  been on v1 firmware since before 2026-07-31, so this brought a large unrelated delta with
  it. Checked the `TFT_BL` trap in the sketchbook `User_Setup.h` **before** flashing (K10 pins
  present, `TFT_BL` correctly undefined) — and the operator confirmed **both sound and a
  rendering LCD** afterwards. Its LittleFS was untouched by the app upload: **pull byte-clean
  at 14840 B and `negchecks.py` PASS** on the DFRobot core.
  ⚠ Note for the future: with the boot toot gated off, **the K10's oldest audio diagnostic is
  gone** — "startup toot plays but later tones are silent" was the signature of a bad
  `TFT_BL 45`. On that board `CMD_BEEP` is now the only audio smoke test.
  **② 1.5 — regressions PASS, except the one already known to be broken.**
  `negchecks.py` PASS on the **T-Deck** and the **K10** post-change (wrong-key → 0,
  tampered → 0, radio-only dedup intact). **`radio_replay.py` PASS** over the air — an exact
  `(src,seq)` duplicate dropped, a fresh seq served (attempt 1's original was itself lost in
  the air and it retried, which is the ambient mesh flakiness, not the dedup).
  **`band` PASS ×3 at ±3.4 / ±8.8 / ±9.4 ms** (bound ±50), four nodes on one chart,
  conductor **`0x300` era 20, 120 bpm**. `intero` answers over the bridge (V4-B 3.871 V/60%,
  48.2 °C die, 87 KB maxalloc, worst pass 35 ms).
  🔎 **THIS CORRECTS THE ALARMING READING OF 1.1.** The Cardputer is the **conductor**, and it
  is the node taking the 1.2–1.7 s Dream Cycle stalls — yet the band measured tight to ±9 ms
  across three runs. **The pulse is COMPUTED from a shared clock, not counted per beat**
  (TTN-RFC-0010), so a stall delays that node's own audible hit and its beacons but does
  **not** move the phase reference. The stall is a real problem for *this node's part* and for
  its mesh rtt; it is **not** a threat to band coherence. Do not repeat the "two and a half
  missed beats would drag the band" framing — it was measured and it is wrong.
  ⚠ **`gps` NOT RUN — the T-Deck went unreachable** (0/2 through the bridge, having answered
  that morning) after a full session on battery; put on a charger. **1.5 is complete except
  this one item.**
  ⚠ **Bridged pull STILL BROKEN and looks worse, exactly as CLAUDE.md predicts.**
  `pull --port COM6 --node v4b_relay` self-healed through 4 rounds and still ended
  **4 ranges short of complete** on a **41285 B** object. V4-B's lanes have refilled to ~42 KB
  since the 07-31 prune, which is consistent with the recorded pattern — **and consistent is
  all it is**: the size story was already DISPROVEN once (10 KB failed, 14 KB succeeded), so
  this is one more data point on an intermittent link, not a diagnosis. **Not tuned. Do not
  tune dwell or retries.** The generation-stamped / snapshot serve remains the open fix, and a
  node's own cable remains the only trustworthy collection path.

- ✅ **2026-08-02 (late) — GATE PART 1.6 PASSES, AND IT FOUND A RENDERER DEFECT THAT MADE
  ONE OF ITS OWN CHECKS IMPOSSIBLE.**
  **① `§7 opposes` is ON THE GLASS on BOTH handhelds** (operator-confirmed) — the finding
  the whole 2026-08-01 spec sync turned on, and until now verified only by byte count.
  **The feelings globe still renders its band overlay** after the merge. `gps` also answers:
  **12 sats, HDOP 0.7 indoors** (T-Deck COM10), completing 1.5.
  **② Why it could not be checked before: the record pane silently rendered the first ~40%
  of a record (T-Deck) and ~15% (Cardputer).** `renderRecord` read the body into a **520 B
  buffer** — not a scroll limit but a **READ limit: bytes past it never left flash.** The RFC
  globe's records average **1036 B and reach 2666 B**, and TTDB-RFC-0003's `opposes` clause
  sits at **body offset 865**, so it was *physically unreachable* on both devices. Nothing on
  screen said the record continued. **The operator was asked to look for something the
  firmware could not display** — and the check would have been recorded as a fail, or worse,
  hand-waved.
  **Fixed on both:** 3 KB read (covers every record the fleet carries — max 2666 B, with a
  `+` in the title if one ever exceeds it), the **whole** body wrapped so the page count is
  honest, and `pg n/m` in the title. **`1` pages forward, `2` back, both wrapping.**
  ⚠ **On the Cardputer `1`/`2`/`3` were already §5's direct modality pins**, so paging there
  is **context-sensitive — the same rule `ENTER` already follows in that file**: with the
  FACE up `1`/`2` pin eye/scope, with the GLOBES up they page the record. **`3` stays the
  modality pin in both stacks**, so one key always returns to the face. Operator-confirmed on
  both devices.
  📎 **This is the same silent-failure shape as the rest of the week, in the RENDERER**: a
  truncation with no indicator. It is worth stating as a rule — *if a view can show less than
  all of a record, it must say so on screen.*
  **③ 1.6's third check was ILL-POSED and the answer is a design gap, not a tick.** The
  handoff asked how `@LAT90–93` render on the T-Deck's record pane. They cannot: the T-Deck's
  three globes contain no such lanes (they are `@LAT0/6/10/14/20/30/32/35/40/50/88/98`), those
  lanes are written at runtime into the **Cardputer's own live TTDB**, and both globes'
  navigable filter is **`isNodeRecord(): lat > -90 && lat < 90`** — written to exclude the
  percept/belief/sync lanes at 94–99, which also excludes 90–93.
  ⚠ **So the `@LAT91` beliefs — the first records on this fleet to carry a TBEW `[ew]` block,
  and arguably the most interesting thing a node now knows about itself — are visible NOWHERE
  on the fleet's glass.** They can only be seen by pulling to the laptop. For a project whose
  end goal is the **rendered** proof leg (SP6), that is a gap rather than an oversight.
  **DECIDED (operator, 2026-08-02): `@LAT91` gets its own view** rather than being promoted
  into the navigable globe range — the globe is a map of places, a belief is not a place.
- ✅ **2026-08-02 — THE BELIEF VIEW IS ON THE GLASS (`FACE_BELIEF`, Cardputer key `4`).**
  A fourth representor view, joining eye / scope / interoception — and it belongs in that
  stack for the same reason interoception does: both are the node reporting on itself.
  **Interoception is the body; this is what the body has learned.** One row per
  (peer, proto): peer · proto · a `conf` bar over 0–255 · the number · `met/violated` · `!`
  for the contradiction flag. Colour carries meaning rather than decoration — **red is not
  "low", it is "the world contradicted this twice running"**. Operator-confirmed on device;
  41% flash / 38% RAM.
  📎 It re-reads the lane **only when `gBeliefRev` changes or the view is entered**, never
  per frame: 8 records × (`recordSpan` + `readBytes`) per frame is exactly the per-frame
  file I/O that cost 767 ms/repaint in the `edgesAt` defect ([[globe-edgesat-per-frame-trap]]).
  📎 **An empty lane SAYS WHY** ("the Dream Cycle writes @LAT91 from @LAT92 testimony; needs
  a still window + a peer, then ≤3 min") instead of drawing a blank panel. On a freshly
  imaged filesystem empty is the CORRECT state, and a blank panel is indistinguishable from
  a broken view — the failure mode this week kept producing.
  ⚠ **The T-Deck cannot have this view, and the reason is structural, not a missing
  keybinding.** `@LAT91` is written by `PerceptLearn`, and Rule 1 only arms an expectation
  off a **`still` `@LAT95` motion window** — the node positively claiming it was anchored.
  **Only the Cardputer has an IMU**, so the T-Deck can never author a belief of its own.
  **NEXT INCREMENT (agreed, not built): `CMD_GET_BELIEF`**, mirroring `CMD_GET_INTERO` —
  the T-Deck already renders another node's interoception from a polled 21-byte payload
  under the rule *transmit the numbers, never the pixels*, and beliefs want exactly that
  treatment. **Deliberately deferred until after Part 2**: the time stream is going to change
  `@LAT91`'s shape anyway (`touched:0` makes `sal` undecayable), so fixing a wire format for
  it now would mean designing it twice.

- ✅ **2026-08-03 — PART 2, THE TEAM TIME STREAM: BUILT, NATIVE-TESTED, WHOLE FLEET
  COMPILES. NOT YET ON HARDWARE.**
  [timestream-handoff.md](timestream-handoff.md) Part 2. New library
  `firmware/libraries/TimeStream/` (+ `TimeStreamNode.h`, the Arduino glue), the
  `synced:` → `stream:`/`wall:` migration across all 7 record formats, `companion.py`
  reading both, and all six sketches wired and building.
  **① THE DESIGN COLLAPSED TO ONE IDEA, AND IT MADE TWO OF THE HANDOFF'S THREE HAZARDS
  DISAPPEAR RATHER THAN BE HANDLED.** A stream's clock reads **elapsed-since-its-own-
  origin** — it starts at 0 when a node finds no stream to join. From that one choice:
  - the merge rule the handoff asked for (**OLDER STREAM WINS**, because it preserves
    more history) becomes simply *the larger clock wins*;
  - **MONOTONICITY is free.** The handoff lists it separately (§2.2.3: "adopting a
    stream can move the clock BACKWARD, putting already-written records out of
    order"). It cannot happen: yielding to an older stream always moves the clock
    FORWARD, because that is what "older" means. **The merge rule IS the monotonicity
    guarantee** — not two mechanisms that have to agree;
  - a foreign stream and a drifting peer on our own reduce to the SAME comparison
    (*is the sender ahead of me?*), so `onAnchor` is one rule, not a table.
  📎 Stated because it is a real property: the stream clock is a **ratchet**. It runs at
  the rate of the fastest crystal ever heard on it and never goes backward on any node.
  Right for ordering and recency; for a DURATION use the node's own `millis()` delta,
  which is what `MotionPercept`'s `dt_ms` already does.
  **② IT RIDES ON HELLO, NOT ON PULSE — AND THAT IS THE LOAD-BEARING CHOICE.** PULSE is
  the obvious carrier and is wrong: **only the conductor emits one, and the conductor is
  elected by lowest id**, so the node holding the oldest stream usually is not allowed
  to speak. A stream only the conductor can announce cannot win the merge it exists to
  win. HELLO is every node, every 2 s, and its payload was **empty**, so this is purely
  additive — an un-reflashed node sends 0 bytes and is a non-participant, not a parse
  error. ⚠ **The pulse clock is deliberately NOT reused as the stream** for the same
  reason plus one more: the band is measured tight (±9 ms, three runs) and is the one
  fully-working subsystem here; hanging record timestamps off it would put every future
  timeline change in the blast radius of the beat.
  **③ THE RECENCY ANCHOR IS WRITTEN TWICE, AND THE REASON IS A SPEC FINDING FOR TTE.**
  **TTDB-RFC-0005 §4 defines `touched` as Unix epoch seconds**, and its decay note
  ("entries untouched for long periods SHOULD have `conf` decremented") assumes an agent
  that can read a wall clock. A fleet with no laptop cannot — so `touched:0`, so `sal`
  never fades, so EPS `= sal×(255−conf)/255` has no time term. **RFC-0005's recency
  machinery is unusable on exactly the class of device the RFC was written for.** So
  `@LAT91` now emits `touched:` spec-conformant (Unix seconds, 0 = unknown) AND a
  **`**TOUCHED** t_ms:<stream ms> stream:0x<id> wall:<0|1> unix_s:<s>`** body line —
  the same instant in two frames, and the second is the one that always exists. That is
  the third item for `percept-learning-return.md` §Part 4, alongside "Rule 3 says how
  `sal` RISES and never says what makes it fall".
  **④ ONE DEFECT THE MIGRATION EXPOSED, IN A NUMBER NOBODY WOULD HAVE QUESTIONED.**
  `@LAT93`'s `dt_ms` is `after.t_ms − before.t_ms`. A stream merge between those two
  windows moves the clock forward by the offset it adopted, **and that offset lands in
  the subtraction and reads as elapsed time that never happened.** It is not detectable
  from the numbers (a minute-long gap looks like a minute-long gap), so the record now
  carries **`dt_across_merge:<0|1>`**. It is recoverable, not lost: a merge only ever
  moves the clock forward, so `dt_ms` over-reads by exactly the offset the `@LAT90`
  **REMAP** line wrote down. Native-tested both ways.
  **⑤ WHAT IS ON FLASH NOW.** `t_ms:<ms> stream:0x<id> wall:<0|1>` replaces
  `t_ms:<ms> synced:<0|1>` in **LINKWIN · ENTWIN · MOTIONWIN · TRANSITION · ACOUSTICWIN
  · TRANSIENT · OUTCOME**. Rendered by **one** function (`timestream::buildStamp`) —
  seven format strings that must agree is seven chances to drift. `stream:0x00000000` is
  meaningful and is not an error: *this timestamp is local `millis()`, comparable with
  nothing but my own records* — what `synced:0` always meant. The difference is that
  `stream:` also **names** the clock when there is one, which `synced:1` never could,
  and after a merge that is otherwise unanswerable.
  ⚠ **BOTH FORMATS ARE LIVE IN THE CORPUS AND BOTH MUST PARSE.** A node's TTDB is
  appended to for its whole life, so pre-2026-08-03 records sit on the same flash as
  post. `companion.py parse_time_fields()` handles both and **does not fabricate an id
  for an old `synced:1`** — it reads back as "some clock, unnameable", which is exactly
  the limitation that motivated the change. `test_perceptlearn` deliberately keeps its
  fixture in the OLD format so the reader is pinned against it.
  **⑥ NEW `@LAT90` LANE — timeline CHANGES, not time.** `STREAM-ORIGIN` /
  `STREAM-ADOPTED` / `STREAM-RECONCILED` / `STREAM-ANCHORED`, plus a **REMAP** line
  carrying `prev_stream` + `prev_t_ms` + `offset_ms` so records written under an
  abandoned stream stay interpretable instead of orphaned. A routine drift correction
  (`EV_SLEW`) writes **nothing** — it would flood the lane. Cap `TIMESTREAM_MAX_LANE 16`
  is a **pathology guard, not a ceiling**: if it fills, two nodes are flapping between
  streams and that IS the finding. Do not raise it.
  📎 A wall-anchor disagreement is **reported, not resolved**: `wall_conflict_ms` on the
  record and a `⚠` on serial. Two laptops, or a stale anchor carried across a merge, is
  a real condition, and the fleet's signature failure is the one nobody printed.
  📎 The date **survives a merge**: a node that knows the date and then joins a
  longer-running blind stream still knows it, to the millisecond, and then propagates it
  back. Native-tested.
  **⑦ NUMBERS.** Native suite **10 tests, 0 failures**, `test_timestream` adding
  **86 checks** (merge, monotonicity across four paths, tie convergence, slew-is-not-a-
  ratchet, wall carry, the 49.7-day `millis()` wrap). Python suite 7/7 with new
  both-format coverage in `test_prox_py`. Flash: Cardputer **41%**, T-Deck **40%**,
  K10 **20%**, all three V4s **94%**. ⚠ Measured against a HEAD worktree, the V4 cost is
  **+3728 B (+0.28% of the partition), +416 B RAM — 74.5 KB of headroom left**. Small,
  but they were already the constrained boards.
  **⑧ ON HARDWARE (Cardputer 0x300, COM14, app-only flash so the existing 121 KB TTDB
  was PRESERVED — the mixed corpus is the point).** Captures in
  `master/timestream-2026-08-03/`.
  - **`@LAT90` STREAM-ORIGIN written on a node with no laptop**: `stream:0x0ad62c42
    wall:0 t_ms:0`, `created:0`. It has a timeline and correctly declines to name the
    date. That is the state the old `synced:0` could not express.
  - **`companion.py sync` → `@LAT90LON3` STREAM-ANCHORED** `stream:0x10578c80 wall:1
    t_ms:4028054 from:0x1` + `**WALL** unix_ms:1785774270662 wall_conflict_ms:0`, and
    its header carries **`created:1785774270`** while the three ORIGIN records above it
    in the same lane still read `created:0`. **The two facts, side by side, in one lane.**
  - 🔎 **THE BEST EVIDENCE CAME FROM CHECKING A NUMBER THAT LOOKED WRONG.**
    `t_ms:4028054` (67 min) looked impossible for a node that had just been flashed, so
    it was checked rather than accepted: the six `@LAT96` windows on that stream read
    `47888 · 633274 · 1233273 · 1833273 · 2433274 · 3033273 · 3633271`, whose deltas are
    `585386 · 599999 · 600000 · 600001 · 599999 · 599998` — **matching each record's own
    `window_ms` to the millisecond.** The clock ticks at real time; three full 123 KB
    pulls simply take longer than expected. The suspicion was wrong and the check is
    now the proof that the stream clock is real.
  - ⚠⚠ **AND IN THAT SAME SERIES IS THE WHOLE ARGUMENT FOR `stream:`, BY ACCIDENT.**
    Two `@LAT96` records read `t_ms:47583 stream:0x0ad62c42` and `t_ms:47888
    stream:0x10578c80` — **305 ms apart on their clocks, an hour apart in the world**,
    because a reboot between them started a new timeline. Under the old format BOTH
    would say `synced:0 t_ms:~47700` and be indistinguishable. This is exactly the
    retroactive ambiguity §2.2.1 predicted, caught on real flash on the first run.
  - **The reboot rule works**: three boots, three DIFFERENT stream ids
    (`0ad62c42`/`fc36a38c`/`10578c80`). A reboot really is a new timeline, not a reused
    id with its clock reset to 0. 📎 Consequence to watch: a node rebooting ALONE writes
    one ORIGIN each time, so 16 solo reboots fill the lane. In a live fleet it is
    self-limiting — a rebooting node ADOPTS the peer's older stream instead.
  - **The mixed corpus parses**: `parse_link_percepts` + `parse_entity_percepts` over
    the real 123 KB file give **48 + 36 windows, 0 unparsed time fields**, 83 old records
    reading `-` (stream 0) and the new one reading `0ad62c42`.
  **⑨ TWO-NODE RUN (T-Deck 0x200 on COM10 flashed too, app-only). THE MERGE FIRED ON
  HARDWARE WITHOUT BEING STAGED.** Captures: `master/timestream-2026-08-03/`
  (`tdeck_final.md`, `cardputer_final.md`).
  - The T-Deck booted, heard nothing in its 6 s listen window, **originated its own
    stream** `0x15ecaee3` — and **1.35 s later heard the Cardputer's 26-minute-old one
    and yielded**:
    ```
    @LAT90LON1  **STREAM-RECONCILED** stream:0x26a1b82d wall:0 t_ms:1570668 from:0x300
                **REMAP** prev_stream:0x15ecaee3 prev_t_ms:7353 offset_ms:1563315
                          rule:older_stream_wins
    ```
    **Older stream won, the clock moved FORWARD by 1563 s, and the mapping back to the
    abandoned timeline is on flash.** That is the whole of §2.2.2 + §2.2.3, and it did
    not need the staged walk-out-of-range — the T-Deck's radio simply is not up inside
    its own listen window.
  - **THE PROPERTY THE FEATURE EXISTS FOR, DEMONSTRATED BY ACCIDENT.** The Cardputer's
    own lane ends `**STREAM-ORIGIN** stream:0x26a1b82d` … `**STREAM-ADOPTED**
    stream:0x26a1b82d from:0x200`. It **originated that stream, was reset, and got its
    own timeline handed back by the T-Deck.** Killing the node that was counting did not
    lose the fleet's place — TTN-RFC-0010's property, now for the log as well as the beat.
  - **Both nodes stamp ONE shared id**: the Cardputer's newest `@LAT96` reads
    `t_ms:1888655 stream:0x26a1b82d wall:0`, on the same stream the T-Deck reconciled
    onto. Cross-node comparability, which `synced:1` could never express.
  - 📎 The T-Deck wrote **no** new percept records: its `@LAT96` and `@LAT97` are both at
    the 48 cap. Its only new records are `@LAT90`. Not a defect — but it means the
    Cardputer is the only node that has demonstrated the new percept stamp.
  ⚠⚠ **THE FINDING THIS RUN PRODUCED: `@LAT90` GROWS ONE RECORD PER REBOOT, AND
  `companion.py` REBOOTS THE CABLED NODE ON EVERY INVOCATION.** The T-Deck went **0 → 7
  records in one session** against a cap of 16; the Cardputer reached 6. Confirmed by
  measurement, not inferred: a pull adds exactly one record (5→6 across one pull, 138 s
  apart), and **three minutes left completely untouched added exactly one** — so the node
  is NOT crash-looping, every record is a real reset, and ordinary orchestration alone
  will fill the lane in ~16 commands. Compounds the documented
  [[looping-companion-py-resets-bridge]] trap.
  🔎 **And most of those records should not exist.** A node that reboots and rejoins
  **the stream it was already on** has had no timeline change — the Cardputer's
  `STREAM-ADOPTED … from:0x200` is it re-adopting a stream *it had itself originated*.
  The lane is specified as "timeline CHANGES, not time", and a plain rejoin is not one.

- ✅ **2026-08-03 (later) — THE @LAT90 CHURN IS FIXED, AND FIXING IT TURNED UP THE
  ACTUAL ROOT CAUSE, WHICH WAS NOT THE THING BEING FIXED.**
  **① The dedup (the intended fix).** `writeRecord()` now asks the STORE, not a counter
  and not NVS: one pass over the `@LAT90` lane answers both "how full is it" and "has it
  already explained this stream". Suppresses exactly two things — an `ADOPTED` onto an
  already-explained stream, and an `ANCHORED` on an already-anchored stream **with zero
  conflict**. `ORIGIN` can never match (its id is new by construction) and `RECONCILED`
  is never suppressed, because its REMAP offset is specific to that merge.
  ⚠ **The needle is `" stream:0x%08lx"` WITH THE LEADING SPACE.** A RECONCILED record
  carries both `stream:0x<new>` and `prev_stream:0x<old>`; a bare `strstr("stream:0x")`
  matches the second, so an id the node had **left** would read as one it still holds and
  the record explaining a genuine return to it would be suppressed. Native-tested against
  the exact record text off flash, because a hand-written fixture is precisely where a
  substring collision gets smoothed away unnoticed.
  📎 Suppression **prints**. A record that is not written must still say so on serial, or
  the lane starts lying about what the node did.
  **② 🔎 THE ROOT CAUSE, FOUND ONLY BECAUSE THE FIX DIDN'T FULLY WORK.** After the dedup,
  a reboot still cost TWO records — serial showed `[stream] origin` immediately followed
  by `[stream] reconciled … offset=3956818ms`. The node was **forking a stream and then
  merging back**, every boot. Cause: the listen window was `now_ms >= TIMESTREAM_LISTEN_MS`
  — **absolute `millis()`, not measured from `begin()`**. On the Cardputer `setup()` takes
  **over six seconds** (BLE + WiFi + codec + display), so millis() was already past the
  window on the first loop pass: **the node originated a stream having never once listened
  with its radio up.** `pulse::Engine` has always done this correctly
  (`now_ms - boot_ms_`); this did not, and that single difference turned every quiet
  rejoin into a fork-and-merge. Now `(uint32_t)(now_ms - begin_ms_)`.
  📎 Neither the dedup nor any native test could have found this — the records it produced
  were individually *correct* (a fork really is a new timeline; the merge really is news).
  Only the serial trace showed the two firing 1.3 s apart on every boot.
  **③ VERIFIED ON HARDWARE, A/B, with the T-Deck up and holding one stream.** Two
  consecutive Cardputer reboots:
  ```
  [stream] adopted stream=0x59fb8ce8 t_ms=224806 wall=0 from=0x200 offset=0ms
  [stream] adopted adds nothing: @LAT90 already explains stream 0x59fb8ce8
           - no record written (the node still rejoined; only the log line is deduped)
  ```
  **`adopted` still fires** — the node rejoins and its clock is right; only the log line
  is deduped. That distinction is the whole check: an absent record could equally have
  meant the node stopped adopting, which would be a far worse bug than the one being
  fixed. And it now `adopted` where before the fix it `origin`ed then `reconciled` —
  ②'s fix, visible in the same trace.
  **Lane held at 10 across three further reboots** (two A/B + a pull's reset), against
  1–2 per reboot before. The lane's own tail is the before/after:
  `ADOPTED 0x26a1b82d` (redundant, pre-fix) · `ORIGIN 0x44574814` + `RECONCILED
  0x26a1b82d` (one reboot, the fork-and-merge bug) · `ORIGIN 0x59fb8ce8` (legitimate —
  the T-Deck genuinely was not audible) · then three reboots that wrote **nothing**.
  📎 Cost: +524 B flash on the V4s (still 94%), Cardputer 41%. Native suite 10 tests /
  0 failures, `test_timestream` now **102 checks**.
  **④ T-DECK REFLASHED WITH BOTH FIXES — and it demonstrated them on its first boot:**
  `[stream] adopted stream=0x59fb8ce8 from=0x300` immediately followed by
  `adopted adds nothing: @LAT90 already explains stream 0x59fb8ce8`. It **adopted**
  rather than forking-and-merging (the window fix) and wrote nothing (the dedup), in one
  trace. **Lane held at 9 across two further reboots.**
  📎 Its lane is now a complete artifact of the day, and worth keeping unpruned as
  evidence: `ORIGIN 0x15ecaee3` (the fork the window bug caused) · `RECONCILED
  0x26a1b82d` (the headline merge, with its REMAP) · **`ADOPTED 0x26a1b82d` ×6 — the
  churn, every one a reboot, every one redundant** · `ADOPTED 0x59fb8ce8` (a genuinely
  new stream, correctly written) · then reboots that write nothing.
  ⚠ **CORRECTION TO A DOCUMENTED BUILD RULE: the T-Deck did NOT need the manual BOOT/RST
  dance.** `esptool --chip esp32s3 --port COMx chip-id` entered the bootloader by itself,
  and `arduino-cli compile --upload` then flashed hands-free. CLAUDE.md has called
  native-USB auto-reset "flaky" on this board since bring-up. One clean success does not
  disprove intermittence — **try the automatic path first, keep the trackball-click + RST
  dance as the fallback** rather than reaching for it by default.
  ⚠ **`TIMESTREAM_MAX_LANE 16`'s refusal policy is still unexamined** and deliberately
  so: a full lane means the next stream's records are stamped with an id nothing
  explains, which is this project's signature failure. The right policy depends on the
  post-fix accumulation rate, which is only now measurable.
  📎 **Trap that cost several attempts and belongs with
  [[usb-uart-chip-reset-not-a-crash]]: asserting DTR *and* RTS together is esptool's
  bootloader-entry sequence, not a reset.** Doing it to read serial put the Cardputer
  into `rst:0x15 … boot:0x3 (DOWNLOAD)` — "waiting for download", silent, and looking
  exactly like a dead node. Recover with `esptool --after hard-reset chip-id`. The
  correct passive read is `companion.py open_serial_no_reset`; to reset deliberately,
  pulse **RTS only**. Several "0 bytes on serial" readings earlier in the session were
  this, not silent firmware.
  📎 Not pinned down: one cluster of three ADOPTED records 22 s / 4 s / 6 s apart, during
  a window in which the port was opened and closed repeatedly. Consistent with pyserial
  toggling DTR on close as well as open (**[[usb-uart-chip-reset-not-a-crash]]** — on S3
  native USB, asserted DTR resets and deasserted reads back NOTHING, which is also why
  raw serial capture returned 0 bytes on both settings and the TTDB had to be the
  instrument). Per-record attribution to individual resets was not established; the
  no-looping result above does not depend on it.
  📎 The first boot pass took **21128 ms** (`widest section linkperc 19013ms`) on the
  now-123 KB TTDB. ⚠ **CORRECTION — this was first written up here as "1.1's O(file) law
  confirmed at 123 KB → ~19 s", and that was WRONG.** The Dream Cycle later printed its
  own timing on a 130 KB file: **`fold 128ms rewrite 1815ms append 517ms TOTAL 2460ms`**
  — 1815 ms of rewrite at 130 KB is ~14 µs/byte, squarely on the recorded 10–13 µs/byte
  law, and the whole cycle is 2.5 s, not 19 s. So **the 19 s belongs to something else on
  the first pass** — `gDb.begin()`'s index scan over 238 records and/or the LittleFS
  mount are the candidates — and it has never been attributed. The section profiler
  charges it to `linkperc` because that is the section the boot Dream Cycle sits in,
  which is exactly the "a section that quietly carries somebody else's cost" trap noted
  on 2026-08-02. **Do not repeat the 19 s figure as a Dream Cycle number.** 1.1's second
  bullet is still open; this neither strengthens nor weakens it.
  📎 Unrelated observation while identifying ports: the Cardputer reported **`mind: 7 KB`
  largest contiguous block** at 25 min uptime (memory records ~45 KB once WiFi/BLE are
  up). Not investigated. If it is real it is a much bigger problem than anything here.

- ✅ **2026-08-03 (later still) — THE SPINE JOINED THE STREAM, AND THE FLEET CARRIED IT
  WITHOUT THE LAPTOP.** V4-A (`0x10`, COM6) and V4-B (`0x11`, COM9) flashed app-only
  (LittleFS untouched), 94% flash / 74 KB headroom each, hash verified.
  **① BOTH ADOPTED THE SAME STREAM `0x59fb8ce8`, AND BOTH GOT IT `from:0x200` — THE
  T-DECK, WHICH WAS NOT CABLED.** It was sitting on battery on the mesh; the laptop
  did not relay anything. That is Part 2's whole claim demonstrated rather than argued:
  a timeline that survives the laptop's absence, propagated node→node. The Cardputer
  originated it, the T-Deck carried it, the two V4s took it up.
  **② ONE `@LAT90` RECORD EACH — no fork-and-merge on either board**, despite two boards
  whose `setup()` timings differ from the Cardputer's. The listen-window fix generalises;
  it was not tuned to one board. Each pull also resets the node, and still one record.
  **③ THE CLOCKS AGREE TO THE MILLISECOND.** V4-A joined at `t_ms:1672837`, V4-B at
  `t_ms:1740837` — **exactly 68000 ms apart, which is the gap between the two flashes.**
  Two independent crystals, two independent boots, one shared timeline.
  **④ MIXED CORPUS CONFIRMED ON A THIRD AND FOURTH BOARD.** V4-A: 68 old `synced:`
  records, then new-format ones; V4-B: 81. On V4-A the record immediately below the join
  is `**ENTWIN** t_ms:1731254 stream:0x59fb8ce8 wall:0` — the two formats are literally
  adjacent on one flash and both parse. Captures: `master/timestream-2026-08-03/
  v4a_after.md`, `v4b_after.md`.
  ⚠⚠ **THE FINDING THIS RUN PRODUCED: `companion.py` COULD NOT READ THE ONE LANE THE TIME
  STREAM EXISTS TO WRITE, AND SAID NOTHING ABOUT IT.** Running both corpora through
  `parse_time_fields` returned `None` for every `@LAT90` verb line. Cause: the seven
  percept formats render the triplet through `timestream::buildStamp` (`t_ms: stream:
  wall:`), but `buildStreamRecord` **hand-writes it in a different order** —
  `stream: wall: t_ms:` — because on that line the stream is the SUBJECT of the sentence
  ("this node moved to timeline X"), not the time an observation was taken. The regex was
  anchored on `t_ms:` first. **The ordering difference is defensible; the order-anchored
  reader was not.** Fixed on the reader side, not the writer: four boards already carry
  records in that order, and matching the fields independently costs nothing. Now:
  `T_MS_RE` / `SYNCED_RE` / `STREAM_RE` / `WALL_RE` matched separately, with
  `prev_stream:0x…` **stripped first** — `\b` does not save you, it matches *inside*
  `prev_stream:`, the same trap the firmware's dedup needle solves with a leading space.
  A `REMAP` line therefore yields no timeline at all rather than the stream the node
  **left**, which would have silently re-filed a merge under the loser. Three new checks
  in `test_prox_py.py` use the exact lines off V4-A's flash. All 7 Python suites pass.
  📎 **This narrows the CLAUDE.md rule "rendered by ONE function, do not hand-write the
  triplet in an eighth place."** That rule is right for the seven *observation* formats.
  `@LAT90` is not an observation — it is a statement about the timeline itself — and it
  gets a different word order for a reason. The obligation it inherits is not "use
  buildStamp" but **"every reader must be order-independent."**
  📎 Serial was silent on both V4s at every DTR/RTS setting tried, including the plain
  `serial.Serial(port, baud)` open that `companion.py`'s own readers use — yet `ping`
  ACKed on the first attempt over the same port, so `Serial` *is* the CDC and the link
  *is* good. Unexplained; the TTDB was used as the instrument instead, as on the
  Cardputer. `scratchpad/banner.py` records the three attempts so the next session does
  not repeat them.
  ⏳ Still unflashed: **V4-C and the K10** (neither plugged in). They send 0-byte HELLOs
  and are non-participants — wire-compatible, just not on the timeline.

- ✅ **2026-08-03 (V4-C) — THE STREAM SPREAD MULTI-HOP, AND FROM A DIFFERENT PARENT.**
  V4-C (`0x12`, COM13) flashed app-only, 94% / 71719 B headroom, hash verified. It
  adopted the same stream `0x59fb8ce8` — but **`from:0x11`, V4-B, which was UNPLUGGED
  from USB and running on its battery.** So the timeline has now propagated
  Cardputer → T-Deck → V4-A/V4-B → V4-C, over several hops, choosing whichever neighbour
  it heard first rather than any fixed parent, with the laptop in none of the paths.
  **Five nodes on one stream: `0x300` · `0x200` · `0x10` · `0x11` · `0x12`.** One
  `@LAT90` record, no fork-and-merge, on a third differently-timed board. Across all
  three V4 corpora: **227 old-format records and 5 new-format, 0 unparsed.**
  📎 **HOW TO IDENTIFY WHICH BOARD IS ON A PORT — read the app image, don't infer from
  the mesh.** COM9 vanished and COM13 appeared, and `intero --node v4c_edge --port COM13`
  answered `up 4m12s` — but that reply can arrive **over the air** from a battery-powered
  node, so it identifies nothing. (It also can't be cross-checked by uptime: contrary to
  the note in §6, **opening a V4's port does not appear to reset it** — these boards were
  silent on serial at every DTR/RTS setting *and* never reprinted a banner.) What is
  definitive:
  ```
  python -m esptool --chip esp32s3 --port COMx --baud 921600 \
         read-flash 0x10000 0x140000 app.bin        # ~17 s
  # then grep the image for the sketch's own banner: "V4-A bridge" / "V4-B relay" /
  # "V4-C edge", and for "older_stream_wins" to see if it predates the time stream.
  ```
  ⚠ **The obvious shortcut does NOT work:** `esp_app_desc_t.project_name` at
  `0x10000+0x50` reads **`arduino-lib-builder`** on every arduino-cli build — it is the
  core's name, not the sketch's, and its `date/time` is the core's build date. Only the
  sketch's own string literals distinguish the boards.

- 📋 **2026-08-03 — NEXT SESSION'S WORK ORDER: [semantic-logging-handoff.md](semantic-logging-handoff.md)**
  (authored against `6abc919`, clean tree). It supersedes `timestream-handoff.md`'s Part 3,
  reordering it after reading the code: **A** recency becomes a time window
  (`--last N` → `--since`), **B** `@LAT95` change-triggered, **C** `@LAT96` change-triggered,
  **D** the two Part-2 closeouts, **E** the TTE return report. Two findings surfaced while
  writing it, neither previously known:
  ⚠ **FINDING A.1 — `proximity --last N` is SILENTLY NOT APPLIED to the entity tier.**
  `consolidate_entity_jaccard()` accepts a `last` parameter (companion.py:1962) and its
  **only call site does not pass one** (companion.py:2391). So `--last 6` narrows the RSSI
  evidence to six windows while the entity cap that bounds it **from above** is computed
  over the node's whole history. A node carried across the house keeps every AP it ever saw
  in its Jaccard set, so the pair still looks co-located and the bound stays tight — i.e.
  the flag fails on precisely the case the operator passes it for (a node that moved). Never
  reported because a too-tight bound yields a plausible number, not an error. Pre-existing,
  unrelated to the time stream.
  ⚠ **FINDING B.3 — `MOTIONPERCEPT_MOVING_MG 60` is CHOSEN, not derived**, unlike
  `PERCEPTLEARN_RSSI_BAND 6` which is the measured p90 of 33 quiet windows with its
  derivation table in the header. The 60 mg comes from published hand-tremor / walking-stride
  figures, **never checked against this BMI270 on this board**. Every `still` claim the
  learning loop rests on rests on that line. Measure it the way `PerceptLearn.h` did before
  change-triggering the lane; a confirmed constant is worth more than an assumed one.
  📎 **The coupling that makes Part B bigger than it looks:** `PerceptLearn::arm(int
  motion_lane)` stores `acting_lane_` — "the @LAT95 record whose `still` claim armed this"
  (PerceptLearn.h:159/196) — and the sketch arms from the record it just wrote
  (cardputer_console.ino:3513). So an expectation is **provenanced to a specific @LAT95
  record**. Change-trigger the lane naively and a `still` window that matches its
  predecessor writes nothing, leaving nothing to cite; arming anyway would produce testimony
  with **false provenance** that `@LAT92`'s tally then inherits. The resolution is the same
  as the one `@LAT92` needs — explicit run-length (`windows_since_last:N`) — so decide both
  together.
  📊 State at handoff: native **419 checks / 0 failures** (`bash scratchpad/t.sh`, rc=0;
  counting convention varies between suites so that is `grep -ciE "^\s*(pass|ok)[: ]"`),
  Python 7/7. `TIMESTREAM_MAX_LANE 16` is **not close to binding** — post-fix a reboot onto
  the stream the node is already on writes nothing (T-Deck 9 records, all pre-fix churn; the
  three V4s 1 each after resets and full pulls) — so do not raise it; only the
  what-happens-when-full policy is still open.

- ✅ **2026-08-03 (Part A) — RECENCY IS NOW A TIME WINDOW, AND IT IS THE FLEET'S CLOCK
  THAT JUDGES IT.** `proximity --since <90s|10m|2h|1d>` lands alongside `--last N`
  (`parse_duration_ms`; a bare number is seconds). The design decision worth knowing:
  **the reference is the newest window on that node's STREAM, fleet-wide, not the node's
  own newest.** Per-node was the obvious reading and it is wrong — a node switched off
  three hours ago has a perfectly fresh newest window *of its own* and would grade its own
  homework straight into a current belief. `stream_references()` takes the max t_ms per
  named stream across every node **and both tiers**, so a node whose @LAT96 lane went
  quiet is still demonstrably alive if its @LAT97 lane was not. Streams `0` and `None` are
  deliberately absent from that map — self-comparable only — so those nodes fall back to
  their own newest and the report marks it `*`, because "recent by its own clock" is a
  strictly weaker claim. Everything dropped lands in a counter and is printed per node
  (`too_old` / `off_stream` / `pre_restart` / `untimed` / `by --last`); a node reduced to
  zero says so in words. Three more rules, each written into `filter_windows_since`'s
  docstring: the node's own reference is its newest in **file order**, not `max(t_ms)` (a
  stream clock is a ratchet and jumps forward on adoption, which `max()` would let win);
  timelines compare by identity, so old `synced:1` records (stream `None`) form their own
  comparable class rather than being fabricated onto a stream; and a `t_ms` that steps
  **backwards** in file order is a millis() restart, so everything before it is
  incomparable however recent its number looks. ✅ **FINDING A.1 is fixed and pinned** —
  `consolidate_entity_jaccard` now takes `since_ms`/`refs` and the call site passes them,
  with a test that fails if the entity cap is ever computed over a wider window than the
  RSSI evidence again. `--last` still works, and now **warns** when the corpus contains
  `windows_since_last:` (the run-length marker Part B will add) — the exact condition
  under which counting records stops proxying time. Python suite **7/7, test_prox_py 74 →
  94 checks**; no firmware touched.
  ⚠ **AND THE FIRST REAL-CORPUS RUN FOUND SOMETHING: THE `@LAT97` LANE IS FULL ON ALL
  FIVE NODES, AND NOT ONE POST-FLASH LINK WINDOW EXISTS ANYWHERE IN THE FLEET.**
  `LINKWIN` counts in `master/timestream-2026-08-03/`: V4-A **48**, V4-B **48**, V4-C
  **48**, T-Deck **48**, Cardputer **48** — i.e. exactly `LINKPERCEPT_MAX_LANE 48` on
  every board — and `grep LINKWIN | grep -c stream:` is **0** on every one. The lane was
  already at its cap when the time-stream firmware went on, and `LinkPercept.h:31` says
  what happens then: *"Stop appending once the @LAT97 lane holds this many records…
  only the append is skipped."* The app reflash does not clear the TTDB (that is a
  separate FS upload), so **the primary hypothesis' own evidence lane has been silently
  discarding on the whole fleet**, and will never carry a `stream:` stamp until it is
  pruned. This is the same failure as the @LAT95 cap that disarmed the learning loop on
  2026-08-02, one lane over and fleet-wide. The remedy already exists and has never been
  needed before: `proximity --clear` (the Dream-Cycle prune, needs `--port`). ⏳ **Not
  run — it needs the boards powered, and dropping a lane is the operator's call.** Do it
  before collecting anything for Part C, or the collection window will be empty.
  📎 It also validates the report design: the `*` markers made this visible on the first
  run — every node's @LAT97 reference printed as its own local clock on stream `-`, while
  its @LAT96 reference printed a real stream id.

- ✅ **2026-08-03 (the prune) — THE `@LAT97` LANE IS OPEN AGAIN ON FOUR OF FIVE NODES, AND
  THE FIRST LINK WINDOW IN THE PROJECT'S HISTORY WITH A TEAM-TIMELINE STAMP IS ON FLASH.**
  ```
  **LINKWIN** t_ms:6611291 stream:0x59fb8ce8 wall:0 window_ms:60000   ← Cardputer, post-prune
  ```
  Before this, `grep LINKWIN | grep -c stream:` was **0 on every node in the fleet**.
  Live pre-prune counts (fresh pulls, not last session's snapshots): V4-A `@LAT97` **48/48**
  with 0 stamped, `@LAT96` 30 (10 stamped); Cardputer `@LAT97` **48/48** with 0 stamped,
  `@LAT96` **48/48**, `@LAT94` **48/48**, `@LAT95` **48/48**. The entity lane proved the
  point by contrast: same node, same hours, same firmware — @LAT96 kept writing and got its
  stream stamp, @LAT97 was full and got nothing.
  **What was cleared: lanes 97 and 96 only.** Backups first, over each board's own cable
  (`master/prune-2026-08-03/*_before.md`: V4-A 44220 B, Cardputer 133460 B).
  | node | | result |
  |---|---|---|
  | V4-A `0x10` | COM6, own cable | ✅ 44220 B → **1293 B**, verified by re-pull |
  | V4-B `0x11` | over the air via V4-A | ✅ verified by bridged pull — **3 stamped windows** already |
  | T-Deck `0x200` | over the air via V4-A | ✅ verified by bridged pull — 1 window, 9 `@LAT90` (known pre-fix churn) |
  | Cardputer `0x300` | COM14, own cable | ✅ 133460 B → **69054 B**, 1 stamped window on each lane |
  | V4-C `0x12` | over the air, then its own cable | ✅ 97 cleared over the air (ACK-only at the time), **both confirmed and 96 cleared on the cable**: 25558 B → **5799 B** |
  📎 **V4-C, second attempt (same session, ~40 min later): it was simply OFF the first
  time and is now up.** `intero` says `up 39m26s`, **4.003 V / 80% (falling)**, die 50.6 C,
  loop 35 ms — a healthy node on battery. Its `@LAT97` clear **ACKed on attempt 1**, and the
  firmware ACKs `clear-percepts` *only* on a successful `removePerceptLanes`, so the ACK is
  the confirmation — but ⚠ **it could NOT be verified by re-pull, unlike the other four**:
  two bridged pulls of V4-C returned **`no data received`**, before and after the lane was
  cleared. Size is not the explanation this time (the same pull worked on V4-B at 4118 B),
  and the node is plainly reachable: a `ping` ACKs and a **21-byte INTERO PERCEPT comes back
  intact**. So the split is **small unicast round-trips succeed, bulk TTDB_DATA streaming
  fails** — consistent with V4-C being the node that adopted the stream `from:0x11` (V4-B)
  rather than from V4-A, i.e. plausibly a hop further out, where a multi-frame stream has to
  be relayed and a single ACK does not. Another eliminated cause for the bridged-pull entry
  above, and a sharper statement of it: *reachable* and *pullable* are different properties.
  ⚠ **V4-C's `@LAT96` was left UNCLEARED at that point, on purpose** — ~30/48, not blocking
  anything, and the one lane that could not be backed up, because the pull is exactly what
  fails. Clearing an un-backed-up lane that is not full buys nothing.
  ✅ **CLOSED the same session, V4-C on its own cable (COM13, identified by the `V4-C edge`
  banner in its app image — COM6/COM14 had become COM10/COM13 between plug-ins, so nothing
  was assumed).** Three things fell out of it:
  1. **The over-the-air clear had landed.** `@LAT97` read **6 records, all 6 stamped**
     `stream:0x59fb8ce8`, down from 48 unstamped. The ACK-only confirmation was sound —
     `clear-percepts` ACKs solely on a successful `removePerceptLanes` — but it is now
     verified rather than argued.
  2. **The pull that failed twice over the air worked instantly on the cable: 25558 B,
     first attempt.** Then 96 backed up, cleared, re-pulled: **5799 B**, entity lane gone,
     `@LAT90` timeline record intact.
  3. **The T-Deck was re-verified over its own cable too** (COM10, `SemPos`+`GPS` in the
     image, no `ES8311` ⇒ not the Cardputer): **13 LINKWIN, all 13 stamped.** Its earlier
     confirmation was a *bridged* pull, which is the path that can silently stitch two file
     generations — so the weaker evidence has been replaced rather than left standing.
  🎯 **END-TO-END, AND THE POINT OF ALL OF IT:** `proximity --since 30m` over the five
  post-prune corpora now prints **`ref t_ms 7496430 on 59fb8ce8` for every node, with
  nothing excluded and not one `*`** — every reference is the FLEET's clock, none is a
  node grading its own homework. An hour earlier the same command fell back to five
  separate local clocks on stream `-`, because the lane that was supposed to carry the
  shared timeline had been full since before the firmware that created it. The recency
  filter and the team time stream only became each other's payoff once the lane was open.
  ⚠ **`@LAT94` (acoustic) and `@LAT95` (motion) are ALSO at 48/48 on the Cardputer and were
  DELIBERATELY LEFT ALONE.** `@LAT95` is the citation lane: `PerceptLearn::arm()` stores an
  index into it as `acting_lane_`, and the node currently holds **8 `@LAT91` beliefs and 24
  `@LAT92` outcomes** whose provenance points there. `removePerceptLanes` rewrites the file,
  so clearing 95 would leave 32 records citing indices into a lane that no longer holds what
  they cite — testimony with false provenance, which is worse than a full lane. Clearing it
  needs a decision about those 32 records first (retire them with the lane? re-base the
  indices?), not a CMD. That decision is open. `@LAT94` has no such coupling but was left
  for the same round-trip.
  ⚠ **NEW OPERATIONAL TRAP — a lane clear needs `--attempts 6+` on a grown TTDB, and the
  default 4 REPORTS A FALSE "NOT applied".** `removePerceptLanes` rewrites the whole file;
  on V4-B and the T-Deck that outran the default RTO ladder (0.5/1/2/4 s) and printed
  `no ACK … NOT applied` — then **succeeded on attempt 5** with `--attempts 7`. The T-Deck
  had ACKed a `ping` on attempt 1 seconds earlier, which is what showed the node was alive
  and the *operation*, not the link, was slow. Same shape as the play/beep ACK false
  negative (a blocking call eats the ACK window). The command is idempotent, so the fix is
  always more attempts.
  ⚠ **And the prune exposed the reset trap from the DATA side, not the probe side.** V4-A
  wrote **no** window for the first several minutes after its clear while V4-B and the
  Cardputer both refilled — because every `companion.py` invocation on COM6 reboots it, and
  COM6 was the bridge for all six over-the-air clears plus two pulls. `LINKPERCEPT_FLUSH_MS`
  is 60 s measured from a window that a reboot restarts, so **a node used as the bridge
  collects nothing while you are working through it.** ✅ **Confirmed by the control, not
  assumed:** left untouched for 3 minutes and then pulled ONCE, V4-A wrote **exactly 3
  LINKWIN at 60 s spacing** (`t_ms` 6772112 / 6832112 / 6892111) plus an ENTWIN, all on
  `stream:0x59fb8ce8` — 1293 B → 4143 B. Nothing was wrong with the node. Do not measure a
  bridge node's collection rate during a session that talks through it; give it one quiet
  interval and one pull instead.

- ✅ **2026-08-03 (Part B opens) — LANE GENERATIONS: A PRUNE NOW WRITES DOWN ITS OWN
  BOUNDARY (`@LAT100`).** Verified on hardware, on V4-A:
  ```
  @LAT100LON0 | created:0 | updated:0 | relates:prunes@LAT0LON0
  **LANE-PRUNED** lane:97 gen:1 removed:47 last_lon:46 t_ms:9913863 stream:0x59fb8ce8 wall:0 node:0x00000010
  ```
  **The defect it closes was created by this session's own prune.** A citation here is an
  ORDINAL — `@LAT92LON0`'s header says `derived_from@LAT97LON1`, and `PerceptLearn` keeps
  the same numbers as `acting_lane_`/`staged_lane_`/`scored_lane_`. A prune resets the
  count, the lane refills, and every pre-existing citation silently starts resolving to a
  **different record with the same index** — not a dangling pointer, which is honest and
  detectable, but a live pointer to the wrong thing. Clearing `@LAT97` re-pointed **all 32
  citing records on the Cardputer** (24 `@LAT92` + 8 `@LAT91`) in one CMD. Nothing resolves
  those edges today, so no output was wrong — but the corpus IS the deliverable.
  The fix is the move `@LAT90`'s REMAP already makes for a superseded timeline: write the
  supersession down. Same idea, one level lower.
  📎 **Three placements were checked and rejected, and the reasons are the design:**
  (1) NOT inside the lane it prunes — the *next* prune of that lane would delete its own
  history; (2) NOT `@LAT90`, however close the concept sits — that lane's dedup scans it
  and asks `recordNamesStream()`, so a prune record carrying the standard stamp would
  answer YES and **suppress a later, legitimate STREAM-ADOPTED record as "already
  explained"**, i.e. the timeline lane would go quiet about a real change because of an
  unrelated prune (same needle-collision shape as `prev_stream:`); (3) NOT `@LAT89` —
  `isNodeRecord()` is `lat > -90 && lat < 90` on both consoles, so 89 would appear as a
  navigable place on the globes, with an eyeball. 90–99 are all taken, so the machinery
  block continues upward to 100, which the globes' `lat < 90` filter ignores.
  🔒 **The invariant is NO PRUNE WITHOUT A MARKER.** Marker-lane capacity is checked
  *before* the rewrite; a boundary that cannot be recorded stops the prune. `LANEGEN_MAX_LANE
  32`'s full-policy is **decided** (refuse + say why), unlike `TIMESTREAM_MAX_LANE`'s — and
  the cost is stated in the header: a node whose marker lane fills stops being able to open
  its percept lanes and will eventually go blind. That is the deliberate trade, because the
  alternative is the silent prune this exists to remove.
  📊 **Hardware verification on V4-A** (COM6, identified by reading its app image — the
  ports had shuffled again, and a USB *instance path* names a socket, not a board):
  `removed:47` matched the 47 records counted before, `last_lon:46`, stamped on the fleet
  stream, `@LAT96` untouched by a lane-97 prune. Then a `--lane 0` (all lanes) prune wrote
  **one** marker for `@LAT96` and **none** for the already-empty `@LAT97` — an empty lane is
  not a prune, which is also what keeps the CMD safe to retry after a lost ACK.
  💻 **Laptop side:** `companion.py prunes --file <ttdb>` prints the generations and the
  citations they invalidated. ⚠ Its first cut was **wrong in a way the test caught**: it
  took the boundary with the highest `last_lon` per lane, which hides a *later* prune of a
  shorter generation behind an earlier, bigger one. The rule is per-citation — was there any
  prune of that lane, at or after this record was written, that covered this index — and it
  reports the **earliest** such prune, the one that actually destroyed the record cited.
  ⚠ It also uses the **time stream** to avoid crying wolf: a record written AFTER a prune,
  citing the new generation's `@LAT97LON1`, has a low index too. Citing t_ms > boundary t_ms
  on the same stream ⇒ live; ≤ ⇒ stale; no comparable time ⇒ **`unknown`**, reported as its
  own verdict rather than guessed either way (pre-2026-08-03 `synced:1` records are genuinely
  unplaceable). Run against the Cardputer it says the honest thing: *no `@LAT100` records —
  this node has never pruned, OR it pruned before lane generations existed and nothing
  recorded it; those two are indistinguishable after the fact, which is the whole reason the
  lane exists.*
  📊 Tests: native **lanegen 18/18** (suite all green), Python **8 files** (`test_lanegen_py`
  14 checks). Cost measured against a HEAD worktree: **V4-A +1748 B flash (+0.13%), +0 B
  RAM** — 94%, **72295 B free**. All five sketches compile (V4-B/V4-C 94%, T-Deck 40%,
  Cardputer 41%).
  ✅ **T-Deck and Cardputer flashed and verified the same session** (COM10/COM14, both
  identified by app image — `ES8311 not found` is the Cardputer-only literal; both carry
  `SemPos`). The T-Deck's **automatic bootloader entry worked again, hands-free** — second
  clean success, so keep the trackball+RST dance as fallback only.
  ```
  **LANE-PRUNED** lane:97 gen:1 removed:48 last_lon:47 t_ms:418673 stream:0xbdc62024 node:0x00000300  (Cardputer)
  **LANE-PRUNED** lane:97 gen:1 removed:48 last_lon:47 t_ms:463764 stream:0xbdc62024 node:0x00000200  (T-Deck)
  ```
  ⚠ **`removed:48` ON BOTH — THE LANES WERE ALREADY FULL AGAIN.** They were pruned to
  empty earlier the SAME afternoon; at `LINKPERCEPT_FLUSH_MS 60000` a 48-record cap refills
  in 48 minutes and then discards in silence. So the morning's fleet-wide prune bought
  under an hour of collection per node, and both consoles had been throwing away link
  windows again before this prune. **This is the argument for Part B in one line: with
  periodic logging, pruning is a treadmill, not a fix.**
  📊 **The reader, on real hardware data.** `prunes` against the Cardputer found all **32**
  citations (24 `@LAT92` + 8 `@LAT91`) — and reported every one as **`unknown`, not
  `stale`**, which is the correct and honest answer: those records carry the pre-2026-08-03
  `synced:` stamp, so they cannot be placed against a boundary in time. They ARE stale in
  fact (re-pointed twice today), and the node cannot prove it. ⚠ Note also the marker says
  `gen:1` on a lane that has now been pruned at least three times — generations count only
  what was RECORDED, and the two earlier prunes predate the firmware. Both limits are the
  same one, stated plainly rather than papered over.
  ✅ **V4-B and V4-C flashed and verified too — THE WHOLE FLEET NOW RECORDS ITS PRUNES.**
  Both identified by reading their app images (`V4-B relay` / `V4-C edge`), which is the
  only way to tell two V4s apart, and each flashed with its own sketch.
  ```
  **LANE-PRUNED** lane:97 gen:1 removed:48 last_lon:47 t_ms:832981 stream:0xbdc62024 node:0x00000011
  **LANE-PRUNED** lane:97 gen:1 removed:48 last_lon:47 t_ms:846755 stream:0xbdc62024 node:0x00000012
  ```
  🎯 **ALL FIVE MARKERS SAY `removed:48`.** V4-A (47, pruned an hour earlier than the rest),
  V4-B 48, V4-C 48, T-Deck 48, Cardputer 48 — **every node in the fleet had refilled to its
  cap and gone back to discarding within one afternoon of being emptied.** That is no longer
  an argument about periodic logging, it is a fleet-wide measurement of it: 5/5 nodes, one
  afternoon. Part B's remaining work (change-triggered `@LAT95`, then `@LAT96`) is what stops
  the treadmill; until then a prune buys 48 minutes.
  📎 And the fleet re-converged on **one stream (`0xbdc62024`) across all five nodes**,
  through three separate reflash rounds, with the laptop in none of the adoption paths.

- ⚠ **2026-08-03 — `TIMESTREAM_MAX_LANE 16` IS NO LONGER "NOT CLOSE TO BINDING": THE
  CARDPUTER IS AT 13/16.** (T-Deck 10/16; measured on the post-flash pulls.) This morning's
  reading — T-Deck 9, the three V4s 1 each — was taken on a **settled** fleet, and the
  accumulation rate of a settled fleet is not the rate that matters. A **flashing session**
  is the pathological case: a board reboots hearing NO peer inside its listen window,
  **originates a new stream** (an ORIGIN is never suppressed — correctly, it is a real
  timeline change), and then writes a second record when it later adopts whatever the fleet
  settled on. The Cardputer's lane shows it: `STREAM-ORIGIN 0x59fb8ce8` → `ORIGIN
  0x450f0e1c` → `ORIGIN 0x2434b81f` → `STREAM-ADOPTED 0xbdc62024 from:0x10`.
  📊 **The rate depends on whether anything else is powered, and that was measured too:**
  V4-B and V4-C, flashed while both consoles were live and in range, adopted straight away
  and wrote **1 record each (2/16 total)** — no ORIGIN at all. So it is ~1 record per board
  when the fleet is up around it and ~2 when the board boots alone, which is exactly why
  the consoles (flashed across rounds where they were often the only node awake) are the
  two sitting at 13 and 10. **Flash with the fleet powered** and the lane grows half as
  fast — a free mitigation available today, ahead of whatever the real fix turns out to be.
  So **D.1's conclusion ("do not raise it") stands, but its evidence does not** — the cap
  is ~3 reflashes away on the Cardputer, and what happens when it fills is still the
  undecided policy (refuse + print, leaving the next stream's records carrying an id
  nothing explains). The likely right answer is not a bigger cap but not writing an ORIGIN
  that an adoption supersedes seconds later — i.e. the same "one record per settled state,
  not one per hop" rule the lane already claims, applied across the settle window rather
  than within one drain. **Decide it before the next fleet reflash, not after.**
  📎 Fleet timeline as of this entry: **`0xbdc62024`**, originated by V4-A after its flash
  and adopted by both consoles. The morning's `0x59fb8ce8` is gone — every node holding it
  rebooted.

- ✅ **2026-08-03 (Part B.3) — `MOTIONPERCEPT_MOVING_MG 60` IS NOW A MEASURED CONSTANT,
  AND IT SURVIVED.** Cardputer `0x300`, `@LAT95` pruned to empty first so the run *is* the
  sample; 48 windows × 60 s (298–997 samples each), node stationary and **untouched for
  50 minutes** — no `companion.py` call, because every invocation resets the board and
  restarts the window. All 48 windows on one stream (`0xbdc62024`), `t_ms` 1761607 →
  4690069 = 48.8 min continuous, so it is one run and not two stitched.
  ```
  dev_max_mg    min 11   p50 12   p75 12   p90 12   p95 13   max 20
  dev_mean_mg   min  8   p50  8   p90  8   max  9
  moving_permille  0 in EVERY window (max 0);  samples >= 60 mg: 0 of 48
  ```
  **p90 = 12 mg → 60 mg is 5.0× the noise floor** and 3× the worst single excursion in
  50 minutes. The floor is a **bias, not jitter**: `dev` is `|mag − 1 g|` and this part
  rests ~8 mg off 1 g, so the usable margin above rest is ~52 mg. The verdict is
  comfortable *and* comfortable in the direction the design intends — 60 mg stays above
  hand tremor (20–40 mg), which is what keeps a held-but-still device on the still side.
  The derivation table is now in `MotionPercept.h` beside the constant, in the shape
  `PerceptLearn.h` uses for `PERCEPTLEARN_RSSI_BAND 6`.
  ⚠ **THE FIRST ATTEMPT AT THIS MEASUREMENT WAS WRONG BY 2.75×, AND HOW IT WAS WRONG IS
  THE POINT.** Reading the 48 windows the lane already held gave **p90 = 33 mg** with one
  80 mg sample, and a `dev_mean_mg` of exactly 14 in every window that I read as the
  part's resting bias. Both were artefacts: those windows were labelled `state:still` **by
  the very threshold under test** (circular), and the node had been picked up, plugged and
  unplugged during them. On the clean run the bias is **8 mg**, not 14. *A lane's own
  label is not evidence that the node was still; only an operator keeping it still is.*
  Prune, then collect — which is also why the prune had to come first rather than being
  cleanup.
  📎 **B.4 (flapping) is partly answered by the same data:** at rest this board is nowhere
  near the line — `moving_permille` was **0** in all 48 windows, not merely under the 100
  verdict gate — so hysteresis is not needed to stop rest-state flapping. It may still be
  needed at the EDGE of real motion, which this run does not measure and a walk-and-stop
  run would.
  📊 And in the same 50 minutes `@LAT94` and `@LAT97` **both refilled to 48/48 again** —
  the treadmill, third measurement today.

- ⚠ **2026-08-03 — THE `@LAT90` CAP IS NOW REACHED ON THE CARDPUTER: 16/16**, exactly as
  predicted an hour earlier, and the 16th record is another abandoned `STREAM-ORIGIN`
  (`0x9c462b30`) written when the post-run pull reset the board. The next timeline change
  is refused, so records could carry an id the lane never explains — the failure this lane
  exists to prevent.
  ✅ **The fix is written, tested and compiled, and is NOT yet flashed.** A `STREAM-ORIGIN`
  is now HELD for `TIMESTREAM_ORIGIN_SETTLE_MS` (30 s) and **dropped if the node moves to
  another stream** — an origin abandoned three seconds later was never "a settled state",
  which is what this lane says it records. ⚠ The settle window alone is not sufficient and
  the second arm is the interesting half: it sits under the 60 s percept flush so no window
  record can be stamped with an unexplained id, but a `@LAT100` prune marker answers to no
  flush period and can land seconds after boot (exactly what this session did) — so the
  hold is **also released the moment the TTDB grows at all**, checked before the time
  condition. Both live in `originDue()` (portable, native-tested, 9 checks), and the
  `< 60000` invariant is **asserted in the test suite**, so raising the constant past the
  flush period fails the build instead of quietly restoring the defect.
  Cost: **V4 +628 B flash, +80 B RAM** (94%, 71667 B free); T-Deck 40%, Cardputer 41%. All
  five sketches compile.
  ✅ **FLASHED AND MEASURED ON THE T-DECK: 11 → 11 @LAT90 records across 4 reboots**, the
  pulled file byte-identical (55486 B) before and after. Before the fix the same pattern
  cost ~2 records per 3 reboots. The one record it *did* write in that window was a real
  `STREAM-ADOPTED 0xe7384824 from:0x10` — a stream the lane had never named — which is
  exactly what should still be written. Cardputer flashed too. ⏳ V4-A/B/C still to do.
  ⚠ **BUT THE CARDPUTER IS ALREADY AT 16/16 AND THERE IS NO WAY TO PRUNE THAT LANE.**
  `CMD_CLEAR_PERCEPTS` deliberately refuses anything outside 94–97 so a prune can never
  touch identity, attestations or sync logs — which means D.1's undecided policy is now
  LIVE on one node. Right now it is still coherent: its newest records carry
  `stream:0xbdc62024`, which the lane does explain. But **the fleet has since moved to
  `0xe7384824`**, and when the Cardputer adopts it the record will be refused and its
  subsequent percepts will carry an id nothing on that node explains.
  📎 Note the observation cost here: confirming which stream it is on now requires a fresh
  percept window, and every pull resets the board and restarts the 60 s window — the same
  trap that made V4-A look dead. It needs one quiet minute, not another pull.
  **The options, none of them free:** (a) leave it — the hold removes the *pressure*, so it
  may simply sit on one stream, and the lane prints its refusal; (b) a narrow op that
  prunes `@LAT90` **and** writes a `@LAT100` boundary; (c) re-flash the FS — wipes 8
  `@LAT91` beliefs, 24 `@LAT92` outcomes and the B.3 sample, so no; (d) raise the cap —
  the header says don't, and it is the wrong fix.

- ✅ **2026-08-03 — OPTION (b) BUILT AND THE CARDPUTER IS REPAIRED: `@LAT90` 16/16 → 1.**
  ```
  **LANE-PRUNED** lane:90 gen:1 removed:16 last_lon:15 t_ms:1438863 stream:0xe7384824 node:0x00000300
  **STREAMS-EXPLAINED** n:12 0x0ad62c42 0xfc36a38c 0x10578c80 0x26a1b82d 0x44574814 0x59fb8ce8 ...
  **STREAM-ADOPTED** stream:0xe7384824 wall:0 t_ms:1447466 node:0x300 from:0x12   <- the one record now in the lane
  ```
  The repair is visible in that last line: the node had already adopted `0xe7384824`
  (from V4-C) and **could not record it** while the lane was full; with the lane pruned it
  wrote the adoption, so its own timeline is explained by its own lane again.
  📎 **The design decision that made the prune acceptable — carry the ids.** Dropping
  `@LAT90` plainly would orphan every older record's `stream:` stamp, which is the exact
  failure that lane exists to prevent, arrived at from the other side. So the boundary
  carries **every stream id the ended generation explained** (12 here) on a
  `**STREAMS-EXPLAINED**` line. An older stamp asks one question — *was this node ever on
  that timeline?* — and that line still answers it. What is genuinely lost, and is stated
  rather than glossed: the per-record offsets, the `from:` provenance, and the adoption
  structure.
  ⚠ **The ids are written BARE (`0x…`), not as `stream:0x…`, on purpose.** The firmware's
  @LAT90 needle is `" stream:0x"`, and a boundary listing twelve ids in that form would
  make the dedup read every one of them as a stream the node is on — the same
  needle-collision family as `prev_stream:`, which is why the marker lane could not live
  in @LAT90 in the first place. Pinned by a native test.
  🔒 **`removePerceptLanes`' guard is NOT weakened.** `pruneTimeline()` is a separate call
  that names @LAT90 explicitly; 98 (belief attestations) and 99 (sync) remain unreachable
  by any path, and the percept path is byte-for-byte what it was. `companion.py`'s
  client-side guard was widened to match (`--lane 90`), with the same refusals.
  📊 Native **lanegen 24/24** + timestream 9 new checks, Python **test_lanegen_py 18**,
  suites all green. Cardputer 41% flash, T-Deck 40% — both flashed and verified.
  ✅ **V4-A and V4-B flashed with this build** (94%, 70339 / 67959 B free), identified by
  app image as always. Neither grew its `@LAT90` lane on the reboot the flash caused —
  V4-A stayed at 3, V4-B at 3 — which is the hold behaving on the spine as it did on the
  T-Deck. ✅ **V4-C flashed too — ALL FIVE NODES now carry the origin hold + the timeline
  prune**, and V4-C's lane likewise did not grow (3 records, newest a real
  `STREAM-ADOPTED 0xe7384824 from:0x200`).
  📊 **Fleet state at close: one stream `0xe7384824` on all five**, and the `@LAT90` lanes
  are V4-A 3 · V4-B 3 · V4-C 3 · T-Deck 11 · Cardputer **1** (post-prune) — against a cap
  of 16 that was 1 record from binding two hours earlier.
  📎 **Where the fleet's streams came from, now readable off the lane:** V4-A's two newest
  records are `STREAM-ORIGIN 0xbdc62024` and `STREAM-ORIGIN 0xe7384824`, both `from:0x10` —
  **V4-A originated both**, on the two occasions it was flashed alone, and each time the
  rest of the fleet adopted it (V4-B `from:0x200`, the Cardputer `from:0x12`). Nobody
  configured that; the oldest-stream-wins merge picked it. Both origins predate the hold,
  which is exactly the kind of record the hold keeps — they survived and were real.

- 📋 **2026-08-03 — NEXT SESSION'S WORK ORDER: [part-b-handoff.md](part-b-handoff.md)**
  (authored against `c353568`). It supersedes `semantic-logging-handoff.md`, whose Part A
  is done and whose Part B is opened but unfinished. What remains: **1** `@LAT95`
  change-triggered with explicit run-length — the citation coupling and `@LAT92`'s tally
  are ONE decision, not two; **2** `@LAT96` change-triggered, whose baseline has been
  accumulating since this afternoon's prune; **3** the closeouts (the `@LAT90` full-policy
  now that a prune path exists, the K10, and the TTE report that is still cleared and
  unsent). Fleet state, both suites' counts, and six traps are stated there.

- ✅ **2026-08-04 (Part B Part 1) — `@LAT95` AND `@LAT92` ARE CHANGE-TRIGGERED WITH
  EXPLICIT RUN-LENGTH. The treadmill is fixed, and it is fixed WITHOUT falsifying a
  tally.** Both lanes filled with **uptime** rather than with events — `@LAT95` in 48
  minutes, `@LAT92` in 24 — and every lane on every node refilled to its cap within one
  afternoon of being pruned, measured three times on 08-03. Now a window whose verdict
  matches the run in progress writes nothing, and the record that closes the run says
  how many it suppressed.
  ```
  **RUN**     windows_since_last:10 reason:changed max_run:30
  **COVERED** state:still windows:9 n:540 window_ms:540000 moving_permille:0
              dev_mean_mg:8 dev_max_mg:20 moving_ms:0 first_t_ms:.. last_t_ms:..
              covered_by:@LAT95LON0
  ```
  **Lane life at rest: 48 min → 24 h on `@LAT95`, ~24 min → ~12 h on `@LAT92`** (cap ×
  `MAX_RUN` 30 × 60 s). A CHANGE is never deferred — a verdict flip writes immediately,
  so `@LAT93` transitions are unaffected in timing.
  ⚠ **§1.1 AND §1.2 WERE ONE DECISION AND THE HANDOFF WAS RIGHT TO SAY SO.** The unlock
  is that **run-length is LOSSLESS for Rule 3**: folding a verdict N times is
  arithmetically identical to folding it once per window (the +2 saturation and −16 floor
  are order-sensitive but not batch-sensitive), so a compressed `@LAT92` lane reconciles
  to the *same* conf/sal/streak/contradiction as an uncompressed one. That is not argued,
  it is **asserted** — `test_perceptlearn.cpp` §8c builds both lanes and compares the
  beliefs field by field. Keeping only transitions here, by contrast, would have removed
  `conf`'s denominator and made every belief systematically over-confident.
  📎 **The citation coupling (§1.1) is resolved by making a window a PAIR, not a record:**
  `(covering record, offset into its run)`. An outcome now reads
  `acting:@LAT95LON7+3` — "the 4th window of the run opened by @LAT95LON7" — and the
  `before` half of an @LAT93 transition, which is now *usually* a suppressed window,
  reads `lane:@LAT95LON0+1`. The `derived_from` **edges stay plain ordinals**: an edge
  must resolve to a record that exists, and the covering record does.
  ⚠ **TWO TRAPS THIS COST, BOTH CAUGHT ONLY BY THE NATIVE TESTS.** (1) `adoptRun()` read
  `claims_`, which the sketch's `arm()` overwrites between `score()` and `buildOutcome()`
  — so every window compared as `changed` and run-length **silently did nothing while
  looking exactly like it worked**; fixed with a `scored_vec_` snapshot taken inside
  `score()`. (2) The sketch's arming branch tested `m == 0`, which used to mean "no
  window" and now means "covered", i.e. the normal case — it would have disarmed Rule 1
  for 29 windows out of every 30. Both are the same shape: *a return value whose meaning
  changed under it.* Branch on `lastClose()`, never on the byte count.
  📎 The sketch now **renders the outcome even when `@LAT92` is full** and throws the
  bytes away, because `buildOutcome` is what adopts the run — skipping it would leave the
  closed run open and let a real change be folded away as unchanged. A record dropped for
  want of lane space must not also corrupt the run accounting.
  📊 **Laptop side: `companion.py motion [--file <ttdb>|--port --node]`** parses `@LAT95`
  and reconstructs the arithmetic — records vs **windows**, and an `unaccounted` count
  when a `**RUN**` line claims windows no `**COVERED**` block explains. It reads **both
  formats**: a pre-08-04 record has no `**RUN**` line and is exactly one window, which is
  the default, so old and new records on the same flash sum correctly. ⚠ Prefer `--file`
  on a node under measurement — opening its port resets it and restarts the 60 s window.
  📊 Suites: native **485 checks** (was 453), Python **252 across 9 files** (was 230/8,
  new `tests/test_motion_py.py`). All five sketches compile: Cardputer 41%, T-Deck 40%,
  V4-A/B/C 94%, K10 20%. Cost measured against a HEAD worktree, Cardputer only (it is the
  only node with an IMU, so the only one carrying these tiers): **+2700 B flash (+0.086%),
  +2920 B RAM** — most of it `PERCEPTLEARN_BUF` 1792 → **2624**, which had to grow because
  a full 8-claim house *with* a covered line per claim renders at 2340 B and `buildOutcome`
  writes nothing rather than truncating. That would have been the **third** time this
  pattern silently lost data, and it would have dropped precisely the records carrying a
  run.
  ⏳ **NOT YET FLASHED — this is software-verified only.** The hardware check that matters
  is the one B.3's trap dictates: **prune `@LAT95`, then leave the Cardputer untouched for
  an hour** and confirm `companion.py motion --file` reports ~60 windows across ~2 records
  with `unaccounted:0`. A lane's own record count is not evidence of how long a node was
  still — that is now literally true, and the reader exists so it stays checkable.
  📎 Untouched by choice: the `@LAT95` **lane-full** path still discards the window and
  disarms the loop. It is ~30× rarer now; letting a full lane keep folding into an
  existing run would be reasonable and is not worth the complexity until the cap is
  actually reached again.

- ✅ **2026-08-04 — `@LAT92` IS PRUNABLE (`lanegen::pruneOutcomes`), BECAUSE IT WAS FULL
  AND THAT LEFT TODAY'S WORK WITH NO HARDWARE PATH.** Found while planning the flash: the
  Cardputer's lanes read `@LAT90 1 · @LAT91 8 · @LAT92 **24/24** · @LAT94 48 · @LAT95 48 ·
  @LAT96 29 · @LAT97 48 · @LAT100 4`. A full outcome lane means the learning loop "is
  still predicting but no longer testifying" — and `removePerceptLanes` refuses anything
  outside 94–97, so `@LAT92`'s half of the run-length change could not be exercised at
  all. Exactly the shape of `@LAT90`'s 16/16 on 08-03, answered the same way: a **separate
  named call**, not a widened guard. 98/99 remain unreachable by any path.
  📎 **What the boundary carries, and why it is not the stream-id list.** `Reconciler` is a
  **pure function** of `@LAT92`, so emptying the lane returns every `@LAT91` belief to
  baseline on the next Dream Cycle. `PerceptLearn.h` already states that as a property, so
  the prune exercises an invariant rather than breaking one — but a belief silently
  falling from 106 back to 128 is indistinguishable from a node that never learned
  anything. So the boundary carries the **tally and the conclusions**:
  ```
  **LANE-PRUNED** lane:92 gen:1 removed:24 last_lon:23 t_ms:.. stream:0x.. node:0x300
  **OUTCOMES-CARRIED** records:24 windows_max:312 beliefs:2 met:288 violated:18
                       unobserved:6 baseline_conf:128 rule:+2/-16
  **BELIEF-AT-BOUNDARY** peer:0x00000200 proto:0 conf:106 sal:16 met:9 violated:5 ...
  ```
  ⚠ `records:` and `windows_max:` are **both** stated on purpose — since this morning a
  record can stand for up to 30 windows, so the record count is no longer the denominator.
  `windows_max` is the **max** across beliefs, not a mean: the claim set changes as peers
  come and go, and a mean would report a number no claim actually experienced.
  ⚠ **The boundary carries NEITHER `**OBSERVED** peer:0x` NOR `**COVERED** peer:0x`** —
  `Reconciler::foldRecord`'s two needles. A boundary carrying either would be folded as
  testimony the next time the lane was read: **the node re-learning from its own
  gravestone.** Third instance of this family (`prev_stream:` in @LAT90, the bare ids in
  `**STREAMS-EXPLAINED**`), and it is pinned by a test on both sides.
  📎 `buildPruneRecord` grew a generic `carried` parameter; the block is built by the
  **sketch**, because folding the lane needs PerceptLearn and LaneGen must not depend on
  it. `LANEGEN_OUTCOME_LANE` is asserted equal to `PERCEPTLEARN_LANE` with a
  `static_assert`, so a drift between the two fails the build rather than emptying a lane
  nobody asked for.
  📎 **The laptop already reports the consequence**: an `@LAT91` belief's
  `reconciles@LAT92LON0` edge reads **stale** against the boundary, so a belief standing
  on evidence that is gone is visible from `companion.py prunes` rather than inferred.
  ⚠ **A near-miss worth recording**: sharing the 2624 B lane-read buffer between the Dream
  Cycle and the prune left `sizeof(buf)` applied to a **pointer** — 4 bytes — which would
  have clamped every fold to 4 bytes and silently emptied every belief. Removed the
  indirection entirely rather than fixing the expression.
  📊 Native **494 checks**, Python **257 across 9 files**. Cost vs HEAD: Cardputer
  **+4620 B flash (+0.147%), +3944 B RAM** (41%); V4-A/B/C **+52 B** and T-Deck **+48 B**
  from the `carried` parameter alone — inert for them, but it does mean their binaries
  changed.

- 📋 **2026-08-04 — THE FLASH + MEASURE RUNBOOK (order matters, and the prune is LAST).**
  Flashing the app does not touch LittleFS, but every `companion.py` call resets the board
  and restarts the 60 s window, so the prune has to be the last thing that touches it.
  1. **`pull` the Cardputer on its own cable** → `master/prune-2026-08-04/cardputer_pre.md`.
     Never clear a lane you could not pull first. This also archives the `@LAT96` baseline
     Part 2 needs and the `@LAT92` generation about to be dropped.
  2. **Flash the app only** — `arduino-cli compile --upload`. ⚠ **Do NOT run
     `Upload-Cardputer-FS.ps1`**: it would wipe the 8 `@LAT91` beliefs, the `@LAT92`
     generation and the B.3 sample, and the boundary record would then describe nothing.
  3. **If V4-A is being flashed, do it now, before the quiet hour** — it is the Cardputer's
     peer, and a reboot mid-measurement lands as `unobserved` claims and breaks the run.
  4. **`cmd --op clear-percepts --lane 95 --attempts 6`** then **`--lane 92 --attempts 6`**.
     ⚠ Lane **95 only**, not `--lane 0`: the default drops 94–97 including the `@LAT96`
     Jaccard baseline that has been accumulating since 08-03. ⚠ A no-ACK is often a false
     negative on a lane clear (whole-TTDB rewrite outruns the RTO ladder) — `ping` first,
     then retry; the op is idempotent.
  5. **Hands off for an hour.** No `companion.py` calls at all.
  6. **`pull`, then `motion --file`.**
  ⚠ **Expect ~31 windows across 2 records, NOT ~60.** The run open at pull time is
  unwritten and lost to the reset — that is the documented `MAX_RUN - 1` cost, not a fault.
  What to check: `unaccounted:0`, a second record reading `windows_since_last:30
  reason:heartbeat`, ~15 windows/record, and on the `@LAT92` side a `**COVERED**` line
  whose `windows:` exceeds 1.

- ⚠ **2026-08-04 — THE FIRST `@LAT92` PRUNE REFUSED ITSELF ON HARDWARE, AND THE REASON IS
  A RULE THIS PROJECT ALREADY HAD.** `--lane 0` landed cleanly (135 370 B → 47 795 B,
  94–97 emptied, four `@LAT100` markers). `--lane 92` did nothing: `buildOutcomeCarried`
  rendered **1124 B** into a **1024 B** buffer and returned 0, so `pruneOutcomes` refused
  rather than write a boundary that understated the evidence. **The mechanism was right —
  "write nothing rather than truncate" fired exactly as designed.** The arithmetic in
  front of it was not: the constant was set from an eyeball estimate of "~100 B a line"
  and a `**BELIEF-AT-BOUNDARY**` line is **122 B**, so a full 8-belief house is 7% over.
  ⚠ **THE ACTUAL DEFECT IS WHERE THE BUILDER LIVED, NOT THE NUMBER.** It was written
  inside `cardputer_console.ino`, and **a native test cannot call into a `.ino`** — so
  the one discipline that has caught this exact failure three times before
  (`MOTIONPERCEPT_TRANSITION_BUF` at 512, `PERCEPTLEARN_BUF` at 1024, `PERCEPTLEARN_BUF`
  again at 1792) could not run. Every one of those was caught by a native test measuring
  the worst case against the constant; this one had no such test *available*, and it is
  the only one of the four that reached hardware. **The fix is
  `perceptlearn::Reconciler::buildBoundary` — the render moved into the library; the
  sketch keeps only the flash I/O the library must not do.** `PERCEPTLEARN_BOUNDARY_BUF`
  is **1536**, and the test asserts the real 8-belief ceiling both fits it **and does not
  fit the 1024 that failed**, so shrinking it back fails the build.
  📎 Lesson worth carrying past this lane: **a builder that renders into a fixed buffer
  belongs in a portable library, not in a sketch** — not for reuse, but because that is
  the only place its size can be pinned. Cost here was one measurement window.
  📊 Native **507 checks**. Cardputer 41% (1 316 161 B), reflashed with the fix.

- ✅ **2026-08-04 — FIRST RUN-LENGTH RECORD READ BACK OFF HARDWARE.** After the `--lane 0`
  prune, `companion.py motion --file` on a fresh pull:
  ```
  lane    t_ms       stream    state  perm  devmax  since  reason
     0    7084422  be6d9616    still     0      11      1  first
  ```
  `reason:first`, `windows_since_last:1`, no `**COVERED**` block, `unaccounted:0` — the
  format, the firmware and the laptop reader agree end to end. 📎 And `dev_max_mg:11`
  lands right on B.3's measured floor (p90 = **12 mg**), an independent confirmation of
  `MOTIONPERCEPT_MOVING_MG 60` from a fresh boot on a different day.
  ⚠ **Only ONE record, because the observer kept resetting the observed.** Every `pull`
  and every `cmd` reboots the cabled node and restarts its 60 s window, so a session that
  flashes, prunes, pulls and re-pulls can never accumulate a run — the node had 8 resets
  in the hour. This is [[looping-companion-py-resets-bridge]] in its most expensive form:
  the run-length behaviour is **unobservable from a session that is actively working on
  the node.** The quiet hour is not a nicety, it is the instrument.

- ✅/⏳ **2026-08-04 — HARDWARE RESULT: THE `@LAT92` PRUNE IS PROVEN; `@LAT95`'s COMPRESSION
  IS NOT, AND THE REASON IS THE CABLE.**
  ✅ **`pruneOutcomes` works end to end.** `@LAT92` 24 → 1, and the boundary carries every
  belief exactly as the node reported it minutes earlier:
  ```
  **LANE-PRUNED** lane:92 gen:1 removed:24 last_lon:23 t_ms:8137821 stream:0xbe6d9616 ...
  **OUTCOMES-CARRIED** records:24 windows_max:24 beliefs:8 met:167 violated:14 unobserved:2
  **BELIEF-AT-BOUNDARY** peer:0x00000010 proto:ble    conf:176 sal:0  met:24 violated:0 ...
  **BELIEF-AT-BOUNDARY** peer:0x00000200 proto:espnow conf:50  sal:56 met:17 violated:7
                         max_streak:2 contradiction:1
  ```
  All 8 beliefs, both contradictions, conf 176/176/176/176/158/64/50/158 — the conclusions
  survived the evidence that produced them, which is the whole point of the boundary.
  `@LAT91` then fell to 3 beliefs re-derived from the one surviving outcome, exactly as
  "a belief is as strong as the evidence retained" predicts.
  ✅ **The `@LAT95` format and the reader agree end to end**, `unaccounted:0`, and
  `dev_max_mg` read 11/12/13/12 across four records — B.3's measured floor (p90 = 12 mg)
  reproduced on a different day. **Folding was observed directly**: after a reset the node
  printed `[motion] percept window -> @LAT95LON5 covers:1` at 60.4 s and then **nothing at
  120 s or 180 s**, which is a covered window behaving exactly as designed (no record, no
  print).
  ⏳ **But compression came out at 1.0.** Four records in 49.6 min, every one
  `reason:first windows_since_last:1` — no run ever survived to close with a `**COVERED**`
  block or reach the 30-window heartbeat.
  ⚠ **THE CAUSE IS NOT THE FIRMWARE: THE RUN WAS BROKEN FOUR TIMES, AND EVERY BREAK IS
  VISIBLE IN A LANE THAT DID NOT CHANGE.** `@LAT97` is still periodic and flushed 48 times
  at a median gap of exactly 60 s, so it is a clean cadence reference. Its three
  over-length gaps sit at t = 7384 / 8137 / 9941 s, and the `@LAT95` records imply run
  breaks at 7477 / 8141 / 10002 — **8137 → 8141 is a four-second match.** One break was
  the `--lane 92` prune (its own boundary is stamped `t_ms:8137821`). **The other two were
  spontaneous.**
  📎 **So the instrument is the disturbance.** A heartbeat needs **31 consecutive
  undisturbed windows** — 31 minutes in which nothing resets the node — and a USB-cabled
  ESP32-S3 does not reliably get them ([[usb-uart-chip-reset-not-a-crash]]: `rst:0x15` is a
  host/USB reset, not a crash). Every `pull`, every `cmd`, and apparently the host itself
  every ~10–30 min, resets the board and calls `reset()` → `breakRun()`. Note the shape:
  the OLD periodic lane was *immune* to this, because a reset costs it one window and
  nothing else — **run-length is the first thing this fleet has built whose correctness
  depends on being left alone.**
  📎 **Next attempt should run it on BATTERY**: unplug the Cardputer (1750 mAh, read 100%),
  leave it 45 min untouched, then plug in and pull ONCE. It is a roaming handheld; this is
  the configuration the fleet was designed around, and it removes the host from the
  experiment entirely. ⚠ Expect `reason:first` on the first record after the plug-in too —
  that reset is unavoidable and lands *after* the window being measured.

- ✅ **2026-08-04 — `@LAT95` RUN-LENGTH IS PROVEN ON HARDWARE. Compression 6.8x, and the
  heartbeat fires to the millisecond.** The node ran ~2 h unattended — the one condition
  the previous attempt could not supply — and the lane now reads **10 records accounting
  for 68 windows** (68.1 min observed, 62 913 samples, `unaccounted:0`):
  ```
  lane        t_ms   state  devmax  since  reason     covered
     5    12369240   still      12      1  first      -
     6    14171240   still      12     30  heartbeat  29x still devmax:13 perm:0
     7    16031903   still      13      1  first      -
     8    17831903   still      14     30  heartbeat  29x still devmax:13 perm:0
  ```
  ```
  **RUN** windows_since_last:30 reason:heartbeat max_run:30
  **COVERED** state:still windows:29 n:28966 window_ms:1740000 moving_permille:0
              dev_mean_mg:9 dev_max_mg:13 moving_ms:0 first_t_ms:16091903
              last_t_ms:17771903 covered_by:@LAT95LON7
  ```
  📊 **LON7 → LON8 is 1 800 000 ms — exactly `MOTIONPERCEPT_MAX_RUN` (30) x 60 000.** The
  covered block's `window_ms:1740000` is exactly 29 x 60 000, and `covered_by` names the
  run's opener. Every number the format promises is present and internally exact.
  📎 **The earlier 1.0 result was the measurement, not the mechanism** — confirmed from the
  other side: the six `reason:first` records are the disturbed period, records 6 and 8 the
  quiet one, on the same lane in one file. `dev_max_mg` held 12–13 mg across 68 windows,
  B.3's floor again.
  ⏳ **`@LAT92`'s run-length is still unexercised, and `@LAT97` is why.** It is FULL
  (48/48), and a full link lane calls `gLearn.disarm()` every window, so no expectation is
  ever armed and no outcome is ever scored. **Prune 94–97 before any run intended to
  exercise the outcome lane** — and keep V4-A powered, since @LAT92 needs peers to predict
  about.

- ✅✅ **2026-08-04 — PART 1 IS FULLY VERIFIED ON HARDWARE. The battery run closed both
  halves, and the lossless claim was checked by an INDEPENDENT laptop re-fold.** The
  Cardputer ran **43 min unplugged and untouched** (the host removed from the experiment
  entirely), with V4-A left powered as its peer.
  📊 **The periodic control, same 43 minutes:** `@LAT94` wrote **43** records and `@LAT97`
  wrote **43** — one per minute, as they always did. Against that:
  ```
  @LAT95   2 records / 31 windows   = 15.5x     compression
  @LAT92   6 records / 36 windows   =  6.0x     compression
  ```
  ✅ **`@LAT95`:** `LON1` reads `windows_since_last:30 reason:heartbeat` with
  `**COVERED** windows:29`, spaced 1 800 000 ms from `LON0` — exactly `MAX_RUN` x 60 000.
  ✅ **`@LAT92`, the half that had never run:**
  ```
  **RUN** windows_since_last:30 reason:heartbeat max_run:30
  **COVERED-SPAN** windows:29 first_t_ms:18884845 last_t_ms:20564845
                   counts_scored_windows_not_minutes:1
  **COVERED** peer:0x00000010 proto:ble    verdict:met windows:29 observed_min:-64 observed_max:-61
  **COVERED** peer:0x00000010 proto:espnow verdict:met windows:29 observed_min:-49 observed_max:-47
  **COVERED** peer:0x00000100 proto:espnow verdict:met windows:29 observed_min:-45 observed_max:-42
  ```
  The span is 1 680 000 ms = 28 x 60 000, exactly 29 windows' worth of gaps.
  🔬 **THE LOSSLESSNESS CLAIM, TESTED THE ONLY WAY THAT COUNTS.** Rule 3 was
  re-implemented independently on the laptop (fold in document order, `**COVERED**` lines
  folded `windows:` times) and run against the pulled lane:
  ```
             laptop re-fold                      device @LAT91
  0x010 ble    conf:182 sal:8 met:35 vio:1  ==   conf:182 sal:8 met:35 vio:1
  0x010 espnow conf:196 sal:0 met:34 unob:1 ==   conf:196 sal:0 met:34 unob:1
  0x100 espnow conf:200 sal:0 met:36        ==   conf:200 sal:0 met:36
  ```
  **Exact on every field.** And the tallies are **34–36 windows from 6 records** — the
  denominator survived compression intact, which is the entire reason run-length was
  legitimate on a tally. `conf 182 = 128 + 2(35) - 16(1)` checks by hand.
  ✅ **The citation fix is visible in the field:** outcomes carry
  `acting:@LAT95LON1+1`, `+3`, `+4` and `@LAT95LON0+0`, `+1` — **non-zero offsets**, i.e.
  expectations correctly provenanced to *suppressed* motion windows rather than to a
  record describing a different one. That was §1.1's whole problem.
  📎 Two incidental observations: `@LAT95LON0` caught the **unplug** as
  `dev_max_mg:466 moving_permille:68` and still returned `state:still` — 6.8% of samples
  over the line is under the 100-permille verdict gate, exactly as designed. And
  **peer `0x00000100` is the K10**, which is powered and being heard over ESP-NOW despite
  being PARKED in §2.

- ⚠ **2026-08-04 — PART 2's ARCHIVED `@LAT96` BASELINE IS NOT USABLE, and the way it fails
  is B.3's trap in a new costume.** Measuring consecutive-window Jaccard drift off
  `cardputer_pre.md` gave plausible numbers (p50 0.333, p90 0.538, max 0.727) — and then
  the cross-check killed them: those 48 windows span **five different streams** and `t_ms`
  runs **backwards four times**, so the lane is fragments of several runs, not one; and the
  `@LAT95` lane that would evidence stillness sits on a **different stream**, so there is
  no independent evidence the node was still while those AP sets were collected.
  📎 **The rule that caught it: the stillness evidence must come from a DIFFERENT SENSOR
  than the one under test.** B.3's failure was windows labelled `still` by the threshold
  being measured; here the threshold is Jaccard and the witness is the IMU, which is
  legitimate — but only if the two cover the same period on the same timeline. **Check the
  stream ids before trusting any cross-lane cross-check.**
  📊 The directional hint survives and matches the handoff's prediction: with a median of
  only **8 APs per window**, one AP appearing or vanishing moves Jaccard by ~0.125, so
  neighbour churn eats much of the dynamic range. Block-smoothing did not obviously rescue
  it (k=3 → p90 0.417, k=8 → p90 0.375, but n falls to 5). If that holds on clean data the
  naive per-window Jaccard trigger is a poor change signal on this board, and Part 2 wants
  a **stable-core** set (APs seen in ≥N of the last M windows) rather than the raw set.
  ⏳ The battery run collected only **5** `@LAT96` windows (its scan is on a ~5 min duty
  cycle), so a clean baseline still needs a longer quiet run — several hours, not one.

- 📋 **2026-08-04 — PART 2's MEASUREMENT IS SET UP, AND ITS GATES ARE CODE, WRITTEN
  BEFORE THE DATA EXISTS.** `companion.py entity-drift --file <ttdb>` measures
  consecutive-window Jaccard drift on a known-still node and **refuses to print a
  distribution unless the run passes four gates**. Declared in advance, which is the only
  order in which a gate means anything:
  1. one stream id across every `@LAT96` record
  2. `t_ms` monotonic
  3. `@LAT95` witnesses stillness over ≥90% of the same span, **on the same timeline** —
     a different sensor from the one under test
  4. ≥30 pairs survive the spacing filter
  ⚠ **Gate 4 is not sample-size padding.** A reboot forces an immediate scan
  (`gLastScanKick == 0`), inserting a window ~60 s after the last instead of ~600 s.
  Drift across that gap **understates** churn, so those pairs are DISCARDED — a
  contaminated pair is wrong, not conservative.
  🔬 **Run against this morning's archive it FAILS 1, 2 and 3 — and PASSES 4** (32 pairs
  kept). So a sample-size check alone would have accepted the bad data; the three
  provenance gates carry the weight. That is the whole lesson of the archive, now
  mechanised.
  📊 **`WIFI_SCAN_PERIOD_MS` is 600 000 — one scan per 10 MINUTES**, not the 5 min the
  record spacing suggested (that spacing was inflated by reboots forcing extra scans). So
  **`@LAT96` fills in 8 HOURS of uptime, not 48 min** — it is ~10x less of a treadmill than
  `@LAT95` was, which lowers Part 2's urgency relative to Part 1's. 48 windows = 47 pairs
  = an **8 h run**, matching B.3's n=48. ⚠ Do NOT shorten the scan period to speed this
  up: the quantity is churn *over the interval the tier actually uses*, so a threshold
  measured at 1-min spacing would not apply to a tier that samples every 10.
  📋 **The run:** prune `--lane 0` first so the run is the sample; leave it **8 h plugged
  in, untouched, physically still**; keep V4-A powered so the stream stays stable; **one**
  pull at the end. Cable is right here even though it was wrong for Part 1 — `@LAT96` is
  still *periodic*, so a reset costs one window instead of breaking a run, and 8 h of
  battery with the display lit is not credible. Record budget **212/256**; `@LAT100` goes
  to 17/32, leaving room for ~3 more full prunes before that lane becomes the story.
  📊 Suites: native **507**, Python **275 across 10 files** (new
  `tests/test_entity_drift_py.py`, 18 checks).

- ❌ **The first 8 h Part 2 baseline FAILED, and the cause is the LAPTOP'S USB HOST
  RESETTING BOTH BOARDS — not "the Cardputer lost power" (2026-08-06).** The gates refused
  it: **5 streams**, `t_ms` backwards 4×. The diagnosis came from **V4-A's own `@LAT90`**,
  pulled over its own cable: it carries a **`STREAM-ORIGIN` for every stream the Cardputer
  later joined** (`be6d9616`, `dffbae31`, `185f5a4b`, `946fea42`, …). Both boards restarted
  **together, ~5–7 times**. ⚠ **V4-A was sitting at 4.096 V / 89 % the whole time, so this
  was never a brownout** — a charged pack does not stop a `USB_UART_CHIP_RESET`, which is a
  *chip* reset driven by the host asserting DTR ([[usb-uart-chip-reset-not-a-crash]]). The
  same "spontaneous host/USB resets" wrecked the first Part 1 attempt; that is **twice**, so
  treat the laptop as an active hazard to any multi-hour run, not a neutral power source.
  🔧 **Fix: power both nodes from a WALL CHARGER or power bank — never a laptop port.** No
  host ⇒ no DTR ⇒ no reset, and unlike battery the run cannot end early. This is not a new
  risk: the 43 min Part 1 battery run already proved the sketch is happy with **no USB host
  attached**. Reconnect to the laptop only for the single pull at the end, where the reset it
  causes costs nothing.
  ⚠ **My own two mistakes here, both worth not repeating.** (1) `intero --port COM6` with
  `--node` left at its default queries **the Cardputer through the bridge** and prints
  `cardputer_1` — an answer on a port still proves nothing about which board that port is,
  exactly as the identify-by-app-image rule says. **Name the node.** (2) That call reset V4-A,
  **destroying its uptime**, which was the one direct measurement of the shared-reset
  hypothesis. `@LAT90` happened to preserve the answer; next time read uptime *first*.
  🔬 **Salvage: the run was ~1 h short, not hopeless.** Longest unbroken stream `185f5a4b` =
  **25 windows / 3.88 h**; the floor is **31 windows ≈ 5.2 h** (≥30 pairs), so a run only has
  to clear 5.2 h — and `ENTITYPERCEPT_MAX_LANE 48` caps it at exactly **8.0 h**. That is the
  usable band. 📈 **Feasibility preview on that one clean stream (NOT a baseline — it did not
  earn one): n=21, min 0.111, p50 0.300, p90 0.444, max 0.556, zero zeros, AP set 4–11.**
  So the signal is live, and it already hints that a **still** node's drift floor is high
  enough that the threshold will be loose — the §6 warning above, now with numbers.
  ⚠ **`@LAT90` is at 15/16 on BOTH boards.** Prune it on both or the next run's stream
  changes cannot be recorded — and that lane is the only reason this failure was diagnosable.
  ⚠ **`mind` on the Cardputer reads 8 KB `maxalloc`, against ~45 KB documented and 29–30 KB
  seen more recently** — the sketch's own gauge calls <16 KB the warn band. It did **not**
  cause the resets (V4-A had 101 KB and reset in lockstep), and WiFi scans still ran, so it
  is logged as a live regression to investigate, not this run's culprit.
  ⚠ **`tests/test_entity_drift_py.py`'s fixture was not byte-faithful** — it wrote
  `**ENTWIN** … n:` / `kind:wifi` where the firmware writes **`entities:`** / **`wifi_ap`**.
  It passed anyway, because `parse_entity_percepts` derives the set from `**ENTITY**` lines
  and ignores the count. Fixed against a real record. *A gate proven only against a record
  the firmware would never emit is not proven.*

- ✅ **PART 2 HAS ITS BASELINE — the second attempt PASSED ALL FOUR GATES (2026-08-06).**
  `master/entity-baseline/cardputer_baseline_2026-08-06.md`, reproducible with
  **`companion.py entity-drift --file <f> --segment`**:

  ```
  SEGMENT: longest contiguous single-stream run = stream e334a7e1, 41 of 48 window(s)
  [PASS] one stream id · [PASS] t_ms monotonic · [PASS] @LAT95 stillness 0 moving,
  95% span, timeline match · [PASS] 37 pairs kept, 3 discarded off-cadence
  AP set/window: min 4 p50 5 max 8   (one AP moves Jaccard ~0.200 at p50)
  DRIFT n=37: min 0.000  p50 0.143  p75 0.286  p90 0.375  p95 0.500  max 0.500
  ```

  🔬 **The run survived TWO reboots without breaking, because V4-A held the stream** —
  `@LAT90` LON1/LON2 are `RECONCILED` back onto `e334a7e1` after the node originated its
  own and lost. That is the team time stream earning its keep: the same reboots that
  shattered the previous night into 5 timelines cost this one only 3 off-cadence pairs.
  A third reboot at ~6.5 h found V4-A absent, originated `be8a1293`, and ended the run.
  ⚠ **It ran ~7.5 h on BATTERY, down to 7 % / 3.574 V — so my "8 h on battery with the
  display lit is not credible" was WRONG.** Battery is viable and is also immune to the
  host resets; a wall charger is still better only because it cannot run out.
  ⚠ **`--segment` selects the longest CONTIGUOUS single-stream run, never a filter by
  stream id** — a node can leave a stream and rejoin it, and a plain filter would stitch
  the two blocks across the hole and present it as one unbroken observation
  (`longest_stream_segment`, with the stitching trap pinned in the tests). The rule is
  outcome-independent (longest wins, drift never consulted), but ⚠ **under it gate 1
  holds BY CONSTRUCTION and tests nothing — say so when reporting; gates 2–4 carry it.**
  ⚠ **ONE NIGHT IS NOT A TRANSFERABLE THRESHOLD.** The preview off the *failed* night
  disagrees materially — p50 **0.300** vs **0.143**, zeros **0/21** vs **15/37**, AP set
  mean **8.2** vs **5.5** — on the same node in the same place. The AP population itself
  differs by day, and Jaccard's quantisation rides on set size (1/5 = 0.200 vs 1/8 =
  0.125). This is the RSSI lesson again ([[rssi-ranging-shadowing-limited]]): **measure a
  second night before fixing the constant**, and expect the threshold to need ≥0.5.
  📊 Python **280 across 10 files** (entity-drift 18 → 23).
  ⚠ Printed output must stay **ASCII**: `⚠` (U+26A0) raises `UnicodeEncodeError` on this
  cp1252 console. Third time; it is a console limit, not a source-encoding one.

- ✅ **A LAPTOP-SIDE FLEET CONSOLE — `orchestrator/fleet_ui.py`, one window over the whole
  fleet (2026-08-06).** tkinter + pyserial only, and it imports `companion.py` as a
  library, so no wire format, parser or retransmit rule is re-implemented here.

  ```bash
  python orchestrator/fleet_ui.py --bridge COM6 --aux COM14   # ports also pickable in-window
  ```

  **Why it holds a connection instead of shelling out per refresh — this is the whole
  design.** Every `companion.py` invocation opens with DTR/RTS asserted and reboots the
  cabled node, so a UI built on the CLI would reset the fleet several times a second: the
  mechanism that fabricated a two-node outage ([[looping-companion-py-resets-bridge]]) and
  then wrecked a Part 1 and a Part 2 overnight run. So each link owns its port on **one
  thread for the port's whole open life** (`open_serial_no_reset`), and polling, commands
  and pulls are all jobs on that thread. Panels: **links** (the V4-A bridge plus one aux
  cable, each with tx/rx frame counters and reply age), **fleet** (every node's
  `CMD_GET_INTERO` body + `CMD_GET_STATUS`, coloured by freshness; double-click toggles
  polling), **global view** (drawn from `master/positions.md` where that SP2 belief exists
  — solid outline — else ring-placed and **dashed, so a drawing never reads as a belief**),
  **lanes** (every lane with its firmware cap and fill bar, plus Clear), **controls**, **log**.
  🔬 **VERIFIED LIVE ON ALL FIVE NODES** (COM6 = V4-A, COM14 = Cardputer):

  ```
  node        via     volts  %     dieC  memKB  up      lp  bpm  conductor      band
  v4a_bridge  bridge  4.081  88%   58.8  81     44m41s  35  120  cardputer_1    clk- chart
  v4b_relay   bridge  3.905  64%   35.2  95     1m32s   35  120  cardputer_1    clk- chart
  v4c_edge    bridge  3.929  67%↑  35.6  95     1m31s   41  120  cardputer_1    clk- chart
  tdeck_1     bridge  3.880  61%   34.8  20     3m59s   74  120  cardputer_1    clk- chart
  cardputer_1 aux     4.200  100%  47.6  7      10m51s  18  120  cardputer_1 *  clk- chart
  ```

  Link routing worked as designed: the aux cable polls **only the node it is declared to
  be** (`['cardputer_1']`, no air hop), the bridge polls the other four. `cardputer_1`
  holding the baton over lower-id nodes is **not** a defect — era wins, lowest-id is only a
  tie-break (§6 2026-07-24) — checked so the next reader need not.
  ⚠ **A NO-RESET OPEN DID NOT RESET EITHER BOARD, AND THAT IS MEASURED, NOT ASSUMED:**
  V4-A's uptime ran **41m28s → 44m41s across three separate connects** and the Cardputer's
  **7m29s → 10m51s**, both monotonic. So the framed toot link works over a `dtr=False`
  open on a **handheld** as well as a V4. ⚠ This does **not** overturn the 2026-07-29 note
  that a no-reset tail reads nothing — that was the sketch's **console text**, which was
  not retested here. Frames yes, prints unretested.
  🔧 **Consequence for the Part 2 runbook:** a run can be inspected *while it is running* —
  and its end-of-run pull taken — without the port open costing a reset. The `intero`
  reset caveat applies to the CLI path, not to this one.
  ✅ **Pull + lanes, over V4-A's own cable: 34 708 B in 0.9 s, zero null bytes** (no gaps),
  clean record boundary at the tail. The panel then read `@LAT96` **48/48**, `@LAT97`
  **48/48**, `@LAT90` **2/16**, `@LAT100` **5/32**, 105 records — matching item 1's
  independently-recorded readiness numbers exactly, which is the corroboration that says
  the lane arithmetic is right. Pulls land in **`master/ui/<node>.md`**, deliberately out
  of the curated `master/` artifacts.
  📋 **Clear routes by lane and refuses what the firmware refuses.** 94–97 and ALL are
  ordinary; `@LAT92` asks with the full warning that it returns every `@LAT91` belief to
  baseline; ALL warns it takes `@LAT96`'s Jaccard baseline with it; 91/93/98/99/100 are
  greyed as "(no prune path)" rather than offering a button the node would refuse. It
  sends **8 attempts** and reports a missing ACK as **unconfirmed, not failed** — a prune
  rewrites flash and can be busy through its own ACK window
  ([[band-play-ack-false-negative]]). Step (a) of item 1's runbook is therefore now four
  button presses for the operator.
  ⚠ **The aux node is DECLARED, never detected, and the UI says so on the glass.** Declared
  wrong on purpose (`tdeck_1` on the Cardputer's cable), the row read **`tdeck_1 has not
  replied`** while the Cardputer's own data filled its row — it did not quietly relabel the
  cable to whoever answered. That is the identify-by-app-image rule holding under a wrong
  operator claim, which is the only time it matters.

- ⏭ **OUTSTANDING ITEMS (as of 2026-08-06, end of session). The working tree is CLEAN —
  everything below is unstarted work, not unsaved work.** Commit `ee85d8f` carries the
  baseline, the four pulled TTDBs, `--segment`, and the tests.

  **1. ▶ NEXT SESSION: the SECOND 8 h baseline night** — the only thing blocking Part 2's
  threshold. Its purpose is **transfer**, not more precision: does night 2 agree with
  night 1 (p50 0.143 · p90 0.375 · p95/max 0.500)? Runbook:

  🛑 **THIS RUNBOOK IS SUPERSEDED — DO NOT COPY IT.** Step (a)'s `--lane 0` spends **four**
  `@LAT100` markers where **one** would do, which is what put the budget at 28/32 and one
  round from never. The corrected night-3 runbook is the 2026-08-10 entry at the end of
  this section; the block below is kept only as the record of what was run.

  ```bash
  # a) prune BOTH boards first (the run must BE the sample). EVERY companion.py call
  #    below is blocked by the permission classifier for Claude -- `pull` as well as
  #    `cmd`, so the end-of-run collection is the operator's too, not just the prune.
  python orchestrator/companion.py cmd --op clear-percepts --lane 0  --node cardputer_1 --port <COM> --attempts 6
  python orchestrator/companion.py cmd --op clear-percepts --lane 90 --node cardputer_1 --port <COM> --attempts 6
  python orchestrator/companion.py cmd --op clear-percepts --lane 0  --node v4a_bridge  --port <COM> --attempts 6
  python orchestrator/companion.py cmd --op clear-percepts --lane 90 --node v4a_bridge  --port <COM> --attempts 6
  # b) CHARGE the Cardputer (night 1 ended at 7 %), then run >=5.2 h, node still,
  #    V4-A POWERED ALONGSIDE -- that is what let night 1 survive two reboots.
  # c) one pull at the end, then:
  python orchestrator/companion.py pull --node cardputer_1 --port <COM> --out master/entity-baseline/cardputer_baseline_night2.md
  python orchestrator/companion.py entity-drift --file master/entity-baseline/cardputer_baseline_night2.md --segment
  ```

  ⚠ **Re-identify the COM ports; do not reuse `COM14`/`COM6` from this session.** ⚠ Never
  run `Upload-Cardputer-FS.ps1` during a measurement — it wipes the lanes.
  📌 **Night-2 attempt, 2026-08-06 evening — ports re-identified BY APP IMAGE, both boards
  plugged in: `COM6` = `V4-A bridge` (16 MB + 2 MB PSRAM, MAC `8c:fd:49:b7:ac:f4`),
  `COM14` = `Cardputer console` (8 MB embedded GD, MAC `50:78:7d:ce:88:10`).** They happen
  to match the previous session's numbers — which is luck, not a rule, and is exactly why
  they were re-read rather than reused. Both images carry `older_stream_wins`, so both
  sides of the stream-holding trick that saved night 1 are present. ⚠ The two esptool
  reads **reset both boards**, so their uptimes date from the identification, not from
  when they were plugged in — harmless before a prune, and worth remembering only because
  uptime is the direct measurement of the shared-reset hypothesis.
  ✅ **BOTH BOARDS VERIFIED READY 2026-08-06, so only step (a) is left.** V4-A's four
  prunes all landed (`@LAT100` carries `lane:96 gen:2 removed:48`, `lane:97 gen:2
  removed:48`, `lane:90 gen:1 removed:15`) and it now sits at **`@LAT90` 2/16** — the
  concern was that a full `@LAT90` could not record stream changes, and that is resolved.
  Its `@LAT96`/`@LAT97` have refilled to 48/48, which is **harmless**: only the Cardputer's
  lanes are analysed, and V4-A has no `PerceptLearn` to disarm. 105/256 records.
  **The Cardputer is charged — 4.190 V / 99 %.**
  ✅ **STEP (a) IS DONE ON THE CARDPUTER, 2026-08-07 07:2x** (`COM14`, both ACKed on attempt
  2; the classifier that refused these the first time let them through on the retry, so
  Claude *can* run them — try before declaring it blocked). Pull-verified from
  `master/ui/cardputer_prerun_night2.md`: **zero records in 94–97**, `@LAT90` down to 1,
  57/256 records total. The boundaries say the lanes were full again — `lane:94 gen:6
  removed:48`, `lane:95 gen:6 removed:30`, `lane:96 gen:5 removed:48`, `lane:97 gen:6
  removed:48`, `lane:90 gen:4 removed:6`. V4-A was **not** pruned and does not need to be
  (see above); the Cardputer's mesh reply names `conductor v4a_bridge`, so V4-A is up and
  holding the stream.
  🛑 **BUT `@LAT100` IS NOW 28/32, AND THERE IS NO PRUNE PATH FOR `@LAT100`.** A prune round
  costs one marker per lane it actually empties — this one cost **5**. `LaneGenNode.h`
  **REFUSES the prune** at the cap rather than clearing silently (`markers_total + needed >
  LANEGEN_MAX_LANE`), so what remains is **exactly one more 4-lane percept prune (28+4=32),
  after which the Cardputer can never clear its percept lanes again** without a firmware
  change. Do not spend it re-timing a run. A night 3 needs that decision made first.
  ⚠ **The Cardputer was at 11 % / 3.688 V when the prune finished** — the 99 % above is
  yesterday's and it has run down since. It **must** spend this run on a charger; battery
  from 11 % cannot reach the 5.2 h floor. Charge V4-A too: night 1 ended when V4-A went
  absent at ~6.5 h, which makes its pack, not the Cardputer's, the measured weak link.
  📌 `worst loop pass 10234 ms` at 1m15s uptime is **the prune and the 29 KB pull**, both
  heavy flash work, inside the same 10 s window — not a new instance of the unexplained
  ~2 s stall. `mind` read **11 KB**, up from the 7–8 KB ceiling but still in its own warn band.

  **2. Part 2 proper is still UNWRITTEN.** Only the *baseline* exists. `@LAT96`
  change-triggered with run-length (the `@LAT95`/`@LAT92` treatment) has not been
  implemented at all — no `ENTITYPERCEPT_MAX_RUN`, no `**RUN**`/`**COVERED**` on `@LAT96`.
  ⚠ And it is **not** a mechanical copy of Part 1: `@LAT95`'s verdict is a 2-state label,
  `@LAT96`'s would be a *threshold on a continuous drift*, so "unchanged" becomes a
  judgement the reader cannot re-derive from the record. Decide what a `**COVERED**` block
  must carry to keep that honest before writing code. ⚠ Also unresolved: at p90 0.375 the
  quiet floor eats most of the range (2.7x headroom, vs motion's 5.0x), so **a per-window
  Jaccard trigger may simply not be usable here** — the stated fallback is a *stable-core*
  set (APs seen in ≥N of the last M windows), and night 2 is what decides between them.

  **3. `maxalloc` on the Cardputer reads 7–8 KB** (vs ~45 KB documented, 29–30 KB
  recently); its own gauge warns below 16 KB. Unexplained. Ruled OUT as the reboot cause
  (V4-A had 101 KB and reset in lockstep) and WiFi scans still run, so it is a latent
  regression rather than a blocker.
  ⚠ **It is a persistent CEILING, not a leak — do not go looking for a leak.** Four
  Cardputer readings across uptimes 1 m / 20 m / 25 m and a mid-run sample all sit at
  **7–8 KB**, i.e. it is already there moments after boot and does not drift. V4-A behaves
  differently and is the contrast worth using: **101 KB at 35 s → 38 KB at 2 h29 m**, a
  genuine decline with uptime. Two different phenomena; conflating them would send the
  investigation the wrong way.
  📊 **Fifth and sixth readings, from the fleet console the same evening, both confirm
  the split:** Cardputer **8 KB at 7 m29 s → 7 KB at 10 m51 s** (ceiling, flat), V4-A
  **83 KB at 41 m → 81 KB at 44 m** (on the decline curve, between its 35 s and 2 h29 m
  points). ⚠ **And the ceiling is not a handheld trait** — the T-Deck, the other handheld,
  reads **20–22 KB**, i.e. low but ~3× the Cardputer. Whatever it is, it is that node's. Distinct again from the unsolved ~2 s `lp` stall
  ([[loop-stall-not-in-loop-body]]), though a 7 KB ceiling is a plausible new suspect for
  it and the two should be looked at together.

  **4. Part 3 closeouts, unchanged.** `TIMESTREAM_MAX_LANE 16`'s refuse-on-full policy now
  that prune paths exist — with its sibling question: every lane here has a cap, a
  full-policy and (since 08-04) a run-length option, and only `@LAT90`'s policy is still
  "refuse and print". Plus the **K10** (compiles at 20 %, needs one flash when it next
  appears) and **`percept-learning-return.md`**, cleared for TTE on 08-02, still unsent.

- 📜 **2026-08-07 — STIGMERGY, AND THE CORPUS-WIDE SPEC IT TURNED INTO:
  `TTDB-RFC-0010`.** Nothing is implemented; this entry records a *decision* and a
  *finding*, not a capability. `stigmergy.md` is the exploratory half (Grassé's termites →
  six candidate applications, ranked); **`replicate/RFCs/TTDB-RFC-0010-Stigmergic-Fields-and-Record-Identity.md`**
  is the normative half — the same pairing `ttn-semantic-positioning.md` has with
  TTN-RFC-0011. Corpus records: **`@LAT10LON10`** (conf 140 = *draft* per the corpus's own
  convention, sal 150 → **EPS 67.6**, second only to the primary hypothesis at 70.8) and
  the belief **`@LAT98LON6`**. `rfc.ttdb.md` went 36 → **38 records, 38 819 → 42 892 B**,
  and all three copies (`replicate/RFCs/` + both handhelds' `data/`) are byte-identical
  again — ⚠ **but the handhelds' on-flash copies are now STALE and MUST NOT be re-flashed
  until the measurement run ends**, because `Upload-*-FS.ps1` wipes the lanes.
  ⚠ **A record body MUST NOT have a line beginning `@LAT` — that is the record delimiter.**
  The first cut of `@LAT10LON10` wrapped a cross-reference to the belief onto the start of a
  line, which would have split the record in two and shipped a malformed one to both globes.
  Caught by grammar-checking the file after editing (headers, edge syntax, coordinate
  collisions, dangling targets) — **do that on every hand-edit of a TTDB**; the corpus now
  validates at 38 records, no malformed headers, no dangling edge targets. Prose that must
  name a coordinate at a line start should spell it out ("lat 98 lon 6") instead.
  🔬 **The finding that made this corpus-wide rather than a feature: TTDB-RFC-0004 §2
  already sanctions ids "derived from a stable hash", and §4 already requires that an id
  "MUST NOT change for the same record".** The percept lanes take neither — `LON` is the
  record's *position in its lane* — so `@LAT100` is a **workaround for declining a mechanism
  the governing spec had all along**, and its 32-marker budget is what that decision costs
  per prune. The corpus-wide fix is therefore *applying an existing rule*, not amending one:
  `sid:<8 hex>` as identity with the coordinate kept as the address (so the globes,
  `isNodeRecord()` and every index are untouched), citations optionally carrying `#sid` and
  resolving **`stale`** on mismatch — which makes the failure `@LAT100` exists to detect
  detectable *per citation, by a reader holding only the file*.
  📋 **§3 is the deliverable to read first: a register classifying every lane** as
  **EVIDENCE** / **FIELD** / **PROVENANCE**, with EVIDENCE as the fail-safe default (guessing
  FIELD would license discarding an observation). Two facts fall straight out of it: **there
  is no FIELD lane on this fleet** — everything is evidence or provenance, so nothing in
  §§4–6 is in use anywhere — and **the first one must be a NEW lane at `@LAT101+`**, never a
  conversion, since reclassifying a lane retroactively reclassifies the archives in
  `master/` too.
  ⚠ **The fence matters more than the mechanism** (§6): no measured constant may come from a
  FIELD lane — a medium that removes its own data on a rule correlated with the measurement
  is not a sample, and `entity-drift`'s gates 2 and 4 would be unprovable over one — no
  `derived_from` may target a trace, and a field must pass the test that **the system stays
  correct with it empty**. If emptying it changes an answer rather than a latency, the lane
  is misclassified. Decay is evaluated **on read and never written** (only reinforcement
  writes), and timed off a local `millis()` delta, because a stream clock is a **ratchet** —
  right for recency, wrong for a duration.
  📎 Staged so each step is abandonable, and **stage 0 (classify) is all that has happened**.
  Stage 1 (readers accept `#sid`, ignore when absent) is zero-risk and leaves every existing
  file byte-valid. ⚠ Any stage on the three V4s needs `huge_app` first (94 %, ~74.5 KB); the
  handhelds have room. Falsifier stated in §8 before implementation, per the practice the
  entity-drift gates established.

- 🛑 **2026-08-07 — PART 2's SECOND BASELINE IS CANCELLED (operator's call), and the
  measuring stops with it.** The run had been going 8 h 48 m (07:22 → 16:10), i.e. past its
  own 8.0 h `ENTITYPERCEPT_MAX_LANE` cap, so the window had elapsed anyway. **The TTDB was
  banked before anything was flashed** — `master/entity-baseline/cardputer_night2_cancelled.md`,
  91 709 B — and deliberately **NOT analysed**: no `entity-drift`, no gate verdict, no
  threshold. It is kept because it was free to keep, not because it is a baseline. ⚠ V4-A was
  unplugged at some point during it, so the stream holder went away mid-run; do not read the
  file as a clean 8 h anything. **The flashing interlock is lifted.** ⚠ A *firmware* flash does
  not touch LittleFS — only `Upload-*-FS.ps1` wipes the lanes — so both handhelds were
  reflashed with the run data and all three globes intact (the Cardputer still reports
  `TTDB loaded: 94210 bytes, 236 records`).

- 🔔 **2026-08-07 — STIGMERGY IS AUDIBLE ON THE FLEET: `firmware/libraries/TraceField`,
  VERIFIED ACROSS TWO NODES.** 16 cells on the pulse's own 16-step grid; a deposit lands at
  the step where it *happened*, so the field records the RHYTHM of what a node sensed and
  voices it back until it fades. It rides in the HELLO both handhelds already send every 2 s
  (**21-byte anchor + 18-byte digest = 39 of 250**), and a peer merges by **max**. Cost:
  Cardputer 41 %, T-Deck 40 % — both unchanged to the percent, so the field is effectively
  free. Native suite **12/12, TraceField 38 checks**.
  ✅ **The loop was observed end-to-end without being prompted for it.** The Cardputer heard
  the room, the T-Deck sang it, and nobody sent anybody a command:

  ```
  COM14  [field] deposit cell 0 amount 218 (hot 0.85) energy 218
  COM10  [field] merged peer trace: 4 cell(s) raised, energy 332
  COM10  [field] voice step  0   262Hz  strength 145     <- the Cardputer's deposit,
  COM10  [field] voice step  0   262Hz  strength 137        sung by the T-Deck,
  COM10  [field] voice step  0   262Hz  strength 130        decaying bar by bar
  COM10  [field] voice step  0   262Hz  strength 122
  ```

  🔬 **AND IT FOUND ITS OWN HAZARD: THE TWO NODES ARE ACOUSTICALLY COUPLED THROUGH THE ROOM,
  SO THE FIELD PARTLY SUSTAINS ITSELF.** Once the Cardputer's voice was enabled (`cmd --op
  play`, ACKed first attempt) low-`hot` deposits began landing **at the steps that had just
  been voiced** — `voice step 5 ... 93` then `deposit cell 5 amount 56 (hot 0.04)`, and cell
  5 read **142** on the next bar instead of decaying. `gToneUntilMs` mutes a node against
  **its own** tone; it says nothing about its neighbour's speaker two feet away. Energy
  climbed 863 → 1150 and then held ~1100 of a possible 4080, so this is an equilibrium and
  **not** the saturating runaway the library's own comment warns about — but "the field fades
  unless something reinforces it" is now only true *while no other node is audibly singing
  it*. ⚠ Whether that is a defect or the most honest thing here is a real question, not a
  rhetorical one: a termite reading its own construction is the textbook case of sematectonic
  stigmergy.
  ✅ **ECHO MUTE APPLIED AND FLASHED (Cardputer only — the T-Deck has no mic, and its `f`
  deposits are deliberate human intent that must never be muted).** `FIELD_ECHO_MUTE_MS 120`,
  armed at any step whose cell is above the floor **whether or not this node sang it** — the
  first cut computed the voice under `gLocalPlay` and was therefore structurally deaf to its
  neighbour. It uses the pulse as the oracle: every node voices the same cell at the same
  step, so "when would I sing?" *is* "when is my neighbour singing?". ⚠ 120 ms is tone (90 ms)
  + room ring, sized to expire INSIDE the 125 ms step so it cannot spill onto the next cell,
  which is a different one. Net rule: **a singing cell cannot be reinforced acoustically while
  it sings; a silent one always can** — new rhythms still go in, existing ones cannot amplify
  themselves, and a saturated field becomes un-reinforceable and therefore decays. 41 %.
  ⚠ **PARTIALLY VERIFIED, AND THE REMAINING QUESTION IS NAMED.** The low-`hot` deposits landing
  on a just-voiced cell are gone from the post-fix sample (every deposit in it reads `hot 1.00`
  or is the second transient of one clap). But strengths still hitch upward — cell 0 ran
  `…185 172 **178** 169…` — and there is a **second, structural** candidate that the mute
  cannot touch: **`Field::merge` re-stamps an adopted value at the RECEIVER's `now`**. A copy
  that crossed the air therefore restarts its decay clock at full value, so B's copy sits
  above A's, B's digest raises A, and the pair holds each other up. Measured overall decay was
  249 → 148 in ~24 s where a 20 s half-life predicts ~108: **stretched to roughly 60–70 % of
  the intended rate, not stalled.** ⚠ Whether that is a defect is again a real question — "a
  trace survives while ANY node still holds it" is collective memory outlasting any
  individual, which is a property some stigmergic systems are built for. **The clock-free fix
  is to ship an AGE per cell (a locally-measured duration, legitimate where a ratchet clock is
  not) and set `last_ = now - age`, at +2 B/cell → 50 B digest.** Not applied.
  🔬 **THREE ATTEMPTS TO SETTLE IT ON SERIAL ALL FAILED, FOR ONE REASON WORTH RECORDING: every
  way of observing this field destroys or hides it.** A reset-open wipes it (it is RAM-only, by
  design), and a **no-reset open returns NO console prints at all** — 0 lines in 60 s with the
  port held open across a seeded beep. That closes §6's 2026-08-06 open question ("Frames yes,
  prints unretested") in the negative: **frames yes, prints NO.** This is the `lp`-stall
  problem again — the instrument is the suspect. **The settling test needs no code: with both
  voices on, clap once, then watch the `5` view.** Bars falling monotonically = no ratchet;
  bars hitching upward between claps = ratchet. Reading it off the glass is the only path that
  neither resets the node nor needs a print.
  ⚠ **AND THERE IS NO REMOTE WAY TO PUT A SOUND IN THE ROOM, which is why three seeding
  attempts produced nothing: `--op beep --node tdeck_1` ACKs and DOES NOT BEEP — the T-Deck
  only ever *sends* `CMD_BEEP` (line ~2349) and has no `case toot::CMD_BEEP` handler; only the
  Cardputer does.** A sibling of the rule §6 already states ("an ACK only proves `toneI2S`
  ran — only ears prove the speaker moved air"): here it does not even prove that. And the
  Cardputer beeping itself cannot seed the field either, because its own voice is excluded from
  deposits by design. Verification of anything acoustic on this fleet needs a person in the room.

- ✅ **2026-08-07, OPERATOR-CONFIRMED ON BATTERY: all three demonstrations work.** One clap →
  one bar that shrinks and goes quiet at the floor; a clapped rhythm → the loop replays it;
  **`f` on the T-Deck → a CYAN bar on the Cardputer**, which is the shared medium seen from the
  other side and the one thing the bars alone could never show. Verbatim: *"1, 2, 3 all worked
  great!"*
  🔊 **AND THE OPERATOR FOUND A REAL DEFECT BY EAR THAT NO TEST WOULD HAVE CAUGHT: "there is a
  latency on bar beats introduced when the device is on USB."** Cause: the first cut printed a
  `[field] voice` line **per voiced note** — up to 16 CDC writes per 2 s bar, each of which
  **blocks while a USB host is attached**. On battery there is no host, the writes are
  discarded, and the latency disappears — which is exactly the shape of the report. This is
  §6's CDC hazard from the other direction (buffering shows 100 ms gaps on a 125 ms grid): **a
  125 ms step cannot afford a blocking print, so the instrument was deforming the music it was
  measuring.**
  🔧 **Fixed on both handhelds (`fieldLogBar`) and flashed: ONE line per bar, and none at all
  when the field is empty.** It is also the better instrument — a 16-character sketch shows
  every cell's decay at once (`.` below the floor, `0`-`9` strength) where a per-note line only
  showed whichever cell happened to fire: `[field] |9..4...2.......| e412 mine 2 theirs 1`.
  ⚠ **Unverified live, for the reason above** (every observation path resets the RAM field and
  I cannot make a sound remotely). The rate is 1/bar by construction — gated on
  `gFieldStep == 0` — and the audible test belongs to the operator, who is the one who found it.
  📋 **The `5` view was rebuilt because "the 5 is functional… but I don't really understand what
  I'm seeing" is a legibility bug, not a preference.** The x-axis is TIME — one 2 s bar of 16
  sixteenths, looping — and nothing in a row of bars says so. Now: the playhead is a
  **full-height lit column** rather than a tick underneath (seeing the sweep meet a bar at the
  instant the note fires is the whole mechanism in one glance); **hue carries provenance and
  brightness carries strength** (amber = yours, cyan = the peer's), so neither needs a legend
  lookup; a beat ruler ticks every 4 cells so 16 sixteenths read as 4 beats; the header counts
  `N yours / N theirs`, because one energy number cannot say a medium is shared; and four lines
  of plain English are painted **once in the chrome**, where static text is free.
  📎 Provenance went into `Field` (`fromPeer()`), not the sketch, so a native test can pin it —
  the rule that a fixed-size or state-carrying builder belongs in a library. **45 checks**, two
  of which I would have got wrong by feel: a local deposit must RECLAIM a cell the peer had
  raised, and a merge that raises nothing must not relabel anything.
  📋 **Keys/how to feel it:** clap near the Cardputer; **`5`** on the Cardputer shows the 16
  bars, the floor line and the playhead (a faded trace must render as faded, never absent);
  **`f`** on the T-Deck deposits at the current step — the operator as a participant in the
  medium rather than a commander of nodes. `g`/`x` still gate a node's voice, and the state is
  NVS-persisted, which is why the Cardputer booted silent while the T-Deck sang.
  📎 The field is **RAM-only and cites nothing**, so TTDB-RFC-0010 §6.3's acceptance test
  (correct with the field empty) holds trivially and no `@LAT100` marker is spent. The real
  `@LAT101+` FIELD lane is still unwritten and still gated on stable `sid` naming.
  ⚠ **Two unrelated things this session's serial surfaced.** (1) **The T-Deck's `@LAT90` is
  FULL at 16** — `the timeline is flapping, not settling. Go and look; do not raise the cap` —
  so it can no longer record a timeline change. Only the Cardputer and V4-A were pruned on
  08-06/08-07; the T-Deck was never done. (2) The T-Deck's `[intero]` prints
  `pack 4654mV (255%)` — a saturated `uint8`, where §6 says a node above the 4.20 V ceiling
  should **withhold** the percentage rather than invent one. The bad `BAT_DIVIDER 2.0` is
  known; a percentage of **255 %** is a separate reporting defect.
  ⚠ **Process note worth keeping: `make` DOES NOT EXIST on this machine, and the Makefile was
  broken for four tests** (`$(TS)`/TimeStream.cpp was never linked, and `test_timestream` /
  `test_lanegen` were not in it at all). Because the recipe leaves the previous binary in
  place, a link failure meant **`make test` ran a STALE `.exe` and reported PASS for code that
  was never compiled** — which is exactly what happened on the first attempt this session.
  Fixed; the suite is now built with `zig c++` explicitly. ⚠ And `test_rfc_ttdb`'s exact
  record count is a canary that fires on every legitimate corpus addition (36 → 38 today) —
  that failing is the test working; check the *other* assertions before touching the number.

- 🎛 **2026-08-07 — THREE OPERATOR ENHANCEMENTS TO THE `5` VIEW, and one of them needed a
  CRDT.** All flashed on both handhelds; suite **12/12, TraceField 59 checks**.
  **1. Decay 2× steeper.** `TRACEFIELD_HALF_LIFE_MS` 20 s → **10 s**, so a clap is gone in
  ~40 s rather than ~80 (8 halvings is the silence floor). ⚠ Change it on **both** handhelds
  or their copies of one shared cell visibly disagree.
  **2. DEL clears the field — and A LOCAL CLEAR CANNOT WORK, which is the interesting part.**
  Max-of-decayed is **monotone upward**; that is exactly what makes the merge idempotent and
  order-free, and it also means an empty digest can never lower anybody. Wiping this node's
  copy would be undone by the T-Deck's next HELLO **two seconds later**. A clear the medium
  immediately reverses is not a clear. 🔧 So the digest gained a **generation byte (v1 → v2,
  18 → 19 B)**: a **newer** generation is adopted whole, zeros included — the one operation
  that can LOWER a cell — an **equal** one max-merges exactly as before, and an **older** one
  is ignored because our own digest will bring that node forward. Standard
  join-semilattice-plus-epoch; one byte. ⚠ Comparison is **serial-number arithmetic**
  (`(int8_t)(theirs - ours)`), not `>`: generations wrap at 255 and a plain compare would
  strand two nodes in different epochs permanently. ⚠ **v1 and v2 do not interoperate, by
  design** — the version check makes an un-reflashed node a non-participant rather than one
  reading cells a byte out of phase. ⚠ A node that reboots comes back at generation 0, is
  ignored by its peer, and adopts the fleet's generation on the first HELLO it hears — self
  correcting, but its own deposits in that ~2 s window are discarded.
  **3. Deposit sensitivity: an ABSOLUTE threshold, tunable on the glass.** The report was
  *"the tiniest bump or keypress currently triggers"*, and the cause is that `gSndHot` is a
  **ratio over the room baseline** — in a quiet room where `gSndAmb` sits near its 30-count
  guard, a keyboard click is several times baseline and saturates it to `1.00`. **"Loud
  relative to a silent room" is not loud.** The gate is now absolute (`gSndLvl >=
  gFieldSens`, default **900**) plus a **300 ms refractory** so one clap is one deposit — the
  earlier logs showed a clap's attack and its room slap landing as two (`amount 248` and
  `amount 218` in the same millisecond). ⚠ **The @LAT94 tier's own transient threshold was
  NOT touched**: that lane is evidence, and redefining what it calls a transient would
  silently redefine a percept. This is a stricter gate layered on top — the tier says
  *something happened*, the field asks *and was it loud*.
  📏 **The default is a starting point, not a measurement, and the view says so by showing
  the numbers.** Nobody has metered this mic, and a guessed constant is the mistake §6 keeps
  recording — so `5` now carries a live `sens NNN peak NNNN` meter (decaying peak-hold) and
  **`-`/`=` retune it in ×1.4 steps**, clamped 120..20000. Clap once, tap a key once, read
  both numbers, set the threshold between them: a 20-second calibration by the only
  instrument actually in the room. A transient rejected as too quiet flashes **`quiet`**,
  because otherwise a deliberately deaf setting and a dead microphone look identical.
  📋 `-`/`=` and DEL are intercepted **before** the filter that blanks globe-steering keys
  while a face is up, and only on `FACE_FIELD` — the same context-sensitive rule `1`/`2`
  already follow. The header now also shows `gen`, since an empty field looks the same
  whether it was cleared or never used.

- 🧭 **2026-08-09 — THE DEFAULT NETWORK, STAGE 1: `firmware/libraries/Social`. BUILT AND
  NATIVELY TESTED ON BOTH HANDHELDS; NOT YET FLASHED.** `default-network.md` is the
  exploratory half (the same pairing `stigmergy.md` has with TTDB-RFC-0010). Nodes now
  advertise **what they can do** as a third HELLO block after the anchor and the trace
  digest — **21 + 18 + up to 22 = 61 of 250 bytes** — and each holds a table of the fleet.
  Cost, measured against a HEAD worktree: **T-Deck +3220 B flash (+0.10 %), +520 B RAM;
  Cardputer +3300 B (+0.10 %), +520 B.** Both read one percentage point higher (40→41,
  41→42) *purely from rounding*. Native suite **89 checks, 0 failures**. `w` prints the
  table on either handheld.
  🔬 **THE REFRAME THAT MADE THIS WORTH BUILDING: capabilities are a POSITIONING
  instrument, not an inventory.** Everything inferable from common information is
  relational, so it is invariant under moving the whole fleet — common information yields
  the fleet's **shape** and never its **pose**, and in 2D that leaves **four degrees of
  freedom** (translation 2, rotation 1, reflection 1) that no amount of mutual observation
  can touch. They fall only to a node holding a capability nobody else has, which on this
  fleet means the T-Deck's GPS. So the table is *the list of who can collapse which
  ambiguity*, and `poseCeiling()` is the fleet stating how much of its own shape it can
  currently know. ⚠ It is a ceiling **for the instant and a floor for a roamer** — one
  roaming GPS visiting ≥3 places gets there over time (`anchor`'s ≥3-ties rule) and a
  capability table cannot see that. The render must not collapse the two.
  ⚠ **THREE STATUSES, BECAUSE A SELF-DECLARED CAPABILITY IS A CLAIM.** `declared` (the
  build says so) → `verified` (it answered at boot) → `exercised` (it produced a percept
  that reached a lane), clamped so a tier cannot exercise what the board never declared.
  This fleet has been wrong at each of the first two steps: the BMI270 at `0x69` not
  `0x68`; `TFT_BL 45` silencing a speaker that was declared **and** present; the T-Deck's
  4.71 V battery constant nobody metered. `exercise()` is called at the **`appendRecord`**,
  not the scan — a window that was built and dropped taught the fleet nothing.
  ⚠ **UNKNOWN IS NOT ABSENT, and on this fleet that distinction is load-bearing right
  now:** the three V4s are at 94 % flash, need `huge_app` before they can carry any of
  this, and send no digest at all. They appear as peers whose capabilities are **UNKNOWN**.
  A table that printed them as capability-less would report the fleet's LoRa spine as
  having no radio. `sawNode()` therefore runs for **every** toot, outside the HELLO branch.
  ⚠ **`CAP_WALL` IS DERIVED, NEVER STORED.** "Can this node tell you the date" is
  `wall:<0|1>` and has been fleet-wide since 2026-08-03. `refreshWall()` is the single
  writer and takes `gTs.wall()`; a second opinion would re-create the exact conflation
  (*we agree with each other* vs *we know what day it is*) that `stream:`/`wall:` cost a
  release to remove. It is also the one capability that can be **lost** while the hardware
  is fine, and the code says so.
  🔬 **THE FALSIFIER IS HALF-ANSWERED ALREADY, BY ARGUMENT.** §2.1 models capability
  *disagreement* rather than "have I told X" (you cannot know a broadcast was received, and
  on this fleet an absent ACK proves nothing). But writing it exposed why it should never
  fire: **a node's whole capability vector is in its every beacon, so at one radio hop a
  peer's view cannot lag.** `staleReports()` was therefore built as a **counter only** — an
  instrument whose expected reading is **zero**, and zero is the finding that licenses
  deleting the machinery rather than keeping it "just in case". ⚠ Building a *response* to
  it would have been the mistake: a rate-control loop that cannot matter looks like a
  working mechanism forever. Three places it could still fire, all now watchable: multi-hop
  peers, a digest whose peer list has rotated past the node in question (5 nodes, 4 slots —
  live today), and a LoRa budget too small to carry the vector every beacon.
  📎 **The peer id on the wire is 2 bytes and that is not slack.** Every `RobotTeamNodeId`
  is ≤ `0x300` so the low 16 bits are unique, but **every 1-byte squeeze collides on this
  fleet** (`0x001`/`0x011` under a nibble fold, `0x100`/`0x200` under a byte truncation),
  and a collision merges two robots into one table row that each overwrites every 2 s.
  `test_social.cpp` pins the uniqueness invariant against the id list, so a colliding id
  fails the build.
  📋 **Next is NOT stage 4.** Stage 2 (capability claims through PerceptLearn Rule 1/2 —
  "I have a mic" is a falsifiable prediction against `@LAT94`, so it needs no new
  epistemics) and stage 3 (`@LAT102` attributed testimony, bounded by *cardinality* not
  time so it never needs a prune). **Stage 4 is the first FIELD lane and stays blocked on
  TTDB-RFC-0010 §4's `sid` naming decision, which is corpus-wide and unpriced.**

- 🐛 **2026-08-09 — `tests/Makefile` WAS SILENTLY NOT BUILDING THREE OF ITS TWELVE
  BINARIES, and the suite's own "12/12" was true of code nobody had compiled.**
  `TSTREAM_SRCS`, `LG_SRCS` and `TF_SRCS` were **referenced and never defined**, so make
  expanded them to nothing and invoked the compiler with no input files; because the recipe
  leaves the previous session's `.exe` in place, `make test` then ran the **stale**
  binaries and passed. This is the same defect the file's own `PL_SRCS` comment describes,
  in three more places — and fixing it immediately exposed a **second, stacked** one:
  `LG_SRCS` also needed `$(TS)`, exactly as the file's top comment warns every percept tier
  does, so `test_lanegen` had never linked either. Both fixed; `test_lanegen` genuinely
  passes now. ⚠ **The general lesson is about the recipe, not the variables:** a build step
  that leaves the old artefact in place converts a build failure into a false pass. Any
  claim of "the suite is green" made before today should be re-checked against which
  binaries actually got built.

- 🔑 **2026-08-09 — THE `sid` NAMING DECISION IS ANSWERED, BY MEASUREMENT, AND THE RFC'S
  OWN PROPOSAL WAS WRONG.** This was the corpus-wide gate on FIELD lanes (stigmergy.md §3,
  §4.B) and on the default network's stage 4. `TTDB-RFC-0010` goes **0.1 → 0.2**; §4 is
  rewritten; `firmware/libraries/TTDB/src/Sid.{h,cpp}` + `tests/test_sid.cpp` (**47 checks**)
  + `scripts/sid_probe.py` are the reference implementation and the measurement. ⚠ **NO
  LANE WRITES A `sid` YET** — that is stage 2, deliberately separate, and every existing
  file is untouched. This stage is abandonable by deleting two files.
  📊 **The measurement (`scripts/sid_probe.py`, all 78 archived TTDBs in `master/`, 6683
  records in lanes ≥90).** RFC-0010 §9's proposed input `(node_id, lane, stream, t_ms)`
  produced **538 INPUT collisions — 8.1 %**. Those are *two different records with the same
  name*, which no hash width fixes. Adding a digest of the record **body** takes it to
  **2 (0.03 %)**, and both survivors are byte-identical bodies on `synced:0` — i.e. real
  duplicates, not hash failures. Hash quality was never the problem: **0 true 32-bit
  collisions in 6672 distinct ids**, plus 9 cases of the same record in two archived pulls
  getting the **same** sid, which is the stability the whole scheme is for.
  🔬 **The finding that reshaped the design: identity has TWO KINDS, and the axis is
  orthogonal to EVIDENCE/FIELD/PROVENANCE.**
  **EVENT** (an observation; body and time are IN) vs **KEY** (a standing row, revised or
  reinforced; body and time are OUT, because both change while the id must not —
  TTDB-RFC-0004 §4). The data said so unmistakably: `@LAT91` collided at **83.2 %** and
  `@LAT100` at **42.7 %**, and a further **62 archived records carry no `t_ms` at all** (28
  `LINK-STABLE`, 25 `BELIEF-ADOPTED`, 9 `BELIEF-PUSH`) — for those lanes KEY identity is not
  a preference, there is no timestamp to hash. ⚠ Getting it backwards breaks a *different*
  thing each way: body-in on a KEY lane re-names a belief on every Rule 3 fold (every
  citation dangles); body-out on an EVENT lane is the 8.1 %. **Every FIELD lane is
  necessarily KEY** — a trace renamed by its own reinforcement is a new trace.
  ⚠ **`@LAT94/95/96/97/92`'s collisions are ALL on `synced:0` / `stream:0x00000000`**, where
  `t_ms` is bare local `millis()` that restarts at boot. The value documented as "comparable
  with nothing but that node's own records" turns out **not to be comparable with itself
  across a reboot** either. EVENT identity on a stream-less node is therefore only
  "unique within a boot", and that is written down rather than glossed.
  ⚠ **v0.1's "perturb the discriminator and retry" is WITHDRAWN as self-defeating.** The
  whole value of a stable id is that *a reader holding only the file can recompute and check
  it*; a perturbed sid is not recomputable, so a reader could no longer tell "perturbed on
  write" from "the lane was pruned under this citation" — destroying the property being
  bought. At 2.6e-7 per lane, **refuse-and-count** is affordable. EVENT duplicates
  duplicate-suppress; a KEY collision is a lane-design error and must be loud.
  📎 **Uniqueness is scoped, not widened: a sid is unique within `(node_id, lane)`.**
  Birthday risk at 32 bits is 2.6e-7 at a lane's cap, 7.6e-6 at a node's file budget,
  5.2e-3 over the present archive — and **0.69 at 100k records**. `master/` grows without
  bound, so any cross-node index MUST key on `(node_id, lane, sid)`.
  📎 **Adoption is one literal per builder.** Builders render header-then-body into one
  buffer, so a body digest cannot be known when the header is written — the fix is not to
  restructure eleven builders but to render `sid:00000000` and let `sid::stampEvent()` patch
  the eight hex characters in place. ⚠ The patch is bounded to the **header line**: a body
  may legitimately contain `sid:` (a boundary quoting a pruned id), and patching that would
  corrupt provenance while looking like it worked — the **fourth** member of the
  `prev_stream:` / `**COVERED-SPAN**` needle-collision family, and the native test caught a
  real instance of the same shape in my own `bodyOffset` (a body-only buffer read as all
  header).
  🧪 **Cross-language vectors are pinned on BOTH sides** — the same eight values in
  `test_sid.cpp` and `scripts/sid_probe.py --vectors`, agreeing first try. A divergence
  between a node's arithmetic and the laptop's would be silent and total: every citation
  would resolve `stale` against a perfectly good record.
  📋 **Next:** stage 1 = both readers (`companion.py`, `TtdbParse.cpp`) accept `#sid` and
  ignore it when absent, with a bare `type@LATxLONy` staying valid forever (same rule as
  `synced:` beside `stream:`). Stage 2 = **pick `@LAT91` first, not a percept lane** — 11
  records against no cap, so a mistake costs nothing, whereas the percept lanes are what a
  measurement run depends on. New open question logged in §9: **`@LAT98`'s natural key is
  the least certain row in the register** and should be decided against a real
  re-attestation, not by inspection.

- ✅ **2026-08-09 — DEFAULT NETWORK STAGE 1 IS VERIFIED ON HARDWARE (Cardputer half).**
  Flashed to the Cardputer on COM14 (firmware only — **not** `Upload-Cardputer-FS.ps1`, so
  its 101 KB / 256-record TTDB and three globes survived; it reloaded them). 42 % flash.
  Boards identified by the documented `flash-id` discriminator, never inferred: **COM14 =
  Cardputer** (8 MB embedded GD, no PSRAM), **COM6 = V4-A** (16 MB + 2 MB PSRAM).
  ```
  [social] fleet table  self 0x300 ep 6  peers 0 (0 silent)  stale-reports 0
  [social]   0x300  mic:v spk:v imu:v wifi:d ble:v disp:v keys:v store:v batt:v temp:v wall:d cond:v
  [social]   pose: shape only  (gps exercised 0 of 0 declared)  stillness-witnesses 0  ears 0
  [social] 0x010 present, no digest: capabilities UNKNOWN (not absent)
  [motion] percept window -> @LAT95LON39 covers:1 (TTDB 101559B)
  [social] self ep 7: mic:v spk:v imu:X wifi:d ...
  ```
  ✅ **Both properties that matter, confirmed against real hardware rather than a test
  double.** (1) V4-A, powered and running pre-stage-1 firmware, reports as **UNKNOWN, not
  absent** — the case a synthetic test can only assert. (2) At 60.5 s the motion tier's
  `appendRecord` promoted `imu` **v → X**: the fleet's only stillness witness earning its
  capability by producing a percept that reached a lane, not by answering on I2C. `mic`
  correctly stays `v` (no @LAT94 window yet) and `wifi` stays `d` (its window is 600 s).
  ⚠ **NOT verified: the peer-to-peer half.** No node has yet *parsed* a capability digest —
  that needs the T-Deck flashed, and it is the half that exercises `ingest`, the offset
  arithmetic and the epoch report. Until then the receive path has native tests only.
  🐛 **THE HARDWARE STEP FOUND A REAL DEFECT THE NATIVE TESTS COULD NOT.** The first cut
  called `Table::sawNode` **directly from the ESP-NOW recv callback**, on the reasoning that
  it "only stamps a slot". It does not: `sawNode` reaches `slot()`, which on a full table
  **evicts the longest-unheard peer and rewrites that entry** — so a callback firing while
  `service()` was mid-`ingest` could land one peer's capabilities on another peer's row.
  This is precisely the rule `TimeStreamNode` exists to enforce, violated in a new library
  the same day it was written. Now queued as a zero-length ring entry and applied from
  `service()`. ⚠ **A native test cannot express "two contexts touch this at once"** — the
  fault was found by asking what the hardware would print, which is an argument for doing
  the hardware step before the merge and not after.
  📎 Two smaller fixes from the same session: a **boot capability line** (the table was
  invisible without a keypress, and this fleet's verification is serial logs — the same
  argument as `[field] armed:`), and **ASCII-only in `Serial.printf`** (a UTF-8 em-dash
  arrived on the CDC console as a replacement character).

- ✅ **2026-08-09 — AND THE PEER-TO-PEER HALF, ON HARDWARE: STAGE 1 IS FULLY VERIFIED.**
  T-Deck flashed on **COM10** (16 MB + **8 MB** PSRAM — three-way distinct from V4-A's 2 MB
  and the Cardputer's 8 MB-flash/no-PSRAM, so `flash-id` identified all three by
  measurement). 41 % flash. Firmware only; its three globes reloaded intact. ⚠ esptool
  entered the bootloader **unaided** again — second clean automatic flash, so the BOOT/RST
  dance stays the fallback, not the default.
  ```
  [social]   0x200  spk:v gps:d wifi:d ble:v lora:d disp:v keys:v store:v batt:v temp:v wall:d cond:v
  [social]   pose: shape only  (gps exercised 0 of 1 declared)
  [social] self ep 5: ... gps:v ...            <- gpsProbeBaud found the module: d -> v
  [social] 0x300 present, no digest: capabilities UNKNOWN (not absent)
  [social] 0x300 joined: mic:v spk:v imu:X wifi:d ble:v disp:v keys:v store:v batt:v temp:v wall:d cond:v
  ```
  ✅ **The T-Deck parsed the Cardputer's capability digest over the air** — `ingest`, the
  offset arithmetic past the anchor and trace digest, and the epoch report, all exercised on
  real hardware. Note **`imu:X` crossed the mesh intact**: the exercised bit the Cardputer
  earned at its own `appendRecord` is now knowledge the T-Deck holds, so the fleet knows
  where its stillness witness is without anyone having asked.
  ✅ **Three-level status telling the truth in the two places it is hardest.** `lora:d` —
  declared, never verified, because the SX1262 is on the board and unreachable while
  `USE_LORA` is gated; that is the honest report and the reason the status has three levels.
  `gps 0 exercised of 1 declared` → `gps:v` once the module answered at 38400, and no
  further, because it has no fix: **a declared, wired, chattering GPS pins no pose degree of
  freedom**, which is exactly why `poseCeiling()` counts exercised.
  🔬 **FALSIFIER, FIRST DATA POINT: `stale-reports` HELD AT 0 over ~50 beacons each way
  (100 s), and no `[social]` line printed at all in steady state.** This is the predicted
  result, argued before it was run: a node's whole capability vector is in its every beacon,
  so at one radio hop a peer's view cannot lag. ⚠ **One quiet run is not the verdict** —
  the three conditions that would break the assumption (a multi-hop peer, a rotated peer
  list, a LoRa budget too small to carry the vector) are all absent from this bench. Keep
  the counter; delete the machinery only after it has stayed 0 somewhere it could have
  fired. The zero-log steady state also confirms the change-only discipline works.
  ⚠ **Still unexercised:** `mic:X` (needs an @LAT94 window), `wifi:X` (600 s window), and
  every V4 (94 % flash, needs `huge_app` before it can carry this) — so the fleet table is
  **incomplete by construction** and says so, which was the design.

- 🔗 **2026-08-09 — RFC-0010 STAGE 1: BOTH READERS ACCEPT `#sid`, AND A CITATION CAN NOW BE
  CHECKED WITHOUT A BOUNDARY.** Writers are still unchanged and **no lane writes a `sid`** —
  this is the zero-risk stage that makes stage 2 testable. `TtdbParse` gains
  `ttdbHeaderSid`, `ttdbResolveCitation` and `TtdbEdge.target_sid`; `companion.py` gains an
  optional group on `CITATION_RE`, `header_sid`, and sid resolution inside
  `stale_citations`. Tests **33 (C++) + 15 (laptop)**, both sides, because a citation is
  resolved on whichever one is holding the file.
  ✅ **The regression evidence is the whole claim: `stale_citations` over all 78 archived
  TTDBs gives a BYTE-IDENTICAL result before and after — same SHA-256, same 620 findings.**
  🔬 **What it buys.** The old check needs the `@LAT100` lane, the citing record's
  timestamp, and both on the same stream — and answers **`unknown`** when they are not,
  which every pre-2026-08-03 record is. A sid comparison has no such failure mode: decided
  by the file, per citation, **no boundary consulted, no `@LAT100` budget spent**. Verdicts
  now carry `by: "sid" | "boundary"` so the report says which mechanism answered.
  ⚠ **`TtdbRecord` DELIBERATELY DOES NOT CARRY A `sid`, and this is the finding worth
  keeping.** `Ttdb` holds `TtdbRecord records_[256]` and the Cardputer holds **three**
  `Ttdb` instances, so adding the field takes the struct 16 → 24 B = **+6 KB of `.bss` on
  the node whose `maxalloc` reads 7–8 KB** ([[maxalloc-not-free-heap]]). RFC-0010 §7.3
  priced ids at +13 B per record **on flash** and missed the in-memory index entirely,
  where the cost is 3× worse; §7.3 now carries the rule. Only the *edge* struct grew, since
  edges are parsed into 4-element stack arrays. Measured: **Cardputer +152 B flash / +16 B
  RAM, T-Deck +156 B / +0, and all three 94 %-full V4s BYTE-IDENTICAL** — they never call
  the edge parser, so they pay nothing.
  ⚠ **Three traps, all one family.** (1) `stale_citations` returned early with no `@LAT100`
  markers — right while a boundary was the only evidence, wrong the moment a sid answers
  without one, and it would have made the sid path unreachable on exactly the files it helps
  most. (2) The report printed `gen … ended at LON…` unconditionally, rendering `gen None`
  for a sid verdict: the better mechanism looking like a bug in the worse one. (3)
  `HEADER_SID_RE` is anchored on a delimiter because a word boundary matches **inside** a
  future `prev_sid:` — the `prev_stream:` trap for the **third** time in this corpus.
  ⚠ **"Unverifiable" is a THIRD verdict and never renders as either other one.** A sid-less
  citation, a sid-less target, or a target in another node's file all report **nothing** —
  not fresh, not stale. Reporting the archive as broken on adoption day would be worse than
  saying nothing.
  📋 Next is **stage 2: one lane writes `sid:`** — `@LAT91` first (11 records, no cap, so a
  mistake costs nothing), never a percept lane, and never during a measurement run.

- 🏷️ **2026-08-09 — RFC-0010 STAGE 2: `@LAT91` IS THE FLEET'S FIRST LANE TO WRITE A STABLE
  ID. Software done; ⚠ NOT YET RUN ON HARDWARE.** `Reconciler::buildBelief` renders
  `sid:00000000` and calls `sid::stampKey`; `beliefKey()` is public so a reader can
  **recompute** the id rather than trust it. The `[dream]` log line now carries
  `sid:%08lx`. Cost: **Cardputer +764 B flash**, T-Deck unchanged, the three 94 %-full V4s
  **byte-identical**. §4.2.6's promise held exactly — one literal, one call, no second
  buffer; the record grew 13 B inside a 2624 B builder that needed no change.
  🎯 **Why this lane first, and it was the measurement's choice not a preference.** It is a
  **KEY-identity** lane — its 83.2 % input-collision rate is what proved identity needs two
  kinds — and it is the cheapest lane to be wrong in: **11 records against no cap**, where
  the percept lanes are what a measurement run depends on.
  ⚠ **The two properties pinned are the ones that make it an identity and not a checksum:
  the id SURVIVES A REVISION** (new conf, new rev, new stamp, new `LON` — same name) **and
  IGNORES THE ORDINAL.** Get either wrong and every citation into this lane silently
  re-points on the next Dream Cycle, which is the failure `@LAT100` exists to make visible.
  🐛 **The first cross-component test found a real defect immediately, and it was the exact
  failure a stable id exists to prevent: the writer wrote an id the reader could not read
  back.** `ttdbHeaderSid` assumed its buffer began at the header line — but every record
  this fleet renders begins `\n---\n\n@LAT…`, so `strchr(line, '\n')` hit the newline at
  index 0 and reported "no sid" for a record that carried one. **Both sides were internally
  consistent and individually green; only a test spanning the two could see it.** General
  rule: test the writer against the reader, never each against itself.
  📎 A second, smaller instance of the same shape in the same hour: my throwaway build
  command was `compile … | head && ./test.exe`, which ran a **stale binary and printed OK**
  after the compile had failed — the identical trap to the `tests/Makefile` defect fixed
  this morning, reproduced by hand within hours of fixing it. Build, *then* run, and let a
  failure stop you.
  ✅ **HARDWARE-VERIFIED 2026-08-09, and in a stronger form than the planned check.** The
  planned "two Dream Cycles 3 min apart" turned out to be uncheckable on a quiet bench:
  with run-length on `@LAT92` a still node accrues **no new outcome records**, so every
  in-session cycle takes the `conf steady` skip path and never reprints (observed: dreams
  at +169 s and +349 s, both `no change`). What IS checkable — and stronger — is **across
  reboots**: `gLastConfN` starts at 0, so the first dream after boot always takes the
  changing path — fresh fold, **full lane rewrite**, new stamps, `rev` reset. Two boots
  (the post-flash reset, then an esptool hard reset), same three sids both times:
  `ab8f77ba` (peer 0x100 espnow) · `ca9b482d` (peer 0x10 ble) · `2b4da8c8` (peer 0x10
  espnow), while the TTDB bytes moved 101384 → 101095 B under the rewrite. Distinct keys
  got distinct ids (same peer, two protos, two sids).
  🎯 **The closing leg was the one the RFC calls the entire point: the laptop recomputed
  all three ids from `(node, lane, key)` alone** — `sid_probe.sid_key(0x300, 91,
  "peer:0x00000010|proto:ble")` = `ca9b482d`, digit for digit against the wire, never
  having seen the records. A reader can now *verify* a belief's name, not just trust it.
  📎 The dream schedule is "at boot, then every 180 s" — the first dream fires ~2 s after
  boot, not at +180 s. And `peer:0x10` in the `[dream]` line is **V4-A** (the V4s are
  0x10/0x11/0x12, `RobotTeamConfig.h` — not the 0x100-family the handhelds use); the print
  is unpadded (`%lx`) but the key preimage uses `%08lx`, so the id is built on the full
  width. The dream cycle also fires the first `[loop]` worst-pass alarm of a session
  (~1.9–2.9 s inside `linkperc`) — that is the lane rewrite's flash cost, already budgeted
  in the TIMING line, not a new stall.

- 🏷️ **2026-08-09 — RFC-0010 STAGE 3: `@LAT101` IS THE FLEET'S FIRST FIELD LANE, BUILT
  AND HARDWARE-VERIFIED ON BOTH HANDHELDS THE SAME DAY.** The SOCIAL field
  (default-network.md §3): one `**PEER**` record per known peer — the three capability
  masks plus a co-presence trace reinforced by beacons the node already hears, decaying
  on a 10 min half-life. The live medium is the `Social` table in RAM; the lane is its
  **durable shadow**, rewritten on material change behind a 60 s gap plus a 30 min
  heartbeat that fires only if something was reinforced — §5.1's *only reinforcement
  writes* holding on flash, so a node alone in a field writes nothing, forever. Natural
  key `node:0x%08lx` (KEY sid, full width). No new wire bytes. **No prune path, and that
  is the stage-3 falsifier pre-committed**: reclaim-lowest happens in RAM (§5.3), spends
  zero `@LAT100`, and `lanegen::prune`'s ≥98 refusal was not widened.
  ✅ **Verified on hardware:** two rewrites in one Cardputer boot with **ordinals
  shuffled and every sid identical**; the T-Deck's trace entered at `27cc5401`, **the id
  the laptop had computed from the key before the record existed**; ten of ten sids
  recomputed digit-for-digit across both nodes, with the same subject carrying different
  ids under different observers (per-`(node,lane)` scoping, demonstrated). After a hard
  reset both handhelds reloaded 5 traces `co:…~` FADED-until-heard (§5.4 unknown-age
  clamp 64), UNKNOWN capabilities stayed UNKNOWN, **no boot-storm rewrite** — and
  `poseCeiling()` said `<=translation` from reloaded knowledge alone: the fleet's sense
  of its own shape now survives a power cycle. The staleness instrument also fired its
  first REAL report (a self epoch bump racing the 2 s beacon; converged next beacon).
  🐛 **THE BIG CATCH IS UPSTREAM OF THIS FEATURE: `Ttdb::appendRecord` PAST
  `TTDB_MAX_RECORDS` WROTE THE BYTES, FAILED TO INDEX THEM, AND RETURNED TRUE.** The
  Cardputer's file is legitimately AT the old cap of 256 (its lane caps sum there), so
  the first five `@LAT101` records were appended "successfully", were invisible to every
  reader, and were then **destroyed by the next Dream Cycle's belief-lane rewrite**
  (`removeLaneRange` copies indexed spans only). Any lane could have hit this; the field
  lane was merely the first new lane since the file filled. Fixed three ways:
  `TTDB_MAX_RECORDS` 256 → **288** (+512 B .bss per open file — do NOT raise it for a
  lane that grows with uptime), `appendRecord` now counts the block's headers and
  **refuses before writing a byte**, and `persistField` pre-checks the index budget and
  defers with one plain sentence. 📎 A smaller catch first: sharing a buffer through a
  `char* rec` alias and measuring `sizeof(rec)` — 4 — so every build refused and the
  first persist wrote `0 trace(s)`; that log line existing is what made both defects
  visible at all.
  📎 `lane_classes` (§7.1) added to both handhelds' repo `data/ttdb.md` — it reaches the
  devices at the next FS flash (deliberately NOT flashed now: an FS image wipes the
  learned lanes), and the fail-safe reads absent-declaration as EVIDENCE, so the delay is
  safe. Cost vs HEAD: Cardputer **+4100 B flash / +592 B RAM** (42 %), T-Deck **+4776 B
  / +608 B** (41 %), V4s **zero content bytes** (byte-diff; only the image's two
  embedded hash fields differ). Native suite 153 checks; `check_makefile.py` green.
  ⚠ **Seen twice while verifying, unrelated to stage 3: the T-Deck's `@LAT90` lane is
  FULL at 16** ("the timeline is flapping, not settling"). Same condition the Cardputer
  had; repair is the `--lane 90` prune, but the lane is telling us the T-Deck flaps
  timelines across reboots — worth a look before pruning the evidence of it.
  📋 Next: stage 4 is pre-satisfied for `@LAT101` (born without a prune); the open RFC
  stages are the default network's 2 (capability claims through Rule 1/2) and 3
  (`@LAT102` attributed testimony), and @LAT98's natural key still wants a real
  re-attestation.

- 🔬 **2026-08-10 — NIGHT 2 WAS NOT A WRITE-OFF: IT FAILED ONE GATE, FOR LENGTH ONLY. Three
  findings, all from data already on disk — no hardware, no port opened, no board reset.**
  The infrastructure arc (TraceField → default network stage 1 → sid → the first FIELD lane)
  is closed; **the primary hypothesis has not moved since 2026-08-06** and the next move
  belongs to it. Before spending the fleet's scarcest resource on a night 3, the banked
  evidence was read.

  **Finding 1 — the cancelled run's gate verdict.** `entity-drift --segment` over
  `master/entity-baseline/cardputer_night2_cancelled.md` (91 705 B):
  ```
  SEGMENT: longest contiguous single-stream run = stream 50956f00, 16 of 46 window(s)
    [PASS] one stream id                              16 window(s), 1 stream(s)
    [PASS] t_ms monotonic                             0 backwards step(s)
    [PASS] @LAT95 witnesses stillness, same timeline  8 motion record(s), 0 moving,
                                                      100% span covered, timeline match
    [FAIL] pairs at 600+/-120 s spacing               14 kept, 1 off-cadence (need 30)
  ```
  ✅ **Stillness, monotonicity and timeline unity all held. The only failure is DURATION** —
  a clean ~2.7 h interval (16 × 600 s) sitting inside a 7.7 h window, against the 30 pairs
  (~5.2 h) the gate requires. The run was disqualified by fragmentation, not by dirt.
  ⚠ **On having looked at a file the previous session deliberately left unanalysed.** That
  decision was about refusing to launder a contaminated run into a baseline, and it stands:
  **no distribution was printed and `--force` was not passed.** The gates were declared
  2026-08-04, before this run existed, and they refused to report — which is exactly the
  case in which looking costs nothing. What was taken from the file is a *verdict on the
  apparatus*, not a number about the world.

  **Finding 2 — why it fragmented, and it is not a firmware defect.** The Cardputer's
  `@LAT90` in that same file carries **two consecutive `STREAM-ORIGIN` records**
  (`LON3` 0x5c68cae2, `LON4` 0xb94644d8, both `from:0x300`, `t_ms:0`) before reconciling
  onto 0x50956f00 `from:0x10`. It rebooted while **nobody was holding a stream** — V4-A had
  been unplugged mid-run. Night 1 survived two reboots *only* because V4-A held one
  throughout.
  🎯 **`TimeStream.h` already argues down the tempting fix**: persisting the id across a
  reboot is wrong, because a node cannot know how long it was powered off and would stamp
  records earlier than a peer wrote during the downtime. So there is nothing to repair —
  **the continuously-powered stream holder is part of the measuring apparatus**, and it
  must be treated as instrumentation rather than as a spare node that happens to be on.
  📎 The T-Deck's own `@LAT90` (from the 2026-08-06 pull, so this predates the 08-09 flag)
  shows the same thing from the other side: `LON8..LON15` carry **eight distinct stream ids
  in eight records**, adopted alternately `from:0x10` and `from:0x300`. That is the fleet
  re-minting a timeline every reboot round, logged faithfully. Whether that is pathology or
  simply a bench that gets rebooted a lot is still open — but it is now clear it is a FLEET
  property, not a T-Deck one, so pruning the T-Deck's lane would only hide it.

  **Finding 3 — the runbook was spending 4× the `@LAT100` budget it needs, and this is the
  actionable one.** `cmd --op clear-percepts --lane 0` writes **one marker per non-empty
  lane in 94–97 = four**. But `lanegen::prune` sets `lo = hi = lane` whenever a lane is
  named (`LaneGenNode.h`, the `lane ? lane : TTDB_PERCEPT_LANE_LO` pair), so
  **`--lane 96` costs exactly one.**
  🛑 At **28/32** on the last pull, the old runbook takes the Cardputer to 32/32 and it can
  then **never clear a percept lane again** without a firmware change. The one-lane prune
  takes it to 29/32 and leaves **three** further attempts.
  ✅ **And one lane is all the gates read.** `@LAT96` is the only gate-input lane near its
  cap (**46/48**). `@LAT95` sits at **21/30** and, change-triggered with run-length, writes
  ~2 records per 8 h of stillness — it does not need clearing. `@LAT94` (48/48) and `@LAT97`
  (48/48) are full and are *not* read by `entity-drift`; a full lane refuses writes, it does
  not churn. With `TTDB_MAX_RECORDS` now 288 and `@LAT96`'s 46 freed, the file has headroom.
  📎 `pruneTimeline` (`--lane 90`) likewise costs **one** marker, drawn from **that node's
  own** `@LAT100` — the T-Deck's 16/16 repair does not touch the Cardputer's budget.

  📋 **CORRECTED NIGHT-3 RUNBOOK.** Supersedes the 2026-08-06 block above. Operator's to
  run — `cmd` and `pull` both open the port and reset the board.
  ```bash
  # a) re-identify BOTH ports BY APP IMAGE (never from memory, never from a mesh reply)
  python -m esptool --chip esp32s3 --port COMx --baud 460800 read-flash 0x10000 0x80000 app.bin
  #    grep for "Cardputer console" / "V4-A bridge"
  # b) prune ONE lane on the Cardputer. NOT --lane 0: that costs 4 of the 4 markers left.
  python orchestrator/companion.py cmd --op clear-percepts --lane 96 --node cardputer_1 --port <COM> --attempts 6
  #    V4-A needs NO prune (its lanes are not analysed and it has no PerceptLearn to disarm)
  # c) verify the prune landed and the budget moved 28 -> 29, not 28 -> 32:
  python orchestrator/companion.py pull   --node cardputer_1 --port <COM> --out master/ui/cardputer_prerun_night3.md
  python orchestrator/companion.py prunes --file master/ui/cardputer_prerun_night3.md
  # d) BOTH boards on a wall charger. V4-A powered and UNTOUCHED for the whole run --
  #    it is the stream holder, i.e. part of the apparatus. >= 5.2 h, Cardputer still.
  # e) one pull at the end, then the gates:
  python orchestrator/companion.py pull --node cardputer_1 --port <COM> --out master/entity-baseline/cardputer_baseline_night3.md
  python orchestrator/companion.py entity-drift --file master/entity-baseline/cardputer_baseline_night3.md --segment
  ```
  🎯 **Pre-committed stop rule, stated before the run per the practice the gates
  established:** the run must hold **one stream for ≥ 30 pairs**. If the `@LAT90` lane shows
  a `STREAM-ORIGIN` or an id change during the window, the run is void as a baseline — bank
  it, do **not** re-time it, and do **not** spend a second marker retrying the same night.
  Two consecutive voids means the fleet cannot hold a timeline long enough to measure this
  at all, and the finding is about the time stream, not about entity drift.
  ⚠ Unchanged interlocks: never `Upload-Cardputer-FS.ps1` during a run (a firmware flash is
  fine, an FS image wipes the lanes); no RFC stage applied to a node mid-run.
  📌 Still open and off the hypothesis path: default-network stages 2 (capability claims
  through Rule 1/2) and 3 (`@LAT102` testimony); `@LAT98`'s natural key, which wants a real
  re-attestation; the three V4s needing `huge_app` before they can carry any of this; and
  the Cardputer's unexplained 7–8 KB `maxalloc`.

- 🧩 **2026-08-10 — PART 2's DESIGN DECISION IS ANSWERED, OFFLINE, BEFORE ANY CODE: the
  `**COVERED**` BLOCK MUST CARRY THE RUN'S UNION, AND THE TRIGGER IS STABLE-CORE, NOT A
  JACCARD THRESHOLD.** The outstanding-items list said to decide what a covered block must
  carry *before* writing the lane, because `@LAT95`'s verdict is a 2-state label and
  `@LAT96`'s would be a threshold on a continuous drift — a judgement the reader cannot
  re-derive. That decision needed no hardware: it was simulated over the **validated**
  night-1 segment (all four gates passed). `scratchpad/lat96_trigger_sim.py`.

  🔬 **First, the premise is smaller than it looked: the entire night-1 segment is TEN
  distinct BSSIDs.** 41 windows, 4–8 APs each (p50 5), union of 10. So "continuous drift"
  is a misdescription — one AP appearing or vanishing moves Jaccard by ~0.2 at the median
  set size, and the metric takes a handful of discrete values. The lane spends 48 records
  per 8 h to carry about ten bits of set membership. ⚠ That is a property of **this bench's
  radio environment**, not of the tier; a 40-AP room would look different, and the entry
  below says where that matters.

  **The two mechanisms, over both nights** (`lost` = APs appearing ONLY in dropped windows,
  i.e. what `_entity_set`'s union — the lane's actual consumer, the coarse proximity bound
  — would no longer contain):
  ```
                          night 1 (gates passed)      night 2 (cancelled, 16 win)
                          records  compress  lost     records  compress  lost
  A  thr 0.375             6/41     6.83x    10%       2/16     8.00x    18%
  A  thr 0.500             3/41    13.67x    10%       1/16    16.00x    36%
  B  core 2 of last 3     11/41     3.73x     0%       7/16     2.29x     9%
  B  core 3 of last 5      9/41     4.56x     0%       5/16     3.20x    27%
  ```
  ⚠ **A's LOSS DOES NOT TRANSFER, WHICH IS A STRONGER OBJECTION THAN THE ONE WE HAD.** Same
  node, same bench, two nights: a fixed threshold loses 10 % one night and 36 % the next.
  The worry on record was that the *threshold* might not transfer; this says that even a
  transferable threshold would not give a transferable **loss**. At comparable compression B
  loses less and degrades gracefully instead of falling off a cliff.

  🎯 **BUT THE DECISIVE ANSWER IS ABOUT THE RECORD, NOT THE TRIGGER.** Both mechanisms lose
  APs only under the assumption that a dropped window contributes nothing — and it does not
  have to. The consumer computes a **union**, so if the `**COVERED**` block carries the
  run's union (the stable core plus the fringe seen during it), **the loss column goes to
  zero by construction, for either trigger**, and the compression survives because the cap
  that matters is `ENTITYPERCEPT_MAX_LANE 48` **records**, not bytes.
  📎 **This is the honest analogue of Part 1's losslessness argument, and it is worth
  stating in the same shape.** Run-length was legitimate on `@LAT92` because folding a
  verdict N times equals folding it once per window. The equivalent claim here is: *the
  run's union must be recoverable from the record that covers it.* A block carrying
  `core:` + `fringe:` satisfies it. A block carrying only `windows:` and a distance does
  **not** — it asserts the set stayed within some radius of a reference the reader cannot
  see, which is exactly the un-re-derivable judgement the outstanding-items note warned
  about.
  ✅ **With that settled, the trigger choice reduces to compression-per-record, and B still
  wins** — and B's block is **self-describing** (it states the set it claims held constant)
  where A's is a claim about an invisible reference. Neither is fully re-derivable from the
  written records alone; that is not the available property, and B gets the one that is.

  ⚠ **What this does NOT settle, stated plainly.** One bench, one node, one radio
  environment. A larger AP alphabet could change A's picture — its loss should *grow* with
  the alphabet rather than shrink, so B's advantage likely holds or widens, but that is an
  argument and not a measurement. Night 2's 16-window segment failed the gates and is used
  here **only as a second draw, never as a baseline**. And `n`/`m` still want a validated
  second night — though they are a **counting rule over recorded sets**, a materially
  weaker dependency than a constant fitted to a continuous quantity.
  📋 **Night 3's purpose therefore NARROWS: it is no longer "decide between the two
  mechanisms" — this decides that — it is "validate `n`/`m` and confirm the still-node
  picture transfers."** The corrected runbook and the `--lane 96` prune rule in the entry
  above are unchanged.

Keep this section current. It is the first thing the next session reads.

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
