#include "park_sensor.h"
#include "Arduino.h"
#include "proximity_sensor.h"

ParkSensor::ParkSensor(int trigger, int echo) : proximitySensor(trigger, echo), distance_noise_reduction(0){}

bool ParkSensor::isParked()
{
  return this -> distance() < 5;
}

double ParkSensor::distance()
{
  this -> distance_noise_reduction += this ->  proximitySensor.distance();
  this -> distance_noise_reduction = this -> distance_noise_reduction / 3;
  return this -> distance_noise_reduction;
}