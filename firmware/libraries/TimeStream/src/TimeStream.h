// TimeStream.h — the team time stream: a fleet-owned timeline that survives the
// laptop's absence.
//
// ---------------------------------------------------------------------------
// THE PROBLEM
// ---------------------------------------------------------------------------
// Every percept record this fleet writes carries `synced:0` unless a laptop has
// pushed a TIME_SYNC, and on `synced:0` the node throws its timestamp away
// (`created:0 updated:0 touched:0`). Three things break as a result:
//
//   1. TBEW recency is INERT. TTDB-RFC-0005 makes `touched` the recency anchor and
//      salience decays from it. With `touched:0` an @LAT91 belief's `sal` can never
//      fade and EPS = sal x (255-conf)/255 has no time term at all. The epistemic
//      weight machinery cannot function on a device with no clock.
//   2. @LAT94's acoustic transient timestamp — the Phase-3 TDoA groundwork — is
//      local `millis()`, i.e. not comparable with any other node's.
//   3. @LAT93 transitions cannot be ordered across nodes.
//
// The single `synced` bit is the actual defect: it conflates TWO orthogonal facts —
// *we agree with each other* and *we know what day it is*. A fleet in a garden with
// no laptop in sight has a perfectly good shared timeline; it simply cannot name the
// date. So the bit becomes two fields, and they ride on every record:
//
//     stream:<u32>   WHICH shared timeline this record belongs to
//     wall:<0|1>     is that timeline anchored to a real-world date
//
// ---------------------------------------------------------------------------
// THE ONE IDEA THAT MAKES IT SMALL
// ---------------------------------------------------------------------------
// **A stream's clock reads ELAPSED-SINCE-ITS-OWN-ORIGIN.** It starts at 0 when a
// node finds no stream to join. Everything else falls out of that choice:
//
//   * The merge rule the handoff asked for — OLDER STREAM WINS, because it preserves
//     more history — becomes "the larger clock wins", since an older stream has been
//     counting longer.
//   * MONOTONICITY comes free, and this is the part worth pausing on. The handoff
//     lists it as a separate hazard ("adopting a stream can move the clock BACKWARD,
//     putting already-written records out of order"). It cannot happen here: yielding
//     to an older stream always moves this node's clock FORWARD, because that is the
//     definition of the stream it is yielding to. **The merge rule IS the
//     monotonicity guarantee** — they are not two mechanisms that have to agree.
//   * The same comparison handles the two cases that look different but are not:
//     a foreign stream and a drifting peer on our own. Both reduce to *is the sender
//     ahead of me?* So there is one rule in `onAnchor`, not a table.
//
// The consequence, stated because it is a real property and not an oversight: the
// stream clock is a RATCHET. It advances at the rate of the fastest crystal that has
// ever been heard on it, and it never runs backward on any node. For ordering and
// recency — the two things it exists for — that is exactly the right trade; for
// measuring a DURATION, use the node's own `millis()` delta, which is what
// MotionPercept's `dt_ms` already does.
//
// ---------------------------------------------------------------------------
// WHY NOT JUST USE THE PULSE CLOCK
// ---------------------------------------------------------------------------
// `pulse::Engine` already carries a shared time base with an election, and it is
// tempting to declare `pulseNow()` the stream. Two reasons not to:
//
//   1. **Its election is by lowest node id, not by age** (TTN-RFC-0010 §4). A young
//      node with a low id legitimately takes the baton, and every follower's clock
//      then jumps BACKWARD to the newcomer's epoch. That is correct for a band —
//      phase is all that matters and a lurch is inaudible at a handoff — and fatal
//      for a log. The handoff says it plainly: *do not reuse that rule here; they
//      are different jobs.*
//   2. The band is measured tight (+-9 ms across three runs, companion.md §6) and
//      is the one subsystem in this fleet that is fully working. Hanging record
//      timestamps off it would put every future timeline change in the blast radius
//      of the beat.
//
// So the stream rides ALONGSIDE the chart on the same frames, with its own rule.
// The two clocks stay independent on purpose.
//
// ---------------------------------------------------------------------------
// TRANSPORT
// ---------------------------------------------------------------------------
// The anchor rides on **HELLO**, which every node already emits every 2 s with an
// EMPTY payload — so this is purely additive, and a node still carrying old firmware
// sends 0 bytes and is simply not a stream participant rather than a parse error.
//
// It deliberately does NOT ride on PULSE, even though PULSE is the obvious carrier:
// only the CONDUCTOR emits a PULSE, and the conductor is elected by id, so the node
// holding the oldest stream usually is not the one allowed to speak. A stream that
// only the conductor can announce is a stream that cannot win the merge it is
// supposed to win.
#pragma once
#include <stdint.h>
#include <stddef.h>

