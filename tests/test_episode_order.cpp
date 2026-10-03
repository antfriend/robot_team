// test_episode_order.cpp — docs/design/episode-order.md §9, native items 1–7 (item 8, the
// seq-0 guard in order(), lives in test_fleettime.cpp beside the rest of order()).
//
//   1. seq is DENSE (a refused append re-uses its number) and boot recovers it from a lane
//      spanning all four tiers, in any record order
//   2. merge = element-wise max; seq 0 is not knowledge; a peer's higher view of US jumps
//      our seq and counts a regression; a full table under-claims
//   3. transitivity: C learns of A through B alone
//   4. render <-> parse round trip; the order lines change NOTHING the consolidator reads;
//      a malformed block refuses the episode
//   5. buffers pinned both ways (block, link episode, worst entity scratch)
//   6. order() over episodes RENDERED AND RE-PARSED from two stores: RFC-0004 §4.8 1–3
//   7. the recv side only copies: the clock does not move until drainInto()
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

#include "Episode.h"
#include "EpisodeOrder.h"
#include "FleetTime.h"
#include "Semantic.h"

using namespace semantic;

static int gChecks = 0, gFails = 0;
static void check(bool ok, const char* what) {
  ++gChecks;
  if (!ok) { ++gFails; printf("  FAIL: %s\n", what); }
}

template <class R>
static void feedText(R& r, const std::string& s) {
  size_t i = 0;
  while (i <= s.size()) {
    size_t j = s.find('\n', i);
    if (j == std::string::npos) j = s.size();
    r.line(s.substr(i, j - i).c_str());
    i = j + 1;
  }
}

static std::string block(const VectorClock& vc) {
  char b[EPISODEORDER_BLOCK_MAX];
  size_t n = vc.renderBlock(b, sizeof(b));
  return std::string(b, n);
}

// ---------------------------------------------------------------------------------------
static void testDense() {
  printf("1. seq is dense, and recovered at boot\n");
  VectorClock vc;
  vc.begin(0x300);
  check(vc.seq() == 0 && vc.nextSeq() == 1, "a fresh node's first episode is seq 1");
  // render with nextSeq, the append is REFUSED: nothing committed
  check(block(vc) == "seq: 1\n", "the first block names seq 1 and no follows (none known)");
  check(vc.nextSeq() == 1, "a refused append spends no number");
  vc.committed(1);
  check(vc.nextSeq() == 2, "a successful append advances seq by exactly one");
  vc.committed(1);
  check(vc.seq() == 1, "committing the same seq twice is idempotent");

  // A lane spanning four tiers, records NOT in seq order (the tiers' bands interleave in
  // file order), with pre-C4 episodes (no seq line) mixed in.
  const char* lane =
      "@LAT103LON40 | created:1 | updated:1\n\n**link window**\n\n```ttdb-episode\n"
      "source: linkpercept\nat: 100 ±0 frame:5000\nseq: 7\n"
      "follows: 0x00000010:3 0x00000200:9\nsaid: 1 | **LINKWIN** t_ms:1\n```\n"
      "@LAT103LON8195 | created:2 | updated:2\n\n**entity window**\n\n```ttdb-episode\n"
      "source: entitypercept\nat: 200 ±0 frame:5000\nseq: 12\n"
      "follows: 0x00000010:5 0x00000012:1 0x00000200:11\nsaid: 1 | **ENTWIN** t_ms:2\n```\n"
      "@LAT103LON16390 | created:3 | updated:3\n\n**motion window**\n\n```ttdb-episode\n"
      "source: motionpercept\nat: 150 ±0 frame:5000\nseq: 9\n"
      "follows: 0x00000010:4\nsaid: 1 | **MOTIONWIN** t_ms:3\n```\n"
      "@LAT103LON24580 | created:4 | updated:4\n\n**acoustic window**\n\n```ttdb-episode\n"
      "source: acousticpercept\nat: t_ms:9 stream:0x1 wall:0\nsaid: 1 | **ACOUSTICWIN**\n```\n"
      "@LAT104LON3 | created:5 | updated:5\n\n```ttdb-carried\nthrough: 30\n```\n";
  OrderRecovery rec;
  feedText(rec, lane);
  check(rec.seq() == 12, "boot recovery takes the HIGHEST seq on the lane, not the last record");
  Follows f[EPISODEORDER_OTHERS];
  uint8_t nf = rec.follows(f, EPISODEORDER_OTHERS);
  check(nf == 3 && f[0].agent == 0x10 && f[0].seq == 5 && f[1].agent == 0x12 &&
            f[2].agent == 0x200 && f[2].seq == 11,
        "...and the follows of THAT episode, not of a later record in the file");
  VectorClock b;
  b.begin(0x300);
  rec.applyTo(b);
  check(b.nextSeq() == 13 && b.regressions() == 0,
        "restore resumes at max+1 and is not counted as a regression (it is our own flash)");
  check(block(b) == "seq: 13\nfollows: 0x00000010:5 0x00000012:1 0x00000200:11\n",
        "...and the recovered vector is written into the next episode");

  OrderRecovery none;
  feedText(none, "@LAT103LON1 | created:0 | updated:0\n\n```ttdb-episode\nsource: x\n"
                 "at: 5\nseq: 0\nfollows: 0x00000010:3\nsaid: 1 | y\n```\n");
  check(none.seq() == 0, "`seq: 0` is not a sequence number (pre-C4 = unsequenced)");
  OrderRecovery bad;
  feedText(bad, "@LAT103LON1 | x\nseq: 4\nfollows: 0x00000010:3 0xzz:1\n");
  check(bad.seq() == 4 && bad.follows(f, 7) == 0,
        "a malformed follows line is not trusted at all (under-claim, never a guess)");
}

