# cardputer-sensorium.md — the Cardputer as a sensing creature

**Status:** proposal / build plan. **Two views are BUILT, flashed and verified on hardware
2026-07-28: the eyeball resting face (§4.1, the boot view, worst render 18 ms) and the
oscilloscope (§4.2, worst render 21 ms).** Both hold the loop budget (worst pass 28 ms
against ≤40). `1`/`2`/ENTER choose between them; there is still **no arbiter** (§3), so the
keyboard is the only thing that picks a view. Console and constellation are still proposal.
See §7 for what each phase now owes.
**Node:** `cardputer_1` = `0x300`, `firmware/cardputer_console`.
**Governing docs:** [companion.md](companion.md) §2/§6 (state), [PLAN.md](PLAN.md) (build
order), [ttn-semantic-positioning.md](ttn-semantic-positioning.md) (the primary
hypothesis), `replicate/RFCs/TTDB-RFC-0005-Epistemic-Weight.md` (the attention math this
reuses), `replicate/RFCs/TTCP-RFC-0002-Globe-and-Navigation.md` (the views this sits
beside).

---

## 1. What this is

Today the Cardputer boots into a **globe** — a map of the fleet, inherited from the
T-Deck. That is a picture of *what it knows*. This proposal gives it a second face: a
picture of *what it is sensing right now*.

The node powers up with its toot into **REPRESENTOR** mode, where the screen is given
over to whichever sense is most activated at that moment — a red eyeball when it is
tilted, a green oscilloscope when the room makes a noise, the console when neighbors
speak. Every other sense keeps polling in the background and can take the screen the
instant it becomes the loudest thing happening. **`t`** drops back to the inherited
globe views.

**The important thing to be clear about up front:** the senses already run. All four
percept tiers (`@LAT97` link, `@LAT96` entity, `@LAT95` motion, `@LAT94` acoustic) poll
continuously today and write to the TTDB every window. This proposal adds almost no
sensing. What it adds is an **arbiter** (which sense deserves the screen) and
**renderers** (what each sense looks like). That is why it is a tractable piece of work
rather than a rewrite.

---

## 2. The sensorium — including what the brief missed

The brief named three modalities. The board has more. Marked ✅ where the sense is
already being polled and logged today.

| # | Modality | Hardware | Polled today? | In the brief? |
|---|---|---|---|---|
| 1 | **Tilt / orientation** | BMI270 accelerometer | ✅ `@LAT95` | ✅ red eyeball |
| 2 | **Rotation / shake** | BMI270 **gyroscope** | ❌ *(accel only)* | ❌ **missed** |
| 3 | **Sound** | ES8311 + MEMS mic | ✅ `@LAT94` | ✅ green scope |
| 4 | **Neighbors** | ESP-NOW / BLE toots + RSSI | ✅ `@LAT97` | ✅ console |
| 5 | **Place** | WiFi BSSID scan | ✅ `@LAT96` | ❌ **missed** |
| 6 | **Interoception — energy** | battery ADC (G10) | ❌ | ❌ **missed** |
| 7 | **Interoception — heat** | ESP32-S3 internal die temp | ❌ | ❌ **missed** |
| 8 | **Rhythm** | the band pulse (`Pulse.h`) | ✅ | ❌ **missed** |
| 9 | **Contact** | 56-key TCA8418 keyboard | ✅ (as input) | — |
| — | *IR (G44)* | emitter only | — | **an effector, not a sense** |
| — | *Grove HY2.0 (G1/G2)* | I²C/analog socket | — | a place to add senses later |

### What you forgot, ranked by how much it adds

1. **The gyroscope.** The BMI270 is a 6-axis part — you named the accelerometer, which
   gives *tilt* (a slow, absolute, gravity-referenced quantity). The gyro gives
   *angular velocity*: shake, flick, spin, being set down hard. These are perceptually
   different and the eyeball wants both — tilt aims the gaze, gyro makes it **dart**.
   An eye that only tilts looks like a gauge; an eye that also saccades looks alive.
   Cost: near zero, the driver is already reading both.

