# Fleet Position Beliefs (semantic positioning SP2)

Authored by `companion.py positions`: the @BELIEF:PROXIMITY pair matrix embedded
into 2D by weighted spring relaxation, then canonicalized — frame ORIGIN at
v4a_bridge, second node on +x, third node at +y.

⚠ THE FRAME IS RELATIVE AND `pose_ceiling` IS 0 OF 4. Every record here is a SHAPE
claim: `sigma_m` measures how well the shape fits its evidence and says nothing
about where that shape sits. Common information cannot reach translation (2),
rotation (1) or reflection (1) — spec §0.1 — and only a GPS fix pins any of them
(`companion.py anchor`).

⚠ v4a_bridge is the frame ORIGIN, NOT an anchor. Before Draft 0.3 these records
carried `anchor_chain: [v4a_bridge]` off a CONFIGURED coordinate, which asserted the
pose and then reported the assertion back as a result (spec §1.2). A configured
constant is not a measurement, so `anchor_chain` is now empty until GPS says
otherwise.

sigma_m folds each node's incident edge residuals + pair sigmas; stress is the fit's
honesty.

---

@BELIEF:POSITION @node(cardputer_1) | sid:5a76e5dd
frame: relative   # origin v4a_bridge, 2nd node on +x, 3rd at +y
x_m: 2.12
y_m: 0.00
sigma_m: 4.04   # SHAPE uncertainty only (spec 0.2)
pose_ceiling: 0   # of 4 DoF: no GPS ties: this is a SHAPE, not a map
dof_pinned: { translation: none, rotation: none, reflection: none }
frame_origin: v4a_bridge   # ORIGIN, not an anchor (spec 1.2)
anchor_chain: []   # no GPS tie: nothing pins pose
embedding_rev: 7
flip_resolved: false   # T-Deck GPS resolves; see pose_ceiling
stress_m: 2.04
conf: 0.45
touched: 2026-08-11T16:08:10Z

---

@BELIEF:POSITION @node(tdeck_1) | sid:dbdf7fb2
frame: relative   # origin v4a_bridge, 2nd node on +x, 3rd at +y
x_m: -0.87
y_m: 0.02
sigma_m: 7.53   # SHAPE uncertainty only (spec 0.2)
pose_ceiling: 0   # of 4 DoF: no GPS ties: this is a SHAPE, not a map
dof_pinned: { translation: none, rotation: none, reflection: none }
frame_origin: v4a_bridge   # ORIGIN, not an anchor (spec 1.2)
anchor_chain: []   # no GPS tie: nothing pins pose
embedding_rev: 7
flip_resolved: false   # T-Deck GPS resolves; see pose_ceiling
stress_m: 2.04
conf: 0.44
touched: 2026-08-11T16:08:10Z

---

@BELIEF:POSITION @node(v4a_bridge) | sid:03c5ab25
frame: relative   # origin v4a_bridge, 2nd node on +x, 3rd at +y
x_m: 0.00
y_m: 0.00
sigma_m: 8.87   # SHAPE uncertainty only (spec 0.2)
pose_ceiling: 0   # of 4 DoF: no GPS ties: this is a SHAPE, not a map
dof_pinned: { translation: none, rotation: none, reflection: none }
frame_origin: v4a_bridge   # ORIGIN, not an anchor (spec 1.2)
anchor_chain: []   # no GPS tie: nothing pins pose
embedding_rev: 7
flip_resolved: false   # T-Deck GPS resolves; see pose_ceiling
stress_m: 2.04
conf: 0.44
touched: 2026-08-11T16:08:10Z

---

@BELIEF:POSITION @node(v4b_relay) | sid:02c5a992
frame: relative   # origin v4a_bridge, 2nd node on +x, 3rd at +y
x_m: 22.99
y_m: -0.14
sigma_m: 12.99   # SHAPE uncertainty only (spec 0.2)
pose_ceiling: 0   # of 4 DoF: no GPS ties: this is a SHAPE, not a map
dof_pinned: { translation: none, rotation: none, reflection: none }
frame_origin: v4a_bridge   # ORIGIN, not an anchor (spec 1.2)
anchor_chain: []   # no GPS tie: nothing pins pose
embedding_rev: 7
flip_resolved: false   # T-Deck GPS resolves; see pose_ceiling
stress_m: 2.04
conf: 0.45
touched: 2026-08-11T16:08:10Z

---

@BELIEF:POSITION @node(v4c_edge) | sid:01c5a7ff
frame: relative   # origin v4a_bridge, 2nd node on +x, 3rd at +y
x_m: -8.60
y_m: 0.35
sigma_m: 8.96   # SHAPE uncertainty only (spec 0.2)
pose_ceiling: 0   # of 4 DoF: no GPS ties: this is a SHAPE, not a map
dof_pinned: { translation: none, rotation: none, reflection: none }
frame_origin: v4a_bridge   # ORIGIN, not an anchor (spec 1.2)
anchor_chain: []   # no GPS tie: nothing pins pose
embedding_rev: 7
flip_resolved: false   # T-Deck GPS resolves; see pose_ceiling
stress_m: 2.04
conf: 0.45
touched: 2026-08-11T16:08:10Z