// ---------------------------------------------------------------------------------------
static void testMerge() {
  printf("2. merge\n");
  VectorClock vc;
  vc.begin(0x300);
  check(vc.mergeEntry(0x200, 5) && vc.mergeEntry(0x10, 2), "new agents are learned");
  check(!vc.mergeEntry(0x200, 4), "a LOWER entry changes nothing (max, never overwrite)");
  check(vc.mergeEntry(0x200, 6), "a higher entry raises it");
  check(!vc.mergeEntry(0x12, 0), "seq 0 is not knowledge: never added");
  check(block(vc) == "seq: 1\nfollows: 0x00000010:2 0x00000200:6\n",
        "follows is sorted by agent, whatever the arrival order");

  vc.committed(3);
  check(!vc.mergeEntry(0x300, 3) && vc.regressions() == 0,
        "a peer echoing our own current seq is not a regression");
  check(vc.mergeEntry(0x300, 40) && vc.nextSeq() == 41 && vc.regressions() == 1,
        "a peer remembering MORE of us than our flash: jump past it, count it");
  check(!vc.mergeEntry(0x300, 7) && vc.nextSeq() == 41, "...and our seq never moves back");

  VectorClock full;
  full.begin(1);
  for (uint32_t a = 2; a < 2 + EPISODEORDER_OTHERS; ++a) full.mergeEntry(a, 1);
  check(full.others() == EPISODEORDER_OTHERS, "the table holds OTHERS agents");
  check(!full.mergeEntry(999, 1) && full.overflow() == 1 && full.others() == EPISODEORDER_OTHERS,
        "a full table drops the newcomer and counts it (an under-claim, never a wrong order)");
  check(full.mergeEntry(2, 5), "...while known agents still advance");
}

