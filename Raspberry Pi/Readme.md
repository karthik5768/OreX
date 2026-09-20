# Real-Time Object Detection on Raspberry Pi

A lightweight, efficient real-time object detection stream built using **Google MediaPipe Tasks API**, **OpenCV**, and **TensorFlow Lite (`efficientdet_lite0.tflite`)**. Designed to run efficiently in headless environments, low-power systems, and single-board computers like the **Raspberry Pi 3B / 4 / 5**.

## Features

* **Headless & Fast:** Runs without requiring a GUI, rendering labels directly to stdout with minimal CPU overhead.
* **EfficientDet-Lite0 Architecture:** Uses Google's optimized TFLite model designed for mobile and edge devices.
* **Automated Setup:** Single-command setup script handles system dependencies, virtual environment configuration, and model downloading.
* **FPS Monitoring:** Tracks real-time frame rates logged every 30 frames.

## Hardware Requirements & Compatibility

* **Hardware:** Raspberry Pi 3B, 3B+, 4, 5, or any Linux-based device with a USB Webcam or Pi Camera module.
* **OS:** **Raspberry Pi OS 64-bit (`aarch64`)** or standard 64-bit Linux distributions (Ubuntu, Debian).

  > **Note:** Official `mediapipe` Python packages require a 64-bit OS.

## Quick Start (From Repository Root)

Navigate into this subfolder, run the setup script, and start the application with a single command:

```bash
cd ~/OreX/Raspberry Pi/ && chmod +x setup.sh && ./setup.sh && source venv/bin/activate && python object_detection.py
```

## Manual Installation

If you want to set up step-by-step:

### 1. Navigate to Project Directory

```bash
cd OreX/Raspberry Pi/
```

### 2. Make Setup Script Executable & Run

```bash
chmod +x setup.sh
./setup.sh
```

### 3. Activate Virtual Environment & Run

```bash
source venv/bin/activate
python object_detection.py
```

## Project Directory Structure

```text
OreX/Raspberry Pi/
├── setup.sh                 # Dependency installation and setup script
├── object_detection.py      # Main object detection Python script
├── efficientdet_lite0.tflite# Downloaded automatically by setup.sh
└── Readme.md                # Project documentation
```

## Performance Optimization (For Pi 3B / Low-Power Boards)

If you encounter performance issues or low FPS on older single-board computers:

1. **Reduce Image Dimensions:** Modify `IMAGE_WIDTH` and `IMAGE_HEIGHT` inside `object_detection.py`:

   ```python
   IMAGE_WIDTH = 160
   IMAGE_HEIGHT = 120
   ```

2. **Implement Frame Skipping:** Process inference every $N$-th frame inside the main loop:

   ```python
   if frame_count % 2 != 0:
       continue
   ```

## Troubleshooting

* **Error: `Could not open camera feed.`**
  * Verify your camera is connected properly (`ls /dev/video*`).
  * If using multiple video devices, change `cv2.VideoCapture(0)` to `cv2.VideoCapture(1)` inside `object_detection.py`.

* **Error: `No matching distribution found for mediapipe`**
  * Make sure you are running **Raspberry Pi OS 64-bit**. Check with `uname -m` (should return `aarch64`).
