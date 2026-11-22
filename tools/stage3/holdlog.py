#!/usr/bin/env python3
"""holdlog.py — hold a node's serial port and write it LINE BY LINE, flushed.

docs/design/rfc0011-stage3.md §11 D10. Replaces scratchpad/catchboot.py for long holds: that
script buffers every byte until it exits, so a live watch on its output sees nothing (runs
1 and 2), and a held window that ends in a crash loses everything.

    python tools/stage3/holdlog.py COM14 2400 --reset > run.log   # reset, catch setup()
    python tools/stage3/holdlog.py COM14 780          >> run.log  # NO reset (between pulls)

--reset: hard-reset through esptool, then re-open the instant the port re-enumerates (an
RTS pulse through the open handle loses setup() on native USB — CLAUDE.md).
Without it the port is opened with DTR/RTS deasserted (fleet.open_serial_no_reset's shape),
so the node keeps running and its rotation and RAM state are not disturbed.
Each line is prefixed with seconds since the hold began, so a gap is visible.
"""
import argparse
import subprocess
import sys
import time

import serial
import serial.tools.list_ports as lp


def open_port(port, reset):
    if reset:
        subprocess.run([sys.executable, "-m", "esptool", "--chip", "esp32s3", "--port", port,
                        "--after", "hard-reset", "chip-id"], capture_output=True, text=True,
                       timeout=60)
        t0 = time.time()
        while time.time() - t0 < 12:
            if any(p.device == port for p in lp.comports()):
                try:
                    s = serial.Serial()
                    s.port, s.baudrate, s.timeout = port, 115200, 0.2
                    s.dtr, s.rts = True, False
                    s.open()
                    print("# re-attached after %.2fs" % (time.time() - t0), flush=True)
                    return s
                except Exception:
                    pass
            time.sleep(0.05)
        return None
    s = serial.Serial()
    s.port, s.baudrate, s.timeout = port, 115200, 0.2
    s.dtr, s.rts = False, False       # deassert BEFORE open: no native-USB reset
    s.open()
    print("# opened without reset", flush=True)
    return s


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("port")
    ap.add_argument("secs", type=float)
    ap.add_argument("--reset", action="store_true")
    a = ap.parse_args()
    s = open_port(a.port, a.reset)
    if s is None:
        print("# port never came back", flush=True)
        return 1
    t0 = time.time()
    end = t0 + a.secs
    pend = b""
    out = sys.stdout.buffer
    while time.time() < end:
        try:
            pend += s.read(4096)
        except serial.SerialException as e:   # a reset/re-enumeration mid-hold: say so
            print("# SERIAL LOST at %.1fs: %s" % (time.time() - t0, e), flush=True)
            return 2
        while b"\n" in pend:
            line, pend = pend.split(b"\n", 1)
            out.write(b"%8.1f " % (time.time() - t0) + line.rstrip(b"\r") + b"\n")
            out.flush()
    if pend:
        out.write(b"%8.1f " % (time.time() - t0) + pend + b"\n")
    s.close()
    print("# held %.0fs" % a.secs, flush=True)
    return 0


if __name__ == "__main__":
    sys.exit(main())
