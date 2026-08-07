# TTDB-RFC-0010: Stigmergic Fields, Lane Discipline, and Stable Record Identity

**Version:** 0.1
**Status:** Draft — **nothing in this RFC is implemented.** The lane register (§3) is a
classification of what already exists and is normative on adoption; §§4–6 describe a
mechanism no node has run.
**RFC Number:** 0010
**Project:** toot-toot-engineering
**Component:** Toot-Toot Database (TTDB)
**Depends on:** TTDB-RFC-0001 (File Format), TTDB-RFC-0003 (Typed Edges),
TTDB-RFC-0004 (Event ID and Collision), TTDB-RFC-0005 (TBEW)
**Relates to:** TTN-RFC-0011 (Semantic Positioning), TTDB-RFC-0007 (Dream Cycle)
**Companion design document:** `stigmergy.md` (the exploratory half; this is the
normative half — the same pairing `ttn-semantic-positioning.md` has with TTN-RFC-0011)
**Author:** antfriend
**Created:** 2026-08-07

This RFC defines two memory disciplines for a TTDB — **append-only evidence** and
**decaying fields** — requires every lane to declare which one it is, and specifies the
record identity that makes reclamation safe.

---

## 1. Motivation

A TTDB lane today is implicitly *append-only evidence with a cap*: records accumulate,
the lane fills, the node stops perceiving, and an operator empties the whole lane. The
emptying is honest — TTDB-RFC-0004 §4 forbids reusing an id for a different record, so a
boundary record is written to say the ordinals were re-pointed — but it is **bounded**: on
the reference fleet the boundary lane itself reached 28 of 32 on 2026-08-07, with no prune
path of its own. At that cap the node can no longer clear its percept lanes at all.

Stigmergy (Grassé 1959) supplies the alternative discipline. A trace that persists in a
shared medium, is **reinforced** when re-observed and **decays** when not, needs no
operator and no boundary: the space of a trace nobody is reinforcing returns by itself.
Decay is not housekeeping — it is the computation, because it is what turns an
accumulating log into a gradient a reader can evaluate locally.

Both disciplines are legitimate. Mixing them silently is not: a decaying medium **rewrites
history by design**, which is the one thing this corpus's provenance machinery exists to
prevent. Hence the requirement that every lane declare its class.

### 1.1 Why this is corpus-wide and not a per-node feature

A record does not stay on the node that wrote it. It is pulled by `TTDB_REQ`/`TTDB_DATA`,
pushed as a belief by `TTDB_PUT` (TTN-RFC-0009), consolidated into the laptop's master
copy, and re-read months later by a parser that has no idea which sketch emitted it.

So the class of a record MUST be determinable **from the file**, by a reader that knows
only this RFC. A discipline that lives in one sketch's comments is not a discipline; it is
a habit, and the reader who has to guess will guess that a faded trace is an absent one.

---

## 2. Record classes (normative)

Every record belongs to exactly one class.

**EVIDENCE** — an observation. Append-only. MUST NOT be reclaimed in place. MAY be the
target of any edge. MAY be pruned wholesale, and such a prune MUST leave a PROVENANCE
boundary (§7.4).

**FIELD** — a trace. MAY be reclaimed in place under §5. MUST NOT be the target of a
`derived_from`-class edge (§6.2). MUST NOT be the source of a measured constant (§6.1).

**PROVENANCE** — an account of the store itself: what it once held, which timeline it was
on, what a boundary replaced. Append-only, and MUST NOT be reclaimed under §5 by any
mechanism, including its own.

> **Fail-safe rule.** A reader that cannot determine a record's class MUST treat it as
> EVIDENCE. Guessing FIELD would license discarding an observation; guessing EVIDENCE only
> licenses keeping a trace too long.

Class is declared per lane in `mmpdb` (§7.1), not per record: a lane whose records disagree
about their own mutability cannot be reasoned about at all.

---

## 3. The lane register (normative on adoption)

The reference fleet's complete lane allocation, classified. `cap` is the firmware constant
that bounds the lane today; `prune` is the operation that can empty it.

