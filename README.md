# 🛣️ Traffic-flow-detection-system
This project is a prototype real-time traffic monitoring system that uses an STM32 microcontroller for vehicle counting, data logging, and traffic analysis.


## 📄 Description
This project implements a prototype real-time traffic monitoring system built on an STM32 microcontroller, designed to provide accurate vehicle flow counting and data logging for intelligent transportation applications.

The prototype uses traffic detection sensors (infrared, ultrasonic, or other suitable types) strategically placed along the road or entry/exit points to detect and count passing vehicles. The STM32 acts as the central processing unit, handling sensor data acquisition, signal processing, and event management in real-time.

In this project, the traffic monitoring system was implemented using two different hardware approaches to demonstrate the versatility of the prototype. The first approach uses an STM32F407 Discovery board paired with an ultrasonic sensor, providing a comprehensive narrative walkthrough of the system’s real-time vehicle detection, data logging, and traffic analysis capabilities. The second approach uses an STM32 Nucleo board with an infrared sensor, offering a simpler demo to illustrate the core functionality of vehicle counting and data acquisition. Both setups showcase the system’s adaptability to different microcontrollers and sensor types while maintaining accurate traffic monitoring performance.

## ⚙️ Tools and Technologies

### Hardware 
- STM32 Nucleo-L476RG microcontroller board
- NodeMCU ESP8266 microcontroller board
- LoRa E32 (868T20D) Module with 868 MHz SMA Antenna
- 12V Switched-Mode Power Supply
- 4-Relay Module
  
### Software
- **STM32CubeIDE** : An integrated development environment (IDE) for STM32 microcontrollers, providing code editing, compilation, debugging, and peripheral configuration tools.
- **Arduino IDE** : A user-friendly integrated development environment for programming Arduino boards, supporting code writing, uploading, and serial monitoring.
- **C (STM32CubeIDE), C++ (Arduino IDE)** : programming languages.
- **Proteus ISIS** : A software tool for designing and simulating electronic circuits and embedded systems.
---
