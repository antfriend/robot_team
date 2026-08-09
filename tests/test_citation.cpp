// test_citation.cpp — TTDB-RFC-0010 §7.2 stage 1: readers accept `#sid`.
//
// The point of this stage is that WRITERS ARE UNCHANGED, so the first thing tested is
// that every existing file still parses byte-identically. The second is the capability
// the sid buys: a citation's freshness decided by a reader holding nothing but the file,
// with no @LAT100 boundary and no timeline comparison.
#include <cstdio>
#include <cstring>
#include "TtdbParse.h"

static int gChecks = 0, gFails = 0;
static void check(bool ok, const char* what) {
  ++gChecks;
  if (!ok) { ++gFails; printf("  FAIL: %s\n", what); }
}

int main() {
  printf("Citation (#sid) tests\n");

  // ---- 1. every PRE-ADOPTION form parses exactly as before -----------------------------
  // ⚠ This is the whole risk of stage 1 and it is why the stage exists separately.
  {
    const char* old_ = "@LAT92LON4 | created:0 | updated:0 | "
                       "relates:testifies_about@LAT95LON2,derived_from@LAT97LON18,senses@LAT0LON0";
    TtdbRecord r;
    check(ttdbParseHeader(old_, r), "a pre-adoption header still parses");
    check(r.lat == 92 && r.lon == 4, "and its coordinate is unchanged");

    TtdbEdge e[4];
    const uint8_t n = ttdbParseEdges(old_, e, 4);
    check(n == 3, "all three edges still parse");
    check(strcmp(e[1].type, "derived_from") == 0, "the type is unchanged");
    check(e[1].target_lat == 97 && e[1].target_lon == 18, "the target is unchanged");
    check(!e[0].has_target_sid && !e[1].has_target_sid && !e[2].has_target_sid,
          "and no edge claims a sid it does not have");

    uint32_t s = 0xdeadbeef;
    check(!ttdbHeaderSid(old_, s), "a header with no sid reports absent");
    check(s == 0xdeadbeef, "and leaves the output untouched");
  }

  // ---- 2. the new form parses, and the coordinate survives the suffix -------------------
  {
    const char* neu = "@LAT92LON4 | sid:a1b2c3d4 | created:0 | updated:0 | "
                      "relates:derived_from@LAT97LON18#0badc0de,senses@LAT0LON0";
    TtdbRecord r;
    check(ttdbParseHeader(neu, r), "a header carrying sid: still parses");
    check(r.lat == 92 && r.lon == 4, "the record's own coordinate is unaffected");
    check(r.created == 0 && r.updated == 0, "and so are its other fields");

    uint32_t s = 0;
    check(ttdbHeaderSid(neu, s) && s == 0xa1b2c3d4u, "the header sid is read");

    TtdbEdge e[4];
    const uint8_t n = ttdbParseEdges(neu, e, 4);
    check(n == 2, "both edges parse");
    // ⚠ The coordinate must not absorb the suffix. `LON18#0badc0de` -> 18.
    check(e[0].target_lat == 97 && e[0].target_lon == 18,
          "the target coordinate stops at the '#'");
    check(e[0].has_target_sid && e[0].target_sid == 0x0badc0deu, "the citation sid is read");
    check(!e[1].has_target_sid, "the bare edge beside it stays sid-less");
  }

  // ---- 3. a sid never leaks across the comma into the next edge -------------------------
  // Same family as `prev_stream:` inside `stream:`: a needle that matches beyond its token.
  {
    const char* mixed = "@LAT0LON0 | relates:a@LAT1LON1,b@LAT2LON2#11223344,c@LAT3LON3";
    TtdbEdge e[4];
    const uint8_t n = ttdbParseEdges(mixed, e, 4);
    check(n == 3, "three edges");
    check(!e[0].has_target_sid, "the edge BEFORE the sid-bearing one has none");
    check(e[1].has_target_sid && e[1].target_sid == 0x11223344u, "the middle one has it");
    check(!e[2].has_target_sid, "the edge AFTER it has none");
    check(e[2].target_lat == 3 && e[2].target_lon == 3, "and parses normally");
  }

  // ---- 4. malformed sids are refused, never guessed -------------------------------------
  {
    TtdbEdge e[2];
    ttdbParseEdges("@LAT0LON0 | relates:a@LAT1LON1#0BADC0DE", e, 2);
    check(!e[0].has_target_sid, "UPPERCASE hex is refused, not normalised");
    ttdbParseEdges("@LAT0LON0 | relates:a@LAT1LON1#0badc0d", e, 2);
    check(!e[0].has_target_sid, "a 7-digit sid is refused");
    ttdbParseEdges("@LAT0LON0 | relates:a@LAT1LON1#", e, 2);
    check(!e[0].has_target_sid, "a bare '#' is refused");
    check(e[0].target_lat == 1 && e[0].target_lon == 1,
          "and a refused sid never damages the coordinate");
  }

  // ---- 5. the capability: freshness from the file alone ---------------------------------
  {
    TtdbEdge e[2];
    ttdbParseEdges("@LAT0LON0 | relates:derived_from@LAT97LON1#a1b2c3d4", e, 2);

    const char* same = "@LAT97LON1 | sid:a1b2c3d4 | created:0";
    const char* other = "@LAT97LON1 | sid:99887766 | created:0";   // slot reclaimed
    const char* none = "@LAT97LON1 | created:0";                   // pre-adoption record

    check(ttdbResolveCitation(e[0], same) == TTDB_CITATION_FRESH,
          "matching sid = FRESH, with no boundary record consulted");
    check(ttdbResolveCitation(e[0], other) == TTDB_CITATION_STALE,
          "a reclaimed slot = STALE, detected per citation");
    check(ttdbResolveCitation(e[0], none) == TTDB_CITATION_UNVERIFIABLE,
          "a target with no sid is UNVERIFIABLE, never stale");

    // ⚠ And the direction that matters most for the corpus: a pre-adoption CITATION must
    // never read as stale, or every archived record reports as broken on adoption day.
    TtdbEdge bare[2];
    ttdbParseEdges("@LAT0LON0 | relates:derived_from@LAT97LON1", bare, 2);
    check(ttdbResolveCitation(bare[0], same) == TTDB_CITATION_UNVERIFIABLE,
          "a sid-less citation is UNVERIFIABLE even against a sid-bearing target");
    check(ttdbResolveCitation(bare[0], none) == TTDB_CITATION_UNVERIFIABLE,
          "and against a sid-less one");
  }

  // ---- 6. the header sid is bounded to the header line -----------------------------------
  {
    // A @LAT100 boundary quoting a pruned record's id is the real case.
    const char* rec = "@LAT100LON4 | created:0\n\n**LANE-PRUNED** carried sid:deadbeef\n";
    uint32_t s = 0xffffffffu;
    check(!ttdbHeaderSid(rec, s), "a body's `sid:` is NOT the record's identity");
    check(s == 0xffffffffu, "and the output is untouched");

    const char* both = "@LAT100LON4 | sid:0000000f | created:0\n\n**X** sid:deadbeef\n";
    check(ttdbHeaderSid(both, s) && s == 0x0000000fu, "the header's own sid wins");
  }

  printf("%s  (%d checks, %d failures)\n", gFails ? "FAILED" : "OK", gChecks, gFails);
  return gFails ? 1 : 0;
}
