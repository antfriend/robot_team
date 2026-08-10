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
  // ⚠ ENTITYPERCEPT_RECORD_BUF, not a hand-picked 512. Since the lane became
  // change-triggered a record can carry a **CORE** list and a **COVERED** union, and
  // buildRecord writes NOTHING rather than truncating — so a local guess here would
  // fail as "wrote 0 bytes" and read like a logic bug.
  char rec[ENTITYPERCEPT_RECORD_BUF];
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

  // =====================================================================
  // CHANGE-TRIGGERED WITH RUN-LENGTH (Part 2, 2026-08-10)
  //
  // The property that justifies the whole fold is that THE RUN'S UNION IS
  // RECOVERABLE FROM THE RECORD THAT COVERS IT — the lane's consumer computes a
  // union (companion.py `_entity_set` -> the Jaccard proximity bound), so a fold
  // that loses an AP is a fold that moves a position estimate.
  // =====================================================================
  {
    Log lg;
    char buf[ENTITYPERCEPT_RECORD_BUF];
    uint32_t t = 0;
    int lane = 0;
    // One window: feed the listed APs, close it, return bytes written.
    auto window = [&](const uint8_t* const* aps, int n_aps) -> size_t {
      for (int i = 0; i < n_aps; ++i) lg.add(aps[i], -60, KIND_WIFI_AP);
      t += ENTITYPERCEPT_FLUSH_MS;
      size_t m = lg.buildRecord(buf, sizeof(buf), lane, 1780000000 + t / 1000,
                                ST(1780000000000ULL + t, true), t);
      if (m) ++lane;
      return m;
    };
    const uint8_t* two[]   = {AP1, AP2};
    static const uint8_t AP3[6] = {0x0c, 0x0f, 0xee, 0x00, 0x00, 0x03};
    const uint8_t* three[] = {AP1, AP2, AP3};

    // w1: nothing has run before -> reason:first, and the core cannot exist yet
    // (1 window of history against CORE_N 3), which the record says out loud.
    size_t m1 = window(two, 2);
    CHECK(m1 > 0 && lg.lastClose() == CLOSE_WRITTEN, "w1 opens a run (written)");
    std::string r1(buf, m1);
    CHECK(r1.find("**RUN** windows_since_last:1 reason:first") != std::string::npos,
          "w1 RUN line: reason:first, gap 1");
    CHECK(r1.find("**CORE** entities:0\n") != std::string::npos,
          "w1 core is EMPTY and says so (no ids: field when there are none)");
    CHECK(r1.find("core_windows:1") != std::string::npos,
          "w1 states the history depth, so an empty core reads as WARMING not unstable");
    CHECK(r1.find("**COVERED**") == std::string::npos,
          "w1 has no COVERED block — there is nothing behind it");

    // w2: same two APs. Still 2-of-2 < CORE_N, so the core has not changed (still
    // empty) and the window folds.
    CHECK(window(two, 2) == 0 && lg.lastClose() == CLOSE_COVERED,
          "w2 folds into the run (0 bytes, CLOSE_COVERED)");

    // w3: now 3-of-3 -> the core becomes {AP1,AP2}. That is a CHANGE, so it writes.
    size_t m3 = window(two, 2);
    CHECK(m3 > 0 && lg.lastClose() == CLOSE_WRITTEN, "w3 core appears -> written");
    std::string r3(buf, m3);
    CHECK(r3.find("**RUN** windows_since_last:2 reason:changed") != std::string::npos,
          "w3 RUN line: gap 2 (w2 was suppressed), reason:changed");
    CHECK(r3.find("**CORE** entities:2 ids:") != std::string::npos,
          "w3 CORE lists the two stable APs");
    CHECK(r3.find("a42bb0112233") != std::string::npos &&
          r3.find("deadbeef0001") != std::string::npos, "w3 CORE ids are both APs");
    CHECK(r3.find("**COVERED** windows:1 entities:2") != std::string::npos,
          "w3 COVERED accounts for the one suppressed window");
    CHECK(r3.find("covered_by:@LAT96LON0") != std::string::npos,
          "COVERED names the record whose run spoke for it, not itself");

    // ---- THE UNION PROPERTY -------------------------------------------
    // w4 sees a THIRD AP once. One sighting in five windows never enters the core,
    // so the window folds — and an AP that appears ONLY in folded windows is exactly
    // what a naive run-length would lose.
    CHECK(window(three, 3) == 0 && lg.lastClose() == CLOSE_COVERED,
          "w4 (transient 3rd AP) folds: one sighting never joins the core");
    for (int i = 0; i < 4; ++i) window(two, 2);      // w5..w8 fold; w9 heartbeats
    size_t m9 = window(two, 2);
    CHECK(m9 > 0 && lg.lastClose() == CLOSE_WRITTEN,
          "w9 writes on the heartbeat (run reached ENTITYPERCEPT_MAX_RUN)");
    std::string r9(buf, m9);
    CHECK(r9.find("reason:heartbeat") != std::string::npos, "w9 reason:heartbeat");
    CHECK(r9.find("**COVERED-ENTITY** kind:wifi_ap id:0c0fee000003") != std::string::npos,
          "THE TRANSIENT AP SURVIVES THE FOLD in COVERED-ENTITY — the union is intact");
    CHECK(r9.find("id:0c0fee000003 n:1 rssi:-60 windows:1") != std::string::npos,
          "and it carries its aggregate: 1 sighting, in 1 of the covered windows");
    CHECK(r9.find("**CORE** entities:2") != std::string::npos,
          "the transient never entered the core, which is the point of a core");

    // ⚠ NEEDLE COLLISION, the family this corpus keeps re-learning (prev_stream:,
    // **COVERED-SPAN**, HEADER_SID_RE). `**COVERED-ENTITY**` must NOT contain the
    // `**ENTITY**` needle, or every reader counting a window's own entities silently
    // folds in the run's union and over-reports what the node saw in that window.
    size_t own = 0, from = 0;
    while ((from = r9.find("**ENTITY**", from)) != std::string::npos) { ++own; from += 4; }
    CHECK(own == 2, "**ENTITY** matches exactly the window's own 2 lines, not COVERED-ENTITY");
  }

  // --- the buffer is pinned in BOTH directions ---------------------------
  // [[render-buffers-belong-in-libraries]]: the size lives in the library because a
  // native test cannot call into a .ino, and it is only pinned if the test shows both
  // that the worst case FITS the new constant and that it does NOT fit the old one.
  {
    Log lg;
    char buf[ENTITYPERCEPT_RECORD_BUF];
    uint32_t t = 0;
    size_t worst = 0;
    // Grow a wide union under a stable core: 12 entities per window, with rotating
    // extras so the covered union climbs toward ENTITYPERCEPT_MAX_UNION.
    for (int w = 0; w < 12; ++w) {
      for (int i = 0; i < ENTITYPERCEPT_MAX_ENTITIES - 1; ++i) {
        uint8_t ap[6] = {0x02, 0x00, 0x00, 0x00, 0x00, (uint8_t)i};
        lg.add(ap, -70 - i, KIND_WIFI_AP);
      }
      uint8_t rot[6] = {0x03, 0x00, 0x00, 0x00, 0x00, (uint8_t)w};   // a fresh AP each window
      lg.add(rot, -80, KIND_WIFI_AP);
      t += ENTITYPERCEPT_FLUSH_MS;
      size_t m = lg.buildRecord(buf, sizeof(buf), w, 1780000000 + t / 1000,
                                ST(1780000000000ULL + t, true), t);
      if (m > worst) worst = m;
    }
    CHECK(worst > 0, "the wide-union case rendered at all");
    CHECK(worst <= ENTITYPERCEPT_RECORD_BUF, "worst case FITS ENTITYPERCEPT_RECORD_BUF");
    CHECK(worst > 1024,
          "and does NOT fit the sketches' old char rec[1024] — which is why the "
          "constant moved into the library");
    printf("     (worst @LAT96 record measured: %u B of %d)\n",
           (unsigned)worst, ENTITYPERCEPT_RECORD_BUF);

    // A record that does not fit is written NOT AT ALL — never truncated. A partial
    // entity list is a record that under-reports the set while looking complete.
    Log lg2;
    char small[600];
    for (int i = 0; i < ENTITYPERCEPT_MAX_ENTITIES; ++i) {
      uint8_t ap[6] = {0x04, 0x00, 0x00, 0x00, 0x00, (uint8_t)i};
      lg2.add(ap, -70, KIND_WIFI_AP);
    }
    size_t m = lg2.buildRecord(small, sizeof(small), 0, 1780000000,
                               ST(1780000000000ULL, true), ENTITYPERCEPT_FLUSH_MS);
    CHECK(m == 0 && lg2.lastClose() == CLOSE_EMPTY,
          "an undersized buffer yields 0 bytes and CLOSE_EMPTY, never a truncated record");
  }

  // --- union overflow ENDS the run rather than dropping an entity --------
  {
    Log lg;
    char buf[ENTITYPERCEPT_RECORD_BUF];
    uint32_t t = 0;
    bool saw_union_full = false;
    for (int w = 0; w < 12; ++w) {
      // A stable pair keeps the core fixed; SIX fresh APs every window make the union
      // climb faster than the heartbeat can close the run. ⚠ Six and not one: with
      // ENTITYPERCEPT_MAX_RUN 6 a run of single newcomers reaches the heartbeat long
      // before ENTITYPERCEPT_MAX_UNION, so a one-per-window test would pass while
      // testing nothing — which is what the first cut of this test did.
      lg.add(AP1, -60, KIND_WIFI_AP);
      lg.add(AP2, -60, KIND_WIFI_AP);
      for (int k = 0; k < 6; ++k) {
        uint8_t rot[6] = {0x05, 0x00, 0x00, 0x00, (uint8_t)w, (uint8_t)k};
        lg.add(rot, -80, KIND_WIFI_AP);
      }
      t += ENTITYPERCEPT_FLUSH_MS;
      size_t m = lg.buildRecord(buf, sizeof(buf), w, 1780000000 + t / 1000,
                                ST(1780000000000ULL + t, true), t);
      if (m && std::string(buf, m).find("reason:union_full") != std::string::npos)
        saw_union_full = true;
    }
    CHECK(saw_union_full,
          "a union that would not fit ENDS the run (reason:union_full) — the record's "
          "capacity bounds the run, so losslessness holds by construction");
  }

  if (g_fail) {
    printf("\n%d FAILED\n", g_fail);
    return 1;
  }
  printf("\nall entitypercept tests passed\n");
  return 0;
}
