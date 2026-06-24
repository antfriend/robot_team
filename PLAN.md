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
- [x] **Reflash the K10** with the radio-only-dedup change (dedup moved off the
      shared dispatch onto the ESP-NOW recv path); `negchecks.py` re-verified on
      COM3 (2026-06-20) — both nodes now radio-only.
- [x] **Bridged pull:** `companion.py pull --node k10_1 --port COM6` reassembles
      the K10's TTDB **byte-exact through the V4-A bridge over ESP-NOW** (1114 B),
      repeatably (~5/6 runs clean). Two firmware fixes made the burst survive the
      air: the K10 **serves the reply from `loop()`, not the recv callback** (so its
      TX/send-callback aren't starved by the WiFi task), and **paces sends** via the
      ESP-NOW send-complete callback + a 6 ms inter-frame gap. `companion.py` now
      uses a fresh `toot_seq` per pull so a non-reset target won't dedup-drop it.
- [x] Radio-replay check: `orchestrator/radio_replay.py --bridge-port COM6 --node
      k10_1` — a duplicate `(src,seq)` injected over the air is dropped by the K10's
      radio dedup (original 7 frames, replay 0, fresh seq+1 7). Closes the
      radio-only-dedup story negchecks.py couldn't reach over USB.

**Done when:** the laptop reassembles the K10's TTDB *through* the V4-A bridge over
ESP-NOW ✅, and a duplicate injected over the air is dropped ✅. **Phase 1b complete.**
Residual: ~1/6 runs drop a frame (no ACK/retry yet) — that reliability is **Phase 2**.

---

## Phase 2 — Reliability layer (ACK/retry + chunking) ✅ on-device verified

Spec: **`RFCs/TTN-RFC-0007-Reliable-Delivery.md`** (2026-06-22) — pins the ACK
payload, retransmit/backoff params, the **dedup-vs-ACK re-ACK rule** (§5, the
load-bearing gotcha: a dedup-dropped `want_ack` toot MUST be re-ACKed, body
processed once), and chunk reassembly. The dependency for Phase 2.5's `TIME_SYNC`.

- [x] `want_ack` toots: ACK payload `(ack_src,ack_seq,ack_chunk,status)` (`Toot`
      `makeAck`/`parseAck`/`ackMatches`); `companion.py` sender retransmits with ×2
      backoff, `N=4`; declares undelivered on exhaustion (never silent).
- [x] Receiver re-ACK: a dedup-dropped `want_ack` toot re-ACKs from the duplicate
      (self-identifying) without re-processing the body (K10 `onEspNowRecv`).
- [x] Chunk + reassemble >208 B: portable `Reassembler` (per-chunk dedup, completed
      ring, TTL evict, `MAX_CHUNKS=8`, `SLOTS=2`); `companion.py reltest` selective
      per-chunk retransmit.

**Done ✅ (2026-06-22, K10 + V4-A on COM3/COM6):** `companion.py ping --node k10_1`
ACKed on attempt 1; `reltest --size 500` delivered a 3-chunk toot, **organically
recovering 2 air-dropped chunks via selective retransmit** (attempts resent only the
unacked chunk) and completing the set (ACCEPTED on the completing chunk). Native
`tests/test_toot.cpp` + `tests/test_ack_py.py` (17 checks) pin the codec.

---

## Phase 2.5 — Fleet time-sync (laptop timestamp → node TTDB log → verify in-sync) ✅ on-device verified

**Done ✅ (2026-06-22, K10 + V4-A on COM6 bridge).** `companion.py sync` had both
nodes adopt + ACK on attempt 1 and logged the laptop master record; `verify
--sync-id 2` confirmed all three carry the `**SYNC** id:2` record and measured skew
**v4a_bridge −2.4 ms, k10_1 −30.6 ms** — both within ±50 ms (the K10's −30 ms is the
honest one-way `TIME_SYNC` delivery delay). The K10's on-flash TTDB grew 1114→1426 B
with two `@LAT99LON<n>` sync records, pulled back byte-exact — the first runtime TTDB
self-write. Two laptop-side timing fixes were needed: sample `epoch_ms` *after* the
settle (not before) and probe with a non-blocking read (the 0.1 s timeout inflated
RTT) — first run showed ~−600 ms, both from harness latency, not the firmware.
Checkboxes below describe the as-built design.


Improvised milestone (2026-06-22): prove the **3-node fleet (laptop + V4-A + K10)
agrees on a wall clock**. The laptop is the only timekeeper; it pushes a timestamp
into the mesh, every node adopts it and **writes a log record into its own TTDB**,
and the laptop then pulls all three and verifies they carry the same sync event and
are in sync. This is the first time data flows **laptop → mesh as a command** and
the first time a node **writes its own TTDB at runtime** — it down-payments Phase 5
(CMD inject) and Phase 6 (node TTDB re-authoring). It rides the existing bridge
inject path (`v4a_bridge.ino` already forwards any non-`TTDB_REQ` toot into ESP-NOW).

**Why now / why honest:** nodes have no RTC or NTP — only `millis()`. "Sync" means
each node adopts `clock_offset = T − millis_at_receipt` so its wall clock is the
laptop's epoch minus the one-way delivery delay. We *measure* that residual with an
NTP-lite probe rather than asserting it, so the "in sync within X ms" claim is real.

### New toot types (needs an RFC first — `RFCs/TTN-RFC-0008-Time-Sync.md`, builds on TTN-RFC-0007)
Per project convention (new toot type → RFC before code). Three types:
- `TIME_SYNC = 9` — laptop → fleet. Payload: `sync_id (u32) | epoch_ms (u64 LE)`.
  Broadcast through the bridge; **every** node that hears it adopts the offset and
  appends its TTDB log record (the V4-A adopts it as it passes the frame on).
- `TIME_REQ  = 10` — laptop → node. Payload: `probe_id (u32)`. "Report your epoch now."
- `TIME_RESP = 11` — node → laptop. Payload: `probe_id (u32) | node_epoch_ms (u64 LE)`.

### Firmware (K10 + V4-A)
- [ ] `Ttdb::appendRecord(text, len)` in `libraries/TTDB`: open the LittleFS
      `ttdb.md` in append mode, write a well-formed record block, close, re-run the
      offset index. Record uses a reserved time-log lane so it doesn't collide with
      the `collision_policy: reject` header — coordinate `@LAT99LON<sync_id>`:
      ```
      ---
      @LAT99LON<sync_id> | created:<T> | updated:<T> | relates:
      **SYNC** id:<sync_id> t_ms:<T> recv_ms:<millis> offset_ms:<T-millis>
      ```
- [ ] Clock module: hold `gClockOffsetMs`; `nowEpochMs() = millis() + gClockOffsetMs`.
- [ ] `handleToot`: on `TIME_SYNC` set the offset + `appendRecord`; on `TIME_REQ`
      reply `TIME_RESP(probe_id, nowEpochMs())`. Keep dedup **radio-only** as today.
- [ ] Delivery: `TIME_SYNC` is fire-and-forget today (~5/6 bridged frames land),
      so resend it N times (or set `FLAG_WANT_ACK` once Phase 2 lands). The K10
      still serves replies from `loop()`, not the recv callback (Phase 1b lesson).

### Companion (`orchestrator/companion.py`)
- [ ] `sync` subcommand: pick `sync_id` + `T = now_ms`, broadcast `TIME_SYNC` through
      the bridge port, and append the same record to the laptop master
      (`master/orchestrator-sync.md`) so the laptop is the 3rd "node."
- [ ] `verify --sync-id N` subcommand, two assertions:
      1. **Has the record** — `pull` the K10 (through the bridge) and the V4-A
         (local), parse for a record with `id:N`; confirm laptop master has it too.
      2. **In sync** — NTP-lite per node: note `t0`, send `TIME_REQ`, read
         `TIME_RESP`, note `t1`; `skew = node_epoch − (t0 + (t1−t0)/2)`. Take the
         min-RTT sample of a few probes. Print a table: node | has_record | skew_ms.

**Done when:** after one `companion.py sync`, all three TTDBs (K10, V4-A, laptop
master) carry the same `sync_id` log record, and the NTP-lite probe shows the K10
and V4-A clocks within a stated bound (target: ≤ 50 ms) of the laptop. Reproducible.

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

> **Down-payment ✅ (2026-06-22): `CMD` actuation works.** `CMD` now carries a verb
> set (`Toot.h` `CmdOp`: `ping` / `set-led RRGGBB` / `clear-led` / `beep` /
> `set-interval`, payload `op | target u32 | args`; `beep` is deferred to `loop()`
> since `playTone` blocks); the K10 acts only on a CMD addressed to it and ACKs it
> (`want_ack`), with `set-led` overriding the local warm/cool indicator until
> `clear-led`. `companion.py cmd --op set-led --rgb 0000FF` and `clear-led` both ACKed
> on attempt 1 on-device (over the K10's USB; the bridge-relayed CMD path was proven
> by `ping` over COM6). **Telemetry collect also works:** `CMD_GET_STATUS` → a node
> answers a STATUS `PERCEPT` (cursor, temp, warm/led/synced flags, epoch), and
> `companion.py monitor` prints a live refreshing table — verified on the K10 over
> COM3 (`@L10L0`, 31.9 °C, warm). This is the laptop **driving + observing** the fleet
> — the Phase 5 core. Remaining below is the full A→B→C spine + Dream-Cycle reconcile.

- [ ] V4-A firmware: bridge — USB-CDC ↔ LoRa/ESP-NOW; channel authority;
      trusted-core key holder.
- [x] Laptop orchestrator: **inject CMD toots** (`cmd`) + **collect telemetry**
      (`monitor`) over the bridge hop. The full A→B→C spine still pending (V4-B/V4-C).
- [ ] Master TTDB on the laptop; reconcile incoming BELIEF/PERCEPT.

**Done when:** a CMD toot from the laptop reaches cluster C and telemetry
returns end-to-end.

---

## Phase 6 — Channel convergence & Dream Cycle

> **Seed ✅ (2026-06-22): `reconcile` consolidates the fleet's sync logs.** The
> minimal first instance of the Dream Cycle: `companion.py reconcile` pulls each
> node's TTDB, folds the `@LAT99` sync records each node self-authored into one
> `master/consolidated.md` with provenance (per-source `recv_ms`/`offset_ms`), and
> confirms every node's logged `t_ms` agrees with the master. Verified on the K10
> over COM3 — both `id:1`/`id:2` consolidated `agree:yes`. Episodic node records →
> a semantic master record.

> **Push-back ✅ (2026-06-24): `push` distributes a re-authored belief back to a
> node (TTN-RFC-0009).** The propagation half of the Dream Cycle: `companion.py
> push` re-authors a belief TTDB from the consolidated sync knowledge, streams it as
> offset-addressed `want_ack TTDB_PUT` slices (reliable, CRC-32 whole-object
> integrity), and the node writes it to a separate `/belief.md`, CRC-verifies, and
> appends a `BELIEF-ADOPTED` record to its own live TTDB (`@LAT98` lane). Verified
> on the K10 — direct over USB **and bridge-relayed over ESP-NOW** (`--port COM6`).

> **Dream Cycle CLOSED ✅ (2026-06-24): a pushed belief changes node behavior.** The
> re-authored belief carries a `**DIRECTIVE** sense_interval_ms:<N>` record; on a
> CRC-verified commit the K10 parses `/belief.md` and retunes its sense→reason→act
> cadence, recording the effective rate as `applied:interval_ms` in its adoption
> record. Verified live on the K10 through the V4-A bridge (COM6): cadence went
> **1000 ms (boot) → 300 ms → 700 ms** as successive beliefs were pushed (measured
> over COM3 without resetting the node), each `push` confirming the change in-band.

- [ ] Switch ESP-NOW to the orchestrator AP channel; HELLO-beacon convergence
      outward from V4-A.
- [x] Re-author + push a node's belief over the link (`push`, TTN-RFC-0009) —
      laptop → K10 verified, **direct over USB and bridge-relayed over ESP-NOW**
      (`push --port COM6 --node k10_1`, 2026-06-24). The K10 defers a radio
      `TTDB_PUT`'s flash write to `loop()` (Phase 1b lesson). _Next: serve
      `/belief.md` back for a byte-level diff._
- [x] **A pushed belief changes node behavior** — the belief's `**DIRECTIVE**`
      retunes the K10's loop cadence (1000→300→700 ms), verified live (TTN-RFC-0009
      §5.2). The Dream Cycle's "Done when" condition.
- [ ] Run the Dream Cycle (`TTDB-RFC-0007`) to consolidate gossiped beliefs into
      the master TTDB; node-to-node BELIEF gossip once a 2nd percept node exists.

**Done when:** the orchestrator reconciles a multi-node belief and pushes an
updated TTDB to a node that changes its behavior. ✅ **Achieved 2026-06-24** —
`reconcile` consolidates, `push` distributes a belief whose directive retunes the
K10's cadence (1000→300→700 ms). Remaining items are multi-node (gated on V4-B/V4-C
+ a 2nd percept node) and channel convergence.

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
