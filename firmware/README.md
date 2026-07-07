# firmware/

Arduino sketches and shared libraries for the robot_team A32 agents, built and
deployed with **arduino-cli**.

## Sketches (one per node)

| Sketch | Board (FQBN) | Core | Role |
|--------|--------------|------|------|
| `k10_percept/` | `UNIHIKER:esp32:k10` | UNIHIKER 0.0.3 (arduino-esp32 **2.x**) | UNIHIKER K10 percept leaf + band lead (melody) |
| `v4a_bridge/`  | `esp32:esp32:esp32s3` | esp32 3.x | Heltec V4 bridge / head |
| `v4b_relay/`   | `esp32:esp32:esp32s3` | esp32 3.x | Heltec V4 relay / mid |
| `v4c_edge/`    | `esp32:esp32:esp32s3` | esp32 3.x | Heltec V4 edge / tail |
| `tdeck_console/` | `esp32:esp32:esp32s3` | esp32 3.x | LilyGo T-Deck handheld console / field operator |

> The K10 uses UNIHIKER's own core, which is **arduino-esp32 2.x**; the Heltec
> nodes use the **3.x** `esp32:esp32` core. The two differ in the ESP-NOW recv
> callback signature — `Toot/src/TootEspNow.h` (`ESPNOW_RECV_CB`) papers over it
> so the same sketches build on both. All five compile clean (verified).

Each sketch folder also holds `data/ttdb.md` — the node's knowledge base,
flashed to LittleFS separately from the firmware.

## Shared libraries (`libraries/`)

Supplied to every compile with `--libraries firmware/libraries`, so they are not
copied into `~/Arduino/libraries`:

- **Toot** — the 250-byte wire frame, portable SHA-256/HMAC, `(src,seq)` dedup,
  and `TootSerialLink` (toots over USB-CDC).
- **TTDB** — streaming reader (`Ttdb`) + `TtdbShare` (serve any byte range of
  the on-disk TTDB to the companion as `TTDB_DATA` toots).
- **Agent32** — sense-reason-act loop scaffold.
- **Pulse** — the band time-base (TTN-RFC-0010): pulse-clock election / `era`
  handoff + beat/step detector, plus `Score.h` note tables for data-driven parts.
- **LinkPercept** — SP0 semantic-positioning instrumentation
  (`ttn-semantic-positioning.md`): per-peer RSSI histograms fed from the radio
  recv callback, flushed as `@LAT97` TTDB records (`**LINK**` lines, min/med/max
  per peer). Portable; format pinned by `tests/test_linkpercept.cpp`.
- **RobotTeamConfig** — shared HMAC key, ESP-NOW channel, node ids.

## Build / deploy

```bash
../scripts/setup.sh                       # once: install esp32 core
../scripts/build.sh  k10_percept          # compile only
../scripts/deploy.sh k10_percept COM5     # compile + flash firmware
../scripts/upload-fs.sh k10_percept COM5  # flash data/ttdb.md to LittleFS
```

`upload-fs.sh` uses `mklittlefs` + `esptool` because arduino-cli has no
filesystem-upload command. Verify the flash size/offset against your board's
partition CSV before relying on it.

## UNIHIKER K10 onboard hardware

`k10_percept` uses the DFRobot **`unihiker_k10`** library for the onboard AHT20
temperature sensor and the RGB LEDs:

- temperature: `aht20.getData(AHT20::eAHT20TempC)`
- RGB LEDs: `k10.rgb->write(-1, 0xRRGGBB)` (index `-1` = all), `k10.rgb->brightness(0..9)`

The library is distributed via the UNIHIKER K10 wiki, not the Arduino registry,
so `arduino-cli lib install` may not find it — install the zip from the wiki (or
drop it in `firmware/libraries/`, where `--libraries` already picks it up). The
K10 may also need DFRobot's board package; the generic `esp32:esp32:esp32s3`
FQBN works for the ESP32-S3 core. To build before the library is in place, set
`#define USE_K10_HW 0` at the top of the sketch to fall back to a serial mock.

## K10 filesystem (TTDB)

The K10's UNIHIKER core uses the `large_spiffs_16MB` partition scheme, which has
**no partition named `spiffs`** — its only LittleFS-capable partition is `model`
(subtype spiffs, `@0x510000`, ~4.5 MB), normally for AI models. A percept node
doesn't use those, so we store the TTDB there:

