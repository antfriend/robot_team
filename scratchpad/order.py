import re, sys

for path in sys.argv[1:]:
    s = open(path, encoding="utf-8", errors="replace").read()
    recs = re.findall(r"^@LAT(\d+)LON(\d+)", s, re.M)
    print("\n== %s  (%d recs, %d bytes)" % (path, len(recs), len(s)))
    print("   first 6:", ["@LAT%sLON%s" % r for r in recs[:6]])
    print("   last  6:", ["@LAT%sLON%s" % r for r in recs[-6:]])
    tail = s[-160:].replace("\n", "\\n")
    print("   tail:", tail)
