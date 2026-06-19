#include "Agent32.h"
#include <math.h>
#include <string.h>

void Agent32::sense() {
  reading_count_ = 0;
  uint32_t now = millis();
  for (uint8_t i = 0; i < sensor_count_; ++i) {
    if (!sensors_[i] || !sensors_[i]->read) continue;
    readings_[reading_count_].sensor = sensors_[i];
    readings_[reading_count_].value = sensors_[i]->read();
    readings_[reading_count_].timestamp = now;
    ++reading_count_;
  }
  ++cycle_id_;
}

void Agent32::reason() {
  matched_ = false;
  action_count_ = 0;

  // Apply a navigation requested on the previous cycle.
  if (has_pending_) {
    cur_lat_ = pending_lat_;
    cur_lon_ = pending_lon_;
    has_pending_ = false;
  }
  if (!db_ || db_->recordCount() == 0) return;

  // 1. Quantize the snapshot into a target coordinate.
  float tlat = 0.0f, tlon = 0.0f;
  for (uint8_t i = 0; i < reading_count_; ++i) {
    const A32Sensor* s = readings_[i].sensor;
    if (!s) continue;
    float span = s->range_max - s->range_min;
    float norm = (span != 0.0f) ? (readings_[i].value - s->range_min) / span : 0.0f;
    if (norm < 0.0f) norm = 0.0f;
    if (norm > 1.0f) norm = 1.0f;
    tlat += norm * (float)s->map_lat;
    tlon += norm * (float)s->map_lon;
  }
  int16_t target_lat = (int16_t)lroundf(tlat);
  int16_t target_lon = (int16_t)lroundf(tlon);

  // 2. Nearest record.
  int idx = db_->nearest(target_lat, target_lon);
  if (idx < 0) return;
  const TtdbRecord& r = db_->record(idx);

  // 3. Move the cursor only if the match is within threshold.
  long dl = (long)r.lat - target_lat;
  long dn = (long)r.lon - target_lon;
  if (dl * dl + dn * dn > (long)match_threshold_ * match_threshold_) return;
  cur_lat_ = r.lat;
  cur_lon_ = r.lon;
  matched_ = true;

  // 4. Read the matched node's typed edges and select actions.
  TtdbEdge edges[A32_MAX_EDGES];
  uint8_t n = db_->edgesAt(idx, edges, A32_MAX_EDGES);
  for (uint8_t k = 0; k < n; ++k) {
    if (strcmp(edges[k].type, "triggers") == 0) {
      int a = findActuator(edges[k].target_lat, edges[k].target_lon);
      if (a >= 0) enqueue((uint8_t)a, 1.0f, 0);
    } else if (strcmp(edges[k].type, "navigates_to") == 0) {
      pending_lat_ = edges[k].target_lat;
      pending_lon_ = edges[k].target_lon;
      has_pending_ = true;
    }
    // `logs` and other edge types are observation side-channels (section 5).
  }
  // Apply inhibits after triggers so order in the edge list does not matter.
  for (uint8_t k = 0; k < n; ++k) {
    if (strcmp(edges[k].type, "inhibits") == 0) {
      int a = findActuator(edges[k].target_lat, edges[k].target_lon);
      if (a >= 0) cancelActions((uint8_t)a);
    }
  }
}

void Agent32::act() {
  // For each actuator named in the queue, run the highest-priority action once
  // (lower priority number wins; ties break on insertion order).
  for (uint8_t i = 0; i < action_count_; ++i) {
    bool best = true;
    for (uint8_t j = 0; j < action_count_; ++j) {
      if (j == i || queue_[j].actuator != queue_[i].actuator) continue;
      if (queue_[j].priority < queue_[i].priority ||
          (queue_[j].priority == queue_[i].priority && j < i)) {
        best = false;
        break;
      }
    }
    if (best) {
      const A32Actuator* a = actuators_[queue_[i].actuator];
      if (a && a->exec) a->exec(queue_[i].value);
    }
  }
  action_count_ = 0;
}

int Agent32::findActuator(int16_t lat, int16_t lon) const {
  for (uint8_t i = 0; i < actuator_count_; ++i)
    if (actuators_[i] && actuators_[i]->map_lat == lat &&
        actuators_[i]->map_lon == lon)
      return i;
  return -1;
}

void Agent32::enqueue(uint8_t actuator, float value, uint8_t priority) {
  if (action_count_ < A32_MAX_ACTIONS)
    queue_[action_count_++] = {actuator, value, priority};
}

void Agent32::cancelActions(uint8_t actuator) {
  uint8_t w = 0;
  for (uint8_t i = 0; i < action_count_; ++i)
    if (queue_[i].actuator != actuator) queue_[w++] = queue_[i];
  action_count_ = w;
}
