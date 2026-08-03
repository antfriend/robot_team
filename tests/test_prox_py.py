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
# 1b) THE TEAM TIME STREAM MIGRATION (2026-08-03). `synced:<0|1>` became
# `stream:0x<id> wall:<0|1>`, and BOTH are live in the corpus: a node's TTDB is
# appended to for its whole life, so records written before the change sit on the
# same flash as the ones written after. A reader that handles only one format
# silently drops half the lane — the exact silent-subset failure the fleet keeps
# finding — so this asserts the old records still parse, byte for byte.
TEXT_STREAM = """
@LAT97LON0 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:60000 stream:0x00000000 wall:0 window_ms:60000
**LINK** peer:0x00000011 proto:espnow n:20 rssi_min:-50 rssi_med:-40 rssi_max:-35

---

@LAT97LON1 | created:1785542400 | updated:1785542400 | relates:observes@LAT0LON0

**LINKWIN** t_ms:120000 stream:0x5ea51de7 wall:1 window_ms:60000
**LINK** peer:0x00000011 proto:espnow n:30 rssi_min:-52 rssi_med:-41 rssi_max:-37
"""
sw = c.parse_link_percepts(TEXT_STREAM)
check(len(sw) == 2, "new-format windows parse")
check(sw[0]["t_ms"] == 60000 and sw[0]["window_ms"] == 60000,
      "t_ms and window_ms survive the field that moved between them")
check(sw[0]["stream"] == 0 and sw[0]["wall"] == 0 and sw[0]["synced"] == 0,
      "stream:0 -> no shared clock (what synced:0 always meant)")
check(sw[1]["stream"] == 0x5ea51de7 and sw[1]["wall"] == 1 and sw[1]["synced"] == 1,
      "a real stream id is parsed, and synced stays derivable for old callers")
check(len(sw[1]["links"]) == 1, "LINK lines still parse alongside")
# The old format must keep its meaning, and must not INVENT a stream id it does
# not have: synced:1 said "some clock", never which one — that is precisely the
# limitation the change exists to fix, so it reads back as unknown, not as a value.
check(wins[1]["synced"] == 1 and wins[1]["stream"] is None,
      "an old synced:1 record is 'some clock, unnameable' — not a fabricated id")
check(wins[0]["stream"] == 0, "and an old synced:0 record is stream 0")
check(c.fmt_stream(sw[1]) == "5ea51de7*" and c.fmt_stream(sw[0]) == "-"
      and c.fmt_stream(wins[1]) == "?",
      "fmt_stream distinguishes anchored / none / unknowable")

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
# BLE is a known proto since the SP0 near-range tier (2026-07-10) added its
# path-loss default, so it estimates a distance (anchored at its own rssi_d0).
check(abs(c.rssi_to_dist_m(-59, "ble") - 1.0) < 1e-9,
      "ble known proto -> distance at its rssi_d0 (BLE near-range tier)")
check(c.rssi_to_dist_m(-50, "lora") is None, "unknown proto -> no distance")

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

# ---------------------------------------------------------------------------
# 8) SP1 entity cap: shared WiFi APs bound a pair's distance from above.
def lw(peer, rssi, n=30):
    return {"lane": 0, "t_ms": 1, "synced": 1, "window_ms": 60000,
            "links": [{"peer": peer, "proto": "espnow", "n": n,
                       "min": rssi, "med": rssi, "max": rssi}]}

# A weak-signal pair: uncalibrated RSSI over-ranges v4a<->v4b to tens of metres.
far = {"v4a_bridge": [lw(0x11, -85)], "v4b_relay": [lw(0x10, -85)]}
pair = frozenset(("v4a_bridge", "v4b_relay"))

b_nocap = c.consolidate_proximity(far)[0]
check(b_nocap["dist_est_m"] > 20, "weak RSSI over-ranges the pair (>20 m, uncapped)")
check(b_nocap["sources"] == {"rssi": 1.0}, "no entity evidence -> sources rssi only")
check(b_nocap["entity_capped"] is False, "no entity bound -> not capped")

# Now the same pair shares WiFi APs -> a 20 m bound clamps the over-range.
ebounds = {pair: {"pair": ("v4a_bridge", "v4b_relay"), "jaccard": 0.8,
                  "bound_m": 20.0, "shared": 4, "union": 5}}
