// v4c_edge.ino — Heltec WiFi LoRa 32 V4, EDGE / tail node (A32 agent).
//
// Role: gateway for the most remote ESP-NOW cluster
// (toot_network_architecture.md). Aggregates/summarizes the local K10 percepts
// before spending LoRa airtime; optional GNSS stamps real @LATxLONy. Serves its
// own TTDB to the companion via TtdbShare.
//
// LoRa is gated behind USE_LORA. With it off, this acts as a local ESP-NOW
// cluster gateway and TTDB-share responder.
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
#include <Pulse.h>    // band tempo + pulse-clock election (TTN-RFC-0010)
#include <Score.h>
#include <RobotTeamConfig.h>

// --- I2S speaker (MAX98357A) — the LoRa spine's voice -----------------------
// Adafruit MAX98357A I2S 3W amp (adafru.it/3006). Wiring per max98357a-v4-wiring.html /
// hardware_specs.md §2: VIN->3V3, GND->GND, LRC->GPIO5, BCLK->GPIO7, DIN->GPIO6, GAIN &
// SD float. Same driver as the T-Deck console: no analog/PWM path, so a tone is
// synthesized as 16-bit I2S samples. toneI2S blocks ~ms, so it runs from setup()/loop()
// only — never a callback. V4-C has no Pulse membership yet, so for now the amp only
// sounds the boot toot (giving the tail node a verified voice); joining the band is a
// separate change (add the Pulse engine + a part, like V4-A/V4-B).
#define USE_SPEAKER 1
#if USE_SPEAKER
#include <ESP_I2S.h>
static I2SClass gI2S;
static const uint32_t I2S_RATE = 16000;
static const int PIN_I2S_BCLK = 7;   // MAX98357A BCLK
static const int PIN_I2S_WS   = 5;   // word select / LRC
static const int PIN_I2S_DOUT = 6;   // data to amp (DIN)

// Synthesize a `ms`-long sine at `freq` as 16-bit stereo samples (L=R; the amp is mono
// but takes stereo frames). Blocks ~ms — call from setup()/loop() only.
static void toneI2S(float freq, uint32_t ms) {
  const int N = 256;
  int16_t buf[N * 2];
  uint32_t total = (uint32_t)((uint64_t)I2S_RATE * ms / 1000);
  float phase = 0.0f, inc = 2.0f * (float)M_PI * freq / (float)I2S_RATE;
  uint32_t done = 0;
  while (done < total) {
    uint32_t n = total - done; if (n > (uint32_t)N) n = N;
    for (uint32_t i = 0; i < n; ++i) {
      int16_t s = (int16_t)(9000.0f * sinf(phase));
      phase += inc; if (phase > 2.0f * (float)M_PI) phase -= 2.0f * (float)M_PI;
      buf[2 * i] = s; buf[2 * i + 1] = s;
    }
    gI2S.write((uint8_t*)buf, n * 2 * sizeof(int16_t));
    done += n;
  }
}

// The Toot-Toot signature on boot — two rising toots (G3 then C4), mirroring the K10.
static void playStartupToot() {
  toneI2S(196.0f, 220);   // G3
  delay(40);
  toneI2S(262.0f, 380);   // C4
}
#endif

#define USE_LORA 0  // Phase 4: long haul back to V4-B.
#define USE_GNSS 0  // Optional: SH1.25-8P GPS for @LATxLONy stamping.

