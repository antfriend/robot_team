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
    LaneGen/            Lane generations (@LAT100): a prune writes down the boundary it
                        creates, so the ordinal citations into the pruned lane
                        (`derived_from@LAT97LON1`) stay readable as history instead of
                        silently resolving into the generation that followed.
                        LaneGenNode.h is the Arduino glue (one copy, five sketches).
    TimeStream/         The team time stream: a fleet-owned timeline that survives the
                        laptop's absence. `stream:<id>` + `wall:<0|1>` replacing the old
                        single `synced` bit; anchors ride on HELLO; @LAT90 logs timeline
                        CHANGES. TimeStreamNode.h is the Arduino glue (one copy, six
                        sketches).
    Social/             The default network (default-network.md): capability advertisement
                        with a THREE-level status (declared/verified/exercised), riding as a
                        third HELLO block after the anchor and the trace digest. Not an
                        inventory — it is the list of who can collapse which positioning
                        ambiguity, so `poseCeiling()` is the fleet stating how much of its
                        own shape it can currently know. Also carries the fleet's FIRST
                        FIELD lane, `@LAT101` (RFC-0010 §5 stage 3): one **PEER**
                        co-presence trace per peer, decay-on-read, reclaim-lowest, NO
                        prune path by design — the RAM table is the live medium and the
                        lane its change-triggered durable shadow. SocialNode.h is the glue.
    Es8311/             Cardputer ADV audio-codec bring-up (speaker AND mic)
    RobotTeamConfig/    Shared key, channel, node ids
  k10_percept/          arduino-cli sketch + data/ttdb.md  (percept leaf + band lead)
  v4a_bridge/  v4b_relay/  v4c_edge/   LoRa spine sketches (LoRa gated off)
  tdeck_console/        LilyGo T-Deck handheld console (fleet remote + harmony voice)
  cardputer_console/    M5Stack Cardputer ADV — 2nd handheld + the fleet's motion and
                        acoustic senses (BMI270 + ES8311 mic); no LoRa, no GPS
orchestrator/companion.py   Laptop side: pull/sync/verify/reconcile/push/cmd/
                            monitor/band over the link
orchestrator/fleet_ui.py    The same fleet in one tkinter window: link status, live
                            intero table, position map, lane caps + Clear. Holds ONE
                            connection per link (open_serial_no_reset) instead of
                            resetting the node on every refresh the way the CLI does.
master/                 Laptop-side artifacts: consolidated + belief TTDBs, logs
master/ui/              TTDBs pulled by fleet_ui.py, kept out of the curated set
scripts/                setup / build / deploy / upload-fs (arduino-cli)
tests/                  Native test for the portable libs (g++ + make)
replicate/              Open-source publication front door (README + the spec store)
  RFCs/                 Governing specs (A32, TTDB, TTN, TTCP) — MOVED here from the
                        repo root on 2026-07-31; `replicate/RFCs/rfc.ttdb.md` is the
                        canonical corpus the handhelds carry in their data/ dirs
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
so no PA-variant flag is needed until Phase 4. All three V4 sketches are at **94% of the
default app partition** (~71–74 KB left) — near the ceiling the T-Deck hit, so the next
feature added to them probably needs `huge_app` first.

⚠ **The three V4s are indistinguishable from the outside, and flashing the wrong sketch
to one is silent. Identify a board by READING ITS APP IMAGE, never by inferring from the
mesh.** COM numbers move between plug-ins, and a `companion.py intero`/`ping` reply can
arrive **over the air** from a battery-powered node, so an answer on a port proves
nothing about which board that port is. These boards also print **nothing** on serial at
any DTR/RTS setting and do not visibly reset when the port is opened, so there is no
banner to read. What works (~17 s):

