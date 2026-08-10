// EntityPercept.h — SP0 entity-co-occurrence instrumentation for SEMANTIC
// POSITIONING (Act II, ttn-semantic-positioning.md §3 Phase 0, second tier).
//
// The sibling of LinkPercept. Where LinkPercept turns every *frame reception*
// into ranging evidence (per-peer RSSI), EntityPercept turns every *external
// entity sighting* into co-occurrence evidence: a duty-cycled WiFi scan feeds
// each visible AP's BSSID here; per-window the sketch renders one TTDB record
// (@LAT96 lane) with a **ENTITY** line per BSSID. Two nodes that see the same
// APs are probably near each other — the Jaccard overlap of their entity sets
// is a coarse proximity BOUND (spec §2.2: "they share 6 APs, they cannot be
// 800 m apart"), consolidated by companion.py, never on-device.
//
// Same discipline as LinkPercept: fixed RAM buffers, no per-sighting flash
// write, portable (no Arduino dependency) so the stats + record format are
// pinned by tests/test_entitypercept.cpp. The sketch supplies the scan hook
// (WiFi.scanNetworks) and the Ttdb::appendRecord.
//
// Concurrency: add() runs wherever the scan result is walked (loop() on the
// V4s — WiFi.scanNetworks is not called from an ISR), flush in loop(); the
// buffers are increment-only, matching LinkPercept's lock-free pragmatism.
#pragma once
#include <stdint.h>
#include <stddef.h>
#include <TimeStream.h>   // the shared time stamp every record carries

#ifndef ENTITYPERCEPT_MAX_ENTITIES
#define ENTITYPERCEPT_MAX_ENTITIES 12   // distinct entities kept per window
#endif
#ifndef ENTITYPERCEPT_FLUSH_MS
// Entities change slowly; a longer window than LinkPercept's. Bring-up: 1 min.
#define ENTITYPERCEPT_FLUSH_MS 60000
#endif
#ifndef ENTITYPERCEPT_MAX_LANE
// Cap the @LAT96 lane like LinkPercept caps @LAT97: the TTDB index + flash must
// not fill before SP1 consolidation/pruning. Stats keep cycling; append skips.
#define ENTITYPERCEPT_MAX_LANE 48
#endif

