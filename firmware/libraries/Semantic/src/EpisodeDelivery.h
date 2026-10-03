// EpisodeDelivery.h — ACT-III §C4 stage 2 (docs/design/episode-order.md §7): other agents'
// LINK episodes fetched from their authors, held verbatim in @LAT105, and the BAR VIEW two
// agents holding the same episodes agree on without coordinating (TTG-RFC-0004 §4.5, §4.8
// item 4).
//
// Portable — no <Arduino.h>, no <FS.h> — so tests/test_episode_delivery.cpp pins all of it.
// The radio and flash I/O is EpisodeDeliveryNode.h's job (the TimeStream/TimeStreamNode split).
//
// THE PROTOCOL, in one paragraph. A receiver whose vector (EpisodeOrder.h) says it has heard
// of agent A's seq V[A], but whose cursor for A is lower, sends WANT{A, cursor+1, V[A]} to A.
// A answers with the FIRST link episode it holds at or after cursor+1, as DATA slices, then
// DONE{through = that seq}; holding none in range, just DONE{through = to_seq}. The receiver
// stores the copy, moves its cursor to `through`, and asks again. One episode per round trip
// means ONE reassembly buffer; no want_ack, because the cursor IS the retry (a short episode
// at DONE does not advance it).
//
// ⚠ HELD EPISODES ARE TESTIMONY. They are in the BAR VIEW and never in beliefs. That second
// half needs no code here: EpisodeReader feeds nothing from a block on any lane but its own
// (TTG-0002 §5.1), and a held copy lives on @LAT105.
#ifndef SEMANTIC_EPISODEDELIVERY_H
#define SEMANTIC_EPISODEDELIVERY_H

#include <stddef.h>
#include <stdint.h>

#include "Episode.h"
#include "EpisodeOrder.h"
#include "FleetTime.h"
#include "Semantic.h"

