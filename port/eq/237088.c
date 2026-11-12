#include "common.h"

void *BtlChar_GetPos(s32 arg0);
f32 BtlUtil_WrapAngle(f32 farg0);
f32 cosf(f32 farg0);
void func_00215E30(f32 farg0, s32 arg1, f32 farg1);
extern f32 D_00386A34;

void func_00237088(s32 arg0) {
    u8 *base;
    u8 *pos;
    f32 var_f20;
    f32 var_f21;

    base = (u8 *)arg0;
    if (base[0xB54] != 0) {
        pos = (u8 *)BtlChar_GetPos(arg0);
        var_f21 = BtlUtil_WrapAngle(BtlUtil_WrapAngle(*(f32 *)(pos + 0xB4) + *(f32 *)(base + 0xB6C)) + D_00386A34);
        var_f20 = *(f32 *)(base + 0xB70);
    } else {
        pos = (u8 *)BtlChar_GetPos(arg0);
        var_f21 = BtlUtil_WrapAngle(*(f32 *)(pos + 0xB4) + *(f32 *)(base + 0xB6C));
        var_f20 = -*(f32 *)(base + 0xB70);
    }
    pos = (u8 *)BtlChar_GetPos(arg0);
    func_00215E30(var_f21, arg0, var_f20 * cosf(*(f32 *)(pos + 0x94)));
}
