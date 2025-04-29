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
unsigned long millisLastDHTRead = 0;

ParkSensor parkA(50,52);
ParkSensor parkB(51,53);
ParkSensor parkC(46,48);

Fan fanSystem(6);

RGBDimmableLight lighting(2,3,4);
bool autoLight = true;

bool playAlarm = false;
unsigned long millisLastFlameDetected = 0;


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
    
    if(parts[1]=="ready")
    {
      Serial.println(command);
    }
    else if(parts[1] == "light")
    { 
      if(num_parts > 1){
        if(parts[2] == "on")
        {
          autoLight = false;
          lighting.on();
        }
        else if(parts[2] == "off")
        {
          autoLight = false;
          lighting.off();
        }
        else if(parts[2] == "auto")
        {
          autoLight = true;
        }
        else if(parts[2] == "color" && num_parts > 2)
        {
          Serial.println("Setting " + parts[3] + "," + parts[4] + "," + parts[5]);
          lighting.setColor(parts[3].toInt(), parts[4].toInt(), parts[5].toInt());
        }
        else{
          returnValue = "Missing color for command: " + command;
        }
      }
      else{
        returnValue = "Missing parameters for light command: " + command;
      }

      Serial.println(parts[0]+";"+returnValue);
    }
    else if(parts[1]=="info")
    {
      if (millis() - millisLastDHTRead > 5000)
      {
        millisLastDHTRead = millis();
        DHT.read();
      }

      String jsonInfo = "{";
      jsonInfo += "\"temperature\":" + String(DHT.temperature()) + ",";
      jsonInfo += "\"humidity\":" + String(DHT.temperature()) + ",";
      jsonInfo += "\"light\":" + String(lightSensor.status()) + ",";
      int color [3];
      lighting.getColor(color);
      jsonInfo += "\"light_color\":[" + String(color[0]) + "," + String(color[1]) + "," + String(color[2]) + "],";

      String mode = "Auto";
      if(!autoLight){
        mode = "Manual";
      }

      jsonInfo += "\"light_mode\":\"" + mode + "\",";
      jsonInfo += "\"park\":[" + String(parkA.isParked()) + "," + String(parkB.isParked()) + "," + String(parkC.isParked()) + "]";
      jsonInfo += "}";

      Serial.println(parts[0]+";"+jsonInfo);
    }

    delete[] parts;
  }
}

void loop()
{
  handleMessages();

  if(autoLight){    
    if(lightSensor.status() < 300)
    {
      //Serial.println("IS DARK");
      lighting.on();
    }
    else if(lightSensor.status() > 350){
      lighting.off();
    }
  }


  if(flameSensor.flameDetected())
  {
    playAlarm = true;
    millisLastFlameDetected = millis();
  }
  else if(playAlarm && millis() - millisLastFlameDetected > 5000){
    playAlarm = false;
  }

  if(playAlarm)
  {
    alarm.play();
  }
  else{
    alarm.stop();

    if(airQualitySensor.airQuality() > 35)
    {
      double intensity = airQualitySensor.airQuality() / 85;
      if(intensity > 1) intensity = 1;
      fanSystem.blow(intensity);
    }
    else{
      fanSystem.off();
    }
  }

}
