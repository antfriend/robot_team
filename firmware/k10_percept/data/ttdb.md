# K10 Percept Node TTDB

```mmpdb
db_id: k10-percept-001
db_name: K10 Percept Node
coord_increment:
  lat: 1
  lon: 1
collision_policy: reject
timestamp_kind: unix
umwelt:
  umwelt_id: k10-percept
  role: percept-capture
  perspective: first-person-sensor
  scope: local-cluster
  constraints:
    - no-lora
    - espnow-default
    - no-ble          # the 2.x DFRobot core cannot run BLE + WiFi concurrently, so
                      # @LAT97 stays empty on this node: it is HEARD, it does not hear
    - no-button       # nothing on this board is reachable by a hand; the screen is
                      # changed only by CMD_SET_VIEW from a console
    - no-battery-sense # runs off USB; intero reports bat 0 mV / pct 255 (unknown)
  senses:
    - ambient_temp    # AHT20 -> the agent's sense/reason/act cursor (@LAT10LON0)
    - wifi_entity     # duty-cycled BSSID scan -> @LAT96
    - tilt            # SC7A20H accelerometer -> @LAT95 still|moving, @LAT93 transitions
    - acoustic        # I2S microphone -> @LAT94 ambient level + transient timestamps
  globe:
    frame: sensor-grid
    origin: "@LAT0LON0"
    mapping: "ambient sensors quantized onto the lat/lon knowledge grid"
cursor_policy:
  max_preview_chars: 256
  max_nodes: 64
typed_edges:
  enabled: true
  syntax: "type@LATxLONy"
librarian:
  enabled: false
  primitive_queries: []
```

```cursor
lat: 0
lon: 0
```

---

@LAT0LON0 | created:1750000000 | updated:1750000000 | relates:navigates_to@LAT10LON0

Home node. Idle perception state. The agent rests here until a sensor reading
quantizes elsewhere on the grid.

---

@LAT10LON0 | created:1750000000 | updated:1750000000 | relates:triggers@LAT10LON0,logs@LAT0LON0

Warm ambient region. Reached when the temperature sensor reads into the upper
band. `triggers` fires the local indicator; `logs` records the observation.
