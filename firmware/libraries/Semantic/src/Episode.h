// Episode.h — the EPISODE tier (ACT-III §C2): one lane of `ttdb-episode` blocks, a ring
// that never refuses a write, and fold-before-forget made crash-safe.
//
// Semantic.h is the consolidator (TERM/BELIEF tier). This file is everything between the
// samplers and it: rendering an episode record, reading the lane back into the
// consolidator, and deciding what the ring folds and what it may delete. Portable — no
// <Arduino.h>, no <FS.h> — so tests/test_episode.cpp pins all of it natively. The Ttdb I/O
// is the sketch glue's job, exactly as LaneGen/LaneGenNode split it.
//
// ---------------------------------------------------------------------------
// THE LANES
// ---------------------------------------------------------------------------
//   @LAT103  EPISODE  (EVIDENCE)   one `ttdb-episode` block per record, EVENT-named
//   @LAT104  CARRIED  (PROVENANCE) the fold checkpoint: `through:` + carried tallies
//
// Why these numbers: every lane < 90 is a node record to both consoles' globes
// (`isNodeRecord()` is `lat > -90 && lat < 90`), and @LAT102 is reserved for attributed
// testimony (docs/design/default-network.md). 103/104 are inert everywhere that draws.
// They sit BESIDE @LAT93–97 during the transition; Phase C's deletion (C0/C5) removes
// those, not these.
//
// ---------------------------------------------------------------------------
// WHY THE CHECKPOINT, NOT THE DELETE, IS THE COMMIT POINT
// ---------------------------------------------------------------------------
// The only delete a Ttdb has is a whole-file rewrite, and that rewrite has seven distinct
// failure modes — three of them "out of heap with the radios up", measured on hardware
// (TTDB.h, TtdbRewriteErr). So a fold that is only safe if the delete succeeds is not
// safe. The order here is:
//
//   1. FOLD    replay the oldest live episodes EVICTING: live → carried, in RAM. The total
//              is invariant (Semantic.h, FOLD BEFORE FORGET), so beliefs do not move.
//   2. COMMIT  append ONE checkpoint record: `through: <ordinal>` + every term's carried
//              tally. An append is the one write a Ttdb does not rewrite for.
//   3. CUT     delete episodes at or below the COMMITTED `through:`, and older checkpoints.
//
// On boot only the NEWEST checkpoint is read, and episodes at or below its `through:` are
// SKIPPED even if they are still on flash. So:
//   - a crash after 1, before 2  → the episodes are still live on flash and the old
//                                   checkpoint still stands: the reboot recomputes the
//                                   same totals. The fold simply did not happen.
//   - a crash after 2, before 3  → the episodes are on flash but behind the horizon:
//                                   skipped, not double-counted. The cut is retried.
//   - a cut refused by the heap  → identical to the line above, indefinitely. Nothing is
//                                   lost and nothing is counted twice; the lane just holds
//                                   a few dead records until a rewrite succeeds.
// That is the whole reason there is a horizon instead of "whatever is on the lane": the
// deletion becomes garbage collection, never bookkeeping.
//
// ⚠ ONLY THE NEWEST CHECKPOINT MAY BE READ. A term the TERM tier reclaimed (lowest EPS,
// table full) is absent from every checkpoint written after it, so feeding an older
// checkpoint too would resurrect a belief the store chose to forget. CheckpointReader
// therefore honours exactly one ordinal, named by the ring's scan.
//
// ---------------------------------------------------------------------------
// WHY OLDEST-FIRST, WHEN C2c SAYS "LOWEST EPS"
// ---------------------------------------------------------------------------
// ACT-III §C2c says eviction order must not be recency. That is right for the TERM tier
// and is what Semantic's reclaim-lowest-EPS does. For EPISODES the order cannot change a
// belief at all — TTG-0003 §2 is a SUM, and the fold is a move — so the choice only
// decides which PROVENANCE survives. Oldest-first is chosen because:
//   1. it keeps the retained window CONTIGUOUS, so the horizon is ONE integer. Evicting by
//      EPS would need a set of folded ordinals on flash, and a set is the thing a
//      bounded store cannot afford to grow;
//   2. a contiguous window is what TTG-0004 §4's `follows@` edges need: "the latest
//      episode held from each node" is only well-defined if no hole sits below it;
//   3. eviction never re-points a citation. Ordinals are one more than the largest on the
//      lane (TTG-0002 §5.1), the oldest is never the largest, so — unlike a @LAT94–97
//      prune, which empties a lane and restarts at LON0 — no ordinal is ever re-used
//      while anything that could cite it is retained. No @LAT100 boundary is needed.
//
// ---------------------------------------------------------------------------
// ⚠ ORDINALS WRAP AT 32768
// ---------------------------------------------------------------------------
// `TtdbRecord::lon` is int16_t. A lane that never restarts reaches 32767 in ~23 days at
// one episode a minute. So ordinals are SERIAL NUMBERS (RFC 1982 shape) modulo
// SEMANTIC_ORDINAL_MOD, and every "older/newer" here is an age measured back from the
// newest record — never a `<` on raw ordinals. The newest is the LAST episode record in
// FILE ORDER, because appends go to the end and rewrites preserve order; that is why
// EpisodeRing::observe() must see the index in file order. This is unambiguous while the
// retained window is far smaller than the modulus (48 vs 32768). ⚠ It does make a raw
// ordinal citation ambiguous across a wrap — C4's `follows@` edges should carry the
// record's sid (TTDB-RFC-0010 §4.3), not a bare ordinal.
#ifndef SEMANTIC_EPISODE_H
#define SEMANTIC_EPISODE_H

