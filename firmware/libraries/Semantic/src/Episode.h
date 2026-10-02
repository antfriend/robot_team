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
// 📎 Since per-tier quotas (below) the modulus a ring actually uses is its tier band,
// SEMANTIC_TIER_SPAN = 8192 — so the link tier wraps in ~5.7 days, not ~23.
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

// ---------------------------------------------------------------------------
// ⚠ PER-TIER QUOTAS: ONE LANE, ONE BAND OF ORDINALS PER TIER (2026-10-01)
// ---------------------------------------------------------------------------
// Every percept tier writes into this ONE lane, but each evicts only its OWN oldest: the
// link tier at ~60 windows/h must not push out the entity tier's 6/h, or
// `entity-survey`'s 8 h of unfolded windows stops being possible. Oldest-first is kept
// PER TIER by giving tier k the LON band [k·SPAN, (k+1)·SPAN). Within a band the run is
// still contiguous and the horizon still one integer, so everything above holds with
// SEMANTIC_ORDINAL_MOD replaced by SEMANTIC_TIER_SPAN (a wrap every ~5.7 days at one link
// episode a minute; the retained window is ≤ 96, far inside 8192).
// A checkpoint carries one `through:` line per tier that has folded, and the TIER IS READ
// OFF THE VALUE — so a pre-band checkpoint's single `through:` is the link tier's, exactly
// as the Cardputer's existing episodes (LON 0..~190) already sit in the link band.
#define SEMANTIC_TIERS 4
#define SEMANTIC_TIER_SPAN (SEMANTIC_ORDINAL_MOD / SEMANTIC_TIERS)   // 8192
enum Tier : uint8_t { TIER_LINK = 0, TIER_ENTITY = 1, TIER_MOTION = 2, TIER_ACOUSTIC = 3 };

// Episodes retained live on flash, PER TIER. Their sum is checked against the index
// budget where the store is opened (EpisodeNode.h), because that is the arithmetic the
// old per-lane caps got wrong: four lanes of 48 + 24 + 16 + 32 SUMMED past 288.
// ⚠ Link stays at 48 while @LAT97 still exists beside it — the Cardputer's index is at
// 234/288 today; it rises when the old lane is retired, not before.
#ifndef SEMANTIC_QUOTA_LINK
#define SEMANTIC_QUOTA_LINK 48
#endif
#ifndef SEMANTIC_QUOTA_ENTITY
#define SEMANTIC_QUOTA_ENTITY 48     // = entity-survey's 8 h at MAX_RUN=1 (one per 600 s)
#endif
#ifndef SEMANTIC_QUOTA_MOTION
#define SEMANTIC_QUOTA_MOTION 24
#endif
#ifndef SEMANTIC_QUOTA_ACOUSTIC
#define SEMANTIC_QUOTA_ACOUSTIC 24
#endif
// One ring's capacity when a ring is used alone (the tests, and a whole-lane ring).
#ifndef SEMANTIC_RING_CAPACITY
#define SEMANTIC_RING_CAPACITY SEMANTIC_QUOTA_LINK
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
// Four numbers since 2026-10-01 (for, against, episodes, seen), each ≤ 12 chars.
#define SEMANTIC_CARRIED_LINE_MAX (16 + 4 * 12 + 3 * (SEMANTIC_LEMMA_MAX + 3))
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

