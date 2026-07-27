#include "Es8311.h"

namespace es8311 {
namespace {

TwoWire* gBus = nullptr;
uint8_t gAddr = I2C_ADDR;

// Register map (subset actually written; names from the Espressif driver).
const uint8_t REG_RESET      = 0x00;  // reset digital/csm/clock manager, master bit 6
const uint8_t REG_CLK_MGR01  = 0x01;  // mclk source (bit7) + per-block clock enables
const uint8_t REG_CLK_MGR02  = 0x02;  // pre-divider (7:5) + pre-multiplier (4:3)
const uint8_t REG_CLK_MGR03  = 0x03;  // adc fs_mode (6) + adc osr
const uint8_t REG_CLK_MGR04  = 0x04;  // dac osr
const uint8_t REG_CLK_MGR05  = 0x05;  // adc/dac clock dividers
const uint8_t REG_CLK_MGR06  = 0x06;  // sclk inverter (5) + bclk divider
const uint8_t REG_CLK_MGR07  = 0x07;  // lrck divider high
const uint8_t REG_CLK_MGR08  = 0x08;  // lrck divider low
const uint8_t REG_SDPIN09    = 0x09;  // DAC serial port: format + word length
const uint8_t REG_SDPOUT0A   = 0x0A;  // ADC serial port: format + word length
const uint8_t REG_SYSTEM0B   = 0x0B;
const uint8_t REG_SYSTEM0C   = 0x0C;
const uint8_t REG_SYSTEM0D   = 0x0D;  // power up analog
const uint8_t REG_SYSTEM0E   = 0x0E;  // power up ADC/PGA
const uint8_t REG_SYSTEM10   = 0x10;
const uint8_t REG_SYSTEM11   = 0x11;
const uint8_t REG_SYSTEM12   = 0x12;  // enable DAC
const uint8_t REG_SYSTEM13   = 0x13;
const uint8_t REG_SYSTEM14   = 0x14;  // mic select (DMIC bit 6) + analog PGA gain
const uint8_t REG_ADC15      = 0x15;  // adc ramp rate
const uint8_t REG_ADC16      = 0x16;  // mic PGA gain
const uint8_t REG_ADC17      = 0x17;  // adc digital volume
const uint8_t REG_ADC1B      = 0x1B;  // adc hpf
const uint8_t REG_ADC1C      = 0x1C;  // adc equalizer / hpf stage 2
const uint8_t REG_DAC31      = 0x31;  // dac mute
const uint8_t REG_DAC32      = 0x32;  // dac digital volume
const uint8_t REG_DAC37      = 0x37;  // dac ramp rate
const uint8_t REG_GP45       = 0x45;  // general purpose (PA/mute control)
const uint8_t REG_CHIPID1    = 0xFD;
const uint8_t REG_CHIPID2    = 0xFE;

// Clock coefficients for MCLK = 256 * fs (see the header: constant across rates).
const uint8_t PRE_DIV = 1, ADC_DIV = 1, DAC_DIV = 1;
const uint8_t FS_MODE = 0, LRCK_H = 0x00, LRCK_L = 0xFF, BCLK_DIV = 4;
const uint8_t ADC_OSR = 0x10, DAC_OSR = 0x10;
// MCLK is derived from the SCLK pin, so the pre-multiplier is forced to x8
// (DIG_MCLK = LRCK*256 = BCLK*8) rather than taken from the coefficient row.
const uint8_t PRE_MULTI_FROM_SCLK = 3;

// Read-modify-write: keep `keep_mask` bits of the current value, or in `set`.
void rmw(uint8_t reg, uint8_t keep_mask, uint8_t set) {
  int cur = readReg(reg);
  if (cur < 0) cur = 0;
  writeReg(reg, (uint8_t)(((uint8_t)cur & keep_mask) | set));
}

}  // namespace

bool writeReg(uint8_t reg, uint8_t val) {
  if (!gBus) return false;
  gBus->beginTransmission(gAddr);
  gBus->write(reg);
  gBus->write(val);
  return gBus->endTransmission() == 0;
}

int readReg(uint8_t reg) {
  if (!gBus) return -1;
  gBus->beginTransmission(gAddr);
  gBus->write(reg);
  if (gBus->endTransmission(false) != 0) return -1;
  if (gBus->requestFrom((int)gAddr, 1) != 1) return -1;
  return gBus->read();
}

bool present(TwoWire& bus, uint8_t addr) {
  gBus = &bus;
  gAddr = addr;
  int id1 = readReg(REG_CHIPID1), id2 = readReg(REG_CHIPID2);
  return id1 == 0x83 && id2 == 0x11;
}

bool begin(TwoWire& bus, uint32_t sample_rate, uint8_t addr) {
  gBus = &bus;
  gAddr = addr;
  (void)sample_rate;   // rate-independent at MCLK = 256*fs (see header)
  if (!present(bus, addr)) return false;

  // --- codec init (upstream es8311_codec_init, slave + MCLK-from-SCLK) --------
  writeReg(REG_CLK_MGR01, 0x30);
  writeReg(REG_CLK_MGR02, 0x00);
  writeReg(REG_CLK_MGR03, 0x10);
  writeReg(REG_ADC16, 0x24);
  writeReg(REG_CLK_MGR04, 0x10);
  writeReg(REG_CLK_MGR05, 0x00);
  writeReg(REG_SYSTEM0B, 0x00);
  writeReg(REG_SYSTEM0C, 0x00);
  writeReg(REG_SYSTEM10, 0x1F);
  writeReg(REG_SYSTEM11, 0x7F);
  writeReg(REG_RESET, 0x80);
  rmw(REG_RESET, 0xBF, 0x00);          // slave mode: clear the master bit
  writeReg(REG_CLK_MGR01, 0x3F);
  rmw(REG_CLK_MGR01, 0xFF, 0x80);      // internal MCLK source = SCLK pin

  // Clock tree for MCLK = 256*fs.
  rmw(REG_CLK_MGR02, 0x07,
      (uint8_t)(((PRE_DIV - 1) << 5) | (PRE_MULTI_FROM_SCLK << 3)));
  writeReg(REG_CLK_MGR05, (uint8_t)(((ADC_DIV - 1) << 4) | (DAC_DIV - 1)));
  rmw(REG_CLK_MGR03, 0x80, (uint8_t)((FS_MODE << 6) | ADC_OSR));
  rmw(REG_CLK_MGR04, 0x80, DAC_OSR);
  rmw(REG_CLK_MGR07, 0xC0, LRCK_H);
  writeReg(REG_CLK_MGR08, LRCK_L);
  rmw(REG_CLK_MGR06, 0xE0, (uint8_t)(BCLK_DIV < 19 ? BCLK_DIV - 1 : BCLK_DIV));
  rmw(REG_CLK_MGR01, (uint8_t)~0x40, 0x00);   // MCLK not inverted
  rmw(REG_CLK_MGR06, (uint8_t)~0x20, 0x00);   // SCLK not inverted

  writeReg(REG_SYSTEM13, 0x10);
  writeReg(REG_ADC1B, 0x0A);
  writeReg(REG_ADC1C, 0x6A);

  // --- serial format: I2S standard (Philips), 16-bit, both directions --------
  rmw(REG_SDPIN09, 0xFC, 0x0C);
  rmw(REG_SDPOUT0A, 0xFC, 0x0C);

  // --- start (upstream es8311_start, CODEC_MODE_BOTH) ------------------------
  rmw(REG_SDPIN09, 0xBF, 0x00);        // un-mute the DAC serial port
  rmw(REG_SDPOUT0A, 0xBF, 0x00);       // un-mute the ADC serial port
  writeReg(REG_ADC17, 0xBF);           // ADC digital volume
  writeReg(REG_SYSTEM0E, 0x02);        // power up ADC + PGA
  writeReg(REG_SYSTEM12, 0x00);        // enable DAC
  writeReg(REG_SYSTEM14, 0x1A);        // analog mic (not DMIC) + PGA gain
  rmw(REG_SYSTEM14, (uint8_t)~0x40, 0x00);   // analog mic: clear the DMIC bit
  writeReg(REG_SYSTEM0D, 0x01);        // power up analog
  writeReg(REG_ADC15, 0x40);
  writeReg(REG_DAC37, 0x48);
  writeReg(REG_GP45, 0x00);
  writeReg(REG_DAC31, 0x00);           // DAC un-muted

  setVolume(70);
  setMicGain(6);
  return true;
}

void setVolume(uint8_t percent) {
  if (percent > 100) percent = 100;
  // Register 0x32 is 0..255 over the codec's full digital range; 0 is mute.
  uint8_t v = percent == 0 ? 0 : (uint8_t)((uint16_t)percent * 255 / 100);
  writeReg(REG_DAC32, v);
}

void setMicGain(uint8_t gain) {
  if (gain > 7) gain = 7;
  writeReg(REG_ADC16, gain);
}

}  // namespace es8311
