"""Phase S0 hardware test: one held connection to the Cardputer, beeps over the USB link
for the first `beep_s` seconds, then silence (clap then), printing every [acoustic] window.

Done when (docs/design/cardputer-sensorium.md §7 S0): windows that hold only beeps report
`transients 0` with `self_blocks > 0`, and a window with claps reports `transients > 0`.

  python scratchpad/s0_beep_test.py COM14 [total_s] [beep_s]
"""
import os
import struct
import sys
import time

sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "orchestrator"))
import fleet as c  # noqa: E402

port = sys.argv[1] if len(sys.argv) > 1 else "COM14"
total = float(sys.argv[2]) if len(sys.argv) > 2 else 360.0
beep_s = float(sys.argv[3]) if len(sys.argv) > 3 else 150.0
target = c.NODE_IDS[os.environ.get("NODE", "cardputer_1")]

ser = c.open_serial_no_reset(port, 115200)
t0 = time.time()
next_beep = t0 + 20.0                     # let a boot (if the open reset it) settle first
buf = b""
beeps = 0
try:
    print("held %s; beeping every 5 s until +%.0fs, then SILENT (clap then), until +%.0fs"
          % (port, beep_s, total), flush=True)
    while time.time() - t0 < total:
        now = time.time()
        if now >= next_beep and now - t0 < beep_s:
            seq = int(now * 1000) & 0x7FFFFFFF
            payload = bytes([c.CMD_BEEP]) + struct.pack("<I", target) + struct.pack("<HH", 880, 200)
            c.write_serial_frame(ser, c.encode_toot(c.CMD, c.ORCHESTRATOR_ID, seq, payload))
            beeps += 1
            next_beep = now + float(os.environ.get("BEEP_EVERY", "5"))
        data = ser.read(512)
        if not data:
            continue
        buf += data
        while b"\n" in buf:
            line, buf = buf.split(b"\n", 1)
            txt = line.decode("utf-8", "replace").strip()
            if "[acoustic]" in txt or "online" in txt:
                phase = "BEEP" if time.time() - t0 < beep_s else "quiet/clap"
                print("  %6.1fs [%s, %d beeps sent] %s" % (time.time() - t0, phase, beeps,
                                                          txt[txt.find("["):]), flush=True)
finally:
    ser.close()
print("done")
