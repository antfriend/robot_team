#!/usr/bin/env python3
"""test_render_py.py -- the two NORMATIVE render rules of the SP6 payoff render
(`ttn-semantic-positioning.md` Draft 0.3 §3 Phase 6).

Both are the same principle, which this fleet has paid to learn twice:

    IF A VIEW CAN SHOW LESS THAN THE WHOLE TRUTH, IT MUST SAY SO ON SCREEN.

  RULE 1 -- a faded trace renders as FADED, never as absent (TTDB-RFC-0010 §6.4).
    "Nobody has reinforced this for an hour" and "there is no such node" are different
    claims, and this fleet has already FABRICATED the second one once.
    ⚠ The defect this file was written against: `fleetmap` stamped every record
    `created:1750000000` -- a frozen constant. A belief from six weeks ago and one from
    a minute ago were byte-identical downstream, so nothing could render decay at all.
    A renderer cannot fade what it cannot date.

  RULE 2 -- the pose renders its own ambiguity (spec §0.1, §3 Phase 6).
    With `pose_ceiling: 0` the shape is correct and the placement is one of infinitely
    many; drawing it as a confident map is the same class of lie as rule 1.
    ⚠ A record with NO `pose_ceiling` field must default to **0**, not to "unknown, so
    assume fine" -- a pre-0.3 record is precisely one with no GPS tie behind it, so the
    fail-safe direction is to under-claim.

Note what is deliberately NOT here: a staleness THRESHOLD. There is no measured cadence
for these beliefs to justify one, and inventing a cut-off would be the same unearned
constant Draft 0.3 spent its day removing. The age is emitted; fading is continuous.

Run: python tests/test_render_py.py
"""
import contextlib
import io
import os
import re
import sys
import tempfile
import time

sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "orchestrator"))
import companion as c  # noqa: E402

fails = 0


def check(cond, msg):
    global fails
    print(("pass: " if cond else "FAIL: ") + msg)
    if not cond:
        fails += 1


d = tempfile.mkdtemp()


def write_positions(path, recs):
    """recs: [(node, x, y, touched_iso_or_None, pose_ceiling_or_None)]"""
    with open(path, "w", encoding="utf-8", newline="\n") as f:
        f.write("# positions\n")
        for nd, x, y, touched, pose in recs:
            f.write(f"\n---\n\n@BELIEF:POSITION @node({nd})\n"
                    f"frame: relative\nx_m: {x:.2f}\ny_m: {y:.2f}\nsigma_m: 0.40\n")
            if pose is not None:
                f.write(f"pose_ceiling: {pose}\n"
                        f"dof_pinned: {{ translation: gps, rotation: none, "
                        f"reflection: none }}\n")
            f.write("conf: 0.70\n")
            if touched:
                f.write(f"touched: {touched}\n")


def write_prox(path, pairs):
    with open(path, "w", encoding="utf-8", newline="\n") as f:
        f.write("# prox\n")
        for a, b in pairs:
            f.write(f"\n---\n\n@BELIEF:PROXIMITY @pair({a}, {b})\n"
                    f"proto: espnow\ndist_est_m: 4.0\ndist_sigma_m: 0.5\n"
                    f"n_obs: 10\nconf: 0.7\n")


def run_fleetmap(pos, prox, out):
    buf = io.StringIO()
    with contextlib.redirect_stdout(buf):
        c.fleetmap(pos, prox, out)
    return open(out, encoding="utf-8").read(), buf.getvalue()


# ---------------------------------------------------------------------------
# 0) The ISO helper the whole of rule 1 rests on.
# ---------------------------------------------------------------------------
check(c.iso_to_unix("1970-01-01T00:00:00Z") == 0, "iso_to_unix epoch")
# Round-trip against the stdlib rather than a hand-computed constant: the point is that
# it agrees with `time.gmtime`, which is what wrote the stamp in the first place.
_iso = "2026-08-11T15:55:40Z"
check(time.strftime("%Y-%m-%dT%H:%M:%SZ",
                    time.gmtime(c.iso_to_unix(_iso))) == _iso,
      "iso_to_unix round-trips a real touched stamp through time.gmtime")
check(c.iso_to_unix("2026-08-11T12:00:00Z") > c.iso_to_unix("2026-06-30T12:00:00Z"),
      "and orders two stamps correctly, which is all fading needs of it")
check(c.iso_to_unix(None) is None and c.iso_to_unix("not a date") is None,
      "and it returns None rather than raising on junk -- an undated belief must not "
      "take the renderer down")

# ---------------------------------------------------------------------------
# 1) RULE 1: distinct `touched` values must survive into the globe.
# ---------------------------------------------------------------------------
pos = os.path.join(d, "positions.md")
prox = os.path.join(d, "proximity.md")
out = os.path.join(d, "ttdb.md")
write_positions(pos, [
    ("v4a_bridge", 0.0, 0.0, "2026-08-11T12:00:00Z", 0),
    ("v4b_relay", 4.0, 0.0, "2026-06-30T12:00:00Z", 0),   # six weeks older
])
write_prox(prox, [("v4a_bridge", "v4b_relay")])
text, console = run_fleetmap(pos, prox, out)

stamps = sorted(set(re.findall(r"created:(\d+)", text)))
check(len(stamps) == 2,
      "REGRESSION: two beliefs touched six weeks apart get DIFFERENT timestamps "
      "(got %r) -- they used to share a frozen constant" % stamps)
