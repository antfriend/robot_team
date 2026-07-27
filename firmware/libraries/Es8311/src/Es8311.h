// Es8311.h — minimal ES8311 audio-codec bring-up for the M5Stack Cardputer ADV.
//
// The ADV replaced the original Cardputer's bare I2S amp with an **ES8311 codec**
// (I2C control at 0x18, I2S data), so the board has both a speaker path (codec DAC ->
// NS4150B -> 8ohm speaker) and a MICROPHONE path (MEMS mic -> codec ADC) on one I2S
// bus. That mic is why the Cardputer is the fleet's acoustic sense organ
// (ttn-semantic-positioning.md Phase 3, environmental TDoA) — but nothing sounds and
// nothing is heard until these registers are written, so this is the gate on both.
//
// Deliberately small: no codec framework, just the register sequence, distilled from
// the Espressif ES8311 driver (MIT, shipped inside the `audio-driver` Arduino library
// at Driver/es8311/es8311.c) down to the one configuration this board uses:
//
//   * codec is I2S **SLAVE** (the ESP32-S3 drives BCLK/LRCK),
//   * **MCLK is taken from the SCLK/BCLK pin** — the ADV does not route a separate
//     MCLK, so the codec's internal DIG_MCLK = LRCK*256 = BCLK*8, which holds exactly
//     when the ESP is in 16-bit stereo (BCLK = 32*fs). Do not run the I2S bus in mono
//     or at another bit width without revisiting this.
//   * I2S standard format (Philips), 16-bit.
//
// At MCLK = 256*fs the whole clock-coefficient table of the upstream driver collapses
// to one constant row (verified against every supported rate: pre_div/pre_multi/
// adc_div/dac_div = 1, fs_mode 0, lrck 0x00ff, bclk_div 4, osr 0x10), which is why no
// table is carried here — any standard rate configures identically.
//
// Arduino-dependent (Wire) by nature: this is register I/O over I2C, not portable
// reasoning code, so it has no native test the way Toot/TTDB/LinkPercept do.
#pragma once
#include <Arduino.h>
#include <Wire.h>

namespace es8311 {

const uint8_t I2C_ADDR = 0x18;   // CE tied low (0x30 >> 1)

// True if an ES8311 answers at `addr` (chip id regs 0xFD/0xFE read 0x83/0x11). Cheap
// probe used at boot so a missing/failed codec is reported instead of silently
// producing silence.
bool present(TwoWire& bus, uint8_t addr = I2C_ADDR);

// Configure the codec as an I2S slave at `sample_rate`, 16-bit, both directions live
// (DAC for the band voice, ADC for the mic). Returns false if the chip does not
// answer. `Wire.begin(sda, scl)` must already have run.
bool begin(TwoWire& bus, uint32_t sample_rate, uint8_t addr = I2C_ADDR);

// Speaker volume, 0..100 (0 = mute). Maps onto DAC volume register 0x32.
void setVolume(uint8_t percent);

// Microphone analog PGA gain, 0..7 (register 0x16; ~0 to +42 dB in 6 dB steps).
// The MEMS mic wants a healthy amount — 6 is a sane starting point.
void setMicGain(uint8_t gain);

// Raw register access (exposed for bring-up dumps from a sketch).
bool writeReg(uint8_t reg, uint8_t val);
int  readReg(uint8_t reg);   // -1 on I2C error

}  // namespace es8311
