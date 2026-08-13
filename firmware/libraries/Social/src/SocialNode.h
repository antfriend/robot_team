// SocialNode.h — the Arduino glue for the default network's capability table.
// ONE copy, both handhelds — same shape as TimeStreamNode.h, LaneGenNode.h and
// TraceFieldNode.h, and for the same reason: the portable logic lives in Social.cpp where
// a native test can reach it, and everything needing `Serial` or a radio callback is here.
//
// ⚠ THE RECV CALLBACK MUST NEVER TOUCH `Table`. `ingest()` walks and mutates a peer array
// and can evict a slot; a HELLO arriving mid-`buildDigest` would ship a digest built from
// two different tables. So the callback COPIES the bytes into a ring and `service()` —
// called from loop() — is the sole mutator. This is the rule `TimeStreamNode` follows for
// anchors, where a torn write moved a node's clock by seven weeks. Here the worst case is
// milder (a peer row briefly describing the wrong node) but the rule is cheaper to keep
// than to re-derive per library.
//
// ⚠ Unlike a trace digest, a capability digest is MEANINGLESS WITHOUT ITS SENDER: the node
// id lives in the signed toot header, not in the payload. So the ring carries `(src,
// bytes)` pairs, and `queueDigest` takes the src explicitly rather than the sketch being
// trusted to remember which digest came from whom.
#pragma once
#include <Arduino.h>
#include "Social.h"
#include "TTDB.h"   // the @LAT101 field's durable shadow lives in the node's TTDB

#ifndef SOCIAL_QUEUE
#define SOCIAL_QUEUE 6
#endif

class SocialNode {
 public:
  void begin(uint32_t self_node, uint16_t declared) { t_.begin(self_node, declared); }

  // ---- callback side: copy only, never ingest --------------------------------------
  // `p` points at the digest — the sketch does the offset arithmetic past the time-stream
  // anchor and the trace digest, so this library keeps its zero dependencies on either.
  void queueDigest(uint32_t from, const uint8_t* p, size_t n) {
    if (!from || !p || n < social::DIGEST_HDR) return;
    if (p[0] != social::DIGEST_MAGIC) return;          // cheap reject before the copy
    if (n > social::DIGEST_LEN_MAX) n = social::DIGEST_LEN_MAX;
    push(from, p, n);
  }

  // Presence with no capability claim — a node heard on the mesh that has told us nothing
  // about itself. Queued, NOT applied.
  //
  // ⚠ A FIRST CUT CALLED `Table::sawNode` DIRECTLY FROM THE CALLBACK, reasoning that it
  // "only stamps a slot". That was wrong and it is the exact rule this file opens with:
  // `sawNode` reaches `Table::slot()`, which on a full table EVICTS the longest-unheard
  // peer and rewrites that entry. A callback doing that while `service()` is mid-`ingest`
  // on the same array is a torn write — one peer's capabilities landing on another peer's
  // row. Found by thinking through what the hardware would print, not by the native tests,
  // which cannot express "two contexts touch this at once".
  void queuePresence(uint32_t from) { push(from, nullptr, 0); }