- the sketch mounts it by label: `LittleFS.begin(true, "/littlefs", 10, "model")`;
- `Upload K10 Filesystem` (task) / `scripts/Upload-K10-FS.ps1` builds a LittleFS
  image with the UNIHIKER core's `mklittlefs` and flashes it to `0x510000` with
  `esptool` (arduino-cli can't upload filesystems). Run it **after** the firmware
  upload; they target different flash regions.

If you later need the onboard AI features, switch to a custom partition scheme
that keeps the model partition and adds a separate user filesystem.

> The bash `scripts/upload-fs.sh` uses generic offsets and is for the V4 / esp32
> 3.x nodes; the K10 uses the dedicated `.ps1` with the `model`-partition offset.

## LilyGo T-Deck console (`tdeck_console`)

The T-Deck is a handheld ESP32-S3 with a 320×240 ST7789 LCD, a BlackBerry
keyboard (its own MCU on I²C `0x55`), a trackball, an SX1262 LoRa radio, and an
I²S speaker — the fleet's **operator console**: the keyboard injects CMD toots and
the screen shows the fleet, so you can drive the swarm without the laptop.

- **FQBN** `esp32:esp32:esp32s3:CDCOnBoot=cdc` (native USB, same as the V4/K10).
- **Console UI is live (`USE_TDECK_HW 1`).** On boot it sounds a **"toot toot"** and
  renders a fleet view on the 320×240 screen; set `USE_TDECK_HW 0` to build the network
  floor headless (byte-exact pull, HMAC reject, `TIME_SYNC`+`@LAT99`, belief
  `TTDB_PUT`+`@LAT98`, STATUS, PULSE) against a serial mock.
- **Keyboard = fleet remote** (each key sends a CMD immediately, no "enter"):
  **`t`** cycle target (V4-B → K10 → V4-A), **`s`** get-status, **`p`** ping, **`b`** beep,
  **`g`** play, **`x`** stop. Default target is **V4-B** — the V4-A bridge only answers
  CMDs from the laptop over USB, not from the mesh, so aiming keys at it gives no reply;
  V4-B/K10 answer over the air (`s` → a `reply <node>` line appears on the screen).
  `g`/`x` map to `CMD_PLAY` / `CMD_STOP` (Toot.h `CmdOp` 6/7) — with target = K10 they
  start/stop the K10's song (the K10 boots silent).
- **Display = Adafruit_ST7789, NOT TFT_eSPI.** Pins are passed at runtime
  (`SPI.begin(SCLK 40, MISO 38, MOSI 41, CS 12)` + `Adafruit_ST7789(&spi, CS 12, DC 11,
  RST -1)`), so it never touches the shared K10 `User_Setup.h`. `init(240,320)` +
  **`setRotation(3)`** = 320×240 landscape right-side-up (rotation 1 is upside-down on
  this panel). Backlight on `GPIO42` (HIGH). Install:
  `arduino-cli lib install "Adafruit ST7735 and ST7789 Library"` (pulls GFX + BusIO).
- **Audio = I²S sine on the MAX98357A amp** (BCLK 7 / WS 5 / DOUT 6) — no analog/PWM
  path like the K10's `Music`. `ESP_I2S` (bundled in the esp32 core) at 16 kHz, 16-bit
  stereo (L=R); `toneI2S()` synthesizes the boot toot. Blocking, so it runs from
  `setup()`/`loop()` only.
- **Board power-on:** `GPIO10` (`PIN_POWERON`) must be driven **HIGH** or the LCD,
  keyboard, LoRa and SD are all unpowered. The sketch asserts it in `setup()` even
  headless so LoRa can be enabled later.
- **Filesystem (TTDB):** reuse the V4 path — it's the same esp32-core default 4 MB
  `spiffs` partition (@0x290000): `scripts/Upload-V4-FS.ps1 -Node tdeck_console
  -Port COMx`. (16 MB flash; the default scheme wastes the top 12 MB — fine for a
  ~1 KB TTDB. Switch to a 16 MB scheme later if the console needs more.)
- **Pin map:** shared SPI bus `SCLK 40 / MOSI 41 / MISO 38` (LCD + LoRa + SD);
  LCD `CS 12 / DC 11 / BL 42`; keyboard I²C `SDA 18 / SCL 8`; trackball `click 0,
  up 3, down 15, left 1, right 2`; SX1262 `CS 9 / BUSY 13 / RST 17 / DIO1 45`; SD
  `CS 39`. See `../hardware_specs.md §3`.

## LoRa (Phase 4)

The V4 sketches gate LoRa behind `#define USE_LORA 0`. To enable: install
RadioLib (`arduino-cli lib install RadioLib`), set `USE_LORA 1`, wire the SX1262
per the V4 GPIO map in `../hardware_specs.md`, and select the correct PA variant
flag for your board revision.
