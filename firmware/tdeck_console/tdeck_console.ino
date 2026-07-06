// tdeck_console.ino — LilyGo T-Deck, HANDHELD CONSOLE / field operator (A32 agent).
//
// Role: a mobile mini-orchestrator carried in-hand. The BlackBerry keyboard injects
// CMD toots and the 320x240 color screen shows the fleet, so an operator can drive
// and observe the swarm without the laptop. It is a full ESP-NOW Dream-Cycle
// participant like V4-B (pull, HMAC, dedup, want_ack ACK, TIME_SYNC adopt + @LAT99
// log, belief TTDB_PUT adopt + @LAT98 attestation, STATUS telemetry, PULSE), plus a
// console UI. The T-Deck also carries an SX1262, so it can join the LoRa spine later
// (USE_LORA) — the only handheld node that bridges color-screen+keyboard and LoRa.
//
// Built from the verified siblings (V4-B's network floor + the K10's mesh
// discipline): serve a TTDB burst from loop() (never the recv callback), pace ESP-NOW
// sends behind the TX-complete callback, dedup radio-only, re-ACK a dropped want_ack
// replay (TTN-RFC-0007 §5), and defer every flash write out of the WiFi task.
//
// Build/deploy with arduino-cli (see firmware/README.md), FQBN
// esp32:esp32:esp32s3:CDCOnBoot=cdc (native USB, like the V4/K10). TTDB in
// data/ttdb.md flashed to LittleFS separately (scripts/Upload-V4-FS.ps1 -Node
// tdeck_console — same esp32-core default 4 MB spiffs partition as the V4).
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
#include <Pulse.h>
#include <RobotTeamConfig.h>

// Real T-Deck peripherals (ST7789 LCD + I2C keyboard). Set to 0 to build/verify the
// network floor headless (byte-exact pull, HMAC reject, sync/belief) with a serial
// mock — exactly how the K10/V4 were first brought up (USE_K10_HW). Flip to 1 on the
// bench once TFT_eSPI is configured for the T-Deck pins (see the User_Setup note
// below) and Wire is wired to the keyboard. The floor works either way.
#define USE_TDECK_HW 0
#define USE_LORA 0        // Phase 4: the T-Deck's SX1262 can join the LoRa spine.
#define USE_PULSE 1       // follow the band clock so `band`/`monitor` see this node.

// --- T-Deck board pin map (LilyGo T-Deck / T-Deck Plus) ---------------------
// Documented here (and in hardware_specs.md) even when USE_TDECK_HW is 0 so the
// board is ready to bring up. The display, LoRa and SD share ONE SPI bus.
static const int PIN_POWERON   = 10;  // board peripheral-power enable: MUST be HIGH
static const int PIN_SPI_SCLK  = 40;  // shared SPI clock (LCD + LoRa + SD)
static const int PIN_SPI_MOSI  = 41;
static const int PIN_SPI_MISO  = 38;
static const int PIN_TFT_CS    = 12;  // ST7789 320x240
static const int PIN_TFT_DC    = 11;
static const int PIN_TFT_BL    = 42;  // backlight (active HIGH)
static const int PIN_KBD_SDA   = 18;  // BlackBerry keyboard (own MCU) over I2C
static const int PIN_KBD_SCL   = 8;
static const uint8_t KBD_ADDR  = 0x55;  // reads one byte = ASCII of the pressed key
static const int PIN_TB_CLICK  = 0;   // trackball click (also BOOT); UP3 DN15 L1 R2
static const int PIN_LORA_CS   = 9;   // SX1262 (shared SPI): BUSY13 RST17 DIO1 45

#if USE_TDECK_HW
#include <Wire.h>
#include <SPI.h>
// The T-Deck LCD is an ST7789 driven by TFT_eSPI, whose pin map is COMPILE-TIME in
// the sketchbook User_Setup.h. IMPORTANT: that same file is currently pinned to the
// K10's ILI9341 pins (CLAUDE.md) — the two boards cannot share one User_Setup. Give
// the T-Deck its own TFT_eSPI setup selected at build time (a -DUSER_SETUP_ID / a
// setup header with ST7789_DRIVER, TFT_MOSI 41, TFT_SCLK 40, TFT_CS 12, TFT_DC 11,
// TFT_BL 42, 240x320 rotated) rather than editing the shared K10 file. This block is
// the on-bench iteration surface; the floor below is what we verify first.
#include <TFT_eSPI.h>
static TFT_eSPI gTft;
#endif

