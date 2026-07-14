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
| **V4-A** | Heltec V4 | Bridge / head — laptop ↔ mesh gateway | head | USB-CDC + LoRa + ESP-NOW | mains, never sleeps | `firmware/v4a_bridge` | ✅ on-device verified (boots, ESP-NOW up, byte-exact pull + HMAC auth; OLED status; **`want_ack` ACK + time-sync: adopts `TIME_SYNC`, answers `TIME_REQ`, appends its own sync log**; LoRa gated off) |
| **V4-B** | Heltec V4 | Relay / mid — store-and-forward long hops | mid | LoRa + ESP-NOW | solar + battery | `firmware/v4b_relay` | ✅ on-device verified as the **3rd mesh node + Dream-Cycle participant** (2026-06-25): standalone byte-exact pull + self-heal + `negchecks` (COM9); then through the V4-A bridge over ESP-NOW — adopts `TIME_SYNC` (`@LAT99` self-write), folds into 3-node `reconcile` (id:3/4 `agree:yes`), and adopts a pushed belief byte-exact (`@LAT98`, 1373 B/crc match). Stores+attests beliefs (no DIRECTIVE action — no agent cadence). relay-forward + LoRa gated off |
| **V4-C** | Heltec V4 | Edge / tail — remote cluster gateway, GNSS stamp | tail | LoRa + ESP-NOW | solar, off-grid | `firmware/v4c_edge` | 🟨 scaffold (cluster gateway; LoRa/GNSS gated off) |
| **K10-1** | UNIHIKER K10 | Percept node — camera/mic/accel, `@PERCEPT` capture, UI | leaf | ESP-NOW / WiFi | battery | `firmware/k10_percept` | ✅ on-device verified (boots from TTDB, Agent32 loop, LCD records + cursor/WARM, "toot toot"; TTDB-share over ESP-NOW & USB; **`want_ack` ACK + re-ACK, chunk reassembly, time-sync with runtime TTDB self-write of `@LAT99` sync records**; **band lead** — Ode-to-Joy melody, boots silent, `CMD_PLAY`/`CMD_STOP`) |
| **T-DECK-1** | LilyGo T-Deck | Handheld console — keyboard injects CMD, screen shows fleet; roams | roaming leaf | ESP-NOW + LoRa (gated) + USB-CDC | battery | `firmware/tdeck_console` | ✅ on-device verified network floor (2026-07-06, COM10): boots from TTDB, **byte-exact pull (1351 B, sha `fd95360b…`)** + **HMAC reject** (`negchecks` wrong-key/tampered → 0). Full participant (pull/HMAC/dedup, `TIME_SYNC`+`@LAT99`, belief `TTDB_PUT`+`@LAT98`, STATUS, PULSE follower). **Console UI live (`USE_TDECK_HW 1`): "toot toot" on boot (I²S sine on the MAX98357A amp) + 320×240 fleet view (Adafruit_ST7789, rotation 3) — both confirmed on-device.** Keyboard (I²C 0x55) → CMD. LoRa gated. **GPS (Plus): NMEA read + `CMD_GET_GPS` GPS PERCEPT built (SP2 roaming anchor); compiles, not yet flashed/skied.** |
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
> e.g. COM11→COM10), then tap RST *without* the trackball to boot the app. V4-C unbuilt.
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
2026-07-13 the ranking points, correctly, at the open crux: **@LAT90LON50 —
Semantic Positioning (EPS 125)**, then **@LAT0LON30 — the unbuilt V4-C edge
(EPS 74)**; everything proven sits below EPS 20. Update the weights when a
record's status changes (a weight-only write does not bump `rev`).

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
HIGH first); native-USB flashing needs manual BOOT/RST (see §6).
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

@LAT0LON30 | created:1750000000 | updated:1750000000 | relates:connected_over@LAT0LON20
[ew]
conf:120
rev:0
sal:140
touched:1783983861
[/ew]

**V4-C edge** (Heltec V4, spine tail) — ⬜ unbuilt scaffold. Off-grid remote-cluster
gateway; GNSS `@LATxLONy` stamping; summarizes PERCEPT before the LoRa hop. Phases
3–4.

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
