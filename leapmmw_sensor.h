#include "esphome.h"
#include <string>
#include "esphome/core/helpers.h"

#define PUBLISH_NUMBER(sensor, valueString) (id(sensor).publish_state(parse_number<float>(valueString).value()))
#define PUBLISH_SWITCH(sensor, onOff) (id(sensor).publish_state(onOff))

void publishTarget(int idx, float dist, float snr) {
  switch(idx) {
    case 1:
      id(target_1_distance_m).publish_state(dist);
      id(target_1_SNR).publish_state(snr);
      break;

    case 2:
      id(target_2_distance_m).publish_state(dist);
      id(target_2_SNR).publish_state(snr);
      break;

    case 3:
      id(target_3_distance_m).publish_state(dist);
      id(target_3_SNR).publish_state(snr);
      break;

    case 4:
      id(target_4_distance_m).publish_state(dist);
      id(target_4_SNR).publish_state(snr);
      break;

    case 5:
    case 6:
    case 7:
    case 8:
      break;
    default:
      ESP_LOGD("custom", "Invalid target sensor number: %d", idx);
      break;
  }
};

static void clearTargets () {
  for(int i = 1 ; i < 9; i++) publishTarget(i, 0.0, 0.0);
}

class leapmmw : public Component, public UARTDevice {

 public:
  leapmmw(UARTComponent *parent) : UARTDevice(parent) {}
  
  void setup() override {
    //
  }

  void getmmwConf(std::string mmwparam) {
    mmwparam = mmwparam + "\r";
    write_array(std::vector<unsigned char>(mmwparam.begin(), mmwparam.end()));
  }

  int readline(int readch, char *buffer, int len)
  {
    static int pos = 0;
    int rpos;

    if (readch > 0) {
      switch (readch) {
        case '\n': // Ignore new-lines
          break;
        case '\r': // Return on CR
          rpos = pos;
          pos = 0;  // Reset position index ready for next time
          return rpos;
        default:
          if (pos < len-1) {
            buffer[pos++] = readch;
            buffer[pos] = 0;
          }
      }
    }
    // No end of line has been found, so return -1.
    return -1;
  }
  std::string getline;

  void loop() override {
    const int max_line_length = 40;
    static char buffer[max_line_length];

    while (available()) {
      if (id(mmwave_sensor).state == 0 && id(num_targets).state > 0) {
        id(num_targets).publish_state(0);
        clearTargets();
      }
      if(readline(read(), buffer, max_line_length) >= 4) {
        std::string line = buffer;

        if (line.substr(0, 18) == "leapMMW:/>$JYBSS,0" && id(num_targets).state > 0) {
          id(num_targets).publish_state(0);
          clearTargets();
        }
        if (line.substr(0, 6) == "$JYRPO") {
          std::string vline = line.substr(6);
          std::vector<std::string> v;    
          for(int i = 0; i < vline.length(); i++) {
              if(vline[i] == ',') {
                  v.push_back("");
              } else {
                  v.back() += vline[i];
              }
          }
          id(num_targets).publish_state(parse_number<float>(v[0]).value());
          if (id(show_target_stats).state == 1) {
            publishTarget(stoi(v[1]), parse_number<float>(v[2]).value(), parse_number<float>(v[4]).value());
            // zero null targets
            for(int i = parse_number<int>(v[0]).value() +1 ; i < 9; i++) publishTarget(i, 0.0, 0.0);
          }
        }
        if (line.substr(0, 6) == "$JYRPO" && id(mmwave_sensor).state == 0) {
          PUBLISH_SWITCH(mmwave_sensor, 1);
        }

        // compare last line
        if (line.substr(0, 8) == "Response") {
          // ESP_LOGD("custom", "Found Response - line is: %s", line.c_str());
          // ESP_LOGD("custom", "Found Response - lastline is: %s", getline.c_str());

          // leapMMW:/>getSensitivity
          if (getline.substr(0, 24) == "leapMMW:/>getSensitivity" || getline.substr(0, 14) == "getSensitivity") {
            std::string getSensitivity = line.substr(9, 1);
            if (getSensitivity.empty()) {
              ESP_LOGD("custom", "Did not find a value for getSensitivity");
            } else {
              // ESP_LOGD("custom", "The value of getSensitivity is: %f", parse_number<float>(getSensitivity).value());
              PUBLISH_NUMBER(sensitivity, getSensitivity);
            }
          }

          // leapMMW:/>getRange
          if (getline.substr(0, 18) == "leapMMW:/>getRange" || getline.substr(0, 8) == "getRange") {
            std::string getRange = line.substr(15, 4);
            if (getRange.empty()) {
              ESP_LOGD("custom", "Did not find a value for getRange");
            } else {
              // ESP_LOGD("custom", "The value of getRange is: %f", parse_number<float>(getRange).value());
              PUBLISH_NUMBER(distance, getRange);
            }
          }

          // leapMMW:/>getLatency
          if (getline.substr(0, 20) == "leapMMW:/>getLatency" || getline.substr(0, 10) == "getLatency") {
            std::string getLatency = line.substr(15, 2);
            if (getLatency.empty()) {
              ESP_LOGD("custom", "Did not find a value for getLatency");
            } else {
              // ESP_LOGD("custom", "The value of getLatency is: %f", parse_number<float>(getLatency).value());
              PUBLISH_NUMBER(latency, getLatency);
            }
          }

          // leapMMW:/>getLedMode
          if (getline.substr(0, 20) == "leapMMW:/>getLedMode" || getline.substr(0, 10) == "getLedMode") {
            std::string getLedMode = line.substr(11, 1);
            if (getLedMode.empty()) {
              ESP_LOGD("custom", "Did not find a value for getLedMode");
            } else {
              int led_state = parse_number<int>(getLedMode).value();
              // ESP_LOGD("custom", "The value of getLedMode is: %i", led_state);
              if (led_state == 0 || led_state == 1) {
                PUBLISH_SWITCH(led, 1 - led_state);
              }
            }
          }
        }
        if (line.substr(0, 4) == "Done") {
          // ESP_LOGD("custom", "Found Done - line is: %s", line.c_str());
          // ESP_LOGD("custom", "Found Done - lastline is: %s", getline.c_str());
          // leapMMW:/>sensorStop
          if (getline.substr(0, 20) == "leapMMW:/>sensorStop") {
            // ESP_LOGD("custom", "sensorStop completed successfully");
            PUBLISH_SWITCH(mmwave_sensor, 0);
          }

          // leapMMW:/>sensorStart
          if (getline.substr(0, 21) == "leapMMW:/>sensorStart") {
            // ESP_LOGD("custom", "sensorStart completed successfully");
            PUBLISH_SWITCH(mmwave_sensor, 1);
          }
        }
        getline = buffer; 
      }
    }
  }
};
