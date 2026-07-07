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
import re
import struct
import sys
import time
import zlib
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
    "tdeck_1": 0x00000200,
}

# Toot types.
PERCEPT = 2
BELIEF = 3
CMD = 4
ACK = 5
TTDB_REQ = 7
TTDB_DATA = 8
TIME_SYNC = 9
TIME_REQ = 10
TIME_RESP = 11
TTDB_PUT = 12
TTDB_REQ_WHOLE = 0    # entire live TTDB
TTDB_REQ_RANGE = 1    # bytes [start,end) of the live TTDB (selective re-request)
TTDB_REQ_BELIEF = 2   # entire stored belief object (/belief.md, TTN-RFC-0009 §3)

# TTDB_PUT payload (TTN-RFC-0009 §2.1): target u32 | belief_id u32 | total u32 |
# crc32 u32 | offset u32 | len u16 | data. crc32 is zlib/IEEE (== firmware toot::crc32).
TTDB_PUT_HEADER_LEN = 22
TTDB_PUT_MAX_SLICE = MAX_BODY - TTDB_PUT_HEADER_LEN   # 186

# Time-sync payload lengths (TTN-RFC-0008).
TIME_SYNC_PAYLOAD_LEN = 12   # sync_id u32 | epoch_ms u64
TIME_REQ_PAYLOAD_LEN = 8     # probe_id u32 | target_node_id u32
TIME_RESP_PAYLOAD_LEN = 12   # probe_id u32 | node_epoch_ms u64

# CMD subcommands (Toot.h CmdOp). Payload: op u8 | target u32 LE | args.
CMD_PING = 0
CMD_SET_LED = 1
CMD_CLEAR_LED = 2
CMD_GET_STATUS = 3   # used by `monitor`; node replies a STATUS PERCEPT (no ACK)
CMD_BEEP = 4
CMD_SET_INTERVAL = 5
CMD_PLAY = 6         # start the node's melody/part (K10 song); nodes boot with it off
CMD_STOP = 7         # stop the node's melody/part
CMD_CLEAR_PERCEPTS = 8  # drop the @LAT97 link-percept lane (SP1 prune, no args)
# User-facing `cmd` ops only (GET_STATUS is internal to `monitor`).
CMD_OPS = {"ping": CMD_PING, "set-led": CMD_SET_LED, "clear-led": CMD_CLEAR_LED,
           "beep": CMD_BEEP, "set-interval": CMD_SET_INTERVAL,
           "play": CMD_PLAY, "stop": CMD_STOP,
           "clear-percepts": CMD_CLEAR_PERCEPTS}

# STATUS payload (Toot.h): cursor_lat i16 | cursor_lon i16 | temp_x100 i16 |
# flags u8 | epoch_ms u64. Returned as a PERCEPT in answer to CMD_GET_STATUS.
STATUS_PAYLOAD_LEN = 15
STATUS_WARM = 1 << 0
STATUS_LED_OVERRIDE = 1 << 1
STATUS_SYNCED = 1 << 2

# Optional PULSE telemetry tail (TTN-RFC-0010 §8), appended to STATUS after the 15
# base bytes when a node is built with USE_PULSE: conductor_id u32 | era u32 |
# beat_period_ms u16 | pulse_epoch u64 | downbeat_epoch u64 | beat_in_bar u8 | pstate
# u8. `band` reads it to measure phase; `monitor` ignores it (reads only the prefix).
STATUS_PULSE_PAYLOAD_LEN = 43
PSTATE_PLAYING = 1 << 0
PSTATE_CONDUCTOR = 1 << 1

DEFAULT_MASTER_SYNC = os.path.join("master", "orchestrator-sync.md")

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


def parse_time_resp(t):
    """Read a TIME_RESP toot dict. Returns (probe_id, node_epoch_ms) or None."""
    if t["type"] != TIME_RESP:
        return None
    p = t["payload"]
    if len(p) < TIME_RESP_PAYLOAD_LEN:
        return None
    probe_id = struct.unpack("<I", p[0:4])[0]
    node_epoch_ms = struct.unpack("<Q", p[4:12])[0]
    return (probe_id, node_epoch_ms)


def parse_status(payload):
    """Read a STATUS payload (the body of a GET_STATUS PERCEPT). Returns a dict or None."""
    if len(payload) < STATUS_PAYLOAD_LEN:
        return None
    clat, clon, tx100, flags, epoch = struct.unpack(
        "<hhhBQ", payload[:STATUS_PAYLOAD_LEN])
    return {
        "cursor": (clat, clon),
        "temp_c": tx100 / 100.0,
        "warm": bool(flags & STATUS_WARM),
        "led": bool(flags & STATUS_LED_OVERRIDE),
        "synced": bool(flags & STATUS_SYNCED),
        "epoch_ms": epoch,
    }


def parse_status_pulse(payload):
    """Read the PULSE telemetry tail of a STATUS payload (TTN-RFC-0010 §8). Returns a
    dict, or None if the node didn't append it (not built with USE_PULSE)."""
    if len(payload) < STATUS_PULSE_PAYLOAD_LEN:
        return None
    cond, era, period = struct.unpack("<IIH", payload[15:25])
    pulse_epoch, downbeat = struct.unpack("<QQ", payload[25:41])
    return {
        "conductor_id": cond,
        "era": era,
        "period_ms": period,
        "pulse_epoch": pulse_epoch,
        "downbeat": downbeat,
        "beat_in_bar": payload[41],
        "playing": bool(payload[42] & PSTATE_PLAYING),
        "conductor": bool(payload[42] & PSTATE_CONDUCTOR),
    }


def open_serial_no_reset(port, baud):
    """Open the bridge port WITHOUT the DTR/RTS auto-reset, so a node's in-RAM
    clock offset (TTN-RFC-0008) survives a reconnect — essential between `sync` and
    `verify`, which are separate invocations. (`pull` keeps its reset+settle: it
    only reads flash, which is offset-independent.)"""
    import serial  # pyserial
    ser = serial.Serial()
    ser.port = port
    ser.baudrate = baud
    ser.timeout = 0.1
    ser.dtr = False   # deassert before open so the S3 native-USB reset doesn't fire
    ser.rts = False
    ser.open()
    return ser


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


def pull(port, baud, node, out_path, timeout, which="ttdb", drop=None):
    try:
        import serial  # pyserial
    except ImportError:
        sys.exit("pyserial not installed. Run: pip install -r requirements.txt")
    if node not in NODE_IDS:
        sys.exit(f"unknown node '{node}'. choices: {', '.join(NODE_IDS)}")
    target = NODE_IDS[node]
    mode = TTDB_REQ_BELIEF if which == "belief" else TTDB_REQ_WHOLE
    obj = "/belief.md" if which == "belief" else "whole TTDB"
    if drop and which == "belief":
        sys.exit("--drop only applies to the live TTDB (belief readback has no range "
                 "re-request path)")

    reader = SerialFrameReader()
    with serial.Serial(port, baud, timeout=0.1) as ser:
        # Opening the port resets the ESP32-S3 (DTR/RTS), so the node reboots here.
        # Wait out its boot (LittleFS mount + k10.begin) before the request, or it
        # lands during boot and is dropped. ~2.5s covers the K10 cold start. (A pull
        # only reads flash, so the reset is harmless here — unlike sync/verify.)
        time.sleep(2.5)
        ser.reset_input_buffer()   # discard the boot log so it isn't parsed as frames
        print(f"requested {obj} from {node} (0x{target:08X}) on {port}")
        if drop:
            print(f"induced loss: will drop first-pass slice(s) {sorted(drop)}")
        data = request_ttdb(ser, reader, target, timeout, mode, drop=drop)

    if data is None:
        sys.exit("no data received (check port, node id, and the key)")
    os.makedirs(os.path.dirname(os.path.abspath(out_path)), exist_ok=True)
    with open(out_path, "wb") as f:
        f.write(data)
    print(f"wrote {len(data)} bytes to {out_path}")


def _stream_request(ser, reader, target, req_payload, timeout, idle, drop=None):
    """Send one TTDB_REQ and collect its TTDB_DATA reply until the stream's
    zero-length EOF marker (or `idle` seconds of silence, or `timeout`). Returns
    (slices, term_offset): slices is {file_offset: bytes}; term_offset is the EOF
    marker's offset (the end of the served range), or None if no EOF was seen.

    `drop` is a set of 0-based data-slice arrival indices to discard, simulating air
    loss so the on-device re-request path is exercised deterministically (the EOF
    marker is never a candidate, so the total length is always learned). It is the
    receiver-side knob behind `pull --drop`.

    A fresh ms-resolution toot_seq keeps a non-reset target from dedup-dropping a
    repeated request (the link is un-deduped, but the radio path is)."""
    drop = drop or set()
    seq = int(time.time() * 1000) & 0x7FFFFFFF
    write_serial_frame(ser, encode_toot(TTDB_REQ, ORCHESTRATOR_ID, seq, req_payload))

    slices = {}            # offset -> bytes
    term = None
    idx = 0                # data-slice arrival index (for induced-loss matching)
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
                    term = off             # EOF marker (end of served range)
                else:
                    if idx in drop:
                        print(f"  induced loss: dropped slice #{idx} "
                              f"(offset {off}, {n} B)")
                    else:
                        slices[off] = p[6:6 + n]
                    idx += 1
        if term is not None:
            break
        if time.time() - last_rx > idle:
            break
    return slices, term


def missing_ranges(slices, total):
    """Byte ranges in [0, total) that no slice in `slices` covers, as a list of
    (start, end). The pull stream is offset-addressed, so a dropped slice is just a
    hole; this is what we selectively re-request."""
    gaps = []
    cur = 0
    for off in sorted(slices):
        end = off + len(slices[off])
        if off > cur:
            gaps.append((cur, off))
        if end > cur:
            cur = end
    if cur < total:
        gaps.append((cur, total))
    return gaps