check("1750000000" not in text,
      "and the frozen constant 1750000000 is gone from the emitted globe")
check(int(stamps[0]) == c.iso_to_unix("2026-06-30T12:00:00Z"),
      "the older record's stamp is its OWN touched, not the run time")

ages = [int(a) for a in re.findall(r"age_s:\s*(\d+)", text)]
check(len(ages) == 2 and ages[0] != ages[1],
      "each record carries its own age_s so the device can fade continuously (got %r)"
      % ages)
check(max(ages) > min(ages) + 3000000,
      "and the six-week gap really is ~6 weeks of seconds apart (%r)" % ages)

# An UNDATED belief must still render -- absent is the one thing it must not be.
write_positions(pos, [("v4a_bridge", 0.0, 0.0, None, 0),
                      ("v4b_relay", 4.0, 0.0, "2026-08-11T12:00:00Z", 0)])
text2, console2 = run_fleetmap(pos, prox, out)
check(text2.count("**POSITION**") == 2,
      "an UNDATED belief is still RENDERED (faded, never absent -- RFC-0010 6.4)")
check("UNDATED" in console2,
      "and the console names it as undated rather than quietly stamping it 'now'")

# ---------------------------------------------------------------------------
# 2) RULE 2: the pose renders its own ambiguity, per record and per globe.
# ---------------------------------------------------------------------------
write_positions(pos, [("v4a_bridge", 0.0, 0.0, "2026-08-11T12:00:00Z", 0),
                      ("v4b_relay", 4.0, 0.0, "2026-08-11T12:00:00Z", 0)])
text3, console3 = run_fleetmap(pos, prox, out)
# Anchored to line start: `fleet_pose_ceiling:` contains `pose_ceiling:` as a substring,
# so a bare `.count()` silently counts the globe banner as a third record. Same
# needle-collision family as `prev_stream:` in @LAT90 and `**COVERED-SPAN**` in @LAT92.
check(len(re.findall(r"^pose_ceiling: 0 of 4$", text3, re.M)) == 2,
      "every RECORD states its own pose_ceiling (the globe banner is not a record)")
check(text3.count("render: SHAPE_NOT_MAP") >= 2,
      "and an unpinned record is explicitly marked SHAPE_NOT_MAP")
check("fleet_pose_ceiling: 0 of 4" in text3,
      "the globe states a fleet-wide ceiling too, for a reader that honours only that")
check("SHAPE, NOT MAP" in console3,
      "and the console tells the operator before they flash it")
check("render: MAP" not in text3,
      "an unpinned frame must NEVER be labelled MAP")

# The fleet ceiling is the WEAKEST node's: pose is a property of the frame.
write_positions(pos, [("v4a_bridge", 0.0, 0.0, "2026-08-11T12:00:00Z", 4),
                      ("v4b_relay", 4.0, 0.0, "2026-08-11T12:00:00Z", 2)])
text4, _ = run_fleetmap(pos, prox, out)
check("fleet_pose_ceiling: 2 of 4" in text4,
      "the fleet ceiling is the MINIMUM across nodes (4 and 2 -> 2), because pose is a "
      "property of the frame, not of one record")
check("render: MAP" not in text4, "so a mixed fleet is still not a MAP")

# All four pinned: only then may it be drawn as a map.
write_positions(pos, [("v4a_bridge", 0.0, 0.0, "2026-08-11T12:00:00Z", 4),
                      ("v4b_relay", 4.0, 0.0, "2026-08-11T12:00:00Z", 4)])
text5, console5 = run_fleetmap(pos, prox, out)
check("render: MAP" in text5 and "SHAPE_NOT_MAP" not in text5,
      "with all 4 DoF pinned it IS a map (the rule is not just 'always refuse')")
check("SHAPE, NOT MAP" not in console5, "and the console stops warning")

# ---------------------------------------------------------------------------
# 3) The fail-safe direction: a record with NO pose_ceiling defaults to 0.
# ---------------------------------------------------------------------------
write_positions(pos, [("v4a_bridge", 0.0, 0.0, "2026-08-11T12:00:00Z", None),
                      ("v4b_relay", 4.0, 0.0, "2026-08-11T12:00:00Z", None)])
text6, _ = run_fleetmap(pos, prox, out)
check("fleet_pose_ceiling: 0 of 4" in text6 and "render: MAP" not in text6,
      "a PRE-0.3 record with no pose_ceiling defaults to 0 -- under-claiming, because "
      "such a record is exactly one with no GPS tie behind it")
parsed = c._parse_positions_full(pos)
check(all(p["pose_ceiling"] == 0 for p in parsed.values()),
      "and the parser is where that default lives, so every consumer inherits it")

# ---------------------------------------------------------------------------
# 4) The real pipeline end to end: today's positions.md must render as a shape.
# ---------------------------------------------------------------------------
real = os.path.join(os.path.dirname(__file__), "..", "master", "positions.md")
if os.path.exists(real):
    nodes = c._parse_positions_full(real)
    check(nodes and all(n["pose_ceiling"] == 0 for n in nodes.values()),
          "the fleet's REAL positions.md is pose_ceiling 0 across the board")
    check(all(n["touched"] for n in nodes.values()),
          "and every real record is dated, so rule 1 is satisfiable on it")
else:
    check(True, "(master/positions.md absent -- skipped the live check)")

# ---------------------------------------------------------------------------
print()
if fails:
    print("%d FAILED" % fails)
    sys.exit(1)
print("all render-rule checks passed")