  // ---- loop side: the only mutator -------------------------------------------------
  // Drains the queue. Logging is CHANGE-ONLY: a digest arrives every 2 s per peer and says
  // nothing new almost every time, so printing each one would bury the interesting event
  // and cost more CDC time than the parse.
  void service(uint32_t now_ms) {
    // Our OWN promotions, logged on change. `verify`/`exercise` are called straight on
    // `table()` by whichever tier earned them, so watching the epoch catches every one
    // regardless of the caller — and without it the three-level status is invisible until
    // somebody presses a key, which on a headless serial log means invisible. This is the
    // same argument as the trace field's `[field] armed:` line: the firmware saying so.
    if (t_.epoch() != last_self_epoch_) {
      last_self_epoch_ = t_.epoch();
      Serial.printf("[social] self ep %u: %s\n", t_.epoch(), capsLine(t_.selfNode()));
    }
    while (tail_ != head_) {
      if (len_[tail_] == 0) {
        // Presence only. Logged on the transition to known-present because it is the
        // UNKNOWN-vs-ABSENT case made visible: the three V4s speak neither this protocol
        // nor the field's, and a fleet table that showed them as capability-less would
        // report the LoRa spine as having no radio.
        if (t_.sawNode(src_[tail_], now_ms))
          // ⚠ ASCII only inside a Serial.printf. A UTF-8 em-dash here arrived on the CDC
          // console as a replacement character — a log line meant for a person, damaged.
          // (Comments may use whatever they like; the wire may not.)
          Serial.printf("[social] 0x%03lx present, no digest: capabilities UNKNOWN "
                        "(not absent)\n", (unsigned long)src_[tail_]);
        tail_ = (uint8_t)((tail_ + 1) % SOCIAL_QUEUE);
        continue;
      }
      const uint8_t ev = t_.ingest(src_[tail_], q_[tail_], len_[tail_], now_ms);
      if (ev & social::Table::ING_NEW_PEER)
        Serial.printf("[social] 0x%03lx joined: %s\n",
                      (unsigned long)src_[tail_], capsLine(src_[tail_]));
      else if (ev & social::Table::ING_CAPS_CHANGED)
        Serial.printf("[social] 0x%03lx now: %s\n",
                      (unsigned long)src_[tail_], capsLine(src_[tail_]));
      if (ev & social::Table::ING_THEY_ARE_STALE_ABOUT_US)
        // The falsifier's instrument firing. At one radio hop this should never print —
        // see the note at the top of Social.h — so when it does, it is the finding.
        Serial.printf("[social] 0x%03lx holds a STALE view of us (ours ep %u, reports #%u)\n",
                      (unsigned long)src_[tail_], t_.epoch(), t_.staleReports());
      tail_ = (uint8_t)((tail_ + 1) % SOCIAL_QUEUE);
    }
    // §5.3 reclamation made audible. Expected NEVER on this fleet (<=5 peers against 8
    // slots) — like the staleness counter, this is an instrument whose interesting
    // reading is zero, and a firing is the finding.
    if (t_.reclaims() != last_reclaims_) {
      last_reclaims_ = t_.reclaims();
      Serial.printf("[social] field FULL: reclaimed lowest-decayed trace 0x%03lx "
                    "(RFC-0010 s5.3, #%u) — no boundary written, none owed\n",
                    (unsigned long)t_.lastReclaimed(), t_.reclaims());
    }
  }

  // Append our capability digest to a HELLO body already holding the anchor and the trace
  // digest. Returns bytes added.
  size_t helloAppend(uint8_t* p, size_t cap, uint32_t now_ms) {
    return t_.buildDigest(p, cap, now_ms);
  }

  // ---- the @LAT101 field's durable shadow (TTDB-RFC-0010 §5, stage 3) --------------
  // Reload the field at boot. Call from setup(), after the TTDB mounts and begin() ran.
  // Every reloaded trace is UNKNOWN-AGE (§5.4) — setup() runs before the stream listen
  // window — so it re-enters clamped and FADED, never absent and never trusted fresh.
  uint8_t loadField(Ttdb& db, uint32_t now_ms) {
    // ⚠ `recbuf_` (shared with persistField — never live at once) is used by NAME here:
    // an earlier cut aliased it through a `char* buf` and then measured `sizeof(buf)` —
    // which is sizeof(POINTER), 4 — so every record was truncated to 3 bytes and the
    // whole reload silently loaded nothing. Caught on hardware by persistField's
    // "0 trace(s)" line, the same defect one function over.
    uint8_t loaded = 0;
    for (int i = 0; i < db.recordCount(); ++i) {
      if (db.record(i).lat != SOCIAL_FIELD_LANE) continue;
      size_t off = 0, len = 0;
      if (!db.recordSpan(i, off, len)) continue;
      if (len >= sizeof(recbuf_)) len = sizeof(recbuf_) - 1;
      const size_t got = db.readBytes(off, (uint8_t*)recbuf_, len);
      if (!got) continue;
      recbuf_[got] = 0;   // parsePeerRecord requires termination; readBytes does not give it
      social::PeerRecord r;
      if (social::Table::parsePeerRecord(recbuf_, got, r) && t_.loadPeer(r, now_ms)) ++loaded;
      yield();
    }
    if (loaded)
      Serial.printf("[social] field: %u peer trace(s) reloaded from @LAT%d — age unknown, "
                    "clamped to %u and FADED until heard (RFC-0010 s5.4)\n",
                    loaded, SOCIAL_FIELD_LANE, (unsigned)SOCIAL_COPRE_UNKNOWN_AGE);
    return loaded;
  }

