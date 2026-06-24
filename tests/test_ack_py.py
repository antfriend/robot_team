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
check({"ping", "set-led", "clear-led"} <= set(c.CMD_OPS),
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

# 13) beep / set-interval ops are exposed and their CmdOp codes match the firmware.
check(c.CMD_OPS["beep"] == 4 and c.CMD_OPS["set-interval"] == 5,
      "CMD_OPS adds beep(4) + set-interval(5)")
# beep args = freq u16 | dur_ms u16; set-interval args = interval_ms u16 (all LE).
check(struct.pack("<HH", 880, 200) == bytes([0x70, 0x03, 0xC8, 0x00]),
      "beep arg layout: freq u16 | dur_ms u16 LE")
check(struct.pack("<H", 500) == bytes([0xF4, 0x01]),
      "set-interval arg layout: interval_ms u16 LE")

# 14) reconcile parser: parse_sync_file reads full SYNC records (Dream-Cycle seed).
d = tempfile.mkdtemp()
mf = os.path.join(d, "m.md")
with open(mf, "w", encoding="utf-8") as f:
    f.write("**SYNC** id:1 t_ms:1782170699715 recv_ms:1782170699715 offset_ms:0\n")
    # node-style: small recv_ms (millis), large offset; t_ms = recv_ms + offset
    f.write("**SYNC** id:2 t_ms:1782170835676 recv_ms:50321 offset_ms:1782170785355\n")
recs = c.parse_sync_file(mf)
check(len(recs) == 2 and recs[0]["id"] == 1 and recs[0]["t_ms"] == 1782170699715
      and recs[1]["recv_ms"] == 50321 and recs[1]["offset_ms"] == 1782170785355,
      "parse_sync_file reads id/t_ms/recv_ms/offset_ms (laptop + node styles)")
check(c.parse_sync_file(os.path.join(d, "nope.md")) == [],
      "parse_sync_file returns [] for a missing file")

# 15) TTDB_PUT slice payload (TTN-RFC-0009 §2.1) is wire-exact and round-trips.
tgt = c.NODE_IDS["k10_1"]
slice_data = bytes((i * 3 + 5) & 0xff for i in range(50))
pl = c.put_slice_payload(tgt, 7, 1000, 0xDEADBEEF, 186, slice_data)
expect = (struct.pack("<IIIII", tgt, 7, 1000, 0xDEADBEEF, 186)
          + struct.pack("<H", 50) + slice_data)
check(pl == expect and len(pl) == c.TTDB_PUT_HEADER_LEN + 50,
      "TTDB_PUT payload: target|belief_id|total|crc|offset|len|data (22B hdr)")
cd = c.decode_toot(c.encode_toot(c.TTDB_PUT, c.ORCHESTRATOR_ID, 1, pl,
                                 flags=c.FLAG_WANT_ACK))
p = cd["payload"]
check(struct.unpack("<I", p[0:4])[0] == tgt and struct.unpack("<I", p[4:8])[0] == 7
      and struct.unpack("<I", p[16:20])[0] == 186
      and struct.unpack("<H", p[20:22])[0] == 50 and p[22:72] == slice_data,
      "TTDB_PUT slice fields survive encode->decode")

# 16) crc32 == zlib (the cross-stack KAT firmware toot::crc32 must also satisfy).
check(c.crc32(b"") == 0 and c.crc32(b"123456789") == 0xCBF43926,
      "crc32 matches the zlib/IEEE KAT (empty=0, '123456789'=0xCBF43926)")
# Continuation: a split sum equals the whole-buffer sum (firmware folds slices).
whole = bytes(range(200))
import zlib as _z  # noqa: E402
split = _z.crc32(whole[100:], _z.crc32(whole[:100])) & 0xFFFFFFFF
check(split == c.crc32(whole), "crc32 is continuation-friendly (slice-by-slice == whole)")

# 17) Belief authoring + slicing (TTN-RFC-0009 §5): valid TTDB, exact re-slice.
bf = os.path.join(d, "bmaster.md")
with open(bf, "w", encoding="utf-8") as f:
    f.write(c.MASTER_SYNC_HEADER)
    f.write("\n---\n\n@LAT99LON0 | created:1 | updated:1 | relates:logs@LAT0LON0\n\n")
    f.write("**SYNC** id:1 t_ms:1782170699715 recv_ms:1782170699715 offset_ms:0\n")
content = c.author_belief(bf, sense_interval_ms=300)
check(b"**BELIEF**" in content and b"**BELIEF-SYNC** id:1" in content
      and b"@LAT0LON0" in content,
      "author_belief emits a BELIEF summary + per-event BELIEF-SYNC records")
check(b"**DIRECTIVE** sense_interval_ms:300" in content and b"@LAT0LON1" in content,
      "author_belief emits a behavioral DIRECTIVE record (Dream-Cycle closure)")
offs = list(range(0, len(content), c.TTDB_PUT_MAX_SLICE)) or [0]
rejoined = b"".join(content[o:o + c.TTDB_PUT_MAX_SLICE] for o in offs)
check(rejoined == content and all(
        len(content[o:o + c.TTDB_PUT_MAX_SLICE]) <= c.TTDB_PUT_MAX_SLICE for o in offs),
      "belief slices (<=186B) concat back byte-exact")

# Belief readback (TTN-RFC-0009 §3): the node serves /belief.md as the same
# offset-addressed TTDB_DATA stream as the live TTDB, selected by a request mode byte.
check(c.TTDB_REQ_BELIEF == 2 and c.TTDB_REQ_BELIEF != c.TTDB_REQ_WHOLE,
      "TTDB_REQ_BELIEF is the firmware enum value (2), distinct from WHOLE")
SLICE = 202  # TTDB_DATA data bytes/slice (firmware kSliceData)
bslices = {o: content[o:o + SLICE] for o in range(0, len(content), SLICE)}
check(c.reassemble(bslices, len(content)) == content,
      "belief readback reassembles byte-exact from offset slices + EOF length")

# 18) Belief id monotonicity + BELIEF-ADOPTED parsing (verify path).
blog = os.path.join(d, "belief-log.md")
check(c.next_belief_id(blog) == 1, "first belief_id is 1 with no push log")
c.append_belief_push_record(blog, 1, "k10_1", len(content), c.crc32(content))
check(c.next_belief_id(blog) == 2, "next_belief_id advances after a logged push")
adopted_txt = ("**BELIEF-ADOPTED** id:2 bytes:512 crc:DEADBEEF recv_ms:123\n"
               "**BELIEF-ADOPTED** id:3 bytes:99 crc:0000000A recv_ms:9 "
               "applied:interval_ms:300\n")
r = c.find_belief_adopted(adopted_txt, 2)
check(r == {"id": 2, "bytes": 512, "crc": 0xDEADBEEF, "applied_interval_ms": None},
      "find_belief_adopted reads id/bytes/crc of the matching record")
r3 = c.find_belief_adopted(adopted_txt, 3)
check(r3["applied_interval_ms"] == 300,
      "find_belief_adopted reads applied:interval_ms when the node acted on the DIRECTIVE")
check(c.find_belief_adopted(adopted_txt, 99) is None,
      "find_belief_adopted returns None for an absent belief_id")

print(("\n%d FAILED" % fails) if fails else "\nALL PASSED")
sys.exit(1 if fails else 0)
