#include <Arduino.h>
#include <DHT.h>
#include <WebServer.h>
#include <WiFi.h>
#include "web_ui.h"

namespace Pins {
constexpr uint8_t mq2 = 1;
constexpr uint8_t mq4 = 2;
constexpr uint8_t mq7 = 3;
constexpr uint8_t dht = 7;
constexpr uint8_t ultrasonicTrigger = 8;
constexpr uint8_t ultrasonicEcho = 9;
constexpr uint8_t leftEnable = 10;
constexpr uint8_t leftIn1 = 11;
constexpr uint8_t leftIn2 = 12;
constexpr uint8_t rightEnable = 13;
constexpr uint8_t rightIn1 = 14;
constexpr uint8_t rightIn2 = 15;
}

constexpr char AP_SSID[] = "OreX-Rover";
constexpr char AP_PASSWORD[] = "orex-rover";
constexpr uint16_t HTTP_PORT = 80;
constexpr uint32_t SENSOR_INTERVAL_MS = 2000;
constexpr uint32_t OBSTACLE_INTERVAL_MS = 100;
constexpr uint32_t MANUAL_TIMEOUT_MS = 1000;
constexpr uint16_t OBSTACLE_DISTANCE_CM = 25;
constexpr uint32_t PWM_FREQUENCY = 20000;
constexpr uint8_t PWM_RESOLUTION = 8;
constexpr uint8_t LEFT_PWM_CHANNEL = 0;
constexpr uint8_t RIGHT_PWM_CHANNEL = 1;

DHT dht(Pins::dht, DHT11);
WebServer server(HTTP_PORT);

enum class DriveMode { Auto, Manual, Stop };
DriveMode driveMode = DriveMode::Stop;

struct SensorData {
  int mq2 = 0;
  int mq4 = 0;
  int mq7 = 0;
  float temperature = NAN;
  float humidity = NAN;
  long distanceCm = -1;
  uint32_t updatedAt = 0;
};

SensorData sensors;
uint32_t lastSensorRead = 0;
uint32_t lastObstacleRead = 0;
uint32_t lastManualCommand = 0;
bool obstacleDetected = false;

void setMotor(uint8_t pwmChannel, uint8_t in1, uint8_t in2, int speed) {
  speed = constrain(speed, -255, 255);
  digitalWrite(in1, speed > 0 ? HIGH : LOW);
  digitalWrite(in2, speed < 0 ? HIGH : LOW);
  ledcWrite(pwmChannel, abs(speed));
}

void drive(int leftSpeed, int rightSpeed) {
  setMotor(LEFT_PWM_CHANNEL, Pins::leftIn1, Pins::leftIn2, leftSpeed);
  setMotor(RIGHT_PWM_CHANNEL, Pins::rightIn1, Pins::rightIn2, rightSpeed);
}

void stopMotors() {
  drive(0, 0);
}

