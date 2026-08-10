"""Pre-registered prediction: what will the stable-core trigger DO on a given node's
own archived @LAT96 windows?

Mirrors EntityPercept::buildRecord exactly — history pushed BEFORE the core is judged,
write on first | core changed | run_len >= MAX_RUN | union would overflow — so the
output is a claim about the next run on that board, stated before the run happens.

  python scratchpad/lat96_predict.py master/ui/v4a_bridge.md

The corpus's practice: state it first, then check the hardware against it. A number
produced after the fact is a description; the same number produced before is a test.
"""
import sys, os
sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "orchestrator"))
import companion as c  # noqa: E402

CORE_N, CORE_M, MAX_RUN, MAX_UNION = 3, 5, 6, 16


def core_of(hist):
    """APs in >= CORE_N of the last CORE_M windows."""
    win = hist[-CORE_M:]
    return {ap for ap in set().union(*win) if sum(ap in s for s in win) >= CORE_N} if win else set()


def simulate(sets):
    hist, records, folds = [], [], 0
    run_open = False
    run_core, run_len, cov = set(), 0, {}
    covered_only = []          # APs that would exist ONLY in a folded window
    for i, s in enumerate(sets):
        hist.append(s)
        cur = core_of(hist)
        changed = run_open and cur != run_core
        heartbeat = run_open and not changed and run_len >= MAX_RUN
        union_full = (run_open and not changed and not heartbeat
                      and len(set(cov) | s) > MAX_UNION)
        write = (not run_open) or changed or heartbeat or union_full
        if write:
            reason = ("first" if not run_open else
                      "changed" if changed else
                      "heartbeat" if heartbeat else "union_full")
            # An AP in the covered union that this closing record does NOT itemise is
            # exactly what **COVERED-ENTITY** exists to preserve.
            only = set(cov) - s
            if only:
                covered_only.append((i, sorted(only)))
            records.append((i, reason, len(cur), len(cov)))
            run_open, run_core, run_len, cov = True, cur, 1, {}
        else:
            folds += 1
            run_len += 1
            for ap in s:
                cov[ap] = cov.get(ap, 0) + 1
    return records, folds, covered_only


def main(path):
    text = open(path, encoding="utf-8", errors="replace").read()
    wins = c.parse_entity_percepts(text)
    sets = [set(e["id"] for e in w["entities"]) for w in wins]
    if c.entity_lane_is_folded(wins):
        sys.exit("REFUSING: %s is already folded — its per-window sets are gone, so it "
                 "cannot be used to predict a fold." % path)

    records, folds, covered_only = simulate(sets)
    print("%s\n  %d archived windows, union %d BSSIDs"
          % (path, len(sets), len(set().union(*sets))))
    print("\nPREDICTION for the next run on this board, at core %d-of-%d, max_run %d:"
          % (CORE_N, CORE_M, MAX_RUN))
    print("  records written : %d  (compression %.2fx)" % (len(records), len(sets) / max(1, len(records))))
    print("  windows folded  : %d" % folds)
    reasons = {}
    for _, r, _, _ in records:
        reasons[r] = reasons.get(r, 0) + 1
    print("  reasons         : %s" % ", ".join("%s=%d" % kv for kv in sorted(reasons.items())))
    print("  first 8 records : %s" % ", ".join(
        "w%d/%s(core %d,cov %d)" % (i, r, k, v) for i, r, k, v in records[:8]))
    print("\n  THE UNION PROPERTY — APs that would exist ONLY in a folded window,")
    print("  i.e. records where **COVERED-ENTITY** is the only thing preventing a loss:")
    if covered_only:
        for i, aps in covered_only:
            print("    at window %d: %s" % (i, ", ".join(aps)))
        print("  -> %d of %d written records carry an AP nothing else would keep."
              % (len(covered_only), len(records)))
    else:
        print("    NONE. On this board's archived data the fold would cost nothing even")
        print("    WITHOUT the covered union — so a clean run here does not test the")
        print("    property, it only fails to contradict it. Say so rather than claiming")
        print("    a pass.")


if __name__ == "__main__":
    # Guarded so the simulate() above can be IMPORTED and validated against real
    # device output without this report firing as a side effect -- which is exactly
    # what happened the first time it was cross-checked against the T-Deck.
    main(sys.argv[1] if len(sys.argv) > 1 else "master/ui/v4a_bridge.md")
