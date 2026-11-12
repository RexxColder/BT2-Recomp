#include "m2c_macros.h"

void func_001E0A00(void *arg0, void *arg1) {
    s32 var_a2;
    void *var_v1;

    var_v1 = arg0 + 0x10;
    var_a2 = 0;
    if (M2C_FIELD(arg0, s32 *, 0x1B0) > 0) {
        do {
            var_a2 += 1;
            M2C_FIELD(var_v1, f32 *, 0x150) = (f32) M2C_FIELD(arg1, f32 *, 0);
            M2C_FIELD(var_v1, f32 *, 0x154) = (f32) M2C_FIELD(arg1, f32 *, 4);
            M2C_FIELD(var_v1, f32 *, 0x158) = (f32) M2C_FIELD(arg1, f32 *, 8);
            M2C_FIELD(var_v1, f32 *, 0x15C) = (f32) M2C_FIELD(arg1, f32 *, 0xC);
            M2C_FIELD(var_v1, f32 *, 0x20) = (f32) M2C_FIELD(arg1, f32 *, 0);
            M2C_FIELD(var_v1, f32 *, 0x24) = (f32) M2C_FIELD(arg1, f32 *, 4);
            M2C_FIELD(var_v1, f32 *, 0x28) = (f32) M2C_FIELD(arg1, f32 *, 8);
            M2C_FIELD(var_v1, f32 *, 0x2C) = (f32) M2C_FIELD(arg1, f32 *, 0xC);
            var_v1 += 0x1B0;
        } while (var_a2 < M2C_FIELD(arg0, s32 *, 0x1B0));
    }
}
