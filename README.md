# 🚗 Smart Parking System  

## 📖 Table of Contents  
- [Overview](#-overview)  
- [Technologies Used](#-technologies-used)  
- [Features](#-features)  
- [Circuit Diagram](#-circuit-diagram)  
- [Setup & Installation](#-setup--installation)  
- [License](#-license)  

## 🔍 Overview  
An IoT-enabled smart parking system that detects parking slot availability using ultrasonic sensors and controls entry using a servo motor. The data is sent to ThingSpeak for real-time cloud monitoring.  

## 🛠️ Technologies Used  
- **Microcontroller:** ESP32  
- **Sensors:** Ultrasonic Sensors  
- **Actuators:** Servo Motor  
- **Cloud:** ThingSpeak  
- **Software:** Arduino IDE

## Circuit Diagram
- [For Gate](circuit/gate.png)
- [For slot](circuit/slots.png)

## 🚀 Features  
✅ Monitors parking slot availability in real-time  
✅ Controls entry gate using a servo motor  
✅ Sends live updates to ThingSpeak for cloud monitoring  

## 🔧 Setup & Installation  
1. Connect ultrasonic sensors and servo motor to ESP32.  
2. Upload the provided code using Arduino IDE.  
3. Connect to Wi-Fi and observe real-time updates on ThingSpeak.