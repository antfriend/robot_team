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
  TIME_SYNC = 9,  // companion -> fleet: set the wall clock (TTN-RFC-0008)
  TIME_REQ = 10,  // companion -> node: "report your epoch now" (skew probe)
  TIME_RESP = 11, // node -> companion: current epoch (ms)
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

// CMD payload layout — the orchestrator drives node behavior (companion.md §4b).
//   [0]     op (CmdOp)
//   [1..4]  target_node_id (u32 LE) — only the addressed node acts + ACKs
//   [5..]   op-specific args
// CMD is a payload convention over the existing CMD type (like TtdbReqMode over
// TTDB_REQ), so it needs no new toot type / RFC. Sent want_ack so the laptop
// gets delivery confirmation (TTN-RFC-0007).
enum CmdOp : uint8_t {
  CMD_PING = 0,          // no-op; accept + ACK (reliability smoke test)
  CMD_SET_LED = 1,       // args: R,G,B (3 bytes) — override the indicator LED
  CMD_CLEAR_LED = 2,     // no args — return the LED to local agent control
  CMD_GET_STATUS = 3,    // no args — node replies a STATUS PERCEPT (not want_ack)
  CMD_BEEP = 4,          // args: freq_hz u16 | dur_ms u16 (both LE; 0 args = default)
  CMD_SET_INTERVAL = 5,  // args: interval_ms u16 LE — agent sense/act cadence
};

// STATUS payload — a node's live telemetry, returned as a PERCEPT toot in answer to
// CMD_GET_STATUS (reused type, so the bridge already forwards it; no new type/RFC):
//   [0..1]  cursor_lat   i16 LE
//   [2..3]  cursor_lon   i16 LE
//   [4..5]  temp_c_x100  i16 LE   (last sensed ambient °C × 100; 0 if none)
//   [6]     flags        u8       bit0 warm · bit1 led_override · bit2 synced
//   [7..14] epoch_ms     u64 LE   (nowEpochMs(); 0 if unsynced)
const size_t STATUS_PAYLOAD_LEN = 15;
enum StatusFlag : uint8_t {
  STATUS_WARM = 1 << 0,
  STATUS_LED_OVERRIDE = 1 << 1,
  STATUS_SYNCED = 1 << 2,
};

