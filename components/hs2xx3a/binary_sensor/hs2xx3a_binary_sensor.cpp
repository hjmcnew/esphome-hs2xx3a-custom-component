#include "esphome/core/log.h"
#include "hs2xx3a_binary_sensor.h"

namespace esphome {
namespace hs2xx3a_binary_sensor {

static const char *TAG = "hs2xx3a_binary_sensor.binary_sensor";

void HS2xx3ABinarySensor::setup() {
    
}
  
void HS2xx3ABinarySensor::update() {

}

void HS2xx3ABinarySensor::dump_config() {
    ESP_LOGCONFIG(TAG, "Custom binary sensor");
}

} //namespace hs2xx3a_binary_sensor
} //namespace esphome