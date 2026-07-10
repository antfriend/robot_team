# PLAN.md — Building the Robot Team

Build plan for `robot_team`. The orchestration model lives in
[companion.md](companion.md) — read it first. This file is the **how and in what
order**; `companion.md` is the **who and why**.

**Goal:** a working swarm of A32 (ESP32) robots — 3× Heltec V4 LoRa spine
(bridge/relay/edge) + UNIHIKER K10 percept nodes + the T-Deck console —
coordinated by the laptop orchestrator, exchanging HMAC-signed toots,
consolidating beliefs via the Dream Cycle into a master TTDB. No cloud LLM on
any device. **Act I (Phases 0–7) builds that floor; Act II proves the primary
hypothesis on top of it: SEMANTIC POSITIONING** (`ttn-semantic-positioning.md`)
— the fleet infers its own physical arrangement from umwelt overlap, verified
against the T-Deck GPS, actuating automatic ESP-NOW↔LoRa transport selection,
and rendered as **TTCP network/node-status views on both the laptop and the
T-Deck** (the end goal).

**Strategy:** additive and bottom-up. Every phase ends with something that runs
and is verified. We never wire the long-range mesh before the in-range default
(ESP-NOW) works. Phases map onto the bring-up order in
`toot_network_architecture.md §6`.

---

## What's Next for antfriend

The software side is running ahead of the bench: SP2 just produced the fleet's
first self-map. The remaining moves all need **you and the hardware** — a human
in the room, a cable, or a walk outside. In priority order:

1. **Reality-check the first fleet map (2 min, no cable).** Open
   [master/positions.md](master/positions.md). It claims: V4-A at the origin,
   **K10 ~3.1 m** out, **V4-B ~3.9 m** and **T-Deck ~2.9 m** off to one side
   (~4.3 × 3.9 m room). Eyeball it, or stride-count one or two pairs. If it
   matches up to rotation/mirror, that's SP1's accuracy bar **and** SP2's sanity
   gate met in one glance — tell me "map checks out" or where it's wrong.
2. **T-Deck GPS bring-up — ▶ the software is built + green; it needs your cable +
   sky (2026-07-10).** The NMEA read and the `@BELIEF:POSITION` GPS-anchoring are
   done and offline-verified (`test_nmea` 27/27, `test_anchor_py` 20/20; T-Deck
   compiles at 78% flash). Your part now: (i) **flash the T-Deck** — plug into
   COM10, manual BOOT/RST (native-USB auto-reset is flaky), upload firmware **+
   the FS image** (`Upload-V4-FS.ps1 -Node tdeck_console`); (ii) **get a lock** —
   carry it to sky view; `companion.py gps --node tdeck_1 --port COM10` should
   print a fix (its screen shows one too), and until then honestly says "no fix";
   (iii) **walk the ties** — stand beside each static node and
   `companion.py gps --at <that-node>`, then `companion.py anchor`. **≥3
   non-collinear ties resolve the mirror** (`flip_resolved: false → true`) and
   start proof leg 1 (positioning scored against GPS, never fed into it). Tell me
   the baud it locked (screen shows it) if the fix never comes — the auto-probe
   tries 38400/9600/115200/57600.
3. **Be the flash-cycle partner when I have firmware ready.** The next few
   software steps each end in a per-node flash: the **BLE near-range tier**
   (SP0 leftover — tightens same-room sigmas), and **publishing positions back**
   to the nodes. Each needs you to plug in one node at a time (one cable on the
   bench) and, on the T-Deck, do the BOOT/RST dance.
4. **Later, gated on the above:** attach the LoRa antennas **before** powering
   the V4s (SX1262 PA safety, `hardware_specs.md`) when we un-gate `USE_LORA`
   for SP5; build the **V4-C edge** node (the 4th static anchor that breaks flip
   ambiguity without GPS); and, for Phase 7 / SP5, **walk a node out of ESP-NOW
   range** so the transport auto-switch has real distance to react to.

