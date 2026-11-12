#include "common.h"

u8 *func_001C14A0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, u8 *arg6, f32 farg0, f32 farg1);

/* 0x001C17F8(a0, a1, a2, a3, t0, t1, t2, f12, f13): r = func_001C14A0(a0, a1, (s16)a2, (s16)a3, 7, t1, t2, f12, f13)
 * (GUESS arity: the asm passes these seven ints and two floats through); when r is not NULL: r+0xC = (s8)t0 byte,
 * r+0xD = t1 byte, r+0x10 = f12, r+0x14 = f13, r+0x18/0x1C/0x20 = the three floats at t2. */
void func_001C17F8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, u8 *arg6, f32 farg0, f32 farg1) {
    s32 s1 = (s8)arg4;
    u8 s2 = (u8)arg5;
    u8 *r;

    r = func_001C14A0(arg0, arg1, (s16)arg2, (s16)arg3, 7, arg5, arg6, farg0, farg1);
    if (r == NULL) {
        return;
    }
    r[0xC] = (u8)s1;
    r[0xD] = s2;
    *(f32 *)(r + 0x10) = farg0;
    *(f32 *)(r + 0x14) = farg1;
    *(f32 *)(r + 0x18) = *(f32 *)(arg6 + 0);
    *(f32 *)(r + 0x1C) = *(f32 *)(arg6 + 4);
    *(f32 *)(r + 0x20) = *(f32 *)(arg6 + 8);
}
