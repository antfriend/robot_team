// test_symmetric_edges.cpp — validates the SYMMETRIC edge types in every TTDB the fleet
// carries, using the firmware's own TtdbParse.cpp.
//
// TTDB-RFC-0003 v1.1 §7.1 declares a type MAY be symmetric — `A opposes B` and
// `B opposes A` assert the same thing — but §2 still forbids a parser from inferring
// the reverse edge. The author must therefore write BOTH directions, and a file that
// declares only one "is well-formed but incomplete, and SHOULD be reported by
// validators rather than silently repaired". This is that validator.
//
// It matters here specifically. The feelings globe encodes Joy/Grief polarity
// POSITIONALLY, in latitude — and §7.3's rationale is that position is invisible to a
// consumer reading the edge list, which is exactly what the handhelds' globe renderer
// traverses. Without `opposes`, the hero's-arc song's most load-bearing relation is
// unreadable by the thing drawing it. With `opposes` written one-way, it is worse:
// readable from one end and absent from the other, so which record you selected would
// decide whether the relation exists.
//
// Node-local supersets are expected and fine (each console carries `type:band` overlay
// records the canonical store does not); the check is on edge symmetry, not on record
// count matching some other file.
#include "TtdbParse.h"
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

static int fails = 0;
#define CHECK(cond, ...)             \
  do {                               \
    if (cond) {                      \
      printf("PASS: " __VA_ARGS__);  \
      printf("\n");                  \
    } else {                         \
      printf("FAIL: " __VA_ARGS__);  \
      printf("\n");                  \
      ++fails;                       \
    }                                \
  } while (0)

// The symmetric types. One entry today; the array is the point — §7.1 is written about
// symmetric types in general and the next one costs a line here.
static const char* kSymmetric[] = {"opposes"};

struct Edge {
  int16_t from_lat, from_lon, to_lat, to_lon;
  std::string type;
};

// Strip the edge-syntax suffix: the feelings store declares `syntax: "type>@TARGET_ID"`,
// so ttdbParseEdges — which splits on '@' — hands back "opposes>" rather than "opposes".
static std::string bareType(const char* t) {
  std::string s(t);
  while (!s.empty() && (s[s.size() - 1] == '>' || s[s.size() - 1] == ' ')) s.erase(s.size() - 1);
  return s;
}

static bool isSymmetric(const std::string& t) {
  for (size_t i = 0; i < sizeof(kSymmetric) / sizeof(kSymmetric[0]); ++i)
    if (t == kSymmetric[i]) return true;
  return false;
}

static std::string readLine(const std::string& data, size_t off) {
  char line[256];
  size_t i = 0;
  while (i < sizeof(line) - 1 && off < data.size()) {
    char c = data[off++];
    if (c == '\n') break;
    if (c != '\r') line[i++] = c;
  }
  line[i] = '\0';
  return std::string(line);
}