namespace semantic {

#define EPISODEDELIVERY_HELD_LANE 105
#define EPISODEDELIVERY_SUBOP_DONE 3          // WANT 1 and DATA 2 are in EpisodeOrder.h

// Held copies kept (lane-wide ring, oldest first) and the slack before a cut is attempted
// (a cut is a whole-file rewrite, so it is batched, as the tiers batch theirs).
#ifndef EPISODEDELIVERY_HELD_QUOTA
#define EPISODEDELIVERY_HELD_QUOTA 32
#endif
#ifndef EPISODEDELIVERY_HELD_SLACK
#define EPISODEDELIVERY_HELD_SLACK 8
#endif
#define EPISODEDELIVERY_HELD_CAP (EPISODEDELIVERY_HELD_QUOTA + EPISODEDELIVERY_HELD_SLACK + 8)

// Largest episode a receiver will reassemble: the worst link window + a maximal order block,
// rounded up. A longer DATA total is refused at its first slice, never truncated.
#define EPISODEDELIVERY_MAX_EPISODE \
  (SEMANTIC_LINK_WINDOW_EPISODE_BUF + EPISODEORDER_BLOCK_MAX + 64)

// Wire sizes. DATA's slice keeps the whole toot body inside toot::MAX_BODY (208).
#define EPISODEDELIVERY_WANT_LEN 20
#define EPISODEDELIVERY_DATA_HDR 17
#define EPISODEDELIVERY_SLICE (208 - EPISODEDELIVERY_DATA_HDR)       // 191
#define EPISODEDELIVERY_DONE_LEN 15

// A first fetch from a newly heard agent starts this many seqs back, not at seq 1: the
// author holds at most its link quota, and the held ring is smaller still.
#ifndef EPISODEDELIVERY_BACKLOG
#define EPISODEDELIVERY_BACKLOG 32
#endif
// Pacing (ms): between WANTs to one answering agent, after an unanswered one, and how long
// a WANT waits for its DONE.
#ifndef EPISODEDELIVERY_RETRY_MS
#define EPISODEDELIVERY_RETRY_MS 5000
#endif
#ifndef EPISODEDELIVERY_BACKOFF_MS
#define EPISODEDELIVERY_BACKOFF_MS 60000
#endif
// Consecutive unanswered WANTs to one agent before it is backed off (a single lost WANT or
// DONE is ordinary at the loss these radios see, ~half of broadcasts; 2026-10-03).
#ifndef EPISODEDELIVERY_MISSES_BEFORE_BACKOFF
#define EPISODEDELIVERY_MISSES_BEFORE_BACKOFF 3
#endif
// Resumes of one episode that make no progress before it is abandoned (cursor unmoved).
#ifndef EPISODEDELIVERY_STALLED_RESUMES
#define EPISODEDELIVERY_STALLED_RESUMES 4
#endif
#ifndef EPISODEDELIVERY_TIMEOUT_MS
#define EPISODEDELIVERY_TIMEOUT_MS 4000
#endif

// The bar (design §7.4): 10 min, so a gate fits in an hour; reported once its line is
// BAR_SETTLE in the past, so a late delivery has landed.
#ifndef EPISODEDELIVERY_BAR_MS
#define EPISODEDELIVERY_BAR_MS 600000UL
#endif
#ifndef EPISODEDELIVERY_BAR_SETTLE_MS
#define EPISODEDELIVERY_BAR_SETTLE_MS 120000UL
#endif

// ---------------------------------------------------------------------------------------
// wire
// ---------------------------------------------------------------------------------------
struct Want {
  uint32_t to, agent, from_seq, to_seq;
  uint8_t  tier;
  uint16_t off;        // > 0: a RESUME of exactly from_seq, starting at this byte
};
struct DataHdr {
  uint32_t to, agent, seq;
  uint16_t total, off;
};
struct Done {
  uint32_t to, agent, through;
  uint16_t total;      // 0: nothing was served; else the episode's length (data was sent)
};
size_t encodeWant(const Want& w, uint8_t* p, size_t cap);
bool decodeWant(const uint8_t* p, size_t len, Want& w);
size_t encodeData(const DataHdr& h, const uint8_t* bytes, size_t n, uint8_t* p, size_t cap);
bool decodeData(const uint8_t* p, size_t len, DataHdr& h, const uint8_t** bytes, size_t* n);
size_t encodeDone(const Done& d, uint8_t* p, size_t cap);
bool decodeDone(const uint8_t* p, size_t len, Done& d);

// ---------------------------------------------------------------------------------------
// the receiver: ONE episode in flight
// ---------------------------------------------------------------------------------------
// arm()/disarm()/state() from loop(); onData()/onDone() from the recv callback, which only
// copies into the buffer loop() armed (the buffer outlives the transfer: loop frees it after
// it has read a final state). `done_` is written last, so loop never reads a half transfer.
// A lost slice does not break the transfer: the receiver keeps the contiguous prefix,
// ignores what follows the gap, ends PARTIAL, and resume() asks for the rest (WANT.off).
class Inflight {
 public:
  enum State : uint8_t { IDLE, WAITING, COMPLETE, EMPTY, PARTIAL, BROKEN };
  void arm(uint32_t self, uint32_t agent, uint8_t* buf, size_t cap);
  void resume();                     // PARTIAL (or a timed-out started one) -> WAITING
  bool started() const { return started_; }
  size_t total() const { return total_; }
  void disarm();
  void onData(const DataHdr& h, const uint8_t* b, size_t n);
  void onDone(const Done& d);
  State state() const;
  uint32_t agent() const { return agent_; }
  uint32_t seq() const { return seq_; }
  uint32_t through() const { return through_; }
  size_t   length() const { return got_; }
  const uint8_t* bytes() const { return buf_; }

 private:
  uint8_t* buf_ = nullptr;
  size_t   cap_ = 0;
  uint32_t self_ = 0, agent_ = 0;
  volatile uint32_t seq_ = 0, through_ = 0;
  volatile uint32_t total_ = 0, got_ = 0;
  volatile uint16_t done_total_ = 0;
  volatile bool armed_ = false, started_ = false, broken_ = false, done_ = false;
};

// Per-agent cursors: which seq the next WANT starts after, and when it may be sent.
class Fetcher {
 public:
  void begin(uint32_t self);
  void seed(uint32_t agent, uint32_t cursor);                  // boot: max held seq
  bool next(const VectorClock& vc, uint32_t now_ms, Want& w);  // a WANT that is due
  void answered(uint32_t agent, uint32_t through, uint32_t now_ms);
  void unanswered(uint32_t agent, uint32_t now_ms);  // retry soon; back off after MISSES
  void retry(uint32_t agent, uint32_t now_ms);                 // broken: ask again soon
  uint32_t cursor(uint32_t agent) const;

