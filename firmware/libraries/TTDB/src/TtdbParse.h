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
//
// ⚠ THIS STRUCT DELIBERATELY DOES **NOT** CARRY A `sid`, AND THAT IS A MEASURED
// DECISION, NOT AN OVERSIGHT. `Ttdb` holds `TtdbRecord records_[TTDB_MAX_RECORDS]` =
// 256 of these, and the Cardputer holds THREE `Ttdb` instances (the mesh globe, the RFC
// corpus, the feelings landscape). Adding `uint32_t sid` + a flag takes the struct from
// 16 to 24 bytes with padding: +2 KB per instance, **+6 KB on a node whose `maxalloc`
// reads 7-8 KB** and whose memory ceiling is still unexplained.
//
// TTDB-RFC-0010 section 7.3 priced stable ids at +13 B per record ON FLASH and said
// nothing about the in-memory index, where on this fleet the cost is 3x worse. A reader
// that wants a record's sid calls `ttdbHeaderSid()` on the header line it already has.
struct TtdbRecord {
  int16_t lat = 0;
  int16_t lon = 0;
  uint32_t file_offset = 0;
  uint32_t created = 0;
  uint32_t updated = 0;
};

// One typed edge: "<type>@LATxLONy" or "<type>@LATxLONy#sid" (mmpdb typed_edges.syntax,
// extended by TTDB-RFC-0010 section 4.3).
//
// This one MAY grow: edges are parsed into short stack arrays (`TtdbEdge es[4]`) and
// copied into each sketch's own slimmer cache, so there is no 256-element index of them.
// 32 bytes of stack in two functions, against 6 KB of .bss for the alternative above.
struct TtdbEdge {
  char type[TTDB_EDGE_TYPE_LEN] = {0};
  int16_t target_lat = 0;
  int16_t target_lon = 0;
  // The `#sid` a citation MAY carry. `has_target_sid` is false for every citation written
  // before RFC-0010 and for every one written after that chooses not to carry one --
  // ⚠ BOTH FORMS ARE PERMANENTLY LIVE (section 4.3), the same rule that keeps
  // `synced:` parsing beside `stream:`. A reader requiring a sid would silently fold every
  // pre-adoption citation in the corpus.
  uint32_t target_sid = 0;
  bool     has_target_sid = false;
};

// Parse a record header line "@LATxLONy | created:.. | updated:.. | relates:..".
// Fills lat/lon/created/updated (leaves file_offset). Returns true if the line
// is a record header with parseable coordinates.
bool ttdbParseHeader(const char* line, TtdbRecord& out);

// Parse the `relates:` edge list from a header line. Returns edge count (<=max).
uint8_t ttdbParseEdges(const char* line, TtdbEdge* out, uint8_t max);

// The `sid:` a record header MAY carry (TTDB-RFC-0010 §4.2). Returns false and leaves
// `out` untouched when absent or malformed — which is the case for every record written
// before adoption, so "false" is the ordinary answer and not an error.
//
// A free function rather than a field on TtdbRecord: see the warning on that struct. The
// caller already holds the header line, so this costs nothing to keep.
bool ttdbHeaderSid(const char* line, uint32_t& out);

// Does a citation still name the record it was written against?
//
// ⚠ This is the capability stable ids exist to buy, and the reason it matters here is
// that the alternative is expensive: without a sid, deciding whether `derived_from@LAT97LON1`
// still points at what its author meant needs the `@LAT100` boundary lane, the citing
// record's timestamp, and both being on the same stream — and it answers UNKNOWN whenever
// they are not. With a sid it is one comparison, by a reader holding nothing but the file.
enum TtdbCitation : uint8_t {
  TTDB_CITATION_UNVERIFIABLE = 0,  // no sid on the edge, or none on the target
  TTDB_CITATION_FRESH,             // both present and equal
  TTDB_CITATION_STALE,             // both present and DIFFERENT: the slot was reclaimed
};
// `target_header` is the header line of the record now at the edge's coordinate.
TtdbCitation ttdbResolveCitation(const TtdbEdge& e, const char* target_header);

// Index of the record nearest (Euclidean on the lat/lon grid) to (lat,lon),
// or -1 if n <= 0.
int ttdbNearest(const TtdbRecord* recs, int n, int16_t lat, int16_t lon);
