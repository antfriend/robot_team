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
  acting_offset_ = 0;
  pending_ = false;
  met_ = violated_ = unobserved_ = 0;
  scored_lane_ = -1;
  scored_stamp_ = timestream::Stamp();
  scored_wall_sec_ = 0;
  streak_ = 0;
  reason_ = "first";
  run_open_ = false;
  run_n_ = 0;
  scored_vec_n_ = 0;
  cov_n_ = 0;
  cov_windows_ = 0;
  cov_first_t_ms_ = 0;
  cov_last_t_ms_ = 0;
}

bool Loop::sameAsRun() const {
  if (!run_open_ || run_n_ != claims_n_) return false;
  for (int i = 0; i < claims_n_; ++i) {
    const Claim& c = claims_[i];
    bool found = false;
    for (int j = 0; j < run_n_; ++j) {
      if (run_[j].peer == c.peer && run_[j].proto == c.proto) {
        if (run_[j].verdict != c.verdict) return false;
        found = true;
        break;
      }
    }
    if (!found) return false;
  }
  return true;
}

void Loop::adoptRun() {
  run_n_ = scored_vec_n_;
  for (int i = 0; i < scored_vec_n_; ++i) run_[i] = scored_vec_[i];
  run_open_ = true;
  cov_n_ = 0;
  cov_windows_ = 0;
  cov_first_t_ms_ = 0;
  cov_last_t_ms_ = 0;
}

