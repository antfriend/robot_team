#include "TtdbParse.h"
#include <stdlib.h>
#include <string.h>

// Parse the int16 immediately following the first occurrence of `key` in `s`.
// Returns 0 if the key is absent.
static int16_t int_after(const char* s, const char* key) {
  const char* p = strstr(s, key);
  if (!p) return 0;
  return (int16_t)strtol(p + strlen(key), nullptr, 10);
}

static uint32_t u32_after(const char* s, const char* key) {
  const char* p = strstr(s, key);
  if (!p) return 0;
  return (uint32_t)strtoul(p + strlen(key), nullptr, 10);
}


// Parse exactly 8 lowercase hex digits at `p`, not running past `end`. Mirrors
// sid::parse: uppercase is REFUSED rather than normalised, because a sid is a hash of a
// canonical preimage and tolerating a second spelling would let two files disagree about
// a record's id while both "parsing fine".
static bool parse_hex8(const char* p, const char* end, uint32_t& out) {
  if (!p || (end && end - p < 8)) return false;
  uint32_t v = 0;
  for (int i = 0; i < 8; ++i) {
    const char c = p[i];
    uint8_t d;
    if (c >= '0' && c <= '9')      d = (uint8_t)(c - '0');
    else if (c >= 'a' && c <= 'f') d = (uint8_t)(c - 'a' + 10);
    else return false;
    v = (v << 4) | d;
  }
  out = v;
  return true;
}

bool ttdbParseHeader(const char* line, TtdbRecord& out) {
  if (!line || line[0] != '@') return false;
  if (!strstr(line, "LAT") || !strstr(line, "LON")) return false;
  // The record id is at the start, so the first LAT/LON are the record's own
  // coordinates (edge tokens with LAT/LON come later in the line).
  out.lat = int_after(line, "LAT");
  out.lon = int_after(line, "LON");
  out.created = u32_after(line, "created:");
  out.updated = u32_after(line, "updated:");
  return true;
}

uint8_t ttdbParseEdges(const char* line, TtdbEdge* out, uint8_t max) {
  const char* rel = strstr(line, "relates:");
  if (!rel) return 0;
  const char* p = rel + 8;  // strlen("relates:")
  uint8_t count = 0;

  while (*p && *p != '\n' && *p != '\r' && count < max) {
    while (*p == ' ') ++p;
    const char* end = p;
    while (*end && *end != ',' && *end != '\n' && *end != '\r') ++end;

    // Locate the '@' that separates the type from the coordinate.
    const char* at = p;
    while (at < end && *at != '@') ++at;
    if (at < end) {
      size_t tlen = (size_t)(at - p);
      while (tlen > 0 && p[tlen - 1] == ' ') --tlen;  // trim trailing space
      if (tlen >= TTDB_EDGE_TYPE_LEN) tlen = TTDB_EDGE_TYPE_LEN - 1;
      memcpy(out[count].type, p, tlen);
      out[count].type[tlen] = '\0';
      // The first LAT/LON at or after '@' belong to this edge token.
      out[count].target_lat = int_after(at, "LAT");
      out[count].target_lon = int_after(at, "LON");
      // The optional `#sid` (TTDB-RFC-0010 section 4.3), bounded to THIS edge token --
      // `end` is the comma or line end, so a later edge's sid can never be read as this
      // one's. Absent is the ordinary case and leaves the pair (0, false).
      out[count].target_sid = 0;
      out[count].has_target_sid = false;
      for (const char* h = at; h < end; ++h) {
        if (*h != '#') continue;
        uint32_t v = 0;
        if (parse_hex8(h + 1, end, v)) {
          out[count].target_sid = v;
          out[count].has_target_sid = true;
        }
        break;   // one '#' per token; a second is malformed, not a second id
      }
      ++count;
    }

    p = end;
    if (*p == ',') ++p;
  }
  return count;
}

int ttdbNearest(const TtdbRecord* recs, int n, int16_t lat, int16_t lon) {
  if (n <= 0) return -1;
  int best = -1;
  long best_d = 0;
  for (int i = 0; i < n; ++i) {
    long dl = (long)recs[i].lat - lat;
    long dn = (long)recs[i].lon - lon;
    long d = dl * dl + dn * dn;
    if (best < 0 || d < best_d) {
      best = i;
      best_d = d;
    }
  }
  return best;
}

// Span of the record's header line — the first line beginning '@' — as [start, end).
// Deliberately a local copy of the scan `sid::stampEvent` does rather than a shared one:
// TTDB and Sid are separate libraries and this is ten lines, so the alternative is a
// dependency edge between them for less code than the edge costs. ⚠ If one of them changes
// what counts as a header line, the other must too; tests/test_citation.cpp and
// tests/test_sid.cpp both pin it, which is what keeps them honest.
static bool headerLineSpan(const char* rec, size_t len, const char*& start,
                           const char*& end) {
  size_t i = 0;
  while (i < len) {
    if (rec[i] == '@') {
      start = rec + i;
      while (i < len && rec[i] != '\n') ++i;
      end = rec + i;
      return true;
    }
    while (i < len && rec[i] != '\n') ++i;
    if (i < len) ++i;
  }
  return false;
}

bool ttdbHeaderSid(const char* line, uint32_t& out) {
  if (!line) return false;
  // ⚠ THE BUFFER DOES NOT NECESSARILY START AT THE HEADER LINE, and assuming it did was a
  // real defect caught by the first cross-component test: every record this fleet renders
  // begins "\n---\n\n@LAT..." (the separator is part of what `appendRecord` is given), so
  // `strchr(line, '\n')` found the newline at index 0 and the function reported "no sid"
  // for a record that carried one. The writer and the reader disagreed, silently, which is
  // the one failure mode a stable id exists to prevent.
  //
  // So locate the header line the way bodyOffset() does — the first line beginning '@' —
  // and search only within it. A body may legitimately contain the text `sid:` (a @LAT100
  // boundary quoting a pruned record's id is the real case) and reading that as the
  // record's own identity is the `prev_stream:`-inside-`stream:` collision again.
  const size_t len = strlen(line);
  const char* start = line;
  const char* end = line + len;
  if (!headerLineSpan(line, len, start, end)) return false;
  for (const char* p = start; p + 4 <= end; ++p) {
    if (p[0] != 's' || p[1] != 'i' || p[2] != 'd' || p[3] != ':') continue;
    // ⚠ Must be a field, not a suffix: `prev_sid:` and `carried_sid:` must not match. A
    // word boundary does NOT help — it matches inside them — so the character before is
    // required to be a delimiter, exactly as companion.py's HEADER_SID_RE does.
    if (p > start && p[-1] != ' ' && p[-1] != '|') continue;
    return parse_hex8(p + 4, end, out);
  }
  return false;
}

TtdbCitation ttdbResolveCitation(const TtdbEdge& e, const char* target_header) {
  // ⚠ Both halves must be present. A citation with no sid is UNVERIFIABLE, never STALE:
  // every citation written before adoption has none, and reporting the corpus as broken
  // would be worse than saying nothing about it. Likewise a target that carries no sid.
  if (!e.has_target_sid) return TTDB_CITATION_UNVERIFIABLE;
  uint32_t now = 0;
  if (!ttdbHeaderSid(target_header, now)) return TTDB_CITATION_UNVERIFIABLE;
  return (now == e.target_sid) ? TTDB_CITATION_FRESH : TTDB_CITATION_STALE;
}
