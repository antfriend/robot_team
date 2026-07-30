"""Put V4-A and V4-B into a duet from the laptop and read back whether they SANG.

Drives the same CMD_DUET the T-Deck's `d` key sends, through the V4-A bridge: V4-A leads
(kOdeLead), V4-B harmonises (kOdeHarm), double time. The invitation is RE-ASSERTED every
2 s exactly as serviceDuet does on the T-Deck — a single ESP-NOW CMD_DUET gets dropped
(companion.md §6), and this test is worthless if it can't tell "the V4 ignored the ask"
from "the ask never arrived".

Confirmation is the partner's own INTERO_VOICING bit, never an ACK: a blocking tone call
eats the ACK window (@LAT90LON70).

  python v4_duet.py COM6 [seconds]
"""
import sys, os, time, struct

sys.path.insert(0, r"c:\git\robot_team\orchestrator")
import serial
import companion as c

DUET_LEAD, DUET_HARM, DUET_OFF = 0, 1, 0xFF
SPEED = 2

port = sys.argv[1]
secs = float(sys.argv[2]) if len(sys.argv) > 2 else 24.0
A, B = c.NODE_IDS["v4a_bridge"], c.NODE_IDS["v4b_relay"]
reader = c.SerialFrameReader()


def send_duet(ser, target, partner, role, speed):
    payload = (bytes([c.CMD_DUET]) + struct.pack("<I", target) +
               struct.pack("<I", partner) + bytes([role, speed]))
    seq = int(time.time() * 1000) & 0x7FFFFFFF
    c.write_serial_frame(ser, c.encode_toot(c.CMD, c.ORCHESTRATOR_ID, seq, payload))


with serial.Serial(port, 115200, timeout=0.1) as ser:
    time.sleep(8.0)                       # the reset this open causes on the bridge
    ser.reset_input_buffer()

    print(f"duet: V4-A leads, V4-B harmonises, speed x{SPEED}, {secs:.0f}s")
    t_end = time.time() + secs
    n = 0
    while time.time() < t_end:
        send_duet(ser, A, B, DUET_LEAD, SPEED)
        time.sleep(0.15)
        send_duet(ser, B, A, DUET_HARM, SPEED)
        n += 1
        # Read both bodies mid-duet. VOICING is the STATE that would sound a note, so this
        # cannot fall between two notes and read false.
        time.sleep(1.0)
        for name, nid in (("V4-A", A), ("V4-B", B)):
            b = c.intero_probe(ser, reader, nid, probes=2)
            v = "?" if b is None else b["voicing"]
            print(f"  t+{n*2:2d}s  {name} voicing={v}", flush=True)
        time.sleep(0.7)

    print("dismissing (3x, a dropped OFF would leave them singing forever)")
    for _ in range(3):
        send_duet(ser, A, B, DUET_OFF, 1)
        time.sleep(0.15)
        send_duet(ser, B, A, DUET_OFF, 1)
        time.sleep(0.4)
    time.sleep(1.0)
    for name, nid in (("V4-A", A), ("V4-B", B)):
        b = c.intero_probe(ser, reader, nid, probes=3)
        print(f"  after OFF  {name} voicing={'?' if b is None else b['voicing']}")
