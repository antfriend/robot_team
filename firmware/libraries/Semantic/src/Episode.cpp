// Episode.cpp — see Episode.h for the design argument (the lanes, the commit order, why
// oldest-first, why serial ordinals). Portable: built natively by tests/test_episode.cpp.
#include "Episode.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

namespace semantic {

// ---------------------------------------------------------------------------------------
// serial ordinals
// ---------------------------------------------------------------------------------------
int16_t ordinalAdd(int16_t x, int32_t d) {
  int32_t v = ((int32_t)x + d) % SEMANTIC_ORDINAL_MOD;
  if (v < 0) v += SEMANTIC_ORDINAL_MOD;
  return (int16_t)v;
}

uint16_t ordinalDistance(int16_t from, int16_t to) {
  int32_t d = ((int32_t)to - (int32_t)from) % SEMANTIC_ORDINAL_MOD;
  if (d < 0) d += SEMANTIC_ORDINAL_MOD;
  return (uint16_t)d;
}

bool ordinalInRun(int16_t x, int16_t from, int16_t through) {
  return ordinalDistance(from, x) <= ordinalDistance(from, through);
}

// ---------------------------------------------------------------------------------------
// line helpers
// ---------------------------------------------------------------------------------------
static const char* skipWs(const char* s) {
  while (*s == ' ' || *s == '\t') ++s;
  return s;
}

static bool startsWith(const char* s, const char* key) {
  return strncmp(s, key, strlen(key)) == 0;
}

// A fence line: "```" optionally followed by a tag. Returns the tag (possibly "") or null.
static const char* fenceTag(const char* l) {
  l = skipWs(l);
  if (strncmp(l, "```", 3) != 0) return 0;
  return l + 3;
}

static bool tagIs(const char* tag, const char* want) {
  size_t n = strlen(want);
  if (strncmp(tag, want, n) != 0) return false;
  tag += n;
  while (*tag == ' ' || *tag == '\t' || *tag == '\r' || *tag == '\n') ++tag;
  return *tag == '\0';
}

// "@LAT<lat>LON<lon>..." -> true. Only the coordinate is read; the rest of the header is
// Ttdb's business.
static bool parseCoord(const char* l, int16_t& lat, int16_t& lon) {
  if (strncmp(l, "@LAT", 4) != 0) return false;
  const char* p = l + 4;
  bool neg = false;
  if (*p == '-') { neg = true; ++p; }
  if (*p < '0' || *p > '9') return false;
  int32_t a = 0;
  while (*p >= '0' && *p <= '9') { a = a * 10 + (*p - '0'); if (a > 32767) return false; ++p; }
  if (strncmp(p, "LON", 3) != 0) return false;
  p += 3;
  bool nego = false;
  if (*p == '-') { nego = true; ++p; }
  if (*p < '0' || *p > '9') return false;
  int32_t o = 0;
  while (*p >= '0' && *p <= '9') { o = o * 10 + (*p - '0'); if (o > 32767) return false; ++p; }
  lat = (int16_t)(neg ? -a : a);
  lon = (int16_t)(nego ? -o : o);
  return true;
}

// A field that is going into a `|`-separated line or a header must not carry the
// separator or a line break — it would read back as a different record.
static bool cleanField(const char* s) {
  for (; *s; ++s)
    if (*s == '|' || *s == '\n' || *s == '\r') return false;
  return true;
}

// ---------------------------------------------------------------------------------------
// EpisodeBuilder
// ---------------------------------------------------------------------------------------
EpisodeBuilder::EpisodeBuilder(char* buf, size_t cap)
    : buf_(buf), cap_(cap), len_(0), percepts_(0), rejected_(0), overflow_(false),
      open_(false) {
  if (buf_ && cap_) buf_[0] = '\0';
}

bool EpisodeBuilder::put(const char* fmt, ...) {
  if (overflow_ || !buf_) { overflow_ = true; return false; }
  va_list ap;
  va_start(ap, fmt);
  int n = vsnprintf(buf_ + len_, cap_ - len_, fmt, ap);
  va_end(ap);
  if (n < 0 || (size_t)n >= cap_ - len_) {
    overflow_ = true;
    buf_[len_] = '\0';     // never leave a half-written line behind
    return false;
  }
  len_ += (size_t)n;
  return true;
}

bool EpisodeBuilder::begin(int16_t ordinal, uint32_t t, const char* title,
                           const char* source, const char* at, int16_t lane) {
  len_ = 0; percepts_ = 0; rejected_ = 0; overflow_ = false; open_ = false;
  if (buf_ && cap_) buf_[0] = '\0';
  if (!title || !source || !at || ordinal < 0 ||
      !cleanField(title) || !cleanField(source) || !cleanField(at)) {
    overflow_ = true;      // a malformed header is unwritable, same verdict as no room
    return false;
  }
  open_ = put("\n---\n\n@LAT%dLON%d | created:%lu | updated:%lu\n\n**%s**\n\n```"
              SEMANTIC_EPISODE_TAG "\nsource: %s\nat: %s\n",
              (int)lane, (int)ordinal, (unsigned long)t, (unsigned long)t, title, source, at);
  return open_;
}

bool EpisodeBuilder::said(uint32_t sentence, const char* text) {
  if (!open_ || !text) return false;
  if (!cleanField(text)) { ++rejected_; return false; }
  return put("said: %lu | %s\n", (unsigned long)sentence, text);
}

bool EpisodeBuilder::percept(const Percept& p) {
  if (!open_) return false;
  if (!cleanField(p.subject) || !cleanField(p.vec) || !cleanField(p.object) ||
      !p.subject[0] || !p.vec[0] || !p.object[0]) {
    ++rejected_;
    return false;
  }
  char line[SEMANTIC_LINE_MAX];
  size_t n = Consolidator::renderPerceptLine(p, line, sizeof(line));
  // Render, then PARSE what was rendered: the episode is immutable once written, so a line
  // the reader would reject must be caught here, while it can still be counted honestly as
  // a rejection rather than surfacing forever as a malformed line in the evidence.
  Percept back;
  Malformed why;
  if (!n || !Consolidator::parsePerceptLine(line, back, why)) { ++rejected_; return false; }
  if (!put("%s\n", line)) return false;
  ++percepts_;
  return true;
}

size_t EpisodeBuilder::finish() {
  if (!open_) return 0;
  open_ = false;
  if (!put("```\n")) return 0;
  return overflow_ ? 0 : len_;
}

// ---------------------------------------------------------------------------------------
// EpisodeReader
// ---------------------------------------------------------------------------------------
EpisodeReader::EpisodeReader(Consolidator& c, int16_t lane)
    : c_(c), lane_(lane), from_(0), through_(0), any_(false),
      close_(Consolidator::KEEPING), cur_lat_(0), cur_lon_(0), have_rec_(false),
      mode_(OUT), fed_(0), outside_(0), foreign_blocks_(0), foreign_malformed_(0),
      unclosed_(0) {}

void EpisodeReader::select(int16_t from, int16_t through, Consolidator::Close close) {
  from_ = from; through_ = through; close_ = close; any_ = true;
}

void EpisodeReader::selectNone() { any_ = false; }

void EpisodeReader::closeBlock() {
  if (mode_ == FEED) {
    c_.endEpisode(close_);
    ++fed_;
  }
  mode_ = OUT;
}

void EpisodeReader::line(const char* l) {
  if (!l) return;
  int16_t lat, lon;
  if (l[0] == '@' && parseCoord(l, lat, lon)) {
    // A header inside an open block means the fence never closed. Close it rather than
    // let the next record's lines be read as this episode's — and count it, because the
    // builder never writes one, so an unclosed block is damage, not style.
    if (mode_ != OUT) { ++unclosed_; closeBlock(); }
    cur_lat_ = lat; cur_lon_ = lon; have_rec_ = true;
    return;
  }

  const char* tag = fenceTag(l);
  if (tag) {
    if (mode_ != OUT) { closeBlock(); return; }       // any fence closes an open block
    if (!tagIs(tag, SEMANTIC_EPISODE_TAG)) return;    // someone else's block
    if (!have_rec_ || cur_lat_ != lane_) {
      // TTG-0002 §5.1: off-lane, it is a quotation, not testimony.
      ++foreign_blocks_;
      mode_ = CHECK;
      return;
    }
    if (any_ && ordinalInRun(cur_lon_, from_, through_)) {
      c_.beginEpisode();
      mode_ = FEED;
    } else {
      ++outside_;
      mode_ = SKIP;
    }
    return;
  }

  if (mode_ == OUT || mode_ == SKIP) return;
  const char* s = skipWs(l);
  if (!startsWith(s, "percept:")) return;             // source:/at:/said: are not percepts
  if (mode_ == FEED) {
    c_.feedLine(s);
  } else {                                            // CHECK
    Percept p;
    Malformed why;
    if (!Consolidator::parsePerceptLine(s, p, why)) ++foreign_malformed_;
  }
}

void EpisodeReader::finish() {
  if (mode_ != OUT) { ++unclosed_; closeBlock(); }
  have_rec_ = false;
}

// ---------------------------------------------------------------------------------------
// the checkpoint
// ---------------------------------------------------------------------------------------
size_t renderCheckpoint(const Consolidator& c, int16_t through, int16_t ordinal,
                        uint32_t t, char* out, size_t cap, int16_t lane) {
  if (!out || cap == 0 || ordinal < 0 || through < 0) return 0;
  size_t len = 0;
  int n = snprintf(out, cap,
                   "\n---\n\n@LAT%dLON%d | created:%lu | updated:%lu\n\n"
                   "**carried through @LAT%dLON%d**\n\n```" SEMANTIC_CARRIED_TAG "\n"
                   SEMANTIC_THROUGH_KEY " %d\n",
                   (int)lane, (int)ordinal, (unsigned long)t, (unsigned long)t,
                   (int)SEMANTIC_EPISODE_LANE, (int)through, (int)through);
  if (n < 0 || (size_t)n >= cap) { out[0] = '\0'; return 0; }
  len = (size_t)n;
  for (size_t i = 0; i < c.termCount(); ++i) {
    const Term* tm = c.term(i);
    char cl[64];
    if (!c.carriedLine(*tm, cl, sizeof(cl))) continue;   // nothing carried for this term
    n = snprintf(out + len, cap - len, "%s | %s | %s | %s\n", cl, tm->subject, tm->vec,
                 tm->object);
    if (n < 0 || (size_t)n >= cap - len) { out[0] = '\0'; return 0; }
    len += (size_t)n;
  }
  n = snprintf(out + len, cap - len, "```\n");
  if (n < 0 || (size_t)n >= cap - len) { out[0] = '\0'; return 0; }
  return len + (size_t)n;
}

CheckpointReader::CheckpointReader(Consolidator& c, int16_t ordinal, int16_t lane)
    : c_(c), lane_(lane), ordinal_(ordinal), in_rec_(false), in_block_(false),
      have_through_(false), through_(0), seeded_(0), malformed_(0) {}

// `carried: <f> <a> <e> | <subject> | <vector> | <object>` — split, then hand the numeric
// head to Consolidator::seedCarried, which already owns that grammar.
static bool splitCarried(const char* l, char* head, size_t hcap, char* s, char* v, char* o) {
  const char* f[4];
  size_t fl[4];
  int nf = 0;
  const char* start = l;
  for (const char* p = l;; ++p) {
    if (*p == '|' || *p == '\0' || *p == '\n' || *p == '\r') {
      if (nf >= 4) return false;                       // too many columns
      f[nf] = start; fl[nf] = (size_t)(p - start); ++nf;
      if (*p != '|') break;
      start = p + 1;
    }
  }
  if (nf != 4) return false;
  if (fl[0] >= hcap) return false;
  memcpy(head, f[0], fl[0]);
  head[fl[0]] = '\0';
  char* dst[3] = {s, v, o};
  for (int k = 0; k < 3; ++k) {
    const char* a = f[k + 1];
    size_t n = fl[k + 1];
    while (n && (*a == ' ' || *a == '\t')) { ++a; --n; }
    while (n && (a[n - 1] == ' ' || a[n - 1] == '\t')) --n;
    if (n == 0 || n >= SEMANTIC_LEMMA_MAX) return false;
    memcpy(dst[k], a, n);
    dst[k][n] = '\0';
  }
  return true;
}

void CheckpointReader::line(const char* l) {
  if (!l) return;
  int16_t lat, lon;
  if (l[0] == '@' && parseCoord(l, lat, lon)) {
    in_rec_ = (lat == lane_ && lon == ordinal_);
    in_block_ = false;
    return;
  }
  if (!in_rec_) return;
  const char* tag = fenceTag(l);
  if (tag) {
    in_block_ = !in_block_ && tagIs(tag, SEMANTIC_CARRIED_TAG);
    return;
  }
  if (!in_block_) return;
  const char* s = skipWs(l);
  if (startsWith(s, SEMANTIC_THROUGH_KEY)) {
    const char* p = skipWs(s + strlen(SEMANTIC_THROUGH_KEY));
    int32_t v = 0;
    bool digits = false;
    while (*p >= '0' && *p <= '9') { v = v * 10 + (*p - '0'); digits = true; if (v >= SEMANTIC_ORDINAL_MOD) break; ++p; }
    if (!digits || v >= SEMANTIC_ORDINAL_MOD) { ++malformed_; return; }
    through_ = (int16_t)v;
    have_through_ = true;
    return;
  }
  if (startsWith(s, SEMANTIC_CARRIED_KEY)) {
    char head[48], subj[SEMANTIC_LEMMA_MAX], vec[SEMANTIC_LEMMA_MAX], obj[SEMANTIC_LEMMA_MAX];
    if (!splitCarried(s, head, sizeof(head), subj, vec, obj) ||
        !c_.seedCarried(subj, vec, obj, head)) {
      ++malformed_;
      return;
    }
    ++seeded_;
  }
}

// ---------------------------------------------------------------------------------------
// EpisodeRing
// ---------------------------------------------------------------------------------------
EpisodeRing::EpisodeRing()
    : capacity_(SEMANTIC_RING_CAPACITY), batch_(SEMANTIC_EVICT_BATCH), ep_any_(false),
      ep_oldest_(0), ep_newest_(0), ep_count_(0), ck_oldest_(0), ck_newest_(0),
      ck_count_(0), has_flash_h_(false), has_ram_h_(false), flash_h_(0), ram_h_(0),
      folds_(0) {}

void EpisodeRing::begin(uint16_t capacity, uint16_t batch) {
  capacity_ = capacity ? capacity : 1;
  // A batch larger than the ring would fold episodes that are not there.
  batch_ = (batch == 0) ? 1 : (batch > capacity_ ? capacity_ : batch);
  has_flash_h_ = has_ram_h_ = false;
  flash_h_ = ram_h_ = 0;
  folds_ = 0;
  resetScan();
}

void EpisodeRing::resetScan() {
  ep_any_ = false;
  ep_oldest_ = ep_newest_ = 0;
  ep_count_ = 0;
  ck_oldest_ = ck_newest_ = 0;
  ck_count_ = 0;
}

void EpisodeRing::observe(int16_t lat, int16_t lon) {
  if (lon < 0) return;                       // not an ordinal this ring wrote
  if (lat == SEMANTIC_EPISODE_LANE) {
    if (!ep_any_) { ep_oldest_ = lon; ep_any_ = true; }
    ep_newest_ = lon;                        // FILE ORDER: the last one seen is the newest
    ++ep_count_;
  } else if (lat == SEMANTIC_CARRIED_LANE) {
    if (ck_count_ == 0) ck_oldest_ = lon;
    ck_newest_ = lon;
    ++ck_count_;
  }
}

void EpisodeRing::setHorizon(int16_t through) {
  flash_h_ = ram_h_ = through;
  has_flash_h_ = has_ram_h_ = true;
}

// Oldest LIVE ordinal and how many are live. The live run is contiguous by construction:
// ordinals are assigned max+1 and only the oldest are ever cut.
uint16_t EpisodeRing::liveFrom(int16_t& from) const {
  if (!ep_any_) return 0;
  const uint16_t span = ordinalDistance(ep_oldest_, ep_newest_);   // count - 1, if contiguous
  if (!has_ram_h_) { from = ep_oldest_; return (uint16_t)(span + 1); }
  // Age of the horizon behind the newest. A horizon at or behind (oldest - 1) folds
  // nothing that is present: everything on flash is live.
  const uint16_t age_h = ordinalDistance(ram_h_, ep_newest_);
  if (age_h > span) { from = ep_oldest_; return (uint16_t)(span + 1); }
  from = ordinalAdd(ram_h_, 1);
  return age_h;                              // ordinals strictly newer than the horizon
}

uint16_t EpisodeRing::live() const {
  int16_t from;
  return liveFrom(from);
}

bool EpisodeRing::liveRun(int16_t& from, int16_t& through) const {
  if (liveFrom(from) == 0) return false;
  through = ep_newest_;
  return true;
}

int16_t EpisodeRing::nextOrdinal() const {
  if (ep_any_) return ordinalAdd(ep_newest_, 1);
  // An empty lane with a horizon was cut down to nothing: continue past the horizon so an
  // ordinal is never re-used while a checkpoint still names it.
  if (has_ram_h_) return ordinalAdd(ram_h_, 1);
  return 0;
}

int16_t EpisodeRing::nextCheckpointOrdinal() const {
  return ck_count_ ? ordinalAdd(ck_newest_, 1) : 0;
}

void EpisodeRing::appended(int16_t ordinal) {
  if (!ep_any_) { ep_oldest_ = ordinal; ep_any_ = true; }
  ep_newest_ = ordinal;
  ++ep_count_;
}

void EpisodeRing::checkpointAppended(int16_t ordinal) {
  if (ck_count_ == 0) ck_oldest_ = ordinal;
  ck_newest_ = ordinal;
  ++ck_count_;
  flash_h_ = ram_h_;
  has_flash_h_ = has_ram_h_;
}

bool EpisodeRing::foldDue(int16_t& from, int16_t& through) const {
  const uint16_t n_live = liveFrom(from);
  if (n_live <= capacity_) return false;
  // Fold down to (capacity - batch) live, so the next fold is `batch` appends away rather
  // than one: every fold is eventually a whole-file rewrite.
  uint16_t n = (uint16_t)(n_live - capacity_ + batch_);
  if (n > n_live) n = n_live;
  through = ordinalAdd(from, (int32_t)n - 1);
  return true;
}

void EpisodeRing::folded(int16_t through) {
  int16_t from;
  const uint16_t before = liveFrom(from);
  ram_h_ = through;
  has_ram_h_ = true;
  const uint16_t after = live();
  folds_ += (uint32_t)(before > after ? before - after : 0);
}

bool EpisodeRing::commitDue() const {
  if (!has_ram_h_) return false;
  return !has_flash_h_ || flash_h_ != ram_h_;
}

// Append [lo..hi] (forward, possibly wrapping) as one or two cuts.
static uint8_t addRun(Cut* out, uint8_t n, uint8_t max, int16_t lat, int16_t lo, int16_t hi) {
  if (lo <= hi) {
    if (n < max) out[n++] = Cut{lat, lo, hi};
  } else {                                   // wrapped: [lo..32767] + [0..hi]
    if (n < max) out[n++] = Cut{lat, lo, (int16_t)(SEMANTIC_ORDINAL_MOD - 1)};
    if (n < max) out[n++] = Cut{lat, 0, hi};
  }
  return n;
}

uint8_t EpisodeRing::cuts(Cut* out, uint8_t max) const {
  uint8_t n = 0;
  if (!out || max == 0) return 0;
  // Episodes at or behind the COMMITTED horizon. Never the RAM one: a fold that has not
  // reached flash must leave its episodes there, or a reboot would lose them outright.
  if (ep_any_ && has_flash_h_) {
    const uint16_t span = ordinalDistance(ep_oldest_, ep_newest_);
    const uint16_t age_h = ordinalDistance(flash_h_, ep_newest_);
    if (age_h <= span) n = addRun(out, n, max, SEMANTIC_EPISODE_LANE, ep_oldest_, flash_h_);
  }
  // Every checkpoint but the newest.
  if (ck_count_ > 1)
    n = addRun(out, n, max, SEMANTIC_CARRIED_LANE, ck_oldest_, ordinalAdd(ck_newest_, -1));
  return n;
}

}  // namespace semantic
