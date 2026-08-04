#!/usr/bin/env python3
"""test_motion_py.py -- verify companion.py's reader for the CHANGE-TRIGGERED @LAT95
motion lane (part-b-handoff.md Part 1, landed 2026-08-04) without hardware.

The one thing this file exists to stop: **counting records and calling them windows.**
Since the lane suppresses windows whose verdict matches the run in progress, a record
count under-reports observation -- and it under-reports it precisely on the windows where
nothing happened, i.e. in the flattering direction for any claim about how still a node
was. The B.3 measurement that derived MOTIONPERCEPT_MOVING_MG was computed by reading 48
windows off a lane; the same script run against a compressed lane would have read 2.

Mirrors the record format pinned by tests/test_motionpercept.cpp.

Run: python tests/test_motion_py.py
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


STREAM = 0xE7384824

# A @LAT95 lane exactly as MotionPercept::buildRecord emits it: a run opener, a record
# closing a 9-window still run with a verdict change, and a heartbeat.
LANE = f"""```mmpdb
db_id: card-1
```

---

@LAT0LON0 | created:0 | updated:0 | relates:senses@LAT0LON0

**SELF** node:0x300

---

@LAT95LON0 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:1000000 stream:0x{STREAM:08x} wall:0 window_ms:60000 n:60
**MOTION** state:still moving_permille:0 dev_mean_mg:8 dev_max_mg:12 moving_ms:0
**RUN** windows_since_last:1 reason:first max_run:30

---

@LAT95LON1 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:1600000 stream:0x{STREAM:08x} wall:0 window_ms:60000 n:60
**MOTION** state:moving moving_permille:1000 dev_mean_mg:400 dev_max_mg:820 moving_ms:60000
**RUN** windows_since_last:10 reason:changed max_run:30
**COVERED** state:still windows:9 n:540 window_ms:540000 moving_permille:0 dev_mean_mg:8 dev_max_mg:20 moving_ms:0 first_t_ms:1060000 last_t_ms:1540000 covered_by:@LAT95LON0

---

@LAT95LON2 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:3400000 stream:0x{STREAM:08x} wall:0 window_ms:60000 n:60
**MOTION** state:moving moving_permille:1000 dev_mean_mg:410 dev_max_mg:900 moving_ms:60000
**RUN** windows_since_last:30 reason:heartbeat max_run:30
**COVERED** state:moving windows:29 n:1740 window_ms:1740000 moving_permille:1000 dev_mean_mg:405 dev_max_mg:950 moving_ms:1740000 first_t_ms:1660000 last_t_ms:3340000
"""

recs = c.parse_motion_percepts(LANE)

# 1) The lane parses, and only @LAT95 records land in it.
check(len(recs) == 3, f"three @LAT95 records parsed (got {len(recs)})")
check([r["lane"] for r in recs] == [0, 1, 2], "in lane order")
check(recs[0]["state"] == "still" and recs[1]["state"] == "moving",
      "verdicts read off the **MOTION** line")
check(recs[0]["stream"] == STREAM and recs[0]["wall"] == 0,
      "the stamp is read by the shared parse_time_fields, stream id and all")

# 2) THE RUN FIELDS -- the whole point.
check(recs[0]["reason"] == "first" and recs[0]["windows_since_last"] == 1,
      "the opener claims one window and says why it was written")
check(recs[0]["covered"] is None, "and carries no covered block")
check(recs[1]["reason"] == "changed" and recs[1]["windows_since_last"] == 10,
      "the closing record claims ten windows")
check(recs[1]["covered"]["windows"] == 9 and recs[1]["covered"]["state"] == "still",
      "nine of which are the covered STILL run, not this record's `moving` verdict")
check(recs[2]["reason"] == "heartbeat",
      "and an unchanged state is re-asserted by the heartbeat, not by a change")

# 3) THE ARITHMETIC. 1 + (1+9) + (1+29) = 41 windows across 3 records.
t = c.motion_totals(recs)
check(t["records"] == 3, f"three records (got {t['records']})")
check(t["windows"] == 41,
      f"but FORTY-ONE windows -- counting records would under-report by 38 "
      f"(got {t['windows']})")
check(t["still_windows"] == 10 and t["moving_windows"] == 31,
      f"split 10 still / 31 moving (got {t['still_windows']}/{t['moving_windows']})")
check(t["samples"] == 60 + 60 + 540 + 60 + 1740,
      f"every sample accounted for (got {t['samples']})")
check(t["window_ms"] == 60000 + 60000 + 540000 + 60000 + 1740000,
      f"and every millisecond observed (got {t['window_ms']})")
check(t["unaccounted"] == 0, "the lane accounts for its own arithmetic exactly")

# 4) A LANE THAT DOES NOT ADD UP SAYS SO. A record claiming windows_since_last:10 with
# no **COVERED** block means its predecessor's closer was lost -- to a full lane, a
# failed render, or a prune that took one record of the pair. Absorbing that silently
# would let the reader invent 9 windows it has no evidence for.
BROKEN = LANE.replace(
    "**COVERED** state:still windows:9 n:540 window_ms:540000 moving_permille:0 "
    "dev_mean_mg:8 dev_max_mg:20 moving_ms:0 first_t_ms:1060000 last_t_ms:1540000 "
    "covered_by:@LAT95LON0\n", "")
bt = c.motion_totals(c.parse_motion_percepts(BROKEN))
check(bt["unaccounted"] == 9,
      f"a **RUN** line claiming windows no **COVERED** block explains is REPORTED "
      f"(got {bt['unaccounted']})")
check(bt["windows"] == 32,
      f"and the missing windows are not invented to make the sum work "
      f"(got {bt['windows']})")

# 5) BOTH FORMATS ARE LIVE. A node's TTDB is appended to for its whole life, so
# pre-2026-08-04 records -- which have no **RUN** line at all -- sit on the same flash as
# post-. An old record is exactly one window, which is the default, so the old lane
# folds into the new arithmetic with no special case. Dropping that default would make
# every legacy record count as zero windows.
LEGACY = f"""```mmpdb
db_id: card-1
```

---

@LAT95LON0 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:1000000 stream:0x{STREAM:08x} wall:0 window_ms:60000 n:60
**MOTION** state:still moving_permille:0 dev_mean_mg:8 dev_max_mg:12 moving_ms:0

---

@LAT95LON1 | created:0 | updated:0 | relates:senses@LAT0LON0

**MOTIONWIN** t_ms:1060000 stream:0x{STREAM:08x} wall:0 window_ms:60000 n:60
**MOTION** state:still moving_permille:0 dev_mean_mg:8 dev_max_mg:11 moving_ms:0
"""
lrecs = c.parse_motion_percepts(LEGACY)
lt = c.motion_totals(lrecs)
check(len(lrecs) == 2 and lt["windows"] == 2,
      f"a pre-run-length record is exactly one window (got {lt['windows']})")
check(all(r["reason"] == "legacy" for r in lrecs),
      "and is labelled `legacy` rather than guessed at")
check(lt["unaccounted"] == 0, "with nothing left unaccounted for")

# 6) An empty / motion-less TTDB yields no records and no crash.
check(c.parse_motion_percepts("# nothing\n") == [], "no @LAT95 -> empty list")
check(c.motion_totals([])["windows"] == 0, "and no windows")

# ---------------------------------------------------------------------------
print()
if fails:
    print(f"{fails} FAILED")
    sys.exit(1)
print("all motion-percept checks passed")