Everything else on the list I can build and offline-test solo (native `zig c++`
tests + arduino-cli compiles); I'll queue firmware so your cable time is batched.

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
Residual: ~1/6 runs dropped a frame (no ACK/retry yet). **Closed ✅ 2026-06-25:** the pull
stream is now self-healing — `companion.py request_ttdb` takes the EOF marker as the true
total length, detects gaps in offset coverage, and selectively re-requests the missing byte
ranges via `TTDB_REQ_RANGE` (which `handleRequest` already serves — no firmware change) until
byte-complete. Offline-gated by `tests/test_pull_py.py`; **on-device verified over COM3 and
bridged over COM6** with `pull --drop` (companion-side induced loss): `--drop 1,3` and
`--drop 0,14` each recovered a byte-exact 2843-B TTDB vs the clean baseline, exercising the
firmware `TTDB_REQ_RANGE` branch live for the first time. The bridged run re-requested the
gaps *over the air* through the V4-A bridge and recovered the same `ce3ca723…` bytes.

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
- [x] `Ttdb::appendRecord(text, len)` in `libraries/TTDB`: open the LittleFS
      `ttdb.md` in append mode, write a well-formed record block, close, re-run the
      offset index. Record uses a reserved time-log lane so it doesn't collide with
      the `collision_policy: reject` header — coordinate `@LAT99LON<sync_id>`:
      ```
      ---
      @LAT99LON<sync_id> | created:<T> | updated:<T> | relates:
      **SYNC** id:<sync_id> t_ms:<T> recv_ms:<millis> offset_ms:<T-millis>
      ```
- [x] Clock module: hold `gClockOffsetMs`; `nowEpochMs() = millis() + gClockOffsetMs`.
- [x] `handleToot`: on `TIME_SYNC` set the offset + `appendRecord`; on `TIME_REQ`
      reply `TIME_RESP(probe_id, nowEpochMs())`. Keep dedup **radio-only** as today.
- [x] Delivery: `TIME_SYNC` is fire-and-forget today (~5/6 bridged frames land),
      so resend it N times (or set `FLAG_WANT_ACK` once Phase 2 lands). The K10
      still serves replies from `loop()`, not the recv callback (Phase 1b lesson).

### Companion (`orchestrator/companion.py`)
- [x] `sync` subcommand: pick `sync_id` + `T = now_ms`, broadcast `TIME_SYNC` through
      the bridge port, and append the same record to the laptop master
      (`master/orchestrator-sync.md`) so the laptop is the 3rd "node."
- [x] `verify --sync-id N` subcommand, two assertions:
      1. **Has the record** — `pull` the K10 (through the bridge) and the V4-A
         (local), parse for a record with `id:N`; confirm laptop master has it too.
      2. **In sync** — NTP-lite per node: note `t0`, send `TIME_REQ`, read
         `TIME_RESP`, note `t1`; `skew = node_epoch − (t0 + (t1−t0)/2)`. Take the
         min-RTT sample of a few probes. Print a table: node | has_record | skew_ms.

**Done when:** after one `companion.py sync`, all three TTDBs (K10, V4-A, laptop
master) carry the same `sync_id` log record, and the NTP-lite probe shows the K10
and V4-A clocks within a stated bound (target: ≤ 50 ms) of the laptop. Reproducible.

> **Sibling milestone — Fleet Pulse & the band ✅ end-to-end on hardware
> (TTN-RFC-0010, 2026-06-26 → 2026-07-06).** Built on the time-sync layer: a
> self-synchronizing beat (shared pulse clock, first-up-conducts election with
> `era` handoff, drift-paced `PULSE` beacons — zero per-beat traffic). Verified:
> **3-node ensemble on one chart, phase skew ≤ ±10.4 ms** (`companion.py band`
> PASS), conductor reboot/handoff exercised live, then `Score.h` data-driven
> parts — K10 lead + T-Deck harmony playing the **two-part Ode to Joy duet at
> 120 BPM**, boot-silent and started/stopped via `CMD_PLAY`/`CMD_STOP`. Details
> and gotchas (tempo lives in `Pulse.h`; era latch survives reflashes): see
> `companion.md §6` + `@LAT90LON40`.

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

