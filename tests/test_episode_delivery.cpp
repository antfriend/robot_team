// test_episode_delivery.cpp — docs/design/episode-order.md §7 (stage 2): delivery of LINK
// episodes into @LAT105, and the BAR VIEW (TTG-RFC-0004 §4.5, §4.8 item 4).
//
//   1. wire: WANT / DATA / DONE round-trip; malformed refused
//   2. Inflight: complete, empty, lost slice, oversize, foreign frames ignored
//   3. Fetcher: backlog on first sight, answered moves the cursor, back-off when silent
//   4. renderHeld: verbatim copy, re-headed, `held:` added; refuses what does not check
//   5. HeldIndex: boot from the lane, dedup, next ordinal, cuts in contiguous runs
//   6. SeqMap: the author's link lon -> seq, from boot lines and appends
//   7. ITEM 4: two agents, each holding its own + the other's copies, give IDENTICAL bar
//      digests while their live beliefs differ; one missing copy changes the digest
//   8. held copies never reach beliefs (EpisodeReader on @LAT103 ignores @LAT105)
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>
#include <vector>

#include "Episode.h"
#include "EpisodeDelivery.h"
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
  while (i < s.size()) {
    size_t j = s.find('\n', i);
    if (j == std::string::npos) j = s.size();
    r.line(s.substr(i, j - i).c_str());
    i = j + 1;
  }
  r.finish();
}

static const uint64_t kFrame = 5500;
static const uint32_t kBar = EPISODEDELIVERY_BAR_MS;

// One link episode of `agent`, stamped at t ±b in kFrame, carrying the clock's order block.
static std::string linkEp(VectorClock& vc, int16_t ord, int64_t t, uint32_t b,
                          const std::vector<LinkClaim>& k, uint64_t frame = kFrame) {
  char at[80];
  snprintf(at, sizeof(at), "%lld \xC2\xB1%lu frame:%llu", (long long)t, (unsigned long)b,
           (unsigned long long)frame);
  char blk[EPISODEORDER_BLOCK_MAX];
  vc.renderBlock(blk, sizeof(blk));
  static char buf[SEMANTIC_LINK_EPISODE_BUF];
  size_t n = renderLinkEpisode(k.data(), (int)k.size(), ord, (uint32_t)(t / 1000), at, buf,
                               sizeof(buf), blk);
  vc.committed(vc.nextSeq());
  return std::string(buf, n);
}

static std::string held(const std::string& rec, uint32_t agent, int16_t ord) {
  uint32_t seq = 0;
  size_t p = rec.find("\nseq: ");
  if (p != std::string::npos) seq = (uint32_t)strtoul(rec.c_str() + p + 6, nullptr, 10);
  static char out[EPISODEDELIVERY_MAX_EPISODE + 64];
  size_t n = renderHeld(rec.data(), rec.size(), agent, seq, ord, out, sizeof(out));
  return std::string(out, n);
}

// ---------------------------------------------------------------------------------------
static void testWire() {
  printf("1. wire\n");
  uint8_t b[208];
  Want w{0x300, 0x300, 41, 57, TIER_LINK}, w2;
  check(encodeWant(w, b, sizeof(b)) == 20 && decodeWant(b, 20, w2) &&
            w2.to == 0x300 && w2.from_seq == 41 && w2.to_seq == 57 && w2.tier == TIER_LINK &&
            w2.off == 0,
        "WANT round-trips (20 B, off 0 = a fresh fetch)");
  check(!decodeWant(b, 19, w2), "a short WANT is refused");
  Want r{0x300, 0x300, 41, 41, TIER_LINK, 382};
  check(encodeWant(r, b, sizeof(b)) == 20 && decodeWant(b, 20, w2) && w2.off == 382 &&
            w2.from_seq == 41 && w2.to_seq == 41,
        "a RESUME round-trips: one seq, from byte 382");
  r.to_seq = 42;
  encodeWant(r, b, sizeof(b));
  check(!decodeWant(b, 20, w2), "a resume naming a range of seqs is refused");
  w.from_seq = 0;
  encodeWant(w, b, sizeof(b));
  check(!decodeWant(b, 20, w2), "WANT from seq 0 is refused (seq 0 is no episode)");
  w = Want{1, 1, 9, 3, 0};
  encodeWant(w, b, sizeof(b));
  check(!decodeWant(b, 20, w2), "WANT with to < from is refused");

  const uint8_t payload[5] = {'a', 'b', 'c', 'd', 'e'};
  DataHdr h{0x200, 0x300, 77, 900, 191}, h2;
  size_t n = encodeData(h, payload, 5, b, sizeof(b));
  const uint8_t* got = nullptr;
  size_t gn = 0;
  check(n == 22 && decodeData(b, n, h2, &got, &gn) && h2.seq == 77 && h2.total == 900 &&
            h2.off == 191 && gn == 5 && memcmp(got, payload, 5) == 0,
        "DATA round-trips");
  uint8_t big[EPISODEDELIVERY_SLICE + 1] = {0};
  check(encodeData(h, big, sizeof(big), b, sizeof(b)) == 0, "a slice over 191 B is never sent");
  check(encodeData(h, big, EPISODEDELIVERY_SLICE, b, sizeof(b)) == 208,
        "a full slice fills the 208 B body exactly");
  DataHdr over{1, 2, 3, 10, 8};
  n = encodeData(over, payload, 5, b, sizeof(b));
  check(!decodeData(b, n, h2, &got, &gn), "a slice past its declared total is refused");

  Done d{0x200, 0x300, 77, 640}, d2;
  check(encodeDone(d, b, sizeof(b)) == 15 && decodeDone(b, 15, d2) && d2.through == 77 &&
            d2.total == 640,
        "DONE round-trips (15 B, with the episode's total)");
  check(!decodeDone(b, 14, d2), "a short DONE is refused");
  b[0] = EPISODEORDER_SUBOP_VECTOR;
  check(!decodeDone(b, 15, d2) && !decodeWant(b, 20, w2), "sub-ops do not cross-decode");
}

