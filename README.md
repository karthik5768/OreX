# OreX — Mine Safety Rover

<div align="center">
  <img src="assets/sih-logo.svg" alt="Smart India Hackathon Logo" width="700" />
</div>

OreX is a smart mine safety rover designed for the Smart India Hackathon problem statement SIH26039. The project focuses on improving mine worker safety by monitoring hazardous gases, detecting nearby obstacles, and enabling remote or autonomous rover navigation in risky underground environments.

This repository contains the embedded control system for the rover, built around an ESP32 microcontroller and a set of environmental and motion sensors. The system can operate in autonomous mode for safe pathing or manual mode through a lightweight web interface.

<div align="center">
  <img src="assets/our-logo.svg" alt="OreX Logo" width="360" />
</div>

> Replace the placeholder logo in [assets/our-logo.svg](assets/our-logo.svg) with your team’s final branding asset when ready.

---

## Problem Statement

Mining environments are hazardous due to:

- toxic gas accumulation such as methane and carbon monoxide
- poor visibility and limited access paths
- risk of collisions with walls, debris, or unstable terrain
- difficult real-time monitoring for workers and supervisors

OreX addresses these challenges with a compact rover that continuously senses the environment and supports safe navigation inside confined mine-like spaces.

---

## Project Vision

To build an affordable, compact, and smart mine-safety rover that can:

- detect dangerous gases early
- measure temperature and humidity
- identify nearby obstacles
- navigate safely in autonomous mode
- provide live telemetry through a web dashboard
- reduce human exposure to hazardous conditions

---

## Core Features

- Gas monitoring using MQ2, MQ4, and MQ7 sensors
- Environmental sensing using DHT11 for temperature and humidity
- Obstacle detection using an ultrasonic sensor
- Autonomous rover movement with collision avoidance
- Manual drive control through an HTTP-based command interface
- Wi-Fi access point mode for direct rover connectivity
- Live JSON telemetry for monitoring and debugging

---

## Hardware Architecture

The current implementation uses an ESP32-based rover platform with the following components:

- ESP32-S3 DevKit M-1
- Two DC geared motors with left/right drive configuration
- Motor control via GPIO PWM outputs
- MQ2 gas sensor
- MQ4 gas sensor
- MQ7 gas sensor
- DHT11 temperature and humidity sensor
- Ultrasonic distance sensor
- Battery-powered rover chassis

The rover acts as a local access-point server and exposes a simple dashboard at the network address 192.168.4.1.

---

## System Behavior

The rover operates in three primary states:

1. Auto mode
   - continuously reads sensor data
   - checks obstacle distance
   - avoids collisions by reversing and steering away from barriers
   - drives forward when the path is clear

2. Manual mode
   - accepts directional commands such as forward, backward, left, and right
   - supports direct operator control

3. Stop mode
   - halts all movement immediately
   - used as a safe fallback state

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
- C++ firmware
- Adafruit DHT sensor library
- Embedded HTTP server for telemetry and control

---

## Getting Started

### 1. Install Requirements

- VS Code
- PlatformIO extension
- ESP32 USB drivers
- A compatible USB cable for firmware upload

### 2. Open the Project

Open the [ESP32](ESP32) folder as a PlatformIO project.

### 3. Build the Firmware

From the project root:

```bash
cd ESP32
pio run
```

### 4. Upload to the Board

```bash
cd ESP32
pio run --target upload
```

### 5. Connect to the Rover

The rover starts its own Wi-Fi access point:

- SSID: OreX-Rover
- Password: orex-rover

Once connected, open the dashboard in a browser:

```text
http://192.168.4.1
```

---

## Web Interface

The rover exposes a simple browser dashboard that displays:

- current operating mode
- obstacle distance
- gas sensor values
- temperature and humidity
- uptime

The same interface can send control commands such as:

- AUTO
- STOP
- FORWARD
- BACKWARD
- LEFT
- RIGHT

---

## API Endpoints

The firmware exposes a simple local API for telemetry and command execution.

### Get sensor and system data

```http
GET /api/data
```

Example response:

```json
{
  "mode": "auto",
  "distanceCm": 18,
  "obstacle": false,
  "mq2": 2400,
  "mq4": 1800,
  "mq7": 2100,
  "temperatureC": 29.4,
  "humidity": 68.1,
  "uptimeMs": 456213
}
```

### Send a command

```http
POST /api/command?cmd=forward
POST /api/command?cmd=stop
POST /api/command?cmd=auto
POST /api/command?cmd=left
```

Supported commands:

- auto
- stop
- forward
- backward
- left
- right

---

## Sensor Interpretation

- MQ2: general combustible gas and smoke detection
- MQ4: methane and natural gas detection
- MQ7: carbon monoxide detection
- DHT11: ambient temperature and relative humidity
- Ultrasonic sensor: object distance in centimeters

These readings provide situational awareness for mine environments where hazards are often invisible to the human eye.

---

## Safety Notes

This project is a prototype and should be treated as a field-research or hackathon demonstration system. Before deployment in real mine operations:

- validate against certified industrial sensors
- enclose electronics from dust and moisture
- test battery safety and power stability
- add fail-safe logic for harsh operational conditions
- confirm all hardware meets site-specific safety regulations

---

## Roadmap

Planned improvements for the next iteration include:

- camera-based obstacle recognition
- live cloud / dashboard integration
- GPS or localization support
- stronger gas threshold alerting
- industrial-grade sensor calibration
- LoRa or mesh communication for remote mine monitoring
- autonomous path planning for complex terrains

---

## Why This Project Matters

OreX is built around the idea that safer mining operations begin with better sensing and smarter machine assistance. By combining gas monitoring, obstacle avoidance, and remote control, the rover offers a practical solution for improving underground safety, especially in difficult or low-visibility conditions.

---

## Contributors

This project is being developed as part of the Smart India Hackathon initiative for SIH26039.

---

## Demo Photos

Add your real project images here to showcase the rover in action.

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

This is an active prototype and may be extended with additional sensing, communication, and industrial deployment features in future versions.
