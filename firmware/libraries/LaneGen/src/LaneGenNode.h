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
#include <LittleFS.h>      // free-space figure in the rewrite-failure report
#include <Preferences.h>
#include <TTDB.h>
#include <TimeStream.h>
#include "LaneGen.h"

// ---------------------------------------------------------------------------------
// A PRUNE THAT COULD NOT RUN NOW, SCHEDULED FOR THE NEXT BOOT (2026-08-13).
//
// 🔬 WHY THIS EXISTS, measured rather than argued. `Ttdb::removeLaneRange` rewrites the
// whole file, and the filesystem allocates while it does. On the Cardputer — BLE + WiFi +
// display + three globes — the largest contiguous block is ~7 KB and the rewrite fails at
// its `read` or `write` step. It does not fail for want of a bigger buffer of ours (the
// copy uses 128 B of stack): it dies inside the filesystem, at whichever call next needs
// memory. What settles it is WHEN:
//
//   same node, same 120 KB file, same code
//     during setup(), radios not yet up   maxalloc 102 KB   -> rewrite SUCCEEDS
//     once BLE + WiFi + display are up    maxalloc   7 KB   -> rewrite FAILS
//
// Verified end to end on 2026-08-13: three lanes (@LAT96, @LAT97, @LAT94) each refused
// in place and each completed at the next boot, TTDB 120307 -> 43143 B.
//
// ⚠ ONE REPORTED FAILURE IN THAT INVESTIGATION WAS THE INSTRUMENT'S OWN, and the note is
// here so the next reader does not over-trust the step name. The post-copy size check was
// first written to report `TTDB_RW_WRITE`, so a rewrite whose COPY HAD COMPLETED reported
// "failed at step 'write'" — indistinguishable from a real mid-copy failure, and it broke
// the boot attempt too. It was caught by arithmetic, not by inspection: the byte counter
// read exactly the number of bytes that should survive. VERIFY now has its own code.
//
// ⚠ STORED IN NVS, NOT ON THE FILESYSTEM, and that is the whole point: the node is in this
// state precisely because filesystem writes are failing. A `/prune.pending` marker file
// would be a smaller instance of the operation that is already broken. NVS is a separate
// subsystem with its own pool.
//
// 📎 NO AUTOMATIC REBOOT. `companion.py` resets the board on nearly every call, so the
// operator's natural next step — a `pull` to verify — IS the reboot that runs it. Forcing
// one would cost the pulse era, mesh membership and 5–27 s of rejoin, unasked, possibly
// mid-experiment.
namespace lanegen {

// A prune has THREE outcomes, not two: done, refused, or durably scheduled for the next
// boot. Collapsing the third into either of the others is a lie in one direction or the
// other — ACCEPTED claims work that has not happened, silence denies work that will.
//
// ⚠ Lives HERE rather than in a sketch because a `.ino` cannot own a type used in a
// function signature: arduino-cli inserts its auto-generated prototypes above anything
// the sketch declares, so the enum is not in scope at the prototype. (Found the direct
// way: `error: 'ClearResult' does not name a type`.) It belongs in the library regardless
// — it is the prune's result, and every sketch that prunes needs the same three answers.
enum PruneResult : uint8_t { PRUNE_FAILED = 0, PRUNE_OK, PRUNE_DEFERRED };

// `lane` is the wire byte, where **0 legitimately means "every percept lane"** — so the
// stored value is lane+1 and 0 is the "nothing scheduled" sentinel. Using 0 for "none"
// would have made the broadest prune the one that could never be scheduled.
//
// ⚠ ONE SLOT. Scheduling a second lane before the first has run OVERWRITES it, so two
// deferrals with no reboot between them lose the earlier one. Left as one slot on
// purpose: in practice every `companion.py` call resets the board, so a second command
// has already run the first schedule by the time it arrives (observed 2026-08-13 — lanes
// 97 and 94 were deferred in turn and both completed). If that ever stops being true, the
// fix is a lane BITMASK here, not a queue.
inline void setPendingPrune(uint8_t lane) {
  Preferences p;
  if (!p.begin("lanegen", false)) return;
  p.putUChar("prune", (uint8_t)(lane + 1));
  p.end();
}

// Read AND CLEAR, in that order.
// ⚠ THE CLEAR HAPPENS BEFORE THE CALLER ATTEMPTS THE PRUNE, DELIBERATELY. If a scheduled
// prune also fails at boot, a flag that survived the attempt would make the node reboot
// into the same failure forever. One attempt per schedule; a second failure is the
// operator's to see, not the node's to loop on.
inline bool takePendingPrune(uint8_t& lane) {
  Preferences p;
  if (!p.begin("lanegen", false)) return false;
  const uint8_t v = p.getUChar("prune", 0);
  if (v) p.remove("prune");
  p.end();
  if (!v) return false;
  lane = (uint8_t)(v - 1);
  return true;
}

}  // namespace lanegen

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

