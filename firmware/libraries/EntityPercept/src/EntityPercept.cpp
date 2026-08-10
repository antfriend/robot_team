// EntityPercept.cpp — see EntityPercept.h. Portable; native-tested.
#include "EntityPercept.h"
#include <stdio.h>
#include <string.h>

namespace entitypercept {

const char* kindName(uint8_t k) {
  switch (k) {
    case KIND_WIFI_AP: return "wifi_ap";
    case KIND_BLE_MAC: return "ble_mac";
    default: return "?";
  }
}

void Log::reset(uint32_t now_ms) {
  memset(ents_, 0, sizeof(ents_));
  ent_count_ = 0;
  window_start_ms_ = now_ms;
  close_ = CLOSE_EMPTY;
}

void Log::histClear() {
  memset(hist_, 0, sizeof(hist_));
  memset(hist_count_, 0, sizeof(hist_count_));
  hist_len_ = 0;
  hist_head_ = 0;
  memset(cur_core_, 0, sizeof(cur_core_));
  cur_core_n_ = 0;
}

void Log::breakRun() {
  run_open_ = false;
  run_lane_ = -1;
  run_len_ = 0;
  run_core_n_ = 0;
  memset(run_core_, 0, sizeof(run_core_));
  memset(cov_, 0, sizeof(cov_));
  cov_ent_n_ = 0;
  cov_windows_ = 0;
  cov_window_ms_ = 0;
  cov_first_t_ms_ = 0;
  cov_last_t_ms_ = 0;
}

bool Log::sameKey(const Key& a, const Key& b) {
  return a.kind == b.kind && memcmp(a.id, b.id, ENTITY_ID_LEN) == 0;
}

void Log::histPush() {
  const int slot = hist_head_;
  int k = 0;
  for (int i = 0; i < ent_count_ && k < ENTITYPERCEPT_MAX_ENTITIES; ++i) {
    if (ents_[i].n == 0) continue;       // seen-but-empty is not a sighting
    memcpy(hist_[slot][k].id, ents_[i].id, ENTITY_ID_LEN);
    hist_[slot][k].kind = ents_[i].kind;
    ++k;
  }
  hist_count_[slot] = (uint8_t)k;
  hist_head_ = (hist_head_ + 1) % ENTITYPERCEPT_CORE_M;
  if (hist_len_ < ENTITYPERCEPT_CORE_M) ++hist_len_;
  cur_core_n_ = core(cur_core_, ENTITYPERCEPT_MAX_ENTITIES);
}

int Log::core(Key* out, int cap) const {
  int n_out = 0;
  // Walk every entity in the ring and count the windows it appears in. O(M^2 x E^2)
  // with M=5 and E=12 — 3600 comparisons at worst, once per 600 s window.
  for (int w = 0; w < hist_len_; ++w) {
    const int slot = (hist_head_ - 1 - w + 2 * ENTITYPERCEPT_CORE_M) % ENTITYPERCEPT_CORE_M;
    for (int i = 0; i < hist_count_[slot]; ++i) {
      const Key& k = hist_[slot][i];
      bool already = false;
      for (int j = 0; j < n_out; ++j)
        if (sameKey(out[j], k)) { already = true; break; }
      if (already) continue;
      int seen = 0;
      for (int w2 = 0; w2 < hist_len_; ++w2) {
        const int s2 =
            (hist_head_ - 1 - w2 + 2 * ENTITYPERCEPT_CORE_M) % ENTITYPERCEPT_CORE_M;
        for (int j = 0; j < hist_count_[s2]; ++j)
          if (sameKey(hist_[s2][j], k)) { ++seen; break; }
      }
      if (seen < ENTITYPERCEPT_CORE_N) continue;
      if (n_out >= cap) return n_out;
      out[n_out++] = k;
    }
  }
  return n_out;
}

int Log::coreCount() const { return cur_core_n_; }

bool Log::coreEntry(int i, const uint8_t*& id, uint8_t& kind) const {
  if (i < 0 || i >= cur_core_n_) return false;
  id = cur_core_[i].id;
  kind = cur_core_[i].kind;
  return true;
}

bool Log::unionWouldOverflow() const {
  int need = cov_ent_n_;
  for (int i = 0; i < ent_count_; ++i) {
    if (ents_[i].n == 0) continue;
    bool found = false;
    for (int j = 0; j < cov_ent_n_; ++j)
      if (cov_[j].kind == ents_[i].kind &&
          memcmp(cov_[j].id, ents_[i].id, ENTITY_ID_LEN) == 0) { found = true; break; }
    if (!found) ++need;
  }
  return need > ENTITYPERCEPT_MAX_UNION;
}

void Log::foldCovered(const timestream::Stamp& ts, uint32_t window_ms) {
  for (int i = 0; i < ent_count_; ++i) {
    if (ents_[i].n == 0) continue;
    int slot = -1;
    for (int j = 0; j < cov_ent_n_; ++j)
      if (cov_[j].kind == ents_[i].kind &&
          memcmp(cov_[j].id, ents_[i].id, ENTITY_ID_LEN) == 0) { slot = j; break; }
    if (slot < 0) {
      // unionWouldOverflow() is checked BEFORE the decision to fold, so this cannot
      // run out of room. Refusing here rather than wrapping keeps that an invariant
      // instead of a comment.
      if (cov_ent_n_ >= ENTITYPERCEPT_MAX_UNION) continue;
      slot = cov_ent_n_++;
      memcpy(cov_[slot].id, ents_[i].id, ENTITY_ID_LEN);
      cov_[slot].kind = ents_[i].kind;
      cov_[slot].n = 0;
      cov_[slot].rssi_max = -128;
      cov_[slot].windows = 0;
    }
    cov_[slot].n += ents_[i].n;
    if (ents_[i].rssi_max > cov_[slot].rssi_max) cov_[slot].rssi_max = ents_[i].rssi_max;
    cov_[slot].windows++;
  }
  if (cov_windows_ == 0) cov_first_t_ms_ = ts.t_ms;
  cov_last_t_ms_ = ts.t_ms;
  cov_windows_++;
  cov_window_ms_ += window_ms;
}

int Log::slotFor(const uint8_t id[ENTITY_ID_LEN], uint8_t kind) {
  for (int i = 0; i < ent_count_; ++i)
    if (ents_[i].kind == kind && memcmp(ents_[i].id, id, ENTITY_ID_LEN) == 0)
      return i;
  if (ent_count_ >= ENTITYPERCEPT_MAX_ENTITIES) return -1;  // window full: drop
  int i = ent_count_++;
  memcpy(ents_[i].id, id, ENTITY_ID_LEN);
  ents_[i].kind = kind;
  ents_[i].n = 0;
  ents_[i].rssi_max = -128;
  return i;
}

void Log::add(const uint8_t id[ENTITY_ID_LEN], int rssi, uint8_t kind) {
  if (rssi == 0) return;            // unknown — not evidence
  if (rssi < -128) rssi = -128;
  if (rssi > 0) rssi = 0;
  int i = slotFor(id, kind);
  if (i < 0) return;
  ents_[i].n++;
  if ((int8_t)rssi > ents_[i].rssi_max) ents_[i].rssi_max = (int8_t)rssi;
}

bool Log::due(uint32_t now_ms) const {
  if (totalObs() == 0) return false;
  return (uint32_t)(now_ms - window_start_ms_) >= (uint32_t)ENTITYPERCEPT_FLUSH_MS;
}

int Log::totalObs() const {
  int t = 0;
  for (int i = 0; i < ent_count_; ++i) t += (int)ents_[i].n;
  return t;
}

bool Log::stats(int slot, const uint8_t*& id, uint8_t& kind, uint32_t& n,
                int& rmax) const {
  if (slot < 0 || slot >= ent_count_ || ents_[slot].n == 0) return false;
  const EntityStats& e = ents_[slot];
  id = e.id;
  kind = e.kind;
  n = e.n;
  rmax = e.rssi_max;
  return true;
}

size_t Log::buildRecord(char* out, size_t cap, int lane_n, uint32_t t_sec,
                        const timestream::Stamp& ts, uint32_t now_ms) {
  if (totalObs() == 0) {
    reset(now_ms);
    close_ = CLOSE_EMPTY;
    return 0;
  }
  const uint32_t window_ms = now_ms - window_start_ms_;

  // The window's set enters the history FIRST, so the core this window is judged
  // against includes it. Judging against the previous window's core would report a
  // change one window late and put the record's own `**CORE**` at odds with the
  // history it was computed from.
  histPush();

  // ------------------------------------------------------------------------
  // Write, or fold into the run in progress?
  // ------------------------------------------------------------------------
  bool core_changed = false;
  if (run_open_) {
    core_changed = (cur_core_n_ != run_core_n_);
    for (int i = 0; !core_changed && i < cur_core_n_; ++i) {
      bool found = false;
      for (int j = 0; j < run_core_n_; ++j)
        if (sameKey(cur_core_[i], run_core_[j])) { found = true; break; }
      if (!found) core_changed = true;
    }
  }
  const bool first     = !run_open_;
  const bool heartbeat = run_open_ && !core_changed && (run_len_ >= ENTITYPERCEPT_MAX_RUN);
  // Checked LAST so its reason only shows when it is the actual cause, but it is not
  // optional: folding a window whose entities will not fit the COVERED block is the one
  // way the union claim could fail, so the run ends instead. See ENTITYPERCEPT_MAX_UNION.
  const bool union_full = run_open_ && !core_changed && !heartbeat && unionWouldOverflow();
  const bool write      = first || core_changed || heartbeat || union_full;

  size_t w = 0;
  if (write) {
    char stamp[64];
    if (!timestream::buildStamp(stamp, sizeof(stamp), ts)) {
      reset(now_ms);
      close_ = CLOSE_EMPTY;
      return 0;
    }
    // Counts THIS window plus every one suppressed since the last record, so 1 means
    // adjacent. On the first record of a chain there is no previous record to measure
    // from and it is 1 by definition, flagged `reason:first`.
    // `run_len_` already counts the covering record's own window plus every fold, so it
    // IS the gap: record at window 1, folds at 2 and 3, this write at 4 -> run_len_ 3,
    // cov_windows_ 2, and `windows_since_last:3` names windows 2, 3 and 4.
    const int since = run_open_ ? run_len_ : 1;
    const char* reason = first ? "first"
                               : (core_changed ? "changed"
                                               : (heartbeat ? "heartbeat" : "union_full"));
    int m = snprintf(out + w, cap - w,
                     "\n---\n\n@LAT96LON%d | created:%lu | updated:%lu | "
                     "relates:observes@LAT0LON0\n\n"
                     "**ENTWIN** %s window_ms:%lu entities:%d\n",
                     lane_n, (unsigned long)t_sec, (unsigned long)t_sec,
                     stamp, (unsigned long)window_ms, ent_count_);
    if (m < 0 || (size_t)m >= cap - w) { reset(now_ms); close_ = CLOSE_EMPTY; return 0; }
    w += (size_t)m;

    for (int i = 0; i < ent_count_; ++i) {
      const uint8_t* id;
      uint8_t kind;
      uint32_t n;
      int rmax;
      if (!stats(i, id, kind, n, rmax)) continue;
      m = snprintf(out + w, cap - w,
                   "**ENTITY** kind:%s id:%02x%02x%02x%02x%02x%02x n:%lu rssi:%d\n",
                   kindName(kind), id[0], id[1], id[2], id[3], id[4], id[5],
                   (unsigned long)n, rmax);
      // ⚠ NOT `break` — a truncated entity list is a record that under-reports what the
      // node saw while looking complete, and this lane's whole job is the set. Writing
      // nothing is the honest failure, and ENTITYPERCEPT_RECORD_BUF is sized so it
      // cannot happen (pinned in both directions by the native test).
      if (m < 0 || (size_t)m >= cap - w) { reset(now_ms); close_ = CLOSE_EMPTY; return 0; }
      w += (size_t)m;
    }

    m = snprintf(out + w, cap - w,
                 "**RUN** windows_since_last:%d reason:%s max_run:%d "
                 "core_n:%d core_m:%d core_windows:%d\n",
                 since, reason, ENTITYPERCEPT_MAX_RUN, ENTITYPERCEPT_CORE_N,
                 ENTITYPERCEPT_CORE_M, hist_len_);
    if (m < 0 || (size_t)m >= cap - w) { reset(now_ms); close_ = CLOSE_EMPTY; return 0; }
    w += (size_t)m;

    // The set this record claims is holding. `entities:0` is a real state and reads two
    // ways — the environment has no stable member, or the history is still warming up —
    // which is why `core_windows:` is on the RUN line above and not left to inference.
    m = snprintf(out + w, cap - w, "**CORE** entities:%d", cur_core_n_);
    if (m < 0 || (size_t)m >= cap - w) { reset(now_ms); close_ = CLOSE_EMPTY; return 0; }
    w += (size_t)m;
    for (int i = 0; i < cur_core_n_; ++i) {
      const uint8_t* id = cur_core_[i].id;
      m = snprintf(out + w, cap - w, "%s%02x%02x%02x%02x%02x%02x",
                   i == 0 ? " ids:" : ",", id[0], id[1], id[2], id[3], id[4], id[5]);
      if (m < 0 || (size_t)m >= cap - w) { reset(now_ms); close_ = CLOSE_EMPTY; return 0; }
      w += (size_t)m;
    }
    m = snprintf(out + w, cap - w, "\n");
    if (m < 0 || (size_t)m >= cap - w) { reset(now_ms); close_ = CLOSE_EMPTY; return 0; }
    w += (size_t)m;

    // The windows the previous record spoke for but never itemised, and the union of
    // what was seen in them. Without the per-entity lines this block would claim
    // `windows_since_last:N` with no account of the N-1 — and the lane's consumer
    // computes a union, so the account has to BE the union.
    if (cov_windows_ > 0) {
      m = snprintf(out + w, cap - w,
                   "**COVERED** windows:%ld entities:%d window_ms:%lu "
                   "first_t_ms:%llu last_t_ms:%llu covered_by:@LAT96LON%d\n",
                   (long)cov_windows_, cov_ent_n_, (unsigned long)cov_window_ms_,
                   (unsigned long long)cov_first_t_ms_,
                   (unsigned long long)cov_last_t_ms_, run_lane_);
      if (m < 0 || (size_t)m >= cap - w) { reset(now_ms); close_ = CLOSE_EMPTY; return 0; }
      w += (size_t)m;
      for (int i = 0; i < cov_ent_n_; ++i) {
        const uint8_t* id = cov_[i].id;
        m = snprintf(out + w, cap - w,
                     "**COVERED-ENTITY** kind:%s id:%02x%02x%02x%02x%02x%02x n:%lu "
                     "rssi:%d windows:%d\n",
                     kindName(cov_[i].kind), id[0], id[1], id[2], id[3], id[4], id[5],
                     (unsigned long)cov_[i].n, (int)cov_[i].rssi_max,
                     (int)cov_[i].windows);
        // Same rule as the ENTITY list: the union is the payload, so a partial one is
        // worse than none.
        if (m < 0 || (size_t)m >= cap - w) { reset(now_ms); close_ = CLOSE_EMPTY; return 0; }
        w += (size_t)m;
      }
    }
  } else {
    foldCovered(ts, window_ms);
  }

  // ------------------------------------------------------------------------
  // Advance the run across reset(), which does not touch it.
  // ------------------------------------------------------------------------
  if (write) {
    breakRun();                     // clears the covered accumulators too
    run_open_ = true;
    run_lane_ = lane_n;
    run_len_ = 1;
    run_core_n_ = cur_core_n_;
    for (int i = 0; i < cur_core_n_; ++i) run_core_[i] = cur_core_[i];
  } else {
    run_len_++;
  }

  reset(now_ms);
  close_ = write ? CLOSE_WRITTEN : CLOSE_COVERED;
  return w;
}

}  // namespace entitypercept
