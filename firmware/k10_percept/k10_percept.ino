// k10_percept.ino — UNIHIKER K10 percept node (A32 agent).
//
// Role: @PERCEPT capture leaf on the ESP-NOW cluster (toot_network_architecture
// .md section 1). No LoRa. Shares its TTDB with the companion two ways:
//   - over ESP-NOW, when a peer sends a TTDB_REQ toot;
//   - over USB-CDC serial, when the laptop companion.py sends a TTDB_REQ.
//
// Build/deploy with arduino-cli (see firmware/README.md). The TTDB lives in
// data/ttdb.md and is flashed to LittleFS separately.
#include <Arduino.h>
#include <LittleFS.h>
#include <WiFi.h>
#include <esp_now.h>
#include <esp_wifi.h>

#include <Toot.h>
#include <TootSerial.h>
#include <TootEspNow.h>
#include <TTDB.h>
#include <TtdbShare.h>
#include <Agent32.h>
#include <RobotTeamConfig.h>

// Real UNIHIKER K10 onboard hardware (DFRobot `unihiker_k10` library). Set to 0
// to fall back to a serial-only mock if the library/board package isn't
// installed yet. API verified against the UNIHIKER K10 Arduino wiki:
//   temperature: aht20.getData(AHT20::eAHT20TempC)
//   RGB LED:     k10.rgb->write(-1, 0xRRGGBB)  /  k10.rgb->brightness(0..9)
#define USE_K10_HW 1
#if USE_K10_HW
#include "unihiker_k10.h"
static UNIHIKER_K10 k10;
static AHT20 aht20;
static Music music;
#endif

