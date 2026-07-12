// EntityPercept.cpp — see EntityPercept.h. Portable; native-tested.
#include "EntityPercept.h"
#include <stdio.h>
#include <string.h>

namespace entitypercept {

const char* kindName(uint8_t k) {
  switch (k) {
    case KIND_WIFI_AP: return "wifi_ap";
    case KIND_BLE_MAC: return "ble_mac";
    default: return "?";
  }
}

void Log::reset(uint32_t now_ms) {
  memset(ents_, 0, sizeof(ents_));
  ent_count_ = 0;
  window_start_ms_ = now_ms;
}

int Log::slotFor(const uint8_t id[ENTITY_ID_LEN], uint8_t kind) {
  for (int i = 0; i < ent_count_; ++i)
    if (ents_[i].kind == kind && memcmp(ents_[i].id, id, ENTITY_ID_LEN) == 0)
      return i;
  if (ent_count_ >= ENTITYPERCEPT_MAX_ENTITIES) return -1;  // window full: drop
  int i = ent_count_++;
  memcpy(ents_[i].id, id, ENTITY_ID_LEN);
  ents_[i].kind = kind;
  ents_[i].n = 0;
  ents_[i].rssi_max = -128;
  return i;
}

void Log::add(const uint8_t id[ENTITY_ID_LEN], int rssi, uint8_t kind) {
  if (rssi == 0) return;            // unknown — not evidence
  if (rssi < -128) rssi = -128;
  if (rssi > 0) rssi = 0;
  int i = slotFor(id, kind);
  if (i < 0) return;
  ents_[i].n++;
  if ((int8_t)rssi > ents_[i].rssi_max) ents_[i].rssi_max = (int8_t)rssi;
}

bool Log::due(uint32_t now_ms) const {
  if (totalObs() == 0) return false;
  return (uint32_t)(now_ms - window_start_ms_) >= (uint32_t)ENTITYPERCEPT_FLUSH_MS;
}

int Log::totalObs() const {
  int t = 0;
  for (int i = 0; i < ent_count_; ++i) t += (int)ents_[i].n;
  return t;
}

bool Log::stats(int slot, const uint8_t*& id, uint8_t& kind, uint32_t& n,
                int& rmax) const {
  if (slot < 0 || slot >= ent_count_ || ents_[slot].n == 0) return false;
  const EntityStats& e = ents_[slot];
  id = e.id;
  kind = e.kind;
  n = e.n;
  rmax = e.rssi_max;
  return true;
}

size_t Log::buildRecord(char* out, size_t cap, int lane_n, uint32_t t_sec,
                        uint64_t t_ms, bool synced, uint32_t now_ms) {
  if (totalObs() == 0) {
    reset(now_ms);
    return 0;
  }
  uint32_t window_ms = now_ms - window_start_ms_;
  size_t w = 0;
  int m = snprintf(out + w, cap - w,
                   "\n---\n\n@LAT96LON%d | created:%lu | updated:%lu | "
                   "relates:observes@LAT0LON0\n\n"
                   "**ENTWIN** t_ms:%llu synced:%d window_ms:%lu entities:%d\n",
                   lane_n, (unsigned long)t_sec, (unsigned long)t_sec,
                   (unsigned long long)t_ms, synced ? 1 : 0,
                   (unsigned long)window_ms, ent_count_);
  if (m < 0 || (size_t)m >= cap - w) return 0;
  w += (size_t)m;
  for (int i = 0; i < ent_count_; ++i) {
    const uint8_t* id;
    uint8_t kind;
    uint32_t n;
    int rmax;
    if (!stats(i, id, kind, n, rmax)) continue;
    m = snprintf(out + w, cap - w,
                 "**ENTITY** kind:%s id:%02x%02x%02x%02x%02x%02x n:%lu rssi:%d\n",
                 kindName(kind), id[0], id[1], id[2], id[3], id[4], id[5],
                 (unsigned long)n, rmax);
    if (m < 0 || (size_t)m >= cap - w) break;  // out of room: emit what fits
    w += (size_t)m;
  }
  reset(now_ms);
  return w;
}

}  // namespace entitypercept
