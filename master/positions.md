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
x_m: 16.25
y_m: -0.00
sigma_m: 51.28
anchor_chain: [v4a_bridge]
embedding_rev: 2
flip_resolved: false   # one anchor; T-Deck GPS resolves
stress_m: 0.90
conf: 0.58
touched: 2026-07-10T17:49:16Z

---

@BELIEF:POSITION @node(tdeck_1)
frame: relative   # anchor v4a_bridge at origin, 2nd node on +x, 3rd at +y
x_m: 33.61
y_m: 31.87
sigma_m: 61.96
anchor_chain: [v4a_bridge]
embedding_rev: 2
flip_resolved: false   # one anchor; T-Deck GPS resolves
stress_m: 0.90
conf: 0.55
touched: 2026-07-10T17:49:16Z

---

@BELIEF:POSITION @node(v4a_bridge)
frame: relative   # anchor v4a_bridge at origin, 2nd node on +x, 3rd at +y
x_m: 0.00
y_m: -0.00
sigma_m: 57.72
anchor_chain: [v4a_bridge]
embedding_rev: 2
flip_resolved: false   # one anchor; T-Deck GPS resolves
stress_m: 0.90
conf: 0.55
touched: 2026-07-10T17:49:16Z

---

@BELIEF:POSITION @node(v4b_relay)
frame: relative   # anchor v4a_bridge at origin, 2nd node on +x, 3rd at +y
x_m: 6.83
y_m: 34.78
sigma_m: 53.15
anchor_chain: [v4a_bridge]
embedding_rev: 2
flip_resolved: false   # one anchor; T-Deck GPS resolves
stress_m: 0.90
conf: 0.56
touched: 2026-07-10T17:49:16Z
