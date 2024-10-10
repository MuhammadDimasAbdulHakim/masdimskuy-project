int pinpot = A1;
int nilaipot;
float volt;
void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600); 
}
void loop() {
  // put your main code here, to run repeatedly:
  nilaipot = analogRead(pinpot);
  volt = nilaipot * (5.0 / 1023.0);
  Serial.println("Analog:");
  Serial.println(nilaipot);
  Serial.println("Tegangan:");
  Serial.println(volt);
  Serial.println("V");
  delay(500);
}
