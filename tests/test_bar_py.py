#!/usr/bin/env python3
"""test_bar_py.py — fleet.py's BAR VIEW (ACT-III §C4 stage 2, docs/design/episode-order.md
§7.4): the per-bar digest two nodes holding the same episodes must agree on.

The digest is pinned against the firmware: the fixture below and its digest 0xfa9dab24 are
asserted in tests/test_episode_delivery.cpp too (BarView + barDigest). If either side
drifts, `fleet.py bar` reports DIFFER for nodes that agree, or AGREE for nodes that do not.

Run: python tests/test_bar_py.py
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


FX = ("@LAT103LON0 | created:0 | updated:0\n\n**link window**\n\n```ttdb-episode\n"
      "source: perceptlearn\nat: 65500 ±50 frame:5500\nseq: 1\nsaid: 1 | x\n"
      "percept: 1 | 0x00000010 | link_stable | espnow | + | -\n"
      "percept: 2 | 0x00000200 | link_stable | ble | - | -\n```\n\n---\n\n"
      "@LAT105LON0 | created:0 | updated:0\n\n**link window**\n\n```ttdb-episode\n"
      "held: 0x00000200\nsource: perceptlearn\nat: 125500 ±50 frame:5500\nseq: 4\n"
      "percept: 1 | 0x00000010 | link_stable | espnow | + | ~\n```\n")
v = c.bar_view(c.bar_episodes(FX), 5500, 1)
check(v["own"] == 1 and v["held"] == 1 and v["terms"] == 2 and v["digest"] == 0xfa9dab24,
      "the pinned fixture: own 1, held 1, 2 terms, digest 0xfa9dab24 (= firmware)")
eps = c.bar_episodes(FX)
check(eps[1]["agent"] == 0x200 and eps[1]["seq"] == 4, "a held copy names its author and seq")

F, B = 5500, c.BAR_MS


def ep(lane, lon, t, b, percepts, held=None, seq=1, frame=F):
    h = f"held: 0x{held:08x}\n" if held is not None else ""
    body = "".join(f"percept: {i + 1} | {p}\n" for i, p in enumerate(percepts))
    return (f"\n---\n\n@LAT{lane}LON{lon} | created:0 | updated:0\n\n**link window**\n\n"
            f"```ttdb-episode\n{h}source: perceptlearn\nat: {t} ±{b} frame:{frame}\n"
            f"seq: {seq}\n{body}```\n")


# The window: [F + (n-1)B, F + nB), whole range inside.
check(c.bar_view(c.bar_episodes(ep(103, 0, F + B, 1000, ["0x99 | link_stable | espnow | + | -"])),
                 F, 1)["terms"] == 0 and
      c.bar_view(c.bar_episodes(ep(103, 0, F + B, 1000, ["0x99 | link_stable | espnow | + | -"])),
                 F, 2)["terms"] == 0,
      "a range across a bar line is in neither bar")
check(c.bar_view(c.bar_episodes(ep(103, 0, F + 1000, 0, ["0x99 | link_stable | espnow | + | -"],
                                   frame=6500)), F, 1)["terms"] == 0,
      "another frame is in no bar of this one")
check(c.bar_view(c.bar_episodes(ep(103, 8195, F + 1000, 0,
                                   ["0x99 | link_stable | espnow | + | -"])), F, 1)["terms"] == 0,
      "a non-LINK own episode is not in the view")

# ITEM 4 on synthetic stores: X and Y each hold their own + the other's copies.
x_own = y_own = x_held = y_held = ""
x_eps, y_eps = [], []
for m in range(1, 20):
    t = F + m * 60000
    ex = ep(103, m, t, 50, [f"0x00000010 | link_stable | espnow | {'+' if m % 3 else '-'} | -"],
            seq=m)
    ey = ep(103, m, t + 20000, 50,
            [f"0x00000300 | link_stable | ble | {'+' if m % 4 else '-'} | -"], seq=m)
    x_own += ex
    y_own += ey
    y_held += ex.replace("@LAT103", "@LAT105").replace("```ttdb-episode\n",
                                                        "```ttdb-episode\nheld: 0x00000300\n")
    x_held += ey.replace("@LAT103", "@LAT105").replace("```ttdb-episode\n",
                                                        "```ttdb-episode\nheld: 0x00000200\n")
    x_eps.append(ex)
    y_eps.append(ey)
X, Y = c.bar_episodes(x_own + x_held), c.bar_episodes(y_own + y_held)
for n in (1, 2):
    vx, vy = c.bar_view(X, F, n), c.bar_view(Y, F, n)
    check(vx["terms"] > 0 and (vx["terms"], vx["digest"]) == (vy["terms"], vy["digest"])
          and vx["own"] == vy["held"] and vx["held"] == vy["own"],
          f"bar {n}: X and Y agree ({vx['terms']} terms, 0x{vx['digest']:08x})")
check(c.parse_episode_beliefs(x_own) != c.parse_episode_beliefs(y_own),
      "NOT VACUOUS: their own beliefs differ")
missing = x_own + "".join(
    e.replace("@LAT103", "@LAT105").replace("```ttdb-episode\n", "```ttdb-episode\nheld: 0x00000200\n")
    for i, e in enumerate(y_eps) if i != 2)
check(c.bar_view(c.bar_episodes(missing), F, 1)["digest"] != c.bar_view(Y, F, 1)["digest"],
      "one missing copy changes that bar's digest (the gate can fail)")
check(c.bar_view(c.bar_episodes(x_held + x_own), F, 2)["digest"] == c.bar_view(X, F, 2)["digest"],
      "record order does not matter")

print()
if fails:
    sys.exit(f"{fails} FAILURE(S)")
print("all bar-view tests passed")