// ---------------------------------------------------------------------------------------
static void slices(Inflight& in, uint32_t to, uint32_t agent, uint32_t seq, const std::string& s,
                   int drop = -1) {
  int k = 0;
  for (size_t off = 0; off < s.size(); off += EPISODEDELIVERY_SLICE, ++k) {
    const size_t n = s.size() - off < EPISODEDELIVERY_SLICE ? s.size() - off : EPISODEDELIVERY_SLICE;
    if (k == drop) continue;
    in.onData(DataHdr{to, agent, seq, (uint16_t)s.size(), (uint16_t)off},
              (const uint8_t*)s.data() + off, n);
  }
}

static void testInflight() {
  printf("2. Inflight\n");
  static uint8_t buf[EPISODEDELIVERY_MAX_EPISODE];
  std::string ep(1000, 'x');
  Inflight in;
  check(in.state() == Inflight::IDLE, "idle until armed");
  in.arm(0x200, 0x300, buf, sizeof(buf));
  check(in.state() == Inflight::WAITING, "armed: waiting for DONE");
  slices(in, 0x200, 0x300, 12, ep);
  check(in.state() == Inflight::WAITING, "all slices in, no DONE yet: still waiting");
  in.onDone(Done{0x200, 0x300, 12, 1000});
  check(in.state() == Inflight::COMPLETE && in.length() == 1000 && in.seq() == 12,
        "slices + DONE: complete");

  // A lost slice (2026-10-03: ~half of broadcasts are lost on the handhelds): the prefix is
  // kept, everything past the gap is ignored, and the transfer ends PARTIAL, not BROKEN.
  std::string mixed;
  for (int i = 0; i < 1000; ++i) mixed += (char)('a' + i % 26);
  in.arm(0x200, 0x300, buf, sizeof(buf));
  slices(in, 0x200, 0x300, 13, mixed, 2);
  in.onDone(Done{0x200, 0x300, 13, 1000});
  check(in.state() == Inflight::PARTIAL && in.length() == 2 * EPISODEDELIVERY_SLICE &&
            in.seq() == 13,
        "a lost slice: PARTIAL, holding the contiguous prefix");
  in.resume();
  check(in.state() == Inflight::WAITING && in.length() == 2 * EPISODEDELIVERY_SLICE,
        "resume: waiting again, prefix kept");
  for (size_t off = 2 * EPISODEDELIVERY_SLICE; off < mixed.size(); off += EPISODEDELIVERY_SLICE) {
    const size_t n = mixed.size() - off < EPISODEDELIVERY_SLICE ? mixed.size() - off
                                                                : EPISODEDELIVERY_SLICE;
    in.onData(DataHdr{0x200, 0x300, 13, 1000, (uint16_t)off}, (const uint8_t*)mixed.data() + off, n);
  }
  in.onDone(Done{0x200, 0x300, 13, 1000});
  check(in.state() == Inflight::COMPLETE && in.length() == 1000 &&
            memcmp(in.bytes(), mixed.data(), 1000) == 0,
        "the resumed rest completes it, byte-exact");

  in.arm(0x200, 0x300, buf, sizeof(buf));
  slices(in, 0x200, 0x300, 14, mixed, 0);
  in.onDone(Done{0x200, 0x300, 14, 1000});
  check(in.state() == Inflight::PARTIAL && in.length() == 0 && in.seq() == 14,
        "a lost FIRST slice: later slices still name the episode; resume from 0");

  in.arm(0x200, 0x300, buf, sizeof(buf));
  in.onDone(Done{0x200, 0x300, 15, 1000});
  check(in.state() == Inflight::PARTIAL && in.seq() == 15 && in.length() == 0,
        "EVERY slice lost: the DONE's total says data was sent, so resume, never skip");

  in.arm(0x200, 0x300, buf, sizeof(buf));
  slices(in, 0x200, 0x300, 16, mixed, 3);
  in.onDone(Done{0x200, 0x300, 16, 1000});
  in.resume();
  in.onDone(Done{0x200, 0x300, 16, 0});
  check(in.state() == Inflight::EMPTY && in.through() == 16,
        "a resume answered 'gone' (folded meanwhile): EMPTY, the cursor moves past it");

  in.arm(0x200, 0x300, buf, sizeof(buf));
  slices(in, 0x200, 0x300, 17, mixed, 3);
  in.onDone(Done{0x200, 0x300, 17, 1000});
  in.resume();
  in.onData(DataHdr{0x200, 0x300, 9, 1000, (uint16_t)(3 * EPISODEDELIVERY_SLICE)},
            (const uint8_t*)mixed.data(), 10);
  in.onData(DataHdr{0x200, 0x300, 17, 999, (uint16_t)(3 * EPISODEDELIVERY_SLICE)},
            (const uint8_t*)mixed.data(), 10);
  check(in.length() == 3 * EPISODEDELIVERY_SLICE,
        "a late slice of another seq or another total is ignored, not appended");

  in.arm(0x200, 0x300, buf, sizeof(buf));
  in.onDone(Done{0x200, 0x300, 40, 0});
  check(in.state() == Inflight::EMPTY && in.through() == 40,
        "DONE alone with total 0: nothing in range, move the cursor");

  in.arm(0x200, 0x300, buf, sizeof(buf));
  slices(in, 0x999, 0x300, 14, ep);           // to someone else
  slices(in, 0x200, 0x100, 14, ep);           // from another agent
  in.onDone(Done{0x200, 0x100, 14, 1000});
  check(in.state() == Inflight::WAITING, "frames for another receiver or agent are ignored");

  in.arm(0x200, 0x300, buf, 500);
  slices(in, 0x200, 0x300, 15, ep);
  in.onDone(Done{0x200, 0x300, 15, 1000});
  check(in.state() == Inflight::BROKEN, "an episode larger than the buffer is refused");

  in.arm(0x200, 0x300, buf, sizeof(buf));
  slices(in, 0x200, 0x300, 16, ep);
  in.onDone(Done{0x200, 0x300, 17, 1000});
  check(in.state() == Inflight::BROKEN, "DONE naming another seq than the slices: BROKEN");
  in.disarm();
  check(in.state() == Inflight::IDLE, "disarm");
}

