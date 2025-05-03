/*
* Author: Nunzio D'Amore.
* Date: 03/04/2025
*
* The LightSensor class measures ambient light 
* intensity and categorizes the sensor output into 
* five levels: DARK, DIM, LIGHT, BRIGHT, and VERY_BRIGHT, 
* based on four predefined thresholds.
*
* The thresholds are determined empirically using 
* a high-precision 15kΩ resistor.
*/

#include "light_sensor.h"
#include "Arduino.h"


#define DARK 200
#define DIM 400
#define LIGHT 600
#define BRIGHT 920

LightSensor::LightSensor(int pin) : pin(pin), currentStatus(0){
  pinMode(this-> pin, INPUT);
}

bool LightSensor::isDark()
{
  return this -> status() <= DARK;  
}

bool LightSensor::isDim()
{
  return this -> status() <= DIM && !this -> isDark();  
}

bool LightSensor::isLight()
{
  return this -> status() <= LIGHT && this -> status() > DIM;  
}

bool LightSensor::isBright()
{
  return this -> status() <= BRIGHT && this -> status() > LIGHT; 
}

bool LightSensor::isVeryBright()
{
  return this -> status() > BRIGHT;
}

int LightSensor::status()
{ 
  long temp = (long) this -> currentStatus; 
  long read = (long) analogRead(this -> pin);
  temp = ((100 * temp) + read)/101;
  this -> currentStatus = temp;

  return this -> currentStatus;
}