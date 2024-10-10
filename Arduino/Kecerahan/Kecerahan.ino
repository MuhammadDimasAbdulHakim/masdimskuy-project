#include <Servo.h>
Servo servo;
int pinpot = A1;
int nilaipot;
int LeD = 9;
float volt;
float kecerahan;
void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600); 
 servo.attach(9);
}
void loop() {
  // put your main code here, to run repeatedly:
  nilaipot = analogRead(pinpot);
  kecerahan = nilaipot * (180.0 / 1023.0);
  Serial.println(kecerahan);
  servo.write(kecerahan);
  delay(10);
}