// ACK payload layout (TTN-RFC-0007 §3). The header's src/seq belong to the
// acknowledging node, so the reference to the acked toot rides in the payload:
//   [0..3] ack_src   u32 LE — src_node_id of the toot being acknowledged
//   [4..7] ack_seq   u32 LE — toot_seq of the toot being acknowledged
//   [8]    ack_chunk u8     — chunk_idx acknowledged (0 if unchunked)
//   [9]    status    u8     — AckStatus
const size_t ACK_PAYLOAD_LEN = 10;
enum AckStatus : uint8_t {
  ACK_ACCEPTED = 0,            // toot accepted and processed
  ACK_REASSEMBLY_PENDING = 1,  // chunk stored, awaiting siblings
  ACK_DROPPED_NO_RESRC = 2,    // no reassembly slot / evicted
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
inline void put_u64(uint8_t* p, uint64_t v) {
  for (int i = 0; i < 8; ++i) p[i] = (uint8_t)(v >> (8 * i));
}
inline uint64_t get_u64(const uint8_t* p) {
  uint64_t v = 0;
  for (int i = 0; i < 8; ++i) v |= (uint64_t)p[i] << (8 * i);
  return v;
}

// CMD payload accessors (see CmdOp). cmdOp() is 0xFF (none) on a too-short body.
inline uint8_t cmdOp(const Toot& t) {
  return t.payload_len >= 1 ? t.payload[0] : 0xFF;
}
inline uint32_t cmdTarget(const Toot& t) {
  return t.payload_len >= 5 ? get_u32(t.payload + 1) : 0;
}

// Serialize `t` into `out` (>= MAX_FRAME) and append the truncated HMAC.
// Returns total frame length, or 0 on error.
size_t encode(const Toot& t, const uint8_t* key, size_t key_len, uint8_t* out,
              size_t out_cap);

// Parse + verify (magic, version, HMAC). Returns true on success.
bool decode(const uint8_t* in, size_t in_len, const uint8_t* key,
            size_t key_len, Toot& t);

// --- ACK helpers (TTN-RFC-0007) --------------------------------------------
// Build an ACK acknowledging `orig`, sent by node `acker_id` with its own
// sequence `acker_seq`. Fills type/src/seq/payload; encode() it like any toot.
void makeAck(const Toot& orig, uint32_t acker_id, uint32_t acker_seq,
             uint8_t status, Toot& out);

// Read an ACK's payload. False if `ack` is not type ACK or is too short.
bool parseAck(const Toot& ack, uint32_t& ack_src, uint32_t& ack_seq,
              uint8_t& ack_chunk, uint8_t& status);

// True if `ack` acknowledges the toot identified by (my_id, my_seq, my_chunk) —
// the match a want_ack sender applies against its outstanding table.
bool ackMatches(const Toot& ack, uint32_t my_id, uint32_t my_seq,
                uint8_t my_chunk);

// --- Time-sync payloads (TTN-RFC-0008) -------------------------------------
//   TIME_SYNC: sync_id u32 | epoch_ms u64        (companion -> fleet)
//   TIME_REQ:  probe_id u32 | target_node_id u32 (companion -> one node)
//   TIME_RESP: probe_id u32 | node_epoch_ms u64  (node -> companion)
const size_t TIME_SYNC_PAYLOAD_LEN = 12;
const size_t TIME_REQ_PAYLOAD_LEN = 8;
const size_t TIME_RESP_PAYLOAD_LEN = 12;

bool parseTimeSync(const Toot& t, uint32_t& sync_id, uint64_t& epoch_ms);
bool parseTimeReq(const Toot& t, uint32_t& probe_id, uint32_t& target);
bool parseTimeResp(const Toot& t, uint32_t& probe_id, uint64_t& node_epoch_ms);

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

#ifndef TOOT_REASSEMBLY_MAX_CHUNKS
#define TOOT_REASSEMBLY_MAX_CHUNKS 8   // cap: 8*208 = 1664 B per logical toot
#endif
#ifndef TOOT_REASSEMBLY_SLOTS
#define TOOT_REASSEMBLY_SLOTS 2        // concurrent (src,seq) sets (TTN-RFC-0007 §6)
#endif
#ifndef TOOT_REASSEMBLY_TTL_MS
#define TOOT_REASSEMBLY_TTL_MS 5000    // evict a stalled partial set
#endif

// Reassembles a logical toot split across chunk_idx/chunk_total that share one
// (src,seq) (TTN-RFC-0007 §6). Transport-agnostic and bounded for tight RAM. It
// owns its own per-chunk dedup (the global DedupSet keys on (src,seq) alone, which
// would wrongly collapse a chunked toot's siblings) plus a small recently-completed
// ring so a duplicate arriving after completion is re-ACKed rather than re-buffered.
class Reassembler {
 public:
  enum Result : uint8_t {
    NEED_MORE,      // chunk stored, awaiting siblings -> ACK REASSEMBLY_PENDING
    COMPLETE,       // this chunk completed the set; body()/bodyLen() valid -> ACCEPTED
    DUPLICATE,      // chunk already present in an open set -> re-ACK PENDING
    COMPLETED_DUP,  // (src,seq) completed earlier -> re-ACK ACCEPTED, no re-buffer
    NO_RESOURCE,    // no slot for a new key -> ACK DROPPED_NO_RESRC
    BAD,            // malformed (total<=1, total>max, idx>=total, total mismatch)
  };

  // Feed a decoded chunk toot. now_ms drives TTL eviction. On COMPLETE the
  // assembled body is at body()/bodyLen() until the next offer().
  Result offer(const Toot& t, uint32_t now_ms);
  const uint8_t* body() const { return out_; }
  size_t bodyLen() const { return out_len_; }

 private:
  struct Slot {
    bool used = false;
    uint32_t src = 0, seq = 0;
    uint8_t total = 0, got = 0;
    uint32_t last_ms = 0;
    bool have[TOOT_REASSEMBLY_MAX_CHUNKS];
    uint16_t len[TOOT_REASSEMBLY_MAX_CHUNKS];
    uint8_t buf[TOOT_REASSEMBLY_MAX_CHUNKS * MAX_BODY];
  };
  Slot* find(uint32_t src, uint32_t seq);
  Slot* allocate(uint32_t now_ms);
  bool recentlyCompleted(uint32_t src, uint32_t seq) const;
  void markCompleted(uint32_t src, uint32_t seq);

  static const size_t kCompletedCap = 16;
  Slot slots_[TOOT_REASSEMBLY_SLOTS];
  uint32_t comp_src_[kCompletedCap] = {0};
  uint32_t comp_seq_[kCompletedCap] = {0};
  bool comp_valid_[kCompletedCap] = {false};
  size_t comp_head_ = 0;
  uint8_t out_[TOOT_REASSEMBLY_MAX_CHUNKS * MAX_BODY];
  size_t out_len_ = 0;
};

}  // namespace toot
