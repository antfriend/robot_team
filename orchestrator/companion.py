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
MAX_BODY = 208                      # body bytes per toot (Toot.h MAX_BODY)
REASSEMBLY_MAX_CHUNKS = 8           # firmware TOOT_REASSEMBLY_MAX_CHUNKS cap
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
BELIEF = 3
CMD = 4
ACK = 5
TTDB_REQ = 7
TTDB_DATA = 8
TTDB_REQ_WHOLE = 0

# Flags (Toot.h Flags).
FLAG_WANT_ACK = 1 << 0

# ACK payload (TTN-RFC-0007 §3): ack_src u32 | ack_seq u32 | ack_chunk u8 | status u8.
ACK_PAYLOAD_LEN = 10
ACK_ACCEPTED = 0
ACK_REASSEMBLY_PENDING = 1
ACK_DROPPED_NO_RESRC = 2


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
        "chunk_idx": frame[12],
        "chunk_total": frame[13],
        "flags": frame[31],
        "payload": frame[HEADER_LEN:body_end],
    }


def make_ack_payload(ack_src, ack_seq, ack_chunk=0, status=ACK_ACCEPTED) -> bytes:
    """Mirror firmware toot::makeAck payload layout (TTN-RFC-0007 §3)."""
    return struct.pack("<II", ack_src, ack_seq) + bytes([ack_chunk, status])


def parse_ack(t):
    """Read an ACK toot dict. Returns (ack_src, ack_seq, ack_chunk, status) or None."""
    if t["type"] != ACK:
        return None
    p = t["payload"]
    if len(p) < ACK_PAYLOAD_LEN:
        return None
    ack_src, ack_seq = struct.unpack("<II", p[0:8])
    return (ack_src, ack_seq, p[8], p[9])


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
    # Use a fresh, monotonic toot_seq per invocation. Radio-path dedup keys on
    # (src,seq): over the bridge the target node is NOT reset when we open the
    # bridge's port, so a fixed seq would be dropped as a replay on a 2nd pull.
    seq = int(time.time()) & 0x7FFFFFFF
    req = encode_toot(TTDB_REQ, ORCHESTRATOR_ID, seq, req_payload)

    slices = {}            # offset -> bytes
    eof_offset = None
    reader = SerialFrameReader()

    with serial.Serial(port, baud, timeout=0.1) as ser:
        # Opening the port resets the ESP32-S3 (DTR/RTS), so the node reboots
        # here. Wait out its boot (LittleFS mount + k10.begin) before the request,
        # or it lands during boot and is dropped. ~2.5s covers the K10 cold start.
        time.sleep(2.5)
        ser.reset_input_buffer()   # discard the boot log so it isn't parsed as frames
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


def send_reliable(ser, reader, frame, target, seq, chunk=0,
                  rto0=0.5, attempts=4):
    """Send a want_ack toot and retransmit until ACKed or `attempts` exhausted
    (TTN-RFC-0007 §4). Retransmits reuse the original (src,seq) so the receiver's
    radio dedup recognizes the duplicate and re-ACKs it (§5). RTO backs off ×2.

    Returns the 1-based attempt number that was ACKed, or 0 if undelivered.
    """
    rto = rto0
    for attempt in range(1, attempts + 1):
        write_serial_frame(ser, frame)
        print(f"  attempt {attempt}/{attempts} (rto {rto:.2f}s)")
        deadline = time.time() + rto
        while time.time() < deadline:
            data = ser.read(256)
            if not data:
                continue
            for fr in reader.feed(data):
                t = decode_toot(fr)
                # The ACK's header src is the responding node; its payload echoes
                # our (src,seq,chunk). Match both.
                if not t or t["type"] != ACK or t["src"] != target:
                    continue
                pa = parse_ack(t)
                if pa and pa[0] == ORCHESTRATOR_ID and pa[1] == seq \
                        and pa[2] == chunk:
                    return attempt
        rto *= 2
    return 0


def ping(port, baud, node, settle, rto0, attempts):
    """Reliability smoke test (TTN-RFC-0007 §8 test 1): send a want_ack CMD to a
    node and confirm exactly one ACK comes back, retransmitting under loss."""
    try:
        import serial  # pyserial
    except ImportError:
        sys.exit("pyserial not installed. Run: pip install -r requirements.txt")
    if node not in NODE_IDS:
        sys.exit(f"unknown node '{node}'. choices: {', '.join(NODE_IDS)}")
    target = NODE_IDS[node]

    seq = int(time.time()) & 0x7FFFFFFF
    # CMD payload: subcommand 0 (ping) + target echo. The node ACKs on receipt.
    payload = bytes([0]) + struct.pack("<I", target)
    frame = encode_toot(CMD, ORCHESTRATOR_ID, seq, payload, flags=FLAG_WANT_ACK)
    reader = SerialFrameReader()

    with serial.Serial(port, baud, timeout=0.1) as ser:
        time.sleep(settle)            # opening the port resets the S3 (see pull())
        ser.reset_input_buffer()
        print(f"ping {node} (0x{target:08X}) on {port} with want_ack")
        acked = send_reliable(ser, reader, frame, target, seq,
                              rto0=rto0, attempts=attempts)

    if acked:
        print(f"ACK from {node} on attempt {acked} — DELIVERED")
    else:
        sys.exit(f"no ACK from {node} after {attempts} attempts — UNDELIVERED")


