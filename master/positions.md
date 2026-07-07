# Fleet Position Beliefs (semantic positioning SP2)

Authored by `companion.py positions`: the @BELIEF:PROXIMITY pair matrix embedded
into 2D by weighted spring relaxation, then canonicalized — anchor at the
origin, second node on +x, third node at +y. The frame is RELATIVE (one anchor
fixes translation only): rotation and reflection are unresolved until a second
anchor (the T-Deck GPS) pins them, so flip_resolved stays false. sigma_m folds
each node's incident edge residuals + pair sigmas; stress is the fit's honesty.

---

@BELIEF:POSITION @node(k10_1)
frame: relative   # anchor v4a_bridge at origin, 2nd node on +x, 3rd at +y
x_m: 3.10
y_m: -0.00
sigma_m: 0.45
anchor_chain: [v4a_bridge]
embedding_rev: 1
flip_resolved: false   # one anchor; T-Deck GPS resolves
stress_m: 0.01
conf: 0.75
touched: 2026-07-07T23:08:55Z

---

@BELIEF:POSITION @node(tdeck_1)
frame: relative   # anchor v4a_bridge at origin, 2nd node on +x, 3rd at +y
x_m: 0.43
y_m: 2.85
sigma_m: 0.47
anchor_chain: [v4a_bridge]
embedding_rev: 1
flip_resolved: false   # one anchor; T-Deck GPS resolves
stress_m: 0.01
conf: 0.63
touched: 2026-07-07T23:08:55Z

---

@BELIEF:POSITION @node(v4a_bridge)
frame: relative   # anchor v4a_bridge at origin, 2nd node on +x, 3rd at +y
x_m: 0.00
y_m: -0.00
sigma_m: 0.52
anchor_chain: [v4a_bridge]
embedding_rev: 1
flip_resolved: false   # one anchor; T-Deck GPS resolves
stress_m: 0.01
conf: 0.65
touched: 2026-07-07T23:08:55Z

---

@BELIEF:POSITION @node(v4b_relay)
frame: relative   # anchor v4a_bridge at origin, 2nd node on +x, 3rd at +y
x_m: 3.34
y_m: 2.15
sigma_m: 0.49
anchor_chain: [v4a_bridge]
embedding_rev: 1
flip_resolved: false   # one anchor; T-Deck GPS resolves
stress_m: 0.01
conf: 0.57
touched: 2026-07-07T23:08:55Z