 private:
  struct E { uint32_t agent, cursor, next_ms; uint8_t misses; bool known; };
  E* find(uint32_t agent, bool add);
  E   e_[EPISODEORDER_OTHERS];
  uint8_t n_ = 0, rr_ = 0;
  uint32_t self_ = 0;
};

// ---------------------------------------------------------------------------------------
// the held lane
// ---------------------------------------------------------------------------------------
// Feed every line of the @LAT105 records in FILE ORDER (oldest first) at boot; then
// appended() for each new copy. Keeps, per copy, (agent, seq, lon) in age order.
class HeldIndex {
 public:
  void reset();
  void line(const char* l);
  void finish();
  void appended(uint32_t agent, uint32_t seq, int16_t lon);
  bool has(uint32_t agent, uint32_t seq) const;
  uint32_t maxSeq(uint32_t agent) const;
  uint16_t count() const { return n_; }
  int16_t nextOrdinal() const;
  // The oldest (count - quota) copies as contiguous LON runs, when count ≥ quota + slack
  // (or `force` and count > quota). Returns runs written (≤ max); `*covers` copies covered.
  uint8_t cuts(Cut* out, uint8_t max, bool force, uint16_t* covers) const;
  void cutDone(uint16_t removed);       // drop the `removed` oldest
  uint32_t agentAt(uint16_t i) const { return e_[i].agent; }

 private:
  void commitCur();
  struct E { uint32_t agent, seq; int16_t lon; };
  E e_[EPISODEDELIVERY_HELD_CAP];
  uint16_t n_ = 0;
  bool     in_rec_ = false;
  E        cur_ = {0, 0, 0};
};

// The author's record as a held copy: verified (one record, @LAT103 in the LINK band, its
// `seq:` equal to `seq`), re-headed `@LAT105LON<ord>`, `held: 0x<agent>` after the fence.
// Returns bytes, or 0 (out[0] = '\0') if anything does not check.
size_t renderHeld(const char* rec, size_t n, uint32_t agent, uint32_t seq, int16_t ord,
                  char* out, size_t cap);

// The author's side: own LINK episodes, lon -> seq. Line-driven at boot (it ignores every
// record but @LAT103's link band) and add() on each append.
#ifndef EPISODEDELIVERY_SEQMAP_CAP
#define EPISODEDELIVERY_SEQMAP_CAP 72
#endif
class SeqMap {
 public:
  void line(const char* l);
  void add(int16_t lon, uint32_t seq);
  void remove(int16_t lon);
  // The lowest seq in [from, to] (to 0 = no upper bound). False if none.
  bool firstInRange(uint32_t from, uint32_t to, uint32_t* seq, int16_t* lon) const;
  uint8_t count() const { return n_; }

 private:
  struct E { int16_t lon; uint32_t seq; };
  E e_[EPISODEDELIVERY_SEQMAP_CAP];
  uint8_t n_ = 0;
  bool    in_link_ = false;
  int16_t cur_lon_ = 0;
};

// ---------------------------------------------------------------------------------------
// the bar view
// ---------------------------------------------------------------------------------------
// Bar N of frame F is the window [F + (N-1)·bar, F + N·bar). An episode is IN it when its
// stamp is bounded, in frame F, and its whole range lies inside the window. Disjoint windows
// are a deliberate narrowing of RFC-0004 §4.5's "everything before the line": with bounded
// retention, a cumulative view would compare different histories, never the same episodes.
int64_t barLine(uint64_t frame, uint32_t bar_ms, int64_t n);
// The newest N whose line is at least settle_ms behind pulse_now; -1 if none yet.
int64_t completeBar(int64_t pulse_now, uint64_t frame, uint32_t bar_ms, uint32_t settle_ms);

// Feed the records of @LAT103 (only its LINK band counts) and @LAT105, any order. Every
// included episode is replayed into `c` (KEEPING), which the caller began empty.
// Which episodes went into a bar, per author: count, lowest/highest seq, and sum of seqs.
// Two nodes that held the same episodes have the same rows, so a peer's BAR record can be
// checked for the same SET without the copies (which retention trims) being on flash.
#define EPISODEDELIVERY_BAR_AGENTS (EPISODEORDER_OTHERS + 1)
struct BarHolds {
  uint32_t agent;
  uint16_t n;
  uint32_t lo, hi, sum;
};

class BarView {
 public:
  // `self` names the author of own (@LAT103) episodes in holds().
  BarView(Consolidator& c, uint64_t frame, int64_t lo, int64_t hi, uint32_t self = 0);
  void line(const char* l);
  void finish();
  uint16_t own() const { return own_; }
  uint16_t held() const { return held_; }
  uint8_t holdsCount() const { return nh_; }
  const BarHolds& holds(uint8_t i) const { return h_[i]; }   // ascending agent
  uint16_t unattributed() const { return unattributed_; }    // no seq, or past AGENTS