static const uint32_t kNodeId = NODE_K10_1;
static const char* kTtdbPath = "/ttdb.md";
// The K10's large_spiffs_16MB scheme has no partition named "spiffs"; its only
// LittleFS-capable partition is "model" (subtype spiffs, @0x510000, ~4.5MB),
// normally used for AI models (unused on a percept node). Mount it by label.
static const char* kFsLabel = "model";
static const uint8_t kBroadcast[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

// Packed @LATxLONy locus this node reports in its toot headers. Until a real
// fix is known, advertise the K10's home node from its TTDB (filled at boot).
static uint8_t gLocus[toot::LOCUS_LEN] = {0};

Ttdb gDb;
TtdbShare* gShare = nullptr;
toot::DedupSet gDedup(64);
toot::Reassembler gReasm;   // chunked-toot reassembly (TTN-RFC-0007 §6)
TootSerialLink gSerial(Serial);
Agent32 gAgent(&gDb);
uint32_t gSeq = 1;

// --- wall clock (TTN-RFC-0008) ----------------------------------------------
// No RTC: synthesize epoch ms from millis() + an offset adopted on TIME_SYNC.
// Unsynced until the first TIME_SYNC; exactly-once adoption is gated on a
// monotonic sync_id (not transport dedup), so the un-deduped paths stay correct.
static int64_t gClockOffsetMs = 0;
static bool gSynced = false;
static uint32_t gLastSyncId = 0;
static inline int64_t nowEpochMs() { return (int64_t)millis() + gClockOffsetMs; }

// A TIME_SYNC adopts the offset in the recv path (for timing accuracy) but defers
// the TTDB log-append to loop() (flash write + re-index, like the TTDB reply).
static volatile bool gSyncPending = false;
static uint32_t gPendSyncId = 0;
static uint64_t gPendEpochMs = 0;
static uint32_t gPendRecvMs = 0;

// Laptop CMD override of the indicator LED (companion.md §4b). When enabled, the
// loop paints this color after the agent acts, so the orchestrator's set-led wins
// over the local warm/cool indicator until a clear-led (or reboot).
static struct {
  bool enabled = false;
  uint32_t color = 0;
} gLedOverride;

// Deferred beep (CMD_BEEP): playTone() blocks ~dur_ms, so it must NOT run in the
// recv callback (WiFi task). handleToot stashes it (after ACK) and loop() plays it.
static volatile bool gBeepPending = false;
static int gBeepFreq = 0;
static int gBeepBeat = 0;   // I2S samples @ 8 kHz: beat = dur_ms * 8 (beat/8000 = s)

// --- pushed belief (TTN-RFC-0009) -------------------------------------------
// The companion re-authors fleet knowledge and pushes it back as offset-addressed
// TTDB_PUT slices, written to a SEPARATE file (never the live TTDB). On a
// CRC-verified commit the node appends a BELIEF-ADOPTED record to its own live TTDB
// — self-attestation that it integrated exactly those bytes. Exactly-once on a
// monotonic belief_id (like the sync_id gate), so the un-deduped USB/bridge path
// can retransmit a lost slice without double-adopting.
static const char* kBeliefPath = "/belief.md";
static bool gBeliefAdopted = false;   // committed at least one belief
static uint32_t gBeliefId = 0;        // last adopted belief id
static bool gPutActive = false;       // a transfer is mid-stream
static uint32_t gPutId = 0, gPutTotal = 0, gPutCrc = 0, gPutNext = 0, gPutCrcRun = 0;
// The live-TTDB BELIEF-ADOPTED append is deferred to loop() (flash write + re-index).
static volatile bool gBeliefSyncPending = false;
static uint32_t gPendBeliefId = 0, gPendBeliefBytes = 0, gPendBeliefCrc = 0;
static uint32_t gPendBeliefRecvMs = 0;

// Parse the behavioral DIRECTIVE from /belief.md (TTN-RFC-0009 §5.2): the
// `**DIRECTIVE** sense_interval_ms:<N>` the node should adopt. Returns N, or 0 if the
// belief carries no directive. The belief is ~1 KB; read the head into a fixed buffer
// (the directive sits near the top) and scan — no String, no whole-file slurp.
static uint32_t parseBeliefDirective() {
  File f = LittleFS.open(kBeliefPath, "r");
  if (!f) return 0;
  static char buf[1536];
  size_t n = f.read((uint8_t*)buf, sizeof(buf) - 1);
  f.close();
  buf[n] = '\0';
  const char* key = "**DIRECTIVE** sense_interval_ms:";
  const char* p = strstr(buf, key);
  return p ? (uint32_t)strtoul(p + strlen(key), nullptr, 10) : 0;
}

// Write one TTDB_PUT slice into the belief file and, on completion, CRC-verify and
// schedule adoption. Returns true if the slice was accepted (so it is ACKed). The
// laptop streams strictly in offset order (stop-and-wait), so we track gPutNext and
// stay idempotent on retransmits (TTN-RFC-0009 §3). Runs in the caller's context —
// for the serial/bridge push path that is loop(), where flash writes are safe.
static bool handlePutSlice(const toot::Toot& t) {
  uint32_t target, bid, total, crc, off;
  const uint8_t* data;
  uint16_t len;
  if (!toot::parsePut(t, target, bid, total, crc, off, data, len)) return false;
  if (target != kNodeId) return false;
  // Already adopted this belief: re-ACK without rewriting (lost-final-ACK case).
  if (gBeliefAdopted && bid == gBeliefId) return true;

  if (off == 0) {                          // (re)start a fresh transfer
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
      gBeliefSyncPending = true;                  // log to live TTDB from loop()
    } else {
      Serial.printf("[belief] id=%lu CRC MISMATCH got %08lX want %08lX (%luB)\n",
                    (unsigned long)bid, (unsigned long)gPutCrcRun,
                    (unsigned long)gPutCrc, (unsigned long)gPutTotal);
    }
  }
  return true;
}