> **Handheld console added ✅ network floor on-device verified (2026-07-06): T-DECK-1.**
> A LilyGo T-Deck joins as a **portable operator console** — a mobile mini-orchestrator
> whose keyboard injects CMD toots and whose 320×240 screen shows the fleet, so the swarm
> is drivable without the laptop. `firmware/tdeck_console` (node id `0x200`) is built from
> the V4-B participant pattern; **verified on hardware** (COM10): boots from TTDB,
> `companion.py pull --node tdeck_1` reassembled a byte-exact 1351 B (sha `fd95360b…`) and
> `negchecks.py` rejected wrong-key/tampered toots (HMAC → 0 frames). Full Dream-Cycle
> participant (pull/HMAC, sync+`@LAT99`, belief+`@LAT98`, STATUS, PULSE follower);
> `companion.py` node map + `RobotTeamConfig` updated (`--node tdeck_1`). It also carries
> an SX1262 (LoRa-spine-capable, `USE_LORA`). **Flashing note:** native-USB auto-reset is
> flaky — manual BOOT/RST bootloader entry required (see `companion.md §6`).
> **Console UI ✅ on-device verified (2026-07-06, `USE_TDECK_HW 1`):** boot "toot toot"
> (I²S sine on the MAX98357A) + 320×240 fleet view (Adafruit_ST7789, runtime pins,
> rotation 3 — not TFT_eSPI); the keyboard is a **fleet remote** (`t` cycle target,
> `s` status / `p` ping / `b` beep / `g` play / `x` stop), verified live over the air
> through the V4-A bridge (bridged pull, STATUS, `sync` id=5). It also plays the harmony
> part of the 120 BPM duet and rejoins after a power-cycle (NVS-persisted song state).

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
      `TTDB_PUT`'s flash write to `loop()` (Phase 1b lesson). **Belief readback:**
      `push` now reads `/belief.md` back (`TTDB_REQ_BELIEF`) and confirms it
      byte-exact (1121 B), not just the CRC; also `pull --file belief`.
- [x] **A pushed belief changes node behavior** — the belief's `**DIRECTIVE**`
      retunes the K10's loop cadence (1000→300→700 ms), verified live (TTN-RFC-0009
      §5.2). The Dream Cycle's "Done when" condition.
- [ ] Run the Dream Cycle (`TTDB-RFC-0007`) to consolidate gossiped beliefs into
      the master TTDB; node-to-node BELIEF gossip **now unblocked — the T-Deck is
      the 2nd percept leaf** (K10 + T-Deck are the two percept authors; V4-A/V4-B
      are bridge/relay). The T-Deck already self-authors `@LAT97` link percepts
      (SP0) alongside its console role, so the two leaves can gossip beliefs
      directly rather than only via the laptop. **Unblocked ≠ built** — to make
      K10 ↔ T-Deck gossip actually run, these pieces are still missing:
      1. **A node-originated belief send path.** Today only `companion.py push`
         originates belief traffic (`TTDB_PUT` slices, laptop → node). A leaf needs
         to *transmit* — either address `TTDB_PUT` slices to a peer node id, or
         populate the so-far-unused `BELIEF` toot type (3) — rather than only
         answering the laptop's pulls.
      2. **On-device consolidation of its own percepts.** The `@LAT97` → `@BELIEF:
         PROXIMITY` fuse (median-of-window-maxes + sigma) currently lives in
         `companion.py proximity`, not on the node. Either the originating leaf
         fuses its own percepts on-device before gossiping, or the leaves gossip
         raw `@LAT97` percepts and the receiver fuses.
      3. **A receiving-node belief consumer.** `case BELIEF` is a no-op
         (k10_percept.ino:620-621, "nothing to do for the floor demo"; the
         reassembler notes "no large-toot consumer yet (Phase 6 BELIEF)"). The peer
         must actually *adopt* a gossiped belief — write it, attest it — instead of
         dropping it. `handlePutSlice` (belief-via-`TTDB_PUT`) exists, but it writes
         the laptop's `/belief.md`; a gossiped peer belief needs its own sink.
      4. **Merge / convergence semantics on-device.** When both leaves hold a belief
         about the same pair, the receiver must merge by TBEW (higher `conf`/`rev`
         wins, or evidence-combine) — the logic that lives in `companion.py
         reconcile` today has no on-device equivalent. Radio `(src,seq)` dedup guards
         the mesh loop, but belief *merge* needs its own idempotency (`rev`/`touched`)
         so re-gossiped beliefs converge instead of oscillating.
      5. **A gossip trigger + peer addressing.** A cadence (periodic, or
         post-consolidation) that sends to the peer leaf addressed node-to-node
         rather than to the laptop.
