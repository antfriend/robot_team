#!/usr/bin/env python3
"""negchecks.py — on-device authentication/replay negative tests for a node.

Proves the K10's toot security floor over USB-CDC (PLAN.md Phase 1 "done when"):
  baseline  a valid TTDB_REQ streams TTDB_DATA frames back     -> expect >0
  wrong-key a TTDB_REQ signed with the wrong key is ignored    -> expect 0 (HMAC reject)
  tampered  a valid frame with one payload byte flipped post-sign -> expect 0 (HMAC reject)
  replay    a second identical (src,seq) request over USB       -> expect >0 (SERVED)

Dedup policy is RADIO-ONLY: (src,seq) dedup guards the ESP-NOW/LoRa path against
replay attacks and mesh forwarding loops, but the trusted USB-CDC link is NOT
deduped so the laptop can retry a lost request. So a replayed request over serial
is served by design — radio-path replay rejection must be tested by injecting a
duplicate over ESP-NOW from a second node (TODO, Phase 1b). This script therefore
gates only on the auth checks (baseline + wrong-key + tampered).

Usage:
  python orchestrator/negchecks.py --port COM3 --node k10_1
Requires: pyserial, and firmware flashed with FQBN suffix CDCOnBoot=cdc (see CLAUDE.md).
"""
import argparse
import hashlib
import hmac
import struct
import sys
import time

import companion as C  # same directory


def hmac_with(key, data):
    return hmac.new(key, data, hashlib.sha256).digest()[:C.HMAC_LEN]


def make_req(target, seq, key, tamper=False):
    """A whole-file TTDB_REQ, signed with `key`; optionally corrupt the body."""
    payload = bytes([C.TTDB_REQ_WHOLE]) + struct.pack("<I", target)
    header = (C.MAGIC + bytes([C.VERSION, C.TTDB_REQ])
              + struct.pack("<I", C.ORCHESTRATOR_ID) + struct.pack("<I", seq)
              + bytes([0, 1]) + b"\x00" * C.LOCUS_LEN
              + bytes([4, 0, len(payload)]) + payload)
    frame = header + hmac_with(key, header)
    if tamper:
        b = bytearray(frame)
        b[C.HEADER_LEN] ^= 0xFF      # flip first payload byte AFTER signing
        frame = bytes(b)
    return frame


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


def send(ser, frame):
    ser.reset_input_buffer()
    C.write_serial_frame(ser, frame)


def run(port, baud, node, window):
    try:
        import serial
    except ImportError:
        sys.exit("pyserial not installed. Run: pip install -r requirements.txt")
    target = C.NODE_IDS[node]
    good = C.NETWORK_KEY
    bad = bytes([b ^ 0xFF for b in C.NETWORK_KEY])

    with serial.Serial(port, baud, timeout=0.1) as ser:
        time.sleep(2.5)              # node reboots on open; wait out its boot
        ser.reset_input_buffer()
        send(ser, make_req(target, 10, good));               base = count_data(ser, target, window)
        time.sleep(0.4)
        send(ser, make_req(target, 11, bad));                wrong = count_data(ser, target, window)
        time.sleep(0.4)
        send(ser, make_req(target, 12, good, tamper=True));  tamper = count_data(ser, target, window)
        time.sleep(0.4)
        send(ser, make_req(target, 20, good));               rep1 = count_data(ser, target, window)
        time.sleep(0.4)
        send(ser, make_req(target, 20, good));               rep2 = count_data(ser, target, window)

    ok = lambda b: "PASS" if b else "FAIL"
    print(f"baseline (valid, seq10)      : {base:3d} frames   {ok(base > 0)} (expect >0)")
    print(f"wrong-key  (seq11, bad HMAC) : {wrong:3d} frames   {ok(wrong == 0)} (expect 0, HMAC reject)")
    print(f"tampered   (seq12, bad HMAC) : {tamper:3d} frames   {ok(tamper == 0)} (expect 0, HMAC reject)")
    print(f"replay 1st (seq20, valid)    : {rep1:3d} frames   {ok(rep1 > 0)} (expect >0)")
    print(f"replay 2nd (seq20, dup)      : {rep2:3d} frames   {ok(rep2 > 0)} (expect >0, served: radio-only dedup)")
    auth_ok = base > 0 and wrong == 0 and tamper == 0
    print("\nAUTH CHECKS (gate)", "PASS" if auth_ok else "FAIL",
          "| serial replay served by design; radio-replay test pending a 2nd node")
    return 0 if auth_ok else 1


def main():
    ap = argparse.ArgumentParser(description="toot HMAC/replay negative checks")
    ap.add_argument("--port", required=True, help="serial port (COM3, /dev/ttyACM0)")
    ap.add_argument("--baud", type=int, default=115200)
    ap.add_argument("--node", required=True, choices=list(C.NODE_IDS))
    ap.add_argument("--window", type=float, default=3.0, help="listen seconds per sub-test")
    args = ap.parse_args()
    sys.exit(run(args.port, args.baud, args.node, args.window))


if __name__ == "__main__":
    main()
