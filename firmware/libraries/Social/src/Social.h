// Social.h — the default network, stage 1: WHO IS HERE AND WHAT CAN THEY DO.
//
// `default-network.md` §6 stage 1. This library carries capability advertisement and
// nothing else: no lane, no belief, no field. It is RAM-only and cites nothing, exactly
// like `TraceField`, so TTDB-RFC-0010 §6.3's acceptance test ("the system must still be
// correct with it EMPTY") is trivially true — a node that just booted knows nothing about
// anybody and is fine, because a HELLO refills the table within one 2 s beacon.
//
// ---------------------------------------------------------------------------
// WHY CAPABILITIES AND POSITIONING ARE ONE FEATURE
// ---------------------------------------------------------------------------
// Everything the fleet can infer from *common information* is relational — do we hear each
// other, do we see the same access points, did that deposit get through — and a relation is
// invariant under moving the whole fleet. So common information yields the fleet's SHAPE
// and never its POSE: in 2D, translation (2), rotation (1) and reflection (1) are four
// degrees of freedom no amount of mutual observation can touch.
//
// Those four are broken only by a node holding a capability nobody else has. That is why
// this table is not metadata: **it is the list of who can collapse which ambiguity**, and
// `poseCeiling()` is the one number that says how much of its own shape the fleet can
// currently know. (⚠ RSSI amplitude is NOT on that list — measured 2-7x over-range and
// decorrelated from distance outdoors, companion.md.)
//
// ---------------------------------------------------------------------------
// THREE STATUSES, EARNED RATHER THAN COMPILED IN
// ---------------------------------------------------------------------------
//   declared   the build says the peripheral is there
//   verified   it answered at boot
//   exercised  it produced a percept that reached a lane
//
// ⚠ A self-declared capability is a CLAIM, and this repo's history is the argument for
// treating it as one: the BMI270 is at I2C 0x69 and not the published 0x68 (declared,
// unverifiable); `TFT_BL 45` silenced a speaker that was declared AND present (verified,
// never exercised); the T-Deck's battery divider reads 4.71 V, above the Li-ion ceiling,
// from constants nobody metered. Rendering `declared` as `has` is how those become lies.
//
// The invariant is enforced on write, not assumed: exercised subset-of verified subset-of
// declared. A tier cannot exercise a capability the board never claimed.
//
// ⚠ CAP_WALL IS DERIVED, NEVER STORED. "Can this node tell you the date" is `wall:<0|1>`
// and has been fleet-wide since 2026-08-03, kept deliberately separate from `stream:`
// because one bit used to conflate *we agree with each other* with *we know what day it
// is*. `refreshWall()` is the ONLY writer of that bit and it takes its argument from
// `timestream::Engine::wall()`. Setting it any other way re-creates the conflation that
// cost a release to remove.
//
// ---------------------------------------------------------------------------
// THE EPOCH, AND THE FALSIFIER IT EXISTS TO TEST
// ---------------------------------------------------------------------------
// You cannot know a broadcast was received — and on this fleet an absent ACK proves
// nothing, since `--op play` and a prune on a grown TTDB both succeed while no-ACKing. So
// "have I told X my capabilities" is not modelled. It is a send-side fact that stays true
// after X reboots and forgets.
//
// What is modelled is the DISAGREEMENT. Each node bumps `cap_epoch` when its own vector
// changes and reports, for each peer it knows, the epoch it currently holds for that peer.
// B hears A's beacon, finds its own entry in A's list, and sees A's copy of B's epoch lag:
// **B has learned from a direct experience of the beacon that A is out of date about B,
// with nobody having asked anybody anything.** That is the stigmergic form, and it is
// self-healing across reboots where a send-side flag is not.
//
// ⚠ BUT WITHIN ONE RADIO HOP IT SHOULD NEVER FIRE, AND THAT IS THE POINT. B's whole
// capability vector is in B's every beacon, so A converges in one 2 s period regardless.
// `staleReports()` is therefore an INSTRUMENT, not a mechanism: it measures whether the
// mechanism has any work to do. default-network.md §6 pre-registered the falsifier before
// this file existed — *if every node's view of every other converges on the first beacon
// and never disagrees, delete the staleness machinery and keep the masks*. It is expected
// to fire only where that assumption breaks: a peer heard over multiple hops, a digest
// whose peer list rotated past the node in question, or a LoRa budget too small to carry
// the vector every time.
#pragma once
#include <stdint.h>
#include <stddef.h>
#include <TimeStream.h>   // timestream::Stamp — the one stamp every record carries

