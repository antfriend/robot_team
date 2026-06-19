// TtdbShare.h — serve a node's TTDB to the companion over any toot transport.
//
// This is the piece that satisfies "the physical robots can share any or all of
// their TTDB with the orchestrating companion over the network." Given a
// TTDB_REQ toot (whole file, or a byte range), it streams the requested bytes
// back as a sequence of offset-addressed, HMAC-signed TTDB_DATA toots, ending
// with a zero-length TTDB_DATA as the EOF marker.
//
// TTDB_DATA payload: u32 file_offset | u16 len | len bytes  (len <= 202).
// Offset-addressing (rather than chunk_idx/total) means the stream survives
// arbitrarily large files, loss, and retries: the companion just writes each
// slice at its offset.
#pragma once
#include <stdint.h>
#include <stddef.h>
#include "TTDB.h"
#include "Toot.h"

class TtdbShare {
 public:
  // send(): hand a complete toot frame to a transport (ESP-NOW, serial, LoRa).
  // Returns true if accepted. ctx is passed straight through.
  using SendFn = bool (*)(const uint8_t* frame, size_t len, void* ctx);

  TtdbShare(Ttdb& db, const uint8_t* key, size_t key_len, uint32_t node_id,
            const uint8_t locus[toot::LOCUS_LEN])
      : db_(db), key_(key), key_len_(key_len), node_id_(node_id) {
    for (size_t i = 0; i < toot::LOCUS_LEN; ++i) locus_[i] = locus[i];
  }

  // Handle a decoded TTDB_REQ. Streams the requested range and the EOF marker.
  // Returns the number of TTDB_DATA toots sent.
  int handleRequest(const toot::Toot& req, SendFn send, void* ctx);

  // The node a TTDB_REQ is addressed to (payload bytes 1..4). A sketch serves
  // the request only when this equals its own node id.
  static uint32_t requestTarget(const toot::Toot& req) {
    return req.payload_len >= 5 ? toot::get_u32(req.payload + 1) : 0;
  }

 private:
  void sendSlice(uint32_t offset, const uint8_t* data, uint16_t n, SendFn send,
                 void* ctx);

  Ttdb& db_;
  const uint8_t* key_;
  size_t key_len_;
  uint32_t node_id_;
  uint8_t locus_[toot::LOCUS_LEN];
  uint32_t seq_ = 1;
};
