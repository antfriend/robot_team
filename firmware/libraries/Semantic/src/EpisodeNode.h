// EpisodeNode.h — the Arduino-side glue for the EPISODE tier (ACT-III §C2). The portable
// half (Episode.h) owns the record grammar, the reader and the ring's bookkeeping; this
// half owns the order of operations against a real Ttdb — the same split as
// TimeStream/TimeStreamNode and TraceField/TraceFieldNode.
//
// ⚠ Header-only and NOT part of the native test build: it includes <Arduino.h> and
// TTDB.h. Everything here that could be wrong in a way a test could catch lives in
// Episode.cpp; what remains is plumbing, and it is kept small on purpose.
//
// THE ORDER, and every step is from loop(), never a radio callback (a flash write):
//   begin()      at boot — before the radios, while the heap is free:
//                  scan the index → read the NEWEST checkpoint (seeds carried + horizon)
//                  → stream the live episodes KEEPING → cut whatever is dead.
//   appendLink() per scored link window: render → appendRecord → feed it KEEPING.
//   service()    fold each tier over ITS quota (EVICTING replay) → commit (append a checkpoint) → cut
//                once SEMANTIC_CUT_SLACK records are dead, with a back-off after failure.
//
// ⚠ A FAILED CUT IS NOT AN ERROR STATE — it is the case the design is for. The checkpoint
// is the commit point, so dead records behind it are skipped on every read and the only
// cost is index slots. What IS worth saying out loud is a cut failing repeatedly with the
// index running low, which is why stats carry the failing step's name.
#pragma once
#include <Arduino.h>
#include <TTDB.h>
#include <stdlib.h>
#include "Episode.h"
#include "EpisodeOrder.h"

namespace episodenode {

// TtdbCut and semantic::Cut are declared as twins so Semantic never includes <FS.h>.
static_assert(sizeof(TtdbCut) == sizeof(semantic::Cut), "TtdbCut / semantic::Cut drifted");
// The readers below hold whole `said:` lines (Episode.h), which are longer than percept lines.
static_assert(SEMANTIC_SAID_LINE_MAX >= SEMANTIC_LINE_MAX + 56,
              "a said line that renders must come back through the reader intact");

#ifndef EPISODENODE_CUT_RETRY_MS
// After a refused rewrite, wait before trying again: with the radios up the refusal is
// usually the heap (TTDB.h), and retrying every window would spend a whole-file copy per
// minute learning the same thing.
#define EPISODENODE_CUT_RETRY_MS 300000UL
#endif

struct Stats {
  uint32_t appended = 0, append_failed = 0, render_failed = 0;
  uint32_t commits = 0, commit_failed = 0, commit_nomem = 0;
  uint32_t cuts = 0, cut_failed = 0, cut_records = 0;
  uint32_t long_lines = 0;          // body lines longer than the line buffer, skipped
  TtdbRewriteErr last_cut_err = TTDB_RW_OK;
};

// Stream one indexed record's lines into anything with line(const char*).
// ⚠ An over-long BODY line is skipped and counted, never fed truncated: a cut percept
// line can parse as a DIFFERENT triple. An over-long HEADER line is fed truncated, because
// the readers only take its leading `@LATxLONy`.
template <class R>
inline bool streamRecord(Ttdb& db, int idx, R& r, uint32_t& long_lines) {
  size_t off = 0, len = 0;
  if (!db.recordSpan(idx, off, len)) return false;
  char chunk[256];
  char line[SEMANTIC_SAID_LINE_MAX];
  size_t ll = 0;
  bool over = false;
  auto emit = [&]() {
    line[ll] = '\0';
    if (ll && line[ll - 1] == '\r') line[--ll] = '\0';
    if (!over || line[0] == '@') r.line(line);
    else ++long_lines;
    ll = 0;
    over = false;
  };
  while (len) {
    const size_t want = len < sizeof(chunk) ? len : sizeof(chunk);
    const size_t got = db.readBytes(off, (uint8_t*)chunk, want);
    if (!got) return false;
    for (size_t i = 0; i < got; ++i) {
      const char c = chunk[i];
      if (c == '\n') emit();
      else if (ll < sizeof(line) - 1) line[ll++] = c;
      else over = true;
    }
    off += got;
    len -= got;
    yield();
  }
  if (ll) emit();
  return true;
}

// Same, over bytes already in RAM (the record just rendered, so it is not read back).
template <class R>
inline void feedBuffer(const char* text, size_t n, R& r) {
  char line[SEMANTIC_SAID_LINE_MAX];
  size_t ll = 0;
  for (size_t i = 0; i <= n; ++i) {
    const char c = (i < n) ? text[i] : '\n';
    if (c == '\n') {
      line[ll] = '\0';
      if (ll || i < n) r.line(line);
      ll = 0;
    } else if (ll < sizeof(line) - 1) {
      line[ll++] = c;
    }
  }
}

// Feeds one stream of lines to the tier's reader AND (when order is on) to boot recovery.
struct BootTee {
  semantic::EpisodeReader& rd;
  semantic::OrderRecovery* rec;
  void (*sink)(void*, const char*);
  void* sink_ctx;
  void line(const char* l) {
    rd.line(l);
    if (rec) rec->line(l);
    if (sink) sink(sink_ctx, l);
  }
};

class Node {
 public:
  // ACT-III §C4 (docs/design/episode-order.md): attach BEFORE begin(). Every episode this
  // node writes then carries `seq:`/`follows:` from `vc`, and begin() restores `vc`'s seq
  // and vector from the newest live episode. Null (the default) writes exactly what it did
  // before. The clock's RADIO side (inbox, emit) is the sketch's; this only reads and
  // commits it, always from loop().
  void attachOrder(semantic::VectorClock* vc) { order_ = vc; }
  // Every line begin() streams (the live episodes, all tiers) is also handed to `fn`. Attach
  // BEFORE begin(). Stage 2's author builds its lon -> seq map from it (EpisodeDeliveryNode.h).
  void attachBootSink(void (*fn)(void*, const char*), void* ctx) {
    boot_sink_ = fn;
    boot_sink_ctx_ = ctx;
  }
  // The last LINK episode this node appended, and a counter that moves with each one.
  uint32_t linkAppends() const { return link_gen_; }
  int16_t lastLinkOrdinal() const { return last_link_ord_; }
  uint32_t lastLinkSeq() const { return last_link_seq_; }

