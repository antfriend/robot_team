// test_precision_job.cpp — the D3b fold job (firmware/libraries/Precision/src/PrecisionJob.h)
// driven against the REAL Ttdb through tests/shim/, with the store changed between passes.
// docs/design/rfc0011-stage3.md §5.1 and D7.
//
// What only this test can show (test_precision.cpp has no store):
//   1. A job spread over passes equals the one-shot Fold over the same episodes, and no
//      pass folds more than PRECISION_JOB_STEP.
//   2. finish() applies the write rule against the record ON FLASH: first write rev 0,
//      unchanged window -> no write, oldest episode cut (window moved) -> rev 1 (D7).
//   3. The store changing mid-job: an unrelated re-index changes nothing; a band episode
//      appended mid-job is folded; the last folded episode cut -> ABORTED; the `from`
//      episode cut -> ABORTED at finish (unverifiable at birth); start() while running
//      is refused.
//   4. An episode bigger than the scratch is counted as skipped, never truncated.
//
// It leaves test_precision_job.out.md behind: tests/test_stage3_gate_py.py gates it, so a
// record written through the real append + removeCuts path is checked by pw1's arithmetic.
#include "PrecisionJob.h"

#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

using namespace precision;

static int gChecks = 0, gFails = 0;
#define CHECK(cond, ...)                         \
  do {                                           \
    ++gChecks;                                   \
    if (!(cond)) {                               \
      ++gFails;                                  \
      printf("FAIL %s:%d: ", __FILE__, __LINE__); \
      printf(__VA_ARGS__);                       \
      printf("\n");                              \
    }                                            \
  } while (0)

static const char* kPath = "test_precision_job.tmp.md";
static const char* kOut = "test_precision_job.out.md";
static fs::FS gFs;
static const int kAco = CH_ACOUSTIC * PRECISION_TIER_SPAN;   // 24576

static std::string aco(int lon, uint64_t t_ms, int rms) {
  char b[400];
  snprintf(b, sizeof(b),
           "\n---\n\n@LAT103LON%d | created:0 | updated:0\nsource: acousticpercept\n"
           "said: 1 | **ACOUSTICWIN** t_ms:%llu stream:0x0000aaaa wall:0 window_ms:60000\n"
           "said: 2 | **ACOUSTIC** rms_mean:%d rms_max:1 peak:1 transients:0\n",
           lon, (unsigned long long)t_ms, rms);
  return b;
}
static std::string other(int lat, int lon) {
  char b[160];
  snprintf(b, sizeof(b), "\n---\n\n@LAT%dLON%d | created:0 | updated:0\n\n**BODY** x\n", lat,
           lon);
  return b;
}
static const int kRms[] = {1000, 1036, 1036, 1107, 1125, 990, 1200};
static const int kN = sizeof(kRms) / sizeof(kRms[0]);

static void writeFixture() {
  std::string s = "# precision job fixture\n";
  s += other(0, 0);
  for (int i = 0; i < kN; ++i) {
    s += aco(kAco + i, 60000ull * (i + 1), kRms[i]);
    if (i == 2) s += other(103, 16384);   // another tier's episode in between
    if (i == 4) s += other(104, 7);       // a checkpoint in between
  }
  s += other(101, 3);
  FILE* f = fopen(kPath, "wb");
  fwrite(s.data(), 1, s.size(), f);
  fclose(f);
}

// The one-shot reference: a fresh Fold over the band's episodes in file order.
static void reference(Ttdb& db, uint8_t chan, Fold& f) {
  static char buf[3072];
  f.reset(chan);
  for (int i = 0; i < db.recordCount(); ++i) {
    const TtdbRecord& r = db.record(i);
    if (r.lat != PRECISION_EPISODE_LANE || chanOfLon(r.lon) != chan) continue;
    size_t off, len;
    db.recordSpan(i, off, len);
    db.readBytes(off, (uint8_t*)buf, len);
    buf[len] = 0;
    f.add(buf, len, r.lon);
  }
}
static bool same(const Fold& a, const Fold& b) {
  return a.var() == b.var() && a.n() == b.n() && a.episodes() == b.episodes() &&
         a.excluded() == b.excluded() && a.segments() == b.segments() &&
         a.from() == b.from() && a.through() == b.through() && a.skipped() == b.skipped();
}

static char gScratch[3072];

// Run a started job to the end, checking the per-pass bound. Returns the final status.
static Job::Status runJob(Job& j, Ttdb& db, int* passes = nullptr, size_t cap = sizeof(gScratch)) {
  Job::Status s;
  int p = 0;
  uint32_t prev_eps = j.fold().episodes();   // the caller may have stepped it already
  do {
    s = j.step(db, gScratch, cap);
    ++p;
    CHECK(j.fold().episodes() - prev_eps <= PRECISION_JOB_STEP,
          "pass %d folded %lu > PRECISION_JOB_STEP", p,
          (unsigned long)(j.fold().episodes() - prev_eps));
    prev_eps = j.fold().episodes();
  } while (s == Job::FOLDING && p < 1000);
  if (passes) *passes = p;
  return s;
}

