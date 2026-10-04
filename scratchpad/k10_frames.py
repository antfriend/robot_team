import re
import sys

sys.path.insert(0, "orchestrator")
import fleet as c  # noqa: E402

t = open(sys.argv[1], encoding="utf-8").read()


def last(lane, n):
    out = []
    for lat, lon, lines in c.lane_records(t, lambda la, lo: la == lane):
        s = f = a = g = None
        for l in lines:
            l = l.strip()
            m = re.match(r"seq: (\d+)", l)
            if m:
                s = int(m.group(1))
            m = re.match(r"at: (\d+).*frame:(\d+)", l)
            if m:
                a, f = int(m.group(1)), int(m.group(2))
            m = re.match(r"held: 0x([0-9a-f]+)", l)
            if m:
                g = int(m.group(1), 16)
        if s:
            out.append((s, f, a, hex(g) if g else "own"))
    return sorted(out)[-n:]


print("K10 own, last 8 (seq, frame, at):", last(103, 8))
print("held copies, last 6 (seq, frame, at, author):", last(105, 6))
