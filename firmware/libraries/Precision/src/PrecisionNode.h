// PrecisionNode.h — Arduino glue for the PRECISION lane (docs/design/rfc0011-stage3.md §2, §5).
//
// ⚠ Header-only and NOT part of the native test build (it includes <Arduino.h> and walks a
// real Ttdb). Everything it decides is in Precision.{h,cpp}, which is tested natively.
//
// One call per Stage D cycle folds ONE channel (rotation link, entity, motion, acoustic) from
// the episodes on flash, then applies the write rule. It owns no buffer: episodes are read
// into, and the record rendered into, the caller's scratch — the episode tier's ONE scratch
// (EpisodeNode::scratch(); a second static boot-looped the Cardputer, docs/log/2026-10.md).
// The fold state (two parsed windows, ~1.2 KB) lives on this function's stack.
#pragma once
#include <Arduino.h>
#include <TTDB.h>
#include <TimeStream.h>

#include "Precision.h"

namespace precision {

class Node {
 public:
  // Returns the channel folded. `t_sec` = the stream's wall seconds (0 if none).
  uint8_t serviceCycle(Ttdb& db, char* scratch, size_t cap, uint32_t node, uint32_t t_sec,
                       const timestream::Stamp& st, Print& log) {
    const uint8_t chan = next_;
    next_ = (uint8_t)((next_ + 1) % CH_COUNT);
    const uint32_t t0 = millis();

    Fold f(chan);
    int existing = -1;
    for (int i = 0; i < db.recordCount(); ++i) {
      const TtdbRecord& r = db.record(i);
      if (r.lat == PRECISION_LANE && r.lon == chan) existing = i;
      if (r.lat != PRECISION_EPISODE_LANE || chanOfLon(r.lon) != (int)chan) continue;
      size_t off = 0, len = 0;
      if (!db.recordSpan(i, off, len) || len + 1 > cap ||
          db.readBytes(off, (uint8_t*)scratch, len) != len) {
        f.skip(r.lon);            // counted and written down; the gate FAILs on any skip
        continue;
      }
      scratch[len] = 0;
      f.add(scratch, len, r.lon);
    }
    const uint32_t fold_ms = millis() - t0;

    OnFlash old;
    if (existing >= 0) {
      size_t off = 0, len = 0;
      if (db.recordSpan(existing, off, len) && len + 1 <= cap &&
          db.readBytes(off, (uint8_t*)scratch, len) == len) {
        scratch[len] = 0;
        readOnFlash(scratch, len, old);
      }
    }

    const char* outcome = "no";
    char why[40];
    snprintf(why, sizeof(why), "n=0");
    uint32_t write_ms = 0;
    if (f.n() > 0) {
      const int d = old.present ? (int)f.prec() - (int)old.prec : 0;
      snprintf(why, sizeof(why), old.present ? "d=%d" : "none on flash", d);
    }
    if (shouldWrite(old, f)) {
      const uint32_t w0 = millis();
      char stamp[72];
      if (!timestream::buildStamp(stamp, sizeof(stamp), st)) stamp[0] = 0;
      const uint16_t rev = old.present ? (uint16_t)(old.rev + 1) : 0;
      const size_t m = render(scratch, cap, f, node, rev, old.present ? old.created : 0,
                              t_sec, stamp);
      if (m == 0) {
        outcome = "FAILED (render)";
      } else if (existing < 0 && db.indexHeadroom() < 1) {
        outcome = "FAILED (index full)";   // ACT-III: never refused without saying so
      } else {
        bool ok = true;
        if (existing >= 0) {
          const TtdbCut cut = {PRECISION_LANE, (int16_t)chan, (int16_t)chan};
          ok = db.removeCuts(&cut, 1);
        }
        outcome = !ok ? "FAILED (removeCuts)"
                : db.appendRecord(scratch, m) ? "yes" : "FAILED (append)";
      }
      write_ms = millis() - w0;
    }
    // The fold keeps ~1.25 KB on THIS stack (two parsed windows). Report the loop task's
    // high-water mark (bytes on ESP-IDF) so the margin is measured, not assumed.
    const unsigned stack_free = (unsigned)uxTaskGetStackHighWaterMark(nullptr);
    log.printf("[prec] chan:%s n:%lu var:%ld prec:%u conf:%u episodes:%lu excluded:%lu "
               "segments:%lu skipped:%lu from:%ld through:%ld ms:%lu wrote:%s (%s) ms_write:%lu "
               "stack_free:%u\n",
               chanName(chan), (unsigned long)f.n(), (long)f.var(), (unsigned)f.prec(),
               (unsigned)f.conf(), (unsigned long)f.episodes(), (unsigned long)f.excluded(),
               (unsigned long)f.segments(), (unsigned long)f.skipped(), (long)f.from(),
               (long)f.through(), (unsigned long)fold_ms, outcome, why,
               (unsigned long)write_ms, stack_free);
    return chan;
  }

 private:
  uint8_t next_ = CH_LINK;
};

}  // namespace precision