// ---------------------------------------------------------------------------
// CHANGE-TRIGGERED WITH RUN-LENGTH (Part 2, 2026-08-10) — and why the trigger is
// a STABLE CORE rather than a threshold on Jaccard drift.
// ---------------------------------------------------------------------------
// @LAT95 and @LAT92 got this treatment on 2026-08-04 and it is NOT mechanically
// copyable here. A motion window's verdict is a 2-state label, so "unchanged" is a
// fact a reader can see. An entity window is a SET, so "unchanged" would be a
// judgement against a constant — and companion.md records what measuring that
// judgement offline said (`scratchpad/lat96_trigger_sim.py`, over the gate-validated
// night-1 segment):
//
//   * the whole 6.45 h segment is TEN distinct BSSIDs, 4-8 per window, so one AP
//     appearing moves Jaccard ~0.2 and "continuous drift" is a misdescription;
//   * a fixed Jaccard threshold's LOSS DOES NOT TRANSFER — the same node on the same
//     bench dropped 10% of its AP union one night and 36% the next;
//   * a stable core at 3-of-5 compressed 4.56x with ZERO union loss on night 1.
//
// ⚠ BUT THE DECIDING ARGUMENT IS ABOUT THE RECORD, NOT THE TRIGGER, and it is the
// same shape as Part 1's: run-length was legitimate on @LAT92 because folding a
// verdict N times equals folding it once per window. The equivalent claim here is
//
//     THE RUN'S UNION MUST BE RECOVERABLE FROM THE RECORD THAT COVERS IT
//
// because the lane's consumer (`companion.py _entity_set` -> the Jaccard proximity
// bound) computes a union. That is what `**COVERED-ENTITY**` is for, and it makes the
// fold lossless for that consumer BY CONSTRUCTION, for any trigger. A `**COVERED**`
// block carrying only `windows:` and a distance would assert that the set stayed
// within some radius of a reference the reader cannot see — the un-re-derivable
// judgement this design exists to avoid.
//
// ⚠ NEITHER MECHANISM IS FULLY RE-DERIVABLE from the written records alone: a reader
// holding only what was written cannot recompute the core over windows that were
// dropped. That property is not available at any compression. What a stable core
// gets instead is being SELF-DESCRIBING — it states the set it claims held, in
// `**CORE**` — and that is the strongest honest claim on offer. Do not upgrade the
// wording in a comment or a commit message to "verifiable"; it is not.
#ifndef ENTITYPERCEPT_CORE_M
// Trailing windows the stable core is computed over.
#define ENTITYPERCEPT_CORE_M 5
#endif
#ifndef ENTITYPERCEPT_CORE_N
// Appearances within those M windows required to be IN the core. 3-of-5 was the
// best loss/compression point in the simulation (4.56x, 0% union loss on night 1;
// 2-of-3 was 3.73x at 0%). ⚠ BOTH ARE STILL PROVISIONAL: one bench, one AP
// alphabet, and the second validated night has not been run. They are a COUNTING
// RULE over recorded sets rather than a constant fitted to a continuous quantity,
// which is a materially weaker dependency than a Jaccard threshold would have been
// — but it is not none, and night 3 exists to settle them.
#define ENTITYPERCEPT_CORE_N 3
#endif
#ifndef ENTITYPERCEPT_MAX_RUN
// The heartbeat, and it is a BUDGET rather than a measurement — same as
// MOTIONPERCEPT_MAX_RUN, but the arithmetic lands differently because this window is
// 600 s, not 60:
//
//   lane life at rest  = MAX_LANE x MAX_RUN windows = 48 x 6 x 600 s = 48 HOURS
//                        (was 8 h — the cap the cancelled night-2 run walked into)
//   worst-case latency = 0 for a core CHANGE; at most 1 HOUR before an unchanging
//                        environment is re-asserted in the lane
//
// ⚠ DELIBERATELY 6 AND NOT 30. The simulation measured the core mechanism itself at
// 3.7-4.6x, so a cap of 6 sits just ABOVE what the data does and the heartbeat
// almost never binds — which is the right relationship: the cap is a backstop, and
// the compression must come from the mechanism where it can be reasoned about. A cap
// of 30 would buy 10 days of lane life and 5 h of silence, and the silence is the
// part that costs: "when did this node last say anything about its surroundings?"
// stops being a meaningful question.
#define ENTITYPERCEPT_MAX_RUN 6
#endif
#ifndef ENTITYPERCEPT_RECORD_BUF
// Buffer buildRecord() needs, and it lives HERE rather than in a sketch because a
// native test cannot call into a .ino — this is the only place its size can be
// pinned (the lesson from four undersized buffers, one of which reached hardware).
// Worst case, all measured in tests/test_entitypercept.cpp:
//
//   header + ENTWIN                                     ~210 B
//   12 x **ENTITY**                                     ~744 B
//   **RUN** + **CORE** with 12 ids                      ~280 B
//   **COVERED** + 12 x **COVERED-ENTITY**              ~1000 B
//                                                      -------
//                                                       ~2234 B
//
// 2560 leaves ~13% headroom. ⚠ buildRecord writes NOTHING rather than truncating, so
// an undersized buffer loses whole windows SILENTLY — and it loses exactly the
// records that close a run, i.e. the ones carrying the union. The sketches' old
// `char rec[1024]` fits the plain form and would have dropped precisely those.
#define ENTITYPERCEPT_RECORD_BUF 2560
#endif
#ifndef ENTITYPERCEPT_MAX_UNION
// Distinct entities the COVERED block can carry. Bigger than a single window's
// ENTITYPERCEPT_MAX_ENTITIES because a run's union is a union: the validated night-1
// segment holds 10 distinct BSSIDs against 4-8 per window, and night 2 holds 11.
//
// ⚠ AND THE OVERFLOW IS NOT A DROP — IT ENDS THE RUN (`reason:union_full`). Folding a
// window whose entities would not fit is the one case where the fold could not describe
// itself, so the run stops instead. That is what makes "the run's union is recoverable
// from the record that covers it" true BY CONSTRUCTION rather than true on this bench:
// the record's capacity bounds the run, not the other way round.
//
// ⚠ AND LIKE Social's reclaim AND THE STALENESS COUNTER, THIS ARM IS EXPECTED TO READ
// ZERO ON THIS FLEET. At MAX_RUN 6 a run tops out at six windows, and the validated
// night-1 environment holds ten distinct BSSIDs in total — so `reason:union_full`
// should never appear in a real lane, and the native suite is where the mechanism is
// exercised (tests/test_entitypercept.cpp needs SIX newcomers per window to trigger
// it; the first cut of that test used one, reached the heartbeat first, and passed
// while testing nothing). If it ever DOES appear in the field, the environment is
// churning far harder than any measurement here assumed — read it as a finding, not
// as a limit to raise.
#define ENTITYPERCEPT_MAX_UNION 16
#endif

