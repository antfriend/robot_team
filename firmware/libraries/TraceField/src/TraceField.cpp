#include "TraceField.h"

namespace tracefield {

// Exponential decay in integer arithmetic, continuous across half-life boundaries.
//
// `whole` halvings by shift, then a LINEAR interpolation across the fraction of the
// current half-life. At frac == half_life the interpolation reaches exactly s>>(whole+1),
// which is where the next shift would put it — so the curve has no step at the boundary.
// Linear-inside-a-halving is not a true exponential, but it is monotone, exact at every
// boundary, and wrong by at most ~6% mid-interval, which is inaudible in a strength that
// drives note amplitude.
//
// ⚠ 8 halvings is the floor, not an optimisation: 255>>8 == 0, so beyond that the answer
// is zero anyway and the shift would be undefined behaviour at >= 32.
uint8_t decayed(uint8_t s, uint32_t last_ms, uint32_t now_ms, uint32_t half_life_ms) {
  if (!s) return 0;
  if (!half_life_ms) return 0;
  // Unsigned wrap makes this correct across millis()' 49.7-day rollover: a "future"
  // last_ms (clock stepped back, or a merge stamped ahead) yields a huge dt and decays
  // to zero rather than reading as freshly deposited. Silence is the safe failure.
  const uint32_t dt = now_ms - last_ms;
  const uint32_t whole = dt / half_life_ms;
  if (whole >= 8) return 0;
  const uint32_t frac = dt % half_life_ms;
  const uint32_t base = (uint32_t)s >> whole;
  const uint32_t drop = (base * frac) / (2u * half_life_ms);
  return (uint8_t)(base - drop);
}

void Field::deposit(uint8_t cell, uint8_t amount, uint32_t now_ms) {
  if (cell >= CELLS || !amount) return;
  const uint32_t cur = decayed(s_[cell], last_[cell], now_ms, half_life_ms_);
  const uint32_t sum = cur + (uint32_t)amount;
  s_[cell] = (uint8_t)(sum > 255 ? 255 : sum);
  last_[cell] = now_ms;
  peer_mask_ &= (uint16_t)~(1u << cell);   // this value is ours now
}

uint8_t Field::strengthAt(uint8_t cell, uint32_t now_ms) const {
  if (cell >= CELLS) return 0;
  return decayed(s_[cell], last_[cell], now_ms, half_life_ms_);
}

uint8_t Field::merge(const uint8_t* digest, size_t len, uint32_t now_ms) {
  if (!digest || len < DIGEST_LEN) return 0;
  if (digest[0] != DIGEST_MAGIC || digest[1] != DIGEST_VERSION) return 0;
  uint8_t raised = 0;
  for (uint8_t i = 0; i < CELLS; ++i) {
    const uint8_t theirs = digest[2 + i];
    if (!theirs) continue;
    // Compare decayed against decayed. Adopting `theirs` stamps it at OUR now, which is
    // the only stamp we can defend: it says "this much trace was here when we heard it".
    if (theirs > decayed(s_[i], last_[i], now_ms, half_life_ms_)) {
      s_[i] = theirs;
      last_[i] = now_ms;
      peer_mask_ |= (uint16_t)(1u << i);   // provenance: a peer put this here
      ++raised;
    }
  }
  return raised;
}

size_t Field::buildDigest(uint8_t* p, size_t cap, uint32_t now_ms) const {
  if (!p || cap < DIGEST_LEN) return 0;
  p[0] = DIGEST_MAGIC;
  p[1] = DIGEST_VERSION;
  for (uint8_t i = 0; i < CELLS; ++i)
    p[2 + i] = decayed(s_[i], last_[i], now_ms, half_life_ms_);
  return DIGEST_LEN;
}

bool Field::alive(uint32_t now_ms) const {
  for (uint8_t i = 0; i < CELLS; ++i)
    if (strengthAt(i, now_ms) >= TRACEFIELD_VOICE_FLOOR) return true;
  return false;
}

uint16_t Field::energy(uint32_t now_ms) const {
  uint16_t e = 0;
  for (uint8_t i = 0; i < CELLS; ++i) e = (uint16_t)(e + strengthAt(i, now_ms));
  return e;
}

// C major pentatonic over three octaves + one. No thirds against fourths, no tritones:
// whatever the room deposits, the chord is playable.
static const uint16_t kPent[CELLS] = {
    262, 294, 330, 392, 440,      // C4 D4 E4 G4 A4
    523, 587, 659, 784, 880,      // C5 D5 E5 G5 A5
    1047, 1175, 1319, 1568, 1760, // C6 D6 E6 G6 A6
    2093,                         // C7
};

uint16_t pitchFor(uint8_t cell) { return cell < CELLS ? kPent[cell] : 0; }

}  // namespace tracefield
