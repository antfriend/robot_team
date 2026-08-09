#include "Sid.h"

namespace sid {

const char kPlaceholder[] = "sid:00000000";
const char kFieldName[]   = "sid:";

static const char kHex[] = "0123456789abcdef";

uint32_t fnv1a(const void* data, size_t len, uint32_t h) {
  const uint8_t* p = (const uint8_t*)data;
  for (size_t i = 0; i < len; ++i) h = fnv1aByte(h, p[i]);
  return h;
}

// Fixed-width lowercase hex, most significant nibble first. Written by hand rather than
// with snprintf so the preimage is identical on an ESP32, on a laptop, and in Python —
// which is the only reason a reader can verify a node's ids at all.
static char* putHex(char* p, uint64_t v, uint8_t nibbles) {
  for (int8_t i = (int8_t)(nibbles - 1); i >= 0; --i)
    *p++ = kHex[(v >> (4 * (uint8_t)i)) & 0xF];
  return p;
}

uint32_t bodyDigest(const char* body, size_t len) {
  if (!body || !len) return 0;
  return fnv1a(body, len);
}

uint32_t forEvent(uint32_t node, int16_t lane, uint32_t stream, uint64_t t_ms,
                  uint32_t body_digest) {
  char pre[EVENT_PREIMAGE_LEN];
  char* p = pre;
  p = putHex(p, node, 8);                    *p++ = '|';
  p = putHex(p, (uint16_t)lane, 4);          *p++ = '|';
  p = putHex(p, stream, 8);                  *p++ = '|';
  p = putHex(p, t_ms, 16);                   *p++ = '|';
  p = putHex(p, body_digest, 8);
  return fnv1a(pre, (size_t)(p - pre));
}

uint32_t forKey(uint32_t node, int16_t lane, const char* key) {
  char head[8 + 1 + 4 + 1];
  char* p = head;
  p = putHex(p, node, 8);                    *p++ = '|';
  p = putHex(p, (uint16_t)lane, 4);          *p++ = '|';
  uint32_t h = fnv1a(head, (size_t)(p - head));
  // ⚠ Streamed rather than copied into a buffer: a natural key is caller-supplied and has
  // no bound, and a fixed staging buffer here would silently truncate one — which would
  // merge two subjects into one identity, the exact failure this file exists to prevent.
  if (key)
    for (const char* q = key; *q; ++q) h = fnv1aByte(h, (uint8_t)*q);
  return h;
}

void format(char out[9], uint32_t s) {
  char* p = putHex(out, s, 8);
  *p = '\0';
}

bool parse(const char* p, size_t len, uint32_t& out) {
  if (!p || len < 8) return false;
  uint32_t v = 0;
  for (size_t i = 0; i < 8; ++i) {
    const char c = p[i];
    uint8_t d;
    if (c >= '0' && c <= '9')      d = (uint8_t)(c - '0');
    else if (c >= 'a' && c <= 'f') d = (uint8_t)(c - 'a' + 10);
    // ⚠ Uppercase is REFUSED, not accepted-and-normalised. The sid is a hash of a canonical
    // preimage; tolerating a second spelling on input would mean two files could disagree
    // about a record's id while both "parsing fine".
    else return false;
    v = (v << 4) | d;
  }
  out = v;
  return true;
}

// Locate the record's header line: the line that begins with '@'. Returns the offset of the
// first body byte (just past that line's '\n').
//
// ⚠ RETURNS 0 — NOT `len` — WHEN THERE IS NO HEADER LINE, and the distinction is load-
// bearing. A first cut returned `len`, which made the *entire buffer* read as header, so a
// body-only buffer containing the text `sid:` got patched as though it were a header field.
// Zero is a safe sentinel because a real body offset is always >= 2 (a header line is at
// least one character plus its newline). Caught by the native test, not by inspection.
static size_t bodyOffset(const char* rec, size_t len) {
  size_t i = 0;
  while (i < len) {
    // start of a line
    if (rec[i] == '@') {
      while (i < len && rec[i] != '\n') ++i;
      return (i < len) ? i + 1 : 0;   // a header with no newline has no body either
    }
    while (i < len && rec[i] != '\n') ++i;
    if (i < len) ++i;
  }
  return 0;
}

// Find `sid:` inside the header line only. Returns the offset of the 8 hex digits, or 0 if
// absent. ⚠ Bounded to the header on purpose: a body may legitimately contain the text
// `sid:` (a boundary record quoting a pruned record's id is the obvious case), and patching
// that instead would corrupt provenance while looking like it worked.
static size_t sidDigitsOffset(const char* rec, size_t len, size_t body_at) {
  if (!body_at || body_at > len) return 0;   // no header line at all: nothing to patch
  const size_t hdr_end = body_at - 1;
  if (hdr_end < 4) return 0;
  for (size_t i = 0; i + 4 <= hdr_end; ++i) {
    if (rec[i] == 's' && rec[i + 1] == 'i' && rec[i + 2] == 'd' && rec[i + 3] == ':') {
      if (i + 4 + 8 > hdr_end) return 0;     // truncated placeholder: refuse, never patch
      return i + 4;
    }
  }
  return 0;
}

static uint32_t stampWith(char* rec, size_t len, uint32_t s) {
  const size_t body_at = bodyOffset(rec, len);
  const size_t at = sidDigitsOffset(rec, len, body_at);
  if (!at) return 0;
  char hex[9];
  format(hex, s);
  for (uint8_t i = 0; i < 8; ++i) rec[at + i] = hex[i];
  return s;
}

uint32_t stampEvent(char* rec, size_t len, uint32_t node, int16_t lane, uint32_t stream,
                    uint64_t t_ms) {
  if (!rec || !len) return 0;
  const size_t body_at = bodyOffset(rec, len);
  if (!sidDigitsOffset(rec, len, body_at)) return 0;   // check before we compute anything
  const uint32_t bd = bodyDigest(rec + body_at, len - body_at);
  return stampWith(rec, len, forEvent(node, lane, stream, t_ms, bd));
}

uint32_t stampKey(char* rec, size_t len, uint32_t node, int16_t lane, const char* key) {
  if (!rec || !len) return 0;
  return stampWith(rec, len, forKey(node, lane, key));
}

bool verifyEvent(const char* rec, size_t len, uint32_t node, int16_t lane, uint32_t stream,
                 uint64_t t_ms, uint32_t* found, uint32_t* computed) {
  if (!rec || !len) return false;
  const size_t body_at = bodyOffset(rec, len);
  const size_t at = sidDigitsOffset(rec, len, body_at);
  if (!at) return false;
  uint32_t got = 0;
  if (!parse(rec + at, len - at, got)) return false;
  const uint32_t want = forEvent(node, lane, stream, t_ms,
                                 bodyDigest(rec + body_at, len - body_at));
  if (found)    *found = got;
  if (computed) *computed = want;
  return got == want;
}

}  // namespace sid
