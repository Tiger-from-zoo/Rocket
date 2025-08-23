#ifndef DSR_IMU_LIB
#define DSR_IMU_LIB

#include<cstdint>
#include<Wire.h>
#include<types.h>

class IMU {
    public:
    Euler_Rotation_Vec rotation_vec;
    Acceleration_Vec accel_vec;

    IMU(char i2c_addr_, Accel_Sensitivity_t sens_a_, Gyro_Sensitivity_t sens_g_);

    void init();

    void read_accel();
    void read_gyro();

    private:
    const char i2c_addr;

    const Accel_Sensitivity_t sens_a;
    const Gyro_Sensitivity_t  sens_g;

    const float accel_multiplier; // LSB/g
    const float gyro_multiplier;  // LSB/deg/s

    void set_power_state();
    void gyro_set_sens();
    void accel_set_sens();

    inline uint16_t read16() {}

};

#endif