#include <stddef.h>
#include <stdint.h>

#include "Semantic.h"

namespace semantic {

#ifndef SEMANTIC_EPISODE_LANE
#define SEMANTIC_EPISODE_LANE 103
#endif
#ifndef SEMANTIC_CARRIED_LANE
#define SEMANTIC_CARRIED_LANE 104
#endif

#define SEMANTIC_EPISODE_TAG "ttdb-episode"
#define SEMANTIC_CARRIED_TAG "ttdb-carried"
#define SEMANTIC_THROUGH_KEY "through:"

#define SEMANTIC_ORDINAL_MOD 32768

// Episodes retained live on flash. 48 is the old per-percept-lane cap — but where four
// lanes of 48 each SUMMED past the index budget, this is the whole evidence tier.
#ifndef SEMANTIC_RING_CAPACITY
#define SEMANTIC_RING_CAPACITY 48
#endif
// Folded per commit. Every commit costs one append + (eventually) one rewrite, so batching
// is what keeps the rewrite rate at one per BATCH episodes instead of one per episode.
#ifndef SEMANTIC_EVICT_BATCH
#define SEMANTIC_EVICT_BATCH 8
#endif

// Worst-case checkpoint: header + fence + `through:` + one `carried:` line per term, each
// with three full-length lemmas and 10-digit tallies. Pinned both ways by the test: a full
// table of maximal lemmas FITS, and it would not have fitted a buffer one line shorter.
// ⚠ This must never be undersized: a checkpoint that does not render cannot commit, and a
// ring that cannot commit can only grow until the WHOLE-FILE index refuses — the exact
// failure this phase exists to delete.
#define SEMANTIC_CARRIED_LINE_MAX (16 + 3 * 12 + 3 * (SEMANTIC_LEMMA_MAX + 3))
#define SEMANTIC_CARRIED_BUF (160 + SEMANTIC_MAX_TERMS * SEMANTIC_CARRIED_LINE_MAX)

// Dead records (episodes behind the committed horizon + superseded checkpoints) tolerated
// before a cut is attempted. A cut is a whole-file rewrite, so attempting one per fold
// would be one rewrite per BATCH+1 windows; this makes it one per ~SLACK. The cost is
// index slots: the tier peaks near CAPACITY + SLACK + a few, against 4×48 + 24 + 16 for
// the lanes it replaces. Boot always cuts regardless (radios down, heap free).
#ifndef SEMANTIC_CUT_SLACK
#define SEMANTIC_CUT_SLACK 16
#endif

// Rendered episode buffer for one link window: header + said/percept pair per claim.
#define SEMANTIC_LINK_EPISODE_BUF 1280   // worst case (8 maximal claims) measured 1194 B by test_episode

// One ordinal range on one lane: the portable twin of TTDB.h's TtdbCut (same fields, same
// order), so the glue converts with a field copy and Semantic never includes <FS.h>.
struct Cut {
  int16_t lat;
  int16_t lon_lo;
  int16_t lon_hi;
};

// ---------------------------------------------------------------------------------------
// Serial-number helpers. Everything older/newer goes through these.
// ---------------------------------------------------------------------------------------
int16_t ordinalAdd(int16_t x, int32_t d);
// Steps from `from` forward to `to`, modulo SEMANTIC_ORDINAL_MOD (0..32767).
uint16_t ordinalDistance(int16_t from, int16_t to);
// Is `x` in the inclusive forward run from `from` to `through`?
bool ordinalInRun(int16_t x, int16_t from, int16_t through);

// ---------------------------------------------------------------------------------------
// WRITING ONE EPISODE
// ---------------------------------------------------------------------------------------
// Renders, into a caller buffer:
//
//   \n---\n\n@LAT103LON<ord> | created:<t> | updated:<t>\n\n**<title>**\n\n
//   ```ttdb-episode\nsource: <source>\nat: <at>\n[said: ...\n][percept: ...\n]```\n
//
// `finish()` returns the record length, or 0 if ANY part overflowed — never a truncated
// record (the builder discipline every lane here follows). A percept whose lemma would
// break the grammar (contains `|` or a newline) is REJECTED and counted, not written: it
// would come back as a malformed line or, worse, as a different triple.
class EpisodeBuilder {
 public:
  EpisodeBuilder(char* buf, size_t cap);
  bool begin(int16_t ordinal, uint32_t t, const char* title, const char* source,
             const char* at, int16_t lane = SEMANTIC_EPISODE_LANE);
  bool said(uint32_t sentence, const char* text);
  bool percept(const Percept& p);
  size_t finish();

