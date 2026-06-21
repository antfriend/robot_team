#!/usr/bin/env python3
"""radio_replay.py — over-the-air (src,seq) replay-drop test through the bridge.

Closes the dedup story that negchecks.py can't: dedup is radio-only, so a replay
over the trusted USB link is served by design. This sends a TTDB_REQ to a mesh
node THROUGH the V4-A bridge (laptop->USB->V4-A->ESP-NOW->target) and checks that
the radio-path dedup on the *target* drops a duplicate (src,seq):

  original   fresh (src,seq) request          -> target serves -> frames come back
  replay     identical (src,seq) over the air -> target drops   -> 0 frames
  fresh seq  (src,seq+1) request              -> served again   -> frames (dedup is per-key)

Run with the bridge tethered (its port) and the target powered in ESP-NOW range:
  python orchestrator/radio_replay.py --bridge-port COM6 --node k10_1
The target is NOT reset by opening the bridge's port, so a unique base seq is used
per invocation (a fixed seq would already be in the target's dedup set on re-run).
"""
import argparse
import struct
import sys
import time

import companion as C  # same directory


def count_data(ser, target, seconds):
    reader = C.SerialFrameReader()
    n = 0
    end = time.time() + seconds
    while time.time() < end:
        for fr in reader.feed(ser.read(256)):
            t = C.decode_toot(fr)
            if t and t["type"] == C.TTDB_DATA and t["src"] == target:
                n += 1
    return n


def req(target, seq):
    payload = bytes([C.TTDB_REQ_WHOLE]) + struct.pack("<I", target)
    return C.encode_toot(C.TTDB_REQ, C.ORCHESTRATOR_ID, seq, payload)


def run(port, baud, node, window, attempts):
    try:
        import serial
    except ImportError:
        sys.exit("pyserial not installed. Run: pip install -r requirements.txt")
    target = C.NODE_IDS[node]

    with serial.Serial(port, baud, timeout=0.1) as ser:
        time.sleep(2.5)              # bridge reboots on open; target keeps running
        for attempt in range(1, attempts + 1):
            seq = int(time.time()) & 0x7FFFFFFF
            ser.reset_input_buffer()
            C.write_serial_frame(ser, req(target, seq));      base = count_data(ser, target, window)
            time.sleep(0.3)
            ser.reset_input_buffer()
            C.write_serial_frame(ser, req(target, seq));      replay = count_data(ser, target, window)
            time.sleep(0.3)
            ser.reset_input_buffer()
            C.write_serial_frame(ser, req(target, seq + 1));  fresh = count_data(ser, target, window)

            print(f"attempt {attempt}: original seq={seq} -> {base:2d} frames | "
                  f"replay (same) -> {replay:2d} | fresh seq+1 -> {fresh:2d}")
            if base == 0:
                print("  (no reply to the original — request lost over the air; retrying)")
                time.sleep(0.5)
                continue
            ok = base > 0 and replay == 0 and fresh > 0
            print("\nRADIO-REPLAY DEDUP", "PASS" if ok else "FAIL",
                  "| over-the-air duplicate (src,seq) dropped by the target" if ok
                  else "| unexpected: replay should yield 0, fresh seq should serve")
            return 0 if ok else 1
    print("\nFAIL: never got a clean original reply (RF too lossy this run)")
    return 1


def main():
    ap = argparse.ArgumentParser(description="over-the-air replay-drop test via the bridge")
    ap.add_argument("--bridge-port", required=True, help="the bridge's serial port (e.g. COM6)")
    ap.add_argument("--baud", type=int, default=115200)
    ap.add_argument("--node", required=True, choices=list(C.NODE_IDS), help="mesh target")
    ap.add_argument("--window", type=float, default=3.0)
    ap.add_argument("--attempts", type=int, default=4)
    args = ap.parse_args()
    sys.exit(run(args.bridge_port, args.baud, args.node, args.window, args.attempts))


if __name__ == "__main__":
    main()
