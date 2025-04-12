/*
* Author: Nunzio D'Amore.
* Date: 03/04/2025
*
* The DHT11 class reads ambient temperature and humidity
* from DHT11 sensor. This class is based on DFRobot_DHT11.
*
*/

#include "DHT11.h"
#include "Arduino.h"


DHT11::DHT11(int pin) : pin(pin), DHT(){
  pinMode(this-> pin, INPUT);
}

void DHT11::read()
{
  this -> DHT.read(this -> pin);
}

float DHT11::temperature(){
  return this -> DHT.temperature;
}

float DHT11::humidity(){
  return this -> DHT.humidity;
}

float DHT11::readTemperature(){
  this -> DHT.read(this -> pin);
  return this -> DHT.temperature;
}

float DHT11::readHumidity(){
  this -> DHT.read(this -> pin);
  return this -> DHT.humidity;
}