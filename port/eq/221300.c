#include "common.h"

void BtlAnim_SetBlend(f32 farg0, s32 arg1);
void *BtlChar_GetPos(s32 arg0);
s32 BtlPad_Test48(s32 arg0, s32 arg1);
f32 BtlUtil_WrapAngle(f32 farg0);
s32 func_001FA288(s32 arg0, s32 arg1);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
s32 func_00212820(s32 arg0);
s32 func_00218838(s32 arg0, s32 arg1);
s32 func_0023F410(s32 arg0);
extern f32 D_00385FA8;
extern f32 D_00385FAC;

s32 func_00221300(s32 arg0) {
    s32 s2;
    s32 t;
    u8 *pa;
    u8 *pb;

    if (func_001FA288(arg0, 0xEE) == 0) {
        return -1;
    }
    BtlAnim_SetBlend(D_00385FA8, arg0);
    if (func_00211310(arg0, 0, 2) != 0) {
        return (func_00212820(arg0) == 0) ? 0x21 : 0x26;
    }
    if (func_00212820(arg0) == 0) {
        return 0xA6;
    }
    if (func_00211310(arg0, 1, 0x80000) != 0) {
        return 0xA6;
    }
    s2 = (BtlPad_Test48(arg0, 0xD) != 0) ? 0x27 : -1;
    if (BtlPad_Test48(arg0, 0xC) != 0) {
        s2 = ((func_0023F410(arg0) & 0x1000) == 0) ? 0x29 : 0x27;
    }
    t = (BtlPad_Test48(arg0, 0xE) != 0) ? 0x23 : s2;
    s2 = (BtlPad_Test48(arg0, 0xF) != 0) ? 0x24 : t;
    if (s2 < 0) {
        return 0xA6;
    }
    if (func_00218838(arg0, 1) == 0) {
        return s2;
    }
    pa = (u8 *)BtlChar_GetPos(arg0);
    pb = (u8 *)BtlChar_GetPos(arg0);
    *(f32 *)(pa + 0xB4) = BtlUtil_WrapAngle(*(f32 *)(pb + 0xB4) + D_00385FAC);
    return s2;
}