// ---------------------------------------------------------------------------------------
static void testTransitive() {
  printf("3. transitivity\n");
  VectorClock a, b, c;
  a.begin(0x10); b.begin(0x200); c.begin(0x300);
  a.committed(4);
  uint8_t w[EPISODEORDER_VECTOR_MAX];
  size_t n = a.encode(w, sizeof(w));
  check(n == 2 + 8 && w[0] == EPISODEORDER_SUBOP_VECTOR && w[1] == 1,
        "A's vector carries only its own entry");
  check(b.mergeWire(w, n), "B merges A");
  b.committed(2);
  n = b.encode(w, sizeof(w));
  check(n == 2 + 16, "B's vector carries itself and A");
  check(c.mergeWire(w, n), "C merges B — never having heard A");
  Follows f[EPISODEORDER_OTHERS];
  uint8_t k = c.follows(f, EPISODEORDER_OTHERS);
  check(k == 2 && f[0].agent == 0x10 && f[0].seq == 4 && f[1].agent == 0x200 && f[1].seq == 2,
        "C knows A:4 through B alone — the vector is transitive");

  check(!c.mergeWire(w, 5) && c.malformed() == 1, "a short payload is refused, nothing merged");
  uint8_t bad[2] = {EPISODEORDER_SUBOP_WANT, 0};
  check(!c.mergeWire(bad, 2), "another sub-op is not a vector");
  uint8_t many[2] = {EPISODEORDER_SUBOP_VECTOR, FLEETTIME_MAX_AGENTS + 1};
  check(!c.mergeWire(many, 2), "n beyond FLEETTIME_MAX_AGENTS is refused");
  check(a.encode(w, 9) == 0, "encode refuses a short buffer rather than truncating");

  // sendDue: change-triggered with a heartbeat
  VectorClock s;
  s.begin(0x10);
  check(!s.sendDue(0), "nothing known, nothing to say");
  s.committed(1);
  check(s.sendDue(0), "first knowledge: send");
  s.sent(1000);
  check(!s.sendDue(1500), "unchanged, before the heartbeat: quiet");
  s.mergeEntry(0x200, 3);
  check(!s.sendDue(1500), "changed, but inside MIN_GAP: wait");
  check(s.sendDue(2000), "changed and MIN_GAP passed: send");
  s.sent(2000);
  check(s.sendDue(2000 + EPISODEORDER_HEARTBEAT_MS), "unchanged: the heartbeat still sends");
}

// ---------------------------------------------------------------------------------------
static void testRecord() {
  printf("4. in the record\n");
  VectorClock vc;
  vc.begin(0x300);
  vc.committed(1411);
  vc.mergeEntry(0x12, 212); vc.mergeEntry(0x10, 388); vc.mergeEntry(0x200, 77);
  const std::string blk = block(vc);
  check(blk == "seq: 1412\nfollows: 0x00000010:388 0x00000012:212 0x00000200:77\n",
        "the design's example renders exactly");

  LinkClaim k[2] = {{0x200, "ble", LINK_MET, -40, -38}, {0x10, "espnow", LINK_VIOLATED, -50, -71}};
  static char with[SEMANTIC_LINK_EPISODE_BUF], without[SEMANTIC_LINK_EPISODE_BUF];
  const char* at = "4890438 ±0 frame:5000";
  size_t nw = renderLinkEpisode(k, 2, 4, 77, at, with, sizeof(with), blk.c_str());
  size_t no = renderLinkEpisode(k, 2, 4, 77, at, without, sizeof(without));
  std::string sw(with, nw), so(without, no);
  check(nw == no + blk.size(), "the block adds exactly its own bytes");
  check(sw.find("\nat: 4890438 ±0 frame:5000\nseq: 1412\nfollows: ") != std::string::npos,
        "seq and follows sit right after `at:`, inside the fence");

  // Round trip through the line parsers.
  uint32_t s = 0;
  check(parseSeqLine("seq: 1412", &s) && s == 1412, "seq parses");
  check(!parseSeqLine("seq: 14x", &s) && !parseSeqLine("seq:", &s) &&
            !parseSeqLine("seq: 99999999999", &s),
        "a malformed or overflowing seq does not");
  Follows f[EPISODEORDER_OTHERS];
  bool ok = false;
  uint8_t nf = parseFollowsLine("follows: 0x00000010:388 0x00000012:212 0x00000200:77", f, 7, &ok);
  check(ok && nf == 3 && f[1].agent == 0x12 && f[1].seq == 212, "follows parses");

  // The consolidator reads the two forms identically.
  Consolidator c1, c2;
  c1.begin(); c2.begin();
  EpisodeReader r1(c1), r2(c2);
  r1.select(4, 4, Consolidator::KEEPING); r2.select(4, 4, Consolidator::KEEPING);
  feedText(r1, sw); feedText(r2, so);
  r1.finish(); r2.finish();
  bool same = c1.termCount() == c2.termCount() && c1.malformedCount() == 0 &&
              c2.malformedCount() == 0;
  for (size_t i = 0; same && i < c1.termCount(); ++i) {
    char a[128], b[128];
    same = c1.beliefLine(*c1.term(i), a, sizeof(a)) && c2.beliefLine(*c2.term(i), b, sizeof(b)) &&
           strcmp(a, b) == 0;
  }
  check(same && r1.fed() == r2.fed(),
        "the consolidator reads an episode with seq/follows EXACTLY as one without");

  // A block that is not exactly seq/follows lines refuses the episode.
  check(renderLinkEpisode(k, 2, 4, 77, at, with, sizeof(with), "seq: 1\npercept: 9 | x\n") == 0,
        "a block smuggling another line refuses the episode");
  check(renderLinkEpisode(k, 2, 4, 77, at, with, sizeof(with), "seq: 1") == 0,
        "a block not ending in a newline refuses");
  check(renderLinkEpisode(k, 2, 4, 77, at, with, sizeof(with), "seq: 1\n```\n") == 0,
        "a block that could close the fence refuses");
  check(renderLinkEpisode(k, 2, 4, 77, at, with, sizeof(with), "") == no,
        "an EMPTY block is the same as none");

  // The in-place said wrap carries it too, and sizes its header with it.
  static char sc[SEMANTIC_ENTITY_EPISODE_BUF];
  const char* body = "**ENTWIN** t_ms:1 stream:0x1 wall:0 window_ms:600000\n";
  memcpy(sc, body, strlen(body));
  size_t ns = renderSaidEpisodeInPlace(sc, sizeof(sc), strlen(body), 8192, 5, "entity window",
                                       "entitypercept", at, blk.c_str());
  check(ns > 0 && std::string(sc, ns).find("seq: 1412\nfollows:") != std::string::npos,
        "the in-place said wrap writes the block too");
}

