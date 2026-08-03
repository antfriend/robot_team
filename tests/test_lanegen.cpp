// test_lanegen.cpp — the lane-generation boundary record (@LAT100).
//
// What is being proven here is small and specific: that a prune leaves behind a record
// which answers "was the index I am holding inside the generation that ended?", and
// that the field it answers with cannot be matched by accident. The ordering logic
// against flash lives in LaneGenNode.h (Arduino) and is exercised on hardware.
//
// Run: bash scratchpad/t.sh lanegen
#include <stdio.h>
#include <string.h>
#include "LaneGen.h"

static int fails = 0;

static void check(bool cond, const char* msg) {
  printf("%s: %s\n", cond ? "pass" : "FAIL", msg);
  if (!cond) ++fails;
}

static lanegen::Prune mk(uint8_t lane, int gen, int removed, int last_lon,
                         uint32_t stream, bool wall) {
  lanegen::Prune p;
  p.lane = lane;
  p.gen = gen;
  p.removed = removed;
  p.last_lon = last_lon;
  p.node_id = 0x00000300;
  p.stamp.t_ms = 6611291;
  p.stamp.stream_id = stream;
  p.stamp.wall = wall;
  return p;
}

int main() {
  char rec[512];

  // 1) The record says what a reader needs, in the frame the rest of the corpus uses.
  size_t n = lanegen::buildPruneRecord(rec, sizeof(rec), 0,
                                       mk(97, 1, 48, 47, 0x59fb8ce8, false), 0);
  check(n > 0, "a prune record is rendered");
  check(strstr(rec, "@LAT100LON0") != NULL, "it lands in the @LAT100 lane");
  check(strstr(rec, "**LANE-PRUNED** lane:97 gen:1 removed:48 last_lon:47") != NULL,
        "lane, generation, count and the highest index that existed are all stated");
  check(strstr(rec, "t_ms:6611291 stream:0x59fb8ce8 wall:0") != NULL,
        "it carries the standard stamp, rendered by buildStamp like the other seven");
  check(strstr(rec, "node:0x00000300") != NULL, "and names the node that pruned");
  // The edge must not point into the lane that was just emptied — a record whose whole
  // job is to keep citations interpretable cannot itself ship a dangling one.
  check(strstr(rec, "relates:prunes@LAT0LON0") != NULL,
        "its only edge is to the node's identity record, never into the pruned lane");
  check(strstr(rec, "@LAT97LON") == NULL,
        "it does NOT cite the pruned lane — that edge would dangle by construction");

  // 2) Truncation is refused. A half-written boundary is worse than none: it would
  //    read as a boundary for a different lane, or with a missing count.
  char small[64];
  check(lanegen::buildPruneRecord(small, sizeof(small), 0,
                                  mk(97, 1, 48, 47, 0x59fb8ce8, false), 0) == 0,
        "a buffer too small yields NOTHING rather than a truncated boundary");

  // 3) ⚠ THE NEEDLE. `lane:9` is a prefix of `lane:94`, `lane:95`, `lane:96`,
  //    `lane:97`. This corpus has been bitten twice by a needle matching inside a
  //    longer token — `prev_stream:` in the @LAT90 reader (which returned the stream a
  //    node had LEFT) and the firmware dedup needle that needs its leading space. The
  //    field is parsed as a number, so a prefix cannot match.
  n = lanegen::buildPruneRecord(rec, sizeof(rec), 3,
                                mk(94, 2, 12, 11, 0x59fb8ce8, true), 1785542400);
  check(lanegen::pruneRecordNamesLane(rec, n, 94),
        "a lane-94 boundary is recognised as lane 94");
  check(!lanegen::pruneRecordNamesLane(rec, n, 9),
        "and NOT as lane 9 — the prefix that a strstr needle would have matched");
  check(!lanegen::pruneRecordNamesLane(rec, n, 95) &&
            !lanegen::pruneRecordNamesLane(rec, n, 97),
        "nor as any other percept lane");
  // `last_lon:11` also contains digits after a colon; the needle carries the leading
  // space and the field name, so it cannot land there.
  check(strstr(rec, "last_lon:11") != NULL &&
            lanegen::pruneRecordNamesLane(rec, n, 94),
        "a neighbouring numeric field does not disturb the match");
  check(!lanegen::pruneRecordNamesLane("", 0, 97) &&
            !lanegen::pruneRecordNamesLane("**LANE-PRUNED** gen:1\n", 22, 97),
        "a body with no lane field names no lane (rather than defaulting to one)");

  // 4) Generation numbering is derived from what is on flash, so it survives reboots
  //    with no state: the first prune of a lane closes generation 1.
  check(lanegen::nextGeneration(0) == 1,
        "the first prune of a lane closes generation 1");
  check(lanegen::nextGeneration(2) == 3,
        "two boundaries already recorded -> the next prune closes generation 3");

  // 5) The wall-anchored case: the header gets real Unix seconds, and the stamp says
  //    the timeline knows the date. Both halves matter — `wall:1` without a `created:`
  //    would be a record that knows the date and refuses to say it.
  check(strstr(rec, "wall:1") != NULL && strstr(rec, "created:1785542400") != NULL,
        "a wall-anchored prune records the date in the header AND in the stamp");
  // And the ordinary garden case does not invent one.
  n = lanegen::buildPruneRecord(rec, sizeof(rec), 1,
                                mk(96, 1, 30, 29, 0x59fb8ce8, false), 0);
  check(strstr(rec, "created:0") != NULL && strstr(rec, "wall:0") != NULL,
        "an unanchored prune writes created:0 rather than a fabricated date");

  // 6) stream:0 is a legitimate state, not an error: a node pruning before it has
  //    heard anyone is on its own millis(), and the boundary must still be written.
  n = lanegen::buildPruneRecord(rec, sizeof(rec), 0, mk(95, 1, 48, 47, 0, false), 0);
  check(n > 0 && strstr(rec, "stream:0x00000000") != NULL,
        "a node with no shared timeline still records its boundary (stream:0)");

  printf("\n");
  if (fails) {
    printf("%d FAILURE(S)\n", fails);
    return 1;
  }
  printf("all lanegen tests passed\n");
  return 0;
}
