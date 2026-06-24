# Fleet Belief (authored by companion push)

This object is re-authored by `companion.py push` from the consolidated fleet sync
knowledge and pushed back to a node (TTN-RFC-0009) — the propagation half of the
Dream Cycle (TTDB-RFC-0007). The node stores it as `/belief.md` and records the
adoption in its own TTDB.

```mmpdb
db_id: fleet-belief-001
db_name: Fleet Belief
coord_increment:
  lat: 1
  lon: 1
collision_policy: reject
timestamp_kind: unix
umwelt:
  umwelt_id: orchestrator
  role: companion-orchestrator
  scope: belief
```

```cursor
lat: 0
lon: 0
```

---

@LAT0LON0 | created:1782170835 | updated:1782170835 | relates:knows@LAT1LON0,directs@LAT0LON1

**BELIEF** summary:fleet-observed-2-sync-events latest_t_ms:1782170835676

---

@LAT0LON1 | created:1782170835 | updated:1782170835 | relates:directed_by@LAT0LON0

**DIRECTIVE** sense_interval_ms:300

---

@LAT1LON0 | created:1782170699 | updated:1782170699 | relates:derives@LAT0LON0

**BELIEF-SYNC** id:1 t_ms:1782170699715

---

@LAT2LON0 | created:1782170835 | updated:1782170835 | relates:derives@LAT0LON0

**BELIEF-SYNC** id:2 t_ms:1782170835676
