// Pulse Monitor Test Script
int ledPin = 13;
int sensorPin = 0;
double alpha = 0.75;
int period = 20;
double change = 0.0;

void setup () {
  pinMode (ledPin, OUTPUT);
  Serial.begin (115200);
}

void loop () {
  static double oldValue = 0;
  static double oldChange = 0;
  int rawValue = analogRead (sensorPin);
  double value = alpha * rawValue + (1 - alpha) * oldValue;
  Serial.print (rawValue);
  Serial.print (",");
  Serial.println (value);
  oldValue = value;
  delay (period);
}

int ledc = 10;  
int sensorPin = 0;
int period = 100;
int change, oldvalue, value;
void setup ()
{
  pinMode(ledc, OUTPUT);
  Serial.begin (9600);
}
void loop ()
{
  value = analogRead (sensorPin);
  change = abs(oldvalue - value);
  if(change >= 2 )
  {
    Serial.println (change);
    analogWrite(ledc, 0); 
  }
  else
  { 
    analogWrite(ledc,255); 
  }
  oldvalue = value;
  delay (period);
}

