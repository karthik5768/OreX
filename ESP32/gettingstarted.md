## Getting Started

### 1. Install Requirements

- VS Code
- PlatformIO extension
- ESP32 USB drivers
- A compatible USB cable for firmware upload

### 2. Open the Project

Open the ESP32 folder as a PlatformIO project or in Arduino IDE.

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

---

## Safety Notes

This project is a prototype and should be treated as a field-research/demonstration system. Before deployment in real mine operations:

- caliberate the gas sensors(IMPORTANT) against certified industrial sensors
- make sure electronics are sealed from dust and moisture
- test battery safety and power stability
- ensure sensors are warmed up atleast ~48 hours before deployment
- confirm all hardware meets site-specific safety regulations and are in proper working conditions

---