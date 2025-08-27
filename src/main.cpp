#include <Arduino.h>
// #include <TinyGPS++.h>
#include <imu.h>
#include<Wire.h>
 
constexpr uint16_t GPSBaud = 9600;

// float accel_x, accel_y, accel_z;
// int16_t LSB_accel_x, LSB_accel_y, LSB_accel_z;

// The TinyGPS++ object
// TinyGPSPlus gps;

// HardwareSerial SerialGPS(2);

IMU imu(0x68, Accel_Sensitivity_t::g4, Gyro_Sensitivity_t::dps500);
Acceleration_Vec *acv_p = &imu.accel_vec;
Euler_Rotation_Vec *erv_p = &imu.rotation_vec;


void setup() {
//   SerialGPS.begin(GPSBaud, SERIAL_8N1, 16, 17);
    imu.init();
    Serial.begin(9600);
    Serial.println("Starting IMU test");
}
 
void loop() {
    imu.read_accel();
    // Serial.println(imu.i2c_addr);
    Serial.println("Accel (X, Y, Z):");
    Serial.println(acv_p->x);
    Serial.println(acv_p->y);
    Serial.println(acv_p->z);
    delay(1000);
    // Serial.print("SerialGPS available: ");
    // Serial.println(SerialGPS.available());

    // while (SerialGPS.available() > 0){
        // // Serial.println("Test");
        // // delay(1000);
        // char c = SerialGPS.read();
        // gps.encode(c);
        // // Serial.print(c);
        // // Serial.print(Serial2.read());
        // if(gps.location.isUpdated()) {
            // //location_msg = String(gps.location.lat(), 3) + String(gps.location.lng(), 3);
            // Serial.print("Lat: ");
            // Serial.println(gps.location.lat());
            // Serial.print("Lon: ");
            // Serial.println(gps.location.lng());
            // Serial.print("H: ");
            // Serial.println(gps.altitude.meters());
            // Serial.print("Speed: ");
            // Serial.println(gps.speed.mps());
            
        // }
    // }
}
