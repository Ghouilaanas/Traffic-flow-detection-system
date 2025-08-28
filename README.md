# 🛣️ Traffic-flow-detection-system
This project is a prototype real-time traffic monitoring system that uses an STM32 microcontroller for vehicle counting, data logging, and traffic analysis.


## 📄 Description
This project implements a prototype real-time traffic monitoring system built on an STM32 microcontroller, designed to provide accurate vehicle flow counting and data logging for intelligent transportation applications.

The prototype uses traffic detection sensors (infrared, ultrasonic, or other suitable types) strategically placed along the road or entry/exit points to detect and count passing vehicles. The STM32 acts as the central processing unit, handling sensor data acquisition, signal processing, and event management in real-time.

In this project, the traffic monitoring system was implemented using **two different hardware approaches** to demonstrate the versatility of the prototype. The first approach uses an STM32F407 Discovery board paired with an ultrasonic sensor and an I²C LCD display to visualize traffic information in real time, providing a comprehensive narrative walkthrough of the system’s real-time vehicle detection, data logging, and traffic analysis capabilities. The second approach uses an STM32 Nucleo board with an infrared sensor and an I²C LCD display, offering a simpler demo to illustrate the core functionality of vehicle counting and data acquisition. Both setups showcase the system’s adaptability to different microcontrollers and sensor types while maintaining accurate traffic monitoring performance.

## ⚙️ Tools and Technologies

### 1. STM32F407 Discovery + Ultrasonic Sensor Approach 
- **Microcontroller**: STM32F407 Discovery
- **Sensor**: Ultrasonic distance sensor
- **Display**: I²C LCD
- **Programming**: Arduino IDE
- **Demo**: Narrative walkthrough video demonstrating system operation
  
### 2. STM32 Nucleo + Infrared Sensor Approach
- **Microcontroller**: STM32 Nucleo
- **Sensor** : Infrared (IR) sensor
- **Display**: I²C LCD
- **Programming**: STM32CubeIDE / HAL library
- **Demo**: Simple demonstration video showcasing vehicle counting
---
