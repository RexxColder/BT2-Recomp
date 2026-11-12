#include "m2c_macros.h"

void func_001E19F0(void *arg0, void *arg1) {
    s32 var_a2;
    void *var_v1;

    var_a2 = 0;
    if (M2C_FIELD(arg0, u8 *, 0x21CC) != 0) {
        var_v1 = arg0 + 0x15C;
        do {
            var_a2 += 1;
            M2C_FIELD(var_v1, f32 *, -0x13C) = (f32) M2C_FIELD(arg1, f32 *, 0);
            M2C_FIELD(var_v1, f32 *, -0x138) = (f32) M2C_FIELD(arg1, f32 *, 4);
            M2C_FIELD(var_v1, f32 *, -0x134) = (f32) M2C_FIELD(arg1, f32 *, 8);
            M2C_FIELD(var_v1, f32 *, -0x130) = (f32) M2C_FIELD(arg1, f32 *, 0xC);
            M2C_FIELD(var_v1, f32 *, -0xC) = (f32) M2C_FIELD(arg1, f32 *, 0);
            M2C_FIELD(var_v1, f32 *, -8) = (f32) M2C_FIELD(arg1, f32 *, 4);
            M2C_FIELD(var_v1, f32 *, -4) = (f32) M2C_FIELD(arg1, f32 *, 8);
            M2C_FIELD(var_v1, f32 *, 0) = (f32) M2C_FIELD(arg1, f32 *, 0xC);
            var_v1 += 0x1B0;
        } while (var_a2 < (s32) M2C_FIELD(arg0, u8 *, 0x21CC));
    }
}