2. **Place** (`@LAT96`, the WiFi BSSID set). The node already logs the access points
   around it, and that set *changes when you carry it to another room* — it is a real,
   working sense of "where am I" with no display. A "constellation" view (each BSSID a
   star, brightness = RSSI, the set shifting as you walk) would surface a modality that
   is currently invisible despite being logged every 10 minutes.

3. **Interoception — battery.** A creature that senses the world but not itself is
   half a creature. G10 reads the pack voltage; on a 1750 mAh battery this is a real,
   slow-moving signal. Best used as *ambient colouring* across all views (see §4.5)
   rather than a view of its own.

4. **Heat.** `temperatureRead()` gives the die temperature. Crude and self-referential
   — but note the fleet's STATUS payload **already reserves a temperature field, and
   this node currently sends `0` in it** while the K10 sends a real reading. Wiring
   this fills an existing hole in the fleet's telemetry for about four lines of code.

5. **Rhythm.** The node knows the band's beat phase at all times. Not a sensor, but it
   *is* an external signal the node perceives and can be dispossessed of (the conductor
   dies, the beat stops). Worth a heartbeat mark on every view.

---

## 3. The representor — how "most activated" is decided

### 3.1 Reuse the fleet's own attention currency

Do **not** invent a new salience scheme. `TTDB-RFC-0005 §3.3` already defines the
project's attention math:

```
EPS = sal × (255 − conf) / 255
```

Each modality reports an `(sal, conf)` pair each tick and the arbiter picks the highest
EPS. The mapping:

- **`sal` — how strongly this sense is deviating from its own baseline.** Each
  modality already keeps a rolling baseline (the acoustic tier's `ambient_`, the motion
  tier's deviation-from-1g, the link tier's per-peer histograms). Salience is the
  current stimulus expressed **in units of that sense's own noise**, clamped to 0–255.
  This is what makes modalities comparable: a whisper in a silent room and a hard tilt
  are both "3× my usual", and the screen should go to whichever is more unusual *for
  that sense* — not to whichever has the bigger raw number.
- **`conf` — how well-explained the stimulus is.** A sound arriving while *we are
  playing a note* is fully explained (conf 255 → EPS 0). A neighbour toot from a node
  we hear every 2 seconds is well-explained. A bang from nowhere is not.

That second term is what stops the mode from being a twitchy meter. It also solves a
problem this node has by construction — see §3.3.

### 3.2 Hysteresis, or the screen will flicker

A pure argmax over six modalities repaints constantly. Three guards:

- **Take-over margin:** a challenger must exceed the incumbent's EPS by ≥ 25% to seize
  the screen.
- **Minimum dwell:** once a modality takes the screen it holds it ≥ 1.5 s regardless.
- **Decay:** salience half-lives back toward 0 over ~3 s, so a bang gives the scope the
  screen and then hands it back rather than latching.

**Default when nothing is activated:** the eyeball, idle — blinking slowly, gaze
following gravity. A resting face, not a blank screen.

### 3.3 The node hears itself — this must be gated

This node has a speaker **and** a microphone, and it sings: the boot toot, `CMD_BEEP`,
and its Ode-to-Joy harmony in the finale. Without a gate, **every note it plays will
seize its own screen** through the acoustic modality, and worse, its own voice will
pollute the `@LAT94` transient log that the whole TDoA idea rests on.

Rule: while `toneI2S()` is sounding, and for ~50 ms after, acoustic samples are marked
`conf: 255` (fully explained) — they still feed the ambient baseline, but they cannot
win the screen and **must not be logged as transients**.

This is worth fixing regardless of whether the representor gets built: it is a latent
data-quality bug in the acoustic tier as it stands today.

### 3.4 The loop budget — the hard constraint

We already learned this node's lesson the expensive way: **the toot link is serviced
once per `loop()` pass, so the slowest pass is the node's response time on the mesh.**
An `edgesAt()` call per record per frame cost 767 ms per repaint and blew `verify` to a
419 ms rtt (companion.md §6).

Therefore the representor is **budgeted before it is written**:

| Constraint | Budget |
|---|---|
| Per-frame render | **≤ 25 ms** |
| Frame rate | **≤ 10 Hz** (100 ms between repaints) |
| Worst loop pass | **≤ 40 ms** (currently 104 ms) |
| `verify` rtt after | **≤ 50 ms**, and the sync bound must still PASS |

