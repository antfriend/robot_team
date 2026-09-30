// Semantic.h — TTG-RFC-0002/0003 for a store that must never refuse a write.
//
// ACT-III.md Phase C, tiers TERM/BELIEF and EPISODE. This is the replacement for
// PerceptLearn's Rule 3 as the DEFAULT consolidator; Rule 3 stays beside it as a
// selectable second one, because its +2/-16 asymmetry is an unrun experiment and
// deleting it would end that experiment with no result (ACT-III §C3).
//
// ---------------------------------------------------------------------------
// WHAT TTG-RFC-0003 §2 ACTUALLY SAYS, AND WHY IT IS THE POINT
// ---------------------------------------------------------------------------
// For each triple (subject, vector, object) over all non-comention, non-held percepts
// of the episodes on the episode lane:
//
//   per episode:  plus  = the LARGEST weight of its `+` percepts
//                 minus = the LARGEST weight of its `-` percepts
//                 (weight = weight_partial for quantifier `~`, else 1)
//   for     = Σ plus    over episodes
//   against = Σ minus   over episodes
//   polarity = `+` if for > against, `-` if against > for, `?` otherwise
//   conf     = round(255 × (max(for,against) + prior_for)
//                        ÷ (for + against + prior_for + prior_against))
//   decided ⇔ polarity ≠ `?` AND conf > belief_conf_threshold
//
// The load-bearing word is **Σ**. A sum is commutative, so the result cannot depend on
// the order the episodes arrive in — which is exactly the property PerceptLearn's
// sequential fold cannot have, and the reason TTG-0003 exists. The per-episode max is
// what keeps one talkative episode from outvoting nine quiet ones: an episode gets one
// vote each way no matter how many times it says the same thing.
//
// ⚠ MEASURED DIFFERENCE FROM RULE 3, on this fleet's own beliefs (2026-09-30, the
// Cardputer's eight @LAT91 records, reproduced 8/8 exactly):
// Rule 3 is `clamp(128 + 2·met − 16·violated, 0, 255)`, so its conf grows with the
// AMOUNT of evidence; TTG-0003's grows with the CONSISTENCY of it. On real data that
// inverts a ranking — met:47/violated:2 (96% consistent) scored 190 under Rule 3 while
// met:11/violated:0 (100% consistent) scored 150, whereas counting gives 240 and 235.
// Since EPS = sal × (255 − conf) / 255, the choice of consolidator changes what the
// fleet ATTENDS to, what eviction drops, and what the snake eats. That is why C3 keeps
// both and compares them rather than assuming.
//
// ---------------------------------------------------------------------------
// WHY IT STREAMS
// ---------------------------------------------------------------------------
// A32-RFC-0002 forbids loading the TTDB whole — the firmware seeks and reads on demand.
// So this is not `consolidate(episodes) → beliefs` over an array; it is a fold driven by
// the caller:
//
//     beginEpisode();  percept(p); percept(p); ...  endEpisode();   // × N episodes
//
// and the belief table is complete when the last episode closes. Two things fall out of
// that shape rather than being designed in:
//
//   1. RAM is bounded by the VOCABULARY (distinct triples), not by the episode count.
//      That is ACT-III §C2b's claim for this tier, made structural.
//   2. Fold-before-forget becomes a MOVE (see below), not a recompute.
//
// ---------------------------------------------------------------------------
// FOLD BEFORE FORGET — the mechanism, and why it is lossless by construction
// ---------------------------------------------------------------------------
// When the episode ring is full, the oldest episode is folded into the beliefs it
// supports BEFORE its record is dropped (ACT-III §C2c). Here that is:
//
//     beginEpisode();  <replay the dying episode's percepts>;  endEpisode(EVICTING);
//
// `endEpisode(EVICTING)` SUBTRACTS the episode's per-episode max from `live_` and ADDS
// it to `carried_`. The total (`live_ + carried_`) is therefore **invariant across
// eviction** — not approximately, not for-this-consumer, but arithmetically, because it
// is the same quantity moved between two accumulators. TTG-RFC-0002 §5.1's rule that
// *an episode MUST NOT be modified after it is written* is what makes the replayed max
// equal the max that was originally added, so this is sound rather than merely plausible.
//
// The split matters on reboot and is the whole reason `carried_` is separate:
//
//     total = carried_  (from episodes no longer on flash — re-seeded from the store)
//           + live_     (recomputed by streaming the episodes still on flash)
//
// Seeding from a tally that already included the retained episodes would double-count
// them. This is also the honest form of ACT-III §C2d's declared divergence from
// TTG-0003 §2: recomputability holds over the retained window, and beyond it the
// carried tally is a lossless summary *for the consolidator*, which is its only reader.
// What is genuinely lost is provenance — which sentence taught it — and `carriedFor()`
// being non-zero is exactly the flag that says so.
//
// ⚠ THE GRAVESTONE TRAP, ALREADY PAID FOR ONCE. @LAT92's boundary rule says a boundary
// carrying `**OBSERVED** peer:0x` or `**COVERED** peer:0x` gets folded as testimony the
// next time the lane is read — the node re-learns from its own headstone, forever, and
// each reboot doubles it. So the carried tally is serialised as its own `carried:` line
// and MUST NEVER be written as a `belief:` line or as a `percept:` line. A carried tally
// is data ABOUT evidence, never evidence. `SEMANTIC_CARRIED_KEY` and
// `SEMANTIC_BELIEF_KEY` are deliberately distinct strings, neither a prefix of the
// other, and neither contains `percept:`.
//
// ---------------------------------------------------------------------------
// WHY THE ARITHMETIC IS INTEGER HALVES
// ---------------------------------------------------------------------------
// `weight_partial` is 0.5 and nothing else fractional appears, so every weight is an
// exact multiple of one half. Counting in halves (2 = 1.0, 1 = 0.5) keeps the whole
// consolidator in integers. That is not a micro-optimisation: C3's gate is that belief
// lines reproduce **byte-for-byte**, and a float `conf` would make that gate depend on
// the FPU and the rounding mode of whatever host built the test. Priors are scaled the
// same way (`prior_for 1` = 2 halves), so the conf formula is one integer expression.
//
// ---------------------------------------------------------------------------
// WHY A FULL TABLE STILL ACCEPTS THE WRITE
// ---------------------------------------------------------------------------
// ACT-III §C2b argues this tier "structurally cannot grow past its own vocabulary", and
// that is true of the tier — but a fixed table can still meet a vocabulary larger than
// itself, and the one thing this phase may not do is refuse. So a full table reclaims
// the **lowest-EPS** entry: EPS = sal × (255 − conf) / 255, the same key `Social`'s
// reclaim-lowest uses and the same one the EPS arbiter and the snake read. One value
// function, three consumers. The store forgets what it neither relies on (low sal) nor
// doubts (high conf), which is the only forgetting that is defensible without an
// operator. Every reclamation increments `reclaimed()` so it is VISIBLE — "forgetting is
// continuous, principled, and visible" is the goal, and an invisible reclamation would
// fail the third of those.
//
// ⚠ A reclamation writes NO lane-generation boundary, and that is not an omission.
// Under KEY naming there is nothing to re-point: a term record is addressed by its
// lemma, not by an ordinal, so no citation breaks when one is dropped. `Social.h` says
// the same thing about @LAT101. Ordinal/EVENT naming is what forces prune boundaries;
// KEY naming is what makes reclamation free.
//
// ---------------------------------------------------------------------------
// WHAT THIS FILE DOES NOT DO
// ---------------------------------------------------------------------------
// - Term record PLACEMENT (TTG-0002 §6: FNV-1a coordinate hashing, `adjacent` offsets,
//   `southeast_step` collisions). Placement is a separate concern from counting and is
//   the next increment; nothing here needs a coordinate to be correct.
// - Reading English. TTG-0002 §3's clause grammar is for an agent reading prose; this
//   fleet's episodes are sensor windows, and its samplers emit `percept:` lines directly
//   (see `percept()` and ACT-III §C2: the four tiers keep their samplers and stop owning
//   a record grammar). `parsePerceptLine` is therefore the whole of the reading side.
// - The episode ring itself. This library is the consolidator the ring calls into.
#ifndef SEMANTIC_H
#define SEMANTIC_H

