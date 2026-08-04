// test_motionpercept.cpp — native pin for the SP0 MOTION tier (@LAT95) and, since
// 2026-08-01, for the transition form it now emits (@LAT93, TTDB-RFC-0006 §5).
//
// This test did not exist until the transition work: MotionPercept.h had admitted for
// months that the tier "has so far been verified only on hardware". Two things made
// writing it non-optional. First, a paired record is a FORMAT with a contract attached
// — §7.1 says an `after` without a `before` is an error, not partial data, and a claim
// like that is worth exactly as much as the test that enforces it. Second, the pair has
// to survive Ttdb::begin()'s record scanner, which treats any line starting with '@' as
// a record header; the check that the `@PERCEPT:` lines stay indented is the one that
// catches a whole class of silent on-device corruption (phantom (0,0) records) that no
// amount of staring at the string literal reliably catches.
//
// Everything here is the real MotionPercept.cpp, unmodified, driven by synthetic
// accelerometer samples — the same discipline as test_linkpercept/test_entitypercept.
#include "MotionPercept.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

// The old API took `(t_ms, bool synced)`. It now takes a timestream::Stamp, and the
// migration is exactly: `synced:1` meant "on SOME shared clock, identity unknown" —
// which is a stream with a wall anchor. `synced:0` meant "local millis()", which is
// stream 0. These tests keep their original intent under the new field.
static const uint32_t kStream = 0x5EA51DE7u;
static timestream::Stamp ST(uint64_t t_ms, bool synced) {
  timestream::Stamp s;
  s.t_ms = t_ms;
  s.stream_id = synced ? kStream : 0;
  s.wall = synced;
  return s;
}

// ---------------------------------------------------------------------------
// helpers
// ---------------------------------------------------------------------------

// Feed one window's worth of samples. `mg` is the deviation from 1 g applied to Z, so
// mg=0 is a dead-still node lying flat and mg=400 is a walking stride.
static void feedWindow(motionpercept::Log& log, uint32_t& now, int mg, int samples) {
  const uint32_t step = MOTIONPERCEPT_FLUSH_MS / (uint32_t)samples;
  for (int i = 0; i < samples; ++i) {
    now += step;
    // alternate the sign so the window has no net drift, only agitation
    int z = 1000 + ((i & 1) ? mg : -mg);
    log.add(0, 0, z, now);
  }
  now += step;  // push past the flush boundary
}

// Value of a `key:` token on a line, as a string. Returns "" when absent.
static const char* field(const char* line, const char* key, char* out, size_t cap) {
  char pat[64];
  snprintf(pat, sizeof(pat), "%s:", key);
  const char* p = strstr(line, pat);
  out[0] = '\0';
  if (!p) return out;
  p += strlen(pat);
  size_t i = 0;
  while (*p && *p != ' ' && *p != '\n' && i + 1 < cap) out[i++] = *p++;
  out[i] = '\0';
  return out;
}

// The whole line containing `needle`, copied out.
static bool lineWith(const char* text, const char* needle, char* out, size_t cap) {
  const char* p = strstr(text, needle);
  if (!p) { out[0] = '\0'; return false; }
  const char* s = p;
  while (s > text && s[-1] != '\n') --s;
  const char* e = strchr(p, '\n');
  size_t n = e ? (size_t)(e - s) : strlen(s);
  if (n >= cap) n = cap - 1;
  memcpy(out, s, n);
  out[n] = '\0';
  return true;
}

// Count lines whose FIRST character is '@' — i.e. what Ttdb::begin() pass 1 would index
// as a record header (TTDB-RFC-0001 §3, TTDB.cpp:24). This is the phantom-record check.
static int recordHeaderLines(const char* text) {
  int n = 0;
  bool line_start = true;
  for (const char* p = text; *p; ++p) {
    if (line_start && *p == '@') ++n;
    line_start = (*p == '\n');
  }
  return n;
}

