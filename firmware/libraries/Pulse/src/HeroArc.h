// HeroArc.h — the hero's-arc song: the fleet's own history, scored (TTN-RFC-0010 §7).
//
// One song, six scenes, told in the order the fleet was actually built. The pulse
// chart's `scene_id` (Pulse.h) is the band's shared position in this story; each node
// looks up its line with score::phraseForScene, and a missing row means SILENT in that
// scene — members enter progressively, the way they entered the project.
//
//   0 ALONE   V4-A alone, keeping time.               (the bridge before the mesh)
//   1 ALLY    V4-B's backbeat answers.                (the 3rd node joins, 2026-06-25)
//   2 GROOVE  V4-C's hi-hat completes the groove —    (the fleet is whole, 2026-07-16 —
//             and still there is no pitched voice.     but nobody sings yet)
//   3 ORDEAL  everything falls away but a heartbeat.  (kill the conductor HERE, live:
//             the chart — and the song's place in it — survives the handoff)
//   4 RETURN  the T-Deck comes back with harmony.     (the roamer returns with the map)
//   5 FINALE  Ode to Joy, everyone playing.
//
// The whole score lives in this one header so re-arranging the song is a data edit in
// a single file, never a protocol change. Each sketch includes it and references only
// its own Part; the linker's gc-sections drops the rest.
#pragma once
#include "Score.h"

