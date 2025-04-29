#include "rgb_dimmable_light.h"
#include "Arduino.h"

RGBDimmableLight::RGBDimmableLight(int r_pin, int g_pin, int b_pin) : r_pin(r_pin), g_pin(g_pin), b_pin(b_pin), r_intensity(255), g_intensity(255), b_intensity(255) {
  pinMode(this-> r_pin, OUTPUT);
  pinMode(this-> g_pin, OUTPUT);
  pinMode(this-> b_pin, OUTPUT);
}

void RGBDimmableLight::setColor(String hexColor)
{
  if (hexColor[0] == '#') {
    hexColor = hexColor.substring(1);
  }

  long number = strtol(hexColor.c_str(), NULL, 16);

  byte red   = (number >> 16) & 0xFF;
  byte green = (number >> 8) & 0xFF;
  byte blue  = number & 0xFF;

  this -> setColor(red, green, blue);
}

void RGBDimmableLight::setColor(int red, int green, int blue)
{
  Serial.println(red);
  Serial.println(green);
  Serial.println(blue);

  int red_intensity = (int)red;
  int green_intensity = (int)green;
  int blue_intensity = (int)blue;

  this -> r_intensity = red_intensity;
  this -> g_intensity = green_intensity;
  this -> b_intensity = blue_intensity;

  analogWrite(this -> r_pin, red_intensity);
  analogWrite(this -> g_pin, green_intensity);
  analogWrite(this -> b_pin, blue_intensity);
}

void RGBDimmableLight::on()
{
  analogWrite(this -> r_pin, this -> r_intensity);
  analogWrite(this -> g_pin, this -> g_intensity);
  analogWrite(this -> b_pin, this -> b_intensity);
}

void RGBDimmableLight::off()
{
  analogWrite(this -> r_pin, 0);
  analogWrite(this -> g_pin, 0);
  analogWrite(this -> b_pin, 0);
}

void RGBDimmableLight::getColor(int outColor[3]) {
    outColor[0] = this->r_intensity;
    outColor[1] = this->g_intensity;
    outColor[2] = this->b_intensity;
}