static bool checkStore(const char* path) {
  FILE* f = fopen(path, "rb");
  if (!f) {
    printf("FAIL: cannot open %s\n", path);
    ++fails;
    return false;
  }
  std::string data;
  char buf[4096];
  size_t n;
  while ((n = fread(buf, 1, sizeof(buf), f)) > 0) data.append(buf, n);
  fclose(f);

  // Index record headers exactly as Ttdb::begin() pass 1 does.
  std::vector<size_t> offs;
  bool line_start = true;
  for (size_t off = 0; off < data.size(); ++off) {
    if (line_start && data[off] == '@') offs.push_back(off);
    line_start = (data[off] == '\n');
  }

  std::vector<TtdbRecord> recs;
  std::vector<Edge> sym;
  int total_edges = 0;
  // The umwelt record carries 17 edges in the feelings store, well past any per-record
  // render cap, so parse with a generous buffer here — this test is about completeness,
  // not about what one screen can draw.
  TtdbEdge edges[32];
  for (size_t i = 0; i < offs.size(); ++i) {
    std::string line = readLine(data, offs[i]);
    TtdbRecord r;
    if (!ttdbParseHeader(line.c_str(), r)) {
      printf("      unparseable header: %.60s\n", line.c_str());
      ++fails;
      continue;
    }
    recs.push_back(r);
    uint8_t ne = ttdbParseEdges(line.c_str(), edges, 32);
    total_edges += ne;
    for (uint8_t e = 0; e < ne; ++e) {
      std::string t = bareType(edges[e].type);
      if (!isSymmetric(t)) continue;
      Edge ed;
      ed.from_lat = r.lat;
      ed.from_lon = r.lon;
      ed.to_lat = edges[e].target_lat;
      ed.to_lon = edges[e].target_lon;
      ed.type = t;
      sym.push_back(ed);
    }
  }

  printf("  %s: %zu records, %d edges, %zu symmetric\n", path, recs.size(), total_edges,
         sym.size());

  // 1. Every symmetric edge has its mirror written explicitly (§7.1: the author writes
  //    both; no parser may infer one).
  int one_way = 0;
  for (size_t i = 0; i < sym.size(); ++i) {
    bool mirrored = false;
    for (size_t j = 0; j < sym.size(); ++j) {
      if (sym[j].type == sym[i].type && sym[j].from_lat == sym[i].to_lat &&
          sym[j].from_lon == sym[i].to_lon && sym[j].to_lat == sym[i].from_lat &&
          sym[j].to_lon == sym[i].from_lon) {
        mirrored = true;
        break;
      }
    }
    if (!mirrored) {
      ++one_way;
      printf("      one-directional %s: @LAT%dLON%d -> @LAT%dLON%d (reverse not written)\n",
             sym[i].type.c_str(), sym[i].from_lat, sym[i].from_lon, sym[i].to_lat,
             sym[i].to_lon);
    }
  }
  CHECK(one_way == 0, "%s: all %zu symmetric edges are written in both directions",
        path, sym.size());

  // 2. No symmetric edge dangles — a polarity claim about a record that is not here.
  int dangling = 0;
  for (size_t i = 0; i < sym.size(); ++i) {
    bool found = false;
    for (size_t j = 0; j < recs.size(); ++j)
      if (recs[j].lat == sym[i].to_lat && recs[j].lon == sym[i].to_lon) found = true;
    if (!found) {
      ++dangling;
      printf("      dangling %s target @LAT%dLON%d\n", sym[i].type.c_str(), sym[i].to_lat,
             sym[i].to_lon);
    }
  }
  CHECK(dangling == 0, "%s: every symmetric target resolves to a record", path);

  // 3. Nothing opposes itself. A record at both ends of one dimension is not a
  //    polarity claim, it is a bug — and it would satisfy check 1 trivially.
  int self = 0;
  for (size_t i = 0; i < sym.size(); ++i)
    if (sym[i].from_lat == sym[i].to_lat && sym[i].from_lon == sym[i].to_lon) ++self;
  CHECK(self == 0, "%s: no record is its own opposite", path);

  return sym.size() > 0;
}

int main(int argc, char** argv) {
  // Both device globes. They are deliberate supersets of the canonical store and of
  // each other (each console draws the OTHER band members, never itself), so they are
  // checked independently rather than diffed.
  const char* defaults[] = {
      "../firmware/tdeck_console/data/feelings.ttdb.md",
      "../firmware/cardputer_console/data/feelings.ttdb.md",
  };

  bool any_symmetric = false;
  if (argc > 1) {
    for (int i = 1; i < argc; ++i) any_symmetric |= checkStore(argv[i]);
  } else {
    for (size_t i = 0; i < sizeof(defaults) / sizeof(defaults[0]); ++i)
      any_symmetric |= checkStore(defaults[i]);
  }

  // A validator that passes because it found nothing to validate is not a passing
  // validator. If the `opposes` edges ever vanish from the flashed globes — which is
  // precisely what a bad merge against the canonical store would do — this fails.
  CHECK(any_symmetric, "the flashed globes actually carry symmetric edges to validate");

  printf("%s: %d checks failed\n", fails ? "RESULT FAIL" : "RESULT OK", fails);
  return fails ? 1 : 0;
}
