#include <Arduino.h>
#include <TinyGPS++.h>
 
static const uint32_t GPSBaud = 9600;

// The TinyGPS++ object
TinyGPSPlus gps;

HardwareSerial SerialGPS(2);

void setup() {
  SerialGPS.begin(GPSBaud, SERIAL_8N1, 16, 17);
  Serial.begin(9600);

  Serial.println("Starting GPS test");
}
 
void loop() {
    // Serial.print("SerialGPS available: ");
    // Serial.println(SerialGPS.available());

    while (SerialGPS.available() > 0){
        // Serial.println("Test");
        // delay(1000);
        char c = SerialGPS.read();
        gps.encode(c);
        // Serial.print(c);
        // Serial.print(Serial2.read());
        if(gps.location.isUpdated()) {
            //location_msg = String(gps.location.lat(), 3) + String(gps.location.lng(), 3);
            Serial.print("Lat: ");
            Serial.println(gps.location.lat());
            Serial.print("Lon: ");
            Serial.println(gps.location.lng());
            Serial.print("H: ");
            Serial.println(gps.altitude.meters());
            
        }
    }
}
