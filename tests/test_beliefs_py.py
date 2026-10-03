#!/usr/bin/env python3
"""test_beliefs_py.py — fleet.py's recomputation of a node's beliefs from a pull
(ACT-III §C3, 2026-10-02).

Since C3 was wired the Cardputer writes no belief record: its beliefs are TTG-0003 counts
over the live @LAT103 episodes plus the newest @LAT104 checkpoint's carried tallies. The
reader must reproduce the firmware's `belief:` lines exactly — and, like the firmware,
read ONLY the newest checkpoint and skip episodes at or behind its horizon even when a
refused cut left them on flash (the double count the commit order exists to prevent).

Verified against hardware the day it was written: 9 of 9 lines byte-identical to the
node's own `[episode]` serial output over the same pull.

Run: python tests/test_beliefs_py.py
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


def ep(lon, *percepts):
    body = "".join(f"percept: {i + 1} | {p}\n" for i, p in enumerate(percepts))
    return (f"\n---\n\n@LAT103LON{lon} | created:0 | updated:0\n\n**link window**\n\n"
            f"```ttdb-episode\nsource: linkpercept\nat: x\n{body}```\n")


def ck(lon, *lines):
    return (f"\n---\n\n@LAT104LON{lon} | created:0 | updated:0\n\n**carried**\n\n"
            "```ttdb-carried\n" + "".join(l + "\n" for l in lines) + "```\n")


A = "0x00000200 | link_stable | espnow"
B = "0x00000010 | link_stable | ble"

# An OLD checkpoint (must be ignored), the NEWEST checkpoint (horizon 5 for link, carrying
# 4 for / 1 against for A), a dead episode at the horizon still on flash, and three live.
TEXT = (ck(0, "through: 2", "carried: 99 99 9 9 | 0x00000200 | link_stable | espnow")
        + ep(5, f"{A} | + | -", f"{B} | + | -")                 # dead: == through
        + ck(1, "through: 5", "through: 16390",
             "carried: 4 1 5 6 | 0x00000200 | link_stable | espnow")
        + ep(6, f"{A} | + | -", f"{A} | + | ~", f"{B} | - | -")  # A once (max), B against
        + ep(7, f"{A} | - | ~", f"{B} | ? | -")                  # A half against; B held
        + ep(8, "- | link_stable | espnow | + | -")                # a mention: never a term
        + ep(16391, f"{B} | + | -"))                             # motion band, live

bs = c.parse_episode_beliefs(TEXT)
by = {(b["subject"], b["object"]): b for b in bs}
a, b = by[("0x00000200", "espnow")], by[("0x00000010", "ble")]
check(len(bs) == 2, "two terms; the mention forms none")
check(a["for_h"] == 4 * 2 + 2 and a["against_h"] == 2 + 1,
      "A = carried 4/1 + live: one vote FOR (per-episode max, not two) + a half AGAINST")
check(c.belief_line(a) == "belief: link_stable | espnow | + | 5 1.5 | 180",
      "the belief line renders halves as N.5, conf = 255*(10+2)/(10+3+4) = 180 exactly "
      "(got '%s')" % c.belief_line(a))
check(b["for_h"] == 2 and b["against_h"] == 2 and b["pol"] == "?",
      "B: the dead episode at the horizon is NOT counted; held is not believed")
check(b["sal"] == 3, "but held percepts count as seen (3 matching percepts live)")
check(a["carried_for_h"] == 8, "only the NEWEST checkpoint seeds carried (99 ignored)")

# No checkpoint at all: every episode is live.
bs2 = c.parse_episode_beliefs(ep(0, f"{A} | + | -") + ep(1, f"{A} | + | -"))
check(len(bs2) == 1 and bs2[0]["for_h"] == 4 and bs2[0]["conf"] == 191,
      "no checkpoint: everything counts — 2 for 0 against, conf round(255*3/4) = 191")

# Order independence, TTG-0003's point: reversing the live episodes changes nothing.
parts = [ep(6, f"{A} | + | -"), ep(7, f"{A} | - | -"), ep(8, f"{A} | + | ~")]
fwd = c.parse_episode_beliefs("".join(parts))
rev = c.parse_episode_beliefs("".join(reversed(parts)))
check([c.belief_line(x) for x in fwd] == [c.belief_line(x) for x in rev],
      "reordered episodes give identical belief lines")

check(c.parse_episode_beliefs("# nothing\n") == [], "no episodes -> no beliefs")

print()
if fails:
    sys.exit(f"{fails} FAILURE(S)")
print("all belief-recomputation tests passed")
