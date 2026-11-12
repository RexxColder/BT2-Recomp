#include "common.h"

void BtlAnim_SetBlend(f32 farg0, u8 *arg1);
void func_00203888(u8 *arg0, s32 arg1, s32 arg2);
s32 func_00203C58(u8 *arg0, s64 arg1);
void func_00203C88(u8 *arg0, s64 arg1);
u8 *func_00210DD8(u8 *arg0);
u8 *func_00211288(u8 *arg0);
s32 func_00211310(u8 *arg0, s32 arg1, s32 arg2);
void func_002113C0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);
extern f32 D_00386830;

s32 func_002305F0(u8 *arg0) {
    if (func_00211310(arg0, 7, 0x2000) != 0) {
        BtlAnim_SetBlend(D_00386830, arg0);
        func_002113C0(arg0, 1, 0x40000, 1);
        func_002113C0(arg0, 1, 0x80000, 1);
        func_002113C0(arg0, 6, 0x10, 1);
        if (func_00203C58(func_00211288(func_00210DD8(arg0)), (s64)0x8000 << 16) != 0) {
            func_002113C0(arg0, 0, 0x4000, 1);
            func_00203888(arg0, 0x186A0, 1);
            func_00203C88(func_00211288(func_00210DD8(arg0)), (s64)0x8000 << 16);
        }
        return 0x21;
    }
    return -1;
}
