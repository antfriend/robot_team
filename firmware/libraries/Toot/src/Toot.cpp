#include "Toot.h"
#include "TootCrypto.h"

namespace toot {

size_t encode(const Toot& t, const uint8_t* key, size_t key_len, uint8_t* out,
              size_t out_cap) {
  size_t body = t.payload_len;
  if (body > MAX_BODY) return 0;
  size_t total = HEADER_LEN + body + HMAC_LEN;
  if (out_cap < total) return 0;

  out[0] = MAGIC0;
  out[1] = MAGIC1;
  out[2] = t.version ? t.version : VERSION;
  out[3] = t.type;
  put_u32(out + 4, t.src_node_id);
  put_u32(out + 8, t.toot_seq);
  out[12] = t.chunk_idx;
  out[13] = t.chunk_total;
  memcpy(out + 14, t.locus, LOCUS_LEN);  // 14..29
  out[30] = t.ttl;
  out[31] = t.flags;
  out[32] = (uint8_t)body;
  memcpy(out + HEADER_LEN, t.payload, body);

  hmac_sha256_trunc(key, key_len, out, HEADER_LEN + body,
                    out + HEADER_LEN + body);
  return total;
}

bool decode(const uint8_t* in, size_t in_len, const uint8_t* key,
            size_t key_len, Toot& t) {
  if (in_len < HEADER_LEN + HMAC_LEN) return false;
  if (in[0] != MAGIC0 || in[1] != MAGIC1) return false;
  uint8_t body = in[32];
  if (body > MAX_BODY) return false;
  size_t total = HEADER_LEN + body + HMAC_LEN;
  if (in_len < total) return false;

  uint8_t mac[HMAC_LEN];
  hmac_sha256_trunc(key, key_len, in, HEADER_LEN + body, mac);
  if (memcmp(mac, in + HEADER_LEN + body, HMAC_LEN) != 0) return false;

  t.version = in[2];
  t.type = in[3];
  t.src_node_id = get_u32(in + 4);
  t.toot_seq = get_u32(in + 8);
  t.chunk_idx = in[12];
  t.chunk_total = in[13];
  memcpy(t.locus, in + 14, LOCUS_LEN);
  t.ttl = in[30];
  t.flags = in[31];
  t.payload_len = body;
  memcpy(t.payload, in + HEADER_LEN, body);
  return true;
}

void makeAck(const Toot& orig, uint32_t acker_id, uint32_t acker_seq,
             uint8_t status, Toot& out) {
  out = Toot();              // reset to defaults (version, ttl=4, zeroed locus)
  out.type = ACK;
  out.src_node_id = acker_id;
  out.toot_seq = acker_seq;
  out.payload_len = (uint8_t)ACK_PAYLOAD_LEN;
  put_u32(out.payload + 0, orig.src_node_id);
  put_u32(out.payload + 4, orig.toot_seq);
  out.payload[8] = orig.chunk_idx;
  out.payload[9] = status;
}

bool parseAck(const Toot& ack, uint32_t& ack_src, uint32_t& ack_seq,
              uint8_t& ack_chunk, uint8_t& status) {
  if (ack.type != ACK || ack.payload_len < ACK_PAYLOAD_LEN) return false;
  ack_src = get_u32(ack.payload + 0);
  ack_seq = get_u32(ack.payload + 4);
  ack_chunk = ack.payload[8];
  status = ack.payload[9];
  return true;
}

bool ackMatches(const Toot& ack, uint32_t my_id, uint32_t my_seq,
                uint8_t my_chunk) {
  uint32_t s, q;
  uint8_t c, st;
  if (!parseAck(ack, s, q, c, st)) return false;
  return s == my_id && q == my_seq && c == my_chunk;
}

bool parseTimeSync(const Toot& t, uint32_t& sync_id, uint64_t& epoch_ms) {
  if (t.type != TIME_SYNC || t.payload_len < TIME_SYNC_PAYLOAD_LEN) return false;
  sync_id = get_u32(t.payload);
  epoch_ms = get_u64(t.payload + 4);
  return true;
}

bool parseTimeReq(const Toot& t, uint32_t& probe_id, uint32_t& target) {
  if (t.type != TIME_REQ || t.payload_len < TIME_REQ_PAYLOAD_LEN) return false;
  probe_id = get_u32(t.payload);
  target = get_u32(t.payload + 4);
  return true;
}

bool parseTimeResp(const Toot& t, uint32_t& probe_id, uint64_t& node_epoch_ms) {
  if (t.type != TIME_RESP || t.payload_len < TIME_RESP_PAYLOAD_LEN) return false;
  probe_id = get_u32(t.payload);
  node_epoch_ms = get_u64(t.payload + 4);
  return true;
}

// --- Reassembler (TTN-RFC-0007 §6) -----------------------------------------
Reassembler::Slot* Reassembler::find(uint32_t src, uint32_t seq) {
  for (size_t i = 0; i < TOOT_REASSEMBLY_SLOTS; ++i)
    if (slots_[i].used && slots_[i].src == src && slots_[i].seq == seq)
      return &slots_[i];
  return nullptr;
}

Reassembler::Slot* Reassembler::allocate(uint32_t now_ms) {
  for (size_t i = 0; i < TOOT_REASSEMBLY_SLOTS; ++i)
    if (!slots_[i].used) return &slots_[i];
  // None free: evict the oldest slot that has gone stale past the TTL.
  Slot* victim = nullptr;
  for (size_t i = 0; i < TOOT_REASSEMBLY_SLOTS; ++i) {
    if (now_ms - slots_[i].last_ms > TOOT_REASSEMBLY_TTL_MS &&
        (!victim || slots_[i].last_ms < victim->last_ms))
      victim = &slots_[i];
  }
  if (victim) victim->used = false;
  return victim;  // nullptr -> caller returns NO_RESOURCE
}

bool Reassembler::recentlyCompleted(uint32_t src, uint32_t seq) const {
  for (size_t i = 0; i < kCompletedCap; ++i)
    if (comp_valid_[i] && comp_src_[i] == src && comp_seq_[i] == seq) return true;
  return false;
}

void Reassembler::markCompleted(uint32_t src, uint32_t seq) {
  comp_src_[comp_head_] = src;
  comp_seq_[comp_head_] = seq;
  comp_valid_[comp_head_] = true;
  comp_head_ = (comp_head_ + 1) % kCompletedCap;
}

Reassembler::Result Reassembler::offer(const Toot& t, uint32_t now_ms) {
  uint8_t total = t.chunk_total, idx = t.chunk_idx;
  if (total <= 1 || total > TOOT_REASSEMBLY_MAX_CHUNKS || idx >= total) return BAD;
  if (recentlyCompleted(t.src_node_id, t.toot_seq)) return COMPLETED_DUP;

  Slot* s = find(t.src_node_id, t.toot_seq);
  if (!s) {
    s = allocate(now_ms);
    if (!s) return NO_RESOURCE;
    s->used = true;
    s->src = t.src_node_id;
    s->seq = t.toot_seq;
    s->total = total;
    s->got = 0;
    for (size_t i = 0; i < TOOT_REASSEMBLY_MAX_CHUNKS; ++i) {
      s->have[i] = false;
      s->len[i] = 0;
    }
  } else if (s->total != total) {
    return BAD;  // inconsistent chunk_total for the same key
  }
  s->last_ms = now_ms;
  if (s->have[idx]) return DUPLICATE;

  uint16_t n = t.payload_len > MAX_BODY ? MAX_BODY : t.payload_len;
  memcpy(s->buf + (size_t)idx * MAX_BODY, t.payload, n);
  s->len[idx] = n;
  s->have[idx] = true;
  s->got++;
  if (s->got < s->total) return NEED_MORE;

  out_len_ = 0;
  for (uint8_t i = 0; i < s->total; ++i) {
    memcpy(out_ + out_len_, s->buf + (size_t)i * MAX_BODY, s->len[i]);
    out_len_ += s->len[i];
  }
  s->used = false;
  markCompleted(t.src_node_id, t.toot_seq);
  return COMPLETE;
}

}  // namespace toot
