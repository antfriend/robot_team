#!/usr/bin/env python3
"""test_entity_py.py — verify companion.py's SP0 entity-co-occurrence tier
(semantic positioning, ttn-semantic-positioning.md §3 Phase 0) without hardware:
parsing the @LAT96 lane the firmware EntityPercept log writes, and the pairwise
Jaccard-overlap consolidation that turns shared WiFi APs into a coarse proximity
bound. Mirrors the on-device record format pinned by test_entitypercept.cpp.

Run: python tests/test_entity_py.py
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


# An @LAT96 lane exactly as EntityPercept::buildRecord emits it (two windows).
LANE = """```mmpdb
db_id: x
```

---

@LAT0LON0 | relates:

**HELLO** node

---

@LAT96LON0 | created:1780000000 | updated:1780000000 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1780000000123 synced:1 window_ms:60000 entities:2
**ENTITY** kind:wifi_ap id:a42bb0112233 n:12 rssi:-58
**ENTITY** kind:wifi_ap id:deadbeef0001 n:3 rssi:-71

---

@LAT96LON1 | created:1780000060 | updated:1780000060 | relates:observes@LAT0LON0

**ENTWIN** t_ms:1780000060777 synced:1 window_ms:60000 entities:1
**ENTITY** kind:wifi_ap id:a42bb0112233 n:9 rssi:-55
"""


# ---------------------------------------------------------------------------
# 1) Parse the @LAT96 lane into windows + entity lists.
wins = c.parse_entity_percepts(LANE)
check(len(wins) == 2, "two @LAT96 windows parsed")
check(wins[0]["t_ms"] == 1780000000123 and wins[0]["synced"] == 1,
      "ENTWIN t_ms + synced parsed")
check(len(wins[0]["entities"]) == 2, "window 0 has 2 ENTITY lines")
e = wins[0]["entities"][0]
check(e["id"] == "a42bb0112233" and e["kind"] == "wifi_ap" and e["n"] == 12
      and e["rssi"] == -58, "ENTITY fields parsed (id/kind/n/rssi)")
check(wins[1]["entities"][0]["id"] == "a42bb0112233", "second window entity parsed")

# 2) A non-@LAT96 record header ends the window (no leak across records).
check(all(all(x["kind"] == "wifi_ap" for x in w["entities"]) for w in wins),
      "no stray lines captured from other records")

# 3) The node's union of BSSIDs across its windows.
seen = c._entity_set(wins)
check(seen == {"a42bb0112233", "deadbeef0001"}, "entity set = union across windows")

# 4) Jaccard consolidation over a small fleet.
#    A saw {AP1, AP2, AP3}; B saw {AP1, AP2, AP4}; C saw {AP9} (disjoint from A/B).
def win(*ids):
    return [{"lane": 0, "t_ms": 1, "synced": 1, "window_ms": 60000,
             "entities": [{"kind": "wifi_ap", "id": i, "n": 5, "rssi": -60} for i in ids]}]

fleet = {
    "v4a_bridge": win("ap1", "ap2", "ap3"),
    "v4b_relay": win("ap1", "ap2", "ap4"),
    "tdeck_1": win("ap9"),
}
beliefs = c.consolidate_entity_jaccard(fleet)
pairs = {frozenset(b["pair"]): b for b in beliefs}
check(frozenset(("v4a_bridge", "v4b_relay")) in pairs,
      "overlapping pair produces a co-occurrence belief")
check(frozenset(("v4a_bridge", "tdeck_1")) not in pairs,
      "disjoint pair produces NO belief (no shared AP)")
ab = pairs[frozenset(("v4a_bridge", "v4b_relay"))]
# shared {ap1,ap2}=2, union {ap1,ap2,ap3,ap4}=4 -> Jaccard 0.5.
check(ab["shared"] == 2 and ab["union"] == 4 and abs(ab["jaccard"] - 0.5) < 1e-9,
      "Jaccard = |intersection| / |union| = 0.5")

# 5) Bound: higher overlap -> tighter (smaller) distance bound; disjoint -> None.
check(c.entity_jaccard_bound(0.0) is None, "disjoint sets -> no bound")
b_hi = c.entity_jaccard_bound(1.0)
b_lo = c.entity_jaccard_bound(0.1)
check(abs(b_hi - c.ENTITY_BOUND_TIGHT_M) < 1e-9, "full overlap -> tightest bound")
check(b_hi < b_lo <= c.ENTITY_BOUND_LOOSE_M, "more overlap -> tighter bound (monotone)")
check(ab["bound_m"] is not None and c.ENTITY_BOUND_TIGHT_M < ab["bound_m"]
      < c.ENTITY_BOUND_LOOSE_M, "the 0.5-Jaccard pair gets a mid-range bound")

# 6) An empty / percept-less TTDB yields no windows and no beliefs (not a crash).
check(c.parse_entity_percepts("# nothing\n") == [], "no @LAT96 -> empty window list")
check(c.consolidate_entity_jaccard({"v4a_bridge": [], "v4b_relay": []}) == [],
      "no entities anywhere -> no beliefs")

# ---------------------------------------------------------------------------
print()
if fails:
    print(f"{fails} FAILED")
    sys.exit(1)
print("all entity-percept checks passed")