int main(void) {
  char rec[512], tr[MOTIONPERCEPT_TRANSITION_BUF], buf[128], line[512];

  // -------------------------------------------------------------------------
  // 1. The @LAT95 window record — the format that was only ever hardware-checked
  // -------------------------------------------------------------------------
  {
    motionpercept::Log log;
    uint32_t now = 1000;
    log.reset(now);
    feedWindow(log, now, 0, 60);            // dead still
    CHECK(log.due(now), "a full window of samples is due at %u ms", MOTIONPERCEPT_FLUSH_MS);
    CHECK(log.samples() == 60, "60 samples folded in (got %d)", log.samples());
    CHECK(log.movingPermille() == 0, "still window is 0 permille moving (got %d)",
          log.movingPermille());

    size_t m = log.buildRecord(rec, sizeof(rec), 0, 1785542400ULL, ST(1785542400000ULL, true), now);
    CHECK(m > 0, "buildRecord renders a still window (%zu bytes)", m);
    CHECK(strstr(rec, "\n---\n\n@LAT95LON0 | ") != NULL, "record opens with the separator + @LAT95LON0 header");
    CHECK(strstr(rec, "relates:senses@LAT0LON0") != NULL, "carries the senses edge to the umwelt");
    lineWith(rec, "**MOTION**", line, sizeof(line));
    CHECK(strcmp(field(line, "state", buf, sizeof(buf)), "still") == 0,
          "still window renders state:still (got '%s')", buf);
    lineWith(rec, "**MOTIONWIN**", line, sizeof(line));
    CHECK(strcmp(field(line, "wall", buf, sizeof(buf)), "1") == 0,
          "wall flag propagates (got '%s')", buf);
    CHECK(strcmp(field(line, "stream", buf, sizeof(buf)), "0x5ea51de7") == 0,
          "and so does the stream id — WHICH clock, not just whether (got '%s')", buf);
    CHECK(recordHeaderLines(rec) == 1, "the window record is exactly ONE record header (got %d)",
          recordHeaderLines(rec));

    // An empty window renders nothing rather than a zero-sample claim.
    CHECK(log.buildRecord(rec, sizeof(rec), 1, 0, ST(0, false), now) == 0,
          "an empty window renders no record");
  }

  // -------------------------------------------------------------------------
  // 2. The verdict boundary — 100 permille, per MotionPercept.cpp
  // -------------------------------------------------------------------------
  {
    motionpercept::Log log;
    uint32_t now = 1000;
    log.reset(now);
    // 9 moving samples in 100 = 90 permille: below the line, still a "still" window.
    for (int i = 0; i < 100; ++i) {
      now += 600;
      log.add(0, 0, 1000 + (i < 9 ? 400 : 0), now);
    }
    CHECK(log.movingPermille() == 90, "9/100 moving samples = 90 permille (got %d)",
          log.movingPermille());
    log.buildRecord(rec, sizeof(rec), 0, 0, ST(0, false), now);
    lineWith(rec, "**MOTION**", line, sizeof(line));
    CHECK(strcmp(field(line, "state", buf, sizeof(buf)), "still") == 0,
          "90 permille is still a 'still' window (got '%s')", buf);

    log.reset(now);
    for (int i = 0; i < 100; ++i) {
      now += 600;
      log.add(0, 0, 1000 + (i < 10 ? 400 : 0), now);
    }
    CHECK(log.movingPermille() == 100, "10/100 moving samples = 100 permille (got %d)",
          log.movingPermille());
    log.buildRecord(rec, sizeof(rec), 1, 0, ST(0, false), now);
    lineWith(rec, "**MOTION**", line, sizeof(line));
    CHECK(strcmp(field(line, "state", buf, sizeof(buf)), "moving") == 0,
          "100 permille tips the window to 'moving' (got '%s')", buf);
  }

  // -------------------------------------------------------------------------
  // 3. THE TRANSITION FORM — TTDB-RFC-0006 §5
  // -------------------------------------------------------------------------
  {
    motionpercept::Log log;
    uint32_t now = 1000;
    log.reset(now);

    // ⚠ `lane` here tracks the sketch's `laneCount(95)`, which only advances when a
    // record is actually APPENDED. Under change-triggering most windows write nothing,
    // so a test that hands out a fresh lane per window would silently assert against
    // ordinals the device never allocates — and this pairing is exactly where that
    // would matter, because the `before` half is now usually a suppressed window.
    int lane = 0;

    // Window 0: still. There is no window before it, so there is no transition — the
    // first window of a node's life cannot be an `after` without orphaning a `before`.
    feedWindow(log, now, 0, 60);
    if (log.buildRecord(rec, sizeof(rec), lane, 1000, ST(1000000ULL, true), now)) ++lane;
    CHECK(!log.transitionPending(), "the FIRST window never yields a transition (no orphan `before`)");
    CHECK(log.buildTransition(tr, sizeof(tr), 0, 0x300) == 0,
          "buildTransition writes nothing when nothing is pending");

    // Window 1: still again. Same verdict = no claim, AND no record — it is folded into
    // the run @LAT95LON0 opened.
    feedWindow(log, now, 0, 60);
    if (log.buildRecord(rec, sizeof(rec), lane, 1060, ST(1060000ULL, true), now)) ++lane;
    CHECK(!log.transitionPending(), "still -> still is not a transition");
    CHECK(log.lastClose() == motionpercept::CLOSE_COVERED,
          "...and under run-length it is not even a record");
    CHECK(lane == 1, "so the lane did not advance (got %d)", lane);

    // Window 2: moving. THE CHANGE — which always writes, at the next free ordinal.
    feedWindow(log, now, 400, 60);
    if (log.buildRecord(rec, sizeof(rec), lane, 1120, ST(1120000ULL, true), now)) ++lane;
    CHECK(log.transitionPending(), "still -> moving IS a transition");

    size_t m = log.buildTransition(tr, sizeof(tr), 0, 0x300);
    CHECK(m > 0, "buildTransition renders the pair (%zu bytes)", m);
    CHECK(m < MOTIONPERCEPT_TRANSITION_BUF,
          "the pair fits MOTIONPERCEPT_TRANSITION_BUF (%zu / %d)",
          m, MOTIONPERCEPT_TRANSITION_BUF);
    CHECK(!log.transitionPending(), "the pending flag clears once written (one record per change)");

    // --- the pairing itself (§5.0, §7.1) ---
    CHECK(strstr(tr, "@PERCEPT:before") != NULL, "carries an @PERCEPT:before node");
    CHECK(strstr(tr, "@PERCEPT:after") != NULL, "carries an @PERCEPT:after node");
    CHECK(strstr(tr, "  @PERCEPT:before") != NULL && strstr(tr, "  @PERCEPT:after") != NULL,
          "both @PERCEPT lines are INDENTED (else Ttdb::begin indexes them as records)");
    CHECK(recordHeaderLines(tr) == 1,
          "the pair is exactly ONE record header, no phantoms (got %d)", recordHeaderLines(tr));

    // --- the edge is the datum (§5.2) ---
    lineWith(tr, "**TRANSITION**", line, sizeof(line));
    CHECK(strcmp(field(line, "from", buf, sizeof(buf)), "still") == 0,
          "from:still (got '%s')", buf);
    CHECK(strcmp(field(line, "to", buf, sizeof(buf)), "moving") == 0,
          "to:moving (got '%s')", buf);
    CHECK(strcmp(field(line, "dt_ms", buf, sizeof(buf)), "60000") == 0,
          "dt_ms is the gap between the two window stamps (got '%s')", buf);
    // §7.3: the agent anchor is mandatory — a transition with no subject is propositional.
    CHECK(strcmp(field(line, "node", buf, sizeof(buf)), "0x300") == 0,
          "the perceiving subject is named (got '%s')", buf);

    lineWith(tr, "  @PERCEPT:before", line, sizeof(line));
    CHECK(strcmp(field(line, "state", buf, sizeof(buf)), "still") == 0,
          "before half is the CLOSING window's state (got '%s')", buf);
    // ⚠ THE `before` HALF IS A SUPPRESSED WINDOW, and this is the check that keeps the
    // citation honest. It was window 1 of the run that @LAT95LON0 opened, so it is
    // addressed as `LON0+1` — NOT as `LON0`, which describes a different window, and not
    // as `LON1`, which is the record the CHANGE went to.
    CHECK(strcmp(field(line, "lane", buf, sizeof(buf)), "@LAT95LON0+1") == 0,
          "before half addresses its covering record AND its offset in that run (got '%s')", buf);
    lineWith(tr, "  @PERCEPT:after", line, sizeof(line));
    CHECK(strcmp(field(line, "state", buf, sizeof(buf)), "moving") == 0,
          "after half is the OPENING window's state (got '%s')", buf);
    CHECK(strcmp(field(line, "lane", buf, sizeof(buf)), "@LAT95LON1+0") == 0,
          "after half addresses its own record at offset 0 (got '%s')", buf);

    // The pair is also written as traversable edges, per §5.2 / RFC-0003 v1.1 §7.3.
    // ⚠ The EDGES stay plain ordinals with no `+k`: an edge must resolve to a record
    // that exists, and the covering record does. The offset lives in the body, where it
    // qualifies the citation without breaking traversal.
    CHECK(strstr(tr, "derived_from@LAT95LON0,derived_from@LAT95LON1") != NULL,
          "both halves are reachable from the edge list, not only from the body");
    CHECK(strstr(tr, "derived_from@LAT95LON0+1") == NULL,
          "and the edge list carries no `+k` — that would not resolve to a record");
    char hdr[512];
    lineWith(tr, "@LAT93LON", hdr, sizeof(hdr));
    CHECK(strncmp(hdr, "@LAT93LON0 | ", 13) == 0,
          "written to the @LAT93 transition lane (got '%.20s')", hdr);
    CHECK(strlen(hdr) < 255, "header line %zu chars < Ttdb::readLine's 256 cap", strlen(hdr));

    // --- the delta (§5.3: ∂[v0,v1] = v1 - v0) ---
    lineWith(tr, "**DELTA**", line, sizeof(line));
    CHECK(strcmp(field(line, "d_permille", buf, sizeof(buf)), "1000") == 0,
          "d_permille is after - before (got '%s')", buf);

    // Window 3: moving again — no claim. Window 4: still — the reverse transition.
    feedWindow(log, now, 400, 60);
    log.buildRecord(rec, sizeof(rec), 3, 1180, ST(1180000ULL, true), now);
    CHECK(!log.transitionPending(), "moving -> moving is not a transition");
    feedWindow(log, now, 0, 60);
    log.buildRecord(rec, sizeof(rec), 4, 1240, ST(1240000ULL, true), now);
    CHECK(log.transitionPending(), "moving -> still IS a transition (the edge runs both ways)");
    log.buildTransition(tr, sizeof(tr), 1, 0x300);
    lineWith(tr, "**TRANSITION**", line, sizeof(line));
    CHECK(strcmp(field(line, "from", buf, sizeof(buf)), "moving") == 0 &&
              strcmp(field(line, "to", buf, sizeof(buf)), "still") == 0,
          "the reverse pair reads moving -> still");
    lineWith(tr, "**DELTA**", line, sizeof(line));
    CHECK(strcmp(field(line, "d_permille", buf, sizeof(buf)), "-1000") == 0,
          "the reverse delta is signed (got '%s')", buf);
  }

  // -------------------------------------------------------------------------
  // 4. A discarded window BREAKS the chain rather than pairing across the gap
  // -------------------------------------------------------------------------
  {
    motionpercept::Log log;
    uint32_t now = 1000;
    log.reset(now);
    feedWindow(log, now, 0, 60);
    log.buildRecord(rec, sizeof(rec), 0, 1000, ST(1000000ULL, true), now);

    // What the sketch does when the @LAT95 lane is full: the window is thrown away.
    feedWindow(log, now, 400, 60);
    log.reset(now);

    // The next window is `moving`, and the last window ANYONE WROTE was `still` — but
    // they are not adjacent, so claiming a transition here would assert an edge across
    // a window that was measured and discarded.
    feedWindow(log, now, 400, 60);
    log.buildRecord(rec, sizeof(rec), 1, 1180, ST(1180000ULL, true), now);
    CHECK(!log.transitionPending(),
          "a discarded window breaks the chain (no transition across the gap)");
  }

  // -------------------------------------------------------------------------
  // 5. Truncation writes NOTHING — a half-written pair is the orphan §7.1 forbids
  // -------------------------------------------------------------------------
  {
    motionpercept::Log log;
    uint32_t now = 1000;
    log.reset(now);
    feedWindow(log, now, 0, 60);
    log.buildRecord(rec, sizeof(rec), 0, 1000, ST(1000000ULL, true), now);
    feedWindow(log, now, 400, 60);
    log.buildRecord(rec, sizeof(rec), 1, 1060, ST(1060000ULL, true), now);
    CHECK(log.transitionPending(), "transition armed for the truncation check");

    char tiny[80];
    memset(tiny, 'x', sizeof(tiny));
    CHECK(log.buildTransition(tiny, sizeof(tiny), 0, 0x300) == 0,
          "a pair that does not fit renders 0 bytes, not a truncated `before`");
    CHECK(!log.transitionPending(),
          "and does not stay pending to be half-written again next pass");
  }

  // -------------------------------------------------------------------------
  // 6. Unsynced clock: the transition is still emitted, and says so
  // -------------------------------------------------------------------------
  {
    motionpercept::Log log;
    uint32_t now = 1000;
    log.reset(now);
    feedWindow(log, now, 0, 60);
    log.buildRecord(rec, sizeof(rec), 0, 0, ST(61000ULL, false), now);
    feedWindow(log, now, 400, 60);
    log.buildRecord(rec, sizeof(rec), 1, 0, ST(121000ULL, false), now);
    size_t m = log.buildTransition(tr, sizeof(tr), 0, 0x300);
    CHECK(m > 0, "a node on no stream still records its own transitions");
    lineWith(tr, "**TRANSITION**", line, sizeof(line));
    CHECK(strcmp(field(line, "stream", buf, sizeof(buf)), "0x00000000") == 0,
          "and marks them stream:0 so they are not ordered against another node "
          "(got '%s')", buf);
    CHECK(strcmp(field(line, "dt_ms", buf, sizeof(buf)), "60000") == 0,
          "dt_ms is still meaningful on one node's own clock (got '%s')", buf);
    CHECK(strcmp(field(line, "dt_across_merge", buf, sizeof(buf)), "0") == 0,
          "and dt is trustworthy: both halves came from the same clock (got '%s')", buf);
  }

  // 6b. A stream merge BETWEEN the two windows makes dt_ms an over-estimate, and the
  // record has to say so — the numbers alone cannot: a merge offset lands in the
  // subtraction and reads as elapsed time that never happened.
  {
    motionpercept::Log log;
    uint32_t now = 0;
    char tr[MOTIONPERCEPT_TRANSITION_BUF], line[512], buf[64];
    char rec[512];
    timestream::Stamp before = ST(61000ULL, false);   // stream 0: local millis()
    timestream::Stamp after = ST(3721000ULL, true);   // adopted an hour-old stream
    feedWindow(log, now, 0, 60);
    log.buildRecord(rec, sizeof(rec), 0, 0, before, now);
    feedWindow(log, now, 400, 60);
    log.buildRecord(rec, sizeof(rec), 1, 0, after, now);
    size_t m = log.buildTransition(tr, sizeof(tr), 0, 0x300);
    CHECK(m > 0, "the transition is still written across a merge");
    lineWith(tr, "**TRANSITION**", line, sizeof(line));
    CHECK(strcmp(field(line, "dt_across_merge", buf, sizeof(buf)), "1") == 0,
          "flagged: the two halves are on DIFFERENT clocks (got '%s')", buf);
    CHECK(strcmp(field(line, "dt_ms", buf, sizeof(buf)), "3660000") == 0,
          "dt_ms is the raw difference — an over-estimate by exactly the merge "
          "offset, which @LAT90's REMAP records, so it is recoverable (got '%s')", buf);
  }

  // -------------------------------------------------------------------------
  // 7. RUN-LENGTH — the lane is change-triggered, and says how much it suppressed
  //
  // This is the section that makes the treadmill fix honest. It is not enough that
  // fewer records are written; the lane has to still answer "how long was this node
  // still?" exactly, or every statistic derived from it (including the B.3 run that
  // measured MOTIONPERCEPT_MOVING_MG) silently weights a 30-window run like a 1-window
  // one.
  // -------------------------------------------------------------------------
  {
    motionpercept::Log log;
    uint32_t now = 1000;
    log.reset(now);
    char rec[MOTIONPERCEPT_RECORD_BUF];
    char line[512], buf[128];

    // Ten still windows in a row — the shelf case that used to cost ten records.
    int lane = 0, records = 0;
    for (int w = 0; w < 10; ++w) {
      feedWindow(log, now, 0, 60);
      size_t m = log.buildRecord(rec, sizeof(rec), lane, 1000 + 60 * w,
                                 ST(1000000ULL + 60000ULL * (uint32_t)w, true), now);
      if (m) { ++lane; ++records; }
    }
    CHECK(records == 1, "ten still windows write ONE record, not ten (got %d)", records);
    CHECK(log.runLength() == 10, "and the run knows it covers all ten (got %d)",
          log.runLength());
    CHECK(log.lastClose() == motionpercept::CLOSE_COVERED,
          "the tenth window was covered, not dropped");
    CHECK(log.coveringLane() == 0 && log.runOffset() == 9,
          "and it is addressable as @LAT95LON%d+%d", log.coveringLane(), log.runOffset());

    // The eleventh window MOVES. A change is never deferred.
    feedWindow(log, now, 400, 60);
    size_t m = log.buildRecord(rec, sizeof(rec), lane, 1660, ST(1660000ULL, true), now);
    CHECK(m > 0, "a verdict CHANGE writes immediately (%zu bytes)", m);
    CHECK(log.lastClose() == motionpercept::CLOSE_WRITTEN, "reported as WRITTEN");
    CHECK(m < MOTIONPERCEPT_RECORD_BUF,
          "a record carrying a COVERED block fits MOTIONPERCEPT_RECORD_BUF (%zu / %d)",
          m, MOTIONPERCEPT_RECORD_BUF);
    CHECK(m > 320,
          "...and would NOT have fitted the sketch's old 320 B buffer (%zu) — which is "
          "why the constant moved with the format", m);
    CHECK(recordHeaderLines(rec) == 1,
          "still exactly one record header (got %d)", recordHeaderLines(rec));

    lineWith(rec, "**RUN**", line, sizeof(line));
    CHECK(strcmp(field(line, "windows_since_last", buf, sizeof(buf)), "10") == 0,
          "windows_since_last counts the 9 suppressed windows AND this one (got '%s')", buf);
    CHECK(strcmp(field(line, "reason", buf, sizeof(buf)), "changed") == 0,
          "and says why it was written (got '%s')", buf);

    // The COVERED block: the nine suppressed windows as one long window.
    lineWith(rec, "**COVERED**", line, sizeof(line));
    CHECK(strcmp(field(line, "state", buf, sizeof(buf)), "still") == 0,
          "the covered windows carry the RUN's state, not this record's (got '%s')", buf);
    CHECK(strcmp(field(line, "windows", buf, sizeof(buf)), "9") == 0,
          "nine of them — windows_since_last minus this record's own (got '%s')", buf);
    CHECK(strcmp(field(line, "n", buf, sizeof(buf)), "540") == 0,
          "with every sample accounted for: 9 x 60 (got '%s')", buf);
    CHECK(strcmp(field(line, "moving_permille", buf, sizeof(buf)), "0") == 0,
          "aggregated over SAMPLES, not as a mean of means (got '%s')", buf);
    CHECK(strcmp(field(line, "covered_by", buf, sizeof(buf)), "@LAT95LON0") == 0,
          "and it names the record whose run they belonged to (got '%s')", buf);
    CHECK(strcmp(field(line, "first_t_ms", buf, sizeof(buf)), "1060000") == 0,
          "the span starts at the first suppressed window (got '%s')", buf);
    CHECK(strcmp(field(line, "last_t_ms", buf, sizeof(buf)), "1540000") == 0,
          "and ends at the last (got '%s')", buf);

    // Total accounting: 10 still windows happened; the lane says so across two records.
    // 1 itemised in @LAT95LON0 + 9 in this record's COVERED block = 10.
    // 9 x 61000: feedWindow() pushes one step past the flush boundary, so a harness
    // window is 61 s. The point is the SUM being present and complete, not the value.
    CHECK(strcmp(field(line, "window_ms", buf, sizeof(buf)), "549000") == 0,
          "every covered window's wall time is summed, so the lane does not understate "
          "stillness (got '%s')", buf);
  }

  // 7b. The heartbeat: an unchanging state is re-asserted after MOTIONPERCEPT_MAX_RUN.
  {
    motionpercept::Log log;
    uint32_t now = 1000;
    log.reset(now);
    char rec[MOTIONPERCEPT_RECORD_BUF];
    char line[512], buf[128];

    int records = 0;
    size_t last = 0;
    for (int w = 0; w < MOTIONPERCEPT_MAX_RUN + 1; ++w) {
      feedWindow(log, now, 0, 60);
      size_t m = log.buildRecord(rec, sizeof(rec), records, 1000 + 60 * w,
                                 ST(1000000ULL + 60000ULL * (uint32_t)w, true), now);
      if (m) { ++records; last = m; }
    }
    CHECK(records == 2,
          "%d identical windows write exactly 2 records: the first and the heartbeat "
          "(got %d)", MOTIONPERCEPT_MAX_RUN + 1, records);
    CHECK(last > 0, "the heartbeat record rendered");
    lineWith(rec, "**RUN**", line, sizeof(line));
    CHECK(strcmp(field(line, "reason", buf, sizeof(buf)), "heartbeat") == 0,
          "and says it was the heartbeat, not a change (got '%s')", buf);
    CHECK(atoi(field(line, "windows_since_last", buf, sizeof(buf))) == MOTIONPERCEPT_MAX_RUN,
          "covering exactly MAX_RUN windows (got '%s')", buf);
    CHECK(log.runLength() == 1, "and it opens a fresh run (got %d)", log.runLength());

    // The arithmetic the constant was chosen on, asserted so it cannot drift silently.
    CHECK(MOTIONPERCEPT_MAX_RUN >= 2,
          "MAX_RUN must exceed 1, or run-length is a no-op with extra fields");
    CHECK((long)MOTIONPERCEPT_MAX_LANE * MOTIONPERCEPT_MAX_RUN *
              (MOTIONPERCEPT_FLUSH_MS / 1000) >= 24L * 3600,
          "lane life at rest is at least 24 h of uptime — the treadmill fix this "
          "section exists for (was 48 minutes)");
  }

  // 7c. A discarded window breaks the RUN too, for the same reason it breaks the
  // transition chain: the next record is not adjacent to the last, so folding across
  // the gap would claim coverage of a window nobody measured.
  {
    motionpercept::Log log;
    uint32_t now = 1000;
    log.reset(now);
    char rec[MOTIONPERCEPT_RECORD_BUF];
    char line[512], buf[128];

    feedWindow(log, now, 0, 60);
    CHECK(log.buildRecord(rec, sizeof(rec), 0, 1000, ST(1000000ULL, true), now) > 0,
          "first window opens a run");
    feedWindow(log, now, 0, 60);
    CHECK(log.buildRecord(rec, sizeof(rec), 1, 1060, ST(1060000ULL, true), now) == 0,
          "second is covered by it");

    log.reset(now);   // the lane went full, or the IMU dropped out

    feedWindow(log, now, 0, 60);
    size_t m = log.buildRecord(rec, sizeof(rec), 1, 1180, ST(1180000ULL, true), now);
    CHECK(m > 0, "after a discard the next still window WRITES rather than folding");
    lineWith(rec, "**RUN**", line, sizeof(line));
    CHECK(strcmp(field(line, "reason", buf, sizeof(buf)), "first") == 0,
          "and calls itself `first` — it is not adjacent to anything (got '%s')", buf);
    CHECK(strcmp(field(line, "windows_since_last", buf, sizeof(buf)), "1") == 0,
          "claiming coverage of itself only (got '%s')", buf);
    CHECK(strstr(rec, "**COVERED**") == NULL,
          "and carrying NO covered block — the discarded window is gone, not absorbed");
  }

  // 7d. Truncation: a record whose COVERED block does not fit is not written at all.
  // The same rule the transition pair follows, for the same reason — a head line
  // claiming `windows_since_last:10` with nothing accounting for the 9 is a lie, where
  // a missing record is merely a gap.
  {
    motionpercept::Log log;
    uint32_t now = 1000;
    log.reset(now);
    char rec[MOTIONPERCEPT_RECORD_BUF];

    for (int w = 0; w < 4; ++w) {
      feedWindow(log, now, 0, 60);
      log.buildRecord(rec, sizeof(rec), 0, 1000 + 60 * w,
                      ST(1000000ULL + 60000ULL * (uint32_t)w, true), now);
    }
    feedWindow(log, now, 400, 60);
    char small[260];   // fits the head + MOTION + RUN, but not the COVERED line
    size_t m = log.buildRecord(small, sizeof(small), 1, 1300, ST(1300000ULL, true), now);
    CHECK(m == 0, "a record whose COVERED block does not fit writes 0 bytes (got %zu)", m);
    CHECK(log.lastClose() == motionpercept::CLOSE_EMPTY,
          "...and reports EMPTY, so the caller cannot mistake it for a covered window");

    // And the run is BROKEN by the failure, not carried. Carrying it would make the
    // next record claim `windows_since_last:6` for windows whose evidence was never
    // written — a record overstating its coverage, which is worse than a missing one.
    char line[512], buf[128];
    feedWindow(log, now, 0, 60);
    CHECK(log.buildRecord(rec, sizeof(rec), 1, 1360, ST(1360000ULL, true), now) > 0,
          "the next window writes");
    lineWith(rec, "**RUN**", line, sizeof(line));
    CHECK(strcmp(field(line, "windows_since_last", buf, sizeof(buf)), "1") == 0,
          "claiming only itself — the lost windows are a gap, not absorbed (got '%s')", buf);
  }

  printf("%s: %d checks failed\n", fails ? "RESULT FAIL" : "RESULT OK", fails);
  return fails ? 1 : 0;
}