#ifndef TIMESTREAM_LANE
// @LAT90 — the stream lane. Sits above the belief lane (91), the outcome side log
// (92) and the transition lane (93), outside the 94..97 percept block.
#define TIMESTREAM_LANE 90
#endif

#ifndef TIMESTREAM_LISTEN_MS
// How long a booting node listens before starting a stream of its own. Three HELLO
// periods (2 s each), so a peer's anchor gets three chances to arrive first.
//
// Forking a stream is not harmful — the merge rule heals it within one more HELLO —
// but it costs an @LAT90 ORIGIN plus an @LAT90 RECONCILED, and it stamps whatever was
// written in between with a stream id that then loses. Listening is cheaper.
// Deliberately LONGER than PULSE_LISTEN_WINDOW_MS (3 s): a band that waits to start
// sounds hesitant, whereas a log that waits to start loses nothing.
#define TIMESTREAM_LISTEN_MS 6000
#endif

#ifndef TIMESTREAM_ORIGIN_SETTLE_MS
// How long a freshly originated stream must SURVIVE before its @LAT90 ORIGIN record
// is written. The listen window above reduces forking; this handles what is left.
//
// THE DEFECT IT FIXES (measured on the Cardputer, 2026-08-03). The listen window is
// a race, and it is lost often: two of three consecutive reboots heard no peer anchor
// inside 6 s, originated, and then — on the NEXT reboot — heard one in time and
// adopted. Each lost race left a permanent `STREAM-ORIGIN` behind, while the return
// to the fleet stream was correctly SILENT (an ADOPTED onto a stream the lane already
// explains is the rejoin case, which is deduped). So the lane accumulated "I started
// X, I started Y" and never said the node left them. With `companion.py` resetting
// the cabled node on nearly every invocation, that took the Cardputer from 13 to 15
// records against a cap of 16 in a single session.
//
// The lane's contract is ONE RECORD PER SETTLED STATE, NOT ONE PER HOP. A stream that
// is abandoned three seconds later was never a settled state, so it should never have
// been written. Holding the record and dropping it if the node moves on is the whole
// fix — and it costs nothing when the origin IS real, because a node that boots alone
// stays on its own stream and the record lands one settle window later.
//
// ⚠ THE HOLD MUST NOT OUTLAST THE FIRST RECORD STAMPED WITH THE STREAM, or that
// record carries an id the lane has not explained — which is the very failure @LAT90
// exists to prevent, reintroduced from the other side. Two things keep that true:
//   * this window is well under the shortest lane flush period (60 s), so no percept
//     window can be stamped and written before it elapses; and
//   * the hold is released EARLY, from service(), the moment the TTDB grows at all —
//     which covers event-driven writes that answer to no flush period, such as a
//     @LAT100 prune marker written seconds after boot (exactly what this session did).
// Raising this above 60000 would break the first guarantee. Don't.
#define TIMESTREAM_ORIGIN_SETTLE_MS 30000
#endif

#ifndef TIMESTREAM_SLEW_MS
// Within our OWN stream, ignore a peer that is ahead by less than this. Without a
// floor here two nodes ratchet each other forward by the frame's transit delay on
// every exchange: A adopts B's stamp minus transit, so A lands a few ms behind B,
// so B's next frame is "ahead" again. At a 2 s HELLO that is a few ms every 2 s —
// ~1000x worse than the crystal drift the correction exists to remove.
//
// 50 ms is comfortably above ESP-NOW transit (single-digit ms) and comfortably below
// anything this stream is used to decide: it anchors 60-second percept windows and a
// TBEW decay measured in minutes. It is NOT tight enough for TDoA — that tier reads
// sub-millisecond and must use the band clock's phase, not this.
#define TIMESTREAM_SLEW_MS 50
#endif

