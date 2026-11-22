// PrecisionNode.h — Arduino glue for the PRECISION lane (docs/design/rfc0011-stage3.md §2,
// §5.1, §11). Header-only; NOT in the native build (it includes <Arduino.h>). Every decision
// is in Precision.{h,cpp} and PrecisionJob.h (Job + Lane), tested natively — the job and the
// cut rider against the real Ttdb through tests/shim/.
//
// Calls, in this order:
//   attach()      — in setup(), BEFORE gEpisodes.begin(): binds the store and scratch and
//                   registers the cut rider (D8), so a boot-time cut carries it too.
//   startCycle()  — from Stage D: start the next rotation channel, or print `busy`.
//   service()     — EVERY loop pass: start a refold a rider cut queued (D8), fold
//                   ≤ PRECISION_JOB_STEP episodes (D3b), and on the pass the fold completes
//                   apply the write rule (append, or defer to the next cut) and print `[prec]`.
//
// It owns no text buffer: episodes are read into, and the record rendered into, the episode
// tier's ONE scratch (a second static boot-looped the Cardputer, docs/log/2026-10.md).
// ⚠ The Lane (its Fold, 1 248 B) IS static: D3b needs it to outlive a pass (design §5.1).
// ⚠ Precision NEVER calls removeCuts: a record leaves flash only inside the episode tier's
// own cut (D8). A rewrite of our own measured ~3 s in run 2.
#pragma once
#include <Arduino.h>
#include <EpisodeNode.h>
#include <TTDB.h>
#include <TimeStream.h>

#include "Precision.h"
#include "PrecisionJob.h"

namespace precision {

class Node {
 public:
  void attach(Ttdb& db, episodenode::Node& episodes) {
    lane_.attach(&db, episodes.scratch(), episodes.scratchCap());
    episodes.attachCutRider(&Lane::riderExtra, &Lane::riderDone, &lane_);
  }

  void startCycle(Print& log) {
    if (!lane_.startCycle()) {
      log.printf("[prec] busy: chan:%s still folding (pass %lu) - rotation held\n",
                 chanName(lane_.job().fold().chan()), (unsigned long)lane_.job().passes());
      return;
    }
    total_ms_ = worst_ms_ = 0;
  }

  void service(uint32_t node, uint32_t t_sec, const timestream::Stamp& st, Print& log) {
    if (lane_.startQueued()) {
      total_ms_ = worst_ms_ = 0;
      log.printf("[prec] chan:%s refold queued by a cut (D8): started\n",
                 chanName(lane_.job().fold().chan()));
    }
    if (!lane_.job().running()) return;
    const uint32_t t0 = millis();
    const Job::Status s = lane_.step();
    const uint32_t ms = millis() - t0;
    total_ms_ += ms;
    if (ms > worst_ms_) worst_ms_ = ms;
    const Job& j = lane_.job();
    if (s == Job::ABORTED) {
      log.printf("[prec] chan:%s ABORTED (%s) after %lu pass(es), episodes:%lu aborts:%lu\n",
                 chanName(j.fold().chan()), j.abortWhy(), (unsigned long)j.passes(),
                 (unsigned long)j.fold().episodes(), (unsigned long)j.aborts());
      return;
    }
    if (s != Job::READY) return;

    const uint32_t w0 = millis();
    char stamp[72];
    if (!timestream::buildStamp(stamp, sizeof(stamp), st)) stamp[0] = 0;
    const char* outcome = "no";
    char why[48];
    lane_.finish(node, t_sec, stamp, outcome, why, sizeof(why));
    const uint32_t write_ms = millis() - w0;
    const Fold& f = j.fold();
    // The loop task's stack high-water mark (bytes on ESP-IDF): the margin, measured.
    const unsigned stack_free = (unsigned)uxTaskGetStackHighWaterMark(nullptr);
    log.printf("[prec] chan:%s n:%lu var:%ld prec:%u conf:%u episodes:%lu excluded:%lu "
               "segments:%lu skipped:%lu from:%ld through:%ld passes:%lu worst_pass_ms:%lu "
               "total_ms:%lu wrote:%s (%s) ms_write:%lu aborts:%lu stale:0x%x refold:0x%x "
               "cut_deleted:%lu stack_free:%u heap:%u\n",
               chanName(f.chan()), (unsigned long)f.n(), (long)f.var(), (unsigned)f.prec(),
               (unsigned)f.conf(), (unsigned long)f.episodes(), (unsigned long)f.excluded(),
               (unsigned long)f.segments(), (unsigned long)f.skipped(), (long)f.from(),
               (long)f.through(), (unsigned long)j.passes(), (unsigned long)worst_ms_,
               (unsigned long)total_ms_, outcome, why, (unsigned long)write_ms,
               (unsigned long)j.aborts(), (unsigned)lane_.staleMask(),
               (unsigned)lane_.refoldMask(), (unsigned long)lane_.deletedByCuts(), stack_free,
               (unsigned)ESP.getFreeHeap());
  }

 private:
  Lane lane_;
  uint32_t total_ms_ = 0, worst_ms_ = 0;
};

}  // namespace precision
