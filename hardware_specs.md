# Toot-Toot Network — Hardware Reference

Spec sheets for the ESP32 agent boards in the toot-toot network, plus the laptop
orchestrator. Compiled for Arduino / PlatformIO development under the Locus framework.

Two board roles:

- **UNIHIKER K10** — *perception + UI node.* Color screen, camera, mics,
  accelerometer, environmental sensors. No LoRa. Rich `@PERCEPT` capture endpoint.
- **Heltec WiFi LoRa 32 V4** — *comms / mesh node.* SX1262 LoRa + WiFi + BLE,
  small mono OLED. The long-range spine of the network.

---

## 1. UNIHIKER K10 (DFR0992)

| Spec | Value |
|---|---|
| MCU | ESP32-S3 (Xtensa LX7 dual-core, up to 240 MHz) |
| SRAM | 512 KB |
| PSRAM | 8 MB |
| Flash | 16 MB external |
| ROM | 384 KB |
| Wi-Fi | 2.4 GHz 802.11 b/g/n (Wi-Fi 4) |
| Bluetooth | BLE 5.0 |
| LoRa | **None** |
| Display | 2.8" color LCD, **240×320**, 262 K colors, 3:4, non-touch |
| Camera | 2 MP |
| Audio in | 2× microphone (mic array) |
| Audio out | Speaker |
| Sensors | Temperature, humidity, ambient light, accelerometer |
| Indicators | 3× RGB LED |
| Buttons | 2× user button (A / B) |
| Storage | MicroSD slot (pairs well with LittleFS internal + SD for TTDB) |
| Ports | USB Type-C, Gravity 3-pin & 4-pin, 2-pin PH2.0 battery, micro:bit-style edge connector |
| Power | USB-C / battery port / edge connector |
| Size | 51.6 × 83 × 11 mm |
| Programming | Arduino (ESP32-S3), MicroPython, Mind+ blocks |
| Price | ~$28.90 |

### GPIO note (important for wiring)
The micro:bit-compatible edge-connector pins do **not** connect directly to the
ESP32-S3. They route through an **XL9535 I²C-to-GPIO expander**. Implications:

- Edge pins are driven over I²C — there is latency, and they are **not suitable
  for fast PWM, precise timing, or hardware interrupts**.
- The ESP32-S3's native GPIO is mostly consumed by the display, camera, audio,
  and onboard sensors.
- For deterministic timing-critical work, treat the K10 as a self-contained
  sensor/UI agent rather than a board you bolt raw peripherals onto.

The edge connector is electrically micro:bit-compatible, so micro:bit expansion
boards / Gravity peripherals work via the expander.

