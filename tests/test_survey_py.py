#!/usr/bin/env python3
"""test_survey_py.py -- pin `companion.py entity-survey`, the instrument that turns
"how far apart must two nodes be?" from one overnight run per candidate distance into
one afternoon walk (`ttn-semantic-positioning.md` Draft 0.3 §4.3).

WHY IT IS NOT JUST `entity-separation` IN A LOOP. That command answers a single bit --
is THIS geometry admissible -- and a NOT-ADMISSIBLE verdict says nothing about how much
further to walk. The fleet has been sitting on exactly that answer (1.12x at bench
scale) with no way to price the next attempt.

⚠ THE ONE DESIGN POINT THIS FILE MOSTLY EXISTS TO DEFEND:

    THE STILL-NODE FLOOR COMES FROM THE ANCHOR, AND ONLY THE ANCHOR.

`entity_separation` may take the floor from either node because both are still. Here
one node is WALKING, and a walker's consecutive-window drift is not sensor noise -- it
is the signal, arriving as apparent drift. Fold it into the floor and the bar rises in
exact proportion to how well the walk worked: the experiment would suppress its own
result, and it would do so silently, looking like a disappointing site. That failure is
invisible in any single record, which is what makes it a test's job.

Run: python tests/test_survey_py.py
"""
import contextlib
import io
import os
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


STREAM = 0xB4347C09
OTHER = 0x0C49E1CD
SPACING = c.ENTITY_SCAN_PERIOD_S          # 600 s
d = tempfile.mkdtemp()


def ent(lane, t_ms, ids, stream=STREAM, covered=None):
    """One @LAT96 record, byte-faithful to EntityPercept::buildRecord."""
    b = ("\n---\n\n@LAT96LON%d | created:0 | updated:0 | "
         "relates:observes@LAT0LON0\n\n" % lane)
    b += ("**ENTWIN** t_ms:%d stream:0x%08x wall:0 window_ms:600000 entities:%d\n"
          % (t_ms, stream, len(ids)))
    for i in ids:
        b += "**ENTITY** kind:wifi_ap id:%s n:1 rssi:-60\n" % i
    if covered is not None:
        b += ("**RUN** windows_since_last:2 reason:changed max_run:6 core_n:3 "
              "core_m:5 core_windows:3\n")
        b += ("**COVERED** windows:1 entities:%d window_ms:600000 first_t_ms:%d "
              "last_t_ms:%d covered_by:@LAT96LON0\n" % (len(covered), t_ms, t_ms))
        for i in covered:
            b += ("**COVERED-ENTITY** kind:wifi_ap id:%s n:1 rssi:-60 windows:1\n" % i)
    return b


def ap(i):
    return "aabbccdd%04d" % i


def lane_from(sets, stream=STREAM, t0=1000000, spacing_s=SPACING, folded=False):
    """One record per set, evenly spaced. `folded` attaches a COVERED union so the
    lane trips `entity_lane_is_folded`."""
    out = []
    for k, s in enumerate(sets):
        out.append(ent(k, t0 + k * spacing_s * 1000, sorted(s), stream,
                       covered=(sorted(s) if folded else None)))
    return "".join(out)


def run(anchor_text, walker_text, stations, **kw):
    a = os.path.join(d, "anchor.md")
    w = os.path.join(d, "walker.md")
    for p, t in ((a, anchor_text), (w, walker_text)):
        with open(p, "w", encoding="utf-8", newline="\n") as f:
            f.write("# ttdb\n" + t)
    st = [c.parse_station(s) for s in stations]
    buf = io.StringIO()
    with contextlib.redirect_stdout(buf):
        rows = c.entity_survey(a, w, st, **kw)
    return rows, buf.getvalue()


# ---------------------------------------------------------------------------
# 0) parse_station -- the operator-facing surface, so its errors must be legible.
# ---------------------------------------------------------------------------
check(c.parse_station("0,10,bench 0 m") == (0.0, 600.0, "bench 0 m"),
      "parse_station converts minutes to seconds and keeps the label")
check(c.parse_station("10.5,20,far") == (630.0, 1200.0, "far"),
      "and accepts fractional minutes")
check(c.parse_station("0,10,a,b,c")[2] == "a,b,c",
      "a label may contain commas -- the split is bounded to 2, so a label like "
      "'garden, far end' survives")
for bad, why in (("0,10", "too few fields"),
                 ("a,10,x", "non-numeric t0"),
                 ("10,10,x", "zero-length station"),
                 ("20,10,x", "t1 before t0")):
    try:
        c.parse_station(bad)
        check(False, "parse_station rejects %s" % why)
    except ValueError:
        check(True, "parse_station rejects %s (%r)" % (why, bad))

