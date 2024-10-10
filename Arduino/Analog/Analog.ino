int pinpot = A1;
int nilaipot;
void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600); 
}
void loop() {
  // put your main code here, to run repeatedly:
  nilaipot = analogRead(pinpot);
  Serial.println(nilaipot);
  delay(500);
}