// --- sense/act bindings -----------------------------------------------------
// Sensor: onboard ambient temperature (AHT20), nominal range -20..60 C, mapped
// to (lat 10, lon 0) so a warm reading drives the cursor to the @LAT10LON0
// record in data/ttdb.md and fires its triggers edge.
static float readAmbientTempC() {
#if USE_K10_HW
  return aht20.getData(AHT20::eAHT20TempC);
#else
  return -20.0f + (float)((millis() / 1000) % 80);  // sawtooth mock
#endif
}
static const A32Sensor kTempSensor = {
    "ambient_temp", readAmbientTempC, /*map_lat=*/10, /*map_lon=*/0,
    /*range_min=*/-20.0f, /*range_max=*/60.0f};

// Actuator at (10,0): the three onboard RGB LEDs. A triggers@LAT10LON0 edge
// fires this with value 1.0 -> red (warm); the loop clears the LEDs each cycle
// so a cold cycle (no trigger) leaves them off.
static void setIndicator(float v) {
#if USE_K10_HW
  k10.rgb->write(-1, v > 0.5f ? 0xFF0000 : 0x000000);  // -1 = all LEDs
#else
  Serial.printf("[ACT] indicator -> %.1f\n", v);
#endif
}
static const A32Actuator kIndicator = {"indicator", setIndicator,
                                       /*map_lat=*/10, /*map_lon=*/0};

static inline void indicatorClear() {
#if USE_K10_HW
  k10.rgb->write(-1, 0x000000);
#endif
}

#if USE_K10_HW
// Two toots — the Toot-Toot signature — on startup (uses the K10 speaker).
// playTone(freq, beat): `beat` is the count of I2S samples at 8 kHz, so the
// duration is beat/8000 seconds — NOT milliseconds. (My earlier 400/600 were
// ~50-75 ms, inaudible.) These match the known-good k10_ttdb_navigator values:
// 2000 -> 0.25 s, 4000 -> 0.5 s.
static void playStartupToot() {
  delay(50);                  // let the speaker settle after k10.begin()
  music.playTone(196, 2000);  // toot  (G3, 0.25 s)
  music.playTone(262, 4000);  // toot  (C4, 0.5 s)
}

// Show TTDB identity + indexed records + live reasoning state on the LCD.
static void renderScreen(float tempC) {
  char line[40];
  k10.canvas->canvasClear(0x000000);
  k10.canvas->canvasText("K10 Percept Node", 1, 0x00E676);
  snprintf(line, sizeof(line), "id 0x%08X", (unsigned)kNodeId);
  k10.canvas->canvasText(String(line), 2, 0x2E7D32);
  snprintf(line, sizeof(line), "TTDB %uB  %d rec", (unsigned)gDb.fileSize(),
           gDb.recordCount());
  k10.canvas->canvasText(String(line), 4, 0x00FF66);

  int row = 6;
  for (int i = 0; i < gDb.recordCount() && row <= 10; ++i) {
    const TtdbRecord& r = gDb.record(i);
    snprintf(line, sizeof(line), "  @LAT%dLON%d", r.lat, r.lon);
    k10.canvas->canvasText(String(line), row++, 0x00FF66);
  }

  bool warm = gAgent.matchedThisCycle();
  snprintf(line, sizeof(line), "temp %.1f C", tempC);
  k10.canvas->canvasText(String(line), 12, 0x00FF66);
  snprintf(line, sizeof(line), "cursor @LAT%dLON%d", gAgent.cursorLat(),
           gAgent.cursorLon());
  k10.canvas->canvasText(String(line), 14, warm ? 0xCCFF90 : 0x2E7D32);
  if (gLedOverride.enabled) {
    snprintf(line, sizeof(line), "LED: laptop #%06X", (unsigned)gLedOverride.color);
    k10.canvas->canvasText(String(line), 16, 0x40C4FF);
  } else {
    k10.canvas->canvasText(warm ? "WARM - indicator ON" : "cool", 16,
                           warm ? 0xFF6F00 : 0x2E7D32);
  }
  k10.canvas->updateCanvas();
}
#endif

