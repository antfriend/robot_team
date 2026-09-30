# robot_team
What started as a team of ESP32 robots soon evolved into a band. A band of unlikely companions.

A fleet of autonomous ESP32 nodes (UNIHIKER K10, Heltec V4s, a LilyGo T-Deck, an M5Stack
Cardputer) that reason from an on-flash markdown knowledge base (TTDB), speak HMAC-signed
250-byte "toots" over ESP-NOW, keep a shared musical pulse, and play in sync — **no cloud
LLM on any device.** A laptop observes, reconciles and re-authors beliefs; the point is that
it can be unplugged.

**The hypothesis** ([ACT-III.md](ACT-III.md) §2): a fleet of embedded agents, with no cloud
model and no laptop present, can **keep** a memory that never refuses a write,
**cooperatively discover** its own arrangement by acting to resolve what it does not know,
**agree** without coordinating, and **display** what it knows and how well it knows it — on
its own screens, unprompted. Each clause has a stated falsifier.

Semantic positioning ([ttn-semantic-positioning.md](ttn-semantic-positioning.md)) is how
that gets tested: the fleet infers its own physical arrangement from the overlap of what its
nodes perceive — verified against the T-Deck's GPS, actuating automatic ESP-NOW ↔ LoRa link
selection, and rendered as live TTCP maps. It keeps every measurement and every falsifier it
has earned; what changed is that it is now the *exercise* rather than the terminal claim.

Where to start:

- [FLEET.md](FLEET.md) — the fleet brain: current state, fleet table, next action. **Read first.**
- [ACT-III.md](ACT-III.md) — the plan of record: the hypothesis and the four workstreams under it.
- [CLAUDE.md](CLAUDE.md) — build & deploy (arduino-cli) and per-board gotchas.
- [PLAN.md](PLAN.md) — the phased build plan (Act I floor → Act II hypothesis).
- [replicate/RFCs/INDEX.md](replicate/RFCs/INDEX.md) — governing specs (A32, TTDB, TTN, TTCP, TTG).
- [docs/log/](docs/log/) — dated findings, one file per month.

Tests: `bash tests/run-all` (16 native + 16 laptop suites; needs the portable `zig c++`).

