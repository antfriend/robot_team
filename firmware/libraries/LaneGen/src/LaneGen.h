// LaneGen.h — LANE GENERATIONS: making a prune something a reader can survive.
//
// THE PROBLEM THIS EXISTS FOR (found 2026-08-03, by committing it).
//
// A citation in this corpus is an ORDINAL: `@LAT92LON0`'s header says
// `testifies_about@LAT95LON0,derived_from@LAT97LON1`, and `PerceptLearn` stores those
// same numbers as `acting_lane_` / `staged_lane_` / `scored_lane_`. The ordinal is the
// count of records in the lane at the moment the citing record was written.
//
// A prune resets that count to zero. The lane then refills — and every pre-existing
// citation silently starts resolving to a DIFFERENT record with the same index. Not a
// dangling pointer, which is honest and detectable: a live pointer to the wrong thing.
// On the Cardputer, 32 records (24 @LAT92 outcomes + 8 @LAT91 beliefs) cite
// `@LAT97LON<n>`, and the @LAT97 prune that opened the lane again re-pointed all 32 in
// one CMD. Nothing resolves those edges today, so no output was wrong — but the corpus
// IS the deliverable, and "a live pointer to the wrong thing" is the exact failure
// class this fleet keeps naming.
//
// The fix is not to avoid pruning (the lanes fill in 48 minutes and the node goes
// blind) and not to rewrite history (you cannot honestly edit what a record said). It
// is to make the boundary itself a record, so a citation written before it reads as
// "generation 1, pruned" instead of resolving into generation 2. This is the same
// move the time stream already makes with `@LAT90`'s REMAP + `prev_stream:` — a record
// stamped by a superseded timeline stays interpretable because the supersession was
// written down. A prune is that event one level down.
//
// ---------------------------------------------------------------------------
// WHY @LAT100 AND NOT ONE OF THE OBVIOUS PLACES — all three were checked, not assumed
// ---------------------------------------------------------------------------
//  * NOT inside the lane it prunes (as a header record of the new generation). The
//    NEXT prune of that lane would delete its own history. Decisive on its own.
//  * NOT `@LAT90`, the timeline lane, however close the concept sits. That lane's
//    dedup scans it record by record (`TimeStreamNode.h`, the loop over
//    `record(i).lat == TIMESTREAM_LANE`) and asks `recordNamesStream(body, id)`. A
//    prune record carrying the standard `t_ms: stream:0x… wall:` stamp would answer
//    YES for whatever stream it was written under — and suppress a later, legitimate
//    STREAM-ADOPTED record as "already explained". The lane would go quiet about a
//    real timeline change because of an unrelated prune. Same needle-collision shape
//    as `prev_stream:` and the leading space, one lane over.
//  * NOT `@LAT89`. `isNodeRecord()` is `lat > -90 && lat < 90` on BOTH consoles, so 89
//    is a NODE: prune markers would appear as navigable places on the globes, with an
//    eyeball and a status line. 90..99 are all taken (90 timeline, 91 belief, 92
//    outcome, 93 transition, 94..97 percepts, 98 belief attestations, 99 sync), so the
//    machinery block continues upward. `int_after()` parses arbitrary ints, and the
//    globes filter by `lat < 90`, so 100 is inert everywhere that matters.
//
// ---------------------------------------------------------------------------
// THE INVARIANT: NO PRUNE WITHOUT A MARKER
// ---------------------------------------------------------------------------
// The marker-lane capacity is checked BEFORE the rewrite, and a prune that cannot be
// recorded does not happen. A silent prune is the thing this file exists to stop, so
// it must not be able to reappear as this file's own failure mode.
//
// Two consequences worth stating:
//  * A prune of an EMPTY lane writes no marker and reports success. That keeps
//    `removePerceptLanes`' documented idempotency, and it is also what makes the CMD
//    safe to retry — which matters, because a lane clear is one of the operations
//    whose flash rewrite outruns the ACK window (companion.md §6: retry with
//    `--attempts 6+`). A retry finds nothing to remove and writes no second marker.
//  * If the rewrite succeeds and the marker append then fails, the function returns
//    false and says so on serial — the node ACKs only on true, so the operator learns.
//    A retry after that finds an empty lane and writes nothing, so the marker is lost
//    for good. That window is small (an append, after a whole-file rewrite has already
//    succeeded) but it is real, and it is the one case where this design degrades to
//    the old silent behaviour. It is reported, not hidden.
#pragma once
#include <stdint.h>
#include <stddef.h>
#include <TimeStream.h>

namespace lanegen {

// The lane the markers live in. See the header comment for why it is not 89, 90, or
// the pruned lane itself.
const int16_t LANE = 100;

// A generation boundary: "generation `gen` of lane `lane` ended here."
struct Prune {
  uint8_t lane = 0;         // the percept lane pruned (94..97)
  int gen = 0;              // the generation that ENDED, 1-based
  int removed = 0;          // records dropped in the rewrite
  int last_lon = 0;         // highest LON index that existed in that generation
  uint32_t node_id = 0;
  timestream::Stamp stamp;  // t_ms / stream / wall, rendered by buildStamp
};

// Render the @LAT100 record. `lane_n` is its LON index, `t_sec` the Unix seconds for
// the header (0 when the stream has no wall anchor — the normal case in a garden).
// Returns bytes written, or 0 if it did not fit: writes NOTHING rather than
// truncating, because a half-written boundary is worse than no boundary at all.
//
// `last_lon` is derivable from `removed` today (a prune takes the whole lane, so the
// indices are 0..removed-1) and is written anyway. The question a reader actually has
// is "is the index I am holding inside the generation that ended?", and a record
// should answer the question it exists for rather than make the reader re-derive it —
// the same reasoning that duplicates the state blocks into an @LAT93 transition. It
// also stops being derivable the moment a partial prune is added.
size_t buildPruneRecord(char* out, size_t cap, int lane_n, const Prune& p,
                        uint32_t t_sec);

// Does this @LAT100 record body describe a prune of `lane`? Used to count a lane's
// generations back off flash, so the numbering survives reboots without state.
//
// ⚠ Matched by PARSING the field, not by `strstr("lane:97")`. `lane:9` is a prefix of
// `lane:94`, and this corpus has already been bitten twice by a needle that matched
// inside a longer token (`prev_stream:` in the @LAT90 reader, and the firmware dedup
// needle that needs its leading space). The digits are read and compared as a number,
// and the character after them must not be a digit.
bool pruneRecordNamesLane(const char* body, size_t len, uint8_t lane);

// The generation the NEXT prune of `lane` will close: existing markers naming it + 1.
// Kept here (rather than in the Arduino glue) so it is native-testable against a
// buffer of record bodies.
int nextGeneration(int markers_naming_lane);

}  // namespace lanegen