// ---------------------------------------------------------------------------------------
static void testFetcher() {
  printf("3. Fetcher\n");
  VectorClock vc;
  vc.begin(0x200);
  Fetcher f;
  f.begin(0x200);
  Want w;
  check(!f.next(vc, 0, w), "nobody heard of: nothing to want");
  vc.mergeEntry(0x300, 100);
  check(f.next(vc, 0, w) && w.agent == 0x300 && w.to == 0x300 &&
            w.from_seq == 100 - EPISODEDELIVERY_BACKLOG + 1 && w.to_seq == 100,
        "first sight: start BACKLOG behind the vector, not at seq 1");
  f.answered(0x300, 80, 10);
  check(f.next(vc, 10, w) && w.from_seq == 81, "answered: the cursor moves to `through`");
  f.answered(0x300, 100, 20);
  check(!f.next(vc, 20, w), "caught up: nothing to want");
  vc.mergeEntry(0x300, 103);
  check(f.next(vc, 20, w) && w.from_seq == 101 && w.to_seq == 103, "a new seq: want it");
  f.unanswered(0x300, 30);
  check(!f.next(vc, 31, w) && f.next(vc, 30 + EPISODEDELIVERY_RETRY_MS, w),
        "ONE unanswered WANT (a lost frame is ordinary): retried after RETRY_MS");
  uint32_t t = 30;
  for (int i = 1; i < EPISODEDELIVERY_MISSES_BEFORE_BACKOFF; ++i) {
    t += EPISODEDELIVERY_RETRY_MS;
    f.unanswered(0x300, t);
  }
  check(!f.next(vc, t + EPISODEDELIVERY_RETRY_MS, w),
        "MISSES_BEFORE_BACKOFF in a row: backed off (a peer without stage 2)");
  check(f.next(vc, t + EPISODEDELIVERY_BACKOFF_MS, w), "...until the back-off passes");
  f.answered(0x300, 100, t);
  f.unanswered(0x300, t + 1);
  check(f.next(vc, t + 1 + EPISODEDELIVERY_RETRY_MS, w), "an answer resets the miss count");

  // A board that is OFF: the back-off doubles per further miss, to the cap.
  Fetcher d;
  d.begin(0x200);
  uint32_t u = 1000;
  for (int i = 0; i < EPISODEDELIVERY_MISSES_BEFORE_BACKOFF; ++i) d.unanswered(0x300, u);
  check(!d.next(vc, u + EPISODEDELIVERY_BACKOFF_MS - 1, w) &&
            d.next(vc, u + EPISODEDELIVERY_BACKOFF_MS, w),
        "the first back-off is BACKOFF_MS");
  d.unanswered(0x300, u);
  check(!d.next(vc, u + 2 * EPISODEDELIVERY_BACKOFF_MS - 1, w) &&
            d.next(vc, u + 2 * EPISODEDELIVERY_BACKOFF_MS, w),
        "one more miss: twice that");
  for (int i = 0; i < 20; ++i) d.unanswered(0x300, u);
  check(!d.next(vc, u + EPISODEDELIVERY_BACKOFF_MAX_MS - 1, w) &&
            d.next(vc, u + EPISODEDELIVERY_BACKOFF_MAX_MS, w),
        "many misses: capped at BACKOFF_MAX_MS (no overflow)");
  d.answered(0x300, 100, u);
  d.unanswered(0x300, u + 1);
  check(d.next(vc, u + 1 + EPISODEDELIVERY_RETRY_MS, w), "an answer ends the back-off entirely");
  f.retry(0x300, 100);
  check(!f.next(vc, 101, w) && f.next(vc, 100 + EPISODEDELIVERY_RETRY_MS, w),
        "broken: retried after RETRY_MS");
  Fetcher g;
  g.begin(0x200);
  g.seed(0x300, 99);
  check(g.next(vc, 0, w) && w.from_seq == 100, "a seeded cursor (from held copies) is used");
  vc.mergeEntry(0x100, 5);
  check(g.next(vc, 0, w) && w.agent == 0x100 && w.from_seq == 1,
        "round robin reaches the next agent; a small seq starts at 1");
}

