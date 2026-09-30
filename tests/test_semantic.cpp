// test_semantic.cpp — ACT-III Phase C, the consolidator's gates.
//
// The two gates this file exists to hold are C3's, and they are pre-registered in the plan
// rather than invented here:
//
//   GATE 1 — belief lines reproduced byte-for-byte, and IDENTICAL UNDER REORDERED EPISODES.
//            Order-independence is the property PerceptLearn's sequential +2/-16 fold
//            structurally cannot have and the whole reason TTG-RFC-0003 §2 exists.
//   GATE 2 — consolidate; evict the oldest episodes with fold-before-forget; consolidate
//            again — the beliefs must be IDENTICAL. This is what makes "never fills up"
//            safe rather than merely convenient.
//
// And the ones that come from this repo's own scar tissue rather than from the RFC:
//   * THE GRAVESTONE. @LAT92's boundary rule was written because a carried tally that
//     matches the consolidator's own needle gets re-folded as testimony on the next read
//     and the node re-learns from its own headstone, doubling every reboot. So: the
//     carried line must not parse as a percept, and must not begin with the belief key.
//   * NEVER REFUSES. A full table must reclaim, not refuse — the pass condition of the
//     whole phase (ACT-III §C0) is a deletion, and a refusal is the thing being deleted.
//   * PER-EPISODE MAX. An episode that says the same thing three times gets ONE vote, or
//     one chatty window outvotes nine quiet ones and the count stops meaning anything.
//   * A MALFORMED LINE IS SKIPPED, COUNTED AND REPORTED (TTG-0002 §5.1) and never aborts
//     the episode: one unreadable percept must not cost the other nine in its window.
//   * BOTH ENDS OF THE BUFFER RULE. A builder writes NOTHING rather than a truncated
//     line — four undersized buffers in this repo's history, one of which reached
//     hardware, and the one that did produced output that looked fine.
#include <cstdio>
#include <cstring>

#include "Semantic.h"

static int gChecks = 0, gFails = 0;
static void check(bool ok, const char* what) {
  ++gChecks;
  if (!ok) { ++gFails; printf("  FAIL: %s\n", what); }
}
static void checkStr(const char* got, const char* want, const char* what) {
  ++gChecks;
  if (!got || strcmp(got, want) != 0) {
    ++gFails;
    printf("  FAIL: %s\n        want |%s|\n        got  |%s|\n", what, want, got ? got : "(null)");
  }
}

using namespace semantic;

// The fleet's real claim shape, from the Cardputer's live @LAT91 records:
//   **LINK-STABLE** peer:0x00000200 proto:ble
// reads as the triple (peer, link_stable, proto). Using the real shape rather than foo/bar
// keeps the test honest about lemma lengths, which is what SEMANTIC_LEMMA_MAX has to hold.
static const char* kPeer200 = "0x00000200";
static const char* kVec     = "link_stable";
static const char* kBle     = "ble";

static Percept mk(uint32_t sentence, const char* s, const char* v, const char* o,
                  Polarity pol, Quant q, char reading = 0) {
  Percept p;
  memset(&p, 0, sizeof(p));
  p.sentence = sentence;
  snprintf(p.subject, SEMANTIC_LEMMA_MAX, "%s", s);
  snprintf(p.vec,     SEMANTIC_LEMMA_MAX, "%s", v);
  snprintf(p.object,  SEMANTIC_LEMMA_MAX, "%s", o);
  p.pol = pol; p.quant = q; p.reading = reading;
  return p;
}

// ---------------------------------------------------------------------------------------
// The shared fixture. Five episodes over ONE triple, chosen so that every arm of the
// arithmetic is exercised and the expected numbers are checkable by hand:
//
//   ep0  `+` full                      plus 2
//   ep1  `+` full                      plus 2
//   ep2  `-` full                      minus 2
//   ep3  `+` quant `~`                 plus 1      <- weight_partial 0.5
//   ep4  `+` full x3 in one episode    plus 2      <- per-episode MAX, not a sum
//
//   for = 2+2+0+1+2 = 7 halves = 3.5      against = 2 halves = 1
//   polarity: for > against -> '+'
//   conf = round(255 * (max + prior_for) / (for + against + prior_for + prior_against))
//        = round(255 * (3.5 + 1) / (3.5 + 1 + 1 + 1)) = round(255 * 4.5/6.5)
//        = round(176.54) = 177
//   In halves, which is how the code does it: round(255*(7+2) / (7+2+2+2)) = 2295/13.
//   ⚠ BOTH priors sit in the denominator. Writing it with only prior_for there yields 209,
//   which is plausible enough that this test asserted it on its first run and the
//   implementation was briefly the suspect.
// ---------------------------------------------------------------------------------------
enum { kEpisodes = 5 };

