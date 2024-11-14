#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define SS_PIN 10
#define RST_PIN 9
#define ACCESS_DELAY 2000  // Durasi akses diizinkan (2 detik)
#define DENIED_DELAY 1000  // Durasi akses ditolak (1 detik)

// Inisialisasi objek RFID dan LCD
MFRC522 mfrc522(SS_PIN, RST_PIN);   
LiquidCrystal_I2C lcd(0x27, 16, 2); // Alamat I2C LCD

// Daftar UID yang diizinkan
String allowedUIDs[] = {
  "02 6F 86 C4 84 60 00",
  "04 38 41 92 51 63 80",
  "E7 60 56 3F"
};

void setup() {
  // Inisialisasi komunikasi serial dan SPI
  Serial.begin(9600);  
  SPI.begin();          
  mfrc522.PCD_Init();   

  // Pesan awal di serial monitor
  Serial.println("Tempatkan kartu di RFID...");

  // Inisialisasi LCD
  lcd.init();        
  lcd.backlight();   
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Siapkan Kartu!");
}

void loop() {
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return; // Jika tidak ada kartu, lanjutkan
  }

  // Pilih kartu
  if (!mfrc522.PICC_ReadCardSerial()) {
    return; // Jika tidak dapat membaca kartu, lanjutkan
  }

  // Menampilkan UID di Serial Monitor dan LCD
  String content = readRFID(); 

  // Cek apakah kartu diizinkan
  if (isAuthorized(content)) {
    grantAccess();  // Fungsi untuk memberi akses
  } else {
    denyAccess();   // Fungsi untuk menolak akses
  }

  // Tampilkan kembali pesan "Siapkan Kartu!" setelah akses diberikan atau ditolak
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Siapkan Kartu!");
}

// Membaca UID kartu RFID
String readRFID() {
  String content = "";
  Serial.print("UID tag : ");
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  content.toUpperCase();  // Ubah UID menjadi huruf besar
  return content;
}

// Mengecek apakah kartu diizinkan berdasarkan UID
bool isAuthorized(String content) {
  // Loop untuk memeriksa apakah UID ada di daftar yang diizinkan
  for (int i = 0; i < sizeof(allowedUIDs) / sizeof(allowedUIDs[0]); i++) {
    if (content.substring(1) == allowedUIDs[i]) {
      return true;  // Jika cocok, akses diizinkan
    }
  }
  return false;  // Jika tidak cocok, akses ditolak
}

// Fungsi untuk memberikan akses jika kartu diizinkan
void grantAccess() {
  Serial.println("Akses diizinkan");
  lcd.clear();  // Membersihkan layar LCD
  lcd.setCursor(0, 0);
  lcd.print("Akses Diizinkan");
  lcd.setCursor(0, 1);
  lcd.print("Selamat Datang!");
  delay(ACCESS_DELAY);
}

// Fungsi untuk menolak akses jika kartu tidak diizinkan
void denyAccess() {
  Serial.println("Akses ditolak");
  lcd.clear();  // Membersihkan layar LCD
  lcd.setCursor(0, 0);
  lcd.print("Akses Ditolak");
  lcd.setCursor(0, 1);
  lcd.print("Coba Lagi!");
  delay(DENIED_DELAY);
}
