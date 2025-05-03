#include "air_conditioning.h"
#include "Arduino.h"


AirConditioning::AirConditioning(int cool_pin, int warm_pin) : cool_pin(cool_pin), warm_pin(warm_pin), autoMode(true){
  pinMode(this-> cool_pin, OUTPUT);
  pinMode(this-> warm_pin, OUTPUT);
}

void AirConditioning::warm()
{
  digitalWrite(this -> warm_pin, HIGH);
  digitalWrite(this -> cool_pin, LOW);
  this -> setAuto(false);
}

void AirConditioning::cool()
{
  digitalWrite(this -> warm_pin, LOW);
  digitalWrite(this -> cool_pin, HIGH);
  this -> setAuto(false);
}

void AirConditioning::stop()
{
  digitalWrite(this -> warm_pin, LOW);
  digitalWrite(this -> cool_pin, LOW);
  this -> setAuto(false);
}

void AirConditioning::setAuto(bool autoMode)
{
  this -> autoMode = autoMode;
}

void AirConditioning::checkTemperature(int currentTemperature)
{
  if(this -> autoMode){
    if(currentTemperature < targetTemperature - 2)
    {
      this -> warm();
    }
    else if(currentTemperature > targetTemperature + 2){
      this -> cool();
    }
    else {
      this -> stop();
    }
    this -> setAuto(true);
  }
}

void AirConditioning::setTargetTemperature(int targetTemperature)
{
  this -> targetTemperature = targetTemperature;
  this -> setAuto(true);
}

int AirConditioning::getTargetTemperature()
{
  return this -> targetTemperature;
}
