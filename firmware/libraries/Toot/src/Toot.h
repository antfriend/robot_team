// Toot.h — the 250-byte robot_team wire frame.
//
// Layout (little-endian multi-byte fields), matching
// toot_network_architecture.md section 3:
//
//   off  field         bytes
//   0    magic         2     0x54 0x54 ("TT")
//   2    version       1
//   3    type          1     see Type
//   4    src_node_id   4
//   8    toot_seq      4     (src,seq) is the dedup key
//   12   chunk_idx     1
//   13   chunk_total   1
//   14   locus_addr    16    @LATxLONy packed
//   30   ttl           1
//   31   flags         1
//   32   payload_len   1     <= 208
//   33   payload       <=208
//   ...  hmac          8     trunc HMAC-SHA256 over header+payload
#pragma once
#include <stdint.h>
#include <stddef.h>
#include <string.h>

namespace toot {

const uint8_t MAGIC0 = 0x54;  // 'T'
const uint8_t MAGIC1 = 0x54;  // 'T'
const uint8_t VERSION = 1;

const size_t HEADER_LEN = 33;
const size_t HMAC_LEN = 8;
const size_t MAX_BODY = 208;
const size_t MAX_FRAME = HEADER_LEN + MAX_BODY + HMAC_LEN;  // 249
const size_t LOCUS_LEN = 16;

enum Type : uint8_t {
  HELLO = 1,      // periodic beacon: node id, role, locus, channel
  PERCEPT = 2,    // a @PERCEPT fragment from a K10
  BELIEF = 3,     // a @BELIEF node from Dream-Cycle consolidation
  CMD = 4,        // companion -> node directive
  ACK = 5,        // confirms (src,seq[,chunk])
  RELAY = 6,      // out-of-range toot for a LoRa node to forward
  TTDB_REQ = 7,   // companion -> node: "share part or all of your TTDB"
  TTDB_DATA = 8,  // node -> companion: one offset-addressed slice of the TTDB
  TIME_SYNC = 9,  // companion -> fleet: set the wall clock (TTN-RFC-0008)
  TIME_REQ = 10,  // companion -> node: "report your epoch now" (skew probe)
  TIME_RESP = 11, // node -> companion: current epoch (ms)
  TTDB_PUT = 12,  // companion -> node: one slice of a pushed belief (TTN-RFC-0009)
  PULSE = 13,     // conductor -> fleet: band chart + time-base beacon (TTN-RFC-0010)
};

enum Flags : uint8_t {
  FLAG_WANT_ACK = 1 << 0,
  FLAG_ENCRYPTED = 1 << 1,
};

// TTDB_REQ payload layout:
//   [0]     mode (TtdbReqMode)
//   [1..4]  target_node_id (u32 LE) — only the addressed node answers
//   [5..8]  start (u32 LE)   } RANGE mode only
//   [9..12] end   (u32 LE)   }
// src_node_id in the header is the requester (the orchestrator).
enum TtdbReqMode : uint8_t {
  TTDB_REQ_WHOLE = 0,   // entire live TTDB (/ttdb.md)
  TTDB_REQ_RANGE = 1,   // bytes [start,end) of the live TTDB
  TTDB_REQ_BELIEF = 2,  // entire stored belief object (/belief.md, TTN-RFC-0009 §3)
  TTDB_REQ_RECORDING = 3,  // the last beat-scheduled audio capture (CMD_RECORD), as a
                           // RECHDR header + 16-bit mono PCM. In RAM, not on flash: it
                           // is a one-shot buffer that does not survive a reboot.
};

// RECHDR — the header prepended to a CMD_RECORD capture, little-endian.
//
// The point of this header is that the fleet's clocks DO NOT have to agree. Measured
// 2026-07-28, nodes hold ~2-4 ms of each other (worst 5.5 ms ~ 1.9 m of sound) but the
// whole fleet wanders together by 15-25 ms for reasons not yet explained. Rather than
// bet on that going away, every node reports what it BELIEVED the time was when it took
// sample 0 — its band epoch, its adopted pulse offset, and its fleet-synced epoch. A
// shared wobble then becomes a correction the companion can apply, instead of an error
// baked into the audio. `start_band_epoch` minus `req_band_epoch` is the node's own
// lateness, which is a measurement rather than an unknown.
const uint32_t RECHDR_MAGIC = 0x31524554;   // "TER1" LE  (Toot rEcording R1)
const size_t   RECHDR_LEN = 64;
//   [0..3]   magic u32 = RECHDR_MAGIC
//   [4..7]   node_id u32
//   [8..11]  sample_rate u32
//   [12..15] samples u32                (16-bit mono, follow at [RECHDR_LEN..])
//   [16..23] start_band_epoch_ms u64    what we believe sample 0 landed on
//   [24..31] req_band_epoch_ms u64      what we were ASKED for (difference = lateness)
//   [32..39] pulse_offset_ms i64        our adopted offset from the conductor
//   [40..47] fleet_epoch_ms u64         TIME_SYNC epoch at sample 0 (0 if unsynced)
//   [48..51] era u32                    chart era; a mismatch invalidates comparison
//   [52..55] conductor_id u32
//   [56..57] beat_period_ms u16
//   [58]     flags u8
//   [59..63] reserved
enum RecFlags : uint8_t {
  REC_FLAG_SYNCED = 1 << 0,   // fleet_epoch_ms is meaningful
  REC_FLAG_LATE   = 1 << 1,   // the start instant had already passed on arrival
  REC_FLAG_SELF   = 1 << 2,   // our own speaker sounded during the capture (§3.3)
};

// CMD payload layout — the orchestrator drives node behavior (companion.md §4b).
//   [0]     op (CmdOp)
//   [1..4]  target_node_id (u32 LE) — only the addressed node acts + ACKs
//   [5..]   op-specific args
// CMD is a payload convention over the existing CMD type (like TtdbReqMode over
// TTDB_REQ), so it needs no new toot type / RFC. Sent want_ack so the laptop
// gets delivery confirmation (TTN-RFC-0007).
enum CmdOp : uint8_t {
  CMD_PING = 0,          // no-op; accept + ACK (reliability smoke test)
  CMD_SET_LED = 1,       // args: R,G,B (3 bytes) — override the indicator LED
  CMD_CLEAR_LED = 2,     // no args — return the LED to local agent control
  CMD_GET_STATUS = 3,    // no args — node replies a STATUS PERCEPT (not want_ack)
  CMD_BEEP = 4,          // args: freq_hz u16 | dur_ms u16 (both LE; 0 args = default)
  CMD_SET_INTERVAL = 5,  // args: interval_ms u16 LE — agent sense/act cadence
  CMD_PLAY = 6,          // no args — start the node's melody/part (K10 song); boots off
  CMD_STOP = 7,          // no args — stop the node's melody/part
  CMD_CLEAR_PERCEPTS = 8,  // args: lane u8 (optional; 0 or absent = ALL percept lanes
                           // 94..97, else that one lat). Drops consumed percept
                           // records from the live TTDB (SP1 prune after
                           // consolidation; flash rewrite, so radio callers MUST
                           // defer it to loop()). An older sender omits the byte and
                           // gets the all-lanes prune, which is the safe default: the
                           // @LAT96 entity lane had no way to be cleared at all, and
                           // it is what grew a TTDB past the size its own bridged
                           // pull can carry (companion.md §6, 2026-07-31).
  CMD_GET_GPS = 9,         // no args — GPS-bearing node (T-Deck Plus) replies a GPS
                           // PERCEPT (semantic positioning SP2: the roaming
                           // ground-truth anchor/verifier). Cheap (no flash): the
                           // node reports its last parsed NMEA fix, so a leaf that
                           // has no GPS just answers quality:0.
  CMD_SET_SCENE = 10,      // args: scene_id u16 LE — move the band to a scene of the
                           // song (TTN-RFC-0010 chart scene). Only the CONDUCTOR owns
                           // the chart, so only the conductor applies + ACKs this;
                           // everyone else ignores it and learns the scene from the
                           // next beacon. Safe to send to NODE_BROADCAST for exactly
                           // that reason — at most one node answers, so a broadcast
                           // cannot storm ACKs, and the operator needn't know who
                           // currently holds the baton.
  CMD_RECORD = 11,         // args: start_band_epoch_ms u64 LE | dur_beats u16 LE.
                           // Capture 16-bit mono PCM starting at a BAND-CLOCK instant,
                           // so a broadcast makes every node record the SAME window of
                           // wall-clock time. That is the whole point: two nodes that
                           // captured one clap can be cross-correlated directly, with no
                           // threshold anywhere in the path — and a threshold is exactly
                           // what made the @LAT94 transient timestamps weak, because it
                           // fires at a different point on the waveform depending on
                           // distance and gain (cardputer-sensorium.md §6).
                           // Safe to broadcast; a node with no mic or no chart declines.
                           // Read the result back with TTDB_REQ_RECORDING.
  CMD_GET_INTERO = 12,     // no args — node replies an INTERO PERCEPT: its sense of its
                           // OWN body (energy, heat, room to think, its own slowness,
                           // the band it hears, its clock). The outward-facing twin of
                           // CMD_GET_STATUS, which reports what a node perceives.
                           // Deliberately cheap enough to POLL: the node reports the
                           // last sample from its own slow interoception cadence and
                           // reads no sensor and no flash in the reply path, so a
                           // console watching one node costs one small toot each way.
                           // A node with no body sense answers with zeroed fields
                           // rather than staying silent (the same honesty as
                           // CMD_GET_GPS answering quality:0 without a GPS).
  CMD_DUET = 13,           // args: partner_node_id u32 LE | role u8 (DuetRole) |
                           //       speed u8 (optional; 1 = as written, 2 = DOUBLE TIME).
                           // "You and I, now, just the two of us." A PAIR performance
                           // between exactly two nodes, deliberately NOT expressed as a
                           // chart scene: a scene is shared by the whole band, so setting
                           // one would drag every powered member in and the result would
                           // be a finale, not a duet. Instead each participant overrides
                           // its OWN part with the phrase its role names, while the
                           // chart's scene stays wherever it was — so the rest of the
                           // fleet is untouched and keeps doing whatever it was doing.
                           // Both voices ride the shared pulse step clock, which is what
                           // makes them in phase; the duet changes WHAT each plays, never
                           // WHEN. role=DUET_OFF ends it, and so does CMD_STOP.
  CMD_SET_VIEW = 14,       // args: view u8 (0..VIEW_COUNT-1 in the RECEIVER's own view
                           // table, or VIEW_NEXT to advance one). "Show me a different
                           // face of yourself."
                           //
                           // The view id is DELIBERATELY node-local and not a fleet-wide
                           // enum. Every node's screen is a different shape with different
                           // senses behind it — the K10 has an eye, a mic and a tilt; the
                           // T-Deck has three globes; a V4 has a 128x64 OLED — so a shared
                           // table would either be a lowest-common-denominator lie or would
                           // have to name views most nodes do not have. What IS shared is
                           // the verb, and VIEW_NEXT is the form that needs no table at
                           // all: one key on a console steps whatever the addressed node
                           // happens to have. A node that has only one view ACKs and does
                           // nothing, which is the honest answer.
                           //
                           // Addressed only, never broadcast: an absolute view id means
                           // something different on each board, so a broadcast would put
                           // the fleet into unrelated states while looking like one
                           // command. (VIEW_NEXT would be defensible band-wide; it is not
                           // allowed either, because then the meaning of a broadcast would
                           // depend on the argument.)
                           //
                           // This is what gives a screen-only node an input device it does
                           // not physically have: the UNIHIKER K10 has no reachable button,
                           // so the console IS its buttons (companion.md §6, 2026-08-12).
};

// CMD_SET_VIEW's "advance one" argument. 0xFF rather than a count so it cannot collide
// with a real view id on any node, present or future.
const uint8_t VIEW_NEXT = 0xFF;

// Which line a node takes in a CMD_DUET. Roles are assigned by the initiator rather than
// derived from node id, so who leads is data on the wire and not a rule in the firmware.
enum DuetRole : uint8_t {
  DUET_LEAD = 0,      // the melody
  DUET_HARM = 1,      // the harmony under it
  DUET_OFF = 0xFF,    // leave the duet, return to the song's own part
};

// Duet SPEED — how many times faster than written the pair takes the phrase. 1 = as scored,
// 2 = double time. It rides on the wire beside the roles for the same reason: the initiator
// decides how the pair plays, so this is data rather than a constant baked into two sketches
// that could disagree. Both voices MUST use the same value or they traverse the phrase at
// different rates and come apart, even though the underlying clock is still shared.
//
// It is NOT a tempo change. The band's beat period is untouched — the pair simply covers the
// phrase in half as many steps, so a duet stays locked to the same pulse the rest of the
// fleet is counting. That is the whole reason double time is a part property here and not a
// chart edit (a chart tempo change would drag the band along and needs a fleet cold-start —
// see PULSE_DEFAULT_BEAT_MS in Pulse.h).
//
// ⚠ A speed is only usable if EVERY note in the phrase still lands on a step the sequencer
// visits (score::noteAt is an exact step match). `kOdeLead`'s tied note at step 54 survives
// ÷2 and would be SILENTLY DROPPED at ÷4 — so participants validate the speed against their
// own phrase and fall back to 1 rather than mangle the melody.
const uint8_t DUET_SPEED_MAX = 4;

// TTDB_PUT payload layout (TTN-RFC-0009 §2.1) — companion -> node, one slice of a
// pushed belief object. All multi-byte fields little-endian:
//   [0..3]   target_node_id u32 — only the addressed node writes/ACKs
//   [4..7]   belief_id      u32 — monotonic; exactly-once adoption gate
//   [8..11]  total_len      u32 — full belief object size
//   [12..15] crc32          u32 — CRC-32 (zlib/IEEE) over the whole object
//   [16..19] offset         u32 — byte offset this slice writes at
//   [20..21] len            u16 — slice length (<= TTDB_PUT_MAX_SLICE)
//   [22..]   data           len bytes
const size_t TTDB_PUT_HEADER_LEN = 22;
const size_t TTDB_PUT_MAX_SLICE = MAX_BODY - TTDB_PUT_HEADER_LEN;  // 186

// STATUS payload — a node's live telemetry, returned as a PERCEPT toot in answer to
// CMD_GET_STATUS (reused type, so the bridge already forwards it; no new type/RFC):
//   [0..1]  cursor_lat   i16 LE
//   [2..3]  cursor_lon   i16 LE
//   [4..5]  temp_c_x100  i16 LE   (last sensed ambient °C × 100; 0 if none)
//   [6]     flags        u8       bit0 warm · bit1 led_override · bit2 synced
//   [7..14] epoch_ms     u64 LE   (nowEpochMs(); 0 if unsynced)
const size_t STATUS_PAYLOAD_LEN = 15;
// Optional PULSE telemetry (TTN-RFC-0010 §8) appended after the 15 base bytes, so a
// plain STATUS reader (monitor) still parses the prefix and a pulse-aware reader
// (companion.py band) reads the tail. A node only appends this when USE_PULSE:
//   [15..18] conductor_id  u32 LE   the chart owner this node is playing
//   [19..22] era           u32 LE   chart revision
//   [23..24] beat_period_ms u16 LE  tempo
//   [25..32] pulse_epoch   u64 LE   pulseNow() sampled at reply build (0 if not playing)
//   [33..40] downbeat_epoch u64 LE  band-epoch ms of beat 0
//   [41]     beat_in_bar   u8       current beat position (0 = downbeat)
//   [42]     pstate        u8       bit0 playing · bit1 conductor
//   [43..44] scene_id      u16 LE   (v2) the chart's scene — what the band is playing
// Same additive discipline as the PULSE beacon: a reader that knows only the 43-byte
// layout still parses everything before the scene, so `monitor`/`band` keep working
// against a node that hasn't been reflashed yet.
const size_t STATUS_PULSE_PAYLOAD_LEN_V1 = 43;
const size_t STATUS_PULSE_PAYLOAD_LEN = 45;

// GPS PERCEPT payload — a GPS-bearing node's last NMEA fix, returned as a PERCEPT
// toot in answer to CMD_GET_GPS (semantic positioning SP2, ttn-semantic-positioning.md
// §3: the T-Deck GPS is the roaming ground-truth anchor + verifier, never an inference
// input). PERCEPT is an existing type (bridge already forwards it), so no new type/RFC.
// Its 24-byte length distinguishes it from a STATUS PERCEPT (15 or 43). All fields LE:
//   [0..3]   lat_1e7    i32   latitude  * 1e7 (degrees; == u-blox/NMEA scaling)
//   [4..7]   lon_1e7    i32   longitude * 1e7
//   [8..11]  alt_cm     i32   MSL altitude, centimetres
//   [12]     quality    u8    GGA fix quality (0 no fix · 1 GPS · 2 DGPS)
//   [13]     sats       u8    satellites used in the fix
//   [14..15] hdop_x10   u16   horizontal dilution of precision * 10
//   [16..23] epoch_ms   u64   node nowEpochMs() at reply (0 if unsynced) — when, not where
const size_t GPS_PERCEPT_PAYLOAD_LEN = 24;

// INTERO PERCEPT payload — a node's INTEROCEPTION, returned as a PERCEPT toot in answer
// to CMD_GET_INTERO (cardputer-sensorium.md §4.5). Same payload-convention discipline as
// STATUS and GPS: an existing toot type (so the bridge already forwards it), and its
// 21-byte length distinguishes it from a STATUS (15/43/45) or GPS (24) PERCEPT.
//
// This is the SEMANTIC data behind an interoception screen, not the screen: numbers a
// receiver renders in its own idiom, at its own size, in its own colours. A remote
// console draws the same body the node draws for itself — nothing pixel-shaped, nothing
// display-specific, and nothing that assumes the two panels are the same shape. That is
// what makes "show me another node's body" a TTCP render rather than a framebuffer copy.
// All fields LE:
//   [0..1]   bat_mv         u16   pack millivolts (0 = this node has no battery sense)
//   [2]      bat_pct        u8    state of charge 0-100 (255 = unknown)
//   [3]      bat_trend      i8    +1 filling · -1 draining · 0 steady (measured, NOT a
//                                 charge-state claim — most boards have no VBUS sense)
//   [4..5]   die_c_x10      i16   DIE temperature x10 (not ambient; -32768 = none)
//   [6..7]   maxalloc_kb    u16   largest CONTIGUOUS heap block, KiB — never free heap,
//                                 which reads ~5x higher and refuses the allocation
//                                 anyway (companion.md §6)
//   [8..11]  uptime_s       u32   seconds since boot
//   [12..13] worst_loop_ms  u16   worst loop pass in the node's current profiler window.
//                                 The node's own sense of its response time: the toot
//                                 link is serviced once per pass, so this IS what the
//                                 mesh feels as rtt.
//   [14..15] beat_period_ms u16   tempo of the chart it is playing (0 = no chart)
//   [16..19] conductor_id   u32   who it believes holds the baton (0 = nobody)
//   [20]     flags          u8    bit0 synced · bit1 conductor · bit2 has-chart ·
//                                 bit3 VOICING (its own voice is sounding a part)
const size_t INTERO_PERCEPT_PAYLOAD_LEN = 21;
enum InteroFlag : uint8_t {
  INTERO_SYNCED = 1 << 0,
  INTERO_CONDUCTOR = 1 << 1,
  INTERO_PLAYING = 1 << 2,   // has a chart — the band clock is running, NOT "is singing"
  // Is this node's own voice actually sounding a part right now (song or duet)? Distinct
  // from PLAYING on purpose: every locked node "has a chart" whether or not it makes a
  // sound, and most parts are silent in most scenes. This is the bit that answers "did it
  // join in?" — so a console can SEE a duet start from the partner's own body report,
  // instead of trusting an ACK that a blocking tone call swallows anyway (@LAT90LON70).
  INTERO_VOICING = 1 << 3,
};
const int16_t INTERO_NO_TEMP = -32768;   // this node cannot read its own temperature

enum PulseStateFlag : uint8_t {
  PSTATE_PLAYING = 1 << 0,
  PSTATE_CONDUCTOR = 1 << 1,
};
enum StatusFlag : uint8_t {
  STATUS_WARM = 1 << 0,
  STATUS_LED_OVERRIDE = 1 << 1,
  STATUS_SYNCED = 1 << 2,
};

// ACK payload layout (TTN-RFC-0007 §3). The header's src/seq belong to the
// acknowledging node, so the reference to the acked toot rides in the payload:
//   [0..3] ack_src   u32 LE — src_node_id of the toot being acknowledged
//   [4..7] ack_seq   u32 LE — toot_seq of the toot being acknowledged
//   [8]    ack_chunk u8     — chunk_idx acknowledged (0 if unchunked)
//   [9]    status    u8     — AckStatus
const size_t ACK_PAYLOAD_LEN = 10;
enum AckStatus : uint8_t {
  ACK_ACCEPTED = 0,            // toot accepted and processed
  ACK_REASSEMBLY_PENDING = 1,  // chunk stored, awaiting siblings
  ACK_DROPPED_NO_RESRC = 2,    // no reassembly slot / evicted
  // ⚠ ACCEPTED BUT NOT YET DONE — the node has DURABLY SCHEDULED the work and will do it
  // at its next boot (2026-08-13, `CMD_CLEAR_PERCEPTS` on a heap-starved node). Without
  // this the node had only two honest answers and neither was true: ACCEPTED claims work
  // that has not happened, and silence reads as "nothing will happen" when something
  // certainly will. Additive to the wire — a node that never defers never emits it, and
  // an old laptop that does not know it simply sees a non-zero status.
  ACK_DEFERRED = 3,
};

struct Toot {
  uint8_t version = VERSION;
  uint8_t type = 0;
  uint32_t src_node_id = 0;
  uint32_t toot_seq = 0;
  uint8_t chunk_idx = 0;
  uint8_t chunk_total = 1;
  uint8_t locus[LOCUS_LEN] = {0};
  uint8_t ttl = 4;
  uint8_t flags = 0;
  uint8_t payload_len = 0;
  uint8_t payload[MAX_BODY] = {0};
};

inline void put_u16(uint8_t* p, uint16_t v) { p[0] = v & 0xff; p[1] = v >> 8; }
inline void put_u32(uint8_t* p, uint32_t v) {
  p[0] = v & 0xff; p[1] = (v >> 8) & 0xff; p[2] = (v >> 16) & 0xff; p[3] = v >> 24;
}
inline uint16_t get_u16(const uint8_t* p) { return p[0] | (p[1] << 8); }
inline uint32_t get_u32(const uint8_t* p) {
  return (uint32_t)p[0] | ((uint32_t)p[1] << 8) | ((uint32_t)p[2] << 16) |
         ((uint32_t)p[3] << 24);
}
inline void put_u64(uint8_t* p, uint64_t v) {
  for (int i = 0; i < 8; ++i) p[i] = (uint8_t)(v >> (8 * i));
}
inline uint64_t get_u64(const uint8_t* p) {
  uint64_t v = 0;
  for (int i = 0; i < 8; ++i) v |= (uint64_t)p[i] << (8 * i);
  return v;
}

// CMD payload accessors (see CmdOp). cmdOp() is 0xFF (none) on a too-short body.
inline uint8_t cmdOp(const Toot& t) {
  return t.payload_len >= 1 ? t.payload[0] : 0xFF;
}
inline uint32_t cmdTarget(const Toot& t) {
  return t.payload_len >= 5 ? get_u32(t.payload + 1) : 0;
}
// CMD_CLEAR_PERCEPTS lane selector: 0 = every percept lane. Absent means 0, so a
// sender built before the argument existed still gets the all-lanes prune.
inline uint8_t cmdClearLane(const Toot& t) {
  return t.payload_len >= 6 ? t.payload[5] : 0;
}
// CMD_SET_VIEW selector. A sender that omits the byte means VIEW_NEXT, not view 0:
// "step it" is the request that is meaningful without knowing the receiver's table,
// and view 0 would silently re-assert a particular face instead.
inline uint8_t cmdView(const Toot& t) {
  return t.payload_len >= 6 ? t.payload[5] : VIEW_NEXT;
}

// TTDB_PUT addressed node (payload bytes 0..3); 0 on a too-short body.
inline uint32_t putTarget(const Toot& t) {
  return t.payload_len >= 4 ? get_u32(t.payload) : 0;
}

// CRC-32 (zlib/IEEE 802.3: poly 0xEDB88320, reflected, init+final XOR 0xFFFFFFFF).
// Pass crc=0 for a fresh sum; the return value can be fed back in as `crc` to
// continue over a split stream — so an N-byte object hashed in one call equals the
// same object hashed slice-by-slice (TTN-RFC-0009 §3). Matches Python zlib.crc32.
uint32_t crc32(uint32_t crc, const uint8_t* buf, size_t len);

// Serialize `t` into `out` (>= MAX_FRAME) and append the truncated HMAC.
// Returns total frame length, or 0 on error.
size_t encode(const Toot& t, const uint8_t* key, size_t key_len, uint8_t* out,
              size_t out_cap);

// Parse + verify (magic, version, HMAC). Returns true on success.
bool decode(const uint8_t* in, size_t in_len, const uint8_t* key,
            size_t key_len, Toot& t);

// --- ACK helpers (TTN-RFC-0007) --------------------------------------------
// Build an ACK acknowledging `orig`, sent by node `acker_id` with its own
// sequence `acker_seq`. Fills type/src/seq/payload; encode() it like any toot.
void makeAck(const Toot& orig, uint32_t acker_id, uint32_t acker_seq,
             uint8_t status, Toot& out);

// Read an ACK's payload. False if `ack` is not type ACK or is too short.
bool parseAck(const Toot& ack, uint32_t& ack_src, uint32_t& ack_seq,
              uint8_t& ack_chunk, uint8_t& status);

// True if `ack` acknowledges the toot identified by (my_id, my_seq, my_chunk) —
// the match a want_ack sender applies against its outstanding table.
bool ackMatches(const Toot& ack, uint32_t my_id, uint32_t my_seq,
                uint8_t my_chunk);

// --- Time-sync payloads (TTN-RFC-0008) -------------------------------------
//   TIME_SYNC: sync_id u32 | epoch_ms u64        (companion -> fleet)
//   TIME_REQ:  probe_id u32 | target_node_id u32 (companion -> one node)
//   TIME_RESP: probe_id u32 | node_epoch_ms u64  (node -> companion)
const size_t TIME_SYNC_PAYLOAD_LEN = 12;
const size_t TIME_REQ_PAYLOAD_LEN = 8;
const size_t TIME_RESP_PAYLOAD_LEN = 12;

bool parseTimeSync(const Toot& t, uint32_t& sync_id, uint64_t& epoch_ms);
bool parseTimeReq(const Toot& t, uint32_t& probe_id, uint32_t& target);
bool parseTimeResp(const Toot& t, uint32_t& probe_id, uint64_t& node_epoch_ms);

// --- TTDB_PUT slice (TTN-RFC-0009) -----------------------------------------
// Read a TTDB_PUT slice's fields. `data` points into t.payload (not copied).
// False if `t` is not TTDB_PUT or the declared len overruns the payload.
bool parsePut(const Toot& t, uint32_t& target, uint32_t& belief_id,
              uint32_t& total_len, uint32_t& crc, uint32_t& offset,
              const uint8_t*& data, uint16_t& len);

// --- PULSE beacon (TTN-RFC-0010) -------------------------------------------
// The band chart + time-base: conductor_id | era | conductor_epoch | downbeat_epoch
// | beat_period_ms | meter_beats | flags | scene_id. Carried rarely (drift-paced),
// never per beat. `conductor_epoch` is the conductor's pulseNow() sampled as the
// beacon is built — a follower adopts (epoch - recv_millis) as its band-clock offset.
//
// `scene_id` (v2, bytes [28..29]) is the band's shared position in a multi-part song:
// the chart says not just how fast to play but WHAT to play. It rides the chart, so it
// inherits the chart's properties for free — it propagates on the same rare beacon and
// it SURVIVES CONDUCTOR HANDOFF (selfAppoint(takeover) keeps the chart and only bumps
// the era), which is the whole point: the song's position outlives the node that was
// counting it.
//
// Wire compatibility is two-way, because the fleet is flashed one cable at a time:
// a v1 (28-byte) beacon from a not-yet-reflashed node parses here as scene 0, and a
// v2 (30-byte) beacon parses on v1 firmware because its length check is `>= 28` and it
// ignores the tail. So a half-reflashed fleet still shares one time-base; it just
// hasn't got a shared scene until the conductor is on v2.
const size_t PULSE_PAYLOAD_LEN_V1 = 28;  // legacy; still accepted on the wire
const size_t PULSE_PAYLOAD_LEN = 30;     // current; what builders emit + buffers hold
enum PulseFlag : uint8_t {
  PULSE_LAPTOP_TIMEBASE = 1 << 0,  // pulse clock == laptop wall epoch (TTN-RFC-0008)
};
// Build a PULSE payload into `p` (>= PULSE_PAYLOAD_LEN). Returns bytes written.
uint8_t buildPulse(uint8_t* p, uint32_t conductor_id, uint32_t era,
                   uint64_t conductor_epoch, uint64_t downbeat_epoch,
                   uint16_t beat_period_ms, uint8_t meter_beats, uint8_t flags,
                   uint16_t scene_id = 0);
// Read a PULSE payload. False if `t` is not PULSE or is shorter than the v1 layout.
// `scene_id` (optional) reads 0 for a v1 beacon that carries no scene.
bool parsePulse(const Toot& t, uint32_t& conductor_id, uint32_t& era,
                uint64_t& conductor_epoch, uint64_t& downbeat_epoch,
                uint16_t& beat_period_ms, uint8_t& meter_beats, uint8_t& flags,
                uint16_t* scene_id = nullptr);

// --- BLE proximity advert (semantic positioning SP0, near-range tier) --------
// A tiny BLE manufacturer-specific-data blob so a node can be heard + ranged by RSSI
// over Bluetooth as well as ESP-NOW (ttn-semantic-positioning.md §3 Phase 0). It is NOT
// a 250-byte toot — a BLE advertisement is ~24 usable bytes — so it carries only the
// sender's node id plus a key-derived tag. The tag is a static HMAC (a beacon is
// inherently replayable), so it PROVES key possession — enough to keep non-fleet /
// keyless BLE devices out of the percept histogram — but is not per-message auth like a
// toot. Layout (all multi-byte fields little-endian):
//   [0..1]  company_id u16 = BLE_COMPANY_ID (required BLE AD framing)
//   [2]     magic      u8  = BLE_ADVERT_MAGIC
//   [3]     version    u8  = BLE_ADVERT_VERSION
//   [4..7]  node_id    u32
//   [8..9]  tag        u16 = first 2 bytes of HMAC-SHA256(key, bytes[2..7])
const size_t BLE_ADVERT_LEN = 10;
const uint16_t BLE_COMPANY_ID = 0xFFFF;   // reserved/no-company id (test use)
const uint8_t BLE_ADVERT_MAGIC = 0x54;    // 'T' (Toot)
const uint8_t BLE_ADVERT_VERSION = 1;

// Write the fleet BLE advert for `node_id` into `out` (>= BLE_ADVERT_LEN). Returns the
// byte count written (BLE_ADVERT_LEN), or 0 if `cap` is too small.
size_t buildBleAdvert(uint8_t* out, size_t cap, uint32_t node_id,
                      const uint8_t* key, size_t key_len);
// Parse a candidate BLE manufacturer-data blob. Returns true and sets `node_id` only
// when company/magic/version match AND the key tag verifies; false otherwise.
bool parseBleAdvert(const uint8_t* data, size_t len, const uint8_t* key, size_t key_len,
                    uint32_t& node_id);

// What the FIRST execution of a (src,seq) actually did. The re-ACK path replays this
// instead of assuming success.
//
// 🛑 THE BUG THIS EXISTS FOR (2026-08-13). The dedup re-ACK used to answer every duplicate
// with `ACK_ACCEPTED` unconditionally. That is right for an op that ACKs unconditionally,
// and it MANUFACTURES SUCCESS for one that does not: `CMD_CLEAR_PERCEPTS` deliberately
// ACKs only when the prune worked ("so a failed prune is loud and the laptop retries").
// On the Cardputer the first attempt ran, failed, and correctly stayed silent — and
// attempts 2..4, carrying the same (src,seq), were re-ACKed by this path. The laptop
// printed `ACK on attempt 4 — APPLIED` for a prune that never happened, and only a re-pull
// exposed it.
//
// ⚠ THE DIRECTION OF THE REMAINING ERROR IS A DELIBERATE CHOICE. A duplicate whose first
// execution refused, or has not finished yet, now gets SILENCE — so the laptop may report
// "NOT applied" for something still in flight or later successful. That is a false
// NEGATIVE, which this project already documents, detects with a ping, and resolves by
// re-pull ([[band-play-ack-false-negative]]). A false POSITIVE has no such safety net: it
// reads as done and stops anyone looking. Given only one of the two can be eliminated
// without a new wire status, eliminate the silent one.
// 📎 Follow-up worth having: an `ACK_REFUSED` status would turn that silence into "I ran
// it and it failed", which is strictly better than both. It is additive to the wire
// (old nodes never emit it), so it can land later without a flag day.
enum DedupOutcome : uint8_t {
  DEDUP_PENDING = 0,   // dispatched; outcome not known yet (deferred flash work)
  DEDUP_ACKED,         // first execution accepted it and ACKed — a dup may be re-ACKed
  DEDUP_REFUSED,       // first execution ran and withheld its ACK — a dup must NOT ACK
  DEDUP_DEFERRED,      // first execution SCHEDULED it — a dup replays ACK_DEFERRED
};

// Small ring of seen (src,seq) keys plus what the first execution of each one did.
// seen() returns true if already present, otherwise records the key and returns false.
class DedupSet {
 public:
  explicit DedupSet(size_t cap = 64) : cap_(cap), head_(0), filled_(0) {
    ring_ = new Entry[cap_];
  }
  ~DedupSet() { delete[] ring_; }
  bool seen(uint32_t src, uint32_t seq) {
    for (size_t i = 0; i < filled_; ++i)
      if (ring_[i].src == src && ring_[i].seq == seq) return true;
    ring_[head_].src = src;
    ring_[head_].seq = seq;
    ring_[head_].outcome = DEDUP_PENDING;
    head_ = (head_ + 1) % cap_;
    if (filled_ < cap_) ++filled_;
    return false;
  }

