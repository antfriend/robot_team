# Fleet Position Beliefs (semantic positioning SP2)

Authored by `companion.py positions`: the @BELIEF:PROXIMITY pair matrix embedded
into 2D by weighted spring relaxation, then canonicalized — anchor at the
origin, second node on +x, third node at +y. The frame is RELATIVE (one anchor
fixes translation only): rotation and reflection are unresolved until a second
anchor (the T-Deck GPS) pins them, so flip_resolved stays false. sigma_m folds
each node's incident edge residuals + pair sigmas; stress is the fit's honesty.

---

@BELIEF:POSITION @node(cardputer_1)
frame: relative   # anchor v4a_bridge at origin, 2nd node on +x, 3rd at +y
x_m: 2.12
y_m: 0.00
sigma_m: 4.04
anchor_chain: [v4a_bridge]
embedding_rev: 5
flip_resolved: false   # one anchor; T-Deck GPS resolves
stress_m: 2.04
conf: 0.45
touched: 2026-07-31T23:01:04Z

---

@BELIEF:POSITION @node(tdeck_1)
frame: relative   # anchor v4a_bridge at origin, 2nd node on +x, 3rd at +y
x_m: -0.87
y_m: 0.02
sigma_m: 7.53
anchor_chain: [v4a_bridge]
embedding_rev: 5
flip_resolved: false   # one anchor; T-Deck GPS resolves
stress_m: 2.04
conf: 0.44
touched: 2026-07-31T23:01:04Z

---

@BELIEF:POSITION @node(v4a_bridge)
frame: relative   # anchor v4a_bridge at origin, 2nd node on +x, 3rd at +y
x_m: 0.00
y_m: 0.00
sigma_m: 8.87
anchor_chain: [v4a_bridge]
embedding_rev: 5
flip_resolved: false   # one anchor; T-Deck GPS resolves
stress_m: 2.04
conf: 0.44
touched: 2026-07-31T23:01:04Z

---

@BELIEF:POSITION @node(v4b_relay)
frame: relative   # anchor v4a_bridge at origin, 2nd node on +x, 3rd at +y
x_m: 22.99
y_m: -0.14
sigma_m: 12.99
anchor_chain: [v4a_bridge]
embedding_rev: 5
flip_resolved: false   # one anchor; T-Deck GPS resolves
stress_m: 2.04
conf: 0.45
touched: 2026-07-31T23:01:04Z

---

@BELIEF:POSITION @node(v4c_edge)
frame: relative   # anchor v4a_bridge at origin, 2nd node on +x, 3rd at +y
x_m: -8.60
y_m: 0.35
sigma_m: 8.96
anchor_chain: [v4a_bridge]
embedding_rev: 5
flip_resolved: false   # one anchor; T-Deck GPS resolves
stress_m: 2.04
conf: 0.45
touched: 2026-07-31T23:01:04Z
