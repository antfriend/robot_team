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

  // 5b) ACK helpers (TTN-RFC-0007). Build an ACK for a want_ack toot, encode +
  // verify it on the wire, and check the sender's outstanding-table match.
  toot::Toot orig;                       // the toot being acknowledged
  orig.type = toot::CMD;
  orig.src_node_id = 0x00000001;         // orchestrator
  orig.toot_seq = 0x12345678;
  orig.chunk_idx = 0;
  orig.flags = toot::FLAG_WANT_ACK;

  toot::Toot ack;
  toot::makeAck(orig, /*acker_id=*/0x00000100, /*acker_seq=*/42,
                toot::ACK_ACCEPTED, ack);
  CHECK(ack.type == toot::ACK && ack.src_node_id == 0x100 &&
            ack.toot_seq == 42 && ack.payload_len == toot::ACK_PAYLOAD_LEN,
        "makeAck sets ACK header");

  uint8_t aframe[toot::MAX_FRAME];
  size_t alen = toot::encode(ack, key, 16, aframe, sizeof(aframe));
  toot::Toot ack2;
  CHECK(toot::decode(aframe, alen, key, 16, ack2), "ACK frame verifies HMAC");

  uint32_t as, aq; uint8_t ac, ast;
  CHECK(toot::parseAck(ack2, as, aq, ac, ast) && as == 0x00000001 &&
            aq == 0x12345678 && ac == 0 && ast == toot::ACK_ACCEPTED,
        "parseAck round-trips (ack_src,ack_seq,ack_chunk,status)");

  // The sender matches on (its own id, seq, chunk); mismatches must fail.
  CHECK(toot::ackMatches(ack2, 0x00000001, 0x12345678, 0), "ackMatches hit");
  CHECK(!toot::ackMatches(ack2, 0x00000001, 0x12345679, 0), "wrong seq misses");
  CHECK(!toot::ackMatches(ack2, 0x00000002, 0x12345678, 0), "wrong src misses");
  CHECK(!toot::ackMatches(ack2, 0x00000001, 0x12345678, 1), "wrong chunk misses");
  // A non-ACK toot is never a match.
  CHECK(!toot::ackMatches(orig, 0x00000001, 0x12345678, 0), "non-ACK never matches");

  // 5c) Chunk reassembly (TTN-RFC-0007 §6): a 500 B logical toot across 3 chunks.
  uint8_t orig500[500];
  for (int i = 0; i < 500; ++i) orig500[i] = (uint8_t)((i * 7 + 1) & 0xff);
  auto mkChunk = [&](uint8_t cidx, uint8_t ctot, const uint8_t* p, uint16_t n) {
    toot::Toot c;
    c.type = toot::BELIEF;
    c.src_node_id = 0x100;
    c.toot_seq = 99;
    c.chunk_idx = cidx;
    c.chunk_total = ctot;
    c.flags = toot::FLAG_WANT_ACK;
    memcpy(c.payload, p, n);
    c.payload_len = (uint8_t)n;
    return c;
  };
  toot::Reassembler ra;
  toot::Toot k0 = mkChunk(0, 3, orig500 + 0, 208);
  toot::Toot k1 = mkChunk(1, 3, orig500 + 208, 208);
  toot::Toot k2 = mkChunk(2, 3, orig500 + 416, 84);
  // Out-of-order delivery still reassembles.
  CHECK(ra.offer(k0, 1000) == toot::Reassembler::NEED_MORE, "chunk0 -> need more");
  CHECK(ra.offer(k2, 1001) == toot::Reassembler::NEED_MORE,
        "chunk2 out-of-order -> need more");
  CHECK(ra.offer(k1, 1002) == toot::Reassembler::COMPLETE, "chunk1 completes set");
  CHECK(ra.bodyLen() == 500 && memcmp(ra.body(), orig500, 500) == 0,
        "reassembled body is byte-exact");
  // A duplicate after completion is recognized (re-ACK ACCEPTED, no re-buffer).
  CHECK(ra.offer(k1, 1003) == toot::Reassembler::COMPLETED_DUP,
        "post-complete duplicate recognized");

  // Duplicate within an open set, and a malformed idx>=total.
  toot::Reassembler rb;
  toot::Toot d0 = mkChunk(0, 2, orig500, 208);
  CHECK(rb.offer(d0, 1) == toot::Reassembler::NEED_MORE, "new set chunk0");
  CHECK(rb.offer(d0, 2) == toot::Reassembler::DUPLICATE, "open-set duplicate");
  toot::Toot dbad = mkChunk(3, 3, orig500, 10);
  CHECK(rb.offer(dbad, 3) == toot::Reassembler::BAD, "idx>=total rejected");

  // 5d) Time-sync payloads (TTN-RFC-0008). u64 epoch must survive the wire.
  const uint64_t kEpoch = 1750000000123ULL;   // ms, > 32 bits
  toot::Toot ts;
  ts.type = toot::TIME_SYNC;
  toot::put_u32(ts.payload + 0, 0xABCD1234);
  toot::put_u64(ts.payload + 4, kEpoch);
  ts.payload_len = toot::TIME_SYNC_PAYLOAD_LEN;
  uint32_t sid; uint64_t ems;
  CHECK(toot::parseTimeSync(ts, sid, ems) && sid == 0xABCD1234 && ems == kEpoch,
        "TIME_SYNC payload round-trips (u32 id + u64 epoch_ms)");

  toot::Toot tr;
  tr.type = toot::TIME_REQ;
  toot::put_u32(tr.payload + 0, 7);
  toot::put_u32(tr.payload + 4, 0x00000100);
  tr.payload_len = toot::TIME_REQ_PAYLOAD_LEN;
  uint32_t pid, tgt;
  CHECK(toot::parseTimeReq(tr, pid, tgt) && pid == 7 && tgt == 0x100,
        "TIME_REQ payload round-trips (probe_id + target)");
  // Wrong-type guard: a TIME_REQ is not parseable as a TIME_SYNC.
  CHECK(!toot::parseTimeSync(tr, sid, ems), "parseTimeSync rejects a TIME_REQ");

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
