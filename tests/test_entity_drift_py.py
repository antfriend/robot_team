#!/usr/bin/env python3
"""test_entity_drift_py.py -- pin the validation gates that guard Part 2's @LAT96
Jaccard threshold (part-b-handoff.md Part 2).

WHY THIS FILE EXISTS. On 2026-08-04 the archived @LAT96 lane produced a completely
plausible drift distribution -- p50 0.333, p90 0.538, max 0.727 -- and it was worthless:
its 48 windows spanned five streams with t_ms running backwards four times, and the
@LAT95 lane that would witness stillness sat on a different timeline. Nothing about the
numbers said so. That is the failure mode, and it is why the gates are code rather than
a habit: a threshold derived from a run that fails them is a number, not a measurement.

The gates were declared BEFORE the 8 h run that will feed them, which is the only order
in which a gate means anything.

Run: python tests/test_entity_drift_py.py
"""
import os
import sys

sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "orchestrator"))
import companion as c  # noqa: E402

fails = 0


def check(cond, msg):
    global fails
    print(("pass: " if cond else "FAIL: ") + msg)
    if not cond:
        fails += 1


STREAM = 0xBE6D9616
OTHER = 0x59FB8CE8


def ent(lane, t_ms, ids, stream=STREAM):
    """One @LAT96 record as EntityPercept::buildRecord emits it."""
    # Byte-faithful to EntityPercept::buildRecord: the window line counts APs as
    # `entities:`, NOT `n:` (the per-AP `n:` is a sighting count), and the kind is
    # `wifi_ap`. Verified against a real @LAT96 record pulled 2026-08-06 -- an earlier
    # fixture here used `n:`/`wifi` and passed anyway, because the parser derives the
    # set from **ENTITY** lines. A gate proven only against a record the firmware
    # would never emit is not proven.
    body = "\n---\n\n@LAT96LON%d | created:0 | updated:0 | relates:observes@LAT0LON0\n\n" % lane
    body += ("**ENTWIN** t_ms:%d stream:0x%08x wall:0 window_ms:600000 entities:%d\n"
             % (t_ms, stream, len(ids)))
    for i in ids:
        body += "**ENTITY** kind:wifi_ap id:%s n:1 rssi:-60\n" % i
    return body


def mot(lane, t_ms, state="still", covered=None, stream=STREAM):
    b = "\n---\n\n@LAT95LON%d | created:0 | updated:0 | relates:senses@LAT0LON0\n\n" % lane
    b += "**MOTIONWIN** t_ms:%d stream:0x%08x wall:0 window_ms:60000 n:1200\n" % (t_ms, stream)
    b += ("**MOTION** state:%s moving_permille:%d dev_mean_mg:9 dev_max_mg:13 "
          "moving_ms:0\n" % (state, 0 if state == "still" else 1000))
    b += "**RUN** windows_since_last:%d reason:%s max_run:30\n" % (
        30 if covered else 1, "heartbeat" if covered else "first")
    if covered:
        b += ("**COVERED** state:%s windows:29 n:28966 window_ms:1740000 "
              "moving_permille:0 dev_mean_mg:9 dev_max_mg:13 moving_ms:0 "
              "first_t_ms:1 last_t_ms:2 covered_by:@LAT95LON0\n" % covered)
    return b


def lane(n_windows, spacing_s=600, stream=STREAM, ap=8, churn=0, t0=1000000):
    """A clean @LAT96 lane: `n_windows` at `spacing_s`, `churn` APs swapped each step."""
    out = ""
    ids = ["aabbccdd%04d" % i for i in range(ap)]
    nxt = ap
    for k in range(n_windows):
        out += ent(k, t0 + k * spacing_s * 1000, ids, stream)
        for _ in range(churn):
            ids = ids[1:] + ["aabbccdd%04d" % nxt]
            nxt += 1
    return out


def witness(t0=1000000, span_s=600 * 47, state="still", stream=STREAM):
    """@LAT95 records bracketing the entity span -- the independent stillness witness."""
    return (mot(0, t0, state, covered=state, stream=stream)
            + mot(1, t0 + span_s * 1000, state, covered=state, stream=stream))