// --- transports -------------------------------------------------------------
// ESP-NOW TX is asynchronous with a shallow queue. TtdbShare streams many
// TTDB_DATA frames back-to-back, which overruns the queue and silently drops all
// but the first few. Gate each send on the previous frame's TX-complete callback
// so the whole TTDB streams intact over the air.
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

// TTN-RFC-0007: acknowledge `orig` back to its sender on `reply`. Used both for a
// freshly-accepted want_ack toot and for re-ACKing a dedup-dropped replay (§5).
static void emitAck(const toot::Toot& orig, uint8_t status,
                    TtdbShare::SendFn reply, void* ctx) {
  toot::Toot ack;
  toot::makeAck(orig, kNodeId, gSeq++, status, ack);
  uint8_t frame[toot::MAX_FRAME];
  size_t flen =
      toot::encode(ack, ROBOT_TEAM_KEY, ROBOT_TEAM_KEY_LEN, frame, sizeof(frame));
  if (flen) reply(frame, flen, ctx);
}

// Pack this node's live telemetry into a STATUS payload (Toot.h) — answered as a
// PERCEPT to CMD_GET_STATUS. Uses the last sensed reading (no I2C from a callback).
static uint8_t buildStatus(uint8_t* p) {
  float t = gAgent.readingCount() > 0 ? gAgent.reading(0).value : 0.0f;
  uint8_t flags = 0;
  if (gAgent.matchedThisCycle()) flags |= toot::STATUS_WARM;
  if (gLedOverride.enabled) flags |= toot::STATUS_LED_OVERRIDE;
  if (gSynced) flags |= toot::STATUS_SYNCED;
  toot::put_u16(p + 0, (uint16_t)(int16_t)gAgent.cursorLat());
  toot::put_u16(p + 2, (uint16_t)(int16_t)gAgent.cursorLon());
  toot::put_u16(p + 4, (uint16_t)(int16_t)(t * 100.0f));
  p[6] = flags;
  toot::put_u64(p + 7, gSynced ? (uint64_t)nowEpochMs() : 0);
  return (uint8_t)toot::STATUS_PAYLOAD_LEN;
}

// Serve a TTDB_REQ addressed to this node. TTDB_REQ_BELIEF streams the stored
// belief object (/belief.md) so the companion can byte-diff what we actually wrote
// (TTN-RFC-0009 §3); any other mode streams the live TTDB via the offset index.
// Both stream a TTDB_DATA burst, so radio callers must invoke this from loop()
// (not the recv callback) — see the gReqPending deferral.
static void serveTtdbReq(const toot::Toot& req, TtdbShare::SendFn send, void* ctx) {
  if (!gShare || TtdbShare::requestTarget(req) != kNodeId) return;
  if (req.payload_len >= 1 && req.payload[0] == toot::TTDB_REQ_BELIEF) {
    static uint8_t bbuf[1536];
    File f = LittleFS.open(kBeliefPath, "r");
    size_t n = f ? f.read(bbuf, sizeof(bbuf)) : 0;  // 0 bytes if no belief yet
    if (f) f.close();
    gShare->handleBufferRequest(bbuf, n, send, ctx);
  } else {
    gShare->handleRequest(req, send, ctx);
  }
}

