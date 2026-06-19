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