// The same three, inside one band of LONs. The whole-lane helpers above are the band
// {0, SEMANTIC_ORDINAL_MOD}. `bandInRun` is false for an `x` outside the band.
struct Band {
  int16_t  base;
  uint16_t span;
};
inline Band wholeLane() { return Band{0, (uint16_t)SEMANTIC_ORDINAL_MOD}; }
inline Band tierBand(uint8_t tier) {
  return Band{(int16_t)(tier * SEMANTIC_TIER_SPAN), (uint16_t)SEMANTIC_TIER_SPAN};
}
// The tier a LON belongs to; -1 for a negative LON (not an ordinal this lane writes).
inline int tierOf(int16_t lon) { return lon < 0 ? -1 : lon / SEMANTIC_TIER_SPAN; }
inline bool inBand(int16_t x, Band b) {
  return (int32_t)x >= b.base && (int32_t)x < (int32_t)b.base + b.span;
}
int16_t bandAdd(int16_t x, int32_t d, Band b);
uint16_t bandDistance(int16_t from, int16_t to, Band b);
bool bandInRun(int16_t x, int16_t from, int16_t through, Band b);

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
  size_t length() const { return len_; }               // bytes written so far

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
  // `band`: the run is read inside that tier's band; an ordinal outside it is outside().
  void select(int16_t from, int16_t through, Consolidator::Close close,
              Band band = wholeLane());
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
  Band    band_;
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
//   through: <ordinal>          ← one line per tier that has folded; the tier is the
//   through: <ordinal>            band the value falls in (tierOf), so lines are unordered
//   carried: <for> <against> <episodes> <seen> | <subject> | <vector> | <object>
//   ```
// ⚠ ONLY THE NEWEST CHECKPOINT IS READ, so every checkpoint must restate EVERY tier's
// horizon, including tiers that did not fold this time. A tier missing from the newest
// checkpoint reads as "never folded", so any of its folded episodes not yet CUT would be
// replayed KEEPING on top of the carried tallies that already hold them — a double count,
// the one thing the commit order exists to rule out. EpisodeTiers::horizons() is the one
// place that list is built, and test_episode's multi-tier protocol reboots after every step.
// ⚠ THE GRAVESTONE RULE, in three independent layers — any one would suffice, and this
// repo has paid for trusting one:
//   1. no line begins `percept:` or `belief:`;
//   2. a `carried:` line has FOUR pipe columns, and parsePerceptLine needs six — so even a
//      reader that dropped the key check would reject it as MAL_COLUMNS;
//   3. the block is on @LAT104 under a different tag, and EpisodeReader only feeds
//      `ttdb-episode` blocks on @LAT103.
// Returns bytes written, or 0 if it would not fit (see SEMANTIC_CARRIED_BUF).
// `throughs`: one horizon per folded tier (1..SEMANTIC_TIERS, at most one per band).
size_t renderCheckpoint(const Consolidator& c, const int16_t* throughs, uint8_t n,
                        int16_t ordinal, uint32_t t, char* out, size_t cap,
                        int16_t lane = SEMANTIC_CARRIED_LANE);
// One horizon (a single tier, or a whole-lane ring).
inline size_t renderCheckpoint(const Consolidator& c, int16_t through, int16_t ordinal,
                               uint32_t t, char* out, size_t cap,
                               int16_t lane = SEMANTIC_CARRIED_LANE) {
  return renderCheckpoint(c, &through, 1, ordinal, t, out, cap, lane);
}

// The exact byte count renderCheckpoint would write (excluding the terminator), so the
// glue can allocate exactly instead of holding SEMANTIC_CARRIED_BUF static on a node
// whose maxalloc is single-digit KB. If the allocation fails the commit simply does not
// happen yet — which the checkpoint-as-commit-point order makes harmless.
size_t checkpointBytes(const Consolidator& c, const int16_t* throughs, uint8_t n,
                       int16_t ordinal, uint32_t t, int16_t lane = SEMANTIC_CARRIED_LANE);
inline size_t checkpointBytes(const Consolidator& c, int16_t through, int16_t ordinal,
                              uint32_t t, int16_t lane = SEMANTIC_CARRIED_LANE) {
  return checkpointBytes(c, &through, 1, ordinal, t, lane);
}

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

// ---------------------------------------------------------------------------------------
// A SAMPLER'S OWN RECORD AS AN EPISODE (the entity tier, 2026-10-01)
// ---------------------------------------------------------------------------------------
// Wraps every `**…` line of an already-rendered record body as one `said:` sentence, in
// order, inside a `ttdb-episode` block. Every other line (the old header, `---`, blanks)
// is dropped. That is how a tier moves into this lane WITHOUT this library learning its
// grammar: EntityPercept keeps rendering `**ENTWIN**`/`**ENTITY**`/`**RUN**`/`**CORE**`/
// `**COVERED**`/`**COVERED-ENTITY**`, and companion.py reads those same lines back out of
// the `said:` column with the same regexes.
//
// ⚠ IT WRITES NO `percept:` LINE, so the episode feeds the consolidator nothing and its
// fold carries nothing. That is a decision, not an omission: the entity tier's only
// consumer is the laptop's Jaccard union, and a per-BSSID term would spend the 32-slot
// TERM table on APs, reclaiming link beliefs to do it. A forgotten entity episode is
// therefore GONE — exactly as a pruned @LAT96 window was — but by ring, never by refusal.
// Returns 0 (never a truncated record) when anything does not fit, when a `**` line holds
// a `|` (it would read back as a different sentence), or when one is too long to come
// back through the on-device line reader (SEMANTIC_LINE_MAX).
size_t renderSaidEpisode(const char* body, size_t n, int16_t ordinal, uint32_t t,
                         const char* title, const char* source, const char* at,
                         char* out, size_t cap);