// Dispatch a decoded, authenticated toot arriving on any transport. `reply` is
// the transport to answer on (ESP-NOW peer or serial). Dedup is a radio/mesh
// concern (replay attacks + forwarding loops), so it is NOT applied here — the
// trusted USB-CDC link is intentionally un-deduped so the laptop can retry a lost
// request. Radio callers gate on gDedup before calling in (see onEspNowRecv).
static void handleToot(const toot::Toot& t, TtdbShare::SendFn reply, void* ctx) {
  bool accepted = false;
  switch (t.type) {
    case toot::TTDB_REQ:
      // The streamed TTDB_DATA reply is itself the confirmation, so a TTDB_REQ is
      // not separately ACKed. Mode selects live TTDB vs stored belief (serveTtdbReq).
      serveTtdbReq(t, reply, ctx);
      break;
    case toot::TTDB_PUT:
      // Companion pushes a re-authored belief, one offset-addressed slice per toot
      // (TTN-RFC-0009). Accept -> ACK each slice; commit + adopt on the last.
      accepted = handlePutSlice(t);
      break;
    case toot::CMD:
      // Orchestrator directive. Only the addressed node acts + ACKs, so a broadcast
      // CMD doesn't draw an ACK from every hearer. CMD is want_ack -> ACK on accept.
      if (toot::cmdTarget(t) == kNodeId) {
        switch (toot::cmdOp(t)) {
          case toot::CMD_SET_LED:
            if (t.payload_len >= 8) {  // op + target(4) + R,G,B
              gLedOverride.color = ((uint32_t)t.payload[5] << 16) |
                                   ((uint32_t)t.payload[6] << 8) | t.payload[7];
              gLedOverride.enabled = true;
            }
            break;
          case toot::CMD_CLEAR_LED:
            gLedOverride.enabled = false;
            break;
          case toot::CMD_GET_STATUS: {
            uint8_t body[toot::STATUS_PAYLOAD_LEN];
            uint8_t slen = buildStatus(body);
            emit(toot::PERCEPT, body, slen, reply, ctx);  // the reply is the answer
            break;
          }
          case toot::CMD_BEEP: {
            int freq = 880, dur = 200;            // defaults
            if (t.payload_len >= 9) {             // op + target(4) + freq(2) + dur(2)
              freq = toot::get_u16(t.payload + 5);
              dur = toot::get_u16(t.payload + 7);
            }
            if (dur > 5000) dur = 5000;           // cap so the loop isn't stalled long
            gBeepFreq = freq;
            gBeepBeat = dur * 8;
            gBeepPending = true;                  // played from loop() (playTone blocks)
            break;
          }
          case toot::CMD_SET_INTERVAL:
            if (t.payload_len >= 7) {
              uint16_t ms = toot::get_u16(t.payload + 5);
              if (ms < 100) ms = 100;             // floor: don't starve the loop
              gAgent.setInterval(ms);
            }
            break;
          default:  // CMD_PING / unknown: nothing to do but ACK
            break;
        }
        accepted = true;  // a CMD addressed to us is acknowledged (when want_ack)
      }
      break;
    case toot::TIME_SYNC: {
      // Adopt the offset here (recv-time millis() is most accurate); defer the
      // TTDB append to loop(). Exactly-once on a monotonic sync_id (TTN-RFC-0008
      // §3.1) — independent of dedup, so a retry can't double-append.
      uint32_t sid; uint64_t ems;
      if (toot::parseTimeSync(t, sid, ems)) {
        uint32_t recv_ms = millis();
        if (!gSynced || sid > gLastSyncId) {
          gClockOffsetMs = (int64_t)ems - (int64_t)recv_ms;
          gSynced = true;
          gLastSyncId = sid;
          gPendSyncId = sid;
          gPendEpochMs = ems;
          gPendRecvMs = recv_ms;
          gSyncPending = true;
        }
        accepted = true;  // ACK the want_ack TIME_SYNC (idempotent on replay)
      }
      break;
    }
    case toot::TIME_REQ: {
      // Skew probe: only the addressed node answers, sampling its epoch as late as
      // possible. Not want_ack — the TIME_RESP is itself the reply.
      uint32_t pid, target;
      if (toot::parseTimeReq(t, pid, target) && target == kNodeId) {
        uint8_t body[toot::TIME_RESP_PAYLOAD_LEN];
        toot::put_u32(body + 0, pid);
        toot::put_u64(body + 4, (uint64_t)nowEpochMs());
        emit(toot::TIME_RESP, body, sizeof(body), reply, ctx);
      }
      break;
    }
    case toot::HELLO:
    case toot::PERCEPT:
    case toot::BELIEF:
      // Neighborhood awareness lands here; nothing to do for the floor demo.
      break;
    default:
      break;
  }
  // TTN-RFC-0007: acknowledge an accepted want_ack toot exactly once on this path.
  // A replay arriving over the radio is re-ACKed in onEspNowRecv without reaching
  // here (§5), so the body is processed once and the ACK stays idempotent.
  if (accepted && (t.flags & toot::FLAG_WANT_ACK))
    emitAck(t, toot::ACK_ACCEPTED, reply, ctx);
}

