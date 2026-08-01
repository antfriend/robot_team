"""Passive serial listener — sends NOTHING, resets nothing.

Used to watch one node's own prints while traffic is driven at it from another port.
Opens without DTR/RTS so it cannot reboot the node it is observing.

  python scratchpad/tail.py COM10 [seconds]
"""
import os
import sys
import time

sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "orchestrator"))
import companion as c  # noqa: E402

port = sys.argv[1]
secs = float(sys.argv[2]) if len(sys.argv) > 2 else 60.0

ser = c.open_serial_no_reset(port, 115200)
buf = b""
end = time.time() + secs
try:
    print("tailing %s for %.0fs (passive)" % (port, secs), flush=True)
    while time.time() < end:
        data = ser.read(256)
        if not data:
            continue
        buf += data
        while b"\n" in buf:
            line, buf = buf.split(b"\n", 1)
            txt = line.decode("utf-8", "replace").rstrip("\r")
            if txt:
                print("  %7.1fs | %s" % (secs - (end - time.time()), txt), flush=True)
finally:
    ser.close()
print("tail done")
