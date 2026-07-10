#!/usr/bin/env python3
"""test_anchor_py.py — verify companion.py's SP2 GPS anchoring without hardware
(semantic positioning, ttn-semantic-positioning.md §3 Phase 2): the GPS PERCEPT
codec, the closed-form 2D Procrustes fit (scale/rotation/translation, reflection
detection), and the end-to-end `anchor` that ties the relative @BELIEF:POSITION map
to absolute lat/lon and resolves the mirror with >=3 ties.

Run: python tests/test_anchor_py.py
"""
import math
import os
import struct
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


# ---------------------------------------------------------------------------
# 1) GPS PERCEPT codec round-trip (incl. negative lat/lon = S/W hemisphere).
def gps_payload(lat, lon, alt_m, quality, sats, hdop, epoch_ms):
    return (struct.pack("<iii", round(lat * 1e7), round(lon * 1e7), round(alt_m * 100))
            + bytes([quality, sats]) + struct.pack("<H", round(hdop * 10))
            + struct.pack("<Q", epoch_ms))


pl = gps_payload(-33.7613000, -150.2057500, 12.3, 2, 11, 1.2, 1780000000000)
check(len(pl) == c.GPS_PERCEPT_PAYLOAD_LEN, "GPS payload is 24 bytes")
g = c.parse_gps(pl)
check(g is not None and abs(g["lat_deg"] + 33.7613) < 1e-6, "parse_gps latitude (S neg)")
check(g is not None and abs(g["lon_deg"] + 150.20575) < 1e-6, "parse_gps longitude (W neg)")
check(g["quality"] == 2 and g["sats"] == 11 and abs(g["hdop"] - 1.2) < 1e-6,
      "parse_gps quality/sats/hdop")
check(g["epoch_ms"] == 1780000000000, "parse_gps epoch")
check(c.parse_gps(pl[:15]) is None, "parse_gps rejects a STATUS-length payload")

# ---------------------------------------------------------------------------
# 2) Procrustes recovers a known rotation+scale (no reflection).
src = [(0.0, 0.0), (1.0, 0.0), (1.0, 1.0), (0.0, 1.0)]
th, s, tx, ty = math.radians(40), 2.0, 3.0, -1.0
ct, sn = math.cos(th), math.sin(th)
dst = [(s * (ct * x - sn * y) + tx, s * (sn * x + ct * y) + ty) for x, y in src]
fit = c.procrustes_2d(src, dst)
check(not fit["reflect"], "proper transform -> reflect False")
check(abs(math.degrees(fit["theta"]) - 40) < 1e-3, "recovered rotation ~40 deg")
check(abs(fit["scale"] - 2.0) < 1e-6, "recovered scale ~2.0")
check(fit["rmse"] < 1e-6, "consistent similarity -> ~0 rmse")

# 3) Procrustes detects a reflection.
dstr = [(s * (ct * x - sn * (-y)) + tx, s * (sn * x + ct * (-y)) + ty) for x, y in src]
fitr = c.procrustes_2d(src, dstr)
check(fitr["reflect"], "reflected transform -> reflect True")
check(fitr["rmse"] < 1e-6, "reflected fit is also exact")

# ---------------------------------------------------------------------------
# 4) End-to-end anchor(): relative square -> geo, 3 ties, flip resolved.
NODES = ["v4a_bridge", "v4b_relay", "k10_1", "tdeck_1"]
rel = {"v4a_bridge": (0.0, 0.0), "v4b_relay": (4.0, 0.0),
       "k10_1": (4.0, 3.0), "tdeck_1": (0.0, 3.0)}

# A synthetic true geo placement: rotate+translate the relative frame (scale 1) about a
# reference, project to lat/lon. anchor() must invert this from the tie subset.
LAT0, LON0 = 47.6205000, -122.3492000
mlon = c.M_PER_DEG_LAT * math.cos(math.radians(LAT0))
gth = math.radians(25)
gc, gs = math.cos(gth), math.sin(gth)


def rel_to_geo(x, y):
    e = gc * x - gs * y + 10.0     # ENU east/north with a translation
    n = gs * x + gc * y - 5.0
    return (LAT0 + n / c.M_PER_DEG_LAT, LON0 + e / mlon)


geo_true = {nd: rel_to_geo(*rel[nd]) for nd in NODES}


