// FleetTime.h — ACT-III §C4: TTG-RFC-0004 §4, "A Fleet of Agents", for this fleet.
//
// §2–3 of that RFC order sayings within ONE store by file order. §4 is what replaces file
// order when several agents' episodes meet: no shared file, clocks that disagree, an ESP32
// with no RTC. Its answer has four parts, and this file is the portable core of all four:
//
//   1. STAMPS WITH A BOUND   `at: <pulse ms> ±<bound ms>` (§4.3). The pulse is TTN-RFC-0010's
//                            fleet clock; the bound is delivery delay + DRIFT_PPM × time
//                            since the last adopted beacon. A stamp with no bound orders
//                            nothing outside its own agent.
//   2. ORDER ACROSS AGENTS   (§4.4) before ⇔ same agent and earlier, OR a `follows` edge
//                            reaches it (a vector clock written as edges — the edge wins
//                            whatever the clocks say), OR the stamp ranges are disjoint.
//                            Otherwise CONCURRENT. The order is partial.
//   3. MAXIMAL FACTS         §3.2's "latest" becomes "the maximal set": one maximal
//                            candidate retires the rest; two incompatible concurrent ones
//                            are CONTESTED and both are quoted.
//   4. THE BAR               (§4.5) a view "as of bar N" over the episodes whose stamp
//                            range ENDS before bar line N. Two agents holding the same
//                            episodes then answer identically as of bar N WITHOUT
//                            COORDINATING — ACT-III §2's "agrees without coordinating",
//                            and TTG-0004 §4.8 item 4, the falsifiable claim of the RFC.
//
// ---------------------------------------------------------------------------
// ⚠ WHICH CLOCK — both traps from CLAUDE.md, and this file sits between them
// ---------------------------------------------------------------------------
// The PULSE clock, not the time stream's. The time stream is a RATCHET (fastest crystal
// heard wins) — right for "which is newer", wrong for a bound, because a bound is a
// DURATION. The pulse clock's election can move a clock backward, which is fine here:
// a stamp is not a log ordinal, it is an interval that already admits its own error, and
// order comes from interval disjointness, not from monotonicity. And per TTG-0004 §4.2
// the per-node offset lives in memory, never in a file: the stamp is the only thing that
// reaches flash, so a copied store carries no stale offset.
//
// ---------------------------------------------------------------------------
// ⚠ WHY UNBOUNDED EPISODES ARE EXCLUDED FROM EVERY BAR VIEW, INCLUDING THEIR OWNER'S
// ---------------------------------------------------------------------------
// The owner could place its own unbounded episode (it knows its own file order), and
// another agent could not. If the owner included it and the other did not, the two would
// answer differently as of bar N while holding the same episodes — the exact failure the
// bar exists to rule out. So the bar is defined over BOUNDED episodes only, for everyone;
// unbounded ones still count in each agent's LIVE view. That is the price of a view two
// agents can agree on without talking, and it is why the episode tier must move its `at:`
// to the pulse before this has anything to agree about (today's `t_ms:` stamps parse as
// unbounded — readable, never mis-ordered, just not yet in any bar).
//
// ⚠ OPEN: A STAMP IS ONLY COMPARABLE WITHIN ONE CHART FRAME. A node that self-appoints
// alone (a handheld booted with no peers) stamps against ITS OWN epoch; when it later
// yields to a better chart its pulse clock JUMPS to the new conductor's epoch, and every
// stamp it took before is in a frame nothing else shares. The bound does not cover that —
// it models drift since the last beacon, not a change of reference. Not solved here. The
// candidate fixes are (a) carry the chart (`conductor`, `era`) beside `at:` and treat
// stamps from different charts as unbounded relative to each other, or (b) a conductor
// that has never heard a peer stamps unbounded. (a) is the honest one; it needs the
// episode block to grow a line, which is the next increment's to decide.
//
// What this file does NOT do: §4.6's scene = grammar hash. These episodes are sensor
// windows read by a fixed mapping (Episode.h renderLinkEpisode), not prose read through
// grammar records, so there is nothing to hash yet. If the mapping ever becomes data, its
// hash is the scene; until then a split cannot occur and a check for one would read zero.
#ifndef SEMANTIC_FLEETTIME_H
#define SEMANTIC_FLEETTIME_H

#include <stddef.h>
#include <stdint.h>

