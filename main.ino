#include "allarm.h"
#include "light_sensor.h"
#include "flame_sensor.h"
#include "air_quality_sensor.h"
#include "proximity_sensor.h"
#include "DHT11.h"


Allarm allarm(13);
LightSensor lightSensor(A0);
FlameSensor flameSensor(A13);
AirQualitySensor airQualitySensor(A9);
DHT11 DHT(10);
ProximitySensor parkA(7,6);

void setup() {
  Serial.begin(9600);
}

void loop() {
  // if(lightSensor.isDark())
  // {
  //   Serial.println("IS DARK");
  // }

  // Serial.println(lightSensor.status());


  // if(airQualitySensor.badQuality())
  // {
  //   Serial.println("BAD QUALITY");
  //   Serial.println(airQualitySensor.airQuality());
  // }


  // if(flameSensor.flameDetected())
  // {
  //   allarm.play();    
  // }

  
  Serial.print("Distance: ");
  Serial.println(parkA.distance());
  delay(100);
}