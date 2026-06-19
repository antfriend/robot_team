#include "TtdbShare.h"

namespace {
const uint16_t kSliceData = 202;  // 208 body - (u32 offset + u16 len)
}

int TtdbShare::handleRequest(const toot::Toot& req, SendFn send, void* ctx) {
  size_t start = 0;
  size_t end = db_.fileSize();

  if (req.payload_len >= 13 && req.payload[0] == toot::TTDB_REQ_RANGE) {
    start = toot::get_u32(req.payload + 5);
    end = toot::get_u32(req.payload + 9);
    if (end > db_.fileSize()) end = db_.fileSize();
    if (start > end) start = end;
  }

  int sent = 0;
  uint8_t buf[kSliceData];
  for (size_t off = start; off < end;) {
    size_t want = end - off;
    if (want > kSliceData) want = kSliceData;
    size_t got = db_.readBytes(off, buf, want);
    if (got == 0) break;
    sendSlice((uint32_t)off, buf, (uint16_t)got, send, ctx);
    ++sent;
    off += got;
    yield();
  }
  // EOF marker: zero-length slice at `end`.
  sendSlice((uint32_t)end, nullptr, 0, send, ctx);
  ++sent;
  return sent;
}

void TtdbShare::sendSlice(uint32_t offset, const uint8_t* data, uint16_t n,
                          SendFn send, void* ctx) {
  toot::Toot t;
  t.type = toot::TTDB_DATA;
  t.src_node_id = node_id_;
  t.toot_seq = seq_++;
  t.chunk_idx = 0;
  t.chunk_total = 1;
  memcpy(t.locus, locus_, toot::LOCUS_LEN);
  t.ttl = 4;
  t.flags = 0;

  toot::put_u32(t.payload + 0, offset);
  toot::put_u16(t.payload + 4, n);
  if (n && data) memcpy(t.payload + 6, data, n);
  t.payload_len = (uint8_t)(6 + n);

  uint8_t frame[toot::MAX_FRAME];
  size_t flen = toot::encode(t, key_, key_len_, frame, sizeof(frame));
  if (flen) send(frame, flen, ctx);
}
