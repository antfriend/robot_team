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

**CONSOLIDATED-SYNC** id:1 t_ms:1782170699715 agree:yes confirmed_by:k10_1,laptop
- k10_1: recv_ms:103890 offset_ms:1782170595825
- laptop: recv_ms:1782170699715 offset_ms:0

---

@LAT99LON2 | created:1782170835 | updated:1782170835 | relates:knows@LAT0LON0

**CONSOLIDATED-SYNC** id:2 t_ms:1782170835676 agree:yes confirmed_by:k10_1,laptop
- k10_1: recv_ms:239291 offset_ms:1782170596385
- laptop: recv_ms:1782170835676 offset_ms:0