static const uint32_t kNodeId = NODE_TDECK_1;
static const char* kTtdbPath = "/ttdb.md";
static const char* kBeliefPath = "/belief.md";
static const uint8_t kBroadcast[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
static uint8_t gLocus[toot::LOCUS_LEN] = {0};

// The console's default CMD target (which node the keyboard drives). V4-A is the
// bridge/head — a good default. On the bench this could cycle with a trackball.
static uint32_t gCmdTarget = NODE_V4A_BRIDGE;

Ttdb gDb;
TtdbShare* gShare = nullptr;
toot::DedupSet gDedup(128);
TootSerialLink gSerial(Serial);
static uint32_t gSeq = 1;

// Console state rendered on the screen (updated from loop() + the recv callback;
// the callback only flips gScreenDirty — no SPI/I2C from the WiFi task).
static uint32_t gEspRx = 0;      // frames decoded off ESP-NOW
static uint32_t gServed = 0;     // TTDB_REQ replies served
static uint32_t gCmdSent = 0;    // CMD toots injected from the keyboard
static uint32_t gReplies = 0;    // STATUS/PERCEPT replies collected
static uint32_t gLastReplySrc = 0;   // src of the last STATUS/PERCEPT reply
static int16_t  gLastReplyTemp = 0;  // last reply temp*100 (fleet view)
static char     gLastKey = 0;        // last key pressed on the console keyboard
static volatile bool gScreenDirty = true;

// --- wall clock (TTN-RFC-0008) ----------------------------------------------
static int64_t gClockOffsetMs = 0;
static bool gSynced = false;
static uint32_t gLastSyncId = 0;
static inline int64_t nowEpochMs() { return (int64_t)millis() + gClockOffsetMs; }
static volatile bool gSyncPending = false;
static uint32_t gPendSyncId = 0;
static uint64_t gPendEpochMs = 0;
static uint32_t gPendRecvMs = 0;

// --- pushed belief (TTN-RFC-0009) -------------------------------------------
// Store + attest exactly like V4-B (no agent cadence to retune, so no DIRECTIVE
// action). Exactly-once on a monotonic belief_id.
static bool gBeliefAdopted = false;
static uint32_t gBeliefId = 0;
static bool gPutActive = false;
static uint32_t gPutId = 0, gPutTotal = 0, gPutCrc = 0, gPutNext = 0, gPutCrcRun = 0;
static volatile bool gBeliefSyncPending = false;
static uint32_t gPendBeliefId = 0, gPendBeliefBytes = 0, gPendBeliefCrc = 0;
static uint32_t gPendBeliefRecvMs = 0;

// Write one TTDB_PUT slice into /belief.md; on completion CRC-verify and schedule the
// adoption attestation. Idempotent on retransmit (laptop streams strictly in offset
// order, stop-and-wait). Runs in loop() so the flash write never blocks the WiFi task.
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

// --- fleet pulse (TTN-RFC-0010) ---------------------------------------------
// The console is a silent band FOLLOWER: it adopts the shared chart, relays a beacon
// when due (so it helps the band converge), and shows the beat on-screen — but sounds
// no part. Lowest live id conducts, so it never takes the baton unless alone.
#if USE_PULSE
static pulse::Engine gPulse;
static uint32_t gNeighbors[8] = {0};
static int      gNeighborCount = 0;
static bool neighborIsNew(uint32_t src) {
  for (int i = 0; i < gNeighborCount; ++i)
    if (gNeighbors[i] == src) return false;
  if (gNeighborCount < (int)(sizeof(gNeighbors) / sizeof(gNeighbors[0])))
    gNeighbors[gNeighborCount++] = src;
  return true;
}
#endif

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

// Inject a CMD toot at gCmdTarget over ESP-NOW — the console's operator function. op
// is a CmdOp (Toot.h); the CMD payload is op | target(4) | args. Fire-and-forget
// (not want_ack): CMD_GET_STATUS is answered by the target's STATUS PERCEPT, which we
// collect for the fleet view; CMD_PING/CMD_BEEP just act.
static void emitCmd(uint8_t op, const uint8_t* args, uint8_t argn) {
  uint8_t body[toot::MAX_BODY];
  body[0] = op;
  toot::put_u32(body + 1, gCmdTarget);
  if (argn && args) memcpy(body + 5, args, argn);
  emit(toot::CMD, body, (uint8_t)(5 + argn), sendEspNow, nullptr);
  gCmdSent++;
  gScreenDirty = true;
  Serial.printf("[cmd] op=%u -> 0x%08X (#%lu)\n", op, (unsigned)gCmdTarget,
                (unsigned long)gCmdSent);
}

// STATUS telemetry for the `monitor` table. The console has no sensor cursor/temp, so
// those fields are 0; report the synced state + epoch, plus the PULSE tail for `band`.
static uint8_t buildStatus(uint8_t* p) {
  toot::put_u16(p + 0, 0);
  toot::put_u16(p + 2, 0);
  toot::put_u16(p + 4, 0);
  p[6] = gSynced ? toot::STATUS_SYNCED : 0;
  toot::put_u64(p + 7, gSynced ? (uint64_t)nowEpochMs() : 0);
#if USE_PULSE
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
      serveTtdbReq(t, reply, ctx);   // the streamed reply is itself the confirmation
      break;
    case toot::TTDB_PUT:
      accepted = handlePutSlice(t);  // belief slice; ACK each
      break;
    case toot::CMD:
      if (toot::cmdTarget(t) == kNodeId) {
        if (toot::cmdOp(t) == toot::CMD_GET_STATUS) {
          uint8_t body[toot::STATUS_PULSE_PAYLOAD_LEN];
          uint8_t slen = buildStatus(body);
          emit(toot::PERCEPT, body, slen, reply, ctx);  // the reply is the answer
        }
        accepted = true;             // ping / set-* (no-op here) / get-status all ACK
      }
      break;
    case toot::PERCEPT: {
      // A collected reply from a node the console queried: stash it for the fleet
      // view (temp is field 4, temp*100 — see buildStatus on the leaf nodes).
      gReplies++;
      gLastReplySrc = t.src_node_id;
      if (t.payload_len >= 6) gLastReplyTemp = (int16_t)toot::get_u16(t.payload + 4);
      gScreenDirty = true;
      break;
    }
    case toot::TIME_SYNC: {
      uint32_t sid; uint64_t ems;
      if (toot::parseTimeSync(t, sid, ems)) {
        uint32_t recv_ms = millis();
        if (!gSynced || sid > gLastSyncId) {
          gClockOffsetMs = (int64_t)ems - (int64_t)recv_ms;
          gSynced = true;
          gLastSyncId = sid;
          gPendSyncId = sid; gPendEpochMs = ems; gPendRecvMs = recv_ms;
          gSyncPending = true;       // append @LAT99 log from loop()
        }
        accepted = true;             // ACK the want_ack TIME_SYNC (idempotent)
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
  if (t.chunk_total > 1) return;            // no chunked consumer on the console
  if (gDedup.seen(t.src_node_id, t.toot_seq)) {
    if (t.flags & toot::FLAG_WANT_ACK)      // TTN-RFC-0007 §5: re-ACK a lost-ACK dup
      emitAck(t, toot::ACK_ACCEPTED, sendEspNow, nullptr);
    return;
  }
  gEspRx++;
  gScreenDirty = true;

  if (t.type == toot::TTDB_REQ) {
    if (!gReqPending) { gPendingReq = t; gReqPending = true; }   // defer burst to loop()
    return;
  }
  if (t.type == toot::TTDB_PUT) {
    if (!gPutPending) { gPendingPut = t; gPutPending = true; }   // defer flash to loop()
    return;
  }
  handleToot(t, sendEspNow, nullptr);       // cheap toots (TIME_*, CMD, PERCEPT, PULSE)
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

// Append a @LAT98 BELIEF-ADOPTED attestation (deferred). No DIRECTIVE to act on, so
// this records the integrated bytes/crc only.
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

// --- console UI (gated) -----------------------------------------------------
#if USE_TDECK_HW
// Read one keycode from the BlackBerry keyboard (its own MCU answers on I2C 0x55; a
// read of 0 means no key). Returns 0 if nothing pending.
static char readKey() {
  if (Wire.requestFrom((int)KBD_ADDR, 1) != 1) return 0;
  int c = Wire.read();
  return (c > 0) ? (char)c : 0;
}

// Draw the fleet view: who we drive, counters, last reply, band phase. Kept coarse —
// full per-node tables are the on-bench iteration surface.
static void renderScreen() {
  gTft.fillScreen(TFT_BLACK);
  gTft.setTextColor(TFT_GREEN, TFT_BLACK);
  gTft.setTextSize(2);
  gTft.setCursor(4, 4);
  gTft.print("T-DECK CONSOLE");
  gTft.setTextSize(1);
  char l[40];
  int y = 34;
  snprintf(l, sizeof(l), "id 0x%08X  ch%d  sync%s", (unsigned)kNodeId,
           ROBOT_TEAM_ESPNOW_CHANNEL, gSynced ? "+" : "-");
  gTft.setCursor(4, y); gTft.print(l); y += 16;
  snprintf(l, sizeof(l), "TTDB %uB %dr", (unsigned)gDb.fileSize(), gDb.recordCount());
  gTft.setCursor(4, y); gTft.print(l); y += 16;
  snprintf(l, sizeof(l), "drive -> 0x%08X", (unsigned)gCmdTarget);
  gTft.setCursor(4, y); gTft.print(l); y += 16;
  snprintf(l, sizeof(l), "cmd %lu  rx %lu  reply %lu", (unsigned long)gCmdSent,
           (unsigned long)gEspRx, (unsigned long)gReplies);
  gTft.setCursor(4, y); gTft.print(l); y += 16;
  if (gLastReplySrc) {
    snprintf(l, sizeof(l), "last 0x%08X  %.1fC", (unsigned)gLastReplySrc,
             gLastReplyTemp / 100.0f);
    gTft.setCursor(4, y); gTft.print(l); y += 16;
  }
  if (gLastKey) {
    snprintf(l, sizeof(l), "key '%c'", gLastKey);
    gTft.setCursor(4, y); gTft.print(l);
  }
}
#endif

void setup() {
  Serial.begin(115200);
  delay(200);

  // T-Deck peripheral power rail: keyboard, LCD, LoRa and SD are all dead until this
  // is HIGH. Safe to assert even headless (USE_TDECK_HW 0) so LoRa can be enabled.
  pinMode(PIN_POWERON, OUTPUT);
  digitalWrite(PIN_POWERON, HIGH);
  delay(100);

#if USE_TDECK_HW
  Wire.begin(PIN_KBD_SDA, PIN_KBD_SCL);
  gTft.init();
  gTft.setRotation(1);            // landscape 320x240
  pinMode(PIN_TFT_BL, OUTPUT);
  digitalWrite(PIN_TFT_BL, HIGH); // backlight on
  gTft.fillScreen(TFT_BLACK);
  gTft.setTextColor(TFT_GREEN, TFT_BLACK);
  gTft.setCursor(4, 4);
  gTft.print("booting...");
#endif

  if (!LittleFS.begin(true) || !gDb.begin(LittleFS, kTtdbPath)) {
    Serial.println("FATAL: TTDB load failed");
  } else {
    Serial.printf("TTDB loaded: %u bytes, %d records\n",
                  (unsigned)gDb.fileSize(), gDb.recordCount());
  }
  gShare = new TtdbShare(gDb, ROBOT_TEAM_KEY, ROBOT_TEAM_KEY_LEN, kNodeId, gLocus);

  WiFi.mode(WIFI_STA);
  esp_wifi_set_channel(ROBOT_TEAM_ESPNOW_CHANNEL, WIFI_SECOND_CHAN_NONE);
  esp_wifi_set_ps(WIFI_PS_NONE);   // keep RX hot for the mesh (K10 lesson)
  if (esp_now_init() != ESP_OK) Serial.println("FATAL: esp_now_init failed");
  esp_now_register_recv_cb(onEspNowRecv);
  esp_now_register_send_cb(onEspNowSend);   // paces TTDB_DATA bursts (see sendEspNow)
  esp_now_peer_info_t peer = {};
  memcpy(peer.peer_addr, kBroadcast, 6);
  peer.channel = ROBOT_TEAM_ESPNOW_CHANNEL;
  peer.encrypt = false;
  esp_now_add_peer(&peer);

#if USE_PULSE
  gPulse.begin(kNodeId, millis());   // silent follower (highest-ish id never conducts)
#endif
  Serial.printf("T-Deck console 0x%08X online (hw %s, LoRa %s)\n", kNodeId,
                USE_TDECK_HW ? "on" : "off", USE_LORA ? "on" : "off");
}

void loop() {
  // Serve TTDB-share / commands arriving from the laptop over USB-CDC (direct pull,
  // negchecks). Un-deduped trusted link.
  uint8_t buf[toot::MAX_FRAME];
  size_t n = 0;
  if (gSerial.poll(buf, sizeof(buf), n)) {
    toot::Toot t;
    if (toot::decode(buf, n, ROBOT_TEAM_KEY, ROBOT_TEAM_KEY_LEN, t)) {
      gScreenDirty = true;
      handleToot(t, sendSerial, nullptr);
    }
  }

  // Serve a deferred ESP-NOW TTDB_REQ (burst streams from the main task).
  if (gReqPending) {
    gReqPending = false;
    serveTtdbReq(gPendingReq, sendEspNow, nullptr);
  }
  // Serve a deferred ESP-NOW TTDB_PUT (belief slice): flash write on the main task.
  if (gPutPending) {
    gPutPending = false;
    handleToot(gPendingPut, sendEspNow, nullptr);
  }
  // Append the deferred TTDB log records (flash write + re-index).
  if (gSyncPending) { gSyncPending = false; appendSyncRecord(); }
  if (gBeliefSyncPending) { gBeliefSyncPending = false; appendBeliefRecord(); }

#if USE_TDECK_HW
  // Console keyboard: a printable key injects a CMD at gCmdTarget (the operator
  // function). 's' -> query STATUS (answer lands in the fleet view); 'p' -> ping;
  // 'b' -> beep. Any other printable key defaults to a status query.
  char k = readKey();
  if (k) {
    gLastKey = k;
    switch (k) {
      case 'p': emitCmd(toot::CMD_PING, nullptr, 0); break;
      case 'b': { uint8_t a[4]; toot::put_u16(a, 880); toot::put_u16(a + 2, 200);
                  emitCmd(toot::CMD_BEEP, a, 4); break; }
      default:  emitCmd(toot::CMD_GET_STATUS, nullptr, 0); break;
    }
  }
#endif

#if USE_PULSE
  // Relay a chart beacon when due (drift-paced / on-join) so the console helps the
  // band converge; it plays no audible part.
  {
    uint32_t pnow = millis();
    pulse::Chart oc;
    uint64_t oepoch;
    if (gPulse.update(pnow, oc, oepoch)) {
      uint8_t body[toot::PULSE_PAYLOAD_LEN];
      uint8_t blen = toot::buildPulse(body, oc.conductor_id, oc.era, oepoch,
                                      oc.downbeat_epoch, oc.beat_period_ms,
                                      oc.meter_beats, oc.flags);
      emit(toot::PULSE, body, blen, sendEspNow, nullptr);
    }
  }
#endif

  // Periodic HELLO beacon + screen heartbeat.
  static uint32_t lastBeacon = 0;
  if (millis() - lastBeacon >= 2000) {
    lastBeacon = millis();
    emit(toot::HELLO, nullptr, 0, sendEspNow, nullptr);
  }
#if USE_TDECK_HW
  static uint32_t lastRender = 0;
  if (gScreenDirty || millis() - lastRender >= 1000) {
    lastRender = millis();
    gScreenDirty = false;
    renderScreen();
  }
#endif
}
