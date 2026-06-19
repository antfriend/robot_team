// TtdbParse.h — pure TTDB record/edge parsing (no Arduino, no FS).
//
// Kept free of Arduino dependencies so the same parsing the firmware uses can
// be unit-tested natively (tests/test_toot.cpp). The streaming Ttdb class wraps
// these over LittleFS; Agent32 uses the structs for reasoning.
#pragma once
#include <stdint.h>
#include <stddef.h>

#ifndef TTDB_EDGE_TYPE_LEN
#define TTDB_EDGE_TYPE_LEN 24
#endif

// One indexed record (TTDB-RFC-0001 section 3 header line).
struct TtdbRecord {
  int16_t lat = 0;
  int16_t lon = 0;
  uint32_t file_offset = 0;
  uint32_t created = 0;
  uint32_t updated = 0;
};

// One typed edge: "<type>@LATxLONy" (mmpdb typed_edges.syntax).
struct TtdbEdge {
  char type[TTDB_EDGE_TYPE_LEN] = {0};
  int16_t target_lat = 0;
  int16_t target_lon = 0;
};

// Parse a record header line "@LATxLONy | created:.. | updated:.. | relates:..".
// Fills lat/lon/created/updated (leaves file_offset). Returns true if the line
// is a record header with parseable coordinates.
bool ttdbParseHeader(const char* line, TtdbRecord& out);

// Parse the `relates:` edge list from a header line. Returns edge count (<=max).
uint8_t ttdbParseEdges(const char* line, TtdbEdge* out, uint8_t max);

// Index of the record nearest (Euclidean on the lat/lon grid) to (lat,lon),
// or -1 if n <= 0.
int ttdbNearest(const TtdbRecord* recs, int n, int16_t lat, int16_t lon);
