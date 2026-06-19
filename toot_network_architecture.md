# Toot-Toot Network — Architecture & Transport Protocol

Agent network architecture for the Locus framework: a swarm of ESP32 agents
(perception nodes + LoRa mesh nodes) coordinated by a laptop orchestrator.

Design principle: **transport is layered and range-adaptive.** Nodes prefer the
cheapest, lowest-latency link available and fall back to longer-range transports
as distance grows. ESP-NOW is the default whenever peers are in range; LoRa is
the long-haul backbone; the orchestrator bridges into the mesh through a tethered
LoRa node.

```
 Latency / cost  →  low ............................. high
 Range           →  short ............................ long
 ┌────────────┬───────────────┬──────────────┬─────────────────┐
 │  ESP-NOW   │   Wi-Fi/UDP   │     BLE      │      LoRa       │
 │ (default,  │ (orchestrator │ (config /    │ (off-grid spine,│
 │  in-range) │  LAN/AP)      │  pairing)    │  V4 nodes only) │
 └────────────┴───────────────┴──────────────┴─────────────────┘
```

---

## 1. Node roles

### Percept node — UNIHIKER K10
- Camera, 2× mic, accelerometer, temp/humidity/light, 240×320 color screen.
- Captures `@PERCEPT:before` / `@PERCEPT:after` pairs; the edge between them is
  the primary datum.
- **No LoRa.** Reaches the network over ESP-NOW (default) or Wi-Fi.
- To send anything across the long-range mesh, it hands off to a nearby V4.

### Mesh nodes — 3× Heltec WiFi LoRa 32 V4 (the spine)

All three share the base hardware — SX1262 LoRa (28 dBm), WiFi, BLE, 128×64 mono
OLED — but each occupies a fixed position along the spine and carries a distinct
role, config, and feature loadout. The spine is linear: **V4-A ── V4-B ── V4-C**,
with V4-B as the midpoint relay so the two ends never need to hear each other
directly.

```
   Laptop
     │ USB-CDC / WiFi
 ┌───▼────┐   LoRa    ┌────────┐   LoRa   ┌────────┐
 │ V4-A   │◄─────────►│  V4-B  │◄────────►│  V4-C  │
 │ BRIDGE │           │ RELAY  │          │ EDGE   │
 │ (head) │           │ (mid)  │          │ (tail) │
 └───┬────┘           └───┬────┘          └───┬────┘
   ESP-NOW             ESP-NOW             ESP-NOW
   cluster A           cluster B           cluster C
  (K10s + orch)       (K10s)             (K10s, off-grid)
```

#### V4-A — **Bridge / head node**
- **Position:** spine head, co-located with the orchestrator.
- **Role:** the only path between the laptop and the LoRa mesh. Ingests CMD toots
  from the orchestrator and injects them onto LoRa; collects telemetry/BELIEF
  toots off LoRa and hands them up to the laptop.
- **Link to orchestrator:** USB-CDC serial (deterministic) during development;
  WiFi-join once stable.
- **Power:** mains/USB — always powered, never sleeps. It's the fixed reference.
- **Config notes:** part of the small **encrypted-peer trusted core** (holds the
  network HMAC key + ESP-NOW LMK). Runs at the orchestrator AP's Wi-Fi channel and
  is the channel authority that HELLO beacons propagate outward from.
- **Antenna:** can stay on the built-in FPC antenna (short hop to V4-B, indoors).

#### V4-B — **Relay / midpoint node**
- **Position:** spine middle, sited for line-of-sight to *both* V4-A and V4-C.
- **Role:** pure store-and-forward LoRa relay. Decrements `ttl`, dedups on
  `(src_node_id, toot_seq)`, forwards. It is the reason A and C can be far apart.
- **Power:** solar + battery via the V4's SH1.25-2P solar input — this is the node
  most likely to be mounted high/outdoors away from mains, so it exploits the V4's
  solar charging and <20 µA idle. Duty-cycles its ESP-NOW wake window between
  forwards.
- **Config notes:** also trusted core (needs the key to verify+re-sign relayed
  toots). Minimal local ESP-NOW cluster — its job is the long hops, not endpoints.
- **Antenna:** **external antenna via the IPEX/U.FL connector** (remove onboard
  inductor ①, bridge ② with 0 Ω) for maximum range on the two longest links.
