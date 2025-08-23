#ifndef DSR_TYPES_LIB
#define DSR_TYPES_LIB

#include<cstdint>

enum class Accel_Sensitivity_t : uint8_t {
    g2  = 0x00,
    g4  = 0x08,
    g8  = 0x10,
    g16 = 0x18
};

enum class Gyro_Sensitivity_t : uint8_t {
    dps250  = 0x00,
    dps500  = 0x08,
    dps1000  = 0x10,
    dps2000 = 0x18
};

// enum class Gyro_DLPF_t : 

typedef struct {
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
} Acceleration_Vec;

typedef struct {
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
} Euler_Rotation_Vec;

#endif