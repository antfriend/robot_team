#!/usr/bin/env python3
"""test_sid_py.py -- the laptop half of stable record identity (TTDB-RFC-0010 §4.2),
and the KEY-kind sids that `ttn-semantic-positioning.md` Draft 0.3 §2.4 requires on
@BELIEF:POSITION and @BELIEF:PROXIMITY.

WHY THIS FILE EXISTS, TWICE OVER.

1. CROSS-LANGUAGE AGREEMENT. The entire value of a stable id is that a reader holding
   only the file can RECOMPUTE it. So a node's arithmetic and the laptop's must agree
   byte for byte on the preimage, and NOTHING ELSE IN THE SYSTEM WOULD NOTICE if they
   stopped: every citation would silently resolve `stale` against a perfectly good
   record. The eight vectors below are the same eight in `tests/test_sid.cpp`.
   ⚠ Until 2026-08-11 the Python side lived only in `scripts/sid_probe.py`, a
   measurement script no test ran. `companion.py` now owns it and sid_probe imports
   from there -- two languages, one implementation each, as RFC-0010 §4.2.2 intends.

2. KEY IDENTITY MUST BE BODY- AND TIME-INDEPENDENT. A position belief is revised
   continuously as evidence accumulates (SP4, "position as living belief"). Under an
   EVENT-kind id every revision renames the record and every typed edge into it
   dangles. RFC-0010 puts it plainly: *"body-in on a KEY lane forks a belief's identity
   on every revision."* The revision tests below are the ones that would catch that,
   and they are the reason this is not just a hash test.

Run: python tests/test_sid_py.py
"""
import os
import sys

sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "orchestrator"))
import companion as c  # noqa: E402

fails = 0


def check(cond, msg):
    global fails
    print(("pass: " if cond else "FAIL: ") + msg)
    if not cond:
        fails += 1


# ---------------------------------------------------------------------------
# 1) The eight cross-language vectors. Identical to tests/test_sid.cpp.
# ---------------------------------------------------------------------------
check(c.fnv1a("") == 0x811C9DC5, "vector fnv1a('') matches test_sid.cpp")
check(c.fnv1a("a") == 0xE40C292C, "vector fnv1a('a') matches test_sid.cpp")
check(c.fnv1a("foobar") == 0xBF9CF968, "vector fnv1a('foobar') matches test_sid.cpp")
check(c.sid_event(0x300, 95, 0xE334A7E1, 3710811,
                  c.sid_body_digest("**MOTIONWIN** state:still\n")) == 0x24A930C2,
      "vector event/basic matches test_sid.cpp")
check(c.sid_event(0, 0, 0, 0, 0) == 0x74526815, "vector event/zero matches test_sid.cpp")
check(c.sid_event(0x300, 96, 0, 60000,
                  c.sid_body_digest("entities:5 rssi:-31")) == 0x05989C91,
      "vector event/nostream matches test_sid.cpp")
check(c.sid_key(0x300, 91, "peer:0x00000200|proto:espnow") == 0x8A93826D,
      "vector key/link-stable matches test_sid.cpp")
check(c.sid_key(0x300, 91, "") == 0x0177C5F9, "vector key/empty matches test_sid.cpp")

# The one Python implementation really is one: sid_probe must be importing, not copying.
sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "scripts"))
import sid_probe  # noqa: E402
check(sid_probe.fnv1a is c.fnv1a and sid_probe.sid_key is c.sid_key,
      "scripts/sid_probe.py IMPORTS companion's hash rather than re-implementing it")

# ---------------------------------------------------------------------------
# 2) KEY identity: no body, no time. This is the property SP4 depends on.
# ---------------------------------------------------------------------------
k1 = c.sid_key(0x300, 91, "peer:0x00000200|proto:espnow")
k2 = c.sid_key(0x300, 91, "peer:0x00000200|proto:espnow")
check(k1 == k2, "a KEY sid is a pure function of (node, lane, key)")
check(c.sid_key(0x300, 91, "peer:0x00000201|proto:espnow") != k1,
      "and different subjects get different ids")
check(c.sid_key(0x301, 91, "peer:0x00000200|proto:espnow") != k1,
      "the AUTHOR is in the preimage (uniqueness is scoped to (node, lane))")
check(c.sid_key(0x300, 92, "peer:0x00000200|proto:espnow") != k1,
      "and so is the lane -- the same key in two lanes is two subjects")

# EVENT identity, by contrast, MUST move when the body moves. Negative control: if this
# ever stopped being true, the 8.1% input-collision measurement would be meaningless.
e1 = c.sid_event(0x300, 96, 1, 1000, c.sid_body_digest("a"))
e2 = c.sid_event(0x300, 96, 1, 1000, c.sid_body_digest("b"))
check(e1 != e2, "NEGATIVE CONTROL: an EVENT sid DOES move with the body")
check(c.sid_event(0x300, 96, 1, 2000, c.sid_body_digest("a")) != e1,
      "and with the timestamp -- the two kinds really are different functions")

# ---------------------------------------------------------------------------
# 3) The belief lanes: a negative lane must render as two's-complement hex4.
# ---------------------------------------------------------------------------
check(c.BELIEF_LANE_POSITION < 0 and c.BELIEF_LANE_PROXIMITY < 0,
      "laptop belief lanes are NEGATIVE -- a namespace provably disjoint from every "
      "node lane (all >= 0)")
check(c.BELIEF_LANE_POSITION != c.BELIEF_LANE_PROXIMITY,
      "and distinct from each other")
# -1 & 0xFFFF == 0xFFFF, i.e. the int16 two's complement RFC-0010 §4.2.2 specifies.
check(c.sid_key(1, -1, "x") == c.sid_key(1, 0xFFFF, "x"),
      "lane -1 hashes as two's-complement 'ffff' (RFC-0010 sec 4.2.2)")
