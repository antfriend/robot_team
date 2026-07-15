// v4c_edge.ino — Heltec WiFi LoRa 32 V4, EDGE / tail node (A32 agent).
//
// Role: gateway for the most remote ESP-NOW cluster (toot_network_architecture.md).
// Aggregates/summarizes the local K10-cluster percepts before spending LoRa airtime;
// optional GNSS stamps real @LATxLONy. Serves its own TTDB to the companion via TtdbShare.
//
// Brought to FULL fleet parity with the verified V4-B relay: it is an ESP-NOW
// **Dream-Cycle participant** — deferred + paced TTDB serve (burst from loop(), never the
// recv callback, or the WiFi task starves its own TX), want_ack ACK + dedup re-ACK
// (TTN-RFC-0007 §5), TIME_SYNC adopt + @LAT99 (TTN-RFC-0008), belief TTDB_PUT adopt + @LAT98
// attestation (TTN-RFC-0009), SP0 link/entity/BLE percepts (ttn-semantic-positioning.md),
// remote CMD_CLEAR_PERCEPTS, OLED status — plus the MAX98357A amp and the band's offbeat
// hi-hat part. Uniform with the other nodes so a bench test sees identical behavior from
// every participant.
//
// LoRa (SX1262) is gated behind USE_LORA (Phase 4: long haul back to V4-B). The edge does
// NOT promiscuously re-broadcast (it's the tail, not a mid-relay); its Phase-4 job is
// cluster aggregation over LoRa, a separate milestone.
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
#include <Pulse.h>    // band tempo (PULSE_DEFAULT_BEAT_MS) lives in Pulse.h — 120 BPM
#include <Score.h>
#include <LinkPercept.h>  // SP0: every authenticated reception becomes a percept
#include <BleLink.h>      // SP0 near-range tier: BLE advert+scan -> PROTO_BLE percepts
#include <EntityPercept.h>  // SP0 entity tier: WiFi BSSID sightings -> @LAT96 percepts
#include <RobotTeamConfig.h>

// --- I2S speaker (MAX98357A) — the LoRa spine's voice -----------------------
// Adafruit MAX98357A I2S 3W amp (adafru.it/3006). Wiring per max98357a-v4-wiring.html /
// hardware_specs.md §2: VIN->3V3, GND->GND, LRC->GPIO5, BCLK->GPIO7, DIN->GPIO6, GAIN &
// SD float. Same driver as the T-Deck console: no analog/PWM path, so a tone is
// synthesized as 16-bit I2S samples. toneI2S blocks ~ms, so it runs from setup()/loop()
// only — never a callback (the deferred-tone discipline every other node uses).
#define USE_SPEAKER 1
#if USE_SPEAKER
#include <ESP_I2S.h>
static I2SClass gI2S;
// 8 kHz (not 16k): the hand-wired MAX98357A only locks reliably at a low BCLK (see companion.md
// §6 / v4a_bridge). Higher fs degrades over the jumper wiring. Fine for toots/beeps/kicks.
static const uint32_t I2S_RATE = 8000;
static const int PIN_I2S_BCLK = 7;   // MAX98357A BCLK
static const int PIN_I2S_WS   = 5;   // word select / LRC
static const int PIN_I2S_DOUT = 6;   // data to amp (DIN)

// Synthesize a `ms`-long SQUARE wave at `freq` as 16-bit stereo samples (L=R; the amp is mono
// but takes stereo frames). Square, not sine: on this hand-wired MAX98357A a sine only
// stuttered/blipped, but a square (max-energy, snaps +/-amp) reproduces cleanly and sustains.
// Blocks ~ms — call from setup()/loop() only.
static void toneI2S(float freq, uint32_t ms, float amp = 11000.0f) {
  const int N = 256;
  int16_t buf[N * 2];
  uint32_t total = (uint32_t)((uint64_t)I2S_RATE * ms / 1000);
  float phase = 0.0f, inc = 2.0f * (float)M_PI * freq / (float)I2S_RATE;
  uint32_t done = 0;
  while (done < total) {
    uint32_t n = total - done; if (n > (uint32_t)N) n = N;
    for (uint32_t i = 0; i < n; ++i) {
      int16_t s = (phase < (float)M_PI) ? (int16_t)amp : (int16_t)-amp;  // 50% square
      phase += inc; if (phase > 2.0f * (float)M_PI) phase -= 2.0f * (float)M_PI;
      buf[2 * i] = s; buf[2 * i + 1] = s;
    }
    gI2S.write((uint8_t*)buf, n * 2 * sizeof(int16_t));
    done += n;
  }
}

