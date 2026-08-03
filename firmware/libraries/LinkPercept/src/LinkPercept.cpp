// LinkPercept.cpp — see LinkPercept.h. Portable; native-tested.
#include "LinkPercept.h"
#include <stdio.h>
#include <string.h>

namespace linkpercept {

const char* protoName(uint8_t p) {
  switch (p) {
    case PROTO_ESPNOW: return "espnow";
    case PROTO_LORA: return "lora";
    case PROTO_BLE: return "ble";
    default: return "?";
  }
}

void Log::reset(uint32_t now_ms) {
  memset(peers_, 0, sizeof(peers_));
  peer_count_ = 0;
  window_start_ms_ = now_ms;
}

int Log::slotFor(uint32_t peer, uint8_t proto) {
  for (int i = 0; i < peer_count_; ++i)
    if (peers_[i].peer == peer && peers_[i].proto == proto) return i;
  if (peer_count_ >= LINKPERCEPT_MAX_PEERS) return -1;  // window full: drop
  int i = peer_count_++;
  peers_[i].peer = peer;
  peers_[i].proto = proto;
  peers_[i].n = 0;
  memset(peers_[i].hist, 0, sizeof(peers_[i].hist));
  return i;
}

void Log::add(uint32_t peer, int rssi, uint8_t proto) {
  if (rssi == 0) return;  // unknown (2.x core) — not evidence
  if (rssi < RSSI_MIN) rssi = RSSI_MIN;
  if (rssi > RSSI_MAX) rssi = RSSI_MAX;
  int i = slotFor(peer, proto);
  if (i < 0) return;
  int b = rssi - RSSI_MIN;
  if (peers_[i].hist[b] < 0xFFFF) {
    peers_[i].hist[b]++;
    peers_[i].n++;
  }
}

bool Log::due(uint32_t now_ms) const {
  if (totalObs() == 0) return false;
  return (uint32_t)(now_ms - window_start_ms_) >= (uint32_t)LINKPERCEPT_FLUSH_MS;
}

int Log::totalObs() const {
  int t = 0;
  for (int i = 0; i < peer_count_; ++i) t += (int)peers_[i].n;
  return t;
}

bool Log::stats(int slot, uint32_t& peer, uint8_t& proto, uint32_t& n,
                int& rmin, int& rmed, int& rmax) const {
  if (slot < 0 || slot >= peer_count_ || peers_[slot].n == 0) return false;
  const PeerStats& p = peers_[slot];
  peer = p.peer;
  proto = p.proto;
  n = p.n;
  rmin = 0;
  rmax = 0;
  rmed = 0;
  uint32_t half = (p.n + 1) / 2, cum = 0;
  bool got_min = false, got_med = false;
  for (int b = 0; b < RSSI_BUCKETS; ++b) {
    if (!p.hist[b]) continue;
    if (!got_min) { rmin = RSSI_MIN + b; got_min = true; }
    rmax = RSSI_MIN + b;
    cum += p.hist[b];
    if (!got_med && cum >= half) { rmed = RSSI_MIN + b; got_med = true; }
  }
  return true;
}

size_t Log::buildRecord(char* out, size_t cap, int lane_n, uint32_t t_sec,
                        const timestream::Stamp& ts, uint32_t now_ms) {
  if (totalObs() == 0) {
    reset(now_ms);
    return 0;
  }
  char stamp[64];
  if (!timestream::buildStamp(stamp, sizeof(stamp), ts)) return 0;
  uint32_t window_ms = now_ms - window_start_ms_;
  size_t w = 0;
  int m = snprintf(out + w, cap - w,
                   "\n---\n\n@LAT97LON%d | created:%lu | updated:%lu | "
                   "relates:observes@LAT0LON0\n\n"
                   "**LINKWIN** %s window_ms:%lu\n",
                   lane_n, (unsigned long)t_sec, (unsigned long)t_sec,
                   stamp, (unsigned long)window_ms);
  if (m < 0 || (size_t)m >= cap - w) return 0;
  w += (size_t)m;
  for (int i = 0; i < peer_count_; ++i) {
    uint32_t peer, n;
    uint8_t proto;
    int rmin, rmed, rmax;
    if (!stats(i, peer, proto, n, rmin, rmed, rmax)) continue;
    m = snprintf(out + w, cap - w,
                 "**LINK** peer:0x%08lX proto:%s n:%lu rssi_min:%d "
                 "rssi_med:%d rssi_max:%d\n",
                 (unsigned long)peer, protoName(proto), (unsigned long)n, rmin,
                 rmed, rmax);
    if (m < 0 || (size_t)m >= cap - w) break;  // out of room: emit what fits
    w += (size_t)m;
  }
  reset(now_ms);
  return w;
}

}  // namespace linkpercept
