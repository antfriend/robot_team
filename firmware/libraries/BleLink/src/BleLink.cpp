// BleLink.cpp — see BleLink.h. ESP32 core BLE glue for the SP0 near-range tier.
#include "BleLink.h"

#include <string>

#include <Arduino.h>
#include <Toot.h>
#include <BLEDevice.h>
#include <BLEAdvertising.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

namespace blelink {

static ObserveFn gCb = nullptr;
static const uint8_t* gKey = nullptr;
static size_t gKeyLen = 0;

// Scan-result handler. Runs in the BLE host task for EVERY advertisement in range
// (phones, watches, beacons, …), so it must be allocation-free: we register with
// shouldParse=false (see begin()), which makes the core store only the RAW payload and
// skip its own advert parser — that parser's per-advert std::vector<BLEUUID> allocations
// exhausted the memory-tight T-Deck's heap and, with C++ exceptions disabled, aborted
// (operator new -> bad_alloc -> std::terminate). Here we walk the raw AD structures for
// the manufacturer-specific field (type 0xFF) ourselves and verify the fleet key tag —
// no String, no vector, no heap churn.
class ScanCB : public BLEAdvertisedDeviceCallbacks {
  void onResult(BLEAdvertisedDevice dev) override {
    if (!gCb) return;
    const uint8_t* p = dev.getPayload();
    size_t n = dev.getPayloadLength();
    if (!p || n == 0) return;
    for (size_t i = 0; i + 1 < n;) {          // AD structures: [len][type][data..]
      uint8_t len = p[i];
      if (len == 0 || i + 1 + len > n) break;
      if (p[i + 1] == 0xFF) {                  // manufacturer-specific data
        uint32_t peer;
        if (toot::parseBleAdvert(p + i + 2, (size_t)(len - 1), gKey, gKeyLen, peer)) {
          gCb(peer, dev.getRSSI());
          return;
        }
      }
      i += 1 + len;
    }
  }
};

void begin(uint32_t node_id, const uint8_t* key, size_t key_len, ObserveFn cb) {
  gCb = cb;
  gKey = key;
  gKeyLen = key_len;

  BLEDevice::init("");   // empty name keeps the advert compact (room for our mfg data)

  // Advertise our key-tagged fleet advert as manufacturer-specific data.
  uint8_t blob[toot::BLE_ADVERT_LEN];
  toot::buildBleAdvert(blob, sizeof(blob), node_id, key, key_len);
  BLEAdvertisementData advData;
  advData.setFlags(0x06);   // LE General Discoverable + BR/EDR not supported
  // setManufacturerData takes Arduino String on the 3.x core (V4/T-Deck) but std::string
  // on the K10's 2.x DFRobot core — build the right type from the same binary blob.
#if defined(ESP_ARDUINO_VERSION_MAJOR) && ESP_ARDUINO_VERSION_MAJOR >= 3
  advData.setManufacturerData(String(blob, sizeof(blob)));
#else
  advData.setManufacturerData(
      std::string(reinterpret_cast<const char*>(blob), sizeof(blob)));
#endif
  BLEAdvertising* adv = BLEDevice::getAdvertising();
  adv->setAdvertisementData(advData);
  adv->setScanResponse(false);
  adv->setMinInterval(0x00A0);   // 0x00A0*0.625ms = 100 ms
  adv->setMaxInterval(0x0140);   // 200 ms — cheap, still frequent enough to range
  adv->start();

  // 🔬 Build-property switch (2026-10-01): with BLE on, the Cardputer's free heap drains
  // ~500 B/min to zero and resets the node; with BLE compiled out it is flat at 108 KB.
  // BLELINK_SCAN=0 keeps the advert and drops the scanner, to split those two halves.
#if defined(BLELINK_SCAN) && BLELINK_SCAN == 0
  return;
#endif
  // Passive, duty-cycled scan; wantDuplicates=true so every reception feeds the
  // histogram (we WANT repeats). Passive = listen only, less airtime for WiFi coexist.
  BLEScan* scan = BLEDevice::getScan();
  // shouldParse=false: hand us the raw payload, skip the core's allocating advert parser
  // (the T-Deck OOM/abort fix — we parse the manufacturer field ourselves in ScanCB).
  scan->setAdvertisedDeviceCallbacks(new ScanCB(), /*wantDuplicates=*/true,
                                     /*shouldParse=*/false);
  scan->setActiveScan(false);
  scan->setInterval(160);   // 100 ms
  scan->setWindow(60);      // 37.5 ms listen (~37% duty) — leaves airtime for ESP-NOW
  scan->start(0, nullptr, false);   // duration 0 = scan until stopped
}

// 60 s, MEASURED (2026-10-01, Cardputer, peers off, 12 min): free heap held ~26.4 KB ±300 B
// and maxalloc ROSE 8 → 17 KB, against ≈ −500 B/min to a reset every ~20 min without it.
// V4-A, same day: −517 B/min unpatched (136.6 → 129.1 KB in 14.5 min, zero in ~4.4 h — the
// 2026-08 decline), and with this on, free heap read EXACTLY 145,172 B after every restart
// for 15 min. ⚠ Takes effect only on a board that CALLS blelink::loop(): every sketch with
// USE_BLE 1 does as of 2026-10-01 (Cardputer, V4-A/B/C, T-Deck; the K10 builds USE_BLE 0).
// A library #define, so it changes only as a BUILD PROPERTY (separate translation unit).
#ifndef BLELINK_RESTART_MS
#define BLELINK_RESTART_MS 60000
#endif

void loop() {
  // The BLE stack advertises/scans in its own FreeRTOS tasks; nothing is needed here —
  // EXCEPT the 2026-10-01 leak: the continuous (`start(0)`) passive scan drains free heap
  // ~500 B/min on the Cardputer, from FOREIGN adverts alone (peers off; the callback never
  // fired). Advertise-only is flat. BLELINK_RESTART_MS > 0 periodically stops, clears and
  // restarts the scan, to test whether the stack releases what it holds across a restart.
  // 0 = never. A sketch that does not call loop() is unaffected at any value.
#if BLELINK_RESTART_MS > 0 && !(defined(BLELINK_SCAN) && BLELINK_SCAN == 0)
  static uint32_t last = 0;
  const uint32_t now = millis();
  if (last == 0) { last = now; return; }
  if (now - last < (uint32_t)BLELINK_RESTART_MS) return;
  last = now;
  BLEScan* scan = BLEDevice::getScan();
  scan->stop();
  scan->clearResults();
  scan->start(0, nullptr, false);
#endif
}

}  // namespace blelink
