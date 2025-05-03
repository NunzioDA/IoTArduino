#ifndef AriConditioning_H
#define AriConditioning_H

#include <Arduino.h>

class AirConditioning
{
  public:
    AirConditioning(int cool_pin, int warm_pin);
    void warm();
    void cool();
    void checkTemperature(int currentTemperature);
    void stop();
    void setAuto(bool autoMode);
    void setTargetTemperature(int targetTemperature);
    int getTargetTemperature();
  private:
    bool autoMode;
    int cool_pin;
    int warm_pin;
    int targetTemperature;
    
};

#endif