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
| D3b | **Taken 2026-11-22 after run 1 (§9): the synchronous fold measured 141–288 ms, over D3's 100 ms budget.** The fold becomes a job, spec in §5.1 | D3's own rule, applied as registered |
| D7 | **Added 2026-11-22 after run 1 (§9): also write when the fold's `from` differs from the on-flash record's `from`** (§4) | Run 1 showed a record kept by the Δ-rule outliving its own episodes: UNVERIFIABLE by construction |

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
  `|π − π_on_flash| > 8` (`prec_write_delta`), **or (D7) when the fold's `from` differs from
  the `from:` on the on-flash record's `**FOLD**` line** (an on-flash record whose `from:`
  will not parse counts as differing). Why D7: the quota cuts a tier's oldest episodes, so a
  record kept by the Δ-rule alone soon cites episodes that are no longer on flash, and the
  gate can never check it again. The calmer the channel, the sooner that happens. With D7 a
  record always names a range that was wholly on flash when it was written. Cost: about one
  write per channel per rotation (12 min) while its tier is at quota, 58–122 ms each (§9).
  `prec_write_delta` still keeps a channel from writing when its window has not moved.
  The old `rev` and `created` come from the old
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
- **Fold state on the stack: 1 248 B, measured** (`sizeof(precision::Fold)`: two parsed
  windows of 600 B, each holding ≤ 10 link keys and ≤ 16 BSSIDs of ≤ 16 hex). The first
  draft of this doc said ~250 B; that was an estimate, and it was wrong by 5×. The `[prec]` line
  prints the loop task's stack high-water mark (`stack_free:`), so the margin is read on
  hardware. An overflow is counted as `excluded` with reason `overflow`, never truncated.
- **Static state:** a rotation counter only. The old `π`/`rev` are re-read from flash at
  each write decision, so the record stays the only source.
- **Time:** unmeasured. Each fold prints
  `[prec] chan:<c> n:… var:… prec:… episodes:… ms:<fold> wrote:<yes|no Δ…> ms_write:…`.
  The section profiler's worst pass for `linkperc` is read over at least 9 folds (≥ 2 per
  channel) on one held connection ([[verify-before-believing]]: n ≥ 9). **Budget D3:
  fold ≤ 100 ms at its worst**, writes excluded; a write is a flash rewrite at most once
  per 12 minutes. Over budget means D3b.
- Compile size is reported against a HEAD build of the same sketch.

### 5.1 D3b: the fold as a job (normative from 2026-11-22)

- **Start:** a Stage D cycle starts a job for the next channel in the rotation (§2). If the
  previous job has not finished, the cycle starts nothing, prints `[prec] busy`, and does
  not advance the rotation.
- **Step:** every loop pass, a running job folds **at most 2** episodes of its band. It
  visits the index in file order from a cursor, so non-band records cost only an in-RAM
  index lookup. The pass reads each episode into `EpisodeNode::scratch()` and parses it into
  the `Fold`. No raw text is kept between passes, so the scratch buffer is free again for
  the other tiers before the pass ends.
- **Cursor:** the cursor is an index position plus the LON of the last episode folded.
  Cuts and appends re-index the Ttdb, so every pass first checks that the record before
  the cursor still has that LON. If it doesn't, the pass rescans for it. If that episode
  is gone, the job is **aborted**. That is safe because episodes are never rewritten in
  place: appends go to the end, rewrites keep order, and delivered episodes live in
  `@LAT105` (Episode.h). So an episode found after the cursor has not been folded.
- **Finish:** the job finishes when the cursor reaches the end of the index. If its
  `from` episode is no longer on flash, it is **aborted**: the record would be
  unverifiable at birth. Otherwise the write rule (§4) is applied in that pass. An episode
  appended to the band mid-job is folded if it lands after the cursor, and `through` and
  `episodes` cover it. The gate is unchanged.
- **An abort** prints `[prec] chan:<c> ABORTED (<reason>)`, writes nothing, and leaves
  that channel to the next rotation. The count of aborts is printed with every `[prec]`
  line.
- **State:** the `Fold` (1,248 B) and the cursor now persist across passes, so they become
  a **static member of `precision::Node`**. That is about **+1.3 KB of `.bss`**, against
  the 5.6 KB static that boot-looped this board (docs/log/2026-10.md). That cost is why D3
  tried the stack first. Heap is the risk, so it is measured (below).
- **Budget (unchanged in value): the worst job pass ≤ 100 ms, write passes excluded.** The
  finishing pass reports its fold part and its write part separately. Each finished job
  prints `[prec] … passes:<p> worst_pass_ms:<w> total_ms:<t> ms_write:<m> aborts:<a>`.
  The budget is read over **≥ 9 finished jobs** on one held connection.
- **Health, added to the stage pass:** no reset over the whole run, from flash through the
  second pull. The `[mem]` boot line and the `[loop] … heap` lines are recorded against
  run 1's (boot: heap 190,392, maxalloc 147,444; running: 15.6–19.0 KB free, maxalloc
  7–10 K). There is no heap threshold, because no number exists that I could justify; a
  reset fails the run.

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

