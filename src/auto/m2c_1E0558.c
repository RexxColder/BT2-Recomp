#include "m2c_macros.h"

void func_001E0558(void *arg0, s32 arg1, void *arg2) {
    s32 var_t0;
    u32 temp_a1;
    void *temp_a0;
    void *var_a3;

    temp_a1 = arg1 & 0xFF;
    if (temp_a1 < (u8) M2C_FIELD(arg0, u8 *, 0x10F00)) {
        var_t0 = 0;
        temp_a0 = arg0 + (temp_a1 * 0x21E0);
        var_a3 = temp_a0 + 0x10;
        if (M2C_FIELD(temp_a0, s32 *, 0x1B0) > 0) {
            do {
                var_t0 += 1;
                M2C_FIELD(var_a3, f32 *, 0x150) = (f32) M2C_FIELD(arg2, f32 *, 0);
                M2C_FIELD(var_a3, f32 *, 0x154) = (f32) M2C_FIELD(arg2, f32 *, 4);
                M2C_FIELD(var_a3, f32 *, 0x158) = (f32) M2C_FIELD(arg2, f32 *, 8);
                M2C_FIELD(var_a3, f32 *, 0x15C) = (f32) M2C_FIELD(arg2, f32 *, 0xC);
                M2C_FIELD(var_a3, f32 *, 0x20) = (f32) M2C_FIELD(arg2, f32 *, 0);
                M2C_FIELD(var_a3, f32 *, 0x24) = (f32) M2C_FIELD(arg2, f32 *, 4);
                M2C_FIELD(var_a3, f32 *, 0x28) = (f32) M2C_FIELD(arg2, f32 *, 8);
                M2C_FIELD(var_a3, f32 *, 0x2C) = (f32) M2C_FIELD(arg2, f32 *, 0xC);
                var_a3 += 0x1B0;
            } while (var_t0 < M2C_FIELD(temp_a0, s32 *, 0x1B0));
        }
    }
}
