# TTDB-RFC-0011 stage 3: one PRECISION lane (`@LAT108`) on the Cardputer

2026-11-22. Committed **before any stage-3 code**; the implementation is held to it. A
change to a rule below is a commit to this file first, with the reason.

Stage 3 per RFC §9.2: `@LAT108` on the Cardputer, folded in the Dream Cycle. §3.4 stays
disabled: `π` is **observed, not used**. Nothing on the node reads `@LAT108`, so no belief,
gain, screen or radio behaviour changes.

## 1. Decisions taken (Dan, 2026-11-22)

| # | Decision | Why |
|---|---|---|
| D1 | **Fold from flash only.** Every fold starts from `var = 0` and reads the channel's live `@LAT103` episodes. No EWMA is carried in RAM between folds | The record is then a pure function of the flash, so a pull can reproduce it |
| D2 | **Spans from PW-1b, as registered:** acoustic 900, motion 60 mg, link 90 dB; entity is Jaccard × 255. `PI_SCALE` 8192, `prec_alpha` 4 | RFC §8.4; fixed whatever the verdict |
| D3 | **Synchronous, one channel per Stage D cycle, measured.** Budget: the fold pass costs **≤ 100 ms** at its worst. Over budget → convert it to a job that reads 2 episodes per loop pass (D3b) | The cost is unmeasured; measure before adding machinery |
| D4 | **`conf = min(240, 16 × floor(log2(1 + n)))`**, integer log2, floored | The RFC's formula does not say how to round; floor is exact in integers. Recorded as an RFC gap |
| D5 | **Gate = exact equality** (§6) | — |
| D6 | Gate pulls go to **`tools/stage3/pulls/`**, never `master/` | Brief: never write to `master/` |

## 2. Where it runs

RFC §4.3 says to fold in Replay, never in Projection. This firmware has neither phase. Its
Dream Cycle is the **Stage D** block of `cardputer_console.ino` (180 s,
`DREAM_RECONCILE_MS`, inside profiler section `[2] linkperc`), which reads testimony back
off flash and never imagines anything. So "fold in Replay" is implemented as **"fold in
Stage D"**. The mapping is a decision, recorded here, not something found in the code.

**Rotation:** each Stage D cycle folds ONE channel, `chan = cycle % 4`, in tier order: link,
entity, motion, acoustic. The first cycle runs on the first loop pass after boot, so all
four have folded by about 9 minutes after boot, and each refolds every 12 minutes.

## 3. The fold (must equal `tools/pw1/pw1_fold.py`'s arithmetic exactly)

**Which episodes.** Tier `k` owns `@LAT103` LON band `[k·8192, (k+1)·8192)` (Episode.h,
`TIER_LINK=0, TIER_ENTITY=1, TIER_MOTION=2, TIER_ACOUSTIC=3`). That gives the channel from
the record index without reading anything. Episodes are visited in **file (index) order**,
which is append order.

**Parsing each episode.** A line that starts `said: <digits> | ` has that prefix stripped.
Then every line is matched with pw1's `parse_record` needles, translated literally:
- `\bt_ms:(\d+)` and `\bstream:0x([0-9a-fA-F]+)`: first occurrence in the record. `\b`
  means the preceding character is not `[A-Za-z0-9_]`, so `first_t_ms:` and `prev_stream:`
  never match.
- `**RUN**…\bwindows_since_last:(\d+)` on the same line; absent or 0 means a run of 1.
- acoustic: the record must contain `**ACOUSTICWIN**`; value from `**ACOUSTIC**…\brms_mean:(-?\d+)`.
- motion: `**MOTIONWIN**`; `**MOTION**…\bdev_mean_mg:(-?\d+)`.
- entity: `**ENTWIN**`; the set of `id:` hex strings from lines starting `**ENTITY**`,
  **case kept**, because pw1 compares them as strings.
- link: `**LINKWIN**`; a map of `(peer, proto)` to `rssi_med` from lines starting
  `**LINK**`, with `\s+peer:(\S+)\s+proto:(\S+)…\brssi_med:(-?\d+)`. A repeated key keeps
  the **last** value.