void Loop::foldIntoRun() {
  // The verdict vector matched, so every claim already has a slot from the previous
  // covered window (or needs one now). Only the observed RANGE moves.
  if (cov_windows_ == 0) cov_first_t_ms_ = scored_stamp_.t_ms;
  cov_last_t_ms_ = scored_stamp_.t_ms;
  ++cov_windows_;
  for (int i = 0; i < claims_n_; ++i) {
    const Claim& c = claims_[i];
    int slot = -1;
    for (int j = 0; j < cov_n_; ++j)
      if (cov_[j].peer == c.peer && cov_[j].proto == c.proto) { slot = j; break; }
    if (slot < 0) {
      if (cov_n_ >= PERCEPTLEARN_MAX_CLAIMS) continue;   // cannot happen: same vector
      slot = cov_n_++;
      cov_[slot].peer = c.peer;
      cov_[slot].proto = c.proto;
      cov_[slot].verdict = c.verdict;
      cov_[slot].windows = 0;
      cov_[slot].observed_min = c.observed;
      cov_[slot].observed_max = c.observed;
    }
    ++cov_[slot].windows;
    if (c.observed < cov_[slot].observed_min) cov_[slot].observed_min = c.observed;
    if (c.observed > cov_[slot].observed_max) cov_[slot].observed_max = c.observed;
    // ⚠ For an UNOBSERVED claim `c.observed` still holds the PREDICTION (score() never
    // overwrites it — there was no median to overwrite it with), so this range is
    // meaningless. It is not rendered for that verdict, and it cannot leak across
    // verdicts: a run holds ONE verdict vector, so a claim that is unobserved here was
    // unobserved in every window of the run.
  }
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

int Loop::score(const timestream::Stamp& ts, uint32_t wall_sec) {
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
  scored_stamp_ = ts;
  scored_wall_sec_ = wall_sec;

  // ------------------------------------------------------------------------
  // Run-length: write, or fold into the run in progress?
  // ------------------------------------------------------------------------
  // Everything above this line ran exactly as it always did — the window WAS scored,
  // the streak WAS advanced, the verdicts exist. All that is decided here is whether
  // this window earns a record of its own or is carried by the one that closes the run.
  const bool first     = !run_open_;
  const bool changed   = run_open_ && !sameAsRun();
  const bool heartbeat = run_open_ && !changed &&
                         (cov_windows_ + 1 >= PERCEPTLEARN_MAX_RUN);

  // Snapshot the vector as scored, BEFORE the sketch's next arm() overwrites claims_.
  scored_vec_n_ = claims_n_;
  for (int i = 0; i < claims_n_; ++i) scored_vec_[i] = claims_[i];

  if (first || changed || heartbeat) {
    reason_ = first ? "first" : (changed ? "changed" : "heartbeat");
    pending_ = true;      // buildOutcome renders it, covered block and all
  } else {
    foldIntoRun();
    pending_ = false;     // ⚠ NOT a dropped window: cov_windows_ counts it
  }
  return n;
}

bool Loop::arm(int motion_lane, int motion_offset) {
  if (staged_n_ == 0) return false;   // nothing heard: nothing to predict about
  for (int i = 0; i < staged_n_; ++i) {
    claims_[i] = staged_[i];
    claims_[i].verdict = VERDICT_UNOBSERVED;
  }
  claims_n_ = staged_n_;
  acting_lane_ = motion_lane;
  acting_offset_ = motion_offset;
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
  const size_t n = renderOutcome(out, cap, lane_n, node_id);
  // ⚠ ALWAYS adopt, even when the render failed. The covered windows are gone either
  // way — nothing was appended — and carrying them forward would make the NEXT record
  // claim `windows_since_last:N` for a stretch whose evidence was never written. A
  // record that overstates its coverage is worse than a window that is simply missing.
  adoptRun();
  return n;
}

size_t Loop::renderOutcome(char* out, size_t cap, int lane_n, uint32_t node_id) {
  char stamp[64];
  if (!timestream::buildStamp(stamp, sizeof(stamp), scored_stamp_)) return 0;
  // `created:`/`updated:` stay Unix seconds per TTDB-RFC-0001, and stay 0 when the
  // fleet has no wall anchor. The stream frame lives in the body, where it can say
  // WHICH clock without redefining a format-level field's unit.
  const unsigned long t_sec = (unsigned long)scored_wall_sec_;

  size_t off = 0;
  int m = snprintf(
      out, cap,
      "\n---\n\n@LAT%dLON%d | created:%lu | updated:%lu | "
      "relates:testifies_about@LAT95LON%d,derived_from@LAT97LON%d,senses@LAT0LON0\n\n"
      "**OUTCOME** %s node:0x%lx acting:@LAT95LON%d+%d "
      "observed_in:@LAT97LON%d band_dbm:%d met:%d violated:%d unobserved:%d streak:%d\n"
      "**RUN** windows_since_last:%d reason:%s max_run:%d\n",
      PERCEPTLEARN_LANE, lane_n, t_sec, t_sec,
      acting_lane_, scored_lane_,
      stamp,
      (unsigned long)node_id, acting_lane_, acting_offset_, scored_lane_,
      PERCEPTLEARN_RSSI_BAND, met_, violated_, unobserved_, streak_,
      cov_windows_ + 1, reason_, PERCEPTLEARN_MAX_RUN);
  if (m < 0 || (size_t)m >= cap) return 0;
  off = (size_t)m;

  // The windows this record's predecessor spoke for but never itemised — emitted BEFORE
  // the record's own pairs because that is the order they happened in, and
  // Reconciler::foldRecord folds in document order. Each line is folded `windows:` times,
  // which is what makes the compression lossless for Rule 3 rather than merely cheap.
  if (cov_windows_ > 0) {
    m = snprintf(out + off, cap - off,
                 "**COVERED-SPAN** windows:%d first_t_ms:%llu last_t_ms:%llu "
                 "counts_scored_windows_not_minutes:1\n",
                 cov_windows_, (unsigned long long)cov_first_t_ms_,
                 (unsigned long long)cov_last_t_ms_);
    if (m < 0 || (size_t)m >= cap - off) return 0;
    off += (size_t)m;
    for (int i = 0; i < cov_n_; ++i) {
      const Covered& c = cov_[i];
      if (c.verdict == VERDICT_UNOBSERVED) {
        // No median was ever observed, so there is no range to report. Printing the
        // prediction here would read as a measurement.
        m = snprintf(out + off, cap - off,
                     "**COVERED** peer:0x%08lx proto:%s verdict:unobserved windows:%ld\n",
                     (unsigned long)c.peer, protoName(c.proto), (long)c.windows);
      } else {
        m = snprintf(out + off, cap - off,
                     "**COVERED** peer:0x%08lx proto:%s verdict:%s windows:%ld "
                     "observed_min:%d observed_max:%d\n",
                     (unsigned long)c.peer, protoName(c.proto), verdictName(c.verdict),
                     (long)c.windows, (int)c.observed_min, (int)c.observed_max);
      }
      // A record carrying `windows_since_last:N` with its COVERED block truncated away
      // would claim N windows and account for one. Write nothing instead — the same
      // rule the head line and the transition pair already follow.
      if (m < 0 || (size_t)m >= cap - off) return 0;
      off += (size_t)m;
    }
  }

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
  const char* kCov = "**COVERED** peer:0x";
  const size_t kCovLen = 19;   // strlen(kCov)

  while (p < end) {
    // ⚠ ONE scan recognising BOTH line kinds, not two passes. A **COVERED** line stands
    // for `windows:` windows that happened BEFORE this record's own, and Rule 3's +2
    // saturation / -16 floor are order-sensitive, so folding all the covered lines of a
    // lane after all the observed ones would produce a different (wrong) belief. Walking
    // the text once keeps document order, which is time order by construction.
    const char* q = p;
    const char* hit = 0;
    bool covered = false;
    while (q < end) {
      if (q[0] == '*') {
        if (q + kObsLen <= end && memcmp(q, kObs, kObsLen) == 0) { hit = q; break; }
        if (q + kCovLen <= end && memcmp(q, kCov, kCovLen) == 0) {
          hit = q; covered = true; break;
        }
      }
      ++q;
    }
    if (!hit) break;
    const char* nl = hit;
    while (nl < end && *nl != '\n') ++nl;
    if (nl >= end) break;   // truncated tail: do not guess at a partial line

    // peer id (8 hex chars after the prefix)
    uint32_t peer = 0;
    const char* h = hit + (covered ? kCovLen : kObsLen);
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

    // proto, verdict and (on a covered line) the repeat count, all within this line
    uint8_t proto = 0xFF, verdict = 0xFF;
    // An OBSERVED line is one window by definition. A COVERED line starts at ZERO and
    // only counts once its `windows:` field parses — see the note below.
    long windows = covered ? 0 : 1;
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
      if (covered && s + 9 <= nl && memcmp(s, "windows:", 8) == 0) {
        const char* v = s + 8;
        long w = 0;
        int d = 0;
        while (v < nl && *v >= '0' && *v <= '9' && d < 9) { w = w * 10 + (*v - '0'); ++v; ++d; }
        // ⚠ A covered line whose count is missing or unparseable folds ZERO times, not
        // once. Guessing 1 would silently under-count a run of 30 by 29 windows while
        // looking like a complete fold — the failure mode this whole lane exists to
        // avoid. A dropped line at least shows up as a lower `lane_records` count.
        if (d > 0) windows = w;
        else windows = 0;
      }
    }
    if (covered && windows < 0) windows = 0;
    if (digits == 8 && proto != 0xFF && verdict != 0xFF) {
      for (long k = 0; k < windows; ++k) fold(peer, proto, verdict);
      if (windows > 0) ++folded;
    }
    p = nl + 1;
  }
  if (folded) ++records_;
  return folded;
}

