#ifndef FlameSensor_h
#define FlameSensor_h

#include <Arduino.h>


/*
  * Author: Nunzio D'Amore.
  * Date: 03/04/2025
  *
  * The FlameSensor class is used to detect flames
  * using an IR sensor. This is achieved by checking
  * if the sensor output is bigger then a user-defined thresold.
  *
  * The default thresold has been chosen using a 15kΩ resistor.
  *
  * ## Usage:
  * ```cpp
  * FlameSensor sensor(A0, 50); // Define a sensor with custom thresholds
  * if (sensor.flameDetected()) {
  *     Serial.println("Warning: Flame detected!");
  * }
  * ```
  *
  * ## Default thresholds:
  * - threshold = 30
*/
class FlameSensor
{
  public:
    /**
     * @brief Constructor: Initializes the FlameSensor object with a default threshold.
     * @param pin The analog pin connected to the flame sensor.
     */
    FlameSensor(int pin);

    /**
     * @brief Constructor: Initializes the FlameSensor object with a custom threshold.
     * @param pin The analog pin connected to the flame sensor.
     * @param threshold The threshold value for flame detection.
     */
    FlameSensor(int pin, int threshold);

    /**
     * @brief Checks if a flame is detected.
     * @return True if a flame is detected, false otherwise.
     */
    bool flameDetected();


  private:
    /**
     * @brief Stores the analog pin connected to the flame sensor.
     */
    int pin;

    /**
     * @brief Stores the threshold value for flame detection.
     */
    int threshold;
};

#endif