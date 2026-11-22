# PW-3 replay protocol (pre-registered)

TTDB-RFC-0011 v0.1.5 §8 and §6.3. Committed before any replay code exists. Constants:
`pw3_constants.py`; rule values (`k_revise`, `pe_agree`, `prec_default`, `conf` baseline,
`pi_alpha`, `PI_SCALE`, `MIN_RESIDUALS`) are `tools/pw2/pw2_constants.py`'s. Scope, parsing and
dedup are PW-1's: all `master/**/*.md`, deduplicated, lanes 94–97 only, never 101.

**Claim.** A node that transmits a percept-derived toot only when `ε ≥ θ_tx` saves airtime
without costing the receiver its beliefs.
**Kills the RFC if** belief disagreement with ungated consolidation exceeds 5 % of beliefs, or
airtime falls by less than 30 %. **Passes** if neither. INCONCLUSIVE if fewer than 20 beliefs.

## Units
The unit is a **logged record** (deduplicated), not an expanded window: run-length-elided
windows were never records, so neither arm transmits them. Series = `(node, channel)`, link
per `(node, peer, proto)`; all four channels (acoustic `rms_mean`, motion `dev_mean_mg`,
entity BSSID set, link `rssi_med`). Segments as in PW-1/PW-2.

## Sender (per series)
Holds a belief updated by §3.4 from **every** record, with `pe` against its own belief body
(`pe_span` and Jaccard as PW-1) and `π` from its online §4.3 fold over previous-record
residuals (128 until 30 residuals). The first record founds the belief. Per record:
`ε = pe·π/255`; transmit iff `ε ≥ θ_tx = 96`. The first record of a series is always
transmitted (a receiver cannot be founded otherwise); that is counted in the airtime.
No peer requests, no heartbeat: neither is specified for this gate.

## Receiver (per series), two arms
- **Ungated:** sees every record. **Gated:** sees only transmitted records.
- Founds its belief at the first record it sees, then applies §3.4 with its own `pe` against
  its own body and the sender's `π` (the SALIENT `prec` field; the §6.4 trust cap is not
  modelled, as there is one trusted sender per series).
- **Disagreement** (per belief, at the end): the gated receiver has no belief, or
  `pe(gated body, ungated body) ≥ pe_agree`. Report the share of beliefs that disagree.

## Airtime
Bytes on air, a proxy (LoRa airtime also depends on spreading factor and preamble, equal in
both arms). PERCEPT toot for a record: `len(body.strip())` bytes split into frames of ≤ 208 B,
each + 33 B header + 8 B HMAC. A SALIENT toot is 53 B. Ungated = Σ PERCEPT toots of all
records. Gated = Σ (SALIENT + PERCEPT toot) over transmitted records — the notification is
paid for on top of the percept, which is the conservative reading of §6.3.
Airtime fall = 1 − gated / ungated.

## Reported without a verdict
Disagreement and airtime fall at `θ_tx` ∈ {64, 96, 128}, per channel; the verdict uses 96 only.

## Guardrails
Read-only on `master/`; thresholds fixed in advance; exclusions logged; surprises reported as
candidate `lat 98` divergence beliefs; a KILL is written back to the RFC as a result.
