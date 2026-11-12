#include "common.h"

s32 func_003126C8(u8 *a0, s32 a1);
s32 func_002113C0(u8 *a0, s32 a1, s32 a2, s32 a3);

/* 0x001FC3B0: stores six sub-records (func_003126C8 at +0x210..+0x260) and fills the block at +0x150
 * from the arguments; arg12 (the 13th argument) is a flag word: bit 1 calls func_002113C0 once,
 * bit 8 tail-calls it with 0x400 (returns its result, else 0). */
s32 func_001FC3B0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7,
                  s32 arg8, s32 arg9, s32 arg10, s32 arg11, s32 arg12,
                  f32 farg0, f32 farg1, f32 farg2, f32 farg3, f32 farg4, f32 farg5) {
    u8 *s0;

    func_003126C8(arg0 + 0x210, arg1);
    func_003126C8(arg0 + 0x220, arg2);
    func_003126C8(arg0 + 0x230, arg3);
    func_003126C8(arg0 + 0x240, arg4);
    func_003126C8(arg0 + 0x250, arg5);
    func_003126C8(arg0 + 0x260, arg6);

    s0 = arg0 + 0x150;
    *(s32 *)(s0 + 0x138) = arg7;
    *(s32 *)(s0 + 0x140) = arg9;
    *(s32 *)(s0 + 0x13C) = arg8;
    *(s32 *)(s0 + 0x144) = arg10;
    *(f32 *)(s0 + 0x120) = farg0;
    *(f32 *)(s0 + 0x124) = farg1;
    *(f32 *)(s0 + 0x128) = farg2;
    *(f32 *)(s0 + 0x12C) = farg3;
    *(f32 *)(s0 + 0x130) = farg4;
    *(f32 *)(s0 + 0x134) = farg5;
    *(s32 *)(s0 + 0x14C) = arg11;
    *(s32 *)(s0 + 0x148) = arg11;
    *(s32 *)(s0 + 0x150) = arg12;

    if ((arg12 & 1) != 0) {
        func_002113C0(arg0, 0xE, 0x40, 1);
    }
    if ((arg12 & 8) != 0) {
        return func_002113C0(arg0, 0xE, 0x400, 1);
    }
    return 0;
}