| Lane | Content | Class | Cap | Prune path |
|---|---|---|---|---|
| `lat < 90` | Node/place records: identity, `**POSITION**` beliefs, the globe | EVIDENCE | — | none (revised by Dream Cycle, never dropped) |
| `@LAT90` | Timeline changes: `STREAM-ORIGIN`/`ADOPTED`/`RECONCILED`/`ANCHORED`, `REMAP` | **PROVENANCE** | 16 | `--lane 90` (`pruneTimeline`) |
| `@LAT91` | `LINK-STABLE` beliefs, one per `(peer, proto)`, with `[ew]` | EVIDENCE | — | none |
| `@LAT92` | `OUTCOME` tallies — the testimony `@LAT91` is folded from | EVIDENCE | 24 | `--lane 92` (`pruneOutcomes`) |
| `@LAT93` | `TRANSITION` pairs (`before`/`after` motion halves) | EVIDENCE | — | none |
| `@LAT94` | Acoustic windows + loudest-transient timestamps | EVIDENCE | 48 | `--lane 94`/`0` |
| `@LAT95` | Motion windows, change-triggered with run-length | EVIDENCE | 48 | `--lane 95`/`0` |
| `@LAT96` | Entity (WiFi BSSID) windows — the Jaccard baseline | EVIDENCE | 48 | `--lane 96`/`0` |
| `@LAT97` | Link windows, per-peer RSSI histograms | EVIDENCE | 48 | `--lane 97`/`0` |
| `@LAT98` | `BELIEF-ADOPTED` attestations (TTN-RFC-0009) | **PROVENANCE** | — | none — guard refuses |
| `@LAT99` | Time-sync log (TTN-RFC-0008) | **PROVENANCE** | — | none — guard refuses |
| `@LAT100` | `LANE-PRUNED` boundaries (lane generations) | **PROVENANCE** | 32 | **none, and this is the binding constraint** |
| `@LAT101+` | *unallocated* | — | — | — |

Three consequences worth stating plainly:

1. **There is not one FIELD lane on the fleet today.** Everything is evidence or
   provenance. Nothing below §4 is in use anywhere.
2. **The first FIELD lane MUST be a new lane at `@LAT101` or above.** It MUST NOT be an
   existing lane converted in place: the archived records in `master/` were written under
   EVIDENCE rules and reclassifying a lane retroactively reclassifies them too.
   ⚠ `@LAT89` and below is unavailable regardless — `isNodeRecord()` bounds navigation to
   `lat > -90 && lat < 90`, so a lane there renders as *a place on the globe*.
3. **`@LAT100` is provenance about provenance, and it has no prune path by design.** Its
   cap is therefore a lifetime budget, not a working set. Any proposal that consumes it
   faster is a proposal to shorten the fleet's life.

---

## 4. Identity: names that survive reclamation

### 4.1 The rule the corpus already had

TTDB-RFC-0004 is unambiguous on both halves of this:

- §2: *"When location is unavailable, coordinates MAY be derived from a stable hash."*
- §4: *"Once assigned, an ID MUST NOT change for the same record."*

The percept lanes take neither option. They name a record by **its ordinal position in its
lane** (`lane_n` → `@LAT97LON3`), so emptying a lane reassigns every name in it to a
different record. `@LAT100` was introduced to make that legible — *a prune writes down the
boundary it creates* — and it works, but it is a **workaround for declining a mechanism
TTDB-RFC-0004 already sanctioned.** Stable-hash naming is not a new invention here; it is
the option the percept lanes did not take.

### 4.2 Stable ids (normative)

A record in a lane that MAY be reclaimed (any FIELD lane, and any EVIDENCE lane whose
implementation chooses §7.3 over boundaries) MUST carry a stable id:

```
@LAT97LON3 | sid:a1b2c3d4 | created:… | updated:… | relates:…
```

- `sid` is 8 lowercase hex digits: a deterministic 32-bit hash over the record's
  identity-defining content — at minimum `node_id`, lane, stream id, and the observation
  timestamp. It MUST be computable on-node in integer arithmetic, and MUST NOT include
  the record's ordinal.