namespace social {

// ---------------------------------------------------------------------------
// Capability bits
// ---------------------------------------------------------------------------
// ⚠ Bit positions are WIRE FORMAT. Append at the top end; never renumber, never reuse a
// retired bit. A node running older firmware reads a newer node's unknown bits as
// capabilities it has no name for, which `capName` renders as `b<n>` rather than dropping
// — an unnamed capability is still evidence that the peer has one.
enum Cap : uint16_t {
  CAP_MIC       = 1u << 0,   // can hear (@LAT94)
  CAP_SPEAKER   = 1u << 1,   // can sound
  CAP_IMU       = 1u << 2,   // can tell whether it moved (@LAT95) — the stillness witness
  CAP_GPS       = 1u << 3,   // can fix itself absolutely — the pose-breaking capability
  CAP_WIFI_SCAN = 1u << 4,   // can see entities (@LAT96)
  CAP_BLE       = 1u << 5,
  CAP_LORA      = 1u << 6,   // long-haul link (gated behind USE_LORA until Phase 4)
  CAP_DISPLAY   = 1u << 7,
  CAP_KEYS      = 1u << 8,   // an operator can act through this node
  CAP_STORE     = 1u << 9,   // holds a TTDB on a filesystem
  CAP_BATTERY   = 1u << 10,  // can read its own charge
  CAP_TEMP      = 1u << 11,
  CAP_WALL      = 1u << 12,  // ⚠ DERIVED from timestream wall(); see refreshWall()
  CAP_CONDUCT   = 1u << 13,  // can hold the pulse baton
  CAP_BRIDGE    = 1u << 14,  // has the laptop on a cable
};
const uint8_t CAP_COUNT = 15;

// Short tag for a table column. Never returns null.
const char* capName(uint8_t bit);

// ---------------------------------------------------------------------------
// Wire form
// ---------------------------------------------------------------------------
// Appended to HELLO after the 21-byte time-stream anchor and the 18-byte trace digest, so
// it sits at a FIXED offset and is itself self-describing in length. Same additive
// contract those two established and for the same reason: a node on older firmware appends
// nothing and is a NON-PARTICIPANT rather than a parse error.
//
// ⚠ The magic AND version are both load-bearing. The digest's position is defined as
// "after the trace digest"; a node that read the next block's bytes as capability masks
// would report peripherals that do not exist, which is worse than reporting none.
//
//   [0]      magic 0xFC
//   [1]      version
//   [2..3]   declared   u16 LE
//   [4..5]   verified   u16 LE
//   [6..7]   exercised  u16 LE
//   [8]      cap_epoch  u8
//   [9]      n_peers    u8
//   [10..]   n_peers x { peer u16 LE, epoch_we_hold u8 }
//
// The SENDER's node id is deliberately absent: it is already in the signed toot header, so
// putting it here would be a second copy that could disagree with the first.
const uint8_t DIGEST_MAGIC   = 0xFC;
const uint8_t DIGEST_VERSION = 1;
const size_t  DIGEST_HDR     = 10;
const size_t  DIGEST_PEER    = 3;

// How many peers this node can hold, and how many fit in one digest. They differ on
// purpose: the table remembers more than a beacon can carry, so `buildDigest` rotates
// through them round-robin. **That rotation is the one thing on this fleet today that can
// make a peer's epoch report genuinely lag** (5 nodes, 4 slots) — i.e. it is what gives
// `staleReports()` something to measure.
#ifndef SOCIAL_MAX_PEERS
#define SOCIAL_MAX_PEERS 8
#endif
#ifndef SOCIAL_DIGEST_PEERS
#define SOCIAL_DIGEST_PEERS 4
#endif

const size_t DIGEST_LEN_MAX = DIGEST_HDR + DIGEST_PEER * SOCIAL_DIGEST_PEERS;

// A peer not heard for this long is FADED, not gone. TTDB-RFC-0010 §6.4: a view that
// draws "present / absent" turns "nobody has been heard from for a while" into "there is
// no such node", and this fleet has already fabricated a two-node outage once that way
// ([[looping-companion-py-resets-bridge]]). Nothing is ever evicted for age — only for
// space, and then the longest-unheard goes first.
#ifndef SOCIAL_PEER_FADE_MS
#define SOCIAL_PEER_FADE_MS 10000u
#endif

// A peer's node id on the wire is its LOW 16 BITS. ⚠ This is an invariant on the fleet's
// id allocation, not a hash: every id in RobotTeamNodeId is <= 0x300, so the low half is
// unique. `tests/test_social.cpp` pins that against the enum, so allocating a colliding id
// fails the build rather than silently merging two nodes into one table row.
inline uint16_t shortId(uint32_t node) { return (uint16_t)(node & 0xFFFFu); }

// ---------------------------------------------------------------------------
// @LAT101 — the fleet's FIRST FIELD LANE (TTDB-RFC-0010 §5, stage 3)
// ---------------------------------------------------------------------------
// The SOCIAL field: one **PEER** trace per known peer, co-presence reinforced by the
// beacons this node already hears, decaying on a half-life. The live medium is this
// table, in RAM; the lane is its durable shadow, rewritten only on material change plus
// a slow heartbeat, so "decay is evaluated on read and never written" (§5.1) holds on
// flash as well as in RAM — steady state writes nothing.
//
// ⚠ THE LANE HAS NO PRUNE PATH, AND THAT IS THE STAGE-3 FALSIFIER (RFC-0010 §8.1).
// Reclamation is §5.3's reclaim-lowest, in RAM, when the table is full; a reclamation
// writes NO @LAT100 boundary because under KEY naming there is nothing to re-point.
// `lanegen::prune` already refuses anything outside 94-97, so no guard was widened to
// make this true. If operating this lane ever requires adding a `--lane 101` clear op,
// the RFC says to abandon it: the treadmill was not the cost that mattered.
//
// ⚠ Its identity kind is KEY (§4.2.7: every FIELD lane necessarily is — a trace renamed
// by its own reinforcement would be a new trace). The natural key is `node:0x%08lx`,
// FULL width: every 1-byte squeeze of this fleet's ids collides, and a key is one more
// place that lesson applies.
#define SOCIAL_FIELD_LANE 101

// Co-presence half-life. Long enough to out-live a brief absence (a reboot, a walk to
// the garden), short enough that "was here this morning" reads faded by lunch.
#ifndef SOCIAL_COPRE_HALF_LIFE_MS
#define SOCIAL_COPRE_HALF_LIFE_MS 600000u
#endif

// Deposit per reception heard from a peer (any toot — presence IS co-presence).
// Saturates at 255 in ~8 beacons (16 s of 2 s HELLOs) against a 10 min half-life.
#ifndef SOCIAL_COPRE_DEPOSIT
#define SOCIAL_COPRE_DEPOSIT 32
#endif

// ⚠ RFC-0010 §5.4: a trace whose age is UNKNOWN must not be treated as fully decayed.
// A record reloaded at boot is always unknown-age on these boards — setup() runs before
// the 6 s stream listen window, so the stamp available at load time is stream 0 —
// therefore reload clamps strength to this value and marks the trace, rather than
// either trusting the stored strength (overstates) or zeroing it (the forbidden
// "faded rendered as absent"). A same-stream ageing path was deliberately NOT built:
// on this fleet it could never run, and a mechanism that cannot run is the mistake
// stage 1's staleness response almost was.
#ifndef SOCIAL_COPRE_UNKNOWN_AGE
#define SOCIAL_COPRE_UNKNOWN_AGE 64
#endif

// Persist policy: material change (new peer, capability change, reclaim) waits out a
// minimum gap — a lane rewrite is a whole-file flash pass, and 60 s also keeps the
// first persist of a boot clear of the 30 s STREAM-ORIGIN settle hold — and unchanged
// reinforcement alone persists at most once per heartbeat, so the on-flash trace ages
// but its recency survives a reboot.
#ifndef SOCIAL_PERSIST_MIN_GAP_MS
#define SOCIAL_PERSIST_MIN_GAP_MS 60000u
#endif
#ifndef SOCIAL_PERSIST_HEARTBEAT_MS
#define SOCIAL_PERSIST_HEARTBEAT_MS 1800000u
#endif

// Record builder buffer. The builder writes NOTHING rather than truncating, so this is
// pinned in tests/test_social.cpp against a worst-case render in BOTH directions (fits
// this constant, would NOT fit a 320 B habit buffer).
#ifndef SOCIAL_PEER_RECORD_BUF
#define SOCIAL_PEER_RECORD_BUF 512
#endif

// ---------------------------------------------------------------------------
// Status of one capability on one node
// ---------------------------------------------------------------------------
// ⚠ UNKNOWN and ABSENT are different answers and must render differently. A V4 running
// pre-stage-1 firmware sends no digest at all: every capability on it is UNKNOWN, and a
// table that printed those as ABSENT would report the fleet's LoRa spine as having no
// radio. default-network.md §6: "the table must say so rather than reporting a V4 as
// capability-less."
enum Status : uint8_t {
  ST_UNKNOWN = 0,   // this node has never told us anything
  ST_ABSENT,        // it told us, and it does not have this
  ST_DECLARED,      // the build claims it
  ST_VERIFIED,      // it answered at boot
  ST_EXERCISED,     // it has actually produced something
};
const char* statusGlyph(Status s);

struct Peer {
  uint32_t node      = 0;
  uint16_t declared  = 0;
  uint16_t verified  = 0;
  uint16_t exercised = 0;
  uint8_t  epoch     = 0;
  uint32_t last_ms   = 0;   // last time we heard ANYTHING from it
  bool     heard     = false;
  bool     spoke     = false;  // has it ever sent a valid digest? (UNKNOWN vs ABSENT)
  // --- the @LAT101 co-presence trace (stored pair; effective value computed on read) ---
  uint8_t  copre         = 0;   // strength at copre_last_ms — never read directly,
  uint32_t copre_last_ms = 0;   //   use Table::copresenceAt() for the decayed value
  uint16_t reinforced    = 0;   // receptions folded since the last persist (§5.2 run-length)
  bool     age_unknown   = false;  // reloaded from flash with no relatable clock (§5.4)
};

// A parsed @LAT101 record — the READER's half, kept in the library so the native suite
// can test the writer against the reader (the stage-2 lesson: both sides individually
// green missed the one defect that mattered).
struct PeerRecord {
  uint32_t node        = 0;
  bool     spoke       = false;
  uint16_t declared    = 0;
  uint16_t verified    = 0;
  uint16_t exercised   = 0;
  uint8_t  cap_epoch   = 0;
  uint8_t  copresence  = 0;
  uint32_t half_life_ms = 0;
  uint16_t reinforced  = 0;
  uint64_t t_ms        = 0;
  uint32_t stream      = 0;
  int      wall        = -1;   // -1 = field absent
  uint32_t sid         = 0;
  bool     has_sid     = false;
};

// ---------------------------------------------------------------------------
// What the fleet can currently know about its own shape
// ---------------------------------------------------------------------------
// ⚠ THIS IS A CEILING FOR THIS INSTANT, AND NOT A BOUND OVER TIME. Both halves matter and
// they point in opposite directions:
//
//   * Upper bound NOW: capabilities are necessary, not sufficient. Three GPS-exercised
//     nodes pin the mirror only if they are also non-collinear and the shape estimate
//     itself is any good. So the renderer must say "at most" — reporting the ceiling as
//     the state is the same class of error as drawing a faded trace as an absent one.
//   * NOT an upper bound over time: one ROAMING GPS node reaches the same place by
//     visiting >=3 distinct spots (`companion.py anchor`'s rule, >=3 ties resolve the
//     mirror), and a capability table cannot see how many places a node has been. The
//     T-Deck is the fleet's roamer, so on this fleet that is the likely path, not a corner
//     case.
//
// The honest summary is therefore "what concurrent fixes could pin", which is exactly the
// question an operator standing in front of the fleet is asking.
enum PoseCeiling : uint8_t {
  POSE_SHAPE_ONLY = 0,  // no absolute fix anywhere: shape known, pose is one of four
  POSE_TRANSLATION,     // >=1 GPS-exercised node: origin pinnable
  POSE_ROTATION,        // >=2: orientation pinnable too
  POSE_FULL,            // >=3 non-collinear: the mirror can fall
};
const char* poseName(PoseCeiling p);

// ---------------------------------------------------------------------------
class Table {
 public:
  // `declared` is the board's compiled-in claim. Nothing is verified or exercised yet:
  // that is the whole point of having three words for it.
  void begin(uint32_t self_node, uint16_t declared);

