// v4b_relay.ino — Heltec WiFi LoRa 32 V4, RELAY / midpoint node (A32 agent).
//
// Role: spine-mid store-and-forward (toot_network_architecture.md). In Phase 4 it
// decrements ttl, dedups on (src,seq), re-signs and re-emits over LoRa. Until then
// it comes up as a verified **ESP-NOW Dream-Cycle participant** — the third node in
// the mesh — so the 3-node fleet (V4-A bridge + V4-B + K10) can be sync'd,
// reconciled, and belief-pushed before any long-range radio is wired.
//
// Built from the verified siblings: V4-A's board bring-up (OLED on Vext, ESP-NOW,
// TIME_SYNC adoption) + the K10's hard-won mesh patterns — serve a TTDB burst from
// loop() (never the recv callback, or the WiFi task starves its own TX), pace
// ESP-NOW sends behind the TX-complete callback, dedup radio-only, and re-ACK a
// dropped want_ack replay (TTN-RFC-0007 §5).
//
// LoRa (SX1262) is gated behind USE_LORA; the promiscuous store-and-forward is gated
// behind USE_RELAY_FORWARD (off here so V4-B doesn't re-broadcast the bridge's mesh
// traffic — forwarding + multi-hop is its own milestone, enabled with range
// separation or LoRa).
#include <Arduino.h>
#include <LittleFS.h>
#include <WiFi.h>
#include <esp_now.h>
#include <esp_wifi.h>

#include <Wire.h>
#include <U8g2lib.h>

#include <Toot.h>
#include <TootSerial.h>
#include <TootEspNow.h>
#include <TTDB.h>
#include <TtdbShare.h>
#include <Pulse.h>
#include <Score.h>
#include <RobotTeamConfig.h>

#define USE_LORA 0           // Phase 4: SX1262 long hops to V4-A and V4-C.
#define USE_RELAY_FORWARD 0  // multi-hop store-and-forward (needs range sep / LoRa).

// --- fleet pulse (TTN-RFC-0010) ---------------------------------------------
// V4-B plays the BACKBEAT part: pulse the onboard LED + an OLED dot on beats 2 & 4
// of the bar (the "snare"), while V4-A keeps every beat and the K10 leads. The
// shared Pulse engine owns the time-base + election; this sketch supplies transport
// (PULSE codec) + instrument. Lowest id conducts, so V4-B (0x11) follows V4-A (0x10).
#define USE_PULSE 1
static pulse::Engine gPulse;
// Heltec V4 onboard white LED (GPIO35 on V3, pin-compatible V4 — confirm vs pinmap;
// OLED dot is the guaranteed-visible fallback per TTN-RFC-0010 §7.2).
static const int      kLedPin = 35;
static const uint32_t PULSE_LED_MS = 110;
static uint32_t gLedClearMs = 0;
static bool     gBeatFlash = false;
// V4-B's PART (TTN-RFC-0010 §7): the backbeat — a flash on beats 2 & 4 (steps 4 & 12 of
// the 16-step bar), the "snare" against V4-A's steady timekeeper and the K10's melody. A
// Score::Phrase on the shared sequencer grid; REST = no tone (LED + OLED-dot hit only).
static const score::Note kPartNotes[] = {
  {4, score::REST, 1}, {12, score::REST, 1},
};
static const score::Phrase kPart = {kPartNotes, 2, 16};
// New-neighbor detection so the conductor only fast-locks a genuine newcomer (§4.2).
static uint32_t gNeighbors[8] = {0};
static int      gNeighborCount = 0;
static bool neighborIsNew(uint32_t src) {
  for (int i = 0; i < gNeighborCount; ++i)
    if (gNeighbors[i] == src) return false;
  if (gNeighborCount < (int)(sizeof(gNeighbors) / sizeof(gNeighbors[0])))
    gNeighbors[gNeighborCount++] = src;
  return true;
}

// --- onboard SSD1306 OLED (status display) ----------------------------------
// Heltec V4: SSD1306 128x64 on I2C (SDA 17 / SCL 18 / RST 21), powered through
// Vext (GPIO36, active-LOW). U8g2 on the generic esp32 core (hardware_specs.md §2).
static const int kVextCtrl = 36;            // drive LOW to power the OLED rail
static const int kOledRst = 21, kOledScl = 18, kOledSda = 17;
U8G2_SSD1306_128X64_NONAME_F_HW_I2C gOled(U8G2_R0, kOledRst, kOledScl, kOledSda);

