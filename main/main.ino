int led = 6;
int button = 5;
int tiltSensor = 3;
int heartSensor = 0;

void setup() {
  pinMode (led, OUTPUT);
  pinMode (button, INPUT);
  pinMode (tiltSensor, INPUT);
  pinMode (heartSensor, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

}