 private:
  void close();
  void hold(uint32_t agent, uint32_t seq);
  Consolidator& c_;
  uint64_t frame_;
  int64_t  lo_, hi_;
  uint32_t self_;
  int16_t  lat_ = 0;
  bool     accept_ = false, in_block_ = false, decided_ = false, started_ = false;
  uint16_t own_ = 0, held_ = 0, unattributed_ = 0;
  uint32_t agent_ = 0, seq_ = 0;
  BarHolds h_[EPISODEDELIVERY_BAR_AGENTS];
  uint8_t  nh_ = 0;
};

struct BarDigest {
  uint16_t terms;
  uint32_t sum;          // Σ FNV-1a("<subject> <belief line>") mod 2^32 — order-free
};
BarDigest barDigest(const Consolidator& c);

// ---------------------------------------------------------------------------------------
// the BAR record (@LAT106): what a node computed for a bar, kept on flash so the gate and
// any peer can read it without a cable at print time (design 7.6, 2026-10-03)
// ---------------------------------------------------------------------------------------
//   @LAT106LON<ord> | created:0 | updated:0
//
//   **BAR** frame:<F> bar:<N> own:<o> held:<h> terms:<t> digest:0x<8 hex> settled_ms:<s>
//   **HOLDS** agent:0x<8 hex> n:<n> lo:<seq> hi:<seq> sum:<sum of seqs>   (one per author)
//
// settled_ms = how long after bar N's closing line it was computed (>= BAR_SETTLE_MS; a
// record written at boot for a bar that settled while the node was off says so).
#ifndef EPISODEDELIVERY_BAR_LANE
#define EPISODEDELIVERY_BAR_LANE 106
#endif
#ifndef EPISODEDELIVERY_BAR_QUOTA
#define EPISODEDELIVERY_BAR_QUOTA 16      // 2 h 40 min of bars
#endif
#ifndef EPISODEDELIVERY_BAR_SLACK
#define EPISODEDELIVERY_BAR_SLACK 4
#endif
#define EPISODEDELIVERY_BAR_CAP (EPISODEDELIVERY_BAR_QUOTA + EPISODEDELIVERY_BAR_SLACK + 4)

// Returns bytes written, or 0 (out[0] = NUL) if it does not fit. Never truncates.
size_t renderBar(char* out, size_t cap, int16_t ord, uint64_t frame, int64_t bar,
                 const BarView& v, const BarDigest& d, int64_t settled_ms);

// Which bars this node has recorded, oldest first. Line-driven at boot (@LAT106 records in
// file order), appended() for each new one.
class BarIndex {
 public:
  void reset() { n_ = 0; cur_lon_ = 0; in_rec_ = false; }
  void line(const char* l);
  void finish() {}                      // line-driven like HeldIndex; nothing pending
  void appended(uint64_t frame, int64_t bar, int16_t lon);
  bool has(uint64_t frame, int64_t bar) const;
  uint16_t count() const { return n_; }
  int16_t nextOrdinal() const;
  // The oldest (count - QUOTA) records as ONE contiguous LON run, once count >= QUOTA + SLACK
  // (or `force` and count > QUOTA). false = nothing to cut. *covers = records in the run.
  bool cut(Cut* out, bool force, uint16_t* covers) const;
  void cutDone(uint16_t removed);

 private:
  struct E { uint64_t frame; int64_t bar; int16_t lon; };
  E e_[EPISODEDELIVERY_BAR_CAP];
  uint16_t n_ = 0;
  int16_t cur_lon_ = 0;
  bool in_rec_ = false;
};

}  // namespace semantic

#endif  // SEMANTIC_EPISODEDELIVERY_H
