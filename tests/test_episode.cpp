// test_episode.cpp — ACT-III Phase C, the EPISODE tier: writer, reader, checkpoint, ring.
//
// test_semantic.cpp holds C3's gates over the CONSOLIDATOR in isolation. This file holds
// them over the whole path the firmware will run — render a record, append it, read the
// lane back, fold, commit, cut, reboot — against a stand-in store, because every expensive
// defect this repo has had was in the seam between two individually-correct pieces.
//
// THE GATES:
//   1. NEVER REFUSES. Every episode offered is appended. Not "almost every", and not
//      "every one that fitted" — the phase's pass condition is a deletion (ACT-III §C0),
//      and a refusal is the thing being deleted.
//   2. FOLD IS INVISIBLE TO BELIEF. At every step the node's beliefs equal a reference
//      consolidator that saw every episode and never evicted anything.
//   3. A REBOOT AT ANY POINT AGREES. A fresh consolidator rebuilt from the store alone —
//      newest checkpoint + live episodes — equals the reference too. Checked after EVERY
//      step, including with commits and cuts made to FAIL, which is the case the
//      checkpoint-as-commit-point design exists for: the heap refuses lane rewrites with
//      the radios up (TTDB.h), so a cut that never happens must cost nothing but space.
//   4. BOUNDED. The live window never exceeds capacity once a commit can land.
//   5. THE GRAVESTONE. Nothing in a checkpoint may be read back as evidence.
//   6. ORDINALS WRAP at 32768 (TtdbRecord::lon is int16_t) without a double count.
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <string>
#include <vector>

#include "AcousticPercept.h"
#include "EntityPercept.h"
#include "Episode.h"
#include "Semantic.h"
#include "TtdbParse.h"

static int gChecks = 0, gFails = 0;
static void check(bool ok, const char* what) {
  ++gChecks;
  if (!ok) { ++gFails; printf("  FAIL: %s\n", what); }
}
static void checkStr(const std::string& got, const std::string& want, const char* what) {
  ++gChecks;
  if (got != want) {
    ++gFails;
    printf("  FAIL: %s\n        want |%s|\n        got  |%s|\n", what, want.c_str(), got.c_str());
  }
}

using namespace semantic;

static Percept mk(uint32_t sentence, const char* s, const char* v, const char* o,
                  Polarity pol, Quant q) {
  Percept p;
  memset(&p, 0, sizeof(p));
  p.sentence = sentence;
  snprintf(p.subject, SEMANTIC_LEMMA_MAX, "%s", s);
  snprintf(p.vec, SEMANTIC_LEMMA_MAX, "%s", v);
  snprintf(p.object, SEMANTIC_LEMMA_MAX, "%s", o);
  p.pol = pol;
  p.quant = q;
  return p;
}

// Feed a block of text to anything with a line(const char*) method, one line at a time,
// the way the glue will stream it off flash.
template <class R>
static void feedText(R& r, const std::string& text) {
  size_t i = 0;
  while (i <= text.size()) {
    size_t j = text.find('\n', i);
    if (j == std::string::npos) j = text.size();
    std::string l = text.substr(i, j - i);
    r.line(l.c_str());
    i = j + 1;
  }
}

// All belief lines, keyed by triple — insertion order legitimately differs after a reboot
// (carried terms are interned first), so equality is per triple, byte-for-byte per line.
static std::map<std::string, std::string> beliefs(const Consolidator& c) {
  std::map<std::string, std::string> out;
  for (size_t i = 0; i < c.termCount(); ++i) {
    const Term* t = c.term(i);
    char b[160];
    size_t n = c.beliefLine(*t, b, sizeof(b));
    // ⚠ NOT ONLY THE BELIEF LINE. `seen` drives sal and therefore EPS — the eviction key,
    // the arbiter's key, the snake's — and `episodes` is reported beside it. On hardware
    // (2026-10-01) the belief lines survived a reboot byte-for-byte while EPS silently
    // changed, because `seen` was neither carried nor protected from the fold's replay.
    // A gate comparing belief lines alone could not see it.
    snprintf(b + n, sizeof(b) - n, " | seen %lu episodes %u eps %u", (unsigned long)t->seen,
             (unsigned)t->episodes, (unsigned)c.eps(*t));
    out[std::string(t->subject) + "|" + t->vec + "|" + t->object] = b;
  }
  return out;
}

// =======================================================================================
// 1. serial ordinals
// =======================================================================================
static void testOrdinals() {
  printf("ordinals\n");
  check(ordinalAdd(32767, 1) == 0, "32767 + 1 wraps to 0");
  check(ordinalAdd(0, -1) == 32767, "0 - 1 wraps to 32767");
  check(ordinalDistance(32760, 5) == 13, "distance across the wrap is the short way forward");
  check(ordinalInRun(2, 32766, 4), "a run that wraps contains an ordinal after the wrap");
  check(ordinalInRun(32767, 32766, 4), "and one before it");
  check(!ordinalInRun(5, 32766, 4), "but not one past its end");
  check(!ordinalInRun(32765, 32766, 4), "nor one before its start");
}

// =======================================================================================
// 2. the builder — exact bytes, rejection, and both ends of the buffer rule
// =======================================================================================
static const char* kGolden =
    "\n---\n\n@LAT103LON7 | created:1234 | updated:1234\n\n**link window**\n\n"
    "```ttdb-episode\nsource: linkpercept\nat: 1234\n"
    "said: 1 | 0x00000200 held the link over ble\n"
    "percept: 1 | 0x00000200 | link_stable | ble | + | -\n"
    "```\n";

static size_t buildGolden(char* buf, size_t cap, EpisodeBuilder** out = 0) {
  static EpisodeBuilder* keep = 0;
  delete keep;
  keep = new EpisodeBuilder(buf, cap);
  keep->begin(7, 1234, "link window", "linkpercept", "1234");
  keep->said(1, "0x00000200 held the link over ble");
  keep->percept(mk(1, "0x00000200", "link_stable", "ble", POL_PLUS, Q_NONE));
  if (out) *out = keep;
  return keep->finish();
}

static void testBuilder() {
  printf("builder\n");
  char buf[512];
  size_t n = buildGolden(buf, sizeof(buf));
  check(n == strlen(kGolden), "finish() returns the record length");
  checkStr(std::string(buf, n), kGolden, "an episode record renders byte-for-byte");

  // The header must index as the record it claims to be — through the firmware's own
  // parser, not a reimplementation of it.
  TtdbRecord r;
  check(ttdbParseHeader("@LAT103LON7 | created:1234 | updated:1234", r) && r.lat == 103 &&
            r.lon == 7 && r.created == 1234,
        "the header indexes through ttdbParseHeader as @LAT103LON7");

  // Both directions of the buffer rule: exactly enough fits; one byte less writes NOTHING.
  const size_t need = strlen(kGolden) + 1;
  std::vector<char> exact(need), shortb(need - 1);
  check(buildGolden(exact.data(), exact.size()) == need - 1, "a buffer of exactly len+1 fits");
  check(buildGolden(shortb.data(), shortb.size()) == 0,
        "one byte short writes NOTHING — never a truncated record");
  check(shortb[0] == '\0' || strlen(shortb.data()) < shortb.size(),
        "and leaves no unterminated half-line behind");

  // A lemma carrying the separator would read back as a DIFFERENT triple. Rejected and
  // counted, and the rest of the episode still renders.
  EpisodeBuilder b(buf, sizeof(buf));
  b.begin(1, 0, "t", "s", "0");
  check(!b.percept(mk(1, "a|b", "v", "o", POL_PLUS, Q_NONE)), "a lemma with `|` is rejected");
  check(!b.percept(mk(1, "a", "v\nx", "o", POL_PLUS, Q_NONE)), "a lemma with a newline is rejected");
  check(b.percept(mk(1, "a", "v", "o", POL_PLUS, Q_NONE)), "and the next good percept still lands");
  check(b.finish() > 0 && b.rejected() == 2 && b.percepts() == 1,
        "rejections are counted, the record is still written");
  check(strstr(buf, "a|b") == 0, "and the rejected lemma never reached the record");

  EpisodeBuilder bad(buf, sizeof(buf));
  check(!bad.begin(1, 0, "title|x", "s", "0"), "a header field with `|` is unwritable");
  check(bad.finish() == 0, "so the record is not written at all");
}

