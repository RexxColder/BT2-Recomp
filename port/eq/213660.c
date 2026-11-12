#include "common.h"

void *BtlChar_GetPos(s32 arg0);
f32 BtlUtil_WrapAngle(f32 farg0);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
s32 func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
f32 cosf(f32 farg0);

s32 func_00213660(s32 arg0) {
    void *p;
    f32 f20;
    f32 f21;

    if (func_00211310(arg0, 2, 0x100) == 0) {
        return 0;
    }
    p = BtlChar_GetPos(arg0);
    f21 = *(f32 *)((u8 *)p + 0x94);
    p = BtlChar_GetPos(arg0);
    f20 = BtlUtil_WrapAngle(f21 + *(f32 *)((u8 *)p + 0x14));
    p = BtlChar_GetPos(arg0);
    *(f32 *)((u8 *)p + 0x14) = f20;
    p = BtlChar_GetPos(arg0);
    *(f32 *)((u8 *)p + 0xB4) = f20;
    p = BtlChar_GetPos(arg0);
    *(f32 *)((u8 *)p + 0xB0) = *(f32 *)((u8 *)p + 0xB0) * cosf(f21);
    return func_002113C0(arg0, 2, 0x100, 0);
}
