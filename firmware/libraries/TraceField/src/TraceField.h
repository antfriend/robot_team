// TraceField.h — a stigmergic trace field you can HEAR (TTDB-RFC-0010 §5, RAM-only).
//
// This is the first FIELD in the fleet's sense of the word: a medium that agents deposit
// into, that decays on its own, and that nobody addresses. It is deliberately **not** a
// TTDB lane. TTDB-RFC-0010 §3 says the first FIELD lane must be a new lane at @LAT101+
// with stable `sid` naming, because reclaiming an ordinal slot re-points every citation
// into it — that is a real cost and it is not what this library is for. This field lives
// in RAM, cites nothing, and is cited by nothing, which makes §6.3's acceptance test
// ("the system must still be correct with the field empty") trivially true: a node that
// just booted has a flat field, plays nothing, and is fine.
//
// WHAT IT IS FOR: feeling the mechanism. 16 cells on the pulse's 16-step phrase grid.
// Make a noise near a node and its cells rise; stop and they fade over a half-life. Each
// node appends its decayed field to the HELLO it already sends every 2 s, and a receiver
// merges by max — so two nodes converge on one field without either sending the other a
// message. What you hear is the medium, not a transmission.
//
// THE MERGE IS MAX-OF-DECAYED, AND THAT CHOICE IS THE WHOLE DESIGN:
//   * idempotent      — merging the same digest twice changes nothing
//   * order-free      — digests may arrive in any order, or be dropped, or repeat
//   * clock-free      — see below; this is the part worth reading
//
// ⚠ THE DIGEST CARRIES ALREADY-DECAYED VALUES, SO NO CLOCK IS COMPARED. A first cut sent
// `(strength, last_ms)` pairs and made the receiver age them, which drags in the sender's
// time base — and a stream clock is a RATCHET (fastest crystal heard wins: right for
// recency, wrong for a duration, companion.md §6). Ageing a peer's trace against our own
// clock would have applied an unbounded offset to every cell. Decaying at the sender and
// shipping the result means a digest is a statement about NOW, true when it was built,
// needing nothing but arrival. It is also why `merge` takes our `now` and not theirs.
//
// ⚠ DECAY IS EVALUATED ON READ AND NEVER WRITTEN (RFC-0010 §5.1). Only a deposit or a
// merge mutates a cell. Nothing here runs on a timer, so a field costs zero work while
// nothing is happening — and on a node whose flash append is 60-220 ms, a design that
// rewrote decayed strengths on a tick would have been unaffordable as well as wrong.
#pragma once
#include <stdint.h>
#include <stddef.h>

namespace tracefield {

// One cell per step of the 16-step phrase (PULSE_STEPS_PER_BEAT 4 x 4 beats). The
// coincidence is the point: cell N is voiced at step N, so the field IS the score.
const uint8_t CELLS = 16;

// Wire form of a whole field: magic, version, then one decayed strength per cell.
// 18 bytes, appended after the 21-byte time-stream anchor in a 250-byte HELLO.
// ⚠ The magic byte is load-bearing, not decoration: the digest sits at a FIXED offset
// after the anchor, so a node running older firmware appends nothing and a node running
// newer firmware must not read the next field's bytes as strengths. Check magic+version
// before trusting a single cell.
//
// VERSION 2 ADDS THE GENERATION BYTE, AND IT EXISTS BECAUSE **A MAX-MERGED FIELD CANNOT
// EXPRESS DELETION.** Max-of-decayed is monotone upward: that is exactly what makes the
// merge idempotent and order-free, and it is also why clearing a field locally does
// nothing — the peer's next digest, two seconds later, floods every cell straight back.
// A "clear" that a shared medium immediately undoes is not a clear.
//
// So the field carries a generation. A digest from a NEWER generation is adopted whole,
// zeros included, which is the one operation that can lower a value; equal generations
// max-merge exactly as before; an older one is ignored, because our own next digest will
// bring that node forward. This is the standard join-semilattice-plus-epoch shape, and one
// byte is the entire cost.
// ⚠ v1 and v2 are NOT interoperable and deliberately so: a v1 node's digest is refused by
// the version check, making it a non-participant rather than a node whose cells are read
// one byte out of phase. Both handhelds are flashed together.
const uint8_t  DIGEST_MAGIC   = 0xFD;
const uint8_t  DIGEST_VERSION = 2;
const size_t   DIGEST_LEN     = 3 + CELLS;

// Default half-life. Short on purpose: a trace must fade inside the attention span of
// somebody standing next to it, or the field cannot be *felt*, only measured.
// ⚠ 20 s -> 10 s on 2026-08-07 at the operator's request after hearing it: twice as steep,
// so a clap is gone in ~40 s rather than ~80 (8 halvings is the silence floor). Change it
// on BOTH handhelds or their copies of one shared cell visibly disagree.
#ifndef TRACEFIELD_HALF_LIFE_MS
#define TRACEFIELD_HALF_LIFE_MS 10000u
#endif

// Below this a cell is silent. Not zero: a cell decaying through the last few counts
// would otherwise keep striking a note nobody can hear but everybody can hear stopping.
#ifndef TRACEFIELD_VOICE_FLOOR
#define TRACEFIELD_VOICE_FLOOR 24
#endif

class Field {
 public:
  explicit Field(uint32_t half_life_ms = TRACEFIELD_HALF_LIFE_MS)
      : half_life_ms_(half_life_ms ? half_life_ms : 1) {}