def request_ttdb(ser, reader, target, timeout=20.0, mode=TTDB_REQ_WHOLE, rounds=4,
                 drop=None):
    """Request a node's whole object over an already-open link; return the
    reassembled bytes, or None. `mode` selects the live TTDB (TTDB_REQ_WHOLE) or the
    stored belief (TTDB_REQ_BELIEF) — both stream the same offset-addressed TTDB_DATA
    slices. Shared by `pull`, `verify`, and `push`.

    Pull-stream reliability: after the first pass the EOF marker fixes the true
    total length, so any dropped slice shows up as a gap in offset coverage. We then
    selectively re-request just those byte ranges (TTDB_REQ_RANGE) until the object
    is byte-complete or `rounds` is exhausted — the receiver-driven analogue of
    reltest's per-chunk retransmit. This closes the old ~1/6 bridged-pull frame drop.
    Range re-request needs the offset index (TTDB_REQ_RANGE -> handleRequest), so it
    applies to the live TTDB only; belief readback streams the whole buffer in one
    pass (handleBufferRequest has no range path).

    `drop` (a set of data-slice indices) discards those slices on the FIRST pass only,
    so the re-request recovery runs deterministically — the on-device test knob behind
    `pull --drop`."""
    base = bytes([mode]) + struct.pack("<I", target)
    slices, total = _stream_request(ser, reader, target, base, timeout, idle=3.0,
                                    drop=drop)
    if not slices and total is None:
        return None
    if total is None or mode != TTDB_REQ_WHOLE:
        # No EOF (best-effort), or an object we can't range-re-request (belief).
        return reassemble(slices, total)

    for r in range(1, rounds + 1):
        gaps = missing_ranges(slices, total)
        if not gaps:
            break
        miss = sum(g1 - g0 for g0, g1 in gaps)
        print(f"  pull round {r}: re-requesting {len(gaps)} gap(s), {miss} B")
        for g0, g1 in gaps:
            rp = bytes([TTDB_REQ_RANGE]) + struct.pack("<III", target, g0, g1)
            got, _ = _stream_request(ser, reader, target, rp, timeout, idle=2.0)
            slices.update(got)

    gaps = missing_ranges(slices, total)
    if gaps:
        print(f"  warning: {len(gaps)} range(s) still missing after {rounds} "
              f"rounds: {gaps}")
    return reassemble(slices, total)


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


def send_cmd(port, baud, node, op, rgb, freq, dur_ms, interval_ms,
             settle, rto0, attempts):
    """Send an orchestrator CMD (companion.md §4b) addressed to one node and confirm
    it via the want_ack ACK. Ops: ping, set-led RRGGBB, clear-led, beep, set-interval."""
    try:
        import serial  # pyserial
    except ImportError:
        sys.exit("pyserial not installed. Run: pip install -r requirements.txt")
    if node not in NODE_IDS:
        sys.exit(f"unknown node '{node}'. choices: {', '.join(NODE_IDS)}")
    if op not in CMD_OPS:
        sys.exit(f"unknown op '{op}'. choices: {', '.join(CMD_OPS)}")
    target = NODE_IDS[node]
    opcode = CMD_OPS[op]

    args = b""
    detail = ""
    if opcode == CMD_SET_LED:
        if not rgb:
            sys.exit("set-led needs --rgb RRGGBB (e.g. FF0000)")
        try:
            args = bytes.fromhex(rgb)
        except ValueError:
            sys.exit(f"--rgb must be 6 hex digits, got '{rgb}'")
        if len(args) != 3:
            sys.exit(f"--rgb must be exactly RRGGBB (3 bytes), got {len(args)}")
        detail = f" #{rgb}"
    elif opcode == CMD_BEEP:
        args = struct.pack("<HH", freq & 0xFFFF, dur_ms & 0xFFFF)
        detail = f" {freq}Hz/{dur_ms}ms"
    elif opcode == CMD_SET_INTERVAL:
        if interval_ms is None:
            sys.exit("set-interval needs --interval-ms (e.g. 500)")
        args = struct.pack("<H", interval_ms & 0xFFFF)
        detail = f" {interval_ms}ms"

    payload = bytes([opcode]) + struct.pack("<I", target) + args
    seq = int(time.time()) & 0x7FFFFFFF
    frame = encode_toot(CMD, ORCHESTRATOR_ID, seq, payload, flags=FLAG_WANT_ACK)
    reader = SerialFrameReader()

    label = f"{op}{detail}"
    with serial.Serial(port, baud, timeout=0.1) as ser:
        time.sleep(settle)            # opening the bridge port resets it (see pull())
        ser.reset_input_buffer()
        print(f"cmd {label} -> {node} (0x{target:08X}) on {port}")
        acked = send_reliable(ser, reader, frame, target, seq,
                              rto0=rto0, attempts=attempts)

    if acked:
        print(f"ACK from {node} on attempt {acked} — APPLIED")
    else:
        sys.exit(f"no ACK from {node} after {attempts} attempts — NOT applied")


def monitor(port, baud, nodes, interval, rounds, settle):
    """Live fleet telemetry: each round polls every node with CMD_GET_STATUS and
    prints a table from the STATUS PERCEPT replies. The observe half of the
    orchestrator loop — complements `cmd` (push) and `sync` (timestamp)."""
    try:
        import serial  # pyserial
    except ImportError:
        sys.exit("pyserial not installed. Run: pip install -r requirements.txt")
    for name in nodes:
        if name not in NODE_IDS:
            sys.exit(f"unknown node '{name}'. choices: {', '.join(NODE_IDS)}")
    targets = {NODE_IDS[name]: name for name in nodes}
    reader = SerialFrameReader()

    with serial.Serial(port, baud, timeout=0.1) as ser:
        time.sleep(settle)
        ser.reset_input_buffer()
        r = 0
        try:
            while rounds == 0 or r < rounds:
                r += 1
                base = int(time.time() * 1000) & 0x7FFFFFFF
                for i, tid in enumerate(targets):
                    seq = (base + i) & 0x7FFFFFFF     # fresh per poll (radio dedup)
                    payload = bytes([CMD_GET_STATUS]) + struct.pack("<I", tid)
                    write_serial_frame(
                        ser, encode_toot(CMD, ORCHESTRATOR_ID, seq, payload))
                latest = {}
                deadline = time.time() + interval
                while time.time() < deadline:
                    data = ser.read(256)
                    if not data:
                        continue
                    for fr in reader.feed(data):
                        t = decode_toot(fr)
                        if not t or t["type"] != PERCEPT or t["src"] not in targets:
                            continue
                        st = parse_status(t["payload"])
                        if st:
                            latest[t["src"]] = st
                print(f"\n[{time.strftime('%H:%M:%S')}] fleet status (round {r})")
                print(f"{'node':<12}{'cursor':<11}{'temp':>7}{'warm':>6}"
                      f"{'led':>5}{'synced':>8}")
                for tid, name in targets.items():
                    st = latest.get(tid)
                    if not st:
                        print(f"{name:<12}{'(no reply)':<11}")
                        continue
                    cur = f"@L{st['cursor'][0]}L{st['cursor'][1]}"
                    yn = lambda b: "Y" if b else "-"  # noqa: E731
                    print(f"{name:<12}{cur:<11}{st['temp_c']:>6.1f}C"
                          f"{yn(st['warm']):>6}{yn(st['led']):>5}"
                          f"{yn(st['synced']):>8}")
        except KeyboardInterrupt:
            print("\nstopped")


# --- Time-sync (TTN-RFC-0008) ----------------------------------------------
MASTER_SYNC_HEADER = """# Orchestrator Master Sync Log

```mmpdb
db_id: orchestrator-sync-001
db_name: Orchestrator Master Sync Log
coord_increment:
  lat: 1
  lon: 1
collision_policy: reject
timestamp_kind: unix
umwelt:
  umwelt_id: orchestrator
  role: companion-orchestrator
  scope: master
```

```cursor
lat: 0
lon: 0
```
"""

# Match the firmware sync record so the same parser reads every node's log.
SYNC_RE = re.compile(r"\*\*SYNC\*\*\s+id:(\d+)")
# Full sync record (laptop master + every node write the same shape).
SYNC_FULL_RE = re.compile(
    r"\*\*SYNC\*\*\s+id:(\d+)\s+t_ms:(\d+)\s+recv_ms:(\d+)\s+offset_ms:(-?\d+)")

CONSOLIDATED_HEADER = """# Orchestrator Consolidated Knowledge (Dream-Cycle seed)

This file is authored by `companion.py reconcile`: it folds each node's
self-reported `@LAT99` sync log into one master view with provenance, the minimal
first instance of the Dream Cycle (TTDB-RFC-0007) — episodic node records
consolidated into a semantic master record.

```mmpdb
db_id: orchestrator-consolidated-001
db_name: Orchestrator Consolidated Knowledge
coord_increment:
  lat: 1
  lon: 1
collision_policy: reject
timestamp_kind: unix
umwelt:
  umwelt_id: orchestrator
  role: companion-orchestrator
  scope: master
```

```cursor
lat: 0
lon: 0
```
"""


def parse_sync_file(path):
    """Extract every **SYNC** record from a TTDB file. Returns a list of
    {id, t_ms, recv_ms, offset_ms} dicts (empty if the file is absent)."""
    if not os.path.exists(path):
        return []
    with open(path, encoding="utf-8", errors="replace") as f:
        text = f.read()
    return [{"id": int(m.group(1)), "t_ms": int(m.group(2)),
             "recv_ms": int(m.group(3)), "offset_ms": int(m.group(4))}
            for m in SYNC_FULL_RE.finditer(text)]


def next_sync_id(master_path):
    """Monotonic sync_id = max id in the master log + 1 (1 if none)."""
    if not os.path.exists(master_path):
        return 1
    with open(master_path, encoding="utf-8") as f:
        ids = [int(m) for m in SYNC_RE.findall(f.read())]
    return (max(ids) + 1) if ids else 1


def append_master_sync_record(master_path, sync_id, epoch_ms):
    """Append the laptop's own sync record (the 3rd 'node'). The laptop is the
    time source, so offset_ms = 0 and recv_ms = epoch_ms (TTN-RFC-0008 §4.2)."""
    os.makedirs(os.path.dirname(os.path.abspath(master_path)), exist_ok=True)
    new_file = not os.path.exists(master_path)
    n = 0
    if not new_file:
        with open(master_path, encoding="utf-8") as f:
            n = len(re.findall(r"@LAT99LON", f.read()))
    t_sec = epoch_ms // 1000
    with open(master_path, "a", encoding="utf-8", newline="\n") as f:
        if new_file:
            f.write(MASTER_SYNC_HEADER)
        f.write(f"\n---\n\n@LAT99LON{n} | created:{t_sec} | updated:{t_sec} | "
                f"relates:logs@LAT0LON0\n\n")
        f.write(f"**SYNC** id:{sync_id} t_ms:{epoch_ms} recv_ms:{epoch_ms} "
                f"offset_ms:0\n")