- [x] **3-node Dream Cycle ✅ on-device verified (2026-06-25)** — a 2nd Heltec V4 joined
      as **V4-B**, the third mesh node. `firmware/v4b_relay` is a full ESP-NOW participant
      (sync adopt + `@LAT99` append, deferred + paced TTDB serve, belief `TTDB_PUT` adopt +
      `@LAT98` attestation), built blind from the K10 + V4-A patterns — worked first try.
      Through the V4-A bridge: `sync`/`verify` across `v4a_bridge,v4b_relay,k10_1` within
      ±50 ms; `reconcile` folded **4 sources** (incl. laptop master), id:3/4 `agree:yes`;
      `push --node v4b_relay` landed belief id=9 byte-exact. Companion unchanged (already
      takes node lists). The laptop now reconciles **3 self-authoring sources**, not 1.
      (True node-to-node belief *gossip* has its 2nd percept leaf in the **T-Deck**
      — K10 + T-Deck are the two percept authors, V4-A/V4-B are bridge/relay — so
      the gossip path is unblocked, no longer waiting on new hardware.)

**Done when:** the orchestrator reconciles a multi-node belief and pushes an
updated TTDB to a node that changes its behavior. ✅ **Achieved 2026-06-24** —
`reconcile` consolidates, `push` distributes a belief whose directive retunes the
K10's cadence (1000→300→700 ms). Remaining items are node-to-node BELIEF gossip
(the **T-Deck is the 2nd percept leaf**, so this is unblocked — K10 ↔ T-Deck) and
channel convergence.

---

## Phase 7 — Field deployment

- [ ] V4-B at the midpoint on solar + external antenna; V4-C off-grid with GNSS.
- [ ] Verify end-to-end laptop ↔ cluster-C delivery in the field.

**Done when:** the fielded spine delivers toots both directions over real
distance, off-grid.

---

# Act II — Semantic Positioning (the primary hypothesis)

Spec: **`ttn-semantic-positioning.md`** (§0 states the hypothesis and its three
proof legs; §3 details each phase below). Adopted 2026-07-07 as the claim the
fleet exists to prove. Act I's remaining phases now *serve* Act II: Phase 3
(V4-C) adds the 4th static node that breaks flip ambiguity, Phase 4 (LoRa)
supplies the long rung SP5 switches to, Phase 7 (field) provides the distances
that make positioning non-trivial. Same additive strategy: every SP phase ends
with something measured.

## SP0 — Instrumentation (every frame becomes a percept)

- [x] Capture per-frame RSSI in each node's ESP-NOW recv callback — **built +
      compile-verified 2026-07-07** on V4-A / V4-B / T-Deck (`ESPNOW_RECV_CB_INFO`
      + `tootEspNowRssi` in `TootEspNow.h`, 3.x `rx_ctrl->rssi`; logged after
      HMAC verify, before dedup — a retried duplicate is a real reception). The
      **K10 is deferred**: its 2.x core's recv callback carries no RX metadata
      (needs the promiscuous-RX trick — a later sub-step; meanwhile the K10 is
      still *observed* by the three 3.x nodes, so its links are covered
      one-directionally). LoRa RSSI/SNR from the SX1262 once Phase 4 is up.
- [x] Batched accumulation + flush — **built**: `firmware/libraries/LinkPercept`
      keeps fixed per-peer RSSI *histograms* (~1.5 KB RAM, exact min/med/max, no
      per-packet flash writes) and flushes one `@LAT97LON<n>` TTDB record per
      window (default 60 s; `**LINKWIN**` context + one `**LINK**` line per
      peer/proto). Lane-capped (`LINKPERCEPT_MAX_LANE` 48) so the TTDB index
      can't fill before SP1 pruning exists. Format pinned by
      `tests/test_linkpercept.cpp` (g++ gate; this machine is device-first).
      Read back with **`companion.py percepts --node <n> --port <p>`**.
