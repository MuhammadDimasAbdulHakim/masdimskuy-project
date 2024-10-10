int pinpot = A1;
int nilaipot;
int LeD = 9;
float volt;
float servo;
void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600); 
}
void loop() {
  // put your main code here, to run repeatedly:
  nilaipot = analogRead(pinpot);
  servo = nilaipot * (255.0 / 1023.0);
  Serial.println(servo);
  analogWrite(LeD, servo);
  delay(10);
}