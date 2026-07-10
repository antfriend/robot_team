// BleLink.cpp — see BleLink.h. ESP32 core BLE glue for the SP0 near-range tier.
#include "BleLink.h"

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
  advData.setManufacturerData(String(blob, sizeof(blob)));   // (uint8_t*, len) ctor
  BLEAdvertising* adv = BLEDevice::getAdvertising();
  adv->setAdvertisementData(advData);
  adv->setScanResponse(false);
  adv->setMinInterval(0x00A0);   // 0x00A0*0.625ms = 100 ms
  adv->setMaxInterval(0x0140);   // 200 ms — cheap, still frequent enough to range
  adv->start();

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

void loop() {
  // The BLE stack advertises/scans in its own FreeRTOS tasks; no periodic work needed.
}

}  // namespace blelink
