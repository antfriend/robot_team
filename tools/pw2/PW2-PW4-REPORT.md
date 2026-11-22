PW-2: PASS — gain-scaled flips 139 vs fixed-step 8217 on 41 high-conf beliefs (pass ≤ 4108.5, kill ≥ 8217)
PW-4: PASS — 4 of 4 workspace on/off pairs identical; canary caught; 1446 ignitions

Protocol and constants: `PW2-PW4-PROTOCOL.md`, `pw2_constants.py` (committed e3835e3 before this code existed).

## PW-2 — gain protects settled beliefs

- Series replayed: 57 (acoustic, motion, link; entity excluded). Cohort (conf ≥ 192 at window 60 under both rules): **41**.
- Flips after injection, summed over the cohort: fixed-step **8217**, gain-scaled **139**.

| channel | cohort | fixed flips | gain flips |
|---|---|---|---|
| acoustic | 2 | 410 | 2 |
| link | 37 | 5784 | 137 |
| motion | 2 | 2023 | 0 |

**Immunity check.** Contradictions a cohort belief absorbed before §3.4 revised it: median 12 over 139 revisions (min 1, max 91).

**Genuine change (no injection, reported, no verdict).** Total body rewrites over all series: fixed 201, gain 152. Genuine persistent steps found in the data: 132; revised within 20 windows — fixed 117 (median latency 0), gain 102 (median latency 1).

**Reading the result (descriptive; nothing re-tuned).** The cohort is dominated by link beliefs (37 of 41); acoustic and motion contribute 2 and 2. The fixed-step rule rewrites a body on every contradiction by construction, so a large fixed-step count is expected; the informative numbers are that §3.4 still rewrote 139 bodies under noise (it is protection, not immunity), and that without injection it revised 102 of 132 genuine steps against 117 for fixed-step, i.e. it follows real change a little less often.

## PW-4 — empty workspace changes no answer

| rule | replay | store identical (off vs on) | ignitions |
|---|---|---|---|
| fixed | archive | yes | 17 |
| fixed | injected | yes | 1312 |
| gain | archive | yes | 19 |
| gain | injected | yes | 98 |

Canary (update path deliberately reads the workspace): store differed, so the test can fail.

## Exclusions and notes

- duplicate: 4982
- unparseable: no t_ms: 9
- Series with ≤ 60 windows (no snapshot, outside every cohort): 11 of 57
- PW-4 is a test of this reference implementation: the update functions take the workspace as an argument only so the canary can misuse it. It shows the specified update rule does not depend on workspace state; it cannot show that firmware code never will.
