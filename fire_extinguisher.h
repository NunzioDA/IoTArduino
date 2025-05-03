#ifndef FireExtinguisher_H
#define FireExtinguisher_H

#include <Arduino.h>

class FireExtinguisher
{
  public:
    FireExtinguisher(int pin);
    void start();
    void stop();
  private:
    int pin;
};

#endif