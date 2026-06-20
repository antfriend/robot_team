# firmware/

Arduino sketches and shared libraries for the robot_team A32 agents, built and
deployed with **arduino-cli**.

## Sketches (one per node)

| Sketch | Board (FQBN) | Core | Role |
|--------|--------------|------|------|
| `k10_percept/` | `UNIHIKER:esp32:k10` | UNIHIKER 0.0.3 (arduino-esp32 **2.x**) | UNIHIKER K10 percept leaf (Phase 1) |
| `v4a_bridge/`  | `esp32:esp32:esp32s3` | esp32 3.x | Heltec V4 bridge / head |
| `v4b_relay/`   | `esp32:esp32:esp32s3` | esp32 3.x | Heltec V4 relay / mid |
| `v4c_edge/`    | `esp32:esp32:esp32s3` | esp32 3.x | Heltec V4 edge / tail |

> The K10 uses UNIHIKER's own core, which is **arduino-esp32 2.x**; the Heltec
> nodes use the **3.x** `esp32:esp32` core. The two differ in the ESP-NOW recv
> callback signature — `Toot/src/TootEspNow.h` (`ESPNOW_RECV_CB`) papers over it
> so the same sketches build on both. All four compile clean (verified).

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

## LoRa (Phase 4)

The V4 sketches gate LoRa behind `#define USE_LORA 0`. To enable: install
RadioLib (`arduino-cli lib install RadioLib`), set `USE_LORA 1`, wire the SX1262
per the V4 GPIO map in `../hardware_specs.md`, and select the correct PA variant
flag for your board revision.
