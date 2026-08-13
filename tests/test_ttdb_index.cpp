// test_ttdb_index.cpp — the TTDB index cap: what happens when a node's file outgrows
// `TTDB_MAX_RECORDS`, and what a lane prune does to the records past it.
//
// ⚠ THE BUG THIS FILE EXISTS FOR, which the fleet has now hit TWICE in two layers:
//
//   `removeLaneRange` rewrites the file by walking the INDEX, not the file. Records past
//   the cap are not in the index, and `recordSpan` used to end the LAST indexed record at
//   EOF — so that one span swallowed the entire unindexed tail. Prune a lane that happens
//   to own record #TTDB_MAX_RECORDS and every record behind it is deleted, silently.
//
// Layer one was `appendRecord`, fixed 2026-08-09 after five @LAT101 records were written
// "successfully" past the index and erased by the next belief-lane rewrite. Layer two is
// `begin()`, which until 2026-08-11 simply stopped recording offsets at the cap and
// returned true — so a file that had outgrown its index was indistinguishable from one
// that fitted. `recordCount()` is what is VISIBLE; `headersSeen()` is what EXISTS.
//
// This is the first native test to drive the REAL `Ttdb` (via tests/shim/), rather than
// replicating its scan the way test_rfc_ttdb.cpp has to. That matters here: the defect is
// in the interaction between begin(), recordSpan() and removeLaneRange(), which a replica
// of any one of them cannot reproduce.
//
// Built with -DTTDB_MAX_RECORDS=16 so the cap is reachable in a fixture.
#include "TTDB.h"
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

static int fails = 0;
#define CHECK(cond, ...)            \
  do {                              \
    if (cond) {                     \
      printf("PASS: " __VA_ARGS__); \
      printf("\n");                 \
    } else {                        \
      printf("FAIL: " __VA_ARGS__); \
      printf("\n");                 \
      ++fails;                      \
    }                               \
  } while (0)

static const char* kPath = "test_ttdb_index.tmp.md";
static fs::FS gFs;

// One well-formed record block, byte-shaped like a real TTDB (TTDB-RFC-0001 §3).
static std::string block(int lat, int lon, int tag) {
  char b[256];
  snprintf(b, sizeof(b),
           "\n---\n\n@LAT%dLON%d | created:0 | updated:0 | "
           "relates:observes@LAT0LON0\n\n**BODY** tag:body-%d\n",
           lat, lon, tag);
  return std::string(b);
}

static void writeFixture(const std::vector<std::pair<int, int> >& lanes) {
  FILE* f = fopen(kPath, "wb");
  const char* pre = "# ttdb fixture\n";
  fwrite(pre, 1, strlen(pre), f);
  for (size_t i = 0; i < lanes.size(); ++i) {
    std::string b = block(lanes[i].first, lanes[i].second, (int)i);
    fwrite(b.data(), 1, b.size(), f);
  }
  fclose(f);
}

static std::string slurp() {
  FILE* f = fopen(kPath, "rb");
  if (!f) return std::string();
  std::string out;
  char buf[512];
  size_t n;
  while ((n = fread(buf, 1, sizeof(buf), f)) > 0) out.append(buf, n);
  fclose(f);
  return out;
}

static int countHeaders(const std::string& s) {
  int n = 0;
  for (size_t i = 0; i + 1 < s.size(); ++i)
    if (s[i] == '\n' && s[i + 1] == '@') ++n;
  return n;
}

static bool has(const std::string& s, const char* needle) {
  return s.find(needle) != std::string::npos;
}

