// Precision.h — TTDB-RFC-0011 stage 3: the PRECISION lane `@LAT108`, observed only.
//
// Design (normative for this code): docs/design/rfc0011-stage3.md. Read §3 before changing
// anything here: the fold MUST equal tools/pw1/pw1_fold.py's arithmetic exactly, and the
// gate (tools/stage3/stage3_gate.py) re-derives every record this writes from a pull.
//
// What it does: refold one channel's live `@LAT103` episodes FROM FLASH (no state carried
// between folds), giving `var`, `n`, `π`; render one KEY record per channel. Nothing on the
// node reads `@LAT108` — RFC §3.4 (gain) stays off.
//
// Portable: no Arduino, no FS. The glue that walks the store is PrecisionNode.h.
#pragma once
#include <stddef.h>
#include <stdint.h>

#define PRECISION_LANE 108
#define PRECISION_EPISODE_LANE 103   // = SEMANTIC_EPISODE_LANE
#define PRECISION_TIER_SPAN 8192     // = SEMANTIC_TIER_SPAN: tier k owns LON [k*8192, (k+1)*8192)
#define PRECISION_SCALE 8192         // prec_scale (RFC §4.2), PW-1/PW-1b PI_SCALE
#define PRECISION_ALPHA 4            // prec_alpha (RFC §9.1)
#define PRECISION_WRITE_DELTA 8      // prec_write_delta (RFC §9.1)
// pe_span per channel — PW-1b, RFC §8.4, registered in tools/pw1b/pw1b_constants.py.
// ⚠ Fixed by pre-registration. Never re-pick these from data; see docs/design §1 D2.
#define PRECISION_SPAN_ACOUSTIC 900
#define PRECISION_SPAN_MOTION 60
#define PRECISION_SPAN_LINK 90
// Per-window parse bounds. Firmware writes <= 8 link slots (LINKPERCEPT_MAX_PEERS) and
// <= 12 entities (ENTITYPERCEPT_MAX_ENTITIES); an overflow EXCLUDES the window with reason
// `overflow` rather than truncating it, so the gate sees a count mismatch, not a quiet skew.
#define PRECISION_MAX_LINK_KEYS 10
#define PRECISION_MAX_IDS 16
#define PRECISION_ID_MAX 16          // hex chars per entity id
#define PRECISION_PEER_MAX 12        // "0x00000200" = 10
#define PRECISION_PROTO_MAX 8        // "espnow" = 6
#define PRECISION_RECORD_BUF 768     // one rendered @LAT108 record (pinned by test_precision)

// RFC §4.3 needs `>>` on a negative int32 to be ARITHMETIC (floor), as pw1_fold.py's Python
// `>>` is. GCC on the ESP32 does that, but C++11 leaves it implementation-defined, so make a
// compiler that differs fail the BUILD — the firmware's, not just a test's.
static_assert((-1 >> 1) == -1, "RFC-0011 §4.3: >> on a negative int must be arithmetic");
static_assert((int32_t)(-6) >> 4 == -1, "RFC-0011 §4.3: (0 - 6) >> 4 must be -1");

