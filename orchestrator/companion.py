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
import math
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
    "cardputer_1": 0x00000300,
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
TTDB_REQ_RECORDING = 3  # the last beat-scheduled audio capture (CMD_RECORD), in RAM

# RECHDR (Toot.h) — the header on a CMD_RECORD capture. Every node reports what it
# BELIEVED the time was at sample 0 rather than assuming the fleet agrees, so the
# 15-25 ms common-mode wander measured on 2026-07-28 becomes a correction here instead
# of an error baked into the audio.
RECHDR_MAGIC = 0x31524554   # "TER1"
RECHDR_LEN = 64
REC_FLAG_SYNCED = 1 << 0
REC_FLAG_LATE = 1 << 1
REC_FLAG_SELF = 1 << 2

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
CMD_GET_GPS = 9      # GPS-bearing node replies a GPS PERCEPT (SP2 roaming anchor)
CMD_SET_SCENE = 10   # args: scene_id u16 LE — move the band to a scene of the song.
                     # Only the CONDUCTOR owns the chart, so only it applies + ACKs;
                     # every other node learns the scene from the next beacon. That is
                     # why `--node broadcast` is safe here: at most one node answers.
NODE_BROADCAST = 0xFFFFFFFF
# GPS PERCEPT payload (Toot.h GPS_PERCEPT_PAYLOAD_LEN): lat_1e7 i32 | lon_1e7 i32 |
# alt_cm i32 | quality u8 | sats u8 | hdop_x10 u16 | epoch_ms u64. 24 B distinguishes
# it from a STATUS PERCEPT (15/43). Returned in answer to CMD_GET_GPS.
GPS_PERCEPT_PAYLOAD_LEN = 24
# User-facing `cmd` ops only (GET_STATUS/GET_GPS are internal to monitor/gps).
CMD_OPS = {"ping": CMD_PING, "set-led": CMD_SET_LED, "clear-led": CMD_CLEAR_LED,
           "beep": CMD_BEEP, "set-interval": CMD_SET_INTERVAL,
           "play": CMD_PLAY, "stop": CMD_STOP,
           "clear-percepts": CMD_CLEAR_PERCEPTS, "set-scene": CMD_SET_SCENE}
CMD_RECORD = 11      # args: start_band_epoch_ms u64 LE | dur_beats u16 LE
CMD_GET_INTERO = 12  # node replies an INTERO PERCEPT — its sense of its OWN body
# INTERO PERCEPT payload (Toot.h INTERO_PERCEPT_PAYLOAD_LEN): bat_mv u16 | bat_pct u8 |
# bat_trend i8 | die_c_x10 i16 | maxalloc_kb u16 | uptime_s u32 | worst_loop_ms u16 |
# beat_period_ms u16 | conductor_id u32 | flags u8. 21 B distinguishes it from a STATUS
# (15/43/45) or GPS (24) PERCEPT. Returned in answer to CMD_GET_INTERO.
INTERO_PERCEPT_PAYLOAD_LEN = 21
INTERO_SYNCED, INTERO_CONDUCTOR, INTERO_PLAYING = 1, 2, 4

# STATUS payload (Toot.h): cursor_lat i16 | cursor_lon i16 | temp_x100 i16 |
# flags u8 | epoch_ms u64. Returned as a PERCEPT in answer to CMD_GET_STATUS.
STATUS_PAYLOAD_LEN = 15
STATUS_WARM = 1 << 0
STATUS_LED_OVERRIDE = 1 << 1
STATUS_SYNCED = 1 << 2

# Optional PULSE telemetry tail (TTN-RFC-0010 §8), appended to STATUS after the 15
# base bytes when a node is built with USE_PULSE: conductor_id u32 | era u32 |
# beat_period_ms u16 | pulse_epoch u64 | downbeat_epoch u64 | beat_in_bar u8 | pstate
# u8 | scene_id u16 (v2). `band` reads it to measure phase; `monitor` ignores it (reads
# only the prefix). The scene tail is additive, so a node still on v1 firmware parses
# fine and just reports scene 0.
STATUS_PULSE_PAYLOAD_LEN_V1 = 43
STATUS_PULSE_PAYLOAD_LEN = 45
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
    if len(payload) < STATUS_PULSE_PAYLOAD_LEN_V1:
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
        # v2 tail; a node on v1 firmware reports scene 0 rather than nothing.
        "scene": (struct.unpack("<H", payload[43:45])[0]
                  if len(payload) >= STATUS_PULSE_PAYLOAD_LEN else 0),
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
                if not t or t["type"] != ACK:
                    continue
                # A broadcast has no single expected responder, so the src filter
                # cannot apply — the band-wide ops are designed so that exactly one
                # node answers (only the conductor applies a scene change), and the
                # echoed (src,seq,chunk) below still proves the ACK is ours.
                if target != NODE_BROADCAST and t["src"] != target:
                    continue
                pa = parse_ack(t)
                if pa and pa[0] == ORCHESTRATOR_ID and pa[1] == seq \
                        and pa[2] == chunk:
                    if target == NODE_BROADCAST:
                        print(f"  ACK from 0x{t['src']:08X} (answered the broadcast)")
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
             settle, rto0, attempts, scene=None):
    """Send an orchestrator CMD (companion.md §4b) addressed to one node and confirm
    it via the want_ack ACK. Ops: ping, set-led RRGGBB, clear-led, beep, set-interval,
    set-scene. `node` may be "broadcast" for the band-wide ops (play/stop/set-scene)."""
    try:
        import serial  # pyserial
    except ImportError:
        sys.exit("pyserial not installed. Run: pip install -r requirements.txt")
    if node == "broadcast":
        target = NODE_BROADCAST
    elif node not in NODE_IDS:
        sys.exit(f"unknown node '{node}'. choices: {', '.join(NODE_IDS)}, broadcast")
    else:
        target = NODE_IDS[node]
    if op not in CMD_OPS:
        sys.exit(f"unknown op '{op}'. choices: {', '.join(CMD_OPS)}")
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
    elif opcode == CMD_SET_SCENE:
        if scene is None:
            sys.exit("set-scene needs --scene N (e.g. --scene 1)")
        args = struct.pack("<H", scene & 0xFFFF)
        detail = f" scene {scene}"

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
        if opcode == CMD_SET_SCENE:
            # Only the conductor owns the chart, so a follower stays deliberately
            # silent here. That is the most likely reason for no ACK, not a lost frame.
            print("no ACK — only the CONDUCTOR applies a scene change. Check who holds"
                  " the baton (`band` marks it with *) and target that node, or use"
                  " `--node broadcast`.")
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
    print(f"{'node':<12}{'conductor':<13}{'era':>4}{'scene':>6}{'bpm':>6}{'beat':>5}"
          f"{'phase_ms':>10}{'skew_ms':>9}{'rtt_ms':>8}")
    conductors = set()
    scenes = set()
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
        scenes.add(r.get("scene", 0))
        bpm = 60000.0 / r["period_ms"] if r["period_ms"] else 0.0
        skew = circular_diff(phases[n], phases[ref], r["period_ms"]) if ref else 0.0
        max_skew = max(max_skew, abs(skew))
        label = f"0x{r['conductor_id']:08X}" + ("*" if r.get("conductor") else "")
        flag = "" if abs(skew) <= bound_ms else "  <-- OUT"
        print(f"{n:<12}{label:<13}{r['era']:>4}{r.get('scene', 0):>6}{bpm:>6.0f}"
              f"{r['beat_in_bar']:>5}"
              f"{phases[n]:>10.1f}{skew:>+9.1f}{r['rtt']:>7.0f}{flag}")
        if abs(skew) > bound_ms:
            ok = False
    if len(conductors) > 1:
        print("  ! not converged — "
              f"{len(conductors)} conductors: "
              f"{', '.join(f'0x{c:08X}' for c in sorted(conductors))}")
        ok = False
    if len(scenes) > 1:
        # One shared chart means one shared scene: a band split across scenes is
        # playing different parts of the song, which is a real failure, not cosmetic.
        print(f"  ! not converged — {len(scenes)} scenes: "
              f"{', '.join(str(s) for s in sorted(scenes))}")
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


def parse_rechdr(data):
    """Read a RECHDR (Toot.h). Returns a dict, or None if this isn't one."""
    if len(data) < RECHDR_LEN or struct.unpack_from("<I", data, 0)[0] != RECHDR_MAGIC:
        return None
    node, rate, samples = struct.unpack_from("<III", data, 4)
    start, req, offset, fleet = struct.unpack_from("<QQqQ", data, 16)
    era, cond, period = struct.unpack_from("<IIH", data, 48)
    return {"node": node, "rate": rate, "samples": samples, "start": start,
            "req": req, "offset": offset, "fleet": fleet, "era": era,
            "conductor": cond, "period": period, "flags": data[58]}


def write_wav(path, pcm, rate):
    """Minimal 16-bit mono PCM WAV. Not worth a dependency."""
    n = len(pcm)
    with open(path, "wb") as f:
        f.write(b"RIFF" + struct.pack("<I", 36 + n) + b"WAVE")
        f.write(b"fmt " + struct.pack("<IHHIIHH", 16, 1, 1, rate, rate * 2, 2, 16))
        f.write(b"data" + struct.pack("<I", n) + pcm)


