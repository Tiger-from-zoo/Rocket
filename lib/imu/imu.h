#ifndef DSR_IMU_LIB
#define DSR_IMU_LIB

#include<cstdint>
#include<Wire.h>
#include<types.h>

float accel_x, accel_y, accel_z;
int16_t accel_x_prev = 0;
int16_t accel_y_prev = 0;
int16_t accel_z_prev = 0;

void imu_init(char i2c_addr, Accel_Sensitivity_t sens);


#endif