namespace precision {

// Same numbering as semantic::Tier, which is what lets the record index name the channel.
enum Chan : uint8_t { CH_LINK = 0, CH_ENTITY = 1, CH_MOTION = 2, CH_ACOUSTIC = 3, CH_COUNT = 4 };
const char* chanName(uint8_t c);       // "link" | "entity" | "motion" | "acoustic" | "?"
int32_t spanOf(uint8_t c);             // 0 for entity (Jaccard, no span)
int chanOfLon(int32_t lon);            // tier of an @LAT103 LON, or -1

// ---- the arithmetic, exactly pw1_fold.py's ----------------------------------------------
int32_t foldStep(int32_t var, int32_t r);     // var += ((r*r) - var) >> PRECISION_ALPHA
uint8_t piFromVar(int32_t var);               // (255*SCALE) / (SCALE + var)
uint8_t confFromN(uint32_t n);                // min(240, 16*floor(log2(1+n)))  (design D4)
uint8_t pe(int32_t diff, int32_t span);       // min(255, |diff|*255 / span)

// One window as pw1's parse_record() sees it.
enum Why : uint8_t { OK = 0, NO_T_MS, NOT_WINDOW, NO_VALUE, OVERFLOW };
const char* whyName(uint8_t w);
struct LinkKey {
  char peer[PRECISION_PEER_MAX + 1];
  char proto[PRECISION_PROTO_MAX + 1];
  int32_t med;
};
struct Window {
  uint8_t why = OK;
  uint64_t t = 0;
  bool has_stream = false;
  uint64_t stream = 0;
  uint32_t run = 1;
  int32_t val = 0;                                    // acoustic / motion
  uint8_t n_ids = 0;                                  // entity
  char ids[PRECISION_MAX_IDS][PRECISION_ID_MAX + 1];
  uint8_t n_links = 0;                                // link
  LinkKey links[PRECISION_MAX_LINK_KEYS];
};
// Parse one episode record (`said: N | ` prefixes stripped line by line). Always fills `w`.
void parseWindow(uint8_t chan, const char* text, size_t len, Window& w);

// The fold over one channel, fed episodes in FILE ORDER. ~1 KB (two Windows): keep it on the
// stack of the function that runs the fold, never static (docs/design §5).
class Fold {
 public:
  explicit Fold(uint8_t chan) : chan_(chan) {}
  // `lon` = the episode's LON. Every episode of the band is passed, parsed or not.
  void add(const char* text, size_t len, int32_t lon);
  void skip(int32_t lon);              // an episode the caller could not read whole
  uint8_t chan() const { return chan_; }
  int32_t var() const { return var_; }
  uint32_t n() const { return n_; }
  uint8_t prec() const { return piFromVar(var_); }
  uint8_t conf() const { return confFromN(n_); }
  uint32_t episodes() const { return episodes_; }
  uint32_t excluded() const { return excluded_; }
  uint32_t segments() const { return segments_; }
  uint32_t peersAbsent() const { return peers_absent_; }
  uint32_t skipped() const { return skipped_; }
  int32_t from() const { return from_; }
  int32_t through() const { return through_; }

 private:
  void note(int32_t lon);
  void residual(int32_t r) { var_ = foldStep(var_, r); ++n_; }
  uint8_t chan_;
  int32_t var_ = 0;
  uint32_t n_ = 0, episodes_ = 0, excluded_ = 0, segments_ = 0, peers_absent_ = 0,
           skipped_ = 0;
  int32_t from_ = -1, through_ = -1;
  bool have_prev_ = false;
  Window prev_, cur_;
};

// The node's identity key for a channel, "node:0x%08lx|chan:%s" (RFC §4.1). False if `cap`
// is too small.
bool keyOf(char* out, size_t cap, uint32_t node, uint8_t chan);

// Render the record (docs/design §4) into `out`, header sid stamped. `stamp` is a
// timestream::buildStamp() triplet; `t_sec` wall seconds or 0. Returns bytes, or 0 if it did
// not fit (nothing is ever truncated).
size_t render(char* out, size_t cap, const Fold& f, uint32_t node, uint16_t rev,
              uint32_t created, uint32_t t_sec, const char* stamp);

// What the write rule needs from the record already on flash.
struct OnFlash {
  bool present = false;     // a parseable **PRECISION** line with prec:
  uint8_t prec = 0;
  uint16_t rev = 0;
  uint32_t created = 0;
};
void readOnFlash(const char* rec, size_t len, OnFlash& out);

// Design §4: write when nothing is on flash or |π - π_flash| > PRECISION_WRITE_DELTA; never
// when n == 0.
bool shouldWrite(const OnFlash& old, const Fold& f);

}  // namespace precision