# ---------------------------------------------------------------------------
# 1) A clean run passes every gate.
# ---------------------------------------------------------------------------
CLEAN = lane(48) + witness()
ew = c.parse_entity_percepts(CLEAN)
mr = c.parse_motion_percepts(CLEAN)
ok, gates, pairs = c.entity_drift_gates(ew, mr)
check(len(ew) == 48, "48 entity windows parsed (got %d)" % len(ew))
check(ok, "a clean 8 h run passes all four gates")
check(len(pairs) == 47, "and yields 47 consecutive-drift pairs (got %d)" % len(pairs))
check(all(p == 0.0 for p in pairs),
      "a truly static AP set drifts 0.000 -- the floor is a floor, not an artefact")

# ---------------------------------------------------------------------------
# 2) GATE 1 -- multiple streams. This is what the archived baseline actually was.
# ---------------------------------------------------------------------------
MIXED = lane(24) + lane(24, t0=1000000 + 24 * 600000, stream=OTHER) + witness()
ok2, g2, _ = c.entity_drift_gates(c.parse_entity_percepts(MIXED),
                                  c.parse_motion_percepts(MIXED))
check(not ok2, "a lane spanning two streams FAILS")
check(not g2[0][1] and "2 stream" in g2[0][2],
      "and it is gate 1 that catches it, naming the count (%s)" % g2[0][2])

# ---------------------------------------------------------------------------
# 3) GATE 2 -- t_ms going backwards.
# ---------------------------------------------------------------------------
BACK = (lane(24) + ent(24, 500000, ["aabbccdd0000"]) + lane(23, t0=1000000 + 25 * 600000)
        + witness())
ok3, g3, _ = c.entity_drift_gates(c.parse_entity_percepts(BACK),
                                  c.parse_motion_percepts(BACK))
check(not ok3 and not g3[1][1], "a lane whose t_ms steps backwards FAILS gate 2")

# ---------------------------------------------------------------------------
# 4) GATE 3 -- the stillness witness. THE one that makes this non-circular.
# ---------------------------------------------------------------------------
MOVED = lane(48) + witness(state="moving")
ok4, g4, _ = c.entity_drift_gates(c.parse_entity_percepts(MOVED),
                                  c.parse_motion_percepts(MOVED))
check(not ok4 and not g4[2][1],
      "a run where the IMU saw MOVING fails gate 3 -- the node was not still, whatever "
      "the AP sets did")

NOWITNESS = lane(48)
ok4b, g4b, _ = c.entity_drift_gates(c.parse_entity_percepts(NOWITNESS),
                                    c.parse_motion_percepts(NOWITNESS))
check(not ok4b and not g4b[2][1],
      "and NO witness at all fails too -- absence of evidence is not stillness")

OTHERTL = lane(48) + witness(stream=OTHER)
ok4c, g4c, _ = c.entity_drift_gates(c.parse_entity_percepts(OTHERTL),
                                    c.parse_motion_percepts(OTHERTL))
check(not ok4c and not g4c[2][1] and "MISMATCH" in g4c[2][2],
      "a witness on a DIFFERENT timeline fails -- it cannot testify about this period, "
      "which is precisely how the archive fooled us")

# ---------------------------------------------------------------------------
# 5) GATE 4 -- off-cadence pairs are DISCARDED, not averaged in.
# A reboot forces an immediate scan, inserting a ~60 s window. Drift across that gap
# understates churn, so it is a WRONG sample rather than a conservative one.
# ---------------------------------------------------------------------------
REBOOT = ""
t = 1000000
ids = ["aabbccdd%04d" % i for i in range(8)]
k = 0
for i in range(40):
    REBOOT += ent(k, t, ids); k += 1
    t += 600000
    if i in (10, 20, 30):          # a reboot: extra scan 60 s later
        REBOOT += ent(k, t - 540000, ids); k += 1
REBOOT += witness(span_s=600 * 40)
okr, gr, pr = c.entity_drift_gates(c.parse_entity_percepts(REBOOT),
                                   c.parse_motion_percepts(REBOOT))