namespace timestream {

// What just happened to this node's sense of the shared timeline. The caller writes
// one @LAT90 record per event (except SLEW, which is routine drift correction and
// would flood the lane).
enum Event : uint8_t {
  EV_NONE = 0,
  EV_ORIGIN,      // found no stream and started one
  EV_ADOPTED,     // had no stream and joined one that was already running
  EV_RECONCILED,  // HAD a stream, heard an older one, and yielded to it
  EV_ANCHORED,    // gained (or changed) the wall-clock anchor for our stream
  EV_SLEW,        // routine forward correction within our own stream — no record
};
const char* eventName(uint8_t ev);

// ---------------------------------------------------------------------------
// The wire anchor — what one node tells another about the timeline it is on.
// ---------------------------------------------------------------------------
// Little-endian, appended to a HELLO payload:
//   [0..3]   stream_id   u32   0 = sender has no stream (nothing to adopt)
//   [4..11]  stream_ms   u64   sender's stream clock, sampled as the frame is built
//   [12..19] wall_off_ms i64   stream_ms + wall_off = Unix epoch ms (valid iff wall)
//   [20]     flags       u8    bit0 wall
struct Anchor {
  uint32_t stream_id = 0;
  uint64_t stream_ms = 0;
  int64_t  wall_off_ms = 0;
  uint8_t  flags = 0;
};
const size_t ANCHOR_LEN = 21;
enum AnchorFlag : uint8_t {
  ANCHOR_WALL = 1 << 0,   // wall_off_ms is meaningful: this stream knows the date
};

// Write `a` into `p` (>= ANCHOR_LEN). Returns bytes written, or 0 if cap is short.
size_t buildAnchor(uint8_t* p, size_t cap, const Anchor& a);
// Read an anchor. False on a short buffer — including the 0-byte HELLO payload an
// un-reflashed node sends, which is the compatibility case, not an error.
bool parseAnchor(const uint8_t* p, size_t len, Anchor& a);

// ---------------------------------------------------------------------------
// What changed, for the @LAT90 record. Populated on every non-NONE event.
// ---------------------------------------------------------------------------
struct Transition {
  uint8_t  ev = EV_NONE;
  uint32_t prev_id = 0;       // the stream we left (0 = we had none)
  uint64_t prev_ms = 0;       // our clock in that stream, at this instant
  uint32_t new_id = 0;
  uint64_t new_ms = 0;
  int64_t  offset_ms = 0;     // new_ms - prev_ms: the mapping that keeps the records
                              // we already wrote interpretable instead of orphaned
  uint32_t from_node = 0;     // who we heard it from (0 = ourselves / the laptop)
  bool     wall = false;
  uint64_t unix_ms = 0;       // 0 unless wall
  // Both sides claimed a wall anchor and they DISAGREED by this many ms. Surfaced
  // rather than silently resolved: two laptops, or one laptop and a stale anchor
  // carried across a merge, is a real condition and the fleet's signature failure
  // mode is the one nobody printed.
  int64_t  wall_conflict_ms = 0;
};

class Engine {
 public:
  // node_id is this node's logical id; now_ms = millis().
  void begin(uint32_t node_id, uint32_t now_ms);

  // Start a stream of our own, having heard none. `entropy` should be hardware
  // randomness (esp_random()) or 0 — it exists so that the SAME node rebooting
  // starts a DIFFERENTLY IDENTIFIED stream. A reboot really is a new timeline: its
  // clock restarts at 0, and if it reused the id, records written before and after
  // would claim one stream with two incompatible clocks. (The merge rule would still
  // heal the live clock — the node would see peers ahead and slew forward — but the
  // already-written history would be unreadable, which is the thing `stream:` is for.)
  // No-op if we already have a stream.
  bool origin(uint32_t now_ms, uint32_t entropy = 0);

  // A HELLO anchor arrived from `src`. Applies the merge rule and returns the event.
  // `recv_ms` = millis() sampled at receipt, so the offset adopted carries only the
  // transit delay as its residual (the same construction as pulse::onBeacon).
  Event onAnchor(const Anchor& a, uint32_t src, uint32_t recv_ms);

  // The laptop supplied wall-clock time (TIME_SYNC / TTN-RFC-0008). Starts a stream
  // first if we have none, so a lone cabled node ends up with both facts rather than
  // a date and no timeline. Returns EV_ANCHORED, or EV_ORIGIN if it also had to
  // start the stream (the caller writes one record either way; ORIGIN carries wall:1).
  Event anchorWall(uint64_t unix_ms, uint32_t now_ms, uint32_t from_node = 0,
                   uint32_t entropy = 0);