// =======================================================================================
// 3. the reader — lane discipline, selection, damage
// =======================================================================================
static std::string record(int16_t lane, int16_t ord, const std::vector<Percept>& ps) {
  char buf[2048];
  EpisodeBuilder b(buf, sizeof(buf));
  b.begin(ord, (uint32_t)ord, "w", "test", "0", lane);
  for (size_t i = 0; i < ps.size(); ++i) b.percept(ps[i]);
  size_t n = b.finish();
  return std::string(buf, n);
}

static void testReader() {
  printf("reader\n");
  std::vector<Percept> plus1(1, mk(1, "p", "v", "o", POL_PLUS, Q_NONE));
  std::vector<Percept> minus1(1, mk(1, "p", "v", "o", POL_MINUS, Q_NONE));

  std::string store = record(103, 0, plus1) + record(103, 1, plus1) + record(103, 2, minus1);

  {
    Consolidator c; c.begin();
    EpisodeReader r(c);
    r.select(0, 2, Consolidator::KEEPING);
    feedText(r, store);
    r.finish();
    const Term* t = c.find("p", "v", "o");
    check(r.fed() == 3 && t && t->totalFor() == 4 && t->totalAgainst() == 2,
          "three on-lane episodes feed: for 2, against 1 (in halves 4/2)");
  }
  {
    Consolidator c; c.begin();
    EpisodeReader r(c);
    r.select(1, 2, Consolidator::KEEPING);
    feedText(r, store);
    r.finish();
    check(r.fed() == 2 && r.outside() == 1, "a selection skips — and counts — the rest");
  }
  {
    // TTG-0002 §5.1: a block of the same tag OFF the lane is a quotation. Checked for
    // malformed lines, contributes nothing.
    std::string quoted = record(50, 0, plus1) +
                         "\n---\n\n@LAT51LON0 | created:0 | updated:0\n\n```ttdb-episode\n"
                         "percept: x | p | v | o | + | -\n```\n";
    Consolidator c; c.begin();
    EpisodeReader r(c);
    r.select(0, 32767, Consolidator::KEEPING);
    feedText(r, quoted);
    r.finish();
    check(c.termCount() == 0 && r.fed() == 0, "an off-lane block teaches nothing");
    check(r.foreignBlocks() == 2 && r.foreignMalformed() == 1,
          "but it is still checked: 2 foreign blocks, 1 malformed line reported");
  }
  {
    // A fence that never closes is damage: closed at the next header, and counted.
    std::string broken = "\n---\n\n@LAT103LON0 | created:0 | updated:0\n\n```ttdb-episode\n"
                         "percept: 1 | p | v | o | + | -\n" + record(103, 1, plus1);
    Consolidator c; c.begin();
    EpisodeReader r(c);
    r.select(0, 1, Consolidator::KEEPING);
    feedText(r, broken);
    r.finish();
    const Term* t = c.find("p", "v", "o");
    check(r.unclosed() == 1 && r.fed() == 2 && t && t->totalFor() == 4,
          "an unclosed block closes at the next header — counted, and the next record is "
          "not swallowed into it");
  }
  {
    // A malformed percept on the lane: skipped, counted, the episode continues.
    std::string mixed = "\n---\n\n@LAT103LON0 | created:0 | updated:0\n\n```ttdb-episode\n"
                        "said: 1 | percept: 1 | not | a | percept | + | -\n"
                        "percept: oops | p | v | o | + | -\n"
                        "percept: 2 | p | v | o | + | -\n```\n";
    Consolidator c; c.begin();
    EpisodeReader r(c);
    r.select(0, 0, Consolidator::KEEPING);
    feedText(r, mixed);
    r.finish();
    const Term* t = c.find("p", "v", "o");
    check(c.malformedCount() == 1 && t && t->totalFor() == 2 && !c.find("not", "a", "percept"),
          "a malformed percept is skipped and counted; a `said:` line quoting one is NOT read");
  }
}

