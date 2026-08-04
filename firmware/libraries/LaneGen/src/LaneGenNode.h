// LaneGenNode.h — the Arduino-side glue for lane generations. One copy, six sketches,
// exactly like TimeStreamNode.h: the portable half (LaneGen.h) owns the record format
// and the field-matching trap, this half owns the order of operations against flash.
//
// Every sketch's `clearPerceptLanes()` calls THIS instead of `gDb.removePerceptLanes()`
// directly. That is the whole integration, and it is why it is one line per board:
// getting the order subtly wrong on one of six would be invisible, because a node that
// prunes without a marker looks exactly like a node that pruned correctly.
//
// THE ORDER, AND WHY IT IS THIS ORDER:
//
//   1. Count what is about to be destroyed (per lane, plus the highest LON in each) —
//      after the rewrite that information does not exist anywhere.
//   2. Count the existing markers, per lane, for the generation numbering. Reading
//      bodies is file I/O, but a prune is an operator action that happens once in a
//      session, not per frame — this is nowhere near the per-frame read that cost
//      767 ms/repaint in the edgesAt defect.
//   3. Check the marker lane has room for every marker this prune needs, BEFORE
//      touching the percept lanes. This is the "no prune without a marker" invariant:
//      if the boundary cannot be recorded, the boundary does not happen.
//   4. ONE rewrite for the whole range (`removePerceptLanes` already does this — four
//      sequential removeLane() calls would be four rewrites and four windows in which
//      the file moves under a concurrent reader, the stitched-pull hazard).
//   5. Append the markers.
#pragma once
#include <Arduino.h>
#include <TTDB.h>
#include <TimeStream.h>
#include "LaneGen.h"

#ifndef LANEGEN_MAX_LANE
// A prune is an operator action, not a periodic write: the first one in this fleet's
// life happened on 2026-08-03, and it took a finding to justify it. So this is a guard
// against a pathology — something pruning in a loop — not a routine ceiling like the
// percept lanes' 48. Same reasoning, and the same instruction, as TIMESTREAM_MAX_LANE:
// if it is ever reached, that IS the finding. Go and look; do not raise it.
//
// ⚠ What happens when it fills is DECIDED, unlike TIMESTREAM_MAX_LANE's still-open
// policy: the prune is REFUSED and says why. That is a real cost — a node whose marker
// lane is full stops being able to open its percept lanes, and will eventually go
// blind. It is the deliberate choice, because the alternative is a prune whose
// boundary nothing records, which is the defect this whole file exists to remove.
#define LANEGEN_MAX_LANE 32
#endif

#ifndef LANEGEN_BUF
#define LANEGEN_BUF 288
#endif

