// GPS Neo-6M -> JSON over Serial
// Sends {"lat":..,"lon":..,"alt":..,"spd":..,"sat":..,"hdop":..,"fix":..} every 1s
// Web page (gps.html) reads via Web Serial API

#include <TinyGPS.h>
#include <SoftwareSerial.h>

#define GPS_RX 4
#define GPS_TX 3

SoftwareSerial gpsSerial(GPS_RX, GPS_TX);
TinyGPS gps;

void setup() {
  Serial.begin(9600);
  while (!Serial) { ; }
  gpsSerial.begin(9600);
  Serial.println(F("{\"status\":\"GPS Neo-6M iniciado\"}"));
}

void loop() {
  while (gpsSerial.available() > 0) {
    gps.encode(gpsSerial.read());
  }

  float flat, flon;
  unsigned long age;
  gps.f_get_position(&flat, &flon, &age);

  if (flat != TinyGPS::GPS_INVALID_F_ANGLE) {
    Serial.print(F("{\"lat\":"));
    Serial.print(flat, 6);
    Serial.print(F(",\"lon\":"));
    Serial.print(flon, 6);
    Serial.print(F(",\"alt\":"));
    Serial.print(gps.f_altitude(), 1);
    Serial.print(F(",\"spd\":"));
    Serial.print(gps.f_speed_kmph(), 1);
    Serial.print(F(",\"sat\":"));
    Serial.print(gps.satellites());
    Serial.print(F(",\"hdop\":"));
    Serial.print(gps.hdop() / 100.0, 1);
    Serial.print(F(",\"fix\":"));
    Serial.print(age < 2000 ? 1 : 0);
    Serial.println(F("}"));
  }

  // Se nao recebe dados por 5s, avisa
  static unsigned long lastData = 0;
  if (gps.satellites() > 0) lastData = millis();
  if (millis() - lastData > 5000) {
    Serial.println(F("{\"status\":\"Sem dados GPS - verifique antena\"}"));
    delay(1000);
  }
}