  // Promote our own capabilities. Both clamp to the level below (a tier cannot exercise
  // what the board never declared), both are idempotent, and both bump `cap_epoch` ONLY on
  // a real change — an epoch that ticked every loop pass would make every peer permanently
  // "stale" and drown the instrument in its own noise.
  bool verify(uint16_t bits);
  bool exercise(uint16_t bits);

  // ⚠ THE ONLY WRITER OF CAP_WALL. Pass `timestream::Engine::wall()`. Kept as a separate
  // call rather than folded into exercise() so that grepping for CAP_WALL finds exactly
  // one assignment: the bit is a cache of the time stream's answer, never a second opinion
  // about it. Losing the wall anchor clears the bit, which is why this can lower a
  // capability and the other two cannot.
  bool refreshWall(bool have_wall);

  uint32_t selfNode()  const { return self_.node; }
  uint8_t  epoch()     const { return self_.epoch; }
  uint16_t declared()  const { return self_.declared; }
  uint16_t verified()  const { return self_.verified; }
  uint16_t exercised() const { return self_.exercised; }

  // Presence, with no capability claim attached. Called for ANY toot from a node — a V4
  // that never sends a digest is still a peer, and must appear in the table as one whose
  // capabilities are UNKNOWN. Returns true if this created the peer, so a caller can log
  // the transition rather than every beacon.
  // ⚠ MUTATES (it can evict on a full table), so it belongs to the service path, never the
  // recv callback. See the warning at the top of SocialNode.h.
  bool sawNode(uint32_t node, uint32_t now_ms);

