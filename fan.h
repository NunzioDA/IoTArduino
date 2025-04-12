#ifndef Fan_h
#define Fan_h

#include <Arduino.h>

/**
  * Author: Nunzio D'Amore.
  * Date: 09/04/2025
  *
  * @brief Fan is a class for controlling a fan connected to a pin.
  *
  * This class allows turning a fan on and off and controlling its intensity
  * by writing an analog value to the specified pin.
  *
  * ## Usage:
  * ```cpp
  * Fan myFan(D3); // Define a fan connected to analog pin D3
  * myFan.blow(0.75); // Set the fan intensity to 75% 
  * ```
*/
class Fan
{
 public:
  /**
   * @brief Constructor for the Fan class.
   *
   * @param pin The digital pin connected to the fan's control signal.
   * This pin is typically used with `analogWrite()` for speed control
   * or `digitalWrite()` for simple on/off functionality.
  */
  Fan(int pin);

  /**
   * @brief Controls the fan to blow at a specified intensity.
   *
   * This method sets the output on the fan's control pin to regulate its speed
   * or turn it on/off based on the provided intensity. The interpretation
   * of the `intensity` parameter depends on the specific implementation
   * (e.g., a value between 0.0 and 1.0 for PWM control).
   *
   * @param intensity A value representing the desired blowing intensity.
   * The range and meaning of this value are implementation-dependent.
  */
  void blow(double intensity);
  
  /*
   * @brief Turns the fan on.
   *
   * This method sets the fan to its maximum speed or a predefined "on" state.
   * The specific behavior depends on how the fan is controlled (e.g.,
   * setting the control pin to HIGH for a simple transistor-controlled fan).
  */
  void on();

  /**
   * @brief Turns the fan off.
   *
   * This method stops the fan. The specific behavior depends on how the
   * fan is controlled (e.g., setting the control pin to LOW).
  */
  void off();

 private:
  int pin; // pin connected to the fan.
};

#endif