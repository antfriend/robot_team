#!/usr/bin/env python3
"""motion_noise.py — B.3: derive MOTIONPERCEPT_MOVING_MG from this BMI270's own
noise floor, instead of from published hand-tremor figures.

The method is PerceptLearn.h's, deliberately: it derived PERCEPTLEARN_RSSI_BAND 6
as the p90 of that node's own consecutive-window drift across 33 known-quiet
windows, and wrote the derivation table into the header. A constant that survives
its own measurement is worth more than one that was reasoned about.

⚠ THE SAMPLE MUST BE KNOWN-QUIET, NOT SELF-LABELLED QUIET. `state:still` is
computed with the very threshold under test, so filtering on it is circular. This
script therefore reports on ALL windows in the file and expects the operator to
have kept the node stationary for the whole run — which is why the run is done on
a pruned lane, with nothing touching the port (every companion.py call resets the
board and restarts the 60 s window).

Usage: python scratchpad/motion_noise.py <pulled-ttdb.md> [...]
"""
import re
import sys

MOTION_RE = re.compile(
    r"\*\*MOTION\*\* state:(\w+) moving_permille:(\d+) dev_mean_mg:(\d+) "
    r"dev_max_mg:(\d+) moving_ms:(\d+)")
WIN_RE = re.compile(r"\*\*MOTIONWIN\*\*.*?\bn:(\d+)")


def pct(sorted_vals, q):
    if not sorted_vals:
        return None
    i = int(round(q * (len(sorted_vals) - 1)))
    return sorted_vals[min(i, len(sorted_vals) - 1)]


def analyse(path):
    text = open(path, encoding="utf-8", errors="replace").read()
    rows = MOTION_RE.findall(text)
    samples = [int(m) for m in WIN_RE.findall(text)]
    if not rows:
        print(f"{path}: no @LAT95 motion windows")
        return None
    mx = sorted(int(r[3]) for r in rows)
    mn = sorted(int(r[2]) for r in rows)
    perm = sorted(int(r[1]) for r in rows)
    moving = sum(1 for r in rows if r[0] == "moving")
    print(f"{path}")
    print(f"  windows            : {len(rows)}  ({moving} labelled moving, "
          f"{len(rows) - moving} still)")
    if samples:
        print(f"  samples per window : min {min(samples)}  max {max(samples)}")
    print(f"  dev_max_mg         : min {mx[0]}  p50 {pct(mx, .5)}  "
          f"p75 {pct(mx, .75)}  p90 {pct(mx, .9)}  p95 {pct(mx, .95)}  max {mx[-1]}")
    print(f"  dev_mean_mg        : min {mn[0]}  p50 {pct(mn, .5)}  "
          f"p90 {pct(mn, .9)}  max {mn[-1]}")
    print(f"  moving_permille    : p50 {pct(perm, .5)}  p90 {pct(perm, .9)}  "
          f"max {perm[-1]}")
    if mn[0] == mn[-1]:
        # ASCII only: this console is cp1252 and a non-ASCII char aborts the report.
        print(f"  !! dev_mean_mg is CONSTANT at {mn[0]} across every window - a "
              f"statistic that never varies carries no information. Check whether "
              f"devMeanMg() is quantised or dominated by a fixed bias before "
              f"anything is derived from it.")
    p90 = pct(mx, .9)
    print(f"\n  p90(dev_max_mg) = {p90} mg   -> the noise floor this node actually has")
    # (kept ASCII for the same reason as above)
    print(f"  MOTIONPERCEPT_MOVING_MG is 60 mg   -> {60 / p90:.2f}x the measured p90")
    over = sum(1 for v in mx if v >= 60)
    print(f"  {over}/{len(mx)} quiet windows contain a sample at or above 60 mg "
          f"({100.0 * over / len(mx):.1f}%) - each is a sample the threshold would "
          f"call motion while the node was stationary.")
    return {"n": len(rows), "p90": p90, "max": mx[-1], "over60": over}


if __name__ == "__main__":
    if len(sys.argv) < 2:
        sys.exit(__doc__)
    for p in sys.argv[1:]:
        analyse(p)
        print()
