#!/usr/bin/env python3
"""test_entity_separation_py.py -- pin THE ABLATION GATEKEEPER
(`ttn-semantic-positioning.md` Draft 0.3 §4.3).

WHY THIS FILE EXISTS. The hypothesis's own falsifier is "the semantic layer adds
nothing over plain radio ranging" (spec §0). Run the ablation at a separation where
two nodes see the same access points and it reports exactly that -- as an artifact of
the test geometry, not a fact about the tier. Measured 2026-08-11 on the night-3
archives: two nodes metres apart clear the still-node p90 by only 1.12x. So an
ablation at bench scale would have retired the primary hypothesis for the wrong
reason, and `entity-separation` exists so that cannot happen by accident.

⚠ AND IT EXISTS IN THE SHAPE IT DOES BECAUSE THE FIRST HAND-RUN GOT IT WRONG. That run
folded a record's `**COVERED**` union into the cross-node set, which inflated the
overlap and HALVED the measured distance (0.250 -> 0.125). The rule that fell out is
the thing this file mainly pins:

    CROSS-NODE separation and WITHIN-NODE drift NEED DIFFERENT INPUTS.
      cross-node : each record's OWN window (`entities`) -- valid on a FOLDED lane,
                   because a folded record still itemises its own window.
      within-node: consecutive windows -- INVALID on a folded lane, because the
                   suppressed windows are gone and the union is a different quantity.

`parse_entity_percepts`'s own docstring already said to keep them apart. A rule written
down and then broken by the next thing written is what a test is for.

Run: python tests/test_entity_separation_py.py
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


def ent(lane, t_ms, ids, stream=STREAM, covered=None):
    """One @LAT96 record. `covered` (a list of ids) makes it a FOLDED record carrying
    a run union, byte-faithful to EntityPercept::buildRecord."""
    b = "\n---\n\n@LAT96LON%d | created:0 | updated:0 | relates:observes@LAT0LON0\n\n" % lane
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


def ap(n):
    return ["aabbccdd%04d" % i for i in range(n)]


def lane(n, ids, stream=STREAM, t0=1000000, spacing_s=600):
    return "".join(ent(k, t0 + k * spacing_s * 1000, ids, stream)
                   for k in range(n))


def run(*texts, **kw):
    """Write two TTDBs to disk, run entity_separation, return its stdout."""
    paths = []
    try:
        for t in texts:
            fd, p = tempfile.mkstemp(suffix=".md")
            with os.fdopen(fd, "w", encoding="utf-8") as f:
                f.write(t)
            paths.append(p)
        buf = io.StringIO()
        with contextlib.redirect_stdout(buf):
            c.entity_separation(paths[0], paths[1], **kw)
        return buf.getvalue()
    finally:
        for p in paths:
            os.unlink(p)


# ---------------------------------------------------------------------------
# 1) THE CORRECTION, pinned in BOTH directions: cross-node reads the record's own
#    window and never the covered union.
# ---------------------------------------------------------------------------
# Node A sees APs 0..3. Node B's WRITTEN window is 4..7 (disjoint -> distance 1.0),
# but its record also carries a COVERED union naming 0..3. Reading the union would
# make the two look identical (distance 0.0). The gap between 1.0 and 0.0 is the whole
# error, made maximal so no rounding can hide it.
A_own = ent(0, 1000000, ap(4)[:4])
B_folded = ent(0, 1000000, ["ffffffff%04d" % i for i in range(4)],
               covered=ap(4)[:4])
wa = c.parse_entity_percepts(A_own)
wb = c.parse_entity_percepts(B_folded)
pairs, used = c.cross_node_pairs(wa, wb, STREAM)
check(len(pairs) == 1, "cross_node_pairs matches one simultaneous window pair")
check(pairs and pairs[0] == 1.0,
      "cross-node distance uses the record's OWN window: disjoint sets -> 1.000 "
      "(got %s)" % (pairs[0] if pairs else None))
check(c.entity_lane_is_folded(wb),
      "and node B's lane IS folded -- so cross-node comparison is legitimate on a "
      "folded lane, which is the half of the rule that is easy to over-restrict")

# The negative control: had the union been folded in, the answer would have been 0.0.
union_b = set(e["id"] for e in wb[0]["entities"]) | set(
    e["id"] for e in wb[0]["covered_entities"])
check(c.jaccard_distance(set(e["id"] for e in wa[0]["entities"]), union_b) < 1.0,
      "NEGATIVE CONTROL: mixing the COVERED union in really does change the answer "
      "(so check 2 is testing something, not restating a tautology)")

# ---------------------------------------------------------------------------
# 2) within_node_floor REFUSES a folded lane -- the other half of the rule.
# ---------------------------------------------------------------------------
folded_lane = (ent(0, 1000000, ap(8)) +
               ent(1, 1000000 + 1200000, ap(8), covered=ap(8)))
f, note = c.within_node_floor(c.parse_entity_percepts(folded_lane))
check(f is None and "FOLDED" in note,
      "within_node_floor REFUSES a folded lane and names that as the cause")
f, note = c.within_node_floor(c.parse_entity_percepts(lane(6, ap(8))))
check(f is not None, "and accepts a periodic lane (%s)" % note)

# ---------------------------------------------------------------------------
# 3) No shared stream = no common zero, so the pair cannot be time-aligned at all.
# ---------------------------------------------------------------------------
out = run(lane(12, ap(8), stream=STREAM), lane(12, ap(8), stream=OTHER))
check("NO SHARED STREAM" in out,
      "two lanes on different streams REFUSE alignment: t_ms is "
      "elapsed-since-origin, so there is no common zero")
check("NOT* ADMISSIBLE" in out or "NOT ADMISSIBLE" in out.replace("*", ""),
      "and that alone makes the geometry not admissible")

# ---------------------------------------------------------------------------
# 4) The verdict itself. Identical AP sets = no separation; disjoint = full separation.
# ---------------------------------------------------------------------------
same = run(lane(12, ap(8)), lane(12, ap(8)))
check("NOT" in same.split("VERDICT:")[1],
      "two nodes seeing the SAME 8 APs are NOT ADMISSIBLE (zero separation)")
check("0.000" in same, "and the cross-node distance is reported as 0.000")

# A node whose APs are disjoint from A's, with A carrying a real still-node floor:
# churn one AP per window on A so its p90 floor is non-zero but small.
def churned(n, ids, t0=1000000):
    out, cur, nxt = "", list(ids), len(ids)
    for k in range(n):
        out += ent(k, t0 + k * 600000, cur)
        cur = cur[1:] + ["aabbccdd%04d" % nxt]
        nxt += 1
    return out

far = run(churned(14, ap(8)), lane(14, ["ffffffff%04d" % i for i in range(8)]))
check("ADMISSIBLE" in far.split("VERDICT:")[1] and
      "NOT" not in far.split("VERDICT:")[1],
      "two nodes with DISJOINT AP sets are ADMISSIBLE (separation >> floor)")

# ---------------------------------------------------------------------------
# 5) The margin is pre-registered, and it is the thing that decides.
# ---------------------------------------------------------------------------
check(c.ENTITY_SEP_MARGIN == 2.0,
      "the required margin is 2.0x, pre-registered 2026-08-11 BEFORE a geometry "
      "satisfying it existed (spec 4.3) -- changing it is a spec change, not a tweak")
check(c.ENTITY_SEP_MATCH_TOL_S * 2 == c.ENTITY_SCAN_PERIOD_S,
      "cross-node matching tolerance is HALF a scan period: beyond that, "
      "nearest-window matching stops being unambiguous")
# THE BENCH REGRESSION. Node B sees 7 of A's 8 APs plus one of its own -- which lands
# at ratio 1.00 against A's 0.222 floor, i.e. within rounding of the 1.12x actually
# measured between the Cardputer and V4-A on 2026-08-11. This case must keep failing.
BENCH_A = churned(14, ap(8))
BENCH_B = churned(14, ap(8)[:7] + ["ffffffff0001"], t0=1000000 + 60000)
bench = run(BENCH_A, BENCH_B, margin=2.0)
check("NOT" in bench.split("VERDICT:")[1],
      "REGRESSION: nodes sharing 7 of 8 APs (ratio ~1.0, the real bench figure) stay "
      "NOT ADMISSIBLE at the 2.0x margin")
check("1.00x" in bench,
      "and the fixture really does sit at the measured marginal ratio, so this is a "
      "regression against reality rather than against an easy case")
loose = run(BENCH_A, BENCH_B, margin=0.01)
check("NOT" not in loose.split("VERDICT:")[1],
      "and it is the MARGIN doing the work -- the same pair passes at 0.01x, so the "
      "verdict is a stated threshold, not an accident of the fixture")
# 1.8x still fails: the margin is demanding on purpose.
two_apart = run(churned(14, ap(8)),
                churned(14, ap(8)[:6] + ["ffffffff0001", "ffffffff0002"],
                        t0=1000000 + 60000), margin=2.0)
check("NOT" in two_apart.split("VERDICT:")[1],
      "even 2-of-8 APs different (ratio 1.8x) is NOT admissible -- 2.0x is a real bar, "
      "not a formality that any separation clears")

# ---------------------------------------------------------------------------
# 6) The report must carry what a result is not admissible without (spec 4.3).
# ---------------------------------------------------------------------------
check("BSSID alphabet" in same,
      "the report states the ALPHABET SIZE -- a tier result without it is as "
      "incomplete as an RSSI result without its terrain")
check("still-node floor" in same, "and the still-node floor it was compared against")
try:
    same.encode("cp1252")
    check(True, "output is cp1252-encodable (this console raises on U+26A0; 4th time)")
except UnicodeEncodeError:
    check(False, "output is cp1252-encodable")

# ---------------------------------------------------------------------------
print()
if fails:
    print("%d FAILED" % fails)
    sys.exit(1)
print("all entity-separation checks passed")