def master_has_record(master_path, sync_id):
    if not os.path.exists(master_path):
        return False
    with open(master_path, encoding="utf-8") as f:
        return f"**SYNC** id:{sync_id}" in f.read()


def broadcast_time_sync(ser, reader, sync_id, epoch_ms, expected_ids,
                        rto0=0.5, attempts=4):
    """Broadcast a want_ack TIME_SYNC and retransmit until every expected
    responder ACKs or attempts run out (TTN-RFC-0007 §4 + TTN-RFC-0008 §5). The
    ACK header src identifies the responder. Returns the set of still-unacked ids."""
    seq = int(time.time()) & 0x7FFFFFFF
    payload = struct.pack("<I", sync_id) + struct.pack("<Q", epoch_ms)
    frame = encode_toot(TIME_SYNC, ORCHESTRATOR_ID, seq, payload,
                        flags=FLAG_WANT_ACK)
    pending = set(expected_ids)
    rto = rto0
    for attempt in range(1, attempts + 1):
        write_serial_frame(ser, frame)
        print(f"  attempt {attempt}/{attempts}: TIME_SYNC id={sync_id} "
              f"(awaiting {len(pending)} ACK, rto {rto:.2f}s)")
        deadline = time.time() + rto
        while time.time() < deadline and pending:
            data = ser.read(256)
            if not data:
                continue
            for fr in reader.feed(data):
                t = decode_toot(fr)
                if not t or t["type"] != ACK:
                    continue
                pa = parse_ack(t)
                if pa and pa[0] == ORCHESTRATOR_ID and pa[1] == seq:
                    pending.discard(t["src"])
        if not pending:
            return set()
        rto *= 2
    return pending


def ntp_probe(ser, reader, target, probes=5, per_timeout=1.0):
    """NTP-lite skew probe (TTN-RFC-0008 §6). Returns (skew_ms, rtt_ms) from the
    minimum-RTT sample, or None if the node never answered. A FRESH toot_seq per
    probe is mandatory: a repeated (src,seq) is dropped by the node's radio dedup."""
    best = None  # (rtt, skew)
    base = int(time.time() * 1000) & 0x7FFFFFFF
    old_to = ser.timeout
    ser.timeout = 0   # non-blocking reads so t1 reflects arrival, not poll quantum
    try:
        for k in range(probes):
            pid = (base + k) & 0x7FFFFFFF      # fresh probe id == fresh toot_seq
            payload = struct.pack("<I", pid) + struct.pack("<I", target)
            frame = encode_toot(TIME_REQ, ORCHESTRATOR_ID, pid, payload)
            t0 = time.time() * 1000.0
            write_serial_frame(ser, frame)
            node_epoch = None
            deadline = time.time() + per_timeout
            while time.time() < deadline and node_epoch is None:
                data = ser.read(256)
                if not data:
                    time.sleep(0.0005)         # ~0.5 ms loop; keep RTT tight
                    continue
                for fr in reader.feed(data):
                    t = decode_toot(fr)
                    if not t or t["type"] != TIME_RESP or t["src"] != target:
                        continue
                    pr = parse_time_resp(t)
                    if pr and pr[0] == pid:
                        node_epoch = pr[1]
                        break
            if node_epoch is None:
                continue
            t1 = time.time() * 1000.0
            rtt = t1 - t0
            skew = node_epoch - (t0 + rtt / 2.0)  # node ahead(+) / behind(-) laptop
            if best is None or rtt < best[0]:
                best = (rtt, skew)
    finally:
        ser.timeout = old_to
    return None if best is None else (best[1], best[0])


def sync(port, baud, expect, master, settle, rto0, attempts):
    try:
        import serial  # noqa: F401  (open_serial_no_reset imports it)
    except ImportError:
        sys.exit("pyserial not installed. Run: pip install -r requirements.txt")
    for name in expect:
        if name not in NODE_IDS:
            sys.exit(f"unknown node '{name}'. choices: {', '.join(NODE_IDS)}")
    targets = {NODE_IDS[name]: name for name in expect}

    sync_id = next_sync_id(master)
    reader = SerialFrameReader()
    ser = open_serial_no_reset(port, baud)
    try:
        time.sleep(settle)
        ser.reset_input_buffer()
        # Sample epoch_ms HERE — right before the broadcast, after the settle — so
        # the timestamp the nodes adopt isn't stale by the settle duration. The
        # residual is then only the one-way delivery delay, which `verify` measures.
        epoch_ms = int(time.time() * 1000)
        print(f"sync id={sync_id} epoch_ms={epoch_ms}; "
              f"broadcasting TIME_SYNC through {port}; expecting ACK from {expect}")
        unacked = broadcast_time_sync(ser, reader, sync_id, epoch_ms,
                                      set(targets), rto0, attempts)
    finally:
        ser.close()
    append_master_sync_record(master, sync_id, epoch_ms)   # log the broadcast epoch

    if not unacked:
        print(f"sync id={sync_id}: all nodes adopted (ACKed) + master logged")
    else:
        names = [targets[i] for i in unacked]
        sys.exit(f"sync id={sync_id}: NO ACK from {names} — unsynced "
                 f"(run again, or check the bridge/mesh)")


def verify(port, baud, nodes, sync_id, bound_ms, master, settle, probes):
    try:
        import serial  # noqa: F401
    except ImportError:
        sys.exit("pyserial not installed. Run: pip install -r requirements.txt")
    for name in nodes:
        if name not in NODE_IDS:
            sys.exit(f"unknown node '{name}'. choices: {', '.join(NODE_IDS)}")

    needle = f"**SYNC** id:{sync_id}".encode()
    reader = SerialFrameReader()
    rows = []  # (name, has_record, skew_ms, rtt_ms)
    ser = open_serial_no_reset(port, baud)
    try:
        time.sleep(settle)
        ser.reset_input_buffer()
        for name in nodes:
            target = NODE_IDS[name]
            # Assertion A — pull the node's TTDB and look for the sync record. A
            # bridged over-air pull occasionally returns empty on one attempt (the
            # whole burst missed; with no EOF there's no total for request_ttdb's
            # range self-heal to gap-fill), so retry a few times — a transient miss
            # must not read as a missing record (like push's verify pull).
            data = None
            for _ in range(3):
                data = request_ttdb(ser, reader, target)
                if data is not None and needle in data:
                    break
            has = data is not None and needle in data
            best = ntp_probe(ser, reader, target, probes)     # Assertion B
            skew, rtt = (best if best else (None, None))
            rows.append((name, has, skew, rtt))
    finally:
        ser.close()

    master_ok = master_has_record(master, sync_id)

    print(f"\nverify sync id={sync_id} (bound +/-{bound_ms} ms)")
    print(f"{'node':<14}{'has_record':<12}{'skew_ms':>10}{'rtt_ms':>10}")
    ok = master_ok
    for name, has, skew, rtt in rows:
        skew_s = f"{skew:+.1f}" if skew is not None else "  n/a"
        rtt_s = f"{rtt:.1f}" if rtt is not None else " n/a"
        in_bound = skew is not None and abs(skew) <= bound_ms
        print(f"{name:<14}{('yes' if has else 'NO'):<12}{skew_s:>10}{rtt_s:>10}"
              f"{'' if (has and in_bound) else '   <-- FAIL'}")
        ok = ok and has and in_bound
    print(f"{'(laptop)':<14}{('yes' if master_ok else 'NO'):<12}"
          f"{'+0.0':>10}{'-':>10}")

    if ok:
        print(f"\nPASS: all 3 carry sync id={sync_id} and are within "
              f"+/-{bound_ms} ms")
    else:
        sys.exit(f"\nFAIL: sync id={sync_id} not present everywhere or skew "
                 f"out of bound")


# --- Fleet pulse (TTN-RFC-0010) --------------------------------------------
def status_probe(ser, reader, target, probes=5, per_timeout=1.0):
    """Probe a node with CMD_GET_STATUS and keep the minimum-RTT reply (NTP-lite, like
    ntp_probe). Returns the PULSE telemetry dict augmented with 'rtt' and 't_mid' (the
    laptop ms instant the node's pulse_epoch corresponds to, t0 + rtt/2), or
    {'plain': True} if the node replied without the pulse tail (needs a reflash), or
    None if it never answered. A FRESH toot_seq per probe dodges the radio dedup."""
    best = None
    saw_plain = False
    base = int(time.time() * 1000) & 0x7FFFFFFF
    old_to = ser.timeout
    ser.timeout = 0   # non-blocking reads so t1 reflects arrival, not poll quantum
    try:
        for k in range(probes):
            seq = (base + k) & 0x7FFFFFFF      # fresh seq == fresh (src,seq)
            payload = bytes([CMD_GET_STATUS]) + struct.pack("<I", target)
            frame = encode_toot(CMD, ORCHESTRATOR_ID, seq, payload)
            t0 = time.time() * 1000.0
            write_serial_frame(ser, frame)
            got = None
            deadline = time.time() + per_timeout
            while time.time() < deadline and got is None:
                data = ser.read(256)
                if not data:
                    time.sleep(0.0005)
                    continue
                for fr in reader.feed(data):
                    t = decode_toot(fr)
                    if not t or t["type"] != PERCEPT or t["src"] != target:
                        continue
                    pp = parse_status_pulse(t["payload"])
                    if pp is not None:
                        got = pp
                        break
                    if parse_status(t["payload"]) is not None:
                        saw_plain = True   # replied, but no pulse tail (old firmware)
            if got is None:
                continue
            t1 = time.time() * 1000.0
            rtt = t1 - t0
            if best is None or rtt < best["rtt"]:
                got["rtt"] = rtt
                got["t_mid"] = t0 + rtt / 2.0
                best = got
    finally:
        ser.timeout = old_to
    if best is None and saw_plain:
        return {"plain": True}
    return best


def circular_diff(a, b, period):
    """Signed shortest distance from b to a on a circle of circumference `period`."""
    d = (a - b) % period
    if d > period / 2.0:
        d -= period
    return d


