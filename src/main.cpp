#include <Arduino.h>

/**
 * Motion Sensor HC-SR501:
 * 
 * +--------GND--OUT--VCC--------+
 * |                             |
 * |                             |
 * - Repeatable Mode             |
 * -                             |
 * - Single Mode                 |
 * |                             |
 * +-----[DISTANCE]--[TIME]------+
*/
const int MOTION_SENSOR_PIN = 2;

int motionSensorPinCurrentState   = LOW;
int motionSensorPinPreviousState  = LOW;

bool isMotionSensorSwitchOffDelayEnabled = false;
unsigned long motionSensorSwitchOffDelayStartTime;

const unsigned long MOTION_SENSOR_SWITCH_OFF_DELAY_MS = 5000;

bool isMotionDetected = false;
bool isDarknessDetected = false;

void setup() {
  Serial.begin(9600);
  
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(MOTION_SENSOR_PIN, INPUT);
}

void loop() {
  motionSensorLoopTick();
  darknessSensorLoopTick();

  if (isDarknessDetected && isMotionDetected) {
    digitalWrite(LED_BUILTIN, HIGH);
  } else {
    digitalWrite(LED_BUILTIN, LOW);
  }

  delay(1000);
}

void motionSensorLoopTick() {
  motionSensorPinPreviousState = motionSensorPinCurrentState; 
  motionSensorPinCurrentState = digitalRead(MOTION_SENSOR_PIN);
  Serial.println(motionSensorPinCurrentState);

  if (motionSensorPinPreviousState == LOW && motionSensorPinCurrentState == HIGH) {
    isMotionSensorSwitchOffDelayEnabled = false;

    isMotionDetected = true;
  } else if (motionSensorPinPreviousState == HIGH && motionSensorPinCurrentState == LOW) {
    isMotionSensorSwitchOffDelayEnabled = true;
    motionSensorSwitchOffDelayStartTime = millis();
  }

  if (isMotionSensorSwitchOffDelayEnabled == true && (millis() - motionSensorSwitchOffDelayStartTime) >= MOTION_SENSOR_SWITCH_OFF_DELAY_MS) {
    isMotionSensorSwitchOffDelayEnabled = false;

    isMotionDetected = false;
  }
}

void darknessSensorLoopTick() {
  isDarknessDetected = true; // debug mode
}
