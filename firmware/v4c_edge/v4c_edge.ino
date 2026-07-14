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
  Serial.printf("V4-C edge 0x%08X online (GNSS %s)\n", kNodeId,
                USE_GNSS ? "on" : "off");
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
}