Consequences that follow from the budget, not from taste:

- **No full-screen repaints.** Every view redraws only what changed — the scope shifts
  columns, the eyeball moves the iris and repaints the annulus it vacated.
- **No filesystem access in any renderer.** Not once, not per record. (The rule the
  globe broke.)
- The oscilloscope will refresh at ~10 Hz. That is a *slow* scope; it will read as a
  living trace, not a 60 fps instrument. If that looks wrong in the hand, the fix is a
  column-shift renderer, **not** a bigger frame budget.

**Gate:** the loop profiler already in the sketch prints the worst pass every 30 s. No
phase of this work is "done" until that number is inside budget *and* `verify` passes.

---

## 4. The views

All views share one canvas allocated once at max size, and all carry two persistent
marks: a **beat tick** (rhythm) and a **battery hue** (interoception).

### 4.1 Eyeball — tilt + rotation (red, screen-filling)

A single eye filling all 240×135. Rendering is deliberately cheap: three filled circles
and an eyelid rectangle.

- **Gaze** = accelerometer tilt. The iris tracks the direction of gravity, so the eye
  appears to look "downhill" — the device physically points its attention. *(Built. The
  axes needed **inverting** on hardware: the chip's frame is the opposite of what was
  assumed blind. The saccade is scaled by the same constants, so one flip fixes an axis
  end to end.)*
  **The gaze sits in a bowl, not on a slope.** Raw tilt is linear in sin(angle), so the
  iris left centre at the slightest lean and the face read as a spirit level. The tilt
  magnitude now runs through `r = (tilt / BOWL_FULL_G) ^ BOWL_GAMMA` (2.0 / 0.80 g ≈ 53°):
  a subtle tilt barely disturbs the ball, a steeper one runs it a long way, and it stops
  at the rim — which `EYE_REACH` always enforced, but the ball used to arrive there early
  and sit on it. Only the **magnitude** is curved; the direction is untouched, or the gaze
  would bend off downhill on the diagonals. **The saccade bypasses the bowl** and is added
  after it: a flick is a kick, not a lean, and a squaring curve would swallow it.
- **Saccade** = gyroscope. Angular velocity displaces the pupil sharply and it springs
  back; a flick makes the eye dart, a shake makes it tremble. *(Built.)*
