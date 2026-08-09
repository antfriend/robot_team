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
// Stage 3 (TTDB-RFC-0010 §5) adds the @LAT101 SOCIAL field — the fleet's FIRST FIELD
// lane — and with it the properties worth pinning are §5's normative ones:
//   * decay is evaluated on read and never written; a deposit accumulates against the
//     DECAYED value, not the stored one
//   * reclaim-lowest: a full table replaces the lowest DECAYED trace, ties to oldest
//   * the WRITER is tested against the READER (the stage-2 lesson: both individually
//     green missed the one defect that mattered), including the `last_ms:` needle whose
//     tail is literally `t_ms:`
//   * the sid is KEY-identified: same peer = same sid across reinforcement, rewrites and
//     ordinals; recomputable from (node, lane, key) alone
//   * §5.4 reload: unknown age clamps, never zeroes; UNKNOWN capabilities survive a
//     reboot as UNKNOWN, not ABSENT; flash never overwrites what the radio said
#include <cstdio>
#include <cstring>
#include "Social.h"
#include "Sid.h"
#include "TtdbParse.h"

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

  // ---- 15. co-presence: deposit, decay-on-read, accumulate-against-decayed -----------
  {
    Table t;
    t.begin(SELF, CAP_MIC);
    t.sawNode(PEER, 1000);
    const Peer* p = t.find(PEER);
    check(p != nullptr, "a reception creates the trace");
    check(t.copresenceAt(*p, 1000) == SOCIAL_COPRE_DEPOSIT, "one deposit = one deposit");
    // §5.1: nothing was written; the effective value halves purely on read.
    check(t.copresenceAt(*p, 1000 + SOCIAL_COPRE_HALF_LIFE_MS) == SOCIAL_COPRE_DEPOSIT / 2,
          "one half-life on read halves the trace");
    check(p->copre == SOCIAL_COPRE_DEPOSIT, "…and the STORED value did not move");
    // A second deposit a half-life later accumulates against the decayed value.
    t.sawNode(PEER, 1000 + SOCIAL_COPRE_HALF_LIFE_MS);
    check(t.copresenceAt(*p, 1000 + SOCIAL_COPRE_HALF_LIFE_MS) ==
              SOCIAL_COPRE_DEPOSIT / 2 + SOCIAL_COPRE_DEPOSIT,
          "a deposit adds to the decayed value, not the stale one");
    // Saturation: a burst of receptions pins at 255 and stays there.
    for (int i = 0; i < 20; ++i) t.sawNode(PEER, 2000000 + i);
    check(t.copresenceAt(*p, 2000020) == 255, "the trace saturates at 255");
  }

  // ---- 16. reclaim-lowest (RFC-0010 §5.3): lowest DECAYED goes, ties to oldest --------
  {
    Table t;
    t.begin(SELF, CAP_MIC);
    // Fill the table. Peer 0x10 is deposited once at t=0 (long decayed by t=900000);
    // everyone else is fresh at t=900000. The victim must be 0x10 — the lowest decayed
    // strength — even though it is NOT the longest-unheard by much on every row.
    t.sawNode(0x10, 0);
    for (uint8_t i = 1; i < SOCIAL_MAX_PEERS; ++i) t.sawNode(0x100u + i, 900000);
    check(t.peerCount() == SOCIAL_MAX_PEERS, "the table is full");
    check(t.reclaims() == 0, "no reclamation yet");
    t.sawNode(0x777, 900001);
    check(t.reclaims() == 1, "a full table reclaims exactly one slot");
    check(t.lastReclaimed() == 0x10, "…and it is the lowest DECAYED trace");
    check(t.find(0x10) == nullptr, "the reclaimed trace is gone");
    check(t.find(0x777) != nullptr, "the new trace is in");
    // No @LAT100 boundary is even expressible from here — the table has no Ttdb. That is
    // §5.3's rule made structural rather than behavioural.

    // Ties: two fully-decayed traces; the OLDER one goes.
    Table t2;
    t2.begin(SELF, CAP_MIC);
    t2.sawNode(0x11, 1000);   // older
    t2.sawNode(0x12, 2000);
    for (uint8_t i = 2; i < SOCIAL_MAX_PEERS; ++i) t2.sawNode(0x200u + i, 90000000);
    t2.sawNode(0x888, 90000001);   // both 0x11/0x12 read 0 by now — tie
    check(t2.lastReclaimed() == 0x11, "a strength tie resolves to the oldest trace");
  }

  // ---- 17. the WRITER against the READER (the stage-2 rule) ---------------------------
  {
    Table t;
    t.begin(SELF, CAP_MIC);
    uint8_t d[DIGEST_LEN_MAX] = {0};
    d[0] = DIGEST_MAGIC; d[1] = DIGEST_VERSION;
    d[2] = (uint8_t)(CAP_GPS | CAP_MIC); d[3] = 0;
    d[4] = (uint8_t)(CAP_GPS | CAP_MIC); d[5] = 0;
    d[6] = (uint8_t)CAP_GPS; d[7] = 0;
    d[8] = 7; d[9] = 0;
    t.ingest(PEER, d, DIGEST_HDR, 5000);

    timestream::Stamp st;
    st.t_ms = 123456789ull;
    st.stream_id = 0xe334a7e1u;
    st.wall = true;

    char rec[SOCIAL_PEER_RECORD_BUF];
    uint32_t sid_w = 0;
    const size_t m = t.buildPeerRecord(rec, sizeof(rec), 0, 3, 1786000000u, st, 6000,
                                       &sid_w);
    check(m > 0, "the record renders");
    check(sid_w != 0, "…with a sid");
    check(strstr(rec, "sid:00000000") == nullptr, "the placeholder was patched");

    PeerRecord r;
    check(Table::parsePeerRecord(rec, m, r), "the reader reads it back");
    check(r.node == PEER, "node round-trips");
    check(r.spoke, "spoke round-trips");
    check(r.declared == (uint16_t)(CAP_GPS | CAP_MIC), "declared round-trips");
    check(r.exercised == (uint16_t)CAP_GPS, "exercised round-trips");
    check(r.cap_epoch == 7, "cap_epoch round-trips");
    check(r.half_life_ms == SOCIAL_COPRE_HALF_LIFE_MS, "half-life round-trips");
    check(r.stream == 0xe334a7e1u, "stream round-trips");
    check(r.wall == 1, "wall round-trips");
    check(r.has_sid && r.sid == sid_w, "the reader reads the sid the writer wrote");

    // ⚠ THE NEEDLE: `last_ms:` ends in `t_ms:`. The record carries last_ms 6000-ish and
    // t_ms 123456789 — a reader matching the bare substring returns the wrong field with
    // both sides individually looking correct.
    check(r.t_ms == 123456789ull, "t_ms is the stamp's, not last_ms's tail");

    // The id is recomputable from (node, lane, key) alone — the verification property.
    char key[24];
    check(Table::peerKey(key, sizeof(key), PEER) > 0, "the key renders");
    check(strcmp(key, "node:0x00000200") == 0, "…at FULL width (1-byte squeezes collide)");
    check(sid::forKey(SELF, SOCIAL_FIELD_LANE, key) == sid_w,
          "a reader recomputes the sid from the key alone");
  }

  // ---- 18. KEY identity: reinforcement, rewrites and ordinals do not rename ----------
  {
    Table t;
    t.begin(SELF, CAP_MIC);
    t.sawNode(PEER, 1000);
    timestream::Stamp st;
    st.t_ms = 111; st.stream_id = 0xAAAA0001u; st.wall = false;
    char rec[SOCIAL_PEER_RECORD_BUF];
    uint32_t sid1 = 0, sid2 = 0, sid3 = 0;
    check(t.buildPeerRecord(rec, sizeof(rec), 0, 0, 1000, st, 2000, &sid1) > 0, "build 1");
    // Reinforce, decay, new ordinal, new stamp, new wall-clock — the trace's name holds.
    for (int i = 0; i < 5; ++i) t.sawNode(PEER, 3000 + i);
    st.t_ms = 999999; st.stream_id = 0xBBBB0002u; st.wall = true;
    check(t.buildPeerRecord(rec, sizeof(rec), 0, 7, 2000, st, 900000, &sid2) > 0, "build 2");
    check(sid1 == sid2, "same peer = same sid across reinforcement + ordinal + stamp");
    // A different subject gets a different name.
    t.sawNode(0x10, 5000);
    const Peer* p1 = t.peerAt(1);
    check(p1 && t.buildPeerRecord(rec, sizeof(rec), 1, 1, 2000, st, 5000, &sid3) > 0,
          "build 3");
    check(sid3 != sid1, "a different peer gets a different sid");
  }

  // ---- 19. §5.4 reload: unknown age clamps, never zeroes; flash never beats radio -----
  {
    Table t;
    t.begin(SELF, CAP_MIC);
    PeerRecord r;
    r.node = PEER; r.spoke = true;
    r.declared = (uint16_t)(CAP_GPS | CAP_MIC);
    r.verified = (uint16_t)(CAP_GPS | CAP_MIC);
    r.exercised = (uint16_t)CAP_GPS;
    r.cap_epoch = 9;
    r.copresence = 200;   // strong when persisted; age now unknowable
    check(t.loadPeer(r, 1000), "a reloaded trace enters the table");
    const Peer* p = t.find(PEER);
    check(p != nullptr, "…and is findable");
    check(t.copresenceAt(*p, 1000) == SOCIAL_COPRE_UNKNOWN_AGE,
          "unknown age CLAMPS the strength");
    check(t.copresenceAt(*p, 1000) > 0, "…and never zeroes it (faded, not absent)");
    check(p->age_unknown, "the trace is marked unknown-age");
    check(t.faded(*p, 1001), "a reloaded peer is FADED until actually heard");
    check(t.statusOf(PEER, CAP_GPS) == ST_EXERCISED, "reloaded masks report");
    check(t.persistDue(200000) == false,
          "a reload alone never schedules a rewrite of identical content");

    // A weak persisted trace reloads as itself — the clamp is a ceiling, not a floor.
    PeerRecord r2; r2.node = 0x10; r2.copresence = 30;
    t.loadPeer(r2, 1000);
    check(t.copresenceAt(*t.find(0x10), 1000) == 30, "below the clamp, stored wins");

    // A live reception re-dates the trace and clears the mark.
    t.sawNode(PEER, 2000);
    check(!t.find(PEER)->age_unknown, "a live reception dates the trace again");
    check(!t.faded(*t.find(PEER), 2001), "…and un-fades the peer");

    // Flash never overwrites what the radio already said: masks stay the LIVE ones.
    Table t2;
    t2.begin(SELF, CAP_MIC);
    uint8_t d[DIGEST_LEN_MAX] = {0};
    d[0] = DIGEST_MAGIC; d[1] = DIGEST_VERSION;
    d[2] = (uint8_t)CAP_MIC; d[3] = 0; d[8] = 3; d[9] = 0;
    t2.ingest(PEER, d, DIGEST_HDR, 500);
    PeerRecord stale; stale.node = PEER; stale.spoke = true;
    stale.declared = (uint16_t)CAP_GPS; stale.verified = (uint16_t)CAP_GPS;
    stale.cap_epoch = 1; stale.copresence = 10;
    t2.loadPeer(stale, 1000);
    check(t2.statusOf(PEER, CAP_MIC) == ST_DECLARED, "live masks survive a reload");
    check(t2.statusOf(PEER, CAP_GPS) == ST_ABSENT, "the gravestone's masks do not");

    // A corrupt record's masks re-clamp exactly as a corrupt digest's do.
    Table t3;
    t3.begin(SELF, CAP_MIC);
    PeerRecord bad; bad.node = 0x11; bad.spoke = true;
    bad.declared = (uint16_t)CAP_MIC;
    bad.verified = (uint16_t)(CAP_MIC | CAP_GPS);      // claims beyond its declaration
    bad.exercised = (uint16_t)CAP_GPS;                 // exercises the undeclared
    t3.loadPeer(bad, 1000);
    check(t3.statusOf(0x11, CAP_GPS) == ST_ABSENT, "flash is one more untrusted mouth");

    // UNKNOWN survives a reboot as UNKNOWN — never collapsed into ABSENT.
    Table t4;
    t4.begin(SELF, CAP_MIC);
    PeerRecord silent; silent.node = 0x12; silent.spoke = false; silent.copresence = 40;
    t4.loadPeer(silent, 1000);
    check(t4.statusOf(0x12, CAP_GPS) == ST_UNKNOWN,
          "a silent peer reloads as UNKNOWN, not capability-less");
  }

  // ---- 20. the persist policy: change-triggered, gapped, heartbeat needs reinforcement
  {
    Table t;
    t.begin(SELF, CAP_MIC);
    check(!t.persistDue(1000), "an empty field owes nothing");
    t.sawNode(PEER, 1000);
    check(!t.persistDue(1000), "a change inside the minimum gap waits");
    check(t.persistDue(SOCIAL_PERSIST_MIN_GAP_MS + 1), "…and fires once the gap passes");
    t.notePersisted(SOCIAL_PERSIST_MIN_GAP_MS + 1);
    check(!t.persistDue(SOCIAL_PERSIST_MIN_GAP_MS + 2), "persisting clears the debt");
    check(t.find(PEER)->reinforced == 0, "…and closes every open run (§5.2)");
    // Reinforcement alone: nothing until the heartbeat, then once.
    t.sawNode(PEER, SOCIAL_PERSIST_MIN_GAP_MS + 5000);
    check(!t.persistDue(SOCIAL_PERSIST_MIN_GAP_MS + 6000),
          "reinforcement alone is not a material change");
    const uint32_t hb = SOCIAL_PERSIST_MIN_GAP_MS + 1 + SOCIAL_PERSIST_HEARTBEAT_MS;
    check(t.persistDue(hb), "…until the heartbeat");
    t.notePersisted(hb);
    check(!t.persistDue(hb + SOCIAL_PERSIST_HEARTBEAT_MS + 1),
          "a heartbeat with nothing reinforced writes nothing — a node alone in a "
          "field is silent forever (§5.1 on flash)");
  }

  // ---- 21. the builder never truncates, and the buffer fits the worst case ------------
  {
    Table t;
    t.begin(SELF, CAP_MIC);
    uint8_t d[DIGEST_LEN_MAX] = {0};
    d[0] = DIGEST_MAGIC; d[1] = DIGEST_VERSION;
    d[2] = 0xFF; d[3] = 0xFF; d[4] = 0xFF; d[5] = 0xFF; d[6] = 0xFF; d[7] = 0xFF;
    d[8] = 255; d[9] = 0;
    t.ingest(PEER, d, DIGEST_HDR, 0xFFFFFFF0u);
    for (int i = 0; i < 70000; ++i) t.sawNode(PEER, 0xFFFFFFF0u);   // reinforced pegs
    timestream::Stamp st;
    st.t_ms = 0xFFFFFFFFFFFFFFFFull; st.stream_id = 0xFFFFFFFFu; st.wall = true;
    char rec[SOCIAL_PEER_RECORD_BUF];
    const size_t m = t.buildPeerRecord(rec, sizeof(rec), 0, 99, 0xFFFFFFFFu, st,
                                       0xFFFFFFF0u, nullptr);
    check(m > 0 && m < SOCIAL_PEER_RECORD_BUF, "the worst-case record fits the buffer");
    check(t.find(PEER)->reinforced == 0xFFFF, "the run-length counter saturates");
    // An undersized destination refuses whole — never a truncated record on flash.
    check(t.buildPeerRecord(rec, 200, 0, 0, 1, st, 1, nullptr) == 0,
          "an undersized buffer writes NOTHING, not a fragment");
  }

  printf("%s  (%d checks, %d failures)\n", gFails ? "FAILED" : "OK", gChecks, gFails);
  return gFails ? 1 : 0;
}