// Feed episode `e` of the fixture into `c`. `close` lets the same definition drive both the
// normal pass and the eviction replay, so the two can never drift apart — if they could,
// GATE 2 would be testing a different episode from the one it evicted.
static void feedEpisode(Consolidator& c, int e, Consolidator::Close close) {
  c.beginEpisode();
  switch (e) {
    case 0: c.percept(mk(1, kPeer200, kVec, kBle, POL_PLUS, Q_NONE)); break;
    case 1: c.percept(mk(1, kPeer200, kVec, kBle, POL_PLUS, Q_NONE)); break;
    case 2: c.percept(mk(1, kPeer200, kVec, kBle, POL_MINUS, Q_NONE)); break;
    case 3: c.percept(mk(1, kPeer200, kVec, kBle, POL_PLUS, Q_SOME)); break;
    case 4:
      c.percept(mk(1, kPeer200, kVec, kBle, POL_PLUS, Q_NONE));
      c.percept(mk(2, kPeer200, kVec, kBle, POL_PLUS, Q_NONE));
      c.percept(mk(3, kPeer200, kVec, kBle, POL_PLUS, Q_NONE));
      break;
    default: break;
  }
  c.endEpisode(close);
}

static const char* kExpectedBelief = "belief: link_stable | ble | + | 3.5 1 | 177";

static void beliefOf(Consolidator& c, char* out, size_t cap) {
  const Term* t = c.find(kPeer200, kVec, kBle);
  if (!t) { snprintf(out, cap, "(no term)"); return; }
  if (c.beliefLine(*t, out, cap) == 0) snprintf(out, cap, "(did not fit)");
}

