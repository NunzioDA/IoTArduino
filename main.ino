#include "alarm.h"
#include "light_sensor.h"
#include "flame_sensor.h"
#include "air_quality_sensor.h"
#include "park_sensor.h"
#include "fan.h"
#include "rgb_dimmable_light.h"
#include "DHT11.h"
#include "string_utils.h"
#include "fire_extinguisher.h"
#include "air_conditioning.h"


// Initializing all the sensors
Alarm alarm(13, 12);
FireExtinguisher fireExtinguisher(24);
LightSensor lightSensor(A0);
FlameSensor flameSensor(A13);
AirQualitySensor airQualitySensor(A9);

DHT11 DHT(10);
unsigned long millisLastDHTRead = -6000;

ParkSensor parkA(50,52);
ParkSensor parkB(51,53);
ParkSensor parkC(46,48);

Fan fanSystem(6);

RGBDimmableLight lighting(2,3,4);
bool autoLight = true;

bool playAlarm = false;
unsigned long millisLastFlameDetected = 0;


AirConditioning airConditioner(30, 31);
int currentTemperature = 20;
int currentHumidity = 30;

int analogReadOffset = 0;

void setup()
{
  // Initializing Serial
  Serial.begin(9600);
}

float airQuality(){
  return airQualitySensor.airQuality() - analogReadOffset;
}

int lightStatus(){
  return lightSensor.status() - analogReadOffset;
}

// This function is used to handle available
// messages from the serial port.
// This is where all the commands are executed
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
    else if (parts[1]=="air"){
      if(parts[2]=="temperature")
      {
        airConditioner.setTargetTemperature(parts[3].toInt());
        Serial.println(parts[0]+";"+returnValue);
      }
      else if(parts[2]=="off")
      {
        airConditioner.stop();
      }
      else if(parts[2]=="cool")
      {
        airConditioner.cool();
      }
      else if(parts[2]=="warm")
      {
        airConditioner.warm();
      }
    }
    else if(parts[1]=="info")
    {
      // Returning info as a json string
      String jsonInfo = "{";
      jsonInfo += "\"temperature\":" + String(currentTemperature) + ",";
      jsonInfo += "\"target_temperature\":" + String(airConditioner.getTargetTemperature()) + ",";
      jsonInfo += "\"humidity\":" + String(currentHumidity) + ",";
      jsonInfo += "\"air\":" + String(airQuality()) + ",";
      jsonInfo += "\"light\":" + String(lightStatus()) + ",";
      jsonInfo += "\"light_status\":" + String(lighting.isOn()) + ",";
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
  if(lighting.isOn())
  {
    int color [3];
    lighting.getColor(color);
    analogReadOffset = (((float)(color[0] + color[1] + color[2]))/(3*255))*17; 
  }
  else{
    analogReadOffset = 0;
  }
  //Serial.println(String(parkA.distance())+ " "  + String(parkB.distance()) + " " + String(parkC.distance()));
  //Serial.println(lightSensor.status());
  handleMessages();

  // Waiting longer when the allarm is playing to 
  // allow the alarm to play longer without delay
  if ((playAlarm && millis() - millisLastDHTRead > 10000) || (!playAlarm && millis() - millisLastDHTRead > 5000))
  {
    millisLastDHTRead = millis();
    DHT.read();
    currentTemperature = DHT.temperature();
    currentHumidity = DHT.humidity();
  }

  airConditioner.checkTemperature(currentTemperature);

  if(autoLight){ 

    if(lightStatus() < 450 && !lighting.isOn())
    {
      lighting.on();
    }
    else if(lighting.isOn()){ 
      int color [3];
      lighting.getColor(color);
      // Computing threshold based on current color
      int top_threshold = 500 + ((double)(color[0] + color[1] + color[2])/765.0) * 250;
      if(lightStatus() > top_threshold){
      
        lighting.off();
      }
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
    fanSystem.off();
    fireExtinguisher.start();
  }
  else{
    alarm.stop();
    fireExtinguisher.stop();
    
    if(airQuality() > 70)
    {
      double intensity = airQuality() / 100;
      if(intensity > 1) intensity = 1;
      fanSystem.blow(intensity);
      //Serial.println(intensity);
    }
    else{
      fanSystem.off();
    }
  }

}
