# TTN-RFC-0002: Typed Edge Taxonomy

**Version:** 1.1
**Status:** Stable
**RFC Number:** 0002
**Project:** toot-toot-engineering
**Component:** Toot Toot Network (TTN)
**Depends on:** TTN-RFC-0001 (Core Mesh Specification), TTDB-RFC-0003 (Typed Edges)
**Author:** antfriend
**Created:** 2026-04-05

---

## Identity / Topology
- knows
- seen_near
- routes_via
- connected_over

## Conversation / BBS
- board_contains
- thread_root
- replies_to
- mentions
- moderates
- supersedes

## AI Semantics
- asks_ai
- ai_summarizes
- ai_flags
- ai_responds_to
- ai_refuses
- ai_confidence_low

## Sensors / Actions
- reports_sensor
- alerts
- commands
- acknowledges
- escalates

## Knowledge Graph
- supports
- contradicts
- refines
- duplicates
- derived_from

## Semantic Polarity
- opposes

Distinct from `contradicts` in Knowledge Graph. `contradicts` is *epistemic* —
two claims that cannot both hold. `opposes` is *semantic* — two concepts at
opposite ends of one dimension, both of which may be perfectly true. Symmetric;
see TTDB-RFC-0003 §7.

## Moderation / Trust
- trusted_by
- muted_by
- blocked_by
- flagged_as_spam
- quarantined

---

## Changelog
- **1.1** — Added §Semantic Polarity (`opposes`), so the taxonomy lists the type
  `TTDB-RFC-0003` §7 defines. Additive; every 1.0-conformant store remains valid.
- **1.0** — Initial.

*Sync note (2026-09-30) — ⚠ UNRESOLVED DIVERGENCE, DO NOT "FIX" BY COPYING EITHER WAY.*
Three checkouts held three byte counts for this file — 1140 here, 845 in
`toot-toot-engineering`, 900 in `antfriend.github.io` — and the sizes are misleading
twice over. The two smaller copies are **1.0 and identical in content** (the 55-byte
gap between them is CRLF). This copy is **1.1, a strict superset**, adding
§Semantic Polarity.

**But 1.1 is not the newer state, and a first reading of this got that backwards.**
Both `opposes` sections were authored on 2026-08-01 (here in `dc42f40`, upstream in
`ecac881`) — and upstream then **deliberately removed it on 2026-09-22** (`796f633`),
reverting its header to 1.0. So the ordering is: added in both, then retracted
upstream only. This checkout is behind a decision, not ahead of one.

What makes it a real question rather than a stale file: `TTDB-RFC-0003` §7, which
**defines** `opposes` and is itself v1.1, is byte-identical in all three checkouts and
was *not* reverted. So upstream now defines the type in the TTDB layer while omitting
it from this network-layer taxonomy — which is a coherent editorial position (a typed
edge need not be a network edge type), but the commit message is a web-edit default and
states no rationale.

Pending a decision, this checkout keeps 1.1 and **nothing is pushed outward for this
file.** Resolving it means either following the upstream retraction here, or restoring
it upstream with the rationale written down. Recorded so the next sync is a comparison
rather than an archaeology — and as a reminder that in this corpus a byte count is not
a direction.

End TTN-RFC-0002