// ---------------------------------------------------------------------------------------
static void testRenderHeld() {
  printf("4. renderHeld\n");
  VectorClock vc;
  vc.begin(0x300);
  vc.committed(40);
  vc.mergeEntry(0x200, 7);
  std::vector<LinkClaim> k = {{0x200, "ble", LINK_MET, -40, -38}};
  std::string ep = linkEp(vc, 12, 1000000, 0, k);            // carries seq 41
  std::string h = held(ep, 0x300, 3);
  check(!h.empty(), "a link episode renders as a held copy");
  check(h.find("\n@LAT105LON3 | created:") != std::string::npos, "re-headed @LAT105LON<ord>");
  check(h.find("```ttdb-episode\nheld: 0x00000300\nsource: ") != std::string::npos,
        "`held:` is the first line inside the fence");
  // Everything after the held line is the author's text, byte for byte.
  const std::string body = ep.substr(ep.find("```ttdb-episode\n") + 16);
  check(h.compare(h.size() - body.size(), body.size(), body) == 0,
        "the rest is the author's episode verbatim");

  static char out[EPISODEDELIVERY_MAX_EPISODE + 64];
  check(renderHeld(ep.data(), ep.size(), 0x300, 40, 3, out, sizeof(out)) == 0 && out[0] == 0,
        "a seq that does not match the DATA's refuses");
  check(renderHeld(ep.data(), ep.size(), 0, 41, 3, out, sizeof(out)) == 0, "agent 0 refuses");
  std::string two = ep + ep;
  check(renderHeld(two.data(), two.size(), 0x300, 41, 3, out, sizeof(out)) == 0,
        "two records in one transfer refuse");
  std::string ent = ep;
  ent.replace(ent.find("@LAT103LON12"), 12, "@LAT103LON8204");
  check(renderHeld(ent.data(), ent.size(), 0x300, 41, 3, out, sizeof(out)) == 0,
        "an episode outside the LINK band refuses (stage 2 delivers link only)");
  std::string other = ep;
  other.replace(other.find("@LAT103"), 7, "@LAT105");
  check(renderHeld(other.data(), other.size(), 0x300, 41, 3, out, sizeof(out)) == 0,
        "a held copy is never re-held (only @LAT103 originals travel)");
  // As Ttdb::recordSpan serves it: from the header to the NEXT record's separator.
  std::string span = ep.substr(ep.find("@LAT103")) + "\n---\n\n";
  check(held(span, 0x300, 3) == h,
        "a record span (no leading separator, the next one's trailing) gives the same copy");
  std::string open = ep.substr(0, ep.rfind("```"));
  check(renderHeld(open.data(), open.size(), 0x300, 41, 3, out, sizeof(out)) == 0,
        "a block that never closes refuses");
  check(renderHeld(ep.data(), ep.size(), 0x300, 41, 3, out, h.size()) == 0,
        "one byte short of the copy: refused, never truncated");
  check(renderHeld(ep.data(), ep.size(), 0x300, 41, 3, out, h.size() + 1) == h.size(),
        "...and exactly enough fits");
}

