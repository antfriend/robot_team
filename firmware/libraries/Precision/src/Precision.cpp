// Precision.cpp — see Precision.h and docs/design/rfc0011-stage3.md §3-§4.
//
// Every matcher below is a literal translation of a regex in tools/pw1/pw1_fold.py's
// parse_record(), named beside it. `\b` before a key means "the previous character is not
// [A-Za-z0-9_]" — which is what keeps `first_t_ms:` and `prev_stream:` from matching.
#include "Precision.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Sid.h"
#include "TtdbParse.h"

namespace precision {

const char* chanName(uint8_t c) {
  switch (c) {
    case CH_LINK: return "link";
    case CH_ENTITY: return "entity";
    case CH_MOTION: return "motion";
    case CH_ACOUSTIC: return "acoustic";
    default: return "?";
  }
}

int32_t spanOf(uint8_t c) {
  switch (c) {
    case CH_LINK: return PRECISION_SPAN_LINK;
    case CH_MOTION: return PRECISION_SPAN_MOTION;
    case CH_ACOUSTIC: return PRECISION_SPAN_ACOUSTIC;
    default: return 0;
  }
}

int chanOfLon(int32_t lon) {
  if (lon < 0 || lon >= PRECISION_TIER_SPAN * CH_COUNT) return -1;
  return (int)(lon / PRECISION_TIER_SPAN);
}

const char* whyName(uint8_t w) {
  switch (w) {
    case OK: return "ok";
    case NO_T_MS: return "no t_ms";
    case NOT_WINDOW: return "not a window record";
    case NO_VALUE: return "no value";
    case OVERFLOW: return "overflow";
    default: return "?";
  }
}

// ---- arithmetic (pw1_fold.fold_var / pi_from_var / _pe) ------------------------------------
int32_t foldStep(int32_t var, int32_t r) { return var + (((r * r) - var) >> PRECISION_ALPHA); }

uint8_t piFromVar(int32_t var) {
  if (var < 0) var = 0;   // unreachable: the EWMA of squares never goes negative
  return (uint8_t)((255u * PRECISION_SCALE) / (PRECISION_SCALE + (uint32_t)var));
}

uint8_t confFromN(uint32_t n) {
  // floor(log2(1+n)) = bit length of (1+n) minus 1. Design D4.
  uint64_t v = (uint64_t)n + 1;
  int lg = -1;
  while (v) { v >>= 1; ++lg; }
  const uint32_t c = 16u * (uint32_t)lg;
  return (uint8_t)(c > 240 ? 240 : c);
}

uint8_t pe(int32_t diff, int32_t span) {
  if (span <= 0) return 0;
  const int64_t a = diff < 0 ? -(int64_t)diff : (int64_t)diff;
  const int64_t v = a * 255 / span;
  return (uint8_t)(v > 255 ? 255 : v);
}

// ---- line scanning -------------------------------------------------------------------------
static bool isWord(char c) {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_';
}
static bool isDigit(char c) { return c >= '0' && c <= '9'; }
static bool isHex(char c) {
  return isDigit(c) || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F');
}
static bool isSpace(char c) { return c == ' ' || c == '\t' || c == '\r' || c == '\f' || c == '\v'; }

// One line, with its `said: <digits> | ` prefix removed (gate: re.sub(r'(?m)^said: \d+ \| ')).
struct Line {
  const char* p;
  const char* e;
};
static const char* stripSaid(const char* p, const char* e) {
  static const char kSaid[] = "said: ";
  const size_t n = sizeof(kSaid) - 1;
  if ((size_t)(e - p) < n || memcmp(p, kSaid, n) != 0) return p;
  const char* q = p + n;
  if (q >= e || !isDigit(*q)) return p;
  while (q < e && isDigit(*q)) ++q;
  if (e - q < 3 || q[0] != ' ' || q[1] != '|' || q[2] != ' ') return p;
  return q + 3;
}

static const char* findIn(const char* p, const char* e, const char* needle) {
  const size_t n = strlen(needle);
  for (; p + n <= e; ++p)
    if (memcmp(p, needle, n) == 0) return p;
  return nullptr;
}

// First `\b<key>` in [p,e) — `key` includes its ':' — whose value parses with `parse`.
// `line_start` is the char just before which a \b holds trivially (the line's own start).
typedef bool (*ValueFn)(const char* v, const char* e, void* out);
static bool firstKey(const char* p, const char* e, const char* line_start, const char* key,
                     ValueFn parse, void* out) {
  const size_t n = strlen(key);
  for (const char* q = p; q + n <= e; ++q) {
    if (memcmp(q, key, n) != 0) continue;
    if (q > line_start && isWord(q[-1])) continue;
    if (parse(q + n, e, out)) return true;
  }
  return false;
}

static bool valU64(const char* v, const char* e, void* out) {   // (\d+)
  if (v >= e || !isDigit(*v)) return false;
  uint64_t x = 0;
  for (; v < e && isDigit(*v); ++v) x = x * 10 + (uint64_t)(*v - '0');
  *(uint64_t*)out = x;
  return true;
}
static bool valI32(const char* v, const char* e, void* out) {   // (-?\d+)
  bool neg = false;
  if (v < e && *v == '-') { neg = true; ++v; }
  if (v >= e || !isDigit(*v)) return false;
  int64_t x = 0;
  for (; v < e && isDigit(*v); ++v) {
    x = x * 10 + (*v - '0');
    if (x > 2147483647LL) x = 2147483647LL;
  }
  *(int32_t*)out = (int32_t)(neg ? -x : x);
  return true;
}
static bool valHex(const char* v, const char* e, void* out) {   // 0x([0-9a-fA-F]+)
  if (v >= e || !isHex(*v)) return false;
  uint64_t x = 0;
  for (; v < e && isHex(*v); ++v) {
    const char c = *v;
    const uint64_t d = isDigit(c) ? (uint64_t)(c - '0')
                     : (c >= 'a') ? (uint64_t)(c - 'a' + 10) : (uint64_t)(c - 'A' + 10);
    x = (x << 4) | d;   // pw1 int(hex,16) is unbounded; ids here are <= 8 hex digits
  }
  *(uint64_t*)out = x;
  return true;
}

// `<tag>...\b<key>(-?\d+)` on the same line, first tag occurrence that succeeds.
static bool tagThenI32(const char* p, const char* e, const char* tag, const char* key,
                       int32_t& out) {
  const char* q = p;
  while ((q = findIn(q, e, tag)) != nullptr) {
    const char* after = q + strlen(tag);
    if (firstKey(after, e, p, key, valI32, &out)) return true;
    ++q;
  }
  return false;
}

static void copyTok(char* dst, size_t cap, const char* s, const char* e, bool& overflow) {
  const size_t n = (size_t)(e - s);
  if (n + 1 > cap) { overflow = true; dst[0] = 0; return; }
  memcpy(dst, s, n);
  dst[n] = 0;
}

void parseWindow(uint8_t chan, const char* text, size_t len, Window& w) {
  w = Window();
  const char* end = text + len;
  bool have_t = false, have_val = false, have_run = false, overflow = false;
  const char* win_tag = chan == CH_ACOUSTIC ? "**ACOUSTICWIN**"
                      : chan == CH_MOTION   ? "**MOTIONWIN**"
                      : chan == CH_ENTITY   ? "**ENTWIN**"
                                            : "**LINKWIN**";
  bool have_win = false;
  for (const char* ls = text; ls < end;) {
    const char* le = (const char*)memchr(ls, '\n', (size_t)(end - ls));
    if (!le) le = end;
    const char* p = stripSaid(ls, le);
    // parse_head: \bt_ms:(\d+), \bstream:0x([0-9a-fA-F]+) — first in the record
    if (!have_t) have_t = firstKey(p, le, p, "t_ms:", valU64, &w.t);
    if (!w.has_stream) w.has_stream = firstKey(p, le, p, "stream:0x", valHex, &w.stream);
    if (!have_win && findIn(p, le, win_tag)) have_win = true;
    // \*\*RUN\*\*[^\n]*?\bwindows_since_last:(\d+)
    if (!have_run) {
      const char* q = p;
      while ((q = findIn(q, le, "**RUN**")) != nullptr) {
        uint64_t r;
        if (firstKey(q + 7, le, p, "windows_since_last:", valU64, &r)) {
          w.run = r ? (uint32_t)(r > 0xFFFFFFFFull ? 0xFFFFFFFFu : r) : 1;   // `run if run else 1`
          have_run = true;
          break;
        }
        ++q;
      }
    }
    if (chan == CH_ACOUSTIC && !have_val)        // \*\*ACOUSTIC\*\*[^\n]*?\brms_mean:(-?\d+)
      have_val = tagThenI32(p, le, "**ACOUSTIC**", "rms_mean:", w.val);
    else if (chan == CH_MOTION && !have_val)     // \*\*MOTION\*\*[^\n]*?\bdev_mean_mg:(-?\d+)
      have_val = tagThenI32(p, le, "**MOTION**", "dev_mean_mg:", w.val);
    else if (chan == CH_ENTITY && (size_t)(le - p) >= 10 && memcmp(p, "**ENTITY**", 10) == 0) {
      // ^\*\*ENTITY\*\*[^\n]*?\bid:([0-9a-fA-F]+)  — a SET of strings, case kept
      for (const char* q = p + 10; q + 3 <= le; ++q) {
        if (memcmp(q, "id:", 3) != 0 || (q > p && isWord(q[-1]))) continue;
        const char* v = q + 3;
        const char* ve = v;
        while (ve < le && isHex(*ve)) ++ve;
        if (ve == v) continue;
        char id[PRECISION_ID_MAX + 1];
        copyTok(id, sizeof(id), v, ve, overflow);
        if (overflow) break;
        bool dup = false;
        for (uint8_t i = 0; i < w.n_ids; ++i) dup |= strcmp(w.ids[i], id) == 0;
        if (!dup) {
          if (w.n_ids >= PRECISION_MAX_IDS) { overflow = true; break; }
          memcpy(w.ids[w.n_ids++], id, sizeof(id));
        }
        break;   // findall: one match per line (the pattern is anchored at ^)
      }
    } else if (chan == CH_LINK && (size_t)(le - p) >= 8 && memcmp(p, "**LINK**", 8) == 0) {
      // ^\*\*LINK\*\*\s+peer:(\S+)\s+proto:(\S+)[^\n]*?\brssi_med:(-?\d+)
      const char* q = p + 8;
      if (q < le && isSpace(*q)) {
        while (q < le && isSpace(*q)) ++q;
        if ((size_t)(le - q) > 5 && memcmp(q, "peer:", 5) == 0) {
          const char* ps = q + 5;
          const char* pe_ = ps;
          while (pe_ < le && !isSpace(*pe_)) ++pe_;
          q = pe_;
          if (pe_ > ps && q < le && isSpace(*q)) {
            while (q < le && isSpace(*q)) ++q;
            if ((size_t)(le - q) > 6 && memcmp(q, "proto:", 6) == 0) {
              const char* rs = q + 6;
              const char* re = rs;
              while (re < le && !isSpace(*re)) ++re;
              int32_t med;
              if (re > rs && firstKey(re, le, p, "rssi_med:", valI32, &med)) {
                char peer[PRECISION_PEER_MAX + 1], proto[PRECISION_PROTO_MAX + 1];
                copyTok(peer, sizeof(peer), ps, pe_, overflow);
                copyTok(proto, sizeof(proto), rs, re, overflow);
                if (!overflow) {
                  int at = -1;   // dict: a repeated key keeps the LAST value
                  for (uint8_t i = 0; i < w.n_links; ++i)
                    if (!strcmp(w.links[i].peer, peer) && !strcmp(w.links[i].proto, proto)) at = i;
                  if (at < 0) {
                    if (w.n_links >= PRECISION_MAX_LINK_KEYS) overflow = true;
                    else at = w.n_links++;
                  }
                  if (at >= 0) {
                    memcpy(w.links[at].peer, peer, sizeof(peer));
                    memcpy(w.links[at].proto, proto, sizeof(proto));
                    w.links[at].med = med;
                  }
                }
              }
            }
          }
        }
      }
    }
    ls = le < end ? le + 1 : end;
  }
  // parse_record's order of refusals: t_ms first, then the window token, then the value.
  if (!have_t) w.why = NO_T_MS;
  else if (!have_win) w.why = NOT_WINDOW;
  else if ((chan == CH_ACOUSTIC || chan == CH_MOTION) && !have_val) w.why = NO_VALUE;
  else if (overflow) w.why = OVERFLOW;
}

// ---- the fold (pw1 _scalar / _entity / _link) ----------------------------------------------
static int cmpKey(const LinkKey& a, const LinkKey& b) {
  const int c = strcmp(a.peer, b.peer);
  return c ? c : strcmp(a.proto, b.proto);
}

static uint8_t jaccardPe(const Window& a, const Window& b) {
  uint32_t inter = 0;
  for (uint8_t i = 0; i < a.n_ids; ++i)
    for (uint8_t j = 0; j < b.n_ids; ++j)
      if (!strcmp(a.ids[i], b.ids[j])) { ++inter; break; }
  const uint32_t u = (uint32_t)a.n_ids + b.n_ids - inter;
  if (u == 0) return 0;
  const uint32_t v = 255u * (u - inter) / u;
  return (uint8_t)(v > 255 ? 255 : v);
}

void Fold::note(int32_t lon) {
  if (from_ < 0) from_ = lon;
  through_ = lon;
  ++episodes_;
}

void Fold::reset(uint8_t chan) {
  chan_ = chan;
  var_ = 0;
  n_ = episodes_ = excluded_ = segments_ = peers_absent_ = skipped_ = 0;
  from_ = through_ = -1;
  have_prev_ = false;
  prev_.why = cur_.why = OK;
}

void Fold::skip(int32_t lon) {
  note(lon);
  ++skipped_;
}

void Fold::add(const char* text, size_t len, int32_t lon) {
  note(lon);
  parseWindow(chan_, text, len, cur_);
  if (cur_.why != OK) { ++excluded_; return; }
  const bool brk = !have_prev_ || cur_.has_stream != prev_.has_stream ||
                   (cur_.has_stream && cur_.stream != prev_.stream) || cur_.t <= prev_.t;
  if (brk) {
    ++segments_;
  } else if (chan_ == CH_LINK) {
    // sorted(r['links']): byte order of (peer, proto). No run expansion for link.
    bool used[PRECISION_MAX_LINK_KEYS] = {false};
    for (uint8_t k = 0; k < cur_.n_links; ++k) {
      int best = -1;
      for (uint8_t i = 0; i < cur_.n_links; ++i)
        if (!used[i] && (best < 0 || cmpKey(cur_.links[i], cur_.links[best]) < 0)) best = i;
      used[best] = true;
      const LinkKey& c = cur_.links[best];
      int at = -1;
      for (uint8_t j = 0; j < prev_.n_links; ++j)
        if (!cmpKey(prev_.links[j], c)) at = j;
      if (at < 0) { ++peers_absent_; continue; }
      residual(pe(c.med - prev_.links[at].med, PRECISION_SPAN_LINK));
    }
  } else {
    for (uint32_t z = 1; z < cur_.run; ++z) residual(0);   // a run of n = n-1 zero residuals
    residual(chan_ == CH_ENTITY ? jaccardPe(prev_, cur_) : pe(cur_.val - prev_.val, spanOf(chan_)));
  }
  prev_ = cur_;
  have_prev_ = true;
}

// ---- the record ----------------------------------------------------------------------------
bool keyOf(char* out, size_t cap, uint32_t node, uint8_t chan) {
  const int m = snprintf(out, cap, "node:0x%08lx|chan:%s", (unsigned long)node, chanName(chan));
  return m > 0 && (size_t)m < cap;
}

size_t render(char* out, size_t cap, const Fold& f, uint32_t node, uint16_t rev,
              uint32_t created, uint32_t t_sec, const char* stamp) {
  char key[48];
  if (!keyOf(key, sizeof(key), node, f.chan())) return 0;
  const uint32_t s = sid::forKey(node, PRECISION_LANE, key);
  char span[12];
  if (f.chan() == CH_ENTITY) snprintf(span, sizeof(span), "jaccard");
  else snprintf(span, sizeof(span), "%ld", (long)spanOf(f.chan()));
  const int m = snprintf(
      out, cap,
      "\n---\n\n@LAT%dLON%d | sid:00000000 | created:%lu | updated:%lu | "
      "relates:derived_from@LAT%dLON%ld\n"
      "[ew]\nconf:%u\nrev:%u\nsal:0\ntouched:%lu\n[/ew]\n\n"
      "**PRECISION** sid:%08lx node:0x%08lx chan:%s prec:%u var:%ld n:%lu prec_scale:%d\n"
      "**FOLD** pe_span:%s alpha:%d mode:expanded predictor:previous_window "
      "from:@LAT%dLON%ld through:@LAT%dLON%ld episodes:%lu excluded:%lu segments:%lu "
      "peers_absent:%lu skipped:%lu\n"
      "**STAMP** %s\n",
      PRECISION_LANE, (int)f.chan(), (unsigned long)(created ? created : t_sec),
      (unsigned long)t_sec, PRECISION_EPISODE_LANE, (long)f.through(), (unsigned)f.conf(),
      (unsigned)rev, (unsigned long)t_sec, (unsigned long)s, (unsigned long)node,
      chanName(f.chan()), (unsigned)f.prec(), (long)f.var(), (unsigned long)f.n(),
      PRECISION_SCALE, span, PRECISION_ALPHA, PRECISION_EPISODE_LANE, (long)f.from(),
      PRECISION_EPISODE_LANE, (long)f.through(), (unsigned long)f.episodes(),
      (unsigned long)f.excluded(), (unsigned long)f.segments(), (unsigned long)f.peersAbsent(),
      (unsigned long)f.skipped(), stamp ? stamp : "");
  if (m <= 0 || (size_t)m >= cap) return 0;
  // Patch the header placeholder; must agree with the body's sid (same key, same function).
  if (sid::stampKey(out, (size_t)m, node, PRECISION_LANE, key) != s) return 0;
  return (size_t)m;
}

void readOnFlash(const char* rec, size_t len, OnFlash& out) {
  out = OnFlash();
  if (!rec || !len) return;
  TtdbEw ew;
  ttdbParseEw(rec, len, ew);
  const char* end = rec + len;
  // header: created:
  const char* h = rec;
  while (h < end && *h != '@') {
    const char* nl = (const char*)memchr(h, '\n', (size_t)(end - h));
    h = nl ? nl + 1 : end;
  }
  uint64_t created = 0;
  if (h < end) {
    const char* he = (const char*)memchr(h, '\n', (size_t)(end - h));
    if (!he) he = end;
    firstKey(h, he, h, "created:", valU64, &created);
  }
  // **PRECISION** ... \bprec:(\d+)   (\b keeps `prec_scale:` out; it has no ':' after prec)
  const char* t = findIn(rec, end, "**PRECISION**");
  if (!t) return;
  const char* te = (const char*)memchr(t, '\n', (size_t)(end - t));
  if (!te) te = end;
  uint64_t p;
  if (!firstKey(t + 13, te, t, "prec:", valU64, &p)) return;
  out.present = true;
  out.prec = (uint8_t)(p > 255 ? 255 : p);
  out.rev = ew.has_rev ? ew.rev : 0;
  out.created = (uint32_t)(created > 0xFFFFFFFFull ? 0xFFFFFFFFu : created);
  // **FOLD** ... from:@LAT103LON<a>   (design D7). Absent or malformed -> has_from false.
  const char* fl = findIn(rec, end, "**FOLD**");
  if (fl) {
    const char* fe = (const char*)memchr(fl, '\n', (size_t)(end - fl));
    if (!fe) fe = end;
    static const char kNeedle[] = " from:@LAT103LON";
    const char* q = findIn(fl, fe, kNeedle);
    if (q) {
      q += sizeof(kNeedle) - 1;
      int32_t v = 0;
      int digits = 0;
      while (q < fe && *q >= '0' && *q <= '9' && digits < 6) { v = v * 10 + (*q++ - '0'); ++digits; }
      if (digits > 0 && (q == fe || *q == ' ' || *q == '\r')) { out.has_from = true; out.from = v; }
    }
  }
}

bool shouldWrite(const OnFlash& old, const Fold& f) {
  if (f.n() == 0) return false;
  if (!old.present) return true;
  if (!old.has_from || old.from != f.from()) return true;   // D7: the window moved
  const int d = (int)f.prec() - (int)old.prec;
  return (d < 0 ? -d : d) > PRECISION_WRITE_DELTA;
}

}  // namespace precision
