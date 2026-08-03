// test_entitypercept.cpp — native tests for the SP0 entity-co-occurrence log
// (semantic positioning, ttn-semantic-positioning.md §3 Phase 0). Pins the
// per-entity stats (dedup by BSSID, sighting count, strongest RSSI) and the
// @LAT96 TTDB record format that companion.py `entities` parses.
#include <cstdio>
#include <cstring>
#include <string>

#include "EntityPercept.h"

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

// The old API took `(t_ms, bool synced)`. It now takes a timestream::Stamp, and the
// migration is exactly: `synced:1` meant "on SOME shared clock, identity unknown" —
// which is a stream with a wall anchor. `synced:0` meant "local millis()", which is
// stream 0. These tests keep their original intent under the new field.
static const uint32_t kStream = 0x5EA51DE7u;
static timestream::Stamp ST(uint64_t t_ms, bool synced) {
  timestream::Stamp s;
  s.t_ms = t_ms;
  s.stream_id = synced ? kStream : 0;
  s.wall = synced;
  return s;
}

static const uint8_t AP1[6] = {0xa4, 0x2b, 0xb0, 0x11, 0x22, 0x33};
static const uint8_t AP2[6] = {0xde, 0xad, 0xbe, 0xef, 0x00, 0x01};

int main() {
  using namespace entitypercept;

  Log log;
  log.reset(1000);

  // --- dedup by BSSID: repeat sightings merge, keeping strongest RSSI -----
  log.add(AP1, -71, KIND_WIFI_AP);
  log.add(AP1, -60, KIND_WIFI_AP);   // stronger — becomes rssi_max
  log.add(AP1, -80, KIND_WIFI_AP);
  log.add(AP2, -50, KIND_WIFI_AP);
  CHECK(log.entityCount() == 2, "two distinct BSSIDs -> two slots");
  CHECK(log.totalObs() == 4, "totalObs counts every sighting");

  const uint8_t* id;
  uint8_t kind;
  uint32_t n;
  int rmax;
  CHECK(log.stats(0, id, kind, n, rmax), "stats on slot 0");
  CHECK(memcmp(id, AP1, 6) == 0 && kind == KIND_WIFI_AP, "slot 0 id + kind");
  CHECK(n == 3, "AP1 sighted 3x");
  CHECK(rmax == -60, "AP1 rssi_max is the strongest sighting");
  CHECK(log.stats(1, id, kind, n, rmax) && n == 1 && rmax == -50, "AP2 single sighting");

  // --- rssi 0 = unknown is not evidence ---------------------------------
  int before = log.totalObs();
  log.add(AP1, 0, KIND_WIFI_AP);
  CHECK(log.totalObs() == before, "rssi 0 ignored (not evidence)");

  // --- record format: @LAT96 lane, ENTWIN header + one ENTITY line per AP -
  char rec[512];
  size_t m = log.buildRecord(rec, sizeof(rec), 3, 1780000000,
                             ST(1780000000123ULL, true), 61000);
  CHECK(m > 0, "buildRecord wrote bytes");
  std::string s(rec, m);
  CHECK(s.find("@LAT96LON3") != std::string::npos, "record on @LAT96 lane");
  CHECK(s.find("**ENTWIN** t_ms:1780000000123 stream:0x5ea51de7 wall:1 "
               "window_ms:60000 entities:2") != std::string::npos,
        "ENTWIN context line");
  CHECK(s.find("**ENTITY** kind:wifi_ap id:a42bb0112233 n:3 rssi:-60")
            != std::string::npos, "AP1 ENTITY line (lowercase hex, no colons)");
  CHECK(s.find("id:deadbeef0001 n:1 rssi:-50") != std::string::npos,
        "AP2 ENTITY line");
  CHECK(s.find("relates:observes@LAT0LON0") != std::string::npos,
        "relates edge to origin");

  // --- buildRecord clears the window -------------------------------------
  CHECK(log.entityCount() == 0 && log.totalObs() == 0, "buildRecord reset the window");

  // --- empty window flushes nothing --------------------------------------
  m = log.buildRecord(rec, sizeof(rec), 4, 1780000100, ST(1780000100000ULL, false), 122000);
  CHECK(m == 0, "empty window -> 0 bytes");

  // --- due(): needs the window to elapse AND an observation --------------
  log.reset(0);
  CHECK(!log.due(ENTITYPERCEPT_FLUSH_MS + 1), "not due with no observations");
  log.add(AP1, -55, KIND_WIFI_AP);
  CHECK(!log.due(ENTITYPERCEPT_FLUSH_MS - 1), "not due before the window elapses");
  CHECK(log.due(ENTITYPERCEPT_FLUSH_MS), "due once the window elapses with obs");

  // --- capacity cap: extra distinct entities are dropped, not overflowed --
  log.reset(0);
  for (int i = 0; i < ENTITYPERCEPT_MAX_ENTITIES + 5; ++i) {
    uint8_t ap[6] = {0x02, 0x00, 0x00, 0x00, 0x00, (uint8_t)i};
    log.add(ap, -70, KIND_WIFI_AP);
  }
  CHECK(log.entityCount() == ENTITYPERCEPT_MAX_ENTITIES, "distinct entities capped at MAX");

  if (g_fail) {
    printf("\n%d FAILED\n", g_fail);
    return 1;
  }
  printf("\nall entitypercept tests passed\n");
  return 0;
}
