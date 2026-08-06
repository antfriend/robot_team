# A Fleet That Maps Itself

*What a team of six ESP32 robots is trying to prove, and what it still doesn't know.*

## The premise

`robot_team` is a small mesh of microcontrollers — three Heltec V4 boards, two
handheld consoles, one parked percept node — coordinated by a laptop. There is
no cloud model on any device, and no neural inference of any kind. Each robot's
entire mind is a single markdown file on its flash: coordinate-addressed
records, typed edges between them, and per-record epistemic weights
(`conf`idence, `sal`ience, revision count). The firmware is a generic
interpreter; the file gives it identity. Sensing means quantizing a reading to a
coordinate, finding the nearest record, and following the edges out of it.

That design choice buys one thing above all: **everything the fleet believes is
legible.** You can read a robot's mind in a text editor, diff it across a week,
and see exactly which observation moved which belief and by how much. It also
imposes a discipline — a system that cannot hide behind a learned weight matrix
has to state its uncertainty in the open, and be wrong in public.

## The claim under test

The fleet exists to test one hypothesis: **a mesh can infer its own physical
arrangement from the semantic structure of what it perceives.** Two nodes whose
percept streams reference the same external things — the same WiFi access
points, the same acoustic transients, correlated link quality — must occupy
overlapping regions of space. Umwelt overlap implies spatial proximity. The
degree and character of that overlap is a distance measurement in disguise.

Position stops being a configured constant and becomes an emergent belief,
revisable like any other. The claim is pinned to three falsifiable legs, so it
can fail cleanly:

1. **Verified** — position beliefs land within their own stated `sigma` of
   ground truth, scored against a roaming GPS handheld that is never an input to
   the inference, only its judge.
2. **Actuated** — the resulting proximity beliefs choose each link's transport
   automatically, ESP-NOW when the belief says in-range, LoRa when it doesn't,
   with hysteresis and no configuration. Belief becomes behavior.
3. **Rendered** — the emergent map is drawn from the same file lineage on a
   laptop browser and on a 320×240 handheld screen. The fleet draws a live
   picture of itself.

And it carries an explicit falsifier: an ablation comparing plain radio ranging
against ranging plus semantic evidence. If the semantic layer adds nothing, the
hypothesis is dead and the document says so.

## Where it actually stands

The floor is built and verified on hardware. Signed 250-byte frames survive the
air with selective retransmit; the fleet agrees on a clock; nodes write their own
memory files at runtime and the laptop consolidates them back; a self-organizing
beat keeps six boards phase-locked within about ten milliseconds. From six
independent pairwise distance beliefs the fleet solved a consistent 2D layout of
itself with a worst pair-fit error of four centimetres — on a bench.

Then it went outside, and the interesting thing happened: **it failed.** In a
garden run, 2.4 GHz signal strength over-ranged real distances by two to seven
times and decorrelated from them almost entirely. Foliage and shadowing, not
noise — no amount of averaging fixes a systematically wrong physics. A second
radio tier (Bluetooth) did not rescue it, and that was the useful part of the
result: both tiers measure *amplitude*, so both fail the same way at the same
time. The failure was informative precisely because it was shared.

That redirected the whole program toward evidence that isn't amplitude. Shared
WiFi access points give a coarse but honest **upper bound** — "these two cannot
be eight hundred metres apart, they see the same six routers" — a term that caps
an over-confident estimate rather than refining it. A microphone on one handheld
now timestamps impulsive transients against the fleet clock, which is a
time-of-arrival measurement: sound travels 343 m/s, so ten milliseconds of clock
agreement is worth about three and a half metres, bounded by clock quality
instead of by leaves.

Recent work has been quieter and structural: a fleet-owned timeline that survives
the laptop's absence, so timestamps stay comparable when nobody is watching; and
change-triggered logging, where a sensor window that says the same thing as the
last one writes nothing but is counted, so a lane records what happened instead
of recording uptime. That compression came out at 15.5× on one lane and 6× on
another, and — the part that mattered — an independent re-derivation on the
laptop reproduced the device's beliefs exactly, field for field. Compressing the
evidence did not change the conclusions drawn from it.

## What we don't know

**Does non-amplitude evidence actually recover the geometry?** Unanswered. The
tiers exist and log real data; the consolidator that turns two nodes' transient
timestamps into a hyperbola of possible positions has not been written. One
handclap heard by two microphones is the cheapest version of this experiment, and
only one node currently has a microphone.

**What is the honest threshold for "the neighbourhood changed"?** The entity tier
needs a measured drift threshold, not a chosen one — and the first attempt at
measuring it was thrown out because the archived data spanned five different
timelines running backwards. The replacement declares its four acceptance gates
in code *before* the data exists, which is the only order in which a gate means
anything. It needs eight uninterrupted hours to run.

**How do you observe a system whose correctness depends on being left alone?**
Run-length logging only works across long undisturbed stretches, and every
diagnostic connection resets the board that is being diagnosed. The first
measurement returned a compression ratio of exactly 1.0 — not a firmware fault
but an artifact of the instrument. It came right when the node ran 43 minutes on
battery with the laptop unplugged entirely. That is a small, concrete instance of
a general problem in autonomous systems, and it will recur.

**What should a memory do when it's full?** Every lane has a cap, and pruning is
destructive by design: some beliefs are a pure function of evidence, so deleting
the evidence returns them to baseline. The current answer is to write a boundary
record carrying both the tally and the conclusions, so a belief standing on
vanished evidence is visible rather than merely diminished. Whether that is the
right policy for every lane is undecided.

## Where the experiments go next

Three lines are live. Measure the entity-drift threshold on a long quiet run and
find out whether a naive per-window comparison is even a usable change signal, or
whether it needs a stable-core notion of "the neighbourhood I usually see."
Write the acoustic time-difference consolidator and get a first non-amplitude
distance constraint out of a clap. Then un-gate the long-range radio and let the
position beliefs *drive* something — walk a node out of range and watch the mesh
fall back before delivery dies, which is the moment inference becomes behavior
and the second proof leg either holds or doesn't.

The general pattern underneath — infer latent geometry from co-occurrence
structure in perception — is not specific to radios or robots. This fleet is a
cheap, auditable, and deliberately falsifiable place to find out whether it
works.
