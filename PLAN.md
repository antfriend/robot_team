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
- [x] **Verify on toolchain (device-first):** `arduino-cli` + the
      `UNIHIKER:esp32:k10` core installed; `k10_percept` compiles, and **firmware +
      LittleFS TTDB are flashed and verified on a real K10** via `.vscode/tasks.json`
      — the LCD renders both TTDB records, the live cursor, and WARM/cool state, and
      the startup "toot toot" plays. The native `g++`/`make` tests were **skipped**
      (no compiler on the K10 machine; chose on-device verification instead).

**Done when:** ~~native tests pass and~~ `k10_percept` compiles clean under
arduino-cli **and runs verified on-device.** ✅ Done — the only open item is the
optional native `g++` test suite, deferred.

---

## Phase 1 — K10 ↔ laptop over USB-CDC (`companion.py pull`)

**Reality check:** there is only **one** physical K10, so the original "two K10s
talk" milestone (kept below, deferred) can't run yet. The available single-K10
milestone proves the toot wire protocol against real hardware using the laptop as
the second party — over USB-CDC, no second radio node needed.

- [x] Single K10 runs the Agent32 loop on-device; LCD shows both TTDB records +
      cursor/WARM state (done in Phase 0).
- [x] Firmware flashed with **`CDCOnBoot=cdc`** so `Serial` (and the TootSerialLink
      `companion.py` pulls over) rides the native USB CDC, not UART0. Without this
      the pull silently gets zero bytes — see CLAUDE.md.
- [x] `companion.py pull --port COM3 --node k10_1` reassembles a **byte-identical**
      copy of `data/ttdb.md` (1114 B, sha256 `ec17aee2…`). Settle delay bumped to
      2.5 s because opening the port resets the S3 and it must finish booting first.
- [x] Negative checks (verified on-device over COM3): a valid request streams 7
      `TTDB_DATA` frames; a **wrong-key** and a **tampered-body** request each yield
      **0** frames (HMAC reject); a **replayed `(src,seq)`** yields **0** frames
      (dedup drop).

**Done when:** the laptop reassembles a byte-exact copy of the K10's TTDB over
USB-CDC ✅, and bad-HMAC / replayed toots are rejected ✅. **Phase 1 complete.**

### Phase 1b — Two nodes talk over ESP-NOW (K10 leaf + V4-A bridge) — ▶ unblocked

A Heltec V4-A is now on hand and **verified standalone** (boots, ESP-NOW up,
byte-exact TTDB pull over USB-CDC, HMAC reject — `negchecks.py`). It runs the
bridge sketch: laptop↔mesh gateway over USB-CDC. Both radio nodes now exist.

- [x] V4-A flashed (`esp32:esp32:esp32s3:CDCOnBoot=cdc`) + TTDB image
      (`scripts/Upload-V4-FS.ps1`, spiffs @0x290000); standalone pull byte-exact.
- [ ] **Reflash the K10** with the radio-only-dedup change (dedup moved off the
      shared dispatch onto the ESP-NOW recv path) and re-run `negchecks.py`.
- [ ] **Bridged pull:** `companion.py pull --node k10_1 --port COM6` with the K10
      powered in range — request routes laptop→USB→V4-A→ESP-NOW→K10 and the
      `TTDB_DATA` slices stream back the same way. Proves ESP-NOW gossip + relay.
- [ ] Radio-replay check: inject a duplicate `(src,seq)` over ESP-NOW and confirm
      the receiver drops it (the dedup test the trusted USB link can't exercise).

**Done when:** the laptop reassembles the K10's TTDB *through* the V4-A bridge over
ESP-NOW, and a duplicate injected over the air is dropped.

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
