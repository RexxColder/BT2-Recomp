#include "common.h"

void *BtlChar_GetPos(void *a0);
s32 BtlPad_Test48(void *a0, s32 a1);
s32 BtlPad_Test4C(void *a0, s32 a1);
f32 BtlUtil_WrapAngle(f32 f12);
s32 func_00211310(void *a0, s32 a1, s32 a2);
s32 func_00212820(void *a0, s32 a1);
extern f32 D_00386C4C;
extern f32 D_00386C50;

s32 func_0023D1E0(void *arg0, s32 arg1) {
    s32 (*s1fn)(void *, s32);
    s32 a1;
    s32 s2v;
    f32 f0;
    f32 af;

    a1 = arg1 & 0xFF;
    if (a1 != 0) {
        s1fn = BtlPad_Test48;
    } else {
        s1fn = BtlPad_Test4C;
    }
    if (func_00212820(arg0, a1) == 0) {
        return -1;
    }
    if (func_00211310(arg0, 0, 0x100) != 0) {
        if (s1fn(arg0, 8) != 0) {
            return 0x26;
        }
        if (s1fn(arg0, 0xA) != 0) {
            return 0x26;
        }
        return -1;
    }
    s2v = BtlPad_Test4C(arg0, 0xA);
    if (s2v != 0) {
        s1fn = BtlPad_Test48;
    }
    if (s1fn(arg0, 0xE) != 0) {
        f0 = BtlUtil_WrapAngle(*(f32 *)((u8 *)BtlChar_GetPos(arg0) + 0x14) - *(f32 *)((u8 *)arg0 + 0x150));
        af = (f0 < 0.0f) ? -f0 : f0;
        return (af < D_00386C4C) ? 0x23 : 0x24;
    }
    if (s1fn(arg0, 0xF) != 0) {
        f0 = BtlUtil_WrapAngle(*(f32 *)((u8 *)BtlChar_GetPos(arg0) + 0x14) - *(f32 *)((u8 *)arg0 + 0x150));
        af = (f0 < 0.0f) ? -f0 : f0;
        return (af < D_00386C50) ? 0x24 : 0x23;
    }
    if (s1fn(arg0, 0xC) != 0 || s1fn(arg0, 0xD) != 0) {
        BtlUtil_WrapAngle(*(f32 *)((u8 *)BtlChar_GetPos(arg0) + 0x14) - *(f32 *)((u8 *)arg0 + 0x150));
        return 0x25;
    }
    if (s2v != 0) {
        return 0x22;
    }
    return -1;
}