int main() {
  printf("TTDB_MAX_RECORDS = %d\n\n", TTDB_MAX_RECORDS);

  // -----------------------------------------------------------------------
  // 1) A file that FITS: the new accounting must be invisible.
  // -----------------------------------------------------------------------
  {
    std::vector<std::pair<int, int> > lanes;
    for (int i = 0; i < 12; ++i) lanes.push_back(std::make_pair(96, i));
    writeFixture(lanes);

    Ttdb db;
    CHECK(db.begin(gFs, kPath), "begin() on a file that fits");
    CHECK(db.recordCount() == 12, "12 records indexed (got %d)", db.recordCount());
    CHECK(db.headersSeen() == 12, "12 headers seen (got %u)",
          (unsigned)db.headersSeen());
    CHECK(!db.indexSaturated(), "not saturated");
    CHECK(db.droppedRecords() == 0, "nothing dropped");
    CHECK(db.indexHeadroom() == TTDB_MAX_RECORDS - 12,
          "headroom is the whole-FILE budget, not one lane's (got %d)",
          db.indexHeadroom());

    size_t off, len;
    CHECK(db.recordSpan(11, off, len), "recordSpan of the last record");
    CHECK(off + len == db.fileSize(),
          "and on an unsaturated file it still runs to EOF — the fix must not "
          "change the normal case");
  }

  // -----------------------------------------------------------------------
  // 2) A file that does NOT fit: saturation is now VISIBLE.
  // -----------------------------------------------------------------------
  {
    std::vector<std::pair<int, int> > lanes;
    for (int i = 0; i < TTDB_MAX_RECORDS; ++i) lanes.push_back(std::make_pair(96, i));
    for (int i = 0; i < 4; ++i) lanes.push_back(std::make_pair(50, i));
    writeFixture(lanes);

    Ttdb db;
    CHECK(db.begin(gFs, kPath), "begin() STILL RETURNS TRUE on an over-cap file");
    CHECK(db.recordCount() == TTDB_MAX_RECORDS, "index is full (got %d)",
          db.recordCount());
    CHECK(db.headersSeen() == (uint32_t)TTDB_MAX_RECORDS + 4,
          "but every header in the FILE is counted (got %u, want %d)",
          (unsigned)db.headersSeen(), TTDB_MAX_RECORDS + 4);
    CHECK(db.indexSaturated(), "so the node can SAY it has outgrown its index");
    CHECK(db.droppedRecords() == 4, "and by how much (got %u)",
          (unsigned)db.droppedRecords());
    CHECK(db.indexHeadroom() == 0, "no headroom left");

    size_t off, len;
    CHECK(db.recordSpan(TTDB_MAX_RECORDS - 1, off, len), "span of the last INDEXED record");
    CHECK(off + len < db.fileSize(),
          "⚠ it must NOT run to EOF: ending there made this one span swallow every "
          "unindexed record behind it (off+len %u, size %u)",
          (unsigned)(off + len), (unsigned)db.fileSize());
  }

  // -----------------------------------------------------------------------
  // 3) THE REGRESSION. Prune the lane that owns the last INDEXED record on a
  //    saturated file. Every unindexed record behind it must survive.
  //    Before the fix this deleted all four and reported success.
  // -----------------------------------------------------------------------
  {
    std::vector<std::pair<int, int> > lanes;
    for (int i = 0; i < TTDB_MAX_RECORDS; ++i) lanes.push_back(std::make_pair(96, i));
    for (int i = 0; i < 4; ++i) lanes.push_back(std::make_pair(50, i));
    writeFixture(lanes);

    Ttdb db;
    db.begin(gFs, kPath);
    const int tail_tag0 = TTDB_MAX_RECORDS;   // fixture tags are the record ordinal
    CHECK(db.indexSaturated(), "fixture is saturated before the prune");

    CHECK(db.removeLaneRange(96, 96), "prune @LAT96 (which owns the last indexed record)");

    std::string after = slurp();
    char needle[64];
    bool all_present = true;
    for (int i = 0; i < 4; ++i) {
      snprintf(needle, sizeof(needle), "tag:body-%d\n", tail_tag0 + i);
      if (!has(after, needle)) all_present = false;
    }
    CHECK(all_present,
          "⚠ ALL FOUR UNINDEXED RECORDS SURVIVED THE PRUNE — the tail is carried "
          "verbatim because we cannot know whether it belongs to the pruned lane, and "
          "keeping a stale record beats destroying evidence");
    CHECK(!has(after, "@LAT96LON0 "), "and the pruned lane really is gone");
    CHECK(countHeaders(after) == 4, "exactly the 4 tail records remain (got %d)",
          countHeaders(after));

    // Convergence: the prune freed index slots, so the previously-invisible records
    // are now indexed. Repeated prunes make progress instead of eating the tail.
    Ttdb db2;
    CHECK(db2.begin(gFs, kPath), "re-open after the prune");
    CHECK(db2.recordCount() == 4 && !db2.indexSaturated(),
          "the freed slots surface the tail: 4 records, no longer saturated (got %d)",
          db2.recordCount());
    CHECK(db2.record(0).lat == 50, "and they parse as the lane they always were");
  }

  // -----------------------------------------------------------------------
  // 4) A prune on a file that fits still behaves exactly as before.
  // -----------------------------------------------------------------------
  {
    std::vector<std::pair<int, int> > lanes;
    for (int i = 0; i < 5; ++i) lanes.push_back(std::make_pair(96, i));
    for (int i = 0; i < 3; ++i) lanes.push_back(std::make_pair(50, i));
    writeFixture(lanes);

    Ttdb db;
    db.begin(gFs, kPath);
    CHECK(!db.indexSaturated(), "control fixture fits the index");
    CHECK(db.removeLaneRange(96, 96), "prune @LAT96");
    std::string after = slurp();
    CHECK(countHeaders(after) == 3, "3 records left (got %d)", countHeaders(after));
    CHECK(!has(after, "@LAT96"), "no @LAT96 survives");
    CHECK(has(after, "tag:body-5") && has(after, "tag:body-7"),
          "and the kept lane is intact");
  }

  // -----------------------------------------------------------------------
  // 5) appendRecord still refuses at the cap (the 2026-08-09 fix), and the
  //    refusal does not corrupt the accounting.
  // -----------------------------------------------------------------------
  {
    std::vector<std::pair<int, int> > lanes;
    for (int i = 0; i < TTDB_MAX_RECORDS; ++i) lanes.push_back(std::make_pair(96, i));
    writeFixture(lanes);

    Ttdb db;
    db.begin(gFs, kPath);
    CHECK(!db.indexSaturated(), "a file exactly AT the cap is not saturated");
    CHECK(db.indexHeadroom() == 0, "but it has no headroom");
    std::string b = block(50, 0, 999);
    CHECK(!db.appendRecord(b.c_str(), b.size()),
          "appendRecord REFUSES rather than writing past the index");
    CHECK(countHeaders(slurp()) == TTDB_MAX_RECORDS,
          "and not one byte was written (got %d headers)", countHeaders(slurp()));
  }

  // -----------------------------------------------------------------------
  // 6) A lane rewrite NAMES the step it failed at (2026-08-13).
  //
  //    `removeLaneRange` returned a bare `false` from seven places. On 2026-08-13 the
  //    Cardputer refused every lane rewrite — @LAT96 from an operator prune, @LAT101 from
  //    the social field's own heartbeat — while V4-A ran the identical code on the
  //    identical command and succeeded, and nothing could say WHICH of the seven it was.
  //    A boolean is the wrong return type for that, so the step is now recorded.
  // -----------------------------------------------------------------------
  {
    std::vector<std::pair<int, int> > lanes;
    for (int i = 0; i < 4; ++i) lanes.push_back(std::make_pair(96, i));
    for (int i = 0; i < 2; ++i) lanes.push_back(std::make_pair(50, i));
    writeFixture(lanes);

    Ttdb db;
    db.begin(gFs, kPath);

    // A refused lane names itself as bad args and — the load-bearing half — does NOT
    // touch the file. The guard that keeps a prune off @LAT98/@LAT99 is the reason.
    CHECK(!db.removePerceptLanes(99), "removePerceptLanes(99) is refused");
    CHECK(db.lastRewriteErr() == TTDB_RW_BAD_ARGS,
          "and names the step 'bad-args' (got '%s')", db.lastRewriteErrName());
    CHECK(countHeaders(slurp()) == 6, "the refusal wrote nothing (got %d headers)",
          countHeaders(slurp()));

    // A reversed range is the other bad-args arm.
    CHECK(!db.removeLaneRange(97, 94), "a reversed range is refused");
    CHECK(db.lastRewriteErr() == TTDB_RW_BAD_ARGS, "and names 'bad-args'");

    // A SUCCESSFUL prune clears the error, so a stale reason can never be read as a
    // fresh failure — the trap every "last error" accessor sets for its callers.
    CHECK(db.removeLaneRange(96, 96), "a real prune succeeds");
    CHECK(db.lastRewriteErr() == TTDB_RW_OK,
          "and RESETS the reason to 'ok' (got '%s')", db.lastRewriteErrName());

    // An idempotent no-op prune is a success, not a silent failure.
    CHECK(db.removeLaneRange(96, 96), "pruning an already-empty lane is idempotent");
    CHECK(db.lastRewriteErr() == TTDB_RW_OK, "and stays 'ok'");
  }

  // -----------------------------------------------------------------------
  // 6b) WHICH FAILURES ARE WORTH RETRYING AT BOOT (2026-08-13).
  //
  //     A heap-starved node schedules a failed prune for its next boot, where the same
  //     code succeeds at ~147 KB instead of ~7 KB. That is only sound for failures caused
  //     by a MISSING RESOURCE. The three excluded cases are excluded for real reasons, not
  //     for being unlikely: BAD_ARGS can never succeed at any heap, and RENAME/REINDEX
  //     both happen after the original file is gone.
  // -----------------------------------------------------------------------
  {
    CHECK(ttdbRewriteRetryable(TTDB_RW_OPEN_SRC), "open-src is retryable at boot");
    CHECK(ttdbRewriteRetryable(TTDB_RW_OPEN_TMP), "open-tmp is retryable at boot");
    CHECK(ttdbRewriteRetryable(TTDB_RW_READ), "read is retryable at boot");
    CHECK(ttdbRewriteRetryable(TTDB_RW_WRITE), "write is retryable at boot");
    CHECK(!ttdbRewriteRetryable(TTDB_RW_BAD_ARGS),
          "bad-args is NOT — a forbidden lane is forbidden at every heap size");
    CHECK(!ttdbRewriteRetryable(TTDB_RW_RENAME),
          "RENAME is NOT — the original is already gone, so a blind retry reasons about "
          "a file that moved");
    CHECK(!ttdbRewriteRetryable(TTDB_RW_REINDEX),
          "reindex is NOT — the rewrite already committed");
    CHECK(!ttdbRewriteRetryable(TTDB_RW_OK),
          "⚠ and OK is NOT retryable: it means NO REWRITE WAS ATTEMPTED (a prune refused "
          "by a full @LAT100 never reaches one), which must never be rescheduled");

    // clearRewriteErr is what makes that last check meaningful — without it a
    // never-attempted prune inherits the previous rewrite's reason and could be
    // rescheduled forever off a stale value.
    std::vector<std::pair<int, int> > lanes;
    for (int i = 0; i < 3; ++i) lanes.push_back(std::make_pair(96, i));
    writeFixture(lanes);
    Ttdb db;
    db.begin(gFs, kPath);
    CHECK(!db.removePerceptLanes(99), "a refused lane records bad-args");
    CHECK(db.lastRewriteErr() == TTDB_RW_BAD_ARGS, "…as expected");
    db.clearRewriteErr();
    CHECK(db.lastRewriteErr() == TTDB_RW_OK,
          "clearRewriteErr resets it, so 'no rewrite attempted' is distinguishable");
  }

  // -----------------------------------------------------------------------
  // 7) A STALE `.tmp` FROM A DIED REWRITE DOES NOT BLOCK OR CORRUPT THE NEXT ONE.
  //
  //    A rewrite that dies between creating the temp and renaming it leaves a full-size
  //    second copy of the TTDB on the filesystem. On a node whose store is a third of its
  //    partition that is exactly how the NEXT rewrite runs out of room — so the orphan is
  //    now cleared before the new temp is opened.
  // -----------------------------------------------------------------------
  {
    std::vector<std::pair<int, int> > lanes;
    for (int i = 0; i < 3; ++i) lanes.push_back(std::make_pair(96, i));
    for (int i = 0; i < 2; ++i) lanes.push_back(std::make_pair(50, i));
    writeFixture(lanes);

    // Plant an orphan temp holding believable garbage, exactly as a died rewrite would.
    std::string tmp_path = std::string(kPath) + ".tmp";
    {
      FILE* t = fopen(tmp_path.c_str(), "wb");
      const char* junk = "# half-written orphan\n\n---\n\n@LAT96LON9 | created:0\n";
      fwrite(junk, 1, strlen(junk), t);
      fclose(t);
    }

    Ttdb db;
    db.begin(gFs, kPath);
    CHECK(db.removeLaneRange(96, 96), "the prune succeeds despite an orphan .tmp");
    CHECK(db.lastRewriteErr() == TTDB_RW_OK, "with no error recorded");

    std::string after = slurp();
    CHECK(countHeaders(after) == 2, "2 records left (got %d)", countHeaders(after));
    CHECK(!has(after, "@LAT96"), "no @LAT96 survives");
    // ⚠ The orphan's content must not have leaked into the live file. It named a @LAT96
    // record, so a rewrite that appended to the stale temp instead of truncating it would
    // resurrect a pruned lane — which reads as a prune that silently did not work.
    CHECK(!has(after, "half-written orphan"),
          "and not one byte of the orphan reached the live TTDB");
    std::remove(tmp_path.c_str());
  }

  std::remove(kPath);
  printf("\n%s\n", fails ? "FAILED" : "all TTDB index checks passed");
  return fails ? 1 : 0;
}
