// test_fleettime.cpp — ACT-III §C4: TTG-RFC-0004 §4.8's test plan, items 1–4.
//
//   1. non-overlapping stamps: the later retires the earlier          (maximal = 1)
//   2. overlapping stamps: contested, both quoted                      (maximal = 2)
//   3. overlapping stamps plus a `follows` edge: the edge decides      (maximal = 1)
//   4. two agents holding the same episodes give IDENTICAL answers as of bar N —
//      received in different orders, at different times, each also holding episodes the
//      other does not have yet. This is the RFC's falsifiable claim and ACT-III §2's
//      "agrees without coordinating"; the test also shows it is NOT vacuous (the live
//      views differ) and that the unbounded-exclusion rule is load-bearing (break it and
//      the bar views differ).
//   5. (scene split) — not applicable: see FleetTime.h, "What this file does NOT do".
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <map>
#include <string>
#include <vector>

#include "FleetTime.h"
#include "Semantic.h"

static int gChecks = 0, gFails = 0;
static void check(bool ok, const char* what) {
  ++gChecks;
  if (!ok) { ++gFails; printf("  FAIL: %s\n", what); }
}

using namespace semantic;

// The fleet's frame in these fixtures: one lineage's downbeat_epoch.
static const uint64_t kFrame = 5000;

static EpisodeRef ep(uint32_t agent, uint32_t seq, int64_t t, uint32_t b, bool bounded = true,
                     uint64_t frame = kFrame) {
  EpisodeRef e;
  memset(&e, 0, sizeof(e));
  e.agent = agent; e.seq = seq;
  e.at.t_ms = t; e.at.bound_ms = b; e.at.bounded = bounded;
  e.at.frame = frame; e.at.has_frame = bounded;
  return e;
}

static void testStamps() {
  printf("stamps\n");
  // TTG-0004 §4.3's own table, at 50 ppm (delivery excluded so the drift term is checked).
  check(boundMs(86400000u, 50, 0) == 4320, "a day since the last beacon: ±4.32 s (RFC: ±4.3 s)");
  check(boundMs(604800000u, 50, 0) == 30240, "a week: ±30.24 s (RFC: ±30 s)");
  check(boundMs(1, 50, 0) == 1, "drift rounds UP — a bound may over-state, never under-state");
  check(boundMs(0) == FLEETTIME_DELIVERY_MS, "fresh beacon: delivery only");

  At c = stampNow(1000, 99999, true, true, kFrame);
  check(c.bounded && c.bound_ms == 0 && c.has_frame && c.frame == kFrame,
        "the conductor's own stamp is exact, and names its frame");
  At u = stampNow(1000, 0, false, false, kFrame);
  check(!u.bounded && !u.has_frame,
        "never heard a chart: UNBOUNDED and frameless, orders nothing outside its agent");

  // --- the frame -------------------------------------------------------------------------
  char fb[64];
  At fa = {1789257600LL, 4, true, 6500, true};
  check(renderAt(fa, fb, sizeof(fb)) &&
            strcmp(fb, "1789257600 \xC2\xB1" "4 frame:6500") == 0,
        "a framed stamp renders `<t> ±<b> frame:<downbeat>`");
  At fr = parseAt(fb);
  check(fr.bounded && fr.has_frame && fr.frame == 6500 && fr.bound_ms == 4, "and parses back");
  check(!parseAt("at: 5 \xC2\xB1" "3 frame:").bounded &&
            !parseAt("at: 5 \xC2\xB1" "3 frame:x").bounded,
        "a malformed frame makes the WHOLE stamp unbounded — a half-read stamp orders nothing");
  At x1 = {1000, 10, true, 5000, true}, x2 = {9000, 10, true, 6500, true},
     x3 = {9000, 10, true, 5000, true};
  check(!sameFrame(x1, x2) && sameFrame(x1, x3), "sameFrame compares lineages");

  char b[48];
  At a = {1789257600LL, 4, true, 0, false};
  size_t n = renderAt(a, b, sizeof(b));
  check(n && strcmp(b, "1789257600 \xC2\xB1" "4") == 0, "renders as the RFC writes it: `1789257600 ±4`");
  At r = parseAt("at: 1789257600 \xC2\xB1" "4");
  check(r.bounded && r.t_ms == 1789257600LL && r.bound_ms == 4 && !r.has_frame,
        "and parses back — bounded but FRAMELESS (the stamps written before 2026-10-01's fix)");
  At old = parseAt("at: t_ms:77 stream:0x00000000 wall:0");
  check(!old.bounded && old.t_ms == 77,
        "a pre-C4 `t_ms:` stamp parses as UNBOUNDED — readable, never mis-ordered");
  check(!parseAt("at: 5 \xC2\xB1" "x").bounded && !parseAt("at: 5 \xC2\xB1" "3 junk").bounded &&
            !parseAt("").bounded && !parseAt(0).bounded,
        "anything malformed is unbounded, never an error");
  check(renderAt(a, b, 5) == 0, "a stamp that does not fit writes nothing");
}

