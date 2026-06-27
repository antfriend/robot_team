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

**On Windows (the K10 dev machine) the real build path is `.vscode/tasks.json`**,
not the `.sh` scripts: tasks "Setup: UNIHIKER core" → "Compile K10" → "Upload K10"
→ "Upload K10 Filesystem". They call `arduino-cli` by full path
(`C:\Program Files\Arduino CLI\arduino-cli.exe`, from winget) because VSCode's
integrated terminal caches a stale PATH. The filesystem task runs
`scripts/Upload-K10-FS.ps1` (PowerShell) because arduino-cli can't upload a
LittleFS image — it builds one with `mklittlefs` and writes it with `esptool`.

FQBN per board: **the UNIHIKER K10 is `UNIHIKER:esp32:k10:CDCOnBoot=cdc`** (DFRobot
core via `--additional-urls .../package_unihiker_index.json`), *not*
`esp32:esp32:esp32s3`. The **`CDCOnBoot=cdc`** suffix is required: the board
default is CDC-on-boot *disabled*, which binds the sketch's `Serial` (and thus the
`TootSerialLink` that `companion.py` pulls over) to **UART0**, not the native USB —
so `companion.py pull` over USB-CDC gets nothing. With `CDCOnBoot=cdc`, `Serial`
is the native USB CDC on the COM port and the toot link works.

**K10 LCD = TFT_eSPI with K10 pins.** The K10 library hard-includes TFT_eSPI
(`#include "../TFT_eSPI/TFT_eSPI.h"`), whose pin map is **compile-time** in
`User_Setup.h`. arduino-cli resolves the *sketchbook* copy
(`~/Documents/Arduino/libraries/TFT_eSPI`) over the core-bundled one, so that
file must hold the K10 pins: `ILI9341, 240x320, TFT_MOSI 21, TFT_MISO -1,
TFT_SCLK 12, TFT_CS 14, TFT_DC 13, TFT_RST -1`. Generic ESP32-S3
defaults there (MOSI 11 / CS 10 / DC 46) leave the panel **backlit but blank** —
the firmware is fine, SPI is just wired to the wrong GPIOs. If a K10 renders
backlight-only, check those pins before touching sketch code.

**Do NOT define `TFT_BL` in that User_Setup.h.** `GPIO45` on the K10 is the **I2S
speaker** data line (`IIS_DOUT`), *not* the LCD backlight — the backlight is driven
by the DFRobot board lib via its abstract `eLCD_BLK` pin (through the mainboard power
chip). Setting `TFT_BL 45` makes `tft.begin()` (inside `k10.initScreen()`) seize
GPIO45 and hold it HIGH, which **silences `Music::playTone` for everything after
`initScreen()`** — the startup "toot" still plays (it runs *before* `initScreen`),
which is the tell. Leave `TFT_BL` undefined: the backlight still works and the speaker
keeps GPIO45. (A bad `TFT_BL 45` was the original cause of "only the startup toot is
audible.")

The Heltec V4 is `esp32:esp32:esp32s3`; set its PA variant per `hardware_specs.md`
(`USE_GC1109_PA` V4.2 / `USE_KCT8103L_PA` V4.3) once the LoRa path is enabled. The
K10's only LittleFS-capable partition is `model` (subtype spiffs, @0x510000),
mounted by label in the sketch.

The **Heltec V4** builds with arduino-cli directly (no VSCode task yet); it also
uses the ESP32-S3 native USB, so it needs `CDCOnBoot=cdc` too:

```bash
ACLI="/c/Program Files/Arduino CLI/arduino-cli.exe"
"$ACLI" compile --upload -p COM6 --fqbn "esp32:esp32:esp32s3:CDCOnBoot=cdc" \
        --libraries firmware/libraries firmware/v4a_bridge        # firmware
powershell -ExecutionPolicy Bypass -File scripts/Upload-V4-FS.ps1 \
        -Node v4a_bridge -Port COM6                               # TTDB image
```

The V4 uses the esp32 core's default 4MB partition (spiffs @0x290000, 0x160000);
`Upload-V4-FS.ps1` builds the LittleFS image with the **esp32** core's `mklittlefs`
(not UNIHIKER's) so the on-flash format matches. LoRa stays gated (`USE_LORA 0`),
so no PA-variant flag is needed until Phase 4.

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
- Every toot is HMAC-signed. The prototype key in `RobotTeamConfig.h` must match
  `companion.py`'s `NETWORK_KEY`.
- **Dedup is radio-only.** `(src_node_id, toot_seq)` dedup is applied on the
  ESP-NOW/LoRa receive path (replay + mesh forwarding-loop guard) but NOT on the
  trusted USB-CDC command link, so the laptop can retry a lost request. Gate dedup
  in the radio recv callback, never in the shared `handleToot` dispatch.
- ESP-NOW is the in-range default; LoRa is long-haul and gated behind `USE_LORA`
  until Phase 4. Don't add the radio before the ESP-NOW floor works.

## Tests

```bash
cd tests && make            # native KAT + codec tests (needs g++)
```

The native test pins SHA-256/HMAC to the same vectors `companion.py` produces,
so firmware and laptop authenticate identically.
