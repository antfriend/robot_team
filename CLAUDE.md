# CLAUDE.md — robot_team

## What this is

A team of autonomous **ESP32 robots** (A32 agents) coordinated by a laptop
**companion**. Each robot reasons from a Toot-Toot Database (TTDB) markdown file
on its filesystem — no cloud LLM, no neural inference. Start every session by
reading [companion.md](companion.md); it is the orchestrator and source of truth.
The build roadmap is [PLAN.md](PLAN.md).

## Layout

```
companion.md            Orchestrator brain (read first)
PLAN.md                 Phased build plan
firmware/
  libraries/            Shared Arduino libs (added per-build via --libraries)
    Toot/               Wire frame + portable SHA-256/HMAC + dedup + serial link
    TTDB/               Streaming TTDB reader + TtdbShare (TTDB-over-network)
    Agent32/            Sense-reason-act loop scaffold
    RobotTeamConfig/    Shared key, channel, node ids
  k10_percept/          arduino-cli sketch + data/ttdb.md  (Phase 1 node)
  v4a_bridge/  v4b_relay/  v4c_edge/   LoRa spine sketches (LoRa gated off)
orchestrator/companion.py   Laptop side: pull a node's TTDB over the link
scripts/                setup / build / deploy / upload-fs (arduino-cli)
tests/                  Native test for the portable libs (g++ + make)
RFCs/                   Governing specs (A32, TTDB, TTN, TTCP)
```

## Build & deploy — arduino-cli (not PlatformIO)

This project deploys with **command-line Arduino** (`arduino-cli`). The A32 RFCs
describe PlatformIO; here, arduino-cli is the chosen path. Each node is a proper
Arduino sketch (`firmware/<node>/<node>.ino`); shared code lives in
`firmware/libraries/` and is supplied with `--libraries` at compile time.

```bash
scripts/setup.sh                          # install esp32 core (once)
scripts/build.sh  k10_percept             # compile
scripts/deploy.sh k10_percept COM5        # compile + flash firmware
scripts/upload-fs.sh k10_percept COM5     # build + flash data/ttdb.md to LittleFS
```

FQBN defaults to `esp32:esp32:esp32s3` (both the K10 and Heltec V4 are S3). For
the Heltec V4, set the PA variant per `hardware_specs.md` (`USE_GC1109_PA` V4.2 /
`USE_KCT8103L_PA` V4.3) once the LoRa path is enabled.

## TTDB on the filesystem, shared over the network

- The TTDB is plain markdown in `firmware/<node>/data/ttdb.md`, flashed to
  LittleFS. The firmware **streams** it (offset index, on-demand seeks) and
  never loads it whole (`A32-RFC-0002`).
- Any node can **share any or all of its TTDB** with the companion: a `TTDB_REQ`
  toot (whole file or a byte range, addressed to a node id) makes the node
  stream `TTDB_DATA` toots back — each an offset-addressed, HMAC-signed slice —
  over ESP-NOW, LoRa, or USB-CDC serial. `orchestrator/companion.py pull`
  reassembles them into the laptop's master copy. See `TTDB/src/TtdbShare.*`.

## Constraints

- Target ESP32-S3, Arduino framework. RAM is tight: stream the TTDB, feed the
  watchdog (`yield()` in long loops), prefer fixed buffers over `String`.
- Every toot is HMAC-signed and dedup-keyed on `(src_node_id, toot_seq)`. The
  prototype key in `RobotTeamConfig.h` must match `companion.py`'s `NETWORK_KEY`.
- ESP-NOW is the in-range default; LoRa is long-haul and gated behind `USE_LORA`
  until Phase 4. Don't add the radio before the ESP-NOW floor works.

## Tests

```bash
cd tests && make            # native KAT + codec tests (needs g++)
```

The native test pins SHA-256/HMAC to the same vectors `companion.py` produces,
so firmware and laptop authenticate identically.