#ifndef LANEGEN_OUTCOME_LANE
// The Learning-from-Action outcome lane, @LAT92. Named here rather than included from
// PerceptLearn.h so this library keeps its one dependency direction — the sketch, which
// has both, asserts the two agree at compile time. See pruneOutcomes() below.
#define LANEGEN_OUTCOME_LANE 92
#endif
#ifndef LANEGEN_CARRIED_BUF
// Room for the caller-built `carried` block a pruneOutcomes() boundary carries.
//
// ⚠ MEASURED, AND THE FIRST NUMBER HERE WAS WRONG. It was set to 1024 from an eyeball
// estimate of "~100 B a line"; the real @LAT92 block is a 120 B tally line plus 8 x
// 122 B belief lines = **1124 B**, so the very first prune on hardware refused itself
// and cost a measurement window. The block is now rendered by
// `perceptlearn::Reconciler::buildBoundary`, whose own PERCEPTLEARN_BOUNDARY_BUF is
// pinned by a native test against the real 8-belief ceiling — this constant only has to
// be at least that, and 1536 matches it exactly.
//
// Both the caller's builder and buildPruneRecord write NOTHING rather than truncating,
// so an undersized buffer refuses the prune instead of writing a boundary that
// understates the evidence it stands in for. That behaviour was correct throughout; the
// arithmetic in front of it was not.
#define LANEGEN_CARRIED_BUF 1536
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
    // ⚠ NAME THE STEP AND THE TWO NUMBERS THAT DISCRIMINATE. "FAILED" on its own cost a
    // whole session on 2026-08-13: the Cardputer refused every lane rewrite while V4-A ran
    // the identical code and succeeded, and nothing on the node or the wire could say
    // which of the seven failure points it was. Heap is `maxalloc`, NOT free heap
    // ([[maxalloc-not-free-heap]]) — a fragmented node has plenty of the second and none
    // of the first, and a filesystem open needs the first.
    Serial.printf("[lanegen] removePerceptLanes FAILED at step '%s' after %u of %u B "
                  "copied — nothing pruned, no marker. maxalloc %u B, %d records, FS %u B "
                  "free.\n",
                  db.lastRewriteErrName(), (unsigned)db.lastRewriteBytes(),
                  (unsigned)db.fileSize(), (unsigned)ESP.getMaxAllocHeap(),
                  db.recordCount(),
                  (unsigned)(LittleFS.totalBytes() - LittleFS.usedBytes()));
    if (db.lastRewriteErr() == TTDB_RW_RENAME)
      Serial.printf("[lanegen] 🛑 THE TTDB IS IN %s.tmp — THIS NODE WILL BOOT EMPTY. "
                    "Rename it back before rebooting.\n", db.path());
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