```bash
python -m esptool --chip esp32s3 --port COMx --baud 460800 \
       read-flash 0x10000 0x80000 app.bin        # 12 s, 512 KB is enough
# grep the image for the sketch's own banner literal:
#   "V4-A bridge" | "V4-B relay" | "V4-C edge" | "Cardputer console" | "T-Deck"
# and for "older_stream_wins" to tell whether it predates the time stream.
```
⚠ **THE GREP CAN RETURN MORE THAN ONE BANNER, AND THE EXTRA ONES ARE NOT THE BOARD.** A
node's image contains OTHER nodes' names because it renders them — the Cardputer's read
back both `Cardputer console` **and** `T-Deck` (2026-08-10). The discriminator is the
sketch's **own** banner, i.e. the one matching the FQBN/partition scheme you are about to
flash; treat any additional hit as a peer label, not a second identity. A read that returns
zero banners is the real alarm.
📎 Useful second grep on the same image: a **string that only today's build contains** tells
you whether a board is current without decoding a version. `"@LAT96 lane FULL"` dates a
build to 2026-08-10 or later; `"MEASUREMENT BUILD (no folding)"` proves a
`-DENTITYPERCEPT_MAX_RUN=1` measurement build, which is otherwise invisible from outside.

⚠ **Read 0x80000 at 460800, not the whole 0x140000 at 921600.** The full-image read at
921600 died mid-transfer with `A fatal error occurred: Corrupt data, expected 0x1000
bytes but received 0xe85 bytes` at ~9% and **left no file at all** (2026-08-06, both
boards, repeatable). ⚠ **And the 0x80000-at-460800 fallback is not immune: it failed the
same way on the Cardputer** (2026-08-10, `received 0xe4a bytes`, no file). `0x40000` at
**230400** completed and still carried every string that mattered. The rule generalises —
**halve the bytes and halve the baud until it completes**; the banners live in the DROM
that maps first, so a 256 KB window is still plenty. The banner literals live in the DROM/`.rodata` segment that maps
first, so the leading **512 KB** carries them — a `V4-A bridge` and a `Cardputer console`
were both found in that window. Half the bytes at half the baud, and it completes.
📎 `flash-id` (3 s) is a useful *pre-filter* on this fleet but never a substitute:
measured, the Cardputer reads **8 MB embedded (GD), no PSRAM** and V4-A reads **16 MB +
2 MB embedded PSRAM**. That separates those two, but the T-Deck is also a 16 MB part and
the other two V4s are unmeasured — so flash size narrows, the banner decides.

⚠ The obvious shortcut does **not** work: `esp_app_desc_t.project_name` (at
`0x10000+0x50`) reads **`arduino-lib-builder`** on every arduino-cli build — that is the
*core's* name, not the sketch's, and the adjacent `date/time` is the core's build date.
Only the sketch's own string literals tell the boards apart.

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
numbers over one held connection (`scratchpad/intero_watch.py`). ⚠ **But that reset is not
universal: on a V4 the port open did NOT reset the board** (2026-08-03, n=1 — V4-C reported
`up 4m12s` and `lp 35 ms` on a connection opened minutes after it was plugged in, and no V4
reprinted a banner at any DTR/RTS setting). So on a V4, `intero`'s uptime is real and the
~8 s-settle caveat does not apply; on the handhelds it does. Do not assume either way —
check the reported uptime against when you plugged the board in.

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
may need manual bootloader entry** (native-USB auto-reset is flaky) — hold the
trackball-click (GPIO0/BOOT) + tap RST to enter download mode (the port
re-enumerates), then tap RST alone to boot the app. ⚠ **But TRY THE AUTOMATIC PATH
FIRST:** on 2026-08-03 `esptool --chip esp32s3 --port COMx chip-id` entered the
bootloader unaided and `arduino-cli compile --upload` then flashed hands-free. One clean
success does not disprove intermittence, so keep the dance as the fallback — just don't
reach for it by default, and don't ask the operator to hold a button before trying;
(2) its **ST7789 display uses
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

**Record pane paging (both handhelds, 2026-08-02).** `renderRecord` used to read a record
body into a **520 B buffer** — a *read* limit, not a scroll limit: bytes past it never left
flash. RFC-globe records average 1036 B and reach **2666 B**, so the T-Deck showed the first
~40% of one and the Cardputer (four lines × 39 cols) ~15%, **with nothing on screen saying
the record continued**. Both now read 3 KB, wrap the whole body, and show `pg n/m` (a `+`
means even 3 KB was not enough). **`1` pages forward, `2` back, both wrapping.** ⚠ On the
**Cardputer those keys are context-sensitive** — with the FACE up `1`/`2` are §5's modality
pins (eye/scope), with the GLOBES up they page; this follows the rule `ENTER` already uses in
that sketch. **`3` (intero) and `4` (beliefs) work from either stack.** General rule this
cost a gate check to learn: *if a view can show less than all of a record, it must say so
on screen.*