def record(port, baud, nodes, lead_beats, dur_beats, outdir, settle, copies,
           self_test=False):
    """Beat-scheduled fleet recording: every node captures the SAME window of wall-clock
    time, because the band clock (TTN-RFC-0010) is a time base they already share.

    Why schedule it rather than trigger on a threshold: the @LAT94 transient timestamps
    fire at a different point on the waveform depending on distance and gain, so their
    error is the SHAPE of the sound rather than the geometry (cardputer-sensorium.md §6).
    A scheduled capture has no threshold anywhere in the path, so two nodes that heard
    one clap can be cross-correlated directly.

    The laptop has no per-beat role. It reads one node's chart, projects the requested
    beat onto the band clock, and broadcasts the resulting instant; each node then
    compares that instant against its OWN clock and stamps what it believed."""
    try:
        import serial  # noqa: F401
    except ImportError:
        sys.exit("pyserial not installed. Run: pip install -r requirements.txt")
    for name in nodes:
        if name not in NODE_IDS:
            sys.exit(f"unknown node '{name}'. choices: {', '.join(NODE_IDS)}")

    reader = SerialFrameReader()
    ser = open_serial_no_reset(port, baud)   # a reset would wipe the very clock we use
    try:
        time.sleep(settle)
        ser.reset_input_buffer()

        # Read the chart from whichever node answers. Any node will do: they share the
        # chart, and disagreement about it is exactly what the per-node stamps capture.
        chart = None
        for name in nodes:
            got = status_probe(ser, reader, NODE_IDS[name], probes=5)
            if got and not got.get("plain") and got.get("playing"):
                chart = got
                print(f"chart from {name}: era {got['era']} "
                      f"conductor 0x{got['conductor_id']:08X} {got['period_ms']} ms/beat")
                break
        if chart is None:
            sys.exit("no node reported a pulse chart — nothing to schedule against")

        period = chart["period_ms"] or 500
        # band_epoch(laptop_ms) = pulse_epoch + (laptop_ms - t_mid)
        now_band = chart["pulse_epoch"] + (time.time() * 1000.0 - chart["t_mid"])
        beats_now = (now_band - chart["downbeat"]) / float(period)
        # Round UP to a downbeat at least `lead_beats` away. The lead is not politeness:
        # this fleet's percept-window flush stalls a node's loop for 60-220 ms, nearly
        # half a beat, so a node caught mid-flush would miss a start scheduled too close.
        target = int(math.ceil(beats_now)) + lead_beats
        target += (-target) % 4                      # next downbeat (meter 4)
        start = int(chart["downbeat"] + target * period)
        wait_s = (start - now_band) / 1000.0
        print(f"start at band epoch {start} (beat {target}), "
              f"in {wait_s:.2f} s, for {dur_beats} beats "
              f"({dur_beats * period / 1000.0:.2f} s)")

        args = struct.pack("<QH", start, dur_beats)
        payload = bytes([CMD_RECORD]) + struct.pack("<I", NODE_BROADCAST) + args
        base = int(time.time() * 1000) & 0x7FFFFFFF
        for k in range(copies):
            # Distinct seqs, or the radio dedup drops the copies. Re-arming the SAME
            # instant is a no-op on the node, so duplicates are safe by construction.
            write_serial_frame(ser, encode_toot(CMD, ORCHESTRATOR_ID, base + k, payload))
            time.sleep(0.02)
        print(f"broadcast CMD_RECORD x{copies}")

        window_s = dur_beats * period / 1000.0
        if self_test:
            # Put a KNOWN signal at a KNOWN instant inside the window. Bytes arriving
            # only proves the transport; a tone that lands at the midpoint proves the
            # capture is sampling the microphone at the scheduled time, which is the
            # entire claim. It also exercises the self-noise flag, since the node is
            # both the source and the listener.
            #
            # Sent on THIS already-open handle rather than via `cmd`, deliberately:
            # send_cmd opens the port with the DTR reset, which would reboot the bridge
            # and shatter the very band we are recording against.
            time.sleep(max(0.0, wait_s) + window_s / 2.0)
            beep = (bytes([CMD_BEEP]) + struct.pack("<I", NODE_IDS[nodes[0]])
                    + struct.pack("<HH", 1000, 200))
            write_serial_frame(ser, encode_toot(CMD, ORCHESTRATOR_ID,
                                                (base + 100) & 0x7FFFFFFF, beep))
            print(f"self-test: 1 kHz 200 ms at +{window_s / 2.0:.2f} s into the window")
            time.sleep(window_s / 2.0 + 0.5)
        else:
            time.sleep(max(0.0, wait_s) + window_s + 0.5)

        os.makedirs(outdir, exist_ok=True)
        rows = []
        for name in nodes:
            data = request_ttdb(ser, reader, NODE_IDS[name], 30.0, TTDB_REQ_RECORDING)
            if not data:
                print(f"{name:<12} nothing captured")
                continue
            h = parse_rechdr(data)
            if h is None:
                print(f"{name:<12} reply was not a RECHDR ({len(data)} B)")
                continue
            pcm = data[RECHDR_LEN:RECHDR_LEN + h["samples"] * 2]
            path = os.path.join(outdir, f"{name}.wav")
            write_wav(path, pcm, h["rate"])
            rows.append((name, h, path))

        if not rows:
            sys.exit("\nno node returned a capture")

        # The payoff table. `late` is the node's OWN report of how far past the requested
        # instant its first sample actually landed — a measurement, not an unknown, and
        # the thing that lets a shared clock wobble be corrected rather than inherited.
        print(f"\n{'node':<12} {'samples':>8} {'late_ms':>8} {'offset_ms':>10} "
              f"{'era':>4} {'flags':>6}  file")
        for name, h, path in rows:
            fl = "".join([("S" if h["flags"] & REC_FLAG_SYNCED else "-"),
                          ("L" if h["flags"] & REC_FLAG_LATE else "-"),
                          ("V" if h["flags"] & REC_FLAG_SELF else "-")])
            print(f"{name:<12} {h['samples']:>8} {h['start'] - h['req']:>8} "
                  f"{h['offset']:>10} {h['era']:>4} {fl:>6}  {path}")
        print("  flags: S=fleet-clock synced  L=start already past on arrival  "
              "V=our own speaker sounded")

        if len(rows) > 1:
            base_start = rows[0][1]["start"]
            spread = max(abs(r[1]["start"] - base_start) for r in rows)
            eras = {r[1]["era"] for r in rows}
            print(f"\ncapture-start spread across nodes: {spread} ms "
                  f"= {spread * 0.343:.2f} m of sound")
            if len(eras) > 1:
                print("  WARNING: nodes reported different chart eras "
                      f"{sorted(eras)} — their beat numbering is not comparable")
    finally:
        ser.close()


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