  // What the first execution of this key did. An unknown key reads PENDING — the honest
  // answer, and the one that withholds an ACK rather than inventing one.
  DedupOutcome outcome(uint32_t src, uint32_t seq) const {
    for (size_t i = 0; i < filled_; ++i)
      if (ring_[i].src == src && ring_[i].seq == seq) return ring_[i].outcome;
    return DEDUP_PENDING;
  }

  // Record what the dispatch decided. ⚠ UPDATE-ONLY, NEVER INSERT: the trusted USB link is
  // deliberately NOT deduped so the laptop can retry, and this is called from the shared
  // dispatch that both transports run through. Inserting here would quietly start
  // deduping USB — turning a supported retry into a dropped one.
  void setOutcome(uint32_t src, uint32_t seq, DedupOutcome o) {
    for (size_t i = 0; i < filled_; ++i)
      if (ring_[i].src == src && ring_[i].seq == seq) { ring_[i].outcome = o; return; }
  }

 private:
  struct Entry {
    uint32_t src = 0;
    uint32_t seq = 0;
    DedupOutcome outcome = DEDUP_PENDING;
  };
  Entry* ring_;
  size_t cap_, head_, filled_;
};

#ifndef TOOT_REASSEMBLY_MAX_CHUNKS
#define TOOT_REASSEMBLY_MAX_CHUNKS 8   // cap: 8*208 = 1664 B per logical toot
#endif
#ifndef TOOT_REASSEMBLY_SLOTS
#define TOOT_REASSEMBLY_SLOTS 2        // concurrent (src,seq) sets (TTN-RFC-0007 §6)
#endif
#ifndef TOOT_REASSEMBLY_TTL_MS
#define TOOT_REASSEMBLY_TTL_MS 5000    // evict a stalled partial set
#endif

// Reassembles a logical toot split across chunk_idx/chunk_total that share one
// (src,seq) (TTN-RFC-0007 §6). Transport-agnostic and bounded for tight RAM. It
// owns its own per-chunk dedup (the global DedupSet keys on (src,seq) alone, which
// would wrongly collapse a chunked toot's siblings) plus a small recently-completed
// ring so a duplicate arriving after completion is re-ACKed rather than re-buffered.
class Reassembler {
 public:
  enum Result : uint8_t {
    NEED_MORE,      // chunk stored, awaiting siblings -> ACK REASSEMBLY_PENDING
    COMPLETE,       // this chunk completed the set; body()/bodyLen() valid -> ACCEPTED
    DUPLICATE,      // chunk already present in an open set -> re-ACK PENDING
    COMPLETED_DUP,  // (src,seq) completed earlier -> re-ACK ACCEPTED, no re-buffer
    NO_RESOURCE,    // no slot for a new key -> ACK DROPPED_NO_RESRC
    BAD,            // malformed (total<=1, total>max, idx>=total, total mismatch)
  };