  // Boot. Call from setup() AFTER gDb.begin() and BEFORE the radios come up, so the cut
  // here runs with the heap that makes a rewrite succeed. `quotas`: per-tier capacity
  // (null = SEMANTIC_QUOTA_*).
  void begin(Ttdb& db, const uint16_t* quotas = nullptr,
             uint16_t batch = SEMANTIC_EVICT_BATCH) {
    db_ = &db;
    c_.begin();
    tiers_.begin(quotas, batch);
    scan();
    if (tiers_.hasCheckpoint()) {
      semantic::CheckpointReader cr(c_, tiers_.checkpointOrdinal());
      for (int i = 0; i < db.recordCount(); ++i)
        if (db.record(i).lat == SEMANTIC_CARRIED_LANE &&
            db.record(i).lon == tiers_.checkpointOrdinal())
          streamRecord(db, i, cr, st_.long_lines);
      tiers_.applyCheckpoint(cr);
      ck_malformed_ = cr.malformed();
    }
    // ONE pass over the lane, each record routed to its own tier's reader.
    semantic::EpisodeReader rd[SEMANTIC_TIERS] = {
        semantic::EpisodeReader(c_), semantic::EpisodeReader(c_),
        semantic::EpisodeReader(c_), semantic::EpisodeReader(c_)};
    int16_t from[SEMANTIC_TIERS], through[SEMANTIC_TIERS];
    bool live[SEMANTIC_TIERS];
    for (uint8_t k = 0; k < SEMANTIC_TIERS; ++k) {
      live[k] = tiers_.ring(k).liveRun(from[k], through[k]);
      if (live[k]) rd[k].select(from[k], through[k], semantic::Consolidator::KEEPING,
                                tiers_.ring(k).band());
    }
    semantic::OrderRecovery orec;    // the newest live episode is never folded (Episode.h)
    for (int i = 0; i < db.recordCount(); ++i) {
      const TtdbRecord& rec = db.record(i);
      if (rec.lat != SEMANTIC_EPISODE_LANE) continue;
      const int k = semantic::tierOf(rec.lon);
      if (k < 0 || k >= SEMANTIC_TIERS || !live[k]) continue;
      if (!tiers_.ring(k).inRun(rec.lon, from[k], through[k])) continue;
      BootTee tee{rd[k], order_ ? &orec : nullptr, boot_sink_, boot_sink_ctx_};
      streamRecord(db, i, tee, st_.long_lines);
    }
    for (uint8_t k = 0; k < SEMANTIC_TIERS; ++k) {
      rd[k].finish();
      boot_fed_ += rd[k].fed();
    }
    if (order_) orec.applyTo(*order_);
    cut(true);                     // boot: always, regardless of slack
  }