  uint16_t percepts() const { return percepts_; }
  uint16_t rejected() const { return rejected_; }
  bool overflowed() const { return overflow_; }

 private:
  bool put(const char* fmt, ...);
  char*    buf_;
  size_t   cap_, len_;
  uint16_t percepts_, rejected_;
  bool     overflow_, open_;
};

// ---------------------------------------------------------------------------------------
// READING THE LANE BACK
// ---------------------------------------------------------------------------------------
// Line-driven so the glue can stream the file without loading it (A32-RFC-0002). Feed
// every line of the records you want considered, in file order, then finish().
//
// TTG-0002 §5.1 "Only the lane is the owner's words": a `ttdb-episode` block on any OTHER
// latitude is still checked for malformed lines (counted in foreignMalformed()) but feeds
// NOTHING to the consolidator — not a percept, not a mention, not an episode count.
class EpisodeReader {
 public:
  explicit EpisodeReader(Consolidator& c, int16_t lane = SEMANTIC_EPISODE_LANE);

  // Which on-lane ordinals feed, and how each closes. Boot: (horizon+1 .. newest,
  // KEEPING). Fold: (oldest live .. new horizon, EVICTING). Ordinals outside the run are
  // counted in outside() and otherwise ignored.
  void select(int16_t from, int16_t through, Consolidator::Close close);
  void selectNone();

  void line(const char* l);
  void finish();

  uint32_t fed() const { return fed_; }
  uint32_t outside() const { return outside_; }
  uint32_t foreignBlocks() const { return foreign_blocks_; }
  uint32_t foreignMalformed() const { return foreign_malformed_; }
  uint32_t unclosed() const { return unclosed_; }

 private:
  void closeBlock();
  Consolidator& c_;
  int16_t lane_;
  int16_t from_, through_;
  bool    any_;
  Consolidator::Close close_;
  int16_t cur_lat_, cur_lon_;
  bool    have_rec_;
  enum Mode : uint8_t { OUT = 0, FEED, CHECK, SKIP } mode_;
  uint32_t fed_, outside_, foreign_blocks_, foreign_malformed_, unclosed_;
};

// ---------------------------------------------------------------------------------------
// THE CHECKPOINT (@LAT104)
// ---------------------------------------------------------------------------------------
//   ```ttdb-carried
//   through: <ordinal>
//   carried: <for> <against> <episodes> | <subject> | <vector> | <object>
//   ```
// ⚠ THE GRAVESTONE RULE, in three independent layers — any one would suffice, and this
// repo has paid for trusting one:
//   1. no line begins `percept:` or `belief:`;
//   2. a `carried:` line has FOUR pipe columns, and parsePerceptLine needs six — so even a
//      reader that dropped the key check would reject it as MAL_COLUMNS;
//   3. the block is on @LAT104 under a different tag, and EpisodeReader only feeds
//      `ttdb-episode` blocks on @LAT103.
// Returns bytes written, or 0 if it would not fit (see SEMANTIC_CARRIED_BUF).
size_t renderCheckpoint(const Consolidator& c, int16_t through, int16_t ordinal,
                        uint32_t t, char* out, size_t cap,
                        int16_t lane = SEMANTIC_CARRIED_LANE);

// The exact byte count renderCheckpoint would write (excluding the terminator), so the
// glue can allocate exactly instead of holding SEMANTIC_CARRIED_BUF static on a node
// whose maxalloc is single-digit KB. If the allocation fails the commit simply does not
// happen yet — which the checkpoint-as-commit-point order makes harmless.
size_t checkpointBytes(const Consolidator& c, int16_t through, int16_t ordinal, uint32_t t,
                       int16_t lane = SEMANTIC_CARRIED_LANE);

// ---------------------------------------------------------------------------------------
// THE LINK TIER AS EPISODES
// ---------------------------------------------------------------------------------------
// One scored PerceptLearn window = one episode. Each claim becomes one sentence:
//
//   said: <k> | <peer> <proto> <verdict> predicted:<p> observed:<o>
//   percept: <k> | <peer> | link_stable | <proto> | <+ - ?> | -
//
// met → `+`, violated → `-`, unobserved → `?` (HELD: the expectation was made and the
// world did not answer. Counted in `seen`, never believed — exactly what Rule 3 and
// consolidator_compare.py do with it, so the measured comparison carries over).
// The verdict numbering mirrors perceptlearn::Verdict; Semantic does not include
// PerceptLearn (one dependency direction), so the glue static_asserts they agree.
#define SEMANTIC_LINK_VECTOR "link_stable"
enum LinkVerdict : uint8_t { LINK_MET = 0, LINK_VIOLATED = 1, LINK_UNOBSERVED = 2 };

struct LinkClaim {
  uint32_t    peer;
  const char* proto;      // "espnow" / "ble" / "lora"
  uint8_t     verdict;    // LinkVerdict
  int16_t     predicted;
  int16_t     observed;
};

// Returns record bytes, or 0 if it did not fit (never truncated). `at` is the caller's
// stamp text (TimeStream's buildStamp today; TTG-0004 §4's `<pulse> ±<bound>` in C4).
size_t renderLinkEpisode(const LinkClaim* claims, int n, int16_t ordinal, uint32_t t,
                         const char* at, char* out, size_t cap);

class CheckpointReader {
 public:
  // Honours ONLY the record at (lane, ordinal) — see ONLY THE NEWEST CHECKPOINT above.
  CheckpointReader(Consolidator& c, int16_t ordinal, int16_t lane = SEMANTIC_CARRIED_LANE);
  void line(const char* l);

