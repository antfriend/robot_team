// test_timestream.cpp — the team time stream (Part 2 of timestream-handoff.md).
//
// The wire round-trip checks are the cheap half. The ones that matter are the
// behavioural invariants, because every one of them is a property the handoff calls
// out as a hazard and this design claims to have made structural:
//
//   * OLDER STREAM WINS — the merge preserves the timeline with more history, and
//     it is decided by the clocks themselves, not by node id (Pulse elects its
//     conductor by lowest id; that rule is wrong here and must not leak in).
//   * MONOTONICITY — no node's stream clock EVER moves backward. Not on adoption,
//     not on a merge, not when a lower-id node joins, not at the 49.7-day millis()
//     wrap. Already-written records can never be re-ordered by a later merge.
//   * CONVERGENCE — two nodes that each started their own stream end up on ONE
//     stream, including the pathological exact-tie case, and they stay there.
//   * THE WALL ANCHOR IS CARRIED, NOT LOST — a node that knows the date and then
//     joins a longer-running blind stream still knows the date afterwards, to the
//     millisecond, and a disagreement between two anchors is REPORTED rather than
//     silently resolved.
//   * A SLEW IS NOT A RATCHET — a peer a few ms ahead on our own stream must not
//     drag us forward on every frame.
#include "TimeStream.h"
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

using namespace timestream;

// Hand one node's anchor to another, as a HELLO would.
static Event pass(Engine& from, uint32_t from_id, uint32_t from_ms,
                  Engine& to, uint32_t to_ms) {
  Anchor a;
  if (!from.fill(a, from_ms)) return EV_NONE;
  uint8_t buf[64];
  size_t n = buildAnchor(buf, sizeof(buf), a);
  Anchor b;
  if (n != ANCHOR_LEN || !parseAnchor(buf, n, b)) return EV_NONE;
  return to.onAnchor(b, from_id, to_ms);
}