def _render_band(probed, bound_ms, watch):
    """Print one fleet-pulse table from a {name: status_probe(...) } map. Returns True
    if the band is converged + tight (one conductor, every node within +/-bound_ms)."""
    # Project each playing node's beat phase to a single laptop instant T. The pulse
    # clock advances 1:1 with real time, so pulse_epoch at t_mid extrapolates linearly.
    playing = {n: r for n, r in probed.items()
               if r and not r.get("plain") and r.get("playing")}
    T = max((r["t_mid"] for r in playing.values()), default=time.time() * 1000.0)
    phases = {}
    for n, r in playing.items():
        proj = r["pulse_epoch"] + (T - r["t_mid"])
        phases[n] = (proj - r["downbeat"]) % r["period_ms"]
    # Reference phase = the conductor's (or the lowest conductor_id if none is probed).
    ref = next((n for n, r in playing.items() if r.get("conductor")), None)
    if ref is None and playing:
        ref = min(playing, key=lambda n: playing[n]["conductor_id"])

    if watch:
        print(f"\n[{time.strftime('%H:%M:%S')}] fleet pulse (TTN-RFC-0010)")
    print(f"{'node':<12}{'conductor':<13}{'era':>4}{'bpm':>6}{'beat':>5}"
          f"{'phase_ms':>10}{'skew_ms':>9}{'rtt_ms':>8}")
    conductors = set()
    max_skew = 0.0
    ok = True
    for n in probed:
        r = probed[n]
        if not r:
            print(f"{n:<12}(no reply)")
            ok = False
            continue
        if r.get("plain"):
            print(f"{n:<12}(no pulse telemetry — reflash with USE_PULSE)")
            ok = False
            continue
        if not r.get("playing"):
            print(f"{n:<12}(not playing yet)")
            ok = False
            continue
        conductors.add(r["conductor_id"])
        bpm = 60000.0 / r["period_ms"] if r["period_ms"] else 0.0
        skew = circular_diff(phases[n], phases[ref], r["period_ms"]) if ref else 0.0
        max_skew = max(max_skew, abs(skew))
        label = f"0x{r['conductor_id']:08X}" + ("*" if r.get("conductor") else "")
        flag = "" if abs(skew) <= bound_ms else "  <-- OUT"
        print(f"{n:<12}{label:<13}{r['era']:>4}{bpm:>6.0f}{r['beat_in_bar']:>5}"
              f"{phases[n]:>10.1f}{skew:>+9.1f}{r['rtt']:>7.0f}{flag}")
        if abs(skew) > bound_ms:
            ok = False
    if len(conductors) > 1:
        print("  ! not converged — "
              f"{len(conductors)} conductors: "
              f"{', '.join(f'0x{c:08X}' for c in sorted(conductors))}")
        ok = False
    elif playing:
        print(f"  * = conductor;  band tight to +/-{max_skew:.1f} ms "
              f"(bound +/-{bound_ms:.0f} ms)")
    return ok


def band(port, baud, nodes, bound_ms, probes, settle, watch, interval):
    """Measure fleet-pulse tightness (TTN-RFC-0010 §8): probe each node's chart + beat
    phase, project all phases to one laptop instant (min-RTT NTP-lite), and report
    inter-node phase skew vs the conductor. Pass = one shared conductor and every node
    within +/-bound_ms. The laptop has NO per-beat role here — it only observes."""
    try:
        import serial  # noqa: F401  (open_serial_no_reset imports it)
    except ImportError:
        sys.exit("pyserial not installed. Run: pip install -r requirements.txt")
    for name in nodes:
        if name not in NODE_IDS:
            sys.exit(f"unknown node '{name}'. choices: {', '.join(NODE_IDS)}")

    reader = SerialFrameReader()
    # Don't reset the bridge: a DTR/RTS reset would wipe V4-A's in-RAM pulse clock +
    # conductor role and disrupt the very band we're measuring (cf. sync/verify).
    ser = open_serial_no_reset(port, baud)
    last_ok = False
    try:
        time.sleep(settle)
        ser.reset_input_buffer()
        first = True
        while first or watch:
            first = False
            probed = {n: status_probe(ser, reader, NODE_IDS[n], probes) for n in nodes}
            last_ok = _render_band(probed, bound_ms, watch)
            if watch:
                time.sleep(interval)
    except KeyboardInterrupt:
        print("\nstopped")
        return
    finally:
        ser.close()

    if not watch:
        if last_ok:
            print(f"\nPASS: band converged + tight within +/-{bound_ms:.0f} ms")
        else:
            sys.exit("\nFAIL: band not converged or a node out of bound")


def reconcile(port, baud, nodes, master, out, do_pull, settle):
    """Dream-Cycle seed (TTDB-RFC-0007): consolidate each node's self-authored sync
    log into one master view with provenance, and confirm the fleet agrees on every
    timestamp. Pulls each node's TTDB first (unless --no-pull / no port)."""
    sources = {"laptop": parse_sync_file(master)}
    master_dir = os.path.dirname(master) or "."
    node_paths = {n: os.path.join(master_dir, f"{n}.md") for n in nodes}

    if do_pull:
        try:
            import serial  # pyserial
        except ImportError:
            sys.exit("pyserial not installed. Run: pip install -r requirements.txt")
        for n in nodes:
            if n not in NODE_IDS:
                sys.exit(f"unknown node '{n}'. choices: {', '.join(NODE_IDS)}")
        reader = SerialFrameReader()
        with serial.Serial(port, baud, timeout=0.1) as ser:
            time.sleep(settle)
            ser.reset_input_buffer()
            for n in nodes:
                data = request_ttdb(ser, reader, NODE_IDS[n])
                if data is None:
                    print(f"warning: no TTDB from {n}; using existing file if present")
                    continue
                os.makedirs(os.path.dirname(os.path.abspath(node_paths[n])) or ".",
                            exist_ok=True)
                with open(node_paths[n], "wb") as f:
                    f.write(data)
                print(f"pulled {n}: {len(data)} B -> {node_paths[n]}")

    for n in nodes:
        sources[n] = parse_sync_file(node_paths[n])

    # Group records by sync_id, tracking which sources reported each + their t_ms.
    events = {}
    for src, recs in sources.items():
        for r in recs:
            e = events.setdefault(r["id"], {"t_ms": set(), "by": {}})
            e["t_ms"].add(r["t_ms"])
            e["by"][src] = r

    os.makedirs(os.path.dirname(os.path.abspath(out)) or ".", exist_ok=True)
    all_agree = True
    with open(out, "w", encoding="utf-8", newline="\n") as f:
        f.write(CONSOLIDATED_HEADER)
        for sid in sorted(events):
            e = events[sid]
            agree = len(e["t_ms"]) == 1
            all_agree = all_agree and agree
            t_ms = min(e["t_ms"])
            names = ",".join(sorted(e["by"]))
            f.write(f"\n---\n\n@LAT99LON{sid} | created:{t_ms // 1000} | "
                    f"updated:{t_ms // 1000} | relates:knows@LAT0LON0\n\n")
            f.write(f"**CONSOLIDATED-SYNC** id:{sid} t_ms:{t_ms} "
                    f"agree:{'yes' if agree else 'NO'} confirmed_by:{names}\n")
            for src in sorted(e["by"]):
                r = e["by"][src]
                mism = "" if r["t_ms"] == t_ms else f"  (t_ms MISMATCH {r['t_ms']})"
                f.write(f"- {src}: recv_ms:{r['recv_ms']} "
                        f"offset_ms:{r['offset_ms']}{mism}\n")

    print(f"\nreconcile: {len(events)} sync event(s) across "
          f"{{{', '.join(sorted(sources))}}}")
    print(f"{'id':>3}  {'t_ms':<16}{'confirmed_by':<26}agree")
    for sid in sorted(events):
        e = events[sid]
        agree = len(e["t_ms"]) == 1
        print(f"{sid:>3}  {min(e['t_ms']):<16}{','.join(sorted(e['by'])):<26}"
              f"{'yes' if agree else 'NO <--'}")
    print(f"\nwrote {out}")
    if not all_agree:
        sys.exit("DISCREPANCY: a node's logged t_ms disagrees with the master")


# --- belief push-back (TTN-RFC-0009) ----------------------------------------
DEFAULT_BELIEF_LOG = os.path.join("master", "belief-log.md")
DEFAULT_BELIEF_OUT = os.path.join("master", "belief.md")

BELIEF_HEADER = """# Fleet Belief (authored by companion push)

This object is re-authored by `companion.py push` from the consolidated fleet sync
knowledge and pushed back to a node (TTN-RFC-0009) — the propagation half of the
Dream Cycle (TTDB-RFC-0007). The node stores it as `/belief.md` and records the
adoption in its own TTDB.

```mmpdb
db_id: fleet-belief-001
db_name: Fleet Belief
coord_increment:
  lat: 1
  lon: 1
collision_policy: reject
timestamp_kind: unix
umwelt:
  umwelt_id: orchestrator
  role: companion-orchestrator
  scope: belief
```

```cursor
lat: 0
lon: 0
```
"""

# Default sense->reason->act cadence the Dream Cycle distributes as a belief
# directive (TTN-RFC-0009 §5.2). Faster than the node's 1000 ms boot default so the
# behavior change is obvious; the node retunes its loop to this on adoption.
DEFAULT_SENSE_INTERVAL_MS = 300

# The node's self-attestation record (live TTDB, lat 98 lane). `applied:interval_ms`
# is optional — present once the node parses + applies the belief's DIRECTIVE.
BELIEF_ADOPTED_RE = re.compile(
    r"\*\*BELIEF-ADOPTED\*\*\s+id:(\d+)\s+bytes:(\d+)\s+crc:([0-9A-Fa-f]+)"
    r"(?:\s+recv_ms:\d+)?(?:\s+applied:interval_ms:(\d+))?")
# The laptop's own push log (one record per delivered belief).
BELIEF_PUSH_RE = re.compile(r"\*\*BELIEF-PUSH\*\*\s+id:(\d+)")


def crc32(data: bytes) -> int:
    """CRC-32 (zlib/IEEE) — the exact sum the firmware toot::crc32 computes."""
    return zlib.crc32(data) & 0xFFFFFFFF