// =======================================================================================
// 4. the checkpoint — round trip, gravestone, only-the-newest, worst-case size
// =======================================================================================
static void testCheckpoint() {
  printf("checkpoint\n");
  Consolidator c; c.begin();
  for (int e = 0; e < 4; ++e) {
    c.beginEpisode();
    c.percept(mk(1, "0x00000200", "link_stable", "ble", e == 2 ? POL_MINUS : POL_PLUS,
                 e == 3 ? Q_SOME : Q_NONE));
    c.endEpisode(Consolidator::KEEPING);
  }
  c.beginEpisode();
  c.percept(mk(1, "0x00000100", "link_stable", "espnow", POL_PLUS, Q_NONE));
  c.endEpisode(Consolidator::KEEPING);       // live only: must NOT appear in a checkpoint
  // Fold the first four (replay them EVICTING).
  for (int e = 0; e < 4; ++e) {
    c.beginEpisode();
    c.percept(mk(1, "0x00000200", "link_stable", "ble", e == 2 ? POL_MINUS : POL_PLUS,
                 e == 3 ? Q_SOME : Q_NONE));
    c.endEpisode(Consolidator::EVICTING);
  }

  static char buf[SEMANTIC_CARRIED_BUF];
  size_t n = renderCheckpoint(c, 3, 0, 99, buf, sizeof(buf));
  std::string ck(buf, n);
  checkStr(ck,
           "\n---\n\n@LAT104LON0 | created:99 | updated:99\n\n"
           "**carried through @LAT103LON3**\n\n```ttdb-carried\nthrough: 3\n"
           "carried: 2.5 1 4 4 | 0x00000200 | link_stable | ble\n```\n",
           "a checkpoint renders byte-for-byte, and only terms with a carried tally appear");

  // --- THE GRAVESTONE, three layers ------------------------------------------------
  bool clean = true;
  for (size_t i = 0; i < ck.size();) {
    size_t j = ck.find('\n', i);
    if (j == std::string::npos) j = ck.size();
    std::string l = ck.substr(i, j - i);
    if (l.compare(0, 8, "percept:") == 0 || l.compare(0, 7, "belief:") == 0) clean = false;
    i = j + 1;
  }
  check(clean, "layer 1: no checkpoint line begins `percept:` or `belief:`");
  Percept p; Malformed why;
  check(!Consolidator::parsePerceptLine("carried: 2.5 1 4 4 | 0x00000200 | link_stable | ble", p, why) &&
            why == MAL_COLUMNS,
        "layer 2: a carried line does not parse as a percept even WITHOUT the key check");
  {
    Consolidator g; g.begin();
    EpisodeReader r(g);
    r.select(0, 32767, Consolidator::KEEPING);
    feedText(r, ck);
    r.finish();
    check(g.termCount() == 0 && r.fed() == 0,
          "layer 3: the episode reader learns nothing from a checkpoint");
  }

  // --- round trip -------------------------------------------------------------------
  {
    Consolidator g; g.begin();
    CheckpointReader cr(g, 0);
    feedText(cr, ck);
    const Term* t = g.find("0x00000200", "link_stable", "ble");
    check(cr.found() && cr.through() == 3 && cr.seeded() == 1 && cr.malformed() == 0,
          "the checkpoint reads back: through 3, one term seeded");
    check(t && t->carried_for == 5 && t->carried_against == 2 && t->live_for == 0,
          "into CARRIED, never live — 2.5/1 in halves is 5/2");
    check(t && t->carried_seen == 4 && t->seen == 4 && t->carried_episodes == 4 &&
              t->episodes == 4,
          "seen and episodes round-trip as CARRIED shares (the 2026-10-01 EPS-drift fix)");
  }
  {
    // A checkpoint written BEFORE that fix is on the Cardputer's flash right now: three
    // numbers, the third a total. It must still parse — seen 0, never a malformed line.
    Consolidator g; g.begin();
    check(g.seedCarried("a", "v", "o", "carried: 3 1 7") && g.find("a", "v", "o") &&
              g.find("a", "v", "o")->carried_for == 6 && g.find("a", "v", "o")->seen == 0 &&
              g.find("a", "v", "o")->episodes == 7,
          "a pre-fix 3-number carried line still seeds (seen 0)");
  }
  // --- only the newest ----------------------------------------------------------------
  {
    Consolidator g; g.begin();
    CheckpointReader cr(g, 1);               // ask for LON1; the store holds LON0
    feedText(cr, ck);
    check(!cr.found() && g.termCount() == 0,
          "a reader told to honour LON1 ignores LON0 entirely — an older checkpoint would "
          "resurrect a belief the store chose to forget");
  }

  // --- worst case: a full table of maximal lemmas and tallies must fit ---------------
  {
    Consolidator big; big.begin();
    char lem[SEMANTIC_LEMMA_MAX];
    for (int k = 0; k < SEMANTIC_MAX_TERMS; ++k) {
      memset(lem, 'a' + (k % 26), sizeof(lem) - 1);
      lem[sizeof(lem) - 1] = '\0';
      snprintf(lem, 4, "%03d", k);           // unique prefix
      lem[3] = 'x';
      char line[64];
      snprintf(line, sizeof(line), "carried: 2147483647.5 2147483647.5 65535 4294967295");
      big.seedCarried(lem, lem, lem, line);
    }
    size_t w = renderCheckpoint(big, 32767, 32767, 4294967295u, buf, sizeof(buf));
    check(big.termCount() == SEMANTIC_MAX_TERMS && w > 0,
          "a FULL table of maximal lemmas and tallies fits SEMANTIC_CARRIED_BUF — a "
          "checkpoint that cannot render cannot commit, and then the ring only grows");
    std::vector<char> tight(w);              // one byte short of w + 1
    check(renderCheckpoint(big, 32767, 32767, 4294967295u, tight.data(), tight.size()) == 0,
          "and one byte less writes nothing — the size is pinned, not guessed");
    printf("    worst-case checkpoint %u B of %u B\n", (unsigned)w, (unsigned)sizeof(buf));
  }
}

// =======================================================================================
// 5. the whole protocol, against a stand-in store, with failures injected
// =======================================================================================
struct Rec {
  int16_t lat, lon;
  std::string text;
};

struct Store {
  std::vector<Rec> recs;
  size_t appends = 0;
  void append(int16_t lat, int16_t lon, const std::string& t) {
    recs.push_back(Rec{lat, lon, t});
    ++appends;
  }
  void cut(const Cut* c, uint8_t n) {
    std::vector<Rec> keep;
    for (size_t i = 0; i < recs.size(); ++i) {
      bool drop = false;
      for (uint8_t k = 0; k < n; ++k)
        if (recs[i].lat == c[k].lat && recs[i].lon >= c[k].lon_lo && recs[i].lon <= c[k].lon_hi)
          drop = true;
      if (!drop) keep.push_back(recs[i]);
    }
    recs.swap(keep);
  }
  size_t count(int16_t lat) const {
    size_t n = 0;
    for (size_t i = 0; i < recs.size(); ++i) n += recs[i].lat == lat;
    return n;
  }
};

static void scan(EpisodeRing& ring, const Store& s) {
  ring.resetScan();
  for (size_t i = 0; i < s.recs.size(); ++i) ring.observe(s.recs[i].lat, s.recs[i].lon);
}

// Exactly what the glue will do at boot. Returns false if the store is inconsistent.
static void bootFrom(const Store& s, Consolidator& c, EpisodeRing& ring, uint16_t cap,
                     uint16_t batch) {
  c.begin();
  ring.begin(cap, batch);
  scan(ring, s);
  if (ring.hasCheckpoint()) {
    CheckpointReader cr(c, ring.checkpointOrdinal());
    for (size_t i = 0; i < s.recs.size(); ++i)
      if (s.recs[i].lat == SEMANTIC_CARRIED_LANE) feedText(cr, s.recs[i].text);
    if (cr.found()) ring.setHorizon(cr.through());
  }
  int16_t from, through;
  if (ring.liveRun(from, through)) {
    EpisodeReader r(c);
    r.select(from, through, Consolidator::KEEPING);
    for (size_t i = 0; i < s.recs.size(); ++i)
      if (s.recs[i].lat == SEMANTIC_EPISODE_LANE) feedText(r, s.recs[i].text);
    r.finish();
  }
}

// A deterministic episode: 1-3 percepts over a small vocabulary, with repeats inside an
// episode (per-episode max), partials, and about one denial in five.
static uint32_t gRng = 12345;
static uint32_t rnd() { gRng = gRng * 1103515245u + 12345u; return (gRng >> 16) & 0x7fff; }
static std::vector<Percept> randomEpisode() {
  static const char* peers[] = {"0x00000100", "0x00000200", "0x00000300", "0x00000010"};
  static const char* protos[] = {"espnow", "ble"};
  std::vector<Percept> ps;
  int n = 1 + (int)(rnd() % 3);
  for (int i = 0; i < n; ++i)
    ps.push_back(mk((uint32_t)(i + 1), peers[rnd() % 4], "link_stable", protos[rnd() % 2],
                    (rnd() % 5 == 0) ? POL_MINUS : POL_PLUS, (rnd() % 4 == 0) ? Q_SOME : Q_NONE));
  return ps;
}

struct Faults {
  int commit_fail_every;   // 0 = never; else every Nth commit attempt fails
  int cut_fail_every;      // 0 = never; else every Nth cut attempt fails
};

