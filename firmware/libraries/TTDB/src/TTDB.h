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

#ifndef TTDB_MAX_RECORDS
#define TTDB_MAX_RECORDS 256
#endif

class Ttdb {
 public:
  // Mount must already be done by the caller (LittleFS.begin / SD.begin).
  bool begin(fs::FS& fs, const char* path);

  size_t fileSize() const { return file_size_; }
  int recordCount() const { return record_count_; }
  const char* path() const { return path_; }
  const TtdbRecord& record(int i) const { return records_[i]; }

  // Raw byte window — the primitive behind whole-file network sharing.
  size_t readBytes(size_t offset, uint8_t* buf, size_t len);

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

  fs::FS* fs_ = nullptr;
  char path_[64] = {0};
  size_t file_size_ = 0;
  int record_count_ = 0;
  TtdbRecord records_[TTDB_MAX_RECORDS];
};
