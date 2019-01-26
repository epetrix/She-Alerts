#include "pitches.h"

int Led = 13; //define LED Interface
int buzzer = 8;
int buttonpin = 3; //define the mercury tilt switch sensor interface
int val = LOW; //define numeric variables val
  
void setup ()
{
  pinMode (Led, OUTPUT); //define LED as output interface
  pinMode (buzzer, OUTPUT); 
  pinMode (buttonpin, INPUT); //define the mercury tilt switch sensor output interface
}
void loop ()
{
  val = digitalRead (buttonpin); //read the values assigned to the digital interface 3 val
  
  while (val == HIGH) //When the mercury tilt switch sensor detects a signal, LED flashes
  {
    digitalWrite(buzzer, HIGH);
  }
    digitalWrite (buzzer, LOW);  
}
