#include "common.h"

void func_002B1B50(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
f32 func_00297FE0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
f32 func_001017F0(s32 arg0, s32 arg1);

f32 func_002B1CB8(s32 arg0) {
    s32 sp0;
    s32 sp4;
    s32 s0;
    s32 t1;
    s32 s1;
    s32 i;
    f32 var_f0;
    f32 x;

    sp0 = 0x7F;
    sp4 = 0x40;
    s0 = *(s32 *)(arg0 + 0x2C);
    func_002B1B50(arg0 + 0xD0, (s32)&sp0, (s32)&sp4, arg0);

    t1 = 0x1C;
    if (!(s0 & 1)) {
        t1 = -1;
    }
    if (s0 & 2) {
        t1 = 0x18;
    }
    if (s0 & 4) {
        t1 = 0x1A;
    }
    if (s0 & 8) {
        t1 = 0x31;
    }
    if (s0 & 0x10) {
        t1 = 0x2C;
    }
    s1 = (s0 & 0x20) ? 0x3C25 : -1;

    var_f0 = (((f32)sp0 / 127.0f) - 1.0f) * 200.0f;
    /* cvt.w.s (truncates toward zero) of var_f0 */
    x = var_f0;
    i = (s32)x;
    if (i > 0) {
        i = 0;
    }
    if (i < -0x3C0) {
        i = -0x3C0;
    }

    if (t1 >= 0) {
        var_f0 = func_00297FE0(1, t1, sp0, sp4, 0);
    }
    if (s1 >= 0) {
        var_f0 = func_001017F0(s1, i);
    }
    return var_f0;
}
