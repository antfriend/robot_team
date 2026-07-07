// test_linkpercept.cpp — native tests for the SP0 link-percept log
// (semantic positioning, ttn-semantic-positioning.md §3 Phase 0). Pins the
// per-peer RSSI stats (min/median/max out of the histogram) and the @LAT97
// TTDB record format that companion.py `percepts` parses.
#include <cstdio>
#include <cstring>
#include <string>

#include "LinkPercept.h"

static int g_fail = 0;
#define CHECK(cond, msg)                                   \
  do {                                                     \
    if (cond) {                                            \
      printf("ok   %s\n", msg);                            \
    } else {                                               \
      printf("FAIL %s (%s:%d)\n", msg, __FILE__, __LINE__); \
      g_fail++;                                            \
    }                                                      \
  } while (0)

int main() {
  using namespace linkpercept;

  // --- stats: min / median / max from the histogram ---------------------
  Log log;
  log.reset(1000);
  // Peer 0x10: RSSI stream with a known median. 5 obs: -70 -60 -50 -50 -40.
  log.add(0x10, -50, PROTO_ESPNOW);
  log.add(0x10, -70, PROTO_ESPNOW);
  log.add(0x10, -40, PROTO_ESPNOW);
  log.add(0x10, -60, PROTO_ESPNOW);
  log.add(0x10, -50, PROTO_ESPNOW);
  uint32_t peer, n;
  uint8_t proto;
  int rmin, rmed, rmax;
  CHECK(log.stats(0, peer, proto, n, rmin, rmed, rmax), "stats on slot 0");
  CHECK(peer == 0x10 && proto == PROTO_ESPNOW, "peer id + proto");
  CHECK(n == 5, "n counts all observations");
  CHECK(rmin == -70, "rssi_min");
  CHECK(rmed == -50, "rssi_med (middle of 5)");
  CHECK(rmax == -40, "rssi_max");

  // --- rssi 0 = unknown (2.x core) is not evidence ----------------------
  log.add(0x10, 0, PROTO_ESPNOW);
  log.stats(0, peer, proto, n, rmin, rmed, rmax);
  CHECK(n == 5, "rssi 0 ignored");

  // --- clamping ----------------------------------------------------------
  log.add(0x11, -120, PROTO_ESPNOW);  // below domain -> clamps to -100
  log.add(0x11, -5, PROTO_ESPNOW);    // above domain -> clamps to -10
  CHECK(log.stats(1, peer, proto, n, rmin, rmed, rmax), "second peer slot");
  CHECK(rmin == -100 && rmax == -10, "rssi clamped to [-100,-10]");

  // --- same peer over a different proto = its own slot -------------------
  log.add(0x10, -80, PROTO_BLE);
  CHECK(log.peerCount() == 3, "(peer, proto) keys the slot");

  // --- due(): window gating ----------------------------------------------
  CHECK(!log.due(1000 + LINKPERCEPT_FLUSH_MS - 1), "not due before the window");
  CHECK(log.due(1000 + LINKPERCEPT_FLUSH_MS), "due after the window");

  // --- buildRecord: format + reset ----------------------------------------
  char rec[1024];
  size_t m = log.buildRecord(rec, sizeof(rec), 3, 1783382400u,
                             1783382400123ull, true, 1000 + 60000);
  CHECK(m > 0 && m < sizeof(rec), "buildRecord wrote");
  std::string s(rec, m);
  CHECK(s.find("@LAT97LON3 | created:1783382400") != std::string::npos,
        "@LAT97 lane header with lane index");
  CHECK(s.find("**LINKWIN** t_ms:1783382400123 synced:1 window_ms:60000") !=
            std::string::npos,
        "LINKWIN window line");
  CHECK(s.find("**LINK** peer:0x00000010 proto:espnow n:5 rssi_min:-70 "
               "rssi_med:-50 rssi_max:-40") != std::string::npos,
        "LINK line for peer 0x10 espnow");
  CHECK(s.find("proto:ble n:1 rssi_min:-80") != std::string::npos,
        "LINK line for peer 0x10 ble");
  CHECK(s.rfind("\n---\n", 1) == 0 || s.compare(0, 5, "\n---\n") == 0,
        "record starts with the separator");
  CHECK(log.totalObs() == 0 && log.peerCount() == 0, "flush clears the window");
  CHECK(log.windowStartMs() == 1000 + 60000, "new window starts at flush time");

  // --- empty flush: nothing written, window still resets ------------------
  m = log.buildRecord(rec, sizeof(rec), 4, 0, 0, false, 90000);
  CHECK(m == 0, "empty window writes nothing");
  CHECK(!log.due(90000 + LINKPERCEPT_FLUSH_MS + 1), "empty window is never due");

  // --- unsynced record ------------------------------------------------------
  log.add(0x200, -55, PROTO_ESPNOW);
  m = log.buildRecord(rec, sizeof(rec), 0, 0, 12345, false, 90000 + 60000);
  s.assign(rec, m);
  CHECK(s.find("**LINKWIN** t_ms:12345 synced:0") != std::string::npos,
        "unsynced window carries millis + synced:0");

  printf(g_fail ? "\n%d FAILURE(S)\n" : "\nall linkpercept tests passed\n",
         g_fail);
  return g_fail ? 1 : 0;
}
