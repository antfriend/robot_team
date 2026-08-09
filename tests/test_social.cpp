// test_social.cpp — the default network, stage 1: capability advertisement.
//
// What is worth pinning here, as opposed to what is easy to pin:
//   * the THREE-LEVEL invariant (exercised subset-of verified subset-of declared) holds
//     against a peer's masks too, not just our own — a corrupt or mid-upgrade digest must
//     read DOWN to the safe level, never up
//   * UNKNOWN and ABSENT never collapse: a node that has never sent a digest must not
//     report as capability-less, which is the exact case of the three V4s on this fleet
//   * `cap_epoch` ticks on CHANGE ONLY — an epoch that moved every pass would make every
//     peer permanently stale and drown the falsifier's instrument in its own noise
//   * epoch comparison is SERIAL-NUMBER arithmetic across the 255->0 wrap (the trap
//     TraceField's generation byte has, in a second place)
//   * the digest ROUND-TRIPS, and a short / over-long / wrong-magic / wrong-version one is
//     REFUSED rather than read as capabilities
//   * the peer list ROTATES, so with more peers than slots every one is eventually named
//   * the low-16-bit id invariant `shortId` depends on actually holds for the fleet's ids
#include <cstdio>
#include <cstring>
#include "Social.h"

static int gChecks = 0, gFails = 0;
static void check(bool ok, const char* what) {
  ++gChecks;
  if (!ok) { ++gFails; printf("  FAIL: %s\n", what); }
}

using namespace social;

// The fleet's ids, copied from RobotTeamConfig.h. Copied rather than included because this
// test must fail when an id is ADDED that breaks the invariant, and including the header
// would only prove the header agrees with itself.
static const uint32_t kFleet[] = {
    0x00000001, 0x00000010, 0x00000011, 0x00000012, 0x00000100,
    0x00000101, 0x00000102, 0x00000200, 0x00000300,
};
static const size_t kFleetN = sizeof(kFleet) / sizeof(kFleet[0]);

static const uint32_t SELF = 0x300;   // Cardputer
static const uint32_t PEER = 0x200;   // T-Deck

