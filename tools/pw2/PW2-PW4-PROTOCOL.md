# PW-2 / PW-4 replay protocol (pre-registered)

TTDB-RFC-0011 v0.1.4 §8. Written and committed before any replay code exists. Constants are in
`pw2_constants.py`. Scope, parsing, dedup and residuals are reused unchanged from PW-1
(`tools/pw1/pw1_fold.py`): all `master/**/*.md`, deduplicated, lanes 94–97 only.

## PW-2: gain protects settled beliefs

**Claim.** With a high-variance channel injected, §3.4 flips bodies of settled (high-`conf`)
beliefs less often than the fixed-step rule it replaces.

**Beliefs.** One scalar belief per series `(node, channel)` (link: per `(node, peer, proto)`),
`body` = last accepted observation, `conf` starts at 128 under both rules. Prediction = the
belief's body (a `before` record), not the previous window. Channels: acoustic, motion, link.
Entity (set-valued) is excluded: a synthetic set-noise model would be a second experiment.

**Two rules, same inputs.**
- *Fixed* (RFC-0005 loop): `pe ≥ pe_agree` → body := observed, `rev += 1`, `conf −= 16`;
  else `conf += 2` (saturating).
- *Gain* (§3.4): `K = 255π/(π+conf)`; corroboration and contradiction branches exactly as §3.4.
  `π` is the channel's online §4.3 fold (128 until 30 residuals).

**Injection.** At window 60 of each series a noisy twin starts reporting on the same belief,
interleaved after each real window. Its observation is the real one plus noise uniform in
`[0, 0.6·span)` with random sign (deterministic xorshift32, seed per stream), clamped. The twin
has its own `π`, folded online from its own residuals.

**Cohort.** Beliefs with `conf ≥ 192` at window 60 under *both* rules (so both rules are
tested on beliefs each considers settled). Flips are counted after window 60, summed over cohort.

**Verdict.** PASS if `flips_gain ≤ 0.5 · flips_fixed`; KILL if `flips_gain ≥ flips_fixed`;
otherwise INCONCLUSIVE; INCONCLUSIVE too if the cohort has fewer than 5 beliefs.

**Reported, no verdict.** (a) the same replay with no injection, to show whether §3.4 still
follows genuine changes; (b) revision latency on genuine steps; (c) cohort size per channel.

### Known property to be stated in the report, not tuned away
`K ≥ k_revise = 160` needs `π ≥ 1.68·conf`, and `π ≤ 255`, so a single contradiction can never
revise a belief with `conf ≥ 152`; it can only lower `conf` (`conf −= conf·K/255`) and set the
contradiction flag, and revises only after several. That is intended (§3.4), but it means a
high-`conf` flip count under §3.4 is small by construction. PW-2 therefore also reports how many
contradictions it takes to revise a cohort belief, so "protection" is not mistaken for "immunity".

## PW-4: an empty workspace changes no answer

Every replay above (and one plain archive replay) is run twice, workspace disabled vs enabled
(§5: ignition at `θ_ign`, capacity `W`, decay, hysteresis). The key is the SHA-256 of the final
sorted belief store. PASS iff all pairs are identical; KILL on any difference.

**Canary.** A third variant deliberately lets the update path read workspace state. It must
produce a different hash. If it does not, the test cannot fail and PW-4 is INCONCLUSIVE.

## Guardrails (as PW-1)
Read-only on `master/`; no threshold changed after data; every exclusion logged; surprises
reported as candidate `lat 98` divergence beliefs; a KILL is written back to the RFC as a
result.
