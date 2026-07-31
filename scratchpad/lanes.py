import re, collections, sys

path = sys.argv[1]
s = open(path, encoding="utf-8", errors="replace").read()
recs = re.findall(r"^@LAT(\d+)LON(\d+)", s, re.M)
c = collections.Counter(lat for lat, _ in recs)
print("%s: %d records, %d bytes" % (path, len(recs), len(s)))
for lat, n in sorted(c.items(), key=lambda kv: -kv[1]):
    print("  @LAT%s: %d records" % (lat, n))
