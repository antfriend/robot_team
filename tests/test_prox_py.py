#!/usr/bin/env python3
"""test_prox_py.py — verify companion.py's SP1 proximity consolidation without
hardware (semantic positioning, ttn-semantic-positioning.md §2.1/§3 Phase 1):
@LAT97 link-percept parsing, directed-link fusion into pair beliefs, the
orchestrator pseudo-peer filter, and path-loss monotonicity.

The firmware half (LinkPercept @LAT97 records) is gated on-device by
`companion.py percepts` (verified 2026-07-07).

Run: python tests/test_prox_py.py
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


# ---------------------------------------------------------------------------
# 1) parse_link_percepts: lanes, LINKWIN context, LINK lines.
TEXT_A = """
@LAT0LON0 | created:1 | updated:1 | relates:

**HELLO** something else

---

@LAT97LON0 | created:10 | updated:10 | relates:observes@LAT0LON0

**LINKWIN** t_ms:60000 synced:0 window_ms:60000
**LINK** peer:0x00000011 proto:espnow n:20 rssi_min:-50 rssi_med:-40 rssi_max:-35
**LINK** peer:0x00000001 proto:espnow n:2 rssi_min:-40 rssi_med:-38 rssi_max:-36

---

@LAT97LON1 | created:20 | updated:20 | relates:observes@LAT0LON0

**LINKWIN** t_ms:120000 synced:1 window_ms:60000
**LINK** peer:0x00000011 proto:espnow n:30 rssi_min:-52 rssi_med:-41 rssi_max:-37
"""
wins = c.parse_link_percepts(TEXT_A)
check(len(wins) == 2, "two @LAT97 windows parsed")
check(wins[0]["lane"] == 0 and wins[1]["lane"] == 1, "lane indices")
check(wins[0]["t_ms"] == 60000 and wins[0]["synced"] == 0, "LINKWIN context")
check(wins[1]["synced"] == 1, "synced flag parsed per window")
check(len(wins[0]["links"]) == 2 and len(wins[1]["links"]) == 1,
      "LINK lines per window")
check(wins[0]["links"][0] == {"peer": 0x11, "proto": "espnow", "n": 20,
                              "min": -50, "med": -40, "max": -35},
      "LINK fields")

# ---------------------------------------------------------------------------
# 2) consolidate_proximity: two directions fuse into one pair belief;
#    the orchestrator pseudo-peer (0x1) is excluded.
TEXT_B = """
@LAT97LON0 | created:10 | updated:10 | relates:observes@LAT0LON0

**LINKWIN** t_ms:60000 synced:0 window_ms:60000
**LINK** peer:0x00000010 proto:espnow n:25 rssi_min:-48 rssi_med:-38 rssi_max:-33
"""
beliefs = c.consolidate_proximity({
    "v4a_bridge": c.parse_link_percepts(TEXT_A),   # A hears B: maxes -35, -37
    "v4b_relay": c.parse_link_percepts(TEXT_B),    # B hears A: max -33
})
check(len(beliefs) == 1, "orchestrator pseudo-peer excluded; one pair belief")
b = beliefs[0]
check(b["a"] == "v4a_bridge" and b["b"] == "v4b_relay", "pair names by id order")
check(b["rssi_ab"] == -36.0, "A->B estimate = median of window maxes (-35,-37)")
check(b["rssi_ba"] == -33.0, "B->A estimate")
check(b["rssi_est"] == -34.5, "pair estimate = mean of directions")
check(b["asym_db"] == 3.0, "direction asymmetry")
check(b["n_obs"] == 20 + 30 + 25, "n_obs sums both directions (minus 0x1)")
check(b["windows"] == 3, "window count")
check(b["dist_est_m"] is not None and b["dist_sigma_m"] > 0,
      "distance + honest sigma emitted")
check(0.1 <= b["conf"] <= 0.7, "conf bounded while uncalibrated")

# ---------------------------------------------------------------------------
# 3) one-directional pair (e.g. K10 observed but not observing) still yields
#    a belief, from the single direction.
beliefs1 = c.consolidate_proximity({"v4a_bridge": c.parse_link_percepts(TEXT_A)})
check(len(beliefs1) == 1 and beliefs1[0]["n_ba"] == 0,
      "one-directional link still produces a belief")
check(beliefs1[0]["asym_db"] == 0.0, "no asymmetry with one direction")

# ---------------------------------------------------------------------------
# 4) path-loss monotonicity: weaker RSSI -> larger distance.
d_strong = c.rssi_to_dist_m(-35, "espnow")
d_weak = c.rssi_to_dist_m(-75, "espnow")
check(d_strong < d_weak, "weaker RSSI maps to larger distance")
check(abs(c.rssi_to_dist_m(-45, "espnow") - 1.0) < 1e-9,
      "model anchored at rssi_d0/d0_m")
check(c.rssi_to_dist_m(-50, "ble") is None, "unknown proto -> no distance")

# ---------------------------------------------------------------------------
# 5) fit_pathloss recovers a known model exactly (points generated from
#    RSSI(d) = -40 - 30*log10(d), i.e. rssi_d0 = -40, n = 3).
a, n, rmse = c.fit_pathloss([(1.0, -40.0), (10.0, -70.0), (100.0, -100.0)])
check(abs(a + 40.0) < 1e-9 and abs(n - 3.0) < 1e-9 and rmse < 1e-9,
      "fit recovers exact synthetic model (rssi_d0 -40, n 3, rmse 0)")

# 6) calibrate -> load_calibration round trip; calibrated model drives
#    rssi_to_dist_m and consolidate_proximity.
import tempfile
cal_path = os.path.join(tempfile.mkdtemp(), "calibration.md")
c.calibrate("espnow", ["1:-40", "10:-70", "100:-100"], cal_path, "unit test")
calib = c.load_calibration(cal_path)
check("espnow" in calib, "calibration file round-trips through the parser")
check(abs(calib["espnow"]["n"] - 3.0) < 0.01, "fitted n survives the file")
check(abs(c.rssi_to_dist_m(-70.0, "espnow", calib) - 10.0) < 0.1,
      "calibrated model overrides the default in rssi_to_dist_m")
b_cal = c.consolidate_proximity({"v4a_bridge": c.parse_link_percepts(TEXT_A)},
                                calib)[0]
check(b_cal["calibrated"], "belief marked calibrated")
b_uncal = c.consolidate_proximity({"v4a_bridge": c.parse_link_percepts(TEXT_A)})[0]
check(b_uncal["dist_sigma_m"] > 0 and not b_uncal["calibrated"],
      "no calibration -> uncalibrated belief with widened sigma")
check(c.load_calibration("no/such/file.md") == {},
      "missing calibration file -> empty (defaults apply)")

# 7) recency filter: last=1 uses only the newest window per node.
b_last = c.consolidate_proximity({"v4a_bridge": c.parse_link_percepts(TEXT_A)},
                                 last=1)[0]
check(b_last["n_ab"] == 30 and b_last["windows"] == 1,
      "last=1 keeps only the newest window (n from lane 1 only)")
check(b_last["rssi_ab"] == -37.0, "estimate from the newest window's max")

print()
if fails:
    sys.exit(f"{fails} FAILURE(S)")
print("all proximity tests passed")
