"""Passive gate watcher — holds ONE connection, sends nothing, resets nothing.

Written for timestream-handoff.md Part 1. Same discipline as tail.py (open without
DTR/RTS so it cannot reboot the node it is observing — [[looping-companion-py-resets-bridge]]),
but it also tees to a log file and pulls the lines that matter to the gate out into a
running summary, so a 30-minute walk does not have to be re-read by eye afterwards.

  python scratchpad/gate_watch.py COM14 1800 scratchpad/gate_card.log [reset]

Pass `reset` as a 4th arg to open WITH DTR, deliberately rebooting the node so the
capture starts at a known t=0. That is the opposite of the usual rule here and is only
right when the thing being measured happens AT BOOT — the Dream Cycle's first pass runs
on the first loop() iteration (`last_dream == 0`), so attaching a passive watcher after
an upload races it and usually loses. Default stays passive.
"""
import os
import re
import sys
import time

sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "orchestrator"))
import companion as c  # noqa: E402

port = sys.argv[1]
secs = float(sys.argv[2]) if len(sys.argv) > 2 else 600.0
logpath = sys.argv[3] if len(sys.argv) > 3 else None

# Lines the gate actually turns on. Everything else is still logged, just not echoed
# to the summary at the end.
KEY = re.compile(r"\[(dream|learn|motion|loop|link|stream)\]")

do_reset = len(sys.argv) > 4 and sys.argv[4] == "reset"
if do_reset:
    import serial  # noqa: E402
    ser = serial.Serial(port, 115200, timeout=0.1)   # DTR asserted -> S3 reboots
else:
    ser = c.open_serial_no_reset(port, 115200)
log = open(logpath, "w", encoding="utf-8") if logpath else None
buf = b""
start = time.time()
end = start + secs
keep = []
try:
    print("watching %s for %.0fs (passive, no reset)" % (port, secs), flush=True)
    while time.time() < end:
        data = ser.read(256)
        if not data:
            continue
        buf += data
        while b"\n" in buf:
            line, buf = buf.split(b"\n", 1)
            txt = line.decode("utf-8", "replace").rstrip("\r")
            if not txt:
                continue
            stamped = "%7.1fs | %s" % (time.time() - start, txt)
            if log:
                log.write(stamped + "\n")
                log.flush()
            if KEY.search(txt):
                keep.append(stamped)
                print(stamped, flush=True)
finally:
    ser.close()
    if log:
        log.close()

print("\n--- summary: %d key lines over %.0fs ---" % (len(keep), time.time() - start))
for k in keep:
    if "[dream]" in k or "TRANSITION" in k or "DROPPED" in k or "[loop]" in k:
        print(k)