// The Toot-Toot signature on boot — two rising toots, C4 -> G4 (a rising fifth). Dropped an
// octave from C5/G5 now that it's a square wave — the harmonics carry these lower notes fine.
static void playStartupToot() {
  toneI2S(262.0f, 220);   // C4
  delay(40);
  toneI2S(392.0f, 380);   // G4
}
#endif

#define USE_LORA 0  // Phase 4: SX1262 long haul back to V4-B.
#define USE_GNSS 0  // Optional: SH1.25-8P GPS for @LATxLONy stamping.

// --- fleet pulse (TTN-RFC-0010) ---------------------------------------------
// V4-C plays the OFFBEAT HI-HAT: a C5 tick (+ LED / OLED dot) on the "&" of each beat
// (steps 2/6/10/14 of the 16-step bar), completing the rhythm section under V4-A's kick
// (every beat) and V4-B's snare (beats 2 & 4). The shared Pulse engine owns the time-base
// + election; this sketch supplies transport (PULSE codec) + instrument. Lowest id
// conducts, so V4-C (0x12) follows V4-A (0x10) / V4-B (0x11).
#define USE_PULSE 1
static pulse::Engine gPulse;
// Heltec V4 onboard white LED (GPIO35 on V3, pin-compatible V4 — confirm vs pinmap;
// OLED dot is the guaranteed-visible fallback per TTN-RFC-0010 §7.2).
static const int      kLedPin = 35;
static const uint32_t PULSE_LED_MS = 110;
static const uint32_t PULSE_PART_TONE_MS = 60;   // hi-hat tick on the amp (blocks; very short)
static uint32_t gLedClearMs = 0;
static bool     gBeatFlash = false;
// The part boots SILENT and only plays between CMD_PLAY and CMD_STOP (the T-Deck's g/x, band-
// wide via NODE_BROADCAST). The step clock keeps running while stopped so phase stays locked;
// only the audible/LED hit is muted. Mirrors the K10.
static bool     gPlayEnabled = false;
// V4-C's PART (TTN-RFC-0010 §7): the offbeat hi-hat — a C4 tick on the "&" of each beat
// (steps 2/6/10/14), the upbeats that lift V4-A's kick and V4-B's snare into a groove. C4
// square, one octave below the old C5. A Score::Phrase on the shared grid; re-voicing = table edit.
static const score::Note kPartNotes[] = {
  {2, score::C4, 1}, {6, score::C4, 1}, {10, score::C4, 1}, {14, score::C4, 1},
};
static const score::Phrase kPart = {kPartNotes, 4, 16};
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
static uint32_t gLastSrc = 0;     // src_node_id of the last toot seen
static volatile bool gOledDirty = true;

