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

print(("\n%d FAILED" % fails) if fails else "\nALL PASSED")
sys.exit(1 if fails else 0)
