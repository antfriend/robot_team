// test_perceptlearn.cpp — Learning from Action Rules 1 and 2 (Stages B and C).
//
// The format checks matter, but the ones that matter MORE are the behavioural ones,
// because this tier's whole value is that it cannot flatter itself:
//   * an expectation is armed ONLY on a positive anchoring claim (Rule 1),
//   * it is scored exactly once and against the NEXT window, not its own,
//   * a peer that goes silent is `unobserved`, never `violated` — otherwise a peer
//     powering off reads as the world contradicting the node,
//   * a `moving` window drops the expectation UNSCORED, because testing a claim the
//     node never made would manufacture evidence,
//   * nothing here mutates anything (Rule 2) — there is no API to do so, by design.
#include "PerceptLearn.h"
#include <stdio.h>
#include <string.h>

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

static const uint8_t ESPNOW = 0, BLE = 2;

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
  char rec[PERCEPTLEARN_BUF], line[512], buf[128];

  // -------------------------------------------------------------------------
  // 1. Rule 1 — an expectation exists only where a claim was made
  // -------------------------------------------------------------------------
  {
    perceptlearn::Loop L;
    // A link window with no peers heard: nothing to predict about.
    L.stageBegin(0);
    CHECK(!L.arm(5), "arm() refuses when no peer was heard (no prediction is possible)");
    CHECK(!L.armed(), "and stays unarmed");

    // Peers heard, and the motion window said `still` -> the node claims anchoring.
    L.stageBegin(0);
    L.stage(0x200, ESPNOW, -35);
    L.stage(0x200, BLE, -52);
    CHECK(L.arm(31), "arm() succeeds on a `still` window with peers");
    CHECK(L.armed(), "the expectation is now outstanding");

    // Scoring happens against the NEXT window, so nothing is pending yet.
    CHECK(!L.outcomePending(), "arming alone produces no outcome — the world has not answered");
    CHECK(L.buildOutcome(rec, sizeof(rec), 0, 0x300) == 0, "and nothing to write");
  }

  // -------------------------------------------------------------------------
  // 2. Met / violated, against the band
  // -------------------------------------------------------------------------
  {
    perceptlearn::Loop L;
    L.stageBegin(14);
    L.stage(0x200, ESPNOW, -35);
    L.stage(0x200, BLE, -52);
    L.arm(31);

    // Next window: espnow drifts 6 (== band, inclusive -> met), ble drifts 7 (violated).
    L.stageBegin(15);
    L.stage(0x200, ESPNOW, -41);
    L.stage(0x200, BLE, -59);
    int n = L.score(ST(600000ULL, false), 0);
    CHECK(n == 2, "both claims scored (got %d)", n);
    CHECK(L.metCount() == 1, "delta exactly == band counts as MET (got met=%d)", L.metCount());
    CHECK(L.violatedCount() == 1, "delta band+1 counts as VIOLATED (got violated=%d)",
          L.violatedCount());
    CHECK(!L.armed(), "the expectation is consumed by scoring — one prediction, one verdict");
    CHECK(L.outcomePending(), "an outcome is now waiting to be testified");

    size_t m = L.buildOutcome(rec, sizeof(rec), 0, 0x300);
    CHECK(m > 0, "outcome record renders (%zu bytes)", m);
    CHECK(!L.outcomePending(), "and clears (never written twice)");
    CHECK(recordHeaderLines(rec) == 1, "exactly ONE record header, no phantoms (got %d)",
          recordHeaderLines(rec));

    // Rule 2's required tuple: acting record, edge, expectation, observed, verdict,
    // provenance.
    lineWith(rec, "**OUTCOME**", line, sizeof(line));
    // ⚠ The acting citation is a (record, offset) PAIR since @LAT95 became
    // change-triggered: a `still` window matching the one before it writes no record, so
    // a bare ordinal would provenance this expectation to a record about another window.
    CHECK(strcmp(field(line, "acting", buf, sizeof(buf)), "@LAT95LON31+0") == 0,
          "names the ACTING record — the @LAT95 window that claimed anchoring (got '%s')", buf);
    CHECK(strcmp(field(line, "observed_in", buf, sizeof(buf)), "@LAT97LON15") == 0,
          "names the @LAT97 window that answered (got '%s')", buf);
    CHECK(strcmp(field(line, "band_dbm", buf, sizeof(buf)), "6") == 0,
          "states the band it judged against (got '%s')", buf);
    CHECK(strstr(rec, "testifies_about@LAT95LON31") != NULL &&
              strstr(rec, "derived_from@LAT97LON15") != NULL,
          "both are reachable as EDGES, not only as body text");
    CHECK(strstr(rec, "**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3") != NULL,
          "provenance names the rule and the record it is testing");

    lineWith(rec, "**OBSERVED** peer:0x00000200 proto:espnow", line, sizeof(line));
    CHECK(strcmp(field(line, "verdict", buf, sizeof(buf)), "met") == 0,
          "espnow claim reads met (got '%s')", buf);
    CHECK(strcmp(field(line, "delta", buf, sizeof(buf)), "-6") == 0,
          "delta is signed and is observed - predicted (got '%s')", buf);
    lineWith(rec, "**OBSERVED** peer:0x00000200 proto:ble", line, sizeof(line));
    CHECK(strcmp(field(line, "verdict", buf, sizeof(buf)), "violated") == 0,
          "ble claim reads violated (got '%s')", buf);
  }

  // -------------------------------------------------------------------------
  // 3. A silent peer is UNOBSERVED, not violated
  // -------------------------------------------------------------------------
  {
    perceptlearn::Loop L;
    L.stageBegin(0);
    L.stage(0x200, ESPNOW, -35);
    L.stage(0x010, ESPNOW, -70);
    L.arm(1);

    L.stageBegin(1);
    L.stage(0x200, ESPNOW, -36);   // 0x010 powered off / out of range
    L.score(ST(0, false), 0);
    CHECK(L.metCount() == 1 && L.violatedCount() == 0,
          "the heard peer is met and the silent one does NOT count against the claim "
          "(met=%d violated=%d)", L.metCount(), L.violatedCount());
    L.buildOutcome(rec, sizeof(rec), 0, 0x300);
    lineWith(rec, "**OBSERVED** peer:0x00000010", line, sizeof(line));
    CHECK(strcmp(field(line, "verdict", buf, sizeof(buf)), "unobserved") == 0,
          "and is recorded as unobserved (got '%s')", buf);
    CHECK(strstr(line, "observed_med:") == NULL,
          "with NO observed_med — inventing one would be fabricating a measurement");
  }

  // -------------------------------------------------------------------------
  // 3b. Overflowing the claim house is REPORTED, not silent
  //
  // The trap this pins: an overflowed (peer, proto) is still in claims_, so score()
  // finds nothing staged for it and calls it VERDICT_UNOBSERVED — byte-identical to
  // case 3 above, where the peer genuinely went quiet. Without a counter the two are
  // indistinguishable, and 4 nodes x {espnow, ble} sits EXACTLY on the cap, so this is
  // the configuration Part 1.3 of the handoff is about to run.
  // -------------------------------------------------------------------------
  {
    perceptlearn::Loop L;
    L.stageBegin(0);
    for (int i = 0; i < PERCEPTLEARN_MAX_CLAIMS; ++i)
      L.stage(0x200 + i, ESPNOW, -35);
    CHECK(L.stagedOverflow() == 0, "a full-but-not-over house reports no overflow (got %d)",
          L.stagedOverflow());

    L.stage(0x999, ESPNOW, -35);
    L.stage(0x999, BLE, -50);
    CHECK(L.stagedOverflow() == 2, "two observations past the cap are counted (got %d)",
          L.stagedOverflow());

    L.stageBegin(1);
    CHECK(L.stagedOverflow() == 0, "and the count is per-window, cleared by stageBegin "
          "(got %d)", L.stagedOverflow());
  }

  // -------------------------------------------------------------------------
  // 3c. The Reconciler's belief cap is reported too
  //
  // Worse than the staged cap because it biases an ANSWER: the dropped pair's testimony
  // never reaches any belief, so conf is folded from a subset of the lane while the
  // output looks like a complete reconciliation.
  // -------------------------------------------------------------------------
  {
    perceptlearn::Reconciler R;
    R.begin();
    for (int i = 0; i < PERCEPTLEARN_MAX_BELIEFS; ++i)
      R.fold(0x200 + i, ESPNOW, perceptlearn::VERDICT_MET);
    CHECK(R.beliefCount() == PERCEPTLEARN_MAX_BELIEFS, "every slot taken (got %d)",
          R.beliefCount());
    CHECK(R.claimsDropped() == 0, "nothing dropped yet (got %d)", R.claimsDropped());

    R.fold(0x999, BLE, perceptlearn::VERDICT_VIOLATED);
    CHECK(R.claimsDropped() == 1, "a claim with no slot is counted, not swallowed (got %d)",
          R.claimsDropped());
    CHECK(R.beliefCount() == PERCEPTLEARN_MAX_BELIEFS,
          "and it does not overwrite an existing belief (got %d)", R.beliefCount());

    R.begin();
    CHECK(R.claimsDropped() == 0, "begin() clears it — every cycle re-folds from scratch "
          "(got %d)", R.claimsDropped());
  }

  // -------------------------------------------------------------------------
  // 4. A `moving` window drops the expectation UNSCORED
  // -------------------------------------------------------------------------
  {
    perceptlearn::Loop L;
    L.stageBegin(0);
    L.stage(0x200, ESPNOW, -35);
    L.arm(1);
    CHECK(L.armed(), "armed while the node claimed to be still");

    L.disarm();   // what the sketch does when the next motion window reads `moving`
    CHECK(!L.armed(), "a `moving` window disarms");

    L.stageBegin(1);
    L.stage(0x200, ESPNOW, -80);   // a huge swing, which a scored claim would call violated
    int n = L.score(ST(0, false), 0);
    CHECK(n == 0, "and the swing is NOT scored (got %d claims) — the node never claimed "
                  "to be anchored, so there is no prediction to be wrong about", n);
    CHECK(!L.outcomePending(), "so no testimony is produced");
  }

  // -------------------------------------------------------------------------
  // 5. Rule 4's counter (Stage E does not act on it yet)
  // -------------------------------------------------------------------------
  {
    perceptlearn::Loop L;
    CHECK(L.violationStreak() == 0, "streak starts at 0");

    for (int i = 0; i < 3; ++i) {
      L.stageBegin(i);
      L.stage(0x200, ESPNOW, -35);
      L.arm(i);
      L.stageBegin(i + 1);
      L.stage(0x200, ESPNOW, -60);   // way outside the band
      L.score(ST(0, false), 0);
      L.buildOutcome(rec, sizeof(rec), 0, 0x300);
    }
    CHECK(L.violationStreak() == 3, "three consecutive violated windows -> streak 3 (got %d)",
          L.violationStreak());

    // One met window resets it. Rule 4 aborts on CONSECUTIVE failures.
    L.stageBegin(9);
    L.stage(0x200, ESPNOW, -60);
    L.arm(9);
    L.stageBegin(10);
    L.stage(0x200, ESPNOW, -61);
    L.score(ST(0, false), 0);
    CHECK(L.violationStreak() == 0, "a met window resets the streak (got %d)",
          L.violationStreak());

    // An all-unobserved window neither breaks nor extends it: nothing was tested.
    L.stageBegin(11);
    L.stage(0x200, ESPNOW, -61);
    L.arm(11);
    L.stageBegin(12);
    L.stage(0x010, ESPNOW, -70);   // different peer entirely
    L.score(ST(0, false), 0);
    CHECK(L.violationStreak() == 0,
          "an all-unobserved window leaves the streak alone (got %d)", L.violationStreak());
  }

  // -------------------------------------------------------------------------
  // 6. Truncation writes nothing, and the buffer is big enough for a full house
  // -------------------------------------------------------------------------
  {
    perceptlearn::Loop L;
    L.stageBegin(0);
    for (int i = 0; i < PERCEPTLEARN_MAX_CLAIMS; ++i)
      L.stage(0x10 + (uint32_t)i, ESPNOW, -40 - i);
    L.arm(1);
    L.stageBegin(1);
    for (int i = 0; i < PERCEPTLEARN_MAX_CLAIMS; ++i)
      L.stage(0x10 + (uint32_t)i, ESPNOW, -40 - i);
    L.score(ST(1785542400000ULL, true), 0);
    size_t m = L.buildOutcome(rec, sizeof(rec), 47, 0x300);
    CHECK(m > 0 && m < PERCEPTLEARN_BUF,
          "a full %d-claim outcome fits PERCEPTLEARN_BUF (%zu / %d)",
          PERCEPTLEARN_MAX_CLAIMS, m, PERCEPTLEARN_BUF);
    CHECK(L.metCount() == PERCEPTLEARN_MAX_CLAIMS, "all %d claims met (got %d)",
          PERCEPTLEARN_MAX_CLAIMS, L.metCount());
    CHECK(recordHeaderLines(rec) == 1, "still exactly one record header (got %d)",
          recordHeaderLines(rec));
    lineWith(rec, "**OUTCOME**", line, sizeof(line));
    CHECK(strcmp(field(line, "wall", buf, sizeof(buf)), "1") == 0,
          "wall propagates (got '%s')", buf);
    CHECK(strcmp(field(line, "stream", buf, sizeof(buf)), "0x5ea51de7") == 0,
          "and so does the stream id (got '%s')", buf);

    perceptlearn::Loop T;
    T.stageBegin(0);
    T.stage(0x200, ESPNOW, -35);
    T.arm(1);
    T.stageBegin(1);
    T.stage(0x200, ESPNOW, -35);
    T.score(ST(0, false), 0);
    char tiny[64];
    CHECK(T.buildOutcome(tiny, sizeof(tiny), 0, 0x300) == 0,
          "an outcome that does not fit writes 0 bytes, not a half record");
    CHECK(!T.outcomePending(), "and does not linger to be half-written again");
  }

  // -------------------------------------------------------------------------
  // 7. Staging is consumed — Rule 1 never re-derives from a stale window
  // -------------------------------------------------------------------------
  {
    perceptlearn::Loop L;
    L.stageBegin(0);
    L.stage(0x200, ESPNOW, -35);
    CHECK(L.arm(1), "armed from freshly staged medians");
    CHECK(!L.arm(2),
          "a SECOND arm() with no new staging refuses — the sketch stages in the link "
          "flush and arms in the motion flush, so a pass where no peer was heard must "
          "not silently re-use the previous window's medians as a prediction");

    perceptlearn::Loop D;
    D.stageBegin(0);
    D.stage(0x200, ESPNOW, -35);
    D.disarm();
    CHECK(!D.arm(1), "disarm() clears the staging too");
  }

  // -------------------------------------------------------------------------
  // 8. STAGE D / Rule 3 — replay of the REAL 2026-08-02 moving run
  //
  // This is the check that makes the on-device result meaningful. The sequence below is
  // the verdict order the Cardputer actually wrote to @LAT92LON17..23 while the T-Deck
  // was carried to another room and back, and the expected conf values are the ones
  // computed BY HAND from those records (percept-learning-return.md §0b). If Stage D on
  // the device disagrees with this, one of the two is wrong and we find out — which is
  // exactly the property a RAM counter would not have given us.
  // -------------------------------------------------------------------------
  {
    using namespace perceptlearn;
    const uint8_t M = VERDICT_MET, V = VERDICT_VIOLATED;
    const uint8_t espnow_seq[] = {M, M, V, M, M, V, M};   // -> 106
    const uint8_t ble_seq[]    = {M, M, V, M, M, V, V};   // -> 88

    Reconciler R;
    R.begin();
    for (int i = 0; i < 7; ++i) {          // fold in lane order, interleaved as written
      R.fold(0x200, ESPNOW, espnow_seq[i]);
      R.fold(0x200, BLE, ble_seq[i]);
    }
    CHECK(R.beliefCount() == 2, "two beliefs, one per (peer, proto) (got %d)",
          R.beliefCount());

    const Belief* esp = 0; const Belief* ble = 0;
    for (int i = 0; i < R.beliefCount(); ++i) {
      if (R.belief(i).proto == ESPNOW) esp = &R.belief(i);
      if (R.belief(i).proto == BLE) ble = &R.belief(i);
    }
    CHECK(esp && esp->conf == 106,
          "espnow reconciles 128 -> 106, matching the hand computation (got %ld)",
          esp ? (long)esp->conf : -1);
    CHECK(ble && ble->conf == 88,
          "ble reconciles 128 -> 88, matching the hand computation (got %ld)",
          ble ? (long)ble->conf : -1);
    CHECK(esp && esp->sal == 16, "espnow sal = 8 per violation = 16 (got %ld)",
          esp ? (long)esp->sal : -1);
    CHECK(ble && ble->sal == 24, "ble sal = 24 (got %ld)", ble ? (long)ble->sal : -1);
    CHECK(ble && ble->contradiction,
          "ble raises the contradiction flag — it violated twice consecutively");
    CHECK(esp && !esp->contradiction,
          "espnow does NOT — its violations were separated by a met window");

    // Idempotence: the belief is a pure function of the lane, so recomputing changes
    // nothing. This is what makes it auditable rather than a running total.
    Reconciler R2;
    R2.begin();
    for (int i = 0; i < 7; ++i) {
      R2.fold(0x200, ESPNOW, espnow_seq[i]);
      R2.fold(0x200, BLE, ble_seq[i]);
    }
    const Belief* esp2 = 0;
    for (int i = 0; i < R2.beliefCount(); ++i)
      if (R2.belief(i).proto == ESPNOW) esp2 = &R2.belief(i);
    CHECK(esp2 && esp2->conf == 106, "re-running the reconciliation is a no-op (got %ld)",
          esp2 ? (long)esp2->conf : -1);

    // Saturation and floor are clamps applied IN ORDER, not to a sum.
    perceptlearn::Reconciler S; S.begin();
    for (int i = 0; i < 8; ++i) S.fold(1, ESPNOW, V);      // 128 - 8*16 = 0
    CHECK(S.belief(0).conf == 0, "conf floors at 0, never negative (got %ld)",
          (long)S.belief(0).conf);
    S.fold(1, ESPNOW, M);
    CHECK(S.belief(0).conf == 2, "and climbs back from the floor, not from -N (got %ld)",
          (long)S.belief(0).conf);

    perceptlearn::Reconciler C; C.begin();
    for (int i = 0; i < 200; ++i) C.fold(2, ESPNOW, M);    // would be 128+400 unclamped
    CHECK(C.belief(0).conf == 255, "conf saturates at 255 (got %ld)",
          (long)C.belief(0).conf);

    // Unobserved neither moves conf nor breaks a violation streak.
    perceptlearn::Reconciler U; U.begin();
    U.fold(3, ESPNOW, V);
    U.fold(3, ESPNOW, VERDICT_UNOBSERVED);
    U.fold(3, ESPNOW, V);
    CHECK(U.belief(0).contradiction,
          "an unobserved claim does not shelter a belief from consecutive violations");
    CHECK(U.belief(0).unobserved == 1 && U.belief(0).conf == 128 - 32,
          "and does not move conf itself (conf=%ld unobs=%ld)",
          (long)U.belief(0).conf, (long)U.belief(0).unobserved);
  }

  // -------------------------------------------------------------------------
  // 9. Stage D reads the outcome lane BACK OFF FLASH — parse a real record body
  // -------------------------------------------------------------------------
  {
    using namespace perceptlearn;
    // Byte-for-byte an @LAT92 record the Cardputer wrote (LON19, the walk-away
    // window) — deliberately kept in the PRE-STREAM `synced:0` format. The corpus
    // already on flash is written this way, and a reader that can only parse the new
    // format would silently fold a subset of the lane, which is exactly the failure
    // Stage D's whole "recompute, never trust a counter" argument depends on avoiding.
    const char* body =
        "\n---\n\n@LAT92LON19 | created:0 | updated:0 | "
        "relates:testifies_about@LAT95LON3,derived_from@LAT97LON3,senses@LAT0LON0\n\n"
        "**OUTCOME** t_ms:229600 synced:0 node:0x300 acting:@LAT95LON3 "
        "observed_in:@LAT97LON3 band_dbm:6 met:0 violated:2 unobserved:0 streak:1\n"
        "**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-45 band:6\n"
        "**OBSERVED** peer:0x00000200 proto:espnow observed_med:-83 delta:-38 "
        "verdict:violated\n"
        "**EXPECTED** peer:0x00000200 proto:ble predicted_med:-56 band:6\n"
        "**OBSERVED** peer:0x00000200 proto:ble observed_med:-93 delta:-37 "
        "verdict:violated\n"
        "**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 "
        "basis:motion_state:still tier:@LAT95 observable:@LAT97 "
        "band_src:p90_of_still_windows\n";

    Reconciler R; R.begin();
    int n = R.foldRecord(body, strlen(body));
    CHECK(n == 2, "parses both claims out of a real @LAT92 record body (got %d)", n);
    CHECK(R.recordsFolded() == 1, "counts one record folded (got %d)", R.recordsFolded());
    CHECK(R.beliefCount() == 2, "two beliefs discovered from the record (got %d)",
          R.beliefCount());
    for (int i = 0; i < R.beliefCount(); ++i) {
      CHECK(R.belief(i).peer == 0x200, "peer id parsed from hex (got 0x%lx)",
            (unsigned long)R.belief(i).peer);
      CHECK(R.belief(i).conf == 128 - 16, "violated -> conf 112 (got %ld)",
            (long)R.belief(i).conf);
    }
    // The **EXPECTED** lines must NOT be folded — only observations carry verdicts.
    CHECK(R.belief(0).met == 0 && R.belief(0).violated == 1,
          "EXPECTED lines are not counted as outcomes (met=%ld violated=%ld)",
          (long)R.belief(0).met, (long)R.belief(0).violated);

    // A truncated read must be ignored, not guessed at. Cut PART WAY THROUGH the second
    // OBSERVED line — trimming the trailing PROVENANCE line would not test anything,
    // since both observations would still be complete.
    const char* last_obs = strstr(strstr(body, "**OBSERVED**") + 1, "**OBSERVED**");
    size_t cut = (size_t)(last_obs - body) + 30;   // lands inside the ble verdict line
    Reconciler T; T.begin();
    int tn = T.foldRecord(body, cut);
    CHECK(tn == 1, "a partial trailing line is ignored, not guessed at (got %d)", tn);
    CHECK(T.beliefCount() == 1, "so only the complete claim becomes a belief (got %d)",
          T.beliefCount());

    // The rendered belief carries an [ew] block — the first on this fleet.
    char brec[PERCEPTLEARN_BUF];
    size_t bm = R.buildBelief(brec, sizeof(brec), 0, 0, 1785542400UL, 0x300, 1,
                              ST(7200000ULL, true));
    CHECK(bm > 0, "belief record renders (%zu bytes)", bm);
    CHECK(strstr(brec, "\n[ew]\n") != NULL && strstr(brec, "\n[/ew]\n") != NULL,
          "carries a TBEW [ew] block");
    CHECK(strstr(brec, "conf:112") != NULL, "with the reconciled conf");
    CHECK(strstr(brec, "**PROVENANCE** rule:LearningFromAction/Rule3") != NULL,
          "and names Rule 3 as its provenance");
    CHECK(recordHeaderLines(brec) == 1, "exactly one record header (got %d)",
          recordHeaderLines(brec));

    // THE RECENCY ANCHOR, WHICH IS THE WHOLE POINT OF PART 2. `touched:` stays in
    // Unix seconds per TTDB-RFC-0005 §4, and **TOUCHED** carries the same instant in
    // the stream frame — the one a node always has.
    CHECK(strstr(brec, "touched:1785542400") != NULL,
          "touched: stays spec-conformant Unix seconds");
    CHECK(strstr(brec, "**TOUCHED** t_ms:7200000 stream:0x5ea51de7 wall:1 "
                       "unix_s:1785542400") != NULL,
          "and **TOUCHED** carries the SAME instant in the stream frame");

    // The case the RFC cannot express, and the reason the second field exists: a
    // fleet with no laptop. `touched:0` says "recency unknown" and salience could
    // never decay from it — but the stream clock is perfectly good.
    size_t bm2 = R.buildBelief(brec, sizeof(brec), 0, 0, 0, 0x300, 1,
                               ST(7200000ULL, false));
    CHECK(bm2 > 0, "a belief on a laptop-less fleet still renders");
    CHECK(strstr(brec, "touched:0") != NULL,
          "with touched:0 — RFC-0005's recency anchor is INERT here, which is the "
          "spec gap this found");
    CHECK(strstr(brec, "**TOUCHED** t_ms:7200000 stream:0x00000000 wall:0") != NULL,
          "while the stream frame still says exactly when it was touched");
  }

  // -------------------------------------------------------------------------
  // 8. RUN-LENGTH — and the one property that makes it acceptable on a TALLY
  //
  // A state series can be compressed by keeping its transitions. A tally cannot: drop
  // the unchanged windows and `conf` loses its denominator. Run-length is the form that
  // fixes the lane growth WITHOUT that cost, and the reason is a claim that has to be
  // tested rather than argued — folding a verdict N times is arithmetically identical
  // to folding it once per window, saturation, floor, streaks and all.
  // -------------------------------------------------------------------------

  // Helper: score one window with a fixed verdict pattern.
  //   drift == 0 -> met (both peers), drift > band -> violated (both peers)
  struct RunHelper {
    static void window(perceptlearn::Loop& L, int lane, int base_espnow, int base_ble,
                       int drift, uint64_t t_ms) {
      L.stageBegin(lane);
      L.stage(0x200, ESPNOW, base_espnow + drift);
      L.stage(0x200, BLE, base_ble + drift);
      L.score(ST(t_ms, true), 0);
      // re-arm from the SAME medians so the next window predicts off this one
      L.stageBegin(lane);
      L.stage(0x200, ESPNOW, base_espnow + drift);
      L.stage(0x200, BLE, base_ble + drift);
      L.arm(lane, 0);
    }
  };

  {
    perceptlearn::Loop L;
    L.stageBegin(0);
    L.stage(0x200, ESPNOW, -35);
    L.stage(0x200, BLE, -52);
    L.arm(7, 0);

    // Window 1: both met. First outcome of this node's life -> always written.
    RunHelper::window(L, 1, -35, -52, 0, 100000);
    CHECK(L.outcomePending(), "the first scored window always writes");
    size_t m = L.buildOutcome(rec, sizeof(rec), 0, 0x300);
    CHECK(m > 0, "and renders (%zu bytes)", m);
    lineWith(rec, "**RUN**", line, sizeof(line));
    CHECK(strcmp(field(line, "reason", buf, sizeof(buf)), "first") == 0,
          "calling itself `first` (got '%s')", buf);
    CHECK(strcmp(field(line, "windows_since_last", buf, sizeof(buf)), "1") == 0,
          "and claiming one window (got '%s')", buf);
    CHECK(strstr(rec, "**COVERED**") == NULL, "with no covered block to carry");

    // Windows 2-4: the same verdict vector. Scored, counted, NOT written.
    for (int w = 0; w < 3; ++w)
      RunHelper::window(L, 2 + w, -35, -52, 0, 160000 + 60000ULL * (uint32_t)w);
    CHECK(!L.outcomePending(),
          "three more all-met windows produce NO record — the lane is change-triggered");
    CHECK(L.coveredWindows() == 3,
          "⚠ but they are COUNTED, not dropped: a tally without its denominator is "
          "over-confident, which is the whole hazard here (got %d)", L.coveredWindows());
    CHECK(L.buildOutcome(rec, sizeof(rec), 1, 0x300) == 0,
          "and there is genuinely nothing to append");

    // Window 5: the links move. A CHANGE is never deferred.
    RunHelper::window(L, 5, -35, -52, 40, 400000);
    CHECK(L.outcomePending(), "a changed verdict vector writes immediately");
    CHECK(L.violatedCount() == 2, "both claims violated (got %d)", L.violatedCount());
    m = L.buildOutcome(rec, sizeof(rec), 1, 0x300);
    CHECK(m > 0, "the closing record renders (%zu bytes)", m);
    CHECK(recordHeaderLines(rec) == 1, "still exactly one record header (got %d)",
          recordHeaderLines(rec));

    lineWith(rec, "**RUN**", line, sizeof(line));
    CHECK(strcmp(field(line, "reason", buf, sizeof(buf)), "changed") == 0,
          "reason:changed (got '%s')", buf);
    CHECK(strcmp(field(line, "windows_since_last", buf, sizeof(buf)), "4") == 0,
          "covering the 3 suppressed windows and its own (got '%s')", buf);

    lineWith(rec, "**COVERED-SPAN**", line, sizeof(line));
    CHECK(strcmp(field(line, "windows", buf, sizeof(buf)), "3") == 0,
          "the span names three covered windows (got '%s')", buf);
    CHECK(strcmp(field(line, "first_t_ms", buf, sizeof(buf)), "160000") == 0 &&
              strcmp(field(line, "last_t_ms", buf, sizeof(buf)), "280000") == 0,
          "and WHEN they were — `windows` counts scored windows, not minutes, and a "
          "moving node scores none at all, so two folded windows can be an hour apart");

    lineWith(rec, "**COVERED** peer:0x00000200 proto:espnow", line, sizeof(line));
    CHECK(strcmp(field(line, "verdict", buf, sizeof(buf)), "met") == 0,
          "the covered espnow claim carries the run's verdict (got '%s')", buf);
    CHECK(strcmp(field(line, "windows", buf, sizeof(buf)), "3") == 0,
          "and the repeat count Rule 3 folds it by (got '%s')", buf);
    CHECK(strcmp(field(line, "observed_min", buf, sizeof(buf)), "-35") == 0,
          "with the range the median moved through while it held (got '%s')", buf);

    // ⚠ Order: the covered block is emitted BEFORE this record's own pairs, because
    // that is the order the windows happened in and Rule 3's clamp is not commutative.
    CHECK(strstr(rec, "**COVERED**") < strstr(rec, "**OBSERVED**"),
          "covered lines precede observed ones — a belief that saturated and then fell "
          "is not one that never rose");
  }

  // 8b. The heartbeat, and the arithmetic PERCEPTLEARN_MAX_RUN was chosen on.
  {
    perceptlearn::Loop L;
    L.stageBegin(0);
    L.stage(0x200, ESPNOW, -35);
    L.arm(7, 0);

    int records = 0;
    for (int w = 0; w < PERCEPTLEARN_MAX_RUN + 1; ++w) {
      L.stageBegin(w + 1);
      L.stage(0x200, ESPNOW, -35);
      L.score(ST(100000ULL + 60000ULL * (uint32_t)w, true), 0);
      L.stageBegin(w + 1);
      L.stage(0x200, ESPNOW, -35);
      L.arm(7, 0);
      if (L.outcomePending()) { L.buildOutcome(rec, sizeof(rec), records, 0x300); ++records; }
    }
    CHECK(records == 2,
          "%d identical windows write 2 records: the first and the heartbeat (got %d)",
          PERCEPTLEARN_MAX_RUN + 1, records);
    lineWith(rec, "**RUN**", line, sizeof(line));
    CHECK(strcmp(field(line, "reason", buf, sizeof(buf)), "heartbeat") == 0,
          "the second says heartbeat (got '%s')", buf);
    CHECK(PERCEPTLEARN_MAX_RUN >= 2,
          "MAX_RUN must exceed 1, or run-length is a no-op with extra fields");
    CHECK((long)PERCEPTLEARN_MAX_LANE * PERCEPTLEARN_MAX_RUN * 60 >= 12L * 3600,
          "lane life with nothing changing is at least 12 h of uptime — it was ~24 "
          "minutes, which is what made this lane a treadmill too");
  }

  // 8c. ⚠ THE CLAIM THAT MAKES THIS ACCEPTABLE ON A TALLY, TESTED RATHER THAN ARGUED.
  // A compressed lane must reconcile to the SAME belief as an uncompressed one — same
  // conf, same sal, same max_streak, same contradiction flag. If it does not, the
  // compression is falsifying evidence, not shrinking it.
  {
    const int N = 9;   // enough met windows to move conf visibly, then two violations

    // (i) the uncompressed lane: N+2 records, one window each
    perceptlearn::Reconciler U; U.begin();
    for (int i = 0; i < N; ++i) U.fold(0x200, ESPNOW, perceptlearn::VERDICT_MET);
    U.fold(0x200, ESPNOW, perceptlearn::VERDICT_VIOLATED);
    U.fold(0x200, ESPNOW, perceptlearn::VERDICT_VIOLATED);

    // (ii) the compressed lane: ONE record carrying the run, parsed off "flash"
    char lane[512];
    snprintf(lane, sizeof(lane),
             "**COVERED-SPAN** windows:%d first_t_ms:1 last_t_ms:2 "
             "counts_scored_windows_not_minutes:1\n"
             "**COVERED** peer:0x00000200 proto:espnow verdict:met windows:%d "
             "observed_min:-35 observed_max:-33\n"
             "**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-35 band:6\n"
             "**OBSERVED** peer:0x00000200 proto:espnow observed_med:-55 delta:-20 "
             "verdict:violated\n", N, N);
    char lane2[512];
    snprintf(lane2, sizeof(lane2),
             "**EXPECTED** peer:0x00000200 proto:espnow predicted_med:-55 band:6\n"
             "**OBSERVED** peer:0x00000200 proto:espnow observed_med:-75 delta:-20 "
             "verdict:violated\n");
    perceptlearn::Reconciler C; C.begin();
    C.foldRecord(lane, strlen(lane));
    C.foldRecord(lane2, strlen(lane2));

    CHECK(U.beliefCount() == 1 && C.beliefCount() == 1,
          "both lanes yield one belief (got %d / %d)", U.beliefCount(), C.beliefCount());
    CHECK(U.belief(0).conf == C.belief(0).conf,
          "SAME conf from a compressed lane as from an uncompressed one (%ld vs %ld) — "
          "run-length is lossless for Rule 3, which is why it is legitimate on a tally",
          (long)U.belief(0).conf, (long)C.belief(0).conf);
    CHECK(U.belief(0).sal == C.belief(0).sal,
          "same sal (%ld vs %ld)", (long)U.belief(0).sal, (long)C.belief(0).sal);
    CHECK(U.belief(0).met == C.belief(0).met && U.belief(0).violated == C.belief(0).violated,
          "same met/violated tallies (%ld/%ld vs %ld/%ld)",
          (long)U.belief(0).met, (long)U.belief(0).violated,
          (long)C.belief(0).met, (long)C.belief(0).violated);
    CHECK(U.belief(0).max_streak == C.belief(0).max_streak &&
              U.belief(0).contradiction == C.belief(0).contradiction,
          "and the same streak/contradiction state (%ld vs %ld)",
          (long)U.belief(0).max_streak, (long)C.belief(0).max_streak);
    CHECK(C.belief(0).met == N,
          "the covered line folded %d times, not once (got %ld)", N,
          (long)C.belief(0).met);
  }

  // 8d. The two parsing traps this format sets, both of the needle-collision family
  // that has already cost this project real time (`prev_stream:` in @LAT90).
  {
    // (i) **COVERED-SPAN** must NOT be read as a claim: it has no peer and no verdict,
    // and folding it would double-count the run.
    char span[256];
    snprintf(span, sizeof(span),
             "**COVERED-SPAN** windows:9 first_t_ms:1 last_t_ms:2\n"
             "**OBSERVED** peer:0x00000200 proto:espnow observed_med:-35 delta:0 "
             "verdict:met\n");
    perceptlearn::Reconciler S; S.begin();
    int sn = S.foldRecord(span, strlen(span));
    CHECK(sn == 1, "**COVERED-SPAN** is not mistaken for a claim (got %d folded)", sn);
    CHECK(S.belief(0).met == 1,
          "so the run is not double-counted (got %ld)", (long)S.belief(0).met);

    // (ii) a covered line whose `windows:` is missing folds ZERO times, not once.
    // Guessing 1 would under-count a run of 30 by 29 while looking like a clean fold.
    char broken[256];
    snprintf(broken, sizeof(broken),
             "**COVERED** peer:0x00000200 proto:espnow verdict:met\n");
    perceptlearn::Reconciler B; B.begin();
    int bn = B.foldRecord(broken, strlen(broken));
    CHECK(bn == 0 && B.beliefCount() == 0,
          "a covered line with no repeat count folds nothing at all (got %d)", bn);
  }

  // 8e. The buffer. A full 8-claim house that ALSO carries a covered line per claim is
  // the biggest record this lane can produce, and buildOutcome writes nothing rather
  // than truncating — so an under-sized buffer loses exactly the run-carrying records.
  {
    perceptlearn::Loop L;
    const uint32_t peers[4] = {0x010, 0x011, 0x012, 0x200};
    for (int pass = 0; pass < 3; ++pass) {
      L.stageBegin(pass);
      for (int i = 0; i < 4; ++i) {
        L.stage(peers[i], ESPNOW, -40 - i);
        L.stage(peers[i], BLE, -60 - i);
      }
      if (pass > 0) L.score(ST(100000ULL + 60000ULL * (uint32_t)pass, true), 0);
      L.stageBegin(pass);
      for (int i = 0; i < 4; ++i) {
        L.stage(peers[i], ESPNOW, -40 - i);
        L.stage(peers[i], BLE, -60 - i);
      }
      L.arm(7, pass);
      if (L.outcomePending()) L.buildOutcome(rec, sizeof(rec), pass, 0x300);
    }
    // One more window, differing, to close a run of covered all-met windows.
    L.stageBegin(9);
    for (int i = 0; i < 4; ++i) {
      L.stage(peers[i], ESPNOW, -80 - i);
      L.stage(peers[i], BLE, -99 - i);
    }
    L.score(ST(500000ULL, true), 0);
    size_t m = L.buildOutcome(rec, sizeof(rec), 9, 0x300);
    CHECK(m > 0, "a full 8-claim house WITH a covered block renders (%zu bytes)", m);
    CHECK(m < PERCEPTLEARN_BUF, "and fits PERCEPTLEARN_BUF (%zu / %d)", m, PERCEPTLEARN_BUF);
    CHECK(m > 1792,
          "⚠ and would NOT have fitted the pre-run-length 1792 (%zu) — the third time "
          "this pattern has nearly cost silent data loss", m);
  }

  printf("%s: %d checks failed\n", fails ? "RESULT FAIL" : "RESULT OK", fails);
  return fails ? 1 : 0;
}
