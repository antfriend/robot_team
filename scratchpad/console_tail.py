"""Dump a node's raw console text for N seconds. Pure listener — sends nothing.

The framed toot link and the sketch's printf output share one UART, so this just strips
anything that isn't printable and prints the lines. Used to watch a node's OWN `[part]`
sequencer prints instead of polling a flag over the mesh: the print says `duet-harm` in
the node's own words, which is the mechanism rather than a report about it.

  python console_tail.py COM9 40 part duet
"""
import sys, time, serial

port, secs = sys.argv[1], float(sys.argv[2])
keys = [k.lower() for k in sys.argv[3:]]

with serial.Serial(port, 115200, timeout=0.1) as ser:
    t_end = time.time() + secs
    buf = b""
    while time.time() < t_end:
        buf += ser.read(4096)
        while b"\n" in buf:
            line, buf = buf.split(b"\n", 1)
            s = "".join(chr(c) for c in line if 32 <= c < 127).strip()
            if not s:
                continue
            if not keys or any(k in s.lower() for k in keys):
                print(f"{time.strftime('%H:%M:%S')}  {s}", flush=True)
