/*
  * Author: Nunzio D'Amore.
  * Date: 03/04/2025
  *
  * The AirQualitySensor class reads air quality values from an MQ-2 sensor 
  * and classifies the air as good or bad based on user-defined thresholds.
  *
  *
  * ## Usage:
  * ```cpp
  * AirQualitySensor sensor(A0, 150, 75); // Define a sensor with custom thresholds
  * if (sensor.badQuality()) {
  *     Serial.println("Warning: Poor air quality!");
  * }
  * ```
  *
  * @note Default thresholds:
  * - badAirThreshold = 100
  * - goodAirThreshold = 50
*/

#include "air_quality_sensor.h"
#include "Arduino.h"

AirQualitySensor::AirQualitySensor(int pin) : pin(pin), badAirThreshold(100), goodAirThreshold(50){}
AirQualitySensor::AirQualitySensor(int pin, int badAirThreshold, int goodAirThreshold) : pin(pin), badAirThreshold(badAirThreshold), goodAirThreshold(goodAirThreshold){}

bool AirQualitySensor::badQuality(){
  return analogRead(this -> pin) >= this -> badAirThreshold;
}

bool AirQualitySensor::goodQuality(){
  return analogRead(this -> pin) <= this -> goodAirThreshold;
}

float AirQualitySensor::airQuality(){
  return analogRead(this -> pin);
}