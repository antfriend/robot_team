// test_pulse.cpp — native (off-device) tests for the fleet-pulse chart SCENE
// extension (TTN-RFC-0010). Build with `make` in this directory.
//
// The scene id rides the pulse chart so that a multi-part song inherits the chart's
// two hard-won properties. Both are asserted here, because both are the reason the
// scene lives on the chart instead of in a message of its own:
//
//   1. Two-way wire compatibility. The fleet is flashed one cable at a time, so a
//      half-reflashed band must still share one time-base: a v1 (28-byte) beacon
//      still parses, and adding the scene must not disturb the bytes a v1 reader
//      looks at.
//   2. The scene SURVIVES CONDUCTOR HANDOFF. Kill the node that is counting and the
//      band keeps its place in the song — the property the whole extension exists for.
#include <cstdio>
#include <cstring>
#include <cstdint>

#include "Toot.h"
#include "Pulse.h"
#include "Score.h"

static int g_fail = 0;
#define CHECK(cond, msg)                                   \
  do {                                                     \
    if (!(cond)) { printf("FAIL: %s\n", msg); ++g_fail; }  \
    else { printf("pass: %s\n", msg); }                    \
  } while (0)

// A PULSE toot carrying `payload` of `len` bytes, as it would arrive off the radio.
static toot::Toot makePulseToot(const uint8_t* payload, uint8_t len) {
  toot::Toot t;
  t.type = toot::PULSE;
  t.payload_len = len;
  memcpy(t.payload, payload, len);
  return t;
}

