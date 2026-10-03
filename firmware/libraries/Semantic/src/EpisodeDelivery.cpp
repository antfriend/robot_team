// EpisodeDelivery.cpp — see EpisodeDelivery.h.
#include "EpisodeDelivery.h"

#include <stdio.h>
#include <string.h>

namespace semantic {

// ---------------------------------------------------------------------------------------
// small helpers (Episode.cpp keeps its own file-static)
// ---------------------------------------------------------------------------------------
static void putU32(uint8_t* p, uint32_t v) {
  p[0] = (uint8_t)v; p[1] = (uint8_t)(v >> 8); p[2] = (uint8_t)(v >> 16); p[3] = (uint8_t)(v >> 24);
}
static uint32_t getU32(const uint8_t* p) {
  return (uint32_t)p[0] | ((uint32_t)p[1] << 8) | ((uint32_t)p[2] << 16) | ((uint32_t)p[3] << 24);
}
static void putU16(uint8_t* p, uint16_t v) { p[0] = (uint8_t)v; p[1] = (uint8_t)(v >> 8); }
static uint16_t getU16(const uint8_t* p) { return (uint16_t)(p[0] | (p[1] << 8)); }

// `@LAT<int>LON<int>` at the start of `s`. Returns false otherwise.
static bool headerCoord(const char* s, int16_t* lat, int16_t* lon) {
  if (strncmp(s, "@LAT", 4) != 0) return false;
  const char* p = s + 4;
  bool neg = false;
  if (*p == '-') { neg = true; ++p; }
  if (*p < '0' || *p > '9') return false;
  long a = 0;
  while (*p >= '0' && *p <= '9') { a = a * 10 + (*p - '0'); if (a > 32767) return false; ++p; }
  if (strncmp(p, "LON", 3) != 0) return false;
  p += 3;
  bool nego = false;
  if (*p == '-') { nego = true; ++p; }
  if (*p < '0' || *p > '9') return false;
  long o = 0;
  while (*p >= '0' && *p <= '9') { o = o * 10 + (*p - '0'); if (o > 32767) return false; ++p; }
  *lat = (int16_t)(neg ? -a : a);
  *lon = (int16_t)(nego ? -o : o);
  return true;
}

static const char* skipWs(const char* s) {
  while (*s == ' ' || *s == '\t') ++s;
  return s;
}

static bool isFence(const char* l) { return strncmp(skipWs(l), "```", 3) == 0; }
static bool isEpisodeFence(const char* l) {
  return strncmp(skipWs(l), "```" SEMANTIC_EPISODE_TAG, 3 + strlen(SEMANTIC_EPISODE_TAG)) == 0;
}

static bool readU32Dec(const char* p, uint32_t* out) {
  uint64_t v = 0;
  int d = 0;
  for (; *p >= '0' && *p <= '9'; ++p, ++d) {
    v = v * 10 + (uint64_t)(*p - '0');
    if (v > 0xFFFFFFFFull) return false;
  }
  if (!d) return false;
  while (*p == ' ' || *p == '\r') ++p;
  if (*p != '\0' && *p != '\n') return false;
  *out = (uint32_t)v;
  return true;
}

static bool readHeldAgent(const char* l, uint32_t* agent) {
  if (strncmp(l, "held: 0x", 8) != 0) return false;
  uint64_t v = 0;
  int d = 0;
  for (const char* p = l + 8;; ++p, ++d) {
    int x;
    if (*p >= '0' && *p <= '9') x = *p - '0';
    else if (*p >= 'a' && *p <= 'f') x = *p - 'a' + 10;
    else if (*p >= 'A' && *p <= 'F') x = *p - 'A' + 10;
    else break;
    v = v * 16 + (uint64_t)x;
    if (v > 0xFFFFFFFFull) return false;
  }
  if (!d) return false;
  *agent = (uint32_t)v;
  return true;
}

// ---------------------------------------------------------------------------------------
// wire
// ---------------------------------------------------------------------------------------
size_t encodeWant(const Want& w, uint8_t* p, size_t cap) {
  if (!p || cap < EPISODEDELIVERY_WANT_LEN) return 0;
  p[0] = EPISODEORDER_SUBOP_WANT;
  putU32(p + 1, w.to); putU32(p + 5, w.agent); putU32(p + 9, w.from_seq); putU32(p + 13, w.to_seq);
  p[17] = w.tier;
  putU16(p + 18, w.off);
  return EPISODEDELIVERY_WANT_LEN;
}

bool decodeWant(const uint8_t* p, size_t len, Want& w) {
  if (!p || len < EPISODEDELIVERY_WANT_LEN || p[0] != EPISODEORDER_SUBOP_WANT) return false;
  w.to = getU32(p + 1); w.agent = getU32(p + 5); w.from_seq = getU32(p + 9);
  w.to_seq = getU32(p + 13); w.tier = p[17]; w.off = getU16(p + 18);
  if (w.off && w.to_seq != w.from_seq) return false;   // a resume names exactly one seq
  return w.from_seq != 0 && (w.to_seq == 0 || w.to_seq >= w.from_seq);
}

size_t encodeData(const DataHdr& h, const uint8_t* bytes, size_t n, uint8_t* p, size_t cap) {
  if (!p || n > EPISODEDELIVERY_SLICE || cap < EPISODEDELIVERY_DATA_HDR + n || (n && !bytes))
    return 0;
  p[0] = EPISODEORDER_SUBOP_DATA;
  putU32(p + 1, h.to); putU32(p + 5, h.agent); putU32(p + 9, h.seq);
  putU16(p + 13, h.total); putU16(p + 15, h.off);
  if (n) memcpy(p + EPISODEDELIVERY_DATA_HDR, bytes, n);
  return EPISODEDELIVERY_DATA_HDR + n;
}

bool decodeData(const uint8_t* p, size_t len, DataHdr& h, const uint8_t** bytes, size_t* n) {
  if (!p || len <= EPISODEDELIVERY_DATA_HDR || p[0] != EPISODEORDER_SUBOP_DATA) return false;
  h.to = getU32(p + 1); h.agent = getU32(p + 5); h.seq = getU32(p + 9);
  h.total = getU16(p + 13); h.off = getU16(p + 15);
  const size_t m = len - EPISODEDELIVERY_DATA_HDR;
  if (m > EPISODEDELIVERY_SLICE || (size_t)h.off + m > h.total || h.seq == 0) return false;
  if (bytes) *bytes = p + EPISODEDELIVERY_DATA_HDR;
  if (n) *n = m;
  return true;
}

size_t encodeDone(const Done& d, uint8_t* p, size_t cap) {
  if (!p || cap < EPISODEDELIVERY_DONE_LEN) return 0;
  p[0] = EPISODEDELIVERY_SUBOP_DONE;
  putU32(p + 1, d.to); putU32(p + 5, d.agent); putU32(p + 9, d.through);
  putU16(p + 13, d.total);
  return EPISODEDELIVERY_DONE_LEN;
}

bool decodeDone(const uint8_t* p, size_t len, Done& d) {
  if (!p || len < EPISODEDELIVERY_DONE_LEN || p[0] != EPISODEDELIVERY_SUBOP_DONE) return false;
  d.to = getU32(p + 1); d.agent = getU32(p + 5); d.through = getU32(p + 9);
  d.total = getU16(p + 13);
  return true;
}

// ---------------------------------------------------------------------------------------
// Inflight
// ---------------------------------------------------------------------------------------
void Inflight::arm(uint32_t self, uint32_t agent, uint8_t* buf, size_t cap) {
  armed_ = false;                    // the callback ignores everything while we rewrite
  buf_ = buf; cap_ = cap; self_ = self; agent_ = agent;
  seq_ = 0; through_ = 0; total_ = 0; got_ = 0;
  started_ = false; broken_ = false; done_ = false; done_total_ = 0;
  armed_ = buf != nullptr && cap > 0;
}

void Inflight::resume() {
  armed_ = false;
  through_ = 0; done_total_ = 0; done_ = false;      // keep seq_, total_, got_ and the bytes
  armed_ = buf_ != nullptr && cap_ > 0;
}

void Inflight::disarm() {
  armed_ = false;
  buf_ = nullptr;
  cap_ = 0;
}

void Inflight::onData(const DataHdr& h, const uint8_t* b, size_t n) {
  if (!armed_ || done_ || broken_ || h.to != self_ || h.agent != agent_) return;
  if (!started_) {                   // any slice names the episode, not only the first
    if (h.total == 0 || h.total > cap_) { broken_ = true; return; }
    seq_ = h.seq; total_ = h.total; got_ = 0; started_ = true;
  }
  if (h.seq != seq_ || h.total != total_) return;   // another episode's late slice
  if (h.off != got_ || got_ + n > total_) return;   // past a gap (or a repeat): stall here
  memcpy(buf_ + got_, b, n);
  got_ += (uint32_t)n;
}

void Inflight::onDone(const Done& d) {
  if (!armed_ || done_ || d.to != self_ || d.agent != agent_) return;
  if (!started_ && d.total) {        // data was sent and every slice was lost: resume at 0
    if (d.total > cap_) broken_ = true;
    else { seq_ = d.through; total_ = d.total; got_ = 0; started_ = true; }
  }
  through_ = d.through;
  done_total_ = d.total;
  done_ = true;                      // last: loop reads nothing until this is set
}

Inflight::State Inflight::state() const {
  if (!armed_) return IDLE;
  if (!done_) return WAITING;
  if (broken_) return BROKEN;
  if (!started_) return EMPTY;
  if (seq_ != through_) return BROKEN;
  if (done_total_ == 0) return EMPTY;                // the resumed seq is gone (folded)
  if (done_total_ != total_) return BROKEN;
  return got_ == total_ ? COMPLETE : PARTIAL;
}

// ---------------------------------------------------------------------------------------
// Fetcher
// ---------------------------------------------------------------------------------------
void Fetcher::begin(uint32_t self) {
  self_ = self;
  n_ = 0;
  rr_ = 0;
}

Fetcher::E* Fetcher::find(uint32_t agent, bool add) {
  for (uint8_t i = 0; i < n_; ++i)
    if (e_[i].agent == agent) return &e_[i];
  if (!add || n_ >= EPISODEORDER_OTHERS) return nullptr;
  e_[n_] = E{agent, 0, 0, 0, false};
  return &e_[n_++];
}

void Fetcher::seed(uint32_t agent, uint32_t cursor) {
  if (agent == self_) return;
  E* e = find(agent, true);
  if (e && cursor > e->cursor) { e->cursor = cursor; e->known = true; }
}

bool Fetcher::next(const VectorClock& vc, uint32_t now_ms, Want& w) {
  Follows f[EPISODEORDER_OTHERS];
  const uint8_t nf = vc.follows(f, EPISODEORDER_OTHERS);
  if (!nf) return false;
  for (uint8_t k = 0; k < nf; ++k) {
    const Follows& x = f[(rr_ + k) % nf];
    E* e = find(x.agent, true);
    if (!e) continue;
    if (!e->known) {                 // first sight: start BACKLOG behind, not at seq 1
      e->cursor = x.seq > EPISODEDELIVERY_BACKLOG ? x.seq - EPISODEDELIVERY_BACKLOG : 0;
      e->known = true;
    }
    if (x.seq <= e->cursor) continue;
    if ((int32_t)(now_ms - e->next_ms) < 0) continue;
    w = Want{x.agent, x.agent, e->cursor + 1, x.seq, TIER_LINK};
    rr_ = (uint8_t)((rr_ + k + 1) % nf);
    return true;
  }
  return false;
}

void Fetcher::answered(uint32_t agent, uint32_t through, uint32_t now_ms) {
  E* e = find(agent, true);
  if (!e) return;
  if (through > e->cursor) e->cursor = through;
  e->known = true;
  e->misses = 0;
  e->next_ms = now_ms;               // more may be waiting: ask again at once
}

void Fetcher::unanswered(uint32_t agent, uint32_t now_ms) {
  E* e = find(agent, true);
  if (!e) return;
  if (e->misses < 255) ++e->misses;
  e->next_ms = now_ms + (e->misses >= EPISODEDELIVERY_MISSES_BEFORE_BACKOFF
                             ? EPISODEDELIVERY_BACKOFF_MS : EPISODEDELIVERY_RETRY_MS);
}

void Fetcher::retry(uint32_t agent, uint32_t now_ms) {
  E* e = find(agent, true);
  if (e) e->next_ms = now_ms + EPISODEDELIVERY_RETRY_MS;
}

uint32_t Fetcher::cursor(uint32_t agent) const {
  for (uint8_t i = 0; i < n_; ++i)
    if (e_[i].agent == agent) return e_[i].cursor;
  return 0;
}

// ---------------------------------------------------------------------------------------
// HeldIndex
// ---------------------------------------------------------------------------------------
void HeldIndex::reset() {
  n_ = 0;
  in_rec_ = false;
}

void HeldIndex::commitCur() {
  if (!in_rec_) return;
  in_rec_ = false;
  if (!cur_.agent || !cur_.seq) return;      // not a copy we can name: ignore it
  if (n_ == EPISODEDELIVERY_HELD_CAP) {      // more on flash than we track: keep the newest
    memmove(&e_[0], &e_[1], (EPISODEDELIVERY_HELD_CAP - 1) * sizeof(E));
    --n_;
  }
  e_[n_++] = cur_;
}

void HeldIndex::line(const char* l) {
  if (!l) return;
  int16_t lat, lon;
  if (l[0] == '@') {
    commitCur();
    if (headerCoord(l, &lat, &lon) && lat == EPISODEDELIVERY_HELD_LANE) {
      cur_ = E{0, 0, lon};
      in_rec_ = true;
    }
    return;
  }
  if (!in_rec_) return;
  uint32_t v;
  if (readHeldAgent(l, &v)) cur_.agent = v;
  else if (strncmp(l, "seq: ", 5) == 0 && readU32Dec(l + 5, &v)) cur_.seq = v;
}

void HeldIndex::finish() { commitCur(); }

void HeldIndex::appended(uint32_t agent, uint32_t seq, int16_t lon) {
  in_rec_ = false;
  cur_ = E{agent, seq, lon};
  in_rec_ = true;
  commitCur();
}

bool HeldIndex::has(uint32_t agent, uint32_t seq) const {
  for (uint16_t i = 0; i < n_; ++i)
    if (e_[i].agent == agent && e_[i].seq == seq) return true;
  return false;
}

uint32_t HeldIndex::maxSeq(uint32_t agent) const {
  uint32_t m = 0;
  for (uint16_t i = 0; i < n_; ++i)
    if (e_[i].agent == agent && e_[i].seq > m) m = e_[i].seq;
  return m;
}

int16_t HeldIndex::nextOrdinal() const {
  return n_ ? ordinalAdd(e_[n_ - 1].lon, 1) : 0;
}

uint8_t HeldIndex::cuts(Cut* out, uint8_t max, bool force, uint16_t* covers) const {
  if (covers) *covers = 0;
  const uint16_t q = EPISODEDELIVERY_HELD_QUOTA;
  if (n_ <= q || (!force && n_ < q + EPISODEDELIVERY_HELD_SLACK) || !out || !max) return 0;
  const uint16_t want = n_ - q;
  uint8_t runs = 0;
  uint16_t covered = 0;
  for (uint16_t i = 0; i < want; ++i) {
    const int16_t lon = e_[i].lon;
    if (runs && out[runs - 1].lon_hi != 32767 && lon == out[runs - 1].lon_hi + 1) {
      out[runs - 1].lon_hi = lon;
    } else {
      if (runs == max) break;        // out of runs: cut what is covered, the rest next time
      out[runs++] = Cut{(int16_t)EPISODEDELIVERY_HELD_LANE, lon, lon};
    }
    ++covered;
  }
  if (covers) *covers = covered;
  return runs;
}

void HeldIndex::cutDone(uint16_t removed) {
  if (removed > n_) removed = n_;
  memmove(&e_[0], &e_[removed], (size_t)(n_ - removed) * sizeof(E));
  n_ -= removed;
}

// ---------------------------------------------------------------------------------------
// renderHeld
// ---------------------------------------------------------------------------------------
size_t renderHeld(const char* rec, size_t n, uint32_t agent, uint32_t seq, int16_t ord,
                  char* out, size_t cap) {
  if (out && cap) out[0] = '\0';
  if (!rec || !out || !n || ord < 0) return 0;
  // The header: the first line that starts with `@LAT`.
  size_t h = 0;
  while (h < n && !(rec[h] == '@' && (h == 0 || rec[h - 1] == '\n'))) ++h;
  if (h >= n) return 0;
  size_t he = h;
  while (he < n && rec[he] != '\n') ++he;
  if (he >= n) return 0;
  char hdr[96];
  const size_t hl = he - h < sizeof(hdr) - 1 ? he - h : sizeof(hdr) - 1;
  memcpy(hdr, rec + h, hl);
  hdr[hl] = '\0';
  int16_t lat, lon;
  if (!headerCoord(hdr, &lat, &lon) || lat != SEMANTIC_EPISODE_LANE || lon < 0 ||
      tierOf(lon) != TIER_LINK)
    return 0;
  const char* rest = strchr(hdr, ' ');            // ` | created:… | updated:…`
  // The body: exactly one episode fence, a `seq:` equal to `seq`, no second record.
  const char* body = rec + he + 1;
  const size_t bl = n - (he + 1);
  size_t fence_end = 0;                           // offset just past the fence line
  bool seq_ok = false;
  int fences = 0;
  for (size_t i = 0; i < bl;) {
    size_t j = i;
    while (j < bl && body[j] != '\n') ++j;
    char line[64];
    const size_t ll = j - i < sizeof(line) - 1 ? j - i : sizeof(line) - 1;
    memcpy(line, body + i, ll);
    line[ll] = '\0';
    if (line[0] == '@' && strncmp(line, "@LAT", 4) == 0) return 0;     // a second record
    if (isEpisodeFence(line)) {
      if (++fences > 1) return 0;
      fence_end = j < bl ? j + 1 : j;
    } else if (strncmp(line, "seq: ", 5) == 0) {
      uint32_t v;
      if (readU32Dec(line + 5, &v) && v == seq) seq_ok = true;
    }
    i = j + 1;
  }
  if (fences != 1 || !seq_ok || !agent) return 0;
  int w = snprintf(out, cap, "\n---\n\n@LAT%dLON%d%s\n", (int)EPISODEDELIVERY_HELD_LANE,
                   (int)ord, rest ? rest : "");
  if (w < 0 || (size_t)w >= cap) { out[0] = '\0'; return 0; }
  size_t len = (size_t)w;
  if (len + fence_end >= cap) { out[0] = '\0'; return 0; }
  memcpy(out + len, body, fence_end);
  len += fence_end;
  w = snprintf(out + len, cap - len, "held: 0x%08lx\n", (unsigned long)agent);
  if (w < 0 || (size_t)w >= cap - len) { out[0] = '\0'; return 0; }
  len += (size_t)w;
  // End the copy at the block's CLOSING fence: a Ttdb record span runs to the next header,
  // so it carries the next record's `---` separator, which is not this episode's text.
  size_t close_end = 0;
  for (size_t i = fence_end; i + 3 <= bl; ++i)
    if ((i == fence_end || body[i - 1] == '\n') && body[i] == '`' && body[i + 1] == '`' &&
        body[i + 2] == '`') {
      size_t j = i + 3;
      while (j < bl && body[j] != '\n') ++j;
      close_end = j < bl ? j + 1 : j;
    }
  if (!close_end) { out[0] = '\0'; return 0; }   // never closed: not an episode we can hold
  const size_t tail = close_end - fence_end;
  const bool needs_nl = !(tail ? body[fence_end + tail - 1] == '\n'
                               : out[len - 1] == '\n');
  if (len + tail + (needs_nl ? 1 : 0) + 1 > cap) { out[0] = '\0'; return 0; }
  memcpy(out + len, body + fence_end, tail);
  len += tail;
  if (len && out[len - 1] != '\n') out[len++] = '\n';
  out[len] = '\0';
  return len;
}

// ---------------------------------------------------------------------------------------
// SeqMap
// ---------------------------------------------------------------------------------------
void SeqMap::line(const char* l) {
  if (!l) return;
  int16_t lat, lon;
  if (l[0] == '@') {
    in_link_ = headerCoord(l, &lat, &lon) && lat == SEMANTIC_EPISODE_LANE && lon >= 0 &&
               tierOf(lon) == TIER_LINK;
    cur_lon_ = in_link_ ? lon : 0;
    return;
  }
  uint32_t v;
  if (in_link_ && strncmp(l, "seq: ", 5) == 0 && readU32Dec(l + 5, &v)) {
    add(cur_lon_, v);
    in_link_ = false;
  }
}

void SeqMap::add(int16_t lon, uint32_t seq) {
  if (!seq) return;
  for (uint8_t i = 0; i < n_; ++i)
    if (e_[i].lon == lon) { e_[i].seq = seq; return; }
  if (n_ == EPISODEDELIVERY_SEQMAP_CAP) {         // full: forget the oldest seq
    uint8_t lo = 0;
    for (uint8_t i = 1; i < n_; ++i)
      if (e_[i].seq < e_[lo].seq) lo = i;
    e_[lo] = e_[--n_];
  }
  e_[n_++] = E{lon, seq};
}

void SeqMap::remove(int16_t lon) {
  for (uint8_t i = 0; i < n_; ++i)
    if (e_[i].lon == lon) { e_[i] = e_[--n_]; return; }
}

bool SeqMap::firstInRange(uint32_t from, uint32_t to, uint32_t* seq, int16_t* lon) const {
  bool found = false;
  E best = {0, 0};
  for (uint8_t i = 0; i < n_; ++i) {
    const E& e = e_[i];
    if (e.seq < from || (to && e.seq > to)) continue;
    if (!found || e.seq < best.seq) { best = e; found = true; }
  }
  if (found) {
    if (seq) *seq = best.seq;
    if (lon) *lon = best.lon;
  }
  return found;
}

// ---------------------------------------------------------------------------------------
// the bar view
// ---------------------------------------------------------------------------------------
int64_t barLine(uint64_t frame, uint32_t bar_ms, int64_t n) {
  return (int64_t)frame + (int64_t)bar_ms * n;
}

int64_t completeBar(int64_t pulse_now, uint64_t frame, uint32_t bar_ms, uint32_t settle_ms) {
  if (!bar_ms) return -1;
  const int64_t t = pulse_now - (int64_t)settle_ms - (int64_t)frame;
  if (t < (int64_t)bar_ms) return -1;            // bar 1's line is F + bar
  return t / (int64_t)bar_ms;
}

BarView::BarView(Consolidator& c, uint64_t frame, int64_t lo, int64_t hi, uint32_t self)
    : c_(c), frame_(frame), lo_(lo), hi_(hi), self_(self) {}

void BarView::hold(uint32_t agent, uint32_t seq) {
  if (!seq) { ++unattributed_; return; }
  uint8_t i = 0;
  while (i < nh_ && h_[i].agent < agent) ++i;
  if (i < nh_ && h_[i].agent == agent) {
    BarHolds& h = h_[i];
    ++h.n;
    if (seq < h.lo) h.lo = seq;
    if (seq > h.hi) h.hi = seq;
    h.sum += seq;
    return;
  }
  if (nh_ == EPISODEDELIVERY_BAR_AGENTS) { ++unattributed_; return; }
  for (uint8_t k = nh_; k > i; --k) h_[k] = h_[k - 1];
  h_[i] = BarHolds{agent, 1, seq, seq, seq};
  ++nh_;
}

void BarView::close() {
  if (started_) {
    c_.endEpisode(Consolidator::KEEPING);
    if (lat_ == EPISODEDELIVERY_HELD_LANE) ++held_;
    else ++own_;
    hold(lat_ == EPISODEDELIVERY_HELD_LANE ? agent_ : self_, seq_);
  }
  in_block_ = decided_ = started_ = false;
  agent_ = seq_ = 0;
}

void BarView::line(const char* l) {
  if (!l) return;
  int16_t lat, lon;
  if (l[0] == '@') {
    close();
    accept_ = headerCoord(l, &lat, &lon) &&
              ((lat == SEMANTIC_EPISODE_LANE && lon >= 0 && tierOf(lon) == TIER_LINK) ||
               lat == EPISODEDELIVERY_HELD_LANE);
    lat_ = accept_ ? lat : 0;
    return;
  }
  if (!accept_) return;
  if (isFence(l)) {
    if (in_block_) { close(); accept_ = false; return; }   // one block per record
    if (isEpisodeFence(l)) in_block_ = true;
    return;
  }
  if (!in_block_) return;
  const char* s = skipWs(l);
  uint32_t v;
  if (lat_ == EPISODEDELIVERY_HELD_LANE && !agent_ && readHeldAgent(s, &v)) { agent_ = v; return; }
  if (!seq_ && strncmp(s, "seq: ", 5) == 0 && readU32Dec(s + 5, &v)) { seq_ = v; return; }
  if (!decided_ && strncmp(s, "at:", 3) == 0) {
    decided_ = true;
    const At a = parseAt(s);
    if (a.bounded && a.has_frame && a.frame == frame_ &&
        a.t_ms - (int64_t)a.bound_ms >= lo_ && a.t_ms + (int64_t)a.bound_ms < hi_) {
      c_.beginEpisode();
      started_ = true;
    }
    return;
  }
  if (started_ && strncmp(s, "percept:", 8) == 0) c_.feedLine(s);
}

void BarView::finish() {
  close();
  accept_ = false;
}

BarDigest barDigest(const Consolidator& c) {
  BarDigest d = {0, 0};
  for (size_t i = 0; i < c.termCount(); ++i) {
    const Term* t = c.term(i);
    char b[128];
    if (!t || !c.beliefLine(*t, b, sizeof(b))) continue;
    uint32_t h = 0x811c9dc5u;
    for (const char* p = t->subject; *p; ++p) h = (h ^ (uint8_t)*p) * 0x01000193u;
    h = (h ^ (uint8_t)' ') * 0x01000193u;
    for (const char* p = b; *p; ++p) h = (h ^ (uint8_t)*p) * 0x01000193u;
    d.sum += h;
    ++d.terms;
  }
  return d;
}

// ---------------------------------------------------------------------------------------
// the BAR record
// ---------------------------------------------------------------------------------------
size_t renderBar(char* out, size_t cap, int16_t ord, uint64_t frame, int64_t bar,
                 const BarView& v, const BarDigest& d, int64_t settled_ms) {
  if (!out || !cap) return 0;
  out[0] = '\0';
  int k = snprintf(out, cap,
                   "@LAT%dLON%d | created:0 | updated:0\n\n"
                   "**BAR** frame:%llu bar:%lld own:%u held:%u terms:%u digest:0x%08lx "
                   "settled_ms:%lld\n",
                   EPISODEDELIVERY_BAR_LANE, (int)ord, (unsigned long long)frame, (long long)bar,
                   (unsigned)v.own(), (unsigned)v.held(), (unsigned)d.terms,
                   (unsigned long)d.sum, (long long)settled_ms);
  if (k < 0 || (size_t)k >= cap) { out[0] = '\0'; return 0; }
  size_t n = (size_t)k;
  for (uint8_t i = 0; i < v.holdsCount(); ++i) {
    const BarHolds& h = v.holds(i);
    k = snprintf(out + n, cap - n, "**HOLDS** agent:0x%08lx n:%u lo:%lu hi:%lu sum:%lu\n",
                 (unsigned long)h.agent, (unsigned)h.n, (unsigned long)h.lo,
                 (unsigned long)h.hi, (unsigned long)h.sum);
    if (k < 0 || (size_t)k >= cap - n) { out[0] = '\0'; return 0; }
    n += (size_t)k;
  }
  return n;
}

// Decimal digits -> value; *end past them. No sscanf: it pulls newlib's scanf (~10 KB) into
// an image the V4s cannot spare.
static bool readDec64(const char* p, uint64_t* v, const char** end) {
  uint64_t x = 0;
  const char* s = p;
  while (*p >= '0' && *p <= '9') {
    if (x > (UINT64_MAX - 9) / 10) return false;
    x = x * 10 + (uint64_t)(*p++ - '0');
  }
  if (p == s) return false;
  *v = x;
  *end = p;
  return true;
}

static bool readBarKey(const char* l, uint64_t* frame, int64_t* bar) {
  if (strncmp(l, "**BAR** frame:", 14) != 0) return false;
  const char* p;
  uint64_t f, b;
  if (!readDec64(l + 14, &f, &p) || strncmp(p, " bar:", 5) != 0) return false;
  const bool neg = p[5] == '-';
  if (!readDec64(p + 5 + (neg ? 1 : 0), &b, &p) || b > (uint64_t)INT64_MAX) return false;
  *frame = f;
  *bar = neg ? -(int64_t)b : (int64_t)b;
  return true;
}

void BarIndex::line(const char* l) {
  if (!l) return;
  int16_t lat, lon;
  if (l[0] == '@') {
    in_rec_ = headerCoord(l, &lat, &lon) && lat == EPISODEDELIVERY_BAR_LANE;
    cur_lon_ = in_rec_ ? lon : 0;
    return;
  }
  uint64_t f;
  int64_t b;
  if (in_rec_ && readBarKey(l, &f, &b)) {
    appended(f, b, cur_lon_);
    in_rec_ = false;
  }
}

void BarIndex::appended(uint64_t frame, int64_t bar, int16_t lon) {
  if (n_ == EPISODEDELIVERY_BAR_CAP) {          // not expected: cut keeps it <= QUOTA+SLACK
    for (uint16_t i = 1; i < n_; ++i) e_[i - 1] = e_[i];
    --n_;
  }
  e_[n_++] = E{frame, bar, lon};
}

bool BarIndex::has(uint64_t frame, int64_t bar) const {
  for (uint16_t i = 0; i < n_; ++i)
    if (e_[i].frame == frame && e_[i].bar == bar) return true;
  return false;
}

int16_t BarIndex::nextOrdinal() const {
  return n_ ? ordinalAdd(e_[n_ - 1].lon, 1) : 0;
}

bool BarIndex::cut(Cut* out, bool force, uint16_t* covers) const {
  if (covers) *covers = 0;
  const uint16_t q = EPISODEDELIVERY_BAR_QUOTA;
  if (!out || n_ <= q || (!force && n_ < q + EPISODEDELIVERY_BAR_SLACK)) return false;
  const uint16_t want = n_ - q;
  uint16_t covered = 1;
  *out = Cut{(int16_t)EPISODEDELIVERY_BAR_LANE, e_[0].lon, e_[0].lon};
  while (covered < want && out->lon_hi != 32767 && e_[covered].lon == out->lon_hi + 1) {
    out->lon_hi = e_[covered].lon;
    ++covered;
  }
  if (covers) *covers = covered;
  return true;
}

void BarIndex::cutDone(uint16_t removed) {
  if (removed > n_) removed = n_;
  for (uint16_t i = removed; i < n_; ++i) e_[i - removed] = e_[i];
  n_ -= removed;
}

}  // namespace semantic
