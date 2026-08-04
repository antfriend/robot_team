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
// Boot toot plays at 25% of fleet loudness (75% quieter); the backbeat keeps full amp.
static const float STARTUP_TOOT_AMP = 2750.0f;   // 11000 / 4
static void playStartupToot() {
  toneI2S(262.0f, 220, STARTUP_TOOT_AMP);   // C4
  delay(40);
  toneI2S(392.0f, 380, STARTUP_TOOT_AMP);   // G4
}
#endif

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
static const uint32_t PULSE_PART_TONE_MS = 120;  // backbeat length on the amp (blocks; short)
static uint32_t gLedClearMs = 0;
static bool     gBeatFlash = false;
// The part boots SILENT and only plays between CMD_PLAY and CMD_STOP (the T-Deck's g/x, band-
// wide via NODE_BROADCAST). The step clock keeps running while stopped so phase stays locked;
// only the audible/LED hit is muted. Mirrors the K10.
static bool     gPlayEnabled = false;
// V4-B's PART in the hero's-arc song (HeroArc.h, TTN-RFC-0010 §7): the BACKBEAT —
// the G3 "snare" on beats 2 & 4 once the ally joins (scene 1), and the bare lub-dub
// HEARTBEAT that alone carries the ordeal (scene 3). Which scenes play what is
// authored in the score table, not here.
static const score::Part& kPart = heroarc::kBackbeat;

// --- the duet (CMD_DUET) -----------------------------------------------------
// Being invited into a duet overrides this node's PART for as long as it lasts: the
// backbeat's job is to answer the floor, and a duet is somebody asking it to carry a
// melody instead. Not a chart scene (a scene is band-wide and would pull in every powered
// member; see Toot.h) and not persisted — the invitation belongs to the moment the console
// asked. Same shape as both consoles' copy, deliberately: the four should stay comparable.
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
// whom — the relay can lead a duet as readily as harmonise one. The inviter RE-ASSERTS a
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
// evidence (@LAT96 lane). V4-B is the solar node the spec names for this — the scan
// hops channels ~2 s so it's kept rare and the ESP-NOW channel is re-asserted after.
// Default off until flashed + serial-verified.
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

// --- interoception (CMD_GET_INTERO) ------------------------------------------
// What the relay can say about its own body, so the T-Deck's record pane can draw it the
// same way it draws the consoles'. Nothing here is display-shaped — the receiver has a
// different panel and palette, and the thing worth sending across a mesh is the
// measurement, not the pixels.
//
// The two PIN constants are MEASURED on this very board, not inherited: an ADC sweep of
// every ADC1 pin (GPIO1-10) against each candidate divider-enable found GPIO1 reading 827 mV
// with GPIO37 driven HIGH and a flat 0 mV in every other state, repeatably. ⚠ Note the
// polarity — the V3's ADC_Ctrl is documented active-LOW and this board is the opposite way
// round. Driving it LOW is exactly the state that DISCONNECTS the divider, which is why the
// first build of this reported 0.000 V with a known-good pack attached.
// ⚠ BAT_DIVIDER is still inherited and unmetered. 4.9 turns the measured 827 mV into 4.05 V,
// a textbook 1S pack on charge, so it is at worst close — but "plausible" is not "checked",
// so the RAW pin millivolts still print beside the derived voltage on the first sample. That
// matters more here than on the bridge: V4-B is the solar+battery node, so its pack voltage
// is the one number that will eventually mean something operationally.
static const int   PIN_BAT_ADC  = 1;      // measured; matches hardware_specs.md §2
static const int   PIN_ADC_CTRL = 37;     // measured: HIGH connects the divider, LOW opens it
static const float BAT_DIVIDER  = 4.9f;   // V3 divider 390k/100k -> (390+100)/100
static const uint32_t INTERO_PERIOD_MS = 2000;   // these signals move in minutes

// ⚠ 0 mV is a REAL, EXPECTED reading here, not a "not yet sampled" one: with no pack on
// the JST lead the divider has nothing to divide. So the have-we-sampled sentinel is its
// own flag rather than `gBatMv != 0` the way it is on the two consoles — using the
// measurement as its own validity flag made the sampler re-run and re-print the boot line
// on EVERY loop pass, a serial flood that shows up as this node's worst-loop-pass number.
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
  // On the solar node that arrow is the closest thing the fleet has to "the sun is out".
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

