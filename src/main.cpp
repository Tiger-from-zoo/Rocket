#include <Arduino.h>
// #include <TinyGPS++.h>
#include <imu.h>
#include<Wire.h>

/* CONSTANTS */
constexpr uint16_t GPSBaud = 9600;
constexpr float g16_x_offset =  0.03031;
constexpr float g16_y_offset = -0.02549;
constexpr float g16_z_offset = -0.02826;
constexpr float dps2000_x_offset = -2.72764;
constexpr float dps2000_y_offset =  0.58537;
constexpr float dps2000_z_offset = -0.27642;

uint8_t itr = 0;
double avg_x = 0;
double avg_y = 0;
double avg_z = 0;


// float accel_x, accel_y, accel_z;
// int16_t LSB_accel_x, LSB_accel_y, LSB_accel_z;

// The TinyGPS++ object
// TinyGPSPlus gps;

// HardwareSerial SerialGPS(2);

IMU imu(0x68, Accel_Sensitivity_t::g16, Gyro_Sensitivity_t::dps2000);
Acceleration_Vec *acv_p = &imu.accel_vec;
Euler_Rotation_Vec *erv_p = &imu.rotation_vec;


void setup() {
//   SerialGPS.begin(GPSBaud, SERIAL_8N1, 16, 17);
    imu.init();
    Serial.begin(9600);
    Serial.println("Starting IMU test");
    Serial.println("Starting in...");
    Serial.println("3");
    delay(1000);
    Serial.println("2");
    delay(1000);
    Serial.println("1");
    delay(1000);
    while (itr < 15) {
        imu.read_gyro();
        // Serial.println(imu.i2c_addr);
        Serial.println("gyro (X, Y, Z):");
        Serial.println(erv_p->x);
        Serial.println(erv_p->y);
        Serial.println(erv_p->z);
        avg_x += static_cast<double>(erv_p->x);
        avg_y += static_cast<double>(erv_p->y);
        avg_z += static_cast<double>(erv_p->z);
        delay(1000);
        itr++;
    }
    avg_x = (avg_x / static_cast<double>(itr));
    avg_y = (avg_y / static_cast<double>(itr));
    avg_z = (avg_z / static_cast<double>(itr));
}
 
void loop() {
    Serial.println("Average gyro per axis over 16 iterations: ");
    Serial.println(avg_x, 5);
    Serial.println(avg_y, 5);
    Serial.println(avg_z, 5);
    delay(5000);
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