def author_belief(master_path, sense_interval_ms=DEFAULT_SENSE_INTERVAL_MS):
    """Re-author a belief TTDB from the master sync knowledge (TTN-RFC-0009 §5.1):
    a `**BELIEF**` summary record, a `**DIRECTIVE**` record carrying the cadence the
    node should adopt, plus one `**BELIEF-SYNC**` record per known sync event. Returns
    valid TTDB bytes the node can store, re-index, and act on."""
    recs = parse_sync_file(master_path)
    latest = max((r["t_ms"] for r in recs), default=0)
    parts = [BELIEF_HEADER]
    parts.append(
        f"\n---\n\n@LAT0LON0 | created:{latest // 1000} | updated:{latest // 1000} | "
        f"relates:knows@LAT1LON0,directs@LAT0LON1\n\n"
        f"**BELIEF** summary:fleet-observed-{len(recs)}-sync-events "
        f"latest_t_ms:{latest}\n")
    # Behavioral directive: the node reads this from /belief.md on adoption and retunes
    # its sense->reason->act cadence (closes the Dream Cycle — consolidated knowledge
    # becomes distributed policy that changes node behavior, PLAN.md Phase 6).
    parts.append(
        f"\n---\n\n@LAT0LON1 | created:{latest // 1000} | updated:{latest // 1000} | "
        f"relates:directed_by@LAT0LON0\n\n"
        f"**DIRECTIVE** sense_interval_ms:{sense_interval_ms}\n")
    for i, r in enumerate(recs):
        parts.append(
            f"\n---\n\n@LAT{i + 1}LON0 | created:{r['t_ms'] // 1000} | "
            f"updated:{r['t_ms'] // 1000} | relates:derives@LAT0LON0\n\n"
            f"**BELIEF-SYNC** id:{r['id']} t_ms:{r['t_ms']}\n")
    return "".join(parts).encode("utf-8")


def next_belief_id(log_path):
    """Monotonic belief_id = max id in the push log + 1 (1 if none)."""
    if not os.path.exists(log_path):
        return 1
    with open(log_path, encoding="utf-8") as f:
        ids = [int(m) for m in BELIEF_PUSH_RE.findall(f.read())]
    return (max(ids) + 1) if ids else 1


def append_belief_push_record(log_path, belief_id, node, total, crc):
    """Record a delivered belief in the laptop's master push log."""
    os.makedirs(os.path.dirname(os.path.abspath(log_path)), exist_ok=True)
    new_file = not os.path.exists(log_path)
    n = 0
    if not new_file:
        with open(log_path, encoding="utf-8") as f:
            n = len(re.findall(r"@LAT97LON", f.read()))
    with open(log_path, "a", encoding="utf-8", newline="\n") as f:
        if new_file:
            f.write("# Orchestrator Belief Push Log\n\n"
                    "One record per belief delivered to a node (TTN-RFC-0009).\n")
        f.write(f"\n---\n\n@LAT97LON{n} | relates:pushed@LAT0LON0\n\n"
                f"**BELIEF-PUSH** id:{belief_id} node:{node} bytes:{total} "
                f"crc:{crc:08X}\n")


def find_belief_adopted(text, belief_id):
    """Find the node's BELIEF-ADOPTED record for `belief_id`. Returns
    {id, bytes, crc} or None."""
    for m in BELIEF_ADOPTED_RE.finditer(text):
        if int(m.group(1)) == belief_id:
            return {"id": belief_id, "bytes": int(m.group(2)),
                    "crc": int(m.group(3), 16),
                    "applied_interval_ms": int(m.group(4)) if m.group(4) else None}
    return None


def put_slice_payload(target, belief_id, total, crc, offset, data):
    """Pack a TTDB_PUT slice payload (TTN-RFC-0009 §2.1)."""
    return (struct.pack("<IIIII", target, belief_id, total, crc, offset)
            + struct.pack("<H", len(data)) + data)


def push_belief(ser, reader, target, content, belief_id, rto0, attempts):
    """Deliver `content` to a node as offset-addressed want_ack TTDB_PUT slices
    (TTN-RFC-0009). Each slice rides the TTN-RFC-0007 reliable sender. Returns True
    when every slice is ACKed."""
    crc = crc32(content)
    total = len(content)
    offsets = list(range(0, total, TTDB_PUT_MAX_SLICE)) or [0]
    print(f"push belief id={belief_id} {total}B crc={crc:08X} -> 0x{target:08X} "
          f"in {len(offsets)} slice(s)")
    base = int(time.time() * 1000) & 0x7FFFFFFF
    for k, off in enumerate(offsets):
        data = content[off:off + TTDB_PUT_MAX_SLICE]
        seq = (base + k) & 0x7FFFFFFF             # fresh (src,seq) per slice
        payload = put_slice_payload(target, belief_id, total, crc, off, data)
        frame = encode_toot(TTDB_PUT, ORCHESTRATOR_ID, seq, payload,
                            flags=FLAG_WANT_ACK)
        acked = send_reliable(ser, reader, frame, target, seq,
                              rto0=rto0, attempts=attempts)
        if not acked:
            return False
        print(f"  slice @{off} ({len(data)}B) ACK on attempt {acked}")
    return True


def push(port, baud, node, src_master, belief_log, out_path, settle, rto0, attempts,
         sense_interval_ms=DEFAULT_SENSE_INTERVAL_MS):
    """Re-author a belief and push it to a node, then verify adoption by pulling the
    node's live TTDB and matching its BELIEF-ADOPTED record (TTN-RFC-0009 §5)."""
    try:
        import serial  # pyserial
    except ImportError:
        sys.exit("pyserial not installed. Run: pip install -r requirements.txt")
    if node not in NODE_IDS:
        sys.exit(f"unknown node '{node}'. choices: {', '.join(NODE_IDS)}")
    target = NODE_IDS[node]

    content = author_belief(src_master, sense_interval_ms)
    crc = crc32(content)
    belief_id = next_belief_id(belief_log)
    os.makedirs(os.path.dirname(os.path.abspath(out_path)) or ".", exist_ok=True)
    with open(out_path, "wb") as f:
        f.write(content)
    print(f"authored belief from {src_master}: {len(content)}B -> {out_path}")

    reader = SerialFrameReader()
    with serial.Serial(port, baud, timeout=0.1) as ser:
        time.sleep(settle)            # opening the port resets the S3 (see pull())
        ser.reset_input_buffer()
        if not push_belief(ser, reader, target, content, belief_id, rto0, attempts):
            sys.exit(f"belief id={belief_id} undelivered after {attempts} attempts")
        time.sleep(0.5)               # let the node commit + apply before we drop the link

    # Verify in a FRESH session. Re-opening the port resets the bridge to a clean
    # state and settles — the conditions under which a standalone bridged pull is
    # reliable. Reusing the push session leaves the bridge mid-stream after the burst,
    # and the verify pull comes back empty (especially after a fresh adoption, when the
    # node is also committing + re-indexing). Re-opening does NOT reset the mesh node,
    # so its just-adopted belief survives. The pull stream is un-ACKed (~1/6 bridged
    # drop), so still retry a few times.
    node_ttdb = None
    belief_bytes = None
    with serial.Serial(port, baud, timeout=0.1) as ser:
        time.sleep(settle)
        ser.reset_input_buffer()
        reader = SerialFrameReader()
        for vattempt in range(1, 4):
            node_ttdb = request_ttdb(ser, reader, target)
            if node_ttdb is not None:
                break
            print(f"  verify pull empty (attempt {vattempt}/3), retrying...")
        # Byte-level readback: pull the node's stored /belief.md so we can diff the
        # actual bytes, not only the CRC attestation (TTN-RFC-0009 §3, §5).
        for _ in range(3):
            belief_bytes = request_ttdb(ser, reader, target, mode=TTDB_REQ_BELIEF)
            if belief_bytes is not None:
                break

    if node_ttdb is None:
        sys.exit("could not pull node TTDB to verify adoption")
    rec = find_belief_adopted(node_ttdb.decode("utf-8", "replace"), belief_id)
    if not rec:
        sys.exit(f"FAIL: node has no BELIEF-ADOPTED id:{belief_id} record")
    ok = rec["bytes"] == len(content) and rec["crc"] == crc
    print(f"\nnode adopted belief id={belief_id}: bytes={rec['bytes']} "
          f"crc={rec['crc']:08X} "
          f"({'MATCH' if ok else 'MISMATCH'} vs sent {len(content)}B/{crc:08X})")
    if not ok:
        sys.exit("DISCREPANCY: adopted bytes/crc disagree with what was pushed")
    # Closing the Dream Cycle: confirm the node didn't just store the belief but
    # acted on its DIRECTIVE (retuned its sense->reason->act cadence, PLAN.md Phase 6).
    applied = rec.get("applied_interval_ms")
    if applied == sense_interval_ms:
        print(f"behavior changed: node retuned sense cadence -> {applied} ms "
              f"(matches DIRECTIVE)")
    elif applied is not None:
        print(f"WARNING: node applied interval_ms:{applied} but DIRECTIVE was "
              f"{sense_interval_ms}")
    else:
        print(f"WARNING: node has no applied:interval_ms — DIRECTIVE not acted on")
    # Byte-exact proof: the bytes the node actually stored equal what we sent.
    if belief_bytes is None:
        print("WARNING: could not read /belief.md back for a byte-diff (CRC still matched)")
    elif belief_bytes == content:
        print(f"stored /belief.md byte-exact ({len(belief_bytes)} B) — full readback MATCH")
    else:
        first = next((i for i in range(min(len(belief_bytes), len(content)))
                      if belief_bytes[i] != content[i]), min(len(belief_bytes), len(content)))
        sys.exit(f"DISCREPANCY: /belief.md readback differs at byte {first} "
                 f"({len(belief_bytes)} B stored vs {len(content)} B sent)")
    append_belief_push_record(belief_log, belief_id, node, len(content), crc)
    print(f"verified — logged BELIEF-PUSH id={belief_id} to {belief_log}")


# --- link percepts (semantic positioning SP0, ttn-semantic-positioning.md) ---
# A node's @LAT97 lane holds one record per flush window, each with a **LINKWIN**
# context line and one **LINK** line per (peer, proto). This is the raw evidence
# SP1 consolidates into @BELIEF:PROXIMITY.
LINKWIN_RE = re.compile(
    r"\*\*LINKWIN\*\*\s+t_ms:(\d+)\s+synced:([01])\s+window_ms:(\d+)")