// --- fleet pulse (TTN-RFC-0010): V4-C completes the rhythm section --------------
// The edge node joins the band as the OFFBEAT HI-HAT: a C5 tick on the "&" of each beat
// (steps 2/6/10/14 of the 16-step bar), under V4-A's kick (every beat) and V4-B's snare
// (beats 2 & 4). The shared Pulse engine owns the time-base + election (lowest id conducts,
// so V4-C = 0x12 follows V4-A/V4-B); this sketch supplies transport (PULSE codec) + the amp.
#define USE_PULSE 1
#if USE_PULSE
static pulse::Engine gPulse;
static const int      kLedPin = 35;             // Heltec V4 onboard LED (fallback visual)
static const uint32_t PULSE_LED_MS = 110;
static const uint32_t PULSE_PART_TONE_MS = 60;  // hi-hat tick on the amp (blocks; very short)
static uint32_t gLedClearMs = 0;
static uint32_t gHelloAt = 0;                    // periodic HELLO so the conductor fast-locks us
// V4-C's PART: the offbeat hi-hat — a C5 tick on the "&" of each beat. Re-voicing is a
// table edit (Score.h).
static const score::Note kPartNotes[] = {
  {2, score::C5, 1}, {6, score::C5, 1}, {10, score::C5, 1}, {14, score::C5, 1},
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
#endif

static const uint32_t kNodeId = NODE_V4C_EDGE;
static const char* kTtdbPath = "/ttdb.md";
static const uint8_t kBroadcast[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
static uint8_t gLocus[toot::LOCUS_LEN] = {0};

Ttdb gDb;
TtdbShare* gShare = nullptr;
toot::DedupSet gDedup(128);
TootSerialLink gSerial(Serial);

static bool sendEspNow(const uint8_t* frame, size_t len, void*) {
  return esp_now_send(kBroadcast, frame, len) == ESP_OK;
}

static uint32_t gSeq = 1;

// Emit a fresh toot into the mesh over ESP-NOW (PULSE beacons, HELLO, STATUS PERCEPT).
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

#if USE_PULSE
// STATUS telemetry for `companion.py band` / `monitor`. V4-C has no time-sync or sensors, so
// those fields are 0; the PULSE tail (TTN-RFC-0010 §8) carries the band phase the verifier
// measures — read from the pulse clock, so it works even though the node isn't wall-synced.
static uint8_t buildStatus(uint8_t* p) {
  toot::put_u16(p + 0, 0);
  toot::put_u16(p + 2, 0);
  toot::put_u16(p + 4, 0);
  p[6] = 0;                                  // not time-synced (no TIME_SYNC path on the edge)
  toot::put_u64(p + 7, 0);
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
}
#endif

static ESPNOW_RECV_CB(onEspNowRecv, data, len) {
  if (len <= 0) return;
  toot::Toot t;
  if (!toot::decode(data, (size_t)len, ROBOT_TEAM_KEY, ROBOT_TEAM_KEY_LEN, t))
    return;
  if (gDedup.seen(t.src_node_id, t.toot_seq)) return;

  if (t.type == toot::TTDB_REQ) {
    if (gShare && TtdbShare::requestTarget(t) == kNodeId)
      gShare->handleRequest(t, sendEspNow, nullptr);
  } else if (t.type == toot::PERCEPT) {
    // Aggregate/summarize cluster-C percepts here before forwarding over LoRa
    // (airtime is scarcest at the tail). Summarization is a Phase 3 task.
  }
#if USE_PULSE
  else if (t.type == toot::PULSE) {
    // Band time-base beacon (TTN-RFC-0010): adoption is cheap (no flash), so it runs here
    // where millis() is the accurate receipt time; the beat renders from loop().
    pulse::Chart c;
    uint64_t cond_epoch;
    if (toot::parsePulse(t, c.conductor_id, c.era, cond_epoch, c.downbeat_epoch,
                         c.beat_period_ms, c.meter_beats, c.flags))
      gPulse.onBeacon(c, cond_epoch, millis());
  } else if (t.type == toot::HELLO) {
    if (neighborIsNew(t.src_node_id)) gPulse.noteNeighbor(millis());
  } else if (t.type == toot::CMD && toot::cmdTarget(t) == kNodeId &&
             toot::cmdOp(t) == toot::CMD_GET_STATUS) {
    // Answer the band/monitor probe with a STATUS PERCEPT — a single frame (cheap, no flash;
    // the V4-A bridge forwards PERCEPT up to the laptop).
    uint8_t body[toot::STATUS_PULSE_PAYLOAD_LEN];
    uint8_t slen = buildStatus(body);
    emitMesh(toot::PERCEPT, body, slen);
  }
#endif
}

void setup() {
  Serial.begin(115200);
  delay(200);

#if USE_SPEAKER
  // Audio first: bring up I2S and sound the boot "toot toot". VIN on 3V3 so the amp works
  // on USB or battery; GAIN & SD float. No Pulse membership yet, so this is its only sound.
  gI2S.setPins(PIN_I2S_BCLK, PIN_I2S_WS, PIN_I2S_DOUT);
  if (gI2S.begin(I2S_MODE_STD, I2S_RATE, I2S_DATA_BIT_WIDTH_16BIT, I2S_SLOT_MODE_STEREO))
    playStartupToot();
  else
    Serial.println("I2S begin failed");
#endif

  if (!LittleFS.begin(true) || !gDb.begin(LittleFS, kTtdbPath))
    Serial.println("FATAL: TTDB load failed");
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
  pinMode(kLedPin, OUTPUT);
  digitalWrite(kLedPin, LOW);
  gPulse.begin(kNodeId, millis());   // follows V4-A/V4-B (higher id); plays the hi-hat
#endif

  Serial.printf("V4-C edge 0x%08X online (GNSS %s, pulse %s)\n", kNodeId,
                USE_GNSS ? "on" : "off", USE_PULSE ? "on" : "off");
}

void loop() {
  uint8_t buf[toot::MAX_FRAME];
  size_t n = 0;
  if (gSerial.poll(buf, sizeof(buf), n)) {
    toot::Toot t;
    if (toot::decode(buf, n, ROBOT_TEAM_KEY, ROBOT_TEAM_KEY_LEN, t) &&
        t.type == toot::TTDB_REQ && gShare &&
        TtdbShare::requestTarget(t) == kNodeId) {
      gShare->handleRequest(t, [](const uint8_t* f, size_t l, void*) {
        gSerial.writeFrame(f, l);
        return true;
      }, nullptr);
    }
  }

#if USE_PULSE
  // --- fleet pulse (TTN-RFC-0010): offbeat hi-hat — tick on the "&" of each beat --------
  {
    uint32_t pnow = millis();
    // Announce ourselves so the conductor fast-locks us (cheap; ~every 2 s).
    if (pnow - gHelloAt >= 2000) {
      gHelloAt = pnow;
      emitMesh(toot::HELLO, nullptr, 0);
    }
    // Emit a chart beacon only when due (drift-paced) or to fast-lock a newcomer — not per beat.
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
    // Hi-hat part: strike the tick on the amp + flash the LED on each struck offbeat step.
    uint16_t sip;
    uint32_t sc;
    const score::Note* nt = nullptr;
    if (gPulse.stepTick(pnow, kPart.steps, sip, sc) && (nt = score::noteAt(kPart, sip))) {
      digitalWrite(kLedPin, HIGH);
      gLedClearMs = pnow + PULSE_LED_MS;
#if USE_SPEAKER
      if (nt->freq != score::REST) toneI2S((float)nt->freq, PULSE_PART_TONE_MS);
#endif
      Serial.printf("[part] step %u offbeat era=%lu\n", sip,
                    (unsigned long)gPulse.chart().era);
    }
    if (gLedClearMs && (int32_t)(pnow - gLedClearMs) >= 0) {
      gLedClearMs = 0;
      digitalWrite(kLedPin, LOW);
    }
  }
#endif
}
