// v4a_bridge.ino — Heltec WiFi LoRa 32 V4, BRIDGE / head node (A32 agent).
//
// Role: the only path between the laptop companion and the mesh
// (toot_network_architecture.md). It:
//   - serves its OWN TTDB to the companion over USB-CDC serial;
//   - relays a companion TTDB_REQ from serial into the ESP-NOW (later LoRa)
//     mesh, and streams the mesh's TTDB_DATA replies back up the serial link.
//
// LoRa (SX1262) is gated behind USE_LORA so this compiles with just the esp32
// core. Enable in Phase 4 with RadioLib and the V4 pin map in hardware_specs.md.
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
// 8 kHz (not 16k): the MAX98357A on this hand-wired build only locks reliably at a low BCLK
// (8000*32 = 256 kHz). 16 kHz stuttered and 44.1 kHz gave silence — higher BCLK degrades over
// the jumper wiring. 8 kHz is plenty for toots/beeps/kicks. Shorten the clock wires to raise it.
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

// --- link percepts (semantic positioning SP0, ttn-semantic-positioning.md) ---
// Per-peer RSSI histograms fed from the ESP-NOW recv callback; flushed from
// loop() as one @LAT97 TTDB record per window (see LinkPercept.h).
static linkpercept::Log gLinkLog;

#define USE_LORA 0  // Phase 4: set 1 and wire RadioLib SX1262 (GPIO 8/9/10/11).
#define USE_BLE  1  // SP0 near-range tier: also advertise+scan over BLE (proto:ble).
// SP0 entity tier: duty-cycled WiFi scan logging visible BSSIDs as co-occurrence
// evidence (@LAT96 lane). V4s only (mains/solar); the scan hops channels ~2 s so
// it's kept rare and the ESP-NOW channel is re-asserted after each. Default off
// until flashed + serial-verified.
#define USE_WIFI_SCAN 1
#define WIFI_SCAN_PERIOD_MS 600000UL   // one ~2 s scan every 10 min

#if USE_WIFI_SCAN
// The entity log accumulates in RAM; flushed to @LAT96 from loop() like gLinkLog.
static entitypercept::Log gEntityLog;
static uint32_t gLastScanKick = 0;
static bool gScanRunning = false;

