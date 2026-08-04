#!/usr/bin/env python3
"""test_lanegen_py.py — the laptop half of lane generations (@LAT100).

The firmware half is tests/test_lanegen.cpp. This covers what companion.py has to
get right for the boundary to be worth writing: reading the marker, and deciding
which citations it invalidated WITHOUT flagging the ones written after it.

Run: python tests/test_lanegen_py.py
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


STREAM = 0x59fb8ce8

# A node that pruned @LAT97 (48 records, indices 0..47) at t_ms 6_600_000, holding
# outcome records written before AND after the prune. The pre-prune one cites the
# generation that was destroyed; the post-prune one cites the live generation and
# happens to use a low index too — which is exactly the case a naive index-only
# check would report as broken.
TEXT = f"""
@LAT0LON0 | created:0 | updated:0 | relates:

**IDENTITY** node:0x300

---

@LAT92LON0 | created:0 | updated:0 | relates:testifies_about@LAT95LON0,derived_from@LAT97LON1,senses@LAT0LON0

**OUTCOME** t_ms:120000 stream:0x{STREAM:08x} wall:0 node:0x300 acting:@LAT95LON0 observed_in:@LAT97LON1 met:8 violated:0

---

@LAT100LON0 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:97 gen:1 removed:48 last_lon:47 t_ms:6600000 stream:0x{STREAM:08x} wall:0 node:0x00000300

---

@LAT92LON1 | created:0 | updated:0 | relates:testifies_about@LAT95LON2,derived_from@LAT97LON1,senses@LAT0LON0

**OUTCOME** t_ms:6700000 stream:0x{STREAM:08x} wall:0 node:0x300 acting:@LAT95LON2 observed_in:@LAT97LON1 met:6 violated:2
"""

mk = c.parse_prune_markers(TEXT)
check(len(mk) == 1, "the @LAT100 marker parses")
check(mk[0]["lane"] == 97 and mk[0]["gen"] == 1 and mk[0]["removed"] == 48
      and mk[0]["last_lon"] == 47,
      "lane, generation, count and the last index that existed all read back")
check(mk[0]["t_ms"] == 6600000 and mk[0]["stream"] == STREAM,
      "the marker carries the standard stamp, and it parses like any other record")
check(c.parse_prune_markers("@LAT0LON0 | created:0\n\n**IDENTITY** node:0x1\n") == [],
      "a TTDB with no prune history yields no markers (not an error)")

stale = c.stale_citations(TEXT)
by_citing = {s["citing"]: s for s in stale}
check(len(stale) == 1, "exactly one citation is reported, not both")
check("@LAT92LON0" in by_citing and by_citing["@LAT92LON0"]["verdict"] == "stale",
      "the record written BEFORE the boundary cites a generation that is gone")
check(by_citing["@LAT92LON0"]["lane"] == 97
      and by_citing["@LAT92LON0"]["lon"] == 1
      and by_citing["@LAT92LON0"]["gen"] == 1,
      "and the report names the lane, the index and the generation that ended")
# ⚠ The check this test exists for. Both records cite @LAT97LON1. Only one of them
# is wrong, and it is not distinguishable by index — only by time, on the timeline
# the marker was written on. A version that flagged both would be noise, and a
# correctness report that cries wolf gets switched off.
check("@LAT92LON1" not in by_citing,
      "the record written AFTER the boundary cites the LIVE generation and is "
      "NOT flagged, though it uses the same index")

# An old-format record (synced:1, no stream id) genuinely cannot be placed against
# a boundary. That is reported as its own verdict rather than guessed either way —
# the same rule the recency filter applies to windows on an unnameable clock.
OLD = TEXT.replace(f"t_ms:120000 stream:0x{STREAM:08x} wall:0",
                   "t_ms:120000 synced:1")
old_stale = c.stale_citations(OLD)
old_by = {s["citing"]: s for s in old_stale}
check(old_by.get("@LAT92LON0", {}).get("verdict") == "unknown",
      "a pre-time-stream citation is 'unknown', never silently stale or safe")

# A citation ABOVE the boundary was never part of the pruned generation.
HIGH = TEXT.replace("derived_from@LAT97LON1,senses", "derived_from@LAT97LON99,senses")
check(all(s["lon"] != 99 for s in c.stale_citations(HIGH)),
      "an index above last_lon was never in the ended generation")

# Lanes with no boundary are untouched, and the marker's own record is not
# self-reported (its only edge points at @LAT0).
check(all(s["lane"] == 97 for s in stale),
      "a lane that was never pruned produces no findings (@LAT95 here)")
check(all(s["citing"] != "@LAT100LON0" for s in stale),
      "the boundary record does not report itself")

# Two generations of the same lane: the newest boundary bounds every reused index.
TWO = TEXT + f"""
---

@LAT100LON1 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:97 gen:2 removed:6 last_lon:5 t_ms:6800000 stream:0x{STREAM:08x} wall:0 node:0x00000300
"""
two = c.stale_citations(TWO)
check(len(c.parse_prune_markers(TWO)) == 2, "both generations are recorded")
check(any(s["citing"] == "@LAT92LON1" and s["verdict"] == "stale" for s in two),
      "a second prune makes the once-live citation stale in its turn — the "
      "boundary is re-evaluated, not decided once")

# The timeline lane's own boundary. Pruning @LAT90 would orphan every older record's
# `stream:` stamp, so the ids it explained ride along in the marker; the reader has to
# surface them or the mitigation is invisible from the laptop.
TL = f"""
@LAT100LON3 | created:0 | updated:0 | relates:prunes@LAT0LON0

**LANE-PRUNED** lane:90 gen:1 removed:16 last_lon:15 t_ms:9000000 stream:0x{STREAM:08x} wall:0 node:0x00000300
**STREAMS-EXPLAINED** n:3 0x59fb8ce8 0xbdc62024 0xe7384824
"""
tl = c.parse_prune_markers(TL)
check(len(tl) == 1 and tl[0]["lane"] == 90 and tl[0]["removed"] == 16,
      "a timeline boundary parses like any other")
check(tl[0]["explained"] == [0x59fb8ce8, 0xbdc62024, 0xe7384824],
      "and the streams it kept answerable are read back in order")
check(tl[0]["stream"] == STREAM,
      "the boundary's OWN stamp is not confused with the ids it carries")
check(c.parse_prune_markers(TEXT)[0]["explained"] == [],
      "a percept boundary carries no id list and reads as an empty one, not None")

print()
if fails:
    sys.exit(f"{fails} FAILURE(S)")
print("all lanegen (laptop) tests passed")
