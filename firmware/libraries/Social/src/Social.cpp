#include "Social.h"

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
      return &peers_[i];
    }
  // Full: the longest-unheard goes. ⚠ Note this is eviction for SPACE, never for age —
  // a faded peer that is still the freshest thing in the table stays, because "we have
  // not heard from anyone in a while" must not empty the fleet's picture of itself.
  uint8_t oldest = 0;
  for (uint8_t i = 1; i < SOCIAL_MAX_PEERS; ++i)
    if ((uint32_t)(now_ms - peers_[i].last_ms) > (uint32_t)(now_ms - peers_[oldest].last_ms))
      oldest = i;
  peers_[oldest] = Peer();
  peers_[oldest].node = node;
  peers_[oldest].heard = true;
  peers_[oldest].last_ms = now_ms;
  return &peers_[oldest];
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
  return !known;
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
