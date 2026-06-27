// Score.h — TTN-RFC-0010 §7: parts & melodies over the fleet pulse.
//
// The pulse (Pulse.h) is the shared clock; a *part* is what a node plays on it. A part
// is a `Phrase`: a sparse list of `Note`s on a sixteenth-note step grid that loops every
// `steps`. Pitched nodes (the K10's speaker) play `freq`; visual/percussive nodes (the
// V4 LEDs) use `freq = REST` and just flash on the struck step. Re-voicing the band is a
// table edit here, not a protocol change — the seam for melodies on purpose-built
// instruments later. Step resolution is Pulse's PULSE_STEPS_PER_BEAT.
#pragma once
#include <stdint.h>

namespace score {

// Equal-tempered pitches in Hz (rounded). REST = a struck step with no tone (a
// rhythmic/visual hit) — distinct from an empty step (no Note at all).
enum Pitch : uint16_t {
  REST = 0,
  C3 = 131, D3 = 147, E3 = 165, F3 = 175, G3 = 196, A3 = 220, B3 = 247,
  C4 = 262, D4 = 294, E4 = 330, F4 = 349, G4 = 392, A4 = 440, B4 = 494,
  C5 = 523, D5 = 587, E5 = 659, F5 = 698, G5 = 784, A5 = 880,
};

// One struck event on the phrase's step grid.
struct Note {
  uint16_t step;       // when in the phrase to strike (0 .. phrase steps-1)
  uint16_t freq;       // pitch Hz, or REST for a no-tone hit
  uint16_t dur_steps;  // hold length in steps (LED/visual sustain); >= 1
};

// A looping line: a sparse note list over `steps` total steps (the loop length).
struct Phrase {
  const Note* notes;
  uint16_t count;
  uint16_t steps;
};

// The note struck exactly at `step_in_phrase`, or nullptr if that step is empty.
inline const Note* noteAt(const Phrase& ph, uint16_t step_in_phrase) {
  for (uint16_t i = 0; i < ph.count; ++i)
    if (ph.notes[i].step == step_in_phrase) return &ph.notes[i];
  return nullptr;
}

}  // namespace score