# ---------------------------------------------------------------------------
# 1) THE LOAD-BEARING ONE: a walking walker must not raise the floor.
#    Anchor sits still in a stable 8-AP room (tiny drift). Walker's own consecutive
#    windows swing wildly because it is being carried. If the floor were taken from
#    the walker -- or from max(anchor, walker) as `entity_separation` does -- the
#    ratio would collapse and a successful walk would report as a failed one.
# ---------------------------------------------------------------------------
room = set(ap(i) for i in range(8))
anchor_sets = [set(room) for _ in range(12)]
anchor_sets[3] = room - {ap(7)}          # one flicker, so the floor is nonzero

# walker: 4 windows in the room, then 8 windows in a completely different AP set
walker_sets = [set(room) for _ in range(4)] + \
              [set(ap(100 + i) for i in range(8)) for _ in range(8)]
# Stations deliberately leave 25-40 min open: the window at 30 min is TRANSIT (the
# walker is mid-carry) and must be excluded rather than attributed to either end.
rows, out = run(lane_from(anchor_sets), lane_from(walker_sets),
                ["0,25,near 0 m", "40,120,far 60 m"], min_pairs=3)

check(rows is not None, "a well-formed walk produces rows")
near = [r for r in rows if r["label"].startswith("near")][0]
far = [r for r in rows if r["label"].startswith("far")][0]
check(near["p50"] == 0.0,
      "at the near station the two nodes see the same room -> distance 0.000")
check(far["p50"] == 1.0,
      "at the far station the AP populations are disjoint -> distance 1.000")
check(far["ok"] and not near["ok"],
      "so the far station is ADMISSIBLE and the near one is not -- the curve the "
      "walk exists to produce")

# The floor printed must be the ANCHOR's, which is tiny (one flicker in 12 windows).
# The walker's own drift includes a 0->1 jump; if that leaked in, p90 would be ~1.0
# and NOTHING could ever clear 2.0x.
floor_line = [ln for ln in out.splitlines() if ln.startswith("anchor floor n=")][0]
p90 = float(floor_line.split("p90")[1].split()[0])
check(p90 < 0.3,
      "the reported floor is the ANCHOR's (p90 %.3f), not polluted by the walker's "
      "motion-induced drift" % p90)
check(far["ratio"] > 2.0,
      "and BECAUSE the floor stayed the anchor's, the successful station clears the "
      "2.0x margin (%.2fx) -- with the walker folded in it never could" % far["ratio"])
check("ANCHOR (must NOT have moved)" in out,
      "the output names which lane is the anchor, since the whole result depends on "
      "that node having held still")

# ---------------------------------------------------------------------------
# 2) Transit windows are excluded, not silently attributed to a station.
# ---------------------------------------------------------------------------
check("in transit / outside every station (excluded)" in out,
      "windows between stations are reported as excluded")
n_excluded = int([ln for ln in out.splitlines()
                  if "in transit" in ln][0].split(";")[1].strip().split()[0])
check(n_excluded == 1,
      "the open 25-40 min gap drops exactly the one mid-carry window (%d) -- the "
      "walker was between stations and belongs to neither" % n_excluded)

rows2, out2 = run(lane_from(anchor_sets), lane_from(walker_sets),
                  ["0,25,near", "40,120,far"], min_pairs=3)
check(sum(r["n"] for r in rows2) + n_excluded == 12,
      "every matched window is either assigned to exactly one station or counted as "
      "transit -- none vanish and none are double-counted")

# ---------------------------------------------------------------------------
# 3) A station boundary SELECTS windows; it must not re-match them. Widening a
#    station must not change any distance already reported for the windows inside it.
# ---------------------------------------------------------------------------
rows3, _ = run(lane_from(anchor_sets), lane_from(walker_sets),
               ["0,200,everything"], min_pairs=3)
allrow = rows3[0]
check(allrow["n"] == 12,
      "one station spanning the whole walk collects every matched pair (%d)"
      % allrow["n"])
check(allrow["min"] == 0.0 and allrow["max"] == 1.0,
      "and it spans both regimes, so bucketing is a filter over a fixed matching")

# ---------------------------------------------------------------------------
# 4) Refusals. Each returns None rather than a number nobody should trust.
# ---------------------------------------------------------------------------
rows4, out4 = run(lane_from(anchor_sets, folded=True), lane_from(walker_sets),
                  ["0,200,x"], min_pairs=3)
check(rows4 is None and "REFUSING" in out4 and "floor" in out4.lower(),
      "a FOLDED anchor lane is REFUSED: consecutive records are not consecutive "
      "windows, so its drift is not a floor")
check("may not be taken from the walker" in out4,
      "and the refusal explains why the walker cannot stand in -- otherwise the "
      "obvious 'fix' is the exact defect this design forbids")

rows5, out5 = run(lane_from(anchor_sets), lane_from(walker_sets, stream=OTHER),
                  ["0,200,x"], min_pairs=3)
check(rows5 is None and "no shared stream" in out5.lower(),
      "no shared stream is REFUSED: t_ms is elapsed-since-origin, so two streams "
      "have no common zero")

