# TTN-RFC-0009: TTDB Push-Back (Belief Distribution)

**Status:** Proposed
**Depends on:** TTN-RFC-0007 (Reliable Delivery), TTDB-RFC-0007 (Locus Point and
Dream Cycle), TTN-RFC-0008 (Time-Sync — sync_id exactly-once pattern)
**Phase:** PLAN.md Phase 6 (Dream Cycle — propagation half)

## 1. Motivation

TTN-RFC-0008 + the `reconcile` seed close one direction of the Dream Cycle: nodes
author episodic `@LAT99` sync records, the companion *pulls* them and consolidates
them into a semantic master view. The other direction — **the companion re-authors
knowledge and pushes it back to a node** so the fleet shares a consolidated belief —
was unspecified. This RFC defines that push path: a transport for writing an
offset-addressed byte stream into a node's filesystem, with whole-object integrity
and exactly-once adoption.

It is the network mechanism behind TTDB-RFC-0007 §"multi-agent belief propagation":
the companion plays the offline consolidator, the node is a propagation target.

## 2. Toot type

```
TTDB_PUT = 12   // companion -> node: one offset-addressed slice of a belief object
```

Mirrors `TTDB_DATA` (8) but in the reverse direction and with whole-object
metadata so the receiver can verify and commit. A push is a sequence of `TTDB_PUT`
toots, each sent `want_ack` (TTN-RFC-0007 §4); the transport is reliable
stop-and-wait, one outstanding slice at a time.

### 2.1 Payload layout (22-byte header + data, little-endian)

```
off  field            bytes   notes
0    target_node_id   4       only the addressed node writes/ACKs
4    belief_id        4       monotonic; exactly-once adoption gate (NOT dedup)
8    total_len        4       full belief object size in bytes
12   crc32            4       CRC-32 (IEEE/zlib) over the whole belief object
16   offset           4       byte offset this slice writes at
20   len              2       slice length (<= 186)
22   data             len     the slice bytes
```

`MAX_SLICE = MAX_BODY(208) - 22 = 186` data bytes per toot.

`crc32` is the standard CRC-32 used by zlib / IEEE 802.3 (poly `0xEDB88320`, init
`0xFFFFFFFF`, reflected, final XOR `0xFFFFFFFF`) so `companion.py`'s `zlib.crc32`
and the firmware `toot::crc32` agree bit-for-bit. It is carried in **every** slice
(not just the first) so a node that joins mid-stream — or the firmware that
accumulates it incrementally — always has the target value.

## 3. Receiver (node) semantics

A node serves a `TTDB_PUT` only when `target_node_id == own id`. State is a single
in-flight transfer plus a last-adopted marker:

```
gBeliefAdopted, gBeliefId            // committed belief (exactly-once gate)
gPutActive, gPutId, gPutTotal,
gPutCrc, gPutNext, gPutCrcRun        // in-progress transfer
```

Delivery is stop-and-wait in offset order, so the receiver tracks the next
expected offset (`gPutNext`) and is idempotent on retransmits:

1. **Already adopted** (`gBeliefAdopted && belief_id == gBeliefId`): re-ACK
   `ACCEPTED`, do **not** rewrite. Handles a lost final ACK after commit.
2. **offset 0**: (re)start — open the belief file `w` (truncate), write, seed
   `gPutCrcRun = crc32(0, data, len)`, `gPutNext = len`, `gPutActive = true`.
3. **offset == gPutNext** (same `belief_id`): append, advance `gPutNext`, continue
   the running CRC `gPutCrcRun = crc32(gPutCrcRun, data, len)`.
4. **offset < gPutNext** (same `belief_id`): a duplicate already-written slice
   (its ACK was lost) — re-ACK `ACCEPTED`, no rewrite.
5. **otherwise** (gap, or unknown `belief_id` mid-transfer): drop **without** ACK,
   forcing the sender to retransmit.

Cases 1–4 ACK `ACCEPTED`. **Completion** (`gPutNext >= gPutTotal`):

- Compare `gPutCrcRun` to `gPutCrc`.
- **Match** → adopt: set `gBeliefAdopted=true, gBeliefId=belief_id`, and append a
  `BELIEF-ADOPTED` provenance record to the node's *live* TTDB (§4). The slice is
  still ACKed regardless (the bytes were stored).
- **Mismatch** → do not adopt; log the mismatch. (Each slice is HMAC-verified, so a
  mismatch implies object-level corruption / a truncated transfer, which `verify`
  catches as a missing `BELIEF-ADOPTED` record.)