- **Blink** on a hard tap (accel spike above the shake threshold), and idly every 8–16 s
  so a resting eye is alive without fidgeting. The lid is **black** and goes straight to
  fully shut: one frame closed, one frame open. *(Built. The blink-open repaint is the
  face's most expensive recurring frame at 24 ms — it is what the ≤25 ms budget buys.)*
  **The 100 ms frame grid is the floor on blink speed.** A blink is quantized to it
  whatever `BLINK_MS` says, and a partial-closure phase would eat the whole blink. Going
  faster than one frame needs the blink to render off the 10 Hz grid — a bigger change
  than a faster blink is worth.
- **Pupil dilation** = overall arousal (the summed EPS across all modalities), so even
  in eyeball mode the face reports that *something else* is happening. *(Built as a
  two-term stand-in until the arbiter lands.)*
- **The pupil also carries the beat**, widening on every beat and hardest on the
  downbeat. This replaced a beat dot in the corner: the rhythm mark §4 asks every view
  to carry is better as a property of something you are already looking at than as a
  second thing to watch.
- **The beat is the face's frame clock.** Rendering happens only inside a ~220 ms pulse
  at the head of each beat (4 frames); between beats the eye is entirely still — no gaze
  update, no repaint, nothing on the SPI bus. With no other sensory input the beat is a
  **one-pixel** dilation; arousal is what opens the swing up to 7 px. Blinks land on a
  beat, and `BLINK_MS` is derived from the frame interval because a blink is quantized to
  the render grid regardless of what it is set to.
  **The clock must never stop:** when the band has no chart the face falls back to a
  free-running local pulse at the fleet tempo. An eye that freezes because the conductor
  died does not read as "dispossessed of the beat", it reads as broken.
  **Intended consequence:** the gaze now moves in beat-quantized steps, so the eye tracks
  a tilt rhythmically rather than smoothly.
- Sclera is off-white, iris **red** as specified; the sclera carries a thin battery
  ring (§4.5). *(Battery ring not built — that is S4.)*
- **Nothing in this view fills a circle it is about to cover.** `Adafruit_GFX::fillCircle`
  fills with *vertical* spans, so a black disc painted under the red one was visible from
  the bench as momentary vertical bars sweeping the iris. The limbal ring is drawn as a
  ring, and a pupil-only change paints **just the circumference** between the old and new
  radius — black outward to dilate, iris-red inward to constrict. The iris is not touched.
- **The catchlight is fixed in ROOM coordinates, not on the iris.** A specular highlight
  belongs to the light source, so the iris slides under it rather than dragging it
  around. It is only visible when something dark is beneath it, which is correct.
- **Sizing (tuned at the bench 2026-07-28):** eye radius 74 px — *larger than the screen
  is tall*, so it crops top and bottom and reads as a close-up of an eye rather than a
  ball drawn on a panel. Iris **36 px**, grown proportionally more than the eye, inside a
  **4 px black limbal ring**. Pupil **10–18 px**. Catchlight 18 px.
  Iris and pupil are specified by **area**: the last +15% is radius × √1.15 = ×1.072
  (34→36, 9→10, 17→18), not ×1.15, which would have been a 32% bigger iris.
  ⚠ The ring is the outermost thing that moves, so **two constants derive from it, not
  from the iris**: how far the gaze may travel (or a full tilt pushes the ring past the
  edge of the sclera) and the erase radius (or a moving iris leaves a crescent of ring
  behind it). Both are `IRIS_OUTER` in the sketch — change the ring and they follow.

*Why the eyeball is the default:* it is the only view that reads correctly when nothing
is happening. A scope with no sound is a flat line; a console with no traffic is empty;
an eye at rest is still a face.

### 4.2 Oscilloscope — sound (green) — **BUILT 2026-07-28**

240 columns = 240 samples = **30 ms per sweep at 8 kHz.** That was not chosen: the mic's
DMA descriptor is 240 frames, so one sweep is exactly one descriptor. The sweep length
fell out of the audio path.

- **Triggered sweep.** Free-running, the trace is an unreadable smear. An **armed** rising
  edge (fall below zero to arm, then cross the level going up) locks the sweep to the same
  point of the same cycle every frame, and a whistled note stands still. Two blocks of PCM
  are kept, not one, because the trigger needs slack to slide within. The trigger level
  rides the tier's `ambient` mean — the one place that statistic is the right one. *(Built.)*
- **Auto-gain**, fast attack / slow release, on the **peak** rather than the ambient mean:
  a scope clips on peaks, so gain off a mean lets a transient run off the top of the
  screen. A floor keeps a quiet room showing a living trace instead of a flat line. *(Built.)*
- **Peak-hold ghost** in dim green behind the live trace, decaying ~15%/frame ≈ a 1 s tail,
  so a transient leaves a visible mark instead of flashing past between 10 Hz frames.
  It also does double duty as the **dirty-band bound** — see below. *(Built.)*
- **The border carries what the waveform cannot say for itself:** it flashes pale on a
  transient the `@LAT94` log actually recorded (watching the tier's own `transients()`
  counter, not a second threshold in the renderer — a private threshold would flash on a
  different set of events and quietly lie about the log), and goes **amber while we are the
  noise** (§3.3). *(Built.)*

**Its rendering strategy is the opposite of the eye's, on purpose.** The eye paints
straight to the panel and touches only what moved, because almost nothing moves. A scope
changes in every column of every frame, so "only what changed" buys nothing — the eye's
rule would degenerate into ~500 separate spans, and it is the per-span `setAddrWindow`,
not the pixels, that costs. So the scope opens **one** address window over the band of
rows that can have changed and streams it row by row from a 480-byte row buffer. A quiet
room deflects into a thin band and pushes ~20 rows; a loud one pushes the lot. **Loud
sound costs more than quiet sound, which is the right way round.**

⚠ **Two things the bench contradicted, both worth keeping:**

1. **The canvas §6 budgets does not fit.** The first build allocated the 64,800 B
   full-screen `GFXcanvas16` §6 costs out "against 249 KB free heap" — and it **failed on
   hardware**: `[scope] canvas alloc failed`. The static free-heap figure is not the number
   that matters. By the time this view can be opened, WiFi, BLE (Bluedroid), ESP-NOW and the
   36 KB globe canvas are all up, and what is missing is a **contiguous** 65 KB block, not
   65 KB. Streaming rows needs 480 bytes and cannot fail — a better property than fitting
   today. **§6's canvas line should be treated as refuted for any view that needs one.**
2. **A live text readout cost ~20 ms per frame — nearly as much as the entire waveform.**
   `Adafruit_GFX::drawChar` with a background colour writes every pixel of the glyph cell
   *individually*: 40 separate `setAddrWindow`+1-pixel transactions per character, ~1,700
   for a 42-character line. The readout is gone. Its only text is a static label painted
   once **on entry, from the key handler** — a key press can afford 20 ms, a render frame
   cannot. Everything live is in the picture already: the trace is the level, the ghost is
   recent peaks, the border is the transient and the self-noise gate.

### 4.3 Console — neighbors

Largely exists already (the `LOG_LINES` ring). Promoted to a full-screen view:

- One line per received toot: source name, type, RSSI, age.
- **A per-neighbour RSSI sparkline** — this is the `@LAT97` histogram the node already
  keeps, finally visible: you can watch a node get closer.
- Salience fires on **novelty**, not volume: a *new* neighbour, a neighbour returning
  after a gap, or one going silent. Routine 2 s HELLOs are well-explained (`conf` high)
  and must never seize the screen, or the console will own it permanently.

### 4.4 Constellation — place *(proposed, not in the brief)*

Each visible BSSID a star; brightness = RSSI; position = a stable hash of the BSSID so
the same room always draws the same sky. Salience fires when the **set changes** —
which is to say, when you carry the node somewhere else. It is the cheapest possible
rendering of "I am somewhere new."

### 4.5 Interoception — always on, never a view

Battery and die temperature are ambient, not events: they colour the other views rather
than claiming the screen. Battery drives a thin arc; below ~15% it is allowed to raise
salience and take the screen once, with a plain low-power message. Heat feeds the
fleet's STATUS temperature field.

---

## 5. Key map — this changes existing bindings

`t` is currently *next node / cycle comm target*. The brief reassigns it, so:

| Key | Was | Now | State |
|---|---|---|---|
| `t` | next node / cycle target | **toggle REPRESENTOR ↔ globe views** | ✅ built |
| `n` | toggle console pane | next node / cycle comm target | ✅ built |
| SPACE | toggle console pane | unchanged | ✅ built |
| arrows, `±`, ENTER | globe navigation | ignored while the face holds the screen | ✅ built |
| ENTER | cycle globes | cycle globes *(in globe mode)* / cycle views *(in representor)* | ✅ built |
| `1` / `2` | — | force eyeball / oscilloscope | ✅ built |
| `3`–`5` | — | force console / constellation / … | ⏳ needs those views |
| `0` | — | release the pin, return to automatic arbitration | ⏳ needs S1 |

A **pin** matters more than it looks: without it there is no way to *watch* a quiet
sense, because by definition the arbiter only shows you the loud one.

---

## 6. What the spare 4 MB is actually for

An honest accounting, because the premise of the question deserves one.

**These views do not need the extra flash.** They are RAM-bound and cheap:

| Item | Cost | Against |
|---|---|---|
| ~~Full-screen canvas 240×135×16bpp~~ | ~~64,800 B~~ | ❌ **refuted on hardware — see §4.2** |
| Scope row buffer (what it actually uses) | 480 B | — |
| Scope sample + ghost + trace buffers | ~1.7 KB | — |
| Arbiter state (6 modalities) | < 1 KB | — |
| The whole scope view, measured | **1.6 KB flash + 2.2 KB RAM** | app at 40%, 1.87 MB free |

All of it fits in what the node has **today**, with no repartition. If the goal is only
the display modes, the 4 MB stays unused and that is fine.

**Here is what the 4 MB genuinely unlocks — and it serves the primary hypothesis.**

The acoustic tier currently logs *when* the loudest transient crossed a threshold. Two
nodes comparing threshold-crossing timestamps is a weak measurement: the threshold fires
at different points on the waveform depending on distance and gain, so the timing error
is the shape of the sound, not the geometry.

The strong version is **cross-correlation**: both nodes keep the raw audio around the
event, and the companion slides one against the other to find the true time offset. That
is real TDoA, and it needs raw samples kept on the node until they can be pulled.

At 8 kHz / 16-bit mono, **1 s = 16 KB**. A repartitioned 3.6 MB filesystem holds ~230
seconds of audio — call it **450 half-second snippets** around transients, a
`@LAT94`-adjacent ring buffer that survives reboot and gets pulled over the existing
`TTDB_REQ` path.

That is the honest answer: *the extra space buys the fleet a real acoustic ranging
measurement, not a prettier screen.*

### Proposed partition (only if the snippet buffer is wanted)

| Partition | Now (huge_app) | Proposed |
|---|---|---|
| app0 | 3 MB | 4 MB |
| spiffs | 917 KB @ **0x310000** | ~3.6 MB @ **new offset** |
| unallocated | **4 MB** | 0 |

⚠ Changing this **requires updating the offset in
[scripts/Upload-Cardputer-FS.ps1](scripts/Upload-Cardputer-FS.ps1)**. Flashing the FS at
the wrong offset for the scheme is the documented failure that boots a node to an empty
globe with the app otherwise looking fine (CLAUDE.md). Treat the partition change and
the script change as one atomic commit.

---

## 7. Build order

Each phase ends with something that runs and is verified, and **every phase re-checks
the loop budget (§3.4)** — that is the gate this node has already failed once.

**Phase S0 — the self-noise gate.** *(half done)* Mark acoustic samples taken while our own
speaker sounds as fully explained; stop logging them as transients.
✅ The **display** half is in: `toneI2S()` sets `gToneUntilMs`, and the face's sound term is
suppressed while it holds, so the node's own notes cannot dilate its own pupil.
⏳ **Still owed: the `@LAT94` log itself.** Our voice is still eligible to be logged as a
transient, which is a live data-quality bug in the tier the TDoA idea rests on.
*Done when:* a `CMD_BEEP` produces **no** `@LAT94` transient, while a clap still does.

**Phase S1 — the arbiter, headless.** Per-modality `(sal, conf)`, EPS ranking,
hysteresis. No new rendering; print the winning modality to serial.
*Done when:* tilting, clapping, and a neighbour rejoining each print the right winner,
and the winner decays back to `idle` within ~3 s.

**Phase S2 — eyeball + scope.** The two views in the brief, plus gyro saccades.
✅ **The eyeball is built, flashed and measured (2026-07-28)**, ahead of the arbiter rather
than after it — because the resting face is the one view that needs no arbiter to be correct.
Gaze, gyro saccade, tap + idle blink, and pupil dilation from a two-term stand-in for EPS.
Measured on hardware: **worst render 24 ms** (budget ≤25 — the blink-open sclera repaint, the
most expensive recurring frame), **worst loop pass 37 ms** (budget ≤40; it was 104 ms),
`ping --node cardputer_1` DELIVERED on attempt 1.
**Re-measured 2026-07-28 after the +15% iris/pupil: worst render 22 ms** — the bigger iris made
the face *cheaper*, because the expensive frame is the sclera repaint and it now skips a larger
disc. Growing the iris buys frame budget; it does not spend it. No canvas, no filesystem, only the crescent
the iris vacated, and **zero pixels written** when the deck is held still.
**The budget is a live constraint, not a note in a doc:** adding the limbal ring pushed the
blink-open frame to **26 ms** and broke it. The fix was ordering, not cutting the feature —
work the geometry out *before* painting anything, so the sclera repaint skips the disc the
iris is about to cover. **Never paint a pixel you are about to paint over.** Back to 24 ms.
**The profiler had to be fixed before any of that could be believed:** it printed the *last*
render, which for a paint-only-what-changed view is almost always 0 ms. Printing the **worst**
render per window immediately exposed a 47 ms entry frame that the old number hid.
⚠ **Known and left there:** entering the face costs **36 ms**, over the ≤25 ms per-frame budget.
It happens once, on entry or on `t`. Two measured fixes already went in (stop painting half the
panel twice; batch ~150 spans under one SPI transaction instead of one each); the remaining cost
is per-row `setAddrWindow` overhead. The loop pass the mesh actually feels stayed at 37 ms, so
the next spend belongs elsewhere.
✅ **The oscilloscope is built, flashed and measured (2026-07-28)** — triggered sweep,
peak auto-gain, peak-hold ghost, and a border that flashes on the tier's own logged
transients and goes amber on our own voice. Measured on hardware: **worst render 21 ms**
(budget ≤25; that is a full-height loud frame — a quiet one pushes ~20 rows), **worst loop
pass 28 ms** (budget ≤40), `ping --node cardputer_1` DELIVERED on attempt 1. Reached with
`2`, or ENTER to cycle; `1` returns to the eye. Two doc-contradicting findings are recorded
in §4.2 — the canvas that will not allocate, and the 20 ms text readout.
**The panel SPI was raised 24 → 40 MHz** to pay for it. Pixel data is the one cost that
cannot be optimized away, and the library's 24 MHz default was leaving 40% of the bus
unused; the ST7789V2 is specified far above this. Everything got faster: **the eye's worst
render fell 22 → 18 ms and its entry frame 36 → 31 ms**, so the known over-budget entry
frame in the warning below is now 31 ms.
⏳ Still owed: a fleet-wide `verify` (measured with `ping` on the cabled node, not the full
sync-bound run).
⚠ **Not verifiable from the laptop — needs eyes at the bench**, same class as the gaze axes:
that the trace, ghost, trigger and border colours actually look right, and that **40 MHz
leaves the panel clean**. If pixels ever tear or speckle, `setSPISpeed(40000000)` in
`setup()` is the first suspect, not a renderer.
⚠ **Seen once, not reproduced:** the first boot after one flash hit a `Guru Meditation
(stack canary, ipc0)` during BLE init and rebooted cleanly. Four subsequent resets were
clean. Noted rather than chased — it is in BLE bring-up, not the scope.
⚠ **Unverifiable from the laptop — needs eyes at the bench:** whether the gaze runs downhill
and whether the axes are swapped. Deliberately exposed as `EYE_GAZE_X` / `EYE_GAZE_Y` /
`EYE_SWAP_AXES` at the top of the eyeball block; this board's IMU already lied once about its
own I2C address, so its axis convention is not something to bury in the renderer.

**Phase S3 — console + key map.** Promote the log ring, add RSSI sparklines, move `t`.
*Done when:* a neighbour power-cycling seizes the screen exactly once, and routine
HELLOs never do.

**Phase S4 — interoception + heat.** Battery arc, low-power alert, and fill the fleet's
STATUS temperature field.
*Done when:* `companion.py monitor` shows a real temperature for `cardputer_1` instead
of `0`.

**Phase S5 — constellation.** The place view.
*Done when:* carrying the node between two rooms visibly changes the sky and raises
salience.

**Phase S6 — the snippet buffer *(optional; needs the repartition)*.** Raw audio around
transients, pulled over `TTDB_REQ`.
*Done when:* two nodes hear one clap and the companion recovers a time offset by
cross-correlation that agrees with their known separation.

---

## 8. Open questions for antfriend

1. **Repartition, or not?** Everything except S6 fits in the current layout. S6 is the
   one that serves the hypothesis. Do you want the 4 MB claimed now (one careful commit,
   with the FS script), later, or never?
2. **`t` reassignment** — is the table in §5 right? `n` is currently the console-pane
   toggle and would move.
3. ~~**Is the eyeball the right resting face**, or should the node rest on the scope?~~
   **Answered 2026-07-28: the eyeball, and it was built first.** Open follow-up: it is now
   the *only* face, so it is also the boot view — say if the globe should stay the power-up
   view instead, with the face reached by `t`.
4. **Constellation and interoception** are my additions, not yours. Worth building, or
   noise?
5. **Should the representor be the boot default on this node only**, or should the
   T-Deck eventually get it too? (It has no IMU and no mic, so it would only ever show
   the console — probably not.)
