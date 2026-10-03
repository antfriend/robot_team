#!/usr/bin/env python3
"""test_episode_order_py.py — fleet.py's port of episode ORDER across agents (ACT-III §C4,
docs/design/episode-order.md stage 1).

The laptop reads `seq:`/`follows:` back out of pulls and orders episodes across nodes with
a Python port of firmware Semantic/src/FleetTime.cpp (parseAt / order / maximal). These
cases MIRROR the C++ ones in tests/test_fleettime.cpp and tests/test_episode_order.cpp —
same inputs, same expected relations — so the port cannot drift from the firmware without
one of the two suites going red. The episode text below is byte-for-byte what
test_episode_order.cpp asserts renderLinkEpisode writes.

Run: python tests/test_episode_order_py.py
"""
import os
import sys

sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "orchestrator"))
import fleet as c  # noqa: E402

fails = 0


def check(cond, msg):
    global fails
    print(("pass: " if cond else "FAIL: ") + msg)
    if not cond:
        fails += 1


FRAME = 5000


def ep(agent, seq, t, b, bounded=True, frame=FRAME, follows=None, has_frame=None):
    return {"agent": agent, "seq": seq, "follows": dict(follows or {}),
            "at": {"t_ms": t, "bound_ms": b, "bounded": bounded, "frame": frame,
                   "has_frame": bounded if has_frame is None else has_frame}}


def rel(a, b):
    return c.episode_order(a, b)[0]


# --- parseAt, as FleetTime::parseAt ------------------------------------------------------
a = c.parse_at("at: 4890438 ±0 frame:5000")
check(a == {"t_ms": 4890438, "bound_ms": 0, "bounded": True, "frame": 5000,
            "has_frame": True}, "a bounded, framed stamp parses")
check(c.parse_at("1000 ±600")["bounded"] and not c.parse_at("1000 ±600")["has_frame"],
      "bounded without a frame")
check(not c.parse_at("1000 ±600 frame:x")["bounded"],
      "a malformed frame makes the WHOLE stamp unbounded (a half-read stamp)")
check(not c.parse_at("1000 ±600 junk")["bounded"], "trailing junk: unbounded")
o = c.parse_at("t_ms:77 stream:0x00000000 wall:0")
check(o["t_ms"] == 77 and not o["bounded"], "a pre-C4 stamp keeps t_ms and orders nothing")
check(not c.parse_at("1000 +-600")["bounded"], "only the UTF-8 ± marks a bound")

# --- order, as test_fleettime.cpp testOrder ----------------------------------------------
check(rel(ep(0x10, 1, 0, 100), ep(0x200, 7, 5000, 100)) == c.ORDER_BEFORE,
      "ITEM 1: non-overlapping stamps order")
c2 = [ep(0x10, 1, 1000, 600), ep(0x200, 7, 2000, 600)]
check(rel(*c2) == c.ORDER_CONCURRENT and c.episode_maximal(c2) == [0, 1],
      "ITEM 2: overlapping, no edge: contested, both quoted")
c3 = [c2[0], ep(0x200, 7, 2000, 600, follows={0x10: 1})]
check(rel(*c3) == c.ORDER_BEFORE and c.episode_maximal(c3) == [1], "ITEM 3: the edge decides")
r, how, contra = c.episode_order(ep(0x10, 9, 5000, 10), ep(0x200, 3, 0, 10, follows={0x10: 9}))
check(r == c.ORDER_BEFORE and how == "edge" and contra,
      "an edge against disjoint stamps: the edge wins and the contradiction is flagged")
check(rel(ep(0x10, 5, 1000, 600), ep(0x200, 1, 1100, 600, follows={0x10: 4}))
      == c.ORDER_CONCURRENT, "follows@seq 4 does not reach seq 5")
check(rel(ep(0x10, 2, 9000, 0), ep(0x10, 3, 0, 0)) == c.ORDER_BEFORE,
      "same agent: its own sequence decides, not its clock")
check(rel(ep(0x10, 1, 0, 0, bounded=False), ep(0x200, 1, 99999, 0)) == c.ORDER_CONCURRENT,
      "an unbounded stamp orders nothing across agents")
check(rel(ep(0x300, 1, 1000, 5, frame=6500), ep(0x10, 40, 90000, 5)) == c.ORDER_CONCURRENT,
      "different frames never order by their numbers")
check(rel(ep(0x300, 2, 1000, 5, has_frame=False), ep(0x10, 40, 90000, 5))
      == c.ORDER_CONCURRENT, "a bounded but frameless stamp orders nothing across agents")
check(rel(ep(0x300, 1, 1000, 5, frame=6500), ep(0x10, 40, 90000, 5, follows={0x300: 1}))
      == c.ORDER_BEFORE, "...but an edge orders across frames: knowledge is not a clock")