static void testOrder() {
  printf("order (items 1-3)\n");
  size_t idx[4];

  // 1. Disjoint ranges: later retires earlier.
  EpisodeRef c1[2] = {ep(0x10, 1, 1000, 50), ep(0x200, 7, 2000, 50)};
  check(order(c1[0], c1[1]) == BEFORE && order(c1[1], c1[0]) == AFTER, "disjoint stamps order");
  size_t k = maximal(c1, 2, idx, 4);
  check(k == 1 && idx[0] == 1, "ITEM 1: the later place retires the earlier");

  // 2. Overlapping ranges, no edge: contested.
  EpisodeRef c2[2] = {ep(0x10, 1, 1000, 600), ep(0x200, 7, 2000, 600)};
  check(order(c2[0], c2[1]) == CONCURRENT, "overlapping stamps are concurrent");
  k = maximal(c2, 2, idx, 4);
  check(k == 2, "ITEM 2: contested — both quoted");

  // 3. Same overlap, but the second was written knowing the first.
  EpisodeRef c3[2] = {c2[0], c2[1]};
  c3[1].follows[0] = Follows{0x10, 1};
  c3[1].n_follows = 1;
  k = maximal(c3, 2, idx, 4);
  check(order(c3[0], c3[1]) == BEFORE && k == 1 && idx[0] == 1, "ITEM 3: the edge decides");

  // The edge wins even against the clocks — and says so.
  EpisodeRef early = ep(0x200, 3, 0, 10), late = ep(0x10, 9, 5000, 10);
  early.follows[0] = Follows{0x10, 9};
  early.n_follows = 1;
  bool contra = false;
  check(order(late, early, &contra) == BEFORE && contra,
        "an edge against disjoint stamps: the edge wins and the contradiction is flagged");

  // A follows edge naming an OLDER seq than the episode does not reach it.
  EpisodeRef x = ep(0x10, 5, 1000, 600), y = ep(0x200, 1, 1100, 600);
  y.follows[0] = Follows{0x10, 4};
  y.n_follows = 1;
  check(order(x, y) == CONCURRENT, "follows@seq 4 does not reach seq 5");

  check(order(ep(0x10, 2, 9000, 0), ep(0x10, 3, 0, 0)) == BEFORE,
        "same agent: its own sequence decides, not its clock");
  check(order(ep(0x10, 1, 0, 0, false), ep(0x200, 1, 99999, 0)) == CONCURRENT,
        "an unbounded stamp orders nothing across agents");

  // THE FRAME CASE (2026-10-01): a node that self-appointed alone, stamped, then joined the
  // fleet's lineage. Its old stamp's NUMBER is far below the fleet's, but it is on a
  // different clock — disjoint-looking ranges in different frames must not order.
  EpisodeRef lone = ep(0x300, 1, 1000, 5, true, 6500);       // its own lineage
  EpisodeRef fleet = ep(0x10, 40, 90000, 5, true, kFrame);    // the fleet's
  check(order(lone, fleet) == CONCURRENT,
        "stamps in DIFFERENT frames never order by their numbers, however far apart");
  EpisodeRef nofr = ep(0x300, 2, 1000, 5);
  nofr.at.has_frame = false;
  check(order(nofr, fleet) == CONCURRENT,
        "a bounded but FRAMELESS stamp orders nothing across agents either");
  EpisodeRef edge = lone;
  fleet.follows[0] = Follows{0x300, 1};
  fleet.n_follows = 1;
  check(order(edge, fleet) == BEFORE,
        "...but a `follows` edge still orders across frames: knowledge is not a clock");
}

// ---------------------------------------------------------------------------------------
// ITEM 4 — two agents, same episodes, same answers as of bar N, no coordination.
// ---------------------------------------------------------------------------------------
struct World {
  EpisodeRef ref;
  std::vector<Percept> ps;
};

static Percept pc(const char* s, const char* o, Polarity pol) {
  Percept p;
  memset(&p, 0, sizeof(p));
  p.sentence = 1;
  snprintf(p.subject, SEMANTIC_LEMMA_MAX, "%s", s);
  snprintf(p.vec, SEMANTIC_LEMMA_MAX, "link_stable");
  snprintf(p.object, SEMANTIC_LEMMA_MAX, "%s", o);
  p.pol = pol;
  p.quant = Q_NONE;
  return p;
}

static uint32_t gRng = 777;
static uint32_t rnd() { gRng = gRng * 1103515245u + 12345u; return (gRng >> 16) & 0x7fff; }

