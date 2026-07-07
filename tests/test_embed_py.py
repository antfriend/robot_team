#!/usr/bin/env python3
"""test_embed_py.py — verify companion.py's SP2 position embedding without
hardware (semantic positioning, ttn-semantic-positioning.md §3 Phase 2):
spring relaxation recovers known geometry (up to the documented rotation/
mirror freedom), the canonical relative frame, honest stress on inconsistent
input, and the @BELIEF:PROXIMITY file parser round-trip.

Run: python tests/test_embed_py.py
"""
import math
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


def mkpair(a, b, dist, sigma=0.2, conf=0.7):
    return {"a": a, "b": b, "proto": "espnow", "dist": dist, "sigma": sigma,
            "n": 100, "conf": conf}


# ---------------------------------------------------------------------------
# 1) Exact square: v4a(0,0) v4b(3,0) tdeck(3,3) k10(0,3). All 6 distances.
S = 3.0
D = S * math.sqrt(2)
square = [
    mkpair("v4a_bridge", "v4b_relay", S),
    mkpair("v4a_bridge", "tdeck_1", D),
    mkpair("v4a_bridge", "k10_1", S),
    mkpair("v4b_relay", "tdeck_1", S),
    mkpair("v4b_relay", "k10_1", D),
    mkpair("k10_1", "tdeck_1", S),
]
pos, residuals, stress = c.embed_positions(square)
check(stress < 0.05, f"square: stress ~0 on consistent input (got {stress:.3f})")
worst = max(abs(got - want) for _, _, want, got in residuals)
check(worst < 0.1, f"square: all pairwise distances recovered (worst {worst:.3f})")

# Canonical frame: anchor at origin, 2nd node on +x, some node at +y.
ax, ay = pos["v4a_bridge"]
check(abs(ax) < 1e-6 and abs(ay) < 1e-6, "anchor v4a_bridge at the origin")
ref = pos["k10_1"]  # first non-anchor in sorted order
check(abs(ref[1]) < 0.05 and ref[0] > 0, "2nd node canonicalized onto +x")
check(all(p[1] > -0.05 for p in pos.values()) and
      any(p[1] > 1.0 for p in pos.values()),
      "mirror canonicalized into the +y half-plane")

# 2) Inconsistent input (triangle-inequality violation) -> honest stress > 0.
bad = [
    mkpair("v4a_bridge", "v4b_relay", 0.4),
    mkpair("v4b_relay", "tdeck_1", 0.3),
    mkpair("v4a_bridge", "tdeck_1", 1.2),  # 0.4 + 0.3 < 1.2
]
_, _, bad_stress = c.embed_positions(bad)
check(bad_stress > 0.05, f"inconsistent distances -> stress > 0 ({bad_stress:.3f})")

# 3) Weights matter: a huge-sigma wrong edge must not wreck a consistent map.
weighted = list(square)
weighted.append(mkpair("v4a_bridge", "tdeck_1", 20.0, sigma=50.0, conf=0.1))
pos_w, res_w, stress_w = c.embed_positions(weighted)
got_diag = next(g for a, b, _, g in res_w
                if (a, b) == ("v4a_bridge", "tdeck_1"))
check(abs(got_diag - D) < 0.5,
      f"low-weight outlier edge barely moves the map (diag {got_diag:.2f})")

# 4) parse_proximity_file round-trip against the writer's exact format.
import tempfile
tmp = os.path.join(tempfile.mkdtemp(), "proximity.md")
with open(tmp, "w", encoding="utf-8") as f:
    f.write(c.PROXIMITY_HEADER)
    f.write("\n---\n\n@BELIEF:PROXIMITY @pair(v4a_bridge, v4b_relay)\n"
            "proto: espnow\nrssi_est_dbm: -35.5\n"
            "rssi_ab_dbm: -33.0   # v4a_bridge hears v4b_relay (n:60)\n"
            "rssi_ba_dbm: -38.0   # v4b_relay hears v4a_bridge (n:64)\n"
            "asym_db: 5.0\ndist_est_m: 4.01\ndist_sigma_m: 0.67\n"
            "n_obs: 124\nwindows: 6\nsources: { rssi: 1.0 }\n"
            "calibrated: yes   # master/calibration.md\n"
            "conf: 0.52\ntouched: 2026-07-07T22:00:00Z\n")
parsed = c.parse_proximity_file(tmp)
check(len(parsed) == 1, "parser finds the record")
p = parsed[0]
check(p["a"] == "v4a_bridge" and p["b"] == "v4b_relay" and
      p["dist"] == 4.01 and p["sigma"] == 0.67 and p["n"] == 124 and
      p["conf"] == 0.52 and p["proto"] == "espnow",
      "parser fields match the writer")

# 5) Determinism: same input -> same embedding (fixed seed).
pos2, _, _ = c.embed_positions(square)
same = all(abs(pos[nd][0] - pos2[nd][0]) < 1e-9 and
           abs(pos[nd][1] - pos2[nd][1]) < 1e-9 for nd in pos)
check(same, "embedding is deterministic")

print()
if fails:
    sys.exit(f"{fails} FAILURE(S)")
print("all embed tests passed")
