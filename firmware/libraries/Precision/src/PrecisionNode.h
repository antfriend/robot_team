// PrecisionNode.h — Arduino glue for the PRECISION lane (docs/design/rfc0011-stage3.md §2,
// §5.1). Header-only; NOT in the native build (it includes <Arduino.h>). Every decision is
// in Precision.{h,cpp} and PrecisionJob.h, which are tested natively — the job against the
// real Ttdb through tests/shim/.
//
// Two calls:
//   startCycle()  — from Stage D, once per Dream Cycle: start the next channel's job, or
//                   print `busy` and leave the rotation where it is.
//   service()     — EVERY loop pass: fold ≤ PRECISION_JOB_STEP episodes (D3b), and on the
//                   pass the fold completes, apply the write rule and print the `[prec]` line.
//
// It owns no text buffer: episodes are read into, and the record rendered into, the caller's
// scratch — the episode tier's ONE scratch (EpisodeNode::scratch(); a second static
// boot-looped the Cardputer, docs/log/2026-10.md). Nothing is kept in it between passes.
// ⚠ The Job (its Fold, 1 248 B) IS static now: D3b needs it to outlive a pass. That is the
// +~1.3 KB .bss design §5.1 weighs against the 5.6 KB that boot-looped this board.
#pragma once
#include <Arduino.h>
#include <TTDB.h>
#include <TimeStream.h>

#include "Precision.h"
#include "PrecisionJob.h"

namespace precision {

class Node {
 public:
  void startCycle(Print& log) {
    if (!job_.start(next_)) {
      log.printf("[prec] busy: chan:%s still folding (pass %lu) - rotation held\n",
                 chanName(job_.fold().chan()), (unsigned long)job_.passes());
      return;
    }
    next_ = (uint8_t)((next_ + 1) % CH_COUNT);
    total_ms_ = worst_ms_ = 0;
  }

  void service(Ttdb& db, char* scratch, size_t cap, uint32_t node, uint32_t t_sec,
               const timestream::Stamp& st, Print& log) {
    if (!job_.running()) return;
    const uint32_t t0 = millis();
    const Job::Status s = job_.step(db, scratch, cap);
    const uint32_t ms = millis() - t0;
    total_ms_ += ms;
    if (ms > worst_ms_) worst_ms_ = ms;
    if (s == Job::ABORTED) {
      log.printf("[prec] chan:%s ABORTED (%s) after %lu pass(es), episodes:%lu aborts:%lu\n",
                 chanName(job_.fold().chan()), job_.abortWhy(), (unsigned long)job_.passes(),
                 (unsigned long)job_.fold().episodes(), (unsigned long)job_.aborts());
      return;
    }
    if (s != Job::READY) return;

    const uint32_t w0 = millis();
    char stamp[72];
    if (!timestream::buildStamp(stamp, sizeof(stamp), st)) stamp[0] = 0;
    const char* outcome = "no";
    char why[48];
    job_.finish(db, scratch, cap, node, t_sec, stamp, outcome, why, sizeof(why));
    const uint32_t write_ms = millis() - w0;
    const Fold& f = job_.fold();
    // The loop task's stack high-water mark (bytes on ESP-IDF): the margin, measured.
    const unsigned stack_free = (unsigned)uxTaskGetStackHighWaterMark(nullptr);
    log.printf("[prec] chan:%s n:%lu var:%ld prec:%u conf:%u episodes:%lu excluded:%lu "
               "segments:%lu skipped:%lu from:%ld through:%ld passes:%lu worst_pass_ms:%lu "
               "total_ms:%lu wrote:%s (%s) ms_write:%lu aborts:%lu stack_free:%u heap:%u\n",
               chanName(f.chan()), (unsigned long)f.n(), (long)f.var(), (unsigned)f.prec(),
               (unsigned)f.conf(), (unsigned long)f.episodes(), (unsigned long)f.excluded(),
               (unsigned long)f.segments(), (unsigned long)f.skipped(), (long)f.from(),
               (long)f.through(), (unsigned long)job_.passes(), (unsigned long)worst_ms_,
               (unsigned long)total_ms_, outcome, why, (unsigned long)write_ms,
               (unsigned long)job_.aborts(), stack_free, (unsigned)ESP.getFreeHeap());
  }

 private:
  Job job_;
  uint8_t next_ = CH_LINK;
  uint32_t total_ms_ = 0, worst_ms_ = 0;
};

}  // namespace precision
