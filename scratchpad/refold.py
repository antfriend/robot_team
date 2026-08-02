"""Independently re-fold a node's @LAT92 outcome lane through Rule 3, on the laptop.

This is the cross-check that discharges TTE Draft 06's standing caveat ("the only
reconciliation was performed by hand, by an outside reader"): a SECOND implementation,
reading the same records off the same pulled file, must arrive at the same conf/sal.

It deliberately re-reads the lane rather than tracking a running total, for the same
reason the device does — a running total would agree with the device by construction
and prove nothing (companion.md, Stage D).

  python scratchpad/refold.py master/gate-2026-08-02/cardputer_walkrun.md
"""
import re
import sys

# Mirrors PerceptLearn.h. If these drift from the header the check is meaningless, so
# they are named the same and listed together.
BASELINE_CONF = 128
CONF_MET = 2
CONF_VIOLATED = 16
SAL_VIOLATED = 8
CONTRADICTION_STREAK = 2

path = sys.argv[1]
text = open(path, encoding="utf-8", errors="replace").read()

# One pass over the file in RECORD ORDER. Folding must be sequential: +2 saturates at
# 255 and -16 floors at 0, and a clamp does not commute with a sum, so tallying first
# and applying the arithmetic once is subtly wrong over long runs.
obs = re.compile(r"\*\*OBSERVED\*\* peer:0x([0-9a-fA-F]+)\s+proto:(\w+).*?verdict:(\w+)")

beliefs = {}
order = []
records = 0
for m in re.finditer(r"^@LAT92LON\d+.*?(?=^@LAT|\Z)", text, re.S | re.M):
    records += 1
    for peer_hex, proto, verdict in obs.findall(m.group(0)):
        key = (int(peer_hex, 16), proto)
        if key not in beliefs:
            beliefs[key] = dict(met=0, violated=0, unobserved=0, conf=BASELINE_CONF,
                                sal=0, streak=0, max_streak=0, contradiction=False)
            order.append(key)
        b = beliefs[key]
        if verdict == "met":
            b["met"] += 1
            b["conf"] = min(255, b["conf"] + CONF_MET)
            b["streak"] = 0
        elif verdict == "violated":
            b["violated"] += 1
            b["conf"] = max(0, b["conf"] - CONF_VIOLATED)
            b["sal"] += SAL_VIOLATED
            b["streak"] += 1
            b["max_streak"] = max(b["max_streak"], b["streak"])
            if b["streak"] >= CONTRADICTION_STREAK:
                b["contradiction"] = True
        else:
            # unobserved: neither corroborates nor contradicts, and must NOT break a
            # violation streak — nothing was tested, so nothing is known.
            b["unobserved"] += 1

print("laptop re-fold of %d @LAT92 record(s) in %s\n" % (records, path))
print("  %-10s %-7s %5s %4s %4s %4s %5s %5s %s"
      % ("peer", "proto", "conf", "sal", "met", "vio", "unobs", "maxst", "contra"))
for key in order:
    b = beliefs[key]
    print("  0x%-8x %-7s %5d %4d %4d %4d %5d %5d %s"
          % (key[0], key[1], b["conf"], b["sal"], b["met"], b["violated"],
             b["unobserved"], b["max_streak"], "YES" if b["contradiction"] else "-"))

# Now compare against what the DEVICE wrote into @LAT91, parsed out of the same file.
print("\ndevice @LAT91 belief lane, for comparison:")
dev = {}
for m in re.finditer(r"^@LAT91LON\d+.*?(?=^@LAT|\Z)", text, re.S | re.M):
    blk = m.group(0)
    ls = re.search(r"\*\*LINK-STABLE\*\* peer:0x([0-9a-fA-F]+)\s+proto:(\w+)", blk)
    tally = re.search(r"\*\*TALLY\*\* met:(\d+) violated:(\d+) unobserved:(\d+).*?"
                      r"max_streak:(\d+)\s+contradiction:(\d+)", blk, re.S)
    ew = re.search(r"conf:(\d+)\s+rev:(\d+)\s+sal:(\d+)", blk)
    if not (ls and tally and ew):
        continue
    key = (int(ls.group(1), 16), ls.group(2))
    dev[key] = dict(conf=int(ew.group(1)), sal=int(ew.group(3)), met=int(tally.group(1)),
                    violated=int(tally.group(2)), unobserved=int(tally.group(3)),
                    max_streak=int(tally.group(4)),
                    contradiction=tally.group(5) != "0")
    b = dev[key]
    print("  0x%-8x %-7s %5d %4d %4d %4d %5d %5d %s"
          % (key[0], key[1], b["conf"], b["sal"], b["met"], b["violated"],
             b["unobserved"], b["max_streak"], "YES" if b["contradiction"] else "-"))

print("")
fields = ["conf", "sal", "met", "violated", "unobserved", "max_streak", "contradiction"]
bad = 0
for key in order:
    if key not in dev:
        print("MISMATCH 0x%x %s: device wrote no belief for this pair" % key)
        bad += 1
        continue
    for f in fields:
        if beliefs[key][f] != dev[key][f]:
            print("MISMATCH 0x%x %s %s: laptop %s, device %s"
                  % (key[0], key[1], f, beliefs[key][f], dev[key][f]))
            bad += 1
for key in dev:
    if key not in beliefs:
        print("MISMATCH 0x%x %s: device has a belief the lane does not support" % key)
        bad += 1

print("CROSS-CHECK %s (%d pair(s), %d field mismatch(es))"
      % ("PASS - two implementations, same evidence, same answer" if not bad else "FAIL",
         len(order), bad))
sys.exit(1 if bad else 0)