int main() {
  printf("Social tests\n");

  // ---- 1. the id invariant shortId() rests on ---------------------------------------
  // ⚠ If this fails, two nodes share a table row and each overwrites the other's
  // capabilities on every beacon. It is the cheapest possible check and it guards the one
  // assumption the wire format makes about the fleet.
  {
    bool unique = true;
    for (size_t i = 0; i < kFleetN && unique; ++i)
      for (size_t j = i + 1; j < kFleetN; ++j)
        if (shortId(kFleet[i]) == shortId(kFleet[j])) { unique = false; break; }
    check(unique, "every RobotTeamNodeId is unique in its low 16 bits");
  }

  // ---- 2. three levels, clamped on write --------------------------------------------
  {
    Table t;
    t.begin(SELF, (uint16_t)(CAP_MIC | CAP_IMU | CAP_SPEAKER));
    check(t.statusOf(SELF, CAP_MIC) == ST_DECLARED, "declared after begin");
    check(t.statusOf(SELF, CAP_GPS) == ST_ABSENT, "undeclared reads ABSENT on self");

    check(t.verify(CAP_MIC), "verify reports a change");
    check(t.statusOf(SELF, CAP_MIC) == ST_VERIFIED, "verified beats declared");
    check(!t.verify(CAP_MIC), "verify is idempotent");

    // A tier cannot exercise what the board never declared.
    check(!t.verify(CAP_GPS), "cannot verify an undeclared capability");
    check(!t.exercise(CAP_GPS), "cannot exercise an undeclared capability");
    check(t.statusOf(SELF, CAP_GPS) == ST_ABSENT, "the undeclared stays absent");

    // Exercising promotes through verified in one call.
    check(t.exercise(CAP_IMU), "exercise reports a change");
    check(t.statusOf(SELF, CAP_IMU) == ST_EXERCISED, "exercised is the top level");
    check((t.verified() & CAP_IMU) != 0, "exercising implies verified");
  }

  // ---- 3. the epoch ticks on change only ---------------------------------------------
  {
    Table t;
    t.begin(SELF, (uint16_t)(CAP_MIC | CAP_IMU));
    const uint8_t e0 = t.epoch();
    t.verify(CAP_MIC);
    const uint8_t e1 = t.epoch();
    check(e1 != e0, "a real change bumps the epoch");
    for (int i = 0; i < 50; ++i) { t.verify(CAP_MIC); t.exercise(0); }
    check(t.epoch() == e1, "50 no-op promotions do not move the epoch");
  }

  // ---- 4. CAP_WALL is derived, and it is the one capability that can be LOST ----------
  {
    Table t;
    t.begin(SELF, (uint16_t)(CAP_MIC | CAP_WALL));
    check(t.statusOf(SELF, CAP_WALL) == ST_DECLARED, "wall starts merely declared");
    check(t.refreshWall(true), "gaining a wall anchor is a change");
    check(t.statusOf(SELF, CAP_WALL) == ST_EXERCISED, "wall:1 exercises the capability");
    check(!t.refreshWall(true), "refreshWall is idempotent");
    // The laptop goes away and the node reconciles onto a stream with no date.
    check(t.refreshWall(false), "losing the anchor is a change");
    check(t.statusOf(SELF, CAP_WALL) == ST_DECLARED,
          "losing wall drops to declared, not to absent");
    // ⚠ A node that never declared it must not acquire it by a refresh.
    Table u;
    u.begin(SELF, CAP_MIC);
    check(!u.refreshWall(true), "refreshWall cannot grant an undeclared capability");
    check(u.statusOf(SELF, CAP_WALL) == ST_ABSENT, "and it stays absent");
  }

  // ---- 5. UNKNOWN never collapses into ABSENT ----------------------------------------
  // This is the three-V4 case: heard on the mesh, running pre-stage-1 firmware, sending no
  // digest at all. A table that reported them as capability-less would report the fleet's
  // LoRa spine as having no radio.
  {
    Table t;
    t.begin(SELF, CAP_MIC);
    check(t.sawNode(0x010, 1000), "sawNode reports a NEW peer");
    check(!t.sawNode(0x010, 1200), "and reports nothing on a repeat (log on change only)");
    check(!t.sawNode(SELF, 1200), "seeing ourselves is never a new peer");
    check(t.peerCount() == 1, "a silent node is still a peer");
    check(t.unknownPeers() == 1, "and it counts as a blind spot");
    check(t.statusOf(0x010, CAP_LORA) == ST_UNKNOWN, "its capabilities are UNKNOWN");
    check(t.statusOf(0x010, CAP_MIC) == ST_UNKNOWN, "every bit is unknown, not absent");
    check(t.statusOf(0x999, CAP_MIC) == ST_UNKNOWN, "a node never seen at all is unknown");
  }

  // ---- 6. digest round-trip, and the refusals ----------------------------------------
  {
    Table a;
    a.begin(PEER, (uint16_t)(CAP_GPS | CAP_SPEAKER | CAP_DISPLAY));
    a.exercise(CAP_GPS);
    a.verify(CAP_SPEAKER);

    uint8_t d[DIGEST_LEN_MAX];
    const size_t n = a.buildDigest(d, sizeof(d), 1000);
    check(n == DIGEST_HDR, "a digest with no known peers is header-only");

    Table b;
    b.begin(SELF, CAP_MIC);
    check(b.ingest(PEER, d, n, 2000) & Table::ING_NEW_PEER, "first digest = new peer");
    check(b.statusOf(PEER, CAP_GPS) == ST_EXERCISED, "exercised survives the wire");
    check(b.statusOf(PEER, CAP_SPEAKER) == ST_VERIFIED, "verified survives the wire");
    check(b.statusOf(PEER, CAP_DISPLAY) == ST_DECLARED, "declared survives the wire");
    check(b.statusOf(PEER, CAP_MIC) == ST_ABSENT, "a spoken-for gap reads ABSENT");
    check(b.ingest(PEER, d, n, 2100) == 0, "re-ingesting the same digest changes nothing");

    // Refusals. Each must leave the table untouched rather than half-parsed.
    check(b.ingest(PEER, d, DIGEST_HDR - 1, 3000) == 0, "a short digest is refused");
    uint8_t bad[DIGEST_LEN_MAX];
    memcpy(bad, d, n);
    bad[0] = 0xFD;                       // the TRACE field's magic, in the wrong slot
    check(b.ingest(PEER, bad, n, 3000) == 0, "wrong magic is refused");
    memcpy(bad, d, n);
    bad[1] = (uint8_t)(DIGEST_VERSION + 1);
    check(b.ingest(PEER, bad, n, 3000) == 0, "a future version is refused, not guessed");
    memcpy(bad, d, n);
    bad[9] = SOCIAL_DIGEST_PEERS + 1;    // claims more peers than the format allows
    check(b.ingest(PEER, bad, n, 3000) == 0, "an over-long peer count is refused");
    memcpy(bad, d, n);
    bad[9] = 1;                          // claims a peer entry that is not in the bytes
    check(b.ingest(PEER, bad, n, 3000) == 0, "a truncated peer list is refused");
    check(b.statusOf(PEER, CAP_GPS) == ST_EXERCISED, "no refusal disturbed the table");
  }

  // ---- 7. a peer's masks are clamped DOWN, never up -----------------------------------
  // A digest whose exercised bits exceed its declared bits is corrupt or mid-upgrade. The
  // safe reading is the lower one: believing it would be the "declared rendered as has"
  // failure arriving over the air instead of from a build.
  {
    uint8_t d[DIGEST_LEN_MAX] = {0};
    d[0] = DIGEST_MAGIC; d[1] = DIGEST_VERSION;
    d[2] = (uint8_t)(CAP_MIC & 0xFF); d[3] = 0;             // declared: mic only
    d[4] = 0xFF; d[5] = 0xFF;                               // verified: everything
    d[6] = 0xFF; d[7] = 0xFF;                               // exercised: everything
    d[8] = 3; d[9] = 0;
    Table t;
    t.begin(SELF, CAP_IMU);
    check(t.ingest(PEER, d, DIGEST_HDR, 1000) != 0, "a self-contradicting digest parses");
    check(t.statusOf(PEER, CAP_MIC) == ST_EXERCISED, "the declared bit survives at full");
    check(t.statusOf(PEER, CAP_GPS) == ST_ABSENT,
          "an exercised bit with no declaration reads ABSENT, not exercised");
  }

  // ---- 8. staleness: serial-number arithmetic, and the wrap ---------------------------
  {
    Table t;
    t.begin(SELF, CAP_MIC);
    // Hand-build a digest from PEER whose peer list holds OUR id at an old epoch.
    for (int i = 0; i < 5; ++i) t.exercise(CAP_MIC), t.verify(CAP_MIC);  // move our epoch
    const uint8_t ours = t.epoch();

    uint8_t d[DIGEST_LEN_MAX] = {0};
    d[0] = DIGEST_MAGIC; d[1] = DIGEST_VERSION;
    d[2] = (uint8_t)(CAP_GPS & 0xFF); d[3] = 0;
    d[4] = 0; d[5] = 0; d[6] = 0; d[7] = 0;
    d[8] = 1; d[9] = 1;
    const uint16_t us = shortId(SELF);
    d[DIGEST_HDR + 0] = (uint8_t)(us & 0xFF);
    d[DIGEST_HDR + 1] = (uint8_t)(us >> 8);
    d[DIGEST_HDR + 2] = ours;                       // they are up to date
    check(!(t.ingest(PEER, d, DIGEST_HDR + DIGEST_PEER, 1000)
            & Table::ING_THEY_ARE_STALE_ABOUT_US), "an equal epoch is not stale");
    check(t.staleReports() == 0, "and nothing is counted");

    d[DIGEST_HDR + 2] = (uint8_t)(ours - 1);        // they are one behind
    check(t.ingest(PEER, d, DIGEST_HDR + DIGEST_PEER, 2000)
          & Table::ING_THEY_ARE_STALE_ABOUT_US, "a lagging epoch is stale");
    check(t.staleReports() == 1, "and it is counted once");
    check(t.lastStaleFrom() == PEER, "and attributed to the reporter");

    d[DIGEST_HDR + 2] = (uint8_t)(ours + 1);        // they are AHEAD (we rebooted)
    t.ingest(PEER, d, DIGEST_HDR + DIGEST_PEER, 3000);
    check(t.staleReports() == 1, "an epoch ahead of ours is not OUR staleness");

    // ⚠ The wrap, tested at the actual seam. Promotions are one-way, so the only way to
    // move the epoch 256 times is CAP_WALL — the one capability that can be lost. Toggling
    // it 256 times brings the epoch back to 0, and a peer reporting 255 is then exactly
    // ONE behind. A plain `<` reads that as 255 AHEAD and the pair never re-converges.
    Table w;
    w.begin(SELF, (uint16_t)(CAP_MIC | CAP_WALL));
    for (int i = 0; i < 128; ++i) { w.refreshWall(true); w.refreshWall(false); }
    check(w.epoch() == 0, "256 wall transitions wrap the epoch back to 0");

    uint8_t wd[DIGEST_LEN_MAX] = {0};
    memcpy(wd, d, DIGEST_HDR + DIGEST_PEER);
    wd[DIGEST_HDR + 2] = 255;
    check(w.ingest(PEER, wd, DIGEST_HDR + DIGEST_PEER, 4000)
          & Table::ING_THEY_ARE_STALE_ABOUT_US,
          "epoch 255 against our 0 is BEHIND, not ahead (255->0 wrap)");
    wd[DIGEST_HDR + 2] = 1;
    const uint16_t before = w.staleReports();
    w.ingest(PEER, wd, DIGEST_HDR + DIGEST_PEER, 5000);
    check(w.staleReports() == before, "epoch 1 against our 0 is genuinely ahead");
  }

  // ---- 9. the peer list rotates ------------------------------------------------------
  // With more peers than digest slots, every peer must eventually be named, or a node that
  // never appears can never learn whether anyone's view of it is current.
  {
    Table t;
    t.begin(SELF, CAP_MIC);
    const uint32_t others[] = {0x010, 0x011, 0x012, 0x100, 0x101, 0x200};
    const size_t nOthers = sizeof(others) / sizeof(others[0]);
    uint8_t d[DIGEST_LEN_MAX] = {0};
    d[0] = DIGEST_MAGIC; d[1] = DIGEST_VERSION; d[8] = 1; d[9] = 0;
    d[2] = (uint8_t)(CAP_BLE & 0xFF); d[3] = 0;
    for (size_t i = 0; i < nOthers; ++i) t.ingest(others[i], d, DIGEST_HDR, 1000);
    check(t.peerCount() == nOthers, "all six peers are held");

    bool seen[nOthers];
    memset(seen, 0, sizeof(seen));
    uint8_t out[DIGEST_LEN_MAX];
    for (int pass = 0; pass < 8; ++pass) {
      const size_t n = t.buildDigest(out, sizeof(out), 2000);
      const uint8_t listed = out[9];
      check(listed <= SOCIAL_DIGEST_PEERS, "never more peers than the format allows");
      check(n == DIGEST_HDR + (size_t)listed * DIGEST_PEER, "length matches the count");
      for (uint8_t k = 0; k < listed; ++k) {
        const uint8_t* e = out + DIGEST_HDR + (size_t)k * DIGEST_PEER;
        const uint16_t id = (uint16_t)(e[0] | (e[1] << 8));
        for (size_t i = 0; i < nOthers; ++i)
          if (shortId(others[i]) == id) seen[i] = true;
      }
    }
    bool all = true;
    for (size_t i = 0; i < nOthers; ++i) if (!seen[i]) all = false;
    check(all, "rotation names every peer within a few beacons");
  }

  // ---- 10. a silent peer is never listed in our digest --------------------------------
  // Reporting epoch 0 for a node that has never spoken would assert we hold a stale view
  // of it, turning our own silence into a disagreement.
  {
    Table t;
    t.begin(SELF, CAP_MIC);
    (void)t.sawNode(0x010, 1000);
    uint8_t out[DIGEST_LEN_MAX];
    t.buildDigest(out, sizeof(out), 1000);
    check(out[9] == 0, "a heard-but-silent peer is not named in the digest");
  }

  // ---- 11. buildDigest never writes a partial digest ----------------------------------
  {
    Table t;
    t.begin(SELF, CAP_MIC);
    uint8_t out[DIGEST_LEN_MAX];
    check(t.buildDigest(out, DIGEST_HDR - 1, 1000) == 0, "short buffer = 0, not a stub");
    check(t.buildDigest(nullptr, sizeof(out), 1000) == 0, "null buffer = 0");
    check(t.buildDigest(out, DIGEST_HDR, 1000) == DIGEST_HDR, "exact header room works");
  }

  // ---- 12. fade is not absence --------------------------------------------------------
  {
    Table t;
    t.begin(SELF, CAP_MIC);
    uint8_t d[DIGEST_LEN_MAX] = {0};
    d[0] = DIGEST_MAGIC; d[1] = DIGEST_VERSION; d[2] = (uint8_t)(CAP_GPS & 0xFF); d[9] = 0;
    t.ingest(PEER, d, DIGEST_HDR, 1000);
    const Peer* p = t.find(PEER);
    check(p != nullptr, "the peer is held");
    check(!t.faded(*p, 1000 + SOCIAL_PEER_FADE_MS / 2), "recent = not faded");
    check(t.faded(*p, 1000 + SOCIAL_PEER_FADE_MS + 1), "old = faded");
    check(t.peerCount() == 1, "a faded peer is still in the table");
    check(t.statusOf(PEER, CAP_GPS) == ST_DECLARED, "and still reports what it claimed");
  }

  // ---- 13. quorum and the pose ceiling ------------------------------------------------
  {
    Table t;
    t.begin(SELF, (uint16_t)(CAP_MIC | CAP_IMU));
    t.exercise((uint16_t)(CAP_MIC | CAP_IMU));
    check(t.poseCeiling() == POSE_SHAPE_ONLY, "no GPS anywhere = shape only");
    check(t.quorum(CAP_MIC) == 1, "self counts in a quorum");

    // A peer that DECLARES a GPS but has never got a fix pins nothing. The T-Deck spent a
    // bring-up session proving a wired, declared GPS can sit at no-fix indoors.
    uint8_t d[DIGEST_LEN_MAX] = {0};
    d[0] = DIGEST_MAGIC; d[1] = DIGEST_VERSION;
    d[2] = (uint8_t)(CAP_GPS & 0xFF); d[3] = 0;
    d[4] = (uint8_t)(CAP_GPS & 0xFF); d[5] = 0;    // verified, not exercised
    d[9] = 0;
    t.ingest(PEER, d, DIGEST_HDR, 1000);
    check(t.declaredQuorum(CAP_GPS) == 1, "the declaration is counted");
    check(t.quorum(CAP_GPS) == 0, "but a fixless GPS exercises nothing");
    check(t.poseCeiling() == POSE_SHAPE_ONLY, "and pins no degree of freedom");

    d[6] = (uint8_t)(CAP_GPS & 0xFF); d[7] = 0;    // now it has a fix
    d[8] = 1;
    t.ingest(PEER, d, DIGEST_HDR, 2000);
    check(t.quorum(CAP_GPS) == 1, "an exercised GPS counts");
    check(t.poseCeiling() == POSE_TRANSLATION, "one fix pins at most the origin");
  }

  // ---- 14. the names a renderer depends on --------------------------------------------
  {
    check(strcmp(capName(3), "gps") == 0, "capName maps the GPS bit");
    check(capName(CAP_COUNT)[0] == 'b', "an unnamed bit renders as b<n>, never blank");
    check(strcmp(statusGlyph(ST_UNKNOWN), statusGlyph(ST_ABSENT)) != 0,
          "unknown and absent are visually distinct");
  }

  printf("%s  (%d checks, %d failures)\n", gFails ? "FAILED" : "OK", gChecks, gFails);
  return gFails ? 1 : 0;
}
