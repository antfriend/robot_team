#!/usr/bin/env python3
"""test_pose_py.py -- pin POSE, the part of position that the fleet's own information
cannot reach (`ttn-semantic-positioning.md` Draft 0.3 §0.1, §0.2, §1.2).

WHY THIS FILE EXISTS. A relation between two nodes is invariant under moving the whole
fleet, so everything inferable from common information alone is inferable only up to
the plane's symmetry group: translation (2) + rotation (1) + reflection (1) = FOUR
degrees of freedom. `sigma_m` measures how well a SHAPE fits its evidence and covers
none of them -- a fleet with a perfect shape and no GPS fix has `sigma_m -> 0` and
UNBOUNDED position error. Draft 0.2 reported `sigma_m` alone, which is why proof leg 1
was dishonest by its own standard.

TWO DEFECTS THIS FILE EXISTS TO KEEP FIXED:

  1. ANCHORING ON V4-A WAS CIRCULAR. `positions.md` carried
     `anchor_chain: [v4a_bridge]`, pinning the map to a CONFIGURED @LATxLONy and
     reporting that assertion back as a result. A configured constant is not a
     measurement. v4a_bridge is the frame ORIGIN -- a labelling choice with no
     epistemic content -- and only GPS fixes pin pose.

  2. "3 TIES RESOLVE THE MIRROR" WAS NEVER CHECKED FOR NON-COLLINEARITY. The spec has
     always said ">=3 NON-COLLINEAR"; the code tested `len(ties) >= 3`. Three ties
     strung along a line map to THEMSELVES under reflection across that line, so they
     resolve nothing, however many there are.

Run: python tests/test_pose_py.py
"""
import math
import os
import re
import sys
import tempfile

sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "orchestrator"))
import companion as c  # noqa: E402

fails = 0


def check(cond, msg):
    global fails
    print(("pass: " if cond else "FAIL: ") + msg)
    if not cond:
        fails += 1


# ---------------------------------------------------------------------------
# 1) The DoF budget itself.
# ---------------------------------------------------------------------------
check(c.POSE_DOF_TOTAL == 4,
      "four degrees of freedom: translation 2 + rotation 1 + reflection 1 (spec 0.1)")

dof, by, note = c.pose_ceiling([])
check(dof == 0, "no ties -> 0 of 4 DoF pinned (got %d)" % dof)
check(all(v == "none" for v in by.values()), "and nothing claims to pin anything")
check("SHAPE, not a map" in note,
      "and the note says so in words, because a 0 that renders as a map is the lie")

dof, by, _ = c.pose_ceiling([(0.0, 0.0)])
check(dof == 2 and by["translation"] == "gps",
      "1 tie pins TRANSLATION only = 2 of 4 DoF (got %d)" % dof)
check(by["rotation"] == "none" and by["reflection"] == "none",
      "and leaves rotation and reflection free")

dof, by, _ = c.pose_ceiling([(0.0, 0.0), (10.0, 0.0)])
check(dof == 3 and by["rotation"] == "gps",
      "2 ties add ROTATION = 3 of 4 DoF (got %d)" % dof)
check(by["reflection"] == "none", "but 2 ties can never resolve the mirror")

dof, by, _ = c.pose_ceiling([(0.0, 0.0), (10.0, 0.0), (0.0, 10.0)])
check(dof == 4 and by["reflection"] == "gps",
      "3 NON-COLLINEAR ties pin all 4 DoF (got %d)" % dof)

# ---------------------------------------------------------------------------
# 2) THE COLLINEARITY DEFECT. This is the check `len(ties) >= 3` could not make.
# ---------------------------------------------------------------------------
collinear = [(0.0, 0.0), (10.0, 0.0), (20.0, 0.0)]
dof, by, note = c.pose_ceiling(collinear)
check(dof == 3 and by["reflection"] == "none",
      "3 COLLINEAR ties do NOT resolve the mirror: still 3 of 4 (got %d)" % dof)
