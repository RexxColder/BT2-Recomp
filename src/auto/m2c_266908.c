#include "m2c_macros.h"

extern f32 D_00386EC0;

void func_00266908(s32 arg0) {
    f32 temp_f0;
    void *temp_a0;

    temp_a0 = arg0 + 0xAF0;
    temp_f0 = M2C_FIELD(temp_a0, f32 *, 0xA8) - D_00386EC0;
    M2C_FIELD(temp_a0, f32 *, 0xA8) = temp_f0;
    if (temp_f0 < 0.0f) {
        M2C_FIELD(temp_a0, f32 *, 0xA8) = 0.0f;
    }
}
