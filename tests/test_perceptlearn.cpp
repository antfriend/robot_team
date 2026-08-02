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
    int n = L.score(600000ULL, false);
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
    CHECK(strcmp(field(line, "acting", buf, sizeof(buf)), "@LAT95LON31") == 0,
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
    L.score(0, false);
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
    int n = L.score(0, false);
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
      L.score(0, false);
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
    L.score(0, false);
    CHECK(L.violationStreak() == 0, "a met window resets the streak (got %d)",
          L.violationStreak());

    // An all-unobserved window neither breaks nor extends it: nothing was tested.
    L.stageBegin(11);
    L.stage(0x200, ESPNOW, -61);
    L.arm(11);
    L.stageBegin(12);
    L.stage(0x010, ESPNOW, -70);   // different peer entirely
    L.score(0, false);
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
    L.score(1785542400000ULL, true);
    size_t m = L.buildOutcome(rec, sizeof(rec), 47, 0x300);
    CHECK(m > 0 && m < PERCEPTLEARN_BUF,
          "a full %d-claim outcome fits PERCEPTLEARN_BUF (%zu / %d)",
          PERCEPTLEARN_MAX_CLAIMS, m, PERCEPTLEARN_BUF);
    CHECK(L.metCount() == PERCEPTLEARN_MAX_CLAIMS, "all %d claims met (got %d)",
          PERCEPTLEARN_MAX_CLAIMS, L.metCount());
    CHECK(recordHeaderLines(rec) == 1, "still exactly one record header (got %d)",
          recordHeaderLines(rec));
    lineWith(rec, "**OUTCOME**", line, sizeof(line));
    CHECK(strcmp(field(line, "synced", buf, sizeof(buf)), "1") == 0,
          "synced propagates (got '%s')", buf);

    perceptlearn::Loop T;
    T.stageBegin(0);
    T.stage(0x200, ESPNOW, -35);
    T.arm(1);
    T.stageBegin(1);
    T.stage(0x200, ESPNOW, -35);
    T.score(0, false);
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
    Reconciler S; S.begin();
    for (int i = 0; i < 8; ++i) S.fold(1, ESPNOW, V);      // 128 - 8*16 = 0
    CHECK(S.belief(0).conf == 0, "conf floors at 0, never negative (got %ld)",
          (long)S.belief(0).conf);
    S.fold(1, ESPNOW, M);
    CHECK(S.belief(0).conf == 2, "and climbs back from the floor, not from -N (got %ld)",
          (long)S.belief(0).conf);

    Reconciler C; C.begin();
    for (int i = 0; i < 200; ++i) C.fold(2, ESPNOW, M);    // would be 128+400 unclamped
    CHECK(C.belief(0).conf == 255, "conf saturates at 255 (got %ld)",
          (long)C.belief(0).conf);

    // Unobserved neither moves conf nor breaks a violation streak.
    Reconciler U; U.begin();
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
    // Byte-for-byte an @LAT92 record the Cardputer wrote (LON19, the walk-away window).
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
    size_t bm = R.buildBelief(brec, sizeof(brec), 0, 0, 1785542400UL, 0x300, 1);
    CHECK(bm > 0, "belief record renders (%zu bytes)", bm);
    CHECK(strstr(brec, "\n[ew]\n") != NULL && strstr(brec, "\n[/ew]\n") != NULL,
          "carries a TBEW [ew] block");
    CHECK(strstr(brec, "conf:112") != NULL, "with the reconciled conf");
    CHECK(strstr(brec, "**PROVENANCE** rule:LearningFromAction/Rule3") != NULL,
          "and names Rule 3 as its provenance");
    CHECK(recordHeaderLines(brec) == 1, "exactly one record header (got %d)",
          recordHeaderLines(brec));
  }

  printf("%s: %d checks failed\n", fails ? "RESULT FAIL" : "RESULT OK", fails);
  return fails ? 1 : 0;
}