check("COLLINEAR" in note, "and the note names collinearity as the cause: %r" % note)
check(c._perp_spread(collinear) == 0.0, "perpendicular spread of a line is 0")
check(c._perp_spread([(0.0, 0.0), (10.0, 0.0), (5.0, 3.0)]) == 3.0,
      "and is the off-line distance otherwise (expected 3.0)")
check(c._perp_spread([(0.0, 0.0), (10.0, 0.0)]) == 0.0,
      "two points are always collinear, so spread is 0 by definition")

# A spread INSIDE the tie error is collinear as far as this measurement can tell --
# claiming a resolved mirror from it is the same overclaim as anchoring on a config.
nearly = [(0.0, 0.0), (10.0, 0.0), (5.0, 0.2)]
dof_tight, by_tight, _ = c.pose_ceiling(nearly, tol_m=0.0)
dof_noisy, by_noisy, note_noisy = c.pose_ceiling(nearly, tol_m=0.5)
check(dof_tight == 4 and by_tight["reflection"] == "gps",
      "0.2 m off the line resolves the mirror when the fit is exact")
check(dof_noisy == 3 and by_noisy["reflection"] == "none",
      "but NOT when the tie error is 0.5 m: the offset is inside the noise")
check("COLLINEAR" in note_noisy,
      "and it says so rather than silently downgrading (%r)" % note_noisy)

# ---------------------------------------------------------------------------
# 3) The record line, and that BOTH numbers are present.
# ---------------------------------------------------------------------------
line = c.dof_pinned_line({"translation": "gps", "rotation": "gps",
                          "reflection": "none"})
check(line == "dof_pinned: { translation: gps, rotation: gps, reflection: none }",
      "dof_pinned renders in spec 2.1's brace form (got %r)" % line)

# ---------------------------------------------------------------------------
# 4) End to end: `positions` must emit pose_ceiling 0 and must NOT anchor on V4-A.
# ---------------------------------------------------------------------------
d = tempfile.mkdtemp()
prox = os.path.join(d, "proximity.md")
with open(prox, "w", encoding="utf-8", newline="\n") as f:
    f.write("# prox\n")
    for a, b, dist in (("v4a_bridge", "v4b_relay", 4.0),
                       ("v4a_bridge", "tdeck_1", 3.0),
                       ("v4b_relay", "tdeck_1", 5.0)):
        f.write(f"\n---\n\n@BELIEF:PROXIMITY @pair({a}, {b})\n"
                f"proto: espnow\ndist_est_m: {dist}\ndist_sigma_m: 0.5\n"
                f"n_obs: 100\nconf: 0.7\n")
pos_out = os.path.join(d, "positions.md")
import contextlib, io  # noqa: E402
with contextlib.redirect_stdout(io.StringIO()) as buf:
    c.positions(prox, pos_out, 400)
ptext = open(pos_out, encoding="utf-8").read()

check("pose_ceiling: 0" in ptext,
      "positions.md reports pose_ceiling 0 -- the honest reading of a relative frame")
check("anchor_chain: []" in ptext, "and an EMPTY anchor_chain")
# Scoped to the RECORDS: the file HEADER quotes the old `anchor_chain: [v4a_bridge]`
# on purpose, to explain what changed and why. Prose about a retracted claim is not
# the claim -- a whole-file search cannot tell them apart, so it must not be used.
check(all("anchor_chain: [v4a_bridge]" not in r
          for r in ptext.split("@BELIEF:POSITION")[1:]),
      "REGRESSION: no RECORD may carry v4a_bridge as an ANCHOR again (spec 1.2)")
check("frame_origin: v4a_bridge" in ptext,
      "it is named as the frame ORIGIN instead, which is a labelling choice")
check("dof_pinned: { translation: none" in ptext,
      "and no degree of freedom claims to be pinned")
check("SHAPE" in buf.getvalue(),
      "the console says it is a shape, not a map -- the operator reads this, not the file")
# Both numbers, on every record: sigma alone is what made proof leg 1 dishonest.
recs = ptext.split("@BELIEF:POSITION")[1:]
check(len(recs) == 3 and all("sigma_m:" in r and "pose_ceiling:" in r for r in recs),
      "EVERY record carries sigma_m AND pose_ceiling (got %d records)" % len(recs))