// ⚠ THE SAME WRAP IN ONE BUFFER, because two static buffers boot-looped the Cardputer
// (2026-10-01): +5632 B of .bss starved the BLE scanner's allocations at boot on a board
// that runs with ~26 KB free. The record (m bytes at buf[0]) is moved to the TAIL and the
// episode is written forward from the head; every write is checked against the first
// unread byte, so a record too big to wrap in `cap` is REFUSED (0), never corrupted.
size_t renderSaidEpisodeInPlace(char* buf, size_t cap, size_t m, int16_t ordinal,
                                uint32_t t, const char* title, const char* source,
                                const char* at);

// ---------------------------------------------------------------------------------------
// THE LINK WINDOW AS AN EPISODE (2026-10-02) — the last tier out of a capped lane
// ---------------------------------------------------------------------------------------
// ONE link-band episode per LinkPercept window, scored or not. It is the @LAT97 record and
// the scored claims of the SAME window in one block, so the window has ONE name that both
// the laptop (fleetmap's RSSI) and PerceptLearn's outcome (`derived_from@`/`observed_in:`)
// cite:
//
//   said: 1 | **LINKWIN** t_ms:… stream:0x… wall:… window_ms:…   ← LinkPercept's own lines,
//   said: 2 | **LINK** peer:0x… proto:espnow n:… rssi_min:…        wrapped as renderSaidEpisode
//   …
//   said: k+1 | 0x… espnow met predicted:-35 observed:-36          ← each scored claim, exactly
//   percept: k+1 | 0x… | link_stable | espnow | + | -                 as renderLinkEpisode writes it
//
// Why one block and not two: tier bands are a fixed four in an int16 LON, so there is no
// fifth band for raw RSSI windows — and two records per minute would halve the link tier's
// retained history for no gain, since both describe one window. An UNSCORED window (no
// expectation armed — the node was moving, or just booted) still writes its `said:` lines
// and simply carries no `percept:` line: the consolidator counts nothing for it, exactly as
// it counted nothing when the window was a @LAT97 record.
// ⚠ All or nothing: a claim that does not fit refuses the whole episode (see the .cpp).
// Pre-2026-10-02 link episodes (claims only, title "link window", source perceptlearn) stay
// readable: the consolidator reads percept: lines alone, and companion.py skips a link
// episode with no **LINKWIN** sentence as "not a window".
#define SEMANTIC_LINK_WINDOW_TITLE "link window"
#define SEMANTIC_LINK_WINDOW_SOURCE "linkpercept"
// Worst case: LINKPERCEPT_MAX_PEERS maximal **LINK** lines + 8 maximal claims + header —
// measured 2064 B (2026-10-02) from an 847 B LinkPercept record.
// Pinned by test_episode against a REAL maximal LinkPercept record, and asserted ≤ the one
// scratch buffer (SEMANTIC_ENTITY_EPISODE_BUF) the Cardputer renders every tier into.
#define SEMANTIC_LINK_WINDOW_EPISODE_BUF 2560
size_t renderLinkWindowEpisode(const char* body, size_t m, const LinkClaim* claims, int n,
                               int16_t ordinal, uint32_t t, const char* at, char* out,
                               size_t cap);
// The same in ONE buffer: LinkPercept's record (m bytes at buf[0]) is moved to the tail and
// wrapped forward from the head, as renderSaidEpisodeInPlace. m == 0 = claims only.
size_t renderLinkWindowEpisodeInPlace(char* buf, size_t cap, size_t m,
                                      const LinkClaim* claims, int n, int16_t ordinal,
                                      uint32_t t, const char* at);

// One entity window as an episode. Worst case = EntityPercept's worst record (2322 B, its
// ENTITYPERCEPT_RECORD_BUF is 2560) + ~11 B of `said: k | ` on each of its ≤ 32 body
// lines + the episode header. Pinned both ways by test_episode against a REAL maximal
// EntityPercept record, not an estimate.
#ifndef SEMANTIC_ENTITY_EPISODE_BUF
#define SEMANTIC_ENTITY_EPISODE_BUF 3072
#endif

class CheckpointReader {
 public:
  // Honours ONLY the record at (lane, ordinal) — see ONLY THE NEWEST CHECKPOINT above.
  CheckpointReader(Consolidator& c, int16_t ordinal, int16_t lane = SEMANTIC_CARRIED_LANE);
  void line(const char* l);

