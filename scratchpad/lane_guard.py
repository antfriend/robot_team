"""Send CMD_CLEAR_PERCEPTS with a lane the node MUST refuse.

companion.py validates --lane client-side, so this bypasses it and puts the bad byte
straight on the wire — the point is to prove the guard is in the FIRMWARE, where it
protects @LAT0 identity, @LAT98 belief attestations and @LAT99 sync logs from a
malformed or hostile CMD. A refusal shows up as no ACK (the ACK is gated on success).

  python scratchpad/lane_guard.py COM6 v4a_bridge 99
"""
import os
import struct
import sys
import time

sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "orchestrator"))
import companion as c  # noqa: E402

port = sys.argv[1]
node = sys.argv[2]
lane = int(sys.argv[3])

target = c.NODE_IDS[node]
payload = bytes([c.CMD_CLEAR_PERCEPTS]) + struct.pack("<I", target) + bytes([lane])
seq = int(time.time() * 1000) & 0x7FFFFFFF
frame = c.encode_toot(c.CMD, c.ORCHESTRATOR_ID, seq, payload, flags=c.FLAG_WANT_ACK)
reader = c.SerialFrameReader()

ser = c.open_serial_no_reset(port, 115200)
try:
    time.sleep(1.0)
    ser.reset_input_buffer()
    print("sending clear-percepts lane=%d to %s (expect REFUSAL: no ACK)" % (lane, node))
    acked = c.send_reliable(ser, reader, frame, target, seq, rto0=0.5, attempts=3)
finally:
    ser.close()

if acked:
    print("\n!! FAIL: node ACKed lane %d — the guard did NOT hold" % lane)
    sys.exit(1)
print("\nPASS: no ACK — node refused lane %d, as it must" % lane)
