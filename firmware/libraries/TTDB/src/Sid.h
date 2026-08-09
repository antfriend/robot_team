// Sid.h — stable record identity (TTDB-RFC-0010 §4), the decision that gates FIELD lanes.
//
// A record here is named by its ORDINAL POSITION in its lane (`@LAT97LON3`), which is the
// one form of name that cannot survive reclamation: emptying a lane re-points every
// existing citation at a different record. `@LAT100` boundaries exist to make that legible,
// and they work — but the boundary lane has a 32-marker lifetime budget and no prune path
// of its own, so it is a cost that only ever goes up.
//
// TTDB-RFC-0004 already sanctioned the alternative in two MUSTs the percept lanes declined:
// §2 *"coordinates MAY be derived from a stable hash"* and §4 *"once assigned, an ID MUST
// NOT change for the same record."* `sid` is that option, taken: **the coordinate stays the
// address, the sid becomes the identity**, so TTCP navigation, `isNodeRecord()`, the globes
// and every index keep working untouched.
//
// ---------------------------------------------------------------------------
// THE INPUT WAS MEASURED, NOT CHOSEN (scripts/sid_probe.py, 2026-08-09)
// ---------------------------------------------------------------------------
// RFC-0010 §9 proposed FNV-1a over `(node_id, lane, stream, t_ms)`. Run against all 78
// archived TTDBs in `master/` — 6683 records in lanes >= 90 — that input produced **538
// INPUT collisions (8.0%)**: two different records with the same name. Not a hash problem.
// No width fixes it. The breakdown is fully explained and it is the whole design:
//
//   @LAT91  83.2%   LINK-STABLE — one belief per (peer, proto), several written in one
//                   fold pass, and REVISED over time. Its identity is a KEY, not a moment.
//   @LAT100 42.7%   LANE-PRUNED — one prune of lanes 94..97 writes four markers at one
//                   instant. Identity is (generation, lane), not the clock.
//   @LAT96  10.1%   } every one of these is on `synced:0` or `stream:0x00000000`, where
//   @LAT95   5.1%   } t_ms is bare local millis() that RESTARTS AT EVERY BOOT. The
//   @LAT97   4.6%   } documented "comparable with nothing but this node's own records"
//   @LAT94   4.3%   } turns out not to be comparable with itself either, across a reboot.
//   @LAT92   2.8%   }
//   @LAT90/93/99  0.0% — these three are already uniquely named by time.
//
// Adding a digest of the record BODY takes that to **0 input collisions and 0 true hash
// collisions in 6672 distinct records** — and, in the same run, 9 cases of the same record
// pulled into two different archive files receiving the SAME sid. That stability across a
// re-pull is the property the whole mechanism is for.
//
// ---------------------------------------------------------------------------
// TWO IDENTITY KINDS, AND THE AXIS IS ORTHOGONAL TO THE MEMORY CLASS
// ---------------------------------------------------------------------------
// RFC-0010 §2 classifies lanes as EVIDENCE / FIELD / PROVENANCE — what may be reclaimed.
// This is a SECOND, INDEPENDENT question: what makes two records the same record.
//
//   EVENT — an observation. It happened once, at an instant, and its content never
//           changes. sid = H(node, lane, stream, t_ms, H(body)).
//   KEY   — a standing row about a subject, revised or reinforced over time. sid =
//           H(node, lane, natural_key). **No time and no body**, because both change while
//           the record's identity must not — RFC-0004 §4 in as many words.
//
// ⚠ THE BODY DIGEST IS REQUIRED FOR EVENT AND FORBIDDEN FOR KEY, and getting that backwards
// breaks a different thing each way. Body-in on a KEY lane forks a belief's identity on
// every revision, so a citation to it dangles the moment Rule 3 folds one more outcome.
// Body-out on an EVENT lane is the 8% measured above.
//
// ⚠ @LAT91 is EVIDENCE with KEY identity; a FIELD trace is FIELD with KEY identity;
// @LAT96 is EVIDENCE with EVENT identity; @LAT100 is PROVENANCE with KEY identity. The two
// axes really are independent — no lane's memory class predicts its identity kind.
//
// ---------------------------------------------------------------------------
// THE UNIQUENESS DOMAIN IS (node, lane) — DO NOT WIDEN THE HASH, NARROW THE CLAIM
// ---------------------------------------------------------------------------
// Measured birthday risk at 32 bits: **2.6e-7** at a lane's 48-record cap, **7.6e-6** at a
// node's 256-record file budget, **5.2e-3** over the present 6672-record archive — and
// **0.69 at 100k records**. The consolidated corpus in `master/` grows without bound, so a
// sid is NOT corpus-unique and must never be treated as such. A citation already carries the
// coordinate, so the scope costs nothing: `derived_from@LAT97LON3#a1b2c3d4` resolves within
// one lane of one file. ⚠ Any cross-node index MUST key on `(node_id, lane, sid)`.
//
// ---------------------------------------------------------------------------
// ⚠ ON COLLISION, REFUSE — DO NOT PERTURB. This corrects RFC-0010 §4.2's own text.
// ---------------------------------------------------------------------------
// §4.2 said to "perturb the discriminator and retry, bounded". That is self-defeating: the
// entire value of a stable id is that **a reader holding nothing but the file can recompute
// it and check it**, which is what makes a `#sid` mismatch mean `stale` reliably. A
// perturbed sid is not recomputable from the record, so a reader could no longer tell
// "perturbed on write" from "the lane was pruned under this citation" — it would destroy
// exactly the property being bought. At 2.6e-7 per lane, refusing is affordable.
//
// For EVENT identity refusal is also almost never a loss: two records with the same node,
// lane, stream, t_ms AND body digest are the same observation written twice, so the correct
// action is duplicate-suppress and count. For KEY identity a collision means two different
// natural keys hashed together — a lane-design error, and it must be loud.
#pragma once
#include <stdint.h>
#include <stddef.h>

