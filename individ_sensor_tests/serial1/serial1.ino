void setup() {
  Serial.begin(9600);
  delay(100);
}

void loop() {
  Serial.print(char('0'));
  Serial.print(char('0'));
  Serial.print(char('0'));
  delay(2000);
  Serial.print(char('0'));
  Serial.print(char('0'));
  Serial.print(char('0'));
  delay(2000);
  Serial.print(char('0'));
  Serial.print(char('0'));
  Serial.print(char('0'));
  delay(3000);
  Serial.print(char('1'));
}