LINK_RE = re.compile(
    r"\*\*LINK\*\*\s+peer:0x([0-9A-Fa-f]{8})\s+proto:(\w+)\s+n:(\d+)\s+"
    r"rssi_min:(-?\d+)\s+rssi_med:(-?\d+)\s+rssi_max:(-?\d+)")


def parse_link_percepts(text):
    """Parse a TTDB's @LAT97 lane into a list of windows:
    {lane, t_ms, synced, window_ms, links: [{peer, proto, n, min, med, max}]}."""
    windows = []
    cur = None
    for line in text.splitlines():
        if line.startswith("@LAT97LON"):
            lane = int(re.match(r"@LAT97LON(\d+)", line).group(1))
            cur = {"lane": lane, "t_ms": None, "synced": None,
                   "window_ms": None, "links": []}
            windows.append(cur)
            continue
        if line.startswith("@"):     # any other record header ends the window
            cur = None
            continue
        if cur is None:
            continue
        m = LINKWIN_RE.search(line)
        if m:
            cur["t_ms"] = int(m.group(1))
            cur["synced"] = int(m.group(2))
            cur["window_ms"] = int(m.group(3))
            continue
        m = LINK_RE.search(line)
        if m:
            cur["links"].append({
                "peer": int(m.group(1), 16), "proto": m.group(2),
                "n": int(m.group(3)), "min": int(m.group(4)),
                "med": int(m.group(5)), "max": int(m.group(6))})
    return windows


def percepts(port, baud, node, save):
    """Pull a node's TTDB and print its link-percept windows (@LAT97 lane) —
    the SP0 'Done when' check: the node is accumulating positioning evidence."""
    try:
        import serial
    except ImportError:
        sys.exit("pyserial not installed. Run: pip install -r requirements.txt")
    target = NODE_IDS[node]
    reader = SerialFrameReader()
    with serial.Serial(port, baud, timeout=0.1) as ser:
        time.sleep(2.5)              # port-open resets the S3; wait out boot
        ser.reset_input_buffer()
        data = request_ttdb(ser, reader, target, 20.0, TTDB_REQ_WHOLE)
    if data is None:
        sys.exit("no data received (check port, node id, and the key)")
    if save:
        os.makedirs(os.path.dirname(os.path.abspath(save)), exist_ok=True)
        with open(save, "wb") as f:
            f.write(data)
        print(f"wrote {len(data)} bytes to {save}")
    windows = parse_link_percepts(data.decode("utf-8", errors="replace"))
    nobs = sum(l["n"] for w in windows for l in w["links"])
    print(f"{node}: {len(windows)} link-percept window(s), "
          f"{nobs} observation(s) (@LAT97 lane)")
    if not windows:
        print("no @LAT97 records yet — leave the mesh chattering for a window "
              "(default 60 s) and re-run")
        return
    print(f"{'lane':>4}  {'t_ms':>14}  {'sync':>4}  {'win_ms':>7}  "
          f"{'peer':>10}  {'proto':6}  {'n':>5}  {'min':>4}  {'med':>4}  {'max':>4}")
    for w in windows:
        first = True
        for l in w["links"]:
            lead = (f"{w['lane']:>4}  {w['t_ms']:>14}  {w['synced']:>4}  "
                    f"{w['window_ms']:>7}") if first else " " * 35
            first = False
            print(f"{lead}  0x{l['peer']:08X}  {l['proto']:6}  {l['n']:>5}  "
                  f"{l['min']:>4}  {l['med']:>4}  {l['max']:>4}")


# --- proximity consolidation (semantic positioning SP1) ----------------------
# Fold the fleet's @LAT97 link-percept windows into one @BELIEF:PROXIMITY record
# per node pair (ttn-semantic-positioning.md §2.1) — the first Dream-Cycle job of
# Act II. Distance comes from a log-distance path-loss model; until the SP1
# calibration walk writes real parameters, the defaults below apply and sigma is
# widened so the estimate stays honest.
# ORCHESTRATOR_ID (defined top-of-file) appears as a percept peer because the
# laptop's bridged pulls/CMDs are real receptions — but it is not a radio-fixed
# node, so RSSI→distance is meaningless for it; excluded from beliefs.

PATHLOSS_DEFAULTS = {  # per proto: RSSI at d0 + path-loss exponent n
    "espnow": {"rssi_d0": -45.0, "d0_m": 1.0, "n": 2.7},
}
UNCAL_SIGMA_FACTOR = 2.0   # sigma multiplier while the model is uncalibrated
DEFAULT_PROXIMITY_OUT = os.path.join("master", "proximity.md")

PROXIMITY_HEADER = """# Fleet Proximity Beliefs (semantic positioning SP1)

Authored by `companion.py proximity`: each node's @LAT97 link-percept windows
(SP0 evidence) fused into one @BELIEF:PROXIMITY record per node pair
(ttn-semantic-positioning.md §2.1). Estimator: median of per-window rssi_max
per direction (the strongest receptions sit nearest line-of-sight truth;
fading only subtracts), directions averaged; sigma from window spread +
direction asymmetry, widened while the path-loss model is uncalibrated.
"""


DEFAULT_CALIBRATION = os.path.join("master", "calibration.md")

CALIBRATION_HEADER = """# Fleet Path-Loss Calibration (semantic positioning SP1)

Authored by `companion.py calibrate` from a measured calibration walk
(ttn-semantic-positioning.md Appendix B): per-station fused RSSI vs ground-truth
distance, least-squares fit of the log-distance model
RSSI(d) = rssi_d0 - 10*n*log10(d/d0). `proximity` reads this file and uses the
fitted model (and drops its uncalibrated-sigma penalty). The model is only
trustworthy inside valid_range_m — the rssi_d0 intercept is an extrapolation,
not a near-field measurement.
"""

CALIB_RE = re.compile(
    r"@BELIEF:CALIBRATION\s+proto:(\w+)[\s\S]*?rssi_d0_dbm:\s*(-?[\d.]+)"
    r"[\s\S]*?d0_m:\s*([\d.]+)[\s\S]*?\bn:\s*([\d.]+)[\s\S]*?rmse_db:\s*([\d.]+)")


def fit_pathloss(stations):
    """stations: [(d_m, rssi_dbm), ...] -> (rssi_d0 @ 1 m, n, rmse_db).
    Least squares on RSSI = rssi_d0 - n * (10*log10(d))."""
    import math
    xs = [10.0 * math.log10(d) for d, _ in stations]
    ys = [r for _, r in stations]
    mx, my = sum(xs) / len(xs), sum(ys) / len(ys)
    sxx = sum((x - mx) ** 2 for x in xs)
    if sxx == 0:
        sys.exit("calibrate: need stations at >= 2 distinct distances")
    slope = sum((x - mx) * (y - my) for x, y in zip(xs, ys)) / sxx
    n = -slope
    rssi_d0 = my - slope * mx
    resid = [y - (rssi_d0 + slope * x) for x, y in zip(xs, ys)]
    rmse = (sum(r * r for r in resid) / len(resid)) ** 0.5
    return rssi_d0, n, rmse


def load_calibration(path):
    """Parse @BELIEF:CALIBRATION records -> {proto: params}. {} if no file."""
    try:
        with open(path, encoding="utf-8") as f:
            text = f.read()
    except FileNotFoundError:
        return {}
    calib = {}
    for m in CALIB_RE.finditer(text):
        calib[m.group(1)] = {"rssi_d0": float(m.group(2)),
                             "d0_m": float(m.group(3)),
                             "n": float(m.group(4)),
                             "rmse_db": float(m.group(5))}
    return calib


def calibrate(proto, station_args, out, note):
    """SP1 calibration: fit the walk's station data, write @BELIEF:CALIBRATION."""
    stations = []
    for s in station_args:
        d, _, r = s.partition(":")
        stations.append((float(d), float(r)))
    if len(stations) < 2:
        sys.exit("calibrate: need at least 2 --station d_m:rssi points")
    rssi_d0, n, rmse = fit_pathloss(stations)
    dmin, dmax = min(d for d, _ in stations), max(d for d, _ in stations)

    os.makedirs(os.path.dirname(os.path.abspath(out)) or ".", exist_ok=True)
    now_iso = time.strftime("%Y-%m-%dT%H:%M:%SZ", time.gmtime())
    st_str = ", ".join(f"{d}:{r}" for d, r in stations)
    with open(out, "w", encoding="utf-8", newline="\n") as f:
        f.write(CALIBRATION_HEADER)
        f.write(f"\n---\n\n@BELIEF:CALIBRATION proto:{proto}\n"
                f"rssi_d0_dbm: {rssi_d0:.1f}\n"
                f"d0_m: 1.0\n"
                f"n: {n:.2f}\n"
                f"rmse_db: {rmse:.1f}\n"
                f"valid_range_m: {dmin}-{dmax}\n"
                f"stations: {st_str}\n"
                f"note: {note}\n"
                f"conf: 0.75\n"
                f"touched: {now_iso}\n")
    print(f"fit: RSSI(d) = {rssi_d0:.1f} - {10 * n:.1f}*log10(d)   "
          f"(n = {n:.2f}, rmse = {rmse:.1f} dB, valid {dmin}-{dmax} m)")
    for d, r in stations:
        pred = rssi_d0 - 10.0 * n * (0 if d == 1 else __import__("math").log10(d))
        print(f"  {d:>6.2f} m: obs {r:>6.1f}  model {pred:>6.1f}  "
              f"resid {r - pred:>+5.1f} dB")
    print(f"wrote {out}")


def rssi_to_dist_m(rssi_dbm, proto, calib=None):
    p = (calib or {}).get(proto) or PATHLOSS_DEFAULTS.get(proto)
    if p is None:
        return None
    return p["d0_m"] * 10.0 ** ((p["rssi_d0"] - rssi_dbm) / (10.0 * p["n"]))


def _median(xs):
    s = sorted(xs)
    m = len(s) // 2
    return s[m] if len(s) % 2 else (s[m - 1] + s[m]) / 2.0


