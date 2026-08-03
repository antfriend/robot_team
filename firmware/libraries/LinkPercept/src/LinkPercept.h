// LinkPercept.h — SP0 instrumentation for SEMANTIC POSITIONING (Act II).
//
// "Every frame reception becomes a percept" (ttn-semantic-positioning.md §3
// Phase 0). The radio recv callback calls add() with the sender's node id and
// the frame's RSSI; per-peer fixed histograms accumulate in RAM (never a
// per-packet flash write — flash-wear discipline). Once per window the sketch
// asks buildRecord() for a complete TTDB record block (@LAT97 lane, one
// **LINK** line per peer with n / rssi min / med / max) and appends it with
// Ttdb::appendRecord, exactly like the @LAT99 sync log.
//
// Portable: no Arduino dependency, so the stats and the record format are
// pinned by the native test (tests/test_linkpercept.cpp).
//
// Concurrency note: add() runs in the WiFi task, flush in loop(). The buffers
// are fixed and increment-only, so the worst race is a lost increment or a
// stat read mid-update during a flush — an acceptable percept loss, matching
// the fleet's volatile-flag pragmatism. No locks in the recv path.
#pragma once
#include <stdint.h>
#include <stddef.h>
#include <TimeStream.h>   // the shared time stamp every record carries

#ifndef LINKPERCEPT_MAX_PEERS
#define LINKPERCEPT_MAX_PEERS 8      // distinct (peer, proto) slots per window
#endif
#ifndef LINKPERCEPT_FLUSH_MS
#define LINKPERCEPT_FLUSH_MS 60000   // bring-up: 1-min windows; raise for the field
#endif
#ifndef LINKPERCEPT_MAX_LANE
// Stop appending once the @LAT97 lane holds this many records: the TTDB index
// (TTDB_MAX_RECORDS) and flash must not fill before SP1 consolidation+pruning
// exists. Stats keep accumulating/clearing; only the append is skipped.
#define LINKPERCEPT_MAX_LANE 48
#endif

namespace linkpercept {

enum Proto : uint8_t { PROTO_ESPNOW = 0, PROTO_LORA = 1, PROTO_BLE = 2 };
const char* protoName(uint8_t p);

// Histogram domain: RSSI clamped to [-100, -10] dBm.
const int RSSI_MIN = -100;
const int RSSI_MAX = -10;
const int RSSI_BUCKETS = RSSI_MAX - RSSI_MIN + 1;

struct PeerStats {
  uint32_t peer;
  uint8_t proto;
  uint32_t n;
  uint16_t hist[RSSI_BUCKETS];
};

class Log {
 public:
  Log() { reset(0); }

  // Record one AUTHENTICATED frame reception (call after toot::decode succeeds
  // — spoofed frames must not become evidence; dedup-dropped duplicates are
  // fine, the reception physics is real). rssi==0 means "unknown" (2.x cores)
  // and is ignored. Safe to call from the radio recv callback.
  void add(uint32_t peer, int rssi, uint8_t proto);

  // True when the window has elapsed and at least one observation is waiting.
  bool due(uint32_t now_ms) const;

  int totalObs() const;
  int peerCount() const { return peer_count_; }

  // When the current window opened. tests/test_linkpercept.cpp asserts on this to prove
  // a flush re-bases the window at flush time rather than at the next observation — the
  // difference matters because `window_ms` in the record is derived from it, and a
  // window that silently starts late reports a shorter one than it measured. (The
  // accessor was missing until 2026-08-01, so that test had not compiled, and therefore
  // `cd tests && make` had not built, for as long as the assertion had been there.)
  uint32_t windowStartMs() const { return window_start_ms_; }

  // Per-peer stats out of the histogram (median = middle observation).
  bool stats(int slot, uint32_t& peer, uint8_t& proto, uint32_t& n,
             int& rmin, int& rmed, int& rmax) const;

  // Render a complete TTDB record block and start a new window:
  //   \n---\n\n@LAT97LON<lane_n> | created:<t_sec> | ... | relates:observes@LAT0LON0
  //   \n\n**LINKWIN** t_ms:<t_ms> stream:0x<id> wall:<0|1> window_ms:<elapsed>
  //   \n**LINK** peer:0x000000NN proto:espnow n:.. rssi_min:.. rssi_med:.. rssi_max:..
  // Returns bytes written, or 0 if there was nothing to flush (still resets
  // the window). Clears all stats.
  size_t buildRecord(char* out, size_t cap, int lane_n, uint32_t t_sec,
                     const timestream::Stamp& ts, uint32_t now_ms);

  void reset(uint32_t now_ms);

 private:
  int slotFor(uint32_t peer, uint8_t proto);

  PeerStats peers_[LINKPERCEPT_MAX_PEERS];
  int peer_count_;
  uint32_t window_start_ms_;
};

}  // namespace linkpercept