  // Fill the anchor to put on our HELLO. False (and a zeroed anchor) if we have no
  // stream — say nothing rather than advertise stream 0.
  bool fill(Anchor& out, uint32_t now_ms);

  bool     have() const { return have_; }
  uint32_t streamId() const { return stream_id_; }
  bool     wall() const { return wall_; }
  // The stream clock: ms since this stream's origin. 0 if we have no stream — but
  // check have(), because 0 is also a legitimate reading in the first millisecond.
  uint64_t nowMs(uint32_t now_ms);
  // Unix epoch ms, or 0 if this stream has no wall anchor.
  uint64_t unixMs(uint32_t now_ms);
  // Unix epoch SECONDS for a record's `created:`/`updated:`/`touched:` fields, or 0
  // when unknown. TTDB-RFC-0005 §4 defines `touched` in Unix seconds, so this is the
  // spec-conformant value and 0 (= unknown) is the spec-conformant fallback.
  //
  // ⚠ It is ALSO why on-device TBEW decay cannot use `touched` alone: a fleet with no
  // laptop has a perfectly usable timeline and still writes 0 here. The stream frame
  // (`t_ms:` beside `stream:` on the record body) is what a node decays against.
  uint32_t wallSec(uint32_t now_ms);

  const Transition& last() const { return last_; }

  // Peers whose stream we out-aged and therefore ignored. They will learn better from
  // our next HELLO, 2 s away — this is a counter, not a problem, but a nonzero value
  // that never falls means a peer is not hearing us at all.
  uint32_t outAged() const { return out_aged_; }

 private:
  // Monotonic ms since begin(), immune to the 49.7-day millis() wrap. A stream that
  // exists to guarantee ordering must not go backward at 49.7 days just because the
  // platform's counter does. Only a LARGE backward step counts as a wrap, so a
  // timestamp sampled slightly out of order (a recv callback's now_ms reaching us
  // after a loop's) does not add 49 days.
  uint64_t mono(uint32_t now_ms);
  void adopt(const Anchor& a, uint64_t m, uint32_t src, uint8_t ev);

