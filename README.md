# robot_team
What started as a team of ESP32 robots soon evolved into a band. A band of unlikely companions.

A fleet of autonomous ESP32 nodes (UNIHIKER K10, Heltec V4s, a LilyGo T-Deck) that
reason from an on-flash markdown knowledge base (TTDB), speak HMAC-signed 250-byte
"toots" over ESP-NOW, keep a shared musical pulse, and play in sync — no cloud LLM
on any device. A laptop companion orchestrates, reconciles, and re-authors beliefs.

**The primary hypothesis** ([ttn-semantic-positioning.md](ttn-semantic-positioning.md)):
the fleet can infer its own physical arrangement from the overlap of what its nodes
perceive — verified against the T-Deck's GPS, actuating automatic ESP-NOW ↔ LoRa
link selection, and rendered as live TTCP network/status maps on both the laptop
and the T-Deck's screen.

Where to start:

- [companion.md](companion.md) — the orchestrator brain: fleet table, current state, next actions. **Read first.**
- [CLAUDE.md](CLAUDE.md) — build & deploy (arduino-cli) and per-board gotchas.
- [PLAN.md](PLAN.md) — the phased build plan.
- [RFCs/INDEX.md](RFCs/INDEX.md) — governing specs (A32, TTDB, TTN, TTCP).