// ---------------------------------------------------------------------------------------
static void testHeldIndex() {
  printf("5. HeldIndex\n");
  std::string lane;
  for (int i = 0; i < 5; ++i) {
    char b[200];
    snprintf(b, sizeof(b),
             "\n---\n\n@LAT105LON%d | created:0 | updated:0\n\n**link window**\n\n"
             "```ttdb-episode\nheld: 0x%08x\nsource: x\nat: 1 \xC2\xB1" "0 frame:1\nseq: %d\n```\n",
             20 + i, i % 2 ? 0x300 : 0x200, 50 + i);
    lane += b;
  }
  lane += "\n---\n\n@LAT103LON4 | created:0 | updated:0\n\n```ttdb-episode\nseq: 999\n```\n";
  HeldIndex hi;
  hi.reset();
  feedText(hi, lane);
  check(hi.count() == 5, "boot reads every @LAT105 copy and nothing else");
  check(hi.has(0x300, 51) && hi.has(0x200, 54) && !hi.has(0x300, 999),
        "dedup by (agent, seq)");
  check(hi.maxSeq(0x300) == 53 && hi.maxSeq(0x200) == 54 && hi.maxSeq(0x100) == 0,
        "max held seq per agent (the fetch cursor's seed)");
  check(hi.nextOrdinal() == 25, "the next ordinal follows the newest copy");

  Cut c[4];
  uint16_t cov = 0;
  check(hi.cuts(c, 4, true, &cov) == 0, "under quota: nothing to cut");
  for (int i = 0; i < EPISODEDELIVERY_HELD_QUOTA + EPISODEDELIVERY_HELD_SLACK - 5; ++i)
    hi.appended(0x300, 100 + i, hi.nextOrdinal());
  check(hi.count() == EPISODEDELIVERY_HELD_QUOTA + EPISODEDELIVERY_HELD_SLACK,
        "appends grow the ring");
  uint8_t n = hi.cuts(c, 4, false, &cov);
  check(n == 1 && c[0].lat == EPISODEDELIVERY_HELD_LANE && c[0].lon_lo == 20 &&
            c[0].lon_hi == 20 + EPISODEDELIVERY_HELD_SLACK - 1 && cov == EPISODEDELIVERY_HELD_SLACK,
        "at quota + slack: cut the oldest SLACK as one contiguous run");
  hi.cutDone(cov);
  // The cut took the oldest SLACK: the 5 boot copies and appended seqs 100..102.
  check(hi.count() == EPISODEDELIVERY_HELD_QUOTA && !hi.has(0x200, 50) && !hi.has(0x300, 102) &&
            hi.has(0x300, 103),
        "exactly the oldest SLACK copies are gone, the rest kept");
  hi.appended(0x300, 999, hi.nextOrdinal());
  check(hi.cuts(c, 4, false, &cov) == 0 && hi.cuts(c, 4, true, &cov) == 1 && cov == 1,
        "between quota and slack: only a forced (boot) cut runs");
}

// ---------------------------------------------------------------------------------------
static void testSeqMap() {
  printf("6. SeqMap\n");
  const char* lines =
      "@LAT103LON40 | x\n```ttdb-episode\nseq: 7\n```\n"
      "@LAT103LON8195 | x\n```ttdb-episode\nseq: 8\n```\n"          // entity: not served
      "@LAT103LON41 | x\n```ttdb-episode\nseq: 10\n```\n"
      "@LAT105LON2 | x\n```ttdb-episode\nheld: 0x10\nseq: 3\n```\n"  // held: not ours
      "@LAT103LON42 | x\n```ttdb-episode\nsource: x\n```\n";         // pre-C4: no seq
  SeqMap m;
  std::string s(lines);
  size_t i = 0;
  while (i < s.size()) {
    size_t j = s.find('\n', i);
    m.line(s.substr(i, j - i).c_str());
    i = j + 1;
  }
  check(m.count() == 2, "only own LINK episodes that carry a seq are mapped");
  uint32_t seq; int16_t lon;
  check(m.firstInRange(1, 0, &seq, &lon) && seq == 7 && lon == 40, "the first link seq");
  check(m.firstInRange(8, 20, &seq, &lon) && seq == 10 && lon == 41,
        "a non-link seq in range is skipped to the next link one");
  check(!m.firstInRange(11, 20, &seq, &lon), "none in range");
  m.add(43, 12);
  check(m.firstInRange(11, 20, &seq, &lon) && seq == 12, "add() on append");
  m.remove(43);
  check(!m.firstInRange(11, 20, &seq, &lon), "remove() when the record is cut");
}