#include <stddef.h>
#include <stdint.h>

namespace semantic {

// Longest lemma held in a triple. Peer ids render as `0x00000200` (10) and protocol
// names as `espnow` (6); 24 leaves room for real lemmas without making the table huge.
#ifndef SEMANTIC_LEMMA_MAX
#define SEMANTIC_LEMMA_MAX 24
#endif

// Distinct (subject, vector, object) triples held at once. The Cardputer formed 8 in two
// months of runtime; 32 is headroom, not a guess at a limit. Overridable as a build
// property so a test can drive reclamation in a fixture instead of at record 33 — the
// same trick `ttdb_index` uses with TTDB_MAX_RECORDS.
#ifndef SEMANTIC_MAX_TERMS
#define SEMANTIC_MAX_TERMS 32
#endif

// A `percept:` line, rendered or parsed. TTG-0002 §4's longest form plus slack.
#ifndef SEMANTIC_LINE_MAX
#define SEMANTIC_LINE_MAX 200
#endif

// ⚠ These two keys must stay distinct, and neither may be a prefix of the other or
// contain "percept:". See THE GRAVESTONE TRAP above.
#define SEMANTIC_BELIEF_KEY  "belief:"
#define SEMANTIC_CARRIED_KEY "carried:"

// TTG-RFC-0002 §4 column 5. `?` and `?-` are HELD: said but not asserted, never believed.
enum Polarity : uint8_t { POL_PLUS = 0, POL_MINUS = 1, POL_HELD = 2, POL_HELD_MINUS = 3 };

// TTG-RFC-0002 §4 column 6. `~` = quant_some (weight_partial); `*` = quant_all/none/
// generic_det (full weight); `-` = none (full weight).
enum Quant : uint8_t { Q_NONE = 0, Q_SOME = 1, Q_ALL = 2 };

// Why a percept line was rejected. TTG-0002 §5.1: a consumer MUST skip, count AND
// REPORT malformed lines — so the reason is part of the API, not a log string.
enum Malformed : uint8_t {
  MAL_OK = 0,
  MAL_COLUMNS,      // fewer than six columns
  MAL_SENTENCE,     // non-integer sentence
  MAL_EMPTY,        // empty subject, vector or object
  MAL_POLARITY,     // polarity not one of + - ? ?-
  MAL_QUANT,        // quantifier not one of * ~ -
  MAL_READING,      // 7th column not one lowercase letter, or on a percept that is not held
  MAL_TOO_LONG      // line longer than SEMANTIC_LINE_MAX
};

struct Percept {
  uint32_t sentence;
  char     subject[SEMANTIC_LEMMA_MAX];
  char     vec[SEMANTIC_LEMMA_MAX];      // `vector` is too close to std::vector to read well
  char     object[SEMANTIC_LEMMA_MAX];   // "-" when the clause is intransitive
  Polarity pol;
  Quant    quant;
  char     reading;                      // 0, or 'a'..'z' for a two-reading held percept
};

// TTG-RFC-0003 §5 constants, as a `numbers` block rather than #defines (ACT-III §C3).
// Weights are HALVES: prior_for 1 → 2. weight_partial is not configurable away from one
// half because the halves representation encodes it; a different partial weight needs a
// different denominator and should be a declared change, not a silent one.
struct Numbers {
  uint16_t prior_for_halves;        // default 2  (= 1)
  uint16_t prior_against_halves;    // default 2  (= 1)
  uint8_t  belief_conf_threshold;   // default 128
  Numbers();
};

// One (subject, vector, object) with its two sums, split by provenance.
struct Term {
  char     subject[SEMANTIC_LEMMA_MAX];
  char     vec[SEMANTIC_LEMMA_MAX];
  char     object[SEMANTIC_LEMMA_MAX];
  uint32_t live_for, live_against;        // from episodes still on flash — recomputable
  uint32_t carried_for, carried_against;  // from episodes evicted — NOT recomputable
  uint32_t seen;                          // every matching percept, incl. held/mentions
  uint32_t asked;                         // queries that found purchase (TTG-0002 §5.2)
  uint16_t rev;                           // += 1 when the belief line changes
  uint16_t episodes;                      // episodes that contributed either way
  bool     used;