**`FACE_BELIEF` is Cardputer-only, structurally.** The `@LAT91` belief lane is written by
`PerceptLearn`, whose Rule 1 arms only off a **`still` `@LAT95` motion window** — and only
the Cardputer has an IMU, so no other node can author a belief. The globes cannot show these
lanes either: `isNodeRecord()` bounds navigation to `lat > -90 && lat < 90`, which excludes
90–93 along with the percept/belief/sync lanes it was written for. Showing them on the T-Deck
needs a `CMD_GET_BELIEF` op mirroring `CMD_GET_INTERO`, not a keybinding.

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

## The team time stream (2026-08-03) — `stream:`/`wall:` replaced `synced:`

`t_ms:<ms> synced:<0|1>` became **`t_ms:<ms> stream:0x<id> wall:<0|1>`** in all seven
record formats (**LINKWIN · ENTWIN · MOTIONWIN · TRANSITION · ACOUSTICWIN · TRANSIENT ·
OUTCOME**). The one bit conflated two facts — *we agree with each other* and *we know
what day it is* — so a fleet in a garden with a perfectly good shared timeline reported
`synced:0` and threw its timestamps away. Those seven are rendered by **one** function,
`timestream::buildStamp`; do not hand-write the triplet in an eighth *observation*
format.

⚠ **BUT `@LAT90` DELIBERATELY LEADS WITH THE STREAM — `stream: wall: t_ms:` — AND EVERY
READER MUST BE ORDER-INDEPENDENT.** That lane is not an observation; it is a statement
about the timeline itself ("this node moved to timeline X"), so the stream is the subject
of the sentence and `buildStreamRecord` writes it first on purpose. `companion.py`'s
first reader was anchored on `t_ms:` and therefore returned `None` for **every record in
the one lane the time stream exists to write**, silently (found 2026-08-03 while flashing
the V4s). It now matches `t_ms:`/`synced:`/`stream:`/`wall:` independently. ⚠ It also
**strips `prev_stream:0x…` first** — `\b` does not help, it matches *inside*
`prev_stream:` — so a REMAP line yields no timeline rather than the stream the node
**left**. Same trap, same shape, as the dedup needle's leading space below.

⚠ **BOTH FORMATS ARE LIVE AND BOTH MUST PARSE.** A node's TTDB is appended to for its
whole life, so pre-2026-08-03 records sit on the same flash as post-. `companion.py
parse_time_fields()` handles both, and an old `synced:1` reads back as **stream `None`**
("some clock, unnameable") rather than a fabricated id. Do not "clean this up" by
dropping the old branch — that silently folds a subset of every existing lane. Verified
on four boards: V4-A carries 68 old-format records, V4-B 81, with new-format records
appended directly beneath them.

`stream:0x00000000` is **meaningful, not an error**: the timestamp is local `millis()`
and comparable with nothing but that node's own records.

Three facts worth knowing before touching it:

- **A stream's clock is elapsed-since-its-own-origin.** That single choice makes the
  merge rule (*older stream wins*) identical to *the larger clock wins*, and makes
  monotonicity automatic — yielding to an older stream can only move a clock FORWARD.
  Consequence: the clock is a **ratchet** (fastest crystal heard wins) — fine for
  ordering/recency, wrong for measuring a duration. Use a local `millis()` delta for
  that, as `MotionPercept`'s `dt_ms` does.
- **Anchors ride on HELLO, never on PULSE.** Only the conductor emits a PULSE and the
  conductor is elected by lowest id, so the node holding the oldest stream usually could
  not speak. HELLO is every node every 2 s and its payload was empty, so this is purely
  additive: an un-reflashed node sends 0 bytes and is a non-participant, not a parse
  error. The pulse clock is deliberately **not** reused — its election would move a
  clock backward, which is fine for a beat and fatal for a log.
