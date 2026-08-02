// PerceptLearn.cpp — see PerceptLearn.h. Portable; native-testable.
#include "PerceptLearn.h"
#include <stdio.h>
#include <string.h>

namespace perceptlearn {

const char* verdictName(uint8_t v) {
  switch (v) {
    case VERDICT_MET: return "met";
    case VERDICT_VIOLATED: return "violated";
    default: return "unobserved";
  }
}

namespace {
const char* protoName(uint8_t p) {
  // Mirrors linkpercept::protoName without depending on it — this library stays
  // usable against any source of (peer, proto, median) triples.
  switch (p) {
    case 0: return "espnow";
    case 1: return "lora";
    default: return "ble";
  }
}
}  // namespace

void Loop::reset() {
  staged_n_ = 0;
  staged_lane_ = -1;
  staged_over_ = 0;
  claims_n_ = 0;
  armed_ = false;
  acting_lane_ = -1;
  pending_ = false;
  met_ = violated_ = unobserved_ = 0;
  scored_lane_ = -1;
  scored_t_ms_ = 0;
  scored_synced_ = false;
  streak_ = 0;
}

void Loop::stageBegin(int link_lane) {
  staged_n_ = 0;
  staged_over_ = 0;
  staged_lane_ = link_lane;
}

void Loop::stage(uint32_t peer, uint8_t proto, int median) {
  if (staged_n_ >= PERCEPTLEARN_MAX_CLAIMS) {
    // ⚠ Do NOT make this a bare `return`. An overflowed peer is still in claims_, so
    // score() finds nothing staged for it and records VERDICT_UNOBSERVED — the buffer
    // running out reads as "the peer went unheard", which is a plausible WRONG answer
    // rather than a gap. The caller must be able to tell the two apart.
    ++staged_over_;
    return;
  }
  Claim& c = staged_[staged_n_++];
  c.peer = peer;
  c.proto = proto;
  c.predicted = (int16_t)median;
  c.observed = (int16_t)median;
  c.verdict = VERDICT_UNOBSERVED;
}

int Loop::findStaged(uint32_t peer, uint8_t proto) const {
  for (int i = 0; i < staged_n_; ++i)
    if (staged_[i].peer == peer && staged_[i].proto == proto) return i;
  return -1;
}

int Loop::score(uint64_t t_ms, bool synced) {
  if (!armed_ || claims_n_ == 0) return 0;

  met_ = violated_ = unobserved_ = 0;
  for (int i = 0; i < claims_n_; ++i) {
    Claim& c = claims_[i];
    int s = findStaged(c.peer, c.proto);
    if (s < 0) {
      // The peer went unheard. NOT a violation: the claim was about where the RSSI
      // would land, and there is no RSSI. Counting silence as a violated prediction
      // would let a peer powering off look like the world contradicting the node.
      c.verdict = VERDICT_UNOBSERVED;
      ++unobserved_;
      continue;
    }
    c.observed = staged_[s].predicted;   // staged holds that window's median
    int d = (int)c.observed - (int)c.predicted;
    if (d < 0) d = -d;
    if (d <= PERCEPTLEARN_RSSI_BAND) {
      c.verdict = VERDICT_MET;
      ++met_;
    } else {
      c.verdict = VERDICT_VIOLATED;
      ++violated_;
    }
  }

  // Rule 4's counter (Stage E does not act on it yet). A window counts as a failure
  // if ANY claim was violated: the expectation was "this link geometry held", and one
  // broken link is enough to have been wrong about that.
  if (violated_ > 0) ++streak_;
  else if (met_ > 0) streak_ = 0;   // an all-unobserved window is neither, so it holds

  armed_ = false;   // one expectation, scored once
  const int n = claims_n_;
  scored_lane_ = staged_lane_;
  scored_t_ms_ = t_ms;
  scored_synced_ = synced;
  pending_ = true;
  return n;
}

bool Loop::arm(int motion_lane) {
  if (staged_n_ == 0) return false;   // nothing heard: nothing to predict about
  for (int i = 0; i < staged_n_; ++i) {
    claims_[i] = staged_[i];
    claims_[i].verdict = VERDICT_UNOBSERVED;
  }
  claims_n_ = staged_n_;
  acting_lane_ = motion_lane;
  armed_ = true;
  // CONSUME the staging. The sketch stages during the link flush and arms during the
  // motion flush later in the SAME loop pass; if the link tier does not flush that
  // pass (no peer was heard at all), staged_ would otherwise still hold the previous
  // window's medians and this would arm a prediction re-derived from stale state —
  // quietly turning Rule 1's live re-derivation back into the precomputed route it
  // forbids. Clearing here makes "no fresh observation" fail loudly as `arm() == false`.
  staged_n_ = 0;
  return true;
}

void Loop::disarm() {
  armed_ = false;
  claims_n_ = 0;
  staged_n_ = 0;   // same reason as arm(): never carry medians across a pass
}

size_t Loop::buildOutcome(char* out, size_t cap, int lane_n, uint32_t node_id) {
  if (!pending_) return 0;
  pending_ = false;   // one record per scoring, success or not

  size_t off = 0;
  int m = snprintf(
      out, cap,
      "\n---\n\n@LAT%dLON%d | created:%lu | updated:%lu | "
      "relates:testifies_about@LAT95LON%d,derived_from@LAT97LON%d,senses@LAT0LON0\n\n"
      "**OUTCOME** t_ms:%llu synced:%d node:0x%lx acting:@LAT95LON%d "
      "observed_in:@LAT97LON%d band_dbm:%d met:%d violated:%d unobserved:%d streak:%d\n",
      PERCEPTLEARN_LANE, lane_n,
      (unsigned long)(scored_synced_ ? (uint32_t)(scored_t_ms_ / 1000) : 0),
      (unsigned long)(scored_synced_ ? (uint32_t)(scored_t_ms_ / 1000) : 0),
      acting_lane_, scored_lane_,
      (unsigned long long)scored_t_ms_, scored_synced_ ? 1 : 0,
      (unsigned long)node_id, acting_lane_, scored_lane_,
      PERCEPTLEARN_RSSI_BAND, met_, violated_, unobserved_, streak_);
  if (m < 0 || (size_t)m >= cap) return 0;
  off = (size_t)m;

  // One EXPECTED/OBSERVED pair per claim: what was predicted, what happened, and the
  // verdict — so a third party can recompute the reconciliation instead of trusting
  // this node's tally. That recomputability is the point of Rule 2.
  for (int i = 0; i < claims_n_; ++i) {
    const Claim& c = claims_[i];
    if (c.verdict == VERDICT_UNOBSERVED) {
      m = snprintf(out + off, cap - off,
                   "**EXPECTED** peer:0x%08lx proto:%s predicted_med:%d band:%d\n"
                   "**OBSERVED** peer:0x%08lx proto:%s verdict:unobserved\n",
                   (unsigned long)c.peer, protoName(c.proto), (int)c.predicted,
                   PERCEPTLEARN_RSSI_BAND, (unsigned long)c.peer, protoName(c.proto));
    } else {
      m = snprintf(out + off, cap - off,
                   "**EXPECTED** peer:0x%08lx proto:%s predicted_med:%d band:%d\n"
                   "**OBSERVED** peer:0x%08lx proto:%s observed_med:%d delta:%d "
                   "verdict:%s\n",
                   (unsigned long)c.peer, protoName(c.proto), (int)c.predicted,
                   PERCEPTLEARN_RSSI_BAND, (unsigned long)c.peer, protoName(c.proto),
                   (int)c.observed, (int)c.observed - (int)c.predicted,
                   verdictName(c.verdict));
    }
    if (m < 0 || (size_t)m >= cap - off) return 0;
    off += (size_t)m;
  }

  // Provenance: which rule, from which record, on what basis. Without this the lane is
  // a pile of numbers nobody can trace back to the claim being tested.
  m = snprintf(out + off, cap - off,
               "**PROVENANCE** rule:LearningFromAction/Rule1 src:@LAT20LON3 "
               "basis:motion_state:still tier:@LAT95 observable:@LAT97 "
               "band_src:p90_of_still_windows\n");
  if (m < 0 || (size_t)m >= cap - off) return 0;
  off += (size_t)m;
  return off;
}

// ---------------------------------------------------------------------------
// Stage D — Rule 3
// ---------------------------------------------------------------------------

void Reconciler::begin() {
  n_ = 0;
  records_ = 0;
  dropped_ = 0;
}

int Reconciler::slotFor(uint32_t peer, uint8_t proto) {
  for (int i = 0; i < n_; ++i)
    if (b_[i].peer == peer && b_[i].proto == proto) return i;
  if (n_ >= PERCEPTLEARN_MAX_BELIEFS) { ++dropped_; return -1; }
  Belief& b = b_[n_];
  b.peer = peer;
  b.proto = proto;
  b.met = b.violated = b.unobserved = 0;
  b.conf = PERCEPTLEARN_BASELINE_CONF;   // every cycle starts here, never from last time
  b.sal = 0;
  b.streak = b.max_streak = 0;
  b.contradiction = false;
  return n_++;
}

void Reconciler::fold(uint32_t peer, uint8_t proto, uint8_t verdict) {
  int i = slotFor(peer, proto);
  if (i < 0) return;
  Belief& b = b_[i];
  if (verdict == VERDICT_MET) {
    ++b.met;
    b.conf += PERCEPTLEARN_CONF_MET;
    if (b.conf > 255) b.conf = 255;          // saturating
    b.streak = 0;
  } else if (verdict == VERDICT_VIOLATED) {
    ++b.violated;
    b.conf -= PERCEPTLEARN_CONF_VIOLATED;
    if (b.conf < 0) b.conf = 0;              // floor
    b.sal += PERCEPTLEARN_SAL_VIOLATED;
    ++b.streak;
    if (b.streak > b.max_streak) b.max_streak = b.streak;
    if (b.streak >= PERCEPTLEARN_CONTRADICTION_STREAK) b.contradiction = true;
  } else {
    // Unobserved. Neither corroborates nor contradicts, and it must not break a
    // violation streak either — nothing was tested, so nothing is known.
    ++b.unobserved;
  }
}

int Reconciler::foldRecord(const char* text, size_t len) {
  int folded = 0;
  const char* p = text;
  const char* end = text + len;
  const char* kObs = "**OBSERVED** peer:0x";
  const size_t kObsLen = 20;   // strlen(kObs)

  while (p < end) {
    // find the next OBSERVED line within the window
    const char* q = p;
    const char* hit = 0;
    while (q + kObsLen <= end) {
      if (q[0] == '*' && memcmp(q, kObs, kObsLen) == 0) { hit = q; break; }
      ++q;
    }
    if (!hit) break;
    const char* nl = hit;
    while (nl < end && *nl != '\n') ++nl;
    if (nl >= end) break;   // truncated tail: do not guess at a partial line

    // peer id (8 hex chars after the prefix)
    uint32_t peer = 0;
    const char* h = hit + kObsLen;
    int digits = 0;
    while (h < nl && digits < 8) {
      char c = *h;
      int v;
      if (c >= '0' && c <= '9') v = c - '0';
      else if (c >= 'a' && c <= 'f') v = c - 'a' + 10;
      else if (c >= 'A' && c <= 'F') v = c - 'A' + 10;
      else break;
      peer = (peer << 4) | (uint32_t)v;
      ++h; ++digits;
    }

    // proto and verdict, both within this line
    uint8_t proto = 0xFF, verdict = 0xFF;
    for (const char* s = hit; s < nl; ++s) {
      if (proto == 0xFF && s + 7 <= nl && memcmp(s, "proto:", 6) == 0) {
        const char* v = s + 6;
        if (v + 6 <= nl && memcmp(v, "espnow", 6) == 0) proto = 0;
        else if (v + 4 <= nl && memcmp(v, "lora", 4) == 0) proto = 1;
        else if (v + 3 <= nl && memcmp(v, "ble", 3) == 0) proto = 2;
      }
      if (verdict == 0xFF && s + 9 <= nl && memcmp(s, "verdict:", 8) == 0) {
        const char* v = s + 8;
        if (v + 3 <= nl && memcmp(v, "met", 3) == 0) verdict = VERDICT_MET;
        else if (v + 8 <= nl && memcmp(v, "violated", 8) == 0) verdict = VERDICT_VIOLATED;
        else verdict = VERDICT_UNOBSERVED;
      }
    }
    if (digits == 8 && proto != 0xFF && verdict != 0xFF) {
      fold(peer, proto, verdict);
      ++folded;
    }
    p = nl + 1;
  }
  if (folded) ++records_;
  return folded;
}

size_t Reconciler::buildBelief(char* out, size_t cap, int i, int lon, uint32_t t_sec,
                               uint32_t node_id, int rev) const {
  if (i < 0 || i >= n_) return 0;
  const Belief& b = b_[i];
  int m = snprintf(
      out, cap,
      "\n---\n\n@LAT%dLON%d | created:%lu | updated:%lu | "
      "relates:believes_about@LAT0LON0,reconciles@LAT92LON0,derived_from@LAT97LON0\n"
      "[ew]\n"
      "conf:%ld\n"
      "rev:%d\n"
      "sal:%ld\n"
      "touched:%lu\n"
      "[/ew]\n\n"
      "**LINK-STABLE** peer:0x%08lx proto:%s node:0x%lx\n"
      "**TALLY** met:%ld violated:%ld unobserved:%ld baseline_conf:%d "
      "rule:+%d/-%d max_streak:%ld contradiction:%d\n"
      "**PROVENANCE** rule:LearningFromAction/Rule3 src:@LAT20LON3 "
      "recomputed_from:@LAT%d lane_records:%d method:sequential_fold_from_baseline\n",
      PERCEPTLEARN_BELIEF_LANE, lon, (unsigned long)t_sec, (unsigned long)t_sec,
      (long)b.conf, rev, (long)b.sal, (unsigned long)t_sec,
      (unsigned long)b.peer, protoName(b.proto), (unsigned long)node_id,
      (long)b.met, (long)b.violated, (long)b.unobserved, PERCEPTLEARN_BASELINE_CONF,
      PERCEPTLEARN_CONF_MET, PERCEPTLEARN_CONF_VIOLATED, (long)b.max_streak,
      b.contradiction ? 1 : 0,
      PERCEPTLEARN_LANE, records_);
  if (m < 0 || (size_t)m >= cap) return 0;
  return (size_t)m;
}

}  // namespace perceptlearn
