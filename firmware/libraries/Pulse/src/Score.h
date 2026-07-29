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

// The note to sound for the steps a loop pass CROSSED, not just the one it landed on.
//
// DEFENSIVE, not a fix for an observed defect — worth being clear about, because it was added
// on a wrong diagnosis and the honest version is more useful than the story that prompted it.
// `Engine::stepTick` fires once for the step the clock is on now, so a pass longer than one
// step (125 ms at 120 BPM) jumps the steps in between and their notes are never reported. On
// the bench that has NOT been observed to lose a note: a double-time duet measured 4.0 s per
// phrase with all 15 notes present in every cycle. But the hazard is real and the margin is
// thin — the percept-window flash append alone takes 60-220 ms (companion.md §6), well over a
// step, and a duet's notes are only 2 steps apart. So this closes it cheaply rather than
// leaving the melody dependent on the loop never stalling.
//
// Returns the LAST note among the crossed steps rather than the first: the point is to sound
// what should be sounding *now*, not to belatedly flam a note whose moment has passed. `speed`
// is the duet time-scale (1 = as written, 2 = double time); `phrase_steps` is the already
// scaled wrap length. The scan is bounded to one phrase so a long stall cannot spin.
inline const Note* noteForCrossedSteps(const Phrase& ph, uint32_t from_exclusive,
                                       uint32_t to_inclusive, uint8_t speed,
                                       uint16_t phrase_steps) {
  if (!phrase_steps) return nullptr;
  if (speed < 1) speed = 1;
  if (to_inclusive - from_exclusive > phrase_steps)
    from_exclusive = to_inclusive - phrase_steps;   // never rescan more than one wrap
  const Note* hit = nullptr;
  for (uint32_t s = from_exclusive + 1; s <= to_inclusive; ++s) {
    const Note* nt = noteAt(ph, (uint16_t)((s % phrase_steps) * speed));
    if (nt) hit = nt;
  }
  return hit;
}

// --- Scenes: one node's line across a multi-part song -----------------------
// The pulse chart carries a `scene_id` (Pulse.h), so the band shares not just a tempo
// but a position in a song. A `Part` is this node's whole score: which Phrase it loops
// in each scene. Selecting a part stays a table lookup — re-arranging the song is a
// data edit here, never a protocol change, exactly as re-voicing the band already is.
//
// A scene with no entry for this node returns nullptr, which is a first-class state,
// not an error: it means this node is SILENT in that scene. That's what lets an
// ensemble enter progressively — members join the story one at a time — without any
// per-node special-casing in the sketches.
const uint16_t kAllScenes = 0xFFFF;  // wildcard: this line plays in every scene

struct ScenePhrase {
  uint16_t scene;    // scene id, or kAllScenes to match any scene
  Phrase phrase;
};

struct Part {
  const ScenePhrase* scenes;
  uint16_t count;
};

// This node's phrase for `scene`, or nullptr if it is silent there. An exact scene
// match wins; a kAllScenes entry is the fallback, so "same line throughout" costs one
// row rather than one per scene.
inline const Phrase* phraseForScene(const Part& part, uint16_t scene) {
  const Phrase* fallback = nullptr;
  for (uint16_t i = 0; i < part.count; ++i) {
    if (part.scenes[i].scene == scene) return &part.scenes[i].phrase;
    if (part.scenes[i].scene == kAllScenes && !fallback)
      fallback = &part.scenes[i].phrase;
  }
  return fallback;
}

}  // namespace score
