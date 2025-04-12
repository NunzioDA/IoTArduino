/**
  * Author: Nunzio D'Amore.
  * Date: 09/04/2025
  *
  * @brief Fan is a class for controlling a fan connected to a pin.
  *
  * This class allows turning a fan on and off and controlling its intensity
  * by writing an analog value to the specified pin.
  *
  * ## Usage:
  * ```cpp
  * Fan myFan(D3); // Define a fan connected to analog pin D3
  * myFan.blow(0.75); // Set the fan intensity to 75% 
  * ```
*/

#include "fan.h"
#include "Arduino.h"

Fan::Fan(int pin) : pin(pin){
  pinMode(this-> pin, OUTPUT);
}

void Fan::blow(double intensity){
  analogWrite(this->pin, intensity * 255);
}

void Fan::on(){
  analogWrite(this->pin, 255);
}

void Fan::off(){
  analogWrite(this->pin, 0);
}