  // Parse a peer's digest. `from` comes from the signed toot header. Returns a bitmask of
  // INGEST_* describing what changed, so the sketch can log on change only — a digest
  // arrives every 2 s per peer and says nothing new almost every time.
  enum Ingest : uint8_t {
    ING_NEW_PEER  = 1 << 0,
    ING_CAPS_CHANGED = 1 << 1,
    ING_THEY_ARE_STALE_ABOUT_US = 1 << 2,
  };
  uint8_t ingest(uint32_t from, const uint8_t* d, size_t len, uint32_t now_ms);

  // Serialise. Returns bytes written, or 0 if `cap` is short — never a partial digest.
  // ⚠ NOT const: it advances the round-robin cursor over the peer list, which is what
  // makes every peer's epoch eventually reported when there are more peers than slots.
  size_t buildDigest(uint8_t* p, size_t cap, uint32_t now_ms);

  // ---- queries -----------------------------------------------------------------
  uint8_t     peerCount() const;
  const Peer* peerAt(uint8_t i) const;      // 0..peerCount()-1, stable within a pass
  const Peer* find(uint32_t node) const;
  bool        faded(const Peer& p, uint32_t now_ms) const;

  // Status of `bit` on `node` (ours or a peer's). UNKNOWN for a node we have never heard
  // a digest from — see the warning on Status.
  Status statusOf(uint32_t node, uint16_t bit) const;

