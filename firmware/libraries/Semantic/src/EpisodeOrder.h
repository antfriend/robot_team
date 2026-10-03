// EpisodeOrder.h — ACT-III §C4, TTG-RFC-0004 §4.4 rule 2: the per-agent `seq` every
// episode carries, and the vector clock (`follows:`) that orders episodes ACROSS agents.
// Design: docs/design/episode-order.md (stage 1 — order without episode delivery).
//
// Portable — no <Arduino.h> — so tests/test_episode_order.cpp pins all of it. The radio
// glue (queueing from the recv callback, emitting the toot) is the sketch's job, exactly as
// TimeStream/TimeStreamNode split it.
//
// ---------------------------------------------------------------------------
// WHAT THE NUMBERS MEAN
// ---------------------------------------------------------------------------
//   seq        this node's episodes, numbered 1, 2, 3 … across ALL tiers. Dense: a number
//              is spent only when the append SUCCEEDS (committed()), so a gap on a pull means
//              an episode that existed and was folded, never one that was not written.
//   V[a]       the highest `seq` of agent `a` this node has HEARD OF. Merged element-wise
//              max, and re-sent, so knowledge of A reaches C through B: a true vector clock,
//              which is what lets FleetTime's order() compare two episodes directly.
//   follows:   V, minus this node, written into every episode. "This episode was said
//              already knowing those." (Operator decision 2026-10-03: KNOWING THAT IT WAS
//              WRITTEN is enough — the Lamport reading of RFC-0004 §4.4's "holds".)
//
// ⚠ EVERY ENTRY IS A LOWER BOUND, so every failure UNDER-claims. A lost toot, a forgotten
// vector, a table too full to add an agent: each leaves fewer pairs ordered, never a pair
// ordered wrongly. Nothing here may ever raise an entry past what was actually received.
//
// ⚠ A PEER'S VIEW OF THIS NODE IS A FLOOR. A received entry for OUR OWN id that is higher
// than our seq means our filesystem was re-imaged (or our seq was otherwise lost) while the
// fleet remembered us. We jump past it and count a regression, so the next episode does not
// re-use a number copies elsewhere already carry.
#ifndef SEMANTIC_EPISODEORDER_H
#define SEMANTIC_EPISODEORDER_H

#include <stddef.h>
#include <stdint.h>

#include "FleetTime.h"

namespace semantic {

// The EPISODE toot (toot::EPISODE, type 14): byte 0 is a sub-op.
#define EPISODEORDER_SUBOP_VECTOR 0
#define EPISODEORDER_SUBOP_WANT   1   // reserved: stage 2 (delivery)
#define EPISODEORDER_SUBOP_DATA   2   // reserved: stage 2 (delivery)

// VECTOR payload: sub-op u8 | n u8 | n × { agent u32 LE, seq u32 LE }. The sender's own
// entry is included (first). ≤ 66 B: one unchunked frame.
#define EPISODEORDER_VECTOR_HDR   2
#define EPISODEORDER_VECTOR_ENTRY 8
#define EPISODEORDER_VECTOR_MAX \
  (EPISODEORDER_VECTOR_HDR + EPISODEORDER_VECTOR_ENTRY * FLEETTIME_MAX_AGENTS)

// Other agents a vector can hold (own entry is kept apart, as `seq`).
#define EPISODEORDER_OTHERS (FLEETTIME_MAX_AGENTS - 1)

// The rendered block: `seq: <u32>\n` (≤ 16) + `follows:` + OTHERS × ` 0x%08lx:<u32>` (≤ 22
// each) + `\n` — 16 + 9 + 7×22 + 1 = 180, +1 NUL. Pinned both ways by the test.
#define EPISODEORDER_BLOCK_MAX 184

// Change-triggered, with a heartbeat (design §3.1). A vector is ~66 B; at about one episode
// a minute per node this is ~0.1–1 frame/s.
#ifndef EPISODEORDER_MIN_GAP_MS
#define EPISODEORDER_MIN_GAP_MS 1000
#endif
#ifndef EPISODEORDER_HEARTBEAT_MS
#define EPISODEORDER_HEARTBEAT_MS 10000
#endif

class VectorClock {
 public:
  void begin(uint32_t self);

  uint32_t self() const { return self_; }
  uint32_t seq() const { return seq_; }            // last COMMITTED own seq; 0 = none yet
  uint32_t nextSeq() const { return seq_ + 1; }    // what the episode being rendered carries

