"""Reset a board and re-attach fast enough to catch setup().

On ESP32-S3 native USB a reset RE-ENUMERATES the device, so the handle you reset through
goes dead and setup()'s output is lost through it (proved on the T-Deck today). But the
Cardputer's setup() takes over six seconds (CLAUDE.md), and re-enumeration takes about
one -- so reset, then poll for the port to come back and open it immediately. We lose the
first second and catch the rest, which is where the TTDB lines live (they come after the
LittleFS mount, not before it).
"""
import subprocess
import sys
import time

import serial
import serial.tools.list_ports as lp

port = sys.argv[1]
secs = float(sys.argv[2]) if len(sys.argv) > 2 else 14.0

# Hard-reset through esptool, which drives the native-USB reset properly.
subprocess.run([sys.executable, "-m", "esptool", "--chip", "esp32s3", "--port", port,
                "--after", "hard-reset", "chip-id"],
               capture_output=True, text=True, timeout=60)

t0 = time.time()
s = None
while time.time() - t0 < 12:
    if any(p.device == port for p in lp.comports()):
        try:
            s = serial.Serial()
            s.port, s.baudrate, s.timeout = port, 115200, 0.2
            s.dtr = True
            s.rts = False
            s.open()
            break
        except Exception:
            s = None
    time.sleep(0.05)

if s is None:
    print("port never came back")
    sys.exit(1)

print("re-attached after %.2fs" % (time.time() - t0))
end = time.time() + secs
buf = b""
while time.time() < end:
    buf += s.read(4096)
s.close()
print(buf.decode("utf-8", errors="replace"))
