#include "pitches.h"

// notes in the melody:
int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};

int Led = 13; //define LED Interface
int buzzer = 8;
int buttonpin = 3; //define the mercury tilt switch sensor interface
int val = LOW;//define numeric variables val
  
void setup ()
{
  pinMode (Led, OUTPUT); //define LED as output interface
  pinMode (buzzer, OUTPUT);
  pinMode (buttonpin, INPUT); //define the mercury tilt switch sensor output interface
}
void loop ()
{
  val = digitalRead (buttonpin); //read the values assigned to the digital interface 3 val
  if (val == HIGH) //When the mercury tilt switch sensor detects a signal, LED flashes
  {
    digitalWrite (Led, HIGH);
    // iterate over the notes of the melody:
    for (int thisNote = 0; thisNote < 8; thisNote++) {
  
      // to calculate the note duration, take one second divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / noteDurations[thisNote];
      tone(8, melody[thisNote], noteDuration);
  
      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
      // stop the tone playing:
      noTone(8);
    }
  }
  else
  {
    digitalWrite (Led, LOW);
  }
}
