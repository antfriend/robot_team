// test_ew.cpp — TTDB-RFC-0011 stage 1: the [ew] reader accepts `prec`.
//
// Stage 1 changes NO writer and NO behaviour. What it adds is the first reader of the TBEW
// block on this fleet (until now `[ew]` was written by PerceptLearn and read by nothing).
// Two halves, both required:
//
//   1. The shared vectors, tests/vectors/ew_vectors.txt — the SAME file test_ew_py.py
//      feeds to fleet.parse_ew(), so the two readers are proven to agree case by case.
//   2. Writer against reader (TTDB-RFC-0010 §7.2): a belief rendered by the real
//      PerceptLearn writer must read back with the values that went in, and with `prec`
//      absent (128, has_prec false), because no writer emits `prec` yet.
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include "TtdbParse.h"
#include "PerceptLearn.h"

static int gChecks = 0, gFails = 0;
#define CHECK(cond, ...)                                  \
  do {                                                    \
    ++gChecks;                                            \
    if (!(cond)) {                                        \
      ++gFails;                                           \
      printf("  FAIL: ");                                 \
      printf(__VA_ARGS__);                                \
      printf("\n");                                       \
    }                                                     \
  } while (0)

struct Case {
  std::string name, text;
  std::vector<std::pair<std::string, long long>> expect;
};

static const char* kKeys[] = {"present", "conf", "rev", "sal", "touched", "prec",
                              "has_conf", "has_rev", "has_sal", "has_touched", "has_prec"};
static const int kNKeys = 11;

static bool loadCases(const char* path, std::vector<Case>& out) {
  FILE* f = fopen(path, "rb");
  if (!f) return false;
  std::string all;
  char buf[4096];
  size_t n;
  while ((n = fread(buf, 1, sizeof(buf), f)) > 0) all.append(buf, n);
  fclose(f);
  if (all.find('\r') != std::string::npos) {
    printf("  FAIL: %s contains CR bytes — it must be checked out eol=lf\n", path);
    return false;
  }
  std::vector<std::string> lines;
  size_t s = 0;
  while (s <= all.size()) {
    size_t e = all.find('\n', s);
    if (e == std::string::npos) { if (s < all.size()) lines.push_back(all.substr(s)); break; }
    lines.push_back(all.substr(s, e - s));
    s = e + 1;
  }
  bool in = false, crlf = false, noeol = false;
  Case c;
  std::vector<std::string> body;
  for (const std::string& L : lines) {
    if (!in) {
      if (L.compare(0, 4, "=== ") == 0) {
        in = true; body.clear(); c = Case();
        std::string rest = L.substr(4);
        crlf = rest.find(" crlf") != std::string::npos;
        noeol = rest.find(" noeol") != std::string::npos;
        c.name = rest.substr(0, rest.find(' '));
      }
      continue;
    }
    if (L.compare(0, 11, "--- expect ") == 0) {
      const char* sep = crlf ? "\r\n" : "\n";
      for (size_t i = 0; i < body.size(); ++i) {
        c.text += body[i];
        if (i + 1 < body.size() || !noeol) c.text += sep;
      }
      std::string kv = L.substr(11);
      size_t p = 0;
      while (p < kv.size()) {
        size_t q = kv.find(' ', p);
        if (q == std::string::npos) q = kv.size();
        std::string tok = kv.substr(p, q - p);
        size_t colon = tok.find(':');
        if (colon != std::string::npos)
          c.expect.push_back({tok.substr(0, colon), atoll(tok.c_str() + colon + 1)});
        p = q + 1;
      }
      out.push_back(c);
      in = false;
      continue;
    }
    body.push_back(L);
  }
  return true;
}

static long long field(const TtdbEw& w, const std::string& k) {
  if (k == "present") return w.present;
  if (k == "conf") return w.conf;
  if (k == "rev") return w.rev;
  if (k == "sal") return w.sal;
  if (k == "touched") return w.touched;
  if (k == "prec") return w.prec;
  if (k == "has_conf") return w.has_conf;
  if (k == "has_rev") return w.has_rev;
  if (k == "has_sal") return w.has_sal;
  if (k == "has_touched") return w.has_touched;
  if (k == "has_prec") return w.has_prec;
  return -1;
}