static OnFlash onFlash(Ttdb& db, uint8_t chan) {
  OnFlash o;
  for (int i = 0; i < db.recordCount(); ++i)
    if (db.record(i).lat == PRECISION_LANE && db.record(i).lon == chan) {
      size_t off, len;
      db.recordSpan(i, off, len);
      db.readBytes(off, (uint8_t*)gScratch, len);
      gScratch[len] = 0;
      readOnFlash(gScratch, len, o);
    }
  return o;
}
static int count108(Ttdb& db) {
  int n = 0;
  for (int i = 0; i < db.recordCount(); ++i) n += db.record(i).lat == PRECISION_LANE;
  return n;
}

int main() {
  const char* stamp = "t_ms:120000 stream:0x0000aaaa wall:0";
  const char* outcome;
  char why[48];

  // ---- 1 + 2: equality with the one-shot fold, and the write rule on flash ---------------
  writeFixture();
  Ttdb db;
  CHECK(db.begin(gFs, kPath), "begin()");
  Fold ref;
  reference(db, CH_ACOUSTIC, ref);
  CHECK(ref.episodes() == (uint32_t)kN && ref.n() == (uint32_t)(kN - 1), "reference folds %d", kN);

  Job j;
  CHECK(j.start(CH_ACOUSTIC), "start()");
  CHECK(!j.start(CH_LINK), "start() while running is refused");
  CHECK(j.fold().chan() == CH_ACOUSTIC, "a refused start() leaves the running job alone");
  int passes = 0;
  CHECK(runJob(j, db, &passes) == Job::READY, "job reaches READY");
  CHECK(passes == (kN + PRECISION_JOB_STEP - 1) / PRECISION_JOB_STEP,
        "%d episodes take %d passes (got %d)", kN,
        (kN + PRECISION_JOB_STEP - 1) / PRECISION_JOB_STEP, passes);
  CHECK(same(j.fold(), ref), "job == one-shot fold (var %ld/%ld n %lu/%lu)", (long)j.fold().var(),
        (long)ref.var(), (unsigned long)j.fold().n(), (unsigned long)ref.n());
  CHECK(j.finish(db, gScratch, sizeof(gScratch), 0x300, 0, stamp, outcome, why, sizeof(why)),
        "first finish writes");
  CHECK(!strcmp(outcome, "yes") && !strcmp(why, "none on flash"), "outcome yes (none on flash), got %s (%s)",
        outcome, why);
  OnFlash o = onFlash(db, CH_ACOUSTIC);
  CHECK(o.present && o.rev == 0 && o.prec == ref.prec() && o.has_from && o.from == kAco,
        "record on flash: rev 0, prec %u, from %ld", o.prec, (long)o.from);
  CHECK(!j.running(), "idle after finish");

  CHECK(j.start(CH_ACOUSTIC), "restart");
  CHECK(runJob(j, db) == Job::READY, "second job READY");
  CHECK(!j.finish(db, gScratch, sizeof(gScratch), 0x300, 0, stamp, outcome, why, sizeof(why)),
        "unchanged window -> no write");
  CHECK(!strcmp(outcome, "no") && !strcmp(why, "d=0"), "outcome no (d=0), got %s (%s)", outcome, why);
  CHECK(count108(db) == 1, "still one @LAT108 record");

  // D7: the oldest episode is cut (as the quota does) -> the window moved -> rewrite, rev 1
  const TtdbCut c0 = {PRECISION_EPISODE_LANE, (int16_t)kAco, (int16_t)kAco};
  CHECK(db.removeCuts(&c0, 1), "cut the oldest acoustic episode");
  CHECK(j.start(CH_ACOUSTIC) && runJob(j, db) == Job::READY, "third job READY");
  CHECK(j.fold().from() == kAco + 1, "from moved to %d", kAco + 1);
  CHECK(j.finish(db, gScratch, sizeof(gScratch), 0x300, 0, stamp, outcome, why, sizeof(why)),
        "window moved -> write (D7) even though prec is close");
  CHECK(strstr(why, "from moved") != nullptr, "why says from moved (%s)", why);
  o = onFlash(db, CH_ACOUSTIC);
  CHECK(o.rev == 1 && o.from == kAco + 1 && count108(db) == 1, "rev 1, from %ld, one record",
        (long)o.from);
  // leave this store for the gate test: the record went through removeCuts + appendRecord
  {
    FILE* in = fopen(kPath, "rb");
    FILE* out = fopen(kOut, "wb");
    char b[4096];
    size_t n;
    while ((n = fread(b, 1, sizeof(b), in)) > 0) fwrite(b, 1, n, out);
    fclose(in);
    fclose(out);
  }

  // ---- 3: the store changing mid-job ------------------------------------------------------
  // (a) unrelated re-index between passes changes nothing
  writeFixture();
  CHECK(db.begin(gFs, kPath), "begin() again");
  reference(db, CH_ACOUSTIC, ref);
  CHECK(j.start(CH_ACOUSTIC), "start (a)");
  CHECK(j.step(db, gScratch, sizeof(gScratch)) == Job::FOLDING, "one pass in");
  const TtdbCut cx = {104, 7, 7};
  CHECK(db.removeCuts(&cx, 1), "cut an unrelated record mid-job (re-index)");
  const std::string ox = other(101, 9);
  CHECK(db.appendRecord(ox.data(), ox.size()), "append an unrelated record mid-job");
  CHECK(runJob(j, db) == Job::READY && same(j.fold(), ref), "unrelated changes: job == reference");
  j.finish(db, gScratch, sizeof(gScratch), 0x300, 0, stamp, outcome, why, sizeof(why));

  // (b) a band episode appended mid-job is folded
  CHECK(j.start(CH_ACOUSTIC), "start (b)");
  j.step(db, gScratch, sizeof(gScratch));
  const std::string late = aco(kAco + kN, 60000ull * (kN + 1), 1150);
  CHECK(db.appendRecord(late.data(), late.size()), "append a band episode mid-job");
  CHECK(runJob(j, db) == Job::READY, "job (b) READY");
  reference(db, CH_ACOUSTIC, ref);
  CHECK(same(j.fold(), ref) && j.fold().through() == kAco + kN &&
            j.fold().episodes() == (uint32_t)kN + 1,
        "appended episode folded: through %ld episodes %lu", (long)j.fold().through(),
        (unsigned long)j.fold().episodes());
  j.finish(db, gScratch, sizeof(gScratch), 0x300, 0, stamp, outcome, why, sizeof(why));

  // (c) the last folded episode is cut -> ABORTED, idle, nothing written
  const int before = count108(db);
  const OnFlash ob = onFlash(db, CH_ACOUSTIC);
  CHECK(j.start(CH_ACOUSTIC), "start (c)");
  CHECK(j.step(db, gScratch, sizeof(gScratch)) == Job::FOLDING, "(c) one pass: folded 2");
  const TtdbCut c2 = {PRECISION_EPISODE_LANE, (int16_t)(kAco + 1), (int16_t)(kAco + 1)};
  CHECK(db.removeCuts(&c2, 1), "cut the LAST FOLDED episode mid-job");
  CHECK(j.step(db, gScratch, sizeof(gScratch)) == Job::ABORTED, "-> ABORTED");
  CHECK(!strcmp(j.abortWhy(), "episode cut mid-fold"), "why: %s", j.abortWhy());
  CHECK(!j.running() && j.aborts() == 1, "idle after abort, aborts 1");
  const OnFlash oa = onFlash(db, CH_ACOUSTIC);
  CHECK(count108(db) == before && oa.rev == ob.rev, "an abort writes nothing");

  // (d) the `from` episode is cut mid-job (last folded survives) -> ABORTED at finish
  CHECK(j.start(CH_ACOUSTIC), "start (d)");
  CHECK(j.step(db, gScratch, sizeof(gScratch)) == Job::FOLDING, "(d) one pass");
  const int32_t from_d = j.fold().from();
  const TtdbCut cf = {PRECISION_EPISODE_LANE, (int16_t)from_d, (int16_t)from_d};
  CHECK(db.removeCuts(&cf, 1), "cut the job's FROM episode mid-job");
  CHECK(runJob(j, db) == Job::ABORTED && !strcmp(j.abortWhy(), "from cut mid-fold"),
        "-> ABORTED (from cut mid-fold), got %s", j.abortWhy());
  CHECK(j.aborts() == 2, "aborts 2");

  // a channel with no episodes: READY at once, n 0, nothing written
  CHECK(j.start(CH_MOTION), "start motion");
  CHECK(j.step(db, gScratch, sizeof(gScratch)) == Job::READY && j.fold().episodes() == 1,
        "motion band: the one stand-in record");
  CHECK(!j.finish(db, gScratch, sizeof(gScratch), 0x300, 0, stamp, outcome, why, sizeof(why)) &&
            !strcmp(why, "n=0"),
        "n = 0 writes nothing (%s)", why);
  CHECK(j.start(CH_ENTITY) && j.step(db, gScratch, sizeof(gScratch)) == Job::READY &&
            j.fold().episodes() == 0,
        "an empty band is READY in one pass");
  j.finish(db, gScratch, sizeof(gScratch), 0x300, 0, stamp, outcome, why, sizeof(why));

  // ---- 4: an episode bigger than the scratch is skipped, not truncated ----------------------
  CHECK(j.start(CH_ACOUSTIC), "start (skip)");
  CHECK(runJob(j, db, nullptr, 64) == Job::READY, "job with a 64 B scratch");
  CHECK(j.fold().skipped() == j.fold().episodes() && j.fold().n() == 0,
        "every episode counted as skipped (%lu of %lu)", (unsigned long)j.fold().skipped(),
        (unsigned long)j.fold().episodes());
  CHECK(!j.finish(db, gScratch, sizeof(gScratch), 0x300, 0, stamp, outcome, why, sizeof(why)),
        "skips only -> n = 0 -> no write");

  remove(kPath);
  printf("RESULT %s: %d of %d checks failed\n", gFails ? "FAIL" : "OK", gFails, gChecks);
  return gFails ? 1 : 0;
}