static void runProtocol(const char* name, uint16_t cap, uint16_t batch, int episodes,
                        Faults f, int16_t start_horizon /* -1 = fresh lane */,
                        uint16_t slack = 0 /* cut when dead() >= slack; 0 = always */) {
  printf("protocol: %s\n", name);
  Store s;
  if (start_horizon >= 0) {
    // A lane that has already been cut down to nothing behind this horizon: the only
    // way to start ordinals near the wrap without writing 32k episodes first.
    Consolidator empty; empty.begin();
    static char ckbuf[SEMANTIC_CARRIED_BUF];
    size_t n = renderCheckpoint(empty, start_horizon, 0, 0, ckbuf, sizeof(ckbuf));
    s.append(SEMANTIC_CARRIED_LANE, 0, std::string(ckbuf, n));
  }

  Consolidator node, ref;
  EpisodeRing ring;
  bootFrom(s, node, ring, cap, batch);
  ref.begin();

  int commits = 0, cuts = 0, failed_commits = 0, failed_cuts = 0;
  bool agree_live = true, agree_boot = true, bounded = true, wrapped = false;
  bool dead_exact = true;
  uint16_t max_present = 0;
  size_t max_records = 0;
  static char ckbuf[SEMANTIC_CARRIED_BUF];

  for (int e = 0; e < episodes; ++e) {
    std::vector<Percept> ps = randomEpisode();
    const int16_t ord = ring.nextOrdinal();
    if (ord < 100 && e > 0 && start_horizon > 30000) wrapped = true;
    std::string text = record(SEMANTIC_EPISODE_LANE, ord, ps);

    // APPEND — never refused.
    s.append(SEMANTIC_EPISODE_LANE, ord, text);
    ring.appended(ord);
    {
      EpisodeReader r(node);
      r.select(ord, ord, Consolidator::KEEPING);
      feedText(r, text);
      r.finish();
    }
    ref.beginEpisode();
    for (size_t i = 0; i < ps.size(); ++i) ref.percept(ps[i]);
    ref.endEpisode(Consolidator::KEEPING);

    // 1. FOLD
    int16_t from, through;
    if (ring.foldDue(from, through)) {
      EpisodeReader r(node);
      r.select(from, through, Consolidator::EVICTING);
      for (size_t i = 0; i < s.recs.size(); ++i)
        if (s.recs[i].lat == SEMANTIC_EPISODE_LANE) feedText(r, s.recs[i].text);
      r.finish();
      ring.folded(through);
    }
    // 2. COMMIT
    if (ring.commitDue()) {
      ++commits;
      if (f.commit_fail_every && commits % f.commit_fail_every == 0) {
        ++failed_commits;                    // the append failed: RAM ahead of flash
      } else {
        const int16_t ck = ring.nextCheckpointOrdinal();
        size_t n = renderCheckpoint(node, ring.ramHorizon(), ck, (uint32_t)e, ckbuf, sizeof(ckbuf));
        if (n == 0) { check(false, "a checkpoint failed to RENDER"); return; }
        s.append(SEMANTIC_CARRIED_LANE, ck, std::string(ckbuf, n));
        ring.checkpointAppended(ck);
      }
    }
    // 3. CUT
    Cut cs[4];
    const uint16_t dead_before = ring.dead();
    uint8_t nc = (dead_before >= slack) ? ring.cuts(cs, 4) : 0;
    if (nc) {
      ++cuts;
      if (f.cut_fail_every && cuts % f.cut_fail_every == 0) {
        ++failed_cuts;                       // the heap refused the rewrite
      } else {
        const size_t before = s.recs.size();
        s.cut(cs, nc);
        if (before - s.recs.size() != dead_before) dead_exact = false;
        scan(ring, s);                       // Ttdb re-indexes after a rewrite
      }
    }

    if (ring.present() > max_present) max_present = ring.present();
    if (s.recs.size() > max_records) max_records = s.recs.size();
    if (ring.live() > cap) bounded = false;

    if (beliefs(node) != beliefs(ref)) agree_live = false;
    // GATE 3 — reboot from the store alone, right now.
    Consolidator boot;
    EpisodeRing bring;
    bootFrom(s, boot, bring, cap, batch);
    if (beliefs(boot) != beliefs(ref)) {
      if (agree_boot) printf("    first disagreement after episode %d\n", e);
      agree_boot = false;
    }
  }

  check(s.count(SEMANTIC_EPISODE_LANE) <= s.appends, "sanity");
  check((int)s.appends >= episodes, "GATE 1: every episode offered was appended — none refused");
  check(agree_live, "GATE 2: the node's beliefs equal the never-evicting reference at EVERY step");
  check(agree_boot, "GATE 3: a reboot from the store alone agrees at EVERY step");
  check(node.foldUnderflow() == 0 && node.refused() == 0,
        "no fold underflow, no refusal — the replay matched what was counted");
  if (!f.commit_fail_every) check(bounded, "GATE 4: the live window never exceeded capacity");
  check(s.count(SEMANTIC_CARRIED_LANE) <= (size_t)(f.cut_fail_every ? 64 : 2),
        "superseded checkpoints are cut, not accumulated");
  if (start_horizon > 30000) check(wrapped, "GATE 6: the run actually crossed the wrap");
  check(dead_exact, "dead() predicts exactly how many records each cut removes");
  if (!f.commit_fail_every && !f.cut_fail_every)
    check(max_records <= (size_t)cap + batch + (slack ? slack : 1) + 2,
          "the tier's index footprint stays near capacity + batch + slack");
  printf("    %d episodes, %u folded, %d commits (%d failed), %d cuts (%d failed), "
         "max %u episode records on flash, %u now, peak %u records in the tier\n",
         episodes, (unsigned)ring.folds(), commits, failed_commits, cuts, failed_cuts,
         (unsigned)max_present, (unsigned)ring.present(), (unsigned)max_records);
}

// =======================================================================================
// 6. the link tier as episodes, and the exact checkpoint size
// =======================================================================================
static void testLink() {
  printf("link\n");
  LinkClaim k[3] = {
    {0x200, "ble", LINK_MET, -40, -38},
    {0x10, "espnow", LINK_VIOLATED, -50, -71},
    {0x100, "espnow", LINK_UNOBSERVED, -60, 0},
  };
  static char buf[SEMANTIC_LINK_EPISODE_BUF];
  size_t n = renderLinkEpisode(k, 3, 4, 77, "t_ms:77 stream:0x00000000 wall:0", buf, sizeof(buf));
  checkStr(std::string(buf, n),
           "\n---\n\n@LAT103LON4 | created:77 | updated:77\n\n**link window**\n\n"
           "```ttdb-episode\nsource: perceptlearn\nat: t_ms:77 stream:0x00000000 wall:0\n"
           "said: 1 | 0x00000200 ble met predicted:-40 observed:-38\n"
           "percept: 1 | 0x00000200 | link_stable | ble | + | -\n"
           "said: 2 | 0x00000010 espnow violated predicted:-50 observed:-71\n"
           "percept: 2 | 0x00000010 | link_stable | espnow | - | -\n"
           "said: 3 | 0x00000100 espnow unobserved predicted:-60 observed:0\n"
           "percept: 3 | 0x00000100 | link_stable | espnow | ? | -\n```\n",
           "a scored link window renders as one episode, one sentence per claim");

  Consolidator c; c.begin();
  EpisodeReader r(c);
  r.select(4, 4, Consolidator::KEEPING);
  feedText(r, std::string(buf, n));
  r.finish();
  const Term* met = c.find("0x00000200", "link_stable", "ble");
  const Term* vio = c.find("0x00000010", "link_stable", "espnow");
  const Term* un  = c.find("0x00000100", "link_stable", "espnow");
  check(met && met->totalFor() == 2 && met->totalAgainst() == 0, "met reads back as one vote FOR");
  check(vio && vio->totalFor() == 0 && vio->totalAgainst() == 2, "violated as one vote AGAINST");
  check(un && un->totalFor() == 0 && un->totalAgainst() == 0 && un->seen == 1,
        "unobserved is HELD: seen, never believed — as Rule 3 and the comparison treat it");

  // The fleet's worst case: PERCEPTLEARN_MAX_CLAIMS (8) claims of maximal width.
  LinkClaim w[8];
  for (int i = 0; i < 8; ++i)
    w[i] = LinkClaim{0xFFFFFFF0u + (uint32_t)i, "espnow", LINK_UNOBSERVED, -32768, -32768};
  size_t wn = renderLinkEpisode(w, 8, 32767, 4294967295u,
                                "t_ms:18446744073709551615 stream:0xffffffff wall:1", buf,
                                sizeof(buf));
  check(wn > 0, "eight maximal claims fit SEMANTIC_LINK_EPISODE_BUF");
  printf("    worst-case link episode %u B of %u B\n", (unsigned)wn, (unsigned)sizeof(buf));

  // checkpointBytes is what the glue allocates; it must equal what renderCheckpoint writes.
  for (int e = 0; e < 6; ++e) {
    c.beginEpisode();
    c.percept(mk(1, "0x00000300", "link_stable", "ble", e % 3 ? POL_PLUS : POL_MINUS,
                 e % 2 ? Q_SOME : Q_NONE));
    c.endEpisode(Consolidator::KEEPING);
  }
  for (int e = 0; e < 3; ++e) {
    c.beginEpisode();
    c.percept(mk(1, "0x00000300", "link_stable", "ble", e % 3 ? POL_PLUS : POL_MINUS,
                 e % 2 ? Q_SOME : Q_NONE));
    c.endEpisode(Consolidator::EVICTING);
  }
  static char ck[SEMANTIC_CARRIED_BUF];
  const int16_t throughs[] = {0, 9, 32767};
  bool same = true;
  for (int i = 0; i < 3; ++i) {
    const int16_t ord = (int16_t)(i * 7);
    const uint32_t t = (uint32_t)i * 1000003u;
    size_t want = checkpointBytes(c, throughs[i], ord, t);
    size_t got = renderCheckpoint(c, throughs[i], ord, t, ck, sizeof(ck));
    if (want != got || got == 0) same = false;
    std::vector<char> exact(want + 1);
    if (renderCheckpoint(c, throughs[i], ord, t, exact.data(), exact.size()) != want) same = false;
  }
  check(same, "checkpointBytes() equals renderCheckpoint()'s length, and want+1 bytes is enough");
}

