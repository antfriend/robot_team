// v4_adc_probe.ino — throwaway diagnostic: WHICH pin on a Heltec V4 reads the battery?
//
// The V3 map (`GPIO1` behind an active-LOW `GPIO37` divider enable, 4.9:1) reads 0 mV on
// this V4 with a known-good pack attached, so the published map is wrong for this board.
// Guessing a second pin from the same source is how you get a second wrong answer, so this
// sweeps EVERY ADC1 pin instead and lets the board say which one moves.
//
// ADC1 on the ESP32-S3 is GPIO1..GPIO10 — the only usable half, since ADC2 is unavailable
// while WiFi is up. WiFi/LoRa/I2S/OLED are all deliberately left uninitialised here, so
// every one of those pins is free to read: this runs before anything claims them.
//
// The tell is not the absolute number, it is which pin CHANGES when a candidate divider
// enable is driven. A switched divider reads ~0 when disconnected and a real voltage when
// connected; an unswitched one reads the same in all three states. So each pin is sampled
// with each candidate control pin LOW, HIGH, and left floating (input / Hi-Z).
//
// Expected magnitudes for a 1S pack at ~3.7-4.2 V:  1:1 -> ~1850-2100 mV,
// 2:1 -> ~1230-1400 mV, 4.9:1 -> ~755-857 mV, direct -> off-scale (clipped ~3100).
#include <Arduino.h>

// GPIO1..GPIO10 = ADC1_CH0..CH9. Nothing else is brought up, so all ten are readable.
static const int kAdcPins[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
static const int kNumAdc = sizeof(kAdcPins) / sizeof(kAdcPins[0]);

// Candidate "connect the divider" pins. 37 is the V3's ADC_Ctrl; 36 is this board's Vext
// (already known to gate the OLED rail, and a plausible shared peripheral enable); 21 is
// listed as OLED RST and is included only to show an unrelated pin as a control.
static const int kCtrlPins[] = {37, 36};
static const int kNumCtrl = sizeof(kCtrlPins) / sizeof(kCtrlPins[0]);

static uint32_t readMv(int pin) {
  uint32_t acc = 0;
  for (int i = 0; i < 8; ++i) acc += analogReadMilliVolts(pin);
  return acc / 8;
}

static void sweep(const char* label) {
  Serial.printf("  %-22s", label);
  for (int i = 0; i < kNumAdc; ++i) Serial.printf(" %5u", readMv(kAdcPins[i]));
  Serial.println();
}

void setup() {
  Serial.begin(115200);
  delay(3000);                 // native USB CDC needs a moment before anyone is listening

  Serial.println();
  Serial.println("=== Heltec V4 ADC sweep — which pin is Vbat? ===");
  Serial.print("  pin ->                ");
  for (int i = 0; i < kNumAdc; ++i) Serial.printf(" %5d", kAdcPins[i]);
  Serial.println();

  // Baseline: every control candidate left as a floating input, so nothing is being driven.
  for (int i = 0; i < kNumCtrl; ++i) pinMode(kCtrlPins[i], INPUT);
  delay(200);
  sweep("all ctrl floating");

  // Then one control pin at a time, LOW and HIGH, others returned to floating. A pin whose
  // ADC reading MOVES between these two rows is sitting behind that switch.
  for (int c = 0; c < kNumCtrl; ++c) {
    for (int j = 0; j < kNumCtrl; ++j) pinMode(kCtrlPins[j], INPUT);
    char lbl[32];

    pinMode(kCtrlPins[c], OUTPUT);
    digitalWrite(kCtrlPins[c], LOW);
    delay(300);                                   // let a switched divider settle
    snprintf(lbl, sizeof(lbl), "GPIO%d LOW", kCtrlPins[c]);
    sweep(lbl);

    digitalWrite(kCtrlPins[c], HIGH);
    delay(300);
    snprintf(lbl, sizeof(lbl), "GPIO%d HIGH", kCtrlPins[c]);
    sweep(lbl);
  }

  Serial.println("=== done. A pin that MOVES between a control's LOW and HIGH rows is it. ===");
  Serial.println("=== 1S pack ~3.7-4.2V:  1:1 ~1850-2100 | 2:1 ~1230-1400 | 4.9:1 ~755-857 ===");
}

// Confirm the ONE bit the sweep turned up: GPIO1 reads a pack voltage only while GPIO37 is
// driven HIGH. Toggling it back and forth repeatedly is the difference between a finding
// inferred from a single row and one demonstrated — and it also shows whether the reading
// is stable across settles, which a divider that needs longer than 300 ms would not be.
void loop() {
  static const float kDivider = 4.9f;
  pinMode(37, OUTPUT);

  digitalWrite(37, LOW);
  delay(400);
  uint32_t lo = readMv(1);

  digitalWrite(37, HIGH);
  delay(400);
  uint32_t hi = readMv(1);

  Serial.printf("  GPIO1: ctrl LOW %4u mV | ctrl HIGH %4u mV -> pack %.3f V (x%.1f)\n",
                lo, hi, hi * kDivider / 1000.0f, kDivider);
  delay(2000);
}
