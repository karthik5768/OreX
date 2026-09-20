#!/usr/bin/env bash
set -e

echo "=== Raspberry Pi Object Detection Setup ==="

# 1. Update system and install required system packages
echo "[1/4] Installing system dependencies..."
sudo apt update
sudo apt install -y python3-pip python3-venv python3-opencv libatlas-base-dev libopenjp2-7 libtiff5 wget

# 2. Set up Virtual Environment
echo "[2/4] Setting up Python virtual environment..."
VENV_DIR="venv"
if [ ! -d "$VENV_DIR" ]; then
    python3 -m venv "$VENV_DIR"
fi

source "$VENV_DIR/bin/activate"

# 3. Install Python dependencies
echo "[3/4] Installing Python libraries (MediaPipe & OpenCV)..."
pip install --upgrade pip
pip install opencv-python mediapipe

# 4. Download TFLite Model if missing
MODEL_FILE="efficientdet_lite0.tflite"
if [ ! -f "$MODEL_FILE" ]; then
    echo "[4/4] Downloading EfficientDet-Lite0 TFLite model..."
    wget -O "$MODEL_FILE" "https://storage.googleapis.com/mediapipe-models/object_detector/efficientdet_lite0/float16/1/efficientdet_lite0.tflite"
else
    echo "[4/4] Model file already exists. Skipping download."
fi

echo ""
echo "=== Setup Complete! ==="
echo "To run the application:"
echo "  source venv/bin/activate"
echo "  python object_detection.py"