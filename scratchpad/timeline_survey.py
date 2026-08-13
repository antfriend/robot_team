"""timeline_survey.py — what is actually filling the @LAT90 timeline lanes.

WHY THIS EXISTS. `TIMESTREAM_MAX_LANE 16`'s refusal-on-full policy has been open since
2026-08-03 with the instruction "decide it against the accumulation rate, not now". On
2026-08-13 four of five witness-bearing boards were found at 16/16 within ~2 days of their
last prune, so the rate is no longer the unknown — but the rate alone does not tell you
whether to raise the cap, change the eviction, or reduce the churn. The COMPOSITION does.

Two questions it answers, neither visible from a record count:

  1. WHICH VERB fills the lane. ORIGIN means a node heard no peer inside its listen window
     and started its own timeline; ADOPTED means it joined someone else's; RECONCILED is
     never suppressed by design. A lane full of ORIGIN is a lost-listen-race problem, not
     a capacity problem, and raising the cap would treat the symptom.

  2. WHETHER AN ID IS SHARED. A stream id that only ever appears on ONE board never
     mattered to the fleet — nobody adopted it. A stream id on six boards cost six lane
     slots for one fact. That ratio is the amplification, and it is what makes @LAT90 a
     FLEET-COUPLED resource: one node's lost race can spend a slot on every other node.

Usage:  python scratchpad/timeline_survey.py <pulled-ttdb.md> [more.md ...]
        (board name is taken from the filename prefix)

⚠ Reads PULLED files, not the boards — so it surveys the lanes as banked. Pull first.
⚠ `prev_stream:` is stripped before matching: it names the stream a RECONCILED record
   LEFT, and a bare `stream:0x` needle matches inside it (same trap as companion.py's).
"""
import re
import sys
import collections

VERBS = ("STREAM-ORIGIN", "STREAM-ADOPTED", "STREAM-RECONCILED", "STREAM-ANCHORED")


def survey(path):
    text = open(path, encoding="utf-8", errors="replace").read()
    verbs = collections.Counter()
    ids = set()
    for line in text.splitlines():
        if not line.startswith("**STREAM-"):
            continue
        for v in VERBS:
            if line.startswith("**%s**" % v):
                verbs[v] += 1
        stripped = re.sub(r"prev_stream:0x[0-9a-f]+", "", line)
        m = re.search(r"\bstream:0x([0-9a-f]+)", stripped)
        if m:
            ids.add(m.group(1))
    records = len(re.findall(r"(?m)^@LAT90LON\d+ \|", text))
    return records, verbs, ids


def main(paths):
    per_board = {}
    for p in paths:
        name = p.replace("\\", "/").split("/")[-1].split("_")[0]
        per_board[name] = survey(p)

    print("%-11s %5s  %-8s %-9s %-11s %-9s" % (
        "board", "recs", "ORIGIN", "ADOPTED", "RECONCILED", "ANCHORED"))
    for name, (recs, verbs, _) in per_board.items():
        print("%-11s %5d  %-8d %-9d %-11d %-9d" % (
            name, recs, verbs["STREAM-ORIGIN"], verbs["STREAM-ADOPTED"],
            verbs["STREAM-RECONCILED"], verbs["STREAM-ANCHORED"]))

    seen = collections.Counter()
    slots = 0
    for _, (_, _, ids) in per_board.items():
        slots += len(ids)
        for i in ids:
            seen[i] += 1
    if not seen:
        print("\nno @LAT90 records found")
        return

    lonely = [i for i, c in seen.items() if c == 1]
    print("\n%d distinct stream id(s) cost %d lane slot(s) fleet-wide "
          "(%.2fx amplification)" % (len(seen), slots, slots / float(len(seen))))
    print("spread — how many boards carry each id:")
    for boards, cnt in sorted(collections.Counter(seen.values()).items()):
        print("   on %d board(s): %3d id(s)   -> %d slot(s)" % (boards, cnt, boards * cnt))
    print("\n%d of %d ids (%.0f%%) exist on ONE board only — never adopted by anyone, so "
          "they cost a slot\nand bought the fleet no shared timeline." % (
              len(lonely), len(seen), 100.0 * len(lonely) / len(seen)))


if __name__ == "__main__":
    if len(sys.argv) < 2:
        sys.exit(__doc__)
    main(sys.argv[1:])