// =======================================================================================
// 7. per-tier quotas: one lane, one band of LONs per tier, one checkpoint for all
// =======================================================================================
// =======================================================================================
// 6b. the entity tier as episodes: a sampler's own record, wrapped as `said:` sentences
// =======================================================================================
static timestream::Stamp entSt(uint64_t t_ms) {
  timestream::Stamp s;
  s.t_ms = t_ms;
  s.stream_id = 0x5EA51DE7u;
  s.wall = true;
  return s;
}

static std::vector<std::string> linesOf(const std::string& t) {
  std::vector<std::string> out;
  size_t a = 0;
  while (a < t.size()) {
    size_t b = t.find('\n', a);
    if (b == std::string::npos) b = t.size();
    out.push_back(t.substr(a, b - a));
    a = b + 1;
  }
  return out;
}

static void testEntityEpisode() {
  printf("entity\n");
  // The worst case test_entitypercept pins for ENTITYPERCEPT_RECORD_BUF: 12 entities a
  // window under a stable core, one fresh AP each window, so the covered union climbs
  // to ENTITYPERCEPT_MAX_UNION. Rendered at @LAT103 with the ENTITY band's ordinals, the
  // way the Cardputer renders it.
  entitypercept::Log lg;
  static char rec[ENTITYPERCEPT_RECORD_BUF];
  static char ep[SEMANTIC_ENTITY_EPISODE_BUF];
  uint32_t t = 0;
  size_t worst_rec = 0, worst_ep = 0, written = 0, covered = 0, said_lines = 0, longest = 0;
  bool all_ok = true, cites_103 = true, saw_covered = false, inplace_full_ok = true;
  size_t inplace_match = 0, inplace_refused = 0, inplace_corrupt = 0;
  size_t min_inplace_cap = (size_t)-1;
  int16_t ord = tierBand(TIER_ENTITY).base;
  for (int w = 0; w < 40; ++w) {
    for (int i = 0; i < ENTITYPERCEPT_MAX_ENTITIES - 1; ++i) {
      uint8_t ap[6] = {0x02, 0x00, 0x00, 0x00, 0x00, (uint8_t)i};
      lg.add(ap, -70 - i, entitypercept::KIND_WIFI_AP);
    }
    uint8_t rot[6] = {0x03, 0x00, 0x00, 0x00, 0x00, (uint8_t)w};
    lg.add(rot, -80, entitypercept::KIND_WIFI_AP);
    t += ENTITYPERCEPT_FLUSH_MS;
    const size_t m = lg.buildRecord(rec, sizeof(rec), ord, 1780000000 + t / 1000,
                                    entSt(1780000000000ULL + t), t, SEMANTIC_EPISODE_LANE);
    if (lg.lastClose() != entitypercept::CLOSE_WRITTEN) { ++covered; continue; }
    if (m > worst_rec) worst_rec = m;
    const std::string r(rec, m);
    if (r.find("@LAT96") != std::string::npos) cites_103 = false;
    if (r.find("**COVERED** ") != std::string::npos) saw_covered = true;
    const size_t n = renderSaidEpisode(rec, m, ord, 1780000000 + t / 1000, "entity window",
                                       "entitypercept", "1234 +-5 frame:9", ep, sizeof(ep));
    if (!n) { all_ok = false; continue; }
    ++written;
    if (n > worst_ep) worst_ep = n;
    // Every `**` line of the record is one `said:` line, in order, and nothing else is.
    std::vector<std::string> body, said;
    for (const std::string& l : linesOf(r))
      if (l.compare(0, 2, "**") == 0) body.push_back(l);
    for (const std::string& l : linesOf(std::string(ep, n))) {
      if (l.compare(0, 6, "said: ") == 0) {
        said.push_back(l.substr(l.find(" | ") + 3));
        if (l.size() > longest) longest = l.size();
      }
      if (l.compare(0, 8, "percept:") == 0) all_ok = false;
    }
    said_lines += said.size();
    if (said != body) all_ok = false;

    // IN PLACE, the way the Cardputer does it (one scratch buffer, EpisodeNode::scratch()).
    // The property is "refuse or match, never anything else": sweep every cap from just
    // past the record to the scratch size, and each result must be 0 or byte-identical
    // to the out-of-place render.
    static char sc[SEMANTIC_ENTITY_EPISODE_BUF];
    for (size_t cap = m + 1; cap <= sizeof(sc); ++cap) {
      memcpy(sc, rec, m);
      const size_t k = renderSaidEpisodeInPlace(sc, cap, m, ord, 1780000000 + t / 1000,
                                                "entity window", "entitypercept",
                                                "1234 +-5 frame:9");
      if (k == 0) { ++inplace_refused; continue; }
      if (k != n || memcmp(sc, ep, n) != 0) ++inplace_corrupt;
      else ++inplace_match;
      if (cap == sizeof(sc) && (k != n || memcmp(sc, ep, n) != 0)) inplace_full_ok = false;
      if (cap < min_inplace_cap) min_inplace_cap = cap;
    }
    ord = bandAdd(ord, 1, tierBand(TIER_ENTITY));
  }
  check(inplace_corrupt == 0, "in place: every cap either REFUSES or matches byte-for-byte "
                              "— never a corrupted record");
  check(inplace_refused > 0 && inplace_match > 0,
        "and the sweep exercised both outcomes (the guard fired, and it did not over-refuse)");
  check(inplace_full_ok, "at the real scratch size every worst-case record wraps in place");
  printf("    in place: %u match, %u refused, 0 corrupt required (got %u); smallest cap that "
         "wrapped %u B\n",
         (unsigned)inplace_match, (unsigned)inplace_refused, (unsigned)inplace_corrupt,
         (unsigned)min_inplace_cap);
  check(written > 3 && covered > 3, "the wide-union walk both wrote and covered windows");
  check(saw_covered, "and at least one record carried a COVERED union");
  check(all_ok, "every written record wraps: each `**` line is one `said:` line, in order, "
                "and no `percept:` line is emitted");
  check(cites_103, "with lane_lat 103 the header AND `covered_by:` name @LAT103, never @LAT96");
  check(longest < SEMANTIC_LINE_MAX,
        "every `said:` line comes back through the on-device line reader intact");
  check(worst_ep <= SEMANTIC_ENTITY_EPISODE_BUF, "worst entity episode FITS its buffer");
  check(worst_ep > ENTITYPERCEPT_RECORD_BUF,
        "and does NOT fit ENTITYPERCEPT_RECORD_BUF: the wrap costs real bytes, so reusing "
        "the record's own buffer would drop exactly the union-carrying windows");
  printf("    worst entity record %u B, its episode %u B of %u B, longest said line %u B, "
         "%u said lines over %u episodes\n",
         (unsigned)worst_rec, (unsigned)worst_ep, (unsigned)SEMANTIC_ENTITY_EPISODE_BUF,
         (unsigned)longest, (unsigned)said_lines, (unsigned)written);

  // An entity episode feeds the consolidator NOTHING: an episode is read, no term forms.
  {
    entitypercept::Log l2;
    uint8_t ap[6] = {1, 2, 3, 4, 5, 6};
    l2.add(ap, -50, entitypercept::KIND_WIFI_AP);
    const size_t m = l2.buildRecord(rec, sizeof(rec), 8200, 1, entSt(1000), 60000,
                                    SEMANTIC_EPISODE_LANE);
    const size_t k = renderSaidEpisode(rec, m, 8200, 1, "entity window", "entitypercept", "x",
                                       ep, sizeof(ep));
    check(m > 0 && k > 0, "a one-AP window renders as an episode");
    check(tierOf(8200) == TIER_ENTITY, "LON 8200 is the entity tier's");
    Consolidator c; c.begin();
    EpisodeReader r(c);
    r.select(8200, 8200, Consolidator::KEEPING, tierBand(TIER_ENTITY));
    feedText(r, std::string(ep, k));
    r.finish();
    check(r.fed() == 1 && c.termCount() == 0 && c.malformedCount() == 0,
          "read back KEEPING: one episode fed, zero terms, zero malformed");
  }

  // Refusals: never a truncated or reinterpreted record.
  {
    const char* piped = "\n---\n\n@LAT103LON8192 | x\n\n**ENTWIN** a|b\n";
    check(renderSaidEpisode(piped, strlen(piped), 8192, 1, "e", "s", "x", ep, sizeof(ep)) == 0,
          "a `**` line holding `|` refuses the episode (it would read back as another sentence)");
    const char* none = "\n---\n\n@LAT103LON8192 | x\n\nplain text\n";
    check(renderSaidEpisode(none, strlen(none), 8192, 1, "e", "s", "x", ep, sizeof(ep)) == 0,
          "a body with no `**` line is no episode");
    std::string longl = "**CORE** ids:" + std::string(SEMANTIC_LINE_MAX, 'a') + "\n";
    check(renderSaidEpisode(longl.c_str(), longl.size(), 8192, 1, "e", "s", "x", ep,
                            sizeof(ep)) == 0,
          "a line too long for the on-device reader refuses the episode");
    const char* ok = "**ENTWIN** t_ms:1\n**ENTITY** kind:wifi_ap id:010203040506 n:1 rssi:-50\n";
    char tiny[120];
    check(renderSaidEpisode(ok, strlen(ok), 8192, 1, "e", "s", "x", tiny, sizeof(tiny)) == 0 &&
              tiny[0] == '\0',
          "no room is 0 bytes and an empty buffer, never a partial record");
  }
}