- **Display:** OLED shows live link health (RSSI to A and C, forward count) since
  this node is the one you'll physically inspect when the mesh degrades.

#### V4-C — **Edge / tail node**
- **Position:** spine tail, the far off-grid end.
- **Role:** gateway for the most remote ESP-NOW cluster — the K10 percept nodes
  that are out of range of everything except V4-C. Aggregates and summarizes their
  PERCEPT toots before sending across LoRa (airtime is scarcest here).
- **Optional feature:** populate the V4's **SH1.25-8P GNSS connector** with a GPS
  module so the tail node can stamp real `@LATxLONy` coordinates onto field
  percepts — useful precisely where there's no other location reference.
- **Power:** battery + solar, expected to be fully off-grid.
- **Config notes:** may run **unencrypted ESP-NOW broadcast** to its local K10
  swarm (encrypted-peer budget is tight; the HMAC payload signature still protects
  integrity) while keeping the LoRa link to V4-B authenticated.
- **Antenna:** external IPEX antenna for the long haul back to V4-B.

> Revision check: confirm each board's PA variant and set the matching Arduino
> flag (`USE_GC1109_PA` for V4.2, `USE_KCT8103L_PA` for V4.3) per unit — the three
> boards need not be the same revision.

#### Spine at a glance

| | V4-A — Bridge | V4-B — Relay | V4-C — Edge |
|---|---|---|---|
| Spine position | head | midpoint | tail |
| Primary job | laptop ↔ mesh gateway | store-and-forward long hops | remote cluster gateway |
| Orchestrator link | USB-CDC / WiFi | none | none |
| Power | mains/USB, always on | solar + battery | solar + battery, off-grid |
| Antenna | built-in FPC | external IPEX | external IPEX |
| ESP-NOW cluster | cluster A (+ orch) | minimal | cluster C (remote K10s) |
| Encryption | trusted core (LMK) | trusted core (LMK) | unencrypted bcast local, signed LoRa |
| Special feature | channel authority | OLED link-health display | GNSS for `@LATxLONy` stamping |
| Sleep | never | duty-cycled wake window | duty-cycled |

### Orchestrator — laptop
- No radio of its own. Speaks to the swarm through:
  - **USB-CDC serial** → bridge V4 (deterministic command/telemetry pipe), and/or
  - **Wi-Fi** (AP or shared LAN) → any K10/V4 directly.
- Runs the Locus reasoning loop, Dream Cycle consolidation, TTDB master copy.

---

## 2. Transport selection (range-adaptive default)

Every node runs the same decision each time it needs to emit a toot:

1. **Is the destination an ESP-NOW peer currently in range?** → send via ESP-NOW.
   This is the **default for prototype development and for any in-range link.**
2. **Is the orchestrator's Wi-Fi reachable and the payload large / bulk?**
   (image frame, batched percepts) → send via Wi-Fi/UDP to orchestrator.
3. **Destination out of ESP-NOW range and this node has LoRa?** → send via LoRa.
4. **Out of range and no LoRa (K10)?** → hand the toot to the nearest in-range V4
   over ESP-NOW; the V4 forwards over LoRa.

For initial prototyping, force step 1 everywhere: bring all boards up on the same
Wi-Fi channel and exchange toots by ESP-NOW broadcast. No router, no pairing,
no orchestrator dependency — fastest path to a working swarm.

---

## 3. ESP-NOW protocol layer (the in-range default)

ESP-NOW is connectionless, infrastructure-free 2.4 GHz peer-to-peer using the
Wi-Fi radio. It is the default toot transport whenever nodes are within range.

