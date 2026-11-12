#include "common.h"

void func_003126C8(s32 arg0, s32 arg1, f32 farg0);
extern f32 D_00384070;

s32 StgGround_TestTri(s32 arg0, s32 arg1, s32 arg2, f32 farg0) {
    f32 x;
    f32 y;
    f32 m0;
    f32 m8;
    f32 m10;
    f32 m18;
    f32 m20;
    f32 m28;
    f32 t;
    f32 e1;
    f32 e2;
    f32 e3;
    s32 var_a0;
    s32 v0;

    x = *(f32 *)(arg0 + 0x0);
    y = *(f32 *)(arg0 + 0x8);
    m0 = *(f32 *)(arg1 + 0x0);
    m8 = *(f32 *)(arg1 + 0x8);
    m10 = *(f32 *)(arg1 + 0x10);
    m18 = *(f32 *)(arg1 + 0x18);
    m20 = *(f32 *)(arg1 + 0x20);
    m28 = *(f32 *)(arg1 + 0x28);
    t = ((*(f32 *)(arg1 + 0x3C) - (*(f32 *)(arg1 + 0x30) * x)) - (*(f32 *)(arg1 + 0x38) * y))
        / *(f32 *)(arg1 + 0x34);

    var_a0 = 0;
    e1 = ((m20 - m0) * (y - m8)) - ((m28 - m8) * (x - m0));
    if (e1 <= D_00384070) {
        e2 = ((m10 - m20) * (y - m28)) - ((m18 - m28) * (x - m20));
        if (e2 <= D_00384070) {
            e3 = ((m0 - m10) * (y - m18)) - ((m8 - m18) * (x - m10));
            if (e3 <= D_00384070) {
                var_a0 = 1;
            }
        }
    }
    v0 = 0;
    if ((farg0 < t) && (t < *(f32 *)(arg0 + 0x4)) && (var_a0 != 0)) {
        *(f32 *)(arg0 + 0x4) = t;
        *(s32 *)(arg0 + 0x20) = arg2;
        func_003126C8(arg0 + 0x10, arg1 + 0x30, farg0);
        v0 = 1;
    }
    return v0;
}
