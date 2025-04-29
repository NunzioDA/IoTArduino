#ifndef ParkSensor_H
#define ParkSensor_H

#include <Arduino.h>
#include "proximity_sensor.h"

class ParkSensor
{
  public:
    ParkSensor(int trigger, int echo);
    bool isParked();
    double distance();
  private:
    ProximitySensor proximitySensor;
    double distance_noise_reduction;
};

#endif