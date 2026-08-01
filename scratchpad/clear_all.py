"""Clear every node's percept lanes over ONE held connection.

Five `companion.py cmd` invocations would reset the bridge five times and probe a
node that just rebooted (companion.md §6, 2026-07-31). This opens once without the
DTR reset and sends all five clears over that session.

Lane 0 = every percept lane 94..97. Nodes refuse anything outside that range, so
identity / belief / sync records are never at risk.

  python scratchpad/clear_all.py COM6 [attempts]
"""
import os
import struct
import sys
import time

sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "orchestrator"))
import companion as c  # noqa: E402

port = sys.argv[1] if len(sys.argv) > 1 else "COM6"
attempts = int(sys.argv[2]) if len(sys.argv) > 2 else 6
nodes = ["v4a_bridge", "v4b_relay", "v4c_edge", "tdeck_1", "cardputer_1"]

reader = c.SerialFrameReader()
ser = c.open_serial_no_reset(port, 115200)
results = {}
try:
    time.sleep(1.0)
    ser.reset_input_buffer()
    print("clearing all percept lanes (94-97) on %d nodes via %s\n" % (len(nodes), port))
    for n in nodes:
        target = c.NODE_IDS[n]
        payload = (bytes([c.CMD_CLEAR_PERCEPTS])
                   + struct.pack("<I", target) + bytes([0]))
        seq = int(time.time() * 1000) & 0x7FFFFFFF
        frame = c.encode_toot(c.CMD, c.ORCHESTRATOR_ID, seq, payload,
                              flags=c.FLAG_WANT_ACK)
        acked = c.send_reliable(ser, reader, frame, target, seq,
                                rto0=0.5, attempts=attempts)
        results[n] = acked
        print("  %-12s %s" % (n, ("cleared (ACK attempt %d)" % acked) if acked
                              else "NO ACK — NOT cleared"))
finally:
    ser.close()

missing = [n for n, a in results.items() if not a]
print("\n%d/%d cleared" % (len(nodes) - len(missing), len(nodes)))
if missing:
    print("!! not cleared: %s — re-run before collecting, or their lanes still"
          " hold pre-move evidence" % ", ".join(missing))
    sys.exit(1)
print("all lanes empty — dwell before collecting so every node refills in place")
