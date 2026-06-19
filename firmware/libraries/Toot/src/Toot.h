// Toot.h — the 250-byte robot_team wire frame.
//
// Layout (little-endian multi-byte fields), matching
// toot_network_architecture.md section 3:
//
//   off  field         bytes
//   0    magic         2     0x54 0x54 ("TT")
//   2    version       1
//   3    type          1     see Type
//   4    src_node_id   4
//   8    toot_seq      4     (src,seq) is the dedup key
//   12   chunk_idx     1
//   13   chunk_total   1
//   14   locus_addr    16    @LATxLONy packed
//   30   ttl           1
//   31   flags         1
//   32   payload_len   1     <= 208
//   33   payload       <=208
//   ...  hmac          8     trunc HMAC-SHA256 over header+payload
#pragma once
#include <stdint.h>
#include <stddef.h>
#include <string.h>

namespace toot {

const uint8_t MAGIC0 = 0x54;  // 'T'
const uint8_t MAGIC1 = 0x54;  // 'T'
const uint8_t VERSION = 1;

const size_t HEADER_LEN = 33;
const size_t HMAC_LEN = 8;
const size_t MAX_BODY = 208;
const size_t MAX_FRAME = HEADER_LEN + MAX_BODY + HMAC_LEN;  // 249
const size_t LOCUS_LEN = 16;

enum Type : uint8_t {
  HELLO = 1,      // periodic beacon: node id, role, locus, channel
  PERCEPT = 2,    // a @PERCEPT fragment from a K10
  BELIEF = 3,     // a @BELIEF node from Dream-Cycle consolidation
  CMD = 4,        // companion -> node directive
  ACK = 5,        // confirms (src,seq[,chunk])
  RELAY = 6,      // out-of-range toot for a LoRa node to forward
  TTDB_REQ = 7,   // companion -> node: "share part or all of your TTDB"
  TTDB_DATA = 8,  // node -> companion: one offset-addressed slice of the TTDB
};

enum Flags : uint8_t {
  FLAG_WANT_ACK = 1 << 0,
  FLAG_ENCRYPTED = 1 << 1,
};

// TTDB_REQ payload layout:
//   [0]     mode (TtdbReqMode)
//   [1..4]  target_node_id (u32 LE) — only the addressed node answers
//   [5..8]  start (u32 LE)   } RANGE mode only
//   [9..12] end   (u32 LE)   }
// src_node_id in the header is the requester (the orchestrator).
enum TtdbReqMode : uint8_t {
  TTDB_REQ_WHOLE = 0,  // entire file
  TTDB_REQ_RANGE = 1,  // bytes [start,end)
};

struct Toot {
  uint8_t version = VERSION;
  uint8_t type = 0;
  uint32_t src_node_id = 0;
  uint32_t toot_seq = 0;
  uint8_t chunk_idx = 0;
  uint8_t chunk_total = 1;
  uint8_t locus[LOCUS_LEN] = {0};
  uint8_t ttl = 4;
  uint8_t flags = 0;
  uint8_t payload_len = 0;
  uint8_t payload[MAX_BODY] = {0};
};

inline void put_u16(uint8_t* p, uint16_t v) { p[0] = v & 0xff; p[1] = v >> 8; }
inline void put_u32(uint8_t* p, uint32_t v) {
  p[0] = v & 0xff; p[1] = (v >> 8) & 0xff; p[2] = (v >> 16) & 0xff; p[3] = v >> 24;
}
inline uint16_t get_u16(const uint8_t* p) { return p[0] | (p[1] << 8); }
inline uint32_t get_u32(const uint8_t* p) {
  return (uint32_t)p[0] | ((uint32_t)p[1] << 8) | ((uint32_t)p[2] << 16) |
         ((uint32_t)p[3] << 24);
}

// Serialize `t` into `out` (>= MAX_FRAME) and append the truncated HMAC.
// Returns total frame length, or 0 on error.
size_t encode(const Toot& t, const uint8_t* key, size_t key_len, uint8_t* out,
              size_t out_cap);

// Parse + verify (magic, version, HMAC). Returns true on success.
bool decode(const uint8_t* in, size_t in_len, const uint8_t* key,
            size_t key_len, Toot& t);

// Small ring of seen (src,seq) keys. seen() returns true if already present,
// otherwise records the key and returns false.
class DedupSet {
 public:
  explicit DedupSet(size_t cap = 64) : cap_(cap), head_(0), filled_(0) {
    ring_ = new Entry[cap_];
  }
  ~DedupSet() { delete[] ring_; }
  bool seen(uint32_t src, uint32_t seq) {
    for (size_t i = 0; i < filled_; ++i)
      if (ring_[i].src == src && ring_[i].seq == seq) return true;
    ring_[head_].src = src;
    ring_[head_].seq = seq;
    head_ = (head_ + 1) % cap_;
    if (filled_ < cap_) ++filled_;
    return false;
  }

 private:
  struct Entry { uint32_t src = 0; uint32_t seq = 0; };
  Entry* ring_;
  size_t cap_, head_, filled_;
};

}  // namespace toot
