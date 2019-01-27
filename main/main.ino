int led = 6;
int button = 5;
int tiltSensor = 3;
int heartSensor = 0;

int isTilt = LOW;

bool ledOn = false;
bool buttonPressed = false;

unsigned long startTiltTime;
unsigned long currTime;

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
    currTime = millis();
    if (currTime - startTiltTime > 10000) { //not trigger again until 10 min passed
      digitalWrite(led, LOW);
      ledOn = false;
    }
  } else if (buttonPressed) { //allow user to signal they're ok and wait 10 min to check again
    currTime = millis();
    if (currTime - startTiltTime > 10000) {
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
      if (buttonPressed) {
         Serial.print(char('0'));
      } else {
         Serial.print(char('1'));
      }
    } else {
      digitalWrite(led, LOW);
    }
  }

}
