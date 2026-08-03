// EntityPercept.h — SP0 entity-co-occurrence instrumentation for SEMANTIC
// POSITIONING (Act II, ttn-semantic-positioning.md §3 Phase 0, second tier).
//
// The sibling of LinkPercept. Where LinkPercept turns every *frame reception*
// into ranging evidence (per-peer RSSI), EntityPercept turns every *external
// entity sighting* into co-occurrence evidence: a duty-cycled WiFi scan feeds
// each visible AP's BSSID here; per-window the sketch renders one TTDB record
// (@LAT96 lane) with a **ENTITY** line per BSSID. Two nodes that see the same
// APs are probably near each other — the Jaccard overlap of their entity sets
// is a coarse proximity BOUND (spec §2.2: "they share 6 APs, they cannot be
// 800 m apart"), consolidated by companion.py, never on-device.
//
// Same discipline as LinkPercept: fixed RAM buffers, no per-sighting flash
// write, portable (no Arduino dependency) so the stats + record format are
// pinned by tests/test_entitypercept.cpp. The sketch supplies the scan hook
// (WiFi.scanNetworks) and the Ttdb::appendRecord.
//
// Concurrency: add() runs wherever the scan result is walked (loop() on the
// V4s — WiFi.scanNetworks is not called from an ISR), flush in loop(); the
// buffers are increment-only, matching LinkPercept's lock-free pragmatism.
#pragma once
#include <stdint.h>
#include <stddef.h>
#include <TimeStream.h>   // the shared time stamp every record carries

#ifndef ENTITYPERCEPT_MAX_ENTITIES
#define ENTITYPERCEPT_MAX_ENTITIES 12   // distinct entities kept per window
#endif
#ifndef ENTITYPERCEPT_FLUSH_MS
// Entities change slowly; a longer window than LinkPercept's. Bring-up: 1 min.
#define ENTITYPERCEPT_FLUSH_MS 60000
#endif
#ifndef ENTITYPERCEPT_MAX_LANE
// Cap the @LAT96 lane like LinkPercept caps @LAT97: the TTDB index + flash must
// not fill before SP1 consolidation/pruning. Stats keep cycling; append skips.
#define ENTITYPERCEPT_MAX_LANE 48
#endif

namespace entitypercept {

// Entity classes (spec §Phase 0). WiFi APs first; BLE MACs reuse the same lane
// once the BLE scanner surfaces raw MACs (today BLE feeds LinkPercept ranging).
enum Kind : uint8_t { KIND_WIFI_AP = 0, KIND_BLE_MAC = 1 };
const char* kindName(uint8_t k);

const int ENTITY_ID_LEN = 6;   // BSSID / MAC — 6 bytes

struct EntityStats {
  uint8_t id[ENTITY_ID_LEN];
  uint8_t kind;
  uint32_t n;        // sightings this window (dedup-merged across scans)
  int8_t rssi_max;   // strongest sighting (nearest the AP)
};

class Log {
 public:
  Log() { reset(0); }

  // Record one entity sighting (BSSID + RSSI). Deduped by (id, kind): a repeat
  // increments n and keeps the strongest RSSI. rssi==0 is ignored (unknown).
  // Call while walking a completed WiFi scan, not from an ISR.
  void add(const uint8_t id[ENTITY_ID_LEN], int rssi, uint8_t kind);

  // True when the window elapsed and at least one entity was seen.
  bool due(uint32_t now_ms) const;

  int totalObs() const;
  int entityCount() const { return ent_count_; }

  // Per-entity stats. `id` points into the log's buffer (valid until reset()).
  bool stats(int slot, const uint8_t*& id, uint8_t& kind, uint32_t& n,
             int& rmax) const;

  // Render a complete TTDB record block and start a new window:
  //   \n---\n\n@LAT96LON<lane_n> | created:<t_sec> | ... | relates:observes@LAT0LON0
  //   \n\n**ENTWIN** t_ms:<t_ms> stream:0x<id> wall:<0|1> window_ms:<..> entities:<n>
  //   \n**ENTITY** kind:wifi_ap id:<12 lowercase hex> n:.. rssi:..
  // Returns bytes written, or 0 if there was nothing to flush (still resets the
  // window). Clears all stats.
  size_t buildRecord(char* out, size_t cap, int lane_n, uint32_t t_sec,
                     const timestream::Stamp& ts, uint32_t now_ms);

  void reset(uint32_t now_ms);

 private:
  int slotFor(const uint8_t id[ENTITY_ID_LEN], uint8_t kind);

  EntityStats ents_[ENTITYPERCEPT_MAX_ENTITIES];
  int ent_count_;
  uint32_t window_start_ms_;
};

}  // namespace entitypercept