// Live status counters rendered on the OLED. Incremented from loop() and the recv
// callback; the callback only flips gOledDirty (no I2C from the WiFi task).
static uint32_t gSerIn = 0;       // frames decoded off the USB link
static uint32_t gEspRx = 0;       // frames decoded off ESP-NOW
static uint32_t gServed = 0;      // TTDB_REQ replies served (serial + mesh)
static uint32_t gForwarded = 0;   // frames re-emitted when USE_RELAY_FORWARD
static uint32_t gLastSrc = 0;     // src_node_id of the last toot seen
static volatile bool gOledDirty = true;

static const uint32_t kNodeId = NODE_V4B_RELAY;
static const char* kTtdbPath = "/ttdb.md";
static const char* kBeliefPath = "/belief.md";
static const uint8_t kBroadcast[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
static uint8_t gLocus[toot::LOCUS_LEN] = {0};

Ttdb gDb;
TtdbShare* gShare = nullptr;
toot::DedupSet gDedup(128);
TootSerialLink gSerial(Serial);
static uint32_t gSeq = 1;

// --- wall clock (TTN-RFC-0008) ----------------------------------------------
// No RTC: epoch ms = millis() + offset adopted on TIME_SYNC. Exactly-once adoption
// is gated on a monotonic sync_id, independent of transport dedup.
static int64_t gClockOffsetMs = 0;
static bool gSynced = false;
static uint32_t gLastSyncId = 0;
static inline int64_t nowEpochMs() { return (int64_t)millis() + gClockOffsetMs; }

// A TIME_SYNC adopts the offset in the recv path (recv-time millis() is most
// accurate) and defers the TTDB log-append to loop() (flash write + re-index).
static volatile bool gSyncPending = false;
static uint32_t gPendSyncId = 0;
static uint64_t gPendEpochMs = 0;
static uint32_t gPendRecvMs = 0;

// --- pushed belief (TTN-RFC-0009) -------------------------------------------
// The companion can push a re-authored belief to V4-B as offset-addressed TTDB_PUT
// slices, written to a SEPARATE /belief.md. On a CRC-verified commit V4-B appends a
// BELIEF-ADOPTED record to its own live TTDB (@LAT98 lane) — self-attestation that it
// integrated exactly those bytes. V4-B has no agent cadence to retune, so it stores +
// attests (no DIRECTIVE action, unlike the K10). Exactly-once on a monotonic belief_id.
static bool gBeliefAdopted = false;
static uint32_t gBeliefId = 0;
static bool gPutActive = false;
static uint32_t gPutId = 0, gPutTotal = 0, gPutCrc = 0, gPutNext = 0, gPutCrcRun = 0;
static volatile bool gBeliefSyncPending = false;
static uint32_t gPendBeliefId = 0, gPendBeliefBytes = 0, gPendBeliefCrc = 0;
static uint32_t gPendBeliefRecvMs = 0;

// Write one TTDB_PUT slice into /belief.md; on completion CRC-verify and schedule the
// adoption attestation. Idempotent on retransmit (the laptop streams strictly in
// offset order, stop-and-wait). Runs in loop() (deferred from the recv callback) so
// the flash write never blocks the WiFi task. Mirrors the K10's handlePutSlice.
static bool handlePutSlice(const toot::Toot& t) {
  uint32_t target, bid, total, crc, off;
  const uint8_t* data;
  uint16_t len;
  if (!toot::parsePut(t, target, bid, total, crc, off, data, len)) return false;
  if (target != kNodeId) return false;
  if (gBeliefAdopted && bid == gBeliefId) return true;  // already adopted: re-ACK

  if (off == 0) {
    File f = LittleFS.open(kBeliefPath, "w");
    if (!f) return false;
    f.write(data, len);
    f.close();
    gPutActive = true; gPutId = bid; gPutTotal = total; gPutCrc = crc;
    gPutNext = len; gPutCrcRun = toot::crc32(0, data, len);
  } else if (gPutActive && bid == gPutId && off == gPutNext) {
    File f = LittleFS.open(kBeliefPath, "a");
    if (!f) return false;
    f.write(data, len);
    f.close();
    gPutNext += len; gPutCrcRun = toot::crc32(gPutCrcRun, data, len);
  } else if (gPutActive && bid == gPutId && off < gPutNext) {
    return true;                           // duplicate slice (ACK lost): idempotent
  } else {
    return false;                          // gap / unknown belief: force retransmit
  }

  if (gPutActive && bid == gPutId && gPutNext >= gPutTotal) {  // last slice
    gPutActive = false;
    if (gPutCrcRun == gPutCrc) {
      gBeliefAdopted = true; gBeliefId = bid;     // commit (exactly-once gate)
      gPendBeliefId = bid; gPendBeliefBytes = gPutTotal; gPendBeliefCrc = gPutCrc;
      gPendBeliefRecvMs = millis();
      gBeliefSyncPending = true;                  // attest to live TTDB from loop()
    } else {
      Serial.printf("[belief] id=%lu CRC MISMATCH got %08lX want %08lX (%luB)\n",
                    (unsigned long)bid, (unsigned long)gPutCrcRun,
                    (unsigned long)gPutCrc, (unsigned long)gPutTotal);
    }
  }
  return true;
}

// --- transports -------------------------------------------------------------
// ESP-NOW TX is async with a shallow queue; a TTDB burst overruns it and drops all
// but the first frames. Gate each send on the prior frame's TX-complete callback so
// the whole stream survives the air (the K10's Phase-1b lesson).
static volatile bool gEspNowTxDone = true;
static ESPNOW_SEND_CB(onEspNowSend, mac, status) {
  (void)status;
  gEspNowTxDone = true;
}
static bool sendEspNow(const uint8_t* frame, size_t len, void*) {
  uint32_t t0 = millis();
  while (!gEspNowTxDone && millis() - t0 < 50) delay(1);  // await prior TX
  gEspNowTxDone = false;
  bool ok = esp_now_send(kBroadcast, frame, len) == ESP_OK;
  delay(6);  // breathing room for the bridge to drain each frame to USB-CDC
  return ok;
}
static bool sendSerial(const uint8_t* frame, size_t len, void*) {
  gSerial.writeFrame(frame, len);
  return true;
}

static void emit(toot::Type type, const uint8_t* body, uint8_t n,
                 TtdbShare::SendFn send, void* ctx) {
  toot::Toot t;
  t.type = type;
  t.src_node_id = kNodeId;
  t.toot_seq = gSeq++;
  memcpy(t.locus, gLocus, toot::LOCUS_LEN);
  if (n && body) memcpy(t.payload, body, n);
  t.payload_len = n;
  uint8_t frame[toot::MAX_FRAME];
  size_t flen =
      toot::encode(t, ROBOT_TEAM_KEY, ROBOT_TEAM_KEY_LEN, frame, sizeof(frame));
  if (flen) send(frame, flen, ctx);
}

// TTN-RFC-0007: ACK `orig` on `reply` — for a freshly-accepted want_ack toot and for
// re-ACKing a dedup-dropped replay (§5).
static void emitAck(const toot::Toot& orig, uint8_t status,
                    TtdbShare::SendFn reply, void* ctx) {
  toot::Toot ack;
  toot::makeAck(orig, kNodeId, gSeq++, status, ack);
  uint8_t frame[toot::MAX_FRAME];
  size_t flen =
      toot::encode(ack, ROBOT_TEAM_KEY, ROBOT_TEAM_KEY_LEN, frame, sizeof(frame));
  if (flen) reply(frame, flen, ctx);
}

// STATUS telemetry for the `monitor` table. No agent cursor or temp sensor, so those
// fields are 0; report the synced state + epoch.
static uint8_t buildStatus(uint8_t* p) {
  toot::put_u16(p + 0, 0);
  toot::put_u16(p + 2, 0);
  toot::put_u16(p + 4, 0);
  p[6] = gSynced ? toot::STATUS_SYNCED : 0;
  toot::put_u64(p + 7, gSynced ? (uint64_t)nowEpochMs() : 0);
#if USE_PULSE
  // PULSE telemetry tail (TTN-RFC-0010 §8) for `companion.py band`.
  uint32_t now = millis();
  uint8_t bib = 0; uint16_t ph = 0; uint32_t bc = 0;
  bool playing = gPulse.phaseNow(now, bib, ph, bc);
  const pulse::Chart& ch = gPulse.chart();
  toot::put_u32(p + 15, ch.conductor_id);
  toot::put_u32(p + 19, ch.era);
  toot::put_u16(p + 23, ch.beat_period_ms);
  toot::put_u64(p + 25, playing ? (uint64_t)gPulse.pulseNow(now) : 0);
  toot::put_u64(p + 33, ch.downbeat_epoch);
  p[41] = bib;
  p[42] = (playing ? toot::PSTATE_PLAYING : 0) |
          (gPulse.conductor() ? toot::PSTATE_CONDUCTOR : 0);
  return (uint8_t)toot::STATUS_PULSE_PAYLOAD_LEN;
#else
  return (uint8_t)toot::STATUS_PAYLOAD_LEN;
#endif
}

// Serve a TTDB_REQ addressed to this node: belief mode streams the stored /belief.md
// (TTN-RFC-0009 §3 readback); any other mode streams the live TTDB. Both stream a
// burst, so radio callers must invoke this from loop() (see the deferral).
static void serveTtdbReq(const toot::Toot& req, TtdbShare::SendFn send, void* ctx) {
  if (!gShare || TtdbShare::requestTarget(req) != kNodeId) return;
  if (req.payload_len >= 1 && req.payload[0] == toot::TTDB_REQ_BELIEF) {
    static uint8_t bbuf[1536];
    File f = LittleFS.open(kBeliefPath, "r");
    size_t n = f ? f.read(bbuf, sizeof(bbuf)) : 0;
    if (f) f.close();
    gShare->handleBufferRequest(bbuf, n, send, ctx);
  } else {
    gShare->handleRequest(req, send, ctx);
  }
  gServed++;
}

// Dispatch a decoded, authenticated toot on any transport. `reply` is the transport
// to answer on. Dedup is radio-only (applied in onEspNowRecv before this), so the
// trusted USB link stays un-deduped and the laptop can retry.
static void handleToot(const toot::Toot& t, TtdbShare::SendFn reply, void* ctx) {
  bool accepted = false;
  switch (t.type) {
    case toot::TTDB_REQ:
      // The streamed TTDB_DATA reply is itself the confirmation (not separately ACKed).
      serveTtdbReq(t, reply, ctx);
      break;
    case toot::TTDB_PUT:
      // Belief slice (push). handlePutSlice writes flash, so radio callers defer this
      // to loop() (see onEspNowRecv); accept -> ACK each slice.
      accepted = handlePutSlice(t);
      break;
    case toot::CMD:
      if (toot::cmdTarget(t) == kNodeId) {
        if (toot::cmdOp(t) == toot::CMD_GET_STATUS) {
          uint8_t body[toot::STATUS_PULSE_PAYLOAD_LEN];
          uint8_t slen = buildStatus(body);
          emit(toot::PERCEPT, body, slen, reply, ctx);  // the reply is the answer
        }
        accepted = true;  // ping / set-* (no-op on V4-B) / get-status all ACK
      }
      break;
    case toot::TIME_SYNC: {
      uint32_t sid; uint64_t ems;
      if (toot::parseTimeSync(t, sid, ems)) {
        uint32_t recv_ms = millis();
        if (!gSynced || sid > gLastSyncId) {
          gClockOffsetMs = (int64_t)ems - (int64_t)recv_ms;
          gSynced = true;
          gLastSyncId = sid;
          gPendSyncId = sid; gPendEpochMs = ems; gPendRecvMs = recv_ms;
          gSyncPending = true;          // append @LAT99 log from loop()
        }
        accepted = true;                // ACK the want_ack TIME_SYNC (idempotent)
      }
      break;
    }
    case toot::TIME_REQ: {
      uint32_t pid, target;
      if (toot::parseTimeReq(t, pid, target) && target == kNodeId) {
        uint8_t body[toot::TIME_RESP_PAYLOAD_LEN];
        toot::put_u32(body + 0, pid);
        toot::put_u64(body + 4, (uint64_t)nowEpochMs());
        emit(toot::TIME_RESP, body, sizeof(body), reply, ctx);
      }
      break;
    }
#if USE_PULSE
    case toot::PULSE: {
      // Band time-base beacon (TTN-RFC-0010). Cheap (no flash) -> adopt inline;
      // millis() here is the receipt time. Not want_ack: corrected by the next.
      pulse::Chart c;
      uint64_t cond_epoch;
      if (toot::parsePulse(t, c.conductor_id, c.era, cond_epoch, c.downbeat_epoch,
                           c.beat_period_ms, c.meter_beats, c.flags))
        gPulse.onBeacon(c, cond_epoch, millis());
      break;
    }
    case toot::HELLO:
      if (neighborIsNew(t.src_node_id)) gPulse.noteNeighbor(millis());
      break;
#endif
    default:
      break;
  }
  if (accepted && (t.flags & toot::FLAG_WANT_ACK))
    emitAck(t, toot::ACK_ACCEPTED, reply, ctx);
}

// A TTDB_REQ / TTDB_PUT arriving over ESP-NOW is stashed and served from loop(): a
// burst reply or a flash write must not run in the WiFi recv callback (K10 lessons).
static volatile bool gReqPending = false;
static toot::Toot gPendingReq;
static volatile bool gPutPending = false;
static toot::Toot gPendingPut;

static ESPNOW_RECV_CB(onEspNowRecv, data, len) {
  if (len <= 0) return;
  toot::Toot t;
  if (!toot::decode(data, (size_t)len, ROBOT_TEAM_KEY, ROBOT_TEAM_KEY_LEN, t)) return;
  if (t.chunk_total > 1) return;            // no chunked consumer on V4-B (no reltest)
  if (gDedup.seen(t.src_node_id, t.toot_seq)) {
    // TTN-RFC-0007 §5: the original ACK was lost (sender retried); re-ACK the dup
    // without re-processing its body.
    if (t.flags & toot::FLAG_WANT_ACK)
      emitAck(t, toot::ACK_ACCEPTED, sendEspNow, nullptr);
    return;
  }
  gEspRx++;
  gLastSrc = t.src_node_id;
  gOledDirty = true;

  if (t.type == toot::TTDB_REQ) {
    if (!gReqPending) { gPendingReq = t; gReqPending = true; }   // defer burst to loop()
    return;
  }
  if (t.type == toot::TTDB_PUT) {
    if (!gPutPending) { gPendingPut = t; gPutPending = true; }   // defer flash to loop()
    return;
  }

#if USE_RELAY_FORWARD
  // Store-and-forward: decrement ttl, re-sign, re-emit (multi-hop milestone). Off by
  // default so V4-B doesn't re-broadcast the bridge's mesh traffic in one room.
  if (t.type != toot::ACK && t.ttl > 1) {
    toot::Toot f = t;
    f.ttl--;
    uint8_t frame[toot::MAX_FRAME];
    size_t flen = toot::encode(f, ROBOT_TEAM_KEY, ROBOT_TEAM_KEY_LEN, frame,
                               sizeof(frame));
    if (flen && sendEspNow(frame, flen, nullptr)) ++gForwarded;
    return;
  }
#endif

  handleToot(t, sendEspNow, nullptr);       // cheap toots (TIME_*, CMD): handle inline
}

// Append an @LAT99 sync-log record (deferred from the recv path). n = count of
// existing lat-99 records so each is unique under collision_policy: reject.
static void appendSyncRecord() {
  int n = 0;
  for (int i = 0; i < gDb.recordCount(); ++i)
    if (gDb.record(i).lat == 99) ++n;
  uint32_t t_sec = (uint32_t)(gPendEpochMs / 1000ULL);
  int64_t offset = (int64_t)gPendEpochMs - (int64_t)gPendRecvMs;
  char rec[200];
  int m = snprintf(
      rec, sizeof(rec),
      "\n---\n\n@LAT99LON%d | created:%lu | updated:%lu | relates:logs@LAT0LON0"
      "\n\n**SYNC** id:%lu t_ms:%llu recv_ms:%lu offset_ms:%lld\n",
      n, (unsigned long)t_sec, (unsigned long)t_sec, (unsigned long)gPendSyncId,
      (unsigned long long)gPendEpochMs, (unsigned long)gPendRecvMs,
      (long long)offset);
  if (m > 0 && gDb.appendRecord(rec, (size_t)m))
    Serial.printf("[sync] id=%lu offset=%lldms logged @LAT99LON%d (TTDB now %uB)\n",
                  (unsigned long)gPendSyncId, (long long)offset, n,
                  (unsigned)gDb.fileSize());
  else
    Serial.println("[sync] appendRecord FAILED");
}

// Append a @LAT98 BELIEF-ADOPTED attestation (deferred). V4-B has no DIRECTIVE to act
// on, so this records the integrated bytes/crc only (no applied:interval_ms).
static void appendBeliefRecord() {
  int n = 0;
  for (int i = 0; i < gDb.recordCount(); ++i)
    if (gDb.record(i).lat == 98) ++n;
  uint32_t t_sec = gSynced ? (uint32_t)(nowEpochMs() / 1000) : 0;
  char rec[256];
  int m = snprintf(
      rec, sizeof(rec),
      "\n---\n\n@LAT98LON%d | created:%lu | updated:%lu | relates:adopts@LAT0LON0"
      "\n\n**BELIEF-ADOPTED** id:%lu bytes:%lu crc:%08lX recv_ms:%lu\n",
      n, (unsigned long)t_sec, (unsigned long)t_sec, (unsigned long)gPendBeliefId,
      (unsigned long)gPendBeliefBytes, (unsigned long)gPendBeliefCrc,
      (unsigned long)gPendBeliefRecvMs);
  if (m > 0 && gDb.appendRecord(rec, (size_t)m))
    Serial.printf("[belief] adopted id=%lu %luB crc=%08lX -> @LAT98LON%d (TTDB %uB)\n",
                  (unsigned long)gPendBeliefId, (unsigned long)gPendBeliefBytes,
                  (unsigned long)gPendBeliefCrc, n, (unsigned)gDb.fileSize());
  else
    Serial.println("[belief] appendRecord FAILED");
}

// Render live status onto the OLED (called from loop(), never the recv callback).
static void renderOled() {
  char l[24];
  gOled.clearBuffer();
  gOled.setFont(u8g2_font_6x10_tf);
  gOled.drawStr(0, 9, "V4-B RELAY");
  gOled.drawStr(78, 9, USE_LORA ? "LoRa+" : "LoRa-");
#if USE_PULSE
  if (gBeatFlash) gOled.drawDisc(124, 4, 3);   // backbeat dot (beats 2 & 4)
  else gOled.drawCircle(124, 4, 3);
#endif

  snprintf(l, sizeof(l), "id %08X", (unsigned)kNodeId);
  gOled.drawStr(0, 20, l);

  if (gDb.fileSize() > 0)
    snprintf(l, sizeof(l), "TTDB %uB %dr", (unsigned)gDb.fileSize(),
             gDb.recordCount());
  else
    snprintf(l, sizeof(l), "TTDB: none");
  gOled.drawStr(0, 31, l);

  snprintf(l, sizeof(l), "ch%d sync%s", ROBOT_TEAM_ESPNOW_CHANNEL,
           gSynced ? "+" : "-");
  gOled.drawStr(0, 42, l);

  snprintf(l, sizeof(l), "rx%lu sv%lu fw%lu", (unsigned long)gEspRx,
           (unsigned long)gServed, (unsigned long)gForwarded);
  gOled.drawStr(0, 53, l);

  snprintf(l, sizeof(l), "last %08X %lus", (unsigned)gLastSrc,
           (unsigned long)(millis() / 1000));
  gOled.drawStr(0, 64, l);
  gOled.sendBuffer();
}

void setup() {
  Serial.begin(115200);
  delay(200);

#if USE_PULSE
  pinMode(kLedPin, OUTPUT);
  digitalWrite(kLedPin, LOW);
#endif

  pinMode(kVextCtrl, OUTPUT);
  digitalWrite(kVextCtrl, LOW);      // LOW = OLED power on (Heltec Vext)
  delay(50);
  gOled.begin();
  gOled.setBusClock(400000);
  renderOled();                      // splash before TTDB/ESP-NOW come up

  if (!LittleFS.begin(true) || !gDb.begin(LittleFS, kTtdbPath)) {
    Serial.println("FATAL: TTDB load failed");
  } else {
    Serial.printf("TTDB loaded: %u bytes, %d records\n",
                  (unsigned)gDb.fileSize(), gDb.recordCount());
  }
  gShare = new TtdbShare(gDb, ROBOT_TEAM_KEY, ROBOT_TEAM_KEY_LEN, kNodeId, gLocus);

  WiFi.mode(WIFI_STA);
  esp_wifi_set_channel(ROBOT_TEAM_ESPNOW_CHANNEL, WIFI_SECOND_CHAN_NONE);
  if (esp_now_init() != ESP_OK) Serial.println("FATAL: esp_now_init failed");
  esp_now_register_recv_cb(onEspNowRecv);
  esp_now_register_send_cb(onEspNowSend);   // paces TTDB_DATA bursts (see sendEspNow)
  esp_now_peer_info_t peer = {};
  memcpy(peer.peer_addr, kBroadcast, 6);
  peer.channel = ROBOT_TEAM_ESPNOW_CHANNEL;
  peer.encrypt = false;
  esp_now_add_peer(&peer);

#if USE_PULSE
  gPulse.begin(kNodeId, millis());   // follows V4-A (lower id); plays the backbeat
#endif
  Serial.printf("V4-B relay 0x%08X online (LoRa %s, forward %s)\n", kNodeId,
                USE_LORA ? "on" : "off", USE_RELAY_FORWARD ? "on" : "off");
}

void loop() {
  // Serve TTDB-share / commands arriving from the laptop over USB-CDC (direct pull,
  // negchecks). Un-deduped trusted link.
  uint8_t buf[toot::MAX_FRAME];
  size_t n = 0;
  if (gSerial.poll(buf, sizeof(buf), n)) {
    toot::Toot t;
    if (toot::decode(buf, n, ROBOT_TEAM_KEY, ROBOT_TEAM_KEY_LEN, t)) {
      gSerIn++;
      gLastSrc = t.src_node_id;
      gOledDirty = true;
      handleToot(t, sendSerial, nullptr);
    }
  }

  // Serve a deferred ESP-NOW TTDB_REQ (burst streams from the main task, where TX
  // pacing via the send callback works).
  if (gReqPending) {
    gReqPending = false;
    serveTtdbReq(gPendingReq, sendEspNow, nullptr);
  }

  // Serve a deferred ESP-NOW TTDB_PUT (belief slice): the flash write (and, on the
  // last slice, the CRC-verify) runs on the main task. handleToot ACKs it back.
  if (gPutPending) {
    gPutPending = false;
    handleToot(gPendingPut, sendEspNow, nullptr);
  }

  // Append the deferred TTDB log records (flash write + re-index).
  if (gSyncPending) { gSyncPending = false; appendSyncRecord(); }
  if (gBeliefSyncPending) { gBeliefSyncPending = false; appendBeliefRecord(); }

#if USE_PULSE
  // --- fleet pulse (TTN-RFC-0010): backbeat part — LED + OLED dot on beats 2 & 4 ---
  {
    uint32_t pnow = millis();
    pulse::Chart oc;
    uint64_t oepoch;
    if (gPulse.update(pnow, oc, oepoch)) {     // drift-paced / on-join only, not per beat
      uint8_t body[toot::PULSE_PAYLOAD_LEN];
      uint8_t blen = toot::buildPulse(body, oc.conductor_id, oc.era, oepoch,
                                      oc.downbeat_epoch, oc.beat_period_ms,
                                      oc.meter_beats, oc.flags);
      emit(toot::PULSE, body, blen, sendEspNow, nullptr);
      Serial.printf("[pulse] beacon era=%lu cond=0x%08X period=%ums%s\n",
                    (unsigned long)oc.era, (unsigned)oc.conductor_id,
                    oc.beat_period_ms, gPulse.conductor() ? " (conductor)" : "");
    }
    // Backbeat part: flash the LED + OLED dot on each struck step of the phrase (2 & 4).
    uint16_t sip;
    uint32_t sc;
    if (gPulse.stepTick(pnow, kPart.steps, sip, sc) && score::noteAt(kPart, sip)) {
      digitalWrite(kLedPin, HIGH);
      gLedClearMs = pnow + PULSE_LED_MS;
      gBeatFlash = true;
      gOledDirty = true;
      Serial.printf("[part] step %u BACKBEAT (beat %u) era=%lu\n", sip, (sip / 4) % 4 + 1,
                    (unsigned long)gPulse.chart().era);
    }
    if (gLedClearMs && (int32_t)(pnow - gLedClearMs) >= 0) {
      gLedClearMs = 0;
      digitalWrite(kLedPin, LOW);
      gBeatFlash = false;
      gOledDirty = true;
    }
  }
#endif

  // Periodic HELLO beacon + OLED heartbeat.
  static uint32_t lastBeacon = 0;
  if (millis() - lastBeacon >= 2000) {
    lastBeacon = millis();
    emit(toot::HELLO, nullptr, 0, sendEspNow, nullptr);
  }
  static uint32_t lastRender = 0;
  if (gOledDirty || millis() - lastRender >= 1000) {
    lastRender = millis();
    gOledDirty = false;
    renderOled();
  }
}
