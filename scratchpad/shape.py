"""Per-(peer, proto) verdict matrix for a labelled walk run.

The shape claim under test (percept-learning-return.md §0b): violations track CHANGE,
not distance — a link that is far but STATIONARY should read `met`, and only transit
windows should violate. Testing it needs ground-truth labels that do NOT come from the
RSSI being tested, which is why the operator's transition marks are passed in here
rather than inferred from the signal.

  python scratchpad/shape.py master/gate-2026-08-02/cardputer_labelled.md \
         scratchpad/gate_labels.txt scratchpad/gate_labelled.log
"""
import re
import sys

ttdb, labelfile, logfile = sys.argv[1], sys.argv[2], sys.argv[3]

# label anchors: "<elapsed_seconds> <name>"
labels = []
for line in open(labelfile, encoding="utf-8"):
    if line.strip():
        t, name = line.split(None, 1)
        labels.append((float(t), name.strip()))

# Map @LAT92 LON -> the capture-elapsed second at which the node printed it, so the
# operator's labels (also in capture-elapsed seconds) can be laid alongside. The record
# itself only carries local millis(), which has a different origin.
lon_time = {}
for line in open(logfile, encoding="utf-8", errors="replace"):
    m = re.search(r"^\s*([0-9.]+)s \| \[learn\] outcome -> @LAT92LON(\d+)", line)
    if m:
        lon_time[int(m.group(2))] = float(m.group(1))


def state_at(t):
    """What the operator says was happening in the window ENDING at t (60 s wide)."""
    if t is None:
        return "?"
    start = t - 60.0
    # a window is labelled by every phase it overlaps, so a mixed window is visible as
    # mixed rather than silently assigned to one side
    phases = []
    for i, (lt, name) in enumerate(labels):
        nxt = labels[i + 1][0] if i + 1 < len(labels) else 1e9
        if start < nxt and t > lt:
            phases.append(name)
    if not phases:
        # NOT "still". The operator only labelled the transitions they were asked to
        # label; anything before the first mark is simply UNLABELLED, and on this run
        # the roamer was in fact being handled during it (that is when the field-mark
        # key was being tried). Calling it "still" would manufacture ground truth and
        # would have buried the real result in a bogus 7% baseline violation rate.
        return "unlabelled"
    return "+".join(phases)


records = re.findall(r"^@LAT92LON(\d+).*?(?=^@LAT|\Z)", open(ttdb, encoding="utf-8",
                                                              errors="replace").read(),
                     re.S | re.M)
text = open(ttdb, encoding="utf-8", errors="replace").read()

rows = []
cols = []
for m in re.finditer(r"^@LAT92LON(\d+)(.*?)(?=^@LAT|\Z)", text, re.S | re.M):
    lon = int(m.group(1))
    body = m.group(2)
    cells = {}
    for pm in re.finditer(r"\*\*OBSERVED\*\* peer:0x([0-9a-fA-F]+)\s+proto:(\w+)\s*"
                          r"(?:observed_med:(-?\d+)\s+delta:(-?\d+)\s+)?verdict:(\w+)",
                          body):
        key = "%s/%s" % (pm.group(1).lstrip("0") or "0", pm.group(2)[:3])
        if key not in cols:
            cols.append(key)
        d = pm.group(4)
        v = pm.group(5)
        cells[key] = ("." if v == "met" else ("X" if v == "violated" else "?"),
                      d if d is not None else "")
    rows.append((lon, cells))

print("legend: . met   X violated   ? unobserved     (delta dBm in parens)\n")
hdr = "  LON  %-22s " % "operator label"
for c in cols:
    hdr += "%-14s" % c
print(hdr)
for lon, cells in rows:
    t = lon_time.get(lon)
    line = "  %3d  %-22s " % (lon, state_at(t))
    for c in cols:
        if c in cells:
            mark, d = cells[c]
            line += "%-14s" % ("%s %s" % (mark, ("(%s)" % d) if d else ""))
        else:
            line += "%-14s" % "-"
    print(line)

# The claim, scored. Only windows that are UNAMBIGUOUSLY one phase count: a window
# straddling a transition is neither, and quietly assigning it to one side is how a
# result like this gets flattered.
print("\nscored on unambiguous windows only (a straddling window is excluded, not assigned):")
for phase, label in (("walking", "TRANSIT"), ("parked", "PARKED FAR"),
                     ("unlabelled", "UNLABELLED (roamer handled)")):
    vio = met = 0
    for lon, cells in rows:
        if state_at(lon_time.get(lon)) != phase:
            continue
        for c, (mark, _) in cells.items():
            if mark == "X":
                vio += 1
            elif mark == ".":
                met += 1
    tot = vio + met
    if tot:
        print("  %-28s %3d claims  %3d met  %3d violated  (%.0f%% violation rate)"
              % (label, tot, met, vio, 100.0 * vio / tot))

# The internal control: three peers that never moved, scored over the WHOLE run. Any
# violation here is the 6 dBm band's false-positive rate on a genuinely stable link, and
# it is the number that says how much of the roamer's signal is real.
print("\ninternal control — peers that never moved, all windows:")
for group, keys in (("STATIONARY (V4-A/B/C)", [c for c in cols if not c.startswith("200/")]),
                    ("ROAMER (T-Deck 0x200)", [c for c in cols if c.startswith("200/")])):
    vio = met = unobs = absent = 0
    for lon, cells in rows:
        for c in keys:
            if c not in cells:
                absent += 1
            elif cells[c][0] == "X":
                vio += 1
            elif cells[c][0] == ".":
                met += 1
            else:
                unobs += 1
    tot = vio + met
    print("  %-24s %3d scored  %3d met  %3d violated  (%.1f%%)  "
          "[%d unobserved, %d no-claim]"
          % (group, tot, met, vio, 100.0 * vio / tot if tot else 0, unobs, absent))

