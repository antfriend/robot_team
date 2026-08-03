"""Reset a node with an RTS-only pulse and print its boot banner.

⚠ Asserting DTR *and* RTS together is esptool's bootloader-entry sequence (RTS->EN,
DTR->GPIO0) and drops an ESP32-S3 into silent DOWNLOAD mode. RTS alone is a reset.

  python scratchpad/banner.py COM6 [seconds]
"""
import os
import sys
import time

sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "orchestrator"))
import companion as c  # noqa: E402

port = sys.argv[1]
secs = float(sys.argv[2]) if len(sys.argv) > 2 else 12.0

# On S3 native USB, DTR does double duty: asserting it resets the board AND is what
# makes the CDC host readable at all (deasserted, the port reads back NOTHING — a
# passive tail on these V4s returns zero bytes, which looks exactly like a dead node).
# It must be asserted at OPEN, not after: setting it on a live handle resets the board
# into a re-enumeration that invalidates the handle, silently.
# RTS must stay FALSE — DTR+RTS together is esptool's DOWNLOAD-mode sequence.
import serial  # noqa: E402  (pyserial)

ser = serial.Serial(port, 115200, timeout=0.1)   # same open companion.py's readers use
try:
    ser.reset_input_buffer()
    buf = b""
    end = time.time() + secs
    print("banner %s (%.0fs)" % (port, secs), flush=True)
    while time.time() < end:
        data = ser.read(256)
        if not data:
            continue
        buf += data
        while b"\n" in buf:
            line, buf = buf.split(b"\n", 1)
            txt = line.decode("utf-8", "replace").rstrip("\r")
            if txt:
                print("  %5.1fs | %s" % (secs - (end - time.time()), txt), flush=True)
finally:
    ser.close()