- **The coordinate remains the address; `sid` is the identity.** Keeping `@LATxLONy` means
  TTCP-RFC-0002 navigation, `isNodeRecord()`, the globes, and every existing index keep
  working unchanged. Replacing the coordinate with a hash would be a larger and worse
  change.
- Collision: the fleet's files declare `collision_policy: reject`. On a `sid` collision
  within a lane an implementation MUST perturb the discriminator and retry, bounded; if it
  still collides it MUST **drop the deposit and count the drop**, never overwrite.

### 4.3 Citations (normative)

TTDB-RFC-0003 §1 requires edges to use the syntax declared in `mmpdb.typed_edges.syntax` —
a **per-file declaration**, so this is an extension of an existing hook, not a format
break. A file using stable ids declares:

```yaml
typed_edges:
  enabled: true
  syntax: "type@LATxLONy[#sid]"
```

- A citation MAY carry `#sid`: `derived_from@LAT97LON3#a1b2c3d4`.
- ⚠ **A `#sid` that does not match the record now at that coordinate MUST resolve as
  `stale`, never as the record found there.** This is the whole point: the failure
  `@LAT100` exists to make detectable becomes detectable *per citation, by a reader holding
  nothing but the file*, with no boundary record and no lane-generation arithmetic.
- ⚠ **Both forms are permanently live.** A bare `type@LATxLONy` MUST remain valid and MUST
  be resolved under the existing `@LAT100` generation discipline. The corpus contains
  archived records that will never have a `sid`; a reader that requires one folds every
  pre-adoption lane silently. *This is the same rule that keeps `synced:` parsing beside
  `stream:`/`wall:`, for the same reason.*

---

## 5. Decay and reinforcement (normative, FIELD lanes only)

A FIELD record carries a strength and the terms needed to age it:

```
**TRACE** sid:a1b2c3d4 … strength:180 half_life_ms:600000 reinforced:9 last_ms:8260961
  stream:0xe334a7e1 wall:0
```

1. **Decay MUST be evaluated on read and MUST NOT be written.** The stored pair is
   `(strength, last_ms)`; the effective value is computed when the record is read. A
   design that re-writes decayed strengths would append to flash on a timer — the flash
   write is 60–220 ms on the reference hardware and the wear is unbounded. **Only
   reinforcement writes.**
2. **Reinforcement** updates `strength`, `reinforced`, and `last_ms` in one appended
   record; `reinforced` is the run-length count and MUST state what it folded, exactly as
   the `**RUN**`/`**COVERED**` forms do.
3. **Reclamation:** when a FIELD lane is full, the record with the lowest *decayed*
   strength is replaced. Ties resolve to the oldest `last_ms`. A reclamation MUST NOT write
   a `@LAT100` boundary — under §4.2 naming there is nothing to re-point, and spending the
   boundary budget per reclamation would be strictly worse than the treadmill it replaces.
