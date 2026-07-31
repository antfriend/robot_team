"""Pull every node into master/<node>.md, preferring each node's OWN cable.

A bridged pull can silently return a file stitched from two generations of a TTDB that
was being appended to underneath the stream (companion.md §6, 2026-07-31) — the gap
check tests offset coverage, not version. Direct pulls are one shot and take seconds,
so they are far less exposed. This routes the two cabled nodes over their own ports and
only bridges the rest, then reports each file's size and lane counts so a stitched or
truncated result is visible BEFORE `proximity --no-pull` consumes it.

  python scratchpad/collect.py
"""
import os
import re
import sys
import time

sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "orchestrator"))
import companion as c  # noqa: E402

BRIDGE = "COM6"
# node -> port to pull it over. COM6 is V4-A's own cable AND the mesh bridge.
ROUTE = {
    "v4a_bridge":  ("COM6",  "direct (own cable)"),
    "tdeck_1":     ("COM10", "direct (own cable)"),
    "v4b_relay":   (BRIDGE,  "bridged"),
    "v4c_edge":    (BRIDGE,  "bridged"),
    "cardputer_1": (BRIDGE,  "bridged"),
}
EXPECT = {"96": ("ENTWIN", "ENTITY"), "97": ("LINKWIN", "LINK")}


def lanes_and_check(path):
    """Return (bytes, {lat: count}, foreign_body_records). The last is the
    two-generation tell: a record carrying another lane's body tokens."""
    s = open(path, encoding="utf-8", errors="replace").read()
    counts = {}
    for lat, _ in re.findall(r"^@LAT(\d+)LON(\d+)", s, re.M):
        counts[lat] = counts.get(lat, 0) + 1
    bad = []
    parts = re.split(r"^(@LAT(\d+)LON(\d+)[^\n]*)$", s, flags=re.M)
    for i in range(1, len(parts), 4):
        lat = parts[i + 1]
        if lat not in EXPECT:
            continue
        body = parts[i + 3] if i + 3 < len(parts) else ""
        toks = set(re.findall(r"\*\*([A-Z_]+)\*\*", body))
        foreign = toks - set(EXPECT[lat])
        if foreign:
            bad.append("@LAT%sLON%s%s" % (lat, parts[i + 2], sorted(foreign)))
    return len(s), counts, bad


def pull_one(node, port, why):
    import serial
    reader = c.SerialFrameReader()
    out = os.path.join("master", "%s.md" % node)
    with serial.Serial(port, 115200, timeout=0.1) as ser:
        time.sleep(2.5)          # port open resets the S3; let it boot
        ser.reset_input_buffer()
        data = c.request_ttdb(ser, reader, c.NODE_IDS[node])
    if data is None:
        print("  %-12s %-20s FAILED (no data)" % (node, why))
        return False
    os.makedirs("master", exist_ok=True)
    with open(out, "wb") as f:
        f.write(data)
    n, counts, bad = lanes_and_check(out)
    lanes = " ".join("@LAT%s:%d" % (k, v) for k, v in sorted(counts.items()))
    print("  %-12s %-20s %6d B  %s" % (node, why, n, lanes))
    if bad:
        print("     !! %d record(s) carry another lane's body — STITCHED PULL: %s"
              % (len(bad), bad[:3]))
    return not bad


print("collecting fleet TTDBs (own cable where available)\n")
ok = True
for node, (port, why) in ROUTE.items():
    try:
        ok &= pull_one(node, port, "%s %s" % (port, why))
    except Exception as e:                                    # noqa: BLE001
        print("  %-12s %-20s ERROR %s" % (node, why, e))
        ok = False
print("\nall pulls clean" if ok else "\n!! at least one pull is suspect — see above")