b_cap = c.consolidate_proximity(far, entity_bounds=ebounds)[0]
check(b_cap["entity_capped"] is True, "over-range beyond the AP bound -> CAPPED")
check(abs(b_cap["dist_est_m"] - 20.0) < 1e-9, "dist clamped to the entity bound")
check(b_cap["entity_jaccard"] == 0.8 and b_cap["entity_shared"] == 4,
      "entity metadata recorded on the belief")
check("entity_jaccard" in b_cap["sources"] and b_cap["sources"]["rssi"] < 1.0,
      "sources mix includes entity_jaccard weight")

# A near pair (strong RSSI, dist << bound): entity contributes weight but does NOT
# refine below the RSSI estimate (the cap only bounds from above).
near = {"v4a_bridge": c.parse_link_percepts(TEXT_A)}  # strong -35 dBm -> small dist
b_near = c.consolidate_proximity(near, entity_bounds=ebounds)[0]
check(b_near["entity_capped"] is False, "short-range pair is not capped (RSSI already < bound)")
check(b_near["dist_est_m"] == c.consolidate_proximity(near)[0]["dist_est_m"],
      "uncapped distance is unchanged by the entity term (no refine below)")
check("entity_jaccard" in b_near["sources"], "entity still contributes to sources mix when present")

# ---------------------------------------------------------------------------
# 9) SP1 BLE second bound: a pair's proto:ble estimate caps its espnow distance.
def link(peer, rssi, proto):
    return {"peer": peer, "proto": proto, "n": 30, "min": rssi, "med": rssi, "max": rssi}

# Same pair heard over BOTH espnow (weak -88 -> far) and ble (-70 -> near ~3.5 m).
far_ble = {
    "v4a_bridge": [{"lane": 0, "t_ms": 1, "synced": 1, "window_ms": 60000,
                    "links": [link(0x11, -88, "espnow"), link(0x11, -70, "ble")]}],
    "v4b_relay": [{"lane": 0, "t_ms": 1, "synced": 1, "window_ms": 60000,
                   "links": [link(0x10, -88, "espnow"), link(0x10, -70, "ble")]}],
}
bel = c.consolidate_proximity(far_ble)
byproto = {b["proto"]: b for b in bel}
check("espnow" in byproto and "ble" in byproto, "both proto beliefs produced for the pair")
esp_far = byproto["espnow"]["dist_est_m"]
ble_est = byproto["ble"]["dist_est_m"]
check(esp_far > ble_est, "espnow over-ranges far while BLE ranges near (pre-bound)")

c.apply_ble_bound(bel)
esp = {b["proto"]: b for b in bel}["espnow"]
ble = {b["proto"]: b for b in bel}["ble"]
check(esp["ble_capped"] is True, "espnow over-range beyond the BLE bound -> CAPPED")
check(esp["ble_bound_m"] is not None and esp["dist_est_m"] <= esp["ble_bound_m"] + 1e-9,
      "espnow distance clamped to the BLE bound (dist + k*sigma)")
check("ble" in esp["sources"], "sources mix gains a ble term")
check(ble["ble_capped"] is False and ble["ble_bound_m"] is None,
      "the BLE belief itself is not bounded by its own estimate")

# BLE present but espnow already within the BLE bound -> not capped, ble still in mix.
near_ble = {
    "v4a_bridge": [{"lane": 0, "t_ms": 1, "synced": 1, "window_ms": 60000,
                    "links": [link(0x11, -40, "espnow"), link(0x11, -55, "ble")]}],
    "v4b_relay": [{"lane": 0, "t_ms": 1, "synced": 1, "window_ms": 60000,
                   "links": [link(0x10, -40, "espnow"), link(0x10, -55, "ble")]}],
}
beln = c.apply_ble_bound(c.consolidate_proximity(near_ble))
espn = {b["proto"]: b for b in beln}["espnow"]
check(espn["ble_capped"] is False, "short-range espnow within BLE bound -> not capped")
check("ble" in espn["sources"], "ble still contributes to sources when present but not capping")

# No BLE evidence -> untouched.
belx = c.apply_ble_bound(c.consolidate_proximity({"v4a_bridge": [lw(0x11, -88)],
                                                  "v4b_relay": [lw(0x10, -88)]}))
check(belx[0]["ble_capped"] is False and belx[0]["ble_bound_m"] is None,
      "no proto:ble for the pair -> no BLE bound applied")
