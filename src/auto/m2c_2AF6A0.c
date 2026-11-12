#include "m2c_macros.h"

void func_002AF6A0(void *arg0) {
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f1;
    void *temp_v1;

    M2C_FIELD(arg0, s8 *, 0x191) = 0;
    temp_v1 = M2C_FIELD(arg0, s32 *, 0) + 0xBD0;
    temp_f0 = M2C_FIELD(temp_v1, f32 *, 0x1C) - M2C_FIELD(temp_v1, f32 *, 0x20);
    M2C_FIELD(temp_v1, f32 *, 0x1C) = temp_f0;
    if (temp_f0 < 0.0f) {
        M2C_FIELD(temp_v1, f32 *, 0x1C) = 0.0f;
    }
    temp_f0_2 = M2C_FIELD(temp_v1, f32 *, 0x10);
    temp_f1 = temp_f0_2 + 2.0f;
    M2C_FIELD(temp_v1, f32 *, 0x14) = temp_f0_2;
    M2C_FIELD(temp_v1, f32 *, 0x10) = temp_f1;
    if (M2C_FIELD(temp_v1, f32 *, 8) <= temp_f1) {
        M2C_FIELD(temp_v1, f32 *, 0x10) = 0.0f;
        M2C_FIELD(arg0, s8 *, 0x191) = 1;
    }
}