static std::map<std::string, std::string> view(const std::vector<const World*>& held,
                                               bool bar, int64_t line,
                                               bool include_unbounded_own = false,
                                               uint32_t owner = 0) {
  Consolidator c;
  c.begin();
  for (size_t i = 0; i < held.size(); ++i) {
    const World* w = held[i];
    bool use = !bar || inBar(w->ref.at, line, kFrame) ||
               (include_unbounded_own && !w->ref.at.bounded && w->ref.agent == owner &&
                w->ref.at.t_ms < line);
    if (!use) continue;
    c.beginEpisode();
    for (size_t k = 0; k < w->ps.size(); ++k) c.percept(w->ps[k]);
    c.endEpisode(Consolidator::KEEPING);
  }
  std::map<std::string, std::string> out;
  for (size_t i = 0; i < c.termCount(); ++i) {
    const Term* t = c.term(i);
    char b[128];
    c.beliefLine(*t, b, sizeof(b));
    out[std::string(t->subject) + "|" + t->object] = b;
  }
  return out;
}

static void testBar() {
  printf("bar (item 4)\n");
  const uint32_t agents[3] = {0x10, 0x200, 0x300};
  const char* peers[] = {"0x00000010", "0x00000100", "0x00000200", "0x00000300"};
  const int64_t downbeat = 5000;
  const uint32_t bar_ms = 60000;
  std::vector<World> world;
  uint32_t seq[3] = {0, 0, 0};
  for (int i = 0; i < 240; ++i) {
    const int a = (int)(rnd() % 3);
    World w;
    const int64_t t = downbeat + (int64_t)i * 1000 + (int64_t)(rnd() % 400);
    w.ref = ep(agents[a], ++seq[a], t, 20 + rnd() % 3000, rnd() % 10 != 0);   // 1 in 10 unbounded
    for (int k = 0; k < 1 + (int)(rnd() % 3); ++k)
      w.ps.push_back(pc(peers[rnd() % 4], rnd() % 2 ? "espnow" : "ble",
                        rnd() % 6 ? POL_PLUS : POL_MINUS));
    world.push_back(w);
  }

  const int64_t line = barLine(downbeat, bar_ms, 2);   // 125 000
  // Agent X holds everything up to t=200 s, received in creation order.
  // Agent Y holds everything up to t=230 s, received SHUFFLED, plus its own late extras.
  std::vector<const World*> X, Y;
  for (size_t i = 0; i < world.size(); ++i) {
    if (world[i].ref.at.t_ms < 205000) X.push_back(&world[i]);
    if (world[i].ref.at.t_ms < 235000) Y.push_back(&world[i]);
  }
  for (size_t i = Y.size(); i > 1; --i) std::swap(Y[i - 1], Y[rnd() % i]);

  std::map<std::string, std::string> xb = view(X, true, line), yb = view(Y, true, line);
  check(!xb.empty(), "the bar view is not empty");
  check(xb == yb,
        "ITEM 4: X and Y — different arrival orders, different extra holdings — answer "
        "IDENTICALLY as of bar 2, without exchanging a byte");
  check(view(X, false, 0) != view(Y, false, 0),
        "and NOT vacuously: their LIVE views differ (Y holds 30 s more)");

  // The exclusion rule is load-bearing: let Y count its own unbounded episodes in its bar.
  size_t unb = 0;
  for (size_t i = 0; i < Y.size(); ++i)
    if (!Y[i]->ref.at.bounded && Y[i]->ref.agent == 0x200 && Y[i]->ref.at.t_ms < line) ++unb;
  check(unb > 0, "the fixture holds unbounded episodes of Y's own before the line");
  check(view(Y, true, line, true, 0x200) != xb,
        "NEGATIVE CONTROL: if an owner counts its own UNBOUNDED episodes in the bar, the "
        "agreement breaks — which is why FleetTime excludes them for everyone");

  // An episode straddling the line belongs to the NEXT bar, for everyone.
  At straddle = {line - 10, 50, true, kFrame, true};
  check(!inBar(straddle, line, kFrame) &&
            inBar(straddle, barLine(downbeat, bar_ms, 3), kFrame),
        "a stamp whose range crosses the line joins the next bar, not this one");
  At other = {line - 30000, 50, true, 6500, true};
  check(!inBar(other, line, kFrame),
        "an episode stamped in ANOTHER lineage's frame joins none of this lineage's bars");
  printf("    %u episodes; X holds %u, Y holds %u; %u terms agree as of bar 2\n",
         (unsigned)world.size(), (unsigned)X.size(), (unsigned)Y.size(), (unsigned)xb.size());
}

int main() {
  testStamps();
  testOrder();
  testBar();
  printf("\n%d checks, %d failures\n", gChecks, gFails);
  return gFails ? 1 : 0;
}