The belief object is written to a **separate file** (`/belief.md`), never the live
`/ttdb.md`, so a push can never destroy a node's self-authored episodic log. The
only mutation of the live TTDB is the append-only `BELIEF-ADOPTED` record.

Like TTN-RFC-0008's `sync_id`, the `belief_id` exactly-once gate is independent of
transport dedup, so it stays correct on the un-deduped USB-CDC / bridge path where a
retransmit is expected.

## 4. Adoption record (live TTDB, `lat 98` lane)

On a CRC-verified commit the node appends, append-only, a new record at
`@LAT98LON<n>` (n = count of existing lat-98 records, unique under
`collision_policy: reject`):

```
@LAT98LON<n> | created:<unix_s> | updated:<unix_s> | relates:adopts@LAT0LON0

**BELIEF-ADOPTED** id:<belief_id> bytes:<total_len> crc:<CRC32 hex8> recv_ms:<millis> applied:interval_ms:<ms>
```

`created`/`updated` are unix seconds from the node's synced clock (0 if unsynced).
This is the node's self-attestation, in its own knowledge base, that it received and
integrity-checked exactly those bytes — the proof the companion verifies. The trailing
`applied:interval_ms:<ms>` is the node's effective sense→reason→act cadence *after* it
acted on the belief's directive (§5.2) — the proof the belief changed behavior, not
just storage.

## 5. Sender (companion) semantics

### 5.1 Re-authoring

`companion.py push`:

1. **Re-author** a belief object (`author_belief`) — here, a TTDB summarising the
   consolidated fleet sync knowledge into a `**BELIEF**` summary, a `**DIRECTIVE**`
   record (§5.2), and one `**BELIEF-SYNC**` record per known sync event.
2. Allocate a monotonic `belief_id` from the master belief log (`next_belief_id`).
3. Slice into ≤186-byte slices and deliver each as a `want_ack TTDB_PUT` via the
   TTN-RFC-0007 reliable sender (retransmit ×N, ×2 backoff), in offset order.
4. **Verify** by pulling the node's live TTDB (in a fresh link session, so a bridge
   relay is reset to a clean state) and matching the `BELIEF-ADOPTED` record for
   `belief_id`: `bytes` and `crc` must equal what was sent, and `applied:interval_ms`
   must equal the directive. Record the push in the master belief log on success.

### 5.2 Behavioral directive — closing the Dream Cycle

A belief is not just stored, it **changes node behavior**. The belief carries one
directive record:

```
@LAT0LON1 | created:<unix_s> | updated:<unix_s> | relates:directed_by@LAT0LON0

**DIRECTIVE** sense_interval_ms:<N>
```

On a CRC-verified commit (§3) the node reads `/belief.md`, parses this directive, and
retunes its sense→reason→act cadence (`Agent32::setInterval`, floored at 100 ms so the
loop/watchdog isn't starved), then records the *effective* cadence in the adoption
record (§4). This is the propagation half of the Dream Cycle made concrete: consolidated
fleet knowledge becomes a distributed policy the node acts on (PLAN.md Phase 6).
`sense_interval_ms` is the first such directive; the record is extensible to further
behavioral parameters.

## 6. Test plan

- **Codec (native + Python):** `TTDB_PUT` payload pack/unpack is wire-exact;
  `toot::crc32` matches `zlib.crc32` on shared vectors (the cross-stack KAT).
- **Slicing (Python):** an N-byte object splits into `ceil(N/186)` offset-addressed
  slices whose concatenation is byte-exact.
- **On-device (K10 over USB-CDC):** push a re-authored belief; confirm every slice
  ACKs, `/belief.md` holds the exact bytes, and the live TTDB gains a
  `BELIEF-ADOPTED` record with matching `bytes`/`crc`; re-push the same `belief_id`
  → re-ACKed, no duplicate record (exactly-once).

## 7. Future work

- Serve the stored belief object back (a `TTDB_REQ` mode addressing `/belief.md`) so
  the companion can diff the bytes, not only the CRC attestation.
- Node-to-node belief gossip (BELIEF toot, type 3) once a second percept node exists.

**Done since draft:** bridge-relayed push to an over-air node (the K10 defers a radio
`TTDB_PUT`'s flash write to `loop()`, like `TTDB_REQ`); and the behavioral directive
(§5.2) — a pushed belief retunes the K10's loop cadence, verified live (1000→300→700 ms)
on-device through the V4-A bridge, closing the Dream Cycle (PLAN.md Phase 6).