long measureDistanceCm() {
  digitalWrite(Pins::ultrasonicTrigger, LOW);
  delayMicroseconds(2);
  digitalWrite(Pins::ultrasonicTrigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(Pins::ultrasonicTrigger, LOW);

  const unsigned long duration = pulseIn(Pins::ultrasonicEcho, HIGH, 25000);
  return duration == 0 ? -1 : static_cast<long>(duration / 58);
}

void readSensors() {
  sensors.mq2 = analogRead(Pins::mq2);
  sensors.mq4 = analogRead(Pins::mq4);
  sensors.mq7 = analogRead(Pins::mq7);

  const float humidity = dht.readHumidity();
  const float temperature = dht.readTemperature();
  if (!isnan(humidity)) sensors.humidity = humidity;
  if (!isnan(temperature)) sensors.temperature = temperature;
  sensors.updatedAt = millis();
}

String modeName() {
  if (driveMode == DriveMode::Auto) return "auto";
  if (driveMode == DriveMode::Manual) return "manual";
  return "stop";
}

String jsonNumber(float value) {
  return isnan(value) ? "null" : String(value, 1);
}

void handleData() {
  String body = "{";
  body += "\"mode\":\"" + modeName() + "\",";
  body += "\"distanceCm\":" + String(sensors.distanceCm) + ",";
  body += "\"obstacle\":" + String(obstacleDetected ? "true" : "false") + ",";
  body += "\"mq2\":" + String(sensors.mq2) + ",";
  body += "\"mq4\":" + String(sensors.mq4) + ",";
  body += "\"mq7\":" + String(sensors.mq7) + ",";
  body += "\"temperatureC\":" + jsonNumber(sensors.temperature) + ",";
  body += "\"humidity\":" + jsonNumber(sensors.humidity) + ",";
  body += "\"uptimeMs\":" + String(millis()) + "}";
  server.send(200, "application/json", body);
}

void handleCommand() {
  const String command = server.hasArg("cmd") ? server.arg("cmd") : "stop";
  lastManualCommand = millis();

  if (command == "auto") {
    driveMode = DriveMode::Auto;
  } else if (command == "stop") {
    driveMode = DriveMode::Stop;
    stopMotors();
  } else if (command == "forward" || command == "backward" || command == "left" || command == "right") {
    driveMode = DriveMode::Manual;
    if (command == "forward") drive(200, 200);
    if (command == "backward") drive(-200, -200);
    if (command == "left") drive(-180, 180);
    if (command == "right") drive(180, -180);
  } else {
    server.send(400, "application/json", "{\"error\":\"unknown command\"}");
    return;
  }

  server.send(200, "application/json", "{\"ok\":true,\"mode\":\"" + modeName() + "\"}");
}

void handleRoot() {
  server.send(200, "text/html", INDEX_HTML);
}

void updateAutonomousDrive() {
  if (driveMode != DriveMode::Auto) return;
  if (obstacleDetected) {
    drive(-170, -170);
    delay(250);
    drive(180, -180);
    delay(350);
  } else {
    drive(180, 180);
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(Pins::ultrasonicTrigger, OUTPUT);
  pinMode(Pins::ultrasonicEcho, INPUT);
  pinMode(Pins::leftIn1, OUTPUT);
  pinMode(Pins::leftIn2, OUTPUT);
  pinMode(Pins::rightIn1, OUTPUT);
  pinMode(Pins::rightIn2, OUTPUT);
  ledcSetup(LEFT_PWM_CHANNEL, PWM_FREQUENCY, PWM_RESOLUTION);
  ledcSetup(RIGHT_PWM_CHANNEL, PWM_FREQUENCY, PWM_RESOLUTION);
  ledcAttachPin(Pins::leftEnable, LEFT_PWM_CHANNEL);
  ledcAttachPin(Pins::rightEnable, RIGHT_PWM_CHANNEL);
  stopMotors();

  analogReadResolution(12);
  dht.begin();

  WiFi.mode(WIFI_AP);
  WiFi.softAP(AP_SSID, AP_PASSWORD);
  Serial.print("AP address: ");
  Serial.println(WiFi.softAPIP());

  server.on("/", HTTP_GET, handleRoot);
  server.on("/api/data", HTTP_GET, handleData);
  server.on("/api/command", HTTP_POST, handleCommand);
  server.onNotFound([]() { server.send(404, "application/json", "{\"error\":\"not found\"}"); });
  server.begin();
}

void loop() {
  const uint32_t now = millis();
  server.handleClient();

  if (now - lastSensorRead >= SENSOR_INTERVAL_MS) {
    lastSensorRead = now;
    readSensors();
  }
  if (now - lastObstacleRead >= OBSTACLE_INTERVAL_MS) {
    lastObstacleRead = now;
    sensors.distanceCm = measureDistanceCm();
    obstacleDetected = sensors.distanceCm > 0 && sensors.distanceCm <= OBSTACLE_DISTANCE_CM;
    updateAutonomousDrive();
  }
  if (driveMode == DriveMode::Manual && now - lastManualCommand > MANUAL_TIMEOUT_MS) {
    driveMode = DriveMode::Stop;
    stopMotors();
  }
}