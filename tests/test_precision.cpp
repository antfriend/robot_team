// test_precision.cpp — TTDB-RFC-0011 stage 3: the @LAT108 fold equals pw1_fold.py exactly.
//
// docs/design/rfc0011-stage3.md §7. Four parts:
//   1. pw1's hand-worked 5-residual case and the arithmetic shift, at the unit level.
//   2. tests/vectors/precision_vectors.txt — the SAME file tools/stage3/test_stage3_gate.py
//      checks the gate (pw1's own code) against. C++ and the gate must agree case by case.
//   3. The record: render -> ttdbParseEw + readOnFlash round-trip, sid, buffer bound.
//   4. The write rule and the overflow-excludes-not-truncates rule.
//
// `test_precision --replay <pull.md>` folds every tier band of a file and prints the same
// line format as `stage3_gate.py --replay`, for the design §6 rehearsal (code against code).
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

#include "Precision.h"
#include "Sid.h"
#include "TtdbParse.h"

using namespace precision;

static int gChecks = 0, gFails = 0;
#define CHECK(cond, ...)               \
  do {                                 \
    ++gChecks;                         \
    if (!(cond)) {                     \
      ++gFails;                        \
      printf("  FAIL: ");              \
      printf(__VA_ARGS__);             \
      printf("\n");                    \
    }                                  \
  } while (0)

static std::string slurp(const char* path) {
  FILE* f = fopen(path, "rb");
  if (!f) return std::string();
  std::string s;
  char b[4096];
  size_t n;
  while ((n = fread(b, 1, sizeof(b), f)) > 0) s.append(b, n);
  fclose(f);
  return s;
}

static int chanOf(const std::string& s) {
  for (int c = 0; c < CH_COUNT; ++c)
    if (s == chanName((uint8_t)c)) return c;
  return -1;
}

struct Ep { int lon; std::string text; };

// ---- --replay: fold every band of a pull (records split at lines starting "@LAT") ----------
static int replay(const char* path) {
  const std::string all = slurp(path);
  if (all.empty()) { printf("cannot read %s\n", path); return 2; }
  std::vector<size_t> starts;
  for (size_t i = 0; i < all.size(); ++i)
    if ((i == 0 || all[i - 1] == '\n') && all.compare(i, 4, "@LAT") == 0) starts.push_back(i);
  for (int c = 0; c < CH_COUNT; ++c) {
    Fold f((uint8_t)c);
    for (size_t k = 0; k < starts.size(); ++k) {
      const size_t s = starts[k], e = k + 1 < starts.size() ? starts[k + 1] : all.size();
      int lat = 0, lon = 0;
      if (sscanf(all.c_str() + s, "@LAT%dLON%d", &lat, &lon) != 2) continue;
      if (lat != PRECISION_EPISODE_LANE || chanOfLon(lon) != c) continue;
      f.add(all.data() + s, e - s, lon);
    }
    printf("%s var:%ld n:%lu prec:%u conf:%u episodes:%lu excluded:%lu segments:%lu "
           "peers_absent:%lu\n", chanName((uint8_t)c), (long)f.var(), (unsigned long)f.n(),
           (unsigned)f.prec(), (unsigned)f.conf(), (unsigned long)f.episodes(),
           (unsigned long)f.excluded(), (unsigned long)f.segments(),
           (unsigned long)f.peersAbsent());
  }
  return 0;
}

// ---- --render-sample: a tiny pull whose @LAT108 record is rendered by THIS code ----------
// tests/test_stage3_gate_py.py feeds it to stage3_gate.gate() and requires MATCH, which is
// the only check that the gate parses the record format the firmware actually writes.
static int renderSample() {
  const char* eps[] = {
      "@LAT103LON16384 | created:0 | updated:0\nsource: motionpercept\n"
      "said: 1 | **MOTIONWIN** t_ms:60000 stream:0x0000aaaa wall:0\n"
      "said: 2 | **MOTION** state:still dev_mean_mg:8\n",
      "@LAT103LON16385 | created:0 | updated:0\nsource: motionpercept\n"
      "said: 1 | **MOTIONWIN** t_ms:1860000 stream:0x0000aaaa wall:0\n"
      "said: 2 | **MOTION** state:still dev_mean_mg:13\n"
      "said: 3 | **RUN** windows_since_last:30 reason:heartbeat max_run:30\n",
      "@LAT103LON16386 | created:0 | updated:0\nsource: motionpercept\n"
      "said: 1 | **MOTIONWIN** t_ms:1920000 stream:0x0000aaaa wall:0\n"
      "said: 2 | **MOTION** state:moving dev_mean_mg:70\n"};
  Fold f(CH_MOTION);
  for (int i = 0; i < 3; ++i) {
    printf("\n---\n\n%s", eps[i]);
    f.add(eps[i], strlen(eps[i]), 16384 + i);
  }
  static char rec[PRECISION_RECORD_BUF];
  const size_t m = render(rec, sizeof(rec), f, 0x300, 0, 0, 0, "t_ms:1920000 stream:0x0000aaaa wall:0");
  if (!m) return 3;
  fwrite(rec, 1, m, stdout);
  return 0;
}