int main() {
  // --- wire round-trip ------------------------------------------------------
  {
    Anchor a;
    a.stream_id = 0xDEADBEEFu;
    a.stream_ms = 0x0102030405060708ull;
    a.wall_off_ms = -1234567890123ll;
    a.flags = ANCHOR_WALL;
    uint8_t buf[32];
    memset(buf, 0xAA, sizeof(buf));
    size_t n = buildAnchor(buf, sizeof(buf), a);
    Anchor b;
    CHECK(n == ANCHOR_LEN, "anchor encodes to %d bytes", (int)ANCHOR_LEN);
    CHECK(parseAnchor(buf, n, b), "anchor parses");
    CHECK(b.stream_id == a.stream_id && b.stream_ms == a.stream_ms &&
              b.wall_off_ms == a.wall_off_ms && b.flags == a.flags,
          "anchor round-trips every field (incl. a NEGATIVE wall offset)");
    CHECK(buildAnchor(buf, ANCHOR_LEN - 1, a) == 0, "short cap writes nothing");
    // The compatibility case: a node still on old firmware sends a 0-byte HELLO.
    CHECK(!parseAnchor(buf, 0, b), "an empty HELLO payload is not a stream anchor");
    CHECK(!parseAnchor(buf, ANCHOR_LEN - 1, b), "a truncated anchor is rejected");
  }

  // --- origin ---------------------------------------------------------------
  {
    Engine e;
    e.begin(0x300, 0);
    CHECK(!e.have(), "a fresh node has no stream");
    CHECK(e.nowMs(1000) == 0, "and its stream clock reads 0");
    CHECK(e.origin(3000, 0x1234), "origin() starts one");
    CHECK(e.have() && e.streamId() != 0, "stream id is non-zero (0 means 'none')");
    CHECK(!e.wall(), "a self-started stream does NOT know the date");
    CHECK(e.nowMs(3000) == 0, "the stream clock reads 0 at its own origin");
    CHECK(e.nowMs(63000) == 60000, "and elapsed-since-origin thereafter");
    CHECK(e.unixMs(63000) == 0 && e.wallSec(63000) == 0,
          "unix time is 0 while wall:0 — TTDB-RFC-0005's 'unknown'");
    CHECK(!e.origin(9000, 1), "origin() is a no-op once a stream exists");
    CHECK(e.last().ev == EV_ORIGIN && e.last().new_ms == 0,
          "the transition records ORIGIN at t_ms 0");
  }

  // A reboot must produce a DIFFERENT stream id, or records written before and after
  // claim one stream with two incompatible clocks.
  {
    Engine a, b;
    a.begin(0x300, 0); a.origin(3000, 0xAAAA);
    b.begin(0x300, 0); b.origin(3000, 0xBBBB);
    CHECK(a.streamId() != b.streamId(),
          "same node + same boot ms + different entropy -> different stream id");
    Engine c, d;
    c.begin(0x200, 0); c.origin(3000, 0);
    d.begin(0x300, 0); d.origin(3000, 0);
    CHECK(c.streamId() != d.streamId(),
          "different nodes with NO entropy still differ (node id is mixed in)");
  }

  // --- adoption: a node with no stream joins one that is running ------------
  {
    Engine old_node, fresh;
    old_node.begin(0x200, 0);
    old_node.origin(0);                       // running since t=0
    fresh.begin(0x300, 900000);               // boots 15 minutes later

    Event ev = pass(old_node, 0x200, 900000, fresh, 900000);
    CHECK(ev == EV_ADOPTED, "a node with no stream ADOPTS the one it hears");
    CHECK(fresh.streamId() == old_node.streamId(), "and takes its id");
    CHECK(fresh.nowMs(900000) == 900000,
          "its clock jumps to the stream's age (900000 ms), not to its own uptime");
    CHECK(fresh.last().prev_id == 0 && fresh.last().offset_ms == 0,
          "adoption from nothing has no remap to record");
    // Both now agree, and stay agreeing as time passes.
    CHECK(fresh.nowMs(960000) == old_node.nowMs(960000),
          "the two clocks track each other afterwards");
  }

  // --- THE MERGE RULE: older wins, and the young node is the one that moves --
  {
    Engine old_node, young;
    old_node.begin(0x200, 0);
    old_node.origin(0);                       // 15 min of history by t=900000
    young.begin(0x100, 0);                    // NOTE: the LOWER node id
    young.origin(895000);                     // only 5 s of history

    const uint64_t young_before = young.nowMs(900000);
    Event ev = pass(old_node, 0x200, 900000, young, 900000);
    CHECK(ev == EV_RECONCILED, "the younger stream yields");
    CHECK(young.streamId() == old_node.streamId(),
          "OLDER STREAM WINS — and it won against the LOWER node id, which is the "
          "rule Pulse uses and the rule this must not use");
    CHECK(young.nowMs(900000) == 900000, "the yielding node lands on the older clock");
    CHECK(young.nowMs(900000) > young_before,
          "MONOTONIC: yielding moved its clock FORWARD (5000 -> 900000)");
    CHECK(young.last().prev_ms == young_before &&
              young.last().offset_ms == (int64_t)(900000 - young_before),
          "the remap offset is recorded, so records under the lost stream stay readable");

    // And the older node does NOT move when it hears the younger one.
    const uint64_t old_before = old_node.nowMs(901000);
    Engine other;
    other.begin(0x100, 0);
    other.origin(900500);
    Event ev2 = pass(other, 0x100, 901000, old_node, 901000);
    CHECK(ev2 == EV_NONE, "the older stream ignores a younger one");
    CHECK(old_node.nowMs(901000) == old_before, "and its clock does not move");
    CHECK(old_node.outAged() == 1, "but it COUNTS the peer it out-aged");
  }

  // --- convergence, including the exact tie ---------------------------------
  {
    Engine a, b;
    a.begin(0x300, 0); a.origin(0, 1);
    b.begin(0x200, 0); b.origin(0, 2);        // identical age, different ids
    CHECK(a.streamId() != b.streamId(), "two distinct streams of the SAME age");

    // Exchange in both directions, twice: this must terminate on one stream.
    for (int i = 0; i < 2; ++i) {
      pass(a, 0x300, 10000, b, 10000);
      pass(b, 0x200, 10000, a, 10000);
    }
    CHECK(a.streamId() == b.streamId(),
          "an exact age tie still converges (broken on stream id, not left split)");
    CHECK(a.nowMs(10000) == b.nowMs(10000), "and the clocks agree");

    // Stable: further exchanges change nothing.
    const uint32_t sid = a.streamId();
    const uint64_t t = a.nowMs(20000);
    pass(a, 0x300, 20000, b, 20000);
    pass(b, 0x200, 20000, a, 20000);
    CHECK(a.streamId() == sid && a.nowMs(20000) == t,
          "converged state is stable — no flapping between the two ids");
  }

  // --- a slew is not a ratchet ---------------------------------------------
  {
    Engine a, b;
    a.begin(0x200, 0); a.origin(0);
    b.begin(0x300, 0);
    pass(a, 0x200, 100000, b, 100000);        // b joins a's stream
    CHECK(b.streamId() == a.streamId(), "b is on a's stream");
    CHECK(b.nowMs(100000) == 100000, "and its clock matches a's");

    // a reads 10 ms ahead — a transit residual, not a disagreement. Ten exchanges
    // must not accumulate into a drift of their own.
    for (int i = 1; i <= 10; ++i)
      pass(a, 0x200, 100000 + i * 10 + 10, b, 100000 + i * 10);
    CHECK(b.nowMs(100100) == 100100,
          "a peer 10 ms ahead on our OWN stream does not drag us forward, 10x over");

    // A real disagreement, past the floor, IS corrected — and only forward.
    Anchor big;
    a.fill(big, 105100);                      // a is now genuinely 5 s ahead
    Event ev = b.onAnchor(big, 0x200, 100100);
    CHECK(ev == EV_SLEW, "a 5 s gap on our own stream is a slew");
    CHECK(b.nowMs(100100) == 105100, "corrected forward by exactly the gap");

    Anchor behind;
    b.fill(behind, 100100);
    behind.stream_ms -= 60000;                // a peer 60 s BEHIND us
    b.onAnchor(behind, 0x200, 100100);
    CHECK(b.nowMs(100100) == 105100,
          "MONOTONIC: a peer behind us on our own stream never pulls us back");
  }

  // --- the wall anchor ------------------------------------------------------
  {
    const uint64_t kNow = 1754200000000ull;   // a real-ish Unix epoch ms

    Engine e;
    e.begin(0x300, 0);
    Event ev = e.anchorWall(kNow, 5000, 0x1);
    CHECK(ev == EV_ORIGIN,
          "a lone cabled node with no stream gets BOTH a stream and a date");
    CHECK(e.have() && e.wall(), "stream:1 wall:1");
    CHECK(e.unixMs(5000) == kNow, "unix time is exactly what the laptop said");
    CHECK(e.wallSec(5000) == (uint32_t)(kNow / 1000), "and wallSec is its seconds");
    CHECK(e.unixMs(65000) == kNow + 60000, "and it advances with the stream");
    CHECK(e.last().wall && e.last().unix_ms == kNow, "the record carries the date");

    // It spreads on the 2 s HELLO to a peer on the same stream that had no date.
    Engine peer;
    peer.begin(0x200, 0);
    pass(e, 0x300, 65000, peer, 65000);
    CHECK(peer.have() && peer.wall(), "the peer adopts the stream AND its date");
    CHECK(peer.unixMs(65000) == kNow + 60000, "to the millisecond");

    Engine blind;
    blind.begin(0x201, 0);
    pass(e, 0x300, 65000, blind, 65000);      // joins, gets the date with the stream
    CHECK(blind.wall(), "a joiner inherits the date");

    // Same stream, peer already on it, date arrives later -> EV_ANCHORED.
    Engine late;
    late.begin(0x202, 0);
    Engine src;
    src.begin(0x203, 0);
    src.origin(0);
    pass(src, 0x203, 10000, late, 10000);
    CHECK(late.have() && !late.wall(), "joined a stream with no date");
    src.anchorWall(kNow, 10000, 0x1);
    Event ev2 = pass(src, 0x203, 10000, late, 10000);
    CHECK(ev2 == EV_ANCHORED, "learning the date on a stream we already hold is ANCHORED");
    CHECK(late.unixMs(10000) == kNow, "and the date is right");
  }

  // --- the date SURVIVES a merge into a longer-running blind stream ---------
  {
    const uint64_t kNow = 1754200000000ull;
    Engine dated, ancient;
    dated.begin(0x300, 0);
    dated.anchorWall(kNow, 5000, 0x1);        // knows the date, 0 s of history
    ancient.begin(0x200, 0);
    ancient.origin(0);                        // 1 hour of history, no date
    const uint64_t hour = 3600000;

    Event ev = pass(ancient, 0x200, hour, dated, 5000 + 0);
    CHECK(ev == EV_RECONCILED, "the dated node yields its younger stream");
    CHECK(dated.streamId() == ancient.streamId(), "and joins the older one");
    CHECK(dated.wall(), "IT STILL KNOWS THE DATE — the anchor is carried, not dropped");
    CHECK(dated.unixMs(5000) == kNow,
          "and the date is unchanged to the millisecond across the merge");
    CHECK(dated.last().wall_conflict_ms == 0, "no conflict: only one side was anchored");

    // ... and now it propagates the date BACK to the stream that outlived it.
    Event ev2 = pass(dated, 0x300, 5000, ancient, hour);
    CHECK(ev2 == EV_ANCHORED, "the older stream learns the date from the younger node");
    CHECK(ancient.unixMs(hour) == kNow, "consistently");
  }

  // --- two anchors that DISAGREE are reported, not silently resolved -------
  {
    const uint64_t kNow = 1754200000000ull;
    Engine a, b;
    a.begin(0x200, 0);
    a.anchorWall(kNow, 0, 0x1);               // origin + date at t=0
    b.begin(0x300, 60000);                    // boots a minute later, so its stream
    b.anchorWall(kNow + 60000 + 7000, 60000, 0x1);  // is younger — and its laptop is
                                              // 7 s fast, which is the point here
    CHECK(b.unixMs(60000) == kNow + 67000, "b's own date is 7 s off a's");

    Event ev = pass(a, 0x200, 60000, b, 60000);
    CHECK(ev == EV_RECONCILED, "b yields to a's older stream");
    CHECK(b.last().wall_conflict_ms == 7000,
          "the 7 s disagreement between the two anchors is REPORTED to the ms, "
          "not silently swallowed by the merge");
    CHECK(b.unixMs(60000) == kNow + 60000 && b.unixMs(60000) == a.unixMs(60000),
          "and b now carries a's date, not its own");
  }

  // --- the 49.7-day millis() wrap ------------------------------------------
  {
    Engine e;
    const uint32_t near_wrap = 0xFFFFF000u;
    e.begin(0x300, near_wrap);
    e.origin(near_wrap);
    CHECK(e.nowMs(near_wrap) == 0, "stream starts at 0 near the wrap");
    CHECK(e.nowMs(0xFFFFFFFFu) == 0x0FFFu, "counts up to the wrap");
    CHECK(e.nowMs(0x00000010u) == 0x1010u,
          "AND STRAIGHT THROUGH IT — a stream that guarantees ordering must not go "
          "backward at 49.7 days because the platform counter does");
    // A slightly out-of-order sample (a recv callback's now_ms arriving after a
    // loop's) must NOT be mistaken for a wrap and add 49 days.
    CHECK(e.nowMs(0x0000000Bu) == 0x1010u,
          "a small backward step holds the high-water mark instead of adding 49 days");
  }

  // --- the @LAT90 record ----------------------------------------------------
  {
    char buf[TIMESTREAM_BUF];
    Engine e;
    e.begin(0x300, 0);
    e.origin(3000, 7);
    size_t n = buildStreamRecord(buf, sizeof(buf), 0, e.last(), 0x300, 0);
    CHECK(n > 0, "ORIGIN renders");
    CHECK(strstr(buf, "@LAT90LON0") != 0, "in the @LAT90 lane");
    CHECK(strstr(buf, "**STREAM-ORIGIN**") != 0, "with the ORIGIN verb");
    CHECK(strstr(buf, " wall:0 ") != 0, "wall:0 — it has a timeline, not a date");
    CHECK(strstr(buf, "t_ms:0 ") != 0, "at stream time 0");
    CHECK(strstr(buf, "created:0") != 0,
          "and created:0, because Unix seconds are genuinely unknown here");
    CHECK(strstr(buf, "**REMAP**") == 0, "no remap: nothing was abandoned");
    CHECK(strstr(buf, "**PROVENANCE** rule:TimeStream/older_stream_wins") != 0,
          "provenance names the rule");

    // A merge record must carry the mapping back to the abandoned stream.
    Engine young, old_node;
    old_node.begin(0x200, 0); old_node.origin(0);
    young.begin(0x100, 0); young.origin(895000);
    pass(old_node, 0x200, 900000, young, 900000);
    n = buildStreamRecord(buf, sizeof(buf), 4, young.last(), 0x100, 0);
    CHECK(n > 0 && strstr(buf, "**STREAM-RECONCILED**") != 0, "RECONCILED renders");
    CHECK(strstr(buf, "**REMAP** prev_stream:0x") != 0, "carrying the old stream id");
    CHECK(strstr(buf, "prev_t_ms:5000") != 0, "and our clock in it");
    CHECK(strstr(buf, "offset_ms:895000") != 0, "and the offset to add to map forward");
    CHECK(strstr(buf, "from:0x200") != 0, "and who we heard it from");

    // Wall record.
    Engine w;
    w.begin(0x300, 0);
    w.anchorWall(1754200000000ull, 0, 0x1);
    n = buildStreamRecord(buf, sizeof(buf), 1, w.last(), 0x300, 1754200000u);
    CHECK(n > 0 && strstr(buf, "**WALL** unix_ms:1754200000000") != 0,
          "the wall anchor is on the record");
    CHECK(strstr(buf, "created:1754200000") != 0,
          "and NOW created: carries real Unix seconds");

    // A SLEW is deliberately not a record — it happens on every drift correction.
    Engine s;
    s.begin(0x300, 0); s.origin(0);
    Anchor ahead;
    s.fill(ahead, 1000);
    ahead.stream_ms += 5000;
    s.onAnchor(ahead, 0x200, 1000);
    CHECK(s.last().ev == EV_SLEW, "a drift correction is a SLEW");
    CHECK(buildStreamRecord(buf, sizeof(buf), 0, s.last(), 0x300, 0) == 0,
          "and writes NO record — routine correction must not flood the lane");

    // Never truncate.
    CHECK(buildStreamRecord(buf, 40, 0, young.last(), 0x100, 0) == 0,
          "a too-small buffer writes NOTHING rather than a half record");
  }

  printf("\n%s (%d failures)\n", fails ? "FAILURES" : "ALL PASS", fails);
  return fails ? 1 : 0;
}
