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
PERCEPT = 2
BELIEF = 3
CMD = 4
ACK = 5
TTDB_REQ = 7
TTDB_DATA = 8
TIME_SYNC = 9
TIME_REQ = 10
TIME_RESP = 11
TTDB_REQ_WHOLE = 0

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
# User-facing `cmd` ops only (GET_STATUS is internal to `monitor`).
CMD_OPS = {"ping": CMD_PING, "set-led": CMD_SET_LED, "clear-led": CMD_CLEAR_LED,
           "beep": CMD_BEEP, "set-interval": CMD_SET_INTERVAL}

# STATUS payload (Toot.h): cursor_lat i16 | cursor_lon i16 | temp_x100 i16 |
# flags u8 | epoch_ms u64. Returned as a PERCEPT in answer to CMD_GET_STATUS.
STATUS_PAYLOAD_LEN = 15
STATUS_WARM = 1 << 0
STATUS_LED_OVERRIDE = 1 << 1
STATUS_SYNCED = 1 << 2

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


def pull(port, baud, node, out_path, timeout):
    try:
        import serial  # pyserial
    except ImportError:
        sys.exit("pyserial not installed. Run: pip install -r requirements.txt")
    if node not in NODE_IDS:
        sys.exit(f"unknown node '{node}'. choices: {', '.join(NODE_IDS)}")
    target = NODE_IDS[node]

    reader = SerialFrameReader()
    with serial.Serial(port, baud, timeout=0.1) as ser:
        # Opening the port resets the ESP32-S3 (DTR/RTS), so the node reboots here.
        # Wait out its boot (LittleFS mount + k10.begin) before the request, or it
        # lands during boot and is dropped. ~2.5s covers the K10 cold start. (A pull
        # only reads flash, so the reset is harmless here — unlike sync/verify.)
        time.sleep(2.5)
        ser.reset_input_buffer()   # discard the boot log so it isn't parsed as frames
        print(f"requested whole TTDB from {node} (0x{target:08X}) on {port}")
        data = request_ttdb(ser, reader, target, timeout)

    if data is None:
        sys.exit("no TTDB data received (check port, node id, and the key)")
    os.makedirs(os.path.dirname(os.path.abspath(out_path)), exist_ok=True)
    with open(out_path, "wb") as f:
        f.write(data)
    print(f"wrote {len(data)} bytes to {out_path}")


def request_ttdb(ser, reader, target, timeout=20.0):
    """Request a node's whole TTDB over an already-open link; return the
    reassembled bytes, or None. Shared by `pull` and `verify`. A fresh toot_seq
    keeps a non-reset target from dedup-dropping a repeated request."""
    req_payload = bytes([TTDB_REQ_WHOLE]) + struct.pack("<I", target)
    seq = int(time.time()) & 0x7FFFFFFF
    write_serial_frame(ser, encode_toot(TTDB_REQ, ORCHESTRATOR_ID, seq, req_payload))

    slices = {}            # offset -> bytes
    eof_offset = None
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
            break
    if not slices and eof_offset is None:
        return None
    return reassemble(slices, eof_offset)


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
            data = request_ttdb(ser, reader, target)         # Assertion A
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
    args = ap.parse_args()

    if args.cmd == "pull":
        pull(args.port, args.baud, args.node, args.out, args.timeout)
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
    elif args.cmd == "cmd":
        send_cmd(args.port, args.baud, args.node, args.op, args.rgb, args.freq,
                 args.dur_ms, args.interval_ms, args.settle, args.rto0, args.attempts)
    elif args.cmd == "monitor":
        monitor(args.port, args.baud, [s for s in args.nodes.split(",") if s],
                args.interval, args.rounds, args.settle)
    elif args.cmd == "reconcile":
        do_pull = bool(args.port) and not args.no_pull
        reconcile(args.port, args.baud, [s for s in args.nodes.split(",") if s],
                  args.master, args.out, do_pull, args.settle)


if __name__ == "__main__":
    main()
