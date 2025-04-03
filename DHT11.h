#ifndef DHT11_h
#define DHT11_h

#include <DFRobot_DHT11.h>
#include <Arduino.h>


/*
* Author: Nunzio D'Amore.
* Date: 03/04/2025
*
* The DHT11 class reads ambient temperature and humidity
* from DHT11 sensor. This class is based on DFRobot_DHT11.
*
* ## Usage:
* ```cpp
*   DHT11 DHT(10);
*   DHT.read();
*   DHT.temperature();
*   DHT.humidity();
* ```
*/
class DHT11
{
  public:
    /**
     * @brief Constructor: Initializes the DHT11 object.
     * @param pin The digital pin connected to the DHT11 sensor.
     */
    DHT11(int pin);

    /**
     * @brief Reads the temperature and humidity data from the DHT11 sensor.
     */
    void read();

    /**
     * @brief Returns the last read temperature value.
     * @return The temperature in degrees Celsius.
     */
    float temperature();

    /**
     * @brief Returns the last read humidity value.
     * @return The relative humidity in percentage.
     */
    float humidity();

    /**
     * @brief Reads and returns the temperature value from the DHT11 sensor.
     * @return The temperature in degrees Celsius.
     */
    float readTemperature();

    /**
     * @brief Reads and returns the humidity value from the DHT11 sensor.
     * @return The relative humidity in percentage.
     */
    float readHumidity();


  private:
    /**
     * @brief Stores the digital pin connected to the DHT11 sensor.
     */
    int pin;

    /**
     * @brief Instance of the DFRobot_DHT11 library for handling the sensor.
     */
    DFRobot_DHT11 DHT;
};

#endif