4. ⚠ **The stream clock is a ratchet.** A stream's clock is elapsed-since-its-own-origin
   and adopts the fastest crystal it hears, which is correct for ordering and recency and
   **wrong for measuring a duration**. A half-life is a duration. Therefore: a node MUST
   compute decay from a *local* `millis()` delta (as `MotionPercept`'s `dt_ms` does) and
   MUST use the stream stamp only to decide whether a peer's trace is comparable at all. A
   trace stamped `stream:0x00000000`, or with a stream this node cannot relate to its own,
   has **unknown age** and MUST NOT be treated as fully decayed.
5. Deposits arriving over the radio MUST be queued from the receive callback and merged
   only from the service path — the rule `TimeStreamNode` follows because `mono()`'s wrap
   accounting cannot survive a torn write.

---

## 6. What MUST NOT be a field

### 6.1 No measured constant may come from a FIELD lane
A threshold, baseline, or published distribution MUST be derived only from EVIDENCE.
A field removes its own data according to a rule correlated with the quantity being
measured, so a distribution over it is not a sample. The reference fleet's baseline
procedure makes this concrete: its gates require one stream id, `t_ms` monotonic, an
independent stillness witness on the same timeline, and ≥30 pairs surviving a cadence
filter. Gates 2 and 4 are unprovable over a medium that evaporates.

### 6.2 No `derived_from` edge may target a FIELD record
An edge must resolve to a record that exists. This is the rule run-length already
established for offsets (`acting:@LAT95LON7+3` may name a folded window; `derived_from`
stays a plain resolvable citation) and it applies with more force to a trace that is
designed to disappear.

### 6.3 A field MUST be an optimisation, never the store of record
**Acceptance test:** the system MUST still be correct with the field **empty**. A node
that has just booted has no traces and MUST behave correctly, if less efficiently. If
emptying a FIELD lane changes an answer rather than a latency, that lane is holding
evidence and is misclassified.

### 6.4 A faded trace MUST render as faded, never as absent
The rendering rule *if a view can show less than all of a record, it must say so on
screen* applies to strength as well as length. A UI that draws only "trail present /
absent" turns "nobody has reinforced this for an hour" into "there is no trail," which is
a different claim.

---

## 7. Adoption

### 7.1 Declaration
A file using this RFC declares its lane classes in `mmpdb`:

```yaml
lane_classes:
  evidence: [0, 91, 92, 93, 94, 95, 96, 97]
  provenance: [90, 98, 99, 100]
  field: [101]
```
Absent declaration, every lane is EVIDENCE (§2 fail-safe).

### 7.2 Staging — each stage is independently abandonable
- **Stage 0 — classify.** Publish the §3 register. No code, no risk. *This RFC is stage 0.*
- **Stage 1 — readers accept `#sid` and ignore it when absent.** Writers unchanged, so
  every existing file stays byte-valid. Zero-risk and it makes stage 2 testable.
- **Stage 2 — one lane writes `sid:`.** Both forms live (§4.3).
- **Stage 3 — the first FIELD lane at `@LAT101`,** decay-on-read, reclaim-lowest.
- **Stage 4 — retire that lane's prune.** `@LAT100` consumption stops growing.

### 7.3 Cost
Per citation `#sid` is +9 bytes; per record `sid:` is +13. At the reference fleet's 48
records/lane that is ~600 B/lane against a 256-record file budget — cheap in flash, and
**not** cheap in the app partition on a node already at 94% (~74.5 KB free): the three
spine nodes need `huge_app` before they carry any of this. The two handhelds (41%, 40%)
have room.

### 7.4 What adoption does NOT change
- A **wholesale** prune of an EVIDENCE lane still writes a `@LAT100` boundary. Stable ids
  make *reclamation* boundary-free; they do not license silent deletion.
- `@LAT98`/`@LAT99` remain unreachable by any prune. The guard is not widened.
- Archived artefacts MUST keep parsing unchanged (§4.3).
- ⚠ No stage may be applied to a node **during a measurement run.** Flashing a filesystem
  image wipes the lanes, and a firmware change mid-run breaks the contiguity the gates test.

---

## 8. Falsifier

Stated before implementation, per the practice this fleet applies to its own measurements:

1. If stage 3 does **not** eliminate the target lane's prune operation, abandon the RFC —
   the treadmill was not the cost that mattered.
2. If a field's decayed choice agrees with the equivalent append-only tally's choice in
   every observed case, the field bought risk and no capability. Report that and stop.
3. If `sid` collisions require more than a bounded retry at 48 records/lane, §4.2's hash
   input is wrong and must be measured, not re-guessed.

---

## 9. Open questions

- The `sid` hash function and discriminator are unspecified pending a measured collision
  rate. FNV-1a over `(node_id, lane, stream, t_ms)` is the obvious first candidate.
- Whether a FIELD lane should be shared over the air as deposits (HELLO carries 21 of 250
  bytes today, and an un-reflashed node contributing 0 bytes is already a non-participant
  rather than a parse error) or held per-node and merged only on pull. `stigmergy.md` §4.A
  argues the former for transport trails; this RFC does not decide it.
- Whether `@LAT100`'s cap should rise. It should not rise as a *response to pressure* —
  the pressure is the signal that the naming is wrong.

End TTDB-RFC-0010
