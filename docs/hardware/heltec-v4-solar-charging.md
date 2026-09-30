# Heltec WiFi LoRa 32 V4 — Solar Charging Implementation Reference

**Project:** Toot Toot Network (TTN) — V4-B solar node
**Status:** Reference document
**Last updated:** 2026-07-06

---

## Overview

The WiFi LoRa 32 V4 is the first Heltec LoRa 32 generation with native solar
charging support. No external charge controller (TP4056 board, MPPT module,
etc.) is required for a basic solar node — the onboard power management IC
handles panel input, battery charging, overcharge protection, and automatic
power-source switching.

---

## Solar Input

| Parameter | Value |
|---|---|
| Connector | SH1.25-2P (1.25 mm pitch, 2-pin) |
| Input voltage range | **4.7–6 V** |
| Recommended panel | 6 V nominal, 1–2 W |

Notes:

- Do **not** use 9 V or 12 V panels — input ceiling is 6 V.
- Size the panel up (2 W+) if the node transmits frequently at 28 dBm
  or must overwinter at Boise latitude (~43.6° N, low winter sun angle).
- 1–2 W @ 6 V is the community-standard sizing for duty-cycled
  LoRa/ESP-NOW nodes.

## Battery

| Parameter | Value |
|---|---|
| Connector | SH1.25-2P (1.25 mm pitch, 2-pin) |
| Cell type | 3.7 V Li-ion / LiPo (3.3–4.4 V range) |
| Suggested capacity | 800–3000 mAh |

Notes:

- Battery and solar connectors are the **same type** — label pigtails.
- Deep-sleep floor is **< 20 µA**, so solar + modest cell rides through
  multi-day cloud cover at TTN duty cycles.

## ⚠️ Polarity Warning

Pre-wired SH1.25 pigtails (AliExpress/Amazon) have **no standardized
polarity**. Verify red-to-positive against the board silkscreen with a
multimeter before connecting either the panel or the battery.

## Power Input Rules (per datasheet)

- USB **or** the 5 V pin may be connected — only one at a time.
- When either USB or 5 V is connected, the **solar panel and battery may
  remain connected simultaneously** → bench-flash over USB-C without
  unplugging panel/battery. Convenient for field service.
- Vext (VE) external supply control: VextCtrl = **GPIO36**.

## Battery Voltage Telemetry (firmware)

For TTN health toots:

- Sense pin: **GPIO1** (ADC1_CH0)
- Enable pin: **GPIO37** (ADC_Ctrl) — pull **HIGH** to enable the divider
- Divider: 390 kΩ / 100 kΩ

```
VBAT = (100 / (100 + 390)) × VADC_IN1
     → VBAT ≈ VADC_IN1 × 4.9
```

Sketch pattern:

```cpp
#define VBAT_ADC   1    // ADC1_CH0
#define ADC_CTRL   37   // pull HIGH to enable divider

float readVBat() {
  pinMode(ADC_CTRL, OUTPUT);
  digitalWrite(ADC_CTRL, HIGH);
  delay(10);                          // settle
  uint32_t mv = analogReadMilliVolts(VBAT_ADC);
  digitalWrite(ADC_CTRL, LOW);        // kill divider leakage pre-sleep
  return (mv * 4.9f) / 1000.0f;
}
```

## Hardware Revision Gotcha

The V4 shipped with different LoRa front-end modules across revisions.
In Arduino (Tools menu), select the matching FEM option:

| Revision | FEM option |
|---|---|
| V4.2 | `USE_GC1109_PA` |
| V4.3 | `USE_KCT8103L_PA` |

Update Heltec libraries and click **Reload Board Data** first. TX power
calibration differs per revision — check which revision each TTN node
(V4-A, V4-B, V4-C) actually is.

## Reference Documents

- Datasheet: <https://resource.heltec.cn/download/WiFi_LoRa_32_V4/datasheet/WiFi_LoRa_32_V4.2.0.pdf>
- Schematic: <https://resource.heltec.cn/download/WiFi_LoRa_32_V4/Schematic/WiFi_LoRa_32_V4.2.pdf>
- Pin map: <https://resource.heltec.cn/download/WiFi_LoRa_32_V4/Pinmap/V4_pinmap.png>
- Heltec wiki (V4): <https://wiki.heltec.org/docs/devices/open-source-hardware/esp32-series/lora-32/wifi-lora-32-v4/>
- Product page: <https://heltec.org/project/wifi-lora-32-v4/>

The schematic shows the actual charge IC part number and charge-current
setting resistor — useful for sizing panel output against charge rate.

## Recommended Products (sourcing links)

### Turnkey option — Heltec official Solar Kit ($45.20)

<https://heltec.org/project/solar-kit-for-dev-board-waterproof-enclosure-for-outdoor-meshtastic-meshcore/>

- 5 W / 6 V panel, IP67 waterproof enclosure, 178×178×35 mm
- Holds 1–4 × 18650 cells in parallel (batteries NOT included)
- Outputs 3.7 V on a 1.25-2P connector → plugs into the V4 **battery**
  port (kit does its own charge management; the V4's onboard solar
  input is bypassed in this configuration)
- Includes mounting bracket sized for WiFi LoRa 32 V3/V4 and
  Mesh Node T114; antenna included (select 915 MHz for US)
- Overcharge protection 4.25 V; over-discharge cutoff 3.0 V
- Strong fit for V4-B if a pre-built weatherproof package beats a
  custom 3D-printed enclosure

### DIY build (using the V4's native solar input)

| Part | Source / search term |
|---|---|
| Solar panel, 6 V / 1–2 W | Voltaic P121/P126 (6V 1W/2W), Adafruit 6V 2W (#5368), or generic "6V 2W epoxy solar panel" |
| Solar pigtail | Search "SH1.25 2P cable" / "1.25mm 2-pin pigtail" — verify polarity! |
| Battery | 3.7 V LiPo 800–3000 mAh with 1.25 mm (SH1.25/Molex PicoBlade-style) plug, or 18650 + SH1.25 holder |
| 18650 battery box | Heltec, $1.99: <https://heltec.org/project/18650-box/> |

### Related Heltec accessories useful for TTN nodes

| Item | Price | Link |
|---|---|---|
| BME280 pressure/temp/humidity sensor | $3.90 | <https://heltec.org/project/bme280-atmospheric-pressure-sensor/> |
| L76K GNSS module (SH1.25-8P port) | $8.00 | <https://heltec.org/project/l76-gnss-module/> |
| Fiberglass omni antenna | $12.90–29.90 | <https://heltec.org/project/fiberglass-omni-antennas/> |
| IPEX→SMA feeder cable | $0.90 | <https://heltec.org/project/ipex1-to-sma-antenna-feeder-cable-rf113-10mm/> |
| Solar product category (5 items) | — | <https://heltec.org/product-category/solar/> |
| WiFi LoRa 32 V4 board | — | <https://heltec.org/project/wifi-lora-32-v4/> |

## Enclosure Note

Many V3 enclosures do **not** fit the V4 (OLED faceplate adds thickness;
battery placement changed). Plan a fresh 3D-printed housing for V4-B with
panel-side cable gland and clearance for both SH1.25 connectors, which sit
adjacent to each other.
