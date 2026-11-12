#include "common.h"

void *BtlChar_GetPos(void *arg0);
void BtlOpp_GetTargetPos(void *arg0, void *arg1);
f32 cosf(f32 farg0);
f32 func_002086B0(s32 arg0);
f32 func_00210D10(void *arg0);
s32 func_00211310(void *arg0, s32 arg1, s32 arg2);
void func_00312650(void *arg0, void *arg1, f32 *arg2);
f32 sinf(f32 farg0);

void func_00216550(u8 *arg0) {
    s32 sp[4];
    f32 pos[4];
    f32 f20;

    if (func_00211310(arg0, 0, 1) != 0) {
        BtlOpp_GetTargetPos(arg0, sp);
        pos[0] = sinf(*(f32 *)((u8 *)BtlChar_GetPos(arg0) + 0xB4));
        pos[1] = 0.0f;
        pos[2] = cosf(*(f32 *)((u8 *)BtlChar_GetPos(arg0) + 0xB4));
        pos[3] = 0.0f;
        f20 = func_002086B0(*(s32 *)(arg0 + 0x1534)) + pos[3];
        f20 = f20 + func_00210D10(arg0);
        pos[2] = pos[2] * f20;
        pos[0] = pos[0] * f20;
        func_00312650(BtlChar_GetPos(arg0), sp, pos);
    }
}
