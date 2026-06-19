#!/usr/bin/env python3
"""companion.py — laptop side of the robot_team orchestrator.

Pulls a node's TTDB over the network. Connect to a node directly over USB-CDC,
or to the V4-A bridge (which routes the request into the mesh and streams the
replies back). The wire format mirrors the firmware exactly:

  - toot frame: firmware/libraries/Toot/src/Toot.h
  - serial framing: 0xAB 0xCD <len_lo> <len_hi> <frame>  (TootSerialLink)
  - auth: truncated HMAC-SHA256 with NETWORK_KEY (== ROBOT_TEAM_KEY)

Usage:
  python companion.py pull --port COM5 --node k10_1 --out master/k10.md
  python companion.py pull --port /dev/ttyACM0 --node v4a_bridge --out master/v4a.md

Requires: pyserial  (pip install -r requirements.txt)
"""
import argparse
import hashlib
import hmac
import os
import struct
import sys
import time
# pyserial is imported lazily inside pull() so the wire codec stays testable
# without the dependency installed.

# Must byte-match RobotTeamConfig.h ROBOT_TEAM_KEY ("robot_team_key01").
NETWORK_KEY = bytes(
    [0x72, 0x6F, 0x62, 0x6F, 0x74, 0x5F, 0x74, 0x65,
     0x61, 0x6D, 0x5F, 0x6B, 0x65, 0x79, 0x30, 0x31])

MAGIC = b"\x54\x54"
VERSION = 1
HEADER_LEN = 33
HMAC_LEN = 8
LOCUS_LEN = 16
ORCHESTRATOR_ID = 0x00000001

# Mirror RobotTeamNodeId.
NODE_IDS = {
    "v4a_bridge": 0x00000010,
    "v4b_relay": 0x00000011,
    "v4c_edge": 0x00000012,
    "k10_1": 0x00000100,
    "k10_2": 0x00000101,
    "k10_3": 0x00000102,
}

# Toot types.
TTDB_REQ = 7
TTDB_DATA = 8
TTDB_REQ_WHOLE = 0


def hmac8(data: bytes) -> bytes:
    return hmac.new(NETWORK_KEY, data, hashlib.sha256).digest()[:HMAC_LEN]


def encode_toot(ttype, src, seq, payload, locus=b"\x00" * LOCUS_LEN,
                ttl=4, flags=0, chunk_idx=0, chunk_total=1) -> bytes:
    assert len(payload) <= 208
    header = (MAGIC + bytes([VERSION, ttype])
              + struct.pack("<I", src) + struct.pack("<I", seq)
              + bytes([chunk_idx, chunk_total]) + locus
              + bytes([ttl, flags, len(payload)]) + payload)
    return header + hmac8(header)


def decode_toot(frame: bytes):
    """Return a dict for a valid frame, else None."""
    if len(frame) < HEADER_LEN + HMAC_LEN:
        return None
    if frame[0:2] != MAGIC:
        return None
    body_len = frame[32]
    total = HEADER_LEN + body_len + HMAC_LEN
    if len(frame) < total:
        return None
    body_end = HEADER_LEN + body_len
    if hmac8(frame[:body_end]) != frame[body_end:body_end + HMAC_LEN]:
        return None
    return {
        "version": frame[2],
        "type": frame[3],
        "src": struct.unpack("<I", frame[4:8])[0],
        "seq": struct.unpack("<I", frame[8:12])[0],
        "payload": frame[HEADER_LEN:body_end],
    }


def write_serial_frame(ser, frame: bytes):
    ser.write(b"\xAB\xCD" + struct.pack("<H", len(frame)) + frame)
    ser.flush()


class SerialFrameReader:
    """State machine matching firmware TootSerialLink.poll()."""

    def __init__(self):
        self.st = 0
        self.need = 0
        self.buf = bytearray()

    def feed(self, data: bytes):
        frames = []
        for c in data:
            if self.st == 0:
                self.st = 1 if c == 0xAB else 0
            elif self.st == 1:
                self.st = 2 if c == 0xCD else 0
            elif self.st == 2:
                self.need = c
                self.st = 3
            elif self.st == 3:
                self.need |= c << 8
                self.buf = bytearray()
                self.st = 4 if 0 < self.need <= 512 else 0
            elif self.st == 4:
                self.buf.append(c)
                if len(self.buf) >= self.need:
                    frames.append(bytes(self.buf))
                    self.st = 0
        return frames


def pull(port, baud, node, out_path, timeout):
    try:
        import serial  # pyserial
    except ImportError:
        sys.exit("pyserial not installed. Run: pip install -r requirements.txt")
    if node not in NODE_IDS:
        sys.exit(f"unknown node '{node}'. choices: {', '.join(NODE_IDS)}")
    target = NODE_IDS[node]

    req_payload = bytes([TTDB_REQ_WHOLE]) + struct.pack("<I", target)
    req = encode_toot(TTDB_REQ, ORCHESTRATOR_ID, 1, req_payload)

    slices = {}            # offset -> bytes
    eof_offset = None
    reader = SerialFrameReader()

    with serial.Serial(port, baud, timeout=0.1) as ser:
        time.sleep(0.3)    # let the USB-CDC link settle
        write_serial_frame(ser, req)
        print(f"requested whole TTDB from {node} (0x{target:08X}) on {port}")

        deadline = time.time() + timeout
        last_rx = time.time()
        while time.time() < deadline:
            chunk = ser.read(256)
            if chunk:
                last_rx = time.time()
                for frame in reader.feed(chunk):
                    t = decode_toot(frame)
                    if not t or t["type"] != TTDB_DATA or t["src"] != target:
                        continue
                    p = t["payload"]
                    if len(p) < 6:
                        continue
                    off = struct.unpack("<I", p[0:4])[0]
                    n = struct.unpack("<H", p[4:6])[0]
                    if n == 0:
                        eof_offset = off       # EOF marker
                    else:
                        slices[off] = p[6:6 + n]
            if eof_offset is not None:
                break
            if time.time() - last_rx > 3.0:
                print("warning: 3s without data; the node may not have replied")
                break

    if not slices and eof_offset is None:
        sys.exit("no TTDB data received (check port, node id, and the key)")

    data = reassemble(slices, eof_offset)
    os.makedirs(os.path.dirname(os.path.abspath(out_path)), exist_ok=True)
    with open(out_path, "wb") as f:
        f.write(data)
    print(f"wrote {len(data)} bytes to {out_path}")


def reassemble(slices, eof_offset):
    end = eof_offset if eof_offset is not None else (
        max(off + len(b) for off, b in slices.items()) if slices else 0)
    out = bytearray(end)
    for off, b in slices.items():
        out[off:off + len(b)] = b
    return bytes(out)


def main():
    ap = argparse.ArgumentParser(description="robot_team orchestrator companion")
    sub = ap.add_subparsers(dest="cmd", required=True)
    p = sub.add_parser("pull", help="pull a node's TTDB over the link")
    p.add_argument("--port", required=True, help="serial port (COM5, /dev/ttyACM0)")
    p.add_argument("--baud", type=int, default=115200)
    p.add_argument("--node", required=True, choices=list(NODE_IDS))
    p.add_argument("--out", required=True, help="output .md path")
    p.add_argument("--timeout", type=float, default=20.0)
    args = ap.parse_args()

    if args.cmd == "pull":
        pull(args.port, args.baud, args.node, args.out, args.timeout)


if __name__ == "__main__":
    main()