def send_reliable_chunked(ser, reader, src, seq, ttype, payload, target,
                          rto0=0.5, attempts=4):
    """Split `payload` into <=MAX_BODY chunks sharing one (src,seq) and deliver
    them reliably (TTN-RFC-0007 §6). Each attempt (re)sends only the still-unacked
    chunks; an ACK clears its chunk. The chunk that completes the set is ACKed
    ACCEPTED, the rest REASSEMBLY_PENDING.

    Returns (delivered_count, total, {chunk_idx: ack_status}).
    """
    chunks = [payload[i:i + MAX_BODY] for i in range(0, len(payload), MAX_BODY)]
    if not chunks:
        chunks = [b""]
    total = len(chunks)
    if total > REASSEMBLY_MAX_CHUNKS:
        sys.exit(f"payload needs {total} chunks > firmware cap "
                 f"{REASSEMBLY_MAX_CHUNKS}")
    frames = {i: encode_toot(ttype, src, seq, ch, flags=FLAG_WANT_ACK,
                             chunk_idx=i, chunk_total=total)
              for i, ch in enumerate(chunks)}
    unacked = set(range(total))
    status = {}
    rto = rto0
    for attempt in range(1, attempts + 1):
        for i in sorted(unacked):
            write_serial_frame(ser, frames[i])
        print(f"  attempt {attempt}/{attempts}: sent {len(unacked)} chunk(s) "
              f"(rto {rto:.2f}s)")
        deadline = time.time() + rto
        while time.time() < deadline and unacked:
            data = ser.read(256)
            if not data:
                continue
            for fr in reader.feed(data):
                t = decode_toot(fr)
                if not t or t["type"] != ACK or t["src"] != target:
                    continue
                pa = parse_ack(t)
                if not pa or pa[0] != src or pa[1] != seq:
                    continue
                if pa[2] in unacked:
                    unacked.discard(pa[2])
                    status[pa[2]] = pa[3]
        if not unacked:
            return total, total, status
        rto *= 2
    return total - len(unacked), total, status


def reltest(port, baud, node, size, settle, rto0, attempts):
    """Chunked-reliability test (TTN-RFC-0007 §8 test 5): send a >208 B toot as
    several want_ack chunks and confirm every chunk is ACKed and the set completes."""
    try:
        import serial  # pyserial
    except ImportError:
        sys.exit("pyserial not installed. Run: pip install -r requirements.txt")
    if node not in NODE_IDS:
        sys.exit(f"unknown node '{node}'. choices: {', '.join(NODE_IDS)}")
    target = NODE_IDS[node]

    seq = int(time.time()) & 0x7FFFFFFF
    payload = bytes((i * 7 + 1) & 0xff for i in range(size))   # known pattern
    reader = SerialFrameReader()
    nchunks = (size + MAX_BODY - 1) // MAX_BODY

    with serial.Serial(port, baud, timeout=0.1) as ser:
        time.sleep(settle)
        ser.reset_input_buffer()
        print(f"reltest {node} (0x{target:08X}): {size} B as {nchunks} chunk(s)")
        delivered, total, status = send_reliable_chunked(
            ser, reader, ORCHESTRATOR_ID, seq, BELIEF, payload, target,
            rto0=rto0, attempts=attempts)

    if delivered == total:
        accepted = sorted(i for i, s in status.items() if s == ACK_ACCEPTED)
        print(f"all {total} chunk(s) delivered; set completed "
              f"(ACCEPTED on chunk {accepted}) — REASSEMBLED")
    else:
        sys.exit(f"only {delivered}/{total} chunks delivered — INCOMPLETE")


def main():
    ap = argparse.ArgumentParser(description="robot_team orchestrator companion")
    sub = ap.add_subparsers(dest="cmd", required=True)
    p = sub.add_parser("pull", help="pull a node's TTDB over the link")
    p.add_argument("--port", required=True, help="serial port (COM5, /dev/ttyACM0)")
    p.add_argument("--baud", type=int, default=115200)
    p.add_argument("--node", required=True, choices=list(NODE_IDS))
    p.add_argument("--out", required=True, help="output .md path")
    p.add_argument("--timeout", type=float, default=20.0)

    pg = sub.add_parser("ping", help="reliable want_ack round-trip (TTN-RFC-0007)")
    pg.add_argument("--port", required=True, help="serial port (COM5, /dev/ttyACM0)")
    pg.add_argument("--baud", type=int, default=115200)
    pg.add_argument("--node", required=True, choices=list(NODE_IDS))
    pg.add_argument("--settle", type=float, default=2.5,
                    help="post-open boot wait (s); the bridge resets on open")
    pg.add_argument("--rto0", type=float, default=0.5,
                    help="initial retransmit timeout (s); ×2 backoff")
    pg.add_argument("--attempts", type=int, default=4)

    rt = sub.add_parser("reltest",
                        help="chunked want_ack delivery of a >208 B toot (TTN-RFC-0007 §6)")
    rt.add_argument("--port", required=True, help="serial port (COM5, /dev/ttyACM0)")
    rt.add_argument("--baud", type=int, default=115200)
    rt.add_argument("--node", required=True, choices=list(NODE_IDS))
    rt.add_argument("--size", type=int, default=500,
                    help="payload bytes to send (default 500 -> 3 chunks)")
    rt.add_argument("--settle", type=float, default=2.5)
    rt.add_argument("--rto0", type=float, default=0.5)
    rt.add_argument("--attempts", type=int, default=4)
    args = ap.parse_args()

    if args.cmd == "pull":
        pull(args.port, args.baud, args.node, args.out, args.timeout)
    elif args.cmd == "ping":
        ping(args.port, args.baud, args.node, args.settle, args.rto0,
             args.attempts)
    elif args.cmd == "reltest":
        reltest(args.port, args.baud, args.node, args.size, args.settle,
                args.rto0, args.attempts)


if __name__ == "__main__":
    main()
