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
x_m: 21.23
y_m: 0.00
sigma_m: 3.37
anchor_chain: [v4a_bridge]
embedding_rev: 4
flip_resolved: false   # one anchor; T-Deck GPS resolves
stress_m: 0.48
conf: 0.68
touched: 2026-07-13T22:32:17Z

---

@BELIEF:POSITION @node(tdeck_1)
frame: relative   # anchor v4a_bridge at origin, 2nd node on +x, 3rd at +y
x_m: 16.05
y_m: 0.67
sigma_m: 18.42
anchor_chain: [v4a_bridge]
embedding_rev: 4
flip_resolved: false   # one anchor; T-Deck GPS resolves
stress_m: 0.48
conf: 0.52
touched: 2026-07-13T22:32:17Z

---

@BELIEF:POSITION @node(v4a_bridge)
frame: relative   # anchor v4a_bridge at origin, 2nd node on +x, 3rd at +y
x_m: 0.00
y_m: 0.00
sigma_m: 253.45
anchor_chain: [v4a_bridge]
embedding_rev: 4
flip_resolved: false   # one anchor; T-Deck GPS resolves
stress_m: 0.48
conf: 0.58
touched: 2026-07-13T22:32:17Z

---

@BELIEF:POSITION @node(v4b_relay)
frame: relative   # anchor v4a_bridge at origin, 2nd node on +x, 3rd at +y
x_m: 17.30
y_m: 8.43
sigma_m: 283.04
anchor_chain: [v4a_bridge]
embedding_rev: 4
flip_resolved: false   # one anchor; T-Deck GPS resolves
stress_m: 0.48
conf: 0.55
touched: 2026-07-13T22:32:17Z
