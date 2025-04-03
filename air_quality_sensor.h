#ifndef AirQualitySensor_h
#define AirQualitySensor_h

#include <Arduino.h>


/*
  * Author: Nunzio D'Amore.
  * Date: 03/04/2025
  *
  * The AirQualitySensor class reads air quality values from an MQ-2 sensor 
  * and classifies the air as good or bad based on user-defined thresholds.
  *
  *
  * ## Usage:
  * ```cpp
  * AirQualitySensor sensor(A0, 150, 75); // Define a sensor with custom thresholds
  * if (sensor.badQuality()) {
  *     Serial.println("Warning: Poor air quality!");
  * }
  * ```
  *
  * ## Default thresholds:
  * - badAirThreshold = 100
  * - goodAirThreshold = 50
*/

class AirQualitySensor
{
  public:
    /**
     * @brief Constructor with default thresholds.
     * @param pin Analog pin to read sensor data from.
    */
    AirQualitySensor(int pin);
    /**
     * @brief Constructor with custom thresholds.
     * @param pin Analog pin to read sensor data from.
     * @param badAirThreshold Value above which the air quality is considered bad.
     * @param goodAirThreshold Value below which the air quality is considered good.
    */
    AirQualitySensor(int pin, int badAirThreshold, int goodAirThreshold);
    /**
     * @brief Checks if the air quality is bad.
     * @return True if air quality is poor, false otherwise.
    */
    bool badQuality();
    /**
     * @brief Checks if the air quality is good.
     * @return True if air quality is good, false otherwise.
    */
    bool goodQuality();
    /**
     * @brief Reads the current air quality value.
     * @return A float representing the sensor reading.
    */
    float airQuality();


  private:
    int pin;
    int badAirThreshold;
    int goodAirThreshold;
};

#endif