  bool     found() const { return have_mask_ != 0; }            // any horizon at all
  bool     has(uint8_t tier) const { return tier < SEMANTIC_TIERS && (have_mask_ >> tier) & 1; }
  int16_t  through(uint8_t tier) const { return tier < SEMANTIC_TIERS ? through_[tier] : -1; }
  int16_t  through() const { return through_[TIER_LINK]; }    // the single-ring form
  uint32_t seeded() const { return seeded_; }
  // A second `through:` in one band is malformed and the FIRST is kept: two horizons for
  // one tier is a checkpoint nothing here writes, so neither is more believable.
  uint32_t malformed() const { return malformed_; }

 private:
  Consolidator& c_;
  int16_t lane_, ordinal_;
  bool    in_rec_, in_block_;
  uint8_t have_mask_;
  int16_t through_[SEMANTIC_TIERS];
  uint32_t seeded_, malformed_;
};

// ---------------------------------------------------------------------------------------
// THE RING — what is live, what to fold, what may be cut. Pure bookkeeping, no I/O.
// ---------------------------------------------------------------------------------------
class EpisodeRing {
 public:
  EpisodeRing();
  // `band`: the LONs this ring owns (a tier's band, or the whole lane). Episodes outside it
  // are not observed. `owns_checkpoints`: whether @LAT104 records are tracked (and cut) by
  // this ring — exactly one ring of a set does it (EpisodeTiers: the link ring).
  void begin(uint16_t capacity = SEMANTIC_RING_CAPACITY,
             uint16_t batch = SEMANTIC_EVICT_BATCH, Band band = wholeLane(),
             bool owns_checkpoints = true);

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

  // Is this LON in [from..through] within this ring's band? (Never the whole-lane test:
  // a run that wraps inside a band would read as most of the lane.)
  bool inRun(int16_t lon, int16_t from, int16_t through) const {
    return bandInRun(lon, from, through, band_);
  }
  Band band() const { return band_; }
  uint16_t capacity() const { return capacity_; }
  bool hasRamHorizon() const { return has_ram_h_; }

 private:
  uint16_t capacity_, batch_;
  Band     band_;
  bool     owns_ck_;
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

// ---------------------------------------------------------------------------------------
// THE TIERS — one EpisodeRing per tier band, one checkpoint for all of them
// ---------------------------------------------------------------------------------------
// Pure bookkeeping, the same contract as EpisodeRing, routed by tierOf(lon). The glue and
// the native test both drive THIS, so the multi-tier order of operations is tested rather
// than re-implemented. The link ring owns the @LAT104 checkpoints.
class EpisodeTiers {
 public:
  EpisodeTiers();
  // quotas[t] = tier t's capacity. Default: SEMANTIC_QUOTA_*.
  void begin(const uint16_t* quotas = 0, uint16_t batch = SEMANTIC_EVICT_BATCH);

  void resetScan();
  void observe(int16_t lat, int16_t lon);

  bool    hasCheckpoint() const { return r_[TIER_LINK].hasCheckpoint(); }
  int16_t checkpointOrdinal() const { return r_[TIER_LINK].checkpointOrdinal(); }
  // After reading the newest checkpoint: each tier it names gets its horizon.
  void applyCheckpoint(const CheckpointReader& cr);

  int16_t nextOrdinal(uint8_t tier) const;
  void appended(int16_t ordinal);          // routed by tierOf(ordinal)

  // 1. FOLD, per tier: the first tier with a fold due. false = none.
  bool foldDue(uint8_t& tier, int16_t& from, int16_t& through) const;
  void folded(uint8_t tier, int16_t through);
  // 2. COMMIT: any tier ahead of flash. horizons() fills EVERY tier's RAM horizon (see
  //    ONLY THE NEWEST CHECKPOINT IS READ) and returns how many.
  bool commitDue() const;
  uint8_t horizons(int16_t* out) const;
  int16_t nextCheckpointOrdinal() const { return r_[TIER_LINK].nextCheckpointOrdinal(); }
  void checkpointAppended(int16_t ordinal);
  // 3. CUT: the union of every tier's cuts (≤ 2 each, + 2 for the checkpoints).
  uint8_t cuts(Cut* out, uint8_t max) const;
  uint16_t dead() const;

  uint16_t live() const;
  uint16_t present() const;
  uint32_t folds() const;
  uint16_t capacity() const;                // Σ quotas — the tier set's index footprint
  const EpisodeRing& ring(uint8_t tier) const { return r_[tier < SEMANTIC_TIERS ? tier : 0]; }

 private:
  EpisodeRing r_[SEMANTIC_TIERS];
};
#define SEMANTIC_TIER_CUTS_MAX (2 * SEMANTIC_TIERS + 2)

}  // namespace semantic

#endif  // SEMANTIC_EPISODE_H
