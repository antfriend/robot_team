"""sid_probe.py -- the measurement behind TTDB-RFC-0010 section 4's sid decision.

Kept in the repo, not the scratchpad, because the decision rests on it: RFC-0010 section 8
falsifier 3 says the hash input "must be measured, not re-guessed", and this is the
measurement. Re-run it after any change to what a record body contains.

    python scripts/sid_probe.py            # measure master/ and print the decision numbers
    python scripts/sid_probe.py --vectors  # print the cross-language test vectors only

WHAT IT ANSWERS
  1. Does the proposed hash INPUT distinguish records that are different?  (An input
     collision is a design error; no hash width fixes it.)
  2. Does the 32-bit hash then collide?
  3. Do the Python and C++ implementations agree byte for byte?  They must, or a laptop
     reader cannot verify a node's ids -- which is the entire point of a stable id.

RESULT, 2026-08-09, over 78 archived TTDBs / 6683 records in lanes >= 90:
  RFC-0010 section 9's proposed (node, lane, stream, t_ms)   538 input collisions (8.0%)
  ...with a digest of the record BODY added                    0 input collisions
  ...32-bit FNV-1a true hash collisions                        0 in 6672 distinct ids
"""
import re, os, sys, glob, collections

ROOT = os.path.join(os.path.dirname(os.path.dirname(os.path.abspath(__file__))), 'master')
REC = re.compile(r'^@LAT(-?\d+)LON(-?\d+)\s*\|', re.M)


# --------------------------------------------------------------------------------------
# The decided scheme. MUST match firmware/libraries/TTDB/src/Sid.cpp byte for byte.
#
# ⚠ IMPORTED FROM companion.py, NOT re-implemented here (2026-08-11). This file used to
# carry its own copy; when the laptop started AUTHORING sids (Draft 0.3 §2.4) that would
# have become a SECOND Python implementation of a hash whose whole value is that every
# reader computes it identically. RFC-0010 §4.2.2 pins it "in two languages deliberately"
# -- two languages, one implementation each. The numbers this script published in the RFC
# are unaffected: the functions are byte-identical, and tests/test_sid_py.py asserts the
# same eight vectors as tests/test_sid.cpp against these imports.
# --------------------------------------------------------------------------------------
sys.path.insert(0, os.path.join(os.path.dirname(os.path.dirname(
    os.path.abspath(__file__))), 'orchestrator'))
from companion import (fnv1a, sid_event, sid_key,          # noqa: E402
                       sid_body_digest as body_digest,
                       FNV_OFFSET, FNV_PRIME)              # noqa: F401


# --------------------------------------------------------------------------------------
# Cross-language vectors. The same values are asserted in tests/test_sid.cpp; if the two
# ever disagree, a node and the laptop have silently stopped agreeing on what a record is
# called, and nothing else in the system would notice.
# --------------------------------------------------------------------------------------
VECTORS = [
    ("fnv1a('')",       fnv1a(""),                                        0x811c9dc5),
    ("fnv1a('a')",      fnv1a("a"),                                       0xe40c292c),
    ("fnv1a('foobar')", fnv1a("foobar"),                                  0xbf9cf968),
    ("event/basic",     sid_event(0x300, 95, 0xe334a7e1, 3710811,
                                  body_digest("**MOTIONWIN** state:still\n")), None),
    ("event/zero",      sid_event(0, 0, 0, 0, 0),                         None),
    ("event/nostream",  sid_event(0x300, 96, 0, 60000,
                                  body_digest("entities:5 rssi:-31")),    None),
    ("key/link-stable", sid_key(0x300, 91, "peer:0x00000200|proto:espnow"), None),
    ("key/empty",       sid_key(0x300, 91, ""),                           None),
]


def print_vectors():
    print("Cross-language sid vectors (Python side).")
    print("Paste-checked against tests/test_sid.cpp.\n")
    for name, got, want in VECTORS:
        mark = ""
        if want is not None:
            mark = "  OK" if got == want else "  ** MISMATCH vs published %08x **" % want
        print("  %-18s %08x%s" % (name, got, mark))


# --------------------------------------------------------------------------------------
def parse_time(body):
    # CLAUDE.md: strip prev_stream FIRST -- \b does not help, it matches INSIDE it.
    b = re.sub(r'prev_stream:0x[0-9a-fA-F]+', '', body)
    t = re.search(r'\bt_ms:(\d+)', b)
    st = re.search(r'stream:0x([0-9a-fA-F]+)', b)
    sy = re.search(r'\bsynced:([01])', b)
    return (int(t.group(1)) if t else None,
            int(st.group(1), 16) if st else (0 if sy else None))


