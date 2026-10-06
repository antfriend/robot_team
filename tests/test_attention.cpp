// test_attention.cpp — the EPS arbiter (docs/design/cardputer-sensorium.md §7 Phase S1).
//
// S1's done-condition is a hardware one: "tilting, clapping, and a neighbour rejoining each
// print the right winner, and the winner decays back to idle within ~3 s." This suite pins
// the same four scenarios against the library, plus the three guards that make it an
// arbiter rather than a meter (decay, dwell, margin) and the one rule that gives `conf`
// its meaning (an explained stimulus never wins).
#include <cstdio>
#include "Attention.h"

static int gChecks = 0, gFails = 0;
static void check(bool ok, const char* what) {
  ++gChecks;
  if (!ok) { ++gFails; printf("  FAIL: %s\n", what); }
}

using namespace attention;

// Run the arbiter forward in 20 ms passes (a loop that is inside its budget) and return
// when it first went idle, or 0 if it did not within `limit_ms`.
static uint32_t idleAfter(Arbiter& a, uint32_t from, uint32_t limit_ms) {
  for (uint32_t t = from; t <= from + limit_ms; t += 20) {
    a.tick(t);
    if (a.winner() == MOD_IDLE) return t - from;
  }
  return 0;
}

int main() {
  printf("Attention tests\n");

  // ---- 1. the currency ----------------------------------------------------------------
  check(eps(255, 0) == 255, "unexplained full salience = EPS 255");
  check(eps(255, 255) == 0, "fully explained = EPS 0, however loud");
  check(eps(200, 128) == 99, "EPS = sal x (255-conf)/255");
  check(decayed(200, 0, ATTENTION_HALF_LIFE_MS, ATTENTION_HALF_LIFE_MS) == 100,
        "one half-life halves");
  check(decayed(200, 1000, 500, ATTENTION_HALF_LIFE_MS) == 0,
        "a backwards clock decays to silence, never to fresh");
  {
    bool mono = true; uint8_t prev = 255;
    for (uint32_t t = 0; t < 8 * ATTENTION_HALF_LIFE_MS; t += 7) {
      const uint8_t v = decayed(255, 0, t, ATTENTION_HALF_LIFE_MS);
      if (v > prev) mono = false;
      prev = v;
    }
    check(mono, "decay is monotone");
  }

  // ---- 2. idle at rest; an explained stimulus never wins -------------------------------
  {
    Arbiter a;
    check(!a.tick(0) && a.winner() == MOD_IDLE, "nothing observed = idle");
    check(!a.observe(MOD_SOUND, 255, 255, 10), "our own tone (conf 255) is not taken");
    a.tick(20);
    check(a.winner() == MOD_IDLE, "...and cannot take the screen");
    a.observe(MOD_MOTION, 30, 0, 40);          // a tremor below the idle floor
    a.tick(60);
    check(a.winner() == MOD_IDLE, "sub-floor stimulus does not wake the face");
  }

  // ---- 3. S1 scenario: a clap wins, then decays to idle within ~3 s -------------------
  {
    Arbiter a;
    a.observe(MOD_SOUND, 255, 0, 1000, 4200);
    check(a.tick(1000) && a.winner() == MOD_SOUND, "a clap takes the screen at once");
    check(a.detail(MOD_SOUND) == 4200, "the held stimulus keeps its detail");
    const uint32_t gone = idleAfter(a, 1000, 5000);
    check(gone >= ATTENTION_DWELL_MS, "it holds for at least the dwell");
    check(gone > 0 && gone <= 3000, "and is back to idle within ~3 s");
    printf("  clap: idle after %lu ms\n", (unsigned long)gone);
  }

  // ---- 4. S1 scenario: a tilt, fed through MotionSalience at 50 Hz ---------------------
  {
    Arbiter a; MotionSalience ms;
    uint32_t t = 0;
    for (; t < 3000; t += 20) {                // flat on the bench: gravity on Z
      a.observe(MOD_MOTION, ms.feed(0, 0, 1000), 0, t);
      a.tick(t);
    }
    check(a.winner() == MOD_IDLE, "a deck lying still is idle");
    // Lean it ~35 degrees over 300 ms, then HOLD the lean.
    bool won = false; uint32_t tiltEnd = 0;
    for (int i = 0; i <= 15; ++i, t += 20) {
      const float k = (float)i / 15.0f;
      a.observe(MOD_MOTION, ms.feed((int)(574 * k), 0, (int)(1000 - 181 * k)), 0, t);
      if (a.tick(t) && a.winner() == MOD_MOTION) won = true;
    }
    check(won, "tilting takes the screen for motion");
    tiltEnd = t;
    uint32_t idleAt = 0;
    for (; t < tiltEnd + 6000; t += 20) {
      a.observe(MOD_MOTION, ms.feed(574, 0, 819), 0, t);
      a.tick(t);
      if (a.winner() == MOD_IDLE && !idleAt) idleAt = t;
    }
    check(idleAt != 0, "HOLDING a tilt is not news: back to idle");
    check(idleAt && idleAt - tiltEnd <= 3500, "within ~3 s of the lean ending");
    printf("  tilt: idle %lu ms after the lean ended\n", (unsigned long)(idleAt - tiltEnd));
    // A key press explains the jolt that comes with it.
    MotionSalience m2; Arbiter b;
    m2.feed(0, 0, 1000);
    const uint8_t jolt = m2.feed(0, 0, 1500);
    check(jolt == 255, "a 500 mg jolt is full motion salience");
    b.observe(MOD_MOTION, jolt, 230, 100);
    b.tick(100);
    check(b.winner() == MOD_IDLE, "a jolt explained by a key press does not win");
  }

  // ---- 5. S1 scenario: a neighbour rejoining -------------------------------------------
  {
    Novelty nv; Arbiter a;
    Novelty::Event ev; uint32_t gap, peer;
    check(nv.heard(0x11, 0, ev, gap) == ATTENTION_SAL_NEW && ev == Novelty::EV_NEW,
          "a first-heard peer is new");
    uint32_t t = 0;
    bool routineWon = false;
    for (int i = 0; i < 30; ++i) {             // HELLOs every 2 s, a few late ones
      t += (i % 7 == 3) ? 2600 : 2000;
      const uint8_t s = nv.heard(0x11, t, ev, gap);
      if (s) a.observe(MOD_NEIGHBOUR, s, 0, t, 0x11);
      if (a.tick(t) && a.winner() == MOD_NEIGHBOUR) routineWon = true;
      check(nv.quiet(t, peer, gap) == 0, "a routine peer never goes quiet");
    }
    check(!routineWon, "routine HELLOs never seize the screen");
    const uint32_t typ = nv.typicalGap(0x11);
    check(typ > 1900 && typ < 2300, "the baseline learned the HELLO period");
    // It power-cycles: 8 s of silence, then it speaks again.
    const uint32_t off = t;
    for (t = off + 20; t < off + 8000; t += 20) {
      const uint8_t s = nv.quiet(t, peer, gap);
      if (s) a.observe(MOD_NEIGHBOUR, s, 0, t, peer);
      a.tick(t);
    }
    check(a.detail(MOD_NEIGHBOUR) == 0x11, "going quiet was noticed, for the right peer");
    const uint8_t s = nv.heard(0x11, t, ev, gap);
    check(ev == Novelty::EV_RETURNED && gap >= 7980, "an 8 s silence is a return");
    check(s >= 128, "a return is at least as salient as going quiet");
    a.observe(MOD_NEIGHBOUR, s, 0, t, 0x11);
    a.tick(t);
    check(a.winner() == MOD_NEIGHBOUR, "a neighbour rejoining wins");
    const uint32_t gone = idleAfter(a, t, 5000);
    check(gone > 0 && gone <= 3000, "and decays back to idle within ~3 s");
    // The dropout did not teach the baseline.
    check(nv.typicalGap(0x11) == typ, "a dropout does not stretch the baseline");
    // A short power-cycle (7 s) is still a return: the threshold is 3 x the peer's own
    // period (6 s here), not Social's 10 s fade. Two dropped HELLOs (6 s) are not.
    nv.heard(0x11, t + 2000, ev, gap);
    nv.heard(0x11, t + 8000, ev, gap);
    check(ev == Novelty::EV_NONE, "two dropped HELLOs (6 s) are routine");
    nv.heard(0x11, t + 15000, ev, gap);
    check(ev == Novelty::EV_RETURNED, "a 7 s reboot gap is caught (below the 10 s fade)");
  }

  // ---- 6. hysteresis: dwell and margin --------------------------------------------------
  {
    Arbiter a;
    a.observe(MOD_SOUND, 150, 0, 0);
    a.tick(0);
    a.observe(MOD_MOTION, 255, 0, 100);        // bigger, but inside the dwell
    a.tick(100);
    check(a.winner() == MOD_SOUND, "dwell: the incumbent holds 1.5 s regardless");
    a.tick(ATTENTION_DWELL_MS);
    check(a.winner() == MOD_MOTION, "after the dwell the stronger stimulus takes over");
  }
  {
    Arbiter a;
    a.observe(MOD_SOUND, 200, 0, 0);
    a.tick(0);
    // Keep both topped up so neither decays; the challenger is +20%, under the margin.
    for (uint32_t t = 0; t <= 4000; t += 20) {
      a.observe(MOD_SOUND, 200, 0, t);
      a.observe(MOD_MOTION, 240, 0, t);
      a.tick(t);
    }
    check(a.winner() == MOD_SOUND, "a +20% challenger does not unseat (margin 25%)");
    for (uint32_t t = 4000; t <= 4100; t += 20) {
      a.observe(MOD_SOUND, 180, 0, t);
      a.observe(MOD_MOTION, 240, 0, t);
      a.tick(t);
    }
    // sound is peak-held at 200 decaying; a weaker sample cannot reset it upward
    check(a.sal(MOD_SOUND) == 200, "peak-hold: a weaker sample does not replace the held one");
  }
  {
    Arbiter a;
    a.observe(MOD_SOUND, 255, 0, 0);
    a.tick(0);
    check(a.total(0) == 255, "total() sums the decayed EPS");
    a.observe(MOD_MOTION, 100, 0, 0);
    check(a.total(0) == 355, "...across modalities");
  }

  // ---- 7. the inbox hands off in order, and drops rather than overwrites --------------
  {
    Inbox in; uint32_t p;
    for (uint32_t i = 1; i <= ATTENTION_INBOX + 3; ++i) in.push(i);
    check(in.dropped() == 4, "a full inbox drops the newest (N-1 usable slots)");
    bool order = true;
    for (uint32_t i = 1; i < ATTENTION_INBOX; ++i) if (!in.pop(p) || p != i) order = false;
    check(order && !in.pop(p), "FIFO, nothing torn");
  }

  printf("%d checks, %d failures\n", gChecks, gFails);
  return gFails ? 1 : 0;
}