// =======================================================================================
// 6c. the acoustic tier as episodes — and AcousticPercept's first native test
// =======================================================================================
static void testAcousticEpisode() {
  printf("acoustic\n");
  // Widest record the builder can emit: maximal header numbers, a maximal stamp (twice:
  // the window's and the transient's), full-scale samples so the levels are as wide as
  // a 16-bit mic allows, and a transient so the **TRANSIENT** line is present.
  acousticpercept::Log lg;
  int16_t quiet[128], loud[128];
  for (int i = 0; i < 128; ++i) {
    quiet[i] = (int16_t)((i & 1) ? 120 : -120);
    loud[i] = (int16_t)((i & 1) ? 32767 : -32768);
  }
  const uint64_t big = 18446744073709551000ULL;
  uint32_t now = 0;
  for (int b = 0; b < 40; ++b) { lg.addBlock(quiet, 128, big + b, now); now += 16; }
  lg.addBlock(loud, 128, big + 99, now);
  now += 16;
  check(lg.transients() > 0, "a full-scale block after a quiet run counts as a transient");
  timestream::Stamp st;
  st.t_ms = big;
  st.stream_id = 0xffffffffu;
  st.wall = true;
  static char rec[ACOUSTICPERCEPT_RECORD_BUF];
  const size_t m = lg.buildRecord(rec, sizeof(rec), 32767, 4294967295u, st,
                                  now + ACOUSTICPERCEPT_FLUSH_MS, 4294967295u);
  const std::string r(rec, m);
  check(m > 0 && m < ACOUSTICPERCEPT_RECORD_BUF, "the widest acoustic record fits its buffer");
  check(r.find("**TRANSIENT** ") != std::string::npos,
        "with its **TRANSIENT** line — the line an undersized buffer silently drops");
  printf("    widest acoustic record %u B of %u B\n", (unsigned)m,
         (unsigned)ACOUSTICPERCEPT_RECORD_BUF);

  // Wrapped in place in the episode scratch, at the ACOUSTIC tier's first ordinal.
  static char sc[SEMANTIC_ENTITY_EPISODE_BUF];
  const int16_t ord = tierBand(TIER_ACOUSTIC).base;
  memcpy(sc, rec, m);
  const size_t n = renderSaidEpisodeInPlace(sc, sizeof(sc), m, ord, 4294967295u,
                                            "acoustic window", "acousticpercept",
                                            "1234 +-5 frame:9");
  check(n > 0 && tierOf(ord) == TIER_ACOUSTIC, "it wraps in place as an acoustic-tier episode");
  std::vector<std::string> body, said;
  for (const std::string& l : linesOf(r))
    if (l.compare(0, 2, "**") == 0) body.push_back(l);
  bool no_percept = true;
  for (const std::string& l : linesOf(std::string(sc, n))) {
    if (l.compare(0, 6, "said: ") == 0) said.push_back(l.substr(l.find(" | ") + 3));
    if (l.compare(0, 8, "percept:") == 0) no_percept = false;
  }
  check(said == body && body.size() == 3 && no_percept,
        "ACOUSTICWIN, ACOUSTIC and TRANSIENT each become one said: line; no percept: line");
}

