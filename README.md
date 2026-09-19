# OreX — Mine Safety Rover

<div align="center">
  <img src="assets/sih-logo.svg" alt="Smart India Hackathon Logo" width="700" />
</div>

OreX is a smart mine safety rover designed by team OreX. We are a team of 6 first year students across vaious branches. The rover helps improve mine worker safety by monitoring hazardous gases, detecting nearby anomalies, and enabling remote or autonomous rover navigation in risky underground environments. OreX Rover acts as the first responder and goes into the mine first before any human worker to ensure safety.

This repository contains the embedded control system for the rover, obstacle detection by raspberry pi and other basic information about the project. The system can operate in autonomous mode for safe pathing or manual mode through a lightweight web UI.

<div align="center">
  <img src="assets/our-logo.svg" alt="OreX Logo" width="360" />
</div>

> Replace the placeholder logo in [assets/our-logo.svg](assets/our-logo.svg) with your team’s final branding asset when ready.

---
## Quick Start
Skip directly to [this](gettingstarted.md) file to set up the prototype immediately.
It is however recommended that you read the entire file to get a grasp of our vision for OreX.

## Problem Statement

Mining environments are hazardous due to:

- toxic gas accumulation such as methane and carbon monoxide
- poor visibility and limited access paths
- risk of collisions with walls, debris, or unstable terrain
- difficult real-time monitoring for human workers and supervisors

OreX addresses these challenges with a compact rover that continuously navigates through the mines and senses the environment for any potential risks before it escalates.

---

## Project Vision

To build an affordable, compact, and smart mine-safety rover that can:

- detect dangerous gases early
- measure environmental values (temperature, humidity)
- identify nearby anomalies
- navigate safely in autonomous mode
- hand over control to workers when needed
- provide live telemetry through a web dashboard
- reduce human exposure to hazardous conditions

---

## Core Features

- Gas monitoring using various sensors
- Environmental sensing (eg temperature and humidity)
- Obstacle detection and avoidance
- Autonomous rover movement with collision avoidance
- Manual drive control from base station
- Wi-Fi, bluetooth, LoRa and wired communications for connectivity at all situations
- Battery backup for navigating through tight spaces
- Live JSON telemetry for monitoring and debugging

---

## Hardware Architecture

We built a simple and cost effective proof of concept prototype that uses an ESP32-based rover platform with the following components:

- ESP32-S3 N16R8
- Two DC geared motors with left/right drive configuration
- L298N motor driver
- MQ2 gas sensor
- MQ4 gas sensor
- MQ7 gas sensor
- DHT11 temperature and humidity sensor
- Ultrasonic distance sensor
- 3 x 18650 batteries
- TP 4056 charger


## Planned Hardware For Next Version
We have the foundation for the actual prototype, which will use:

- Sensors - NDIR methane sensor
            - Electrochemical CO sensor
            - Electrochemical H2S sensor
            - Electrochemical/galvanic O2 sensor
            - NDIR CO2 sensor
            - DHT22 Temperature Sensor (used in the prototype can be improved)
            - 6-axis IMU (Inertial Measurement Unit)
            - Ultrasonic Sensor 
            - PIR Sensor
            - Barometric Sensor 
- Microcontroller - ESP32S3 N16R8
- Single Board Computer - Raspberry Pi 5
- Motor Mechanics - Motor Driver 
                  - Track Style Chassis 
                  - high torque motors 
                  - Servo Motor
                  - Suspension
- Camera - IR + Thermal + Night vision 
- Communication - Wired
                - LoRa (Backup)
                - Bluetooth (Backup)
                - Wifi 2.4G (Backup)

The rover acts as a local access-point server and exposes a simple dashboard at the network address 192.168.4.1.

---

## System Behavior

The rover operates in three primary states:

1. Auto mode
   - continuously reads sensor data
   - checks for obstacle and anomalies
   - avoids collisions by reversing and steering away from barriers
   - drives forward when the path is clear

2. Manual mode
   - accepts directional commands such as forward, backward, left, and right
   - supports direct operator control from base station

3. Stop mode
   - halts all movement immediately
   - used as a safe fallback state

4. SOS mode
   - finds unconcious mine workers
   - leads them to the nearest exit
   - allows for voice-voice communication between mine workers and supervisors
   
---

## Repository Structure

```text
OreX/
├── ESP32/
│   ├── include/
│   ├── lib/
│   ├── src/
│   │   └── main.cpp
│   ├── test/
│   └── platformio.ini
├── README.md
└── .git/
```

The primary logic for the rover is implemented in [ESP32/src/main.cpp](ESP32/src/main.cpp), and the build configuration is defined in [ESP32/platformio.ini](ESP32/platformio.ini).

---

## Software Stack

- PlatformIO
- Arduino framework for ESP32
- Embedded HTTP server for telemetry and control
- *Languages:* C++, HTML, CSS, JavaScript, Python, SQL
- *Front end:* React, Tailwind CSS
- *Charts and maps:* Chart.js for live gas graphs, Leaflet for the cave map
- *Backend:* FastAPI (Python)
- *Database:* PostgreSQL (Supabase)
- *Live data:* MQTT / WebSockets to stream sensor readings from the rover
- *Video feed:* MJPEG / WebRTC via MediaMTX
- *AI analysis:* Python (pandas, scikit-learn) for detecting abnormal gas levels
- *Report generation:* LLM API to write incident reports, ReportLab for PDF
- *Alerts:* Twilio / email / Telegram bot to notify authorities and media
- *Hosting:* Vercel (front end), Render or AWS (backend)
- *Tools:* Git and GitHub, Postman
- *Libraries:* Adafruit DHT sensor library

---
## Getting Started
Go to [Getting Started](ESP32/gettingstarted.md) to set up the prototype


## Sensor Interpretation

- MQ2: general combustible gas and smoke detection
- MQ4: methane and natural gas detection
- MQ7: carbon monoxide detection
- DHT11: ambient temperature and relative humidity
- Ultrasonic sensor: object distance in centimeters

These readings provide situational awareness for mine environments where hazards are often invisible to the human eye.



## Roadmap

Planned improvements for the next iteration include:

- camera-based obstacle recognition
- detecting whether a person is concious or not using image processing and large language models
- using local LLMs to detect anomalies and inform local authorities about potential hazards
- live cloud / dashboard integration
- GPS or localization support
- stronger gas threshold alerting
- industrial-grade sensor calibration
- LoRa or mesh communication for remote mine monitoring
- autonomous path planning for complex terrains

---

## Why This Project Matters

OreX is built by us around the idea that safer mining operations begin with better sensing and smarter machine assistance. By combining gas monitoring, anomaly detection, edge AI, advanced communication systems, the rover offers a practical solution for improving underground safety, especially in difficult or low-visibility conditions.

---

## Contributors

This project is being developed for the Smart India Hackathon initiative for SIH26039.


---

## Demo Photos

OreX in action

<div align="center">
  <img src="assets/demo/demo-1.svg" alt="Demo Photo 1" width="900" />
  <br /><br />
  <img src="assets/demo/demo-2.svg" alt="Demo Photo 2" width="900" />
  <br /><br />
  <img src="assets/demo/demo-3.svg" alt="Demo Photo 3" width="900" />
</div>

> Replace the SVG placeholders in the [assets/demo](assets/demo) folder with real photos of the rover, testing setup, or field demonstration.

---

## Project Status

The repository currently contains the core ESP32 firmware for the rover prototype, including sensor reading, autonomous navigation logic, and a browser-based control interface.

This is an active prototype and is continuously being extended with additional sensing, communication, and industrial deployment features.