- A record missing its window token or its value is **excluded**: it is not folded and
  does **not** break the segment, exactly as in pw1.

**Segments.** A residual is taken between consecutive folded records of the channel. A
**new segment** starts (no residual) when the stream differs from the previous record's,
or `t_ms` is not greater than the previous record's. This is the stage-3 rule.
⚠ pw1 itself groups each stream and **sorts it by `t_ms`**. The two agree whenever each
stream's records are in increasing `t_ms` order in the file and streams do not interleave.
The gate reports whether that held (§6), rather than assuming it.

**Residuals** (pw1 `_scalar`, `_entity`, `_link`):
- scalar (acoustic, motion): for each record after a segment's first, add `run − 1` zero
  residuals (expanded mode, which gave the verdict), then `pe(val − prev.val)`.
- entity: the same, with `pe = min(255, 255 · |A △ B| / |A ∪ B|)`, and 0 when the union is
  empty.
- link: **no run expansion**. For each key of the current window in sorted
  `(peer, proto)` byte order that is also in the previous window, add
  `pe(rssi_med − prev)`. Keys missing from the previous window are counted, not folded.
- `pe(d) = min(255, |d| · 255 / span)`, using truncating division.

**Arithmetic** (RFC §4.3):
`var += ((r·r) − var) >> 4` on `int32_t`; `π = (255 · 8192) / (8192 + var)`; `n` counts every
residual folded. ⚠ The `>>` of a negative `int32_t` must be **arithmetic**. A
`static_assert((-1 >> 1) == -1)` in the library makes a compiler that shifts logically fail
the ESP32 build itself, not just a test.

**Fold metadata kept:** `from`/`through` (the first and last episode LON in the band at fold
time), `episodes` (how many were read), `excluded`, `segments`, `peers_absent` (link), and
`skipped` (an episode larger than the read buffer). Episodes are rendered in the same
3072 B buffer they are read back into, so `skipped` must be 0, and the gate treats any
skip as FAIL.

## 4. The record

```
\n---\n\n@LAT108LON<k> | sid:<8 hex> | created:<t> | updated:<t> | relates:derived_from@LAT103LON<through>
[ew]
conf:<D4>
rev:<rewrites>
sal:0
touched:<t>
[/ew]

**PRECISION** sid:<8 hex> node:0x00000300 chan:<link|entity|motion|acoustic> prec:<π> var:<var> n:<n> prec_scale:8192
**FOLD** pe_span:<span|jaccard> alpha:4 mode:expanded predictor:previous_window from:@LAT103LON<a> through:@LAT103LON<b> episodes:<e> excluded:<x> segments:<s> peers_absent:<p> skipped:<k>
**STAMP** <timestream::buildStamp triplet>
```
- **Address and identity:** `LON` = tier number (a fixed KEY address). `sid` =
  `sid::stampKey(node, 108, "node:0x00000300|chan:<c>")`, patched into the header
  placeholder in place. `t` is the stream's wall seconds, or 0.
- **`predictor:previous_window` is stated in the record on purpose.** RFC §3.2 defines
  `pe` on a `@PERCEPT` before/after pair. This fold, like PW-1, uses the previous window as
  the prediction. That divergence goes back to the RFC as a candidate `lat 98` belief.