POSITION_BELIEF_HEADER = """# Fleet Position Belief (authored by companion push --positions)

The fleet's @BELIEF:POSITION map (semantic positioning SP2), re-authored by
`companion.py push --positions` and pushed back to a node over the mesh
(TTN-RFC-0009) — publishing where the fleet believes each node is. The node
stores it byte-exact as `/belief.md`, CRC-verifies, and attests adoption in its
own TTDB. Each record carries `node_id:` so a node can find its OWN position by
matching its numeric id (SP4 address loop). GPS remains verifier-only; these
coordinates come from the RSSI/BLE embedding, not from GPS being fed back in.

```mmpdb
db_id: fleet-position-belief-001
db_name: Fleet Position Belief
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


def author_position_belief(src_path):
    """Re-author a position belief from master/positions.md (relative frame) or
    master/anchored.md (geo frame). Emits one @BELIEF:POSITION record per node in
    the same format as the source, with a `node_id:` line injected so firmware can
    match its own position by id. Returns valid TTDB bytes the node stores byte-exact
    as /belief.md. Zero new toot type — rides the existing TTN-RFC-0009 push path."""
    if not os.path.exists(src_path):
        sys.exit(f"no position belief source at {src_path} — run `positions` "
                 f"(relative) or `anchor` (geo) first")
    with open(src_path, encoding="utf-8") as f:
        text = f.read()
    parts = [POSITION_BELIEF_HEADER]
    n = 0
    for chunk in text.split("@BELIEF:POSITION")[1:]:
        m = re.match(r"\s*@node\((\w+)\)", chunk)
        if not m:
            continue
        node = m.group(1)
        # Body = every line up to the next record separator, verbatim (preserves
        # relative x_m/y_m or geo lat_deg/lon_deg exactly for a byte-diff readback).
        body = chunk.split("\n---")[0]
        header_line, _, rest = body.partition("\n")   # header_line == " @node(name)..."
        nid = NODE_IDS.get(node)
        id_line = f"node_id: 0x{nid:08X}\n" if nid is not None else ""
        parts.append(f"\n---\n\n@BELIEF:POSITION{header_line.rstrip()}\n"
                     f"{id_line}{rest.strip(chr(10))}\n")
        n += 1
    if n == 0:
        sys.exit(f"no @BELIEF:POSITION records in {src_path}")
    return "".join(parts).encode("utf-8"), n


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
         sense_interval_ms=DEFAULT_SENSE_INTERVAL_MS, positions_src=None):
    """Re-author a belief and push it to a node, then verify adoption by pulling the
    node's live TTDB and matching its BELIEF-ADOPTED record (TTN-RFC-0009 §5). With
    `positions_src` set, publishes the fleet @BELIEF:POSITION map instead of the sync
    belief (SP2 "publish positions back") — same push rails, no DIRECTIVE cadence."""
    try:
        import serial  # pyserial
    except ImportError:
        sys.exit("pyserial not installed. Run: pip install -r requirements.txt")
    if node not in NODE_IDS:
        sys.exit(f"unknown node '{node}'. choices: {', '.join(NODE_IDS)}")
    target = NODE_IDS[node]

    if positions_src:
        content, n_pos = author_position_belief(positions_src)
        print(f"authored position belief from {positions_src}: {n_pos} node(s)")
    else:
        content = author_belief(src_master, sense_interval_ms)
    crc = crc32(content)
    belief_id = next_belief_id(belief_log)
    os.makedirs(os.path.dirname(os.path.abspath(out_path)) or ".", exist_ok=True)
    with open(out_path, "wb") as f:
        f.write(content)
    src_label = positions_src if positions_src else src_master
    print(f"authored belief from {src_label}: {len(content)}B -> {out_path}")

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
    # A position belief carries no DIRECTIVE (it publishes coordinates, not policy),
    # so the cadence assertion is skipped — byte-exact storage + CRC is the contract.
    applied = rec.get("applied_interval_ms")
    if positions_src:
        print("position belief stored (no DIRECTIVE — publishing coordinates, "
              "not policy; SP4 will make a node act on its own position)")
    elif applied == sense_interval_ms:
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


# --- entity co-occurrence percepts (semantic positioning SP0, entity tier) ---
# A node's @LAT96 lane holds one record per WiFi-scan window, each with a
# **ENTWIN** context line and one **ENTITY** line per visible BSSID. Two nodes
# seeing the same APs are probably near each other (ttn-semantic-positioning.md
# §2.2): the Jaccard overlap of their BSSID sets is a coarse proximity BOUND.
ENTWIN_RE = re.compile(
    r"\*\*ENTWIN\*\*\s+t_ms:(\d+)\s+synced:([01])\s+window_ms:(\d+)"
    r"(?:\s+entities:(\d+))?")
ENTITY_RE = re.compile(
    r"\*\*ENTITY\*\*\s+kind:(\w+)\s+id:([0-9a-fA-F]{12})\s+n:(\d+)\s+rssi:(-?\d+)")

# WiFi co-visibility bound (spec §2.2): sharing APs caps distance to ~30–100 m.
# Higher Jaccard -> tighter bound. Coarse heuristic, recalibratable per site.
ENTITY_BOUND_TIGHT_M = 30.0    # near-total AP overlap
ENTITY_BOUND_LOOSE_M = 100.0   # a single shared AP


def parse_entity_percepts(text):
    """Parse a TTDB's @LAT96 lane into a list of windows:
    {lane, t_ms, synced, window_ms, entities: [{kind, id, n, rssi}]}.
    `id` is the 12-hex BSSID string (lowercased)."""
    windows = []
    cur = None
    for line in text.splitlines():
        if line.startswith("@LAT96LON"):
            lane = int(re.match(r"@LAT96LON(\d+)", line).group(1))
            cur = {"lane": lane, "t_ms": None, "synced": None,
                   "window_ms": None, "entities": []}
            windows.append(cur)
            continue
        if line.startswith("@"):     # any other record header ends the window
            cur = None
            continue
        if cur is None:
            continue
        m = ENTWIN_RE.search(line)
        if m:
            cur["t_ms"] = int(m.group(1))
            cur["synced"] = int(m.group(2))
            cur["window_ms"] = int(m.group(3))
            continue
        m = ENTITY_RE.search(line)
        if m:
            cur["entities"].append({
                "kind": m.group(1), "id": m.group(2).lower(),
                "n": int(m.group(3)), "rssi": int(m.group(4))})
    return windows


def _entity_set(windows, last=None):
    """Union of BSSIDs a node saw across its (recent) windows -> set of ids."""
    if last:
        windows = windows[-last:]
    ids = set()
    for w in windows:
        for e in w["entities"]:
            ids.add(e["id"])
    return ids


def entity_jaccard_bound(jaccard):
    """Map a Jaccard overlap in [0,1] to a coarse distance BOUND in metres, or
    None when the sets are disjoint (no bound — they may be anywhere). This is an
    UPPER bound: it caps the RSSI estimate ("they share APs, they can't be far"),
    it does not refine below it (spec §2.2)."""
    if jaccard <= 0.0:
        return None
    return ENTITY_BOUND_LOOSE_M - jaccard * (ENTITY_BOUND_LOOSE_M - ENTITY_BOUND_TIGHT_M)


def consolidate_entity_jaccard(windows_by_node, last=None):
    """windows_by_node: {node_name: [parse_entity_percepts window, ...]}.
    For every node pair that both logged entities, compute the Jaccard overlap of
    their BSSID sets and the coarse distance bound it implies. Returns a list of
    {pair, jaccard, shared, union, bound_m} dicts, disjoint/empty pairs dropped."""
    sets = {name: _entity_set(wins, last) for name, wins in windows_by_node.items()}
    sets = {n: s for n, s in sets.items() if s}   # nodes that saw at least one AP
    names = sorted(sets)
    out = []
    for i in range(len(names)):
        for j in range(i + 1, len(names)):
            a, b = names[i], names[j]
            inter = sets[a] & sets[b]
            union = sets[a] | sets[b]
            jac = len(inter) / len(union) if union else 0.0
            if not inter:
                continue          # disjoint: no co-occurrence evidence
            out.append({"pair": (a, b), "jaccard": jac, "shared": len(inter),
                        "union": len(union), "bound_m": entity_jaccard_bound(jac)})
    out.sort(key=lambda r: -r["jaccard"])
    return out


def entities(port, baud, node, save):
    """Pull a node's TTDB and print its entity-percept windows (@LAT96 lane) —
    the SP0 entity-tier 'Done when' check: the node logs visible WiFi APs."""
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
    windows = parse_entity_percepts(data.decode("utf-8", errors="replace"))
    nobs = sum(e["n"] for w in windows for e in w["entities"])
    seen = _entity_set(windows)
    print(f"{node}: {len(windows)} entity-percept window(s), {nobs} sighting(s), "
          f"{len(seen)} distinct AP(s) (@LAT96 lane)")
    if not windows:
        print("no @LAT96 records yet — needs a node built with USE_WIFI_SCAN and a "
              "scan window (default 60 s); re-run after one elapses")
        return
    print(f"{'lane':>4}  {'t_ms':>14}  {'sync':>4}  {'win_ms':>7}  "
          f"{'kind':7}  {'bssid':12}  {'n':>4}  {'rssi':>5}")
    for w in windows:
        first = True
        for e in w["entities"]:
            lead = (f"{w['lane']:>4}  {w['t_ms']:>14}  {w['synced']:>4}  "
                    f"{w['window_ms']:>7}") if first else " " * 35
            first = False
            print(f"{lead}  {e['kind']:7}  {e['id']:12}  {e['n']:>4}  {e['rssi']:>5}")


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
    # BLE near-range tier (SP0): a low-power advert reads ~-59 dBm at 1 m; n~2 indoors.
    # Uncalibrated default so proto:ble beliefs still estimate distance — recalibrate
    # per environment with `calibrate --proto ble`.
    "ble": {"rssi_d0": -59.0, "d0_m": 1.0, "n": 2.0},
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


def _sources_mix(entity_jaccard=None, has_ble=False):
    """Normalized evidence-mix weights for a @BELIEF:PROXIMITY `sources:` line
    (ttn-semantic-positioning.md §2). RSSI is always the base; a present entity
    (WiFi Jaccard) or BLE term adds weight, then all are normalized to sum ~1."""
    parts = {"rssi": 1.0}
    if entity_jaccard is not None:
        parts["entity_jaccard"] = 0.4 * entity_jaccard
    if has_ble:
        parts["ble"] = 0.3
    total = sum(parts.values())
    return {k: round(v / total, 2) for k, v in parts.items()}


# BLE bound: how many sigmas above the BLE point estimate to place the upper bound.
BLE_BOUND_K_SIGMA = 1.0
# BLE saturation/consistency guard (ttn-semantic-positioning.md §2.2). The
# 2026-07-13 garden re-run showed a saturated BLE read on a reflective far path
# clamp a 14.6 m pair to ~0.6 m with high confidence — worse than no BLE (its
# strong side is a reflection/near-field spike, not proximity). The discriminator
# is NOT asymmetry: the clean run measured 30-40 dB directional asymmetry on EVERY
# path, good and bad alike, so asym doesn't separate the one BLE win (v4a<->tdeck
# 5.96 m, plausible) from the failure (v4b<->tdeck 0.6 m, implausible). It is the
# field's own signature — "BLE-strong-but-espnow-weak": a BLE estimate is used as a
# TIGHT bound only when it is not a near-field-SATURATED reading (< a floor) that a
# co-measured espnow tier says is actually FAR. Otherwise it is FLAGGED
# reflection-suspect and NOT allowed to cap the other tiers (their measurement wins).
BLE_SATURATION_DIST_M = 1.5     # a BLE estimate below this is near-field-saturated
BLE_CONSISTENCY_RATIO = 3.0     # co-measured espnow this many x the BLE bound = conflict


def apply_ble_bound(beliefs, k_sigma=BLE_BOUND_K_SIGMA):
    """SP1 second bound: a pair's BLE proto:ble estimate caps its espnow distance.
    BLE is a near-range radio (~10-30 m), so a pair heard over BLE is bounded TIGHTER
    than by WiFi entity overlap. The bound is the BLE estimate's upper confidence edge
    (dist + k*sigma); it caps the pair's other-proto distance from above, never refines
    below (like the entity cap), and adds a `ble` term to that belief's sources mix.

    Saturation/consistency guard: a BLE reading is used as a tight bound only when it
    is not a near-field-SATURATED spike (dist < BLE_SATURATION_DIST_M) on a path a
    co-measured espnow reading says is >BLE_CONSISTENCY_RATIO x farther. A
    reflection-suspect reading is FLAGGED (`ble_reflection_suspect`) and its bound is
    NOT applied — the strong side driving it isn't genuine proximity (the 2026-07-13
    field failure). This never lets BLE clamp a pair below what a co-measured tier
    says, while preserving a plausible mid-range BLE estimate that legitimately caps an
    over-ranging espnow. Mutates and returns `beliefs`."""
    by_pair = {}
    for b in beliefs:
        by_pair.setdefault(frozenset((b["a"], b["b"])), {})[b["proto"]] = b
    for protos in by_pair.values():
        ble = protos.get("ble")
        if not ble or ble.get("dist_est_m") is None:
            continue
        bound = ble["dist_est_m"] + k_sigma * (ble.get("dist_sigma_m") or 0.0)

        # --- BLE saturation/consistency guard ("BLE-strong-but-espnow-weak") ---
        saturated = ble["dist_est_m"] < BLE_SATURATION_DIST_M
        espnow = protos.get("espnow")
        far_conflict = bool(espnow and espnow.get("dist_est_m") is not None
                            and espnow["dist_est_m"] > bound * BLE_CONSISTENCY_RATIO)
        suspect = saturated and far_conflict
        ble["ble_saturated"] = bool(saturated)
        ble["ble_reflection_suspect"] = bool(suspect)
        if suspect:
            # Untrustworthy BLE spike: flag it across the pair's tiers, but do NOT
            # let it clamp the amplitude/topology estimates (keep what they measured).
            for proto, b in protos.items():
                if proto != "ble":
                    b["ble_saturated"] = bool(saturated)
                    b["ble_reflection_suspect"] = True
            continue

        for proto, b in protos.items():
            if proto == "ble" or b.get("dist_est_m") is None:
                continue
            b["ble_bound_m"] = round(bound, 2)
            b["sources"] = _sources_mix(entity_jaccard=b.get("entity_jaccard"),
                                        has_ble=True)
            if b["dist_est_m"] > bound:
                b["dist_est_m"] = round(bound, 2)
                b["ble_capped"] = True
                if b.get("dist_sigma_m"):
                    b["dist_sigma_m"] = round(min(b["dist_sigma_m"], bound / 2.0), 2)
    return beliefs


def consolidate_proximity(windows_by_node, calib=None, last=None, entity_bounds=None):
    """windows_by_node: {node_name: [parse_link_percepts window, ...]}.
    calib: load_calibration() output (fitted path-loss per proto), or None.
    last: use only each node's newest N windows — the recency filter. A node
    that moved (the calibration walk!) leaves stale-distance windows behind;
    position is a *current* belief, so recent evidence must be able to win.
    entity_bounds: {frozenset((a,b)): {jaccard, bound_m, shared, union}} from
    consolidate_entity_jaccard — the SP1 entity cap. Shared WiFi APs bound a pair's
    distance from ABOVE ("they share N APs, they can't be far", spec §2.2); this
    caps the RSSI estimate (never refines below it) and adds a `sources:` mix.
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

        a_name = id_to_name.get(lo, f"0x{lo:08X}")
        b_name = id_to_name.get(hi, f"0x{hi:08X}")

        # SP1 entity cap (ttn-semantic-positioning.md §2.2). The entity term bounds
        # distance from ABOVE and never refines below the RSSI estimate: at short
        # range (bench) it just contributes to the `sources:` mix; in the field it
        # clamps an RSSI estimate that over-ranged a pair that clearly shares APs —
        # the exact failure GPS caught in the garden (RSSI 2–7x too large).
        eb = (entity_bounds or {}).get(frozenset((a_name, b_name)))
        entity_capped = False
        entity_jaccard = entity_shared = None
        if eb and eb.get("bound_m") is not None:
            entity_jaccard = round(eb["jaccard"], 2)
            entity_shared = eb["shared"]
            if dist is not None and dist > eb["bound_m"]:
                dist = eb["bound_m"]
                entity_capped = True
                if sigma is not None:            # a clamped estimate is more certain
                    sigma = min(sigma, eb["bound_m"] / 2.0)
        # Sources mix — rssi + entity now; the BLE term is added later by
        # apply_ble_bound (it needs the whole beliefs list to find the ble estimate).
        sources = _sources_mix(entity_jaccard=entity_jaccard)

        conf = round(max(0.1, min(0.85 if calibrated else 0.7, conf)), 2)

        beliefs.append({
            "a": a_name, "b": b_name,
            "proto": proto, "rssi_est": round(rssi_est, 1),
            "rssi_ab": (round(ests[0], 1) if ab else None),
            "rssi_ba": (round(ests[-1], 1) if ba else None),
            "n_ab": ab["n"] if ab else 0, "n_ba": ba["n"] if ba else 0,
            "windows": (ab["windows"] if ab else 0) + (ba["windows"] if ba else 0),
            "asym_db": round(asym, 1), "rssi_sigma_db": round(rssi_sigma, 1),
            "dist_est_m": (round(dist, 2) if dist else None),
            "dist_sigma_m": (round(sigma, 2) if sigma else None),
            "n_obs": n_obs, "conf": conf, "calibrated": calibrated,
            "sources": sources, "entity_jaccard": entity_jaccard,
            "entity_bound_m": (round(eb["bound_m"], 2) if eb and eb.get("bound_m") else None),
            "entity_shared": entity_shared, "entity_capped": entity_capped,
            "ble_bound_m": None, "ble_capped": False,
            "ble_saturated": False, "ble_reflection_suspect": False,
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
    entity_windows_by_node = {}
    for n in nodes:
        try:
            with open(node_paths[n], encoding="utf-8", errors="replace") as f:
                text = f.read()
            windows_by_node[n] = parse_link_percepts(text)
            entity_windows_by_node[n] = parse_entity_percepts(text)
        except FileNotFoundError:
            print(f"warning: {node_paths[n]} missing; {n} contributes nothing")
    # SP1 entity cap: fuse the @LAT96 WiFi co-occurrence into per-pair distance bounds.
    entity_bounds = {frozenset(e["pair"]): e
                     for e in consolidate_entity_jaccard(entity_windows_by_node)}
    if entity_bounds:
        print(f"entity co-occurrence: {len(entity_bounds)} pair(s) with shared APs "
              f"(WiFi cap active)")
    beliefs = consolidate_proximity(windows_by_node, calib, last, entity_bounds)
    # SP1 second bound: fold each pair's BLE proto:ble estimate in as a tighter
    # near-range cap on the espnow distance (ttn-semantic-positioning.md §2.2).
    apply_ble_bound(beliefs)
    ble_pairs = {frozenset((b["a"], b["b"])) for b in beliefs if b["proto"] == "ble"}
    if ble_pairs:
        suspect = {frozenset((b["a"], b["b"])) for b in beliefs
                   if b["proto"] == "ble" and b.get("ble_reflection_suspect")}
        note = (f"; {len(suspect)} reflection-suspect (bound suppressed)"
                if suspect else "")
        print(f"BLE near-range: {len(ble_pairs)} pair(s) with proto:ble "
              f"(BLE bound active{note})")

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
                    f"sources: {{ {', '.join(f'{k}: {v}' for k, v in b['sources'].items())} }}\n"
                    + (f"entity_jaccard: {b['entity_jaccard']}   # shared "
                       f"{b['entity_shared']} AP(s), bound <= {b['entity_bound_m']} m"
                       f"{' — CAPPED the RSSI estimate' if b['entity_capped'] else ''}\n"
                       if b["entity_jaccard"] is not None else "")
                    + (f"ble_bound_m: {b['ble_bound_m']}   # near-range BLE estimate"
                       f"{' — CAPPED the RSSI estimate' if b['ble_capped'] else ''}\n"
                       if b["ble_bound_m"] is not None else "")
                    + (f"ble_reflection_suspect: yes   # saturated/asymmetric BLE"
                       f" — NOT used as a tight bound (reflection guard, "
                       f"ttn-semantic-positioning.md §2.2)\n"
                       if b.get("ble_reflection_suspect") else "")
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
          f"{'sigma_m':>8} {'n':>5} {'conf':>5} {'entJ':>5} {'cap':>4}")
    for b in beliefs:
        j = f"{b['entity_jaccard']:.2f}" if b["entity_jaccard"] is not None else "-"
        cap = ("ble" if b["ble_capped"] else "ent" if b["entity_capped"]
               else "ble?" if b.get("ble_reflection_suspect") else "")
        print(f"{b['a'] + ' <-> ' + b['b']:<28} {b['proto']:6} "
              f"{b['rssi_est']:>6} {b['asym_db']:>5} {b['dist_est_m']:>7} "
              f"{b['dist_sigma_m']:>8} {b['n_obs']:>5} {b['conf']:>5} {j:>5} "
              f"{cap:>4}")
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


# --- position embedding (semantic positioning SP2) ---------------------------
# Turn the pairwise @BELIEF:PROXIMITY matrix into per-node @BELIEF:POSITION via
# weighted spring relaxation (stress majorization-lite — the spec's "~40 lines",
# ttn-semantic-positioning.md §3 Phase 2). Laptop-side first; the same loop is
# portable to the head node later. One anchor (V4-A) pins translation only, so
# the output frame is RELATIVE: V4-A at the origin, V4-B along +x, and the
# mirror image unresolved (flip_resolved: false) until the T-Deck GPS supplies
# a second, roaming anchor.
DEFAULT_POSITIONS_OUT = os.path.join("master", "positions.md")

POSITIONS_HEADER = """# Fleet Position Beliefs (semantic positioning SP2)

Authored by `companion.py positions`: the @BELIEF:PROXIMITY pair matrix embedded
into 2D by weighted spring relaxation, then canonicalized — anchor at the
origin, second node on +x, third node at +y. The frame is RELATIVE (one anchor
fixes translation only): rotation and reflection are unresolved until a second
anchor (the T-Deck GPS) pins them, so flip_resolved stays false. sigma_m folds
each node's incident edge residuals + pair sigmas; stress is the fit's honesty.
"""


def parse_proximity_file(path):
    """Parse master/proximity.md -> [{a, b, proto, dist, sigma, n, conf}]."""
    with open(path, encoding="utf-8") as f:
        text = f.read()
    pairs = []
    for chunk in text.split("@BELIEF:PROXIMITY")[1:]:
        m_pair = re.match(r"\s*@pair\((\w+),\s*(\w+)\)", chunk)
        fields = {k: re.search(k + r":\s*(-?[\d.]+)", chunk)
                  for k in ("dist_est_m", "dist_sigma_m", "n_obs", "conf")}
        m_proto = re.search(r"proto:\s*(\w+)", chunk)
        if not m_pair or not all(fields.values()):
            continue
        pairs.append({"a": m_pair.group(1), "b": m_pair.group(2),
                      "proto": m_proto.group(1) if m_proto else "?",
                      "dist": float(fields["dist_est_m"].group(1)),
                      "sigma": float(fields["dist_sigma_m"].group(1)),
                      "n": int(float(fields["n_obs"].group(1))),
                      "conf": float(fields["conf"].group(1))})
    return pairs


def embed_positions(pairs, iters=1500, seed=1, anchor="v4a_bridge", restarts=8):
    """Weighted spring relaxation of the pair-distance graph into 2D, with
    random restarts (a folded start is a local minimum springs cannot uncross;
    for <=10 nodes, restart-and-keep-best is cheaper than being clever).
    Returns (pos {node: (x, y)}, residuals [(a, b, want, got)], stress_m)."""
    import math
    import random
    nodes = sorted({p["a"] for p in pairs} | {p["b"] for p in pairs})
    if len(nodes) < 2:
        sys.exit("positions: need at least 2 nodes with proximity beliefs")
    # Weight: confidence over variance (a wide-sigma pair may not drag the map).
    springs = [(p["a"], p["b"], p["dist"], p["conf"] / max(p["sigma"], 0.1) ** 2)
               for p in pairs]
    wmax = max(w for _, _, _, w in springs)
    dmean = sum(p["dist"] for p in pairs) / len(pairs)

    def relax(rng):
        p = {nd: [rng.uniform(-dmean, dmean), rng.uniform(-dmean, dmean)]
             for nd in nodes}
        for it in range(iters):
            eta = 0.25 * (1.0 - it / iters) + 0.02
            for a, b, d, w in springs:
                dx, dy = p[b][0] - p[a][0], p[b][1] - p[a][1]
                cur = math.hypot(dx, dy) or 1e-6
                f = eta * (w / wmax) * (cur - d) / cur  # >0 pulls together
                p[a][0] += f * dx / 2
                p[a][1] += f * dy / 2
                p[b][0] -= f * dx / 2
                p[b][1] -= f * dy / 2
        num = sum(w * (math.hypot(p[a][0] - p[b][0], p[a][1] - p[b][1]) - d) ** 2
                  for a, b, d, w in springs)
        return p, (num / sum(w for _, _, _, w in springs)) ** 0.5

    pos, best = None, None
    for r in range(restarts):
        cand, st = relax(random.Random(seed + r))
        if best is None or st < best:
            pos, best = cand, st

    # Canonical relative frame: anchor -> origin, next node -> +x axis,
    # first off-axis node -> +y half-plane (deterministic mirror choice; the
    # TRUE mirror stays unknown — flip_resolved: false).
    import math as _m
    anch = anchor if anchor in pos else nodes[0]
    ax, ay = pos[anch]
    for nd in nodes:
        pos[nd][0] -= ax
        pos[nd][1] -= ay
    ref = next((nd for nd in nodes if nd != anch), None)
    theta = _m.atan2(pos[ref][1], pos[ref][0])
    c, s = _m.cos(-theta), _m.sin(-theta)
    for nd in nodes:
        x, y = pos[nd]
        pos[nd] = [x * c - y * s, x * s + y * c]
    third = next((nd for nd in nodes if abs(pos[nd][1]) > 1e-6), None)
    if third and pos[third][1] < 0:
        for nd in nodes:
            pos[nd][1] = -pos[nd][1]

    residuals = []
    num = den = 0.0
    for a, b, d, w in springs:
        got = math.hypot(pos[a][0] - pos[b][0], pos[a][1] - pos[b][1])
        residuals.append((a, b, d, got))
        num += w * (got - d) ** 2
        den += w
    stress = (num / den) ** 0.5 if den else 0.0
    return {nd: (pos[nd][0], pos[nd][1]) for nd in nodes}, residuals, stress


def ascii_map(pos, width=57, height=19):
    """Tiny TTCP foreshadow: the fleet's self-map as terminal art."""
    xs = [p[0] for p in pos.values()]
    ys = [p[1] for p in pos.values()]
    pad = 0.5
    x0, x1 = min(xs) - pad, max(xs) + pad
    y0, y1 = min(ys) - pad, max(ys) + pad
    grid = [[" "] * width for _ in range(height)]
    for name, (x, y) in sorted(pos.items()):
        cx = int((x - x0) / (x1 - x0) * (width - 8))
        cy = int((1.0 - (y - y0) / (y1 - y0)) * (height - 1))
        label = "*" + name[:7]
        for k, ch in enumerate(label):
            if 0 <= cx + k < width:
                grid[cy][cx + k] = ch
    lines = ["  +" + "-" * width + "+"]
    lines += ["  |" + "".join(row) + "|" for row in grid]
    lines += ["  +" + "-" * width + "+",
              f"   {x1 - x0:.1f} m wide x {y1 - y0:.1f} m tall  "
              f"(relative frame; mirror unresolved)"]
    return "\n".join(lines)


def positions(proximity_path, out, iters):
    """SP2: embed the proximity beliefs into @BELIEF:POSITION records + a map."""
    pairs = parse_proximity_file(proximity_path)
    if not pairs:
        sys.exit(f"no @BELIEF:PROXIMITY records in {proximity_path} — run "
                 f"`companion.py proximity` first")
    pos, residuals, stress = embed_positions(pairs, iters)

    # embedding_rev: monotonic per output file (warm-start bookkeeping).
    rev = 1
    try:
        with open(out, encoding="utf-8") as f:
            revs = re.findall(r"embedding_rev:\s*(\d+)", f.read())
        if revs:
            rev = max(int(r) for r in revs) + 1
    except FileNotFoundError:
        pass

    # Per-node honesty: rms of incident-edge residuals + mean pair sigma.
    inc = {nd: [] for nd in pos}
    conf_inc = {nd: [] for nd in pos}
    for p in pairs:
        got = next(g for a, b, _, g in residuals
                   if (a, b) == (p["a"], p["b"]))
        for nd in (p["a"], p["b"]):
            inc[nd].append((got - p["dist"]) ** 2 + p["sigma"] ** 2)
            conf_inc[nd].append(p["conf"])
    now_iso = time.strftime("%Y-%m-%dT%H:%M:%SZ", time.gmtime())

    os.makedirs(os.path.dirname(os.path.abspath(out)) or ".", exist_ok=True)
    with open(out, "w", encoding="utf-8", newline="\n") as f:
        f.write(POSITIONS_HEADER)
        for nd, (x, y) in sorted(pos.items()):
            sigma = (sum(inc[nd]) / len(inc[nd])) ** 0.5 if inc[nd] else 0.0
            conf = sum(conf_inc[nd]) / len(conf_inc[nd]) if conf_inc[nd] else 0.1
            conf = round(max(0.1, min(0.8, conf - min(0.3, stress / 4.0))), 2)
            f.write(f"\n---\n\n@BELIEF:POSITION @node({nd})\n"
                    f"frame: relative   # anchor v4a_bridge at origin, "
                    f"2nd node on +x, 3rd at +y\n"
                    f"x_m: {x:.2f}\ny_m: {y:.2f}\n"
                    f"sigma_m: {sigma:.2f}\n"
                    f"anchor_chain: [v4a_bridge]\n"
                    f"embedding_rev: {rev}\n"
                    f"flip_resolved: false   # one anchor; T-Deck GPS resolves\n"
                    f"stress_m: {stress:.2f}\n"
                    f"conf: {conf}\n"
                    f"touched: {now_iso}\n")

    print(f"positions: embedded {len(pos)} node(s) from {len(pairs)} pair "
          f"belief(s)  (rev {rev}, stress {stress:.2f} m)")
    print(f"{'node':<12} {'x_m':>7} {'y_m':>7} {'sigma_m':>8}")
    for nd, (x, y) in sorted(pos.items()):
        sigma = (sum(inc[nd]) / len(inc[nd])) ** 0.5 if inc[nd] else 0.0
        print(f"{nd:<12} {x:>7.2f} {y:>7.2f} {sigma:>8.2f}")
    print(f"\npair fit (want -> got):")
    for a, b, want, got in residuals:
        print(f"  {a:<11}<->{b:<11} {want:>6.2f} -> {got:>6.2f}  "
              f"({got - want:+.2f})")
    print()
    print(ascii_map(pos))
    print(f"\nwrote {out}")


# --- GPS: the roaming ground-truth anchor (semantic positioning SP2) --------
# The T-Deck Plus GPS is the fleet's VERIFIER and second anchor: a fix taken beside a
# static node ties the emergent relative map (positions.md) to absolute coordinates and
# resolves its mirror (ttn-semantic-positioning.md §3 Phase 2). GPS is never an inference
# input — only a score/anchor. `gps` reads a fix; `anchor` fits the relative map to geo.
DEFAULT_GPS_FIXES = os.path.join("master", "gps-fixes.md")
DEFAULT_ANCHORED_OUT = os.path.join("master", "anchored.md")
M_PER_DEG_LAT = 111319.4908    # metres per degree latitude (spherical earth)


def parse_gps(payload):
    """Decode a GPS PERCEPT payload -> dict, or None if it isn't one (len != 24)."""
    if len(payload) != GPS_PERCEPT_PAYLOAD_LEN:
        return None
    lat_1e7, lon_1e7, alt_cm = struct.unpack("<iii", payload[0:12])
    quality, sats = payload[12], payload[13]
    hdop_x10 = struct.unpack("<H", payload[14:16])[0]
    epoch_ms = struct.unpack("<Q", payload[16:24])[0]
    return {"lat_deg": lat_1e7 / 1e7, "lon_deg": lon_1e7 / 1e7,
            "alt_m": alt_cm / 100.0, "quality": quality, "sats": sats,
            "hdop": hdop_x10 / 10.0, "epoch_ms": epoch_ms}


def gps_probe(ser, reader, target, probes=6, per_timeout=1.2):
    """Query a node with CMD_GET_GPS and keep the best reply (most sats, then lowest
    HDOP). Returns the parse_gps dict, or None if the node never answered. A fresh
    toot_seq per probe dodges the radio dedup (like status_probe)."""
    best = None
    base = int(time.time() * 1000) & 0x7FFFFFFF
    old_to = ser.timeout
    ser.timeout = 0
    try:
        for k in range(probes):
            seq = (base + k) & 0x7FFFFFFF
            payload = bytes([CMD_GET_GPS]) + struct.pack("<I", target)
            write_serial_frame(ser, encode_toot(CMD, ORCHESTRATOR_ID, seq, payload))
            deadline = time.time() + per_timeout
            got = None
            while time.time() < deadline and got is None:
                data = ser.read(256)
                if not data:
                    time.sleep(0.0005)
                    continue
                for fr in reader.feed(data):
                    t = decode_toot(fr)
                    if not t or t["type"] != PERCEPT or t["src"] != target:
                        continue
                    g = parse_gps(t["payload"])
                    if g is not None:
                        got = g
                        break
            if got is None:
                continue
            better = (best is None or got["sats"] > best["sats"] or
                      (got["sats"] == best["sats"] and got["hdop"] and
                       (not best["hdop"] or got["hdop"] < best["hdop"])))
            if better:
                best = got
    finally:
        ser.timeout = old_to
    return best


def parse_intero(payload):
    """Decode an INTERO PERCEPT payload -> dict, or None if it isn't one (len != 21)."""
    if len(payload) != INTERO_PERCEPT_PAYLOAD_LEN:
        return None
    bat_mv = struct.unpack("<H", payload[0:2])[0]
    bat_pct = payload[2]
    bat_trend = struct.unpack("<b", payload[3:4])[0]
    die_c10 = struct.unpack("<h", payload[4:6])[0]
    maxalloc_kb, = struct.unpack("<H", payload[6:8])
    uptime_s, = struct.unpack("<I", payload[8:12])
    worst_loop_ms, = struct.unpack("<H", payload[12:14])
    beat_period_ms, = struct.unpack("<H", payload[14:16])
    conductor_id, = struct.unpack("<I", payload[16:20])
    flags = payload[20]
    return {"bat_mv": bat_mv, "bat_pct": None if bat_pct == 255 else bat_pct,
            "bat_trend": bat_trend, "die_c": die_c10 / 10.0,
            "maxalloc_kb": maxalloc_kb, "uptime_s": uptime_s,
            "worst_loop_ms": worst_loop_ms, "beat_period_ms": beat_period_ms,
            "conductor_id": conductor_id, "flags": flags,
            "synced": bool(flags & INTERO_SYNCED),
            "conductor": bool(flags & INTERO_CONDUCTOR),
            "playing": bool(flags & INTERO_PLAYING)}


def intero_probe(ser, reader, target, probes=4, per_timeout=1.2):
    """Query a node with CMD_GET_INTERO and return the last reply (parse_intero dict),
    or None if it never answered. Fresh toot_seq per probe dodges the radio dedup."""
    got = None
    base = int(time.time() * 1000) & 0x7FFFFFFF
    old_to = ser.timeout
    ser.timeout = 0
    try:
        for k in range(probes):
            seq = (base + k) & 0x7FFFFFFF
            payload = bytes([CMD_GET_INTERO]) + struct.pack("<I", target)
            write_serial_frame(ser, encode_toot(CMD, ORCHESTRATOR_ID, seq, payload))
            deadline = time.time() + per_timeout
            while time.time() < deadline:
                data = ser.read(256)
                if not data:
                    time.sleep(0.0005)
                    continue
                hit = False
                for fr in reader.feed(data):
                    t = decode_toot(fr)
                    if not t or t["type"] != PERCEPT or t["src"] != target:
                        continue
                    b = parse_intero(t["payload"])
                    if b is not None:
                        got, hit = b, True
                        break
                if hit:
                    break
            if got is not None:
                return got
    finally:
        ser.timeout = old_to
    return got


def intero(port, baud, node, probes, settle):
    """Read a node's INTEROCEPTION (CMD_GET_INTERO): energy, heat, room to think, its own
    worst loop pass, the band it hears, its clock. The laptop-side twin of the T-Deck's
    record-pane body view — and the reason it exists here at all: a units error at a
    protocol boundary is invisible on the node itself (the Cardputer shipped TENTHS in a
    field documented as HUNDREDTHS and only `monitor` printing 4.8C for a 48C die caught
    it), so every field is read back end to end from the laptop too."""
    try:
        import serial  # pyserial
    except ImportError:
        sys.exit("pyserial not installed. Run: pip install -r requirements.txt")
    if node not in NODE_IDS:
        sys.exit(f"unknown node '{node}'. choices: {', '.join(NODE_IDS)}")
    target = NODE_IDS[node]
    reader = SerialFrameReader()
    with serial.Serial(port, baud, timeout=0.1) as ser:
        time.sleep(settle)
        ser.reset_input_buffer()
        print(f"querying interoception on {node} (0x{target:08X}) via {port} ...")
        b = intero_probe(ser, reader, target, probes)
    if b is None:
        sys.exit(f"no INTERO PERCEPT from {node} — is it powered, on the mesh/bridge, and "
                 f"flashed with CMD op {CMD_GET_INTERO}?")
    arrow = {1: "rising", -1: "falling", 0: "steady"}[b["bat_trend"]]
    pct = "--" if b["bat_pct"] is None else f"{b['bat_pct']}%"
    up = b["uptime_s"]
    up_s = (f"{up // 3600}h{(up % 3600) // 60:02d}m" if up >= 3600
            else f"{up // 60}m{up % 60:02d}s")
    bpm = 60000 // b["beat_period_ms"] if b["beat_period_ms"] else 0
    cond = next((n for n, i in NODE_IDS.items() if i == b["conductor_id"]),
                f"0x{b['conductor_id']:08X}" if b["conductor_id"] else "-")
    print(f"{node} BODY")
    note = ""
    if not b["bat_mv"]:
        note = "   [0 mV = no battery sense on this node]"
    elif b["bat_pct"] is None:
        # Above the 4.20 V Li-ion ceiling the node withholds the percentage rather than
        # invent one: it is measuring the charge rail with no pack on it, or its divider
        # ratio is wrong. Both are real readings of the wrong thing.
        note = "   [EXT: not a 1S pack voltage — charge rail, or check the divider]"
    print(f"  energy : {b['bat_mv'] / 1000:.3f} V  {pct}  ({arrow}){note}")
    print(f"  heat   : {b['die_c']:.1f} C die (not ambient — no ambient sensor exists)")
    print(f"  mind   : {b['maxalloc_kb']} KB largest contiguous block (NOT free heap)")
    print(f"  self   : up {up_s}   worst loop pass {b['worst_loop_ms']} ms "
          f"(= what the mesh feels as rtt)")
    print(f"  band   : {bpm} bpm  conductor {cond}"
          + ("*" if b["conductor"] else "") + ("  playing" if b["playing"] else "")
          + ("  clk+" if b["synced"] else "  clk-"))


def gps(port, baud, node, at, probes, settle, fixes_path):
    """SP2: read the node's GPS fix (CMD_GET_GPS). With --at NODE, record it as a
    ground-truth tie point beside that static node for `anchor` to consume."""
    try:
        import serial  # pyserial
    except ImportError:
        sys.exit("pyserial not installed. Run: pip install -r requirements.txt")
    if node not in NODE_IDS:
        sys.exit(f"unknown node '{node}'. choices: {', '.join(NODE_IDS)}")
    if at is not None and at not in NODE_IDS:
        sys.exit(f"unknown --at node '{at}'. choices: {', '.join(NODE_IDS)}")
    target = NODE_IDS[node]
    reader = SerialFrameReader()
    with serial.Serial(port, baud, timeout=0.1) as ser:
        time.sleep(settle)
        ser.reset_input_buffer()
        print(f"querying GPS on {node} (0x{target:08X}) via {port} ...")
        fix = gps_probe(ser, reader, target, probes)

    if fix is None:
        sys.exit(f"no GPS PERCEPT from {node} — is it powered and on the mesh/bridge?")
    q = fix["quality"]
    if q == 0:
        print(f"{node}: NO FIX yet (quality 0, {fix['sats']} sats) — the GPS is talking "
              f"but hasn't locked. Give it sky view + a minute, then retry.")
        return
    qual = {1: "GPS", 2: "DGPS"}.get(q, f"q{q}")
    print(f"{node} FIX ({qual}): {fix['lat_deg']:.7f}, {fix['lon_deg']:.7f}  "
          f"alt {fix['alt_m']:.1f} m  sats {fix['sats']}  HDOP {fix['hdop']:.1f}")

    if at is None:
        print("(no --at given: not recorded. Re-run with --at <static-node> beside the "
              "node whose position this fix ties down.)")
        return
    now_iso = time.strftime("%Y-%m-%dT%H:%M:%SZ", time.gmtime())
    header = ("# Fleet GPS Fixes (semantic positioning SP2 ground truth)\n\n"
              "Authored by `companion.py gps --at <node>`: each record is a T-Deck GPS\n"
              "fix taken beside a static node. `companion.py anchor` fits the relative\n"
              "@BELIEF:POSITION map to these absolute tie points (GPS is the verifier +\n"
              "anchor, never an inference input). >=3 non-collinear ties resolve the "
              "mirror.\n")
    os.makedirs(os.path.dirname(os.path.abspath(fixes_path)) or ".", exist_ok=True)
    if not os.path.exists(fixes_path):
        with open(fixes_path, "w", encoding="utf-8", newline="\n") as f:
            f.write(header)
    with open(fixes_path, "a", encoding="utf-8", newline="\n") as f:
        f.write(f"\n---\n\n@PERCEPT:GPS @at({at})\n"
                f"lat_deg: {fix['lat_deg']:.7f}\nlon_deg: {fix['lon_deg']:.7f}\n"
                f"alt_m: {fix['alt_m']:.1f}\nquality: {q}\nsats: {fix['sats']}\n"
                f"hdop: {fix['hdop']:.1f}\nsource_node: {node}\n"
                f"node_epoch_ms: {fix['epoch_ms']}\ntouched: {now_iso}\n")
    print(f"recorded a tie point for '{at}' -> {fixes_path}")


def parse_gps_fixes(path):
    """Parse master/gps-fixes.md -> {node: (lat_deg, lon_deg)} averaging quality>0
    fixes per tie node."""
    with open(path, encoding="utf-8") as f:
        text = f.read()
    acc = {}
    for chunk in text.split("@PERCEPT:GPS")[1:]:
        m_at = re.match(r"\s*@at\((\w+)\)", chunk)
        fields = {k: re.search(k + r":\s*(-?[\d.]+)", chunk)
                  for k in ("lat_deg", "lon_deg", "quality")}
        if not m_at or not all(fields.values()):
            continue
        if int(float(fields["quality"].group(1))) == 0:
            continue
        node = m_at.group(1)
        lat, lon = float(fields["lat_deg"].group(1)), float(fields["lon_deg"].group(1))
        acc.setdefault(node, []).append((lat, lon))
    return {nd: (sum(p[0] for p in v) / len(v), sum(p[1] for p in v) / len(v))
            for nd, v in acc.items()}


def procrustes_2d(src, dst):
    """Best-fit 2D similarity (scale + rotation + translation, reflection allowed)
    mapping src points onto dst, in closed form (no numpy). src/dst: equal-length
    lists of (x, y). Returns a dict with theta, scale, reflect, centroids and rmse.
    Reflection is chosen when it lowers the residual — this is what resolves the
    embedding's mirror once >=3 non-collinear ties exist (2 ties leave it ambiguous)."""
    import math
    n = len(src)
    sx = sum(p[0] for p in src) / n
    sy = sum(p[1] for p in src) / n
    dx = sum(q[0] for q in dst) / n
    dy = sum(q[1] for q in dst) / n
    Q = [(q[0] - dx, q[1] - dy) for q in dst]

    def fit(reflect):
        P = [(p[0] - sx, -(p[1] - sy) if reflect else (p[1] - sy)) for p in src]
        a = sum(P[i][0] * Q[i][0] + P[i][1] * Q[i][1] for i in range(n))
        b = sum(P[i][0] * Q[i][1] - P[i][1] * Q[i][0] for i in range(n))
        theta = math.atan2(b, a)
        denom = sum(P[i][0] ** 2 + P[i][1] ** 2 for i in range(n)) or 1e-9
        s = math.hypot(a, b) / denom
        c, sn = math.cos(theta), math.sin(theta)
        res = 0.0
        for i in range(n):
            rx = s * (c * P[i][0] - sn * P[i][1])
            ry = s * (sn * P[i][0] + c * P[i][1])
            res += (rx - Q[i][0]) ** 2 + (ry - Q[i][1]) ** 2
        return theta, s, res

    th0, s0, r0 = fit(False)
    th1, s1, r1 = fit(True)
    reflect = r1 < r0 - 1e-9
    theta, s, res = (th1, s1, r1) if reflect else (th0, s0, r0)
    return {"theta": theta, "scale": s, "reflect": reflect,
            "src_centroid": (sx, sy), "dst_centroid": (dx, dy),
            "rmse": (res / n) ** 0.5}


def apply_fit(fit, x, y):
    """Map a relative (x, y) through a procrustes_2d fit -> dst-frame (east, north) m."""
    import math
    px = x - fit["src_centroid"][0]
    py = -(y - fit["src_centroid"][1]) if fit["reflect"] else (y - fit["src_centroid"][1])
    c, sn = math.cos(fit["theta"]), math.sin(fit["theta"])
    ex = fit["scale"] * (c * px - sn * py) + fit["dst_centroid"][0]
    en = fit["scale"] * (sn * px + c * py) + fit["dst_centroid"][1]
    return ex, en


def parse_positions_file(path):
    """Parse master/positions.md -> ({node: (x_m, y_m)}, {node: sigma_m})."""
    with open(path, encoding="utf-8") as f:
        text = f.read()
    pos, sig = {}, {}
    for chunk in text.split("@BELIEF:POSITION")[1:]:
        m = re.match(r"\s*@node\((\w+)\)", chunk)
        fx = re.search(r"x_m:\s*(-?[\d.]+)", chunk)
        fy = re.search(r"y_m:\s*(-?[\d.]+)", chunk)
        fs = re.search(r"sigma_m:\s*(-?[\d.]+)", chunk)
        if not (m and fx and fy):
            continue
        pos[m.group(1)] = (float(fx.group(1)), float(fy.group(1)))
        sig[m.group(1)] = float(fs.group(1)) if fs else 0.0
    return pos, sig


def anchor(positions_path, fixes_path, out):
    """SP2 anchoring: fit the relative @BELIEF:POSITION map to the T-Deck GPS tie
    points and emit absolute-coordinate @BELIEF:POSITION records (lat/lon), resolving
    the mirror when >=3 non-collinear ties are available."""
    import math
    pos, sig = parse_positions_file(positions_path)
    if not pos:
        sys.exit(f"no @BELIEF:POSITION in {positions_path} — run `positions` first")
    try:
        ties_geo = parse_gps_fixes(fixes_path)
    except FileNotFoundError:
        sys.exit(f"no GPS fixes at {fixes_path} — run `gps --at <node>` at >=2 (ideally "
                 f">=3) static nodes first")
    ties = [nd for nd in ties_geo if nd in pos]
    if len(ties) < 2:
        sys.exit(f"need GPS ties at >=2 embedded nodes; have {len(ties)} ({ties}). "
                 f"Walk the T-Deck to more static nodes and `gps --at` each.")

    # Geo reference = tie centroid; project ties to a local ENU (metres) tangent plane.
    lat0 = sum(ties_geo[nd][0] for nd in ties) / len(ties)
    lon0 = sum(ties_geo[nd][1] for nd in ties) / len(ties)
    m_per_deg_lon = M_PER_DEG_LAT * math.cos(math.radians(lat0))

    def geo_to_enu(lat, lon):
        return ((lon - lon0) * m_per_deg_lon, (lat - lat0) * M_PER_DEG_LAT)

    def enu_to_geo(e, n):
        return (lat0 + n / M_PER_DEG_LAT, lon0 + e / m_per_deg_lon)

    src = [pos[nd] for nd in ties]
    dst = [geo_to_enu(*ties_geo[nd]) for nd in ties]
    fit = procrustes_2d(src, dst)
    flip_resolved = len(ties) >= 3
    # Scale should be ~1 (both frames are metric); a big departure flags a calibration
    # or tie-measurement error worth surfacing rather than silently absorbing.
    scale_warn = "" if 0.85 <= fit["scale"] <= 1.15 else "  <-- WARN: far from 1.0"

    geo = {}
    for nd, (x, y) in pos.items():
        e, n = apply_fit(fit, x, y)
        geo[nd] = enu_to_geo(e, n)

    now_iso = time.strftime("%Y-%m-%dT%H:%M:%SZ", time.gmtime())
    os.makedirs(os.path.dirname(os.path.abspath(out)) or ".", exist_ok=True)
    with open(out, "w", encoding="utf-8", newline="\n") as f:
        f.write("# Fleet Anchored Position Beliefs (semantic positioning SP2)\n\n"
                "Authored by `companion.py anchor`: the relative @BELIEF:POSITION map\n"
                "(positions.md) fitted onto the T-Deck GPS tie points (gps-fixes.md) by\n"
                "a 2D similarity (scale+rotation+translation, reflection allowed). GPS is\n"
                "the verifier + anchor, never an inference input. flip_resolved is true\n"
                "only with >=3 non-collinear ties (2 leave the mirror ambiguous).\n\n"
                f"fit: ties={len(ties)} {ties}  scale={fit['scale']:.4f}{scale_warn}  "
                f"reflected={fit['reflect']}  tie_rmse={fit['rmse']:.2f} m  "
                f"flip_resolved={flip_resolved}\n")
        for nd in sorted(geo):
            lat, lon = geo[nd]
            f.write(f"\n---\n\n@BELIEF:POSITION @node({nd})\n"
                    f"frame: geo   # absolute, GPS-anchored\n"
                    f"lat_deg: {lat:.7f}\nlon_deg: {lon:.7f}\n"
                    f"x_m: {pos[nd][0]:.2f}\ny_m: {pos[nd][1]:.2f}   # relative frame\n"
                    f"sigma_m: {sig.get(nd, 0.0):.2f}\n"
                    f"anchor_chain: [v4a_bridge, gps]\n"
                    f"is_tie: {'yes' if nd in ties else 'no'}\n"
                    f"flip_resolved: {'true' if flip_resolved else 'false'}\n"
                    f"tie_rmse_m: {fit['rmse']:.2f}\n"
                    f"touched: {now_iso}\n")

    print(f"anchor: fitted {len(pos)} node(s) to {len(ties)} GPS tie(s) {ties}")
    print(f"  scale {fit['scale']:.4f}{scale_warn}  reflected {fit['reflect']}  "
          f"tie rmse {fit['rmse']:.2f} m  flip_resolved {flip_resolved}")
    if not flip_resolved:
        print("  NOTE: 2 ties fix rotation+translation but NOT the mirror. A 3rd "
              "non-collinear GPS tie resolves flip_resolved.")
    print(f"  {'node':<12} {'lat_deg':>13} {'lon_deg':>13}  tie")
    for nd in sorted(geo):
        lat, lon = geo[nd]
        print(f"  {nd:<12} {lat:>13.7f} {lon:>13.7f}  {'*' if nd in ties else ''}")
    print(f"\nwrote {out}")


# --- SP6: fleet-map TTDB for the T-Deck globe --------------------------------
# The T-Deck globe (PLAN.md SP6-T) renders whatever is in its on-flash TTDB. This
# authors "the map the mesh draws of itself": one record per fleet node at its
# believed position (from positions.md), body = the belief, and a relates: edge per
# link TYPED BY TRANSPORT (from proximity.md) so the globe colours links with no
# firmware guesswork. Same file the antfriend.github.io viewer loads -> one lineage.
DEFAULT_FLEETMAP_OUT = os.path.join("firmware", "tdeck_console", "data", "ttdb.md")
FLEETMAP_SCALE_DEG_PER_M = 1.0   # metres -> globe degrees (must match the firmware)
FLEET_FRIENDLY = {
    "v4a_bridge": "V4-A", "v4b_relay": "V4-B", "v4c_edge": "V4-C",
    "k10_1": "K10", "k10_2": "K10-2", "k10_3": "K10-3", "tdeck_1": "T-Deck",
    "cardputer_1": "Card",
}


def _parse_positions_full(path):
    """positions.md -> {node: {x_m, y_m, sigma_m, conf}}."""
    with open(path, encoding="utf-8") as f:
        text = f.read()
    nodes = {}
    for chunk in text.split("@BELIEF:POSITION")[1:]:
        m = re.match(r"\s*@node\((\w+)\)", chunk)
        if not m:
            continue

        def g(key):
            mm = re.search(rf"{key}:\s*(-?[\d.]+)", chunk)
            return float(mm.group(1)) if mm else 0.0
        nodes[m.group(1)] = {"x_m": g("x_m"), "y_m": g("y_m"),
                             "sigma_m": g("sigma_m"), "conf": g("conf")}
    return nodes


def _parse_proximity(path):
    """proximity.md -> {frozenset(a,b): {proto, dist_est_m, conf}} (undirected)."""
    if not os.path.exists(path):
        return {}
    with open(path, encoding="utf-8") as f:
        text = f.read()
    edges = {}
    for chunk in text.split("@BELIEF:PROXIMITY")[1:]:
        m = re.match(r"\s*@pair\(([^,]+),\s*([^)]+)\)", chunk)
        if not m:
            continue
        proto = re.search(r"proto:\s*(\w+)", chunk)
        dist = re.search(r"dist_est_m:\s*(-?[\d.]+)", chunk)
        conf = re.search(r"\nconf:\s*(-?[\d.]+)", chunk)
        edges[frozenset((m.group(1).strip(), m.group(2).strip()))] = {
            "proto": proto.group(1) if proto else "espnow",
            "dist_est_m": float(dist.group(1)) if dist else 0.0,
            "conf": float(conf.group(1)) if conf else 0.0}
    return edges


def _fleet_coords(nodes):
    """node -> (lat, lon) int degrees, nudged so none collide (index is int16)."""
    used, coord = set(), {}
    for name, p in nodes.items():
        lat = int(round(p["y_m"] * FLEETMAP_SCALE_DEG_PER_M))
        lon = int(round(p["x_m"] * FLEETMAP_SCALE_DEG_PER_M))
        while (lat, lon) in used:
            lon += 1
        used.add((lat, lon))
        coord[name] = (lat, lon)
    return coord


def fleetmap(positions_path, proximity_path, out):
    nodes = _parse_positions_full(positions_path)
    if not nodes:
        sys.exit(f"no @BELIEF:POSITION in {positions_path} — run `positions` first")
    edges = _parse_proximity(proximity_path)
    coord = _fleet_coords(nodes)
    ts = 1750000000
    anchor_node = "v4a_bridge" if "v4a_bridge" in coord else next(iter(coord))
    alat, alon = coord[anchor_node]

    parts = ["# T-Deck Fleet Map TTDB (semantic positioning SP6)\n", """
```mmpdb
db_id: tdeck-console-001
db_name: T-Deck Handheld Console - Fleet Map
coord_increment:
  lat: 1
  lon: 1
collision_policy: reject
timestamp_kind: unix
umwelt:
  umwelt_id: tdeck-console
  role: handheld-console
  perspective: operator
  scope: fleet-command
  globe:
    frame: mesh-topology
    origin: "@LAT0LON0"
    mapping: "each record is a fleet node at its believed position; the map the mesh draws of itself (companion.py fleetmap from positions.md + proximity.md)"
typed_edges:
  enabled: true
  syntax: "type@LATxLONy"
librarian:
  enabled: false
  primitive_queries: []
```
""", f"\n```cursor\nlat: {alat}\nlon: {alon}\n```\n"]

    for name, p in nodes.items():
        lat, lon = coord[name]
        rel = []
        for pair, e in edges.items():
            if name in pair:
                other = next(n for n in pair if n != name)
                if other in coord:
                    olat, olon = coord[other]
                    rel.append(f"{e['proto']}@LAT{olat}LON{olon}")
        relates = "relates:" + ",".join(rel)
        parts.append("\n---\n")
        parts.append(f"\n@LAT{lat}LON{lon} | created:{ts} | updated:{ts} | {relates}\n")
        parts.append(f"\n**POSITION** node:{name}\n")
        parts.append(f"name: {FLEET_FRIENDLY.get(name, name)}\n")
        parts.append(f"x_m: {p['x_m']:.2f}  y_m: {p['y_m']:.2f}\n")
        parts.append(f"sigma_m: {p['sigma_m']:.2f}   conf: {p['conf']:.2f}\n")
        for pair, e in edges.items():
            if name in pair:
                other = next(n for n in pair if n != name)
                parts.append(f"link {FLEET_FRIENDLY.get(other, other)}: {e['proto']} "
                             f"{e['dist_est_m']:.1f}m conf {e['conf']:.2f}\n")
    ttdb = "".join(parts)
    with open(out, "w", encoding="utf-8", newline="\n") as f:
        f.write(ttdb)
    print(f"fleetmap: {len(nodes)} node(s), {len(edges)} link(s) -> {out} "
          f"({len(ttdb.encode('utf-8'))} B)")
    for name in nodes:
        lat, lon = coord[name]
        print(f"  {FLEET_FRIENDLY.get(name, name):<7} @LAT{lat}LON{lon}  "
              f"sigma {nodes[name]['sigma_m']:.1f} m")
    print("flash it: python scripts/... then Upload-Tdeck-FS.ps1 -Port COM10")


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
    bd.add_argument("--nodes", default="v4a_bridge,v4b_relay,v4c_edge,tdeck_1",
                    help="comma-separated nodes to probe")
    bd.add_argument("--bound-ms", type=float, default=50.0, dest="bound_ms")
    bd.add_argument("--probes", type=int, default=5)
    bd.add_argument("--settle", type=float, default=0.5)
    bd.add_argument("--watch", action="store_true",
                    help="refresh the table live until Ctrl-C")
    bd.add_argument("--interval", type=float, default=1.0,
                    help="seconds between refreshes (--watch)")

    rd = sub.add_parser("record",
                        help="beat-scheduled fleet audio capture (CMD_RECORD)")
    rd.add_argument("--port", required=True, help="bridge serial port (COM6, ...)")
    rd.add_argument("--baud", type=int, default=115200)
    rd.add_argument("--nodes", default="cardputer_1",
                    help="comma-separated nodes to record + pull from")
    rd.add_argument("--lead-beats", type=int, default=8, dest="lead_beats",
                    help="beats of notice before the capture starts; rounded up to a "
                         "downbeat. Keep it >=4: a node mid percept-flush stalls for "
                         "60-220 ms and would miss a nearer start")
    rd.add_argument("--dur-beats", type=int, default=4, dest="dur_beats",
                    help="capture length in beats (4 = one bar = 2 s at 120 BPM, "
                         "which is the 32 KB the node's RAM buffer holds)")
    rd.add_argument("--out", default=os.path.join("master", "recordings"),
                    help="directory for the per-node WAVs")
    rd.add_argument("--settle", type=float, default=0.5)
    rd.add_argument("--copies", type=int, default=3,
                    help="broadcast repeats; re-arming the same instant is a node no-op")
    rd.add_argument("--self-test", action="store_true", dest="self_test",
                    help="beep 1 kHz for 200 ms at the MIDPOINT of the window, so the "
                         "captured audio can be checked for the right signal at the "
                         "right instant rather than merely for having arrived")

    cm = sub.add_parser("cmd", help="send a CMD to a node (ping/set-led/clear-led)")
    cm.add_argument("--port", required=True, help="serial port (COM5, /dev/ttyACM0)")
    cm.add_argument("--baud", type=int, default=115200)
    cm.add_argument("--node", required=True, choices=list(NODE_IDS) + ["broadcast"])
    cm.add_argument("--op", required=True, choices=list(CMD_OPS))
    cm.add_argument("--rgb", default=None, help="RRGGBB hex for set-led (e.g. FF0000)")
    cm.add_argument("--freq", type=int, default=880, help="beep frequency Hz")
    cm.add_argument("--dur-ms", type=int, default=200, dest="dur_ms",
                    help="beep duration ms")
    cm.add_argument("--interval-ms", type=int, default=None, dest="interval_ms",
                    help="agent sense/act cadence ms (set-interval)")
    cm.add_argument("--scene", type=int, default=None,
                    help="scene id for set-scene (only the conductor applies it)")
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

    ec = sub.add_parser(
        "entities",
        help="pull + print a node's entity-percept windows (@LAT96 WiFi APs, SP0)")
    ec.add_argument("--port", required=True, help="serial port (COM6, direct or bridge)")
    ec.add_argument("--baud", type=int, default=115200)
    ec.add_argument("--node", required=True, choices=list(NODE_IDS))
    ec.add_argument("--save", default=None,
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

    po = sub.add_parser(
        "positions",
        help="SP2: embed @BELIEF:PROXIMITY into @BELIEF:POSITION + a fleet map")
    po.add_argument("--proximity", default=DEFAULT_PROXIMITY_OUT,
                    help="proximity beliefs to embed (companion.py proximity)")
    po.add_argument("--out", default=DEFAULT_POSITIONS_OUT)
    po.add_argument("--iters", type=int, default=3000)

    gp = sub.add_parser(
        "gps", help="SP2: read the T-Deck GPS fix; --at records a ground-truth tie")
    gp.add_argument("--port", required=True, help="serial port (COM10 direct, or bridge)")
    gp.add_argument("--baud", type=int, default=115200)
    gp.add_argument("--node", default="tdeck_1", choices=list(NODE_IDS),
                    help="the GPS-bearing node to query (default tdeck_1)")
    gp.add_argument("--at", default=None, choices=list(NODE_IDS),
                    help="record this fix as a tie point beside this static node")
    gp.add_argument("--probes", type=int, default=6)
    gp.add_argument("--settle", type=float, default=2.5)
    gp.add_argument("--fixes", default=DEFAULT_GPS_FIXES,
                    help="tie-point file `anchor` consumes")

    io = sub.add_parser(
        "intero", help="read a node's INTEROCEPTION (energy/heat/RAM/own slowness/band)")
    io.add_argument("--port", required=True, help="serial port (direct, or the bridge)")
    io.add_argument("--baud", type=int, default=115200)
    io.add_argument("--node", default="cardputer_1", choices=list(NODE_IDS),
                    help="the node to ask about its own body (default cardputer_1)")
    io.add_argument("--probes", type=int, default=4)
    io.add_argument("--settle", type=float, default=2.5)

    an = sub.add_parser(
        "anchor",
        help="SP2: fit the relative position map to GPS ties -> absolute lat/lon")
    an.add_argument("--positions", default=DEFAULT_POSITIONS_OUT,
                    help="relative @BELIEF:POSITION map (companion.py positions)")
    an.add_argument("--fixes", default=DEFAULT_GPS_FIXES,
                    help="GPS tie points (companion.py gps --at)")
    an.add_argument("--out", default=DEFAULT_ANCHORED_OUT)

    fm = sub.add_parser(
        "fleetmap",
        help="SP6: author the T-Deck fleet-map TTDB from position+proximity beliefs")
    fm.add_argument("--positions", default=DEFAULT_POSITIONS_OUT,
                    help="relative @BELIEF:POSITION map (companion.py positions)")
    fm.add_argument("--proximity", default=DEFAULT_PROXIMITY_OUT,
                    help="@BELIEF:PROXIMITY links (companion.py proximity)")
    fm.add_argument("--out", default=DEFAULT_FLEETMAP_OUT,
                    help="TTDB to write (flash with Upload-Tdeck-FS.ps1)")

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
    pb.add_argument("--positions", nargs="?", const=DEFAULT_POSITIONS_OUT,
                    default=None, dest="positions_src",
                    help="publish the fleet @BELIEF:POSITION map (SP2) instead of the "
                         "sync belief; optional path (default master/positions.md)")
    pb.add_argument("--anchored", action="store_const", const=DEFAULT_ANCHORED_OUT,
                    dest="positions_src",
                    help="publish the GPS-anchored (geo) position map "
                         "(master/anchored.md) — shorthand for --positions with that file")

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
    elif args.cmd == "record":
        record(args.port, args.baud, [s for s in args.nodes.split(",") if s],
               args.lead_beats, args.dur_beats, args.out, args.settle, args.copies,
               args.self_test)
    elif args.cmd == "cmd":
        send_cmd(args.port, args.baud, args.node, args.op, args.rgb, args.freq,
                 args.dur_ms, args.interval_ms, args.settle, args.rto0, args.attempts,
                 scene=args.scene)
    elif args.cmd == "percepts":
        percepts(args.port, args.baud, args.node, args.save)
    elif args.cmd == "entities":
        entities(args.port, args.baud, args.node, args.save)
    elif args.cmd == "proximity":
        do_pull = bool(args.port) and not args.no_pull
        proximity(args.port, args.baud, [s for s in args.nodes.split(",") if s],
                  args.out, do_pull, args.settle, args.calibration, args.last,
                  args.clear)
    elif args.cmd == "calibrate":
        calibrate(args.proto, args.station, args.out, args.note)
    elif args.cmd == "positions":
        positions(args.proximity, args.out, args.iters)
    elif args.cmd == "gps":
        gps(args.port, args.baud, args.node, args.at, args.probes, args.settle,
            args.fixes)
    elif args.cmd == "intero":
        intero(args.port, args.baud, args.node, args.probes, args.settle)
    elif args.cmd == "anchor":
        anchor(args.positions, args.fixes, args.out)
    elif args.cmd == "fleetmap":
        fleetmap(args.positions, args.proximity, args.out)
    elif args.cmd == "monitor":
        monitor(args.port, args.baud, [s for s in args.nodes.split(",") if s],
                args.interval, args.rounds, args.settle)
    elif args.cmd == "reconcile":
        do_pull = bool(args.port) and not args.no_pull
        reconcile(args.port, args.baud, [s for s in args.nodes.split(",") if s],
                  args.master, args.out, do_pull, args.settle)
    elif args.cmd == "push":
        push(args.port, args.baud, args.node, args.src_master, args.belief_log,
             args.out, args.settle, args.rto0, args.attempts, args.sense_interval_ms,
             positions_src=args.positions_src)


if __name__ == "__main__":
    main()