// Prune the OUTCOME lane (@LAT92) and record the boundary — the second lane outside the
// percept block that can be pruned, and only through this call.
//
// WHY THIS EXISTS. `PERCEPTLEARN_MAX_LANE 24` was reached on the Cardputer, and a full
// outcome lane means the learning loop "is still predicting but no longer testifying" —
// it keeps arming expectations and scoring them, and writes none of it down. Unlike a
// percept lane there was no way out: `removePerceptLanes` refuses anything outside
// 94..97, so on 2026-08-04 the run-length work that this lane exists to exercise had no
// hardware path at all. Exactly the shape of @LAT90's 16/16, and answered the same way.
//
// ⚠ WHY IT IS A SEPARATE CALL AND NOT A WIDENED GUARD — the same reason pruneTimeline()
// is. That guard's stated purpose is that identity (@LAT0), belief attestations (@LAT98)
// and the sync log (@LAT99) are unreachable by ANY path, and pruning a different lane
// than the one requested is worse than refusing. Nothing here weakens it: this names
// @LAT92 explicitly and prunes exactly that.
//
// ⚠ WHAT IS LOST, AND IT IS MORE THAN AN ORDINAL. `Reconciler` is a PURE FUNCTION of
// this lane, recomputed from baseline every cycle — which is what makes a belief
// auditable rather than trusted, and which means **pruning the lane resets every @LAT91
// belief toward baseline**. PerceptLearn.h already states that as a property ("the
// belief is exactly as strong as the evidence still retained"), so the prune does not
// break an invariant; it exercises one. But a belief silently falling from 106 back to
// 128 with nothing saying why would be indistinguishable from a node that had never
// learned anything.
//
// So `carried` — built by the caller, which is the only place that can fold the lane —
// records the tally and the conclusions at the boundary. An older reader's question is
// "how much evidence stood behind the last belief, and what did it say?", and that block
// still answers it. What is genuinely gone is the per-window testimony: the individual
// verdicts, the predicted/observed medians, and the ability to RE-derive conf rather
// than read it. That is the stated cost, and it is why this is a repair, not routine
// maintenance.
inline bool pruneOutcomes(Ttdb& db, const timestream::Stamp& stamp, uint32_t node_id,
                          uint32_t t_sec, const char* carried) {
  const int16_t lane = (int16_t)LANEGEN_OUTCOME_LANE;
  int held = 0, top = -1;
  for (int i = 0; i < db.recordCount(); ++i) {
    if (db.record(i).lat != lane) continue;
    ++held;
    if (db.record(i).lon > top) top = db.record(i).lon;
  }
  if (!held) return true;                       // idempotent, same as a percept prune

  int markers_total = 0;
  const int gen = nextGeneration(countMarkers(db, (uint8_t)lane, markers_total));
  if (markers_total + 1 > LANEGEN_MAX_LANE) {
    Serial.printf("[lanegen] @LAT%d lane FULL — cannot record a @LAT%d boundary, so "
                  "the outcome lane is NOT pruned\n", (int)LANE, (int)lane);
    return false;
  }

  Prune p;
  p.lane = (uint8_t)lane;
  p.gen = gen;
  p.removed = held;
  p.last_lon = top;
  p.node_id = node_id;
  p.stamp = stamp;
  // Bigger than LANEGEN_BUF: this record carries the tally block as well. `static`
  // because 1856 B is too much to put on the loop stack next to the caller's own
  // PERCEPTLEARN_BOUNDARY_BUF buffer — and a prune is single-threaded by construction
  // (the radio path defers it to loop(), the serial path already runs there).
  static char rec[LANEGEN_CARRIED_BUF + 320];
  const size_t m = buildPruneRecord(rec, sizeof(rec), markers_total, p, t_sec, 0, 0,
                                    carried);
  if (!m) {
    Serial.println("[lanegen] outcome boundary would not fit — NOT pruned");
    return false;
  }
  // ⚠ RENDER BEFORE REMOVING, like pruneTimeline. The boundary is built from the state
  // the prune is about to destroy, and a rewrite that succeeded followed by a render
  // that did not would leave the lane gone and unexplained.
  if (!db.removeLane(lane)) {
    Serial.println("[lanegen] removeLane(outcome) FAILED — nothing pruned");
    return false;
  }
  if (!db.appendRecord(rec, m)) {
    Serial.printf("[lanegen] ⚠ @LAT%d PRUNED BUT ITS BOUNDARY WAS NOT WRITTEN — the "
                  "beliefs will fall back to baseline with nothing saying why\n",
                  (int)lane);
    return false;
  }
  Serial.printf("[lanegen] @LAT%d gen %d closed: %d record(s), tally carried "
                "-> @LAT%dLON%d\n", (int)lane, gen, held, (int)LANE, markers_total);
  return true;
}

}  // namespace lanegen
