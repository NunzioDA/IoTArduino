#include "park_sensor.h"
#include "Arduino.h"
#include "proximity_sensor.h"

ParkSensor::ParkSensor(int trigger, int echo) : proximitySensor(trigger, echo), distance_noise_reduction(10){}

bool ParkSensor::isParked()
{
  bool returnValue = this -> distance() < 9 | this -> distance() > 15;
  return returnValue;
}

double ParkSensor::distance()
{
  //this -> distance_noise_reduction = (1.5*this -> distance_noise_reduction + this ->  proximitySensor.distance())/ 2.5;

  delay(5); 
  return this ->  proximitySensor.distance();
}