  uint32_t totalFor()     const { return live_for + carried_for; }
  uint32_t totalAgainst() const { return live_against + carried_against; }
};

class Consolidator {
 public:
  Consolidator();

  void begin();                      // reference Numbers
  void begin(const Numbers& n);
  void reset();                      // drop every term; keeps Numbers

  // --- the stream -----------------------------------------------------------------
  void beginEpisode();
  // Parse one store line and accumulate it. A malformed line is SKIPPED, COUNTED and
  // reported (TTG-0002 §5.1) and never aborts the episode: one unreadable percept must
  // not cost the other nine in the same window.
  bool feedLine(const char* line);
  // Accumulates into the current episode. Returns false and bumps skipped() for a
  // percept that is well-formed but NOT BELIEVED (held, or a mention with subject or
  // vector `-`, or a comention) — those still count towards `seen`.
  bool percept(const Percept& p);
  enum Close : uint8_t { KEEPING = 0, EVICTING = 1 };
  // KEEPING  — add this episode's per-episode max to `live_`.
  // EVICTING — MOVE it from `live_` to `carried_`; the total is unchanged. See
  //            FOLD BEFORE FORGET. Replay exactly the percepts the dying episode holds.
  void endEpisode(Close close = KEEPING);

  // --- reading the result ---------------------------------------------------------
  size_t      termCount() const;
  const Term* term(size_t i) const;              // insertion order = order of first percept
  const Term* find(const char* subject, const char* vec, const char* object) const;

