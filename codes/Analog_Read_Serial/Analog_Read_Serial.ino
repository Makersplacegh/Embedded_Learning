
int pot = A0;
void setup() {
  // put your setup code here, to run once:
  pinMode(pot, INPUT);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  int readVal = analogRead(pot);
Serial.println(readVal);
delay(50);

}
