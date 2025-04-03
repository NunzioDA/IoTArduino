/*
* Author: Nunzio D'Amore.
* Date: 03/04/2025
*
* The Allarm class allows playing an alarm melody using a buzzer 
* while ensuring non-blocking execution by utilizing the millis() function.
* This approach prevents delays that could interfere with other tasks 
* running on the microcontroller.
*/

#include "allarm.h"
#include "Arduino.h"

#define MELODY_NOTE_DURATION 500
#define RESET_TIME 700

Allarm::Allarm(int pin) : pin(pin), melody{800, 200}, melodyIndex(0), playing(false), startMillis(0)
{
  // Initializing all the parameters and
  // setting pin to OUTPUT mode
  pinMode(pin, OUTPUT);
}

void Allarm::play()
{
  // If the RESET_TIME is elapsed reset
  // all parameters
  if(this -> elapsed() > RESET_TIME)
  {
    this -> playing = false;
    this -> melodyIndex = 0;
    this -> startMillis = millis();
  }
  else{
    // If not playing play the current note
    if(!playing){
      this -> startMillis = millis();
      tone(this -> pin, this -> melody[melodyIndex], MELODY_NOTE_DURATION);
      this -> playing = true;
    }
    else{
      // If playing check if the note has
      // been played and update the melody index
      if(this -> elapsed() >= MELODY_NOTE_DURATION){
        this -> playing = false;

        // If we reached the end of the melody
        // start from the beginning
        if(this -> melodyIndex + 1 < MELODY_SIZE)
          this -> melodyIndex ++;
        else this -> melodyIndex = 0;
      }

    }
  }
}

// Returns the elapsed time
int Allarm::elapsed()
{
  return millis() - this -> startMillis;
}