  // TTG-RFC-0003 §2, over totalFor()/totalAgainst().
  char    polarity(const Term& t) const;         // '+', '-' or '?'
  uint8_t conf(const Term& t) const;             // 0..255, integer round-half-up
  bool    decided(const Term& t) const;
  // EPS = sal × (255 − conf) / 255, TTDB-RFC-0005 §3.3. sal = min(255, seen + asked)
  // per TTG-0002 §5.2. This is the eviction key, the arbiter's key and the snake's key.
  uint8_t sal(const Term& t) const;
  uint8_t eps(const Term& t) const;

  // --- serialising ----------------------------------------------------------------
  // `belief: <vector> | <object or -> | <+ - ?> | <for> <against> | <conf>` (TTG-0002
  // §5.2). for/against render as an integer, or N.5 for a half. Returns bytes written,
  // or 0 if it would not fit — never a truncated line (four undersized buffers in this
  // repo's history, so builders here write nothing rather than something).
  size_t beliefLine(const Term& t, char* out, size_t cap) const;
  // `carried: <for> <against> <episodes>`. Written only when carried_* is non-zero;
  // returns 0 otherwise, which is also how a reader tells a fully-recomputable term
  // from one whose provenance is partly gone.
  size_t carriedLine(const Term& t, char* out, size_t cap) const;
  // Re-seed `carried_` on boot from a `carried:` line. Creates the term if absent.
  bool   seedCarried(const char* subject, const char* vec, const char* object,
                     const char* carried_line);

  // --- what it refused, dropped and reclaimed ---------------------------------------
  uint32_t malformedCount() const;               // TTG-0002 §5.1's MUST-report
  Malformed lastMalformed() const;
  uint32_t skipped() const;                      // well-formed but not believed
  uint32_t reclaimed() const;                    // lowest-EPS entries dropped, table full
  // A write is NEVER refused (ACT-III §C0). This exists so that claim is testable from
  // outside rather than asserted: it must stay 0 for the life of the process.
  uint32_t refused() const;
  // Non-zero means an EVICTING replay did not match what was originally counted —
  // impossible while episodes are immutable, so it indicts the caller, not the store.
  // Exposed because this repo's expensive defects were all silent ones.
  uint32_t foldUnderflow() const;

  // --- PerceptLearn Rule 3, kept as a selectable second consolidator (ACT-III §C3) ---
  // clamp(128 + 2·met − 16·violated, 0, 255). Verified 8/8 against the Cardputer's live
  // beliefs 2026-09-30. ⚠ Valid ONLY over the retained window: the fold is sequential and
  // order-dependent, so a carried tally cannot be replayed to check it. Any comparison
  // against conf() must say so or it compares an exact number with an approximate one.
  static uint8_t rule3Conf(uint32_t met, uint32_t violated);

  // Parse one `percept:` line (with or without the `percept:` prefix). On failure sets
  // `why` and returns false; the caller counts it via the Consolidator, or directly.
  static bool parsePerceptLine(const char* line, Percept& out, Malformed& why);
  static size_t renderPerceptLine(const Percept& p, char* out, size_t cap);

  // Vector naming a comention pair (TTG-0002 §4) — never believed. Settable because the
  // role name is a grammar key, not a constant of the world.
  void setComentionRole(const char* role);

 private:
  Term   terms_[SEMANTIC_MAX_TERMS];
  // Per-episode scratch, parallel to terms_: the largest weight this episode has said
  // either way, in halves. TTG-0003 §2's "per episode, plus = the LARGEST weight".
  uint8_t ep_plus_[SEMANTIC_MAX_TERMS];
  uint8_t ep_minus_[SEMANTIC_MAX_TERMS];
  Numbers n_;
  char    comention_[SEMANTIC_LEMMA_MAX];
  size_t  count_;
  uint32_t malformed_, skipped_, reclaimed_, refused_, fold_underflow_;
  Malformed last_mal_;
  bool     in_episode_;

  int  findIndex(const char* s, const char* v, const char* o) const;
  int  intern(const char* s, const char* v, const char* o);   // -1 only if reclaim failed
  int  reclaimLowestEps();
};

}  // namespace semantic

#endif  // SEMANTIC_H