// ---------------------------------------------------------------------------------------
static BarDigest digestOf(const std::string& store, int64_t n, uint16_t* own = nullptr,
                          uint16_t* hld = nullptr) {
  static Consolidator c;
  c.begin();
  BarView v(c, kFrame, barLine(kFrame, kBar, n - 1), barLine(kFrame, kBar, n));
  feedText(v, store);
  if (own) *own = v.own();
  if (hld) *hld = v.held();
  return barDigest(c);
}

// The BAR record a node would write for bar n of `store`, and only its HOLDS lines.
static std::string barRecordOf(const std::string& store, int64_t n, uint32_t self,
                               int16_t ord = 0, int64_t settled = 120000) {
  static Consolidator c;
  c.begin();
  BarView v(c, kFrame, barLine(kFrame, kBar, n - 1), barLine(kFrame, kBar, n), self);
  feedText(v, store);
  v.finish();
  static char out[1024];
  const size_t m = renderBar(out, sizeof(out), ord, kFrame, n, v, barDigest(c), settled);
  return std::string(out, m);
}

static std::string holdsOf(const std::string& rec) {
  std::string out;
  size_t at = 0;
  while ((at = rec.find("**HOLDS**", at)) != std::string::npos) {
    const size_t e = rec.find('\n', at);
    out += rec.substr(at, e - at + 1);
    at = e;
  }
  return out;
}

static std::string beliefsOf(const std::string& store) {
  static Consolidator c;
  c.begin();
  EpisodeReader r(c);
  r.select(0, 8191, Consolidator::KEEPING, tierBand(TIER_LINK));
  feedText(r, store);
  std::string out;
  for (size_t i = 0; i < c.termCount(); ++i) {
    char b[128];
    if (c.beliefLine(*c.term(i), b, sizeof(b))) { out += c.term(i)->subject; out += b; out += "\n"; }
  }
  return out;
}