int main(int argc, char** argv) {
  printf("[ew] reader tests (TTDB-RFC-0005 + RFC-0011 prec)\n");

  // ---- 1. shared vectors ---------------------------------------------------------------
  const char* path = argc > 1 ? argv[1] : "vectors/ew_vectors.txt";
  std::vector<Case> cases;
  CHECK(loadCases(path, cases), "load %s", path);
  CHECK(cases.size() >= 25, "vector file holds the full case list (got %zu)", cases.size());
  for (const Case& c : cases) {
    CHECK((int)c.expect.size() == kNKeys, "%s: expect line lists all %d keys (got %zu)",
          c.name.c_str(), kNKeys, c.expect.size());
    for (int i = 0; i < kNKeys; ++i) {
      bool listed = false;
      for (auto& e : c.expect) listed |= (e.first == kKeys[i]);
      CHECK(listed, "%s: expect line is missing `%s`", c.name.c_str(), kKeys[i]);
    }
    TtdbEw w;
    w.prec = 7;                        // garbage in `out` must be overwritten, not kept
    const bool ret = ttdbParseEw(c.text.data(), c.text.size(), w);
    CHECK(ret == w.present, "%s: return value equals present", c.name.c_str());
    for (auto& e : c.expect) {
      const long long got = field(w, e.first);
      CHECK(got == e.second, "%s: %s = %lld (got %lld)", c.name.c_str(), e.first.c_str(),
            e.second, got);
    }
  }

  // ---- 2. a reader must not read past `len` ----------------------------------------------
  {
    const char* s = "@LAT0LON1 | created:0 | updated:0\n[ew]\nprec:42\n[/ew]\n";
    TtdbEw w;
    // cut before "[/ew]": the block is unterminated WITHIN len, even though the bytes
    // after len would close it
    const size_t cut = (size_t)(strstr(s, "[/ew]") - s);
    CHECK(!ttdbParseEw(s, cut, w) && w.prec == 128 && !w.has_prec,
          "a block closed only beyond `len` is not read (prec %u)", w.prec);
    CHECK(ttdbParseEw(s, strlen(s), w) && w.prec == 42, "and is read with the full length");
    CHECK(!ttdbParseEw(nullptr, 0, w) && !w.present, "null input -> defaults, false");
  }

  // ---- 3. writer against reader: the real PerceptLearn @LAT91 renderer ------------------
  {
    const char* body =
        "\n---\n\n@LAT92LON19 | created:0 | updated:0 | "
        "relates:testifies_about@LAT95LON3,derived_from@LAT97LON3,senses@LAT0LON0\n\n"
        "**OUTCOME** t_ms:229600 synced:0 node:0x300 acting:@LAT95LON3 "
        "observed_in:@LAT97LON3 band_dbm:6 met:0 violated:2 unobserved:0 streak:1\n"
        "**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-45 band:6\n"
        "**OBSERVED** peer:0x00000200 proto:espnow observed_med:-83 delta:-38 "
        "verdict:violated\n";
    perceptlearn::Reconciler R;
    R.begin();
    CHECK(R.foldRecord(body, strlen(body)) == 1, "fixture folds one claim");
    CHECK(R.beliefCount() == 1, "one belief to render");
    timestream::Stamp ts;
    ts.t_ms = 7200000ULL;
    ts.stream_id = 0x92fb56aeu;
    ts.wall = true;
    static char rec[PERCEPTLEARN_BUF];
    const uint32_t t_sec = 1785542400UL;
    const int rev = 3;
    const size_t m = R.buildBelief(rec, sizeof(rec), 0, 4, t_sec, 0x300, rev, ts);
    CHECK(m > 0, "PerceptLearn renders the belief (%zu B)", m);
    TtdbEw w;
    CHECK(ttdbParseEw(rec, m, w), "the reader finds the writer's [ew] block");
    const perceptlearn::Belief& b = R.belief(0);
    CHECK(w.has_conf && w.conf == (uint8_t)b.conf, "conf round-trips (%u vs %ld)", w.conf,
          (long)b.conf);
    CHECK(w.has_rev && w.rev == rev, "rev round-trips (%u)", w.rev);
    CHECK(w.has_sal && w.sal == (uint8_t)b.sal, "sal round-trips (%u vs %ld)", w.sal,
          (long)b.sal);
    CHECK(w.has_touched && w.touched == t_sec, "touched round-trips (%lu)",
          (unsigned long)w.touched);
    CHECK(!w.has_prec && w.prec == 128,
          "no writer emits prec in stage 1, so it reads as unassessed 128");
    // The **TALLY** line carries `baseline_conf:128`: the block reader must not see it.
    CHECK(strstr(rec, "baseline_conf:") != NULL, "fixture really carries baseline_conf:");
  }

  printf("RESULT %s: %d of %d checks failed\n", gFails ? "FAIL" : "OK", gFails, gChecks);
  return gFails ? 1 : 0;
}
