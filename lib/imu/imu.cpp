#include<imu.h>

int16_t accel_x_buf = 0;
int16_t accel_y_buf = 0;
int16_t accel_z_buf = 0;

int16_t gyro_x_buf = 0;
int16_t gyro_y_buf = 0;
int16_t gyro_z_buf = 0;

static Acceleration_Vec accel_vec;
static Euler_Rotation_Vec rotation_vec;
static float accel_multiplier = 4096.0f; // LSB/g
static float gyro_multiplier = 32.8f;  // LSB/deg/s

void imu_set_power_state(char i2c_addr) {
  Wire.beginTransmission((uint8_t)i2c_addr);
  Wire.write(0x6B); // "PWR_MGMT_1" register
  Wire.write(0x00); // H_RESET, SLEEP, CYCLE, GYRO_STANDBY, PD_PTAT = 0, CLKSEL = 00 (Internal 20MHz clock)
  Wire.endTransmission();

  return;
}

void gyro_set_sens(char i2c_addr, Gyro_Sensitivity_t sens) {
  Wire.beginTransmission((uint8_t)i2c_addr);
  Wire.write(0x1B); // "GYRO_CONFIG" register
  Wire.write((uint8_t)sens);
  Wire.endTransmission();

  return;
}

void accel_set_sens(char i2c_addr, Accel_Sensitivity_t sens) {
  Wire.beginTransmission((uint8_t)i2c_addr);
  Wire.write(0x1C); // "ACCEL_CONFIG" register
  Wire.write((uint8_t)sens);
  Wire.endTransmission();

  return;
}

void imu_init(char i2c_addr, Accel_Sensitivity_t sens_a, Gyro_Sensitivity_t sens_g) {
  // Accelerometer start
  Wire.setClock(400000);
  Wire.begin();
  delay(250);

  imu_set_power_state(i2c_addr);
  
  accel_set_sens(i2c_addr, sens_a);
  gyro_set_sens(i2c_addr, sens_g);

  switch(sens_a) {
    case Accel_Sensitivity_t::g2:  accel_multiplier = 16384.0f;
    case Accel_Sensitivity_t::g4:  accel_multiplier = 8192.0f;
    case Accel_Sensitivity_t::g8:  accel_multiplier = 4096.0f;
    case Accel_Sensitivity_t::g16: accel_multiplier = 2048.0f;
    default:                       accel_multiplier = 4096.0f;
  }

  switch(sens_g) {
    case Gyro_Sensitivity_t::dps250 :  gyro_multiplier = 131.0f;
    case Gyro_Sensitivity_t::dps500 :  gyro_multiplier = 62.5f;
    case Gyro_Sensitivity_t::dps1000:  gyro_multiplier = 32.8f;
    case Gyro_Sensitivity_t::dps2000:  gyro_multiplier = 16.4f;
    default:                           gyro_multiplier = 32.8f;
  }
  
  return;
}

Acceleration_Vec read_accel(char i2c_addr) {
  Wire.beginTransmission((uint8_t)i2c_addr);
  Wire.write(0x3B); // "ACCEL_XOUT_H"
  Wire.endTransmission();

  Wire.requestFrom((uint8_t)i2c_addr, 6);

  accel_vec.x = (Wire.read()<<8 | Wire.read()) / accel_multiplier;
  accel_vec.y = (Wire.read()<<8 | Wire.read()) / accel_multiplier;
  accel_vec.z = (Wire.read()<<8 | Wire.read()) / accel_multiplier;

  return accel_vec;
}

Euler_Rotation_Vec read_gyro(char i2c_addr) {
  Wire.beginTransmission((uint8_t)i2c_addr);
  Wire.write(0x43); // "GYRO_XOUT_H"
  Wire.endTransmission();

  Wire.requestFrom((uint8_t)i2c_addr, 6);

  rotation_vec.x = (Wire.read()<<8 | Wire.read()) / gyro_multiplier;
  rotation_vec.y = (Wire.read()<<8 | Wire.read()) / gyro_multiplier;
  rotation_vec.z = (Wire.read()<<8 | Wire.read()) / gyro_multiplier;

  return rotation_vec;
}