### Hard constraints (drive the framing)
| Constraint | Value | Consequence for toot design |
|---|---|---|
| Max payload per packet | **250 bytes** | A toot must fit in 250 B or be chunked + reassembled. |
| Total peer-list size | 20 | Plan clusters ≤ ~20 nodes per radio neighborhood. |
| Encrypted peers | default 7, max 17 (≤10 STA / ≤6 STA+AP practically) | Reserve encryption for a small trusted core; broadcast the rest. |
| Unencrypted peers | effectively unlimited senders to one RX | Fine for a star of many percept nodes → one gateway. |
| Channel | all peers must share the Wi-Fi channel; ch 0 = "current" | **Channel coordination is mandatory** (see below). |
| Throughput | ~200 Kbps open air, up to ~550 Kbps shielded (1 Mbps PHY default) | Don't stream raw images over ESP-NOW; summarize or use Wi-Fi. |
| Delivery feedback | per-packet TX callback (success/fail) | Use it for the ACK/retry layer. |
| Auth on receive | **none enforced** — RX accepts unencrypted + spoofable MACs | Add an HMAC + nonce in the payload yourself. |
| Deep sleep | supported on S3 in station mode (wake window/interval) | Percept nodes can sleep between captures and still RX. |

### Toot frame (fits in the 250-byte ESP-NOW payload)

A single ESP-NOW packet carries one **toot** (or one chunk of a larger toot):

```
 offset  field            bytes   notes
 ------  ---------------  ------   -----------------------------------------
   0     magic            2        0x54 0x54  ("TT")
   2     version          1        protocol version
   3     type             1        PERCEPT / BELIEF / CMD / ACK / RELAY / HELLO
   4     src_node_id      4        stable logical id (not just MAC)
   8     toot_seq         4        monotonic per-source; (src,seq) = dedup key
  12     chunk_idx        1        0-based
  13     chunk_total      1        1 if unchunked
  14     locus_addr      16        @LATxLONy coordinate address (packed)
  30     ttl              1        hop budget for relay
  31     flags            1        bit0 want_ack, bit1 encrypted_payload, …
  32     payload_len      1        ≤ 208
  33     payload         ≤208      toot body (TTDB markdown fragment / fields)
  ...    hmac             8        truncated HMAC-SHA256 over header+payload
```

Budget: 33 B header + 8 B HMAC = 41 B overhead → **≤ 208 B of toot body per packet.**
Toots larger than that are split across chunks `chunk_idx / chunk_total` and
reassembled on `(src_node_id, toot_seq)`.

### Message types
- **HELLO** — periodic broadcast announcing node id, role, locus addr, channel,
  and whether it carries LoRa. Builds the in-range neighbor table. Default beacon.
- **PERCEPT** — a `@PERCEPT:before`/`after` fragment or edge datum from a K10.
- **BELIEF** — a `@BELIEF:` node produced by Dream-Cycle consolidation, gossiped
  to neighbors.
- **CMD** — orchestrator → node directive (relayed in via the bridge).
- **ACK** — confirms `(src,seq[,chunk])`; absence triggers retry.
- **RELAY** — a toot whose destination is out of local range; a LoRa node picks
  it up and forwards. `ttl` decrements per hop; drop at 0.

### Reliability
ESP-NOW gives a TX-success callback but no end-to-end guarantee. Layer on:
- **Dedup** on `(src_node_id, toot_seq)` — every node keeps a small seen-set.
- **ACK + retry** for `want_ack` toots: retransmit with backoff up to N times.
- **TTL** to kill relay loops.
- Idempotent toots: re-delivery is harmless because dedup drops repeats.

### Security
Because ESP-NOW enforces no auth on receive and MACs spoof trivially:
- Append a **truncated HMAC-SHA256** (shared network key) over header+payload;
  drop packets that fail verification.
- Include `toot_seq` as a **nonce** so replayed packets are dedup-dropped.
- Reserve ESP-NOW's native peer encryption for the small trusted core
  (orchestrator bridge + key relays), since the encrypted-peer count is limited.

### Channel coordination (the one rule that bites you)
All ESP-NOW peers must be on the **same Wi-Fi channel**, and that channel must
match any AP a node is also joined to. Decision:
- **Prototype:** pin every board to a fixed channel (e.g. ch 1), no AP. Simplest.
- **With orchestrator AP:** every node's ESP-NOW channel = the orchestrator AP's
  channel. If a node associates to the AP, ESP-NOW follows that channel
  automatically; nodes that don't associate must be set to it explicitly.
- HELLO beacons advertise the channel so a newly-woken node can converge.

---

## 4. LoRa backbone (long-haul)

When peers are out of ESP-NOW range, V4 nodes carry toots over SX1262 LoRa.
Same toot frame, but:
- LoRa airtime is precious — only **BELIEF**, **CMD**, and summarized **PERCEPT**
  toots cross LoRa, never raw chunked media.