// A chunk of a logical toot (chunk_total > 1) goes to the Reassembler, which owns
// per-chunk dedup and emits the per-chunk ACK status (TTN-RFC-0007 §6). Each call
// sends at most one ACK frame, so running it in the recv callback is not a burst.
static void handleChunk(const toot::Toot& t) {
  toot::Reassembler::Result r = gReasm.offer(t, millis());
  uint8_t status;
  switch (r) {
    case toot::Reassembler::NEED_MORE:
    case toot::Reassembler::DUPLICATE:
      status = toot::ACK_REASSEMBLY_PENDING;
      break;
    case toot::Reassembler::COMPLETE:
      Serial.printf("[reasm] (0x%08X,%u) assembled %u bytes\n",
                    (unsigned)t.src_node_id, (unsigned)t.toot_seq,
                    (unsigned)gReasm.bodyLen());
      status = toot::ACK_ACCEPTED;  // no large-toot consumer yet (Phase 6 BELIEF)
      break;
    case toot::Reassembler::COMPLETED_DUP:
      status = toot::ACK_ACCEPTED;
      break;
    case toot::Reassembler::NO_RESOURCE:
      status = toot::ACK_DROPPED_NO_RESRC;
      break;
    default:  // BAD
      return;
  }
  if (t.flags & toot::FLAG_WANT_ACK) emitAck(t, status, sendEspNow, nullptr);
}

// A TTDB_REQ arriving over ESP-NOW is stashed here and served from loop(), not
// from the recv callback: streaming the whole reply from the WiFi task would
// block its own TX (the send-complete callback can't run), starving the burst.
static volatile bool gReqPending = false;
static toot::Toot gPendingReq;

// A TTDB_PUT slice (belief push) is likewise deferred: handlePutSlice writes the
// slice to LittleFS (and the last one re-indexes), which must not run in the WiFi
// recv callback. The sender serializes slices (waits for each ACK before the next,
// TTN-RFC-0009), so a single pending slot suffices; a retransmit of an already-seen
// slice is caught by the (src,seq) dedup below and re-ACKed without touching this.
static volatile bool gPutPending = false;
static toot::Toot gPendingPut;

static ESPNOW_RECV_CB(onEspNowRecv, data, len) {
  if (len <= 0) return;
  toot::Toot t;
  if (!toot::decode(data, (size_t)len, ROBOT_TEAM_KEY, ROBOT_TEAM_KEY_LEN, t)) return;
  // Chunked toots bypass the (src,seq) dedup (which would collapse sibling chunks)
  // and go to the Reassembler, which dedups per (src,seq,chunk_idx).
  if (t.chunk_total > 1) { handleChunk(t); return; }
  if (gDedup.seen(t.src_node_id, t.toot_seq)) {  // radio-path replay/loop guard
    // TTN-RFC-0007 §5: the original ACK was evidently lost (the sender retried),
    // so re-ACK the duplicate without re-processing its body. The dup frame
    // self-identifies, so a fresh ACCEPTED ACK is correct for an unchunked toot.
    if (t.flags & toot::FLAG_WANT_ACK)
      emitAck(t, toot::ACK_ACCEPTED, sendEspNow, nullptr);
    return;
  }
  if (t.type == toot::TTDB_REQ) {
    if (!gReqPending) { gPendingReq = t; gReqPending = true; }  // defer to loop()
  } else if (t.type == toot::TTDB_PUT) {
    if (!gPutPending) { gPendingPut = t; gPutPending = true; }  // flash write -> loop()
  } else {
    handleToot(t, sendEspNow, nullptr);                         // cheap, no burst
  }
}

