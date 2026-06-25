#!/usr/bin/env python3
"""test_pull_py.py — verify companion.py's pull-stream reliability layer without
any serial hardware: gap detection + selective TTDB_REQ_RANGE re-request recovers
a lossy offset-addressed TTDB_DATA stream byte-exact (the laptop half of the
"pull-stream ACK" work; closes the old ~1/6 bridged-pull frame drop).

The firmware half (handleRequest's TTDB_REQ_RANGE branch) is gated on-device by a
bridged `companion.py pull` that now self-heals dropped slices.

Run: python tests/test_pull_py.py
"""
import os
import struct
import sys

sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "orchestrator"))
import companion as c  # noqa: E402

fails = 0


def check(cond, msg):
    global fails
    print(("pass: " if cond else "FAIL: ") + msg)
    if not cond:
        fails += 1


# ---------------------------------------------------------------------------
# 1) missing_ranges: holes in offset coverage given a known total length.
# ---------------------------------------------------------------------------
check(c.missing_ranges({}, 0) == [], "empty object -> no gaps")
check(c.missing_ranges({0: b"x" * 10}, 10) == [], "fully covered -> no gaps")
check(c.missing_ranges({}, 10) == [(0, 10)], "nothing received -> whole file is a gap")
# Two 202-B slices present (0, 202), a 202-B slice dropped at 404, total 606.
present = {0: b"a" * 202, 202: b"b" * 202}
check(c.missing_ranges(present, 606) == [(404, 606)], "trailing dropped slice -> tail gap")
# Middle slice dropped: have [0,202) and [404,606), miss [202,404).
mid = {0: b"a" * 202, 404: b"c" * 202}
check(c.missing_ranges(mid, 606) == [(202, 404)], "middle dropped slice -> interior gap")
# Multiple holes, out-of-order keys, overlap-safe.
multi = {404: b"c" * 100, 0: b"a" * 100}
check(c.missing_ranges(multi, 600) == [(100, 404), (504, 600)],
      "multiple holes detected from out-of-order slices")


# ---------------------------------------------------------------------------
# 2) End-to-end: a mock node streams TTDB_DATA, dropping some slices on the first
#    whole-file pass; request_ttdb must re-request the gaps and reassemble exact.
# ---------------------------------------------------------------------------
SLICE = 202  # mirrors firmware TtdbShare kSliceData


class MockNode:
    """Serves an offset-addressed TTDB_DATA stream like TtdbShare. Drops the data
    slices whose start offset is in `drop` — but only on the first WHOLE pass, so a
    re-requested RANGE is served cleanly (models transient air loss that a retry
    survives). The EOF marker is never dropped, so the total length is always learned."""

    def __init__(self, node_id, data, drop):
        self.node_id = node_id
        self.data = data
        self.drop = set(drop)
        self.seq = 1
        self.rx = bytearray()      # bytes waiting for the companion to read()

    def _emit(self, offset, payload_bytes):
        pl = struct.pack("<IH", offset, len(payload_bytes)) + payload_bytes
        frame = c.encode_toot(c.TTDB_DATA, self.node_id, self.seq, pl)
        self.seq += 1
        self.rx += b"\xAB\xCD" + struct.pack("<H", len(frame)) + frame

    def _serve(self, start, end, apply_drops):
        off = start
        while off < end:
            n = min(SLICE, end - off)
            if not (apply_drops and off in self.drop):
                self._emit(off, self.data[off:off + n])
            off += n
        self._emit(end, b"")  # EOF marker at the served range's end

    def on_request(self, frame):
        t = c.decode_toot(frame)
        if not t or t["type"] != c.TTDB_REQ:
            return
        p = t["payload"]
        mode = p[0]
        target = struct.unpack("<I", p[1:5])[0]
        if target != self.node_id:
            return
        if mode == c.TTDB_REQ_RANGE:
            start, end = struct.unpack("<II", p[5:13])
            self._serve(start, end, apply_drops=False)
        else:  # WHOLE
            self._serve(0, len(self.data), apply_drops=True)
            self.drop.clear()  # transient loss: gone on the retry


class MockSerial:
    """Just enough of pyserial for request_ttdb: write() hands the frame to the
    node (which synchronously queues its reply), read() drains that queue."""

    def __init__(self, node):
        self.node = node
        self.fr = c.SerialFrameReader()

    def write(self, data):
        for frame in self.fr.feed(data):
            self.node.on_request(frame)

    def flush(self):
        pass

    def read(self, n=1):
        take = self.node.rx[:n]
        del self.node.rx[:n]
        return bytes(take)


def run_pull(blob, drop):
    node = MockNode(0x0BADF00D, blob, drop)
    ser = MockSerial(node)
    reader = c.SerialFrameReader()
    return c.request_ttdb(ser, reader, node.node_id, timeout=5.0)


# A ~1.1 KB TTDB (like the K10's) spans 6 data slices; drop a couple mid-stream.
blob = bytes((i * 37 + 11) & 0xFF for i in range(1126))

got = run_pull(blob, drop=[])
check(got == blob, "lossless pull reassembles byte-exact")

got = run_pull(blob, drop=[202, 808])
check(got == blob, "two dropped slices recovered via range re-request -> byte-exact")

got = run_pull(blob, drop=[0])
check(got == blob, "dropped first slice (offset 0) recovered -> byte-exact")

# Drop the last data slice (start offset 1010 for a 1126-B blob): tail gap to EOF.
last = (len(blob) // SLICE) * SLICE
got = run_pull(blob, drop=[last])
check(got == blob, "dropped final data slice recovered -> byte-exact")

# Empty object: EOF only, no data, no gaps.
check(run_pull(b"", drop=[]) == b"", "empty TTDB -> empty bytes, no spurious gaps")


# ---------------------------------------------------------------------------
# 3) Companion-side induced loss (`pull --drop`): discard slices by arrival index
#    on the first pass against a LOSSLESS node, then recover via range re-request.
#    This is the exact mechanism the on-device --drop test exercises.
# ---------------------------------------------------------------------------
def run_pull_drop(blob, drop_idx):
    node = MockNode(0x0BADF00D, blob, drop=[])   # node is lossless...
    ser = MockSerial(node)
    reader = c.SerialFrameReader()
    return c.request_ttdb(ser, reader, node.node_id, timeout=5.0, drop=set(drop_idx))


check(run_pull_drop(blob, [1, 3]) == blob,
      "--drop discards slices 1,3 on first pass; range re-request recovers byte-exact")
check(run_pull_drop(blob, [0]) == blob, "--drop 0 (first slice) recovers byte-exact")
# Dropping an index past the last slice is a no-op (nothing to recover).
check(run_pull_drop(blob, [99]) == blob, "--drop of an absent index is a harmless no-op")


print()
if fails:
    print(f"{fails} FAILED")
    sys.exit(1)
print("all pull-reliability checks passed")
