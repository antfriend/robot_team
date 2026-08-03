// LaneGen.cpp — portable (no Arduino), so the record format and the field-matching
// trap are both native-testable. The Arduino wiring lives in LaneGenNode.h.
#include "LaneGen.h"
#include <stdio.h>
#include <string.h>

namespace lanegen {

size_t buildPruneRecord(char* out, size_t cap, int lane_n, const Prune& p,
                        uint32_t t_sec) {
  char stamp[64];
  if (!timestream::buildStamp(stamp, sizeof(stamp), p.stamp)) return 0;
  // The edge points at the node's own identity record, never at the lane that was
  // just emptied: an edge into a pruned lane would dangle by construction, and a
  // record whose whole purpose is to keep citations interpretable must not ship one.
  int n = snprintf(
      out, cap,
      "\n---\n\n@LAT%dLON%d | created:%lu | updated:%lu | relates:prunes@LAT0LON0\n\n"
      "**LANE-PRUNED** lane:%u gen:%d removed:%d last_lon:%d %s node:0x%08lX\n",
      (int)LANE, lane_n, (unsigned long)t_sec, (unsigned long)t_sec,
      (unsigned)p.lane, p.gen, p.removed, p.last_lon, stamp,
      (unsigned long)p.node_id);
  if (n <= 0 || (size_t)n >= cap) return 0;   // nothing rather than a truncation
  return (size_t)n;
}

bool pruneRecordNamesLane(const char* body, size_t len, uint8_t lane) {
  if (!body || len == 0) return false;
  static const char kNeedle[] = " lane:";
  const size_t nlen = sizeof(kNeedle) - 1;
  for (size_t i = 0; i + nlen < len; ++i) {
    if (memcmp(body + i, kNeedle, nlen) != 0) continue;
    size_t j = i + nlen;
    if (j >= len || body[j] < '0' || body[j] > '9') continue;
    unsigned v = 0;
    while (j < len && body[j] >= '0' && body[j] <= '9') {
      v = v * 10 + (unsigned)(body[j] - '0');
      if (v > 65535u) return false;           // malformed; do not wrap into a match
      ++j;
    }
    // A digit here would mean the match was a PREFIX of a longer number — the trap
    // this function exists to avoid. j is one past the last digit, so the check is
    // simply that we consumed them all, which the loop above guarantees.
    return v == (unsigned)lane;
  }
  return false;
}

int nextGeneration(int markers_naming_lane) {
  return (markers_naming_lane < 0 ? 0 : markers_naming_lane) + 1;
}

}  // namespace lanegen
