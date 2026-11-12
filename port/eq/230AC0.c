#include "common.h"

s32 BtlAnim_SetBlend(f32 farg0, s32 arg0, s32 arg1);
s32 func_001FA288(f32 farg0, s32 arg0, s32 arg1);
s32 func_00203888(s32 arg0, s32 arg1, s32 arg2);
s32 func_00203C58(s32 arg0, s64 arg1);
void func_00203C88(s32 arg0, s64 arg1);
s32 func_00210DD8(s32 arg0);
s32 func_00211288(s32 arg0);
s32 func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_0023C710(s32 arg0);
extern f32 D_00386850;

s32 func_00230AC0(s32 arg0, f32 farg0) {
    if (func_001FA288(farg0, arg0, 0x18C) != 0) {
        BtlAnim_SetBlend(D_00386850, arg0, 0x18D);
        return func_0023C710(arg0);
    }
    if (func_001FA288(D_00386850, arg0, 0x18D) != 0) {
        if (func_00203C58(func_00211288(func_00210DD8(arg0)), (s32)0x80000000) != 0) {
            func_002113C0(arg0, 0, 0x4000, 1);
            func_00203888(arg0, 0x186A0, 1);
            func_00203C88(func_00211288(func_00210DD8(arg0)), (s32)0x80000000);
        }
        return 0x99;
    }
    return -1;
}
