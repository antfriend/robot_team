# PLAN.md — Building the Robot Team

Build plan for `robot_team`. The orchestration model lives in
[companion.md](companion.md) — read it first. This file is the **how and in what
order**; `companion.md` is the **who and why**.

**Goal:** a working swarm of A32 (ESP32) robots — 3× Heltec V4 LoRa spine
(bridge/relay/edge) + UNIHIKER K10 percept nodes — coordinated by the laptop
orchestrator, exchanging HMAC-signed toots, consolidating beliefs via the Dream
Cycle into a master TTDB. No cloud LLM on any device.

**Strategy:** additive and bottom-up. Every phase ends with something that runs
and is verified. We never wire the long-range mesh before the in-range default
(ESP-NOW) works. Phases map onto the bring-up order in
`toot_network_architecture.md §6`.

---

## Phase 0 — Scaffold (arduino-cli project + portable libs) ✅ scaffolded

Deploy path is **command-line arduino-cli**, not PlatformIO (the A32-RFC default
is overridden for this project). Each node is a proper Arduino sketch; shared
code lives in `firmware/libraries/` and is added per-build with `--libraries`.

- [x] Sketch-per-node layout under `firmware/`, `data/ttdb.md` per node.
- [x] `CLAUDE.md` (arduino-cli flavored) + `firmware/README.md`.
- [x] `scripts/{setup,build,deploy,upload-fs}.sh` — arduino-cli compile/upload,
      plus `mklittlefs`+`esptool` for the LittleFS TTDB image.
- [x] `libraries/Toot/` — 250-byte frame, portable SHA-256/HMAC, `(src,seq)`
      dedup, TTL, serial framing (`toot_network_architecture.md §3`).
- [x] `libraries/TTDB/` — streaming reader + offset index (`A32-RFC-0002`) and
      `TtdbShare` (serve any byte range to the companion).
- [x] `libraries/Agent32/` — full sense→reason→act loop over the TTDB index:
      quantize readings → nearest record → move cursor → fire `triggers` /
      `navigates_to` / `inhibits` edges to coordinate-matched actuators.
- [x] `libraries/TTDB/` coordinate index + `TtdbParse` (header/edge parsing,
      nearest search), wired into `Ttdb::nearest()` / `edgesAt()`.
- [x] `k10_percept` exercises the loop end-to-end (placeholder temp sensor →
      `@LAT10LON0` warm record → `triggers` fires the indicator).
- [x] `orchestrator/companion.py pull` — reassembles a node's TTDB over serial.
- [x] Native test (`tests/`, g++/make): SHA-256/HMAC vectors pinned to Python,
      plus TTDB header/edge parsing and nearest-search. Parser + routing logic
      also cross-checked against the sample TTDB with a Python mirror.
- [ ] **Verify on toolchain:** `cd tests && make` (needs g++), then
      `scripts/build.sh k10_percept` (needs arduino-cli + esp32 core). No C++
      compiler was available where the scaffold was authored — first real build
      closes Phase 0.

**Done when:** native tests pass and `k10_percept` compiles clean under
arduino-cli.

---

## Phase 1 — Two K10s talk (ESP-NOW broadcast, fixed channel)

The fastest path to a live swarm. No orchestrator, no LoRa.

- [ ] Author `data/k10.md` TTDB: percept umwelt, `@PERCEPT:before/after`
      capture nodes, basic edges.
- [ ] K10 firmware: HELLO beacon + PERCEPT emit/receive over ESP-NOW broadcast,
      fixed channel 1.
- [ ] Validate framing, dedup, HMAC on real hardware (serial assertions).
- [ ] Show locus `@LATxLONy` / belief state on the 240×320 screen.

**Done when:** two K10s exchange verified HELLO + PERCEPT toots; bad-HMAC and
replayed toots are dropped.

---

## Phase 2 — Reliability layer (ACK/retry + chunking)

- [ ] `want_ack` toots: ACK on `(src,seq[,chunk])`; retransmit w/ backoff.
- [ ] Chunk + reassemble a toot larger than the 208 B body budget.

**Done when:** a >208 B toot is delivered intact under induced packet loss.

---

## Phase 3 — Edge gateway (V4-C joins an ESP-NOW cluster)

- [ ] V4-C firmware: ESP-NOW cluster member + RELAY handling.
- [ ] K10 → V4-C handoff (RELAY type); V4-C summarizes PERCEPT before LoRa.
- [ ] Optional: GNSS module on SH1.25-8P → real `@LATxLONy` stamping.

**Done when:** a K10 out of range of everything but V4-C gets its percept onto
the (stubbed) LoRa side via V4-C, summarized.

---

## Phase 4 — LoRa backbone (V4-B relay + V4-C over SX1262)

Mind the PA-variant Arduino flag per board (`USE_GC1109_PA` V4.2 /
`USE_KCT8103L_PA` V4.3) and **antenna-before-power** (`hardware_specs.md`).

- [ ] V4-B firmware: pure store-and-forward — decrement `ttl`, dedup, re-sign,
      forward. OLED shows RSSI-to-A / RSSI-to-C / forward count.
- [ ] Forward a RELAY toot between two ESP-NOW clusters that can't hear each
      other; confirm TTL decrement + midpoint dedup.
- [ ] V4-B external IPEX antenna + solar power bring-up.

**Done when:** a toot crosses cluster-C → V4-C → V4-B → (V4-A stub) over real
LoRa with correct TTL and no duplicates.

---

## Phase 5 — Orchestrator + bridge (V4-A, laptop in the loop)

- [ ] V4-A firmware: bridge — USB-CDC ↔ LoRa/ESP-NOW; channel authority;
      trusted-core key holder.
- [ ] Laptop orchestrator: inject CMD toots, collect telemetry across the full
      A→B→C spine.
- [ ] Master TTDB on the laptop; reconcile incoming BELIEF/PERCEPT.

**Done when:** a CMD toot from the laptop reaches cluster C and telemetry
returns end-to-end.

---

## Phase 6 — Channel convergence & Dream Cycle

- [ ] Switch ESP-NOW to the orchestrator AP channel; HELLO-beacon convergence
      outward from V4-A.
- [ ] Run the Dream Cycle (`TTDB-RFC-0007`) to consolidate gossiped beliefs into
      the master TTDB; re-author + reflash node TTDBs as behavior evolves.

**Done when:** the orchestrator reconciles a multi-node belief and pushes an
updated TTDB to a node that changes its behavior.

---

## Phase 7 — Field deployment

- [ ] V4-B at the midpoint on solar + external antenna; V4-C off-grid with GNSS.
- [ ] Verify end-to-end laptop ↔ cluster-C delivery in the field.

**Done when:** the fielded spine delivers toots both directions over real
distance, off-grid.

---

## Definition of Done (every phase)

1. Native tests pass (`pio run -e native`) where logic is testable off-device.
2. On-device serial assertions pass for hardware-bound behavior.
3. The relevant A32 agent contract items (`companion.md §3`) hold.
4. `companion.md §2` fleet status and `§6` next-action are updated.

## Conventions

- One TTDB file per node role in `data/` (`k10.md`, `v4a.md`, …); laptop holds
  the master.
- Firmware version (platformio build flags) and TTDB version (`mmpdb.db_id`)
  version independently (`A32-RFC-0004 §7`).
- New edge types or toot types get an RFC in `RFCs/` before code depends on them.
