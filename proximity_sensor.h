#ifndef ProximitySensor_h
#define ProximitySensor_h

#include <Arduino.h>

/**
 * @brief ProximitySensor is a class for measuring distance 
 * using an ultrasonic sensor.
 *
 * This class allows measuring distances using the HC-SR04 sensor 
 * with a trigger and echo pin.
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