check(c.sid_key(1, -1, "x") != c.sid_key(1, -2, "x"),
      "and -1 and -2 are still different lanes")

# ---------------------------------------------------------------------------
# 4) Position sids: recomputable, per-node, and REFUSED rather than guessed.
# ---------------------------------------------------------------------------
sid_a = c.position_sid("v4a_bridge")
check(sid_a is not None and sid_a == c.sid_key(
    c.ORCHESTRATOR_ID, c.BELIEF_LANE_POSITION,
    "node:0x%08x" % c.NODE_IDS["v4a_bridge"]),
      "a position sid is recomputable from the KEY ALONE -- no file needed")
check(c.position_sid("tdeck_1") != sid_a, "and differs per node")
check(c.position_sid("no_such_node") is None,
      "an unknown node yields NO sid (refuse, do not perturb -- sec 4.2.4)")
check(c.sid_header_field(None) == "",
      "and no sid means no header field, never a guessed one")
check(c.sid_header_field(0xA1B2C3D4) == " | sid:a1b2c3d4",
      "the header field is lowercase 8-hex in RFC-0010's form")
check(c.header_sid("@BELIEF:POSITION @node(v4a_bridge)"
                   + c.sid_header_field(sid_a)) == sid_a,
      "and companion's own READER round-trips what its writer emits")

# ---------------------------------------------------------------------------
# 5) Proximity sids: symmetric in the pair, and proto is part of the subject.
# ---------------------------------------------------------------------------
p_ab = c.proximity_sid("v4a_bridge", "v4b_relay", "espnow")
p_ba = c.proximity_sid("v4b_relay", "v4a_bridge", "espnow")
check(p_ab is not None and p_ab == p_ba,
      "proximity is SYMMETRIC: (a,b) and (b,a) are one subject, one id -- otherwise a "
      "change in iteration order silently renames every pair belief")
check(c.proximity_sid("v4a_bridge", "v4b_relay", "ble") != p_ab,
      "but espnow and ble about the same pair are different standing rows (@LAT91's "
      "peer|proto precedent)")
check(c.proximity_sid("v4a_bridge", "v4c_edge", "espnow") != p_ab,
      "and a different pair is a different subject")
check(c.proximity_sid("v4a_bridge", "no_such_node", "espnow") is None,
      "an unknown node in the pair yields no sid")
check(p_ab != c.position_sid("v4a_bridge"),
      "position and proximity sids cannot collide across their lanes")

# ---------------------------------------------------------------------------
# 6) END TO END: a REVISED belief keeps its name. This is the whole point.
# ---------------------------------------------------------------------------
import contextlib, io, re, tempfile  # noqa: E402

d = tempfile.mkdtemp()
prox = os.path.join(d, "proximity.md")


def write_prox(dist):
    with open(prox, "w", encoding="utf-8", newline="\n") as f:
        f.write("# prox\n")
        for a, b, base in (("v4a_bridge", "v4b_relay", 4.0),
                           ("v4a_bridge", "tdeck_1", 3.0),
                           ("v4b_relay", "tdeck_1", 5.0)):
            f.write(f"\n---\n\n@BELIEF:PROXIMITY @pair({a}, {b})\n"
                    f"proto: espnow\ndist_est_m: {base + dist}\ndist_sigma_m: 0.5\n"
                    f"n_obs: 100\nconf: 0.7\n")


def sids_of(path):
    text = open(path, encoding="utf-8").read()
    out = {}
    for chunk in text.split("@BELIEF:POSITION")[1:]:
        m = re.match(r"\s*@node\((\w+)\)", chunk)
        s = re.search(r"sid:([0-9a-f]{8})", chunk.split("\n", 1)[0])
        if m:
            out[m.group(1)] = s.group(1) if s else None
    return out


out1 = os.path.join(d, "p1.md")
out2 = os.path.join(d, "p2.md")
write_prox(0.0)
with contextlib.redirect_stdout(io.StringIO()):
    c.positions(prox, out1, 400)
write_prox(3.5)          # the world moved: every distance, sigma, conf and rev changes
with contextlib.redirect_stdout(io.StringIO()):
    c.positions(prox, out2, 400)

s1, s2 = sids_of(out1), sids_of(out2)
check(s1 and all(v is not None for v in s1.values()),
      "every @BELIEF:POSITION record carries a sid (got %r)" % s1)
check(s1 == s2,
      "A REVISED BELIEF KEEPS ITS NAME across a re-embed that changed every number -- "
      "the property SP4 depends on and an EVENT-kind id would destroy")
t1 = open(out1, encoding="utf-8").read()
t2 = open(out2, encoding="utf-8").read()
check(t1 != t2, "NEGATIVE CONTROL: the two files really do differ (so the check above "
                "is not comparing a file to itself)")

# The fixture proximity file is hand-written and carries no sids, so the sids above can
# only have come from the writer under test.
check("sid:" not in open(prox, encoding="utf-8").read(),
      "the input fixture carries no sids, so the ones above came from the writer")

# ---------------------------------------------------------------------------
# 7) The push path must carry the sid to the node unchanged.
# ---------------------------------------------------------------------------
blob, n = c.author_position_belief(out1)
btext = blob.decode("utf-8")
check(n == 3 and btext.count("sid:") == 3,
      "author_position_belief carries every sid through to /belief.md (got %d)"
      % btext.count("sid:"))
for nd, s in s1.items():
    if s:
        check(f"sid:{s}" in btext, f"  {nd}'s sid survives the push re-author")
        break

# ---------------------------------------------------------------------------
print()
if fails:
    print("%d FAILED" % fails)
    sys.exit(1)
print("all sid (laptop) checks passed")