static const uint32_t kNodeId = NODE_V4C_EDGE;
static const char* kTtdbPath = "/ttdb.md";
static const char* kBeliefPath = "/belief.md";
static const uint8_t kBroadcast[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
static uint8_t gLocus[toot::LOCUS_LEN] = {0};

Ttdb gDb;
TtdbShare* gShare = nullptr;
toot::DedupSet gDedup(128);
TootSerialLink gSerial(Serial);
static uint32_t gSeq = 1;

#if USE_SPEAKER
// Deferred CMD_BEEP (T-Deck 'b' / companion): toneI2S() blocks, and CMD is handled inline in the
// recv callback — so the handler only sets these; loop() plays the tone (same discipline as the kick).
static volatile bool     gBeepPending = false;
static volatile uint16_t gBeepFreq = 0;   // Hz
static volatile uint16_t gBeepMs   = 0;   // duration
#endif

// --- link percepts (semantic positioning SP0, ttn-semantic-positioning.md) ---
// Per-peer RSSI histograms fed from the ESP-NOW recv callback; flushed from
// loop() as one @LAT97 TTDB record per window (see LinkPercept.h).
static linkpercept::Log gLinkLog;

#define USE_BLE 1  // SP0 near-range tier: also advertise+scan over BLE (proto:ble).
#if USE_BLE
// Feed a decoded, key-verified BLE fleet advert into the same link-percept histogram as
// ESP-NOW, tagged PROTO_BLE (BLE scan task — add() is increment-only/safe).
static void onBleObserve(uint32_t peer, int rssi) {
  gLinkLog.add(peer, rssi, linkpercept::PROTO_BLE);
}
#endif

// SP0 entity tier: duty-cycled WiFi scan logging visible BSSIDs as co-occurrence
// evidence (@LAT96 lane). V4-C is off-grid solar like V4-B — the scan hops channels
// ~2 s so it's kept rare and the ESP-NOW channel is re-asserted after each. Default off
// until flashed + serial-verified.
#define USE_WIFI_SCAN 1
#define WIFI_SCAN_PERIOD_MS 600000UL   // one ~2 s scan every 10 min

#if USE_WIFI_SCAN
static entitypercept::Log gEntityLog;
static uint32_t gLastScanKick = 0;
static bool gScanRunning = false;

// Duty-cycled, non-blocking WiFi scan (see v4a_bridge.ino for the rationale).
static void serviceWifiScan() {
  uint32_t now = millis();
  if (!gScanRunning && (now - gLastScanKick >= WIFI_SCAN_PERIOD_MS || gLastScanKick == 0)) {
    if (WiFi.scanNetworks(true /*async*/, false /*show_hidden*/) == WIFI_SCAN_RUNNING) {
      gScanRunning = true;
      gLastScanKick = now;
    }
  }
  if (gScanRunning) {
    int found = WiFi.scanComplete();
    if (found >= 0) {
      for (int i = 0; i < found; ++i) {
        uint8_t* b = WiFi.BSSID(i);
        if (b) gEntityLog.add(b, (int)WiFi.RSSI(i), entitypercept::KIND_WIFI_AP);
      }
      WiFi.scanDelete();
      esp_wifi_set_channel(ROBOT_TEAM_ESPNOW_CHANNEL, WIFI_SECOND_CHAN_NONE);
      gScanRunning = false;
      Serial.printf("[wifi] scan: %d AP(s) folded into @LAT96 window\n", found);
    }
  }
}
#endif

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
// The companion can push a re-authored belief to V4-C as offset-addressed TTDB_PUT
// slices, written to a SEPARATE /belief.md. On a CRC-verified commit V4-C appends a
// BELIEF-ADOPTED record to its own live TTDB (@LAT98 lane) — self-attestation that it
// integrated exactly those bytes. V4-C has no agent cadence to retune, so it stores +
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

// STATUS telemetry for the `monitor` / `band` tables. No agent cursor or temp sensor, so
// those fields are 0; report the synced state + epoch plus the PULSE tail.
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
    case toot::PERCEPT:
      // Edge role: aggregate/summarize cluster-C percepts here before spending LoRa
      // airtime (airtime is scarcest at the tail). Summarization is a Phase 3 task.
      break;
    case toot::CMD:
      // Band-wide play/stop: honor a broadcast (or targeted) PLAY/STOP so one T-Deck press
      // starts/stops the whole fleet. Boots silent. Other ops stay targeted (below).
      if ((toot::cmdOp(t) == toot::CMD_PLAY || toot::cmdOp(t) == toot::CMD_STOP) &&
          (toot::cmdTarget(t) == kNodeId || toot::cmdTarget(t) == NODE_BROADCAST)) {
        gPlayEnabled = (toot::cmdOp(t) == toot::CMD_PLAY);
        accepted = true;
        break;
      }
      if (toot::cmdTarget(t) == kNodeId) {
        if (toot::cmdOp(t) == toot::CMD_GET_STATUS) {
          uint8_t body[toot::STATUS_PULSE_PAYLOAD_LEN];
          uint8_t slen = buildStatus(body);
          emit(toot::PERCEPT, body, slen, reply, ctx);  // the reply is the answer
        }
#if USE_SPEAKER
        if (toot::cmdOp(t) == toot::CMD_BEEP) {
          uint16_t freq = 880, ms = 200;      // defaults (match the T-Deck)
          if (t.payload_len >= 9) {           // op + target(4) + freq(2) + dur(2)
            freq = toot::get_u16(t.payload + 5);
            ms   = toot::get_u16(t.payload + 7);
          }
          if (ms > 5000) ms = 5000;           // cap so loop() isn't stalled long
          gBeepFreq = freq; gBeepMs = ms; gBeepPending = true;  // played deferred from loop()
        }
#endif
        if (toot::cmdOp(t) == toot::CMD_CLEAR_PERCEPTS) {
          // Flash rewrite: reaches here only from loop() (radio path defers).
          // ACK only on success, so a failed prune is loud (laptop retries).
          accepted = gDb.removeLane(97);
          if (accepted)
            Serial.printf("[link] @LAT97 lane cleared (TTDB now %uB, %dr)\n",
                          (unsigned)gDb.fileSize(), gDb.recordCount());
        } else {
          accepted = true;  // ping / set-* (no-op on V4-C) / get-status all ACK
        }
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
static volatile bool gClearPending = false;
static toot::Toot gPendingClear;

static ESPNOW_RECV_CB_INFO(onEspNowRecv, info, data, len) {
  if (len <= 0) return;
  toot::Toot t;
  if (!toot::decode(data, (size_t)len, ROBOT_TEAM_KEY, ROBOT_TEAM_KEY_LEN, t)) return;
  // SP0 link percept: an authenticated frame is a distance measurement in
  // disguise. Logged BEFORE dedup — a retried duplicate is a real reception.
  gLinkLog.add(t.src_node_id, tootEspNowRssi(info), linkpercept::PROTO_ESPNOW);
  if (t.chunk_total > 1) return;            // no chunked consumer on V4-C (no reltest)
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
  if (t.type == toot::CMD && toot::cmdTarget(t) == kNodeId &&
      toot::cmdOp(t) == toot::CMD_CLEAR_PERCEPTS) {
    if (!gClearPending) { gPendingClear = t; gClearPending = true; }  // flash: loop()
    return;
  }

  handleToot(t, sendEspNow, nullptr);       // cheap toots (TIME_*, CMD, PULSE): handle inline
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

// Append a @LAT98 BELIEF-ADOPTED attestation (deferred). V4-C has no DIRECTIVE to act
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
  gOled.drawStr(0, 9, "V4-C EDGE");
  gOled.drawStr(78, 9, USE_LORA ? "LoRa+" : "LoRa-");
#if USE_PULSE
  if (gBeatFlash) gOled.drawDisc(124, 4, 3);   // offbeat hi-hat dot ("&" of each beat)
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

  snprintf(l, sizeof(l), "rx%lu sv%lu", (unsigned long)gEspRx,
           (unsigned long)gServed);
  gOled.drawStr(0, 53, l);

  snprintf(l, sizeof(l), "last %08X %lus", (unsigned)gLastSrc,
           (unsigned long)(millis() / 1000));
  gOled.drawStr(0, 64, l);
  gOled.sendBuffer();
}

void setup() {
  Serial.begin(115200);
  delay(200);

#if USE_SPEAKER
  // Audio first: bring up I2S and sound the boot "toot toot" before the OLED (like the
  // K10/T-Deck). VIN on 3V3 so the amp works on USB or battery; GAIN & SD float.
  gI2S.setPins(PIN_I2S_BCLK, PIN_I2S_WS, PIN_I2S_DOUT);
  if (gI2S.begin(I2S_MODE_STD, I2S_RATE, I2S_DATA_BIT_WIDTH_16BIT, I2S_SLOT_MODE_STEREO))
    playStartupToot();
  else
    Serial.println("I2S begin failed");
#endif

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
  gPulse.begin(kNodeId, millis());   // follows V4-A/V4-B (higher id); plays the hi-hat
#endif

#if USE_BLE
  blelink::begin(kNodeId, ROBOT_TEAM_KEY, ROBOT_TEAM_KEY_LEN, onBleObserve);
  Serial.println("BLE near-range tier up (advert + passive scan)");
#endif

  Serial.printf("V4-C edge 0x%08X online (LoRa %s, GNSS %s, BLE %s)\n", kNodeId,
                USE_LORA ? "on" : "off", USE_GNSS ? "on" : "off",
                USE_BLE ? "on" : "off");
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

  // Serve a deferred CMD_CLEAR_PERCEPTS (TTDB rewrite on the main task).
  if (gClearPending) {
    gClearPending = false;
    handleToot(gPendingClear, sendEspNow, nullptr);
  }

  // Append the deferred TTDB log records (flash write + re-index).
  if (gSyncPending) { gSyncPending = false; appendSyncRecord(); }
  if (gBeliefSyncPending) { gBeliefSyncPending = false; appendBeliefRecord(); }

  // SP0: flush the link-percept window into the @LAT97 lane (flash write from
  // loop(), never the recv callback). Lane-capped until SP1 adds pruning.
  if (gLinkLog.due(millis())) {
    int lane = 0;
    for (int i = 0; i < gDb.recordCount(); ++i)
      if (gDb.record(i).lat == 97) ++lane;
    if (lane >= LINKPERCEPT_MAX_LANE) {
      gLinkLog.reset(millis());  // lane full: drop the window, keep observing
    } else {
      char rec[1024];
      uint32_t t_sec = gSynced ? (uint32_t)(nowEpochMs() / 1000) : 0;
      uint64_t t_ms = gSynced ? (uint64_t)nowEpochMs() : (uint64_t)millis();
      size_t m = gLinkLog.buildRecord(rec, sizeof(rec), lane, t_sec, t_ms,
                                      gSynced, millis());
      if (m && gDb.appendRecord(rec, m))
        Serial.printf("[link] percept window -> @LAT97LON%d (TTDB %uB)\n", lane,
                      (unsigned)gDb.fileSize());
    }
  }

#if USE_WIFI_SCAN
  // SP0 entity tier: duty-cycled scan + flush the window into the @LAT96 lane
  // (same defer-to-loop + lane-cap discipline as the @LAT97 link lane).
  serviceWifiScan();
  if (gEntityLog.due(millis())) {
    int lane = 0;
    for (int i = 0; i < gDb.recordCount(); ++i)
      if (gDb.record(i).lat == 96) ++lane;
    if (lane >= ENTITYPERCEPT_MAX_LANE) {
      gEntityLog.reset(millis());  // lane full: drop the window, keep observing
    } else {
      char rec[1024];
      uint32_t t_sec = gSynced ? (uint32_t)(nowEpochMs() / 1000) : 0;
      uint64_t t_ms = gSynced ? (uint64_t)nowEpochMs() : (uint64_t)millis();
      size_t m = gEntityLog.buildRecord(rec, sizeof(rec), lane, t_sec, t_ms,
                                        gSynced, millis());
      if (m && gDb.appendRecord(rec, m))
        Serial.printf("[entity] percept window -> @LAT96LON%d (TTDB %uB)\n", lane,
                      (unsigned)gDb.fileSize());
    }
  }
#endif

#if USE_SPEAKER
  // Play a deferred CMD_BEEP requested from the recv callback / serial CMD (toneI2S blocks).
  if (gBeepPending) {
    gBeepPending = false;
    uint16_t freq = gBeepFreq, ms = gBeepMs;
    toneI2S((float)freq, ms);
    Serial.printf("[beep] %u Hz, %u ms\n", freq, ms);
  }
#endif

#if USE_PULSE
  // --- fleet pulse (TTN-RFC-0010): offbeat hi-hat — tick on the "&" of each beat ------
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
    // Hi-hat part: strike the tick on the amp + flash the LED + OLED dot on each struck
    // offbeat step of the phrase (2/6/10/14).
    uint16_t sip;
    uint32_t sc;
    const score::Note* nt = nullptr;
    if (gPulse.stepTick(pnow, kPart.steps, sip, sc) && (nt = score::noteAt(kPart, sip))) {
      if (gPlayEnabled) {             // boots silent; only between CMD_PLAY and CMD_STOP
        digitalWrite(kLedPin, HIGH);
        gLedClearMs = pnow + PULSE_LED_MS;
        gBeatFlash = true;
        gOledDirty = true;
#if USE_SPEAKER
        // Sound the hi-hat on the amp. Blocks ~PULSE_PART_TONE_MS; offbeats are >=250ms apart
        // (deferred-tone discipline, safe in loop()).
        if (nt->freq != score::REST) toneI2S((float)nt->freq, PULSE_PART_TONE_MS);
#endif
        Serial.printf("[part] step %u offbeat era=%lu\n", sip,
                      (unsigned long)gPulse.chart().era);
      }
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