static void testBands() {
  printf("bands\n");
  const Band e = tierBand(TIER_ENTITY);
  check(e.base == 8192 && e.span == 8192, "tier 1 owns [8192, 16384)");
  check(tierOf(0) == TIER_LINK && tierOf(8191) == TIER_LINK && tierOf(8192) == TIER_ENTITY &&
        tierOf(32767) == TIER_ACOUSTIC && tierOf(-1) == -1, "tierOf reads the band off a LON");
  check(bandAdd(16383, 1, e) == 8192, "a band wraps to its own base, not to the next tier");
  check(bandAdd(8192, -1, e) == 16383, "and backwards to its own top");
  check(bandDistance(16380, 8195, e) == 7, "distance across a band's wrap is the short way");
  check(bandInRun(8193, 16382, 8194, e), "a run wrapping inside the band contains its tail");
  check(!bandInRun(16381, 16382, 8194, e), "but not one before its start");
  check(!bandInRun(5, 16382, 8194, e), "and never a LON of another tier");
  check(ordinalAdd(32767, 1) == 0 && ordinalInRun(2, 32766, 4),
        "the whole-lane helpers are the band {0, 32768}");
}

static void testTierCheckpoint() {
  printf("tier checkpoint\n");
  Consolidator c; c.begin();
  c.beginEpisode(); c.percept(mk(1, "0x00000100", "link_stable", "espnow", POL_PLUS, Q_NONE));
  c.endEpisode(Consolidator::EVICTING);
  static char buf[SEMANTIC_CARRIED_BUF];
  const int16_t hs[] = {143, 8231, 24600};
  size_t n = renderCheckpoint(c, hs, 3, 7, 0, buf, sizeof(buf));
  check(n > 0, "a three-tier checkpoint renders");
  check(std::string(buf, n).find("through: 143\nthrough: 8231\nthrough: 24600\n") !=
            std::string::npos, "one through: line per tier, in the order given");
  {
    Consolidator back; back.begin();
    CheckpointReader cr(back, 7);
    feedText(cr, std::string(buf, n));
    check(cr.has(TIER_LINK) && cr.through(TIER_LINK) == 143, "link horizon read back");
    check(cr.has(TIER_ENTITY) && cr.through(TIER_ENTITY) == 8231, "entity horizon read back");
    check(!cr.has(TIER_MOTION), "a tier that never folded has no horizon");
    check(cr.has(TIER_ACOUSTIC) && cr.through(TIER_ACOUSTIC) == 24600, "acoustic horizon");
    check(cr.malformed() == 0 && cr.seeded() == 1, "and the carried tally with it");
  }
  const int16_t dup[] = {143, 150};
  check(renderCheckpoint(c, dup, 2, 7, 0, buf, sizeof(buf)) == 0,
        "two horizons in ONE band are refused at render time");
  {
    // A hand-written store with two horizons for one tier: first kept, second counted.
    const std::string bad =
        "@LAT104LON3 | created:0 | updated:0\n\n```ttdb-carried\nthrough: 10\nthrough: 12\n```\n";
    Consolidator back; back.begin();
    CheckpointReader cr(back, 3);
    feedText(cr, bad);
    check(cr.through(TIER_LINK) == 10 && cr.malformed() == 1,
          "a second horizon for one tier is malformed and the first is kept");
  }
  {
    // The Cardputer's on-flash checkpoint today: one through:, pre-band. It is the link's.
    const std::string old =
        "@LAT104LON2 | created:0 | updated:0\n\n```ttdb-carried\nthrough: 143\n"
        "carried: 141 2 499 9 | 0x00000200 | link_stable | ble\n```\n";
    Consolidator back; back.begin();
    CheckpointReader cr(back, 2);
    feedText(cr, old);
    EpisodeTiers t; t.begin();
    t.observe(SEMANTIC_CARRIED_LANE, 2);
    for (int16_t o = 100; o <= 150; ++o) t.observe(SEMANTIC_EPISODE_LANE, o);
    t.applyCheckpoint(cr);
    check(t.ring(TIER_LINK).hasHorizon() && t.ring(TIER_LINK).flashHorizon() == 143 &&
              !t.ring(TIER_ENTITY).hasHorizon(),
          "a pre-band checkpoint's single horizon lands on the link tier only");
    check(t.ring(TIER_LINK).live() == 7 && t.live() == 7,
          "and the existing episodes LON 100..150 are link episodes, 7 of them live");
  }
}

struct TierFaults {
  int commit_fail_every;
  int cut_fail_every;
};

static void bootTiers(const Store& s, Consolidator& c, EpisodeTiers& t, const uint16_t* q,
                      uint16_t batch) {
  c.begin();
  t.begin(q, batch);
  t.resetScan();
  for (size_t i = 0; i < s.recs.size(); ++i) t.observe(s.recs[i].lat, s.recs[i].lon);
  if (t.hasCheckpoint()) {
    CheckpointReader cr(c, t.checkpointOrdinal());
    for (size_t i = 0; i < s.recs.size(); ++i)
      if (s.recs[i].lat == SEMANTIC_CARRIED_LANE) feedText(cr, s.recs[i].text);
    t.applyCheckpoint(cr);
  }
  for (uint8_t k = 0; k < SEMANTIC_TIERS; ++k) {
    int16_t from, through;
    if (!t.ring(k).liveRun(from, through)) continue;
    EpisodeReader r(c);
    r.select(from, through, Consolidator::KEEPING, t.ring(k).band());
    for (size_t i = 0; i < s.recs.size(); ++i)
      if (s.recs[i].lat == SEMANTIC_EPISODE_LANE) feedText(r, s.recs[i].text);
    r.finish();
  }
}

