// Attention.h — the EPS arbiter (docs/design/cardputer-sensorium.md §3, §7 Phase S1).
//
// Which sense deserves the screen. Every modality reports a stimulus as a `(sal, conf)`
// pair and the arbiter ranks them by the project's own attention currency, TTDB-RFC-0005
// §3.3 — NOT a new salience scheme:
//
//     EPS = sal × (255 − conf) / 255
//
//   * `sal`  — how far this sense is from ITS OWN baseline, in units of its own noise,
//              0..255. That is what makes a tilt and a clap comparable at all.
//   * `conf` — how well-explained the stimulus is. Our own tone explains a sound; a key
//              press explains a jolt; a routine HELLO explains a neighbour. conf 255 ->
//              EPS 0, so an explained stimulus can never win however loud it is.
//
// Three guards stop it being a twitchy meter (§3.2), all here and all native-tested:
//   * DECAY      — a stimulus is a PEAK that half-lives toward 0, so a clap takes the
//                  screen and hands it back instead of latching. A new stimulus replaces
//                  the held one only if its EPS beats what the held one has decayed to.
//   * DWELL      — once a modality wins it holds >= ATTENTION_DWELL_MS, even against idle.
//   * MARGIN     — a challenger must beat the incumbent's EPS by ATTENTION_MARGIN_PCT.
// Below ATTENTION_IDLE_EPS nothing is "activated" and the winner is MOD_IDLE — the resting
// face (§3.2: an eye at rest is still a face).
//
// HEADLESS by design (Phase S1): this library renders nothing and owns no view. The sketch
// prints the winner. Giving it the screen is S2/S3's job, and the summed EPS it already
// exposes (`total()`) is the number the eye's two-term arousal stand-in is waiting for.
//
// Portable: no Arduino dependency. Nothing here may be called from a radio callback —
// `Inbox` is the one piece that is, and it only copies.
#pragma once
#include <stdint.h>
#include <stddef.h>

// Half-life of a held stimulus. Full scale (255) falls below the idle floor (32) in three
// half-lives = 2.4 s, which is S1's "decays back to idle within ~3 s" with dwell inside it.
#ifndef ATTENTION_HALF_LIFE_MS
#define ATTENTION_HALF_LIFE_MS 800u
#endif
#ifndef ATTENTION_IDLE_EPS
#define ATTENTION_IDLE_EPS 32
#endif
#ifndef ATTENTION_DWELL_MS
#define ATTENTION_DWELL_MS 1500u
#endif
#ifndef ATTENTION_MARGIN_PCT
#define ATTENTION_MARGIN_PCT 25
#endif
#ifndef ATTENTION_MAX_PEERS
#define ATTENTION_MAX_PEERS 8
#endif
#ifndef ATTENTION_INBOX
#define ATTENTION_INBOX 16
#endif

namespace attention {

// The modalities S1 ranks. Place (S5) and the low-battery alert (§4.5) append here; the
// index is the tie-break (lower wins), so keep the order stable.
enum Modality : uint8_t {
  MOD_MOTION    = 0,   // tilt + shake (BMI270)
  MOD_SOUND     = 1,   // the room (ES8311 mic), @LAT94's own transients
  MOD_NEIGHBOUR = 2,   // novelty on the mesh: new, returned, gone quiet
  MOD_COUNT     = 3,
  MOD_IDLE      = 0xFF,
};
const char* modalityName(uint8_t m);

inline uint8_t eps(uint8_t sal, uint8_t conf) {
  return (uint8_t)(((uint32_t)sal * (255u - conf)) / 255u);
}

// Continuous half-life decay of an 8-bit strength — the same shift-then-interpolate shape
// as TraceField's, so it is monotone, has no step at the half-life seam, and a millis()
// rollover or a backwards clock decays to SILENCE, never to "fresh".
uint8_t decayed(uint8_t v, uint32_t t0_ms, uint32_t now_ms, uint32_t half_life_ms);

class Arbiter {
 public:
  // A stimulus on modality `m`. Peak-hold: it replaces the held one only if its EPS is at
  // least what the held one has decayed to — so a steady drizzle cannot reset a fading
  // bang, and a bigger event always lands. `detail` rides along for the log (a peer id,
  // an RMS); it is the held stimulus's, never a later weaker one's.
  // Returns true when the stimulus was taken.
  bool observe(uint8_t m, uint8_t sal, uint8_t conf, uint32_t now_ms, uint32_t detail = 0);

  // Re-rank with hysteresis. Returns true when the winner changed.
  bool tick(uint32_t now_ms);

  uint8_t  winner() const { return winner_; }
  uint32_t heldSince() const { return since_ms_; }
  uint8_t  epsAt(uint8_t m, uint32_t now_ms) const;
  uint8_t  sal(uint8_t m) const  { return m < MOD_COUNT ? s_[m].sal : 0; }   // as held
  uint8_t  conf(uint8_t m) const { return m < MOD_COUNT ? s_[m].conf : 0; }
  uint32_t detail(uint8_t m) const { return m < MOD_COUNT ? s_[m].detail : 0; }
  // Summed EPS across modalities, 0..255*MOD_COUNT — overall arousal (§4.1 pupil).
  uint16_t total(uint32_t now_ms) const;