- **The recv callback must never touch `timestream::Engine`.** `mono()` mutates its
  49.7-day wrap accounting; a torn write moves the node's clock by seven weeks.
  `TimeStreamNode` (the glue used by all six sketches) queues anchors in a ring from the
  callback and mutates only from `service()`, called first in `loop()`. Callback-built
  STATUS/GPS/TIME_RESP replies read `clockOffsetMs()`, a plain scalar.

New **`@LAT90`** lane logs timeline CHANGES (`STREAM-ORIGIN`/`ADOPTED`/`RECONCILED`/
`ANCHORED`) with a **REMAP** line carrying the offset, so records stamped with a stream
that later lost stay interpretable. A routine drift correction writes nothing.

⚠ **A `STREAM-ORIGIN` IS HELD FOR `TIMESTREAM_ORIGIN_SETTLE_MS` (30 s) BEFORE IT IS
WRITTEN, AND DROPPED IF THE NODE MOVES ON** (2026-08-03). The 6 s listen window is a
*race* and it is lost often: two of three consecutive Cardputer reboots heard no peer
anchor in time, originated, and the next reboot adopted the fleet stream — whose record
was then correctly deduped. Each lost race left a permanent ORIGIN with nothing saying
the node had left it, taking that lane from 13 to 15 against a cap of 16 in one session
(`companion.py` resets the cabled node on nearly every call). The lane's contract is *one
record per settled state, not one per hop*; a stream abandoned three seconds later was
never a state. ⚠ **The hold is ALSO released early the moment the TTDB grows at all** —
the settle window sits under the 60 s percept flush so no window record can carry an
unexplained id, but a `@LAT100` prune marker answers to no flush period and can land
seconds after boot. Both arms live in `originDue()` (portable, native-tested), and the
`< 60000` invariant is asserted in the test suite, so raising the constant past the flush
period fails the build rather than quietly restoring the defect.

A reboot that rejoins **the stream the node was already on** writes nothing: the lane is
deduped by stream id, read back off flash. ⚠ **The needle is `" stream:0x%08lx"` WITH THE
LEADING SPACE** — a RECONCILED record also carries `prev_stream:0x<old>`, so a bare
`strstr("stream:0x")` matches a stream the node has **left**. `ORIGIN` and `RECONCILED`
are never suppressed; an `ANCHORED` is only suppressed when `wall_conflict_ms == 0`.

⚠ **The listen window is measured from `begin()`, NOT from `millis()`.** A first cut used
absolute `millis()`, which silently assumes `setup()` is short — and on the Cardputer
`setup()` takes **over six seconds** (BLE + WiFi + codec + display), so the node
originated a stream on its first loop pass having never listened with its radio up, then
reconciled onto its peer's a second later: **two `@LAT90` records for a reboot that should
write none.** `pulse::Engine` gets this right (`now_ms - boot_ms_`); copy that shape for
any future listen/settle window on these boards. Native tests could not catch it — each
record was individually correct — only a serial trace showed the pair firing every boot.

`TIMESTREAM_MAX_LANE 16`'s refusal-on-full policy is still unexamined: a full lane means
the next stream's records carry an id nothing explains. Don't raise the cap; decide the
policy against the post-fix accumulation rate.

Cost, measured against a HEAD worktree: **V4 +3728 B flash (+0.28%), +416 B RAM**, so
the three V4s sit at **94% with ~74.5 KB left**. Cardputer 41%, T-Deck 40%, K10 20%.

## Change-triggered lanes with run-length (2026-08-04) — `@LAT95` and `@LAT92`

Both lanes used to write one record per 60 s window whether or not anything happened, so
they filled with **uptime** (`@LAT95` in 48 min, `@LAT92` in 24) and pruning was a
treadmill. Now a window whose verdict matches the run in progress writes nothing, and the
record that closes the run states what it suppressed:

```
**RUN**     windows_since_last:10 reason:changed|heartbeat|first max_run:30
**COVERED** state:still windows:9 n:540 window_ms:540000 ... covered_by:@LAT95LON0
**COVERED** peer:0x00000200 proto:espnow verdict:met windows:9 observed_min:-35 ...
```