size_t Reconciler::beliefKey(char* out, size_t cap, uint32_t peer, uint8_t proto) {
  const int m = snprintf(out, cap, "peer:0x%08lx|proto:%s",
                         (unsigned long)peer, protoName(proto));
  return (m < 0 || (size_t)m >= cap) ? 0 : (size_t)m;
}

size_t Reconciler::buildBelief(char* out, size_t cap, int i, int lon, uint32_t t_sec,
                               uint32_t node_id, int rev,
                               const timestream::Stamp& ts,
                               uint32_t* sid_out) const {
  if (sid_out) *sid_out = 0;
  if (i < 0 || i >= n_) return 0;
  const Belief& b = b_[i];
  char stamp[64];
  if (!timestream::buildStamp(stamp, sizeof(stamp), ts)) return 0;
  int m = snprintf(
      out, cap,
      "\n---\n\n@LAT%dLON%d | sid:00000000 | created:%lu | updated:%lu | "
      "relates:believes_about@LAT0LON0,reconciles@LAT92LON0,derived_from@LAT97LON0\n"
      "[ew]\n"
      "conf:%ld\n"
      "rev:%d\n"
      "sal:%ld\n"
      "touched:%lu\n"
      "[/ew]\n\n"
      "**LINK-STABLE** peer:0x%08lx proto:%s node:0x%lx\n"
      "**TOUCHED** %s unix_s:%lu\n"
      "**TALLY** met:%ld violated:%ld unobserved:%ld baseline_conf:%d "
      "rule:+%d/-%d max_streak:%ld contradiction:%d\n"
      "**PROVENANCE** rule:LearningFromAction/Rule3 src:@LAT20LON3 "
      "recomputed_from:@LAT%d lane_records:%d method:sequential_fold_from_baseline\n",
      PERCEPTLEARN_BELIEF_LANE, lon, (unsigned long)t_sec, (unsigned long)t_sec,
      (long)b.conf, rev, (long)b.sal, (unsigned long)t_sec,
      (unsigned long)b.peer, protoName(b.proto), (unsigned long)node_id,
      stamp, (unsigned long)t_sec,
      (long)b.met, (long)b.violated, (long)b.unobserved, PERCEPTLEARN_BASELINE_CONF,
      PERCEPTLEARN_CONF_MET, PERCEPTLEARN_CONF_VIOLATED, (long)b.max_streak,
      b.contradiction ? 1 : 0,
      PERCEPTLEARN_LANE, records_);
  if (m < 0 || (size_t)m >= cap) return 0;

  // Stamp the placeholder. KEY identity: the subject, and nothing that changes about it.
  // ⚠ `lon` is deliberately NOT an input — a belief that moves slot keeps its name, which
  // is TTDB-RFC-0004 §4 in one line and the reason this lane went first.
  char key[48];
  if (!beliefKey(key, sizeof(key), b.peer, b.proto)) return 0;
  const uint32_t s = sid::stampKey(out, (size_t)m, node_id, PERCEPTLEARN_BELIEF_LANE, key);
  // ⚠ A record is never half-stamped. If the placeholder was not found, the header format
  // string and this call have drifted apart — and shipping an unstamped record from a lane
  // that declares stable ids is worse than shipping none, because a reader would read the
  // absence as "pre-adoption" rather than "broken".
  if (!s) return 0;
  if (sid_out) *sid_out = s;
  return (size_t)m;
}

