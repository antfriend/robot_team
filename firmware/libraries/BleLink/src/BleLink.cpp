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

// Scan-result handler: decode manufacturer data as a fleet advert (magic + key tag)
// and report the peer + RSSI. Runs in the BLE task — keep it light (Phase-1b discipline).
class ScanCB : public BLEAdvertisedDeviceCallbacks {
  void onResult(BLEAdvertisedDevice dev) override {
    if (!gCb || !dev.haveManufacturerData()) return;
    String md = dev.getManufacturerData();
    uint32_t peer;
    if (toot::parseBleAdvert(reinterpret_cast<const uint8_t*>(md.c_str()),
                             md.length(), gKey, gKeyLen, peer))
      gCb(peer, dev.getRSSI());
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
  scan->setAdvertisedDeviceCallbacks(new ScanCB(), /*wantDuplicates=*/true);
  scan->setActiveScan(false);
  scan->setInterval(160);   // 100 ms
  scan->setWindow(60);      // 37.5 ms listen (~37% duty) — leaves airtime for ESP-NOW
  scan->start(0, nullptr, false);   // duration 0 = scan until stopped
}

void loop() {
  // The BLE stack advertises/scans in its own FreeRTOS tasks; no periodic work needed.
}

}  // namespace blelink
