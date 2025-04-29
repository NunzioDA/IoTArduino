#ifndef Alarm_h
#define Alarm_h

#include <Arduino.h>

/*
* Author: Nunzio D'Amore.
* Date: 03/04/2025
*
* The Alarm class allows playing an alarm melody using a buzzer and 
* while ensuring non-blocking execution by utilizing the millis() function.
* This approach prevents delays that could interfere with other tasks 
* running on the microcontroller.
*/
class Alarm
{
  public:
    /**
     * @brief Constructor: Initializes the Alarm object.
     * @param buzzerPin The digital pin connected to the buzzer.
     * @param ledPin The digital pin connected to the led.
     */
    Alarm(int buzzerPin, int ledPin);

    /**
     * @brief Starts playing the alarm melody.
     */
    void play();

    /**
     * @brief Stops playing the alarm melody.
     */
    void stop();


  private:
    /**
     * @brief Stores the digital pin connected to the buzzer.
     */
    int buzzerPin;
    /**
     * @brief Stores the digital pin connected to the led.
     */
    int ledPin;

    /**
     * @brief Constant defining the number of notes in the melody.
     */
    static const int MELODY_SIZE = 2;

    /**
     * @brief Array storing the frequency values (in Hz) for the alarm melody notes.
     * Each element represents a note's frequency.
     */
    int melody[MELODY_SIZE];

    /**
     * @brief Keeps track of the current note being played in the melody array.
     */
    int melodyIndex;

    /**
     * @brief Keeps track of the current ledStatus.
     */
    bool ledStatus;

    /**
     * @brief Boolean flag indicating whether the alarm melody is currently playing.
     */
    bool playing;

    /**
     * @brief Stores the value of millis() when the current note started playing.
     */
    int startMillis;

    /**
     * @brief Calculates the elapsed time since the start of the current note.
     * @return The elapsed time in milliseconds.
     */
    int elapsed();
};

#endif