  uint32_t node_id_ = 0;
  bool     have_ = false;
  uint32_t stream_id_ = 0;
  int64_t  offset_ms_ = 0;    // stream_ms = mono() + offset_ms_
  bool     wall_ = false;
  int64_t  wall_off_ms_ = 0;  // stream_ms + wall_off = Unix epoch ms
  uint64_t wrap_ = 0;
  uint32_t last_now_ = 0;
  uint32_t out_aged_ = 0;
  Transition last_;
};

// ---------------------------------------------------------------------------
// THE TIME STAMP EVERY RECORD CARRIES
// ---------------------------------------------------------------------------
// Replaces the single `synced:<0|1>` that appeared in 7 record formats across 5
// libraries. It is defined ONCE, here, and rendered by buildStamp, because seven
// snprintf format strings that have to say the same thing is seven chances to drift
// — and a corpus half in one frame and half in another is worse than either.
//
//     t_ms:<ms> stream:0x<id> wall:<0|1>
//
// `stream:0x00000000` is meaningful and is NOT an error: it says this node had no
// shared timeline when it wrote the record, so `t_ms` is local `millis()` and is
// comparable with nothing but this node's own records. That is exactly what the old
// `synced:0` meant — the difference is that `stream:` also names the timeline when
// there IS one, which `synced:1` never did. A record that says `synced:1` cannot tell
// you WHICH clock it agreed with, and after a merge that is unanswerable.
//
// MIGRATION: readers must accept both. `synced:1` maps to "some stream, identity
// unknown"; `synced:0` maps to `stream:0`.
struct Stamp {
  uint64_t t_ms = 0;        // stream ms, or local millis() when stream_id == 0
  uint32_t stream_id = 0;
  bool     wall = false;
};
// Writes the triplet into `out`. Returns bytes written, or 0 if it did not fit.
size_t buildStamp(char* out, size_t cap, const Stamp& s);

// Render the @LAT90 record for `tr`. `lane_n` is the LON index in the lane,
// `t_sec` the Unix seconds for the header (0 when the stream has no wall anchor —
// which is the normal case and exactly what this whole lane exists to survive).
// Returns bytes written, or 0 if it did not fit. Writes NOTHING rather than
// truncating: a half-written provenance line is worse than no record.
size_t buildStreamRecord(char* out, size_t cap, int lane_n, const Transition& tr,
                         uint32_t node_id, uint32_t t_sec);

// ---------------------------------------------------------------------------
// IS THIS RECORD WORTH WRITING? (the @LAT90 dedup, added 2026-08-03)
// ---------------------------------------------------------------------------
// The lane is specified as "timeline CHANGES, not time", and the first two-node run
// showed it was not living up to that: it grew ONE RECORD PER REBOOT, and
// `companion.py` reboots the cabled node on every invocation — 0 to 7 records in one
// session against a cap of 16 (companion.md §6). Most of those said nothing: a node
// that reboots and rejoins THE STREAM IT WAS ALREADY ON has not changed timeline. The
// clearest case was a node re-adopting, from its peer, a stream it had itself
// originated four records earlier.
//
// The fix is to ask the STORE, not a counter and not NVS: the lane already knows which
// streams it has explained, so read it back before appending. Same discipline as Stage
// D's fold — a RAM flag would be cheaper, would survive no reboot, and is exactly the
// thing that reboot broke.
//
// ⚠ **A SOLO REBOOT'S `STREAM-ORIGIN` IS NOT THE DEFECT AND MUST KEEP BEING WRITTEN.**
// A node that boots alone genuinely IS on a new timeline — its clock restarts at 0 and
// its next records carry an id nothing else explains. (Persisting the id and RESUMING
// the old stream is the tempting alternative and it is wrong: the node cannot know how
// long it was powered off, so it would stamp records with times earlier than what a
// peer wrote during the downtime and break ordering at the stream level. Starting fresh
// is honest, and the merge restores continuity with a REMAP the moment a peer is heard.)

// Does this @LAT90 record body name `id` as a stream the node was ON?
//
// ⚠ **THE LEADING SPACE IN THE NEEDLE IS LOAD-BEARING.** A STREAM-RECONCILED record
// carries both `stream:0x<new>` and, on its REMAP line, `prev_stream:0x<old>`. A bare
// search for "stream:0x" matches the second, so an id the node had LEFT would read as
// one it still holds — and the record explaining a genuine return to it would be
// suppressed. `text` comes straight off flash and is not NUL-terminated, so the search
// is bounded by `len`.
bool recordNamesStream(const char* text, size_t len, uint32_t id);

// Does this @LAT90 record carry a wall anchor (`wall:1`)? Distinct from naming the
// stream: a lane can explain a stream without the date ever having been known.
bool recordIsWallAnchored(const char* text, size_t len);

// Would writing `tr` say anything the @LAT90 lane does not already say?
//   `named`    — some record in the lane already names tr.new_id
//   `anchored` — ...and at least one of those carries wall:1
//
// Suppresses exactly two things, and nothing else:
//   * ADOPTED onto a stream already explained — the rejoin case, i.e. the defect.
//   * ANCHORED on an already-anchored stream WITH NO CONFLICT. A conflicting anchor is
//     the most interesting record this lane can hold (two sources, or a stale anchor
//     carried across a merge), so it is always written.
// ORIGIN can never match (its id is new by construction) and RECONCILED is never
// suppressed: its REMAP offset is specific to that merge, and two merges onto one
// stream from different priors are different facts.
bool recordIsRedundant(const Transition& tr, bool named, bool anchored);

// Is a HELD `STREAM-ORIGIN` (see TIMESTREAM_ORIGIN_SETTLE_MS) due to be written?
// Portable and pure so the release rule is native-testable; the Arduino glue supplies
// the clock and the record count.
//
//   held_ms/held_records — millis() and Ttdb::recordCount() when the origin was held
//   now_ms/records_now   — the same two, now
//
// True on EITHER condition, and the record-count one exists because it is the case
// the time window cannot cover: a record stamped with this stream has already reached
// flash, so the explanation is owed immediately regardless of how young the stream is.
// The explaining record then lands one loop pass later — after the record it explains,
// which is honest ordering for an append-only log and readable either way.
bool originDue(uint32_t held_ms, uint32_t now_ms, int held_records, int records_now);

#ifndef TIMESTREAM_BUF
// Measured against the widest form (STREAM-RECONCILED, which carries both stream
// ids, both clocks, the offset, a wall conflict and the provenance line): 512 B is
// ~2x the worst case. buildStreamRecord returns 0 rather than truncating.
#define TIMESTREAM_BUF 512
#endif

}  // namespace timestream
