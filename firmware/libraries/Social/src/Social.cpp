#include "Social.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TraceField.h"   // tracefield::decayed — ONE tested implementation of the decay
#include "Sid.h"          // stable record identity (TTDB-RFC-0010 §4)
#include "TtdbParse.h"    // ttdbHeaderSid — the reader reads the id the writer wrote

namespace social {

static const char* kCapNames[CAP_COUNT] = {
    "mic", "spk", "imu", "gps", "wifi", "ble", "lora", "disp",
    "keys", "store", "batt", "temp", "wall", "cond", "brdg",
};

const char* capName(uint8_t bit) {
  // ⚠ An unknown bit renders as `b<n>`, never as blank. A peer running newer firmware has
  // a capability we have no word for, and "a capability I cannot name" is a materially
  // different report from "no capability".
  static char unnamed[6];
  if (bit < CAP_COUNT) return kCapNames[bit];
  unnamed[0] = 'b';
  if (bit < 10) { unnamed[1] = (char)('0' + bit); unnamed[2] = 0; }
  else { unnamed[1] = (char)('0' + bit / 10); unnamed[2] = (char)('0' + bit % 10); unnamed[3] = 0; }
  return unnamed;
}

const char* statusGlyph(Status s) {
  switch (s) {
    case ST_UNKNOWN:   return "?";   // never told us
    case ST_ABSENT:    return ".";   // told us, hasn't got it
    case ST_DECLARED:  return "d";
    case ST_VERIFIED:  return "v";
    case ST_EXERCISED: return "X";
    default:           return "?";
  }
}

const char* poseName(PoseCeiling p) {
  switch (p) {
    case POSE_SHAPE_ONLY:  return "shape only";
    case POSE_TRANSLATION: return "<=translation";
    case POSE_ROTATION:    return "<=rotation";
    case POSE_FULL:        return "<=full";
    default:               return "?";
  }
}

void Table::begin(uint32_t self_node, uint16_t declared) {
  self_ = Peer();
  self_.node = self_node;
  self_.declared = declared;
  self_.heard = true;
  self_.spoke = true;   // we have certainly told ourselves
  for (uint8_t i = 0; i < SOCIAL_MAX_PEERS; ++i) peers_[i] = Peer();
  cursor_ = 0;
  stale_reports_ = 0;
  last_stale_from_ = 0;
}

bool Table::verify(uint16_t bits) {
  // Clamped to declared: a board cannot verify a peripheral it never claimed. Silently
  // dropping the excess is right — the alternative is a table that reports hardware the
  // build does not know about, which is the failure this whole tier exists to prevent.
  const uint16_t next = (uint16_t)(self_.verified | (bits & self_.declared));
  if (next == self_.verified) return false;
  self_.verified = next;
  ++self_.epoch;
  return true;
}

bool Table::exercise(uint16_t bits) {
  // Exercising implies verified: a tier that produced a percept has, by construction,
  // found its peripheral. So this promotes through both levels in one call rather than
  // requiring the sketch to remember to call verify() first — a rule that is enforced is
  // cheaper than a rule that is documented.
  const uint16_t add = (uint16_t)(bits & self_.declared);
  const uint16_t nv = (uint16_t)(self_.verified | add);
  const uint16_t nx = (uint16_t)(self_.exercised | add);
  if (nv == self_.verified && nx == self_.exercised) return false;
  self_.verified = nv;
  self_.exercised = nx;
  ++self_.epoch;
  return true;
}

bool Table::refreshWall(bool have_wall) {
  if (!(self_.declared & CAP_WALL)) return false;
  const bool now_set = (self_.exercised & CAP_WALL) != 0;
  if (now_set == have_wall) return false;
  if (have_wall) {
    self_.verified  = (uint16_t)(self_.verified | CAP_WALL);
    self_.exercised = (uint16_t)(self_.exercised | CAP_WALL);
  } else {
    // ⚠ The one capability that can be LOST while the hardware is fine. A stream that had
    // a wall anchor and no longer does is a real state (the laptop went away and the node
    // reconciled onto a stream with no date), and reporting it as still-dated would be a
    // fabricated id in a different costume.
    self_.verified  = (uint16_t)(self_.verified & ~(uint16_t)CAP_WALL);
    self_.exercised = (uint16_t)(self_.exercised & ~(uint16_t)CAP_WALL);
  }
  ++self_.epoch;
  return true;
}

Peer* Table::slot(uint32_t node, uint32_t now_ms) {
  if (!node || node == self_.node) return nullptr;
  for (uint8_t i = 0; i < SOCIAL_MAX_PEERS; ++i)
    if (peers_[i].heard && peers_[i].node == node) return &peers_[i];
  for (uint8_t i = 0; i < SOCIAL_MAX_PEERS; ++i)
    if (!peers_[i].heard) {
      peers_[i] = Peer();
      peers_[i].node = node;
      peers_[i].heard = true;
      peers_[i].last_ms = now_ms;
      field_dirty_ = true;   // a persisted lane without this peer is out of date
      return &peers_[i];
    }
  // Full: RFC-0010 §5.3 reclaim — the LOWEST DECAYED co-presence goes, ties resolved to
  // the oldest trace. ⚠ Still eviction for SPACE, never for age: a faded peer that is
  // nonetheless the strongest trace in the table stays, because "we have not heard from
  // anyone in a while" must not empty the fleet's picture of itself. No @LAT100 boundary
  // is written — under KEY naming there is nothing to re-point (§5.3's own rule).
  uint8_t low = 0;
  uint8_t low_s = copresenceAt(peers_[0], now_ms);
  for (uint8_t i = 1; i < SOCIAL_MAX_PEERS; ++i) {
    const uint8_t s = copresenceAt(peers_[i], now_ms);
    if (s < low_s ||
        (s == low_s && (uint32_t)(now_ms - peers_[i].copre_last_ms) >
                           (uint32_t)(now_ms - peers_[low].copre_last_ms))) {
      low = i;
      low_s = s;
    }
  }
  ++reclaims_;
  last_reclaimed_ = peers_[low].node;
  field_dirty_ = true;
  peers_[low] = Peer();
  peers_[low].node = node;
  peers_[low].heard = true;
  peers_[low].last_ms = now_ms;
  return &peers_[low];
}

const Peer* Table::slotConst(uint32_t node) const {
  if (node == self_.node) return &self_;
  for (uint8_t i = 0; i < SOCIAL_MAX_PEERS; ++i)
    if (peers_[i].heard && peers_[i].node == node) return &peers_[i];
  return nullptr;
}

bool Table::sawNode(uint32_t node, uint32_t now_ms) {
  const bool known = slotConst(node) != nullptr && node != self_.node;
  Peer* p = slot(node, now_ms);
  if (!p) return false;
  p->last_ms = now_ms;
  // Presence IS co-presence: every reception from a node is a deposit into its trace.
  // ⚠ This is the ONLY deposit site. ingest() does not deposit again — a HELLO carrying
  // a digest already queued a presence entry for the same beacon, and depositing twice
  // would double-count every capability-speaking peer against every silent one.
  reinforce(*p, now_ms);
  return !known;
}

void Table::reinforce(Peer& p, uint32_t now_ms) {
  // Decay to now FIRST, so repeated deposits accumulate against the current value and
  // not a stale one — the same order TraceField::deposit uses, for the same reason.
  const uint16_t s = (uint16_t)tracefield::decayed(p.copre, p.copre_last_ms, now_ms,
                                                  SOCIAL_COPRE_HALF_LIFE_MS)
                     + SOCIAL_COPRE_DEPOSIT;
  p.copre = (s > 255) ? 255 : (uint8_t)s;
  p.copre_last_ms = now_ms;
  p.age_unknown = false;   // a live reception dates the trace again
  if (p.reinforced < 0xFFFF) ++p.reinforced;
}

uint8_t Table::copresenceAt(const Peer& p, uint32_t now_ms) const {
  return tracefield::decayed(p.copre, p.copre_last_ms, now_ms, SOCIAL_COPRE_HALF_LIFE_MS);
}

uint8_t Table::ingest(uint32_t from, const uint8_t* d, size_t len, uint32_t now_ms) {
  if (!d || len < DIGEST_HDR) return 0;
  if (d[0] != DIGEST_MAGIC || d[1] != DIGEST_VERSION) return 0;
  const uint8_t n = d[9];
  if (n > SOCIAL_DIGEST_PEERS) return 0;                       // malformed, not truncated
  if (len < DIGEST_HDR + (size_t)n * DIGEST_PEER) return 0;    // never read past the end

  uint8_t ev = 0;
  Peer* p = slot(from, now_ms);
  if (!p) return 0;
  if (!p->spoke) ev |= ING_NEW_PEER;

  const uint16_t dec = (uint16_t)(d[2] | (d[3] << 8));
  const uint16_t ver = (uint16_t)(d[4] | (d[5] << 8));
  const uint16_t exe = (uint16_t)(d[6] | (d[7] << 8));
  if (p->spoke && (dec != p->declared || ver != p->verified || exe != p->exercised))
    ev |= ING_CAPS_CHANGED;
  // A persisted @LAT101 record states the masks and the epoch, so any change to them —
  // including the first digest from a peer we only knew as present — owes a rewrite.
  if (!p->spoke || (ev & ING_CAPS_CHANGED) || p->epoch != d[8]) field_dirty_ = true;

  p->declared  = dec;
  // ⚠ Clamp the peer's own claims the same way we clamp ours. A peer whose masks disagree
  // with each other is either mid-upgrade or corrupt, and the safe reading is the LOWER
  // one: reporting a capability as exercised on the strength of a bit that contradicts its
  // own declaration is exactly the "declared rendered as has" failure, arriving over the
  // air instead of from a build.
  p->verified  = (uint16_t)(ver & dec);
  p->exercised = (uint16_t)(exe & ver & dec);
  p->epoch     = d[8];
  p->last_ms   = now_ms;
  p->spoke     = true;

  // Their picture of US. Serial-number arithmetic, not `<`: epochs wrap at 255 and a plain
  // comparison strands the pair in different eras forever with no way back — the same trap
  // TraceField's generation byte has, solved the same way.
  const uint16_t us = shortId(self_.node);
  for (uint8_t i = 0; i < n; ++i) {
    const uint8_t* e = d + DIGEST_HDR + (size_t)i * DIGEST_PEER;
    const uint16_t id = (uint16_t)(e[0] | (e[1] << 8));
    if (id != us) continue;
    if ((int8_t)(self_.epoch - e[2]) > 0) {
      ++stale_reports_;
      last_stale_from_ = from;
      ev |= ING_THEY_ARE_STALE_ABOUT_US;
    }
    break;
  }
  return ev;
}

size_t Table::buildDigest(uint8_t* p, size_t cap, uint32_t now_ms) {
  (void)now_ms;
  if (!p || cap < DIGEST_HDR) return 0;

  // How many peer entries actually fit, bounded by both the buffer and the wire cap.
  uint8_t room = (uint8_t)((cap - DIGEST_HDR) / DIGEST_PEER);
  if (room > SOCIAL_DIGEST_PEERS) room = SOCIAL_DIGEST_PEERS;

  p[0] = DIGEST_MAGIC;
  p[1] = DIGEST_VERSION;
  p[2] = (uint8_t)(self_.declared & 0xFF);
  p[3] = (uint8_t)(self_.declared >> 8);
  p[4] = (uint8_t)(self_.verified & 0xFF);
  p[5] = (uint8_t)(self_.verified >> 8);
  p[6] = (uint8_t)(self_.exercised & 0xFF);
  p[7] = (uint8_t)(self_.exercised >> 8);
  p[8] = self_.epoch;

  // Round-robin from `cursor_` so that with more peers than slots every one is eventually
  // reported. Only peers we have actually HEARD FROM in this protocol are listed: an epoch
  // of 0 for a node that has never spoken would assert we hold a stale view of it, which
  // would make our silence look like disagreement.
  uint8_t written = 0;
  for (uint8_t k = 0; k < SOCIAL_MAX_PEERS && written < room; ++k) {
    const uint8_t i = (uint8_t)((cursor_ + k) % SOCIAL_MAX_PEERS);
    if (!peers_[i].heard || !peers_[i].spoke) continue;
    uint8_t* e = p + DIGEST_HDR + (size_t)written * DIGEST_PEER;
    const uint16_t id = shortId(peers_[i].node);
    e[0] = (uint8_t)(id & 0xFF);
    e[1] = (uint8_t)(id >> 8);
    e[2] = peers_[i].epoch;
    ++written;
  }
  if (written) cursor_ = (uint8_t)((cursor_ + written) % SOCIAL_MAX_PEERS);
  p[9] = written;
  return DIGEST_HDR + (size_t)written * DIGEST_PEER;
}

uint8_t Table::peerCount() const {
  uint8_t n = 0;
  for (uint8_t i = 0; i < SOCIAL_MAX_PEERS; ++i) if (peers_[i].heard) ++n;
  return n;
}

const Peer* Table::peerAt(uint8_t i) const {
  uint8_t n = 0;
  for (uint8_t k = 0; k < SOCIAL_MAX_PEERS; ++k) {
    if (!peers_[k].heard) continue;
    if (n == i) return &peers_[k];
    ++n;
  }
  return nullptr;
}

const Peer* Table::find(uint32_t node) const { return slotConst(node); }

bool Table::faded(const Peer& p, uint32_t now_ms) const {
  return (uint32_t)(now_ms - p.last_ms) > SOCIAL_PEER_FADE_MS;
}

Status Table::statusOf(uint32_t node, uint16_t bit) const {
  const Peer* p = slotConst(node);
  if (!p || !p->spoke) return ST_UNKNOWN;
  if (p->exercised & bit) return ST_EXERCISED;
  if (p->verified & bit)  return ST_VERIFIED;
  if (p->declared & bit)  return ST_DECLARED;
  return ST_ABSENT;
}

uint8_t Table::quorum(uint16_t bit) const {
  uint8_t n = (self_.exercised & bit) ? 1 : 0;
  for (uint8_t i = 0; i < SOCIAL_MAX_PEERS; ++i)
    if (peers_[i].heard && peers_[i].spoke && (peers_[i].exercised & bit)) ++n;
  return n;
}

uint8_t Table::declaredQuorum(uint16_t bit) const {
  uint8_t n = (self_.declared & bit) ? 1 : 0;
  for (uint8_t i = 0; i < SOCIAL_MAX_PEERS; ++i)
    if (peers_[i].heard && peers_[i].spoke && (peers_[i].declared & bit)) ++n;
  return n;
}

uint8_t Table::unknownPeers() const {
  uint8_t n = 0;
  for (uint8_t i = 0; i < SOCIAL_MAX_PEERS; ++i)
    if (peers_[i].heard && !peers_[i].spoke) ++n;
  return n;
}

// ---------------------------------------------------------------------------
// The @LAT101 field — persistence (TTDB-RFC-0010 §5, stage 3)
// ---------------------------------------------------------------------------

bool Table::persistDue(uint32_t now_ms) const {
  const uint32_t gap = now_ms - last_persist_ms_;
  if (field_dirty_ && gap >= SOCIAL_PERSIST_MIN_GAP_MS) return true;
  if (gap < SOCIAL_PERSIST_HEARTBEAT_MS) return false;
  // Heartbeat: only if something was actually reinforced since the last persist — a
  // node alone in a field writes nothing, forever, which is §5.1's contract on flash.
  for (uint8_t i = 0; i < SOCIAL_MAX_PEERS; ++i)
    if (peers_[i].heard && peers_[i].reinforced) return true;
  return false;
}

void Table::notePersisted(uint32_t now_ms) {
  field_dirty_ = false;
  last_persist_ms_ = now_ms;
  for (uint8_t i = 0; i < SOCIAL_MAX_PEERS; ++i) peers_[i].reinforced = 0;
}

size_t Table::peerKey(char* out, size_t cap, uint32_t node) {
  const int m = snprintf(out, cap, "node:0x%08lx", (unsigned long)node);
  if (m <= 0 || (size_t)m >= cap) return 0;
  return (size_t)m;
}

size_t Table::buildPeerRecord(char* out, size_t cap, uint8_t i, int lon, uint32_t t_sec,
                              const timestream::Stamp& ts, uint32_t now_ms,
                              uint32_t* sid_out) {
  const Peer* p = peerAt(i);
  if (!p || !out) return 0;

  char stamp[64];
  if (!timestream::buildStamp(stamp, sizeof(stamp), ts)) return 0;

  // ⚠ The stamp gets its own line, which puts `t_ms:` at a LINE START. That is what lets
  // the reader disambiguate it from `last_ms:` — whose tail is literally `t_ms:` — by
  // boundary rather than by luck. Same needle family as `prev_stream:` inside `stream:`.
  const int m = snprintf(
      out, cap,
      "\n---\n\n@LAT%dLON%d | sid:00000000 | created:%lu | updated:%lu |\n"
      "**PEER** node:0x%08lx spoke:%d declared:0x%04x verified:0x%04x "
      "exercised:0x%04x cap_epoch:%u\n"
      "**TRACE** copresence:%u half_life_ms:%lu reinforced:%u last_ms:%lu\n"
      "%s\n",
      SOCIAL_FIELD_LANE, lon, (unsigned long)t_sec, (unsigned long)t_sec,
      (unsigned long)p->node, p->spoke ? 1 : 0, p->declared, p->verified, p->exercised,
      p->epoch,
      copresenceAt(*p, now_ms), (unsigned long)SOCIAL_COPRE_HALF_LIFE_MS, p->reinforced,
      (unsigned long)p->copre_last_ms, stamp);
  if (m <= 0 || (size_t)m >= cap) return 0;   // whole record or nothing — never truncate

  char key[24];
  if (!peerKey(key, sizeof(key), p->node)) return 0;
  const uint32_t s =
      sid::stampKey(out, (size_t)m, self_.node, SOCIAL_FIELD_LANE, key);
  if (!s) return 0;   // an unstamped FIELD record has no identity; refuse to write it
  if (sid_out) *sid_out = s;
  return (size_t)m;
}

// Bounded token find requiring a boundary before the needle: start of buffer, newline,
// space, or '|'. ⚠ Exists because `last_ms:` CONTAINS `t_ms:` — a bare search returns
// the wrong field with both sides individually looking correct.
static const char* findTok(const char* rec, size_t len, const char* tok) {
  const size_t tl = strlen(tok);
  if (tl == 0 || len < tl) return nullptr;
  for (size_t i = 0; i + tl <= len; ++i) {
    if (memcmp(rec + i, tok, tl) != 0) continue;
    if (i == 0) return rec + i;
    const char b = rec[i - 1];
    if (b == '\n' || b == ' ' || b == '|') return rec + i;
  }
  return nullptr;
}

static bool tokU32(const char* rec, size_t len, const char* tok, uint32_t& out, int base) {
  const char* p = findTok(rec, len, tok);
  if (!p) return false;
  out = (uint32_t)strtoul(p + strlen(tok), nullptr, base);
  return true;
}

bool Table::parsePeerRecord(const char* rec, size_t len, PeerRecord& out) {
  if (!rec || !len) return false;
  out = PeerRecord();
  if (!findTok(rec, len, "**PEER** ")) return false;

  uint32_t v = 0;
  if (!tokU32(rec, len, "node:0x", v, 16) || !v) return false;
  out.node = v;
  if (tokU32(rec, len, "spoke:", v, 10)) out.spoke = v != 0;
  if (tokU32(rec, len, "declared:0x", v, 16)) out.declared = (uint16_t)v;
  if (tokU32(rec, len, "verified:0x", v, 16)) out.verified = (uint16_t)v;
  if (tokU32(rec, len, "exercised:0x", v, 16)) out.exercised = (uint16_t)v;
  if (tokU32(rec, len, "cap_epoch:", v, 10)) out.cap_epoch = (uint8_t)v;
  if (tokU32(rec, len, "copresence:", v, 10)) out.copresence = (uint8_t)(v > 255 ? 255 : v);
  if (tokU32(rec, len, "half_life_ms:", v, 10)) out.half_life_ms = v;
  if (tokU32(rec, len, "reinforced:", v, 10)) out.reinforced = (uint16_t)v;
  if (tokU32(rec, len, "stream:0x", v, 16)) out.stream = v;
  if (tokU32(rec, len, "wall:", v, 10)) out.wall = (int)v;
  // ⚠ `t_ms:` LAST and boundary-checked — findTok is what keeps `last_ms:` from
  // answering for it. 64-bit, so not through tokU32.
  const char* t = findTok(rec, len, "t_ms:");
  if (t) out.t_ms = (uint64_t)strtoull(t + 5, nullptr, 10);

  uint32_t hs = 0;
  // ttdbHeaderSid bounds itself to the header line, wherever the record block starts.
  if (ttdbHeaderSid(rec, hs)) { out.sid = hs; out.has_sid = true; }
  return true;
}

bool Table::loadPeer(const PeerRecord& r, uint32_t now_ms) {
  if (!r.node || r.node == self_.node) return false;
  // A reload is not a material change: whatever this call does to the table, the lane
  // already says it, so it must not schedule a rewrite of identical content. Restore
  // the entry value rather than clearing — dirt from a REAL change survives a load.
  const bool dirty_at_entry = field_dirty_;

  // §5.4: this trace's age is UNKNOWN — setup() runs before the stream listen window,
  // so nothing at load time can relate the record's stamp to the current clock. It MUST
  // NOT be treated as fully decayed (that is "faded rendered as absent"), and trusting
  // the stored strength would overstate it; so it re-enters clamped and marked.
  uint8_t strength = r.copresence;
  if (strength > SOCIAL_COPRE_UNKNOWN_AGE) strength = SOCIAL_COPRE_UNKNOWN_AGE;

  // Never let flash overwrite what the radio already said: a peer that has spoken THIS
  // boot outranks its own gravestone. Only top up the trace (max-merge, the TraceField
  // rule) and fill capability masks a silent peer has not yet given us.
  Peer* p = slot(r.node, now_ms);
  if (!p) return false;
  const bool live = p->spoke || p->copre > 0;
  if (!p->spoke && r.spoke) {
    p->declared  = r.declared;
    // Re-clamp exactly as ingest() clamps a digest: flash is one more untrusted mouth.
    p->verified  = (uint16_t)(r.verified & r.declared);
    p->exercised = (uint16_t)(r.exercised & p->verified);
    p->epoch     = r.cap_epoch;
    p->spoke     = true;
  }
  if (copresenceAt(*p, now_ms) < strength) {
    p->copre = strength;
    p->copre_last_ms = now_ms;
    p->age_unknown = true;
  }
  if (!live) {
    // FADED until actually heard: last_ms is set one fade period into the past, which
    // modular arithmetic keeps exact even when it wraps below zero near boot.
    p->last_ms = now_ms - (SOCIAL_PEER_FADE_MS + 1);
    p->reinforced = 0;
  }
  field_dirty_ = dirty_at_entry;
  return true;
}

PoseCeiling Table::poseCeiling() const {
  // ⚠ Counted on EXERCISED, not declared. A GPS that has never returned a fix pins
  // nothing, and the T-Deck spent a bring-up session proving a declared-and-wired GPS can
  // sit at no-fix indefinitely indoors. Counting declarations here would report the fleet
  // as fully located from a cold boot in a basement.
  // ⚠ And counted as CONCURRENT fixes: one roaming node visiting three places gets to the
  // same answer over time, which this cannot see. See the note on PoseCeiling — this is a
  // ceiling for the instant and a floor for a roamer, and the render must not collapse the
  // two into a single confident claim about where anybody is.
  const uint8_t g = quorum(CAP_GPS);
  if (g >= 3) return POSE_FULL;
  if (g == 2) return POSE_ROTATION;
  if (g == 1) return POSE_TRANSLATION;
  return POSE_SHAPE_ONLY;
}

}  // namespace social