# --- seq 0 = unsequenced (test_fleettime.cpp, design §2) ---------------------------------
check(rel(ep(0x300, 0, 1000, 600), ep(0x10, 5, 1100, 600, follows={0x300: 7}))
      == c.ORDER_CONCURRENT, "no follows edge reaches an unsequenced (seq 0) episode")
check(rel(ep(0x300, 0, 1000, 600), ep(0x300, 0, 1100, 600)) == c.ORDER_CONCURRENT,
      "two unsequenced episodes of one agent are NOT the same episode")
check(rel(ep(0x300, 0, 1000, 5), ep(0x300, 0, 9000, 5)) == c.ORDER_BEFORE,
      "...they fall through to the stamp rule")
check(rel(ep(0x300, 0, 9000, 5), ep(0x300, 4, 1000, 5)) == c.ORDER_AFTER,
      "one unsequenced: still the stamps, not the sequence")

# --- the record, as test_episode_order.cpp renders it ------------------------------------
REC = ("\n---\n\n@LAT103LON4 | created:77 | updated:77\n\n**link window**\n\n"
       "```ttdb-episode\nsource: perceptlearn\nat: 4890438 ±0 frame:5000\nseq: 1412\n"
       "follows: 0x00000010:388 0x00000012:212 0x00000200:77\n"
       "said: 1 | 0x00000200 ble met predicted:-40 observed:-38\n"
       "percept: 1 | 0x00000200 | link_stable | ble | + | -\n```\n"
       "\n---\n\n@LAT103LON5 | created:78 | updated:78\n\n**link window**\n\n"
       "```ttdb-episode\nsource: perceptlearn\nat: t_ms:78 stream:0x1 wall:0\n"
       "said: 1 | 0x00000200 ble met predicted:-40 observed:-38\n```\n"
       "\n---\n\n@LAT103LON6 | created:79 | updated:79\n\n**link window**\n\n"
       "```ttdb-episode\nsource: perceptlearn\nat: 5 ±0 frame:5000\nseq: 1413\n"
       "follows: 0x00000010:388 0xzz:1\n```\n")
eps = c.parse_episode_order(REC, 0x300)
check(len(eps) == 3, "every @LAT103 record is an episode")
check(eps[0]["seq"] == 1412 and eps[0]["follows"] == {0x10: 388, 0x12: 212, 0x200: 77}
      and eps[0]["at"]["frame"] == 5000, "seq, follows and the frame read back")
check(eps[1]["seq"] == 0 and eps[1]["follows"] == {} and not eps[1]["at"]["bounded"],
      "a pre-C4 episode reads as unsequenced and unbounded")
check(eps[2]["seq"] == 1413 and eps[2]["follows"] == {},
      "a malformed follows line is dropped whole (an under-claim, as OrderRecovery)")
check(c.parse_follows_line("follows: 0x10:1 0x200:99999999999")[1] is False,
      "an overflowing seq is malformed")
# The belief recomputation must not notice the new lines.
BARE = "".join(l for l in REC.splitlines(keepends=True)
               if not (l.startswith("seq: ") or l.startswith("follows:")))
with_lines = [c.belief_line(b) for b in c.parse_episode_beliefs(REC)]
check(with_lines and with_lines == [c.belief_line(b) for b in c.parse_episode_beliefs(BARE)],
      "parse_episode_beliefs gives identical beliefs with and without seq/follows lines")
check(c.parse_link_percepts(REC) == [], "and so does the link reader (no **LINKWIN**)")

# --- the instrument ----------------------------------------------------------------------
A = [ep(0x10, s, s * 60000, 50) for s in range(1, 6)]
B = [ep(0x200, s, s * 60000 + 30000, 50, follows={0x10: s}) for s in range(1, 6)]
for e in A + B:
    e.update(lon=0, tier=0)
rep = c.order_report({0x10: A, 0x200: B})
p = rep["pairs"]
check(p["total"] == 25 and p["edge"] + p["stamps"] + p["concurrent"] == 25,
      "every cross-agent pair is classified exactly once")
check(p["contradictions"] == 0, "edges that agree with the stamps are no contradiction")
check(p["gate_pairs"] == 25 and p["gate_edge"] == 15,
      "gate (b): pairs > 20 s apart, of which B-after-A are ordered by edge (A after B is not)")
B2 = [dict(e, follows={}) for e in B]
rep2 = c.order_report({0x10: A, 0x200: B2})
check(rep2["pairs"]["edge"] == 0 and rep2["pairs"]["stamps"] == 25,
      "with no vectors heard, the same pairs fall back to stamps")
G = [ep(0x10, s, 0, 0) for s in (3, 4, 6, 6)]
check(c.order_report({0x10: G})["agents"][0x10]["gaps"] == 1 and
      c.order_report({0x10: G})["agents"][0x10]["duplicates"] == 1,
      "per-agent density: a missing seq is a gap, a repeated one a duplicate")

print()
if fails:
    sys.exit(f"{fails} FAILURE(S)")
print("all episode-order tests passed")
