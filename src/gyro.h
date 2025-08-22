#include <Arduino.h>
#include <Wire.h>

float accel_x, accel_y, accel_z;
int16_t accel_x_prev = 0;
int16_t accel_y_prev = 0;
int16_t accel_z_prev = 0;

void setup() {
  // Accelerometer start
  Wire.setClock(400000);
  Wire.begin();
  delay(250);

  Wire.beginTransmission(0x68);
  Wire.write(0x6B);
  Wire.write(0x00);
  Wire.endTransmission();
  Wire.beginTransmission(0x68);
  Wire.write(0x1C);
  Wire.write(0x10);
  Wire.endTransmission();

  // DFPlayer Mini start
  Serial.begin(9600);
  Serial.println((3088/4096));
}

void loop() {
  // Reading accelerometer values and detecting movement //
  Wire.beginTransmission(0x68);
  Wire.write(0x3B);
  Wire.endTransmission();
  Wire.requestFrom(0x68, 6);

  accel_x_prev = Wire.read()<<8 | Wire.read();
  accel_y_prev = Wire.read()<<8 | Wire.read();
  accel_z_prev = Wire.read()<<8 | Wire.read();

  // Converting raw accel data to G's //
  //float fin_accel_x, fin_accel_y, fin_accel_z;
  const float lsb_to_g = 4096.0f;
  
  accel_x = accel_x_prev / lsb_to_g;
  accel_y = accel_y_prev / lsb_to_g;
  accel_z = accel_z_prev / lsb_to_g;

  // DEBUG //
  //fin_accel_x = accel_x / lsb_to_g;
  //fin_accel_y = accel_y / lsb_to_g;
  //fin_accel_z = accel_z / lsb_to_g;
  // DEBUG //

  // Reset values for next iteration //
  // accel_x_prev = accel_x;
  // accel_y_prev = accel_y;
  // accel_z_prev = accel_z;

  // DEBUG //
  Serial.print("RAW X: ");
  Serial.print(accel_x_prev);
  Serial.print(" RAW Y: ");
  Serial.print(accel_y_prev);
  Serial.print(" RAW Z: ");
  Serial.println(accel_z_prev);
  Serial.print("X: ");
  Serial.print(accel_x, 5);
  Serial.print(" Y: ");
  Serial.print(accel_y, 5);
  Serial.print(" Z: ");
  Serial.println(accel_z, 5);
  Serial.println("");
  // DEBUG //
  
  delay(250);
}