  // The append of the episode carrying `s` succeeded. Never moves seq backward.
  void committed(uint32_t s);

  // Boot: the newest own episode replayed from flash carried `s` and this follows vector.
  // Merges like any received vector (so it too can only raise entries).
  void restore(uint32_t s, const Follows* f, uint8_t n);

  // One received entry. Returns true when anything changed.
  bool mergeEntry(uint32_t agent, uint32_t seq);
  // A VECTOR payload (sub-op byte included). False = malformed (nothing merged).
  bool mergeWire(const uint8_t* p, size_t len);

  // VECTOR payload for the toot: own entry first (when seq > 0), then every other.
  // Returns bytes, or 0 if cap is short.
  size_t encode(uint8_t* p, size_t cap) const;

  // The other agents with seq > 0, sorted by agent id. Returns the count.
  uint8_t follows(Follows* out, uint8_t max) const;

  // `seq: <nextSeq()>\n` + `follows: …\n` (omitted when empty). Returns bytes (excl. NUL),
  // or 0 if cap is short (out[0] = '\0').
  size_t renderBlock(char* out, size_t cap) const;

  // Send policy: due when the vector changed (and MIN_GAP has passed) or HEARTBEAT is due.
  bool sendDue(uint32_t now_ms) const;
  void sent(uint32_t now_ms);

  uint32_t regressions() const { return regressions_; }   // floor jumps (see header)
  uint32_t overflow() const { return overflow_; }          // agents dropped: table full
  uint32_t malformed() const { return malformed_; }        // VECTOR payloads refused
  uint8_t  others() const { return n_; }

 private:
  Follows  e_[EPISODEORDER_OTHERS];   // sorted by agent
  uint8_t  n_ = 0;
  uint32_t self_ = 0, seq_ = 0;
  uint32_t regressions_ = 0, overflow_ = 0, malformed_ = 0;
  bool     dirty_ = false, ever_sent_ = false;
  uint32_t last_sent_ms_ = 0;
};

// ---------------------------------------------------------------------------------------
// The recv-callback side: copy and nothing else
// ---------------------------------------------------------------------------------------
// ⚠ THE RECV CALLBACK MUST NEVER TOUCH THE CLOCK (CLAUDE.md, the TimeStream rule): a merge
// mid-render would write a `follows:` that half-reflects a vector. push() is a bounded copy
// into a ring; drainInto() runs from loop(). A full ring drops the NEWEST payload — the
// next heartbeat carries the same knowledge, so a drop under-claims, never corrupts.
#ifndef EPISODEORDER_INBOX
#define EPISODEORDER_INBOX 4
#endif
class VectorInbox {
 public:
  bool push(const uint8_t* p, size_t len);           // callback-safe; false = dropped
  uint8_t drainInto(VectorClock& vc);                  // loop(); returns payloads merged
  uint32_t dropped() const { return dropped_; }

 private:
  uint8_t  buf_[EPISODEORDER_INBOX][EPISODEORDER_VECTOR_MAX];
  uint8_t  len_[EPISODEORDER_INBOX] = {0};
  volatile uint8_t head_ = 0, tail_ = 0;              // head_: writer, tail_: reader
  uint32_t dropped_ = 0;
};

// ---------------------------------------------------------------------------------------
// The block lines, read back
// ---------------------------------------------------------------------------------------
// `seq: <u32>` → true + value. Anything else (including `seq: 0`) → false.
bool parseSeqLine(const char* line, uint32_t* seq);
// `follows: 0x<hex>:<u32> …` → entries written (≤ max). `*ok` false on any malformed token
// (the entries before it are still returned; a reader decides whether to trust them).
uint8_t parseFollowsLine(const char* line, Follows* out, uint8_t max, bool* ok = 0);

// Boot recovery: feed every line of this node's live episodes (any order of records). It
// keeps the highest `seq:` seen and the `follows:` of the episode that carried it.
class OrderRecovery {
 public:
  void line(const char* l);
  uint32_t seq() const { return best_seq_; }
  uint8_t follows(Follows* out, uint8_t max) const;
  void applyTo(VectorClock& vc) const;

 private:
  uint32_t cur_seq_ = 0, best_seq_ = 0;
  bool     capture_ = false;
  Follows  f_[EPISODEORDER_OTHERS];
  uint8_t  nf_ = 0;
};

}  // namespace semantic

#endif  // SEMANTIC_EPISODEORDER_H
