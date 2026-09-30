"""Run BOTH consolidators over the fleet's own outcome lane and report the difference.

ACT-III §C3 asks for a measurement, not a preference: *does an asymmetric in-place fold beat
counting, on this fleet's real episodes?* This is the laptop half of that question, over the
24-record `@LAT92` lane banked from the Cardputer on 2026-09-30 before its Phase A flash.

    python scratchpad/consolidator_compare.py [store.md]

WHAT IT HAS TO GET RIGHT, AND HOW IT PROVES IT DID
--------------------------------------------------
A `@LAT92` record is one OUTCOME, and its `**OBSERVED**` lines are that window's percepts.
But a `**COVERED** ... windows:N` line is N WINDOWS folded into one line by run-length
(CLAUDE.md: "folding a verdict N times equals folding it once per window"), so a converter
that treats a covered line as ONE observation silently discards N-1 of them -- and it
discards them in the flattering direction, because the windows run-length drops are the ones
where nothing changed. So covered lines are expanded back to N windows here.

The check that the expansion is right is not an assertion in this file: the summed windows
must reproduce the `**TALLY** met:/violated:` numbers that the node itself wrote into its
@LAT91 beliefs. If they match, the conversion is faithful to what the node counted; if they
do not, this script is wrong and says so rather than reporting a comparison built on sand.

WHY THE TWO NUMBERS DIVERGE
---------------------------
Rule 3 is `clamp(128 + 2*met - 16*violated)` -- its conf tracks how MUCH was seen.
TTG-RFC-0003 §2 counts: `round(255*(max+1)/(for+against+2))` -- its conf tracks how
CONSISTENT what was seen is. Since EPS = sal*(255-conf)/255 drives attention, eviction and
the snake, the choice is not cosmetic.
"""
import re
import sys
import os

DEFAULT = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "master",
                       "cardputer_pre_actIII_2026-09-30.md")

# ⚠ `**COVERED-SPAN**` must NOT match the peer-carrying `**COVERED**` needle -- the same
# needle-collision family as `prev_stream:`. Anchor on the literal followed by ` peer:`.
RE_OBSERVED = re.compile(r"^\*\*OBSERVED\*\* peer:(\S+) proto:(\S+).*?verdict:(\w+)", re.M)
RE_COVERED = re.compile(r"^\*\*COVERED\*\* peer:(\S+) proto:(\S+).*?verdict:(\w+).*?windows:(\d+)", re.M)
RE_TALLY = re.compile(r"\*\*TALLY\*\* met:(\d+) violated:(\d+) unobserved:(\d+)")
RE_CLAIM = re.compile(r"^\*\*LINK-STABLE\*\* peer:(\S+) proto:(\S+)", re.M)
RE_CONF = re.compile(r"conf:(\d+)")


def chunks(text):
    return re.split(r"\n---\s*\n", text)


def rule3(met, violated):
    return max(0, min(255, 128 + 2 * met - 16 * violated))


def ttg(for_w, against_w):
    """TTG-RFC-0003 §2 with prior_for = prior_against = 1, in whole windows."""
    mx = max(for_w, against_w)
    num = 255 * (mx + 1)
    den = for_w + against_w + 2
    return (2 * num + den) // (2 * den)          # round half up, integer only


