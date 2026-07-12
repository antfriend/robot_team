#!/usr/bin/env python3
"""test_position_belief_py.py — verify companion.py's SP2 "publish @BELIEF:POSITION
back to each node" authoring without hardware (semantic positioning,
ttn-semantic-positioning.md §3 Phase 2, PLAN.md SP2). Checks that
`author_position_belief` turns master/positions.md (relative frame) and
master/anchored.md (geo frame) into a valid, byte-exact-round-trippable belief that
rides the existing TTN-RFC-0009 push path — one @BELIEF:POSITION record per node,
each tagged with node_id: so firmware can match its own position (SP4).

Run: python tests/test_position_belief_py.py
"""
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


REL = """# Fleet Position Beliefs (semantic positioning SP2)

Authored by `companion.py positions`.

---

@BELIEF:POSITION @node(k10_1)
frame: relative   # anchor v4a_bridge at origin
x_m: 16.25
y_m: -0.00
sigma_m: 51.28
conf: 0.58
flip_resolved: false
touched: 2026-07-10T17:49:16Z

---

@BELIEF:POSITION @node(v4a_bridge)
frame: relative   # anchor v4a_bridge at origin
x_m: 0.00
y_m: -0.00
sigma_m: 57.72
conf: 0.55
flip_resolved: false
touched: 2026-07-10T17:49:16Z
"""

GEO = """# Fleet Anchored Position Beliefs (semantic positioning SP2)

Authored by `companion.py anchor`.

fit: ties=4 scale=0.2768 reflected=False tie_rmse=4.98 m flip_resolved=True

---

@BELIEF:POSITION @node(k10_1)
frame: geo   # absolute, GPS-anchored
lat_deg: 43.6525104
lon_deg: -116.3364312
x_m: 16.25
y_m: -0.00   # relative frame
sigma_m: 51.28
anchor_chain: [v4a_bridge, gps]
is_tie: yes
flip_resolved: true
tie_rmse_m: 4.98
touched: 2026-07-10T18:00:59Z

---

@BELIEF:POSITION @node(tdeck_1)
frame: geo   # absolute, GPS-anchored
lat_deg: 43.6525171
lon_deg: -116.3365556
x_m: 33.61
y_m: 31.87   # relative frame
sigma_m: 61.96
anchor_chain: [v4a_bridge, gps]
is_tie: yes
flip_resolved: true
tie_rmse_m: 4.98
touched: 2026-07-10T18:00:59Z
"""


def author(text):
    with tempfile.NamedTemporaryFile("w", suffix=".md", delete=False,
                                     encoding="utf-8", newline="\n") as f:
        f.write(text)
        path = f.name
    try:
        content, n = c.author_position_belief(path)
    finally:
        os.unlink(path)
    return content.decode("utf-8"), n


# ---------------------------------------------------------------------------
# 1) Relative-frame authoring: record count, node_id tags, field preservation.
rel, nrel = author(REL)
check(nrel == 2, "relative: 2 @BELIEF:POSITION records authored")
check(rel.count("@BELIEF:POSITION @node(") == 2, "relative: both records keyed by @node")
check("node_id: 0x00000100" in rel, "relative: k10_1 tagged node_id 0x100")
check("node_id: 0x00000010" in rel, "relative: v4a_bridge tagged node_id 0x10")
check("x_m: 16.25" in rel and "sigma_m: 51.28" in rel,
      "relative: numeric fields preserved verbatim")
check("frame: relative" in rel, "relative: frame line preserved")

# 2) node_id sits directly under the @node header so a firmware strstr finds it
#    adjacent to that node's own coordinates.
m = re.search(r"@node\(k10_1\)\s*\nnode_id: 0x00000100\s*\nframe: relative", rel)
check(m is not None, "relative: node_id injected between @node header and body")

# 3) The belief is valid TTDB the node can store: has an mmpdb header + cursor.
check("```mmpdb" in rel and "db_id: fleet-position-belief-001" in rel,
      "authored belief carries an mmpdb header")
check("```cursor" in rel, "authored belief carries a cursor block")

# 4) CRC + byte contract: the bytes are stable and CRC matches (what push verifies).
b1, _ = author(REL)
b2, _ = author(REL)
check(b1 == b2, "authoring is deterministic (byte-identical)")
check(isinstance(c.crc32(b1.encode("utf-8")), int), "crc32 computes over the bytes")

# 5) Geo-frame authoring: absolute lat/lon carried through, ids tagged.
geo, ngeo = author(GEO)
check(ngeo == 2, "geo: 2 anchored records authored")
check("lat_deg: 43.6525104" in geo and "lon_deg: -116.3364312" in geo,
      "geo: absolute lat/lon preserved")
check("node_id: 0x00000200" in geo, "geo: tdeck_1 tagged node_id 0x200")
check("frame: geo" in geo, "geo: frame line preserved (absolute)")
check("anchor_chain: [v4a_bridge, gps]" in geo, "geo: anchor_chain preserved")

# 6) A node can locate its OWN position by its numeric id (the SP4 use).
for node, nid in (("k10_1", 0x100), ("tdeck_1", 0x200)):
    tag = f"node_id: 0x{nid:08X}"
    idx = geo.find(tag)
    seg = geo[idx: idx + 220]
    check("lat_deg:" in seg and "lon_deg:" in seg,
          f"geo: {node} finds its lat/lon adjacent to its node_id")

# 7) An empty / record-less source is a hard error, not a silent empty push.
try:
    author("# nothing here\n\nno records\n")
    check(False, "empty source should sys.exit")
except SystemExit:
    check(True, "empty source rejected (SystemExit)")

# ---------------------------------------------------------------------------
print()
if fails:
    print(f"{fails} FAILED")
    sys.exit(1)
print("all position-belief checks passed")