  // Rewrite the lane from the live table — the ONLY writer of @LAT101. Call from loop()
  // when persistDue() says so (a lane rewrite is a whole-file flash pass, so this is
  // change-triggered plus a slow heartbeat, never periodic).
  // ⚠ Watch the sids across persists: same peer, same sid, every time, while copresence
  // and the ordinal move — the property stage 2 pinned for @LAT91, now on a lane whose
  // records are DESIGNED to be rewritten.
  bool persistField(Ttdb& db, uint32_t t_sec, const timestream::Stamp& ts,
                    uint32_t now_ms) {
    // ⚠ Check the INDEX budget before touching the file. The Cardputer's TTDB sat
    // exactly at TTDB_MAX_RECORDS on 2026-08-09 and the first persist "succeeded" into
    // records the index could not hold — which the next lane rewrite then destroyed.
    // appendRecord now refuses at the cap; this pre-check turns five cryptic per-record
    // failures into one sentence naming the actual problem, and deferPersist() keeps
    // the retry (and the sentence) to once per minimum gap instead of every loop pass.
    int held = 0;   // the lane's own records are about to be replaced, so they are room
    for (int i = 0; i < db.recordCount(); ++i)
      if (db.record(i).lat == SOCIAL_FIELD_LANE) ++held;
    if (db.recordCount() - held + (int)t_.peerCount() > TTDB_MAX_RECORDS) {
      Serial.printf("[social] field NOT persisted: index at %d of %d records — no room "
                    "for %u trace(s). The RAM field keeps working; the shadow waits.\n",
                    db.recordCount(), TTDB_MAX_RECORDS, t_.peerCount());
      t_.deferPersist(now_ms);
      return false;
    }
    if (!db.removeLane(SOCIAL_FIELD_LANE)) {
      // Name the step and the heap. This fires on a 60 s heartbeat, so it is the fleet's
      // cheapest early warning that lane rewrites have stopped working on a node — on
      // 2026-08-13 it had been firing on the Cardputer for some time before an operator
      // prune noticed the same failure, and "FAILED" alone said nothing actionable.
      Serial.printf("[social] field persist FAILED (removeLane @LAT%d) at step '%s' — "
                    "maxalloc %u B\n",
                    SOCIAL_FIELD_LANE, db.lastRewriteErrName(),
                    (unsigned)ESP.getMaxAllocHeap());
      t_.deferPersist(now_ms);
      return false;
    }
    uint8_t written = 0;
    for (uint8_t i = 0; i < t_.peerCount(); ++i) {
      uint32_t sid = 0;
      const size_t m = t_.buildPeerRecord(recbuf_, sizeof(recbuf_), i, written, t_sec, ts,
                                          now_ms, &sid);
      if (!m) continue;   // builder refuses rather than truncates; nothing half-written
      if (!db.appendRecord(recbuf_, m)) {
        Serial.printf("[social] field append FAILED @LAT%dLON%u\n", SOCIAL_FIELD_LANE,
                      written);
        continue;
      }
      const social::Peer* p = t_.peerAt(i);
      Serial.printf("[social] field @LAT%dLON%u sid:%08lx node:0x%03lx co:%u "
                    "reinforced:%u\n",
                    SOCIAL_FIELD_LANE, written, (unsigned long)sid,
                    (unsigned long)(p ? p->node : 0),
                    p ? t_.copresenceAt(*p, now_ms) : 0, p ? p->reinforced : 0);
      ++written;
      yield();
    }
    t_.notePersisted(now_ms);
    Serial.printf("[social] field persisted: %u trace(s) (TTDB %uB)\n", written,
                  (unsigned)db.fileSize());
    return true;
  }

