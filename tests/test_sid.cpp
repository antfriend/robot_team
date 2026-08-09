// test_sid.cpp — stable record identity (TTDB-RFC-0010 §4, decided 2026-08-09).
//
// What is worth pinning, as opposed to what is easy to pin:
//   * FNV-1a matches the published vectors, so `companion.py` and a node compute the SAME
//     preimage — the property that lets a reader verify a node's ids at all
//   * the two identity kinds behave OPPOSITELY where it matters: an EVENT sid changes when
//     the body changes; a KEY sid does NOT, because a belief is revised and a trace is
//     reinforced while its identity must not move (RFC-0004 §4)
//   * `stampEvent` patches only the HEADER's sid, never a `sid:` occurring in a body — the
//     needle-collision family that has now cost this project four separate bugs
//   * the digest covers the body only, so the ordinal (header-only) cannot enter the id
//   * a stamped record VERIFIES, and any single-byte edit to its body makes it fail
//   * parse refuses uppercase and short input rather than normalising
#include <cstdio>
#include <cstring>
#include "Sid.h"

static int gChecks = 0, gFails = 0;
static void check(bool ok, const char* what) {
  ++gChecks;
  if (!ok) { ++gFails; printf("  FAIL: %s\n", what); }
}

using namespace sid;

int main() {
  printf("Sid tests\n");

  // ---- 1. FNV-1a against the published vectors ---------------------------------------
  // ⚠ These are the canonical FNV-1a 32-bit test vectors. If they ever fail, the node and
  // the laptop have stopped agreeing on what a record is called, which is silent and total.
  check(fnv1a("", 0) == 0x811c9dc5u, "FNV-1a(\"\") = offset basis");
  check(fnv1a("a", 1) == 0xe40c292cu, "FNV-1a(\"a\")");
  check(fnv1a("foobar", 6) == 0xbf9cf968u, "FNV-1a(\"foobar\")");
  {
    // Streaming must equal one-shot, or `forKey`'s unbounded key streaming is wrong.
    uint32_t h = fnv1aInit();
    const char* s = "foobar";
    for (const char* p = s; *p; ++p) h = fnv1aByte(h, (uint8_t)*p);
    check(h == fnv1a(s, 6), "streamed FNV-1a equals one-shot");
  }

  // ---- 1b. CROSS-LANGUAGE VECTORS ------------------------------------------------------
  // ⚠ These same eight values are computed by `scripts/sid_probe.py --vectors`. They exist
  // because the entire value of a stable id is that a reader holding only the file can
  // RECOMPUTE it — so a node and the laptop must agree byte for byte on the preimage, and
  // nothing else in the system would notice if they stopped. A divergence here is silent
  // and total: every citation would resolve `stale` against a perfectly good record.
  {
    check(forEvent(0x300, 95, 0xe334a7e1u, 3710811,
                   bodyDigest("**MOTIONWIN** state:still\n", 26)) == 0x24a930c2u,
          "vector event/basic matches sid_probe.py");
    check(forEvent(0, 0, 0, 0, 0) == 0x74526815u, "vector event/zero matches sid_probe.py");
    check(forEvent(0x300, 96, 0, 60000, bodyDigest("entities:5 rssi:-31", 19)) == 0x05989c91u,
          "vector event/nostream matches sid_probe.py");
    check(forKey(0x300, 91, "peer:0x00000200|proto:espnow") == 0x8a93826du,
          "vector key/link-stable matches sid_probe.py");
    check(forKey(0x300, 91, "") == 0x0177c5f9u, "vector key/empty matches sid_probe.py");
  }

  // ---- 2. format / parse round-trip, and the refusals ---------------------------------
  {
    char out[9];
    format(out, 0x0a1b2c3du);
    check(strcmp(out, "0a1b2c3d") == 0, "format is 8 lowercase hex, zero-padded");
    format(out, 0);
    check(strcmp(out, "00000000") == 0, "zero formats as the placeholder");

    uint32_t v = 0xdeadbeefu;
    check(parse("0a1b2c3d", 8, v) && v == 0x0a1b2c3du, "parse round-trips");
    v = 0xdeadbeefu;
    check(!parse("0A1B2C3D", 8, v), "uppercase is REFUSED, not normalised");
    check(v == 0xdeadbeefu, "a refused parse leaves the output untouched");
    check(!parse("0a1b2c3", 7, v), "a short sid is refused");
    check(!parse("0a1b2c3g", 8, v), "a non-hex digit is refused");
    check(!parse(nullptr, 8, v), "null is refused");
  }

  // ---- 3. EVENT identity: the body is IN ----------------------------------------------
  // This is what took the archived percept lanes from 4-10% input collisions to zero.
  {
    const uint32_t NODE = 0x300, STREAM = 0xe334a7e1u;
    const uint64_t T = 3710811;
    const uint32_t a = forEvent(NODE, 95, STREAM, T, bodyDigest("state:still", 11));
    const uint32_t b = forEvent(NODE, 95, STREAM, T, bodyDigest("state:moving", 12));
    check(a != b, "same node/lane/stream/time + different body = different sid");
    check(a == forEvent(NODE, 95, STREAM, T, bodyDigest("state:still", 11)),
          "EVENT sid is deterministic");
    check(a != forEvent(NODE, 96, STREAM, T, bodyDigest("state:still", 11)),
          "the lane is part of the identity");
    check(a != forEvent(0x200, 95, STREAM, T, bodyDigest("state:still", 11)),
          "the node is part of the identity");
    check(a != forEvent(NODE, 95, 0, T, bodyDigest("state:still", 11)),
          "the stream is part of the identity");
    check(a != forEvent(NODE, 95, STREAM, T + 1, bodyDigest("state:still", 11)),
          "the timestamp is part of the identity");

    // ⚠ THE MEASURED CASE. Two windows on a node with no stream, whose local millis()
    // restarted at a reboot: identical lane, identical `stream:0x00000000`, identical
    // t_ms:60000. Under the RFC's original input these were ONE name for two records —
    // 344 of the archive's 538 input collisions are exactly this shape.
    const uint32_t w1 = forEvent(NODE, 96, 0, 60000, bodyDigest("entities:5 rssi:-31", 19));
    const uint32_t w2 = forEvent(NODE, 96, 0, 60000, bodyDigest("entities:5 rssi:-75", 19));
    check(w1 != w2, "two boot-restarted windows are distinguished by their bodies");
  }

  // ---- 4. KEY identity: the body and the time are OUT ---------------------------------
  // The opposite rule, and it must be opposite. An @LAT91 belief is REVISED as Rule 3 folds
  // outcomes; a FIELD trace is REINFORCED. If either changed its sid, every citation to it
  // would dangle on the next fold — RFC-0004 §4 forbids exactly that.
  {
    const uint32_t NODE = 0x300;
    const uint32_t k1 = forKey(NODE, 91, "peer:0x00000200|proto:espnow");
    const uint32_t k2 = forKey(NODE, 91, "peer:0x00000200|proto:espnow");
    check(k1 == k2, "KEY sid is deterministic");
    check(k1 != forKey(NODE, 91, "peer:0x00000200|proto:ble"),
          "a different proto is a different subject");
    check(k1 != forKey(NODE, 91, "peer:0x00000010|proto:espnow"),
          "a different peer is a different subject");
    check(k1 != forKey(0x200, 91, "peer:0x00000200|proto:espnow"),
          "the observing node is part of the identity");
    check(forKey(NODE, 91, "") != forKey(NODE, 92, ""), "the lane separates empty keys");
    check(forKey(NODE, 91, nullptr) == forKey(NODE, 91, ""),
          "a null key behaves as an empty one rather than crashing");

    // The whole point, stated as a test: a long natural key must not be truncated into
    // another subject's identity.
    const char* long_a = "peer:0x00000200|proto:espnow|note:aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa1";
    const char* long_b = "peer:0x00000200|proto:espnow|note:aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa2";
    check(forKey(NODE, 91, long_a) != forKey(NODE, 91, long_b),
          "a long key is streamed whole, never truncated into a collision");
  }

  // ---- 5. stampEvent patches the HEADER, and only the header --------------------------
  {
    // ⚠ The body deliberately contains the text `sid:` — a @LAT100 boundary quoting a
    // pruned record's id is the real case. Patching that instead is the same needle
    // collision as `prev_stream:` inside `stream:` and `**COVERED-SPAN**` inside
    // `**COVERED**`; this is the fourth member of that family and it is tested for.
    char rec[256];
    const char* tmpl =
        "\n---\n\n@LAT95LON3 | sid:00000000 | created:0 | updated:0\n\n"
        "**MOTIONWIN** t_ms:3710811 carried sid:deadbeef forward\n";
    memcpy(rec, tmpl, strlen(tmpl) + 1);
    const size_t n = strlen(rec);

    const uint32_t s = stampEvent(rec, n, 0x300, 95, 0xe334a7e1u, 3710811);
    check(s != 0, "stampEvent found the placeholder and wrote an id");
    check(strstr(rec, "sid:deadbeef") != nullptr,
          "the body's `sid:` occurrence is UNTOUCHED");
    char hex[9];
    format(hex, s);
    check(strncmp(strstr(rec, "@LAT95LON3 | sid:") + 17, hex, 8) == 0,
          "the header now carries the computed id");
    check(strstr(rec, "sid:00000000") == nullptr, "the placeholder is gone");

    // Verification: the property a reader holding only the file gets.
    uint32_t found = 0, computed = 0;
    check(verifyEvent(rec, n, 0x300, 95, 0xe334a7e1u, 3710811, &found, &computed),
          "a stamped record verifies");
    check(found == computed && found == s, "and reports the same id both ways");

    // A single byte changed in the body must break it. This is the whole integrity claim.
    char* p = strstr(rec, "3710811");
    p[6] = '2';
    check(!verifyEvent(rec, n, 0x300, 95, 0xe334a7e1u, 3710811, &found, &computed),
          "one edited body byte fails verification");
    check(found != computed, "and the mismatch is visible to the reader");
  }

  // ---- 6. the ordinal cannot enter the identity ---------------------------------------
  // RFC-0010 §4.2 requires this explicitly: naming a record by where it sits is the defect
  // the whole mechanism replaces. Two records identical but for their LON must share a sid.
  {
    char a[160], b[160];
    const char* ta = "@LAT95LON3 | sid:00000000 | created:0\n\n**MOTIONWIN** state:still\n";
    const char* tb = "@LAT95LON7 | sid:00000000 | created:0\n\n**MOTIONWIN** state:still\n";
    memcpy(a, ta, strlen(ta) + 1);
    memcpy(b, tb, strlen(tb) + 1);
    const uint32_t sa = stampEvent(a, strlen(a), 0x300, 95, 1, 1000);
    const uint32_t sb = stampEvent(b, strlen(b), 0x300, 95, 1, 1000);
    check(sa == sb && sa != 0, "the ordinal is NOT part of the id (LON3 == LON7)");
  }

  // ---- 7. a record is never half-stamped ----------------------------------------------
  {
    char no_field[80];
    const char* t1 = "@LAT95LON3 | created:0\n\n**MOTIONWIN** state:still\n";
    memcpy(no_field, t1, strlen(t1) + 1);
    check(stampEvent(no_field, strlen(no_field), 0x300, 95, 1, 1) == 0,
          "no placeholder = no stamp");
    check(strcmp(no_field, t1) == 0, "and the record is untouched");

    // A truncated placeholder in the header must be refused, not partially overwritten.
    char trunc[80];
    const char* t2 = "@LAT95LON3 | sid:00\n\n**MOTIONWIN** x\n";
    memcpy(trunc, t2, strlen(t2) + 1);
    check(stampEvent(trunc, strlen(trunc), 0x300, 95, 1, 1) == 0,
          "a truncated placeholder is refused");
    check(strcmp(trunc, t2) == 0, "and that record is untouched too");

    char headerless[64];
    const char* t3 = "**MOTIONWIN** sid:00000000 state:still\n";
    memcpy(headerless, t3, strlen(t3) + 1);
    check(stampEvent(headerless, strlen(headerless), 0x300, 95, 1, 1) == 0,
          "a body-only buffer is refused: its `sid:` is not a header field");
    check(strcmp(headerless, t3) == 0, "and it is untouched");
  }

  // ---- 8. stampKey ignores the body, by construction -----------------------------------
  {
    char a[160], b[160];
    const char* ta = "@LAT91LON0 | sid:00000000 |\n\n**LINK-STABLE** conf:120 streak:3\n";
    const char* tb = "@LAT91LON0 | sid:00000000 |\n\n**LINK-STABLE** conf:198 streak:41\n";
    memcpy(a, ta, strlen(ta) + 1);
    memcpy(b, tb, strlen(tb) + 1);
    const char* key = "peer:0x00000200|proto:espnow";
    const uint32_t sa = stampKey(a, strlen(a), 0x300, 91, key);
    const uint32_t sb = stampKey(b, strlen(b), 0x300, 91, key);
    check(sa == sb && sa != 0,
          "a belief keeps its id across a revision (RFC-0004 section 4)");
  }

  printf("%s  (%d checks, %d failures)\n", gFails ? "FAILED" : "OK", gChecks, gFails);
  return gFails ? 1 : 0;
}
