#include "common.h"

extern f32 D_00384638;
extern f32 D_0038463C;

void func_0012A360(f32 farg0, u8 *arg1, u8 *arg2, s32 arg3, u8 *arg4);
s32 func_001E70B0(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3, s32 arg4, u8 *arg5, u8 *arg6,
                  u8 *arg7, f32 farg0);
void func_001E72F8(u8 *arg0, u8 *arg1);
void func_001E7208(u8 *arg0, s32 arg1);
void func_001E7238(u8 *arg0, u8 *arg1);
void func_001E7268(u8 *arg0, f32 farg0);
s32 func_001E71D8(u8 *arg0, s32 arg1);

s32 func_001501C0(u8 *arg0, u8 *arg1, u8 *arg2, u8 *arg3, u8 arg4, u8 *arg5, s32 arg6,
                  u8 *arg7, f32 farg0, f32 farg1, f32 farg2, f32 farg3, f32 *arg8) {
    (void)farg0; /* f12 (entF) is passed by both callers but unused (asm reads only f13..f15) */
    u8 sp[0x90];
    f32 scale;
    f32 ratio;
    f32 q;
    f32 cur;

    if ((arg4 & 1) != 0 && *(s32 *)arg3 == 0) {
        scale = (f32)*(s16 *)(arg1 + 0x18) * D_00384638 * farg2;
        func_0012A360(scale, sp, arg7, arg6, arg3);
        *(f32 *)(sp + 0xC) = 1.0f;
        func_001E70B0(arg3, arg2, 0, 0, arg1[5], sp, arg0 + 536 * arg1[3] + 1664, arg5, farg3);
        func_001E72F8(arg3, arg7);
        func_001E7208(arg3, 1);
        *arg8 = 1.0f;
    }

    if (*(s32 *)arg3 == 0) {
        return 0;
    }

    if ((arg4 & 8) != 0) {
        scale = (f32)*(s16 *)(arg1 + 0x18) * D_0038463C * farg2;
        func_0012A360(scale, sp, arg7, arg6, arg3);
        *(f32 *)(sp + 0xC) = 1.0f;
        func_001E7238(arg3, sp);
    }

    if ((arg4 & 0x20) != 0) {
        ratio = farg2 / farg1;
        q = *(f32 *)(arg1 + 0x10) / *(f32 *)(arg1 + 0xC);
        cur = *arg8 * ratio;
        func_001E7268(arg3, cur);
        *arg8 = *arg8 + q * farg2;
    }

    if ((arg4 & 0x40) != 0) {
        func_001E72F8(arg3, arg7);
    }

    if ((arg4 & 2) != 0) {
        return func_001E71D8(arg3, arg1[4]);
    }
    return 0;
}
