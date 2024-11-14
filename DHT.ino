#include "DHT.h"

#define DHTPIN 2      
#define DHTTYPE DHT22 

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println("DHT22 sensor!");

  dht.begin();
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
  Serial.println(" *C");
}
