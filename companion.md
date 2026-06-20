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
| **V4-A** | Heltec V4 | Bridge / head — laptop ↔ mesh gateway | head | USB-CDC + LoRa + ESP-NOW | mains, never sleeps | `firmware/v4a_bridge` | ✅ on-device verified (boots, ESP-NOW up, TTDB-share + HMAC auth over USB-CDC; byte-exact pull; OLED status display; LoRa gated off) |
| **V4-B** | Heltec V4 | Relay / mid — store-and-forward long hops | mid | LoRa + ESP-NOW | solar + battery | `firmware/v4b_relay` | 🟨 scaffold (ttl/dedup forward; LoRa gated off) |
| **V4-C** | Heltec V4 | Edge / tail — remote cluster gateway, GNSS stamp | tail | LoRa + ESP-NOW | solar, off-grid | `firmware/v4c_edge` | 🟨 scaffold (cluster gateway; LoRa/GNSS gated off) |
| **K10-1** | UNIHIKER K10 | Percept node — camera/mic/accel, `@PERCEPT` capture, UI | leaf | ESP-NOW / WiFi | battery | `firmware/k10_percept` | ✅ on-device verified (boots from TTDB, Agent32 loop runs, LCD shows both records + cursor/WARM, startup "toot toot"; ESP-NOW HELLO + TTDB-share over ESP-NOW & USB) |
| **orchestrator** | laptop | The companion itself — Locus loop, Dream Cycle, master TTDB | — | USB-CDC + WiFi | mains | `orchestrator/companion.py` | 🟨 scaffold (`pull` reassembles a node's TTDB) |

Legend: ⬜ not started · 🟨 scaffold (compiles/ports, not on-device verified) · ✅ on-device verified

> **Hardware on hand: one K10 + one Heltec V4-A.** K10 = FQBN `UNIHIKER:esp32:k10`
> (COM3); V4-A = FQBN `esp32:esp32:esp32s3` (COM6). Both use the ESP32-S3 native USB,
> so both need the **`CDCOnBoot=cdc`** flag (see build note). With a 2nd radio node
> now in hand, Phase 1b (two-node ESP-NOW) is unblocked — see §6. V4-B / V4-C unbuilt.

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
  intentionally NOT deduped so the laptop can retry. K10 firmware was changed to
  match the V4 — **the K10 must be reflashed** (`CDCOnBoot=cdc` build) when next
  connected, then re-run negchecks.
- **Next action: Phase 1b two-node ESP-NOW.** Both radio nodes now exist. Plug the
  K10 into power (no data link needed) alongside the USB-tethered V4-A and run the
  **bridged pull**: `companion.py pull --node k10_1 --port COM6` routes the request
  laptop→USB→V4-A→ESP-NOW→K10 and streams `TTDB_DATA` back the same way. That proves
  HELLO/PERCEPT-class gossip + the bridge relay in one shot. Then the radio-replay
  test (inject a duplicate over ESP-NOW) closes the dedup story.

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
`orchestrator/negchecks.py`.

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
bridge. ⚠ **Reflash pending:** firmware changed to radio-only dedup (see
`@LAT90LON0`) but not yet reflashed — reflash + re-run `negchecks.py` when next on
COM3.

---

@LAT0LON20 | created:1750000000 | updated:1750000000 | relates:routes_via@LAT0LON10,navigates_to@LAT0LON30

**V4-B relay** (Heltec V4, spine mid) — ⬜ unbuilt scaffold. Pure store-and-forward
LoRa relay: decrement `ttl`, dedup, re-sign, forward; OLED shows RSSI-to-A /
RSSI-to-C / forward count. Phase 4 (LoRa backbone).

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
dispatch. The K10 was updated to match the V4-A (reflash pending).

---

@LAT90LON10 | created:1781913600 | updated:1781913600 | relates:supports@LAT0LON10,supports@LAT10LON10

**Lesson — native-USB `CDCOnBoot`**. Both S3 boards expose the ESP32-S3 built-in
USB (no UART bridge chip), so `Serial` — and the `TootSerialLink` the companion
pulls over — only reaches the COM port when built with the FQBN suffix
`CDCOnBoot=cdc`; otherwise it binds to UART0 and pulls return zero bytes. Opening
the port resets the board, so `companion.py` waits ~2.5 s before sending the request.

---

@LAT90LON20 | created:1781913600 | updated:1781913600 | relates:derived_from@LAT0LON10,derived_from@LAT10LON10

**Next milestone — bridged ESP-NOW pull (Phase 1b).** With the K10 powered in range
and the V4-A tethered, `companion.py pull --node k10_1 --port COM6` routes the
request laptop→USB→V4-A→ESP-NOW→K10 and streams `TTDB_DATA` back the same way —
proving over-the-air gossip + the bridge relay in one shot. Then inject a duplicate
`(src,seq)` over the air to close the radio-replay dedup test. Reflash the K10 first.
