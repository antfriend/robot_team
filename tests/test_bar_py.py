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

# The BAR record (@LAT106), pinned byte for byte against tests/test_episode_delivery.cpp.
WANT = ("@LAT106LON7 | created:0 | updated:0\n\n"
        "**BAR** frame:5500 bar:1 own:1 held:1 terms:2 digest:0xfa9dab24 settled_ms:120000\n"
        "**HOLDS** agent:0x00000200 n:1 lo:4 hi:4 sum:4\n"
        "**HOLDS** agent:0x00000300 n:1 lo:1 hi:1 sum:1\n")
fv = c.bar_view(c.bar_episodes(FX), 5500, 1, self_id=0x300)
check(c.render_bar_record(7, 5500, 1, fv, 120000) == WANT,
      "the pinned fixture's BAR record, byte-exact (= firmware renderBar)")
recs = c.parse_bar_records(FX + "\n---\n\n" + WANT)
r = recs.get((5500, 1))
check(r is not None and r["digest"] == 0xfa9dab24 and r["terms"] == 2 and r["lon"] == 7
      and r["holds"] == {0x200: (1, 4, 4, 4), 0x300: (1, 1, 1, 1)} and r["settled_ms"] == 120000,
      "parse_bar_records reads it back")
check(r is not None and r["holds"] == fv["holds"], "its HOLDS rows = the recomputed holds")
check(r is not None and r["deliver"] is None, "a pre-2026-10-05 record carries no DELIVER")

# The DELIVER line, pinned against the same string in tests/test_episode_delivery.cpp.
D = dict(zip(c.DELIVER_FIELDS, (11599, 132468, 885, 544, 116, 2578, 135, 2828, 2852, 38, 0, 2)))
DL = ("**DELIVER** up_s:11599 heap:132468 fetched:885 unanswered:544 broken:116 resumed:2578 "
      "empty:135 served:2828 wants:2852 early:38 wantq_drop:0 superseded:2\n")
check(c.render_bar_record(7, 5500, 1, fv, 120000, D) == WANT + DL,
      "DELIVER rides after the BAR/HOLDS lines, byte-exact (= firmware renderBar)")
rd = c.parse_bar_records(WANT + DL)[(5500, 1)]
check(rd["deliver"] == D and rd["holds"] == r["holds"] and rd["digest"] == r["digest"],
      "parse_bar_records reads DELIVER back, and the rest of the record is unchanged")
D2 = dict(D, up_s=12199, fetched=925, served=2960, wants=2985)
D3 = dict(D, up_s=40, fetched=3)                       # rebooted: counters restarted
dr = c.deliver_rows({(5500, 1): dict(rd), (5500, 2): dict(rd, deliver=D2),
                     (5500, 3): dict(rd, deliver=D3), (5500, 4): dict(rd, deliver=None)})
check(len(dr) == 3 and dr[0][3] is None and dr[1][3]["fetched"] == 40 and
      dr[1][3]["served"] == 132 and dr[2][3] is None,
      "deliver_rows: per-bar deltas; none for the first, none across a reboot, old records skipped")

import io, contextlib  # noqa: E402
# TTG-0004 §4.8 item 5: a fleet with two grammar hashes reports the split. Same strings as
# tests/test_episode_delivery.cpp's testGrammar.
G = {"hash": 0x11111111, "same": 1, "splits": {0x300: 0x22222222}}
GL = ("**GRAMMAR** hash:0x11111111 same:1 split:1\n"
      "**SPLIT** agent:0x00000300 grammar:0x22222222\n")
check(c.render_bar_record(7, 5500, 1, fv, 120000, D, G) == WANT + DL + GL,
      "GRAMMAR + SPLIT ride after DELIVER, byte-exact (= firmware renderBar)")
rg = c.parse_bar_records(WANT + DL + GL)[(5500, 1)]
check(rg["grammar"] == {"hash": 0x11111111, "same": 1, "split": 1, "splits": {0x300: 0x22222222}}
      and rg["deliver"] == D and rg["holds"] == r["holds"],
      "parse_bar_records reads GRAMMAR/SPLIT back; the rest of the record is unchanged")
check(r["grammar"] is None, "a pre-2026-10-06 record carries no grammar")
one = {"x": c.parse_bar_records(c.render_bar_record(1, 5500, 1, fv, 1, None,
                                                    {"hash": 0xAA, "same": 1, "splits": {}})),
       "y": c.parse_bar_records(c.render_bar_record(1, 5500, 1, fv, 1, None,
                                                    {"hash": 0xAA, "same": 1, "splits": {}}))}
