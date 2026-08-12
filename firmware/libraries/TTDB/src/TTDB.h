// TTDB.h — streaming Toot-Toot Database reader for ESP32 (A32-RFC-0002).
//
// Two-pass: begin() scans the file once for record-header offsets, then parses
// each header into a coordinate index (TtdbRecord). Record bodies and edges are
// read on demand by seeking. The whole file is never held in RAM. The raw byte
// accessors (fileSize/readBytes) back the network share (TtdbShare); the
// coordinate index + edgesAt()/nearest() back Agent32 reasoning.
#pragma once
#include <Arduino.h>
#include <FS.h>
#include "TtdbParse.h"

// ⚠ 256 -> 288 on 2026-08-09, when the Cardputer's file was found legitimately AT the
// old cap: its lane caps sum to ~256 (4x48 percepts + 24 outcomes + 16 timeline + the
// fleet map + beliefs), so the new @LAT101 field lane had no index room at all — its
// records were appended past the index and destroyed by the next lane rewrite. 288 is
// the old budget plus the field lane's 8 and margin; the cost is +512 B of .bss per
// OPEN FILE (16 B/entry), x3 files on a handheld. Do not raise this for a lane that
// grows with uptime — that pressure is the signal the lane's design is wrong, and
// appendRecord now REFUSES at the cap rather than half-succeeding.
#ifndef TTDB_MAX_RECORDS
#define TTDB_MAX_RECORDS 288
#endif

// Slots remaining at which a node should start SAYING it is running out. Not a limit —
// the limit is TTDB_MAX_RECORDS — but a node that announces only saturation announces it
// too late to do anything about. 16 is one field-lane's worth (@LAT101 caps at 8, doubled
// for margin), so the warning fires while a whole lane could still be written.
#define TTDB_INDEX_WARN_SLOTS 16

// The percept lanes — semantic-positioning evidence a node writes about its own
// umwelt, and the only records CMD_CLEAR_PERCEPTS may drop: @LAT94 acoustic,
// @LAT95 motion, @LAT96 entity (WiFi BSSIDs), @LAT97 link (per-peer RSSI).
#define TTDB_PERCEPT_LANE_LO 94
#define TTDB_PERCEPT_LANE_HI 97

class Ttdb {
 public:
  // Mount must already be done by the caller (LittleFS.begin / SD.begin).
  bool begin(fs::FS& fs, const char* path);

  size_t fileSize() const { return file_size_; }
  int recordCount() const { return record_count_; }
  const char* path() const { return path_; }
  const TtdbRecord& record(int i) const { return records_[i]; }

  // ⚠ HOW MANY RECORDS THE FILE HAS, vs how many the INDEX HOLDS. These differ, and
  // until 2026-08-11 nothing could tell you so: begin()'s pass-1 scan simply stopped
  // recording offsets at the cap and returned true. A node whose file had outgrown its
  // index looked perfectly healthy — same as `appendRecord`'s pre-2026-08-09 defect,
  // one layer down, and with the same consequence (removeLaneRange copies indexed spans
  // only). `recordCount()` is what is VISIBLE; `headersSeen()` is what EXISTS.
  uint32_t headersSeen() const { return headers_seen_; }
  bool indexSaturated() const { return headers_seen_ > (uint32_t)record_count_; }
  uint32_t droppedRecords() const {
    return headers_seen_ - (uint32_t)record_count_;
  }
  // Records that may still be appended before EVERY lane stops accepting them. This is
  // a whole-FILE budget shared by all lanes, so a lane with room in its own cap can
  // still be refused — which is why it is worth printing next to the lane counts.
  int indexHeadroom() const { return TTDB_MAX_RECORDS - record_count_; }

  // Raw byte window — the primitive behind whole-file network sharing.
  size_t readBytes(size_t offset, uint8_t* buf, size_t len);

  // Append a complete, well-formed record block (separator + header line + body,
  // per TTDB-RFC-0001) to the file and index it so it is immediately visible to
  // readBytes()/recordCount()/nearest() and to the next network pull. The first
  // runtime writer of a node's TTDB (TTN-RFC-0008 sync log). Returns false if the
  // file can't be opened/written or the re-index fails.
  //
  // Indexes the new record INCREMENTALLY — it does not re-read the file. Nodes whose
  // TTDB grows at runtime (the Cardputer appends four percept lanes a minute) append
  // often enough that an O(file) re-index per append dominates their worst loop pass,
  // and the toot link is serviced once per pass. Falls back to a full begin() if the
  // appended block is anything other than the expected one-or-more record headers.
  bool appendRecord(const char* text, size_t len);

  // Rewrite the TTDB without any record at latitude `lat` (percept-lane prune,
  // semantic positioning SP1 — CMD_CLEAR_PERCEPTS). Idempotent (no such records
  // -> true, no rewrite); re-indexes on success. This is a flash rewrite: call
  // from loop(), never a radio recv callback.
  bool removeLane(int16_t lat);

  // Same, for every latitude in [lo, hi] — in ONE rewrite. Prefer this over
  // calling removeLane() per lane: each call rewrites the whole file, so four
  // sequential calls cost four rewrites AND four windows in which the file moves
  // under a concurrent reader (the stitched-pull hazard, companion.md §6).
  bool removeLaneRange(int16_t lo, int16_t hi);

  // CMD_CLEAR_PERCEPTS backing call. `lane` is the wire byte: 0 = every percept
  // lane, else exactly that one. Returns false for any lane outside the percept
  // range, so a malformed or hostile CMD can never drop @LAT0 identity, @LAT98
  // belief attestations or @LAT99 sync logs — the prune is not a general delete.
  bool removePerceptLanes(uint8_t lane);

  // Byte span of record `index` (header line through just before the next
  // record or EOF).
  bool recordSpan(int index, size_t& offset, size_t& length) const;

  // Index of the record nearest (lat,lon) on the grid, or -1 if empty.
  int nearest(int16_t lat, int16_t lon) const {
    return ttdbNearest(records_, record_count_, lat, lon);
  }

  // Parse the typed edges of record `index`. Returns edge count (<= max).
  uint8_t edgesAt(int index, TtdbEdge* out, uint8_t max);

 private:
  size_t readLine(size_t offset, char* buf, size_t cap);
  // Same, through a handle the caller already holds. readLine() opens and closes the
  // file per call, so any loop reading more than one line must use this instead.
  static size_t readLineFrom(File& f, size_t offset, char* buf, size_t cap);

  fs::FS* fs_ = nullptr;
  char path_[64] = {0};
  size_t file_size_ = 0;
  int record_count_ = 0;
  uint32_t headers_seen_ = 0;
  // Offset of the FIRST header the index could not hold, or file_size_ when the whole
  // file fits. It exists so the unindexed tail is a SPAN WE CAN NAME: without it the
  // last indexed record's span ran to EOF and swallowed every record past the cap, so
  // pruning a lane that happened to own record #288 deleted all of them.
  size_t tail_offset_ = 0;
  TtdbRecord records_[TTDB_MAX_RECORDS];
};