// STATUS telemetry for the `monitor` table. No agent cursor, so those fields are 0; report
// the synced state + epoch. The temperature field is no longer 0: it carries the die
// reading. Toot.h calls the field "ambient" and this is not that — but a die reading is a
// real measurement of a real body, and an empty field is not.
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
  // clock is running, and the backbeat is silent in the scenes it has no row for. Reported
  // as the STATE that would sound a note rather than the instant of one, so a 2 s poll
  // cannot fall between two beats and read false. Unlike the consoles there is no
  // `!conductor()` term: this node's voice has never been gated on the baton (see loop()).
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
      // Band-wide play/stop: honor a broadcast (or targeted) PLAY/STOP so one T-Deck press
      // starts/stops the whole fleet. Boots silent. Other ops stay targeted (below).
      if ((toot::cmdOp(t) == toot::CMD_PLAY || toot::cmdOp(t) == toot::CMD_STOP) &&
          (toot::cmdTarget(t) == kNodeId || toot::cmdTarget(t) == NODE_BROADCAST)) {
        gPlayEnabled = (toot::cmdOp(t) == toot::CMD_PLAY);
        if (!gPlayEnabled) setDuet(toot::DUET_OFF, 0, 1);   // stop means stop, duet included
#if USE_PULSE
        // CMD_PLAY arms the story to walk itself: as conductor we auto-advance the early
        // scenes and hold at the grief (ORDEAL) for the returning roamer (see serviceSong).
        if (gPlayEnabled) gPulse.armSong(heroarc::SCENE_ALONE, millis());
        else              gPulse.disarmSong();
#endif
        accepted = true;
        break;
      }
      // Move the band to a scene of the song. The chart belongs to the CONDUCTOR, so
      // only the conductor applies + ACKs this; everyone else ignores it and learns the
      // scene from the next beacon. That is exactly why it is safe to broadcast: at
      // most one node answers, so the operator needn't know who holds the baton.
      if (toot::cmdOp(t) == toot::CMD_SET_SCENE &&
          (toot::cmdTarget(t) == kNodeId || toot::cmdTarget(t) == NODE_BROADCAST)) {
#if USE_PULSE
        if (gPulse.conductor() && t.payload_len >= 7) {
          uint16_t want = toot::get_u16(t.payload + 5);
          gPulse.setScene(want, millis());
          accepted = (gPulse.scene() == want);  // ACK the achieved state (idempotent)
        }
#endif
        break;
      }
      if (toot::cmdTarget(t) == kNodeId) {
        if (toot::cmdOp(t) == toot::CMD_GET_STATUS) {
          uint8_t body[toot::STATUS_PULSE_PAYLOAD_LEN];
          uint8_t slen = buildStatus(body);
          emit(toot::PERCEPT, body, slen, reply, ctx);  // the reply is the answer
        }
        if (toot::cmdOp(t) == toot::CMD_GET_INTERO) {
          // "Show me your body", from the T-Deck's record pane or `companion.py intero`.
          // buildIntero reads nothing (all cached by serviceIntero) and the reply is ONE
          // frame, so unlike a TTDB burst this is safe to answer from the recv callback.
          uint8_t body[toot::INTERO_PERCEPT_PAYLOAD_LEN];
          uint8_t ilen = buildIntero(body);
          emit(toot::PERCEPT, body, ilen, reply, ctx);
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
          uint8_t lane = toot::cmdClearLane(t);   // 0 = every percept lane
          accepted = (lane == TIMESTREAM_LANE)
                     ? lanegen::pruneTimeline(gDb, gStamp, kNodeId, gStreamWallSec)
                     : lanegen::prune(gDb, lane, gStamp, kNodeId, gStreamWallSec);
          if (accepted)
            Serial.printf("[link] percept lane %s cleared (TTDB now %uB, %dr)\n",
                          lane ? String(lane).c_str() : "ALL",
                          (unsigned)gDb.fileSize(), gDb.recordCount());
        } else if (toot::cmdOp(t) == toot::CMD_DUET) {
          // A console asking the relay to sing with it. Flags + a phrase pointer only —
          // no flash, no tone (the note sounds from loop() like every other part).
          accepted = applyDuetCmd(t);
        } else {
          accepted = true;  // ping / set-* (no-op on V4-B) / get-status all ACK
        }
      }
      break;
    case toot::TIME_SYNC: {
      uint32_t sid; uint64_t ems;
      if (toot::parseTimeSync(t, sid, ems)) {
        uint32_t recv_ms = millis();
        if (!gSynced || sid > gLastSyncId) {
          // The laptop supplies the DATE. It does not supply the timeline — the fleet
          // already has one — so this ANCHORS the stream instead of replacing its
          // clock. Latched here, applied by gTs.service() from loop().
          gTs.onTimeSync(ems, recv_ms, t.src_node_id);
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
                           c.beat_period_ms, c.meter_beats, c.flags, &c.scene_id))
        gPulse.onBeacon(c, cond_epoch, millis());
      break;
    }
    case toot::HELLO:
      if (neighborNeedsLock(t.src_node_id, millis())) gPulse.noteNeighbor(millis());
      break;