  // How many nodes (INCLUDING us) have `bit` at exercised / at declared-or-better. The
  // gap between the two is the fleet's honesty margin, and it is worth rendering.
  uint8_t quorum(uint16_t bit) const;
  uint8_t declaredQuorum(uint16_t bit) const;

  // Peers heard but never yet heard FROM in this protocol: the size of the blind spot.
  uint8_t unknownPeers() const;

  // See the falsifier note at the top of this file. `staleReports` counts the times a peer
  // told us its picture of us was behind ours; if this stays 0 across a run, the mechanism
  // is unnecessary at one hop and should be deleted rather than kept "just in case".
  uint16_t staleReports() const { return stale_reports_; }
  uint32_t lastStaleFrom() const { return last_stale_from_; }

  // The best pose the fleet's capabilities could support. See PoseCeiling.
  PoseCeiling poseCeiling() const;

  // ---- the @LAT101 field (TTDB-RFC-0010 §5) ------------------------------------
  // Decayed co-presence of a peer at `now_ms`. Pure — §5.1's "evaluated on read".
  uint8_t copresenceAt(const Peer& p, uint32_t now_ms) const;

  // §5.3 reclamations so far, and who went last — an instrument like staleReports():
  // with <=5 peers against SOCIAL_MAX_PEERS 8 slots this is EXPECTED to read zero on
  // this fleet, and the native suite is where the mechanism is actually exercised.
  uint16_t reclaims() const { return reclaims_; }
  uint32_t lastReclaimed() const { return last_reclaimed_; }

