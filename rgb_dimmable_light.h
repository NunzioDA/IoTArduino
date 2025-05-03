#ifndef RGBDimmableLight_h
#define RGBDimmableLight_h

#include <Arduino.h>

/**
  * Author: Nunzio D'Amore.
  * Date: 09/04/2025
  *
  * @brief RGBDimmableLight is a class for controlling an RGB LED where each color channel can be dimmed.
  *
  * This class allows setting the color of an RGB LED by specifying a color name.
  * It assumes that the connected pins support PWM (Pulse Width Modulation) for dimming
  * the intensity of each red, green, and blue component.
  *
  * ## Usage:
  * ```cpp
  * RGBDimmableLight myLight(3, 5, 6); // Define an RGB LED connected to digital pins 3 (R), 5 (G), 6 (B)
  * myLight.setColor("#F52E9D");      // Set the LED to red
  * // ... other color names can be supported in the implementation
  * ```
 */
class RGBDimmableLight{
 public:
  /**
   * @brief Constructor for the RGBDimmableLight class.
   *
   * @param r_pin The pin connected to the red LED component.
   * @param g_pin The pin connected to the green LED component.
   * @param b_pin The pin connected to the blue LED component.
   * It is expected that these pins support PWM output for dimming functionality
  */
  RGBDimmableLight(int r_pin, int g_pin, int b_pin);

  /**
   * @brief Sets the color of the RGB LED based on a color hex.
   *
   * This method takes a string representing the desired color and sets the
   * appropriate intensity levels for the red, green, and blue LED components.
   *
   * @param hexColor A string representing the desired color in hexadecimal.
  */
  void setColor(String hexColor);

  /**
   * @brief Sets the color of the RGB LED based on a color name.
   *
   * This method takes the r, g, b intensities to set the led color.
  */
  void setColor(int red, int green, int blue);

  /**
   * @brief Switches the light on
   *
   * This method is used to switch the light on
   *
  */
  void on();

  /**
   * @brief Switches the light off
   *
   * This method is used to switch the light off
   *
  */
  void off();
  /**
   * @brief Used to get the current light color
   *
  */
  void getColor(int color[3]);
  /**
  * @brief Used to check if the light is on
  */
  bool isOn();

 private:
  int r_pin; // pin connected to the red LED component.
  int g_pin; // pin connected to the green LED component.
  int b_pin; // pin connected to the blue LED component.
  int r_intensity; // intensity of the red LED component.
  int g_intensity; // intensity of the blue LED component.
  int b_intensity; // intensity of the green LED component.
  bool status; // Current light status
};

#endif