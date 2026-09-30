// Semantic.cpp — see Semantic.h for the design argument. This file is the arithmetic.
//
// Portable on purpose: no <Arduino.h>, so tests/test_semantic.cpp builds it natively and
// pins the belief-line bytes on the host. A fixed-buffer builder that lives in a sketch
// cannot be pinned by a native test at all, which is why it lives here.
#include "Semantic.h"

#include <stdio.h>
#include <string.h>

namespace semantic {

// ---------------------------------------------------------------------------------------
// small string helpers — no allocation, no <String.h>, nothing that can throw
// ---------------------------------------------------------------------------------------
static bool streq(const char* a, const char* b) { return a && b && strcmp(a, b) == 0; }

// Copy a trimmed field into a lemma slot. Returns false if it does not FIT, which is a
// malformed line rather than a truncation: silently truncating two long lemmas that share
// a prefix would MERGE two distinct triples into one belief, and a wrong belief is worse
// than a skipped line. TTG-0002 §5.1 requires malformed lines be skipped, counted and
// reported, so this is inside that contract.
// 0 = ok, 1 = empty after trimming, 2 = does not fit.
// ⚠ The verdict must come from the TRIMMED length, not the raw one: a field of two spaces
// has raw length 2, and reading that as "too long" reported MAL_TOO_LONG for an EMPTY
// subject. A wrong reason is a wrong report, and TTG-0002 §5.1 requires the reason.
static int copyLemmaWhy(char* dst, const char* src, size_t len) {
  while (len && (*src == ' ' || *src == '\t')) { ++src; --len; }
  while (len && (src[len - 1] == ' ' || src[len - 1] == '\t')) --len;
  if (len == 0) return 1;
  if (len >= SEMANTIC_LEMMA_MAX) return 2;
  memcpy(dst, src, len);
  dst[len] = '\0';
  return 0;
}
static bool copyLemma(char* dst, const char* src, size_t len) {
  return copyLemmaWhy(dst, src, len) == 0;
}

// halves -> "3" or "3.5". Returns chars written (never truncates; 0 if it would).
static size_t halvesToStr(uint32_t halves, char* out, size_t cap) {
  uint32_t whole = halves / 2;
  int n = (halves & 1u) ? snprintf(out, cap, "%lu.5", (unsigned long)whole)
                        : snprintf(out, cap, "%lu", (unsigned long)whole);
  if (n < 0 || (size_t)n >= cap) return 0;
  return (size_t)n;
}

// "3" / "3.5" -> halves. Advances *p past the token. false on anything else.
static bool strToHalves(const char** p, uint32_t* out) {
  const char* s = *p;
  while (*s == ' ' || *s == '\t') ++s;
  if (*s < '0' || *s > '9') return false;
  uint32_t whole = 0;
  while (*s >= '0' && *s <= '9') { whole = whole * 10 + (uint32_t)(*s - '0'); ++s; }
  uint32_t halves = whole * 2;
  if (*s == '.') {
    ++s;
    if (*s != '5') return false;      // 0.5 is the only fraction the halves basis admits
    ++s;
    halves += 1;
  }
  *p = s;
  *out = halves;
  return true;
}

// ---------------------------------------------------------------------------------------
Numbers::Numbers()
    : prior_for_halves(2),          // TTG-0003 §5 prior_for 1
      prior_against_halves(2),      // TTG-0003 §5 prior_against 1
      belief_conf_threshold(128) {} // TTG-0003 §5 belief_conf_threshold 128

Consolidator::Consolidator() { reset(); }

void Consolidator::begin() { Numbers d; begin(d); }

void Consolidator::begin(const Numbers& n) {
  n_ = n;
  reset();
}

void Consolidator::reset() {
  memset(terms_, 0, sizeof(terms_));
  memset(ep_plus_, 0, sizeof(ep_plus_));
  memset(ep_minus_, 0, sizeof(ep_minus_));
  count_ = 0;
  malformed_ = skipped_ = reclaimed_ = refused_ = fold_underflow_ = 0;
  last_mal_ = MAL_OK;
  in_episode_ = false;
  // TTG-0002 §4 calls the pairing role `comention`; it is a grammar key, so it is data.
  snprintf(comention_, sizeof(comention_), "%s", "comention");
}

void Consolidator::setComentionRole(const char* role) {
  if (role && *role) snprintf(comention_, sizeof(comention_), "%s", role);
}

// ---------------------------------------------------------------------------------------
// parsing — TTG-RFC-0002 §4 line, §5.1 validation
// ---------------------------------------------------------------------------------------
bool Consolidator::parsePerceptLine(const char* line, Percept& out, Malformed& why) {
  why = MAL_OK;
  if (!line) { why = MAL_COLUMNS; return false; }
  size_t len = strlen(line);
  if (len >= SEMANTIC_LINE_MAX) { why = MAL_TOO_LONG; return false; }

  // Tolerate the `percept:` key, with or without it, so a caller can hand us either a
  // whole store line or just the columns.
  const char* s = line;
  while (*s == ' ' || *s == '\t') ++s;
  if (strncmp(s, "percept:", 8) == 0) s += 8;

  // Split on '|' into at most 7 fields, remembering each field's extent.
  const char* f[8];
  size_t      fl[8];
  int         nf = 0;
  const char* start = s;
  for (const char* p = s;; ++p) {
    if (*p == '|' || *p == '\0' || *p == '\n' || *p == '\r') {
      if (nf < 8) { f[nf] = start; fl[nf] = (size_t)(p - start); ++nf; }
      if (*p != '|') break;
      start = p + 1;
    }
  }
  if (nf < 6) { why = MAL_COLUMNS; return false; }

  memset(&out, 0, sizeof(out));

  // 1. sentence — must be a non-empty run of digits.
  {
    const char* p = f[0];
    size_t      l = fl[0];
    while (l && (*p == ' ' || *p == '\t')) { ++p; --l; }
    while (l && (p[l - 1] == ' ' || p[l - 1] == '\t')) --l;
    if (l == 0) { why = MAL_SENTENCE; return false; }
    uint32_t v = 0;
    for (size_t i = 0; i < l; ++i) {
      if (p[i] < '0' || p[i] > '9') { why = MAL_SENTENCE; return false; }
      v = v * 10 + (uint32_t)(p[i] - '0');
    }
    out.sentence = v;
  }

  // 2-4. subject / vector / object. `-` is well-formed in all three: a `-` subject or
  // vector is a MENTION (TTG-0005 §3), a `-` object is an intransitive clause.
  { int w = copyLemmaWhy(out.subject, f[1], fl[1]);
    if (w) { why = (w == 2) ? MAL_TOO_LONG : MAL_EMPTY; return false; } }
  { int w = copyLemmaWhy(out.vec, f[2], fl[2]);
    if (w) { why = (w == 2) ? MAL_TOO_LONG : MAL_EMPTY; return false; } }
  { int w = copyLemmaWhy(out.object, f[3], fl[3]);
    if (w) { why = (w == 2) ? MAL_TOO_LONG : MAL_EMPTY; return false; } }

  // 5. polarity
  {
    char t[8] = {0};
    if (!copyLemma(t, f[4], fl[4] < sizeof(t) ? fl[4] : sizeof(t) - 1)) { why = MAL_POLARITY; return false; }
    if      (streq(t, "+"))  out.pol = POL_PLUS;
    else if (streq(t, "-"))  out.pol = POL_MINUS;
    else if (streq(t, "?"))  out.pol = POL_HELD;
    else if (streq(t, "?-")) out.pol = POL_HELD_MINUS;
    else { why = MAL_POLARITY; return false; }
  }

  // 6. quantifier
  {
    char t[8] = {0};
    if (!copyLemma(t, f[5], fl[5] < sizeof(t) ? fl[5] : sizeof(t) - 1)) { why = MAL_QUANT; return false; }
    if      (streq(t, "-")) out.quant = Q_NONE;
    else if (streq(t, "~")) out.quant = Q_SOME;
    else if (streq(t, "*")) out.quant = Q_ALL;
    else { why = MAL_QUANT; return false; }
  }

  // 7. optional reading letter — one lowercase letter, and ONLY on a held percept.
  // TTG-0002 §5.1 names both halves of that rule, and the second half is the one worth
  // enforcing: a reading letter on an asserted percept means the grammar read a sentence
  // two ways and then asserted one of them anyway.
  if (nf >= 7) {
    char t[8] = {0};
    size_t l = fl[6] < sizeof(t) - 1 ? fl[6] : sizeof(t) - 1;
    bool empty = !copyLemma(t, f[6], l);
    if (!empty) {
      if (strlen(t) != 1 || t[0] < 'a' || t[0] > 'z') { why = MAL_READING; return false; }
      if (out.pol != POL_HELD && out.pol != POL_HELD_MINUS) { why = MAL_READING; return false; }
      out.reading = t[0];
    }
  }
  return true;
}

size_t Consolidator::renderPerceptLine(const Percept& p, char* out, size_t cap) {
  const char* pol = (p.pol == POL_PLUS) ? "+" : (p.pol == POL_MINUS) ? "-"
                  : (p.pol == POL_HELD) ? "?" : "?-";
  const char* q   = (p.quant == Q_SOME) ? "~" : (p.quant == Q_ALL) ? "*" : "-";
  int n;
  if (p.reading)
    n = snprintf(out, cap, "percept: %lu | %s | %s | %s | %s | %s | %c",
                 (unsigned long)p.sentence, p.subject, p.vec, p.object, pol, q, p.reading);
  else
    n = snprintf(out, cap, "percept: %lu | %s | %s | %s | %s | %s",
                 (unsigned long)p.sentence, p.subject, p.vec, p.object, pol, q);
  if (n < 0 || (size_t)n >= cap) { if (cap) out[0] = '\0'; return 0; }
  return (size_t)n;
}

// ---------------------------------------------------------------------------------------
// the table
// ---------------------------------------------------------------------------------------
int Consolidator::findIndex(const char* s, const char* v, const char* o) const {
  for (size_t i = 0; i < count_; ++i)
    if (terms_[i].used && streq(terms_[i].subject, s) && streq(terms_[i].vec, v) &&
        streq(terms_[i].object, o))
      return (int)i;
  return -1;
}

// Drop the lowest-EPS term so a write can proceed. EPS = sal × (255 − conf) / 255, the
// same key Social's reclaim-lowest uses — the store gives up what it neither relies on
// (low sal) nor doubts (high conf). Ties go to the OLDEST, which keeps the choice
// deterministic; a nondeterministic eviction would break C3's byte-for-byte gate.
//
// ⚠ No @LAT100 boundary is written, and that is not an omission: under KEY naming a term
// is addressed by its lemma, so no ordinal citation breaks when one is dropped.
int Consolidator::reclaimLowestEps() {
  if (count_ == 0) return -1;
  size_t  victim = 0;
  uint8_t best = 255;
  bool    found = false;
  for (size_t i = 0; i < count_; ++i) {
    if (!terms_[i].used) continue;
    uint8_t e = eps(terms_[i]);
    if (!found || e < best) { best = e; victim = i; found = true; }
  }
  if (!found) return -1;
  // Shift the tail down so insertion order survives — TTG-0002 §5.2 wants belief lines
  // "in order of first percept". The scratch arrays are index-parallel to terms_, so they
  // move in lockstep or this episode's votes land on the wrong triples.
  for (size_t i = victim; i + 1 < count_; ++i) {
    terms_[i]    = terms_[i + 1];
    ep_plus_[i]  = ep_plus_[i + 1];
    ep_minus_[i] = ep_minus_[i + 1];
  }
  --count_;
  memset(&terms_[count_], 0, sizeof(Term));
  ep_plus_[count_] = ep_minus_[count_] = 0;
  ++reclaimed_;
  return (int)victim;
}

int Consolidator::intern(const char* s, const char* v, const char* o) {
  int i = findIndex(s, v, o);
  if (i >= 0) return i;
  if (count_ >= SEMANTIC_MAX_TERMS) {
    if (reclaimLowestEps() < 0) return -1;   // cannot happen with a non-empty table
  }
  Term& t = terms_[count_];
  memset(&t, 0, sizeof(t));
  snprintf(t.subject, SEMANTIC_LEMMA_MAX, "%s", s);
  snprintf(t.vec,     SEMANTIC_LEMMA_MAX, "%s", v);
  snprintf(t.object,  SEMANTIC_LEMMA_MAX, "%s", o);
  t.used = true;
  ep_plus_[count_] = ep_minus_[count_] = 0;
  return (int)count_++;
}

// ---------------------------------------------------------------------------------------
// the stream
// ---------------------------------------------------------------------------------------
void Consolidator::beginEpisode() {
  memset(ep_plus_, 0, sizeof(ep_plus_));
  memset(ep_minus_, 0, sizeof(ep_minus_));
  in_episode_ = true;
}

bool Consolidator::percept(const Percept& p) {
  // Forgiving rather than strict: a percept outside an episode opens one. Dropping it
  // would be a refusal, and refusals are the thing this phase exists to remove.
  if (!in_episode_) beginEpisode();

  // NOT BELIEVED, per TTG-0002 §4 / TTG-0005 §3:
  //   - held (`?`, `?-`): said but not asserted
  //   - mention: subject or vector `-` — counted and searchable, never believed
  //   - comention: the pairing role
  const bool mention   = streq(p.subject, "-") || streq(p.vec, "-");
  const bool held      = (p.pol == POL_HELD || p.pol == POL_HELD_MINUS);
  const bool comention = streq(p.vec, comention_);

  if (mention) {
    // No full triple to key on, so there is nothing to increment but the skip count.
    // ⚠ Narrower than TTG-0002 §5.2's per-LEMMA `seen`, deliberately: this table is
    // keyed by triple, not by lemma. Per-lemma `seen` arrives with the term-record
    // writer (placement), which is the increment that needs a lemma-addressed record.
    ++skipped_;
    return false;
  }

  int i = intern(p.subject, p.vec, p.object);
  if (i < 0) { ++refused_; return false; }   // must stay 0; see refused()

  ++terms_[i].seen;                          // held and comention percepts still count as seen
  if (held || comention) { ++skipped_; return false; }

  const uint8_t w = (p.quant == Q_SOME) ? 1 : 2;   // weight_partial 0.5 = one half
  if (p.pol == POL_PLUS) {
    if (w > ep_plus_[i]) ep_plus_[i] = w;          // "the LARGEST weight of its + percepts"
  } else {
    if (w > ep_minus_[i]) ep_minus_[i] = w;
  }
  return true;
}

void Consolidator::endEpisode(Close close) {
  for (size_t i = 0; i < count_; ++i) {
    const uint8_t pl = ep_plus_[i], mi = ep_minus_[i];
    if (!pl && !mi) continue;
    Term& t = terms_[i];
    if (close == KEEPING) {
      t.live_for     += pl;
      t.live_against += mi;
      ++t.episodes;
    } else {
      // FOLD BEFORE FORGET: a MOVE, so live_ + carried_ is invariant. An underflow means
      // the replay did not match what was originally counted — impossible if the episode
      // was immutable (TTG-0002 §5.1), so it is a caller bug and must not be silent.
      if (t.live_for >= pl) t.live_for -= pl; else { t.live_for = 0; ++fold_underflow_; }
      if (t.live_against >= mi) t.live_against -= mi; else { t.live_against = 0; ++fold_underflow_; }
      t.carried_for     += pl;
      t.carried_against += mi;
      // `episodes` is NOT decremented: the episode did contribute; it is merely no longer
      // on flash. That is what makes carried_ a summary rather than a deletion.
    }
  }
  memset(ep_plus_, 0, sizeof(ep_plus_));
  memset(ep_minus_, 0, sizeof(ep_minus_));
  in_episode_ = false;
}

// ---------------------------------------------------------------------------------------
// reading the result — TTG-RFC-0003 §2
// ---------------------------------------------------------------------------------------
size_t      Consolidator::termCount() const { return count_; }
const Term* Consolidator::term(size_t i) const { return i < count_ ? &terms_[i] : 0; }
const Term* Consolidator::find(const char* s, const char* v, const char* o) const {
  int i = findIndex(s, v, o);
  return i < 0 ? 0 : &terms_[i];
}

char Consolidator::polarity(const Term& t) const {
  const uint32_t F = t.totalFor(), A = t.totalAgainst();
  if (F > A) return '+';
  if (A > F) return '-';
  return '?';
}

uint8_t Consolidator::conf(const Term& t) const {
  const uint32_t F = t.totalFor(), A = t.totalAgainst();
  const uint32_t mx = (F > A) ? F : A;
  // 64-bit intermediate: F and A are unbounded sums, and 255 × F overflows 32 bits at
  // ~16.8 M halves. Cheap insurance for a number that must be exact to be byte-stable.
  const uint64_t num = (uint64_t)255 * (mx + n_.prior_for_halves);
  const uint64_t den = (uint64_t)F + A + n_.prior_for_halves + n_.prior_against_halves;
  if (den == 0) return 128;
  const uint64_t r = (2 * num + den) / (2 * den);   // round half up, integer only
  return (uint8_t)(r > 255 ? 255 : r);
}

bool Consolidator::decided(const Term& t) const {
  return polarity(t) != '?' && conf(t) > n_.belief_conf_threshold;
}

uint8_t Consolidator::sal(const Term& t) const {
  const uint32_t s = t.seen + t.asked;          // TTG-0002 §5.2
  return (uint8_t)(s > 255 ? 255 : s);
}

uint8_t Consolidator::eps(const Term& t) const {
  // TTDB-RFC-0005 §3.3. One value function, three consumers: eviction here, the EPS
  // arbiter (ACT-III §6.4) and the snake (§7).
  const uint32_t e = (uint32_t)sal(t) * (uint32_t)(255 - conf(t)) / 255u;
  return (uint8_t)(e > 255 ? 255 : e);
}

// ---------------------------------------------------------------------------------------
// serialising
// ---------------------------------------------------------------------------------------
size_t Consolidator::beliefLine(const Term& t, char* out, size_t cap) const {
  char fbuf[16], abuf[16];
  if (!halvesToStr(t.totalFor(), fbuf, sizeof(fbuf))) return 0;
  if (!halvesToStr(t.totalAgainst(), abuf, sizeof(abuf))) return 0;
  const char pol[2] = {polarity(t), '\0'};
  int n = snprintf(out, cap, SEMANTIC_BELIEF_KEY " %s | %s | %s | %s %s | %u",
                   t.vec, t.object, pol, fbuf, abuf, (unsigned)conf(t));
  if (n < 0 || (size_t)n >= cap) { if (cap) out[0] = '\0'; return 0; }
  return (size_t)n;
}

size_t Consolidator::carriedLine(const Term& t, char* out, size_t cap) const {
  if (t.carried_for == 0 && t.carried_against == 0) { if (cap) out[0] = '\0'; return 0; }
  char fbuf[16], abuf[16];
  if (!halvesToStr(t.carried_for, fbuf, sizeof(fbuf))) return 0;
  if (!halvesToStr(t.carried_against, abuf, sizeof(abuf))) return 0;
  int n = snprintf(out, cap, SEMANTIC_CARRIED_KEY " %s %s %u", fbuf, abuf,
                   (unsigned)t.episodes);
  if (n < 0 || (size_t)n >= cap) { if (cap) out[0] = '\0'; return 0; }
  return (size_t)n;
}

bool Consolidator::seedCarried(const char* subject, const char* vec, const char* object,
                               const char* carried_line) {
  if (!subject || !vec || !object || !carried_line) return false;
  const char* p = carried_line;
  while (*p == ' ' || *p == '\t') ++p;
  const size_t klen = strlen(SEMANTIC_CARRIED_KEY);
  if (strncmp(p, SEMANTIC_CARRIED_KEY, klen) == 0) p += klen;
  uint32_t cf = 0, ca = 0;
  if (!strToHalves(&p, &cf)) return false;
  if (!strToHalves(&p, &ca)) return false;
  uint32_t eps_count = 0;
  const char* q = p;
  while (*q == ' ' || *q == '\t') ++q;
  while (*q >= '0' && *q <= '9') { eps_count = eps_count * 10 + (uint32_t)(*q - '0'); ++q; }

  int i = intern(subject, vec, object);
  if (i < 0) { ++refused_; return false; }
  terms_[i].carried_for     = cf;
  terms_[i].carried_against = ca;
  if (eps_count > terms_[i].episodes) terms_[i].episodes = (uint16_t)eps_count;
  return true;
}

// ---------------------------------------------------------------------------------------
uint32_t  Consolidator::malformedCount() const { return malformed_; }
Malformed Consolidator::lastMalformed()  const { return last_mal_; }
uint32_t  Consolidator::skipped()        const { return skipped_; }
uint32_t  Consolidator::reclaimed()      const { return reclaimed_; }
uint32_t  Consolidator::refused()        const { return refused_; }
uint32_t  Consolidator::foldUnderflow()  const { return fold_underflow_; }

// PerceptLearn Rule 3, the selectable second consolidator. Reverse-engineered from and
// verified against all eight of the Cardputer's live @LAT91 beliefs on 2026-09-30 (exact,
// 8/8). ⚠ Order-dependent and valid only over the retained window — see the header.
uint8_t Consolidator::rule3Conf(uint32_t met, uint32_t violated) {
  const int32_t base = 128;
  int64_t v = (int64_t)base + 2 * (int64_t)met - 16 * (int64_t)violated;
  if (v < 0) v = 0;
  if (v > 255) v = 255;
  return (uint8_t)v;
}

bool Consolidator::feedLine(const char* line) {
  Percept p;
  Malformed why = MAL_OK;
  if (!parsePerceptLine(line, p, why)) {
    ++malformed_;
    last_mal_ = why;
    return false;   // TTG-0002 §5.1: skip, count, report. Never abort the episode.
  }
  return percept(p);
}

}  // namespace semantic
