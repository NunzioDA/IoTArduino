/*
  * Author: Nunzio D'Amore.
  * Date: 03/04/2025
  *
  * The FlameSensor class is used to detect flames
  * using an IR sensor. This is achieved by checking
  * if the sensor output is bigger then a user-defined thresold.
  *
  * The default thresold has been chosen using a 15kΩ resistor.
  *
  * ## Usage:
  * ```cpp
  * FlameSensor sensor(A0, 50); // Define a sensor with custom thresholds
  * if (sensor.flameDetected()) {
  *     Serial.println("Warning: Flame detected!");
  * }
  * ```
  *
  * ## Default thresholds:
  * - threshold = 30
*/

#include "flame_sensor.h"
#include "Arduino.h"

FlameSensor::FlameSensor(int pin) : pin(pin), threshold(400){
  pinMode(this-> pin, INPUT);
}
FlameSensor::FlameSensor(int pin, int threshold) : pin(pin), threshold(threshold){}

bool FlameSensor::flameDetected(){
  return analogRead(this -> pin) >= this -> threshold;
}