  // One scored link window -> one episode in the LINK band. The write is never refused by
  // this tier; the only refusal left is the whole-file index cap inside appendRecord.
  bool appendLink(const semantic::LinkClaim* claims, int n, const char* at, uint32_t t) {
    if (!db_) return false;
    const int16_t ord = tiers_.nextOrdinal(semantic::TIER_LINK);
    char ob[EPISODEORDER_BLOCK_MAX];
    const size_t m = semantic::renderLinkEpisode(claims, n, ord, t, at, scratch_,
                                                 sizeof(scratch_), orderBlock(ob));
    if (!m) { ++st_.render_failed; return false; }
    return appendRendered(scratch_, m, ord);
  }

  // ⚠ ONE SCRATCH BUFFER for every episode render, and the sampler renders INTO IT. Two
  // statics here (+5632 B .bss) boot-looped the Cardputer on 2026-10-01: the BLE scanner's
  // `operator new` failed at boot with ~26 KB free. Everything that touches it runs from
  // loop(), one call after another, so one buffer is enough. Not reentrant by design.
  char* scratch() { return scratch_; }
  static constexpr size_t scratchCap() { return sizeof(scratch_); }

  // A sampler's record, already rendered at scratch()[0..m) (body lines `**…`), becomes one
  // episode at `ord`, which the caller took from nextOrdinal(tier) BEFORE rendering, so the
  // record's own citations (EntityPercept's `covered_by:`) can name it. Wrapped in place —
  // see Episode.h, renderSaidEpisodeInPlace.
  bool appendSaidScratch(int16_t ord, size_t m, const char* title, const char* source,
                         const char* at, uint32_t t) {
    if (!db_) return false;
    char ob[EPISODEORDER_BLOCK_MAX];
    const size_t n = semantic::renderSaidEpisodeInPlace(scratch_, sizeof(scratch_), m, ord, t,
                                                        title, source, at, orderBlock(ob));
    if (!n) { ++st_.render_failed; return false; }
    return appendRendered(scratch_, n, ord);
  }

  // One LINK window, scored or not (2026-10-02): LinkPercept's record already rendered at
  // scratch()[0..m), plus this window's scored claims (n may be 0). `ord` was taken from
  // nextOrdinal(TIER_LINK) BEFORE rendering, so PerceptLearn's stageBegin() could cite it.
  // See Episode.h, THE LINK WINDOW AS AN EPISODE.
  bool appendLinkWindowScratch(int16_t ord, size_t m, const semantic::LinkClaim* claims,
                               int n, const char* at, uint32_t t) {
    if (!db_) return false;
    char ob[EPISODEORDER_BLOCK_MAX];
    const size_t r = semantic::renderLinkWindowEpisodeInPlace(scratch_, sizeof(scratch_), m,
                                                              claims, n, ord, t, at,
                                                              orderBlock(ob));
    if (!r) { ++st_.render_failed; return false; }
    return appendRendered(scratch_, r, ord);
  }