- [x] **On-device verify (the SP0 gate) ✅ 2026-07-07.** V4-A (COM6), V4-B
      (COM9), T-Deck (COM10) all flashed, hash-verified, byte-exact pull
      confirmed on each (regression: the new instrumentation didn't disturb
      the floor). `percepts` over the bridge shows every node logging real,
      **asymmetric** RSSI for every peer in one window: V4-A↔T-Deck (-60/-46/-36
      vs -49…-59/-42…-50/-37…-44), V4-A↔V4-B (-44/-34/-33 vs -47/-34/-32),
      V4-B↔T-Deck (-53/-29/-26 vs -38/-34/-30). Exactly the "distance
      measurement in disguise" the spec calls for — first real evidence.
- [ ] Piggyback each node's recent per-peer RSSI into existing beacons so both
      directions of every link are known (asymmetry is diagnostic).
- [~] **BLE advertise + scan as the near-range tier — BUILT + compile-verified
      2026-07-10** (motivated by the garden RSSI failure: an independent second
      ranging radio). Portable key-tagged advert codec in Toot
      (`build/parseBleAdvert`, native-tested) + ESP32 glue lib
      `firmware/libraries/BleLink` (advertise fleet id + passive duty-cycled scan →
      `LinkPercept` PROTO_BLE). Flows through the existing `(pair, proto)` proximity
      pipeline with zero new code (added a BLE path-loss default). Wired into
      V4-A/V4-B/T-Deck behind `USE_BLE`; **all fit the default partition** (V4-A 90 %,
      T-Deck 95 % — Bluedroid, no NimBLE/partition change). K10 deferred (2.x core).
      **Not yet flashed.**
- [ ] Duty-cycled WiFi scans (V4s) logging visible BSSIDs as `@PERCEPT:ENTITY`
      (the entity-co-occurrence tier — still to build).
- [ ] K10 RSSI capture via the 2.x promiscuous-RX workaround (or a core bump).

**Done when:** `pull` returns a percept lane with link + entity observations
from every powered node; verified with a serial dump. Pure plumbing, no inference.

## SP1 — Pairwise distance (calibration + consolidation)

- [x] **Calibration walk ✅ DONE 2026-07-07** ("walking range test"): V4-A fixed
      in the workroom, V4-B walked to 4 stations (strides ×0.75 m): workroom
      far side 3.75 m, hall end 9 m, deck 19.5 m NLOS, front yard 37.5 m,
      ~3 min dwell each; both directions logged. Fused per-station RSSI
      (median of window maxes): -33 / -54.8 / -67.5 / -82.5. **Fit
      (`companion.py calibrate` → `master/calibration.md`): RSSI(d) = −6.3 −
      48.4·log₁₀(d), n = 4.84, rmse 1.4 dB, valid 3.75–37.5 m** — through-wall
      home propagation (open air would be n≈2.7; recalibrate per environment).
      `proximity` now auto-loads it (calibrated sigma, no ×2 penalty). Bonus
      finding: the **ESP-NOW envelope ≈ −90 dBm** (frame counts collapse
      30→4/min) → model says the link dies at **~54 m through-house** — SP5's
      auto-switch threshold, measured. Also added `proximity --last N`
      (recency filter — the walk proved a moved node's stale windows pollute
      the fuse).
- [x] Consolidation job — **built + first live run 2026-07-07**:
      `companion.py proximity` pulls the fleet, fuses each pair's directional
      `@LAT97` windows (median of per-window `rssi_max` per direction,
      directions averaged; sigma from spread + asymmetry, ×2 while
      uncalibrated; the orchestrator pseudo-peer `0x1` excluded) into
      **`@BELIEF:PROXIMITY`** records in `master/proximity.md`. Offline gate:
      `tests/test_prox_py.py` (21 checks). **First fleet proximity map:**
      V4-A↔V4-B 0.34 m ±0.18 (n=282), V4-A↔T-Deck 1.21 m ±1.78 (n=303),
      V4-B↔T-Deck 0.26 m ±0.15 (n=352) — plausible bench geometry, and the
      triangle-inequality violation (0.34+0.26 < 1.21) is the expected
      uncalibrated-RSSI distortion, honestly covered by the wide sigma.
