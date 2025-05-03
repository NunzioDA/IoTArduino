#include "fire_extinguisher.h"
#include "Arduino.h"


FireExtinguisher::FireExtinguisher(int pin) : pin(pin){
  pinMode(this-> pin, OUTPUT);
}

void FireExtinguisher::start()
{
  digitalWrite(this -> pin, HIGH);
}

void FireExtinguisher::stop()
{
  digitalWrite(this -> pin, LOW);
}