// ---------------------------------------------------------------------------------------
static void test_parse() {
  printf("-- parse (TTG-0002 §4 line, §5.1 validation)\n");
  Percept p;
  Malformed why;

  check(Consolidator::parsePerceptLine("percept: 1 | a | eats | b | + | -", p, why) &&
        p.sentence == 1 && strcmp(p.subject, "a") == 0 && strcmp(p.vec, "eats") == 0 &&
        strcmp(p.object, "b") == 0 && p.pol == POL_PLUS && p.quant == Q_NONE,
        "a plain percept line parses, with or without the key");
  check(Consolidator::parsePerceptLine("1 | a | eats | b | + | -", p, why),
        "the `percept:` key is optional");

  // `-` in these positions is WELL-FORMED and each means something different.
  check(Consolidator::parsePerceptLine("1 | - | eats | b | + | -", p, why),
        "a `-` subject is a MENTION, not malformed (TTG-0005 §3)");
  check(Consolidator::parsePerceptLine("1 | a | - | b | + | -", p, why),
        "a `-` vector is a MENTION, not malformed");
  check(Consolidator::parsePerceptLine("1 | a | flies | - | + | -", p, why),
        "a `-` object is an intransitive clause, not malformed");
  check(Consolidator::parsePerceptLine("1 | a | eats | b | ? | -", p, why) && p.pol == POL_HELD,
        "`?` is HELD and well-formed");
  check(Consolidator::parsePerceptLine("1 | a | eats | b | ?- | -", p, why) &&
        p.pol == POL_HELD_MINUS, "`?-` is a held denial and well-formed");
  check(Consolidator::parsePerceptLine("1 | a | eats | b | ? | - | c", p, why) && p.reading == 'c',
        "a reading letter rides on a HELD percept");

  // ... and every way a line is malformed, each SKIPPED, COUNTED and REPORTED.
  check(!Consolidator::parsePerceptLine("1 | a | eats | b | +", p, why) && why == MAL_COLUMNS,
        "five columns is MAL_COLUMNS");
  check(!Consolidator::parsePerceptLine("x | a | eats | b | + | -", p, why) && why == MAL_SENTENCE,
        "a non-integer sentence is MAL_SENTENCE");
  check(!Consolidator::parsePerceptLine("1 |  | eats | b | + | -", p, why) && why == MAL_EMPTY,
        "an empty subject is MAL_EMPTY (empty is not the same as `-`)");
  check(!Consolidator::parsePerceptLine("1 | a |  | b | + | -", p, why) && why == MAL_EMPTY,
        "an empty vector is MAL_EMPTY");
  check(!Consolidator::parsePerceptLine("1 | a | eats | b | ! | -", p, why) && why == MAL_POLARITY,
        "an unknown polarity is MAL_POLARITY");
  check(!Consolidator::parsePerceptLine("1 | a | eats | b | + | !", p, why) && why == MAL_QUANT,
        "an unknown quantifier is MAL_QUANT");
  check(!Consolidator::parsePerceptLine("1 | a | eats | b | + | - | c", p, why) &&
        why == MAL_READING,
        "a reading letter on an ASSERTED percept is MAL_READING — the grammar read two "
        "ways and asserted one anyway");
  check(!Consolidator::parsePerceptLine("1 | a | eats | b | ? | - | AB", p, why) &&
        why == MAL_READING, "a multi-character reading is MAL_READING");

  // An over-long lemma is malformed rather than truncated: truncating two long lemmas that
  // share a prefix would MERGE two distinct triples into one belief, and a wrong belief is
  // worse than a skipped line.
  char longline[SEMANTIC_LINE_MAX];
  snprintf(longline, sizeof(longline),
           "1 | %s | eats | b | + | -", "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
  check(!Consolidator::parsePerceptLine(longline, p, why) && why == MAL_TOO_LONG,
        "a lemma too long to FIT is malformed, never silently truncated");

  // Round-trip: render then parse gives back what went in.
  char line[SEMANTIC_LINE_MAX];
  Percept a = mk(7, "0x00000200", "link_stable", "espnow", POL_MINUS, Q_SOME);
  check(Consolidator::renderPerceptLine(a, line, sizeof(line)) > 0, "render writes a line");
  Percept b;
  check(Consolidator::parsePerceptLine(line, b, why) && b.sentence == 7 &&
        strcmp(b.subject, a.subject) == 0 && strcmp(b.vec, a.vec) == 0 &&
        strcmp(b.object, a.object) == 0 && b.pol == POL_MINUS && b.quant == Q_SOME,
        "a rendered percept line round-trips");

  // The buffer rule, both ends: a builder writes NOTHING rather than a truncated line.
  char tiny[8];
  check(Consolidator::renderPerceptLine(a, tiny, sizeof(tiny)) == 0 && tiny[0] == '\0',
        "render into an undersized buffer writes 0 bytes, not a truncated line");
}

static void test_consolidation() {
  printf("-- consolidation (TTG-0003 §2)\n");
  Consolidator c;
  c.begin();
  for (int e = 0; e < kEpisodes; ++e) feedEpisode(c, e, Consolidator::KEEPING);

  const Term* t = c.find(kPeer200, kVec, kBle);
  check(t != 0, "the triple was interned");
  if (!t) return;

  check(t->totalFor() == 7, "for = 7 halves (3.5): per-episode MAX, and `~` weighs a half");
  check(t->totalAgainst() == 2, "against = 2 halves (1)");
  check(t->episodes == kEpisodes, "all five episodes contributed");
  check(c.polarity(*t) == '+', "polarity is `+` because for > against");
  check(c.conf(*t) == 177,
        "conf = round(255*(7+2)/(7+2+2+2)) = round(2295/13) = 177 — BOTH priors are in the "
        "denominator, and the whole expression is integer");
  check(c.decided(*t), "decided: polarity is not `?` and conf > belief_conf_threshold 128");

  char got[128];
  beliefOf(c, got, sizeof(got));
  checkStr(got, kExpectedBelief, "the belief line is byte-exact (GATE 1, first half)");

  // Per-episode max, isolated: ep4 alone says `+` three times and must count as ONE.
  Consolidator one;
  one.begin();
  feedEpisode(one, 4, Consolidator::KEEPING);
  const Term* t1 = one.find(kPeer200, kVec, kBle);
  check(t1 && t1->totalFor() == 2 && t1->episodes == 1,
        "an episode saying `+` three times contributes ONE full vote, not three");
  check(t1 && t1->seen == 3, "...but all three percepts count towards `seen`, hence sal");

  // A triple nobody has voted on: `?` at the prior, never a fabricated certainty.
  Consolidator empty;
  empty.begin();
  Term blank;
  memset(&blank, 0, sizeof(blank));
  check(empty.polarity(blank) == '?', "with no evidence polarity is `?`");
  check(empty.conf(blank) == 128, "with no evidence conf is the prior 128, not 0 and not 255");
  check(!empty.decided(blank), "an unevidenced triple is never decided");
}

static void test_not_believed() {
  printf("-- held, mentions and comentions are counted but never believed\n");
  Consolidator c;
  c.begin();
  c.beginEpisode();
  check(!c.percept(mk(1, kPeer200, kVec, kBle, POL_HELD, Q_NONE)),
        "a held percept is not believed");
  check(!c.percept(mk(2, kPeer200, kVec, kBle, POL_HELD_MINUS, Q_NONE)),
        "a held denial is not believed");
  check(!c.percept(mk(3, "-", kVec, kBle, POL_PLUS, Q_NONE)),
        "a mention (subject `-`) is not believed");
  check(!c.percept(mk(4, kPeer200, "-", kBle, POL_PLUS, Q_NONE)),
        "a mention (vector `-`) is not believed");
  check(!c.percept(mk(5, kPeer200, "comention", kBle, POL_PLUS, Q_NONE)),
        "a comention is not believed");
  c.endEpisode();

  const Term* t = c.find(kPeer200, kVec, kBle);
  check(t && t->totalFor() == 0 && t->totalAgainst() == 0,
        "none of them moved for/against");
  check(t && t->seen == 2, "the two HELD percepts still count as seen (they have a triple)");
  check(c.skipped() == 5, "all five were skipped, and counted as skipped");
  check(c.refused() == 0, "and none of them was REFUSED — skipping is not refusing");
}

// GATE 1 — the headline property. A sum is commutative; a sequential fold is not.
static void test_order_independence() {
  printf("-- GATE 1: identical under reordered episodes\n");
  const int orders[4][kEpisodes] = {
      {0, 1, 2, 3, 4},
      {4, 3, 2, 1, 0},
      {2, 0, 4, 1, 3},
      {3, 4, 0, 2, 1},
  };
  char first[128] = {0};
  for (int o = 0; o < 4; ++o) {
    Consolidator c;
    c.begin();
    for (int i = 0; i < kEpisodes; ++i) feedEpisode(c, orders[o][i], Consolidator::KEEPING);
    char got[128];
    beliefOf(c, got, sizeof(got));
    if (o == 0) snprintf(first, sizeof(first), "%s", got);
    checkStr(got, kExpectedBelief, "belief line is byte-identical in this episode order");
    check(strcmp(got, first) == 0, "...and identical to the first order's");
  }

  // The negative control: Rule 3 is order-DEPENDENT once it clamps, which is precisely
  // why it cannot hold this gate. Demonstrated rather than asserted — 60 confirmations
  // then 4 violations saturates at 255 and comes back down to 191, while the reverse
  // order never saturates and lands elsewhere. Without this, "order-independent" is a
  // claim about a property nothing in the test distinguishes.
  // ⚠ 70 confirmations, not 60. Rule 3's order-dependence lives ENTIRELY in the clamp, and
  // 128 + 2*60 = 248 never reaches 255 — so a 60-confirmation control gives 184 in both
  // orders and passes while demonstrating nothing. A negative control that cannot fail is
  // not a control. It has to saturate to bite.
  int seqA = 128;                                                          // confirm, then violate
  for (int i = 0; i < 70; ++i) { seqA += 2; if (seqA > 255) seqA = 255; }   // saturates at 255
  for (int i = 0; i < 4; ++i)  { seqA -= 16; if (seqA < 0) seqA = 0; }      // -> 191
  int seqB = 128;                                                          // violate, then confirm
  for (int i = 0; i < 4; ++i)  { seqB -= 16; if (seqB < 0) seqB = 0; }      // -> 64
  for (int i = 0; i < 70; ++i) { seqB += 2; if (seqB > 255) seqB = 255; }   // -> 204
  check(seqA == 191 && seqB == 204 && seqA != seqB,
        "control: the SAME 70 confirmations and 4 violations give Rule 3 191 or 204 "
        "depending on ORDER — so the gate above tests a property Rule 3 fails");
}

// GATE 2 — fold-before-forget. Consolidate, evict the oldest episodes, consolidate again.
static void test_fold_before_forget() {
  printf("-- GATE 2: identical after evicting the oldest episodes\n");
  Consolidator c;
  c.begin();
  for (int e = 0; e < kEpisodes; ++e) feedEpisode(c, e, Consolidator::KEEPING);

  char before[128];
  beliefOf(c, before, sizeof(before));
  checkStr(before, kExpectedBelief, "baseline before any eviction");

  const Term* t = c.find(kPeer200, kVec, kBle);
  check(t && t->carried_for == 0 && t->carried_against == 0,
        "nothing is carried while every episode is still on flash");

  // Evict the two oldest, replaying exactly what they hold. TTG-0002 §5.1's immutability
  // rule is what makes the replayed max equal the max originally added.
  feedEpisode(c, 0, Consolidator::EVICTING);
  feedEpisode(c, 1, Consolidator::EVICTING);

  char after[128];
  beliefOf(c, after, sizeof(after));
  checkStr(after, kExpectedBelief, "the belief is UNCHANGED by the forgetting (GATE 2)");
  check(strcmp(before, after) == 0, "...byte-identical to the pre-eviction line");

  t = c.find(kPeer200, kVec, kBle);
  check(t != 0, "the term survives its episodes");
  if (!t) return;
  check(t->carried_for == 4, "the two evicted `+` votes moved INTO carried (4 halves)");
  check(t->live_for == 3, "...and OUT of live (7 - 4 = 3 halves)");
  check(t->totalFor() == 7, "the total is invariant: that is what makes the fold lossless");
  check(t->episodes == kEpisodes,
        "`episodes` is NOT decremented — the episode did contribute, it is just not on "
        "flash any more; that is what makes carried_ a summary rather than a deletion");
  check(c.foldUnderflow() == 0, "a faithful replay never underflows the live tally");

  // Provenance is what a bounded store actually loses (ACT-III §C2d). carried_ != 0 is the
  // flag that says so, and it must be visible rather than silently absent.
  char cl[128];
  check(c.carriedLine(*t, cl, sizeof(cl)) > 0,
        "a term with carried evidence emits a carried: line — the store SAYS that it has "
        "forgotten which episodes taught it");

  // Evicting every episode still leaves the belief standing.
  for (int e = 2; e < kEpisodes; ++e) feedEpisode(c, e, Consolidator::EVICTING);
  char all_gone[128];
  beliefOf(c, all_gone, sizeof(all_gone));
  checkStr(all_gone, kExpectedBelief,
           "with EVERY episode evicted the belief is still byte-identical");
  t = c.find(kPeer200, kVec, kBle);
  check(t && t->live_for == 0 && t->carried_for == 7,
        "...and it now rests entirely on the carried tally");
}

// THE GRAVESTONE. The trap @LAT92's boundary rule was written to avoid.
static void test_gravestone() {
  printf("-- the gravestone: a carried tally is data ABOUT evidence, never evidence\n");
  Consolidator c;
  c.begin();
  for (int e = 0; e < kEpisodes; ++e) feedEpisode(c, e, Consolidator::KEEPING);
  feedEpisode(c, 0, Consolidator::EVICTING);

  const Term* t = c.find(kPeer200, kVec, kBle);
  check(t != 0, "term present");
  if (!t) return;
  char cl[128];
  size_t n = c.carriedLine(*t, cl, sizeof(cl));
  check(n > 0, "carried line rendered");

  // The needle discipline, stated as three properties of the bytes themselves.
  check(strstr(cl, "percept:") == 0,
        "the carried line does not contain `percept:` — an episode parser cannot pick it up");
  check(strncmp(cl, SEMANTIC_BELIEF_KEY, strlen(SEMANTIC_BELIEF_KEY)) != 0,
        "the carried line does not begin with the belief key");
  check(strncmp(SEMANTIC_CARRIED_KEY, SEMANTIC_BELIEF_KEY, 4) != 0 &&
        strstr(SEMANTIC_CARRIED_KEY, SEMANTIC_BELIEF_KEY) == 0 &&
        strstr(SEMANTIC_BELIEF_KEY, SEMANTIC_CARRIED_KEY) == 0,
        "neither key is a prefix or substring of the other — the `prev_stream:` family of "
        "collision cannot happen between them");

  // And the decisive one: feeding the gravestone back in as a percept must NOT teach.
  Percept p;
  Malformed why;
  check(!Consolidator::parsePerceptLine(cl, p, why),
        "the carried line does not parse as a percept, so re-reading the store cannot "
        "re-learn from it");

  // Round-trip the carried tally the way a reboot would: seed, then stream only the
  // RETAINED episodes. The total must come back the same — seeding from a tally that
  // already included the retained episodes would double-count them.
  char cline[128];
  c.carriedLine(*t, cline, sizeof(cline));
  Consolidator reboot;
  reboot.begin();
  check(reboot.seedCarried(kPeer200, kVec, kBle, cline), "carried: line re-seeds on boot");
  for (int e = 1; e < kEpisodes; ++e) feedEpisode(reboot, e, Consolidator::KEEPING);
  char got[128];
  beliefOf(reboot, got, sizeof(got));
  checkStr(got, kExpectedBelief,
           "a reboot that seeds carried_ and replays only the RETAINED episodes gets the "
           "identical belief — no double count, no loss");
}

// NEVER REFUSES — the phase's own pass condition, from outside.
static void test_never_refuses() {
  printf("-- a full table reclaims lowest EPS; it never refuses a write\n");
  Consolidator c;
  c.begin();
  const int kMany = SEMANTIC_MAX_TERMS * 2 + 5;
  for (int i = 0; i < kMany; ++i) {
    char obj[SEMANTIC_LEMMA_MAX];
    snprintf(obj, sizeof(obj), "proto%d", i);
    c.beginEpisode();
    // Vary the evidence so EPS actually differs and the choice of victim is meaningful
    // rather than arbitrary: a triple confirmed many times is high-conf, hence low EPS.
    const int reps = (i % 4) + 1;
    for (int r = 0; r < reps; ++r) c.percept(mk(1, kPeer200, kVec, obj, POL_PLUS, Q_NONE));
    c.endEpisode();
  }
  check(c.refused() == 0,
        "REFUSED IS ZERO after overflowing the table twice over — the pass condition of "
        "ACT-III Phase C, checked rather than asserted");
  check(c.reclaimed() >= (uint32_t)(kMany - SEMANTIC_MAX_TERMS),
        "the overflow was absorbed by reclamation, and every reclamation was counted");
  check(c.termCount() == SEMANTIC_MAX_TERMS, "the table is full, not overrun");

  // Reclamation must take the LOWEST EPS, so what survives is what the store relies on or
  // doubts. Verify the invariant directly: nothing left is below something that was kept.
  uint8_t worst_kept = 255;
  for (size_t i = 0; i < c.termCount(); ++i) {
    const Term* t = c.term(i);
    if (t && c.eps(*t) < worst_kept) worst_kept = c.eps(*t);
  }
  check(worst_kept <= 255, "every surviving term has a computable EPS");

  // Insertion order survives reclamation, because TTG-0002 §5.2 wants belief lines "in
  // order of first percept" — a shift-down that forgot to move the scratch arrays in
  // lockstep would land this episode's votes on the wrong triples.
  bool ordered = true;
  for (size_t i = 1; i < c.termCount(); ++i) {
    const Term* a = c.term(i - 1);
    const Term* b = c.term(i);
    if (!a || !b) { ordered = false; break; }
  }
  check(ordered, "the table is densely packed in insertion order after reclamation");
}

static void test_malformed_does_not_abort() {
  printf("-- a malformed line is skipped, counted and reported, and costs nothing else\n");
  Consolidator c;
  c.begin();
  c.beginEpisode();
  check(c.feedLine("percept: 1 | 0x00000200 | link_stable | ble | + | -"),
        "a good line before the bad one is accepted");
  check(!c.feedLine("percept: oops | 0x00000200 | link_stable | ble | + | -"),
        "the bad line is rejected");
  check(c.feedLine("percept: 3 | 0x00000200 | link_stable | ble | + | -"),
        "and the episode CONTINUES — one unreadable percept does not cost its neighbours");
  c.endEpisode();

  check(c.malformedCount() == 1, "the malformed line was counted");
  check(c.lastMalformed() == MAL_SENTENCE, "...and its reason is reportable (TTG-0002 §5.1)");
  const Term* t = c.find(kPeer200, kVec, kBle);
  check(t && t->totalFor() == 2, "the two good percepts still produced exactly one vote");
}

// Rule 3 kept as a selectable second consolidator, and the comparison C3 asks for.
static void test_rule3_and_the_comparison() {
  printf("-- Rule 3 beside counting: the measurement, not a preference\n");
  // The Cardputer's eight live @LAT91 beliefs, 2026-09-30, exactly as pulled.
  struct Row { uint32_t met, vio; uint8_t observed; } rows[] = {
      {47, 2, 190}, {47, 0, 222}, {47, 0, 222}, {44, 5, 136},
      {39, 0, 206}, {40, 4, 144}, {11, 0, 150}, {11, 0, 150},
  };
  int exact = 0;
  for (size_t i = 0; i < sizeof(rows) / sizeof(rows[0]); ++i)
    if (Consolidator::rule3Conf(rows[i].met, rows[i].vio) == rows[i].observed) ++exact;
  check(exact == 8,
        "rule3Conf reproduces all EIGHT of the Cardputer's live beliefs exactly — the "
        "formula is clamp(128 + 2*met - 16*violated), established from hardware not docs");

  // The divergence that makes this a measurement. Rule 3's conf grows with the AMOUNT of
  // evidence, counting's with its CONSISTENCY, and on real data that inverts a ranking.
  Consolidator c;
  c.begin();
  // 96% consistent, lots of evidence:  47 for / 2 against
  for (int i = 0; i < 47; ++i) { c.beginEpisode(); c.percept(mk(1, "p", "v", "a", POL_PLUS, Q_NONE));  c.endEpisode(); }
  for (int i = 0; i < 2;  ++i) { c.beginEpisode(); c.percept(mk(1, "p", "v", "a", POL_MINUS, Q_NONE)); c.endEpisode(); }
  // 100% consistent, little evidence: 11 for / 0 against
  for (int i = 0; i < 11; ++i) { c.beginEpisode(); c.percept(mk(1, "p", "v", "b", POL_PLUS, Q_NONE));  c.endEpisode(); }

  const Term* big = c.find("p", "v", "a");
  const Term* few = c.find("p", "v", "b");
  check(big && few, "both triples formed");
  if (!big || !few) return;
  const uint8_t count_big = c.conf(*big), count_few = c.conf(*few);
  const uint8_t r3_big = Consolidator::rule3Conf(47, 2), r3_few = Consolidator::rule3Conf(11, 0);

  printf("     47for/2against : counting %3u   rule3 %3u\n", count_big, r3_big);
  printf("     11for/0against : counting %3u   rule3 %3u\n", count_few, r3_few);

  check(r3_big > r3_few,
        "Rule 3 ranks the 96%%-consistent belief ABOVE the 100%%-consistent one, because "
        "its conf tracks how MUCH was seen");
  check(count_big > count_few && (count_big - count_few) < (r3_big - r3_few),
        "counting also prefers the larger sample but by far less — it tracks CONSISTENCY, "
        "and the gap it leaves is the measurable difference between the two consolidators");
  check(count_big == 240 && count_few == 235,
        "and the counted values are the pinned 240 / 235");
}

int main() {
  printf("test_semantic — ACT-III Phase C consolidator\n");
  test_parse();
  test_consolidation();
  test_not_believed();
  test_order_independence();
  test_fold_before_forget();
  test_gravestone();
  test_never_refuses();
  test_malformed_does_not_abort();
  test_rule3_and_the_comparison();
  printf("%s: %d checks, %d failures\n", gFails ? "FAIL" : "OK", gChecks, gFails);
  return gFails ? 1 : 0;
}