 private:
  struct Slot { uint8_t eps = 0, sal = 0, conf = 0; uint32_t t = 0; uint32_t detail = 0; };
  Slot     s_[MOD_COUNT];
  uint8_t  winner_ = MOD_IDLE;
  uint32_t since_ms_ = 0;
};

// Neighbour NOVELTY (§4.3): salience fires on a new neighbour, one returning after a gap,
// or one going quiet — never on volume. Each peer's own inter-arrival time is its baseline,
// so "late" is measured in units of how often THAT peer usually speaks (a conductor sends
// a PULSE per beat; a V4 only HELLOs every 2 s).
//
// ⚠ A peer that power-cycles is often silent for LESS than the 10 s Social fade, so the
// threshold is `max(ATTENTION_LATE_MULT x typical gap, ATTENTION_LATE_MIN_MS)`, not the fade.
// ⚠ The baseline only learns from ON-TIME arrivals (gap <= 2x typical), not from every
// arrival short of late. A dropout that taught it would make every later dropout — and
// then a real reboot — look routine.
#ifndef ATTENTION_LATE_MULT
#define ATTENTION_LATE_MULT 3u
#endif
#ifndef ATTENTION_LATE_MIN_MS
#define ATTENTION_LATE_MIN_MS 4000u
#endif
#ifndef ATTENTION_SAL_NEW
#define ATTENTION_SAL_NEW 200
#endif
#ifndef ATTENTION_SAL_QUIET
#define ATTENTION_SAL_QUIET 96
#endif

class Novelty {
 public:
  enum Event : uint8_t { EV_NONE = 0, EV_NEW, EV_RETURNED, EV_QUIET };

  // A reception from `peer`. Returns the salience of this arrival (0 = routine) and sets
  // `ev`, and `gap_ms` to the silence it ended (0 for a new peer).
  uint8_t heard(uint32_t peer, uint32_t now_ms, Event& ev, uint32_t& gap_ms);
  // Has a peer just gone late? At most one per call (call every pass). Returns its
  // salience and identity, or 0. A peer is reported quiet ONCE per silence.
  uint8_t quiet(uint32_t now_ms, uint32_t& peer, uint32_t& gap_ms);

  uint32_t typicalGap(uint32_t peer) const;   // ms, 0 if unknown
  uint32_t lateAfter(uint32_t typ) const;

 private:
  struct Peer { uint32_t node = 0, last = 0, typ = 0; bool used = false, late = false; };
  Peer p_[ATTENTION_MAX_PEERS];
};

// Motion salience (§3.1): how far the deck is from its own recent pose, plus how hard it
// is being shoved. Two terms, max'd:
//   * TILT  — a fast pose estimate against a slow one, so a deliberate lean is salient and
//             then fades as the slow estimate catches up: HOLDING a tilt is not news.
//   * SHAKE — ||a| - 1 g|, gravity-invariant, the tap/shove energy the face already uses.
// Fed at a fixed rate; the coefficients assume ~20 ms samples (the face's 50 Hz poll).
#ifndef ATTENTION_TILT_FLOOR_MG
#define ATTENTION_TILT_FLOOR_MG 50
#endif
#ifndef ATTENTION_TILT_SPAN_MG
#define ATTENTION_TILT_SPAN_MG 250
#endif
#ifndef ATTENTION_SHAKE_FLOOR_MG
#define ATTENTION_SHAKE_FLOOR_MG 80
#endif
#ifndef ATTENTION_SHAKE_SPAN_MG
#define ATTENTION_SHAKE_SPAN_MG 240
#endif

class MotionSalience {
 public:
  uint8_t feed(int ax_mg, int ay_mg, int az_mg);
  int lastTiltMg() const { return tilt_mg_; }
  int lastShakeMg() const { return shake_mg_; }
 private:
  bool  primed_ = false;
  float fx_ = 0, fy_ = 0, fz_ = 0;   // fast pose, tau ~200 ms
  float sx_ = 0, sy_ = 0, sz_ = 0;   // slow pose, tau ~1 s: the baseline
  int   tilt_mg_ = 0, shake_mg_ = 0;
};

// Callback -> loop handoff for receptions: copy only. Single producer (the radio callback),
// single consumer (loop). Full = drop the newest; a lost presence costs at most one
// spurious "late", and the next reception corrects it.
class Inbox {
 public:
  void push(uint32_t peer) {
    const uint8_t h = head_, n = (uint8_t)((h + 1) % ATTENTION_INBOX);
    if (n == tail_) { ++dropped_; return; }
    q_[h] = peer; head_ = n;
  }
  bool pop(uint32_t& peer) {
    const uint8_t t = tail_;
    if (t == head_) return false;
    peer = q_[t]; tail_ = (uint8_t)((t + 1) % ATTENTION_INBOX);
    return true;
  }
  uint32_t dropped() const { return dropped_; }
 private:
  volatile uint32_t q_[ATTENTION_INBOX] = {};
  volatile uint8_t head_ = 0, tail_ = 0;
  volatile uint32_t dropped_ = 0;
};

}  // namespace attention
