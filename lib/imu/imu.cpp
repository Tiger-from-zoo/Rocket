#include<imu.h>

constexpr uint8_t bytes_6 = 6;

float accel_sens_float(Accel_Sensitivity_t sens_) {
  switch(sens_) {
    case Accel_Sensitivity_t::g2:  return 16384.0f;
    case Accel_Sensitivity_t::g4:  return 8192.0f;
    case Accel_Sensitivity_t::g8:  return 4096.0f;
    case Accel_Sensitivity_t::g16: return 2048.0f;
    default:                       return 4096.0f;
  }
}

float gyro_sens_float(Gyro_Sensitivity_t sens_) {
  switch(sens_) {
    case Gyro_Sensitivity_t::dps250 :  return 131.0f;
    case Gyro_Sensitivity_t::dps500 :  return 62.5f;
    case Gyro_Sensitivity_t::dps1000:  return 32.8f;
    case Gyro_Sensitivity_t::dps2000:  return 16.4f;
    default:                           return 131.0f;
  }
}

IMU::IMU(
  uint8_t i2c_addr_,
  Accel_Sensitivity_t sens_a_,
  Gyro_Sensitivity_t sens_g_,
  float accel_x_offset_,
  float accel_y_offset_,
  float accel_z_offset_,
  float gyro_x_offset_,
  float gyro_y_offset_,
  float gyro_z_offset_
) :
  i2c_addr(i2c_addr_),
  accel_multiplier(accel_sens_float(sens_a_)), 
  gyro_multiplier(gyro_sens_float(sens_g_)),
  sens_a(sens_a_),
  sens_g(sens_g_), 
  accel_x_offset(accel_x_offset_),
  accel_y_offset(accel_y_offset_),
  accel_z_offset(accel_z_offset_),
  gyro_x_offset(gyro_x_offset_),
  gyro_y_offset(gyro_y_offset_),
  gyro_z_offset(gyro_z_offset_) {}

void IMU::set_power_state(uint8_t pwr_state_) {
  Wire.beginTransmission(this->i2c_addr);
  Wire.write(0x6B); // "PWR_MGMT_1" register
  Wire.write(pwr_state_); // H_RESET, SLEEP, CYCLE, GYRO_STANDBY, PD_PTAT = 0, CLKSEL = 01 (PLL)
  Wire.endTransmission();

  return;
}

void IMU::gyro_set_sens() {
  Wire.beginTransmission(this->i2c_addr);
  Wire.write(0x1B); // "GYRO_CONFIG" register
  Wire.write(static_cast<uint8_t>(this->sens_g));
  Wire.endTransmission();

  return;
}

void IMU::accel_set_sens() {
  Wire.beginTransmission(this->i2c_addr);
  Wire.write(0x1C); // "ACCEL_CONFIG" register
  Wire.write(static_cast<uint8_t>(this->sens_a));
  Wire.endTransmission();

  return;
}

void IMU::init() {
  // Wire.setClock(400000);
  Wire.begin();
  delay(250);

  IMU::set_power_state(0x80); // H_RESET
  delay(1000);
  IMU::set_power_state(0x00); // Default power state
  
  IMU::accel_set_sens();
  IMU::gyro_set_sens();
  
  return;

}
void IMU::read_accel() {
  Wire.beginTransmission(this->i2c_addr);
  Wire.write(0x3B); // "ACCEL_XOUT_H"
  Wire.endTransmission();

  Wire.requestFrom(this->i2c_addr, bytes_6);
  this->accel_vec.x = static_cast<float>(read16() / this->accel_multiplier) + accel_x_offset;
  this->accel_vec.y = static_cast<float>(read16() / this->accel_multiplier) + accel_y_offset;
  this->accel_vec.z = static_cast<float>(read16() / this->accel_multiplier) + accel_z_offset;

  return;
}

void IMU::read_gyro() {
  Wire.beginTransmission(this->i2c_addr);
  Wire.write(0x43); // "GYRO_XOUT_H"
  Wire.endTransmission();

  Wire.requestFrom(this->i2c_addr, bytes_6);
  this->rotation_vec.x = static_cast<float>(read16() / this->gyro_multiplier) + gyro_x_offset;
  this->rotation_vec.y = static_cast<float>(read16() / this->gyro_multiplier) + gyro_y_offset;
  this->rotation_vec.z = static_cast<float>(read16() / this->gyro_multiplier) + gyro_z_offset;

  return;
}

inline int16_t IMU::read16() {
  return int16_t(Wire.read()<<8 | Wire.read());
}
