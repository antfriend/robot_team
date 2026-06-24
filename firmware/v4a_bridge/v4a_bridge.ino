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
#include <RobotTeamConfig.h>

#define USE_LORA 0  // Phase 4: set 1 and wire RadioLib SX1262 (GPIO 8/9/10/11).

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
  return (uint8_t)toot::STATUS_PAYLOAD_LEN;
}

static ESPNOW_RECV_CB(onEspNowRecv, data, len) {
  if (len <= 0) return;
  toot::Toot t;
  if (!toot::decode(data, (size_t)len, ROBOT_TEAM_KEY, ROBOT_TEAM_KEY_LEN, t))
    return;
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
}

// Render the live bridge status onto the OLED (called from loop(), never the cb).
static void renderOled() {
  char l[24];
  gOled.clearBuffer();
  gOled.setFont(u8g2_font_6x10_tf);              // 6x10 -> 21 cols x 6 rows
  gOled.drawStr(0, 9, "V4-A BRIDGE");
  gOled.drawStr(78, 9, USE_LORA ? "LoRa+" : "LoRa-");

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

  Serial.printf("V4-A bridge 0x%08X online (LoRa %s)\n", kNodeId,
                USE_LORA ? "on" : "off");
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
        if (toot::cmdOp(t) == toot::CMD_GET_STATUS) {
          uint8_t body[toot::STATUS_PAYLOAD_LEN];
          uint8_t slen = buildStatus(body);
          emitSerial(toot::PERCEPT, body, slen);
        }
        if (t.flags & toot::FLAG_WANT_ACK) emitAckSerial(t, toot::ACK_ACCEPTED);
      } else {
        injectToMesh(buf, n);
        gInjected++;
      }
    }
  }

  // Refresh the OLED on change, plus a ~1s heartbeat to tick the uptime.
  static uint32_t lastRender = 0;
  if (gOledDirty || millis() - lastRender >= 1000) {
    lastRender = millis();
    gOledDirty = false;
    renderOled();
  }
}