  // Does the on-flash shadow owe a rewrite? Material change gated by the minimum gap,
  // or unchanged reinforcement at most once per heartbeat.
  bool persistDue(uint32_t now_ms) const;
  // The lane was rewritten: close every open run (§5.2 — the persisted records stated
  // what they folded, so the counts restart) and start the gap/heartbeat clocks.
  void notePersisted(uint32_t now_ms);
  // A persist attempt was REFUSED (index full, removeLane failure): restart the gap
  // clock WITHOUT closing the runs or clearing the dirt, so the retry comes in one
  // minimum gap instead of every loop pass — the refusal prints once per gap, not as
  // a flood, and nothing pretends the lane was written.
  void deferPersist(uint32_t now_ms) { last_persist_ms_ = now_ms; }

  // Render peer `i`'s @LAT101 record into `out`, sid stamped (KEY: `node:0x%08lx`).
  // Strength is written DECAYED TO NOW — the TraceField digest rule: a persisted value
  // is a statement about the moment it was built, needing nothing but arrival.
  // Returns bytes, or 0 (never a truncated record). `sid_out` optional.
  size_t buildPeerRecord(char* out, size_t cap, uint8_t i, int lon, uint32_t t_sec,
                         const timestream::Stamp& ts, uint32_t now_ms,
                         uint32_t* sid_out = nullptr);

  // The natural key, public so a reader can RECOMPUTE the id rather than trust it —
  // the same contract as Reconciler::beliefKey.
  static size_t peerKey(char* out, size_t cap, uint32_t node);

  // Parse an @LAT101 record (writer's counterpart; see PeerRecord).
  // ⚠ `rec` MUST be NUL-terminated at or after `len`: bytes arrive from Ttdb::readBytes
  // un-terminated, and the numeric conversions read past `len` on an unterminated
  // buffer. The glue writes buf[got] = 0 before calling; a test buffer is a C string.
  static bool parsePeerRecord(const char* rec, size_t len, PeerRecord& out);

  // Seed the table from a reloaded record: §5.4 unknown-age clamp, masks re-clamped
  // exactly as ingest() clamps them, FADED until actually heard, and NEVER overwriting
  // a peer the radio has already told us more about. Does not mark the field dirty —
  // a reload followed by a persist of the same bytes would be a pointless rewrite.
  bool loadPeer(const PeerRecord& r, uint32_t now_ms);

 private:
  Peer*       slot(uint32_t node, uint32_t now_ms);   // find-or-make, evicting if needed
  const Peer* slotConst(uint32_t node) const;
  void        reinforce(Peer& p, uint32_t now_ms);    // decay-to-now, deposit, count

  Peer     self_;
  Peer     peers_[SOCIAL_MAX_PEERS];
  uint8_t  cursor_         = 0;   // round-robin over peers for the digest's peer list
  uint16_t stale_reports_  = 0;
  uint32_t last_stale_from_ = 0;
  // Field bookkeeping. `field_dirty_` is set by anything a persisted record would state
  // differently: a peer created, a capability mask or epoch changed, a slot reclaimed.
  bool     field_dirty_    = false;
  uint16_t reclaims_       = 0;
  uint32_t last_reclaimed_ = 0;
  uint32_t last_persist_ms_ = 0;
};

}  // namespace social
