// LaneGen.cpp — portable (no Arduino), so the record format and the field-matching
// trap are both native-testable. The Arduino wiring lives in LaneGenNode.h.
#include "LaneGen.h"
#include <stdio.h>
#include <string.h>

namespace lanegen {

size_t buildPruneRecord(char* out, size_t cap, int lane_n, const Prune& p,
                        uint32_t t_sec, const uint32_t* explained,
                        int n_explained) {
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
  size_t len = (size_t)n;
  if (explained && n_explained > 0) {
    // One extra body line naming every stream the ended generation explained. Written
    // as a whole line or not at all: a half-written id list would silently shorten the
    // set of streams that stay answerable, which is worse than admitting the loss.
    char ids[24 * 17 + 32];
    int m = snprintf(ids, sizeof(ids), "**STREAMS-EXPLAINED** n:%d", n_explained);
    if (m <= 0 || (size_t)m >= sizeof(ids)) return 0;
    for (int i = 0; i < n_explained; ++i) {
      const int k = snprintf(ids + m, sizeof(ids) - (size_t)m, " 0x%08lx",
                             (unsigned long)explained[i]);
      if (k <= 0 || (size_t)(m + k) >= sizeof(ids)) return 0;
      m += k;
    }
    if (len + (size_t)m + 2 >= cap) return 0;
    len += (size_t)snprintf(out + len, cap - len, "%s\n", ids);
  }
  return len;
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