  // Feed a decoded chunk toot. now_ms drives TTL eviction. On COMPLETE the
  // assembled body is at body()/bodyLen() until the next offer().
  Result offer(const Toot& t, uint32_t now_ms);
  const uint8_t* body() const { return out_; }
  size_t bodyLen() const { return out_len_; }

 private:
  struct Slot {
    bool used = false;
    uint32_t src = 0, seq = 0;
    uint8_t total = 0, got = 0;
    uint32_t last_ms = 0;
    bool have[TOOT_REASSEMBLY_MAX_CHUNKS];
    uint16_t len[TOOT_REASSEMBLY_MAX_CHUNKS];
    uint8_t buf[TOOT_REASSEMBLY_MAX_CHUNKS * MAX_BODY];
  };
  Slot* find(uint32_t src, uint32_t seq);
  Slot* allocate(uint32_t now_ms);
  bool recentlyCompleted(uint32_t src, uint32_t seq) const;
  void markCompleted(uint32_t src, uint32_t seq);

  static const size_t kCompletedCap = 16;
  Slot slots_[TOOT_REASSEMBLY_SLOTS];
  uint32_t comp_src_[kCompletedCap] = {0};
  uint32_t comp_seq_[kCompletedCap] = {0};
  bool comp_valid_[kCompletedCap] = {false};
  size_t comp_head_ = 0;
  uint8_t out_[TOOT_REASSEMBLY_MAX_CHUNKS * MAX_BODY];
  size_t out_len_ = 0;
};

}  // namespace toot