namespace heroarc {

enum Scene : uint16_t {
  SCENE_ALONE  = 0,
  SCENE_ALLY   = 1,
  SCENE_GROOVE = 2,
  SCENE_ORDEAL = 3,
  SCENE_RETURN = 4,
  SCENE_FINALE = 5,
  SCENE_COUNT  = 6,
};

// --- story pacing (the song walks itself; see Pulse::serviceSong + the T-Deck) ------
// One place for the tempo of the STORY (distinct from the musical tempo in Pulse.h).
// The conductor auto-advances the early scenes on SCENE_HOLD_MS; it holds at SCENE_ORDEAL
// (the grief the roamer must return to). The returning T-Deck drives the last two scenes:
// it dwells ORDEAL_HOLD_MS in the grief, then calls the RETURN, then RETURN_HOLD_MS later
// the FINALE. So `g` starts the song and it plays to the end on its own — but the band
// waits at grief whenever the T-Deck is away, and rejoins its part the moment it is back.
static const uint32_t SCENE_HOLD_MS  = 6000;  // conductor: each early scene's dwell (0->3)
static const uint32_t ORDEAL_HOLD_MS = 6000;  // roamer: grief dwell before the turn
static const uint32_t RETURN_HOLD_MS = 9000;  // roamer: let the RETURN harmony play out

// Short scene names for screens/serial (fits the T-Deck status line).
inline const char* sceneName(uint16_t s) {
  switch (s) {
    case SCENE_ALONE:  return "ALONE";
    case SCENE_ALLY:   return "ALLY";
    case SCENE_GROOVE: return "GROOVE";
    case SCENE_ORDEAL: return "ORDEAL";
    case SCENE_RETURN: return "RETURN";
    case SCENE_FINALE: return "FINALE";
    default:           return "?";
  }
}

// --- Phrases (16-step bar = one 4/4 measure @ 120 BPM; melodies loop 64 = 4 bars) ---

// V4-A: four-on-the-floor kick, the pulse the whole story rides.
static const score::Note kKickNotes[] = {
  {0, score::C4, 1}, {4, score::C4, 1}, {8, score::C4, 1}, {12, score::C4, 1},
};
static const score::Phrase kKick = {kKickNotes, 4, 16};

// V4-B: backbeat "snare" on 2 & 4.
static const score::Note kSnareNotes[] = {
  {4, score::G3, 1}, {12, score::G3, 1},
};
static const score::Phrase kSnare = {kSnareNotes, 2, 16};

// V4-B, the ordeal: a bare lub-dub heartbeat (30/min) — the minimum that proves the
// clock is alive. This is what carries the song across the conductor's death.
static const score::Note kHeartNotes[] = {
  {0, score::G3, 1}, {2, score::G3, 1},
};
static const score::Phrase kHeart = {kHeartNotes, 2, 16};

// V4-C: offbeat hi-hat on the "&" of each beat.
static const score::Note kHatNotes[] = {
  {2, score::C4, 1}, {6, score::C4, 1}, {10, score::C4, 1}, {14, score::C4, 1},
};
static const score::Phrase kHat = {kHatNotes, 4, 16};

// Ode to Joy, lead line (4 bars): E E F G | G F E D | C C D E | E. D D—
static const score::Note kOdeLeadNotes[] = {
  {0,  score::E4, 4}, {4,  score::E4, 4}, {8,  score::F4, 4}, {12, score::G4, 4},
  {16, score::G4, 4}, {20, score::F4, 4}, {24, score::E4, 4}, {28, score::D4, 4},
  {32, score::C4, 4}, {36, score::C4, 4}, {40, score::D4, 4}, {44, score::E4, 4},
  {48, score::E4, 6}, {54, score::D4, 2}, {56, score::D4, 8},
};
static const score::Phrase kOdeLead = {
    kOdeLeadNotes, sizeof(kOdeLeadNotes) / sizeof(kOdeLeadNotes[0]), 64};

// Ode to Joy, harmony a third below (the T-Deck's voice from the 2026-07-06 duet).
static const score::Note kOdeHarmNotes[] = {
  {0,  score::C4, 4}, {4,  score::C4, 4}, {8,  score::D4, 4}, {12, score::E4, 4},
  {16, score::E4, 4}, {20, score::D4, 4}, {24, score::C4, 4}, {28, score::B3, 4},
  {32, score::A3, 4}, {36, score::A3, 4}, {40, score::B3, 4}, {44, score::C4, 4},
  {48, score::C4, 6}, {54, score::B3, 2}, {56, score::B3, 8},
};
static const score::Phrase kOdeHarm = {
    kOdeHarmNotes, sizeof(kOdeHarmNotes) / sizeof(kOdeHarmNotes[0]), 64};

// --- Parts (one per band role; a scene with no row = silent in that scene) ---------

// V4-A the timekeeper: present from the first scene, silent only through the ordeal
// (its death is the ordeal — scene 3 has no row).
static const score::ScenePhrase kTimekeeperScenes[] = {
  {SCENE_ALONE, kKick}, {SCENE_ALLY, kKick}, {SCENE_GROOVE, kKick},
  {SCENE_RETURN, kKick}, {SCENE_FINALE, kKick},
};
static const score::Part kTimekeeper = {
    kTimekeeperScenes, sizeof(kTimekeeperScenes) / sizeof(kTimekeeperScenes[0])};

// V4-B the ally: backbeat once it joins; alone with the heartbeat in the ordeal.
static const score::ScenePhrase kBackbeatScenes[] = {
  {SCENE_ALLY, kSnare}, {SCENE_GROOVE, kSnare}, {SCENE_ORDEAL, kHeart},
  {SCENE_RETURN, kSnare}, {SCENE_FINALE, kSnare},
};
static const score::Part kBackbeat = {
    kBackbeatScenes, sizeof(kBackbeatScenes) / sizeof(kBackbeatScenes[0])};

// V4-C the edge: hats complete the groove; silent through the ordeal.
static const score::ScenePhrase kHihatScenes[] = {
  {SCENE_GROOVE, kHat}, {SCENE_RETURN, kHat}, {SCENE_FINALE, kHat},
};
static const score::Part kHihat = {
    kHihatScenes, sizeof(kHihatScenes) / sizeof(kHihatScenes[0])};

// T-Deck the returning roamer: arrives with harmony (the song's first pitched voice),
// then carries the lead in the finale (the K10, when it rejoins the roster, takes
// harmony back — a two-row table edit here).
static const score::ScenePhrase kConsoleScenes[] = {
  {SCENE_RETURN, kOdeHarm}, {SCENE_FINALE, kOdeLead},
};
static const score::Part kConsole = {
    kConsoleScenes, sizeof(kConsoleScenes) / sizeof(kConsoleScenes[0])};

// Cardputer the newcomer — the fleet's EARS. It arrives after the story is already
// being told, and it is the one node with a microphone, so its line is to LISTEN: it
// is silent through every scene and joins only the finale, doubling the harmony under
// the T-Deck's lead. (Its acoustic percepts run the whole time; the silence is the
// part, not an omission.)
static const score::ScenePhrase kNewcomerScenes[] = {
  {SCENE_FINALE, kOdeHarm},
};
static const score::Part kNewcomer = {
    kNewcomerScenes, sizeof(kNewcomerScenes) / sizeof(kNewcomerScenes[0])};

// K10 the percept leaf (future — still on v1 firmware, off the band roster): joins the
// finale with the harmony under the T-Deck's lead. Defined now so rejoining is a
// reflash, not a rewrite.
static const score::ScenePhrase kPerceptScenes[] = {
  {SCENE_FINALE, kOdeHarm},
};
static const score::Part kPercept = {
    kPerceptScenes, sizeof(kPerceptScenes) / sizeof(kPerceptScenes[0])};

}  // namespace heroarc
