int led = 6;
int button = 5;
int tiltSensor = 3;
int heartSensor = 0;

int isTilt = LOW;

bool ledOn = false;
bool buttonPressed = false;

unsigned long startTiltTime;

void setup() {
  pinMode (led, OUTPUT);
  pinMode (button, INPUT);
  pinMode (tiltSensor, INPUT);
  pinMode (heartSensor, INPUT);
  Serial.begin(9600);
}

void loop() {
  isTilt = digitalRead (tiltSensor);
  
  if (ledOn) {
    if (millis() - startTiltTime > 10000) { //not trigger >1x per 10 min
      digitalWrite(led, LOW);
      ledOn = false;
    }
  } else if (buttonPressed) {
    if (millis() - startTiltTime > 10000) { //not trigger >1x per 10 min
      buttonPressed = false;
    }
  } else {
    if (isTilt == HIGH) {
      digitalWrite(led, HIGH);
      ledOn = true;
      startTiltTime = millis();
      while (millis() - startTiltTime < 10000) { //wait 10 sec
        if (digitalRead(button) == LOW) {
          ledOn = false;
          buttonPressed = true;
          digitalWrite(led, LOW);
          break;
        }
      }
    } else {
      digitalWrite(led, LOW);
    }
  }

}
