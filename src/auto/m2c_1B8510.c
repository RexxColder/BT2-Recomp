#include "m2c_macros.h"

void func_001B8510(void *arg0, void *arg1) {
    s32 temp_v0;

    M2C_FIELD(arg1, f32 *, 0x50) = (f32) (M2C_FIELD(arg1, f32 *, 0x50) - 1.0f);
    if (M2C_FIELD(arg0, s32 *, 0x60) & 1) {
        M2C_FIELD(arg1, f32 *, 0x50) = 0.0f;
    }
    if (M2C_FIELD(arg1, f32 *, 0x50) <= 0.0f) {
        M2C_FIELD(arg1, f32 *, 0x50) = 0.0f;
        temp_v0 = M2C_FIELD(arg1, s32 *, 0x3C) - 0x10;
        M2C_FIELD(arg1, s32 *, 0x3C) = temp_v0;
        if (temp_v0 <= 0) {
            M2C_FIELD(arg1, s32 *, 0x3C) = 0;
            M2C_FIELD(arg1, s32 *, 0x5C) = (s32) (M2C_FIELD(arg1, s32 *, 0x5C) & ~1);
            M2C_FIELD(arg0, s32 *, 0x74) = (s32) (M2C_FIELD(arg0, s32 *, 0x74) - 1);
        }
    }
}