// ---------------------------------------------------------------------------------------
static void testBuffers() {
  printf("5. buffers, pinned both ways\n");
  VectorClock vc;
  vc.begin(0xFFFFFFFFu);
  vc.committed(0xFFFFFFFEu);         // nextSeq = 4294967295, the widest seq
  for (uint32_t i = 0; i < EPISODEORDER_OTHERS; ++i) vc.mergeEntry(0xFFFFFFF0u + i, 0xFFFFFFFFu);
  char b[EPISODEORDER_BLOCK_MAX];
  size_t n = vc.renderBlock(b, sizeof(b));
  check(n > 0, "a maximal block fits EPISODEORDER_BLOCK_MAX");
  char tight[EPISODEORDER_BLOCK_MAX];
  check(vc.renderBlock(tight, n) == 0 && tight[0] == '\0',
        "...and does not fit one byte less than it needs (refused, never truncated)");
  printf("    maximal block %u B of %u B\n", (unsigned)n, (unsigned)EPISODEORDER_BLOCK_MAX);
  check(strlen(b) == n, "the maximal block is intact for the episode below");

  LinkClaim w[8];
  for (int i = 0; i < 8; ++i)
    w[i] = LinkClaim{0xFFFFFFF0u + (uint32_t)i, "espnow", LINK_UNOBSERVED, -32768, -32768};
  static char lk[SEMANTIC_LINK_EPISODE_BUF];
  const char* at = "t_ms:18446744073709551615 stream:0xffffffff wall:1";
  size_t wn = renderLinkEpisode(w, 8, 32767, 4294967295u, at, lk, sizeof(lk), b);
  check(wn > 0, "8 maximal claims + a maximal block fit SEMANTIC_LINK_EPISODE_BUF (1408)");
  static char old[1280];
  check(renderLinkEpisode(w, 8, 32767, 4294967295u, at, old, sizeof(old), b) == 0,
        "...and would NOT have fitted the old 1280");
  printf("    worst link episode with a maximal block %u B of %u B\n", (unsigned)wn,
         (unsigned)sizeof(lk));
}

// ---------------------------------------------------------------------------------------
// 6. Two stores, rendered and parsed back, then ordered.
struct Parsed {
  EpisodeRef ref;
};