check("ble" not in belx[0]["sources"], "no ble term in sources without BLE evidence")

# ---------------------------------------------------------------------------
# 10) SP1 BLE saturation/consistency guard (2026-07-13 garden failure). A
# near-field-SATURATED BLE read ("BLE-strong") on a path a co-measured espnow tier
# says is FAR ("espnow-weak") must NOT clamp the pair below what espnow measures.
#
# Failure case: espnow bidirectional & weak (-90 -> far ~big); BLE saturated
# strong (-40 -> ~0.6 m, sub-1.5 m floor). The reflection spike would clamp a far
# pair to sub-meter; the guard must suppress it and keep the espnow measurement.
refl_ble = {
    "v4a_bridge": [{"lane": 0, "t_ms": 1, "synced": 1, "window_ms": 60000,
                    "links": [link(0x11, -90, "espnow"), link(0x11, -40, "ble")]}],
    "v4b_relay": [{"lane": 0, "t_ms": 1, "synced": 1, "window_ms": 60000,
                   "links": [link(0x10, -90, "espnow"), link(0x10, -40, "ble")]}],
}
belr = c.consolidate_proximity(refl_ble)
bpr = {b["proto"]: b for b in belr}
esp_far_r = bpr["espnow"]["dist_est_m"]
check(bpr["ble"]["dist_est_m"] < c.BLE_SATURATION_DIST_M,
      "strong BLE read ranges inside the near-field saturation floor")
check(esp_far_r > bpr["ble"]["dist_est_m"] * c.BLE_CONSISTENCY_RATIO,
      "co-measured espnow says the pair is far (BLE-strong-but-espnow-weak)")
c.apply_ble_bound(belr)
espr = {b["proto"]: b for b in belr}["espnow"]
bler = {b["proto"]: b for b in belr}["ble"]
check(bler["ble_saturated"] is True and bler["ble_reflection_suspect"] is True,
      "saturated BLE conflicting with a far espnow -> reflection_suspect")
check(espr["ble_capped"] is False and espr["ble_bound_m"] is None,
      "reflection-suspect BLE does NOT cap the co-measured espnow distance")
check(abs(espr["dist_est_m"] - esp_far_r) < 1e-9,
      "espnow keeps its own (far) measurement — not clamped below the tier")
check(espr["ble_reflection_suspect"] is True,
      "the suspect flag propagates onto the espnow belief for transparency")
check("ble" not in espr["sources"],
      "a suppressed BLE bound does not add a ble term to the sources mix")

# Plausible mid-range BLE (NOT saturated) still legitimately caps an over-ranging
# espnow — the one BLE win must survive the guard (v4a<->tdeck: BLE ~5 m, espnow far).
good_ble = {
    "v4a_bridge": [{"lane": 0, "t_ms": 1, "synced": 1, "window_ms": 60000,
                    "links": [link(0x11, -95, "espnow"), link(0x11, -72, "ble")]}],
    "v4b_relay": [{"lane": 0, "t_ms": 1, "synced": 1, "window_ms": 60000,
                   "links": [link(0x10, -95, "espnow"), link(0x10, -72, "ble")]}],
}
belg = c.apply_ble_bound(c.consolidate_proximity(good_ble))
bg = {b["proto"]: b for b in belg}
check(bg["ble"]["dist_est_m"] >= c.BLE_SATURATION_DIST_M,
      "a plausible mid-range BLE estimate is above the saturation floor")
check(bg["ble"]["ble_reflection_suspect"] is False,
      "plausible-range BLE is NOT flagged suspect despite a far espnow")
check(bg["espnow"]["ble_capped"] is True,
      "plausible BLE still caps the over-ranging espnow (the BLE win survives)")

# Genuine near pair: BLE saturated (0.6 m) but espnow AGREES it's close (the bench
# case) -> NO far-conflict, NOT suspect, the bound still applies (regression on near_ble).
belok = c.apply_ble_bound(c.consolidate_proximity(near_ble))
bok = {b["proto"]: b for b in belok}["ble"]
check(bok["ble_saturated"] is True, "sub-1.5 m BLE estimate flagged saturated")
check(bok["ble_reflection_suspect"] is False,
      "saturated BLE with an AGREEING close espnow is NOT flagged (no conflict)")

print()
if fails:
    sys.exit(f"{fails} FAILURE(S)")
print("all proximity tests passed")
