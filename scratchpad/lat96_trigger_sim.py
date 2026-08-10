"""Offline simulation: what would a change-trigger on @LAT96 actually cost?

Part 2 proper is unwritten, and companion.md §6 flagged the decision that must be made
BEFORE code: `@LAT95`'s verdict is a 2-state label, `@LAT96`'s would be a threshold on a
continuous drift, so a `**COVERED**` window is a *judgement* rather than a repeat.

This asks the question the run-length work on `@LAT92` could answer trivially and this
one cannot: **is dropping a covered window LOSSLESS for what reads the lane?**

@LAT96's consumer is `_entity_set` — the UNION of BSSIDs over recent windows, which is
the Jaccard proximity bound between two nodes. So the loss to measure is APs that appear
ONLY in dropped windows.

Run against the validated night-1 baseline (all four gates passed) — no threshold is
derived here; this is a mechanism comparison, not a constant.
"""
import sys, statistics
sys.path.insert(0, "orchestrator")
import companion as C

PATHS = [
    ("night 1 (GATES PASSED)", "master/entity-baseline/cardputer_baseline_2026-08-06.md"),
    ("night 2 (cancelled)",    "master/entity-baseline/cardputer_night2_cancelled.md"),
]


def segment(path):
    text = open(path, encoding="utf-8", errors="replace").read()
    ew = C.parse_entity_percepts(text)
    stream, _, seg = C.longest_stream_segment(ew)
    return stream, seg


def sets_of(seg):
    return [set(e["id"] for e in w["entities"]) for w in seg]


def sim_threshold(sets, thr):
    """Mechanism A: a window is COVERED when its Jaccard distance from the run's
    reference (the last WRITTEN window) is <= thr. Otherwise it opens a new run."""
    written = [0]
    ref = sets[0]
    for i in range(1, len(sets)):
        d = C.jaccard_distance(ref, sets[i])
        if d is None or d <= thr:
            continue
        written.append(i)
        ref = sets[i]
    return written


def sim_core(sets, n, m):
    """Mechanism B: the STABLE CORE — APs seen in >= n of the last m windows. A window
    is covered when the core is unchanged."""
    written = [0]
    core_at = lambda i: {ap for ap in set().union(*sets[max(0, i - m + 1):i + 1])
                         if sum(ap in s for s in sets[max(0, i - m + 1):i + 1]) >= n}
    ref = core_at(0)
    for i in range(1, len(sets)):
        c = core_at(i)
        if c == ref:
            continue
        written.append(i)
        ref = c
    return written


def loss(sets, written):
    """APs the lane would no longer contain at all, and how many windows' worth."""
    full = set().union(*sets) if sets else set()
    kept = set().union(*[sets[i] for i in written]) if written else set()
    return full, kept, full - kept


for label, path in PATHS:
    stream, seg = segment(path)
    sets = sets_of(seg)
    if not sets:
        print(f"{label}: no windows"); continue
    sizes = [len(s) for s in sets]
    full = set().union(*sets)
    print(f"\n=== {label} — stream {stream}, {len(seg)} windows in the segment")
    print(f"    AP set size per window: min {min(sizes)} p50 {statistics.median(sizes):.0f} "
          f"max {max(sizes)};  union over the segment: {len(full)} distinct BSSIDs")

    # ⚠ ALL consecutive pairs, NOT the gate-filtered set (the gates discard pairs
    # outside 600+/-120 s). A trigger runs on every window the node takes, so this is
    # the right population for a mechanism comparison — but it is NOT the baseline,
    # and the recorded baseline numbers stay the authority for any threshold.
    ds = sorted(d for d in (C.jaccard_distance(sets[i], sets[i + 1])
                            for i in range(len(sets) - 1)) if d is not None)
    if ds:
        pct = lambda p: ds[min(len(ds) - 1, int(len(ds) * p))]   # companion.py's rule
        print(f"    drift over ALL consecutive pairs (not gate-filtered): "
              f"p50 {pct(.50):.3f} p90 {pct(.90):.3f} max {ds[-1]:.3f}")

    print("    MECHANISM A — per-window Jaccard trigger")
    print("      thr   records/windows  compression   APs lost   % of union")
    for thr in (0.0, 0.125, 0.25, 0.375, 0.5, 0.625, 0.75):
        w = sim_threshold(sets, thr)
        _, kept, lost = loss(sets, w)
        print(f"      {thr:<5.3f} {len(w):>3}/{len(sets):<3}          "
              f"{len(sets)/len(w):>5.2f}x      {len(lost):>4}      "
              f"{100*len(lost)/max(1,len(full)):>5.1f}%")

    print("    MECHANISM B — stable core (APs in >= n of the last m windows)")
    print("      n/m   records/windows  compression   APs lost   % of union   core size")
    for n, m in ((2, 3), (3, 5), (4, 5), (5, 8), (6, 8)):
        w = sim_core(sets, n, m)
        _, kept, lost = loss(sets, w)
        cores = []
        for i in range(len(sets)):
            lo = max(0, i - m + 1)
            win = sets[lo:i + 1]
            cores.append(len({ap for ap in set().union(*win)
                              if sum(ap in s for s in win) >= n}))
        print(f"      {n}/{m}   {len(w):>3}/{len(sets):<3}          "
              f"{len(sets)/len(w):>5.2f}x      {len(lost):>4}      "
              f"{100*len(lost)/max(1,len(full)):>5.1f}%        "
              f"{min(cores)}-{max(cores)} (p50 {statistics.median(cores):.0f})")
