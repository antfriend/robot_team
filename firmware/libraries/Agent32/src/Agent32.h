// Agent32.h — deterministic sense-reason-act loop over a TTDB (A32-RFC-0003).
//
// No inference. Each cycle:
//   SENSE  — sample registered sensors into a snapshot.
//   REASON — quantize the snapshot to a target (lat,lon), find the nearest TTDB
//            record, move the cursor there (if within threshold), and read its
//            typed edges: `triggers` enqueues an action, `navigates_to` sets the
//            next cursor, `inhibits` cancels a queued action.
//   ACT    — drive the actuators the queued actions name, by priority.
//
// Routing model: a sensor maps its normalized reading onto a direction vector
// (map_lat,map_lon); summed over sensors that gives the target coordinate. An
// actuator declares the (map_lat,map_lon) it sits at, so a `triggers@LATxLONy`
// edge fires the actuator whose coordinate matches the edge target. This is the
// symmetric, fully-deterministic binding A32-RFC-0003 section 3 leaves to the
// implementation.
#pragma once
#include <Arduino.h>
#include <TTDB.h>

#ifndef A32_MAX_SENSORS
#define A32_MAX_SENSORS 16
#endif
#ifndef A32_MAX_ACTUATORS
#define A32_MAX_ACTUATORS 16
#endif
#ifndef A32_MAX_EDGES
#define A32_MAX_EDGES 16
#endif
#ifndef A32_MAX_ACTIONS
#define A32_MAX_ACTIONS 16
#endif

typedef float (*A32SensorReadFn)();
typedef void (*A32ActuatorExecFn)(float value);

struct A32Sensor {
  const char* name;
  A32SensorReadFn read;
  int16_t map_lat;   // direction this sensor pushes the target lat at full scale
  int16_t map_lon;   // direction this sensor pushes the target lon at full scale
  float range_min;
  float range_max;
};

struct A32Actuator {
  const char* name;
  A32ActuatorExecFn exec;
  int16_t map_lat;   // a triggers@LATxLONy edge at this coord fires this actuator
  int16_t map_lon;
};

struct A32Reading {
  const A32Sensor* sensor;
  float value;
  uint32_t timestamp;
};

class Agent32 {
 public:
  explicit Agent32(Ttdb* db = nullptr) : db_(db) {}
  void setDb(Ttdb* db) { db_ = db; }

  void registerSensor(const A32Sensor* s) {
    if (sensor_count_ < A32_MAX_SENSORS) sensors_[sensor_count_++] = s;
  }
  void registerActuator(const A32Actuator* a) {
    if (actuator_count_ < A32_MAX_ACTUATORS) actuators_[actuator_count_++] = a;
  }
  void setInterval(uint32_t ms) { interval_ms_ = ms; }
  uint32_t intervalMs() const { return interval_ms_; }
  // Max grid distance for a reading to "match" a record; beyond it the cursor
  // holds position (A32-RFC-0003 section 3.2 no_match_policy).
  void setMatchThreshold(int16_t t) { match_threshold_ = t; }

  void sense();
  void reason();
  void act();

  int16_t cursorLat() const { return cur_lat_; }
  int16_t cursorLon() const { return cur_lon_; }
  bool matchedThisCycle() const { return matched_; }
  uint8_t readingCount() const { return reading_count_; }
  const A32Reading& reading(uint8_t i) const { return readings_[i]; }

 private:
  struct Action { uint8_t actuator; float value; uint8_t priority; };

  int findActuator(int16_t lat, int16_t lon) const;
  void enqueue(uint8_t actuator, float value, uint8_t priority);
  void cancelActions(uint8_t actuator);

  Ttdb* db_;
  const A32Sensor* sensors_[A32_MAX_SENSORS];
  const A32Actuator* actuators_[A32_MAX_ACTUATORS];
  A32Reading readings_[A32_MAX_SENSORS];
  Action queue_[A32_MAX_ACTIONS];
  uint8_t sensor_count_ = 0;
  uint8_t actuator_count_ = 0;
  uint8_t reading_count_ = 0;
  uint8_t action_count_ = 0;
  uint32_t interval_ms_ = 1000;
  uint32_t cycle_id_ = 0;
  int16_t cur_lat_ = 0;
  int16_t cur_lon_ = 0;
  int16_t pending_lat_ = 0;
  int16_t pending_lon_ = 0;
  bool has_pending_ = false;
  int16_t match_threshold_ = 64;
  bool matched_ = false;
};
