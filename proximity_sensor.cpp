/**
 * @brief ProximitySensor is a class for measuring distance 
 * using an ultrasonic sensor.
 *
 * This class allows measuring distances using the HC-SR04 sensor 
 * with a trigger and echo pin.
 */
 
#include "proximity_sensor.h"
#include "Arduino.h"


ProximitySensor::ProximitySensor(int trigger, int echo) : trigger(trigger), echo(echo)
{
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
}


float ProximitySensor::distance()
{
  digitalWrite(this -> trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(this -> trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(this -> trigger, LOW);

  float duration = pulseIn(this -> echo, HIGH);

  float distance = (duration*.0343)/2;
  return distance;
}