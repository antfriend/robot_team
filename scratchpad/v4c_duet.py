"""Put V4-C into a duet over its own USB link and watch its sequencer say what it played.

One connection does both jobs: the framed toot link and the sketch's printf output share the
UART, so this sends CMD_DUET on the same handle it reads console text from. That matters
because opening the port resets the node, and a duet is deliberately NOT persisted — so a
separate listener process would clear the very thing it came to watch.

Verifies the node's OWN `[part]` lines rather than a polled flag: the print names the phrase
and the step, which is the mechanism, not a report about it.

  python v4c_duet.py COM13 [seconds]
"""
import sys, time, struct

sys.path.insert(0, r"c:\git\robot_team\orchestrator")
import serial
import companion as c

DUET_HARM, DUET_OFF = 1, 0xFF
SPEED = 2

port = sys.argv[1]
secs = float(sys.argv[2]) if len(sys.argv) > 2 else 24.0
TARGET = c.NODE_IDS["v4c_edge"]
PARTNER = c.NODE_IDS["tdeck_1"]          # named on the wire; need not be present to test us


def send_duet(ser, role, speed):
    payload = (bytes([c.CMD_DUET]) + struct.pack("<I", TARGET) +
               struct.pack("<I", PARTNER) + bytes([role, speed]))
    seq = int(time.time() * 1000) & 0x7FFFFFFF
    c.write_serial_frame(ser, c.encode_toot(c.CMD, c.ORCHESTRATOR_ID, seq, payload))


def drain(ser, buf, keys=("duet", "part")):
    buf += ser.read(8192)
    while b"\n" in buf:
        line, buf = buf.split(b"\n", 1)
        s = "".join(chr(x) for x in line if 32 <= x < 127).strip()
        if s and any(k in s.lower() for k in keys):
            print(f"{time.strftime('%H:%M:%S')}  {s}", flush=True)
    return buf


with serial.Serial(port, 115200, timeout=0.1) as ser:
    time.sleep(8.0)                       # the reset this open causes
    ser.reset_input_buffer()
    buf = b""
    print(f"inviting v4c_edge to HARMONISE at speed x{SPEED} for {secs:.0f}s")
    # The band must be playing for nothing — a duet overrides the part outright — but the
    # invitation is re-asserted on the same 2 s cadence serviceDuet uses on the T-Deck.
    t_end = time.time() + secs
    last = 0.0
    while time.time() < t_end:
        if time.time() - last >= 2.0:
            send_duet(ser, DUET_HARM, SPEED)
            last = time.time()
        buf = drain(ser, buf)
        time.sleep(0.05)

    print("dismissing (3x)")
    for _ in range(3):
        send_duet(ser, DUET_OFF, 1)
        time.sleep(0.3)
        buf = drain(ser, buf)
    time.sleep(1.5)
    drain(ser, buf)
