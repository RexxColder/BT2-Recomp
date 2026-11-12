#include "m2c_macros.h"

s32 func_002AF5E8(void *arg0) {
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f1;
    f32 temp_f2;
    s32 var_v1;
    void *temp_v0;

    var_v1 = 0;
    M2C_FIELD(arg0, s8 *, 0x191) = 0;
    temp_v0 = M2C_FIELD(arg0, s32 *, 0) + 0xBD0;
    temp_f0 = M2C_FIELD(temp_v0, f32 *, 0x1C) - M2C_FIELD(temp_v0, f32 *, 0x20);
    M2C_FIELD(temp_v0, f32 *, 0x1C) = temp_f0;
    if (temp_f0 < 0.0f) {
        M2C_FIELD(temp_v0, f32 *, 0x1C) = 0.0f;
    }
    temp_f1 = M2C_FIELD(temp_v0, f32 *, 0x10);
    temp_f2 = M2C_FIELD(temp_v0, f32 *, 8);
    temp_f0_2 = temp_f1 + M2C_FIELD(temp_v0, f32 *, 0x18);
    M2C_FIELD(temp_v0, f32 *, 0x14) = temp_f1;
    M2C_FIELD(temp_v0, f32 *, 0x10) = temp_f0_2;
    if (temp_f2 <= temp_f0_2) {
        M2C_FIELD(temp_v0, f32 *, 0x10) = temp_f2;
        var_v1 = 1;
    }
    return var_v1;
}