static EpisodeRef parseEpisode(uint32_t agent, const std::string& rec) {
  EpisodeRef e;
  memset(&e, 0, sizeof(e));
  e.agent = agent;
  size_t i = 0;
  while (i < rec.size()) {
    size_t j = rec.find('\n', i);
    if (j == std::string::npos) j = rec.size();
    std::string l = rec.substr(i, j - i);
    uint32_t s;
    if (l.compare(0, 4, "at: ") == 0) e.at = parseAt(l.c_str());
    else if (parseSeqLine(l.c_str(), &s)) e.seq = s;
    else if (l.compare(0, 8, "follows:") == 0)
      e.n_follows = parseFollowsLine(l.c_str(), e.follows, FLEETTIME_MAX_AGENTS);
    i = j + 1;
  }
  return e;
}

static std::string renderOne(VectorClock& vc, int16_t ord, const char* at) {
  LinkClaim k[1] = {{0x99, "espnow", LINK_MET, -40, -40}};
  char blk[EPISODEORDER_BLOCK_MAX];
  vc.renderBlock(blk, sizeof(blk));
  static char buf[SEMANTIC_LINK_EPISODE_BUF];
  size_t n = renderLinkEpisode(k, 1, ord, 0, at, buf, sizeof(buf), blk);
  vc.committed(vc.nextSeq());
  return std::string(buf, n);
}

static void testOrderFromText() {
  printf("6. order over rendered episodes (RFC-0004 §4.8 items 1-3)\n");
  VectorClock A, B;
  A.begin(0x10); B.begin(0x200);
  // A writes, then (radio) B learns A's vector, then B writes. Stamps overlap.
  EpisodeRef a1 = parseEpisode(0x10, renderOne(A, 1, "1000 ±600 frame:5000"));
  uint8_t w[EPISODEORDER_VECTOR_MAX];
  B.mergeWire(w, A.encode(w, sizeof(w)));
  EpisodeRef b1 = parseEpisode(0x200, renderOne(B, 1, "1100 ±600 frame:5000"));
  check(a1.seq == 1 && b1.seq == 1 && b1.n_follows == 1 && b1.follows[0].agent == 0x10,
        "seq and follows survive render -> text -> parse");
  check(order(a1, b1) == BEFORE, "ITEM 3: overlapping stamps, the edge decides (A before B)");
  EpisodeRef c2[2] = {a1, b1};
  size_t idx[2];
  check(maximal(c2, 2, idx, 2) == 1 && idx[0] == 1, "...so B's episode alone is maximal");

  // A writes again WITHOUT hearing B: concurrent with b1 (overlap, no edge either way).
  EpisodeRef a2 = parseEpisode(0x10, renderOne(A, 2, "1200 ±600 frame:5000"));
  check(order(a2, b1) == CONCURRENT, "ITEM 2: overlapping stamps, no edge: contested");
  check(order(a1, a2) == BEFORE, "same agent: seq decides");

  // Disjoint stamps, no edge: the stamps decide (ITEM 1).
  EpisodeRef a3 = parseEpisode(0x10, renderOne(A, 3, "90000 ±5 frame:5000"));
  check(order(b1, a3) == BEFORE, "ITEM 1: non-overlapping stamps retire the earlier");
}

// ---------------------------------------------------------------------------------------
static void testInbox() {
  printf("7. the recv side only copies\n");
  VectorClock src, vc;
  src.begin(0x10); vc.begin(0x300);
  src.committed(9);
  uint8_t w[EPISODEORDER_VECTOR_MAX];
  size_t n = src.encode(w, sizeof(w));
  VectorInbox in;
  check(in.push(w, n), "the callback's push succeeds");
  check(vc.others() == 0, "...and the clock has NOT moved: nothing merges in the callback");
  check(in.drainInto(vc) == 1 && vc.others() == 1, "loop() drains it into the clock");
  for (int i = 0; i < EPISODEORDER_INBOX + 2; ++i) in.push(w, n);
  check(in.dropped() >= 3, "a full inbox drops (and counts) rather than overwriting");
  check(in.drainInto(vc) == EPISODEORDER_INBOX - 1, "what was queued is all delivered");
  check(!in.push(w, EPISODEORDER_VECTOR_MAX + 1), "an oversized payload is never copied");
}

int main() {
  testDense();
  testMerge();
  testTransitive();
  testRecord();
  testBuffers();
  testOrderFromText();
  testInbox();
  printf("\n%d checks, %d failures\n", gChecks, gFails);
  return gFails ? 1 : 0;
}
