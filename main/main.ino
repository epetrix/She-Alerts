int led = 6;
int button = 5;
int tiltSensor = 3;
int heartSensor = 0;

int isTilt = LOW;
int ledOn = 0;

unsigned long startTime;

void setup() {
  pinMode (led, OUTPUT);
  pinMode (button, INPUT);
  pinMode (tiltSensor, INPUT);
  pinMode (heartSensor, INPUT);
  Serial.begin(9600);
}

void loop() {
  isTilt = digitalRead (tiltSensor);
  if (ledOn == 1) {
    if (millis() - startTime > 10000) {
      digitalWrite(led, LOW);
      ledOn = 0;
    }
  } else {
    if (isTilt == HIGH) {
      digitalWrite(led, HIGH);
      ledOn = 1;
      startTime = millis();
      delay (5000); //wait for 5 seconds
    } else {
      digitalWrite(led, LOW);
    }
  }

}
