// FleetTime.cpp — see FleetTime.h. Portable; pinned by tests/test_fleettime.cpp.
#include "FleetTime.h"

#include <stdio.h>
#include <string.h>

namespace semantic {

// ---------------------------------------------------------------------------------------
// stamps
// ---------------------------------------------------------------------------------------
uint32_t boundMs(uint32_t ms_since_beacon, uint32_t drift_ppm, uint32_t delivery_ms) {
  // drift = ms × ppm / 1e6, rounded UP: a bound that is a hair too small claims an order
  // the clocks cannot support, and one a hair too large only claims less.
  const uint64_t num = (uint64_t)ms_since_beacon * drift_ppm;
  const uint64_t drift = (num + 999999u) / 1000000u;
  const uint64_t b = drift + delivery_ms;
  return b > 0xFFFFFFFFu ? 0xFFFFFFFFu : (uint32_t)b;
}

At stampNow(int64_t pulse_now_ms, uint32_t ms_since_beacon, bool have_beacon,
            bool conductor, uint64_t frame) {
  At a;
  a.t_ms = pulse_now_ms;
  a.frame = frame;
  a.has_frame = true;
  if (conductor) {
    a.bound_ms = 0;          // it IS the reference; nothing was delivered to it
    a.bounded = true;
  } else if (have_beacon) {
    a.bound_ms = boundMs(ms_since_beacon);
    a.bounded = true;
  } else {
    a.bound_ms = 0;
    a.bounded = false;
    a.frame = 0;
    a.has_frame = false;     // no chart, so no frame to name
  }
  return a;
}

bool sameFrame(const At& a, const At& b) {
  return a.has_frame && b.has_frame && a.frame == b.frame;
}

size_t renderAt(const At& a, char* out, size_t cap) {
  int n;
  if (a.bounded && a.has_frame)
    n = snprintf(out, cap, "%lld \xC2\xB1%lu frame:%llu", (long long)a.t_ms,
                 (unsigned long)a.bound_ms, (unsigned long long)a.frame);
  else if (a.bounded)
    n = snprintf(out, cap, "%lld \xC2\xB1%lu", (long long)a.t_ms, (unsigned long)a.bound_ms);
  else
    n = snprintf(out, cap, "%lld", (long long)a.t_ms);
  if (n < 0 || (size_t)n >= cap) { if (cap) out[0] = '\0'; return 0; }
  return (size_t)n;
}

static const char* skipWs(const char* s) {
  while (*s == ' ' || *s == '\t') ++s;
  return s;
}

// Signed decimal; advances *p. false if no digits.
static bool readInt(const char** p, int64_t* out) {
  const char* s = *p;
  bool neg = false;
  if (*s == '-') { neg = true; ++s; }
  if (*s < '0' || *s > '9') return false;
  int64_t v = 0;
  while (*s >= '0' && *s <= '9') { v = v * 10 + (*s - '0'); ++s; }
  *out = neg ? -v : v;
  *p = s;
  return true;
}

At parseAt(const char* s) {
  At a;
  a.t_ms = 0; a.bound_ms = 0; a.bounded = false; a.frame = 0; a.has_frame = false;
  if (!s) return a;
  s = skipWs(s);
  if (strncmp(s, "at:", 3) == 0) s = skipWs(s + 3);

  const char* p = s;
  int64_t t;
  if (readInt(&p, &t)) {
    a.t_ms = t;
    const char* q = skipWs(p);
    if ((unsigned char)q[0] == 0xC2 && (unsigned char)q[1] == 0xB1) {
      q += 2;
      int64_t b;
      if (readInt(&q, &b) && b >= 0 && b <= 0xFFFFFFFFLL) {
        const char* r = skipWs(q);
        // Optional ` frame:<u64>`. A malformed frame makes the WHOLE stamp unbounded, not
        // merely frameless: a half-read stamp is one we are not sure we read.
        bool ok = true;
        uint64_t fr = 0;
        bool hf = false;
        if (strncmp(r, "frame:", 6) == 0) {
          const char* f = r + 6;
          if (*f < '0' || *f > '9') ok = false;
          while (ok && *f >= '0' && *f <= '9') { fr = fr * 10 + (uint64_t)(*f - '0'); ++f; }
          hf = ok;
          r = skipWs(f);
        }
        if (ok && (*r == '\0' || *r == '\r' || *r == '\n')) {
          a.bound_ms = (uint32_t)b;
          a.bounded = true;
          a.frame = fr;
          a.has_frame = hf;
        }
      }
    }
    return a;
  }
  // Pre-C4 form: `t_ms:<n> stream:0x… wall:…` — keep the number for the owner's own
  // reference, but it is UNBOUNDED: it orders nothing across agents and joins no bar.
  const char* tm = strstr(s, "t_ms:");
  if (tm) {
    const char* q = tm + 5;
    int64_t v;
    if (readInt(&q, &v)) a.t_ms = v;
  }
  return a;
}

// ---------------------------------------------------------------------------------------
// order
// ---------------------------------------------------------------------------------------
// Does `later` say it was written already knowing `earlier`?
// ⚠ seq 0 is UNSEQUENCED (every episode written before per-agent seq): no edge reaches it,
// because `follows.seq >= 0` would otherwise make it known by anyone naming its agent.
static bool knows(const EpisodeRef& later, const EpisodeRef& earlier) {
  if (earlier.seq == 0) return false;
  for (uint8_t i = 0; i < later.n_follows && i < FLEETTIME_MAX_AGENTS; ++i)
    if (later.follows[i].agent == earlier.agent && later.follows[i].seq >= earlier.seq)
      return true;
  return false;
}

// Strictly-before by stamps alone: both bounded and the ranges do not overlap.
// Strictly-before by stamps alone: both bounded, in the SAME frame, and the ranges do not
// overlap. Stamps from different lineages are numbers on different clocks.
static bool stampBefore(const At& a, const At& b) {
  if (!a.bounded || !b.bounded || !sameFrame(a, b)) return false;
  return a.t_ms + (int64_t)a.bound_ms < b.t_ms - (int64_t)b.bound_ms;
}

Order order(const EpisodeRef& a, const EpisodeRef& b, bool* contradiction) {
  if (contradiction) *contradiction = false;
  if (a.agent == b.agent && a.seq != 0 && b.seq != 0) {
    if (a.seq == b.seq) return SAME;
    return a.seq < b.seq ? BEFORE : AFTER;       // §4.4 (1): the agent's own order
  }
  const bool a_then_b = knows(b, a);             // §4.4 (2): b was said knowing a
  const bool b_then_a = knows(a, b);
  if (a_then_b && !b_then_a) {
    if (contradiction && stampBefore(b.at, a.at)) *contradiction = true;
    return BEFORE;
  }
  if (b_then_a && !a_then_b) {
    if (contradiction && stampBefore(a.at, b.at)) *contradiction = true;
    return AFTER;
  }
  // Mutual knowledge is impossible between distinct episodes unless a store was edited;
  // fall through to the clocks rather than claim either.
  if (stampBefore(a.at, b.at)) return BEFORE;    // §4.4 (3)
  if (stampBefore(b.at, a.at)) return AFTER;
  return CONCURRENT;
}

size_t maximal(const EpisodeRef* c, size_t n, size_t* out, size_t max) {
  size_t k = 0;
  for (size_t i = 0; i < n; ++i) {
    bool dominated = false;
    for (size_t j = 0; j < n && !dominated; ++j)
      if (j != i && order(c[i], c[j]) == BEFORE) dominated = true;
    if (!dominated && k < max) out[k++] = i;
  }
  return k;
}

// ---------------------------------------------------------------------------------------
// the bar
// ---------------------------------------------------------------------------------------
int64_t barLine(int64_t downbeat_ms, uint32_t bar_ms, uint32_t n) {
  return downbeat_ms + (int64_t)bar_ms * (int64_t)n;
}

bool inBar(const At& a, int64_t line, uint64_t frame) {
  return a.bounded && a.has_frame && a.frame == frame &&
         a.t_ms + (int64_t)a.bound_ms < line;
}

}  // namespace semantic