// Duty-cycled, non-blocking WiFi scan. Kick an async scan on the period; when it
// completes, fold each AP's BSSID+RSSI into gEntityLog, delete the results, and
// re-assert the ESP-NOW channel (scanning left the radio hopping). Never blocks.
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
    if (found >= 0) {                       // WIFI_SCAN_RUNNING(-1)/FAILED(-2) not yet
      for (int i = 0; i < found; ++i) {
        uint8_t* b = WiFi.BSSID(i);          // 6-byte AP MAC
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

// Feed a decoded, key-verified BLE fleet advert into the same link-percept histogram as
// ESP-NOW, tagged PROTO_BLE (runs in the BLE scan task — add() is increment-only/safe).
#if USE_BLE
static void onBleObserve(uint32_t peer, int rssi) {
  gLinkLog.add(peer, rssi, linkpercept::PROTO_BLE);
}
#endif

// --- fleet pulse (TTN-RFC-0010) ---------------------------------------------
// The bridge has the lowest node id (0x10), so when it is present it conducts the
// band (lowest id keeps the baton). Its PART is the TIMEKEEPER: pulse the onboard
// LED + an OLED beat dot on EVERY beat. The shared Pulse engine owns the time-base
// and election; this sketch supplies the transport (PULSE codec) and instrument.
#define USE_PULSE 1
static pulse::Engine gPulse;
// Heltec WiFi LoRa 32 V4 onboard white LED. V4 is pin-compatible with V3, whose
// LED is GPIO35 — confirm against the V4 pinmap (hardware_specs.md hedges board
// pins); the OLED beat dot is the guaranteed-visible fallback either way.
static const int      kLedPin = 35;
static const uint32_t PULSE_LED_MS = 110;
static const uint32_t PULSE_PART_TONE_MS = 130;  // kick length on the amp (blocks; short)
static uint32_t gLedClearMs = 0;       // 0 = LED not currently flashing
static bool     gBeatFlash = false;    // OLED beat-dot state
// The part boots SILENT and only plays between CMD_PLAY and CMD_STOP (the T-Deck's g/x, band-
// wide via NODE_BROADCAST). The step clock keeps running while stopped so phase stays locked;
// only the audible/LED hit is muted. Mirrors the K10.
static bool     gPlayEnabled = false;
static uint32_t gHelloAt = 0;          // periodic HELLO so the conductor fast-locks us
// V4-A's PART (TTN-RFC-0010 §7): the timekeeper — "four on the floor", a note on every
// beat (steps 0/4/8/12 of the 16-step bar), the steady pulse the band rides. Now that the
// V4 has a MAX98357A speaker it sounds a C4 kick on each beat (was REST/LED-only); the
// LED + OLED-dot still hit with it. C4 (262 Hz) square — one octave below the old C5.
// Re-voicing is a table edit (Score.h).
static const score::Note kPartNotes[] = {
  {0, score::C4, 1}, {4, score::C4, 1}, {8, score::C4, 1}, {12, score::C4, 1},
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
// Vext (GPIO36, active-LOW). Driven with U8g2 on the generic esp32 core (no
// Heltec board library). Pins per hardware_specs.md section 2.
static const int kVextCtrl = 36;            // drive LOW to power the OLED rail
static const int kOledRst = 21, kOledScl = 18, kOledSda = 17;
U8G2_SSD1306_128X64_NONAME_F_HW_I2C gOled(U8G2_R0, kOledRst, kOledScl, kOledSda);

// Live status counters rendered on the OLED. Incremented from loop() and the
// ESP-NOW recv callback; the callback only flips gOledDirty (no I2C in the cb).
static uint32_t gSerIn = 0;       // frames decoded off the USB link
static uint32_t gInjected = 0;    // frames injected into the mesh
static uint32_t gLocalServed = 0; // local TTDB_REQ served over serial
static uint32_t gEspRx = 0;       // frames decoded off ESP-NOW
static uint32_t gBridged = 0;     // mesh frames bridged up to the laptop
static uint32_t gLastSrc = 0;     // src_node_id of the last toot seen
static volatile bool gOledDirty = true;

// Deferred CMD_BEEP (T-Deck 'b' key / companion): toneI2S() blocks ~dur_ms, so a beep
// requested from the ESP-NOW recv callback must NOT play there — the callback sets these
// and loop() sounds it. Same deferred-tone discipline as the pulse kick and the K10 beep.
static volatile bool     gBeepPending = false;
static volatile uint16_t gBeepFreq = 0;   // Hz
static volatile uint16_t gBeepMs   = 0;   // duration

static const uint32_t kNodeId = NODE_V4A_BRIDGE;
static const char* kTtdbPath = "/ttdb.md";
static const uint8_t kBroadcast[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
static uint8_t gLocus[toot::LOCUS_LEN] = {0};

Ttdb gDb;
TtdbShare* gShare = nullptr;
toot::DedupSet gDedup(128);
TootSerialLink gSerial(Serial);
static uint32_t gSeq = 1;

// Wall clock (TTN-RFC-0008): the bridge adopts TIME_SYNC like any node. It hears
// the sync over the un-deduped USB link, so exactly-once adoption/append is gated
// on a monotonic sync_id (§3.1), not on transport dedup.
static int64_t gClockOffsetMs = 0;
static bool gSynced = false;
static uint32_t gLastSyncId = 0;
static inline int64_t nowEpochMs() { return (int64_t)millis() + gClockOffsetMs; }

static bool sendEspNow(const uint8_t* frame, size_t len, void*) {
  return esp_now_send(kBroadcast, frame, len) == ESP_OK;
}
static bool sendSerial(const uint8_t* frame, size_t len, void*) {
  gSerial.writeFrame(frame, len);
  return true;
}

// Forward a verified frame across the mesh. (LoRa added in Phase 4.)
static void injectToMesh(const uint8_t* frame, size_t len) {
  esp_now_send(kBroadcast, frame, len);
}

// Emit a fresh toot up the serial link to the laptop.
static void emitSerial(toot::Type type, const uint8_t* body, uint8_t n) {
  toot::Toot t;
  t.type = type;
  t.src_node_id = kNodeId;
  t.toot_seq = gSeq++;
  memcpy(t.locus, gLocus, toot::LOCUS_LEN);
  if (n && body) memcpy(t.payload, body, n);
  t.payload_len = n;
  uint8_t fr[toot::MAX_FRAME];
  size_t fl = toot::encode(t, ROBOT_TEAM_KEY, ROBOT_TEAM_KEY_LEN, fr, sizeof(fr));
  if (fl) gSerial.writeFrame(fr, fl);
}

// Emit a fresh toot into the mesh over ESP-NOW (PULSE beacons, HELLO).
static void emitMesh(toot::Type type, const uint8_t* body, uint8_t n) {
  toot::Toot t;
  t.type = type;
  t.src_node_id = kNodeId;
  t.toot_seq = gSeq++;
  memcpy(t.locus, gLocus, toot::LOCUS_LEN);
  if (n && body) memcpy(t.payload, body, n);
  t.payload_len = n;
  uint8_t fr[toot::MAX_FRAME];
  size_t fl = toot::encode(t, ROBOT_TEAM_KEY, ROBOT_TEAM_KEY_LEN, fr, sizeof(fr));
  if (fl) esp_now_send(kBroadcast, fr, fl);
}

static void emitAckSerial(const toot::Toot& orig, uint8_t status) {
  toot::Toot ack;
  toot::makeAck(orig, kNodeId, gSeq++, status, ack);
  uint8_t fr[toot::MAX_FRAME];
  size_t fl = toot::encode(ack, ROBOT_TEAM_KEY, ROBOT_TEAM_KEY_LEN, fr, sizeof(fr));
  if (fl) gSerial.writeFrame(fr, fl);
}

// Adopt a TIME_SYNC for the bridge itself and append its sync-log record. Gated on
// the monotonic sync_id so a retransmit over the un-deduped USB link neither
// re-adopts nor double-appends (TTN-RFC-0008 §3.1, §4).
static void adoptTimeSync(const toot::Toot& t) {
  uint32_t sid; uint64_t ems;
  if (!toot::parseTimeSync(t, sid, ems)) return;
  uint32_t recv_ms = millis();
  if (gSynced && sid <= gLastSyncId) return;
  gClockOffsetMs = (int64_t)ems - (int64_t)recv_ms;
  gSynced = true;
  gLastSyncId = sid;
  int n = 0;
  for (int i = 0; i < gDb.recordCount(); ++i)
    if (gDb.record(i).lat == 99) ++n;
  uint32_t t_sec = (uint32_t)(ems / 1000ULL);
  int64_t offset = (int64_t)ems - (int64_t)recv_ms;
  char rec[200];
  int m = snprintf(
      rec, sizeof(rec),
      "\n---\n\n@LAT99LON%d | created:%lu | updated:%lu | relates:logs@LAT0LON0"
      "\n\n**SYNC** id:%lu t_ms:%llu recv_ms:%lu offset_ms:%lld\n",
      n, (unsigned long)t_sec, (unsigned long)t_sec, (unsigned long)sid,
      (unsigned long long)ems, (unsigned long)recv_ms, (long long)offset);
  if (m > 0) gDb.appendRecord(rec, (size_t)m);
  Serial.printf("[sync] bridge id=%lu offset=%lldms @LAT99LON%d (TTDB %uB)\n",
                (unsigned long)sid, (long long)offset, n, (unsigned)gDb.fileSize());
}

// The bridge's STATUS telemetry (Toot.h). No agent cursor or temp sensor, so those
// fields are 0; it reports its synced state + epoch for the `monitor` table.
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

static ESPNOW_RECV_CB_INFO(onEspNowRecv, info, data, len) {
  if (len <= 0) return;
  toot::Toot t;
  if (!toot::decode(data, (size_t)len, ROBOT_TEAM_KEY, ROBOT_TEAM_KEY_LEN, t))
    return;
  // SP0 link percept: an authenticated frame is a distance measurement in
  // disguise. Logged BEFORE dedup — a retried duplicate is a real reception.
  gLinkLog.add(t.src_node_id, tootEspNowRssi(info), linkpercept::PROTO_ESPNOW);
  if (gDedup.seen(t.src_node_id, t.toot_seq)) return;
  gEspRx++;
  gLastSrc = t.src_node_id;
  gOledDirty = true;
  // Bridge mesh -> laptop: anything destined upward (TTDB_DATA, telemetry,
  // beliefs, ACKs, skew-probe replies) is re-framed onto the serial link.
  if (t.type == toot::TTDB_DATA || t.type == toot::BELIEF ||
      t.type == toot::PERCEPT || t.type == toot::ACK ||
      t.type == toot::TIME_RESP) {
    gSerial.writeFrame(data, (size_t)len);
    gBridged++;
  } else if (t.type == toot::TTDB_REQ &&
             TtdbShare::requestTarget(t) == kNodeId) {
    if (gShare) gShare->handleRequest(t, sendEspNow, nullptr);
  }
#if USE_SPEAKER
  else if (t.type == toot::CMD && toot::cmdTarget(t) == kNodeId &&
           toot::cmdOp(t) == toot::CMD_BEEP) {
    // T-Deck 'b' (or companion) beep, over the mesh. Parse freq/dur; the tone is played
    // deferred from loop() — toneI2S blocks, so it must never run in this callback.
    uint16_t freq = 880, ms = 200;             // defaults (match the T-Deck)
    if (t.payload_len >= 9) {                   // op + target(4) + freq(2) + dur(2)
      freq = toot::get_u16(t.payload + 5);
      ms   = toot::get_u16(t.payload + 7);
    }
    if (ms > 5000) ms = 5000;                   // cap so loop() isn't stalled long
    gBeepFreq = freq;
    gBeepMs = ms;
    gBeepPending = true;
  }
#endif
  else if (t.type == toot::CMD &&
           (toot::cmdOp(t) == toot::CMD_PLAY || toot::cmdOp(t) == toot::CMD_STOP) &&
           (toot::cmdTarget(t) == kNodeId || toot::cmdTarget(t) == NODE_BROADCAST)) {
    // Band-wide play/stop (T-Deck g/x, broadcast). Just a flag — safe from the callback.
    gPlayEnabled = (toot::cmdOp(t) == toot::CMD_PLAY);
  }
#if USE_PULSE
  else if (t.type == toot::PULSE) {
    // Band time-base beacon (TTN-RFC-0010). Adoption is cheap (no flash), so it
    // runs here where millis() is the accurate receipt time; the beat renders from
    // loop(). The lowest-id rule means the bridge usually conducts, but it still
    // yields to any better (higher-era / lower-id) chart it hears.
    pulse::Chart c;
    uint64_t cond_epoch;
    if (toot::parsePulse(t, c.conductor_id, c.era, cond_epoch, c.downbeat_epoch,
                         c.beat_period_ms, c.meter_beats, c.flags))
      gPulse.onBeacon(c, cond_epoch, millis());
  } else if (t.type == toot::HELLO) {
    if (neighborIsNew(t.src_node_id)) gPulse.noteNeighbor(millis());
  }
#endif
}

// Render the live bridge status onto the OLED (called from loop(), never the cb).
static void renderOled() {
  char l[24];
  gOled.clearBuffer();
  gOled.setFont(u8g2_font_6x10_tf);              // 6x10 -> 21 cols x 6 rows
  gOled.drawStr(0, 9, "V4-A BRIDGE");
  gOled.drawStr(78, 9, USE_LORA ? "LoRa+" : "LoRa-");
#if USE_PULSE
  // Beat dot (top-right): filled on the beat, hollow otherwise — the band's pulse.
  if (gBeatFlash) gOled.drawDisc(124, 4, 3);
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

  snprintf(l, sizeof(l), "ESPNOW ch%d", ROBOT_TEAM_ESPNOW_CHANNEL);
  gOled.drawStr(0, 42, l);

  snprintf(l, sizeof(l), "se%lu in%lu sv%lu", (unsigned long)gSerIn,
           (unsigned long)gInjected, (unsigned long)gLocalServed);
  gOled.drawStr(0, 53, l);

  snprintf(l, sizeof(l), "rx%lu br%lu %lus", (unsigned long)gEspRx,
           (unsigned long)gBridged, (unsigned long)(millis() / 1000));
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

  // Bring up the OLED status display: Vext power rail first, then U8g2.
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
  gShare = new TtdbShare(gDb, ROBOT_TEAM_KEY, ROBOT_TEAM_KEY_LEN, kNodeId,
                         gLocus);

  WiFi.mode(WIFI_STA);
  esp_wifi_set_channel(ROBOT_TEAM_ESPNOW_CHANNEL, WIFI_SECOND_CHAN_NONE);
  esp_now_init();
  esp_now_register_recv_cb(onEspNowRecv);
  esp_now_peer_info_t peer = {};
  memcpy(peer.peer_addr, kBroadcast, 6);
  peer.channel = ROBOT_TEAM_ESPNOW_CHANNEL;
  peer.encrypt = false;
  esp_now_add_peer(&peer);

#if USE_PULSE
  gPulse.begin(kNodeId, millis());   // lowest id -> usually conducts the band
#endif

#if USE_BLE
  // Near-range tier: advertise this node + passively scan peers over BLE, feeding RSSI
  // into the same @LAT97 lane as ESP-NOW (proto:ble). Starts after WiFi/ESP-NOW so the
  // radio arbiter coexists them.
  blelink::begin(kNodeId, ROBOT_TEAM_KEY, ROBOT_TEAM_KEY_LEN, onBleObserve);
  Serial.println("BLE near-range tier up (advert + passive scan)");
#endif

  Serial.printf("V4-A bridge 0x%08X online (LoRa %s, BLE %s)\n", kNodeId,
                USE_LORA ? "on" : "off", USE_BLE ? "on" : "off");
}

void loop() {
  // Laptop -> mesh / self. A TTDB_REQ for this node is served locally; for any
  // other node it is injected into the mesh and replies flow back via
  // onEspNowRecv -> serial.
  uint8_t buf[toot::MAX_FRAME];
  size_t n = 0;
  if (gSerial.poll(buf, sizeof(buf), n)) {
    toot::Toot t;
    if (toot::decode(buf, n, ROBOT_TEAM_KEY, ROBOT_TEAM_KEY_LEN, t)) {
      gSerIn++;
      gLastSrc = t.src_node_id;
      gOledDirty = true;
      // A request addressed to the bridge is served locally over serial;
      // anything else is injected into the mesh, and replies come back via
      // onEspNowRecv -> serial.
      if (t.type == toot::TTDB_REQ && TtdbShare::requestTarget(t) == kNodeId) {
        if (gShare) gShare->handleRequest(t, sendSerial, nullptr);
        gLocalServed++;
      } else if (t.type == toot::TIME_SYNC) {
        // The bridge adopts the sync itself, ACKs over serial, AND forwards it
        // into the mesh so the leaves (K10) adopt too (TTN-RFC-0008 §2.1).
        adoptTimeSync(t);
        if (t.flags & toot::FLAG_WANT_ACK) emitAckSerial(t, toot::ACK_ACCEPTED);
        injectToMesh(buf, n);
        gInjected++;
      } else if (t.type == toot::TIME_REQ) {
        uint32_t pid, target;
        if (toot::parseTimeReq(t, pid, target) && target == kNodeId) {
          uint8_t body[toot::TIME_RESP_PAYLOAD_LEN];
          toot::put_u32(body + 0, pid);
          toot::put_u64(body + 4, (uint64_t)nowEpochMs());
          emitSerial(toot::TIME_RESP, body, sizeof(body));
        } else {
          injectToMesh(buf, n);  // probe addressed to a mesh node
          gInjected++;
        }
      } else if (t.type == toot::CMD && toot::cmdTarget(t) == kNodeId) {
        // CMD addressed to the bridge itself: answer GET_STATUS with a PERCEPT,
        // and ACK any want_ack CMD. (Relayed CMDs for mesh nodes fall through.)
        bool ok = true;
        if (toot::cmdOp(t) == toot::CMD_GET_STATUS) {
          uint8_t body[toot::STATUS_PULSE_PAYLOAD_LEN];
          uint8_t slen = buildStatus(body);
          emitSerial(toot::PERCEPT, body, slen);
        } else if (toot::cmdOp(t) == toot::CMD_CLEAR_PERCEPTS) {
          // SP1 prune. Serial CMDs already run in loop(), so the TTDB rewrite
          // is safe here. ACK only on success (a failed prune must be loud).
          ok = gDb.removeLane(97);
          if (ok)
            Serial.printf("[link] @LAT97 lane cleared (TTDB now %uB, %dr)\n",
                          (unsigned)gDb.fileSize(), gDb.recordCount());
        }
#if USE_SPEAKER
        else if (toot::cmdOp(t) == toot::CMD_BEEP) {
          // Beep from the laptop (same deferred play as the mesh path below).
          uint16_t freq = 880, ms = 200;
          if (t.payload_len >= 9) {
            freq = toot::get_u16(t.payload + 5);
            ms   = toot::get_u16(t.payload + 7);
          }
          if (ms > 5000) ms = 5000;
          gBeepFreq = freq;
          gBeepMs = ms;
          gBeepPending = true;
        }
#endif
        else if (toot::cmdOp(t) == toot::CMD_PLAY || toot::cmdOp(t) == toot::CMD_STOP) {
          gPlayEnabled = (toot::cmdOp(t) == toot::CMD_PLAY);   // band play/stop over USB
        }
        if (ok && (t.flags & toot::FLAG_WANT_ACK))
          emitAckSerial(t, toot::ACK_ACCEPTED);
      } else {
        injectToMesh(buf, n);
        gInjected++;
      }
    }
  }

#if USE_SPEAKER
  // Play a deferred CMD_BEEP requested from the recv callback / serial CMD (toneI2S blocks
  // ~dur_ms, so it plays here in loop(), never from the callback).
  if (gBeepPending) {
    gBeepPending = false;
    uint16_t freq = gBeepFreq, ms = gBeepMs;
    toneI2S((float)freq, ms);
    Serial.printf("[beep] %u Hz, %u ms\n", freq, ms);
  }
#endif

#if USE_PULSE
  // --- fleet pulse (TTN-RFC-0010): timekeeper part — LED + OLED dot every beat ----
  {
    uint32_t pnow = millis();
    // Announce ourselves periodically so the conductor can fast-lock us (and so we
    // are heard if a lower-id node ever appears). Cheap; ~every 2 s.
    if (pnow - gHelloAt >= 2000) {
      gHelloAt = pnow;
      emitMesh(toot::HELLO, nullptr, 0);
    }
    // Emit a chart beacon only when due (drift-paced) or to fast-lock a newcomer —
    // never one per beat (§5).
    pulse::Chart oc;
    uint64_t oepoch;
    if (gPulse.update(pnow, oc, oepoch)) {
      uint8_t body[toot::PULSE_PAYLOAD_LEN];
      uint8_t blen = toot::buildPulse(body, oc.conductor_id, oc.era, oepoch,
                                      oc.downbeat_epoch, oc.beat_period_ms,
                                      oc.meter_beats, oc.flags);
      emitMesh(toot::PULSE, body, blen);
      Serial.printf("[pulse] beacon era=%lu cond=0x%08X period=%ums%s\n",
                    (unsigned long)oc.era, (unsigned)oc.conductor_id,
                    oc.beat_period_ms, gPulse.conductor() ? " (conductor)" : "");
    }
    // Timekeeper part: strike the note (kick) + flash the LED + OLED dot on each struck
    // step of the phrase.
    uint16_t sip;
    uint32_t sc;
    const score::Note* nt = nullptr;
    if (gPulse.stepTick(pnow, kPart.steps, sip, sc) && (nt = score::noteAt(kPart, sip))) {
      if (gPlayEnabled) {              // boots silent; only between CMD_PLAY and CMD_STOP
        digitalWrite(kLedPin, HIGH);
        gLedClearMs = pnow + PULSE_LED_MS;
        gBeatFlash = true;
        gOledDirty = true;
#if USE_SPEAKER
        // Sound the kick on the amp. Blocks ~PULSE_PART_TONE_MS; beats are >=500ms apart, so
        // this is the same deferred-tone discipline the K10/T-Deck use in loop().
        if (nt->freq != score::REST) toneI2S((float)nt->freq, PULSE_PART_TONE_MS);
#endif
        Serial.printf("[part] step %u beat %u%s era=%lu\n", sip, (sip / 4) % 4 + 1,
                      sip == 0 ? " DOWNBEAT" : "", (unsigned long)gPulse.chart().era);
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
  // SP0 entity tier: run the duty-cycled scan, then flush its window into the
  // @LAT96 lane (same defer-to-loop + lane-cap discipline as the @LAT97 link lane).
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

  // Refresh the OLED on change, plus a ~1s heartbeat to tick the uptime.
  static uint32_t lastRender = 0;
  if (gOledDirty || millis() - lastRender >= 1000) {
    lastRender = millis();
    gOledDirty = false;
    renderOled();
  }
}
