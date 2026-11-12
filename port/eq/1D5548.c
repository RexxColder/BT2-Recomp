#include "common.h"

extern u8 *D_00387E9C;

u8 *func_001D54E8(u8 *a0, u8 *a1, s32 a2, s32 a3, s32 t0, s32 t1, s32 t2, s32 t3,
                  f32 f0, f32 f1, f32 f2, f32 f3, f32 f4, f32 f5, f32 f6, f32 f7,
                  f32 s0, f32 s1, f32 s2);
void func_00129C28(void *a0, void *a1);
void func_00129BB8(u8 *a0, void *a1, f32 farg0);
void *memcpy(void *arg0, void *arg1, u32 arg2);

/* 0x001D5548: spawns one record from two 16-byte blocks (copied to the stack) through
 * func_001D54E8 and fills its float and byte fields; the float stack arguments arg8..arg10
 * are the caller's 9th..11th arguments. */
void func_001D5548(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7,
                   f32 farg0, f32 farg1, f32 farg2, f32 farg3, f32 farg4, f32 farg5, f32 farg6, f32 farg7,
                   f32 arg8, f32 arg9, f32 arg10) {
    u8 blk[0xB0];
    u8 *s0;
    u8 *s1;
    f32 f0;
    f32 f1;
    f32 f3;
    f32 f4;
    f32 f2;

    memcpy(blk, arg0, 0x10);
    memcpy(blk + 0x10, arg1, 0x10);
    s0 = func_001D54E8(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7,
                       farg0, farg1, farg2, farg3, farg4, farg5, farg6, farg7,
                       arg8, arg9, arg10);
    if (s0 == NULL) {
        return;
    }
    s1 = s0 + 0x10;
    func_00129C28(s0, blk);
    func_00129C28(s1, blk + 0x10);
    *(f32 *)(s0 + 0x20) = farg0;
    func_00129BB8(s1, s1, farg0);

    f3 = farg3 - farg2;
    f4 = arg8 * 30.0f;
    if (farg1 == 0.0f) {
        f0 = 0.0f;
    } else {
        f0 = 1.0f / farg1;
    }
    f2 = arg9 * 30.0f;
    f1 = farg6 / f4;
    *(f32 *)(s0 + 0x24) = f0;
    *(f32 *)(s0 + 0x2C) = f3 / f4;
    *(f32 *)(s0 + 0x30) = farg4;
    *(f32 *)(s0 + 0x34) = farg5;
    *(f32 *)(s0 + 0x40) = farg7;
    *(f32 *)(s0 + 0x44) = f4;
    *(f32 *)(s0 + 0x48) = f2;
    *(u8 *)(s0 + 0x54) = (u8)(arg2 & 0xFF);
    *(u8 *)(s0 + 0x55) = (u8)(arg3 & 0xFF);
    *(u8 *)(s0 + 0x56) = (u8)(arg4 & 0xFF);
    *(u8 *)(s0 + 0x58) = (u8)(arg5 & 0xFF);
    *(u8 *)(s0 + 0x59) = (u8)(arg6 & 0xFF);
    *(u8 *)(s0 + 0x5B) = 1;
    *(f32 *)(s0 + 0x28) = farg2;
    *(f32 *)(s0 + 0x38) = farg6;
    *(s32 *)(s0 + 0x50) = 0;
    *(u8 *)(s0 + 0x57) = 0;
    *(u8 *)(s0 + 0x5A) = 0;
    *(u8 *)(s0 + 0x5C) = 0;
    *(f32 *)(s0 + 0x3C) = f1;
    *(f32 *)(s0 + 0x4C) = arg10;
    *(s32 *)(D_00387E9C + 0x1430) = *(s32 *)(D_00387E9C + 0x1430) + 1;
}
