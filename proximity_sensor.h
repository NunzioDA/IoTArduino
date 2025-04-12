#ifndef ProximitySensor_h
#define ProximitySensor_h

#include <Arduino.h>

/**
  * Author: Nunzio D'Amore.
  * Date: 03/04/2025
  *
  * @brief ProximitySensor is a class for measuring distance 
  * using an ultrasonic sensor.
  *
  * This class allows measuring distances using the HC-SR04 sensor 
  * with a trigger and echo pin.
  *
  * ## Usage:
  * ```cpp
  * ProximitySensor sensor(7, 6); // Define a sensor with custom thresholds
  * Serial.print("Distance: ");
  * Serial.println(sensor.distance());
  * ```
 */
class ProximitySensor
{
  public:
    /**
     * @brief Constructor for the ProximitySensor class.
     * 
     * @param trigger The digital pin used to send the ultrasonic pulse.
     * @param echo The digital pin used to receive the reflected signal.
     */
    ProximitySensor(int trigger, int echo);

    /**
     * @brief Measures the distance detected by the ultrasonic sensor.
     * 
     * @return The measured distance in centimeters.
     */
    float distance();
  
  private:
    int trigger; // Digital pin for triggering the ultrasonic pulse.
    int echo;    // Digital pin for receiving the reflected pulse.
};

#endif