by, sp = c.grammar_split(one)
check(by == {"x": 0xAA, "y": 0xAA} and sp == [], "one grammar across the fleet: no split")
two = {"x": one["x"],
       "y": c.parse_bar_records(c.render_bar_record(1, 5500, 1, fv, 1, None,
                                                    {"hash": 0xBB, "same": 0,
                                                     "splits": {0x300: 0xAA}}))}
by, sp = c.grammar_split(two)
buf = io.StringIO()
with contextlib.redirect_stdout(buf):
    is_split = c.grammar_report(two)
check(by == {"x": 0xAA, "y": 0xBB} and sp == [(5500, 1, "y", 0x300, 0xAA)] and is_split
      and "SPLIT" in buf.getvalue(),
      "two grammar hashes: the fleet check reports the split, and what the boards saw")
quiet = io.StringIO()
with contextlib.redirect_stdout(quiet):
    check(c.grammar_report({"x": c.parse_bar_records(WANT)}) is False and quiet.getvalue() == "",
          "records with no GRAMMAR line: nothing reported, no split claimed")

# Scoring records: X and Y each record bar 1 and 2 (item-4 stores above).
xr = "".join(c.render_bar_record(n, F, n, c.bar_view(X, F, n, self_id=0x300), 120000) + "\n---\n\n"
             for n in (1, 2))
yr = "".join(c.render_bar_record(n, F, n, c.bar_view(Y, F, n, self_id=0x200), 125000) + "\n---\n\n"
             for n in (1, 2))
RX, RY = c.parse_bar_records(xr), c.parse_bar_records(yr)
views = {"x": {(F, n): c.bar_view(X, F, n, self_id=0x300) for n in (1, 2)},
         "y": {(F, n): c.bar_view(Y, F, n, self_id=0x200) for n in (1, 2)}}
rows = c.bar_records_report({"x": RX, "y": RY}, views)
check(len(rows) == 2 and all(da and ha for _, _, _, da, ha in rows),
      "records of the same episodes: digests AGREE and HOLDS sets are the same")
miss = c.bar_episodes(missing)
mr = c.parse_bar_records(c.render_bar_record(0, F, 1, c.bar_view(miss, F, 1, self_id=0x300), 1))
rows = c.bar_records_report({"x": mr, "y": RY}, {})
check(rows[0][3] is False and rows[0][4] is False,
      "one missing copy: the records DIFFER and their sets differ (scorable with no copies)")
check(len(c.bar_records_report({"x": RX}, {})) == 2, "a bar only one node recorded is listed")
import io, contextlib  # noqa: E402
bad = c.parse_bar_records(xr)
bad[(F, 1)]["digest"] ^= 1                     # bar 1 recorded something else; bar 2 intact
buf = io.StringIO()
with contextlib.redirect_stdout(buf):
    c.bar_records_report({"x": bad}, views)
check("NOT reproduced" in buf.getvalue().splitlines()[0] and
      "[reproduced]" in buf.getvalue().splitlines()[1],
      "(f) can fail: a record the copies on flash do not reproduce says NOT reproduced")

rec = {0x200: (10, 200, 209, 2045), 0x300: (10, 1038, 1057, 10473)}
check(c.bar_holds_trimmed({0x200: (10, 200, 209, 2045), 0x300: (4, 1050, 1057, 4215)}, rec),
      "copies cut since the record (fewer, inside its seq range): trimmed")
check(not c.bar_holds_trimmed(dict(rec), rec), "the same holds are not 'trimmed'")
check(not c.bar_holds_trimmed({0x200: (10, 200, 209, 2045), 0x300: (4, 1050, 1060, 4215)}, rec),
      "a seq outside the recorded range is a contradiction, not a trim")
check(not c.bar_holds_trimmed({0x200: (10, 200, 209, 2045), 0x999: (1, 5, 5, 5)}, rec),
      "an author the record never held is a contradiction, not a trim")

recc = {0x300: (10, 900, 918, 9090), 0x200: (1, 231, 231, 231)}
check(c.bar_only_held_changed({0x300: (10, 900, 918, 9090), 0x200: (4, 231, 234, 930)}, recc, 0x300),
      "own row intact, more held copies since the record: 'changed since', not a contradiction")
check(not c.bar_only_held_changed({0x300: (9, 900, 918, 8190), 0x200: (4, 231, 234, 930)}, recc, 0x300)
      or c.bar_holds_trimmed({0x300: (9, 900, 918, 8190)}, {0x300: recc[0x300]}),
      "a trimmed own row still counts as intact")
check(not c.bar_only_held_changed({0x300: (11, 900, 920, 9999), 0x200: (1, 231, 231, 231)}, recc, 0x300),
      "an own row that GREW past the record is a contradiction")

print()
if fails:
    sys.exit(f"{fails} FAILURE(S)")
print("all bar-view tests passed")
