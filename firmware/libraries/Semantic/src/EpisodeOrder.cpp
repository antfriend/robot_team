// EpisodeOrder.cpp — see EpisodeOrder.h.
#include "EpisodeOrder.h"

#include <stdio.h>
#include <string.h>

namespace semantic {

static void putU32(uint8_t* p, uint32_t v) {
  p[0] = (uint8_t)v; p[1] = (uint8_t)(v >> 8); p[2] = (uint8_t)(v >> 16); p[3] = (uint8_t)(v >> 24);
}
static uint32_t getU32(const uint8_t* p) {
  return (uint32_t)p[0] | ((uint32_t)p[1] << 8) | ((uint32_t)p[2] << 16) | ((uint32_t)p[3] << 24);
}

void VectorClock::begin(uint32_t self) {
  self_ = self;
  seq_ = 0;
  n_ = 0;
  regressions_ = overflow_ = malformed_ = 0;
  dirty_ = false;
  ever_sent_ = false;
  last_sent_ms_ = 0;
}

void VectorClock::committed(uint32_t s) {
  if (s > seq_) {
    seq_ = s;
    dirty_ = true;
  }
}

void VectorClock::restore(uint32_t s, const Follows* f, uint8_t n) {
  if (s > seq_) seq_ = s;            // our own number: not a regression, it is our flash
  for (uint8_t i = 0; i < n && f; ++i) mergeEntry(f[i].agent, f[i].seq);
  dirty_ = true;                     // announce what we recovered
}

bool VectorClock::mergeEntry(uint32_t agent, uint32_t s) {
  if (s == 0) return false;          // "never heard": not knowledge
  if (agent == self_) {
    if (s <= seq_) return false;
    seq_ = s;                        // the fleet remembers more of us than our flash does
    ++regressions_;
    dirty_ = true;
    return true;
  }
  uint8_t i = 0;
  while (i < n_ && e_[i].agent < agent) ++i;
  if (i < n_ && e_[i].agent == agent) {
    if (s <= e_[i].seq) return false;
    e_[i].seq = s;
    dirty_ = true;
    return true;
  }
  if (n_ >= EPISODEORDER_OTHERS) {   // full: drop the newcomer — an under-claim, never wrong
    ++overflow_;
    return false;
  }
  memmove(&e_[i + 1], &e_[i], (size_t)(n_ - i) * sizeof(Follows));
  e_[i] = Follows{agent, s};
  ++n_;
  dirty_ = true;
  return true;
}

bool VectorClock::mergeWire(const uint8_t* p, size_t len) {
  if (!p || len < EPISODEORDER_VECTOR_HDR || p[0] != EPISODEORDER_SUBOP_VECTOR ||
      p[1] > FLEETTIME_MAX_AGENTS ||
      len < EPISODEORDER_VECTOR_HDR + (size_t)p[1] * EPISODEORDER_VECTOR_ENTRY) {
    ++malformed_;
    return false;
  }
  const uint8_t n = p[1];
  for (uint8_t i = 0; i < n; ++i) {
    const uint8_t* q = p + EPISODEORDER_VECTOR_HDR + (size_t)i * EPISODEORDER_VECTOR_ENTRY;
    mergeEntry(getU32(q), getU32(q + 4));
  }
  return true;
}

size_t VectorClock::encode(uint8_t* p, size_t cap) const {
  const uint8_t n = (uint8_t)(n_ + (seq_ ? 1 : 0));
  const size_t body = EPISODEORDER_VECTOR_HDR + (size_t)n * EPISODEORDER_VECTOR_ENTRY;
  const size_t need = body + (grammar_ ? EPISODEORDER_VECTOR_GRAMMAR : 0);
  if (!p || cap < need) return 0;
  p[0] = EPISODEORDER_SUBOP_VECTOR;
  p[1] = n;
  uint8_t* q = p + EPISODEORDER_VECTOR_HDR;
  if (seq_) { putU32(q, self_); putU32(q + 4, seq_); q += EPISODEORDER_VECTOR_ENTRY; }
  for (uint8_t i = 0; i < n_; ++i, q += EPISODEORDER_VECTOR_ENTRY) {
    putU32(q, e_[i].agent);
    putU32(q + 4, e_[i].seq);
  }
  if (grammar_) putU32(p + body, grammar_);
  return need;
}

bool vectorGrammar(const uint8_t* p, size_t len, uint32_t* g) {
  if (!p || len < EPISODEORDER_VECTOR_HDR || p[0] != EPISODEORDER_SUBOP_VECTOR ||
      p[1] > FLEETTIME_MAX_AGENTS)
    return false;
  const size_t body = EPISODEORDER_VECTOR_HDR + (size_t)p[1] * EPISODEORDER_VECTOR_ENTRY;
  if (len < body + EPISODEORDER_VECTOR_GRAMMAR) return false;
  const uint32_t v = getU32(p + body);
  if (!v) return false;
  if (g) *g = v;
  return true;
}

uint8_t VectorClock::follows(Follows* out, uint8_t max) const {
  uint8_t k = 0;
  for (uint8_t i = 0; i < n_ && k < max; ++i) out[k++] = e_[i];
  return k;
}

size_t VectorClock::renderBlock(char* out, size_t cap) const {
  if (!out || cap == 0) return 0;
  size_t len = 0;
  int w = snprintf(out, cap, "seq: %lu\n", (unsigned long)nextSeq());
  if (w < 0 || (size_t)w >= cap) { out[0] = '\0'; return 0; }
  len = (size_t)w;
  if (n_ == 0) return len;
  w = snprintf(out + len, cap - len, "follows:");
  if (w < 0 || (size_t)w >= cap - len) { out[0] = '\0'; return 0; }
  len += (size_t)w;
  for (uint8_t i = 0; i < n_; ++i) {
    w = snprintf(out + len, cap - len, " 0x%08lx:%lu", (unsigned long)e_[i].agent,
                 (unsigned long)e_[i].seq);
    if (w < 0 || (size_t)w >= cap - len) { out[0] = '\0'; return 0; }
    len += (size_t)w;
  }
  if (len + 2 > cap) { out[0] = '\0'; return 0; }
  out[len++] = '\n';
  out[len] = '\0';
  return len;
}

bool VectorClock::sendDue(uint32_t now_ms) const {
  if (!ever_sent_) return seq_ != 0 || n_ != 0;
  const uint32_t since = now_ms - last_sent_ms_;
  if (since >= EPISODEORDER_HEARTBEAT_MS) return true;
  return dirty_ && since >= EPISODEORDER_MIN_GAP_MS;
}

void VectorClock::sent(uint32_t now_ms) {
  last_sent_ms_ = now_ms;
  ever_sent_ = true;
  dirty_ = false;
}

// ---------------------------------------------------------------------------------------
// inbox
// ---------------------------------------------------------------------------------------
bool VectorInbox::push(const uint8_t* p, size_t len) {
  const uint8_t next = (uint8_t)((head_ + 1) % EPISODEORDER_INBOX);
  if (!p || len == 0 || len > EPISODEORDER_VECTOR_MAX || next == tail_) {
    ++dropped_;
    return false;
  }
  memcpy(buf_[head_], p, len);
  len_[head_] = (uint8_t)len;
  head_ = next;                      // publish last: the reader never sees a half copy
  return true;
}

uint8_t VectorInbox::drainInto(VectorClock& vc) {
  uint8_t merged = 0;
  while (tail_ != head_) {
    if (vc.mergeWire(buf_[tail_], len_[tail_])) ++merged;
    tail_ = (uint8_t)((tail_ + 1) % EPISODEORDER_INBOX);
  }
  return merged;
}

// ---------------------------------------------------------------------------------------
// parsing
// ---------------------------------------------------------------------------------------
static bool readU32(const char** pp, uint32_t* out, int base) {
  const char* p = *pp;
  uint64_t v = 0;
  int digits = 0;
  for (;; ++p, ++digits) {
    int d;
    if (*p >= '0' && *p <= '9') d = *p - '0';
    else if (base == 16 && *p >= 'a' && *p <= 'f') d = *p - 'a' + 10;
    else if (base == 16 && *p >= 'A' && *p <= 'F') d = *p - 'A' + 10;
    else break;
    v = v * (uint64_t)base + (uint64_t)d;
    if (v > 0xFFFFFFFFull) return false;
  }
  if (!digits) return false;
  *out = (uint32_t)v;
  *pp = p;
  return true;
}

static bool lineEnd(const char* p) {
  while (*p == ' ' || *p == '\t' || *p == '\r') ++p;
  return *p == '\0' || *p == '\n';
}

bool parseSeqLine(const char* line, uint32_t* seq) {
  if (!line || strncmp(line, "seq: ", 5) != 0) return false;
  const char* p = line + 5;
  uint32_t v;
  if (!readU32(&p, &v, 10) || !lineEnd(p) || v == 0) return false;
  if (seq) *seq = v;
  return true;
}

uint8_t parseFollowsLine(const char* line, Follows* out, uint8_t max, bool* ok) {
  if (ok) *ok = false;
  if (!line || strncmp(line, "follows:", 8) != 0) return 0;
  const char* p = line + 8;
  uint8_t k = 0;
  for (;;) {
    while (*p == ' ') ++p;
    if (lineEnd(p)) break;
    uint32_t a, s;
    if (p[0] != '0' || (p[1] != 'x' && p[1] != 'X')) return k;
    p += 2;
    if (!readU32(&p, &a, 16) || *p != ':') return k;
    ++p;
    if (!readU32(&p, &s, 10) || (*p != ' ' && !lineEnd(p))) return k;
    if (k < max && out) out[k++] = Follows{a, s};
  }
  if (ok) *ok = true;
  return k;
}

// ---------------------------------------------------------------------------------------
// boot recovery
// ---------------------------------------------------------------------------------------
void OrderRecovery::line(const char* l) {
  if (!l) return;
  if (l[0] == '@') {                 // a record header: the next lines are another episode
    cur_seq_ = 0;
    capture_ = false;
    return;
  }
  uint32_t s;
  if (parseSeqLine(l, &s)) {
    cur_seq_ = s;
    capture_ = s > best_seq_;
    if (capture_) { best_seq_ = s; nf_ = 0; }
    return;
  }
  if (capture_ && strncmp(l, "follows:", 8) == 0) {
    bool ok = false;
    const uint8_t n = parseFollowsLine(l, f_, EPISODEORDER_OTHERS, &ok);
    nf_ = ok ? n : 0;                // a malformed vector is not trusted at all
    capture_ = false;
  }
}

uint8_t OrderRecovery::follows(Follows* out, uint8_t max) const {
  uint8_t k = 0;
  for (; k < nf_ && k < max; ++k) out[k] = f_[k];
  return k;
}

void OrderRecovery::applyTo(VectorClock& vc) const {
  vc.restore(best_seq_, f_, nf_);
}

}  // namespace semantic
