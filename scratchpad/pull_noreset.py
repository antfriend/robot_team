"""Bridged pull WITHOUT the DTR/RTS reset, to isolate why collect.py gets no data.

reach.py (pings) and clear_all.py (CMDs) both work over the bridge and both open with
open_serial_no_reset. collect.py's pulls open with the stock DTR reset and get nothing
from any bridged node. This runs the same pull over a non-resetting open so the two
differ in exactly one thing.

  python scratchpad/pull_noreset.py COM6 v4b_relay [out.md]
"""
import os
import sys
import time

sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "orchestrator"))
import companion as c  # noqa: E402

port, node = sys.argv[1], sys.argv[2]
out = sys.argv[3] if len(sys.argv) > 3 else "scratchpad/%s_noreset.md" % node

reader = c.SerialFrameReader()
ser = c.open_serial_no_reset(port, 115200)
try:
    time.sleep(1.0)
    ser.reset_input_buffer()
    print("bridged pull of %s via %s, NO reset on open" % (node, port))
    t0 = time.time()
    data = c.request_ttdb(ser, reader, c.NODE_IDS[node])
finally:
    ser.close()

if data is None:
    print("no data — the reset is NOT the discriminator")
    sys.exit(1)
open(out, "wb").write(data)
print("got %d bytes in %.1fs -> %s" % (len(data), time.time() - t0, out))