- The 250 B ESP-NOW limit is comfortably within a multi-packet LoRa transfer, but
  prefer toots that fit a single LoRa frame to minimize airtime and collisions.
- Meshtastic / MeshCore firmware is an option if you want a proven LoRa transport
  beneath the toot protocol rather than rolling your own routing.

---

## 5. Orchestrator integration

```
            ┌──────────────── Laptop orchestrator ────────────────┐
            │  Locus loop · Dream Cycle · TTDB master · planner    │
            └──────┬───────────────────────────────┬──────────────┘
              USB-CDC serial                    Wi-Fi (AP / LAN)
                   │                                 │
            ┌──────▼──────┐                  ┌────────▼────────┐
            │ V4-A BRIDGE │  ESP-NOW (ch X)  │  K10 percept    │
            │ (head, GW)  │◄────────────────►│  nodes (clus A) │
            └──────┬──────┘                  └─────────────────┘
                   │ LoRa 863–928 MHz
            ┌──────▼──────┐  ESP-NOW   ┌─────────────────┐
            │ V4-B RELAY  │◄──────────►│ K10s (cluster B)│
            │ (mid, solar,│            └─────────────────┘
            │  ext ant.)  │
            └──────┬──────┘
                   │ LoRa (longest haul)
            ┌──────▼──────┐  ESP-NOW   ┌─────────────────────────┐
            │ V4-C EDGE   │◄──────────►│ K10s (cluster C,        │
            │ (tail, GNSS,│            │ off-grid percept swarm) │
            │  off-grid)  │            └─────────────────────────┘
            └─────────────┘
```

- **V4-A (head)** is the only path between the laptop and the LoRa mesh. Tether by
  USB for a deterministic pipe during development; move to WiFi-join once stable.
- **V4-B (mid)** exists so the head and tail never need to hear each other — it
  store-and-forwards over the two longest LoRa hops, running on solar with an
  external antenna.
- **V4-C (tail)** gateways the most remote ESP-NOW cluster, summarizes its percepts
  before spending LoRa airtime, and (optionally) GPS-stamps `@LATxLONy` addresses.
- Within each LoRa node's neighborhood, K10s form an **ESP-NOW cluster** (the
  default in-range transport). Inter-cluster traffic rides the A–B–C LoRa spine.
- The orchestrator's TTDB is the master; nodes gossip BELIEF/PERCEPT toots that
  the orchestrator reconciles during the Dream Cycle.

---

## 6. Prototype bring-up order

1. **Two K10s, ESP-NOW broadcast, fixed channel.** Exchange HELLO + PERCEPT
   toots. Validate framing, dedup, HMAC. No orchestrator, no LoRa.
2. **Add ACK/retry + chunking.** Send a toot larger than 208 B; confirm reassembly.
3. **Add V4-C (edge) to an ESP-NOW cluster.** Confirm a K10 → V4-C handoff
   (RELAY type) and percept summarization before LoRa.
4. **Bring up V4-B (relay) + V4-C over LoRa.** Forward a RELAY toot between two
   ESP-NOW clusters that can't hear each other; confirm `ttl` decrement and dedup
   at the midpoint.
5. **Attach the orchestrator** to V4-A (bridge) over USB-CDC; inject CMD toots,
   collect telemetry across the full A→B→C spine. Reconcile into TTDB.
6. **Switch ESP-NOW channel to the orchestrator AP channel** and confirm
   convergence outward from V4-A via HELLO beacons.
7. **Field the spine:** V4-B on solar + external antenna at the midpoint, V4-C
   off-grid with GNSS at the tail; verify end-to-end toot delivery laptop ↔ cluster C.

---

## 7. Defaults summary

- **In-range transport: ESP-NOW, always, by default.** Used for all prototype
  development and for any link where peers can hear each other.
- **Out-of-range transport:** LoRa via V4 nodes (RELAY).
- **Bulk / media:** Wi-Fi/UDP to orchestrator, never ESP-NOW or LoRa.
- **Toot ≤ 208 B body** per ESP-NOW packet; chunk if larger.
- **Every toot is HMAC-signed and dedup-keyed** on `(src_node_id, toot_seq)`.
- **All ESP-NOW peers share one channel**, advertised in HELLO beacons.
