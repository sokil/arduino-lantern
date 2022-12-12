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
 * 
 * Photoresistor:
 * 
 * VCC +-----[LIGHTSENSOR]--+---[10K RESISTOR]-----+ GND
 *                            |
 *                            |
 *                            + SIGNAL
*/
const int MOTION_SENSOR_DIGITAL_PIN = 2;
const int LIGHT_SENSOR_ANALOG_PIN = 0;
const int RELAY_DIGINAL_PIN = 4;

int motionSensorPinCurrentState   = LOW;
int motionSensorPinPreviousState  = LOW;

bool isMotionSensorSwitchOffDelayEnabled = false;
unsigned long motionSensorSwitchOffDelayStartTime;

const unsigned long MOTION_SENSOR_SWITCH_OFF_DELAY_MS = 5000;
const unsigned int LIGHT_SENSOR_THESHOLD = 80;

bool isMotionDetected = false;
bool isDarknessDetected = false;

void motionSensorLoopTick() {
  motionSensorPinPreviousState = motionSensorPinCurrentState; 
  motionSensorPinCurrentState = digitalRead(MOTION_SENSOR_DIGITAL_PIN);

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

void lightSensorLoopTick() {
  int lightLevel = analogRead(LIGHT_SENSOR_ANALOG_PIN);
  
  Serial.println(lightLevel);

  if (lightLevel > LIGHT_SENSOR_THESHOLD) {
    isDarknessDetected = false;
  } else {
    isDarknessDetected = true;
  }
}

void relaySwitchOn() {
  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(RELAY_DIGINAL_PIN, HIGH);
}

void relaySwitchOff() {
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(RELAY_DIGINAL_PIN, LOW);
}

void setup() {
  Serial.begin(9600);
  
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(RELAY_DIGINAL_PIN, OUTPUT);
  pinMode(MOTION_SENSOR_DIGITAL_PIN, INPUT);
}

void loop() {
  motionSensorLoopTick();
  lightSensorLoopTick();

  if (isDarknessDetected && isMotionDetected) {
    relaySwitchOn();
  } else {
    relaySwitchOff();
  }

  delay(1000);
}
