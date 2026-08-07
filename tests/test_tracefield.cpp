// test_tracefield.cpp — the stigmergic trace field (TTDB-RFC-0010 §5, RAM-only).
//
// What is actually worth pinning here, as opposed to what is easy to pin:
//   * decay is CONTINUOUS across half-life boundaries (the shift-then-interpolate seam)
//   * merge is IDEMPOTENT and ORDER-FREE — the properties that make it a field and not a
//     message, so they are tested as properties, not as one example
//   * a digest round-trips, and a digest from an older/newer/garbage sender is REFUSED
//     rather than read as strengths
//   * a deposit reinforces against the DECAYED value, not the stored one (the bug that
//     would make an old trace un-fadeable by re-striking it)
//   * millis() rollover and a backwards clock decay to SILENCE, never to "fresh"
#include <cstdio>
#include <cstring>
#include "TraceField.h"

static int gChecks = 0, gFails = 0;
static void check(bool ok, const char* what) {
  ++gChecks;
  if (!ok) { ++gFails; printf("  FAIL: %s\n", what); }
}

using namespace tracefield;

static const uint32_t HL = 20000;   // the shipped default half-life

int main() {
  printf("TraceField tests\n");

  // ---- 1. decay basics -------------------------------------------------------------
  check(decayed(200, 0, 0, HL) == 200, "no time passed = no decay");
  check(decayed(200, 0, HL, HL) == 100, "one half-life halves");
  check(decayed(200, 0, 2 * HL, HL) == 50, "two half-lives quarter");
  check(decayed(200, 0, 8 * HL, HL) == 0, "eight half-lives = silence");
  check(decayed(200, 0, 100 * HL, HL) == 0, "far future = silence, not UB");
  check(decayed(0, 0, 1, HL) == 0, "a dead cell stays dead");

  // ⚠ The seam: shift-then-interpolate must not step at the boundary. Approaching HL
  // from below must land on the same value the shift gives AT HL.
  const uint8_t just_before = decayed(200, 0, HL - 1, HL);
  const uint8_t at_boundary = decayed(200, 0, HL, HL);
  check(just_before == at_boundary || just_before == at_boundary + 1,
        "decay is continuous across the half-life boundary (no step)");

  // Monotone: decay must never increase as time passes. This is the property that a
  // sloppy interpolation breaks, and it would sound like a note getting louder on its own.
  bool monotone = true;
  uint8_t prev = 255;
  for (uint32_t t = 0; t <= 8 * HL; t += HL / 16) {
    const uint8_t v = decayed(255, 0, t, HL);
    if (v > prev) { monotone = false; break; }
    prev = v;
  }
  check(monotone, "decay is monotone non-increasing over 8 half-lives");

  // ---- 2. deposit reinforces against the DECAYED value ------------------------------
  {
    Field f(HL);
    f.deposit(3, 200, 0);
    check(f.strengthAt(3, 0) == 200, "deposit lands");
    check(f.strengthAt(3, HL) == 100, "deposited trace fades on read");
    // Re-strike after one half-life: 100 (decayed) + 100 = 200, NOT 200 + 100 = 255.
    f.deposit(3, 100, HL);
    check(f.strengthAt(3, HL) == 200,
          "re-strike adds to the decayed value, not the stored one");
    f.deposit(3, 200, HL);
    check(f.strengthAt(3, HL) == 255, "deposit saturates at 255, never wraps");
  }

  // ---- 3. cells are independent, and out-of-range is a no-op ------------------------
  {
    Field f(HL);
    f.deposit(0, 100, 0);
    check(f.strengthAt(1, 0) == 0, "a deposit touches exactly one cell");
    f.deposit(CELLS, 255, 0);        // out of range
    f.deposit(200, 255, 0);
    check(f.energy(0) == 100, "an out-of-range cell is dropped, not wrapped into cell 0");
    check(f.strengthAt(CELLS, 0) == 0, "reading out of range is 0, not UB");
  }

  // ---- 4. digest round-trip ---------------------------------------------------------
  {
    Field a(HL);
    a.deposit(2, 180, 0);
    a.deposit(9, 60, 0);
    uint8_t d[DIGEST_LEN];
    check(a.buildDigest(d, sizeof(d), 0) == DIGEST_LEN, "digest is DIGEST_LEN bytes");
    check(d[0] == DIGEST_MAGIC && d[1] == DIGEST_VERSION, "digest carries magic+version");
    check(d[2 + 2] == 180 && d[2 + 9] == 60, "digest carries decayed strengths by cell");

    uint8_t tiny[DIGEST_LEN - 1];
    check(a.buildDigest(tiny, sizeof(tiny), 0) == 0,
          "a short buffer yields NOTHING, never a partial digest");

    Field b(HL);
    check(b.merge(d, sizeof(d), 0) == 2, "merge raises exactly the cells that were set");
    check(b.strengthAt(2, 0) == 180 && b.strengthAt(9, 0) == 60, "merged values land");
  }

  // ---- 5. the digest is DECAYED AT THE SENDER, so no clock is compared --------------
  {
    Field a(HL);
    a.deposit(5, 200, 0);
    uint8_t d[DIGEST_LEN];
    a.buildDigest(d, sizeof(d), 2 * HL);         // built two half-lives later
    check(d[2 + 5] == 50, "buildDigest ships the decayed value, not the stored one");
    // A receiver whose clock bears no relation to the sender's still gets it right.
    Field b(HL);
    b.merge(d, sizeof(d), 999999);
    check(b.strengthAt(5, 999999) == 50,
          "a receiver on an unrelated clock adopts the value as-of-arrival");
  }

  // ---- 6. merge is IDEMPOTENT and ORDER-FREE (the field properties) -----------------
  {
    Field a(HL), b(HL);
    a.deposit(1, 100, 0); a.deposit(4, 200, 0);
    b.deposit(1, 150, 0); b.deposit(7, 90, 0);
    uint8_t da[DIGEST_LEN], db[DIGEST_LEN];
    a.buildDigest(da, sizeof(da), 0);
    b.buildDigest(db, sizeof(db), 0);

    Field x(HL), y(HL);
    x.merge(da, sizeof(da), 0); x.merge(db, sizeof(db), 0);   // a then b
    y.merge(db, sizeof(db), 0); y.merge(da, sizeof(da), 0);   // b then a
    bool same = true;
    for (uint8_t i = 0; i < CELLS; ++i)
      if (x.strengthAt(i, 0) != y.strengthAt(i, 0)) same = false;
    check(same, "merge is order-free: a-then-b equals b-then-a");
    check(x.strengthAt(1, 0) == 150, "max wins on a contested cell");

    const uint8_t again = x.merge(da, sizeof(da), 0);
    check(again == 0, "merge is idempotent: re-merging raises nothing");
  }

  // ---- 7. a digest we must NOT read as strengths ------------------------------------
  {
    Field f(HL);
    uint8_t bad[DIGEST_LEN];
    memset(bad, 0x55, sizeof(bad));
    check(f.merge(bad, sizeof(bad), 0) == 0, "wrong magic is refused");
    bad[0] = DIGEST_MAGIC; bad[1] = DIGEST_VERSION + 7;
    check(f.merge(bad, sizeof(bad), 0) == 0, "unknown version is refused");
    bad[1] = DIGEST_VERSION;
    check(f.merge(bad, DIGEST_LEN - 1, 0) == 0, "a truncated digest is refused whole");
    check(f.merge(nullptr, DIGEST_LEN, 0) == 0, "a null digest is refused");
    check(f.energy(0) == 0, "a refused digest leaves the field untouched");
  }

  // ---- 8. clock hazards: rollover and a backwards stamp both go SILENT --------------
  {
    Field f(HL);
    const uint32_t near_wrap = 0xFFFFFFFFu - (HL / 2);
    f.deposit(6, 200, near_wrap);
    // Wrap past zero by half a half-life: total elapsed = HL, so 200 -> 100.
    const uint32_t after = near_wrap + HL;      // wraps
    check(f.strengthAt(6, after) == 100,
          "decay is correct across the millis() 49.7-day rollover");

    Field g(HL);
    g.deposit(6, 200, 1000000);
    // Read "before" the deposit (clock stepped back): unsigned wrap makes dt enormous.
    check(g.strengthAt(6, 500000) == 0,
          "a backwards clock decays to silence, never reads as freshly deposited");
  }

  // ---- 9. voice floor + pitch table -------------------------------------------------
  {
    Field f(HL);
    check(!f.alive(0), "an empty field is silent");
    f.deposit(0, TRACEFIELD_VOICE_FLOOR - 1, 0);
    check(!f.alive(0), "a cell below the floor does not sound");
    f.deposit(0, 2, 0);
    check(f.alive(0), "a cell at the floor sounds");

    // Pentatonic: no semitone (ratio < 1.09) between adjacent cells, so any chord the
    // room deposits is consonant. This is the reason the table is not chromatic.
    bool pentatonic = true;
    for (uint8_t i = 1; i < CELLS; ++i) {
      const double r = (double)pitchFor(i) / (double)pitchFor(i - 1);
      if (r <= 1.0 || r < 1.09) pentatonic = false;
    }
    check(pentatonic, "pitch table is ascending with no semitone steps");
    check(pitchFor(CELLS) == 0, "an out-of-range cell has no pitch");
  }

  // ---- 10. provenance: whose mark is this? ------------------------------------------
  // For the operator, not the mechanism — but a shared medium that cannot show which marks
  // are yours looks exactly like a local echo on the glass, and that distinction IS the
  // claim. It must describe the value shown NOW, not the cell's history.
  {
    Field f(HL);
    check(!f.fromPeer(0), "a fresh cell is not a peer's");
    f.deposit(0, 100, 0);
    check(!f.fromPeer(0), "a local deposit is ours");

    Field p(HL);
    p.deposit(0, 200, 0);
    p.deposit(3, 200, 0);
    uint8_t d[DIGEST_LEN];
    p.buildDigest(d, sizeof(d), 0);
    f.merge(d, sizeof(d), 0);
    check(f.fromPeer(0), "a merge that RAISED our cell marks it as the peer's");
    check(f.fromPeer(3), "a merge into an empty cell marks it as the peer's");

    // Re-depositing locally must take ownership back — otherwise the panel would keep
    // crediting a peer for a mark the operator just made themselves.
    f.deposit(0, 100, 0);
    check(!f.fromPeer(0), "a local deposit RECLAIMS a cell the peer had raised");

    // A merge that changes nothing must not relabel anything.
    Field q(HL);
    q.deposit(5, 250, 0);
    uint8_t weak[DIGEST_LEN];
    Field r(HL);
    r.deposit(5, 10, 0);
    r.buildDigest(weak, sizeof(weak), 0);
    q.merge(weak, sizeof(weak), 0);
    check(!q.fromPeer(5), "a merge that raises NOTHING leaves provenance alone");
    check(f.fromPeer(CELLS) == false, "out-of-range provenance is false, not UB");
  }

  printf("%d checks, %d failures\n", gChecks, gFails);
  return gFails ? 1 : 0;
}