// --- setup / loop -----------------------------------------------------------
void setup() {
  Serial.begin(115200);
  delay(200);

#if USE_K10_HW
  k10.begin();              // inits onboard peripherals incl. AHT20 + rgb
  playStartupToot();        // "toot toot"
  k10.initScreen(2);        // 2 = default orientation
  k10.creatCanvas();
  k10.rgb->brightness(5);   // 0-9
#endif

  if (!LittleFS.begin(true, "/littlefs", 10, kFsLabel)) {
    Serial.println("FATAL: LittleFS mount failed");
  } else if (!gDb.begin(LittleFS, kTtdbPath)) {
    Serial.println("FATAL: TTDB load failed");
  } else {
    Serial.printf("TTDB loaded: %u bytes, %d records\n",
                  (unsigned)gDb.fileSize(), gDb.recordCount());
  }
  gShare = new TtdbShare(gDb, ROBOT_TEAM_KEY, ROBOT_TEAM_KEY_LEN, kNodeId,
                         gLocus);

  WiFi.mode(WIFI_STA);
  esp_wifi_set_channel(ROBOT_TEAM_ESPNOW_CHANNEL, WIFI_SECOND_CHAN_NONE);
  if (esp_now_init() != ESP_OK) {
    Serial.println("FATAL: esp_now_init failed");
  }
  esp_now_register_recv_cb(onEspNowRecv);
  esp_now_register_send_cb(onEspNowSend);   // paces TTDB_DATA bursts (see sendEspNow)
  esp_now_peer_info_t peer = {};
  memcpy(peer.peer_addr, kBroadcast, 6);
  peer.channel = ROBOT_TEAM_ESPNOW_CHANNEL;
  peer.encrypt = false;
  esp_now_add_peer(&peer);

  gAgent.registerSensor(&kTempSensor);
  gAgent.registerActuator(&kIndicator);
  gAgent.setInterval(1000);
  gAgent.setMatchThreshold(8);
  Serial.printf("K10 percept node 0x%08X online\n", kNodeId);
}

