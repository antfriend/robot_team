// TimeStream.cpp — the team time stream. See TimeStream.h for the design.
#include "TimeStream.h"
#include <stdio.h>
#include <string.h>

namespace timestream {

const char* eventName(uint8_t ev) {
  switch (ev) {
    case EV_ORIGIN: return "origin";
    case EV_ADOPTED: return "adopted";
    case EV_RECONCILED: return "reconciled";
    case EV_ANCHORED: return "anchored";
    case EV_SLEW: return "slew";
    default: return "none";
  }
}

// --- wire ------------------------------------------------------------------

static inline void put_u32(uint8_t* p, uint32_t v) {
  p[0] = (uint8_t)v; p[1] = (uint8_t)(v >> 8);
  p[2] = (uint8_t)(v >> 16); p[3] = (uint8_t)(v >> 24);
}
static inline uint32_t get_u32(const uint8_t* p) {
  return (uint32_t)p[0] | ((uint32_t)p[1] << 8) | ((uint32_t)p[2] << 16) |
         ((uint32_t)p[3] << 24);
}
static inline void put_u64(uint8_t* p, uint64_t v) {
  for (int i = 0; i < 8; ++i) p[i] = (uint8_t)(v >> (8 * i));
}
static inline uint64_t get_u64(const uint8_t* p) {
  uint64_t v = 0;
  for (int i = 0; i < 8; ++i) v |= (uint64_t)p[i] << (8 * i);
  return v;
}

size_t buildAnchor(uint8_t* p, size_t cap, const Anchor& a) {
  if (cap < ANCHOR_LEN) return 0;
  put_u32(p, a.stream_id);
  put_u64(p + 4, a.stream_ms);
  put_u64(p + 12, (uint64_t)a.wall_off_ms);
  p[20] = a.flags;
  return ANCHOR_LEN;
}

bool parseAnchor(const uint8_t* p, size_t len, Anchor& a) {
  if (len < ANCHOR_LEN) return false;
  a.stream_id = get_u32(p);
  a.stream_ms = get_u64(p + 4);
  a.wall_off_ms = (int64_t)get_u64(p + 12);
  a.flags = p[20];
  return true;
}

// --- engine ----------------------------------------------------------------

void Engine::begin(uint32_t node_id, uint32_t now_ms) {
  node_id_ = node_id;
  have_ = false;
  stream_id_ = 0;
  offset_ms_ = 0;
  wall_ = false;
  wall_off_ms_ = 0;
  wrap_ = 0;
  last_now_ = now_ms;
  out_aged_ = 0;
  last_ = Transition();
}

uint64_t Engine::mono(uint32_t now_ms) {
  // A step backwards of more than half the counter's span is a wrap; anything
  // smaller is two samples taken out of order, and we hold the high-water mark.
  if (now_ms < last_now_) {
    if ((uint32_t)(last_now_ - now_ms) > 0x80000000u) wrap_ += 0x100000000ull;
    else return wrap_ + last_now_;
  }
  last_now_ = now_ms;
  return wrap_ + now_ms;
}

// Mix (node_id, clock, entropy) into a stream id that is never 0 — 0 is the wire's
// "I have no stream". Finalizer from the MurmurHash3 avalanche, which is cheap,
// branch-free and spreads a low-entropy input across all 32 bits (boot times differ
// by only a few ms across a cold fleet, so the id must not be dominated by them).
static uint32_t mix32(uint32_t a, uint32_t b, uint32_t c) {
  uint32_t h = a * 0x9E3779B1u;
  h ^= b + 0x85EBCA6Bu + (h << 6) + (h >> 2);
  h ^= c + 0xC2B2AE35u + (h << 6) + (h >> 2);
  h ^= h >> 16; h *= 0x85EBCA6Bu;
  h ^= h >> 13; h *= 0xC2B2AE35u;
  h ^= h >> 16;
  return h ? h : 1u;
}

bool Engine::origin(uint32_t now_ms, uint32_t entropy) {
  if (have_) return false;
  uint64_t m = mono(now_ms);
  stream_id_ = mix32(node_id_, (uint32_t)m, entropy);
  offset_ms_ = -(int64_t)m;      // the stream reads 0 at its own origin
  have_ = true;
  wall_ = false;
  wall_off_ms_ = 0;

  last_ = Transition();
  last_.ev = EV_ORIGIN;
  last_.new_id = stream_id_;
  last_.new_ms = 0;
  last_.from_node = node_id_;
  return true;
}

void Engine::adopt(const Anchor& a, uint64_t m, uint32_t src, uint8_t ev) {
  const bool had = have_;
  const uint64_t prev_ms = had ? (uint64_t)((int64_t)m + offset_ms_) : 0;
  const uint32_t prev_id = had ? stream_id_ : 0;

  // Adopt via an OFFSET, never by assigning the number: everything else on this node
  // that reads the stream clock (a window still open, an armed expectation) keeps
  // running off the same monotonic base, so it moves with us instead of being
  // stranded on the old frame (TTN-RFC-0008's rule, and the handoff's §2.2.3).
  const int64_t delta = (int64_t)a.stream_ms - (int64_t)prev_ms;
  stream_id_ = a.stream_id;
  offset_ms_ = (int64_t)a.stream_ms - (int64_t)m;
  have_ = true;

  int64_t conflict = 0;
  if (a.flags & ANCHOR_WALL) {
    if (wall_ && had) {
      // Both sides know the date. Ours was expressed against the stream we are
      // leaving; re-express it against theirs and see whether we actually agree.
      const int64_t ours = (int64_t)wall_off_ms_ - delta;
      conflict = ours - a.wall_off_ms;
    }
    wall_off_ms_ = a.wall_off_ms;   // the older stream's anchor is the fleet's
    wall_ = true;
  } else if (wall_ && had) {
    // We know the date and they do not: carry the anchor across the merge so the
    // fleet does not lose its date by joining a longer-running but blind stream.
    wall_off_ms_ -= delta;
  }

  last_ = Transition();
  last_.ev = ev;
  last_.prev_id = prev_id;
  last_.prev_ms = prev_ms;
  last_.new_id = stream_id_;
  last_.new_ms = a.stream_ms;
  last_.offset_ms = had ? delta : 0;
  last_.from_node = src;
  last_.wall = wall_;
  last_.unix_ms = wall_ ? (uint64_t)((int64_t)a.stream_ms + wall_off_ms_) : 0;
  last_.wall_conflict_ms = conflict;
}

Event Engine::onAnchor(const Anchor& a, uint32_t src, uint32_t recv_ms) {
  if (a.stream_id == 0) return EV_NONE;    // the sender has no stream to offer
  const uint64_t m = mono(recv_ms);

  if (!have_) {                            // nothing of our own: join outright
    adopt(a, m, src, EV_ADOPTED);
    return EV_ADOPTED;
  }

  const uint64_t mine = (uint64_t)((int64_t)m + offset_ms_);
  const int64_t ahead = (int64_t)a.stream_ms - (int64_t)mine;

  if (a.stream_id != stream_id_) {
    // A FOREIGN stream. The older one wins, because it preserves more history — and
    // since a stream clock reads elapsed-since-origin, "older" is simply "ahead".
    // Note this can only ever move us FORWARD; see the header.
    if (ahead > 0 || (ahead == 0 && a.stream_id < stream_id_)) {
      adopt(a, m, src, EV_RECONCILED);
      return EV_RECONCILED;
    }
    // We out-age them. Say nothing; our own HELLO is 2 s away and will pull them in.
    // (The tie is broken on stream id so two streams of identical age still converge
    // instead of ignoring each other forever.)
    ++out_aged_;
    return EV_NONE;
  }

  // Our OWN stream. Same comparison, but a floor under it: correcting for a few ms
  // of transit on every frame is a ratchet, not a correction (see TIMESTREAM_SLEW_MS).
  if (ahead > TIMESTREAM_SLEW_MS) {
    offset_ms_ += ahead;
    last_ = Transition();
    last_.ev = EV_SLEW;
    last_.prev_id = last_.new_id = stream_id_;
    last_.prev_ms = mine;
    last_.new_ms = a.stream_ms;
    last_.offset_ms = ahead;
    last_.from_node = src;
    // The wall anchor is expressed against the stream, and the stream just moved, so
    // the anchor moves with it or the date shifts by the correction.
    if (wall_) wall_off_ms_ -= ahead;
  }

  // A peer on our stream may know the date when we do not — that is how a wall
  // anchor spreads from the one cabled node to the whole fleet, on the 2 s HELLO,
  // with no extra message.
  if ((a.flags & ANCHOR_WALL) && !wall_) {
    wall_off_ms_ = a.wall_off_ms;
    wall_ = true;
    const uint64_t now = (uint64_t)((int64_t)m + offset_ms_);
    last_ = Transition();
    last_.ev = EV_ANCHORED;
    last_.prev_id = last_.new_id = stream_id_;
    last_.prev_ms = last_.new_ms = now;
    last_.from_node = src;
    last_.wall = true;
    last_.unix_ms = (uint64_t)((int64_t)now + wall_off_ms_);
    return EV_ANCHORED;
  }

  return last_.ev == EV_SLEW ? EV_SLEW : EV_NONE;
}

Event Engine::anchorWall(uint64_t unix_ms, uint32_t now_ms, uint32_t from_node,
                         uint32_t entropy) {
  const bool started = origin(now_ms, entropy);   // no-op if we already have one
  const uint64_t m = mono(now_ms);
  const uint64_t s = (uint64_t)((int64_t)m + offset_ms_);

  int64_t conflict = 0;
  const int64_t off = (int64_t)unix_ms - (int64_t)s;
  if (wall_) conflict = wall_off_ms_ - off;
  wall_off_ms_ = off;
  wall_ = true;

  const uint8_t ev = started ? EV_ORIGIN : EV_ANCHORED;
  last_ = Transition();
  last_.ev = ev;
  last_.prev_id = last_.new_id = stream_id_;
  last_.prev_ms = last_.new_ms = s;
  last_.from_node = from_node;
  last_.wall = true;
  last_.unix_ms = unix_ms;
  last_.wall_conflict_ms = conflict;
  return (Event)ev;
}

bool Engine::fill(Anchor& out, uint32_t now_ms) {
  out = Anchor();
  if (!have_) return false;
  out.stream_id = stream_id_;
  out.stream_ms = nowMs(now_ms);
  out.wall_off_ms = wall_off_ms_;
  out.flags = wall_ ? ANCHOR_WALL : 0;
  return true;
}

uint64_t Engine::nowMs(uint32_t now_ms) {
  if (!have_) return 0;
  return (uint64_t)((int64_t)mono(now_ms) + offset_ms_);
}

uint64_t Engine::unixMs(uint32_t now_ms) {
  if (!have_ || !wall_) return 0;
  return (uint64_t)((int64_t)nowMs(now_ms) + wall_off_ms_);
}

uint32_t Engine::wallSec(uint32_t now_ms) {
  const uint64_t u = unixMs(now_ms);
  return u ? (uint32_t)(u / 1000) : 0;
}

// --- the per-record stamp --------------------------------------------------

size_t buildStamp(char* out, size_t cap, const Stamp& s) {
  int m = snprintf(out, cap, "t_ms:%llu stream:0x%08lx wall:%d",
                   (unsigned long long)s.t_ms, (unsigned long)s.stream_id,
                   s.wall ? 1 : 0);
  if (m < 0 || (size_t)m >= cap) return 0;
  return (size_t)m;
}

// --- is this record worth writing? (the @LAT90 dedup) ----------------------

// Bounded substring search: the record body arrives straight from Ttdb::readBytes and
// is not NUL-terminated, so strstr() would run off the end of the buffer.
static const char* findIn(const char* hay, size_t n, const char* needle) {
  const size_t m = strlen(needle);
  if (m == 0 || n < m) return 0;
  for (size_t i = 0; i + m <= n; ++i)
    if (memcmp(hay + i, needle, m) == 0) return hay + i;
  return 0;
}

bool recordNamesStream(const char* text, size_t len, uint32_t id) {
  char needle[32];
  // The leading space is what keeps this from matching `prev_stream:0x...` — see the
  // header. buildStreamRecord emits lowercase hex (%08lx), so the needle must too.
  int m = snprintf(needle, sizeof(needle), " stream:0x%08lx", (unsigned long)id);
  if (m < 0 || (size_t)m >= sizeof(needle)) return false;
  return findIn(text, len, needle) != 0;
}

bool recordIsWallAnchored(const char* text, size_t len) {
  return findIn(text, len, " wall:1") != 0;
}

bool recordStreamId(const char* text, size_t len, uint32_t& out) {
  // Same needle discipline as recordNamesStream, for the same reason: the leading
  // space is what keeps `prev_stream:0x<old>` on a REMAP line — the stream the node
  // LEFT — from being read back as one it was on.
  const char* p = findIn(text, len, " stream:0x");
  if (!p) return false;
  p += 10;                                  // past " stream:0x"
  const char* end = text + len;
  uint32_t v = 0;
  int digits = 0;
  for (; p < end && digits < 8; ++p, ++digits) {
    const char c = *p;
    uint32_t d;
    if (c >= '0' && c <= '9') d = (uint32_t)(c - '0');
    else if (c >= 'a' && c <= 'f') d = (uint32_t)(c - 'a' + 10);
    else if (c >= 'A' && c <= 'F') d = (uint32_t)(c - 'A' + 10);
    else break;
    v = (v << 4) | d;
  }
  if (!digits) return false;
  out = v;
  return true;
}

bool recordIsRedundant(const Transition& tr, bool named, bool anchored) {
  if (tr.ev == EV_ADOPTED) return named;
  if (tr.ev == EV_ANCHORED) return anchored && tr.wall_conflict_ms == 0;
  return false;   // ORIGIN cannot match; RECONCILED's REMAP is always news
}

bool originDue(uint32_t held_ms, uint32_t now_ms, int held_records, int records_now) {
  // The TTDB grew: something is on flash stamped with this stream, so it is owed an
  // explanation now, however young it is. Checked FIRST because it is the condition
  // the settle window cannot cover.
  if (records_now > held_records) return true;
  // Unsigned subtraction so a millis() wrap does not make the record wait 49 days.
  return (uint32_t)(now_ms - held_ms) >= TIMESTREAM_ORIGIN_SETTLE_MS;
}

// --- the @LAT90 record -----------------------------------------------------

size_t buildStreamRecord(char* out, size_t cap, int lane_n, const Transition& tr,
                         uint32_t node_id, uint32_t t_sec) {
  if (tr.ev == EV_NONE || tr.ev == EV_SLEW) return 0;

  const char* verb = "STREAM-ORIGIN";
  if (tr.ev == EV_ADOPTED) verb = "STREAM-ADOPTED";
  else if (tr.ev == EV_RECONCILED) verb = "STREAM-RECONCILED";
  else if (tr.ev == EV_ANCHORED) verb = "STREAM-ANCHORED";

  size_t w = 0;
  int m = snprintf(out, cap,
                   "\n---\n\n@LAT%dLON%d | created:%lu | updated:%lu | "
                   "relates:describes@LAT0LON0\n\n"
                   "**%s** stream:0x%08lx wall:%d t_ms:%llu node:0x%lx from:0x%lx\n",
                   TIMESTREAM_LANE, lane_n, (unsigned long)t_sec,
                   (unsigned long)t_sec, verb, (unsigned long)tr.new_id,
                   tr.wall ? 1 : 0, (unsigned long long)tr.new_ms,
                   (unsigned long)node_id, (unsigned long)tr.from_node);
  if (m < 0 || (size_t)m >= cap) return 0;
  w = (size_t)m;

  // The mapping that keeps records written under the abandoned stream readable. This
  // is the whole reason a merge writes anything at all: without it, every record
  // stamped `stream:<loser>` is orphaned in a timeline that no longer exists.
  if (tr.prev_id && tr.prev_id != tr.new_id) {
    m = snprintf(out + w, cap - w,
                 "**REMAP** prev_stream:0x%08lx prev_t_ms:%llu offset_ms:%lld "
                 "rule:older_stream_wins\n",
                 (unsigned long)tr.prev_id, (unsigned long long)tr.prev_ms,
                 (long long)tr.offset_ms);
    if (m < 0 || (size_t)m >= cap - w) return 0;
    w += (size_t)m;
  }

  if (tr.wall) {
    m = snprintf(out + w, cap - w,
                 "**WALL** unix_ms:%llu wall_conflict_ms:%lld\n",
                 (unsigned long long)tr.unix_ms, (long long)tr.wall_conflict_ms);
    if (m < 0 || (size_t)m >= cap - w) return 0;
    w += (size_t)m;
  }

  m = snprintf(out + w, cap - w,
               "**PROVENANCE** rule:TimeStream/older_stream_wins src:TTN-RFC-0008 "
               "basis:elapsed_since_stream_origin event:%s\n",
               eventName(tr.ev));
  if (m < 0 || (size_t)m >= cap - w) return 0;
  return w + (size_t)m;
}

}  // namespace timestream