int main(int argc, char** argv) {
  if (argc > 2 && !strcmp(argv[1], "--replay")) return replay(argv[2]);
  if (argc > 1 && !strcmp(argv[1], "--render-sample")) return renderSample();
  printf("Precision (@LAT108) fold tests\n");

  // ---- 1. arithmetic -----------------------------------------------------------------------
  {
    // pw1 test_pw1_fold.HandWorked: r = 10, 0, 20, 5, 255 -> var 6, 5, 29, 28, 4090; pi 170.
    const int32_t rs[] = {10, 0, 20, 5, 255}, want[] = {6, 5, 29, 28, 4090};
    int32_t v = 0;
    for (int i = 0; i < 5; ++i) {
      v = foldStep(v, rs[i]);
      CHECK(v == want[i], "hand-worked step %d: var %ld (want %ld)", i, (long)v, (long)want[i]);
    }
    CHECK(piFromVar(4090) == 170, "pi(4090) = 170 (got %u)", piFromVar(4090));
    // ⚠ The shift. (0 - 6) >> 4 is -1 arithmetic; a logical shift gives 268435455 and the
    // EWMA explodes. This is the step that would catch it at run time (the static_assert in
    // Precision.h catches it at build time).
    volatile int32_t six = 6;                         // keep the compiler from folding it
    CHECK(((0 - six) >> 4) == -1, "(0 - 6) >> 4 == -1 at run time");
    CHECK(foldStep(6, 0) == 5, "foldStep(6, 0) == 5 (got %ld)", (long)foldStep(6, 0));
    CHECK(piFromVar(0) == 255, "pi(0) = 255");
    // conf, design D4: min(240, 16 * floor(log2(1 + n)))
    const uint32_t ns[] = {0, 1, 2, 3, 6, 7, 32766, 32767, 100000000};
    const uint8_t cs[] = {0, 16, 16, 32, 32, 48, 224, 240, 240};
    for (int i = 0; i < 9; ++i)
      CHECK(confFromN(ns[i]) == cs[i], "conf(n=%lu) = %u (got %u)", (unsigned long)ns[i], cs[i],
            confFromN(ns[i]));
    CHECK(pe(-10, 90) == 28 && pe(10, 90) == 28, "pe(+-10, 90) = 28");
    CHECK(pe(1000, 60) == 255, "pe beyond span clamps to 255");
    CHECK(pe(0, 900) == 0, "pe(0) = 0");
    CHECK(chanOfLon(0) == CH_LINK && chanOfLon(8191) == CH_LINK && chanOfLon(8192) == CH_ENTITY &&
          chanOfLon(16384) == CH_MOTION && chanOfLon(24576) == CH_ACOUSTIC &&
          chanOfLon(32768) == -1 && chanOfLon(-1) == -1, "tier bands from LON");
  }

  // ---- 2. shared vectors -------------------------------------------------------------------
  {
    const char* path = "vectors/precision_vectors.txt";
    const std::string all = slurp(path);
    CHECK(!all.empty(), "load %s", path);
    CHECK(all.find('\r') == std::string::npos, "%s has no CR bytes (eol=lf)", path);
    std::vector<std::string> L;
    size_t s = 0;
    while (s <= all.size()) {
      size_t e = all.find('\n', s);
      if (e == std::string::npos) { L.push_back(all.substr(s)); break; }
      L.push_back(all.substr(s, e - s));
      s = e + 1;
    }
    int cases = 0;
    bool hand_seen = false;
    for (size_t i = 0; i < L.size(); ++i) {
      if (L[i].compare(0, 4, "=== ") != 0) continue;
      const std::string head = L[i].substr(4);
      const std::string name = head.substr(0, head.find(' '));
      const int chan = chanOf(head.substr(head.find("chan:") + 5));
      CHECK(chan >= 0, "%s: channel parses", name.c_str());
      if (chan < 0) continue;
      std::vector<Ep> eps;
      std::string expect;
      size_t j = i + 1;
      for (; j < L.size() && L[j].compare(0, 4, "=== ") != 0; ++j) {
        if (L[j].compare(0, 16, "--- episode lon:") == 0) {
          Ep ep;
          ep.lon = atoi(L[j].c_str() + 16);
          size_t k = j + 1;
          for (; k < L.size() && L[k].compare(0, 4, "--- ") != 0; ++k) ep.text += L[k] + "\n";
          eps.push_back(ep);
          j = k - 1;
        } else if (L[j].compare(0, 10, "--- expect") == 0) {
          expect = L[j].substr(10);
        }
      }
      i = j - 1;
      ++cases;
      Fold f((uint8_t)chan);
      for (const Ep& ep : eps) f.add(ep.text.data(), ep.text.size(), ep.lon);
      const struct { const char* k; long long got; } got[] = {
          {"var", f.var()}, {"n", f.n()}, {"prec", f.prec()}, {"conf", f.conf()},
          {"episodes", f.episodes()}, {"excluded", f.excluded()}, {"segments", f.segments()},
          {"peers_absent", f.peersAbsent()}};
      int listed = 0;
      for (const auto& g : got) {
        const std::string needle = std::string(" ") + g.k + ":";
        const size_t at = expect.find(needle);
        if (at == std::string::npos) continue;
        ++listed;
        const long long want = atoll(expect.c_str() + at + needle.size());
        CHECK(g.got == want, "%s: %s = %lld (C++ got %lld)", name.c_str(), g.k, want, g.got);
      }
      CHECK(listed == 8, "%s: expect line lists all 8 fields (got %d) — run --fill-vectors",
            name.c_str(), listed);
      if (name == "hand_worked_acoustic") {
        hand_seen = true;   // pinned by hand, independent of the generator
        CHECK(f.var() == 4090 && f.prec() == 170 && f.n() == 5,
              "hand_worked_acoustic is pw1's 4090 / 170 / 5 (got %ld / %u / %lu)",
              (long)f.var(), f.prec(), (unsigned long)f.n());
      }
    }
    CHECK(cases >= 8, "vector file holds the full case list (got %d)", cases);
    CHECK(hand_seen, "the hand-pinned case is present");
  }

  // ---- 3. the record ------------------------------------------------------------------------
  {
    const char* ep =
        "@LAT103LON16384 | created:0 | updated:0\n"
        "said: 1 | **MOTIONWIN** t_ms:60000 stream:0x0000aaaa wall:0\n"
        "said: 2 | **MOTION** dev_mean_mg:8\n";
    const char* ep2 =
        "@LAT103LON16385 | created:0 | updated:0\n"
        "said: 1 | **MOTIONWIN** t_ms:120000 stream:0x0000aaaa wall:0\n"
        "said: 2 | **MOTION** dev_mean_mg:50\n";
    Fold f(CH_MOTION);
    f.add(ep, strlen(ep), 16384);
    f.add(ep2, strlen(ep2), 16385);
    static char rec[PRECISION_RECORD_BUF];
    const char* stamp = "t_ms:120000 stream:0x0000aaaa wall:0";
    const size_t m = render(rec, sizeof(rec), f, 0x300, 3, 1790000000u, 1795305600u, stamp);
    CHECK(m > 0 && m < sizeof(rec), "record renders inside PRECISION_RECORD_BUF (%zu B)", m);
    TtdbRecord hr;
    const char* hdr = strchr(rec, '@');
    CHECK(hdr && ttdbParseHeader(hdr, hr) && hr.lat == 108 && hr.lon == CH_MOTION,
          "header is @LAT108LON2");
    uint32_t hs = 0;
    CHECK(ttdbHeaderSid(rec, hs), "header carries a sid");
    char key[48];
    keyOf(key, sizeof(key), 0x300, CH_MOTION);
    CHECK(!strcmp(key, "node:0x00000300|chan:motion"), "key is RFC §4.1's (%s)", key);
    CHECK(hs == sid::forKey(0x300, 108, key), "header sid = forKey(node, 108, key)");
    char body_sid[16];
    snprintf(body_sid, sizeof(body_sid), "sid:%08lx", (unsigned long)hs);
    CHECK(strstr(strstr(rec, "**PRECISION**"), body_sid) != NULL, "body sid equals header sid");
    TtdbEw ew;
    CHECK(ttdbParseEw(rec, m, ew) && ew.conf == f.conf() && ew.rev == 3 && !ew.has_prec,
          "[ew] reads back conf %u rev 3 (stage 1 reader)", ew.conf);
    OnFlash of;
    readOnFlash(rec, m, of);
    CHECK(of.present && of.prec == f.prec() && of.rev == 3 && of.created == 1790000000u,
          "readOnFlash: prec %u rev %u created %lu", of.prec, of.rev, (unsigned long)of.created);
    CHECK(strstr(rec, "predictor:previous_window") && strstr(rec, "from:@LAT103LON16384") &&
              strstr(rec, "through:@LAT103LON16385") && strstr(rec, "pe_span:60") &&
              strstr(rec, "**STAMP** t_ms:120000"),
          "FOLD/STAMP lines carry the range, span and predictor");
    CHECK(render(rec, 64, f, 0x300, 0, 0, 0, stamp) == 0, "a short buffer renders nothing");
    // worst case fits: 5 digit lons, 10 digit counts
    Fold big(CH_ENTITY);
    CHECK(render(rec, sizeof(rec), big, 0xFFFFFFFFu, 65535, 4294967295u, 4294967295u,
                 "t_ms:18446744073709551615 stream:0xffffffff wall:1") > 0,
          "a wide record still fits PRECISION_RECORD_BUF");
  }

  // ---- 4. the write rule and overflow ------------------------------------------------------
  {
    Fold none(CH_LINK);
    OnFlash absent;
    CHECK(!shouldWrite(absent, none), "n = 0 writes nothing");
    const char* a = "@LAT103LON0 | x\n**LINKWIN** t_ms:1 stream:0x1\n**LINK** peer:0x1 proto:ble rssi_med:-50\n";
    const char* b = "@LAT103LON1 | x\n**LINKWIN** t_ms:2 stream:0x1\n**LINK** peer:0x1 proto:ble rssi_med:-50\n";
    Fold f(CH_LINK);
    f.add(a, strlen(a), 0);
    f.add(b, strlen(b), 1);
    CHECK(f.n() == 1 && f.prec() == 255, "one zero residual -> prec 255");
    CHECK(shouldWrite(absent, f), "nothing on flash -> write");
    OnFlash near;
    near.present = true;
    near.prec = 247;
    CHECK(!shouldWrite(near, f), "|255 - 247| = 8 -> no write");
    near.prec = 246;
    CHECK(shouldWrite(near, f), "|255 - 246| = 9 -> write");
    // overflow EXCLUDES the window; it never truncates it
    std::string many = "@LAT103LON0 | x\n**LINKWIN** t_ms:1 stream:0x1\n";
    for (int i = 0; i < PRECISION_MAX_LINK_KEYS + 1; ++i) {
      char ln[96];
      snprintf(ln, sizeof(ln), "**LINK** peer:0x%08x proto:ble rssi_med:-50\n", i);
      many += ln;
    }
    Window w;
    parseWindow(CH_LINK, many.data(), many.size(), w);
    CHECK(w.why == OVERFLOW, "more link keys than PRECISION_MAX_LINK_KEYS -> excluded (overflow)");
    std::string longid = "@LAT103LON8192 | x\n**ENTWIN** t_ms:1 stream:0x1\n**ENTITY** id:0123456789abcdef0\n";
    parseWindow(CH_ENTITY, longid.data(), longid.size(), w);
    CHECK(w.why == OVERFLOW, "an id longer than PRECISION_ID_MAX -> excluded (overflow)");
    Fold sk(CH_MOTION);
    sk.skip(16384);
    CHECK(sk.skipped() == 1 && sk.episodes() == 1 && sk.from() == 16384, "skip() is counted");
  }

  printf("RESULT %s: %d of %d checks failed\n", gFails ? "FAIL" : "OK", gFails, gChecks);
  return gFails ? 1 : 0;
}
