#include "common.h"

s32 BtlChar_GetPos(s32 arg0);
s32 BtlObjXf_Update(s32 arg0);
f32 BtlUtil_WrapAngle(f32 farg0);
s32 func_001FA3A8(s32 arg0);
f32 func_00200550(s32 arg0, s32 arg1, s32 arg2);
void func_00201568(f32 farg0, s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
void func_00201968(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_00201B90(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
f32 func_00210A98(s32 arg0);
s32 func_00211288(s32 arg0);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
s32 func_00240FA0(s32 arg0, s32 arg1);
s32 func_002417E8(s32 arg0, s32 arg1);
s32 func_00241820(s32 arg0, s32 arg1);
s32 func_00241868(s32 arg0, s32 arg1);
s32 func_002418A0(s32 arg0, s32 arg1);
extern f32 D_003858E0;
extern f32 D_003858E4;

s32 func_00201D90(s32 arg0, s32 arg1) {
    s32 sp[4];
    f32 f20;
    s32 s4;
    s32 s0;
    s32 s1;
    s32 r;
    u8 *p;

    if (func_00211310(arg0, 3, 4) != 0) {
        return 0;
    }
    p = (u8 *)arg1;
    if (*(s32 *)(p + 0x64) == 0) {
        return 0;
    }
    s4 = 1;
    f20 = func_00200550(arg0, arg1, (s32)sp);
    if (!(fabsf(BtlUtil_WrapAngle(*(f32 *)(BtlChar_GetPos(arg0) + 0x14) - f20)) < D_003858E0)) {
        s4 = 0;
    }
    p = *(u8 **)(arg1 + 0x64);
    s1 = *(s32 *)(p + 4);
    s0 = func_00211288(*(s32 *)p);
    r = func_00240FA0(s0, s1);
    if ((r != 0 && r != 2) || !(D_003858E4 < fabsf(func_00210A98(s0)))) {
        if (func_001FA3A8(BtlObjXf_Update(arg0)) & 0x100000) {
            if (*(s32 *)(arg1 + 0x50) & 0x10) {
                r = func_002418A0(s0, s1);
            } else {
                r = func_00241868(s0, s1);
            }
        } else if (*(s32 *)(arg1 + 0x50) & 0x10) {
            r = func_00241820(s0, s1);
        } else {
            r = func_002417E8(s0, s1);
        }
        if (r == 0) {
            r = 3;
        }
        if (r == 1) {
            return 0;
        }
        if (r == 2) {
            func_00201968(arg0, s0, arg1, r);
        } else if ((u32)(r - 0x1B) < 2U) {
            func_00201B90(arg0, s0, arg1, r);
        } else if (*(s32 *)(arg0 + 0xADC) > 0) {
            func_00201968(arg0, s0, arg1, r);
        } else {
            func_00201568(f20, arg0, s0, arg1, r, s4, (s32)sp);
        }
        return 1;
    }
    return 0;
}