check("discarded off-cadence" in gr[3][2], "gate 4 reports what it discarded")
check(len(pr) == 39,
      "3 reboots insert 3 short windows -> 6 off-cadence pairs dropped, 39 kept "
      "(got %d)" % len(pr))
check(okr, "39 clean pairs still clears the 30-pair floor")

# ---------------------------------------------------------------------------
# 6) GATE 4 -- too few pairs refuses, however clean they are.
# ---------------------------------------------------------------------------
SHORT = lane(12) + witness(span_s=600 * 11)
oks, gs, ps = c.entity_drift_gates(c.parse_entity_percepts(SHORT),
                                   c.parse_motion_percepts(SHORT))
check(not oks and not gs[3][1] and len(ps) == 11,
      "a 2 h run yields 11 pairs and is REFUSED -- run another night rather than "
      "lowering the bar (got %d)" % len(ps))

# ---------------------------------------------------------------------------
# 7) The metric itself.
# ---------------------------------------------------------------------------
check(c.jaccard_distance({1, 2, 3}, {1, 2, 3}) == 0.0, "identical sets drift 0.0")
check(c.jaccard_distance({1, 2}, {3, 4}) == 1.0, "disjoint sets drift 1.0")
check(abs(c.jaccard_distance(set(range(8)), set(range(1, 9))) - (2 / 9)) < 1e-9,
      "one AP swapped out of 8 drifts 2/9 = 0.222 -- the quantisation that makes a "
      "small AP set a noisy signal")
check(c.jaccard_distance(set(), set()) is None,
      "two empty windows yield no sample, rather than a fabricated 0.0")

# ---------------------------------------------------------------------------
# 8) SEGMENT SELECTION -- the longest CONTIGUOUS single-stream run.
# A reboot late in an otherwise good night originates a fresh stream and splits the
# lane. Judging the long interval on its own merits is fair; stitching intervals
# together is not, which is why this is contiguity-based and not a filter by id.
# ---------------------------------------------------------------------------
SPLIT = lane(41) + lane(7, t0=9000000, stream=OTHER)
st, idx, seg = c.longest_stream_segment(c.parse_entity_percepts(SPLIT))
check(st == STREAM and len(seg) == 41 and idx == 0,
      "a 41+7 split night selects the 41-window segment (got %d at %d)" % (len(seg), idx))

# The trap: the node LEAVES a stream and REJOINS it. A filter by stream id would
# return 6+6=12 windows spanning a hole and call it one observation.
REJOIN = (lane(6) + lane(9, t0=5000000, stream=OTHER)
          + lane(6, t0=9000000))
rew = c.parse_entity_percepts(REJOIN)
st2, _, seg2 = c.longest_stream_segment(rew)
check(len(seg2) == 9 and st2 == OTHER,
      "leave-and-rejoin picks the 9-window CONTIGUOUS middle, not the 6+6 union "
      "(got %d)" % len(seg2))
check(len([w for w in rew if w["stream"] == STREAM]) == 12 and len(seg2) != 12,
      "-- and a plain filter by stream id WOULD have returned that stitched 12, "
      "which is the whole reason this is contiguity-based")

check(c.longest_stream_segment([]) == (None, 0, []),
      "an empty lane yields no segment rather than raising")

# Segment selection must not rescue a genuinely bad run: the segment still faces
# gates 2-4, and a moving witness inside it still fails.
MOVEDSEG = lane(41) + witness(span_s=600 * 40, state="moving")
_, _, ms = c.longest_stream_segment(c.parse_entity_percepts(MOVEDSEG))
okm, gm, _ = c.entity_drift_gates(ms, c.parse_motion_percepts(MOVEDSEG))
check(not okm and not gm[2][1],
      "a selected segment whose IMU saw MOVING still FAILS -- selection narrows the "
      "window, it does not lower the bar")

# ---------------------------------------------------------------------------
print()
if fails:
    print("%d FAILED" % fails)
    sys.exit(1)
print("all entity-drift gate checks passed")