static void testItem4() {
  printf("7. ITEM 4: same episodes, same bar view, no coordination\n");
  VectorClock X, Y;
  X.begin(0x300); Y.begin(0x200);
  std::string xOwn, yOwn, xHeld, yHeld;
  std::vector<std::string> yEps;
  int16_t xo = 0, yo = 0, xh = 0, yh = 0;
  // Three bars of traffic. Each minute X and Y each write a link window about the peers
  // they can hear, with DIFFERENT verdicts, so their own beliefs differ.
  for (int m = 1; m < 30; ++m) {
    const int64_t t = (int64_t)kFrame + (int64_t)m * 60000;
    std::string ex = linkEp(X, xo++, t, 50,
                            {{0x10, "espnow", (uint8_t)(m % 3 ? LINK_MET : LINK_VIOLATED), -50, -52},
                             {0x200, "ble", LINK_MET, -40, -41}});
    std::string ey = linkEp(Y, yo++, t + 20000, 50,
                            {{0x10, "espnow", LINK_MET, -45, -44},
                             {0x300, "ble", (uint8_t)(m % 4 ? LINK_MET : LINK_VIOLATED), -40, -60}});
    xOwn += ex; yOwn += ey;
    yHeld += held(ex, 0x300, yh++);           // Y fetched X's episode
    xHeld += held(ey, 0x200, xh++);           // X fetched Y's
    yEps.push_back(ey);
  }
  // A store also carries an entity episode and a pre-C4 one, neither of which may count.
  VectorClock z; z.begin(0x300);
  static char eb[SEMANTIC_ENTITY_EPISODE_BUF];
  const char* ebody = "**ENTWIN** t_ms:1 stream:0x1 wall:0 window_ms:600000\n";
  memcpy(eb, ebody, strlen(ebody));
  char at[64];
  snprintf(at, sizeof(at), "%llu \xC2\xB1" "0 frame:%llu", (unsigned long long)(kFrame + 70000),
           (unsigned long long)kFrame);
  size_t en = renderSaidEpisodeInPlace(eb, sizeof(eb), strlen(ebody), 8200, 0, "entity window",
                                       "entitypercept", at);
  xOwn += std::string(eb, en);

  const std::string xStore = xOwn + xHeld, yStore = yOwn + yHeld;
  check(beliefsOf(xStore) != beliefsOf(yStore),
        "NOT VACUOUS: the two agents' own beliefs differ");
  for (int64_t n = 1; n <= 2; ++n) {
    uint16_t xo2, xh2, yo2, yh2;
    BarDigest a = digestOf(xStore, n, &xo2, &xh2), b = digestOf(yStore, n, &yo2, &yh2);
    char msg[160];
    snprintf(msg, sizeof(msg), "bar %lld: X (own %u held %u) and Y (own %u held %u) agree, "
             "%u terms", (long long)n, xo2, xh2, yo2, yh2, a.terms);
    check(a.terms > 0 && a.terms == b.terms && a.sum == b.sum && xo2 == yh2 && xh2 == yo2, msg);
  }
  check(digestOf(xOwn + xHeld, 1).sum != digestOf(xOwn, 1).sum,
        "the held copies are IN the view (without them it differs)");

  // Falsifier sensitivity: X missing ONE of Y's bar-1 copies gives a different digest.
  std::string xMissing = xOwn;
  int16_t k = 0;
  for (size_t i = 0; i < yEps.size(); ++i)
    if (i != 3) xMissing += held(yEps[i], 0x200, k++);
  check(digestOf(xMissing, 1).sum != digestOf(yStore, 1).sum,
        "one missing copy CHANGES the bar view (the gate can fail)");
  check(digestOf(xMissing, 2).sum == digestOf(yStore, 2).sum,
        "...and only that bar's: bars are disjoint windows");

  // The BAR record's HOLDS rows: the same SET of episodes gives the same rows on both
  // nodes, and the missing copy shows there too, so a pair of records answers gate (g)
  // after retention has trimmed the copies themselves.
  for (int64_t n = 1; n <= 2; ++n) {
    const std::string hx = holdsOf(barRecordOf(xStore, n, 0x300));
    const std::string hy = holdsOf(barRecordOf(yStore, n, 0x200));
    char msg[96];
    snprintf(msg, sizeof(msg), "bar %lld: X's and Y's HOLDS rows are identical (2 authors)",
             (long long)n);
    check(!hx.empty() && hx == hy && std::count(hx.begin(), hx.end(), '\n') == 2, msg);
  }
  check(holdsOf(barRecordOf(xMissing, 1, 0x300)) != holdsOf(barRecordOf(yStore, 1, 0x200)),
        "one missing copy changes that bar's HOLDS rows");

  // Order does not matter: held copies first, own later.
  check(digestOf(xHeld + xOwn, 2).sum == digestOf(xStore, 2).sum,
        "record order in the store does not change the view");

  // The window: an episode straddling a bar line belongs to neither bar.
  VectorClock s; s.begin(0x100);
  std::string straddle = linkEp(s, 0, barLine(kFrame, kBar, 1), 1000,
                                {{0x99, "espnow", LINK_MET, -40, -40}});
  check(digestOf(straddle, 1).terms == 0 && digestOf(straddle, 2).terms == 0,
        "a stamp range across a bar line is in neither bar");
  std::string other = linkEp(s, 1, (int64_t)kFrame + 60000, 0,
                             {{0x99, "espnow", LINK_MET, -40, -40}}, 6500);
  check(digestOf(other, 1).terms == 0, "a stamp in another frame is in no bar of this one");

  check(completeBar((int64_t)kFrame + kBar + EPISODEDELIVERY_BAR_SETTLE_MS - 1, kFrame, kBar,
                    EPISODEDELIVERY_BAR_SETTLE_MS) == -1 &&
            completeBar((int64_t)kFrame + kBar + EPISODEDELIVERY_BAR_SETTLE_MS, kFrame, kBar,
                        EPISODEDELIVERY_BAR_SETTLE_MS) == 1,
        "bar 1 is complete exactly SETTLE after its line");
  check(barLine(kFrame, kBar, 3) == (int64_t)kFrame + 3 * (int64_t)kBar, "barLine");

  // CROSS-LANGUAGE PIN: the same fixture and the same digest are asserted in
  // tests/test_episode_order_py.py (fleet.py bar_view). If either side drifts, a laptop
  // would report DIFFER for nodes that agree, or AGREE for nodes that do not.
  const std::string fx =
      "@LAT103LON0 | created:0 | updated:0\n\n**link window**\n\n```ttdb-episode\n"
      "source: perceptlearn\nat: 65500 \xC2\xB1" "50 frame:5500\nseq: 1\nsaid: 1 | x\n"
      "percept: 1 | 0x00000010 | link_stable | espnow | + | -\n"
      "percept: 2 | 0x00000200 | link_stable | ble | - | -\n```\n\n---\n\n"
      "@LAT105LON0 | created:0 | updated:0\n\n**link window**\n\n```ttdb-episode\n"
      "held: 0x00000200\nsource: perceptlearn\nat: 125500 \xC2\xB1" "50 frame:5500\nseq: 4\n"
      "percept: 1 | 0x00000010 | link_stable | espnow | + | ~\n```\n";
  uint16_t fo = 0, fh = 0;
  const BarDigest fd = digestOf(fx, 1, &fo, &fh);
  check(fo == 1 && fh == 1 && fd.terms == 2 && fd.sum == 0xfa9dab24u,
        "the pinned fixture: own 1, held 1, 2 terms, digest 0xfa9dab24 (= fleet.py)");

  // CROSS-LANGUAGE PIN #2: the BAR record for the fixture, byte for byte
  // (tests/test_bar_py.py renders and parses this exact text).
  const std::string want =
      "@LAT106LON7 | created:0 | updated:0\n\n"
      "**BAR** frame:5500 bar:1 own:1 held:1 terms:2 digest:0xfa9dab24 settled_ms:120000\n"
      "**HOLDS** agent:0x00000200 n:1 lo:4 hi:4 sum:4\n"
      "**HOLDS** agent:0x00000300 n:1 lo:1 hi:1 sum:1\n";
  check(barRecordOf(fx, 1, 0x300, 7) == want, "the pinned fixture's BAR record, byte-exact");
}

