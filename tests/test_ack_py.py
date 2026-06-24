#!/usr/bin/env python3
"""test_ack_py.py — verify companion.py's ACK codec (TTN-RFC-0007) is wire-exact
and self-consistent, without any serial hardware.

This is the in-session gate for the laptop half of the reliability layer; the
firmware half is gated by tests/test_toot.cpp (native, run on-device / with g++).
Both encode the same 10-byte ACK payload over the same HMAC key, so a frame one
side emits decodes on the other.

Run: python tests/test_ack_py.py
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


# 1) ACK payload byte layout matches firmware toot::makeAck exactly:
#    ack_src u32 LE | ack_seq u32 LE | ack_chunk u8 | status u8.
ack_src, ack_seq = c.ORCHESTRATOR_ID, 0x12345678
pl = c.make_ack_payload(ack_src, ack_seq, 0, c.ACK_ACCEPTED)
expect = struct.pack("<II", ack_src, ack_seq) + bytes([0, 0])
check(pl == expect and len(pl) == c.ACK_PAYLOAD_LEN, "ACK payload is 10 wire-exact bytes")

# 2) Encode an ACK (as the firmware would), decode it back, verify HMAC + fields.
frame = c.encode_toot(c.ACK, 0x00000100, 42, pl)
t = c.decode_toot(frame)
check(t is not None, "ACK frame verifies HMAC (same key as firmware)")
check(t and t["type"] == c.ACK and t["src"] == 0x100 and t["seq"] == 42,
      "ACK header round-trips (type/src/seq)")

# 3) parse_ack extracts the acked (src, seq, chunk, status).
pa = c.parse_ack(t)
check(pa == (ack_src, ack_seq, 0, c.ACK_ACCEPTED),
      "parse_ack returns (ack_src, ack_seq, ack_chunk, status)")

# 4) A non-ACK toot is not parseable as an ACK.
cmd = c.decode_toot(c.encode_toot(c.CMD, ack_src, ack_seq, b"\x00",
                                  flags=c.FLAG_WANT_ACK))
check(c.parse_ack(cmd) is None, "parse_ack rejects a non-ACK toot")

# 5) want_ack flag rides in header byte 31 (flags), per Toot.h.
want = c.encode_toot(c.CMD, ack_src, ack_seq, b"\x00", flags=c.FLAG_WANT_ACK)
check(want[31] == c.FLAG_WANT_ACK, "FLAG_WANT_ACK set in the frame flags byte")

# 6) Tamper detection: flip a payload byte -> HMAC rejects.
bad = bytearray(frame)
bad[c.HEADER_LEN] ^= 0xFF
check(c.decode_toot(bytes(bad)) is None, "tampered ACK frame rejected")

# 7) Chunk split + placement must mirror the firmware Reassembler (TTN-RFC-0007 §6).
payload = bytes((i * 7 + 1) & 0xff for i in range(500))
chunks = [payload[i:i + c.MAX_BODY] for i in range(0, len(payload), c.MAX_BODY)]
check(len(chunks) == 3 and [len(x) for x in chunks] == [208, 208, 84],
      "500 B splits into 3 chunks of 208/208/84")
check(all(len(x) <= c.MAX_BODY for x in chunks), "no chunk exceeds MAX_BODY")
check(b"".join(chunks) == payload,
      "in-order concat reassembles byte-exact (placement math)")

# 8) chunk_idx / chunk_total survive encode -> decode (the fields the node routes on).
cf = c.encode_toot(c.BELIEF, c.ORCHESTRATOR_ID, 99, chunks[1],
                   flags=c.FLAG_WANT_ACK, chunk_idx=1, chunk_total=3)
cd = c.decode_toot(cf)
check(cd and cd["chunk_idx"] == 1 and cd["chunk_total"] == 3,
      "chunk_idx/chunk_total round-trip through the frame")

# 9) Time-sync payloads (TTN-RFC-0008) round-trip with a >32-bit epoch.
sid, epoch = 7, 1750000000123
ts = c.decode_toot(c.encode_toot(c.TIME_SYNC, c.ORCHESTRATOR_ID, 1,
                                 struct.pack("<I", sid) + struct.pack("<Q", epoch)))
got_sid = struct.unpack("<I", ts["payload"][0:4])[0]
got_epoch = struct.unpack("<Q", ts["payload"][4:12])[0]
check(got_sid == sid and got_epoch == epoch,
      "TIME_SYNC payload round-trips (u32 sync_id + u64 epoch_ms)")

tr = c.decode_toot(c.encode_toot(c.TIME_RESP, c.NODE_IDS["k10_1"], 1,
                                 struct.pack("<I", 42) + struct.pack("<Q", epoch)))
check(c.parse_time_resp(tr) == (42, epoch),
      "parse_time_resp returns (probe_id, node_epoch_ms)")

# 10) Master sync log: monotonic id, append, presence, firmware-matching format.
import tempfile  # noqa: E402
tmp = os.path.join(tempfile.mkdtemp(), "orchestrator-sync.md")
check(c.next_sync_id(tmp) == 1, "first sync_id is 1 when no master log exists")
c.append_master_sync_record(tmp, 1, 1750000000000)
c.append_master_sync_record(tmp, 2, 1750000005000)
check(c.next_sync_id(tmp) == 3, "next_sync_id is max(id)+1 after two records")
check(c.master_has_record(tmp, 2) and not c.master_has_record(tmp, 9),
      "master_has_record matches present / absent ids")
txt = open(tmp, encoding="utf-8").read()
check(len(c.SYNC_RE.findall(txt)) == 2 and "@LAT99LON0" in txt and
      "@LAT99LON1" in txt,
      "master uses @LAT99LON<n> lane + parseable **SYNC** lines (firmware format)")

# 11) CMD payload layout (op u8 | target u32 LE | args) == firmware cmdOp/cmdTarget.
tgt = c.NODE_IDS["k10_1"]
pl = bytes([c.CMD_SET_LED]) + struct.pack("<I", tgt) + bytes([0xFF, 0x00, 0x00])
cd = c.decode_toot(c.encode_toot(c.CMD, c.ORCHESTRATOR_ID, 1, pl,
                                 flags=c.FLAG_WANT_ACK))
p = cd["payload"]
check(p[0] == c.CMD_SET_LED and struct.unpack("<I", p[1:5])[0] == tgt and
      p[5:8] == bytes([0xFF, 0x00, 0x00]),
      "CMD set-led payload: op | target | RGB (firmware cmdOp/cmdTarget layout)")
check(set(c.CMD_OPS) == {"ping", "set-led", "clear-led"},
      "CMD_OPS exposes ping/set-led/clear-led")

# 12) STATUS payload (cursor/temp/flags/epoch) parses what the firmware packs.
flags = c.STATUS_WARM | c.STATUS_SYNCED
body = struct.pack("<hhhBQ", 10, 0, 2350, flags, 1782170835676)
st = c.parse_status(body)
check(st is not None and st["cursor"] == (10, 0) and abs(st["temp_c"] - 23.5) < 1e-6
      and st["warm"] and st["synced"] and not st["led"]
      and st["epoch_ms"] == 1782170835676,
      "parse_status reads cursor/temp/flags/epoch (firmware STATUS layout)")
check(c.parse_status(b"\x00\x00") is None, "parse_status rejects a short payload")

print(("\n%d FAILED" % fails) if fails else "\nALL PASSED")
sys.exit(1 if fails else 0)