**Run 2 onward (after D3b and D7):** the same two-pull condition, with two additions.
For each channel in the second pull, one of two things must be true:
- its record has a **higher `rev`** than in the first pull (a new write), or
- its `from` is still **the oldest episode of its band in that pull**. A record like that
  is what D7 would leave unrewritten, because its window has not moved.

Run 1's second pull failed both. The gate tool reports which case holds, so the
condition is checked, not eyeballed. And the §5.1 health condition must hold.

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

## 9. Run 1 (2026-11-22, build `424873b`, synchronous fold): stage NOT PASSED

The Cardputer was flashed with firmware only (FS untouched) and held on one connection for
15 minutes from reset. Boot: `TTDB loaded: 183824 bytes, 264/288`, `heap 190392 free,
maxalloc 147444`.

| `[prec]` fold | n | var | π | conf | episodes | ms (fold) | write | ms_write | stack_free |
|---|---|---|---|---|---|---|---|---|---|
| link | 62 | 91 | 252 | 80 | 40 | **288** | yes (first) | 122 | 3400 |
| entity | 35 | 2272 | 199 | 80 | 40 | **187** | yes (first) | 69 | 2712 |
| motion | 244 | 0 | 255 | 112 | 23 (4 excl.) | **141** | yes (first) | 58 | 2712 |
| acoustic | 21 | 19 | 254 | 64 | 24 | **178** | yes (first) | 69 | 2712 |
| link | 62 | 91 | 252 | 80 | 40 | **175** | no (Δ 0) | 0 | 2712 |

- **D3 budget: FAILED.** All five folds exceed 100 ms. The profiler's `linkperc` worst pass
  reads 182–412 ms on the fold passes, against single digits to tens of ms otherwise. Hence
  D3b.
- **Gate, pull 1** (12:49 pm, `tools/stage3/pulls/cardputer_20261122_1249_g1.md`): **MATCH × 4**.
  The firmware's records equal pw1's arithmetic on the board's own flash.
- **Gate, pull 2** (1:02 pm, `…_1302_g2.md`): link, entity, motion MATCH; **acoustic
  UNVERIFIABLE** (`@LAT103LON27924..27947` partly cut). No record had been rewritten
  (every Δ ≤ 8), so pull 2 re-checked pull 1's records rather than new ones. Hence D7 and
  the §6 run-2 condition.
- Stack held: 2,712 B was the lowest free mark. No reset; running heap was 15.6–19.0 KB free.

## 10. Run 2 (2026-11-22, build `3b86d6f`, D3b + D7): stage NOT PASSED

Firmware only (FS untouched). One held connection for 40 minutes from reset, then pull 1, then
pull 2 thirteen minutes later. One boot banner and no reset over the held window. Boot:
`heap 189104 free, maxalloc 147444`.

- **D3b budget: PASSED.** Across 14 finished jobs (≥ 3 per channel), `worst_pass_ms` was
  **8–17 ms** against 100 ms. Totals were 63–362 ms spread over 9–24 passes. No `ABORTED`,
  no `busy`. Stack was 2,956 B free at worst; heap 16.6–22.3 KB free.
- **D7 worked as designed:** motion rewrote once (`from moved 16546->16555`) and acoustic
  three times (27924→28023→28041→28059). Link and entity windows did not move, so they did
  not rewrite (d = 0, 4, 6).
- **⚠ A rewrite costs about 3 s, not 58–122 ms.** The four rewrites took `ms_write` 2,889–3,028 ms,
  and each shows as a `linkperc` worst pass of 2.9–3.0 s. Run 1's 58–122 ms were **first
  writes** (append only). A rewrite is `removeCuts`, a whole-file rewrite of a ~185 KB TTDB.
  Writes were outside the budget by design (§5), but on this run they **doubled the rate of
  whole-file rewrites** (4 from `@LAT108` against 2 episode cuts and 1 delivery cut).
- **Gate, pull 1** (3:04 pm, `tools/stage3/pulls/cardputer_20261122_1504_r2g1.md`): **MATCH × 4**.
- **Gate, pull 2** (3:17 pm, `…_1517_r2g2.md`): link, entity, motion MATCH; **acoustic
  UNVERIFIABLE** again. Its record (rev 3, `@LAT103LON28059..28075`) had been cut **past its
  `through`** (oldest on flash: 28077). Independence: link, entity and motion UNMOVED;
  acoustic NOT-INDEPENDENT.
- **Unexplained:** the acoustic job should have run at least once between the two pulls.
  Rotation runs every 3 minutes, whether or not the pull reset the board. It would have
  moved `from` and rewritten. Pull 2 still holds rev 3. With no serial capture between the
  pulls, the candidates (an abort, `FAILED (removeCuts)` under low heap, `busy`) cannot be
  told apart. Next instrument: hold the port **without reset** between the two pulls.
- **Acoustic churns faster than one rotation.** From 27924 to 28077 is about 150 episodes in
  roughly 2.5 h, about 1 a minute, against a quota of 24 with batched cuts. So a record that is
  12 minutes old can lose its whole range. D7 makes a record verifiable when it is written;
  it cannot keep it verifiable until an arbitrary pull.

Correctness so far: every record that could be checked is MATCH. That is 14 MATCH, 0 FAIL
over 4 pulls and 2 builds. The failures are verifiability (acoustic) and write cost, not the
fold.