// `rate[k]`: tier k's share of appends (link busy, entity slow). `entity_start`: if ≥ 0, a
// store whose entity band was already cut down behind this horizon — to cross ITS wrap.
static void runTierProtocol(const char* name, const uint16_t* q, uint16_t batch, int episodes,
                            TierFaults f, int16_t entity_start, uint16_t slack) {
  printf("tier protocol: %s\n", name);
  static const int rate[SEMANTIC_TIERS] = {12, 1, 3, 2};
  int rate_sum = 0;
  for (int k = 0; k < SEMANTIC_TIERS; ++k) rate_sum += rate[k];

  Store s;
  if (entity_start >= 0) {
    Consolidator empty; empty.begin();
    static char ckb[SEMANTIC_CARRIED_BUF];
    size_t n = renderCheckpoint(empty, entity_start, 0, 0, ckb, sizeof(ckb));
    s.append(SEMANTIC_CARRIED_LANE, 0, std::string(ckb, n));
  }
  Consolidator node, ref;
  EpisodeTiers tiers;
  bootTiers(s, node, tiers, q, batch);
  ref.begin();

  int appended[SEMANTIC_TIERS] = {0, 0, 0, 0};
  int commits = 0, cuts = 0, failed_commits = 0, failed_cuts = 0;
  bool agree_live = true, agree_boot = true, bounded = true, protected_ = true;
  bool dead_exact = true, entity_wrapped = false, left_band = false;
  size_t max_records = 0;
  static char ckbuf[SEMANTIC_CARRIED_BUF];

  for (int e = 0; e < episodes; ++e) {
    int pick = (int)(rnd() % (uint32_t)rate_sum);
    uint8_t tier = 0;
    while (pick >= rate[tier]) pick -= rate[tier++];
    std::vector<Percept> ps = randomEpisode();
    const int16_t ord = tiers.nextOrdinal(tier);
    if (tier == TIER_ENTITY && entity_start >= 0 && ord < entity_start) entity_wrapped = true;
    if (tierOf(ord) != tier) left_band = true;
    const std::string text = record(SEMANTIC_EPISODE_LANE, ord, ps);
    s.append(SEMANTIC_EPISODE_LANE, ord, text);
    tiers.appended(ord);
    ++appended[tier];
    {
      EpisodeReader r(node);
      r.select(ord, ord, Consolidator::KEEPING, tierBand(tier));
      feedText(r, text);
      r.finish();
    }
    ref.beginEpisode();
    for (size_t i = 0; i < ps.size(); ++i) ref.percept(ps[i]);
    ref.endEpisode(Consolidator::KEEPING);

    // 1. FOLD — every tier that is over its quota, one at a time.
    uint8_t ft;
    int16_t from, through;
    while (tiers.foldDue(ft, from, through)) {
      EpisodeReader r(node);
      r.select(from, through, Consolidator::EVICTING, tiers.ring(ft).band());
      for (size_t i = 0; i < s.recs.size(); ++i)
        if (s.recs[i].lat == SEMANTIC_EPISODE_LANE) feedText(r, s.recs[i].text);
      r.finish();
      tiers.folded(ft, through);
    }
    // 2. COMMIT — every tier's horizon, every time.
    if (tiers.commitDue()) {
      ++commits;
      if (f.commit_fail_every && commits % f.commit_fail_every == 0) {
        ++failed_commits;
      } else {
        int16_t hs[SEMANTIC_TIERS];
        const uint8_t nh = tiers.horizons(hs);
        const int16_t ck = tiers.nextCheckpointOrdinal();
        size_t n = renderCheckpoint(node, hs, nh, ck, (uint32_t)e, ckbuf, sizeof(ckbuf));
        if (n == 0) { check(false, "a multi-tier checkpoint failed to RENDER"); return; }
        s.append(SEMANTIC_CARRIED_LANE, ck, std::string(ckbuf, n));
        tiers.checkpointAppended(ck);
      }
    }
    // 3. CUT
    Cut cs[SEMANTIC_TIER_CUTS_MAX];
    const uint16_t dead_before = tiers.dead();
    const uint8_t nc = (dead_before >= slack) ? tiers.cuts(cs, SEMANTIC_TIER_CUTS_MAX) : 0;
    if (nc) {
      ++cuts;
      if (f.cut_fail_every && cuts % f.cut_fail_every == 0) {
        ++failed_cuts;
      } else {
        const size_t before = s.recs.size();
        s.cut(cs, nc);
        if (before - s.recs.size() != dead_before) dead_exact = false;
        tiers.resetScan();
        for (size_t i = 0; i < s.recs.size(); ++i) tiers.observe(s.recs[i].lat, s.recs[i].lon);
      }
    }

    if (s.recs.size() > max_records) max_records = s.recs.size();
    for (uint8_t k = 0; k < SEMANTIC_TIERS; ++k) {
      const uint16_t lv = tiers.ring(k).live();
      if (lv > q[k]) bounded = false;
      // THE QUOTA CLAIM: a tier keeps its own window however busy the others are.
      const int floor_k = appended[k] < (int)(q[k] - batch) ? appended[k] : (int)(q[k] - batch);
      if ((int)lv < floor_k) {
        if (protected_) printf("    tier %u held %u live, expected >= %d, at episode %d\n",
                               (unsigned)k, (unsigned)lv, floor_k, e);
        protected_ = false;
      }
    }
    if (beliefs(node) != beliefs(ref)) agree_live = false;
    Consolidator boot;
    EpisodeTiers bt;
    bootTiers(s, boot, bt, q, batch);
    if (beliefs(boot) != beliefs(ref)) {
      if (agree_boot) printf("    first disagreement after episode %d (tier %u)\n", e, tier);
      agree_boot = false;
    }
  }

  check(!left_band, "nextOrdinal never left its tier's band");
  check((int)s.appends >= episodes, "GATE 1 (tiers): every episode appended — none refused");
  check(agree_live, "GATE 2 (tiers): beliefs equal the never-evicting reference at every step");
  check(agree_boot, "GATE 3 (tiers): a reboot from the store alone agrees at every step");
  check(node.foldUnderflow() == 0 && node.refused() == 0, "no fold underflow, no refusal");
  check(bounded, "GATE 4 (tiers): no tier's live window exceeded its own quota");
  check(protected_, "GATE 7: no tier was evicted by another — each keeps min(appended, quota-batch)");
  check(dead_exact, "dead() predicts exactly how many records each multi-tier cut removes");
  if (entity_start >= 0) check(entity_wrapped, "GATE 6 (tiers): the entity band crossed its wrap");
  if (!f.commit_fail_every && !f.cut_fail_every)
    check(max_records <= (size_t)tiers.capacity() + SEMANTIC_TIERS * (batch + 1) +
                         (slack ? slack : 1) + 2,
          "the tier set's footprint stays near Σquota + batch per tier + slack");
  printf("    %d episodes (link %d entity %d motion %d acoustic %d), %u folded, %d commits "
         "(%d failed), %d cuts (%d failed), peak %u records\n",
         episodes, appended[0], appended[1], appended[2], appended[3],
         (unsigned)tiers.folds(), commits, failed_commits, cuts, failed_cuts,
         (unsigned)max_records);
}

int main() {
  testOrdinals();
  testLink();
  testEntityEpisode();
  testAcousticEpisode();
  testBuilder();
  testReader();
  testCheckpoint();
  testBands();
  testTierCheckpoint();

  Faults none = {0, 0};
  Faults cutsFail = {0, 2};          // every other rewrite refused, as with radios up
  Faults commitsFail = {3, 0};       // every third checkpoint append fails
  Faults both = {3, 2};
  runProtocol("clean", 8, 3, 300, none, -1);
  runProtocol("cuts refused half the time", 8, 3, 300, cutsFail, -1);
  runProtocol("commits fail one in three", 8, 3, 300, commitsFail, -1);
  runProtocol("both", 8, 3, 300, both, -1);
  runProtocol("batch 1", 5, 1, 120, none, -1);
  runProtocol("across the 32768 wrap", 8, 3, 200, both, 32700);
  runProtocol("fleet constants", SEMANTIC_RING_CAPACITY, SEMANTIC_EVICT_BATCH, 400, cutsFail, -1);
  runProtocol("fleet constants, cut at slack", SEMANTIC_RING_CAPACITY, SEMANTIC_EVICT_BATCH,
              400, none, -1, SEMANTIC_CUT_SLACK);
  runProtocol("slack, both faults, across the wrap", 8, 3, 300, both, 32700, 5);

  const uint16_t small[SEMANTIC_TIERS] = {8, 5, 4, 4};
  const uint16_t fleet[SEMANTIC_TIERS] = {SEMANTIC_QUOTA_LINK, SEMANTIC_QUOTA_ENTITY,
                                          SEMANTIC_QUOTA_MOTION, SEMANTIC_QUOTA_ACOUSTIC};
  runTierProtocol("clean", small, 2, 400, TierFaults{0, 0}, -1, 0);
  runTierProtocol("both faults", small, 2, 400, TierFaults{3, 2}, -1, 0);
  runTierProtocol("slack, both faults, entity across its band wrap", small, 2, 500,
                  TierFaults{3, 2}, 16370, 5);
  runTierProtocol("fleet quotas, cut at slack", fleet, SEMANTIC_EVICT_BATCH, 1200,
                  TierFaults{0, 0}, -1, SEMANTIC_CUT_SLACK);

  printf("\n%d checks, %d failures\n", gChecks, gFails);
  return gFails ? 1 : 0;
}