namespace entitypercept {

// Entity classes (spec §Phase 0). WiFi APs first; BLE MACs reuse the same lane
// once the BLE scanner surfaces raw MACs (today BLE feeds LinkPercept ranging).
enum Kind : uint8_t { KIND_WIFI_AP = 0, KIND_BLE_MAC = 1 };
const char* kindName(uint8_t k);

const int ENTITY_ID_LEN = 6;   // BSSID / MAC — 6 bytes

struct EntityStats {
  uint8_t id[ENTITY_ID_LEN];
  uint8_t kind;
  uint32_t n;        // sightings this window (dedup-merged across scans)
  int8_t rssi_max;   // strongest sighting (nearest the AP)
};

// One entity in a run's union: the aggregate the COVERED block carries so the fold
// loses nothing the lane's consumer reads. `windows` is how many of the covered
// windows it appeared in — the field a reader needs to tell a core member from a
// one-window visitor without re-deriving the core.
struct CoveredEntity {
  uint8_t id[ENTITY_ID_LEN];
  uint8_t kind;
  uint32_t n;        // sightings summed across the covered windows
  int8_t rssi_max;   // strongest across them
  int16_t windows;
};

// What buildRecord() did with the window it just closed. WRITTEN and COVERED are BOTH
// successful closes; only EMPTY means nothing was there.
//
// ⚠ Branch on this, NEVER on the returned byte count. Before the lane became
// change-triggered, 0 bytes meant "no window". It now means "covered", which is the
// normal case for a node in a stable environment — this is the same trap that would
// have silenced @LAT95's learning loop for 29 windows in 30 (companion.md, 2026-08-04).
enum Close : uint8_t {
  CLOSE_EMPTY = 0,    // no sightings, or the record did not fit
  CLOSE_WRITTEN,      // a record was rendered; it opens a new run
  CLOSE_COVERED,      // folded into the run in progress; no record, no loss
};

class Log {
 public:
  Log() { reset(0); histClear(); breakRun(); }

  // Record one entity sighting (BSSID + RSSI). Deduped by (id, kind): a repeat
  // increments n and keeps the strongest RSSI. rssi==0 is ignored (unknown).
  // Call while walking a completed WiFi scan, not from an ISR.
  void add(const uint8_t id[ENTITY_ID_LEN], int rssi, uint8_t kind);

  // True when the window elapsed and at least one entity was seen.
  bool due(uint32_t now_ms) const;

  int totalObs() const;
  int entityCount() const { return ent_count_; }

  // Per-entity stats. `id` points into the log's buffer (valid until reset()).
  bool stats(int slot, const uint8_t*& id, uint8_t& kind, uint32_t& n,
             int& rmax) const;