  // Any tier: a record already rendered at `ord` = nextOrdinal(tier). Appends, then feeds
  // it KEEPING from RAM (it is not read back).
  bool appendRendered(const char* rec, size_t m, int16_t ord) {
    if (!db_) return false;
    const int k = semantic::tierOf(ord);
    if (k < 0 || k >= SEMANTIC_TIERS) { ++st_.render_failed; return false; }
    const uint32_t seq = pending_seq_;
    pending_seq_ = 0;                // spent or not, it belongs to THIS render only
    if (!db_->appendRecord(rec, m)) { ++st_.append_failed; return false; }
    ++st_.appended;
    // ⚠ Commit ONLY the seq this render carried, and only now: a refused append re-uses
    // the number, so seq stays dense (EpisodeOrder.h).
    if (order_ && seq) order_->committed(seq);
    if (k == semantic::TIER_LINK) {
      last_link_ord_ = ord;
      last_link_seq_ = seq;
      ++link_gen_;
    }
    tiers_.appended(ord);
    semantic::EpisodeReader r(c_);
    r.select(ord, ord, semantic::Consolidator::KEEPING, semantic::tierBand((uint8_t)k));
    feedBuffer(rec, m, r);
    r.finish();
    return true;
  }
  int16_t nextOrdinal(uint8_t tier) const { return tiers_.nextOrdinal(tier); }

  // Fold -> commit -> cut. Cheap when nothing is due (no file I/O at all).
  void service(uint32_t now_ms, uint32_t t) {
    if (!db_) return;
    uint8_t k;
    int16_t from, through;
    while (tiers_.foldDue(k, from, through)) {       // each tier over ITS quota, in turn
      semantic::EpisodeReader r(c_);
      r.select(from, through, semantic::Consolidator::EVICTING, tiers_.ring(k).band());
      for (int i = 0; i < db_->recordCount(); ++i) {
        const TtdbRecord& rec = db_->record(i);
        if (rec.lat == SEMANTIC_EPISODE_LANE && tiers_.ring(k).inRun(rec.lon, from, through))
          streamRecord(*db_, i, r, st_.long_lines);
      }
      r.finish();
      tiers_.folded(k, through);
    }
    if (tiers_.commitDue()) commit(t);
    if (tiers_.dead() >= SEMANTIC_CUT_SLACK &&
        (last_cut_fail_ms_ == 0 || now_ms - last_cut_fail_ms_ >= EPISODENODE_CUT_RETRY_MS)) {
      if (!cut(false)) last_cut_fail_ms_ = now_ms ? now_ms : 1;
      else last_cut_fail_ms_ = 0;
    }
  }

  semantic::Consolidator& beliefs() { return c_; }
  const semantic::EpisodeTiers& tiers() const { return tiers_; }
  // The node's beliefs (ACT-III §C3): live + carried, exactly what a reboot recomputes.
  const semantic::Consolidator& consolidator() const { return c_; }
  const Stats& stats() const { return st_; }
  uint32_t bootFed() const { return boot_fed_; }
  uint32_t checkpointMalformed() const { return ck_malformed_; }

  // One line of state, then one `belief:` line per term, for the serial log.
  void print(Print& out) const {
    const semantic::EpisodeRing& lk = tiers_.ring(semantic::TIER_LINK);
    out.printf("[episode] live %u present %u dead %u horizon %s%d terms %u reclaimed %lu "
               "| appended %lu (fail %lu) commits %lu (fail %lu nomem %lu) cuts %lu "
               "(fail %lu last '%s') malformed %lu | tiers L%u/%u E%u/%u M%u/%u A%u/%u\n",
               (unsigned)tiers_.live(), (unsigned)tiers_.present(), (unsigned)tiers_.dead(),
               lk.hasHorizon() ? "" : "none/", (int)lk.flashHorizon(),
               (unsigned)c_.termCount(), (unsigned long)c_.reclaimed(),
               (unsigned long)st_.appended, (unsigned long)st_.append_failed,
               (unsigned long)st_.commits, (unsigned long)st_.commit_failed,
               (unsigned long)st_.commit_nomem, (unsigned long)st_.cuts,
               (unsigned long)st_.cut_failed, ttdbRewriteErrName(st_.last_cut_err),
               (unsigned long)c_.malformedCount(),
               (unsigned)tiers_.ring(0).live(), (unsigned)tiers_.ring(0).capacity(),
               (unsigned)tiers_.ring(1).live(), (unsigned)tiers_.ring(1).capacity(),
               (unsigned)tiers_.ring(2).live(), (unsigned)tiers_.ring(2).capacity(),
               (unsigned)tiers_.ring(3).live(), (unsigned)tiers_.ring(3).capacity());
    for (size_t i = 0; i < c_.termCount(); ++i) {
      const semantic::Term* tm = c_.term(i);
      char b[128];
      if (c_.beliefLine(*tm, b, sizeof(b)))
        out.printf("[episode]   %s %s eps:%u carried:%s\n", tm->subject, b,
                   (unsigned)c_.eps(*tm),
                   (tm->carried_for || tm->carried_against) ? "yes" : "no");
    }
  }