namespace lanegen {

// Count the @LAT100 markers naming `lane`. Also returns the total marker count in
// `total`, which is what the capacity check needs.
inline int countMarkers(Ttdb& db, uint8_t lane, int& total) {
  char body[320];
  int naming = 0;
  total = 0;
  for (int i = 0; i < db.recordCount(); ++i) {
    if (db.record(i).lat != LANE) continue;
    ++total;
    size_t off = 0, len = 0;
    if (!db.recordSpan(i, off, len)) continue;
    const size_t want = len < sizeof(body) ? len : sizeof(body);
    const size_t got = db.readBytes(off, (uint8_t*)body, want);
    if (pruneRecordNamesLane(body, got, lane)) ++naming;
  }
  return naming;
}

// Prune percept lanes exactly as CMD_CLEAR_PERCEPTS always did — `lane` is the wire
// byte, 0 meaning every percept lane — and write the generation boundary for each lane
// that actually held records. Returns true only if the prune AND every marker
// succeeded; the sketch ACKs on that, so a boundary that could not be written reaches
// the operator as a missing ACK rather than as silence.
inline bool prune(Ttdb& db, uint8_t lane, const timestream::Stamp& stamp,
                  uint32_t node_id, uint32_t t_sec) {
  const int16_t lo = lane ? (int16_t)lane : (int16_t)TTDB_PERCEPT_LANE_LO;
  const int16_t hi = lane ? (int16_t)lane : (int16_t)TTDB_PERCEPT_LANE_HI;
  // Mirror removePerceptLanes' refusal rather than clamping: a caller asking for
  // @LAT99 has a bug or bad intent, and this wrapper must not become the way around
  // the guard that keeps a prune from touching identity, attestations or sync logs.
  if (lo < TTDB_PERCEPT_LANE_LO || hi > TTDB_PERCEPT_LANE_HI) return false;

  const int span = TTDB_PERCEPT_LANE_HI - TTDB_PERCEPT_LANE_LO + 1;
  int held[8] = {0}, top[8];
  for (int i = 0; i < span; ++i) top[i] = -1;
  for (int i = 0; i < db.recordCount(); ++i) {
    const int16_t lat = db.record(i).lat;
    if (lat < lo || lat > hi) continue;
    const int k = lat - TTDB_PERCEPT_LANE_LO;
    ++held[k];
    if (db.record(i).lon > top[k]) top[k] = db.record(i).lon;
  }

  int needed = 0;
  for (int i = 0; i < span; ++i)
    if (held[i]) ++needed;
  // Idempotent: nothing to remove is not a prune, so it writes no boundary. This is
  // also what makes the CMD safe to retry after an ACK is lost to a slow rewrite.
  if (!needed) return true;

  int markers_total = 0;
  int gen[8] = {0};
  for (int i = 0; i < span; ++i) {
    if (!held[i]) continue;
    const uint8_t l = (uint8_t)(TTDB_PERCEPT_LANE_LO + i);
    int total = 0;
    gen[i] = nextGeneration(countMarkers(db, l, total));
    markers_total = total;   // same for every pass; read once, kept for the check
  }

  if (markers_total + needed > LANEGEN_MAX_LANE) {
    Serial.printf("[lanegen] @LAT%d lane FULL at %d, %d marker(s) needed — PRUNE "
                  "REFUSED. Something is pruning in a loop; go and look. Clearing a "
                  "lane without recording the boundary would silently re-point every "
                  "citation into it.\n",
                  (int)LANE, markers_total, needed);
    return false;
  }

  if (!db.removePerceptLanes(lane)) {
    Serial.println("[lanegen] removePerceptLanes FAILED — nothing pruned, no marker");
    return false;
  }

  bool ok = true;
  int lane_n = markers_total;
  char rec[LANEGEN_BUF];
  for (int i = 0; i < span; ++i) {
    if (!held[i]) continue;
    Prune p;
    p.lane = (uint8_t)(TTDB_PERCEPT_LANE_LO + i);
    p.gen = gen[i];
    p.removed = held[i];
    p.last_lon = top[i];
    p.node_id = node_id;
    p.stamp = stamp;
    const size_t m = buildPruneRecord(rec, sizeof(rec), lane_n, p, t_sec);
    if (!m || !db.appendRecord(rec, m)) {
      // The rewrite already happened, so this is the one path that degrades to the old
      // silent prune. Say so in the words a reader of the log will need.
      Serial.printf("[lanegen] ⚠ @LAT%u PRUNED BUT ITS BOUNDARY WAS NOT WRITTEN — "
                    "gen %d (%d records) is now unexplained, and citations into that "
                    "lane will resolve into the new generation.\n",
                    (unsigned)p.lane, p.gen, p.removed);
      ok = false;
      continue;
    }
    Serial.printf("[lanegen] @LAT%u gen %d closed: %d record(s), last @LAT%uLON%d "
                  "-> @LAT%dLON%d\n",
                  (unsigned)p.lane, p.gen, p.removed, (unsigned)p.lane, p.last_lon,
                  (int)LANE, lane_n);
    ++lane_n;
  }
  return ok;
}

// Prune the TIMELINE lane (@LAT90) and record the boundary — the one lane outside the
// percept block that can be pruned, and only through this call.
//
// WHY THIS EXISTS AT ALL. `TIMESTREAM_MAX_LANE 16` is a guard against a pathology, and
// on 2026-08-03 the Cardputer reached it — from spurious `STREAM-ORIGIN` records that
// the origin hold now prevents, but the 16 already on flash cannot be un-written. A
// full timeline lane cannot record the node's next timeline change, so its later
// records carry a stream id nothing on that node explains. That is the exact failure
// @LAT90 exists to prevent, arrived at from the other side.
//
// ⚠ WHY IT IS A SEPARATE CALL AND NOT A WIDENED `removePerceptLanes`. That guard
// refuses anything outside 94..97 so a prune can never reach identity (@LAT0), belief
// attestations (@LAT98) or the sync log (@LAT99), and its stated reason is that
// pruning a DIFFERENT lane than the one requested is worse than refusing. Nothing here
// weakens it: this call names @LAT90 explicitly, prunes exactly that, and 98/99 remain
// unreachable by any path.
//
// ⚠ WHAT IS LOST, STATED PLAINLY. The per-record offsets, the `from:` provenance and
// the adoption structure go. What is KEPT is the set of stream ids the generation
// explained, carried into the boundary as `**STREAMS-EXPLAINED**` — because an older
// record's `stream:0x..` stamp asks exactly one question ("was this node ever on that
// timeline?") and that line still answers it. A prune that dropped the ids would turn
// every earlier stamp on the node into an unanswerable id, which is the very thing
// being fixed.
inline bool pruneTimeline(Ttdb& db, const timestream::Stamp& stamp, uint32_t node_id,
                          uint32_t t_sec) {
  const int16_t lane = (int16_t)TIMESTREAM_LANE;
  uint32_t ids[TIMESTREAM_MAX_LANE];
  int n_ids = 0, held = 0, top = -1;
  char body[320];
  for (int i = 0; i < db.recordCount(); ++i) {
    if (db.record(i).lat != lane) continue;
    ++held;
    if (db.record(i).lon > top) top = db.record(i).lon;
    size_t off = 0, len = 0;
    if (!db.recordSpan(i, off, len)) continue;
    const size_t want = len < sizeof(body) ? len : sizeof(body);
    const size_t got = db.readBytes(off, (uint8_t*)body, want);
    // Reuse the timeline lane's own reader rather than a second parser: it already
    // knows that the needle carries a leading space, so a REMAP's `prev_stream:` (the
    // stream the node LEFT) cannot be mistaken for one it was on.
    uint32_t id = 0;
    if (!timestream::recordStreamId(body, got, id) || !id) continue;
    bool seen = false;
    for (int k = 0; k < n_ids; ++k)
      if (ids[k] == id) { seen = true; break; }
    if (!seen && n_ids < (int)(sizeof(ids) / sizeof(ids[0]))) ids[n_ids++] = id;
  }
  if (!held) return true;                       // idempotent, same as a percept prune

  int markers_total = 0;
  const int gen = nextGeneration(countMarkers(db, (uint8_t)lane, markers_total));
  if (markers_total + 1 > LANEGEN_MAX_LANE) {
    Serial.printf("[lanegen] @LAT%d lane FULL — cannot record a @LAT%d boundary, so "
                  "the timeline lane is NOT pruned\n", (int)LANE, (int)lane);
    return false;
  }

  Prune p;
  p.lane = (uint8_t)lane;
  p.gen = gen;
  p.removed = held;
  p.last_lon = top;
  p.node_id = node_id;
  p.stamp = stamp;
  // Bigger than LANEGEN_BUF: this record carries the id list as well.
  char rec[TIMESTREAM_MAX_LANE * 12 + 320];
  const size_t m = buildPruneRecord(rec, sizeof(rec), markers_total, p, t_sec,
                                    ids, n_ids);
  if (!m) {
    Serial.println("[lanegen] timeline boundary would not fit — NOT pruned");
    return false;
  }
  if (!db.removeLane(lane)) {
    Serial.println("[lanegen] removeLane(timeline) FAILED — nothing pruned");
    return false;
  }
  if (!db.appendRecord(rec, m)) {
    Serial.printf("[lanegen] ⚠ @LAT%d PRUNED BUT ITS BOUNDARY WAS NOT WRITTEN — %d "
                  "stream id(s) are now unexplained on this node\n", (int)lane, n_ids);
    return false;
  }
  Serial.printf("[lanegen] @LAT%d gen %d closed: %d record(s), %d stream id(s) "
                "carried forward -> @LAT%dLON%d\n",
                (int)lane, gen, held, n_ids, (int)LANE, markers_total);
  return true;
}

}  // namespace lanegen
