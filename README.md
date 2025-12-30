# This repo is no longer actively maintained as of 2025-12-30.

## This repo houses development of a custom component to support the LeapMMW HS2xx3A series of mmWave sensors, also branded as the DFRobot sen0395.

### Installation:
 * Download the [leapmmw_sensor.h](https://raw.githubusercontent.com/hjmcnew/esphome-hs2xx3a-custom-component/release/leapmmw_sensor.h) file into your esphome configuration directory
 * Include the following in the YAML configuration for your ESP board:
   ```
   substitutions:
     device_name: leapmmw
 
     # This will vary based on your board
     uart_tx_pin: TX
     
     # This will vary based on your board
     uart_rx_pin: RX
     
     # This will vary based on your board
     gpio_pin: D0
     
     # (Optional) Path to the leapmmw_sensor.h file relative to your esphome configuration directory.
     # header_file: leapmmw_sensor.h
   
   packages:
     remote_package:
       url: https://github.com/hjmcnew/esphome-hs2xx3a-custom-component
       ref: release
       files: [packages/uart.yml, packages/leapmmw_sensor.yml]
       # For additional debugging replace the above line with:
       # files: [packages/uart_debug.yml, packages/leapmmw_sensor.yml]
   ```
