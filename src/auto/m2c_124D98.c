#include "m2c_macros.h"

s32 func_00126040();                                /* extern */
void *func_00203CC0(s32);                           /* extern */
s32 func_00210DD8(s32);                             /* extern */

void func_00124D98(s32 arg0) {
    void *temp_s0;
    void *temp_v0;

    temp_s0 = arg0 + 0x10A0;
    temp_v0 = func_00203CC0(func_00210DD8(func_00126040(arg0)));
    M2C_FIELD(temp_s0, f32 *, 0x7C) = (f32) ((f32) M2C_FIELD(temp_v0, s32 *, 0) / (f32) M2C_FIELD(temp_v0, s32 *, 4));
    M2C_FIELD(temp_s0, f32 *, 0x80) = (f32) ((f32) M2C_FIELD(temp_v0, s32 *, 0xC) / (f32) M2C_FIELD(temp_v0, s32 *, 0x10));
    M2C_FIELD(temp_s0, s32 *, 0x84) = (s32) M2C_FIELD(temp_v0, s32 *, 0x14);
}
