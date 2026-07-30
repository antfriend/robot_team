# CLAUDE.md — robot_team

## What this is

A team of autonomous **ESP32 robots** (A32 agents) coordinated by a laptop
**companion**. Each robot reasons from a Toot-Toot Database (TTDB) markdown file
on its filesystem — no cloud LLM, no neural inference. Start every session by
reading [companion.md](companion.md); it is the orchestrator and source of truth.
The build roadmap is [PLAN.md](PLAN.md). The **primary hypothesis** the fleet
exists to prove is **semantic positioning**
([ttn-semantic-positioning.md](ttn-semantic-positioning.md)): infer node
positions from umwelt overlap, verify against the T-Deck GPS, auto-switch links
ESP-NOW ↔ LoRa from the resulting beliefs, and render fleet/node status as TTCP
on the laptop and the T-Deck (PLAN.md Act II).

## Layout

```
companion.md            Orchestrator brain (read first)
PLAN.md                 Phased build plan (Act I floor -> Act II hypothesis)
ttn-semantic-positioning.md   The primary hypothesis + its proof legs
firmware/
  libraries/            Shared Arduino libs (added per-build via --libraries)
    Toot/               Wire frame + portable SHA-256/HMAC + dedup + serial link
    TTDB/               Streaming TTDB reader + TtdbShare (TTDB-over-network)
    Agent32/            Sense-reason-act loop scaffold
    Pulse/              Band time-base: pulse-clock election + beat/step
                        sequencer + Score.h note tables (TTN-RFC-0010)
    LinkPercept/        SP0 positioning evidence: per-peer RSSI histograms ->
                        @LAT97 TTDB records (ttn-semantic-positioning.md)
    EntityPercept/      SP0 entity tier: duty-cycled WiFi BSSID sightings ->
                        @LAT96 records; Jaccard overlap = coarse proximity bound
    MotionPercept/      SP0 motion tier: accelerometer windows -> @LAT95 still|moving
                        (makes "the observer held still" checkable, not assumed)
    AcousticPercept/    SP0 acoustic tier: mic windows -> @LAT94, incl. the fleet-clock
                        timestamp of the loudest transient (Phase 3 TDoA groundwork)
    Es8311/             Cardputer ADV audio-codec bring-up (speaker AND mic)
    RobotTeamConfig/    Shared key, channel, node ids
  k10_percept/          arduino-cli sketch + data/ttdb.md  (percept leaf + band lead)
  v4a_bridge/  v4b_relay/  v4c_edge/   LoRa spine sketches (LoRa gated off)
  tdeck_console/        LilyGo T-Deck handheld console (fleet remote + harmony voice)
  cardputer_console/    M5Stack Cardputer ADV — 2nd handheld + the fleet's motion and
                        acoustic senses (BMI270 + ES8311 mic); no LoRa, no GPS
orchestrator/companion.py   Laptop side: pull/sync/verify/reconcile/push/cmd/
                            monitor/band over the link
master/                 Laptop-side artifacts: consolidated + belief TTDBs, logs
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
so no PA-variant flag is needed until Phase 4. Both V4 sketches are at **93–94% of the
default app partition** — near the ceiling the T-Deck hit, so the next feature added to
them probably needs `huge_app` first.

⚠ **`pull` a V4 over its OWN cable, not through the V4-A bridge.** The bridged path
(laptop → V4-A → air → V4-B) now fails on a full TTDB: no data, or a truncated/gappy
file. It is **not** a firmware regression — control-tested by reflashing both V4s from
HEAD, which failed identically. V4-B's TTDB has grown 858 B → 54 KB on unpruned percept
lanes, and ~270 ESP-NOW frames across a busy mesh is a different job from ~5. The direct
pull on the node's own port is byte-exact and repeatable (companion.md §6).

As of 2026-07-30 both V4s answer **`CMD_GET_INTERO` (op 12)** and **`CMD_DUET` (op 13)**,
so the T-Deck's record pane and its `d` key work against the spine, not just the two
consoles (user-confirmed from the T-Deck against both V4s, audibly). Note the V4s need
**no conductor-gate exception for the duet** — their voice was never gated on the baton
the way a console's is.

⚠ **The V4's battery divider enable `GPIO37` is ACTIVE HIGH — the opposite of the V3's
documented active-LOW `ADC_Ctrl`.** Vbat is `GPIO1` (as published) behind it, `BAT_DIVIDER
4.9`. Driving GPIO37 **LOW disconnects the divider** and the node reads a flat **0.000 V**
with a perfectly good pack attached — which is what the first build of this did. Found by
sweeping every ADC1 pin (GPIO1–10) against each candidate control pin in LOW/HIGH/floating
with WiFi/LoRa/I2S/OLED left uninitialised (`scratchpad/v4_adc_probe/`); GPIO1 read 827 mV
only with GPIO37 HIGH. Verified: V4-A 4.096 V/89%, V4-B 3.831 V/52%, both rising on charge.
`BAT_DIVIDER` itself is still unmetered — the first `[intero]` line prints raw pin mV.

⚠ **Do not use `gBatMv != 0` as the "have I sampled" flag** (use `gBatSampled`): 0 mV is a
legitimate reading, and using a measurement as its own validity flag made the sampler
re-run and re-print every loop pass — a serial flood that reported as a 2–4 s worst loop
pass. All four nodes carry `gBatSampled` as of 2026-07-30.

⚠ **`lp` (worst loop pass) is a 10-second-window number, so sampling it late reads clean.**
Every node shows a multi-second stall reliably at boot and occasionally later, then single-
or double-digit ms; a series started at 77 s of uptime misses it entirely and looks like a
fix. State the uptime range with any claim about it. `companion.py intero` also **resets the
node on port open**, so looping it can never see past the ~8 s settle — watch windowed
numbers over one held connection (`scratchpad/intero_watch.py`).

⚠ **That stall is NOT in any sketch's loop body — stop looking there.** The Cardputer's
section profiler caught `worst pass 2009ms (widest section render 6ms)`: the nine sections
do not account for the time, so the loop task is being **descheduled between iterations**.
The **async WiFi scan is exonerated** by direct observation (a scan completed with the loop
at 10 ms on both sides). Next instrument is FreeRTOS-level, not another section.

The **LilyGo T-Deck** (`firmware/tdeck_console`) builds like the V4
(`esp32:esp32:esp32s3:CDCOnBoot=cdc`) **but on the `huge_app` partition scheme**, so
its SP6-T screen UI + BLE fit (the default 4 MB scheme left the app at 95%). **Flash
its FS with `scripts/Upload-Tdeck-FS.ps1 -Node tdeck_console -Port <COMx>`, NOT
`Upload-V4-FS.ps1`** — huge_app puts the LittleFS partition at **0x310000** (size
0xE0000), whereas the V4 script writes to the default **0x290000**. Flashing the FS
at the wrong offset drops the LittleFS superblock in the app region and garbage on the
real spiffs partition, so the mount fails silently and the node boots to an **empty
globe / "(no record selected)"** with the app otherwise fine — recover by re-flashing
with the correct Tdeck script. Plus three T-Deck-specific rules: (1) **flashing
needs manual bootloader entry** (native-USB auto-reset is flaky) — hold the
trackball-click (GPIO0/BOOT) + tap RST to enter download mode (the port
re-enumerates), then tap RST alone to boot the app; (2) its **ST7789 display uses
Adafruit_ST7789 with runtime pins** (`arduino-cli lib install "Adafruit ST7735 and
ST7789 Library"`), deliberately NOT TFT_eSPI, so it never touches the K10's shared
`User_Setup.h`; (3) **GPIO10 must be driven HIGH** first or the LCD/keyboard/LoRa/SD
are unpowered. Audio is I²S (MAX98357A) via the core's `ESP_I2S` — no analog tone path.

