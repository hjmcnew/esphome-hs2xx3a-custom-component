#include "esphome/core/log.h"
#include "hs2xx3a.h"

namespace esphome {
namespace hs2xx3a {

static const char *TAG = "hs2xx3a.component";

void HS2xx3AComponent::setup() {

}

void HS2xx3AComponent::loop() {

}

void HS2xx3AComponent::dump_config(){
    ESP_LOGCONFIG(TAG, "HS2xx3A component");
}

}  // namespace hs2xx3a
}  // namespace esphome