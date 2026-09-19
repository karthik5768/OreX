import os
import time
import cv2
import mediapipe as mp
from mediapipe.tasks import python
from mediapipe.tasks.python import vision

# --- Path Configuration ---
SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
MODEL_PATH = os.path.join(SCRIPT_DIR, "efficientdet_lite0.tflite")
CONF_THRESHOLD = 0.5
IMAGE_WIDTH = 320
IMAGE_HEIGHT = 240

# --- Initialize MediaPipe Object Detector ---
print("Loading TFLite Model via MediaPipe Tasks API...")
base_options = python.BaseOptions(model_asset_path=MODEL_PATH)
options = vision.ObjectDetectorOptions(
    base_options=base_options,
    score_threshold=CONF_THRESHOLD
)
detector = vision.ObjectDetector.create_from_options(options)

# --- Initialize Camera ---
cap = cv2.VideoCapture(0)
cap.set(cv2.CAP_PROP_FRAME_WIDTH, IMAGE_WIDTH)
cap.set(cv2.CAP_PROP_FRAME_HEIGHT, IMAGE_HEIGHT)

if not cap.isOpened():
    print("Error: Could not open camera feed.")
    exit()

print("Headless Object Detection Running. Press Ctrl+C to exit...")

frame_count = 0
start_time = time.time()

try:
    while True:
        ret, frame = cap.read()
        if not ret:
            print("Failed to capture frame.")
            break

        frame_count += 1

        # Convert frame BGR -> RGB and wrap in MediaPipe Image container
        rgb_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
        mp_image = mp.Image(image_format=mp.ImageFormat.SRGB, data=rgb_frame)

        # Detect objects
        detection_result = detector.detect(mp_image)

        # Parse Detections
        detected_objects = []
        for detection in detection_result.detections:
            category = detection.categories[0]
            label_name = category.category_name
            confidence = int(category.score * 100)
            detected_objects.append(f"{label_name} ({confidence}%)")

        if detected_objects:
            print(f"[Frame {frame_count}] Detected: {', '.join(detected_objects)}")

        if frame_count % 30 == 0:
            elapsed = time.time() - start_time
            print(f"--- Running at {frame_count / elapsed:.2f} FPS ---")

except KeyboardInterrupt:
    print("\nStopping detection stream...")

finally:
    cap.release()
    print("Camera released.")