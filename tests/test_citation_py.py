"""test_citation_py.py -- TTDB-RFC-0010 section 7.2 stage 1, laptop reader.

The C++ counterpart is tests/test_citation.cpp; both must agree, because a citation is
resolved on whichever side happens to be holding the file.

What is worth pinning:
  * every PRE-ADOPTION file parses byte-identically -- the whole risk of this stage
  * a `#sid` citation resolves with NO @LAT100 boundary and NO timeline comparison, which
    is the capability being bought
  * "I cannot check this" never renders as either "fine" or "broken"
  * the needle-collision guard: `prev_sid:` must not be read as `sid:`
"""
import os, sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)),
                                "..", "orchestrator"))
import companion as c                                          # noqa: E402

fails = []


def check(ok, what):
    print(("pass: " if ok else "FAIL: ") + what)
    if not ok:
        fails.append(what)


# --- 1. the pre-adoption corpus is untouched --------------------------------------------
OLD = """
@LAT92LON4 | created:0 | updated:0 | relates:derived_from@LAT97LON18,senses@LAT0LON0

**OUTCOME** t_ms:120000 stream:0xe334a7e1 wall:0

---

@LAT97LON18 | created:0 | updated:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:120000 stream:0xe334a7e1 wall:0
"""
check(c.header_sid("@LAT97LON1 | created:0 | updated:0") is None,
      "a pre-adoption header reports no sid")
check(c.CITATION_RE.findall("relates:derived_from@LAT97LON18,senses@LAT0LON0")
      == [("derived_from", "97", "18", ""), ("senses", "0", "0", "")],
      "pre-adoption citations parse with an empty sid group")
check(c.stale_citations(OLD) == [],
      "a file with no boundaries and no sids reports nothing (not a crash)")

# --- 2. the needle-collision guard -------------------------------------------------------
check(c.header_sid("@LAT97LON1 | sid:a1b2c3d4 | created:0") == 0xa1b2c3d4,
      "a header sid is read")
check(c.header_sid("@LAT97LON1 | prev_sid:deadbeef | created:0") is None,
      "`prev_sid:` is NOT read as `sid:` -- the trap `prev_stream:` set for @LAT90")
check(c.header_sid("@LAT100LON4 | created:0\n\n**LANE-PRUNED** carried sid:deadbeef\n")
      is None,
      "a body's `sid:` is not the record's identity")
check(c.header_sid("@LAT97LON1 | sid:A1B2C3D4 | created:0") is None,
      "uppercase is refused rather than normalised (as sid::parse does)")

# --- 3. the capability: resolved from the file, no boundary ------------------------------
FRESH = """
@LAT92LON0 | created:0 | relates:derived_from@LAT97LON1#a1b2c3d4

**OUTCOME** t_ms:1000 stream:0xe334a7e1 wall:0

---

@LAT97LON1 | sid:a1b2c3d4 | created:0 | relates:observes@LAT0LON0

**LINKWIN** t_ms:1000 stream:0xe334a7e1 wall:0
"""
check(c.stale_citations(FRESH) == [],
      "a matching sid is FRESH and reports nothing")

STALE = FRESH.replace("sid:a1b2c3d4 | created:0 | relates:observes",
                      "sid:99887766 | created:0 | relates:observes")
st = c.stale_citations(STALE)
check(len(st) == 1 and st[0]["verdict"] == "stale" and st[0]["by"] == "sid",
      "a reclaimed slot is STALE, decided by sid")
check(st[0]["cited_sid"] == 0xa1b2c3d4 and st[0]["found_sid"] == 0x99887766,
      "and the report carries both ids so a reader can see the substitution")
check(st[0]["gen"] is None and st[0]["boundary"] is None,
      "with NO generation and NO boundary -- none was needed")
check("@LAT100" not in STALE,
      "...and the file contains no @LAT100 record at all, which is the point")

# --- 4. "I cannot check this" is its own answer ------------------------------------------
NOSID_TARGET = FRESH.replace("@LAT97LON1 | sid:a1b2c3d4 |", "@LAT97LON1 |")
check(c.stale_citations(NOSID_TARGET) == [],
      "a sid-bearing citation against a sid-less target reports NOTHING, "
      "never 'stale' -- unverifiable must not render as broken")

CROSS = """
@LAT92LON0 | created:0 | relates:derived_from@LAT97LON1#a1b2c3d4

**OUTCOME** t_ms:1000 stream:0xe334a7e1 wall:0
"""
check(c.stale_citations(CROSS) == [],
      "a citation whose target is not in this file is unverifiable, not stale")

# --- 5. the boundary path still works, and is labelled -----------------------------------
BOUNDARY = """
@LAT92LON0 | created:0 | relates:derived_from@LAT97LON1

**OUTCOME** t_ms:1000 stream:0xe334a7e1 wall:0

---

@LAT100LON0 | created:0 | relates:bounds@LAT0LON0

**LANE-PRUNED** lane:97 gen:0 removed:48 last_lon:47 t_ms:5000 stream:0xe334a7e1 wall:0
"""
b = c.stale_citations(BOUNDARY)
check(len(b) == 1 and b[0]["by"] == "boundary",
      "a sid-less citation still resolves the old way, and says which way it was")

print()
print(("all citation (laptop) tests passed" if not fails
       else f"{len(fails)} FAILURE(S)"))
sys.exit(1 if fails else 0)