def records(path):
    txt = open(path, encoding='utf-8', errors='replace').read()
    hits = list(REC.finditer(txt))
    for i, m in enumerate(hits):
        end = hits[i + 1].start() if i + 1 < len(hits) else len(txt)
        rec = txt[m.start():end]
        body = rec.split('\n', 1)[1] if '\n' in rec else ''
        yield int(m.group(1)), int(m.group(2)), body


def measure():
    files = sorted(glob.glob(os.path.join(ROOT, '**', '*.md'), recursive=True))
    if not files:
        print("no TTDBs under %s" % ROOT)
        return 1
    print("%d archived TTDBs under master/\n" % len(files))

    lane_total, lane_dupe_time, lane_dupe_full = (collections.Counter() for _ in range(3))
    seen_sid = {}
    true_collisions, stable_repulls = 0, 0
    no_time = collections.Counter()

    for path in files:
        rel = os.path.relpath(path, ROOT)
        node = fnv1a(os.path.basename(path)) & 0xFFFFFFFF   # stand-in for the node id
        by_time, by_full = {}, {}
        for lat, lon, body in records(path):
            if lat < 90:
                continue
            t_ms, stream = parse_time(body)
            if t_ms is None:
                m = re.search(r'^\*\*([A-Z][A-Z0-9-]*)\*\*', body, re.M)
                no_time[m.group(1) if m else '-'] += 1
                continue
            lane_total[lat] += 1
            kt = (lat, stream, t_ms)
            if kt in by_time:
                lane_dupe_time[lat] += 1
            by_time[kt] = 1
            bd = body_digest(body)
            kf = (lat, stream, t_ms, bd)
            if kf in by_full:
                lane_dupe_full[lat] += 1
            by_full[kf] = 1
            s = sid_event(node, lat, stream or 0, t_ms, bd)
            if s in seen_sid:
                prev_rel, prev_body = seen_sid[s]
                if prev_rel != rel:
                    if prev_body == body:
                        stable_repulls += 1
                    else:
                        true_collisions += 1
                        print("  ** TRUE COLLISION %s vs %s @LAT%dLON%d" %
                              (prev_rel, rel, lat, lon))
            else:
                seen_sid[s] = (rel, body)

    print("== input collisions, by lane ==")
    print("  %-8s %8s %14s %14s" % ("lane", "records", "(lane,strm,t)", "+ body digest"))
    for lane in sorted(lane_total):
        n = lane_total[lane]
        print("  @LAT%-4d %8d %8d %4.1f%% %8d %4.1f%%" %
              (lane, n, lane_dupe_time[lane], lane_dupe_time[lane] / n * 100,
               lane_dupe_full[lane], lane_dupe_full[lane] / n * 100))
    tot, dt, df = (sum(lane_total.values()), sum(lane_dupe_time.values()),
                   sum(lane_dupe_full.values()))
    print("  %-8s %8d %8d %4.1f%% %8d %4.1f%%" % ("TOTAL", tot, dt, dt / tot * 100,
                                                  df, df / tot * 100))

    print("\n== records in lanes >= 90 with NO t_ms (KEY identity is not optional) ==")
    for mk, n in no_time.most_common():
        print("  %-22s %d" % (mk, n))

    print("\n== 32-bit FNV-1a over the decided input ==")
    print("  distinct sids            %d" % len(seen_sid))
    print("  TRUE hash collisions     %d" % true_collisions)
    print("  same record, two pulls   %d  (same sid -- the stability the scheme is for)"
          % stable_repulls)

    print("\n== birthday risk at 32 bits ==")
    import math
    for pop, label in ((48, "one lane at its cap"), (256, "one node file budget"),
                       (len(seen_sid), "this whole archive"), (100000, "100k records")):
        p = 1 - math.exp(-pop * (pop - 1) / 2 / 2 ** 32)
        print("  %-24s n=%-7d P(any collision) ~ %.2e" % (label, pop, p))
    print("\n  -> 32 bits is right for a (node, lane) scope and WRONG for the corpus;")
    print("     RFC-0010 section 4.2 therefore scopes uniqueness, it does not widen the hash.")
    return 0


if __name__ == '__main__':
    if '--vectors' in sys.argv:
        print_vectors()
    else:
        print_vectors()
        print()
        sys.exit(measure())