// ---------------------------------------------------------------------------------------
static void testBarRecord() {
  printf("9. the BAR record (@LAT106) and its index\n");
  static Consolidator c;
  c.begin();
  BarView v(c, kFrame, 0, 1, 0x300);
  v.finish();
  char out[256];
  const size_t full = renderBar(out, sizeof(out), 3, kFrame, 4, v, barDigest(c), 130000);
  check(full > 0 && strstr(out, "own:0 held:0 terms:0 digest:0x00000000") &&
            !strstr(out, "**HOLDS**"),
        "an empty bar is still recorded (no HOLDS rows)");
  char tight[256];
  check(renderBar(tight, full + 1, 3, kFrame, 4, v, barDigest(c), 130000) == full,
        "it fits in exactly its length + NUL");
  check(renderBar(tight, full, 3, kFrame, 4, v, barDigest(c), 130000) == 0 && tight[0] == '\0',
        "one byte less: nothing written, never truncated");

  BarIndex ix;
  ix.reset();
  std::string boot;
  for (int i = 0; i < 3; ++i) {
    renderBar(out, sizeof(out), (int16_t)(10 + i), kFrame, 40 + i, v, barDigest(c), 120000);
    boot += std::string(out) + "\n---\n\n";
  }
  feedText(ix, "@LAT105LON9 | created:0 | updated:0\n\n**BAR** frame:5500 bar:99 x\n\n---\n\n" +
                   boot);
  check(ix.count() == 3 && ix.has(kFrame, 41) && !ix.has(kFrame, 99) && !ix.has(6500, 41),
        "boot scan: three bars, keyed by (frame, bar); another lane's text is ignored");
  check(ix.nextOrdinal() == 13, "the next record takes the next LON");
  Cut cut;
  uint16_t covers = 9;
  check(!ix.cut(&cut, false, &covers) && covers == 0, "under quota: nothing to cut");
  for (int i = 3; i < EPISODEDELIVERY_BAR_QUOTA + EPISODEDELIVERY_BAR_SLACK; ++i)
    ix.appended(kFrame, 40 + i, ix.nextOrdinal());
  check(ix.cut(&cut, false, &covers) && cut.lat == EPISODEDELIVERY_BAR_LANE &&
            cut.lon_lo == 10 && cut.lon_hi == 10 + EPISODEDELIVERY_BAR_SLACK - 1 &&
            covers == EPISODEDELIVERY_BAR_SLACK,
        "at QUOTA + SLACK: the oldest SLACK records, one contiguous run");
  ix.cutDone(covers);
  check(ix.count() == EPISODEDELIVERY_BAR_QUOTA && !ix.has(kFrame, 40) && ix.has(kFrame, 44),
        "cutDone drops exactly the oldest");
  ix.appended(kFrame, 100, ix.nextOrdinal());
  check(!ix.cut(&cut, false, &covers) && ix.cut(&cut, true, &covers) && covers == 1,
        "over quota but under slack: only a forced (boot) cut");
}

// ---------------------------------------------------------------------------------------
static void testNotBeliefs() {
  printf("8. held copies are testimony: never in beliefs\n");
  VectorClock Y; Y.begin(0x200);
  std::string ey = linkEp(Y, 0, 1000000, 0, {{0x10, "espnow", LINK_MET, -45, -44}});
  std::string h = held(ey, 0x200, 0);
  check(beliefsOf(h).empty(), "an EpisodeReader on @LAT103 feeds nothing from @LAT105");
  check(beliefsOf(ey) != "", "...while the same text on @LAT103 does");
}

int main() {
  testWire();
  testInflight();
  testFetcher();
  testRenderHeld();
  testHeldIndex();
  testSeqMap();
  testItem4();
  testNotBeliefs();
  testBarRecord();
  printf("\n%d checks, %d failures\n", gChecks, gFails);
  return gFails ? 1 : 0;
}
