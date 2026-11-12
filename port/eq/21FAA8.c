#include "common.h"

/* 0x0021FAA8: if (func_00211310(a0, 6, 1)) tail func_00215E30(a0, *(f32 *)(a0 + 0xB64), *(f32 *)(a0 + 0xB68)). */
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
void func_00215E30(s32 arg0, f32 farg0, f32 farg1);

void func_0021FAA8(s32 a0) {
    f32 f12;
    f32 f13;

    if (func_00211310(a0, 6, 1) == 0) {
        return;
    }
    f12 = *(f32 *)((u8 *)a0 + 0xB64);
    f13 = *(f32 *)((u8 *)a0 + 0xB68);
    func_00215E30(a0, f12, f13);
}