# ---------------------------------------------------------------------------
# 5) End to end: 3 COLLINEAR GPS ties must not claim a resolved mirror.
# ---------------------------------------------------------------------------
NODES = ["v4a_bridge", "v4b_relay", "k10_1", "tdeck_1"]
# A deliberately collinear layout: three ties along y = 0.
rel = {"v4a_bridge": (0.0, 0.0), "v4b_relay": (10.0, 0.0),
       "k10_1": (20.0, 0.0), "tdeck_1": (10.0, 7.0)}
LAT0, LON0 = 43.6, -116.2


def rel_to_geo(x, y):
    return (LAT0 + y / c.M_PER_DEG_LAT,
            LON0 + x / (c.M_PER_DEG_LAT * math.cos(math.radians(LAT0))))


pos_path = os.path.join(d, "pos2.md")
with open(pos_path, "w", encoding="utf-8", newline="\n") as f:
    f.write(c.POSITIONS_HEADER)
    for nd, (x, y) in sorted(rel.items()):
        f.write(f"\n---\n\n@BELIEF:POSITION @node({nd})\n"
                f"frame: relative\nx_m: {x:.2f}\ny_m: {y:.2f}\nsigma_m: 0.40\n"
                f"pose_ceiling: 0\nanchor_chain: []\nembedding_rev: 1\n"
                f"flip_resolved: false\nstress_m: 0.01\nconf: 0.7\n"
                f"touched: 2026-07-10T00:00:00Z\n")

fix_path = os.path.join(d, "fixes.md")
anc_path = os.path.join(d, "anchored.md")


def write_fixes(ties):
    with open(fix_path, "w", encoding="utf-8", newline="\n") as f:
        f.write("# fixes\n")
        for nd in ties:
            lat, lon = rel_to_geo(*rel[nd])
            f.write(f"\n---\n\n@PERCEPT:GPS @at({nd})\n"
                    f"lat_deg: {lat:.7f}\nlon_deg: {lon:.7f}\nalt_m: 10.0\n"
                    f"quality: 1\nsats: 9\nhdop: 1.0\nsource_node: tdeck_1\n"
                    f"node_epoch_ms: 0\ntouched: 2026-07-10T00:00:00Z\n")


write_fixes(["v4a_bridge", "v4b_relay", "k10_1"])       # 3 ties, all COLLINEAR
with contextlib.redirect_stdout(io.StringIO()) as buf:
    c.anchor(pos_path, fix_path, anc_path)
atext = open(anc_path, encoding="utf-8").read()
check("flip_resolved: false" in atext,
      "REGRESSION: 3 COLLINEAR ties give flip_resolved FALSE (len(ties)>=3 said true)")
check("pose_ceiling: 3" in atext, "and pose_ceiling 3 of 4, not 4")
check("COLLINEAR" in atext or "COLLINEAR" in buf.getvalue(),
      "and collinearity is named, so the operator knows what to move")
check("anchor_chain: [gps x3]" in atext,
      "the anchor chain is GPS ONLY -- v4a_bridge is not in it")

write_fixes(["v4a_bridge", "v4b_relay", "tdeck_1"])     # 3 ties, NON-collinear
with contextlib.redirect_stdout(io.StringIO()):
    c.anchor(pos_path, fix_path, anc_path)
atext = open(anc_path, encoding="utf-8").read()
check("flip_resolved: true" in atext,
      "3 NON-collinear ties DO resolve the mirror (the fix is not just 'always false')")
check("pose_ceiling: 4" in atext, "and pin all 4 DoF")

# ---------------------------------------------------------------------------
# 6) The push path must carry the new fields to the nodes unchanged.
# ---------------------------------------------------------------------------
blob, n = c.author_position_belief(pos_out)
btext = blob.decode("utf-8")
check(n == 3 and "pose_ceiling: 0" in btext,
      "author_position_belief carries pose_ceiling through to /belief.md")
check("dof_pinned:" in btext, "and dof_pinned with it")

# ---------------------------------------------------------------------------
print()
if fails:
    print("%d FAILED" % fails)
    sys.exit(1)
print("all pose checks passed")
