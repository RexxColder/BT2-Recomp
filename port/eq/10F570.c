#include "common.h"

s32 func_0020B6E0(s32 arg0);
s32 func_0020B7E0(s32 arg0);
void func_0010CFC8(s32 arg0, f32 farg0);
s32 func_0010CE18(s32 arg0);
extern f32 D_00383E58;
extern f32 D_00383E5C;
extern f32 D_00383E60;
extern f32 D_00383E64;

s32 func_0010F570(s32 arg0, s32 arg1) {
    s32 temp_s1;
    f32 var_f12;

    temp_s1 = func_0020B6E0(arg1);
    if (func_0020B7E0(arg1) != 0) {
        memset((void *)arg0, 0, 0xC);
        var_f12 = 0.25f;
        if (temp_s1 < 0x2710) {
            if (temp_s1 >= 0x3E9) {
                var_f12 = (((f32)temp_s1 - D_00383E58) / D_00383E5C) * D_00383E60 + D_00383E58;
            } else {
                var_f12 = D_00383E64;
            }
        }
        func_0010CFC8(arg0, var_f12);
        return func_0010CE18(arg0);
    }
    return func_0010CE18(arg0); /* asm 0x0010F5A0: a0 = s2 tambien en la rama sin vibracion */
}