#endif
    default:
      break;
  }

  // The time-stream anchor rides on HELLO — every node emits one every 2 s and its
  // payload was EMPTY until now, so this is purely additive: a node still on old
  // firmware sends 0 bytes and parseAnchor declines, making it a non-participant
  // rather than a parse error. Outside the USE_PULSE guard on purpose: the band is
  // optional, a shared timeline is not.
  gTs.onHello(t, millis());
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
  if (t.type == toot::CMD && toot::cmdTarget(t) == kNodeId &&
      toot::cmdOp(t) == toot::CMD_CLEAR_PERCEPTS) {
    if (!gClearPending) { gPendingClear = t; gClearPending = true; }  // flash: loop()
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
  // ever matters on solar, pulse it across two loop passes rather than blocking on a settle.
  pinMode(PIN_ADC_CTRL, OUTPUT);
  digitalWrite(PIN_ADC_CTRL, HIGH);

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

  // The time stream starts EMPTY, not with a stream of our own: this node listens for
  // TIMESTREAM_LISTEN_MS first (gTs.service), because joining an older stream is free
  // and forking one costs a merge. Independent of USE_PULSE — the band is optional, a
  // shared timeline is not.
  gTs.begin(kNodeId, &gDb, millis());

#if USE_BLE
  blelink::begin(kNodeId, ROBOT_TEAM_KEY, ROBOT_TEAM_KEY_LEN, onBleObserve);
  Serial.println("BLE near-range tier up (advert + passive scan)");
#endif

  Serial.printf("V4-B relay 0x%08X online (LoRa %s, forward %s, BLE %s)\n", kNodeId,
                USE_LORA ? "on" : "off", USE_RELAY_FORWARD ? "on" : "off",
                USE_BLE ? "on" : "off");
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
      size_t m = gLinkLog.buildRecord(rec, sizeof(rec), lane, gStreamWallSec,
                                      gStamp, millis());
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
      size_t m = gEntityLog.buildRecord(rec, sizeof(rec), lane, gStreamWallSec,
                                      gStamp, millis());
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
  // --- fleet pulse (TTN-RFC-0010): backbeat part — LED + OLED dot on beats 2 & 4 ---
  {
    uint32_t pnow = millis();
    pulse::Chart oc;
    uint64_t oepoch;
    if (gPulse.update(pnow, oc, oepoch)) {     // drift-paced / on-join only, not per beat
      uint8_t body[toot::PULSE_PAYLOAD_LEN];
      uint8_t blen = toot::buildPulse(body, oc.conductor_id, oc.era, oepoch,
                                      oc.downbeat_epoch, oc.beat_period_ms,
                                      oc.meter_beats, oc.flags, oc.scene_id);
      emit(toot::PULSE, body, blen, sendEspNow, nullptr);
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
    // Backbeat part: the scene selects the phrase (snare / heartbeat / no row = SILENT);
    // the step clock runs regardless, so a silent scene stays in phase.
    // A DUET overrides the phrase (and the scene's silence) for as long as it lasts — the
    // pair was asked for by name, and the step clock underneath is the same one.
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
        // Sound the note on the amp. Blocks; beats are >=500ms apart (deferred-tone
        // discipline, safe in loop()). Articulation scales with speed so double time stays
        // staccato instead of slurring into the next slot.
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
          Serial.printf("[part] step %u BACKBEAT (beat %u) era=%lu\n", sip,
                        (sip / 4) % 4 + 1, (unsigned long)gPulse.chart().era);
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
    uint8_t hb[timestream::ANCHOR_LEN];
    size_t hn = gTs.helloPayload(hb, sizeof(hb), millis());
    emit(toot::HELLO, hn ? hb : nullptr, hn, sendEspNow, nullptr);
  }
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
