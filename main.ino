#include "alarm.h"
#include "light_sensor.h"
#include "flame_sensor.h"
#include "air_quality_sensor.h"
#include "park_sensor.h"
#include "fan.h"
#include "rgb_dimmable_light.h"
#include "DHT11.h"
#include "string_utils.h"

Alarm alarm(13, 12);
LightSensor lightSensor(A0);
FlameSensor flameSensor(A13);
AirQualitySensor airQualitySensor(A9);
DHT11 DHT(10);

ParkSensor parkA(50,52);
ParkSensor parkB(51,53);
ParkSensor parkC(46,48);

Fan fanSystem(6);

RGBDimmableLight lighting(2,3,4);
bool autoLight = true;

void setup()
{
  Serial.begin(9600);
}

void handleMessages()
{
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    Serial.println("Received: " + command);
    
    int num_parts = 1;
    String* parts = splitString(command, ';', num_parts);
    String returnValue = "ok";

    if(parts[0] == "light")
    { 
      if(num_parts > 1){
        if(parts[1] == "on")
        {
          autoLight = false;
          lighting.on();
        }
        else if(parts[1] == "off")
        {
          autoLight = false;
          lighting.off();
        }
        else if(parts[1] == "auto")
        {
          autoLight = true;
        }
        else if(parts[1] == "color" && num_parts > 2)
        {
          lighting.setColor(parts[2]);
        }
        else{
          returnValue = "Missing color for command: " + command;
        }
      }
      else{
        returnValue = "Missing parameters for light command: " + command;
      }

      Serial.println(returnValue);
    }
    else if(parts[0]=="info")
    {
      DHT.read();
      String jsonInfo = "{";
      jsonInfo += "\"temperature:\"" + String(DHT.temperature()) + ",";
      jsonInfo += "\"humidity:\"" + String(DHT.temperature()) + ",";
      jsonInfo += "\"park:\"[" + String(parkA.isParked()) + "," + String(parkB.isParked()) + "," + String(parkC.isParked()) + "]";
      jsonInfo += "}";

      Serial.println(jsonInfo);
    }

    delete[] parts;
  }
}

void loop()
{
  handleMessages();

  if(autoLight){
    if(lightSensor.isDark())
    {
      //Serial.println("IS DARK");
      lighting.on();
    }
    else{
      lighting.off();
    }
  }

  if(flameSensor.flameDetected())
  {
    alarm.play();    
  }
  else{
    if(airQualitySensor.badQuality())
    {
      //Serial.println("BAD QUALITY");
      fanSystem.on();
    }
    else{
      fanSystem.off();
    }
  }

}