#include "park_sensor.h"
#include "Arduino.h"
#include "proximity_sensor.h"

ParkSensor::ParkSensor(int trigger, int echo) : proximitySensor(trigger, echo){}

bool ParkSensor::isParked()
{
  return this -> proximitySensor.distance() == 0;
}