def consolidate_proximity(windows_by_node, calib=None, last=None):
    """windows_by_node: {node_name: [parse_link_percepts window, ...]}.
    calib: load_calibration() output (fitted path-loss per proto), or None.
    last: use only each node's newest N windows — the recency filter. A node
    that moved (the calibration walk!) leaves stale-distance windows behind;
    position is a *current* belief, so recent evidence must be able to win.
    Returns a list of pair-belief dicts, one per (unordered pair, proto)."""
    id_to_name = {v: k for k, v in NODE_IDS.items()}
    directed = {}  # (obs_id, peer_id, proto) -> {"maxes": [...], "n": int, "windows": int}
    for name, wins in windows_by_node.items():
        obs_id = NODE_IDS[name]
        if last:
            wins = wins[-last:]
        for w in wins:
            for l in w["links"]:
                if l["peer"] == ORCHESTRATOR_ID:
                    continue  # laptop pseudo-peer: real reception, useless range
                k = (obs_id, l["peer"], l["proto"])
                d = directed.setdefault(k, {"maxes": [], "n": 0, "windows": 0})
                d["maxes"].append(l["max"])
                d["n"] += l["n"]
                d["windows"] += 1

    pairs = {}
    for (a, b, proto), d in directed.items():
        key = (min(a, b), max(a, b), proto)
        pairs.setdefault(key, {})[(a, b)] = d

    beliefs = []
    for (lo, hi, proto), dirs in sorted(pairs.items()):
        ab = dirs.get((lo, hi))          # lo hears hi
        ba = dirs.get((hi, lo))          # hi hears lo
        ests, all_maxes, n_obs = [], [], 0
        for d in (ab, ba):
            if d:
                ests.append(_median(d["maxes"]))
                all_maxes.extend(d["maxes"])
                n_obs += d["n"]
        rssi_est = sum(ests) / len(ests)
        asym = abs(ests[0] - ests[1]) if len(ests) == 2 else 0.0
        spread = (max(all_maxes) - min(all_maxes)) if len(all_maxes) > 1 else 0.0
        calibrated = bool(calib) and proto in calib
        rmse = calib[proto]["rmse_db"] if calibrated else 0.0
        rssi_sigma = max(3.0, spread / 2.0, asym / 2.0, rmse)

        dist = rssi_to_dist_m(rssi_est, proto, calib)
        d_lo = rssi_to_dist_m(rssi_est + rssi_sigma, proto, calib)  # stronger = closer
        d_hi = rssi_to_dist_m(rssi_est - rssi_sigma, proto, calib)
        sig_factor = 1.0 if calibrated else UNCAL_SIGMA_FACTOR
        sigma = ((d_hi - d_lo) / 2.0) * sig_factor if dist else None

        # Confidence: grows with sample count, shrinks with direction asymmetry;
        # capped lower while uncalibrated (TBEW-style honesty, heuristic for now).
        conf = 0.3 + 0.3 * min(1.0, n_obs / 200.0) + 0.2 * max(0.0, 1.0 - asym / 6.0)
        conf = round(max(0.1, min(0.85 if calibrated else 0.7, conf)), 2)

        beliefs.append({
            "a": id_to_name.get(lo, f"0x{lo:08X}"),
            "b": id_to_name.get(hi, f"0x{hi:08X}"),
            "proto": proto, "rssi_est": round(rssi_est, 1),
            "rssi_ab": (round(ests[0], 1) if ab else None),
            "rssi_ba": (round(ests[-1], 1) if ba else None),
            "n_ab": ab["n"] if ab else 0, "n_ba": ba["n"] if ba else 0,
            "windows": (ab["windows"] if ab else 0) + (ba["windows"] if ba else 0),
            "asym_db": round(asym, 1), "rssi_sigma_db": round(rssi_sigma, 1),
            "dist_est_m": (round(dist, 2) if dist else None),
            "dist_sigma_m": (round(sigma, 2) if sigma else None),
            "n_obs": n_obs, "conf": conf, "calibrated": calibrated,
        })
    return beliefs


def proximity(port, baud, nodes, out, do_pull, settle,
              calib_path=DEFAULT_CALIBRATION, last=None, clear=False):
    """SP1: pull each node's TTDB, fuse the @LAT97 lanes into @BELIEF:PROXIMITY
    records (master/proximity.md), and print the pair table."""
    calib = load_calibration(calib_path)
    if calib:
        for proto, p in calib.items():
            print(f"calibration: {proto} RSSI(d) = {p['rssi_d0']:.1f} - "
                  f"{10 * p['n']:.1f}*log10(d)  (rmse {p['rmse_db']} dB)")
    master_dir = os.path.dirname(out) or "master"
    node_paths = {n: os.path.join(master_dir, f"{n}.md") for n in nodes}
    for n in nodes:
        if n not in NODE_IDS:
            sys.exit(f"unknown node '{n}'. choices: {', '.join(NODE_IDS)}")

    if do_pull:
        try:
            import serial
        except ImportError:
            sys.exit("pyserial not installed. Run: pip install -r requirements.txt")
        reader = SerialFrameReader()
        with serial.Serial(port, baud, timeout=0.1) as ser:
            time.sleep(settle)
            ser.reset_input_buffer()
            for n in nodes:
                data = request_ttdb(ser, reader, NODE_IDS[n])
                if data is None:
                    print(f"warning: no TTDB from {n}; using existing file if present")
                    continue
                os.makedirs(os.path.dirname(os.path.abspath(node_paths[n])) or ".",
                            exist_ok=True)
                with open(node_paths[n], "wb") as f:
                    f.write(data)
                print(f"pulled {n}: {len(data)} B -> {node_paths[n]}")

    windows_by_node = {}
    for n in nodes:
        try:
            with open(node_paths[n], encoding="utf-8", errors="replace") as f:
                windows_by_node[n] = parse_link_percepts(f.read())
        except FileNotFoundError:
            print(f"warning: {node_paths[n]} missing; {n} contributes nothing")
    beliefs = consolidate_proximity(windows_by_node, calib, last)

    os.makedirs(os.path.dirname(os.path.abspath(out)) or ".", exist_ok=True)
    now_iso = time.strftime("%Y-%m-%dT%H:%M:%SZ", time.gmtime())
    with open(out, "w", encoding="utf-8", newline="\n") as f:
        f.write(PROXIMITY_HEADER)
        for b in beliefs:
            f.write(f"\n---\n\n@BELIEF:PROXIMITY @pair({b['a']}, {b['b']})\n"
                    f"proto: {b['proto']}\n"
                    f"rssi_est_dbm: {b['rssi_est']}\n"
                    f"rssi_ab_dbm: {b['rssi_ab']}   # {b['a']} hears {b['b']}"
                    f" (n:{b['n_ab']})\n"
                    f"rssi_ba_dbm: {b['rssi_ba']}   # {b['b']} hears {b['a']}"
                    f" (n:{b['n_ba']})\n"
                    f"asym_db: {b['asym_db']}\n"
                    f"dist_est_m: {b['dist_est_m']}\n"
                    f"dist_sigma_m: {b['dist_sigma_m']}\n"
                    f"n_obs: {b['n_obs']}\n"
                    f"windows: {b['windows']}\n"
                    f"sources: {{ rssi: 1.0 }}\n"
                    + (f"calibrated: yes   # {calib_path} "
                       f"{calib.get(b['proto'])}\n" if b["calibrated"] else
                       f"calibrated: no   # default path-loss "
                       f"{PATHLOSS_DEFAULTS.get(b['proto'])} — run the SP1 "
                       f"calibration walk\n")
                    + f"conf: {b['conf']}\n"
                    f"touched: {now_iso}\n")

    print(f"\nproximity: {len(beliefs)} pair belief(s) from "
          f"{{{', '.join(sorted(windows_by_node))}}}")
    print(f"{'pair':<28} {'proto':6} {'rssi':>6} {'asym':>5} {'dist_m':>7} "
          f"{'sigma_m':>8} {'n':>5} {'conf':>5}")
    for b in beliefs:
        print(f"{b['a'] + ' <-> ' + b['b']:<28} {b['proto']:6} "
              f"{b['rssi_est']:>6} {b['asym_db']:>5} {b['dist_est_m']:>7} "
              f"{b['dist_sigma_m']:>8} {b['n_obs']:>5} {b['conf']:>5}")
    if all(b["calibrated"] for b in beliefs) and beliefs:
        print(f"\nwrote {out}  (calibrated model — mind the fit's valid range)")
    else:
        print(f"\nwrote {out}  (uncalibrated model — distances are order-of-"
              f"magnitude until the calibration walk)")

    # The Dream-Cycle prune (SP1): the consumed raw percepts are consolidated
    # into beliefs above, so tell each node to drop its @LAT97 lane (also
    # un-wedges a node that hit LINKPERCEPT_MAX_LANE). Fresh serial session;
    # want_ack so an unacked clear is loud, not silent.
    if clear and port:
        import serial
        print("clearing consumed @LAT97 lanes (CMD clear-percepts)...")
        reader = SerialFrameReader()
        with serial.Serial(port, baud, timeout=0.1) as ser:
            time.sleep(settle)
            ser.reset_input_buffer()
            for n in nodes:
                target = NODE_IDS[n]
                payload = bytes([CMD_CLEAR_PERCEPTS]) + struct.pack("<I", target)
                seq = int(time.time() * 1000) & 0x7FFFFFFF
                frame = encode_toot(CMD, ORCHESTRATOR_ID, seq, payload,
                                    flags=FLAG_WANT_ACK)
                acked = send_reliable(ser, reader, frame, target, seq)
                print(f"  {n}: " + (f"cleared (ACK attempt {acked})" if acked
                                    else "NO ACK — lane NOT cleared"))


