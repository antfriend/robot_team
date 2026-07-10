// BleLink.h — BLE near-range proximity tier for SEMANTIC POSITIONING (SP0).
//
// The near-range companion to the ESP-NOW link-percept path
// (ttn-semantic-positioning.md §3 Phase 0): each node advertises a small key-tagged
// fleet id over BLE and passively scans for peers. Every decoded fleet advert becomes
// a proximity observation — (peer_id, RSSI) — reported to a callback the sketch wires
// into LinkPercept as PROTO_BLE, so BLE receptions flow through the exact same
// @LAT97 → @BELIEF:PROXIMITY (proto:ble) pipeline as ESP-NOW.
//
// ESP32-only glue over the core BLE library (no native test); the advert codec it
// relies on (toot::buildBleAdvert / parseBleAdvert) is portable and native-tested in
// the Toot library. Coexists with WiFi/ESP-NOW through the ESP32 radio arbiter — keep
// the scan passive + duty-cycled so it doesn't starve the mesh.
#pragma once
#include <stdint.h>
#include <stddef.h>

namespace blelink {

// Called from the BLE scan task for each decoded, key-verified fleet advert. Must be
// cheap + non-blocking (feed a LinkPercept histogram, set a flag) — same discipline as
// the ESP-NOW recv callback.
typedef void (*ObserveFn)(uint32_t peer_id, int rssi);

// Start BLE: advertise this node's fleet advert as manufacturer data and begin a
// passive, duty-cycled scan. `key`/`key_len` must be the shared toot key (the advert
// tag proves key possession). `cb` receives each fleet peer's (id, RSSI). Call once,
// after WiFi/ESP-NOW is up.
void begin(uint32_t node_id, const uint8_t* key, size_t key_len, ObserveFn cb);

// Reserved periodic hook (the BLE stack scans/advertises in its own tasks; nothing is
// required here today). Safe to call every loop().
void loop();

}  // namespace blelink
