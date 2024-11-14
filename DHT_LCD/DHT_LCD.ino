#include "DHT.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define DHTPIN 2      
#define DHTTYPE DHT22 

LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT dht(DHTPIN, DHTTYPE);
int sda = A4;
int scl = A5;

void setup() {
  Serial.begin(9600);
  Serial.println("DHT22 sensor!");

  dht.begin();
  lcd.init();
  lcd.backlight();
  lcd.clear();
}

void loop() {
  delay(2000);
  float kelembapan = dht.readHumidity();
  float suhu = dht.readTemperature();
  if (isnan(kelembapan) || isnan(suhu)) {
    Serial.println("Gagal membaca dari sensor DHT!");
    return;
  }
  Serial.print("Kelembapan: ");
  Serial.print(kelembapan);
  Serial.print(" %\t");
  Serial.print("Suhu: ");
  Serial.print(suhu);
  Serial.println(" C");

  lcd.setCursor(0,0);
  lcd.print("Kelembapan:");
  lcd.print(kelembapan);
  lcd.print(" %");
  lcd.setCursor(0,1);
  lcd.print("Suhu:");
  lcd.print(suhu);
  lcd.print(" C");
}