  // Close the current window. Renders a complete TTDB record block ONLY when the
  // window opens a run, changes the stable core, fills the run budget, or would
  // overflow the union the COVERED block must carry; otherwise the window is folded
  // into the run in progress and nothing is written. Either way it is counted and a
  // new window starts.
  //
  //   \n---\n\n@LAT96LON<lane_n> | created:<t_sec> | ... | relates:observes@LAT0LON0
  //   \n\n**ENTWIN** t_ms:<t_ms> stream:0x<id> wall:<0|1> window_ms:<..> entities:<n>
  //   \n**ENTITY** kind:wifi_ap id:<12 lowercase hex> n:.. rssi:..
  //   \n**RUN** windows_since_last:<N> reason:<first|changed|heartbeat|union_full>
  //            max_run:<M> core_n:<n> core_m:<m> core_windows:<k>
  //   \n**CORE** entities:<c> ids:<hex>,<hex>,...            (ids: absent when c is 0)
  //   \n**COVERED** windows:<N-1> entities:<u> window_ms:<..> first_t_ms:..
  //            last_t_ms:.. covered_by:@LAT96LON<lane>       (only when N > 1)
  //   \n**COVERED-ENTITY** kind:.. id:<12 hex> n:.. rssi:.. windows:..
  //
  // Returns bytes written, or 0 when the window was covered or empty — ⚠ CHECK
  // lastClose(), NOT the byte count, to tell those apart. `cap` should be
  // ENTITYPERCEPT_RECORD_BUF: a record that does not fit is written NOT AT ALL.
  size_t buildRecord(char* out, size_t cap, int lane_n, uint32_t t_sec,
                     const timestream::Stamp& ts, uint32_t now_ms);

  Close lastClose() const { return close_; }
  // Windows the open run speaks for, including the one its record itemises.
  int runLength() const { return run_len_; }

  // The stable core over the trailing history: entities seen in at least
  // ENTITYPERCEPT_CORE_N of the last ENTITYPERCEPT_CORE_M windows. `coreWindows()` is
  // how many windows of history it was computed over — a reader needs it to tell an
  // empty core that is WARMING UP from one that means the environment is unstable.
  int coreCount() const;
  bool coreEntry(int i, const uint8_t*& id, uint8_t& kind) const;
  int coreWindows() const { return hist_len_; }

  void reset(uint32_t now_ms);

 private:
  struct Key { uint8_t id[ENTITY_ID_LEN]; uint8_t kind; };

  int slotFor(const uint8_t id[ENTITY_ID_LEN], uint8_t kind);
  void histClear();
  void histPush();                       // fold this window's set into the ring
  int  core(Key* out, int cap) const;    // -> count written
  static bool sameKey(const Key& a, const Key& b);
  void breakRun();
  // Would folding this window exceed the union the COVERED block can carry?
  bool unionWouldOverflow() const;
  void foldCovered(const timestream::Stamp& ts, uint32_t window_ms);

  EntityStats ents_[ENTITYPERCEPT_MAX_ENTITIES];
  int ent_count_;
  uint32_t window_start_ms_;
  Close close_;

  // Trailing window history — the core's only input. A ring of the last M windows'
  // KEY SETS (not their counts): the core asks "in how many windows did this appear",
  // so per-window sightings are irrelevant and storing them would be a bigger buffer
  // saying the same thing.
  Key hist_[ENTITYPERCEPT_CORE_M][ENTITYPERCEPT_MAX_ENTITIES];
  uint8_t hist_count_[ENTITYPERCEPT_CORE_M];
  int hist_len_;    // windows held, 0..M
  int hist_head_;   // next slot to write
  // The core, recomputed once per window in histPush() rather than on demand. A
  // read-time recompute needs a scratch buffer with no owner — the shape that becomes
  // a `static` local and quietly stops being reentrant.
  Key cur_core_[ENTITYPERCEPT_MAX_ENTITIES];
  int cur_core_n_;

  bool run_open_;
  int  run_lane_;
  int  run_len_;
  Key  run_core_[ENTITYPERCEPT_MAX_ENTITIES];
  int  run_core_n_;

  CoveredEntity cov_[ENTITYPERCEPT_MAX_UNION];
  int      cov_ent_n_;
  int32_t  cov_windows_;
  uint32_t cov_window_ms_;
  uint64_t cov_first_t_ms_;
  uint64_t cov_last_t_ms_;
};

}  // namespace entitypercept