### Role in the network
Ideal Locus `@PERCEPT` capture node: camera + mic + accelerometer + environment
in one unit, with a 240×320 screen for showing belief/percept state (your
`@LATxLONy` address display is already running here per the boot screen).
Talks to the rest of the mesh over **Wi-Fi / BLE only** — it must hop through a
Heltec node (or the orchestrator's AP) to reach anything LoRa.

---

## 2. Heltec WiFi LoRa 32 V4

| Spec | Value |
|---|---|
| MCU | ESP32-S3R2 (Xtensa LX7 dual-core, up to 240 MHz) |
| PSRAM | 2 MB |
| Flash | 16 MB external |
| Wi-Fi | 2.4 GHz 802.11 b/g/n |
| Bluetooth | BLE 5.0 |
| LoRa | Semtech **SX1262** |
| LoRa band | HF 863–928 MHz (EU868 / US915 region-dependent; your unit boxed as HF 863–928) |
| LoRa TX power | High-power 28±1 dBm / low-power 22 dBm version |
| Display | 0.96" **SSD1306 OLED, 128×64**, monochrome |
| USB–Serial | **Native USB** (CP2102 removed vs V3 — uses ESP32-S3 built-in USB CDC) |
| Headers | 40-pin (V3 was 36-pin), gold-plated |
| Extra interfaces | SH1.25-2P solar input (4.7–6 V), SH1.25-8P GNSS/GPS connector |
| Antenna | FPC integrated in screen bracket + IPEX/U.FL connector |
| Battery | 3.3–4.4 V Li-ion, integrated charge + protection |
| Idle power | < 20 µA |
| PCB | 6-layer, immersion gold |
| Buttons | PRG (GPIO0 / boot) + RST |
| Programming | Arduino, PlatformIO, ESP-IDF, MicroPython |

### Key GPIO map (V4 — pin-compatible with V3)

| Function | GPIO |
|---|---|
| OLED SDA | 17 |
| OLED SCL | 18 |
| OLED RST | 21 |
| LoRa NSS / CS | 8 |
| LoRa SCK | 9 |
| LoRa MOSI | 10 |
| LoRa MISO | 11 |
| LoRa RST | 12 |
| LoRa BUSY | 13 |
| LoRa DIO1 | 14 |
| PRG / BOOT button | 0 |
| Vbat ADC (read) | 1 |
| Vext control (peripheral power) | 36 |

> The OLED pins above are confirmed from Heltec's V4 example code. The SX1262
> SPI pins follow the V3 mapping, which Heltec states the V4 retains — verify
> against the official V4 pinmap PNG and datasheet (links below) before
> committing board pins, especially since FEM/PA selection differs by revision.

### Arduino board-revision gotcha
The V4 needs the correct **LoRa FEM/PA option** selected in the Arduino Tools menu:

- **V4.2** → `USE_GC1109_PA`
- **V4.3** → `USE_KCT8103L_PA`

After updating the Heltec ESP32 library, use **Tools → Reload Board Data** so the
cache refreshes. Wrong PA selection = degraded or broken TX.

### Bootloader entry
Hold **PRG**, tap **RST** once, release **PRG**.

### External antenna mod
To use the IPEX connector instead of the built-in FPC antenna: remove the onboard
inductor at position ① and bridge position ② with a 0 Ω resistor. **Always attach
an antenna before powering on** — TX into an open RF port can damage the SX1262.

### Role in the network
The mesh backbone. Each V4 is a LoRa relay/gateway; one V4 tethered to the
orchestrator over USB-CDC serial (or WiFi) acts as the **ground-station bridge**
between the laptop and the off-grid LoRa agents. Meshtastic/MeshCore-compatible
if you want a proven transport layer under the toot-toot protocol.

### Official resources
- Datasheet: `https://resource.heltec.cn/download/WiFi_LoRa_32_V4/datasheet/WiFi_LoRa_32_V4.2.0.pdf`
- Schematic: `https://resource.heltec.cn/download/WiFi_LoRa_32_V4/Schematic/WiFi_LoRa_32_V4.2.pdf`
- Pin map (PNG): `https://resource.heltec.cn/download/WiFi_LoRa_32_V4/Pinmap/V4_pinmap.png`
- Resource index: `https://resource.heltec.cn/download/WiFi_LoRa_32_V4`

---

## 3. Laptop orchestrator

Not a fixed spec — but for the toot-toot network design, the relevant interfaces:

| Channel | How it reaches agents |
|---|---|
| USB-CDC serial | Direct to a tethered Heltec V4 (bridge node) or a K10. Native USB on S3 = simple `Serial` link, good for a deterministic command/telemetry pipe. |
| Wi-Fi | Orchestrator as AP or same LAN → reaches K10s and V4s directly (MQTT, UDP, HTTP, WebSocket). |
| BLE | Short-range config / pairing to either board. |
| LoRa (indirect) | Orchestrator has no radio; it speaks LoRa **through** a USB- or WiFi-attached V4 gateway. |

Suggested topology for Locus:

```
        [Laptop orchestrator]
           |            |
        USB-CDC       Wi-Fi (AP/LAN)
           |            |
   [Heltec V4 bridge]  [K10 percept nodes]
           |  LoRa (SX1262, 863-928 MHz)
   +-------+--------+--------+
   |       |        |        |
 [V4]    [V4]     [V4] ... off-grid mesh agents
```

---

## 4. Quick comparison

| | UNIHIKER K10 | Heltec WiFi LoRa 32 V4 |
|---|---|---|
| MCU | ESP32-S3 (LX7) | ESP32-S3R2 (LX7) |
| PSRAM / Flash | 8 MB / 16 MB | 2 MB / 16 MB |
| LoRa | ✗ | ✓ SX1262, 28 dBm |
| Wi-Fi / BLE | ✓ / ✓ | ✓ / ✓ |
| Display | 240×320 color LCD | 128×64 mono OLED |
| Camera / mics | 2 MP + 2 mic | ✗ |
| Onboard sensors | temp, humidity, light, accel | ✗ |
| Free fast GPIO | limited (I²C expander) | yes (40-pin native) |
| Battery / solar | battery port | battery + solar + GNSS |
| Native USB serial | yes | yes (no UART bridge chip) |
| Best role | perception + UI endpoint | long-range mesh node / gateway |

---

*Verify all GPIO assignments against the linked official datasheet/pinmap before
finalizing board pin definitions — vendor revisions (V4.2 vs V4.3) differ in the
PA/FEM path and Arduino board-config selection.*