  // ---- render ----------------------------------------------------------------------
  // The fleet table, one line per node. ⚠ Renders four distinct states and never collapses
  // them: `X` exercised, `v` verified, `d` declared, `.` absent, `?` unknown — and a peer
  // that has not been heard from recently is marked FADED rather than dropped, because
  // "nobody has been heard from" and "there is nobody" are different claims.
  void printTable(uint32_t now_ms) {
    Serial.printf("[social] fleet table  self 0x%03lx ep %u  peers %u (%u silent)  "
                  "stale-reports %u\n",
                  (unsigned long)t_.selfNode(), t_.epoch(), t_.peerCount(),
                  t_.unknownPeers(), t_.staleReports());
    Serial.printf("[social]   0x%03lx  %s   (self)\n",
                  (unsigned long)t_.selfNode(), capsLine(t_.selfNode()));
    for (uint8_t i = 0; i < t_.peerCount(); ++i) {
      const social::Peer* p = t_.peerAt(i);
      if (!p) continue;
      // `co:` is the DECAYED value — §6.4: a faded trace renders as faded, never as
      // absent. `~` marks an unknown-age trace reloaded from flash (§5.4), which stays
      // marked until a live reception dates it again.
      Serial.printf("[social]   0x%03lx  co:%3u%s  %s   %s%s\n", (unsigned long)p->node,
                    t_.copresenceAt(*p, now_ms), p->age_unknown ? "~" : " ",
                    capsLine(p->node),
                    t_.faded(*p, now_ms) ? "FADED " : "",
                    p->spoke ? "" : "(no digest: capabilities UNKNOWN, not absent)");
    }
    // The one number that says how much of its own shape the fleet can currently know.
    Serial.printf("[social]   pose: %s  (gps exercised %u of %u declared)  "
                  "stillness-witnesses %u  ears %u\n",
                  social::poseName(t_.poseCeiling()),
                  t_.quorum(social::CAP_GPS), t_.declaredQuorum(social::CAP_GPS),
                  t_.quorum(social::CAP_IMU), t_.quorum(social::CAP_MIC));
  }

  social::Table& table() { return t_; }
  const social::Table& table() const { return t_; }

 private:
  // One push for both kinds. `n == 0` means "presence only", which is why `queueDigest`
  // rejects anything shorter than a header before calling this — a short digest must not
  // become a presence record by accident.
  void push(uint32_t from, const uint8_t* p, size_t n) {
    if (!from) return;
    const uint8_t h = head_;
    src_[h] = from;
    len_[h] = (uint8_t)n;
    for (size_t i = 0; i < n; ++i) q_[h][i] = p[i];
    head_ = (uint8_t)((h + 1) % SOCIAL_QUEUE);
    if (head_ == tail_) tail_ = (uint8_t)((tail_ + 1) % SOCIAL_QUEUE);   // drop oldest
  }

  // "mic:X spk:v gps:? ..." for one node. Static buffer: called once per printf argument
  // list, never twice in the same one.
  const char* capsLine(uint32_t node) {
    size_t o = 0;
    for (uint8_t b = 0; b < social::CAP_COUNT; ++b) {
      const social::Status s = t_.statusOf(node, (uint16_t)(1u << b));
      if (s == social::ST_ABSENT) continue;          // omit what a node simply lacks
      const int w = snprintf(line_ + o, sizeof(line_) - o, "%s%s:%s",
                             o ? " " : "", social::capName(b), social::statusGlyph(s));
      if (w <= 0 || (size_t)w >= sizeof(line_) - o) break;
      o += (size_t)w;
    }
    if (!o) snprintf(line_, sizeof(line_), "(nothing claimed)");
    return line_;
  }

  social::Table t_;
  uint8_t  q_[SOCIAL_QUEUE][social::DIGEST_LEN_MAX] = {{0}};
  uint32_t src_[SOCIAL_QUEUE] = {0};
  uint8_t  len_[SOCIAL_QUEUE] = {0};
  uint8_t  head_ = 0, tail_ = 0;
  // Seeded to a value the epoch cannot hold at construction, so the FIRST service pass
  // always reports — a node whose capabilities never change after boot must still say what
  // they are, and `begin()` leaves the epoch at 0.
  uint16_t last_self_epoch_ = 0xFFFF;
  uint16_t last_reclaims_   = 0;
  char     line_[160] = {0};
  // One record buffer for both field I/O paths (load at setup, persist from loop) —
  // they are never live at once, and this is a node whose buffers are sized against
  // maxalloc, not free heap.
  char     recbuf_[SOCIAL_PEER_RECORD_BUF] = {0};
};