- [x] **Prune ✅ (2026-07-07): `CMD_CLEAR_PERCEPTS` (op 8) + `Ttdb::removeLane`**
      — streaming TTDB compaction (idempotent, ACK gated on success, radio path
      deferred to `loop()` like every flash write); `proximity --clear` closes
      the loop: pull → consolidate → prune consumed `@LAT97` lanes over the
      air. Verified live on all three nodes (V4-A over USB; V4-B + T-Deck
      **through the bridge over ESP-NOW**, ACK attempt 1) — also un-wedged
      V4-B from its 48-lane cap. **First full-loop run produced a 6-pair
      calibrated bench map (2.2–4.0 m, sigma 0.3–0.7 m) that includes the
      K10** — mapped one-directionally by the other nodes' observations, no
      K10 firmware change.
- [ ] Entity-Jaccard cap + BLE bound terms (gated on the SP0 entity/BLE
      sub-steps).

**Done when:** `dist_est_m` within ~30–50 % of tape-measure truth for every
powered pair, `sigma` honest. (Needs the calibration walk.)

## SP2 — Embedding + anchoring (position beliefs)

- [x] **Embedding solver ✅ built + first fleet self-map (2026-07-07):**
      `companion.py positions` — weighted spring relaxation (conf/sigma²
      weights, 8 random restarts to escape fold minima) over the
      `@BELIEF:PROXIMITY` matrix → **`@BELIEF:POSITION`** records
      (`master/positions.md`) in a canonical relative frame (V4-A origin, 2nd
      node +x, mirror flagged `flip_resolved: false` until GPS) + an ASCII
      fleet map. Offline gate `tests/test_embed_py.py` (10 checks: exact
      square recovery, honest stress on inconsistent input, outlier-weight
      immunity, parser round-trip, determinism). **First live embed: 4 nodes,
      6 pairs, stress 0.01 m** — worst pair-fit error 4 cm; the fleet's six
      independent distance beliefs agree on one 2D layout (~4.3 × 3.9 m bench).
- [~] **T-Deck GPS online as the roaming anchor + verifier** — NMEA read + the
      `anchor` fit are **built + offline-verified 2026-07-10, awaiting a sky-view
      flash session.** Portable `firmware/libraries/Gps` (GGA parser, checksum +
      hemisphere-signed, `test_nmea.cpp` 27/27); the T-Deck reads its u-blox on
      UART1 (GPIO44/43, auto-baud), shows the fix, and answers `CMD_GET_GPS`
      (op 9) with a 24-B GPS PERCEPT (compiles, 78% flash, not yet flashed).
      `companion.py gps [--at <node>]` records ground-truth ties; `companion.py
      anchor` fits the relative map onto them by 2D Procrustes (reflection
      allowed) → absolute lat/lon `@BELIEF:POSITION` in `master/anchored.md`,
      **flip resolved with ≥3 non-collinear ties** (2 ties emit `flip_resolved:
      false`, honest). `test_anchor_py.py` 20/20 (3-tie recovers geo within
      0.3 cm). GPS is verifier+anchor only, never an inference input.
      **READ ✅ LIVE ON HARDWARE 2026-07-10 (T-Deck COM10):** flashed first try,
      `gps --node tdeck_1` returned a clean 12-sat lock indoors (43.65248,
      -116.33647, HDOP 1.1) — auto-baud + NMEA decode + `CMD_GET_GPS` round-trip
      all verified on real signal. **Pending:** walk the ties (`gps --at`) +
      `anchor` to resolve the mirror.
- [ ] Publish `@BELIEF:POSITION` back to each node over the mesh.

**Done when:** the embedded map recovers the bench/yard geometry within stated
`sigma`, scored against T-Deck GPS fixes (GPS is the verifier, never an input).

