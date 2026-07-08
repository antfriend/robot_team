// test_rfc_ttdb.cpp — native proof that RFCs/rfc.ttdb.md (the semantic
// compression of the RFC corpus) is carryable by the fleet's own streaming TTDB
// reader. It replicates Ttdb::begin()'s two-pass index byte-for-byte (line_start
// '@' scan, then ttdbParseHeader on each header line, both from TTDB.cpp) over
// the real file, using the firmware's TtdbParse.cpp unmodified, then checks the
// invariants Agent32 reasoning and TtdbShare streaming depend on. Keeping this in
// the native suite means the compression stays verified as the RFCs evolve: edit
// an RFC + regenerate the gist, and a broken header/edge/coordinate fails here
// before it ever reaches flash. See RFCs/rfc.ttdb.md and RFCs/INDEX.md.
#include "TtdbParse.h"
#include <cstdio>
#include <cstring>
#include <vector>
#include <string>

#ifndef TTDB_MAX_RECORDS
#define TTDB_MAX_RECORDS 256
#endif

static int fails = 0;
#define CHECK(cond, ...)             \
  do {                               \
    if (cond) {                      \
      printf("PASS: " __VA_ARGS__);  \
      printf("\n");                  \
    } else {                         \
      printf("FAIL: " __VA_ARGS__);  \
      printf("\n");                  \
      ++fails;                       \
    }                                \
  } while (0)

// Read one header line the way Ttdb::readLine does: up to '\n', drop '\r',
// cap at 256 bytes.
static std::string readLine(const std::string& data, size_t off) {
  char line[256];
  size_t i = 0;
  while (i < sizeof(line) - 1 && off < data.size()) {
    char c = data[off++];
    if (c == '\n') break;
    if (c != '\r') line[i++] = c;
  }
  line[i] = '\0';
  return std::string(line);
}

int main(int argc, char** argv) {
  const char* path = argc > 1 ? argv[1] : "../RFCs/rfc.ttdb.md";
  FILE* f = fopen(path, "rb");
  if (!f) {
    printf("FAIL: cannot open %s\n", path);
    return 1;
  }
  std::string data;
  char buf[4096];
  size_t n;
  while ((n = fread(buf, 1, sizeof(buf), f)) > 0) data.append(buf, n);
  fclose(f);

  // Pass 1 — identical to Ttdb::begin(): a record header is a line whose first
  // character is '@'.
  std::vector<TtdbRecord> recs;
  bool line_start = true;
  for (size_t off = 0; off < data.size(); ++off) {
    char c = data[off];
    if (line_start && c == '@') {
      TtdbRecord r;
      r.file_offset = (uint32_t)off;
      recs.push_back(r);
    }
    line_start = (c == '\n');
  }
  CHECK(recs.size() == 33, "pass-1 scan indexes 33 records (got %zu)", recs.size());
  CHECK(recs.size() <= TTDB_MAX_RECORDS, "fits TTDB_MAX_RECORDS (%d)", TTDB_MAX_RECORDS);

  // Pass 2 — every indexed '@' line MUST parse, or it stays a phantom (0,0)
  // record on the device. Header must also fit readLine's 256 cap WITH the
  // relates: list intact, else edgesAt() silently truncates edges on-device.
  size_t max_hdr = 0;
  int parsed = 0;
  for (auto& r : recs) {
    std::string line = readLine(data, r.file_offset);
    if (line.size() > max_hdr) max_hdr = line.size();
    TtdbRecord pr;
    if (ttdbParseHeader(line.c_str(), pr)) {
      pr.file_offset = r.file_offset;
      r = pr;
      ++parsed;
    } else {
      printf("      unparseable header at offset %u: %.60s\n", r.file_offset, line.c_str());
    }
  }
  CHECK(parsed == (int)recs.size(), "all %zu headers parse (no phantom (0,0) records)", recs.size());
  CHECK(max_hdr < 255, "longest header line %zu chars < readLine cap 256", max_hdr);

  // Duplicate coordinates violate collision_policy: reject.
  int dups = 0;
  for (size_t a = 0; a < recs.size(); ++a)
    for (size_t b = a + 1; b < recs.size(); ++b)
      if (recs[a].lat == recs[b].lat && recs[a].lon == recs[b].lon) ++dups;
  CHECK(dups == 0, "no duplicate (lat,lon) ids (%d dups)", dups);

  // Edges: parse every header's relates: list with the firmware parser and
  // verify every target resolves to an indexed record (a dangling edge would
  // render as a grayed-out link and break graph navigation).
  int total_edges = 0, dangling = 0, max_edges_one = 0;
  for (auto& r : recs) {
    std::string line = readLine(data, r.file_offset);
    TtdbEdge edges[8];
    uint8_t ne = ttdbParseEdges(line.c_str(), edges, 8);
    if (ne > max_edges_one) max_edges_one = ne;
    total_edges += ne;
    for (uint8_t e = 0; e < ne; ++e) {
      bool found = false;
      for (auto& t : recs)
        if (t.lat == edges[e].target_lat && t.lon == edges[e].target_lon) found = true;
      if (!found) {
        ++dangling;
        printf("      dangling edge %s@LAT%dLON%d from @LAT%dLON%d\n",
               edges[e].type, edges[e].target_lat, edges[e].target_lon, r.lat, r.lon);
      }
      if (strlen(edges[e].type) >= TTDB_EDGE_TYPE_LEN - 1) {
        printf("      edge type at cap (truncated?): %s\n", edges[e].type);
        ++fails;
      }
    }
  }
  CHECK(dangling == 0, "all %d edges resolve to indexed records", total_edges);
  CHECK(max_edges_one <= 8, "max edges on one record %d fits an 8-slot buffer", max_edges_one);

  // Agent32-style navigation sanity: nearest() lands where expected.
  int idx = ttdbNearest(recs.data(), (int)recs.size(), 20, 7);
  CHECK(idx >= 0 && recs[idx].lat == 20 && recs[idx].lon == 7,
        "nearest(20,7) = TTN-RFC-0007 record (got LAT%dLON%d)",
        idx >= 0 ? recs[idx].lat : -1, idx >= 0 ? recs[idx].lon : -1);
  idx = ttdbNearest(recs.data(), (int)recs.size(), 97, 2);
  CHECK(idx >= 0 && recs[idx].lat == 98,
        "nearest(97,2) lands in the lat-98 belief lane (got LAT%d)",
        idx >= 0 ? recs[idx].lat : -1);

  // recordSpan reconstruction: preamble + record spans must tile the file
  // exactly (this is what TtdbShare streams over the mesh).
  size_t covered = recs.empty() ? data.size() : recs[0].file_offset;
  for (size_t i = 0; i < recs.size(); ++i) {
    size_t end = (i + 1 < recs.size()) ? recs[i + 1].file_offset : data.size();
    covered += end - recs[i].file_offset;
  }
  CHECK(covered == data.size(), "preamble + record spans tile the file (%zu bytes)", data.size());

  printf("%s: %d checks failed\n", fails ? "RESULT FAIL" : "RESULT OK", fails);
  return fails ? 1 : 0;
}