rows6, out6 = run("", lane_from(walker_sets), ["0,200,x"], min_pairs=3)
check(rows6 is None and "no @LAT96 windows at all" in out6,
      "an empty lane is REFUSED rather than reported as a perfect score")

# ---------------------------------------------------------------------------
# 5) Underpowered stations are flagged, never quietly passed.
# ---------------------------------------------------------------------------
rows7, out7 = run(lane_from(anchor_sets), lane_from(walker_sets),
                  ["0,15,tiny", "40,120,far"], min_pairs=10)
tiny = [r for r in rows7 if r["label"] == "tiny"][0]
check(not tiny["ok"] and "UNDERPOWERED" in tiny["note"],
      "a station with fewer than min_pairs windows is UNDERPOWERED and cannot be "
      "admissible on 2 samples, however clean they look")
check("UNDERPOWERED" in out7, "and the operator sees it in the table")

rows8, out8 = run(lane_from(anchor_sets), lane_from(walker_sets),
                  ["0,15,tiny", "200,300,nothing here"], min_pairs=3)
empty = [r for r in rows8 if r["label"] == "nothing here"][0]
check(empty["n"] == 0 and not empty["ok"],
      "a station with NO windows is reported as empty rather than dropped from the "
      "table -- an operator who mistyped a time must be able to see it")

# ---------------------------------------------------------------------------
# 6) The zero-floor trap, same family as the bug `entity_separation` shipped with:
#    0/0 is the LEAST separated geometry, not an infinitely separated one.
# ---------------------------------------------------------------------------
flat = [set(room) for _ in range(12)]              # anchor never changes -> floor 0
rows9, out9 = run(lane_from(flat), lane_from(flat), ["0,200,identical"], min_pairs=3)
ident = rows9[0]
check(ident["p50"] == 0.0 and ident["ratio"] == 0.0 and not ident["ok"],
      "two IDENTICAL lanes with a zero floor give ratio 0.0, not inf -- 0/0 is two "
      "nodes in the same unchanging room, the least separated geometry there is")

rows10, _ = run(lane_from(flat), lane_from([set(ap(100 + i) for i in range(8))
                                            for _ in range(12)]),
                ["0,200,disjoint"], min_pairs=3)
check(rows10[0]["ratio"] == float("inf") and rows10[0]["ok"],
      "but a zero floor with a NONZERO distance is genuinely unbounded separation "
      "and is admissible")

# ---------------------------------------------------------------------------
# 7) The summary line the walk exists to produce.
# ---------------------------------------------------------------------------
check("SMALLEST ADMISSIBLE STATION: far" in out,
      "the survey names the smallest admissible station -- the answer to 'how far "
      "apart is far enough?'")
check("only" in out and "increasing separation" in out,
      "and states the precondition that makes 'smallest' meaningful, since it "
      "cannot check the order itself")

rows11, out11 = run(lane_from(anchor_sets), lane_from([set(room) for _ in range(12)]),
                    ["0,200,all near"], min_pairs=3)
check("NO STATION CLEARS" in out11 and "do not" in out11.lower()
      and "falsification" in out11,
      "a walk where nothing clears the margin says so AND warns it is a fact about "
      "the site, not a falsification of the hypothesis")

# ---------------------------------------------------------------------------
# 8) THE CADENCE TRAP. A survey at 10-minute windows needs ~100 min per station to
#    reach min_pairs, so the obvious way to fit one into an afternoon is a faster
#    scan build. That inflates every ratio: the floor is a TEMPORAL drift, so halving
#    the spacing halves the time the AP set has to change. The tool must say so.
# ---------------------------------------------------------------------------
fast = [set(room) for _ in range(12)]
fast[3] = room - {ap(7)}
rows12, out12 = run(lane_from(fast, spacing_s=60),
                    lane_from([set(ap(100 + i) for i in range(8)) for _ in range(12)],
                              spacing_s=60),
                    ["0,60,fast build"], spacing_s=60, tol_s=30,
                    match_tol_s=30, min_pairs=3)
check("NOT comparable" in out12 and "SPACING 60 s" in out12,
      "a non-default --spacing is loudly flagged as not comparable to the "
      "pre-registered margin -- the margin was set against a 600 s floor")
_, out13 = run(lane_from(anchor_sets), lane_from(walker_sets),
               ["0,200,x"], min_pairs=3)
check("NOT comparable" not in out13,
      "and the warning stays quiet at the fleet's real cadence, so it keeps meaning "
      "something when it does fire")

# ---------------------------------------------------------------------------
# 9) The alphabet must be stated with any result (spec §4.3).
# ---------------------------------------------------------------------------
check("BSSID alphabet across both nodes: 16" in out,
      "the BSSID alphabet is reported (8 room + 8 far = 16), because a tier result "
      "without its alphabet size is as incomplete as an RSSI result without terrain")

# ---------------------------------------------------------------------------
print()
if fails:
    print("%d FAILED" % fails)
    sys.exit(1)
print("all entity-survey checks passed")
