#include "common.h"

u8 *BtlChar_GetPos(s32 arg0);
s32 BtlPad_Test48(s32 arg0, s32 arg1);
f32 BtlUtil_WrapAngle(f32 farg0);
s32 func_001FA1D0(f32 farg0, s32 arg0);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
f32 func_002175B0(s32 arg0);

s32 func_00218328(s32 arg0) {
    f32 f20;
    f32 diff;
    f32 x;
    f32 ax;
    u8 *s0;

    if (BtlPad_Test48(arg0, 8) == 0) {
        return 0;
    }
    if (func_00211310(arg0, 1, 1) != 0) {
        return 0;
    }
    if (func_001FA1D0(0.5f, arg0) == 0) {
        return 0;
    }
    f20 = func_002175B0(arg0);
    BtlChar_GetPos(arg0);
    s0 = BtlChar_GetPos(arg0);
    diff = *(f32 *)(s0 + 0xB4) - *(f32 *)(s0 + 0xBC);
    x = BtlUtil_WrapAngle(f20 - BtlUtil_WrapAngle(diff));
    ax = (x < 0.0f) ? -x : x;
    if (1.0f < ax) {
        return 1;
    }
    return 0;
}