def write_positions(path, pos):
    with open(path, "w", encoding="utf-8", newline="\n") as f:
        f.write(c.POSITIONS_HEADER)
        for nd, (x, y) in sorted(pos.items()):
            f.write(f"\n---\n\n@BELIEF:POSITION @node({nd})\n"
                    f"frame: relative\nx_m: {x:.2f}\ny_m: {y:.2f}\n"
                    f"sigma_m: 0.40\nanchor_chain: [v4a_bridge]\n"
                    f"embedding_rev: 1\nflip_resolved: false\nstress_m: 0.01\n"
                    f"conf: 0.7\ntouched: 2026-07-10T00:00:00Z\n")


def write_fixes(path, ties):
    with open(path, "w", encoding="utf-8", newline="\n") as f:
        f.write("# fixes\n")
        for nd in ties:
            lat, lon = geo_true[nd]
            f.write(f"\n---\n\n@PERCEPT:GPS @at({nd})\n"
                    f"lat_deg: {lat:.7f}\nlon_deg: {lon:.7f}\nalt_m: 10.0\n"
                    f"quality: 1\nsats: 9\nhdop: 1.0\nsource_node: tdeck_1\n"
                    f"node_epoch_ms: 0\ntouched: 2026-07-10T00:00:00Z\n")


def parse_anchored(path):
    import re
    with open(path, encoding="utf-8") as f:
        text = f.read()
    out = {}
    for chunk in text.split("@BELIEF:POSITION")[1:]:
        m = re.match(r"\s*@node\((\w+)\)", chunk)
        la = re.search(r"lat_deg:\s*(-?[\d.]+)", chunk)
        lo = re.search(r"lon_deg:\s*(-?[\d.]+)", chunk)
        fr = re.search(r"flip_resolved:\s*(\w+)", chunk)
        if m and la and lo:
            out[m.group(1)] = (float(la.group(1)), float(lo.group(1)),
                               fr.group(1) if fr else "?")
    return out


def geo_dist_m(a, b):
    dlat = (a[0] - b[0]) * c.M_PER_DEG_LAT
    dlon = (a[1] - b[1]) * c.M_PER_DEG_LAT * math.cos(math.radians(a[0]))
    return math.hypot(dlat, dlon)


d = tempfile.mkdtemp()
pos_path = os.path.join(d, "positions.md")
fix_path = os.path.join(d, "gps-fixes.md")
anc_path = os.path.join(d, "anchored.md")
write_positions(pos_path, rel)
write_fixes(fix_path, ["v4a_bridge", "v4b_relay", "k10_1"])   # 3 ties
c.anchor(pos_path, fix_path, anc_path)
res = parse_anchored(anc_path)

check(len(res) == 4, "anchored map has all 4 nodes")
worst = max(geo_dist_m(res[nd][:2], geo_true[nd]) for nd in NODES)
check(worst < 0.10, f"3-tie anchor recovers absolute geo within {worst*100:.1f} cm")
check(all(res[nd][2] == "true" for nd in NODES), "3 ties -> flip_resolved true")
# The non-tie node (tdeck_1) is recovered purely from the fit — the real test.
check(geo_dist_m(res["tdeck_1"][:2], geo_true["tdeck_1"]) < 0.10,
      "non-tie node placed correctly from the fit alone")

# 5) parse round-trips against the writers.
back_pos, back_sig = c.parse_positions_file(pos_path)
check(back_pos["v4b_relay"] == (4.0, 0.0) and abs(back_sig["v4b_relay"] - 0.40) < 1e-9,
      "parse_positions_file round-trip")
back_fix = c.parse_gps_fixes(fix_path)
check(len(back_fix) == 3 and geo_dist_m(back_fix["k10_1"], geo_true["k10_1"]) < 1e-3,
      "parse_gps_fixes round-trip (quality>0)")

# 6) Two ties -> flip stays unresolved (honest: a segment maps two ways).
write_fixes(fix_path, ["v4a_bridge", "v4b_relay"])   # 2 ties
c.anchor(pos_path, fix_path, anc_path)
res2 = parse_anchored(anc_path)
check(all(res2[nd][2] == "false" for nd in NODES),
      "2 ties -> flip_resolved false (mirror ambiguous)")

print()
if fails:
    sys.exit(f"{fails} FAILURE(S)")
print("all anchor tests passed")