## SP3 — Environmental TDoA (directional evidence; parallelizable)

- [ ] Onset detection on temp/light/pressure channels → `@PERCEPT:ENV`;
      cross-correlate onsets across nodes (slow fronts first — the ±ms
      TTN-RFC-0008 sync is already sufficient).

## SP4 — Position as living belief (address loop)

- [ ] High-`conf` position disagreeing with the configured `@LATxLONy` raises a
      revision event (flag-for-operator default); movement detection via
      `touched` decay → re-embedding.

## SP5 — Transport auto-switch (proof leg 2: actuation)

- [ ] Per-peer transport choice from belief: ESP-NOW when `dist_est + k·sigma`
      fits the calibrated envelope and percepts are fresh, else **LoRa**
      (un-gates `USE_LORA`, Phase 4). Hysteresis mandatory; switch events are
      logged percepts so the Dream Cycle audits its own choices.

**Done when:** a pair walked out of ESP-NOW range falls back to LoRa *before*
delivery dies and returns when back in range — zero manual transport config.

## SP6 — TTCP rendering (proof leg 3: the payoff render, the end goal)

- [ ] **Laptop:** master TTDB (+ proximity/position beliefs, node status:
      last-seen, skew, transport, `conf`/`sigma`) rendered in the browser per
      `RFCs/TTCP-RFC-0001..0003` — the working example is
      [antfriend.github.io](https://github.com/antfriend/antfriend.github.io)
      (dependency-free JS viewer, loads `?ttdb=<file>.md`); this leg is
      authoring discipline, not new renderer code.
- [ ] **T-Deck:** native TTCP mini-renderer on the 320×240, grown from the
      console fleet view — nodes at believed `@LATxLONy` with `sigma` circles,
      edges colored by transport + link health, trackball cursor
      (TTCP-RFC-0002), keyboard keeps the CMD-remote role.

**Done when:** laptop and T-Deck render the same fleet state from the same TTDB
lineage, and physically rearranging the bench shows up on both screens within a
stated number of Dream Cycles. **This is the project's end goal.**

---

> **Cross-cutting ✅ (2026-07-08): the RFC corpus is now fleet-carryable.**
> `RFCs/rfc.ttdb.md` semantically compresses the 28-file, ~266 KB RFC corpus
> **8.4:1** into one conformant TTDB — one record per RFC (normative gist +
> `depends_on` edge graph + `[ew]` status/salience), each record's `src:` line
> its deterministic expansion target (TTN-RFC-0004 applied to itself), plus a
> `lat-98` belief lane recording where implemented reality diverges from spec
> text (arduino-cli vs PlatformIO, radio-only dedup, defer-to-loop, …).
> `tests/test_rfc_ttdb.cpp` streams the real file through the firmware's
> *unmodified* `TtdbParse.cpp` and replicates `Ttdb::begin()`'s two-pass index —
> 33/33 records, all 79 edges resolve, headers fit the 256 B on-device line cap,
> spans tile the file — so the compression stays verified as the RFCs evolve.
> Side effect worth noting: this brought up a **working native test toolchain
> (portable `zig c++`)** on the dev machine, retiring the long-standing "no
> compiler here" caveat — `test_toot` / `test_linkpercept` / `test_rfc_ttdb` now
> actually run off-device. A robot can carry its own governing specs; the same
> record is directly TTCP-renderable (foreshadows SP6).

---

## Definition of Done (every phase)

1. Native tests pass (`tests/`, `make` or portable `zig c++` — SHA/HMAC, codec,
   TTDB parse, RFC round-trip) where logic is testable off-device.
2. On-device serial assertions pass for hardware-bound behavior.
3. The relevant A32 agent contract items (`companion.md §3`) hold.
4. `companion.md §2` fleet status and `§6` next-action are updated.

## Conventions

- One TTDB file per node role in `data/` (`k10.md`, `v4a.md`, …); laptop holds
  the master.
- Firmware version (platformio build flags) and TTDB version (`mmpdb.db_id`)
  version independently (`A32-RFC-0004 §7`).
- New edge types or toot types get an RFC in `RFCs/` before code depends on them.