def main():
    ap = argparse.ArgumentParser(description="robot_team orchestrator companion")
    sub = ap.add_subparsers(dest="cmd", required=True)
    p = sub.add_parser("pull", help="pull a node's TTDB (or stored belief) over the link")
    p.add_argument("--port", required=True, help="serial port (COM5, /dev/ttyACM0)")
    p.add_argument("--baud", type=int, default=115200)
    p.add_argument("--node", required=True, choices=list(NODE_IDS))
    p.add_argument("--out", required=True, help="output .md path")
    p.add_argument("--timeout", type=float, default=20.0)
    p.add_argument("--file", choices=["ttdb", "belief"], default="ttdb",
                   help="which object to pull: the live TTDB (default) or /belief.md")
    p.add_argument("--drop", default="",
                   help="comma-separated data-slice indices to discard on the first "
                        "pass (induced loss; forces the TTDB_REQ_RANGE self-heal). "
                        "live TTDB only. e.g. --drop 1,3")

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

    sy = sub.add_parser("sync", help="push a timestamp to the fleet (TTN-RFC-0008)")
    sy.add_argument("--port", required=True, help="bridge serial port (COM6, ...)")
    sy.add_argument("--baud", type=int, default=115200)
    sy.add_argument("--expect", default="v4a_bridge,k10_1",
                    help="comma-separated nodes expected to ACK the sync")
    sy.add_argument("--master", default=DEFAULT_MASTER_SYNC,
                    help="laptop master sync log to append")
    sy.add_argument("--settle", type=float, default=0.5,
                    help="post-open drain (s); sync/verify open WITHOUT reset")
    sy.add_argument("--rto0", type=float, default=0.5)
    sy.add_argument("--attempts", type=int, default=4)

    vf = sub.add_parser("verify",
                        help="confirm each node has the sync record + measure skew")
    vf.add_argument("--port", required=True, help="bridge serial port (COM6, ...)")
    vf.add_argument("--baud", type=int, default=115200)
    vf.add_argument("--sync-id", type=int, required=True, dest="sync_id",
                    help="the sync_id to verify (printed by `sync`)")
    vf.add_argument("--nodes", default="v4a_bridge,k10_1",
                    help="comma-separated nodes to check")
    vf.add_argument("--bound-ms", type=float, default=50.0, dest="bound_ms")
    vf.add_argument("--master", default=DEFAULT_MASTER_SYNC)
    vf.add_argument("--settle", type=float, default=0.5)
    vf.add_argument("--probes", type=int, default=5)

    bd = sub.add_parser("band",
                        help="measure fleet pulse phase tightness (TTN-RFC-0010)")
    bd.add_argument("--port", required=True, help="bridge serial port (COM6, ...)")
    bd.add_argument("--baud", type=int, default=115200)
    bd.add_argument("--nodes", default="v4a_bridge,v4b_relay,k10_1",
                    help="comma-separated nodes to probe")
    bd.add_argument("--bound-ms", type=float, default=50.0, dest="bound_ms")
    bd.add_argument("--probes", type=int, default=5)
    bd.add_argument("--settle", type=float, default=0.5)
    bd.add_argument("--watch", action="store_true",
                    help="refresh the table live until Ctrl-C")
    bd.add_argument("--interval", type=float, default=1.0,
                    help="seconds between refreshes (--watch)")

    cm = sub.add_parser("cmd", help="send a CMD to a node (ping/set-led/clear-led)")
    cm.add_argument("--port", required=True, help="serial port (COM5, /dev/ttyACM0)")
    cm.add_argument("--baud", type=int, default=115200)
    cm.add_argument("--node", required=True, choices=list(NODE_IDS))
    cm.add_argument("--op", required=True, choices=list(CMD_OPS))
    cm.add_argument("--rgb", default=None, help="RRGGBB hex for set-led (e.g. FF0000)")
    cm.add_argument("--freq", type=int, default=880, help="beep frequency Hz")
    cm.add_argument("--dur-ms", type=int, default=200, dest="dur_ms",
                    help="beep duration ms")
    cm.add_argument("--interval-ms", type=int, default=None, dest="interval_ms",
                    help="agent sense/act cadence ms (set-interval)")
    cm.add_argument("--settle", type=float, default=2.5)
    cm.add_argument("--rto0", type=float, default=0.5)
    cm.add_argument("--attempts", type=int, default=4)

    pc = sub.add_parser(
        "percepts",
        help="pull + print a node's link-percept windows (@LAT97, SP0)")
    pc.add_argument("--port", required=True, help="serial port (COM6, direct or bridge)")
    pc.add_argument("--baud", type=int, default=115200)
    pc.add_argument("--node", required=True, choices=list(NODE_IDS))
    pc.add_argument("--save", default=None,
                    help="also write the pulled TTDB to this path")

    px = sub.add_parser(
        "proximity",
        help="SP1: fuse fleet @LAT97 percepts into @BELIEF:PROXIMITY per pair")
    px.add_argument("--port", default=None,
                    help="port to pull nodes from (omit / --no-pull to use files)")
    px.add_argument("--baud", type=int, default=115200)
    px.add_argument("--nodes", default="v4a_bridge,v4b_relay,tdeck_1")
    px.add_argument("--out", default=DEFAULT_PROXIMITY_OUT)
    px.add_argument("--no-pull", action="store_true", dest="no_pull",
                    help="don't pull; read existing master/<node>.md")
    px.add_argument("--settle", type=float, default=2.5)
    px.add_argument("--calibration", default=DEFAULT_CALIBRATION,
                    help="fitted path-loss file (companion.py calibrate)")
    px.add_argument("--last", type=int, default=None,
                    help="use only each node's newest N windows (recency "
                         "filter — a moved node leaves stale windows behind)")
    px.add_argument("--clear", action="store_true",
                    help="after consolidating, CMD each node to drop its "
                         "@LAT97 lane (the Dream-Cycle prune; needs --port)")

    ca = sub.add_parser(
        "calibrate",
        help="SP1: fit the path-loss model from calibration-walk stations")
    ca.add_argument("--proto", default="espnow", choices=["espnow", "lora", "ble"])
    ca.add_argument("--station", action="append", required=True,
                    help="d_m:rssi_dbm (repeat per station, e.g. --station 9:-54.8)")
    ca.add_argument("--out", default=DEFAULT_CALIBRATION)
    ca.add_argument("--note", default="",
                    help="provenance: how the station RSSI values were derived")

    mo = sub.add_parser("monitor", help="live fleet telemetry table (poll GET_STATUS)")
    mo.add_argument("--port", required=True, help="serial port (COM5, /dev/ttyACM0)")
    mo.add_argument("--baud", type=int, default=115200)
    mo.add_argument("--nodes", default="v4a_bridge,k10_1")
    mo.add_argument("--interval", type=float, default=1.0,
                    help="seconds per poll round")
    mo.add_argument("--rounds", type=int, default=0, help="0 = until Ctrl-C")
    mo.add_argument("--settle", type=float, default=2.5)

    rc = sub.add_parser(
        "reconcile",
        help="Dream-Cycle seed: consolidate node sync logs into the master")
    rc.add_argument("--port", default=None,
                    help="port to pull nodes from (omit / --no-pull to use files)")
    rc.add_argument("--baud", type=int, default=115200)
    rc.add_argument("--nodes", default="k10_1")
    rc.add_argument("--master", default=DEFAULT_MASTER_SYNC,
                    help="laptop master sync log")
    rc.add_argument("--out", default=os.path.join("master", "consolidated.md"))
    rc.add_argument("--no-pull", action="store_true", dest="no_pull",
                    help="don't pull; read existing master/<node>.md")
    rc.add_argument("--settle", type=float, default=2.5)

    pb = sub.add_parser(
        "push",
        help="re-author a belief and push it back to a node (TTN-RFC-0009)")
    pb.add_argument("--port", required=True, help="serial port (COM3, /dev/ttyACM0)")
    pb.add_argument("--baud", type=int, default=115200)
    pb.add_argument("--node", required=True, choices=list(NODE_IDS))
    pb.add_argument("--from", dest="src_master", default=DEFAULT_MASTER_SYNC,
                    help="master sync log to author the belief from")
    pb.add_argument("--belief-log", default=DEFAULT_BELIEF_LOG, dest="belief_log",
                    help="laptop belief push log (monotonic belief_id source)")
    pb.add_argument("--out", default=DEFAULT_BELIEF_OUT,
                    help="where to write the authored belief locally")
    pb.add_argument("--settle", type=float, default=2.5)
    pb.add_argument("--rto0", type=float, default=0.5)
    pb.add_argument("--attempts", type=int, default=4)
    pb.add_argument("--sense-interval-ms", type=int, default=DEFAULT_SENSE_INTERVAL_MS,
                    dest="sense_interval_ms",
                    help="cadence the belief DIRECTIVE tells the node to adopt")

    args = ap.parse_args()

    if args.cmd == "pull":
        drop = {int(x) for x in args.drop.split(",") if x.strip() != ""}
        pull(args.port, args.baud, args.node, args.out, args.timeout, args.file, drop)
    elif args.cmd == "ping":
        ping(args.port, args.baud, args.node, args.settle, args.rto0,
             args.attempts)
    elif args.cmd == "reltest":
        reltest(args.port, args.baud, args.node, args.size, args.settle,
                args.rto0, args.attempts)
    elif args.cmd == "sync":
        sync(args.port, args.baud, [s for s in args.expect.split(",") if s],
             args.master, args.settle, args.rto0, args.attempts)
    elif args.cmd == "verify":
        verify(args.port, args.baud, [s for s in args.nodes.split(",") if s],
               args.sync_id, args.bound_ms, args.master, args.settle, args.probes)
    elif args.cmd == "band":
        band(args.port, args.baud, [s for s in args.nodes.split(",") if s],
             args.bound_ms, args.probes, args.settle, args.watch, args.interval)
    elif args.cmd == "cmd":
        send_cmd(args.port, args.baud, args.node, args.op, args.rgb, args.freq,
                 args.dur_ms, args.interval_ms, args.settle, args.rto0, args.attempts)
    elif args.cmd == "percepts":
        percepts(args.port, args.baud, args.node, args.save)
    elif args.cmd == "proximity":
        do_pull = bool(args.port) and not args.no_pull
        proximity(args.port, args.baud, [s for s in args.nodes.split(",") if s],
                  args.out, do_pull, args.settle, args.calibration, args.last,
                  args.clear)
    elif args.cmd == "calibrate":
        calibrate(args.proto, args.station, args.out, args.note)
    elif args.cmd == "monitor":
        monitor(args.port, args.baud, [s for s in args.nodes.split(",") if s],
                args.interval, args.rounds, args.settle)
    elif args.cmd == "reconcile":
        do_pull = bool(args.port) and not args.no_pull
        reconcile(args.port, args.baud, [s for s in args.nodes.split(",") if s],
                  args.master, args.out, do_pull, args.settle)
    elif args.cmd == "push":
        push(args.port, args.baud, args.node, args.src_master, args.belief_log,
             args.out, args.settle, args.rto0, args.attempts, args.sense_interval_ms)


if __name__ == "__main__":
    main()
