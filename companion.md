# companion.md — Robot Team Orchestrator

**This file is the single source of truth for the robot_team project.** It knows
everything about the fleet and orchestrates a swarm of simpler **A32 agents**.
Read it first, every session. When something here is wrong or stale, fix *this
file* — it is the brain, not a logbook.

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
| **K10-1** | UNIHIKER K10 | Percept node — camera/mic/accel, `@PERCEPT` capture, UI | leaf | ESP-NOW / WiFi | battery | `firmware/k10_percept` | ✅ on-device verified (boots from TTDB, Agent32 loop, LCD records + cursor/WARM, "toot toot"; TTDB-share over ESP-NOW & USB; **`want_ack` ACK + re-ACK, chunk reassembly, time-sync with runtime TTDB self-write of `@LAT99` sync records**) |
| **orchestrator** | laptop | The companion itself — Locus loop, Dream Cycle, master TTDB | — | USB-CDC + WiFi | mains | `orchestrator/companion.py` | 🟨 scaffold (`pull` reassembles a node's TTDB) |

Legend: ⬜ not started · 🟨 scaffold (compiles/ports, not on-device verified) · ✅ on-device verified

> **Hardware on hand: one K10 + two Heltec V4 (V4-A bridge + a 2nd V4 for V4-B).**
> K10 = FQBN `UNIHIKER:esp32:k10` (COM3); the V4s = FQBN `esp32:esp32:esp32s3` (V4-A
> on COM6). All use the ESP32-S3 native USB, so all need the **`CDCOnBoot=cdc`** flag
> (see build note). The 2nd V4 is the **V4-B relay** — ✅ on-device verified as the 3rd
> mesh node + Dream-Cycle participant (flashed COM9; sync/reconcile/push, §6). V4-C unbuilt.
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
- **Next action — pick one:** (a) **More tunes / parts** — kLeadNotes is a one-table swap
  (TTN-RFC-0010 §7); add a song selector or a 2nd pitched node (purpose-built hardware — the
  user's stated progression). (b) **Faster reconvergence** — shorten `PULSE_RESYNC_PERIOD_MS`
  + `PULSE_CONDUCTOR_TIMEOUT_MS` (and/or persist `era` in NVS) so a conductor reboot
  re-locks in seconds, not ~90 s; still well within the minimal-traffic budget. (b)
  **Parts/melodies** — the `Part`/`hit` split (TTN-RFC-0010 §7) is the seam for per-node
  melodies on purpose-built hardware (the user's stated next progression). (c) Confirm the
  **V4 white LED on GPIO35** actually blinks (OLED beat-dot is the fallback). Plus earlier
  options: more `**DIRECTIVE**` types, V4-B relay forwarding, belief range-readback. Phases
  3–4 (V4-C, LoRa) gated on V4-C + `USE_LORA`.

Keep this section current. It is the first thing the next session reads.

---

## 7. Fleet knowledge map (TTDB)

The companion **dogfoods the TTDB format**: below is its own knowledge of the
fleet, encoded the way the A32 nodes encode theirs (`TTDB-RFC-0001` file format,
`TTDB-RFC-0003` typed edges, `TTN-RFC-0002` edge taxonomy). It is the master map
§6 narrates. Globe: `lon` = spine position (**0** laptop · **10** head · **20**
mid · **30** tail), `lat 10` = leaf/cluster depth, `lat 90` = engineering
decisions & lessons. Keep both this map and §6 in sync.

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

**Orchestrator** — the laptop companion, the only LLM in the system. Holds the
master TTDB and drives the fleet. `orchestrator/companion.py pull` reassembles any
node's TTDB over the link (whole-file or byte-range, HMAC-verified), directly over
USB-CDC or through the V4-A bridge into the mesh. Verified: byte-exact pulls of
both built nodes (K10 1114 B, V4-A 976 B). Auth/replay floor checked with
`orchestrator/negchecks.py`. Also `cmd`/`monitor` (drive + observe nodes),
`reconcile` (fold node `@LAT99` sync logs → `master/consolidated.md`, Dream-Cycle
seed), and `push` (re-author + distribute a belief → `master/belief.md`, see
`@LAT90LON30`).

---

@LAT0LON10 | created:1750000000 | updated:1781913600 | relates:connected_over@LAT0LON0,routes_via@LAT10LON10,navigates_to@LAT0LON20,acknowledges@LAT0LON0

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

**K10-1 percept** (UNIHIKER K10, leaf in the head's ESP-NOW cluster) — ✅ on-device
verified. FQBN `UNIHIKER:esp32:k10:CDCOnBoot=cdc`, on COM3. Agent32 sense→reason→act
loop runs; LCD shows both TTDB records + cursor/WARM; startup "toot toot". Byte-exact
pull (1114 B) + HMAC reject + dedup. Reaches the laptop over ESP-NOW via the V4-A
bridge. Reflashed 2026-06-20 to radio-only dedup (see `@LAT90LON0`) and re-verified
with `negchecks.py` — now consistent with the V4-A. Self-writes its TTDB at runtime:
`@LAT99` time-sync logs (`sync`), and on a pushed belief adopts `/belief.md` and
appends a `BELIEF-ADOPTED` record in its `@LAT98` lane (`push`, `@LAT90LON30`).

---

@LAT0LON20 | created:1750000000 | updated:1750000000 | relates:routes_via@LAT0LON10,navigates_to@LAT0LON30

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

**V4-C edge** (Heltec V4, spine tail) — ⬜ unbuilt scaffold. Off-grid remote-cluster
gateway; GNSS `@LATxLONy` stamping; summarizes PERCEPT before the LoRa hop. Phases
3–4.

---

@LAT90LON0 | created:1781913600 | updated:1781913600 | relates:supports@LAT0LON10,supports@LAT10LON10

**Decision — dedup is radio-only** (2026-06-20). `(src,seq)` dedup applies on the
ESP-NOW/LoRa receive path only (replay + mesh forwarding-loop guard); the trusted
USB-CDC command link is intentionally NOT deduped, so the laptop can retry a lost
request. Gate dedup in the radio recv callback, never in the shared `handleToot`
dispatch. The K10 was reflashed to match the V4-A (2026-06-20) and re-verified.

---

@LAT90LON10 | created:1781913600 | updated:1781913600 | relates:supports@LAT0LON10,supports@LAT10LON10

**Lesson — native-USB `CDCOnBoot`**. Both S3 boards expose the ESP32-S3 built-in
USB (no UART bridge chip), so `Serial` — and the `TootSerialLink` the companion
pulls over — only reaches the COM port when built with the FQBN suffix
`CDCOnBoot=cdc`; otherwise it binds to UART0 and pulls return zero bytes. Opening
the port resets the board, so `companion.py` waits ~2.5 s before sending the request.

---

@LAT90LON20 | created:1781913600 | updated:1781913600 | relates:derived_from@LAT0LON10,derived_from@LAT10LON10

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
