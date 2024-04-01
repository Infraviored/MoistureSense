# MoistureSense

The MoistureSense Project is a highly efficient and cost-effective system designed to monitor soil moisture levels for plants. Utilizing capacitive moisture sensors sourced from AliExpress, this project integrates with a Wemos D1 microcontroller to deliver timely and accurate soil humidity readings. It's ideal for anyone looking to maintain optimal watering schedules for their plants, ensuring they are never over or under-watered. The system can operate as a standalone battery-powered unit or be connected to a 24-volt power supply for enhanced functionality, including automatic watering through a solenoid valve.

<div style="display:flex; justify-content:space-between; align-items:center;">
  <img src="https://github.com/Infraviored/MoistureSense/blob/main/models/renders/battery.png?raw=true" alt="Battery Edition" width="33%"/>
  <img src="https://github.com/Infraviored/MoistureSense/blob/main/models/renders/valve.png?raw=true" alt="Valve Edition" width="20.5%"/>
  <img src="https://github.com/Infraviored/MoistureSense/blob/main/models/renders/rear.png?raw=true" alt="Rear View" width="33%"/>
</div>

## Overview

This project offers a smart solution to monitor soil moisture levels, leveraging capacitive moisture sensors and a Wemos D1 microcontroller. It is designed to operate with minimal power consumption, remaining in deep sleep mode and waking once daily to measure and report soil moisture levels. By connecting to Wi-Fi and publishing moisture levels over MQTT, it integrates smoothly into smart home systems or remote monitoring setups. This README details the hardware components, software configuration, and setup instructions for both the battery-powered and wired versions of the Moisture Sensor Project.


## Hardware

### Electrical Components
- **Capacitive Moisture Sensors:** Sourced from AliExpress, these sensors provide accurate moisture level readings of the soil.
- **Wemos D1 Mini Microcontroller:** Controls the moisture sensor and manages Wi-Fi connectivity and MQTT messaging.
- **CR32 Lithium Battery (Standalone Version):** Powers the standalone unit, ensuring long-term operation without the need for external power sources.
- **Solenoid Valve (Wired Version):** Allows for automatic watering based on soil moisture level readings.
- **PCBs:** Custom PCB designs for both versions are available for manufacturing at JL PCB, tailored to facilitate easy assembly and deployment.

### Assembly
1. **PCB Assembly:** Solder the Wemos D1 Mini and the moisture sensor to the corresponding PCB. Ensure to use the appropriate version for your setup (battery-powered or wired).
2. **Battery Installation (Standalone Version):** Insert the CR32 lithium battery according to the markings on the PCB.
3. **Power Supply Connection (Wired Version):** Connect the 24-volt power supply to the PCB, ensuring correct polarity.
4. **Solenoid Valve Connection (Wired Version):** Attach the solenoid valve to the designated connectors on the PCB for automatic watering functionality.

## Features and Functionality

- **Soil Moisture Monitoring:** Accurately measures soil moisture levels, allowing for optimal watering schedules.
- **Energy Efficient:** Remains in deep sleep mode to conserve power, waking only to take readings and transmit data.
- **MQTT Integration:** Seamlessly publishes soil moisture data over MQTT for easy integration with smart home systems or remote monitoring platforms.
- **Automatic Watering (Wired Version):** The solenoid valve can be automatically controlled based on soil moisture levels to water plants as needed.

## Support

For support, questions, or feedback regarding the Moisture Sensor Project, please open an issue in the GitHub repository or contact the project maintainers directly.

### Links

- Moisture Sensor: [AliExpress Moisture Sensor](https://de.aliexpress.com/item/1005005962452779.html?spm=a2g0o.productlist.main.3.6c92lf4glf4g4m)
- D1 Mini: [AliExpress D1 Mini](https://de.aliexpress.com/item/32965631778.html?spm=a2g0o.productlist.main.3.7b892bb6kXaTYH)
