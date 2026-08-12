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
#include <HeroArc.h>  // the hero's-arc song: scene -> phrase tables for every role
#include <LinkPercept.h>  // SP0: every authenticated reception becomes a percept
#include <BleLink.h>      // SP0 near-range tier: BLE advert+scan -> PROTO_BLE percepts
#include <EntityPercept.h>  // SP0 entity tier: WiFi BSSID sightings -> @LAT96 percepts
#include <TimeStreamNode.h>  // the team time stream -> @LAT90 (a timeline the fleet owns)
#include <LaneGenNode.h>   // lane generations: a prune writes down its own boundary -> @LAT100
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
// Boot toot plays at 25% of fleet loudness (75% quieter); the beat kick keeps full amp.
static const float STARTUP_TOOT_AMP = 2750.0f;   // 11000 / 4
static void playStartupToot() {
  toneI2S(262.0f, 220, STARTUP_TOOT_AMP);   // C4
  delay(40);
  toneI2S(392.0f, 380, STARTUP_TOOT_AMP);   // G4
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
// V4-A's PART in the hero's-arc song (HeroArc.h, TTN-RFC-0010 §7): the TIMEKEEPER —
// "four on the floor", the steady C4 kick the story rides, present from scene 0
// (V4-A alone) and silent only through the ordeal. Which scenes it plays is authored
// in the score table, not here — re-arranging the song is a HeroArc.h edit.
static const score::Part& kPart = heroarc::kTimekeeper;

// --- the duet (CMD_DUET) -----------------------------------------------------
// Being invited into a duet overrides this node's PART for as long as it lasts: the
// timekeeper's job is the floor under the story, and a duet is somebody asking it to
// carry a melody instead. Not a chart scene (a scene is band-wide and would pull in
// every powered member; see Toot.h) and not persisted — the invitation belongs to the
// moment the console asked. Same shape as both consoles' copy, deliberately: this is
// the fourth node to learn it and the four should stay comparable line for line.
static uint8_t  gDuetRole = toot::DUET_OFF;
static uint32_t gDuetPeer = 0;
static uint8_t  gDuetSpeed = 1;      // 1 = as written, 2 = double time (set by the inviter)
static inline bool duetOn() { return gDuetRole != toot::DUET_OFF; }

// Can this phrase be taken at `speed`? Double time traverses the SAME note table in half
// as many steps, so every note must still land on a step the sequencer visits (noteAt is
// an exact match). Refuse rather than silently drop a note — kOdeLead's tied note at step
// 54 is exactly that case at ÷4. Computed once when a duet is set up, not per step.
static uint8_t validDuetSpeed(const score::Phrase& ph, uint8_t speed) {
  if (speed < 1) return 1;
  if (speed > toot::DUET_SPEED_MAX) speed = toot::DUET_SPEED_MAX;
  if (ph.steps % speed) return 1;
  for (uint16_t i = 0; i < ph.count; ++i)
    if (ph.notes[i].step % speed) return 1;
  return speed;
}

// Enter/leave a duet, validating the inviter's speed against the phrase our role names.
// Both voices must land on the same speed or they cover the phrase at different rates and
// come apart — which is why the inviter sends it rather than each side deciding.
static void setDuet(uint8_t role, uint32_t partner, uint8_t speed) {
  if (role == toot::DUET_OFF) {
    gDuetRole = toot::DUET_OFF;
    gDuetPeer = 0;
    gDuetSpeed = 1;
    return;
  }
  gDuetRole = role;
  gDuetPeer = partner;
  const score::Phrase& ph =
      (role == toot::DUET_LEAD) ? heroarc::kOdeLead : heroarc::kOdeHarm;
  gDuetSpeed = validDuetSpeed(ph, speed);
  if (gDuetSpeed != speed)
    Serial.printf("[duet] speed x%u refused (a note would be dropped) -> x%u\n",
                  speed, gDuetSpeed);
}

// Apply a CMD_DUET payload. Roles ride on the wire, so nothing here assumes who invited
// whom — the bridge can lead a duet as readily as harmonise one. The inviter RE-ASSERTS a
// live duet every couple of seconds (a single ESP-NOW invitation gets dropped), so log
// only on a real change: an otherwise-identical repeat is the mechanism working.
static bool applyDuetCmd(const toot::Toot& t) {
  if (t.payload_len < 10) return false;
  uint32_t partner = toot::get_u32(t.payload + 5);
  uint8_t role = t.payload[9];
  // The speed byte is additive: a sender that predates it means "as written", the same
  // discipline the STATUS and PULSE tails use.
  uint8_t speed = (t.payload_len >= 11) ? t.payload[10] : 1;
  bool changed = (role != gDuetRole) || (gDuetSpeed != speed);
  setDuet(role, partner, speed);
  if (changed)
    Serial.printf("[duet] %s by 0x%08X (speed x%u)\n",
                  role == toot::DUET_OFF ? "dismissed"
                  : role == toot::DUET_LEAD ? "invited to LEAD" : "invited to HARM",
                  (unsigned)partner, gDuetSpeed);
  return true;
}

// Conductor fast-lock (§4.2): only beacon when a neighbor actually needs locking, not on
// every HELLO.
static uint32_t gNeighbors[8] = {0};
static uint32_t gNeighborSeen[8] = {0};
static int      gNeighborCount = 0;
// Fast-lock a neighbor that is brand-new OR returning after a gap (a power-cycle): as the
// conductor we then beacon immediately so the (re)joiner locks within a round trip instead
// of waiting up to PULSE_RESYNC_PERIOD for the next scheduled beacon. A steadily-present
// neighbor (HELLO ~every 2 s) does NOT retrigger it, so steady-state traffic stays minimal.
// Without the returning-neighbor case, a reflashed or power-cycled peer self-appoints at
// era 1 and free-runs as its own conductor for up to a full resync period (30 s) before it
// hears us and yields — which reads as a split conductor/era in `band`.
static const uint32_t NEIGHBOR_REJOIN_GAP_MS = 3000;
static bool neighborNeedsLock(uint32_t src, uint32_t now) {
  for (int i = 0; i < gNeighborCount; ++i) {
    if (gNeighbors[i] == src) {
      bool rejoined = (uint32_t)(now - gNeighborSeen[i]) >= NEIGHBOR_REJOIN_GAP_MS;
      gNeighborSeen[i] = now;
      return rejoined;
    }
  }
  if (gNeighborCount < (int)(sizeof(gNeighbors) / sizeof(gNeighbors[0]))) {
    gNeighbors[gNeighborCount] = src;
    gNeighborSeen[gNeighborCount] = now;
    gNeighborCount++;
  }
  return true;   // brand new
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
// --- the team time stream (TimeStreamNode.h) --------------------------------
// gTs owns BOTH facts now: which shared timeline this node is on, and whether that
// timeline knows the date. The old single `synced` bit could only ever answer the
// second, and answered it "no" for a fleet in perfect agreement with itself. The
// macros keep every reader below reading the way it always did; the difference is
// that they are callback-safe scalars refreshed once per loop(), never live reads of
// an engine the WiFi task must not touch.
static timestream::Node gTs;
#define gStamp         (gTs.stamp())
#define gStreamWallSec (gTs.wallSec())
#define gSynced        (gTs.wall())
#define gClockOffsetMs (gTs.clockOffsetMs())
static uint32_t gLastSyncId = 0;
static inline int64_t nowEpochMs() { return gTs.nowEpochMs(); }

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
  // The laptop supplies the DATE. It does not supply the timeline — the fleet already
  // has one — so this ANCHORS the stream rather than replacing its clock. Latched
  // here, applied by gTs.service() from loop().
  gTs.onTimeSync(ems, recv_ms, t.src_node_id);
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

// --- interoception (CMD_GET_INTERO) ------------------------------------------
// What the bridge can say about its own body, so the T-Deck's record pane can draw it
// the same way it draws the consoles'. Nothing here is display-shaped — the receiver has
// a different panel and palette, and the thing worth sending across a mesh is the
// measurement, not the pixels.
//
// The two PIN constants are MEASURED on this board, not inherited: an ADC sweep of every
// ADC1 pin (GPIO1-10) against each candidate divider-enable found GPIO1 reading 827 mV with
// GPIO37 driven HIGH and a flat 0 mV in every other state, repeatably. ⚠ Note the polarity —
// the V3's ADC_Ctrl is documented active-LOW and this board is the opposite way round.
// Driving it LOW is exactly the state that DISCONNECTS the divider, which is why the first
// build of this reported 0.000 V with a known-good pack attached.
// ⚠ BAT_DIVIDER is still inherited and unmetered. 4.9 turns the measured 827 mV into 4.05 V,
// a textbook 1S pack on charge, so it is at worst close — but "plausible" is not "checked",
// so the RAW pin millivolts still print beside the derived voltage on the first sample.
// Same discipline as the T-Deck's BAT_DIVIDER.
static const int   PIN_BAT_ADC  = 1;      // measured; matches hardware_specs.md §2
static const int   PIN_ADC_CTRL = 37;     // measured: HIGH connects the divider, LOW opens it
static const float BAT_DIVIDER  = 4.9f;   // V3 divider 390k/100k -> (390+100)/100
static const uint32_t INTERO_PERIOD_MS = 2000;   // these signals move in minutes

// ⚠ 0 mV is a REAL, EXPECTED reading here, not a "not yet sampled" one: with no pack on
// the JST lead the divider has nothing to divide, and the bridge runs on mains. So the
// have-we-sampled sentinel is its own flag rather than `gBatMv != 0` the way it is on the
// two consoles — using the measurement as its own validity flag made the sampler re-run
// and re-print the boot line on EVERY loop pass, which is a serial flood that shows up as
// this node's own worst-loop-pass number.
static bool     gBatSampled = false;
static uint16_t gBatMv    = 0;      // pack millivolts (0 = no pack / no divider)
static float    gBatSlow  = 0.0f;   // slow EMA — the fill/drain reference
static int8_t   gBatTrend = 0;      // +1 filling, -1 draining, 0 steady
static uint8_t  gBatPct   = 0;
static int16_t  gDieC10   = 0;      // ESP32-S3 die temperature, tenths of a degree
static uint32_t gMaxAllocK = 0;     // largest CONTIGUOUS block, NOT free heap
static uint32_t gWorstLoopMs = 0;   // worst loop pass in the last window (our own slowness)
static uint32_t gLoopWorstRun = 0;  // accumulator for the window in progress

// Above this the number on the pin is NOT a 1S pack voltage — a Li-ion cell tops out at
// 4.20 V, so more than this means we are reading the USB rail with no pack on it, or the
// divider ratio above is wrong. Either way a state-of-charge percentage would be fiction,
// so the volts are still reported and only the PERCENTAGE is withheld (255 = unknown).
// The bridge runs on mains, so this is its expected steady state, not an error.
static const uint16_t BAT_LIION_CEILING_MV = 4250;

// Voltage -> state of charge for a 1S Li-ion, linear between curve points. Deliberately
// coarse: the flat middle of a Li-ion curve means any percentage between 3.7 and 3.9 V is
// a guess, and more decimals would only dress that up.
static uint8_t batPercent(uint16_t mv) {
  static const uint16_t kV[] = {3300, 3500, 3680, 3730, 3760, 3790,
                                3820, 3870, 3950, 4000, 4100, 4200};
  static const uint8_t  kP[] = {   0,    5,   10,   20,   30,   40,
                                  50,   60,   70,   80,   90,  100};
  const int n = sizeof(kP) / sizeof(kP[0]);
  if (mv <= kV[0]) return 0;
  if (mv >= kV[n - 1]) return 100;
  for (int i = 1; i < n; ++i)
    if (mv < kV[i]) {
      int span = kV[i] - kV[i - 1];
      return (uint8_t)(kP[i - 1] + (int)(kP[i] - kP[i - 1]) * (mv - kV[i - 1]) / span);
    }
  return 100;
}

static void serviceIntero(uint32_t now) {
  static uint32_t last = 0;
  if (gBatSampled && now - last < INTERO_PERIOD_MS) return;
  last = now;

  // Four reads averaged: one 12-bit sample of a divided pack is noisy at exactly the
  // millivolt scale the trend arrow reads, and the burst costs well under a millisecond
  // once per 2 s. No settle delay here because PIN_ADC_CTRL is held LOW for good (setup)
  // rather than pulsed per read — ~7 uA through a 490k divider is not worth stalling a
  // loop that has a band clock to keep.
  uint32_t acc = 0;
  for (int i = 0; i < 4; ++i) acc += analogReadMilliVolts(PIN_BAT_ADC);
  uint32_t pin_mv = acc / 4;
  uint16_t mv = (uint16_t)(pin_mv * BAT_DIVIDER);

  bool first = !gBatSampled;
  gBatSampled = true;
  gBatMv = mv;
  // 255 = "there is no pack voltage to turn into a percentage" — either nothing is
  // connected (0 mV) or the number is above a cell's ceiling. The volts are still
  // reported; only the percentage, the part that would be invented, is withheld.
  gBatPct = (mv == 0 || mv > BAT_LIION_CEILING_MV) ? 255 : batPercent(mv);
  // Filling or draining? A ~2-minute EMA is the reference, so the arrow reports the
  // direction of the PACK rather than of the last sample's noise. There is no VBUS sense
  // pin, so no charge state is claimed — only which way the voltage is actually moving.
  if (first) gBatSlow = (float)mv;
  else       gBatSlow += ((float)mv - gBatSlow) * 0.03f;
  float d = (float)mv - gBatSlow;
  gBatTrend = (d > 12.0f) ? 1 : (d < -12.0f) ? -1 : 0;

  // Die temperature, not ambient: there is no ambient sensor on this board. It reads high
  // (40-55 C is normal) with WiFi and BLE up millimetres away, so it measures how hard the
  // node is working as much as it measures the room.
  gDieC10 = (int16_t)lroundf(temperatureRead() * 10.0f);
  gMaxAllocK = ESP.getMaxAllocHeap() / 1024;

  if (first)
    Serial.printf("[intero] pin %lumV x%.2f = pack %umV (%u%%) | die %.1fC | "
                  "maxalloc %luK  <- CHECK THE PACK VOLTAGE AGAINST A METER\n",
                  (unsigned long)pin_mv, BAT_DIVIDER, mv, gBatPct,
                  gDieC10 / 10.0f, (unsigned long)gMaxAllocK);
}

// The bridge's STATUS telemetry (Toot.h). No agent cursor, so those fields are 0; it
// reports its synced state + epoch for the `monitor` table. The temperature field is no
// longer 0: it carries the die reading. Toot.h calls the field "ambient" and this is not
// that — but a die reading is a real measurement of a real body, and an empty field is not.
static uint8_t buildStatus(uint8_t* p) {
  toot::put_u16(p + 0, 0);
  toot::put_u16(p + 2, 0);
  toot::put_u16(p + 4, (uint16_t)(gDieC10 * 10));   // tenths here, HUNDREDTHS on the wire
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
  toot::put_u16(p + 43, ch.scene_id);   // v2 tail: what the band is playing
  return (uint8_t)toot::STATUS_PULSE_PAYLOAD_LEN;
#else
  return (uint8_t)toot::STATUS_PAYLOAD_LEN;
#endif
}

// INTERO PERCEPT — the answer to CMD_GET_INTERO (Toot.h INTERO_PERCEPT_PAYLOAD_LEN).
// Reads NOTHING: every field is the last sample serviceIntero() took on its own 2 s
// cadence, so this is safe from the recv callback and cheap enough for a remote console
// to poll while it watches us — which is exactly the use case (the T-Deck's record pane).
static uint8_t buildIntero(uint8_t* p) {
  toot::put_u16(p + 0, gBatMv);
  p[2] = gBatSampled ? gBatPct : 255;   // 255 = unknown (never sampled / no pack / not a pack)
  p[3] = (uint8_t)(int8_t)gBatTrend;
  toot::put_u16(p + 4, (uint16_t)gDieC10);
  toot::put_u16(p + 6, (uint16_t)gMaxAllocK);
  toot::put_u32(p + 8, millis() / 1000);
  toot::put_u16(p + 12, (uint16_t)(gWorstLoopMs > 65535 ? 65535 : gWorstLoopMs));
#if USE_PULSE
  const pulse::Chart& ch = gPulse.chart();
  toot::put_u16(p + 14, ch.beat_period_ms);
  toot::put_u32(p + 16, ch.conductor_id);
  // VOICING answers "is it singing", which PLAYING does not: PLAYING only means the band
  // clock is running, and the timekeeper is silent through the ordeal. Reported as the
  // STATE that would sound a note rather than the instant of one, so a 2 s poll cannot
  // fall between two beats and read false. Unlike the consoles there is no `!conductor()`
  // term: the bridge's voice has never been gated on holding the baton (see loop()).
  bool voicing = duetOn() ||
                 (gPlayEnabled && score::phraseForScene(kPart, gPulse.scene()) != nullptr);
  p[20] = (gSynced ? toot::INTERO_SYNCED : 0) |
          (gPulse.conductor() ? toot::INTERO_CONDUCTOR : 0) |
          (gPulse.playing() ? toot::INTERO_PLAYING : 0) |
          (voicing ? toot::INTERO_VOICING : 0);
#else
  toot::put_u16(p + 14, 0);
  toot::put_u32(p + 16, 0);
  p[20] = gSynced ? toot::INTERO_SYNCED : 0;
#endif
  return (uint8_t)toot::INTERO_PERCEPT_PAYLOAD_LEN;
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
  else if (t.type == toot::CMD && toot::cmdOp(t) == toot::CMD_GET_INTERO &&
           toot::cmdTarget(t) == kNodeId) {
    // "Show me your body", from the T-Deck's record pane over the air. buildIntero reads
    // nothing (all cached by serviceIntero) and the reply is ONE frame, so unlike a TTDB
    // burst this is safe to answer straight from the callback.
    uint8_t body[toot::INTERO_PERCEPT_PAYLOAD_LEN];
    uint8_t ilen = buildIntero(body);
    emitMesh(toot::PERCEPT, body, ilen);
  }
  else if (t.type == toot::CMD && toot::cmdOp(t) == toot::CMD_DUET &&
           toot::cmdTarget(t) == kNodeId) {
    // A console asking the bridge to sing with it. Flags + a phrase pointer only — no
    // flash, no tone (the note sounds from loop() like every other part).
    applyDuetCmd(t);
  }
  else if (t.type == toot::CMD &&
           (toot::cmdOp(t) == toot::CMD_PLAY || toot::cmdOp(t) == toot::CMD_STOP) &&
           (toot::cmdTarget(t) == kNodeId || toot::cmdTarget(t) == NODE_BROADCAST)) {
    // Band-wide play/stop (T-Deck g/x, broadcast). Just a flag — safe from the callback.
    gPlayEnabled = (toot::cmdOp(t) == toot::CMD_PLAY);
    if (!gPlayEnabled) setDuet(toot::DUET_OFF, 0, 1);   // stop means stop, duet included
#if USE_PULSE
    // CMD_PLAY also arms the story to walk itself: as conductor we auto-advance the early
    // scenes and hold at the grief (ORDEAL) for the returning roamer (see serviceSong).
    if (gPlayEnabled) gPulse.armSong(heroarc::SCENE_ALONE, millis());
    else              gPulse.disarmSong();
#endif
  }
#if USE_PULSE
  else if (t.type == toot::CMD && toot::cmdOp(t) == toot::CMD_SET_SCENE &&
           (toot::cmdTarget(t) == kNodeId || toot::cmdTarget(t) == NODE_BROADCAST)) {
    // Scene change from the T-Deck / mesh. Only the CONDUCTOR owns the chart, so only
    // it applies this; the rest learn the scene from the next beacon. Cheap (chart
    // fields + a beacon flag, no flash), so it is callback-safe like beacon adoption.
    if (gPulse.conductor() && t.payload_len >= 7)
      gPulse.setScene(toot::get_u16(t.payload + 5), millis());
  }
  else if (t.type == toot::PULSE) {
    // Band time-base beacon (TTN-RFC-0010). Adoption is cheap (no flash), so it
    // runs here where millis() is the accurate receipt time; the beat renders from
    // loop(). The lowest-id rule means the bridge usually conducts, but it still
    // yields to any better (higher-era / lower-id) chart it hears.
    pulse::Chart c;
    uint64_t cond_epoch;
    if (toot::parsePulse(t, c.conductor_id, c.era, cond_epoch, c.downbeat_epoch,
                         c.beat_period_ms, c.meter_beats, c.flags, &c.scene_id))
      gPulse.onBeacon(c, cond_epoch, millis());
  } else if (t.type == toot::HELLO) {
    if (neighborNeedsLock(t.src_node_id, millis())) gPulse.noteNeighbor(millis());
  }
#endif

  // The time-stream anchor rides on HELLO — every node emits one every 2 s and its
  // payload was EMPTY until now, so this is purely additive: a node still on old
  // firmware sends 0 bytes and parseAnchor declines, making it a non-participant
  // rather than a parse error. Outside the USE_PULSE guard on purpose: the band is
  // optional, a shared timeline is not.
  gTs.onHello(t, millis());
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
  if (gI2S.begin(I2S_MODE_STD, I2S_RATE, I2S_DATA_BIT_WIDTH_16BIT, I2S_SLOT_MODE_STEREO)) {
    // I2S comes up either way — the speaker must be ready for band notes and CMD_BEEP.
    // Only the boot signature is gated (STARTUP_TOOT, RobotTeamConfig.h): silent fleet.
#if STARTUP_TOOT
    playStartupToot();
#endif
  } else {
    Serial.println("I2S begin failed");
  }
#endif

#if USE_PULSE
  pinMode(kLedPin, OUTPUT);
  digitalWrite(kLedPin, LOW);
#endif

  // Connect the Vbat divider (HIGH — measured, see PIN_ADC_CTRL) and leave it connected:
  // the alternative is pulsing it per read with a settle delay, and ~8 uA through a 490k
  // divider is cheaper than stalling a loop that has a band clock to keep. If that current
  // ever matters, pulse it across two loop passes rather than blocking on a settle.
  pinMode(PIN_ADC_CTRL, OUTPUT);
  digitalWrite(PIN_ADC_CTRL, HIGH);

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
    Serial.printf("TTDB loaded: %u bytes, %d/%d records indexed (%d free)\n",
                  (unsigned)gDb.fileSize(), gDb.recordCount(),
                  TTDB_MAX_RECORDS, gDb.indexHeadroom());
    // The index is a whole-FILE budget shared by every lane, so a lane with room in
    // its own cap can still be refused - and until 2026-08-11 nothing said so.
    // Saturation is worse than a refusal: records past the cap are invisible to every
    // reader, and a lane prune walks the INDEX, so before the tail-carry fix the next
    // rewrite deleted them outright. That is how five @LAT101 records died once.
    if (gDb.indexSaturated())
      Serial.printf("!! TTDB INDEX SATURATED: file holds %u records, %u INVISIBLE to\n"
                    "   every reader. Prune a lane to surface them.\n",
                    (unsigned)gDb.headersSeen(), (unsigned)gDb.droppedRecords());
    else if (gDb.indexHeadroom() <= TTDB_INDEX_WARN_SLOTS)
      Serial.printf("!! TTDB INDEX NEARLY FULL: %d slot(s) left; at 0 EVERY lane\n"
                    "   stops accepting records whatever its own cap says.\n",
                    gDb.indexHeadroom());
  }
#if USE_WIFI_SCAN
  // ⚠ THE BOARD DECLARES ITS OWN @LAT96 BUILD, AT BOOT — see the Cardputer's copy.
  // `ENTITYPERCEPT_MAX_RUN` lives in EntityPercept.cpp, a separate translation unit, so
  // it can only be set by a BUILD PROPERTY, and a build property is invisible from the
  // outside. `max_run:1` is the MEASUREMENT build (every window writes its own record);
  // the default 6 folds them into runs. An entity SURVEY needs both nodes unfolded, so
  // this stopped being a Cardputer-only question and the V4 has to answer it too.
  Serial.printf("[entity] @LAT96 build: max_run:%d core:%d-of-%d scan:%lus%s\n",
                ENTITYPERCEPT_MAX_RUN, ENTITYPERCEPT_CORE_N, ENTITYPERCEPT_CORE_M,
                (unsigned long)(WIFI_SCAN_PERIOD_MS / 1000),
                ENTITYPERCEPT_MAX_RUN == 1 ? "  <- MEASUREMENT BUILD (no folding)" : "");
#endif
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

  // The time stream starts EMPTY, not with a stream of our own: this node listens for
  // TIMESTREAM_LISTEN_MS first (gTs.service), because joining an older stream is free
  // and forking one costs a merge. Independent of USE_PULSE — the band is optional, a
  // shared timeline is not.
  gTs.begin(kNodeId, &gDb, millis());

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

  // FIRST, before anything reads a clock: settle which timeline this node is on and
  // refresh gStamp. Every tier below stamps from that one snapshot, so records flushed
  // in the same pass carry the same instant rather than separate readings of a clock
  // that moved between them.
  gTs.service(millis());
  const uint32_t loop_t0 = millis();

  // The body's own senses. Cheap and rare (four ADC reads + a die-temperature read once
  // per 2 s), and it must run from loop() rather than from a CMD_GET_INTERO so a remote
  // poll costs the same whether or not anyone is watching.
  serviceIntero(loop_t0);

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
        } else if (toot::cmdOp(t) == toot::CMD_GET_INTERO) {
          // `companion.py intero --node v4a_bridge` over the cable.
          uint8_t body[toot::INTERO_PERCEPT_PAYLOAD_LEN];
          uint8_t ilen = buildIntero(body);
          emitSerial(toot::PERCEPT, body, ilen);
        } else if (toot::cmdOp(t) == toot::CMD_DUET) {
          ok = applyDuetCmd(t);
        } else if (toot::cmdOp(t) == toot::CMD_CLEAR_PERCEPTS) {
          // SP1 prune. Serial CMDs already run in loop(), so the TTDB rewrite
          // is safe here. ACK only on success (a failed prune must be loud).
          uint8_t lane = toot::cmdClearLane(t);   // 0 = every percept lane
          ok = (lane == TIMESTREAM_LANE)
                 ? lanegen::pruneTimeline(gDb, gStamp, kNodeId, gStreamWallSec)
                 : lanegen::prune(gDb, lane, gStamp, kNodeId, gStreamWallSec);
          if (ok)
            Serial.printf("[link] percept lane %s cleared (TTDB now %uB, %dr)\n",
                          lane ? String(lane).c_str() : "ALL",
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
          if (!gPlayEnabled) setDuet(toot::DUET_OFF, 0, 1);    // stop means stop
#if USE_PULSE
          if (gPlayEnabled) gPulse.armSong(heroarc::SCENE_ALONE, millis());
          else              gPulse.disarmSong();
#endif
        }
#if USE_PULSE
        else if (toot::cmdOp(t) == toot::CMD_SET_SCENE) {
          // Move the band to a scene of the song. Only the conductor may author the
          // chart, so the ACK reflects the achieved state: it confirms both that we
          // hold the baton and that the band is now on the asked-for scene (so a
          // repeat of the current scene still ACKs rather than looking like a failure).
          ok = false;
          if (gPulse.conductor() && t.payload_len >= 7) {
            uint16_t want = toot::get_u16(t.payload + 5);
            gPulse.setScene(want, millis());
            ok = (gPulse.scene() == want);
          }
        }
#endif
        if (ok && (t.flags & toot::FLAG_WANT_ACK))
          emitAckSerial(t, toot::ACK_ACCEPTED);
      }
#if USE_PULSE
      else if (t.type == toot::CMD && toot::cmdOp(t) == toot::CMD_SET_SCENE &&
               toot::cmdTarget(t) == NODE_BROADCAST) {
        // Broadcast scene change over USB: apply it here if we hold the baton, and
        // relay it either way so a mesh-side conductor can act on it.
        if (gPulse.conductor() && t.payload_len >= 7) {
          gPulse.setScene(toot::get_u16(t.payload + 5), millis());
          if (t.flags & toot::FLAG_WANT_ACK) emitAckSerial(t, toot::ACK_ACCEPTED);
        }
        injectToMesh(buf, n);
        gInjected++;
      }
#endif
      else {
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
      uint8_t hb[timestream::ANCHOR_LEN];
      size_t hn = gTs.helloPayload(hb, sizeof(hb), millis());
      emitMesh(toot::HELLO, hn ? hb : nullptr, hn);
    }
    // Emit a chart beacon only when due (drift-paced) or to fast-lock a newcomer —
    // never one per beat (§5).
    pulse::Chart oc;
    uint64_t oepoch;
    if (gPulse.update(pnow, oc, oepoch)) {
      uint8_t body[toot::PULSE_PAYLOAD_LEN];
      uint8_t blen = toot::buildPulse(body, oc.conductor_id, oc.era, oepoch,
                                      oc.downbeat_epoch, oc.beat_period_ms,
                                      oc.meter_beats, oc.flags, oc.scene_id);
      emitMesh(toot::PULSE, body, blen);
      Serial.printf("[pulse] beacon era=%lu cond=0x%08X period=%ums scene=%u%s\n",
                    (unsigned long)oc.era, (unsigned)oc.conductor_id,
                    oc.beat_period_ms, oc.scene_id,
                    gPulse.conductor() ? " (conductor)" : "");
    }
    // As conductor, walk the story: auto-advance the early scenes on SCENE_HOLD_MS and
    // hold at the grief (ORDEAL) until the returning T-Deck drives the RETURN/FINALE.
    gPulse.serviceSong(pnow, heroarc::SCENE_HOLD_MS, heroarc::SCENE_ORDEAL);
    // The chart's scene moved (or we just joined a band mid-song): re-selection is
    // just the phraseForScene lookup below reading the new scene.
    uint16_t new_scene;
    if (gPulse.sceneChanged(new_scene))
      Serial.printf("[scene] scene %u %s (era %lu cond 0x%08X)\n", new_scene,
                    heroarc::sceneName(new_scene),
                    (unsigned long)gPulse.chart().era,
                    (unsigned)gPulse.chart().conductor_id);
    // Timekeeper part: the scene selects the phrase (no row = SILENT in that scene);
    // the step clock runs regardless, so a silent scene stays in phase and re-entry
    // lands on the grid. Strike the note + LED + OLED dot on each struck step.
    // A DUET overrides the phrase (and the scene's silence) for as long as it lasts —
    // the pair was asked for by name, and the step clock underneath is the same one.
    const score::Phrase* ph;
    bool voice;
    uint8_t speed = 1;
    if (duetOn()) {
      ph = (gDuetRole == toot::DUET_LEAD) ? &heroarc::kOdeLead : &heroarc::kOdeHarm;
      voice = true;
      speed = gDuetSpeed;             // already validated against this phrase by setDuet
    } else {
      ph = score::phraseForScene(kPart, gPulse.scene());
      voice = gPlayEnabled;           // boots silent; only between CMD_PLAY and CMD_STOP
    }
    // DOUBLE TIME is these two lines: wrap the phrase in `steps/speed` slots and look the
    // note up at `sip*speed`. The pulse clock and beat period are untouched, so the pair
    // covers the written phrase in half the steps while staying locked to the beat the
    // rest of the fleet counts. ONE stepTick per pass — the call consumes the tick.
    const uint16_t steps = ph ? (uint16_t)(ph->steps / speed) : 16;
    uint16_t sip;
    uint32_t sc;
    static uint32_t prev_step = 0;
    static bool have_prev = false;
    if (gPulse.stepTick(pnow, steps, sip, sc)) {
      // Catch up over any steps this pass jumped, so a stalled pass cannot swallow the
      // note that fell in the gap. Defensive: the percept flush and a blocking tone both
      // exceed a step, and a duet's notes are only 2 steps apart.
      const score::Note* nt = nullptr;
      if (ph)
        nt = (have_prev && sc > prev_step + 1)
                 ? score::noteForCrossedSteps(*ph, prev_step, sc, speed, steps)
                 : score::noteAt(*ph, (uint16_t)(sip * speed));
      prev_step = sc;
      have_prev = true;
      if (nt && voice) {
        digitalWrite(kLedPin, HIGH);
        gLedClearMs = pnow + PULSE_LED_MS;
        gBeatFlash = true;
        gOledDirty = true;
#if USE_SPEAKER
        // Sound the note on the amp. Blocks; beats are >=500ms apart, so this is the same
        // deferred-tone discipline the K10/T-Deck use in loop(). Articulation scales with
        // speed so double time stays staccato instead of slurring into the next slot.
        if (nt->freq != score::REST) {
          uint32_t ms = PULSE_PART_TONE_MS / speed;
          if (ms < 80) ms = 80;
          toneI2S((float)nt->freq, ms);
        }
#endif
        if (duetOn())
          Serial.printf("[part] step %2u/%u  %4uHz (%s x%u)\n", sip, steps, nt->freq,
                        gDuetRole == toot::DUET_LEAD ? "duet-lead" : "duet-harm", speed);
        else
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
      size_t m = gLinkLog.buildRecord(rec, sizeof(rec), lane, gStreamWallSec,
                                      gStamp, millis());
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
      // SAY THIS OUT LOUD -- the same argument @LAT95 got after 2026-08-02, and it
      // cost a live debugging session on 2026-08-10 to notice @LAT96 never got it.
      // A full entity lane looks EXACTLY like a healthy node: the scan still runs and
      // prints, the other tiers still flush, and the window is dropped in silence.
      // Rate-limited to one line per 5 min so it informs without flooding.
      static uint32_t last_ent_full_log = 0;
      uint32_t nowf = millis();
      if (nowf - last_ent_full_log > 300000 || last_ent_full_log == 0) {
        last_ent_full_log = nowf;
        Serial.printf("[entity] @LAT96 lane FULL (%d/%d) - windows are being "
                      "DISCARDED. Prune with `companion.py cmd --op clear-percepts "
                      "--lane 96`.\n", lane, ENTITYPERCEPT_MAX_LANE);
      }
      gEntityLog.reset(nowf);      // lane full: drop the window, keep observing
    } else {
      // static + ENTITYPERCEPT_RECORD_BUF: since @LAT96 became change-triggered a
      // record can carry a **CORE** list and the run's **COVERED** union (worst
      // case 2322 B, pinned in tests/test_entitypercept.cpp). That fits neither the
      // old 1024 nor the loop task's stack, and buildRecord writes NOTHING rather
      // than truncating -- so an undersized buffer here loses windows silently.
      static char rec[ENTITYPERCEPT_RECORD_BUF];
      size_t m = gEntityLog.buildRecord(rec, sizeof(rec), lane, gStreamWallSec,
                                      gStamp, millis());
      if (m && gDb.appendRecord(rec, m))
        Serial.printf("[entity] percept window -> @LAT96LON%d (TTDB %uB)\n", lane,
                      (unsigned)gDb.fileSize());
      else if (gEntityLog.lastClose() == entitypercept::CLOSE_COVERED)
        // SAY THIS OUT LOUD. Under run-length "wrote nothing" is the NORMAL case
        // for a node in a stable environment, and a lane that silently does nothing
        // is this corpus's least favourite failure mode. The run length and core
        // size are how an operator tells a working fold from a dead tier.
        Serial.printf("[entity] window covered (run %d, core %d)\n",
                      gEntityLog.runLength(), gEntityLog.coreCount());
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

  // Close the profiler window. Published every 10 s so `lp` reports a RECENT worst case
  // rather than a boot spike that never clears — the same per-window discipline the two
  // consoles use, which is what makes the four nodes' `lp` numbers comparable.
  {
    uint32_t dt = millis() - loop_t0;
    if (dt > gLoopWorstRun) gLoopWorstRun = dt;
    static uint32_t windowStart = 0;
    if (millis() - windowStart >= 10000) {
      windowStart = millis();
      gWorstLoopMs = gLoopWorstRun;
      gLoopWorstRun = 0;
    }
  }
}
