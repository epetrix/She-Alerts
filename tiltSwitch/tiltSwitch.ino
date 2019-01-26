int Led = 13 ;/ / define LED Interface
int buttonpin = 3; / / define the mercury tilt switch sensor interface
int val ;/ / define numeric variables val
void setup ()
{
pinMode (Led, OUTPUT) ;/ / define LED as output interface
pinMode (buttonpin, INPUT) ;/ / define the mercury tilt switch sensor output interface
http://keyes-arduino.taobao.com
}
void loop ()
{
val = digitalRead (buttonpin) ;/ / read the values assigned to the digital interface 3 val
if (val == HIGH) / / When the mercury tilt switch sensor detects a signal, LED flashes
{
digitalWrite (Led, HIGH);
}
else
{
digitalWrite (Led, LOW);
}
}
