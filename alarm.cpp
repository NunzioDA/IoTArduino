/*
* Author: Nunzio D'Amore.
* Date: 03/04/2025
*
* The Alarm class allows playing an alarm melody using a buzzer 
* while ensuring non-blocking execution by utilizing the millis() function.
* This approach prevents delays that could interfere with other tasks 
* running on the microcontroller.
*/

#include "alarm.h"
#include "Arduino.h"

#define MELODY_NOTE_DURATION 500
#define RESET_TIME 700

Alarm::Alarm(int buzzerPin, int ledPin) : buzzerPin(buzzerPin), ledPin(ledPin), melody{800, 200}, melodyIndex(0), playing(false), startMillis(0)
{
  // setting pins to OUTPUT mode
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
}

void Alarm::stop()
{
  this -> playing = false;
  this -> melodyIndex = 0;
  this -> startMillis = millis();
  digitalWrite(this -> ledPin, LOW);
}

void Alarm::play()
{
  // If the RESET_TIME is elapsed reset
  // all parameters
  if(this -> elapsed() > RESET_TIME)
  {
    this -> stop();
  }
  else{
    // If not playing play the current note
    if(!playing){
      this -> startMillis = millis();
      tone(this -> buzzerPin, this -> melody[melodyIndex], MELODY_NOTE_DURATION);
      this -> playing = true;
    }
    else{
      // If playing check if the note has
      // been played and update the melody index
      if(this -> elapsed() >= MELODY_NOTE_DURATION){
        this -> playing = false;

        this -> ledStatus = !this -> ledStatus;
        digitalWrite(this -> ledPin, this -> ledStatus);

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
int Alarm::elapsed()
{
  return millis() - this -> startMillis;
}
