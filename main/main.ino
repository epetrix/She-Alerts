//SENSORS
int led = 6;              
int button = 5;
int tiltSensor = 3;
int heartSensor = 0;

int isTilt = LOW;

//BOOLEANS
bool ledOn = false;
bool buttonPressed = false;
bool highBMP = false; 

//TIME
unsigned long startTiltTime;
unsigned long currTime;

//VARIABLES
int samp_size = 4; 
int rise_thresh = 4;

//SETUP
void setup() {
  pinMode (led, OUTPUT);
  pinMode (button, INPUT);
  pinMode (tiltSensor, INPUT);
  pinMode (heartSensor, INPUT);
  Serial.begin(9600);
}

//LOOP
void loop() {
  //INIT
  isTilt = digitalRead (tiltSensor);
  float reads[samp_size], sum; 
  long int now, ptr; 
  float last, reader, start;
  float first, second, third, before, print_value;  
  bool rising; 
  int rise_count; 
  int n; 
  long int last_beat;

  //INITIALIZE ARRAY 
  for(int i = 0; i < samp_size; i++) {
    reads[i] = 0; 
   }

  sum = 0; 
  ptr = 0; 

  while(1) {
    n = 0; 
    start = millis(); 
    reader = 0.;

    do {
      reader += analogRead(heartSensor);
      n++;
      now = millis(); 
    }

    while(now < start + 20); 
    reader /= n; //average

    sum -= reads[ptr];
    sum += reader;
    reads[ptr] = reader;
    last = sum / samp_size; 

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
    }

    if (last > before) {
      rise_count++; 
      if(!rising && rise_count > rise_thresh) {
        rising = true; 
        first = millis() - last_beat;
        last_beat = millis(); 

        print_value = 60000. / (0.4 * first + 0.3 * second + 0.3 * third); 
        isTilt = digitalRead (tiltSensor);

        
        //IF HEART RATE IS HIGH!!! && YOU'VE FALLEN!!!
        if(print_value > 100 && isTilt == HIGH) {
          Serial.print("BPM \t"); 
          Serial.print(print_value); 
          Serial.println(" "); 

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
              Serial.println(char('0'));
            } else {
              Serial.println(char('1'));
            }
          } else {
            digitalWrite(led, LOW);
          }
         }       
        }
       third = second; 
       second = first; 
      }
    }

    else {
      rising = false; 
      rise_count = 0; 
    }

    before = last; 
    ptr++; 
    ptr %= samp_size; 
  }
}
