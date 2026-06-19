// test_toot.cpp — native (off-device) tests for the portable parts of the
// firmware: SHA-256, HMAC, the toot codec, and dedup. Build with `make` in
// this directory (needs g++). These do NOT touch Arduino/LittleFS.
//
// The KAT digests below are emitted by Python's hashlib/hmac, so passing them
// proves the firmware authenticates byte-for-byte with orchestrator/companion.py.
#include <cstdio>
#include <cstring>
#include <cstdint>

#include "Toot.h"
#include "TootCrypto.h"
#include "TtdbParse.h"

static int g_fail = 0;
#define CHECK(cond, msg)                                   \
  do {                                                     \
    if (!(cond)) { printf("FAIL: %s\n", msg); ++g_fail; }  \
    else { printf("pass: %s\n", msg); }                    \
  } while (0)

static void to_hex(const uint8_t* b, size_t n, char* out) {
  for (size_t i = 0; i < n; ++i) sprintf(out + 2 * i, "%02x", b[i]);
}

int main() {
  const uint8_t key[16] = {0x72, 0x6f, 0x62, 0x6f, 0x74, 0x5f, 0x74, 0x65,
                           0x61, 0x6d, 0x5f, 0x6b, 0x65, 0x79, 0x30, 0x31};

  // 1) SHA-256("abc") known answer.
  uint8_t h[32];
  char hex[65];
  toot::sha256((const uint8_t*)"abc", 3, h);
  to_hex(h, 32, hex);
  CHECK(strcmp(hex,
               "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad")
            == 0,
        "SHA-256(abc) matches Python hashlib");

  // 2) HMAC-SHA256 RFC 4231 case 2 (also matches Python hmac).
  uint8_t mac[32];
  toot::hmac_sha256((const uint8_t*)"Jefe", 4,
                    (const uint8_t*)"what do ya want for nothing?", 28, mac);
  to_hex(mac, 32, hex);
  CHECK(strcmp(hex,
               "5bdcc146bf60754e6a042426089575c75a003f089d2739839dec58b964ec3843")
            == 0,
        "HMAC-SHA256(Jefe,...) matches Python hmac");

  // 3) Toot encode/decode round trip.
  toot::Toot t;
  t.type = toot::TTDB_DATA;
  t.src_node_id = 0x100;
  t.toot_seq = 7;
  for (int i = 0; i < 50; ++i) t.payload[i] = (uint8_t)i;
  t.payload_len = 50;
  uint8_t frame[toot::MAX_FRAME];
  size_t flen = toot::encode(t, key, 16, frame, sizeof(frame));
  CHECK(flen == toot::HEADER_LEN + 50 + toot::HMAC_LEN, "encode length");

  toot::Toot t2;
  CHECK(toot::decode(frame, flen, key, 16, t2), "decode verifies HMAC");
  CHECK(t2.type == toot::TTDB_DATA && t2.src_node_id == 0x100 &&
            t2.toot_seq == 7 && t2.payload_len == 50 &&
            memcmp(t2.payload, t.payload, 50) == 0,
        "decoded fields round-trip");

  // 4) Tamper detection: flip a payload byte -> HMAC fails.
  frame[40] ^= 0xFF;
  CHECK(!toot::decode(frame, flen, key, 16, t2), "tampered frame rejected");

  // 5) Dedup.
  toot::DedupSet dd(8);
  CHECK(!dd.seen(1, 1), "first (1,1) is new");
  CHECK(dd.seen(1, 1), "second (1,1) is a dupe");
  CHECK(!dd.seen(1, 2), "(1,2) is new");

  // 6) TTDB header parsing (matches data/ttdb.md and the Python reference).
  TtdbRecord hr;
  const char* warm =
      "@LAT10LON0 | created:1750000000 | updated:1750000001 | "
      "relates:triggers@LAT10LON0,logs@LAT0LON0";
  CHECK(ttdbParseHeader(warm, hr) && hr.lat == 10 && hr.lon == 0 &&
            hr.created == 1750000000u && hr.updated == 1750000001u,
        "parse record header");
  TtdbRecord neg;
  CHECK(ttdbParseHeader("@LAT-5LON-3 | created:1 | updated:2 | "
                        "relates:navigates_to@LAT0LON0",
                        neg) &&
            neg.lat == -5 && neg.lon == -3,
        "parse negative coordinates");

  // 7) Typed-edge parsing.
  TtdbEdge edges[8];
  uint8_t ne = ttdbParseEdges(warm, edges, 8);
  CHECK(ne == 2 && strcmp(edges[0].type, "triggers") == 0 &&
            edges[0].target_lat == 10 && edges[0].target_lon == 0 &&
            strcmp(edges[1].type, "logs") == 0 && edges[1].target_lat == 0 &&
            edges[1].target_lon == 0,
        "parse triggers + logs edges");

  // 8) Nearest-record search (the core of Agent32 reason()).
  TtdbRecord recs[3];
  recs[0].lat = 0;  recs[0].lon = 0;
  recs[1].lat = 10; recs[1].lon = 0;
  recs[2].lat = 0;  recs[2].lon = 30;
  CHECK(ttdbNearest(recs, 3, 9, 1) == 1, "nearest picks the warm record");
  CHECK(ttdbNearest(recs, 0, 0, 0) == -1, "nearest of empty index is -1");

  printf(g_fail ? "\n%d FAILED\n" : "\nALL PASSED\n", g_fail);
  return g_fail ? 1 : 0;
}