namespace semantic {

// TTN-RFC-0010 §5 paces beacons to this drift budget; TTG-0004 §4.3's table is at 50 ppm.
#ifndef FLEETTIME_DRIFT_PPM
#define FLEETTIME_DRIFT_PPM 50
#endif
// One-way delivery uncertainty of a beacon. ESP-NOW frames on this fleet land in single-
// digit ms; 20 is a stated allowance, not a measurement, and is the first number to
// replace with one (`companion.py band` measures the residual skew).
#ifndef FLEETTIME_DELIVERY_MS
#define FLEETTIME_DELIVERY_MS 20
#endif
// Episodes a `follows` vector names at most (one per OTHER agent). Six boards today.
#ifndef FLEETTIME_MAX_AGENTS
#define FLEETTIME_MAX_AGENTS 8
#endif

// ---------------------------------------------------------------------------------------
// 1. stamps
// ---------------------------------------------------------------------------------------
struct At {
  int64_t  t_ms;       // pulse time
  uint32_t bound_ms;   // ± this
  bool     bounded;    // false: orders nothing outside its own agent, in no bar view
};

// The bound for a stamp taken now. `conductor`: this node IS the chart's reference, so
// only delivery applies. `have_beacon` false (never heard a chart): unbounded.
At stampNow(int64_t pulse_now_ms, uint32_t ms_since_beacon, bool have_beacon,
            bool conductor);
uint32_t boundMs(uint32_t ms_since_beacon, uint32_t drift_ppm = FLEETTIME_DRIFT_PPM,
                 uint32_t delivery_ms = FLEETTIME_DELIVERY_MS);

// `<t> ±<b>` (no key) for a bounded stamp; `<t>` alone for an unbounded one. ± is UTF-8
// (C2 B1) as the RFC writes it. Returns bytes, or 0 if it did not fit.
size_t renderAt(const At& a, char* out, size_t cap);
// Parse the value of an `at:` line (key optional). Anything that is not `<int> ±<uint>`
// parses as UNBOUNDED — including every pre-C4 `t_ms:… stream:… wall:…` stamp — with
// t_ms taken from a leading integer or a `t_ms:` field when present. Never fails: an
// unreadable stamp is a stamp that orders nothing, which is the safe reading.
At parseAt(const char* s);

// ---------------------------------------------------------------------------------------
// 2. order
// ---------------------------------------------------------------------------------------
struct Follows {
  uint32_t agent;
  uint32_t seq;        // the latest episode from `agent` held when this one was written
};

struct EpisodeRef {
  uint32_t agent;      // node id
  uint32_t seq;        // per-agent, increasing (NOT the lane ordinal: that wraps and
                       // collides across agents — TTG-0004 §4.7 "Identity")
  At       at;
  Follows  follows[FLEETTIME_MAX_AGENTS];
  uint8_t  n_follows;
};

enum Order : uint8_t { CONCURRENT = 0, BEFORE = 1, AFTER = 2, SAME = 3 };
// How `a` relates to `b`. `*clock_contradiction` (optional) is set when an edge decided
// against what the stamps alone would have said — the edge wins (§4.4: "whatever the
// clocks say"), but a contradiction means a bound was too tight, which is worth counting.
Order order(const EpisodeRef& a, const EpisodeRef& b, bool* clock_contradiction = 0);

// §3.2 → §4.4: the indices of the MAXIMAL candidates (no other candidate is after them).
// One maximal = it retires the rest; more than one = contested, quote them all.
// Returns the count written to `out` (≤ max).
size_t maximal(const EpisodeRef* cands, size_t n, size_t* out, size_t max);

// ---------------------------------------------------------------------------------------
// 4. the bar
// ---------------------------------------------------------------------------------------
// Bar line N is the start of Dream bar N: downbeat + N × bar_ms. A Dream bar is a whole
// number of pulse bars (meter × beat), long enough to be a Dream Cycle — an hour in the
// RFC's example; it is the caller's `bar_ms`.
int64_t barLine(int64_t downbeat_ms, uint32_t bar_ms, uint32_t n);
// Is this episode part of the view as of bar line `line`? Bounded AND its whole range
// ends strictly before the line.
bool inBar(const At& a, int64_t line);

}  // namespace semantic

#endif  // SEMANTIC_FLEETTIME_H