⚠ **`len(records)` IS NO LONGER THE WINDOW COUNT, and it is wrong in the flattering
direction** — the windows it drops are the ones where nothing happened, so any statistic
computed by counting records under-reports stillness. Use `companion.py motion` (or
`parse_motion_percepts` + `motion_totals`), which sums itemised windows plus every
`**COVERED**` block's `windows:` and reports an `unaccounted` count when a `**RUN**` line
claims windows nothing explains. Both formats are live: a pre-08-04 record has no `**RUN**`
line and is exactly one window, which is the default — do not "clean up" that default.

⚠ **A window is now a PAIR — `(covering record, offset into its run)` — not a record.**
`acting:@LAT95LON7+3` means "the 4th window of the run opened by @LAT95LON7". `@LAT93`'s
`before` half is *usually* a suppressed window and reads `lane:@LAT95LON0+1`. **The
`derived_from` edges stay plain ordinals** with no `+k`: an edge must resolve to a record
that exists.

⚠ **BRANCH ON `lastClose()` / `outcomePending()`, NEVER ON THE BYTE COUNT.**
`buildRecord` returning 0 used to mean "no window" and now means "covered", which is the
normal case for a still node. The sketch's old `if (m == 0) gLearn.disarm();` would have
silenced Rule 1 for 29 windows out of every 30 while looking perfectly healthy.

⚠ **`PerceptLearn::adoptRun()` reads a `scored_vec_` snapshot taken inside `score()`, NOT
`claims_`.** The sketch stages+scores in the link flush and re-arms in the motion flush,
and `arm()` overwrites `claims_`. A first cut adopted from `claims_`, so every window
compared as `changed` and **run-length silently did nothing while looking like it worked**
— each record was individually correct; only the native test caught it. For the same
reason the sketch **renders the outcome even when `@LAT92` is full** and discards the
bytes: `buildOutcome` is what adopts the run.

**Run-length is LOSSLESS for Rule 3** — folding a verdict N times equals folding it once
per window — which is the only reason it is legitimate on `@LAT92`, a *tally*. Dropping
unchanged windows without the count would remove `conf`'s denominator and make every
belief over-confident. `Reconciler::foldRecord` walks `**OBSERVED**` and `**COVERED**`
lines in **one pass, in document order**, because the clamp is order-sensitive; a covered
line whose `windows:` will not parse folds **zero** times, never one.
⚠ `**COVERED-SPAN**` deliberately does not match the `**COVERED** peer:0x` needle — same
needle-collision family as `prev_stream:` in `@LAT90`.

Buffers grew with the format and both are load-bearing: `MOTIONPERCEPT_RECORD_BUF` **512**
(the sketch's old `char rec[320]` would have fitted the plain form and dropped exactly the
run-carrying records) and `PERCEPTLEARN_BUF` 1792 → **2624** (a full 8-claim house with a
covered line per claim renders at 2340 B). Both builders write **nothing** rather than
truncating, so an undersized buffer loses data silently. Cost, measured against a HEAD
worktree on the Cardputer (the only node with an IMU, hence the only one carrying these
tiers): **+2700 B flash (+0.086%), +2920 B RAM**; it sits at 41%.

**Pruning `@LAT92` (`cmd --op clear-percepts --lane 92`, 2026-08-04).** The outcome lane
reached its cap of 24, and `removePerceptLanes` refuses anything outside 94–97, so it got
its own named call — `lanegen::pruneOutcomes`, exactly as `@LAT90` got `pruneTimeline`.
**98/99 stay unreachable by any path; the guard was not widened.**
⚠ **This prune is destructive beyond its own lane.** `Reconciler` is a *pure function* of
`@LAT92`, so emptying it returns every `@LAT91` belief to baseline on the next Dream Cycle.
That is the design, not a fault — but it is why the boundary carries `**OUTCOMES-CARRIED**`
(the tally) and one `**BELIEF-AT-BOUNDARY**` line per belief (the conclusions). Both
`records:` and `windows_max:` are stated because a record is no longer a window.
⚠ **The boundary must never contain `**OBSERVED** peer:0x` or `**COVERED** peer:0x`** —
`Reconciler::foldRecord`'s needles. A boundary carrying either gets folded as testimony
next time the lane is read: the node re-learns from its own gravestone.
⚠ **`--lane 0` drops 94–97 including `@LAT96`**, whose Jaccard baseline Part 2 needs. Name
the lane you mean.

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