size_t Reconciler::buildBoundary(char* out, size_t cap, int records) const {
  long met = 0, violated = 0, unobserved = 0, windows_max = 0;
  for (int i = 0; i < n_; ++i) {
    met += b_[i].met;
    violated += b_[i].violated;
    unobserved += b_[i].unobserved;
    // The most windows any SINGLE claim was tested over. Not a mean across beliefs: the
    // claim set changes as peers come and go, so a mean reports a number no claim
    // actually experienced.
    const long w = b_[i].met + b_[i].violated + b_[i].unobserved;
    if (w > windows_max) windows_max = w;
  }

  int m = snprintf(out, cap,
                   "**OUTCOMES-CARRIED** records:%d windows_max:%ld beliefs:%d "
                   "met:%ld violated:%ld unobserved:%ld baseline_conf:%d rule:+%d/-%d\n",
                   records, windows_max, n_, met, violated, unobserved,
                   PERCEPTLEARN_BASELINE_CONF, PERCEPTLEARN_CONF_MET,
                   PERCEPTLEARN_CONF_VIOLATED);
  if (m < 0 || (size_t)m >= cap) return 0;
  size_t off = (size_t)m;

  for (int i = 0; i < n_; ++i) {
    const Belief& b = b_[i];
    m = snprintf(out + off, cap - off,
                 "**BELIEF-AT-BOUNDARY** peer:0x%08lX proto:%s conf:%ld sal:%ld "
                 "met:%ld violated:%ld unobserved:%ld max_streak:%ld contradiction:%d\n",
                 (unsigned long)b.peer, protoName(b.proto), (long)b.conf, (long)b.sal,
                 (long)b.met, (long)b.violated, (long)b.unobserved,
                 (long)b.max_streak, b.contradiction ? 1 : 0);
    if (m < 0 || (size_t)m >= cap - off) return 0;
    off += (size_t)m;
  }
  return off;
}

}  // namespace perceptlearn