- **Write rule:** write when no `@LAT108` record exists at that LON, or when
  `|π − π_on_flash| > 8` (`prec_write_delta`). The old `rev` and `created` come from the old
  record (`ttdbParseEw()`, stage 1's first real use) and its `**PRECISION**` line. On a write,
  `rev = old + 1` (0 on the first write) and `created` is kept.
- **Replacement:** `removeCuts({108, k, k})` and then `appendRecord`. No whole-lane rewrite,
  no other record touched. A fold with `n = 0` writes nothing.
- **Index:** exactly 4 keys, so the lane can never exceed 4 records and needs no quota. A
  write that `indexHeadroom()` cannot accommodate is **printed with its reason**, never
  silently dropped (ACT-III: nothing is refused without saying so).

## 5. Memory, cost, and the boot-loop history

- **No new static buffer** (docs/log/2026-10.md: a second 5.6 KB static boot-looped the
  Cardputer, starving BLE). Episodes are read into, and the record is rendered into,
  `EpisodeNode::scratch()`. Nothing else uses it during Stage D: the link window has
  already been appended, and the other tiers flush later in the pass.
- **Fold state on the stack**, ~250 B: at most 12 link keys and 24 BSSIDs × 2 sets.
  An overflow is counted as `excluded` with reason `overflow`, never truncated silently.
- **Static state:** a rotation counter only. The old `π`/`rev` are re-read from flash at
  each write decision, so the record stays the only source.
- **Time:** unmeasured. Each fold prints
  `[prec] chan:<c> n:… var:… prec:… episodes:… ms:<fold> wrote:<yes|no Δ…> ms_write:…`.
  The section profiler's worst pass for `linkperc` is read over at least 9 folds (≥ 2 per
  channel) on one held connection ([[verify-before-believing]]: n ≥ 9). **Budget D3:
  fold ≤ 100 ms at its worst**, writes excluded; a write is a flash rewrite at most once
  per 12 minutes. Over budget means D3b.
- Compile size is reported against a HEAD build of the same sketch.

## 6. The gate (pass condition fixed before the flash)

`tools/stage3/stage3_gate.py <pull.md>`, read-only over the pull:
1. For each `@LAT108` record, take its `**FOLD**` range. Check that every episode of that
   tier from `from` to `through` is present in the pull: within a band the ordinals are
   contiguous, wrapping at 8192, and the count must equal `episodes:`.
2. Strip the `said: N | ` prefixes, parse with pw1's own `parse_record` (imported), build
   segments by §3's rule, compute residuals with pw1's own `_scalar` / `_entity` / `_link`
   (spans set by `tools/pw1b.apply_spans`), and fold with pw1's `fold_var` / `pi_from_var`.
3. Verdict per record: **MATCH** if `var`, `n`, `prec`, `conf`, `episodes`, `excluded` and
   `segments` are all equal; **FAIL** on any difference or on `skipped > 0`;
   **UNVERIFIABLE** if part of the range is gone (a cut removed it), in which case pull sooner.
4. Also reported: whether pw1's own grouping (sort within a stream) would have given the
   same residual list (the §3 caveat).

**Stage 3 PASSES** when, on the Cardputer flashed with this build, **two pulls at least one
full rotation (12 min) apart, the first ≥ 10 min after boot,** each hold a record for **all
four channels** and **every record is MATCH**. Any FAIL fails the stage. UNVERIFIABLE means
pull again; it is not a pass. Separately, **the cost budget (D3) must be met**, or D3b is
built and the gate re-run.

Before hardware, a **rehearsal**: the native C++ fold run over an existing Cardputer pull
must equal the gate tool's fold over the same file, channel by channel. That is code
against code, with no threshold, so it reads `master/` as a fixture, not as an experiment.

## 7. Tests (native, in `tests/run-all`)

- pw1's hand-worked 5-residual case (`var` 4090, `π` 170), ported.
- Arithmetic shift: `static_assert`, plus a runtime case `(0 − 6) >> 4 == −1` inside the
  fold. A logical shift would make `var` enormous.
- **Shared vectors** `tests/vectors/precision_vectors.txt`: synthetic episode sequences per
  channel (runs, segment breaks, excluded records, link keys appearing and disappearing,
  `said:` prefixes, entity case). The expected `var`/`n`/`π`/`conf` are generated once by
  pw1's functions and committed. The C++ test and the gate tool's test both read the file.
- Record render → `ttdbParseEw()` + `**PRECISION**` parse → values round-trip, and the
  `sid` verifies.
- Write rule: no record → write; Δ ≤ 8 → no write; Δ > 8 → write with `rev + 1`; `n = 0` →
  nothing.

## 8. Out of scope

§3.4 (gain), any reader of `@LAT108`, other nodes, the `@LAT109` workspace, and any change to
`tools/pw1` / `tools/pw1b`. Flashing needs Dan at the bench; each flash is asked for first.