  bool     found() const { return have_through_; }
  int16_t  through() const { return through_; }
  uint32_t seeded() const { return seeded_; }
  uint32_t malformed() const { return malformed_; }

 private:
  Consolidator& c_;
  int16_t lane_, ordinal_;
  bool    in_rec_, in_block_, have_through_;
  int16_t through_;
  uint32_t seeded_, malformed_;
};

// ---------------------------------------------------------------------------------------
// THE RING — what is live, what to fold, what may be cut. Pure bookkeeping, no I/O.
// ---------------------------------------------------------------------------------------
class EpisodeRing {
 public:
  EpisodeRing();
  void begin(uint16_t capacity = SEMANTIC_RING_CAPACITY,
             uint16_t batch = SEMANTIC_EVICT_BATCH);

  // --- scan: call resetScan(), then observe() for EVERY indexed record IN FILE ORDER.
  // Repeat after any rewrite (Ttdb re-indexes). Horizons survive a rescan.
  void resetScan();
  void observe(int16_t lat, int16_t lon);

  bool    hasCheckpoint() const { return ck_count_ > 0; }
  int16_t checkpointOrdinal() const { return ck_newest_; }   // the ONLY one to read
  uint16_t checkpointsPresent() const { return ck_count_; }
  uint16_t present() const { return ep_count_; }             // episode records on flash

  // After reading the newest checkpoint. Sets BOTH horizons: at boot RAM equals flash.
  void setHorizon(int16_t through);
  bool hasHorizon() const { return has_flash_h_; }
  int16_t flashHorizon() const { return flash_h_; }

  // The run of episodes that feed the consolidator at boot. false = nothing live.
  bool liveRun(int16_t& from, int16_t& through) const;
  uint16_t live() const;                                      // newer than the RAM horizon

  int16_t nextOrdinal() const;
  int16_t nextCheckpointOrdinal() const;
  void appended(int16_t ordinal);                             // after appendRecord succeeded
  void checkpointAppended(int16_t ordinal);                   // after the COMMIT succeeded

  // 1. FOLD — live > capacity. Replay [from..through] EVICTING, then folded(through).
  bool foldDue(int16_t& from, int16_t& through) const;
  void folded(int16_t through);
  // 2. COMMIT — the RAM horizon is ahead of flash. Render a checkpoint with
  //    through = ramHorizon(), append it, then checkpointAppended().
  bool commitDue() const;
  int16_t ramHorizon() const { return ram_h_; }
  // 3. CUT — what may be deleted now. Uses the FLASH horizon only, never RAM. Up to four
  //    cuts (each lane's range may wrap). Returns the count; 0 = nothing to cut.
  uint8_t cuts(Cut* out, uint8_t max) const;
  // How many records those cuts would remove: the glue cuts once this reaches
  // SEMANTIC_CUT_SLACK (and always at boot), not on every fold.
  uint16_t dead() const;

  uint32_t folds() const { return folds_; }                   // episodes folded, lifetime

 private:
  uint16_t capacity_, batch_;
  // scan
  bool    ep_any_;
  int16_t ep_oldest_, ep_newest_;
  uint16_t ep_count_;
  int16_t ck_oldest_, ck_newest_;
  uint16_t ck_count_;
  // horizons
  bool    has_flash_h_, has_ram_h_;
  int16_t flash_h_, ram_h_;
  uint32_t folds_;
  uint16_t liveFrom(int16_t& from) const;
};

}  // namespace semantic

#endif  // SEMANTIC_EPISODE_H