  // Reinforce `cell` by `amount`, saturating at 255. Decays the cell to `now` first, so
  // repeated deposits accumulate against the current value rather than a stale one.
  void deposit(uint8_t cell, uint8_t amount, uint32_t now_ms);

  // Wipe the field and OPEN A NEW GENERATION, so the clear propagates instead of being
  // undone by the next peer digest (see DIGEST_VERSION). This is the only operation that
  // can lower another node's cell, and it is deliberately the operator's to invoke.
  void clear();

  uint8_t generation() const { return gen_; }

  // The decayed strength of `cell` at `now_ms`. Pure: does not mutate.
  uint8_t strengthAt(uint8_t cell, uint32_t now_ms) const;

  // Max-merge a peer's digest. Returns the number of cells this raised (0 = the peer
  // told us nothing we did not already have, which is the common case and is silent).
  uint8_t merge(const uint8_t* digest, size_t len, uint32_t now_ms);

  // Serialise the field, decayed to `now_ms`, into `p`. Returns bytes written, or 0 if
  // `cap` is short — never a partial digest.
  size_t buildDigest(uint8_t* p, size_t cap, uint32_t now_ms) const;

  // True if any cell is above the voice floor: "is there anything to hear right now?"
  bool alive(uint32_t now_ms) const;

  // Did this cell's CURRENT value arrive from a peer, rather than from a local deposit?
  //
  // Provenance exists for the operator, not for the mechanism: the field works identically
  // without it. But a shared medium that cannot show you which marks are yours is
  // indistinguishable on the glass from a local echo, and that distinction is the entire
  // claim being demonstrated. Set by merge() on a cell it raises, cleared by deposit() —
  // so it always describes the value you are looking at now, not the cell's history.
  bool fromPeer(uint8_t cell) const {
    return cell < CELLS && (peer_mask_ & (uint16_t)(1u << cell)) != 0;
  }

  // Sum of decayed strengths — the field's total energy, for a render that wants one
  // number (a level meter, a brightness).
  uint16_t energy(uint32_t now_ms) const;

  uint32_t halfLifeMs() const { return half_life_ms_; }

 private:
  uint8_t  s_[CELLS]      = {0};
  uint32_t last_[CELLS]   = {0};
  uint16_t peer_mask_     = 0;   // one bit per cell: this value came from a peer
  uint8_t  gen_           = 0;   // epoch; a higher one may LOWER cells (see clear())
  uint32_t half_life_ms_;
};

// Pitch for a cell: a pentatonic run, so ANY combination of cells is consonant. That is
// not decoration — the field's contents are chosen by the environment, not by a composer,
// so the scale has to make every possible chord acceptable. Values match score::Pitch's
// rounded Hz; the table is duplicated rather than included so this library keeps its
// zero dependencies.
uint16_t pitchFor(uint8_t cell);

// Decay `s` last touched at `last_ms`, read at `now_ms`, with `half_life_ms`. Exposed
// because it is the one piece of arithmetic worth testing directly.
uint8_t decayed(uint8_t s, uint32_t last_ms, uint32_t now_ms, uint32_t half_life_ms);

}  // namespace tracefield