def main():
    path = sys.argv[1] if len(sys.argv) > 1 else DEFAULT
    with open(path, encoding="utf-8") as fh:
        text = fh.read()

    # --- episodes: expand run-length back into windows -------------------------------
    episodes = []            # list of {(peer, proto): verdict} per WINDOW
    outcome_records = 0
    for c in chunks(text):
        if not re.search(r"^@LAT92LON", c, re.M):
            continue
        outcome_records += 1
        per_window = {}
        for peer, proto, verdict in RE_OBSERVED.findall(c):
            per_window.setdefault((peer, proto), []).append((verdict, 1))
        for peer, proto, verdict, n in RE_COVERED.findall(c):
            per_window.setdefault((peer, proto), []).append((verdict, int(n)))
        # Each window is its own episode: one vote each way, per TTG-0003 §2's per-episode
        # max. Expanding here rather than weighting later keeps the per-episode rule honest.
        widest = 0
        for hits in per_window.values():
            widest = max(widest, sum(n for _, n in hits))
        for w in range(widest):
            ep = {}
            for key, hits in per_window.items():
                seen = 0
                for verdict, n in hits:
                    if seen <= w < seen + n:
                        ep[key] = verdict
                        break
                    seen += n
            if ep:
                episodes.append(ep)

    # --- consolidate ------------------------------------------------------------------
    counts = {}              # (peer, proto) -> [for_windows, against_windows]
    for ep in episodes:
        for key, verdict in ep.items():
            c = counts.setdefault(key, [0, 0])
            if verdict == "met":
                c[0] += 1
            elif verdict == "violated":
                c[1] += 1

    # --- the node's own beliefs, for the faithfulness check ----------------------------
    node = {}                # (peer, proto) -> (met, violated, conf)
    for c in chunks(text):
        if not re.search(r"^@LAT91LON", c, re.M):
            continue
        claim, tally, conf = RE_CLAIM.search(c), RE_TALLY.search(c), RE_CONF.search(c)
        if claim and tally and conf:
            node[(claim.group(1), claim.group(2))] = (
                int(tally.group(1)), int(tally.group(2)), int(conf.group(1)))

    print("store            : %s" % os.path.normpath(path))
    print("@LAT92 records   : %d   ->  %d windows (run-length expanded)"
          % (outcome_records, len(episodes)))
    print("@LAT91 beliefs   : %d" % len(node))
    print()

    hdr = "%-12s %-7s %6s %4s   %6s %5s   %6s %5s   %s"
    print(hdr % ("peer", "proto", "met", "vio", "rule3", "node", "count", "delta", "faithful?"))
    faithful = mismatched = 0
    rows = []
    for key in sorted(counts, key=lambda k: (k[0], k[1])):
        f, a = counts[key]
        r3 = rule3(f, a)
        tg = ttg(f, a)
        nm, nv, nc = node.get(key, (None, None, None))
        ok = (nm == f and nv == a)
        if nm is None:
            verdict = "no belief"
        elif ok:
            verdict = "yes"
            faithful += 1
        else:
            verdict = "NO  node said met:%s vio:%s" % (nm, nv)
            mismatched += 1
        rows.append((key, f, a, r3, tg, nc))
        print(hdr % (key[0], key[1], f, a, r3, nc if nc is not None else "-", tg,
                     (tg - r3) if nc is not None else 0, verdict))

    print()
    if mismatched:
        print("*** %d claim(s) DISAGREE with the node's own tally — the run-length expansion "
              "in this script is wrong, so the comparison above is not trustworthy. ***"
              % mismatched)
        return 1
    print("run-length expansion reproduces the node's own met/violated counts on %d/%d "
          "claims, so the episode set is faithful to what the node counted." % (faithful, len(counts)))

    both = [r for r in rows if r[5] is not None]
    if both:
        print()
        print("Rule 3 conf  : min %3d  max %3d  mean %5.1f"
              % (min(r[3] for r in both), max(r[3] for r in both),
                 sum(r[3] for r in both) / len(both)))
        print("Counting conf: min %3d  max %3d  mean %5.1f"
              % (min(r[4] for r in both), max(r[4] for r in both),
                 sum(r[4] for r in both) / len(both)))
        print("Counting is higher on %d of %d claims; largest gap %+d."
              % (sum(1 for r in both if r[4] > r[3]), len(both),
                 max(r[4] - r[3] for r in both)))
        # The ranking inversion is the finding that matters, because EPS reads conf.
        by_r3 = [r[0] for r in sorted(both, key=lambda r: -r[3])]
        by_ct = [r[0] for r in sorted(both, key=lambda r: -r[4])]
        print("Most-confident claim under Rule 3 : %s/%s" % by_r3[0])
        print("Most-confident claim under counting: %s/%s" % by_ct[0])
        print("Ranking %s between the two consolidators."
              % ("DIFFERS" if by_r3 != by_ct else "agrees"))
    return 0


if __name__ == "__main__":
    sys.exit(main())
