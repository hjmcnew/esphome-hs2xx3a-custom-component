## This repo houses development of a custome component to support the LeapMMW HS2xx3A series of mmWave sensors, also branded as the DFRobot sen0395.

There are two ways to install:

### Option 1:
 * Download the zip file from releases in the sidebar
 * Extract it into your esphome configuration directory
 * Include the following in the YAML configuration for your ESP board:
   ```
   substitutions:
     device_name: leapmmw
     uart_tx_pin: TX
     uart_rx_pin: RX
     gpio_pin: D0
     header_file: leapmmw_sensor.h
   packages:
     leapmmw_sensor: !include packages/leapmmw_sensor.yml
   ```

### Option 2:
 * Download the leapmmw_sensor.h file into your esphome configuration directory
 * Include the following in the YAML configuration for your ESP board:
   ```
   substitutions:
     device_name: leapmmw
     uart_tx_pin: TX
     uart_rx_pin: RX
     gpio_pin: D0
     header_file: leapmmw_sensor.h
   packages:
     remote_package:
       url: https://github.com/hjmcnew/esphome-hs2xx3a-custom-component
       ref: release
       file: packages/leapmmw_sensor.yml
   ```