int main() {
  // --- 1) v2 wire round-trip ------------------------------------------------
  uint8_t body[toot::PULSE_PAYLOAD_LEN];
  uint8_t n = toot::buildPulse(body, 0x10, 5, 123456, 100000, 500, 4, 0, 7);
  CHECK(n == 30, "buildPulse emits the 30-byte v2 payload");

  uint32_t cid = 0, era = 0;
  uint64_t cepoch = 0, downbeat = 0;
  uint16_t period = 0, scene = 0xFFFF;
  uint8_t meter = 0, flags = 0;
  toot::Toot t2 = makePulseToot(body, n);
  bool ok = toot::parsePulse(t2, cid, era, cepoch, downbeat, period, meter, flags,
                             &scene);
  CHECK(ok && cid == 0x10 && era == 5 && cepoch == 123456 && downbeat == 100000 &&
            period == 500 && meter == 4 && scene == 7,
        "parsePulse round-trips every chart field including scene");

  // --- 2) additive: the scene must not disturb the v1 byte range ------------
  uint8_t body_s0[toot::PULSE_PAYLOAD_LEN];
  uint8_t body_s9[toot::PULSE_PAYLOAD_LEN];
  toot::buildPulse(body_s0, 0x10, 5, 123456, 100000, 500, 4, 0, 0);
  toot::buildPulse(body_s9, 0x10, 5, 123456, 100000, 500, 4, 0, 9);
  CHECK(memcmp(body_s0, body_s9, toot::PULSE_PAYLOAD_LEN_V1) == 0,
        "scene is purely additive: bytes [0..27] are identical regardless of scene");
  CHECK(memcmp(body_s0 + 28, body_s9 + 28, 2) != 0,
        "...and the scene really is carried in the [28..29] tail");

  // --- 3) a v1 beacon from a not-yet-reflashed node still parses -------------
  scene = 0xFFFF;
  toot::Toot t1 = makePulseToot(body_s9, toot::PULSE_PAYLOAD_LEN_V1);  // truncated
  ok = toot::parsePulse(t1, cid, era, cepoch, downbeat, period, meter, flags, &scene);
  CHECK(ok, "a v1 (28-byte) beacon still parses — a half-reflashed band shares time");
  CHECK(scene == 0, "a v1 beacon reads as scene 0 rather than garbage");

  // Too short is still rejected.
  toot::Toot t_short = makePulseToot(body_s9, 27);
  CHECK(!toot::parsePulse(t_short, cid, era, cepoch, downbeat, period, meter, flags,
                          &scene),
        "a payload below the v1 length is still rejected");

  // The scene-out pointer is optional (v1 call sites keep compiling + working).
  CHECK(toot::parsePulse(t2, cid, era, cepoch, downbeat, period, meter, flags),
        "parsePulse works without asking for the scene");

  // --- 4) a cold band starts at scene 0 -------------------------------------
  pulse::Engine cond;
  cond.begin(0x10, 0);
  pulse::Chart out;
  uint64_t oepoch = 0;
  CHECK(!cond.update(1000, out, oepoch), "no chart during the listen window");
  CHECK(cond.update(3000, out, oepoch), "self-appoints after the listen window");
  CHECK(cond.conductor() && cond.scene() == 0, "a cold conductor starts at scene 0");
  CHECK(out.scene_id == 0, "the emitted chart carries the scene");

  uint16_t got = 0xFFFF;
  CHECK(cond.sceneChanged(got) && got == 0,
        "sceneChanged fires once on first adopting a chart (so the part gets selected)");
  CHECK(!cond.sceneChanged(got), "...and does not fire again while the scene holds");

  // --- 5) only the conductor may author a scene -----------------------------
  const uint32_t era_before = cond.chart().era;
  CHECK(cond.setScene(3, 3000), "the conductor moves the band to a scene");
  CHECK(cond.scene() == 3, "the chart carries the new scene");
  CHECK(cond.chart().era == era_before + 1, "a scene move bumps the era (chart revision)");
  CHECK(!cond.setScene(3, 3100), "re-issuing the same scene is a no-op");
  CHECK(cond.chart().era == era_before + 1, "...and does not churn the era");

  CHECK(cond.sceneChanged(got) && got == 3, "sceneChanged reports the move");

  // The move schedules an immediate beacon rather than waiting a resync period.
  CHECK(cond.update(3200, out, oepoch) && out.scene_id == 3,
        "a scene move beacons immediately so the band turns the page together");

  // --- 6) a follower adopts the scene, and cannot author one ----------------
  pulse::Engine foll;
  foll.begin(0x11, 0);
  pulse::Chart beacon;
  beacon.conductor_id = 0x10;
  beacon.era = 5;
  beacon.downbeat_epoch = 100000;
  beacon.beat_period_ms = 500;
  beacon.meter_beats = 4;
  beacon.scene_id = 3;
  foll.onBeacon(beacon, /*conductor_epoch=*/200000, /*recv_ms=*/100);
  CHECK(!foll.conductor() && foll.scene() == 3, "a follower adopts the chart's scene");
  CHECK(foll.sceneChanged(got) && got == 3,
        "a node joining a running band selects the scene already in progress");

  CHECK(!foll.setScene(9, 200), "a follower declines to author a scene (no forking)");
  CHECK(foll.scene() == 3, "...and stays on the conductor's scene");

  // --- 7) THE POINT: the scene survives conductor handoff -------------------
  // The conductor goes silent. After the timeout the follower takes the baton.
  const uint64_t downbeat_before = foll.chart().downbeat_epoch;
  const uint32_t follow_era = foll.chart().era;
  const uint32_t takeover_at = 100 + PULSE_CONDUCTOR_TIMEOUT_MS + 0x11 * PULSE_TAKEOVER_STAGGER_MS + 1;
  CHECK(foll.update(takeover_at, out, oepoch), "the follower takes over after the timeout");
  CHECK(foll.conductor(), "...becoming the conductor");
  CHECK(foll.scene() == 3,
        "THE SONG KEEPS ITS PLACE: the new conductor inherits scene 3");
  CHECK(out.scene_id == 3, "...and re-broadcasts the inherited scene");
  CHECK(foll.chart().downbeat_epoch == downbeat_before,
        "the beat does not lurch across the handoff (downbeat preserved)");
  CHECK(foll.chart().era == follow_era + 1, "the era bumps so followers prefer the new chart");
  CHECK(!foll.sceneChanged(got), "handoff is not a scene change — parts do not re-select");

  // A *cold* start is different from a takeover: it restarts the song from the top.
  pulse::Engine cold;
  cold.begin(0x12, 0);
  cold.update(3000, out, oepoch);
  CHECK(cold.scene() == 0, "a cold start restarts the song at scene 0, unlike a takeover");

  // --- 8) scene -> phrase selection (Score.h) -------------------------------
  static const score::Note kIntro[] = {{0, score::C4, 1}};
  static const score::Note kFinale[] = {{0, score::E4, 1}, {4, score::G4, 1}};
  static const score::Note kPulseHit[] = {{0, score::REST, 1}};

  // A node that is silent in scene 0, enters in scene 1, and has a finale line.
  static const score::ScenePhrase kLateEntry[] = {
      {1, {kIntro, 1, 16}},
      {2, {kFinale, 2, 16}},
  };
  static const score::Part kLate = {kLateEntry, 2};

  CHECK(score::phraseForScene(kLate, 0) == nullptr,
        "a node with no entry for a scene is SILENT there (progressive entry)");
  const score::Phrase* ph = score::phraseForScene(kLate, 1);
  CHECK(ph && ph->count == 1 && ph->notes[0].freq == score::C4,
        "an exact scene match selects that scene's phrase");
  ph = score::phraseForScene(kLate, 2);
  CHECK(ph && ph->count == 2, "a later scene selects a different phrase");

  // A timekeeper that plays the same line throughout costs one wildcard row.
  static const score::ScenePhrase kAlways[] = {
      {score::kAllScenes, {kPulseHit, 1, 4}},
      {2, {kFinale, 2, 16}},
  };
  static const score::Part kKeeper = {kAlways, 2};
  ph = score::phraseForScene(kKeeper, 0);
  CHECK(ph && ph->count == 1 && ph->steps == 4, "kAllScenes is the fallback line");
  ph = score::phraseForScene(kKeeper, 2);
  CHECK(ph && ph->count == 2, "an exact scene match still beats the wildcard");

  printf("\n%s (%d failure%s)\n", g_fail ? "FAILED" : "ALL PASS", g_fail,
         g_fail == 1 ? "" : "s");
  return g_fail ? 1 : 0;
}