The **M5Stack Cardputer ADV** (`firmware/cardputer_console`, node `0x300`) is the second
handheld and builds like the T-Deck — `esp32:esp32:esp32s3:CDCOnBoot=cdc` on **huge_app**,
plus `FlashSize=8M` (the ADV has 8 MB; huge_app only describes the first 4 MB, which is
deliberate so its FS offset matches the T-Deck's). Flash its FS with
**`scripts/Upload-Cardputer-FS.ps1`** (spiffs @0x310000) — same three globes as the T-Deck.
Unlike the T-Deck its **auto-reset works**: plain `arduino-cli compile --upload -p COMx` with
no BOOT/RST dance. Board-specific rules:
1. **Everything hangs off one I2C bus** (SDA 8 / SCL 9): keyboard **0x34**, codec **0x18**,
   IMU **0x69** — the BMI270 is at the *secondary* address, NOT the 0x68 the published pin map
   implies (first boot printed `BMI270 NOT FOUND`). The sketch tries both and, on failure,
   prints an I2C bus scan; read that before touching pin constants.
2. **The keyboard is a TCA8418 matrix scanner**, not a keyboard MCU handing over ASCII. It
   boots asleep — it does nothing until `KP_GPIO1/2/3` + `CFG` are written. Key numbers are
   `col*10 + row + 1` over a 7-col × 8-row matrix, and the physical rows interleave TCA rows,
   so the keycode→character map in the sketch is **tabulated, not derived** — if a key does
   the wrong thing, fix the table, not the decode.
3. **Audio goes through an ES8311 codec** (`firmware/libraries/Es8311`), so the speaker AND the
   mic are dead until its registers are written. The board routes **no MCLK**, so the codec is
   configured to derive MCLK from BCLK — which only holds while the I2S bus runs **16-bit
   stereo** (BCLK = 32·fs). Don't switch it to mono or another bit width without revisiting
   `Es8311.cpp`. ⚠ **DAC volume (reg 0x32) is 0.5 dB/step with unity at `0xBF`, NOT a linear
   0..255 loudness control** — above 0xBF is digital gain (to +32 dB at 0xFF) that clips a
   full-scale source rather than raising it. `setVolume(100)` therefore scales to 0xBF, not
   0xFF. Tone amplitude is **30000/32767**, deliberately just under full scale because a square
   overshoots its edges ~9% through the reconstruction filter. The boot line
   `[codec] DAC vol reg 0x32 = 0x..` reads the register back — **a volume that silently failed
   to take looks exactly like a speaker that is just small.**
4. The display is an **ST7789V2 240×135 on its own SPI** (SCLK 36 / MOSI 35 / CS 37 / DC 34 /
   RST 33 / BL 38), driven by Adafruit_ST7789 with runtime pins — same reasoning as the T-Deck,
   so it never touches the K10's shared `User_Setup.h`. Use `init(135,240)` +
   **`setRotation(3)`**; rotation 1 renders upside-down, exactly as it did on the T-Deck.

The T-Deck now carries **three globes** flashed as three files in `data/` (all picked up by
`Upload-Tdeck-FS.ps1` since it images the whole dir): `ttdb.md` (the mesh fleet globe),
`rfc.ttdb.md` (the RFC corpus), and **`feelings.ttdb.md` (the affective landscape + band
overlay — the DEFAULT power-up view)**. The trackball click cycles Feelings → SemPos → RFC,
skipping any file that failed to load; only `ttdb.md` touches the mesh. If the feelings globe
boots empty, `feelings.ttdb.md` wasn't flashed (re-run `Upload-Tdeck-FS.ps1`).

**On SemPos (the mesh map) the record pane renders the selected node's INTEROCEPTION**, not
record text: BAT/DIE/MEM gauges + a footer (uptime · `lp` worst loop pass · bpm · conductor ·
clk). Its own body comes from a local sampler; every other node's arrives as a 21-byte **INTERO
PERCEPT** answering **`CMD_GET_INTERO` (op 12)**, polled every 3 s *only* while that record is
selected and the main pane is showing. INTERO PERCEPT is a payload convention over the existing
PERCEPT type distinguished by **length** (15/43/45 STATUS · 24 GPS · **21 INTERO**) — no new toot
type, so the bridge already forwards it. Transmit the numbers, never the pixels: the receiver has
a different panel and palette, which is what makes this a TTCP render. Read it from the laptop
with `companion.py intero --node <n> --port <p>`. **`d` starts a DUET with the node the pane is
showing** (`CMD_DUET` op 13, `partner u32 | role u8`): T-Deck leads, partner harmonises, both
from HeroArc.h's finale pairing. A duet is **not** a chart scene — a scene is band-wide and would
pull in every powered member — it overrides only the two participants' *parts* and leaves the
scene alone. ⚠ It also **must** bypass the `!gPulse.conductor()` play gate, or it is always a
solo: with just the two handhelds powered one of them conducts and it is the T-Deck (lower id),
i.e. the lead. That exception is safe *only* for a duet (a conductor is the phase reference); do
not widen it to the hero's-arc song, where the gate stops a self-appointed node playing out of
phase. Confirm a duet by the partner's **`INTERO_VOICING`** bit (pane footer shows `SINGING`),
never by an ACK — a blocking tone call eats the ACK window.

⚠ **`CMD_DUET` is NOT sent once — a live duet is re-asserted every 2 s and a dismissal repeated
3×** (`serviceDuet`). A single ESP-NOW invitation gets dropped, and when it does the console sings
the lead alone at a partner that never heard the ask (observed on hardware). Repeating idempotent
state beats want_ack here: it also rejoins a partner that rebooted mid-duet and self-corrects a
speed disagreement, which a retry would not. Receipt logging is change-only, so repeats are
silent — don't "optimise" the repeat away.

The duet plays in **double time**, and that is a *part* property, not a tempo change: `speed`
rides on `CMD_DUET` (additive byte; absent = as written) and the pair covers the phrase in
`steps/speed` slots, looking notes up at `sip*speed`. **The beat period is untouched**, so the
duet stays locked to the pulse the rest of the fleet counts — changing the chart tempo instead
would drag the whole band along and needs a fleet cold-start. `DUET_DEFAULT_SPEED` (T-Deck) is
the one line to change; ⚠ **`score::noteAt` is an exact step match**, so a speed that puts a note
between slots would silently drop it — `kOdeLead`'s tied note at step 54 survives ÷2 but not ÷4 —
hence `validDuetSpeed` refuses and falls back to 1. To verify a rate change, measure the
**step-0 → step-0 interval** off the node's own `[part]` prints; do NOT divide note-count by
notes-per-phrase (invalid unless the window aligns to phrase boundaries) and do not trust
per-note serial gaps (CDC buffering shows 100 ms gaps on a 125 ms grid). The mesh map holds **V4-A, V4-B, T-Deck and the
Cardputer as of 2026-07-29 — the K10 was removed** (v1 firmware, off the band roster). ⚠ The
T-Deck's own `PIN_BAT_ADC 4` / `BAT_DIVIDER 2.0` come from LilyGo's `utilities.h`, NOT a meter:
it reads **4.71 V**, above the 4.20 V Li-ion ceiling, so above that ceiling the node withholds
the percentage instead of inventing one. A meter on the JST lead settles it; it is one constant.

Separately, the
**self-walking hero's-arc song** (`g` auto-advances scenes and holds at the grief for the
returning T-Deck) lives in the **shared `Pulse` engine** (`armSong`/`serviceSong`) + `HeroArc.h`
pacing, so enabling it means **reflashing the whole fleet** (K10 + all three V4s + T-Deck), not
just the T-Deck — the conductor is whichever node holds the baton, and every node must know how
to walk the story and where the grief gate is.

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