namespace sid {

// FNV-1a, 32-bit. Chosen for being computable on-node in integer arithmetic with no table
// and no allocation, and trivially reproducible in `companion.py` — the two implementations
// must agree byte for byte or a laptop-side reader cannot verify a node's ids.
const uint32_t FNV_OFFSET = 0x811c9dc5u;
const uint32_t FNV_PRIME  = 0x01000193u;

inline uint32_t fnv1aInit() { return FNV_OFFSET; }
inline uint32_t fnv1aByte(uint32_t h, uint8_t b) { return (h ^ b) * FNV_PRIME; }
uint32_t fnv1a(const void* data, size_t len, uint32_t h = FNV_OFFSET);

// ---------------------------------------------------------------------------
// The canonical preimage
// ---------------------------------------------------------------------------
// Fixed-width lowercase hex with `|` separators, built by hand rather than by snprintf:
// no `%llu` portability question, no locale, no endianness, and cheap on a node.
//
//   EVENT : hex8(node) '|' hex4(lane) '|' hex8(stream) '|' hex16(t_ms) '|' hex8(bodyDigest)
//   KEY   : hex8(node) '|' hex4(lane) '|' <key bytes verbatim>
//
// ⚠ `lane` is written as hex4 of its two's-complement u16 so a negative lane is still
// deterministic, even though no lane below 90 carries a sid today.
const size_t EVENT_PREIMAGE_LEN = 8 + 1 + 4 + 1 + 8 + 1 + 16 + 1 + 8;   // 48

// The digest of a record's BODY: every byte after the header line. Excluding the header is
// what makes this non-circular (the sid lives in the header) and is also what satisfies
// RFC-0010 §4.2's "MUST NOT include the record's ordinal" — the ordinal is only ever in the
// header. Returns 0 for an empty body, which `forEvent` treats as a legitimate input.
uint32_t bodyDigest(const char* body, size_t len);

uint32_t forEvent(uint32_t node, int16_t lane, uint32_t stream, uint64_t t_ms,
                  uint32_t body_digest);

// `key` is the lane's declared natural key, canonically rendered by the lane's owner. See
// the register in TTDB-RFC-0010 §4.4; e.g. `@LAT91` uses "peer:0x00000200|proto:espnow".
uint32_t forKey(uint32_t node, int16_t lane, const char* key);

// Render as the 8 lowercase hex digits the file carries. `out` needs 9 bytes.
void format(char out[9], uint32_t s);

// Parse 8 hex digits. Returns false (and leaves `out` untouched) on anything else — a
// malformed sid must read as "unverifiable", never as some other record's id.
bool parse(const char* p, size_t len, uint32_t& out);

// ---------------------------------------------------------------------------
// The writer helper — why stage 2 is a one-line change per builder
// ---------------------------------------------------------------------------
// Every record builder in this fleet renders its header FIRST and then its body, into one
// fixed buffer. A body digest therefore cannot be known when the header is written. The
// resolution is not to restructure eleven builders: render the header with the literal
// placeholder `sid:00000000`, then call this, which locates the header line, digests
// everything after it, and PATCHES THE EIGHT HEX CHARACTERS IN PLACE.
//
// So adopting stable ids costs each builder exactly one added literal in its format string
// plus one call here — and no extra buffer, which matters on a node whose largest record
// builder already holds 2624 bytes.
//
// Returns the sid written, or 0 if the buffer holds no header line or no placeholder (in
// which case nothing is modified — a record is never half-stamped).
uint32_t stampEvent(char* rec, size_t len, uint32_t node, int16_t lane, uint32_t stream,
                    uint64_t t_ms);
uint32_t stampKey(char* rec, size_t len, uint32_t node, int16_t lane, const char* key);

// Recompute an EVENT record's sid from the record text alone and compare it with the one
// the record carries. This is the property the whole mechanism buys: a reader holding
// nothing but the file can tell a genuine id from a damaged or fabricated one.
// `found`/`computed` are filled when non-null. False if there is no parsable sid.
bool verifyEvent(const char* rec, size_t len, uint32_t node, int16_t lane, uint32_t stream,
                 uint64_t t_ms, uint32_t* found, uint32_t* computed);

// The placeholder a builder writes into its header, and the field name readers look for.
extern const char kPlaceholder[];   // "sid:00000000"
extern const char kFieldName[];     // "sid:"

}  // namespace sid
