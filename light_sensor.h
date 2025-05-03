#ifndef LightSensor_h
#define LightSensor_h


#include <Arduino.h>

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
*
*
* ## Usage:
* ```cpp
*   LightSensor lightSensor(A0);
*   if(lightSensor.isDark())
*   {
*     Serial.println("IS DARK");
*   }
* ```
* @note Default thresholds:
*   DARK 200
*   DIM 400
*   LIGHT 600
*   BRIGHT 920
*/
class LightSensor
{
  public:
    /**
     * @brief Constructor: Initializes the LightSensor object.
     * @param pin The analog pin connected to the light sensor.
     */
    LightSensor(int pin);

    /**
     * @brief Reads the light sensor and returns the light level.
     * @return The value the sensor returns.
     */
    int status();

    /**
     * @brief Checks if the light level is DARK.
     * @return True if the light level is DARK, false otherwise.
     */
    bool isDark();

    /**
     * @brief Checks if the light level is DIM.
     * @return True if the light level is DIM, false otherwise.
     */
    bool isDim();

    /**
     * @brief Checks if the light level is LIGHT.
     * @return True if the light level is LIGHT, false otherwise.
     */
    bool isLight();

    /**
     * @brief Checks if the light level is BRIGHT.
     * @return True if the light level is BRIGHT, false otherwise.
     */
    bool isBright();

    /**
     * @brief Checks if the light level is VERY_BRIGHT.
     * @return True if the light level is VERY_BRIGHT, false otherwise.
     */
    bool isVeryBright();


  private:
    /**
     * @brief Stores the analog pin connected to the light sensor.
     */
    int pin;
    /**
     * @brief Stores the current status of the light sensor.
     */
    int currentStatus;
};

#endif