# Orchestrator Consolidated Knowledge (Dream-Cycle seed)

This file is authored by `companion.py reconcile`: it folds each node's
self-reported `@LAT99` sync log into one master view with provenance, the minimal
first instance of the Dream Cycle (TTDB-RFC-0007) — episodic node records
consolidated into a semantic master record.

```mmpdb
db_id: orchestrator-consolidated-001
db_name: Orchestrator Consolidated Knowledge
coord_increment:
  lat: 1
  lon: 1
collision_policy: reject
timestamp_kind: unix
umwelt:
  umwelt_id: orchestrator
  role: companion-orchestrator
  scope: master
```

```cursor
lat: 0
lon: 0
```

---

@LAT99LON1 | created:1782170699 | updated:1782170699 | relates:knows@LAT0LON0

**CONSOLIDATED-SYNC** id:1 t_ms:1782170699715 agree:yes confirmed_by:k10_1,laptop,v4a_bridge
- k10_1: recv_ms:103890 offset_ms:1782170595825
- laptop: recv_ms:1782170699715 offset_ms:0
- v4a_bridge: recv_ms:20222 offset_ms:1782170679493

---

@LAT99LON2 | created:1782170835 | updated:1782170835 | relates:knows@LAT0LON0

**CONSOLIDATED-SYNC** id:2 t_ms:1782170835676 agree:yes confirmed_by:k10_1,laptop,v4a_bridge
- k10_1: recv_ms:239291 offset_ms:1782170596385
- laptop: recv_ms:1782170835676 offset_ms:0
- v4a_bridge: recv_ms:155661 offset_ms:1782170680015

---

@LAT99LON3 | created:1782429925 | updated:1782429925 | relates:knows@LAT0LON0

**CONSOLIDATED-SYNC** id:3 t_ms:1782429925125 agree:yes confirmed_by:k10_1,laptop,v4a_bridge,v4b_relay
- k10_1: recv_ms:1293165 offset_ms:1782428631960
- laptop: recv_ms:1782429925125 offset_ms:0
- v4a_bridge: recv_ms:2795865 offset_ms:1782427129260
- v4b_relay: recv_ms:45601 offset_ms:1782429879524

---

@LAT99LON4 | created:1782430029 | updated:1782430029 | relates:knows@LAT0LON0

**CONSOLIDATED-SYNC** id:4 t_ms:1782430029108 agree:yes confirmed_by:k10_1,laptop,v4a_bridge,v4b_relay
- k10_1: recv_ms:1397154 offset_ms:1782428631954
- laptop: recv_ms:1782430029108 offset_ms:0
- v4a_bridge: recv_ms:56335 offset_ms:1782429972773
- v4b_relay: recv_ms:149590 offset_ms:1782429879518
