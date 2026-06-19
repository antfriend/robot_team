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

}  // namespace toot
