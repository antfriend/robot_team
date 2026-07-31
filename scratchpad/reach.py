"""One held connection, many probes — reachability without rebooting the bridge.

Every `companion.py ping` invocation opens the port with DTR/RTS asserted, which
resets the V4-A bridge. Looping it therefore power-cycles the bridge once per probe
and measures a node that has just rebooted. This opens ONCE, without the reset, and
probes each node several times over that single session.

  python scratchpad/reach.py COM6 [rounds]
"""
import os
import struct
import sys
import time

sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "orchestrator"))
import companion as c  # noqa: E402

port = sys.argv[1] if len(sys.argv) > 1 else "COM6"
rounds = int(sys.argv[2]) if len(sys.argv) > 2 else 3
nodes = sys.argv[3].split(",") if len(sys.argv) > 3 else [
    "v4a_bridge", "v4b_relay", "v4c_edge", "tdeck_1", "cardputer_1"]

reader = c.SerialFrameReader()
results = {n: [] for n in nodes}

ser = c.open_serial_no_reset(port, 115200)
try:
    time.sleep(1.0)          # brief drain only; the node is NOT rebooting here
    ser.reset_input_buffer()
    print("held one connection on %s (no DTR reset), %d rounds\n" % (port, rounds))
    for rnd in range(1, rounds + 1):
        for n in nodes:
            target = c.NODE_IDS[n]
            # Fresh seq per request so a non-reset target cannot dedup-drop it.
            seq = int(time.time() * 1000) & 0x7FFFFFFF
            payload = bytes([0]) + struct.pack("<I", target)
            frame = c.encode_toot(c.CMD, c.ORCHESTRATOR_ID, seq, payload,
                                  flags=c.FLAG_WANT_ACK)
            t0 = time.time()
            acked = c.send_reliable(ser, reader, frame, target, seq,
                                    rto0=0.5, attempts=4)
            dt = (time.time() - t0) * 1000.0
            results[n].append(acked)
            print("  round %d  %-12s %s (%.0f ms)"
                  % (rnd, n, ("ACK att %d" % acked) if acked else "NO ACK", dt))
        print("")
finally:
    ser.close()

print("summary over %d rounds, one held connection:" % rounds)
for n in nodes:
    got = [a for a in results[n] if a]
    print("  %-12s %d/%d reached%s"
          % (n, len(got), rounds,
             ("  attempts=" + ",".join(str(a) for a in got)) if got else ""))