 private:
  // The `seq:`/`follows:` block for the episode about to be rendered, or null when order
  // is off or the block does not fit (an episode WITHOUT order beats no episode at all).
  const char* orderBlock(char* ob) {
    pending_seq_ = 0;
    if (!order_ || !order_->renderBlock(ob, EPISODEORDER_BLOCK_MAX)) return nullptr;
    pending_seq_ = order_->nextSeq();
    return ob;
  }

  void scan() {
    tiers_.resetScan();
    for (int i = 0; i < db_->recordCount(); ++i)
      tiers_.observe(db_->record(i).lat, db_->record(i).lon);
  }

  // Exact-size heap allocation, freed at once: a 4.4 KB static for a write that happens
  // once per BATCH windows is the wrong trade on a node whose maxalloc is single-digit KB.
  // A failed malloc just leaves the commit due — harmless by the commit-point order.
  // ⚠ EVERY tier's horizon goes in, not just the one that folded: only the newest
  // checkpoint is ever read (Episode.h, THE CHECKPOINT).
  void commit(uint32_t t) {
    const int16_t ck = tiers_.nextCheckpointOrdinal();
    int16_t hs[SEMANTIC_TIERS];
    const uint8_t nh = tiers_.horizons(hs);
    const size_t need = semantic::checkpointBytes(c_, hs, nh, ck, t);
    if (!need) { ++st_.commit_failed; return; }
    char* buf = (char*)malloc(need + 1);
    if (!buf) { ++st_.commit_nomem; return; }
    const size_t m = semantic::renderCheckpoint(c_, hs, nh, ck, t, buf, need + 1);
    const bool ok = m && db_->appendRecord(buf, m);
    free(buf);
    if (!ok) { ++st_.commit_failed; return; }
    ++st_.commits;
    tiers_.checkpointAppended(ck);
  }

  bool cut(bool boot) {
    semantic::Cut cs[SEMANTIC_TIER_CUTS_MAX];
    const uint8_t n = tiers_.cuts(cs, SEMANTIC_TIER_CUTS_MAX);
    if (!n) return true;
    (void)boot;
    TtdbCut tc[SEMANTIC_TIER_CUTS_MAX];
    for (uint8_t i = 0; i < n; ++i) tc[i] = TtdbCut{cs[i].lat, cs[i].lon_lo, cs[i].lon_hi};
    const uint16_t dead = tiers_.dead();
    db_->clearRewriteErr();
    if (!db_->removeCuts(tc, n)) {
      ++st_.cut_failed;
      st_.last_cut_err = db_->lastRewriteErr();
      // ⚠ RENAME means the TTDB is in `<path>.tmp` and the index is stale; anything but
      // a rescan of what Ttdb now believes would compound it.
      scan();
      return false;
    }
    ++st_.cuts;
    st_.cut_records += dead;
    st_.last_cut_err = TTDB_RW_OK;
    scan();                        // removeCuts re-indexed; the tiers re-read the index
    return true;
  }

  Ttdb* db_ = nullptr;
  semantic::VectorClock* order_ = nullptr;
  uint32_t pending_seq_ = 0;
  void (*boot_sink_)(void*, const char*) = nullptr;
  void* boot_sink_ctx_ = nullptr;
  uint32_t link_gen_ = 0, last_link_seq_ = 0;
  int16_t last_link_ord_ = 0;
  static_assert(SEMANTIC_ENTITY_EPISODE_BUF >= SEMANTIC_LINK_EPISODE_BUF,
                "the shared scratch must hold the largest episode any tier renders");
  char scratch_[SEMANTIC_ENTITY_EPISODE_BUF];
  semantic::Consolidator c_;
  semantic::EpisodeTiers tiers_;
  Stats st_;
  uint32_t last_cut_fail_ms_ = 0;
  uint32_t boot_fed_ = 0;
  uint32_t ck_malformed_ = 0;
};

}  // namespace episodenode