void loop() {
  // Serve TTDB-share / commands arriving from the laptop over USB-CDC.
  uint8_t buf[toot::MAX_FRAME];
  size_t n = 0;
  if (gSerial.poll(buf, sizeof(buf), n)) {
    toot::Toot t;
    if (toot::decode(buf, n, ROBOT_TEAM_KEY, ROBOT_TEAM_KEY_LEN, t))
      handleToot(t, sendSerial, nullptr);
  }

  // Serve an ESP-NOW TTDB_REQ deferred from the recv callback (so the reply
  // streams from the main task, where TX pacing via the send callback works).
  if (gReqPending) {
    gReqPending = false;
    serveTtdbReq(gPendingReq, sendEspNow, nullptr);  // live TTDB or belief, by mode
  }

  // Serve an ESP-NOW TTDB_PUT (belief slice) deferred from the recv callback: the
  // slice write (and, on the final slice, the CRC-verify + re-index) is a flash op
  // that must run on the main task. handleToot writes the slice and ACKs it back
  // over ESP-NOW; the live-TTDB adoption append is itself deferred via gBeliefSyncPending.
  if (gPutPending) {
    gPutPending = false;
    handleToot(gPendingPut, sendEspNow, nullptr);
  }

  // Write the TIME_SYNC log record deferred from the recv path (TTN-RFC-0008 §4):
  // a new @LAT99LON<n> record, where n is the count of existing lat-99 records so
  // each is unique under collision_policy: reject. Header times are unix seconds
  // (timestamp_kind: unix); ms precision lives in the body.
  if (gSyncPending) {
    gSyncPending = false;
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

  // Log a CRC-verified pushed belief to the live TTDB (TTN-RFC-0009 §4), deferred
  // from the recv/put path: a new @LAT98LON<n> record (n = count of existing lat-98
  // records, unique under collision_policy: reject). The belief bytes themselves
  // live in /belief.md; this is the node's append-only attestation of adoption.
  if (gBeliefSyncPending) {
    gBeliefSyncPending = false;
    // Act on the belief's DIRECTIVE — this is the Dream Cycle closing: a pushed,
    // re-authored belief changes node behavior, not just stored state (Phase 6).
    // Retune the sense->reason->act cadence; the attestation records what took effect.
    uint32_t interval = parseBeliefDirective();
    if (interval >= 100)              // floor: don't starve the loop / watchdog
      gAgent.setInterval(interval);
    uint32_t effective = gAgent.intervalMs();
    int n = 0;
    for (int i = 0; i < gDb.recordCount(); ++i)
      if (gDb.record(i).lat == 98) ++n;
    uint32_t t_sec = gSynced ? (uint32_t)(nowEpochMs() / 1000) : 0;
    char rec[256];
    int m = snprintf(
        rec, sizeof(rec),
        "\n---\n\n@LAT98LON%d | created:%lu | updated:%lu | relates:adopts@LAT0LON0"
        "\n\n**BELIEF-ADOPTED** id:%lu bytes:%lu crc:%08lX recv_ms:%lu "
        "applied:interval_ms:%lu\n",
        n, (unsigned long)t_sec, (unsigned long)t_sec,
        (unsigned long)gPendBeliefId, (unsigned long)gPendBeliefBytes,
        (unsigned long)gPendBeliefCrc, (unsigned long)gPendBeliefRecvMs,
        (unsigned long)effective);
    if (m > 0 && gDb.appendRecord(rec, (size_t)m))
      Serial.printf("[belief] adopted id=%lu %luB crc=%08lX -> @LAT98LON%d "
                    "(TTDB %uB) cadence=%lums\n",
                    (unsigned long)gPendBeliefId, (unsigned long)gPendBeliefBytes,
                    (unsigned long)gPendBeliefCrc, n, (unsigned)gDb.fileSize(),
                    (unsigned long)effective);
    else
      Serial.println("[belief] appendRecord FAILED");
  }

  // Play a deferred CMD_BEEP from the main task (playTone blocks ~dur_ms).
  if (gBeepPending) {
    gBeepPending = false;
#if USE_K10_HW
    music.playTone(gBeepFreq, gBeepBeat);
#endif
    Serial.printf("[beep] %d Hz, beat %d\n", gBeepFreq, gBeepBeat);
  }

  // Periodic HELLO beacon + percept tick.
  static uint32_t last = 0;
  if (millis() - last >= gAgent.intervalMs()) {
    last = millis();
    indicatorClear();   // LEDs off unless this cycle's TTDB trigger re-lights
    gAgent.sense();
    gAgent.reason();
    gAgent.act();
#if USE_K10_HW
    // A laptop set-led overrides the local indicator until clear-led (companion.md
    // §4b) — applied after act() so the orchestrator's command wins this cycle.
    if (gLedOverride.enabled) k10.rgb->write(-1, gLedOverride.color);
#endif
    Serial.printf("[cycle] cursor @LAT%dLON%d match=%d led=%s\n", gAgent.cursorLat(),
                  gAgent.cursorLon(), gAgent.matchedThisCycle(),
                  gLedOverride.enabled ? "laptop" : "agent");
#if USE_K10_HW
    renderScreen(gAgent.readingCount() > 0 ? gAgent.reading(0).value : 0.0f);
#endif
    emit(toot::HELLO, nullptr, 0, sendEspNow, nullptr);
  }
}
