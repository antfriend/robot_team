import re, sys

# Which body token belongs to which lane.
EXPECT = {"96": ("ENTWIN", "ENTITY"), "97": ("LINKWIN", "LINK")}

for path in sys.argv[1:]:
    s = open(path, encoding="utf-8", errors="replace").read()
    # Split into records on the @LAT header.
    parts = re.split(r"^(@LAT(\d+)LON(\d+)[^\n]*)$", s, flags=re.M)
    bad = 0
    total = 0
    for i in range(1, len(parts), 4):
        lat = parts[i + 1]
        body = parts[i + 3] if i + 3 < len(parts) else ""
        if lat not in EXPECT:
            continue
        total += 1
        toks = set(re.findall(r"\*\*([A-Z_]+)\*\*", body))
        if not toks:
            continue
        allowed = set(EXPECT[lat])
        foreign = toks - allowed
        if foreign or not (toks & allowed):
            bad += 1
            if bad <= 4:
                print("   MISMATCH @LAT%sLON%s body=%s foreign=%s"
                      % (lat, parts[i + 2], sorted(toks), sorted(foreign)))
    print("%s: %d percept records, %d with wrong-lane body" % (path, total, bad))
