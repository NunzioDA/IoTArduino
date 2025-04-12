#ifndef ParkSensor_H
#define ParkSensor_H

#include <Arduino.h>
#include "proximity_sensor.h"

class ParkSensor
{
  public:
    ParkSensor(int trigger, int echo);
    bool isParked();
  private:
    ProximitySensor proximitySensor;
};

#endif