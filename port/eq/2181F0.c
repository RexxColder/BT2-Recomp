#include "common.h"

s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
f32 BtlOpp_GetDistance(s32 arg0, f32 farg0);
f32 func_002086B0(s32 arg0);
f32 func_00210D10(s32 arg0);
void *BtlChar_GetPos(s32 arg0);

void func_002181F0(s32 arg0, f32 farg0) {
    f32 temp_f20;
    u8 *temp_v0;

    if (func_00211310(arg0, 0, 1) == 0) {
        return;
    }
    temp_f20 = BtlOpp_GetDistance(arg0, farg0);
    temp_f20 = temp_f20 - func_002086B0(*(s32 *)((u8 *)arg0 + 0x1534));
    temp_f20 = temp_f20 - func_00210D10(arg0);
    temp_f20 = temp_f20 / farg0;
    if (temp_f20 < 0.0f) {
        temp_f20 = 0.0f;
    }
    if (1.0f < temp_f20) {
        temp_f20 = 1.0f;
    }
    temp_v0 = (u8 *)BtlChar_GetPos(arg0);
    *(f32 *)(temp_v0 + 0xD4) = *(f32 *)(temp_v0 + 0xD4) * temp_f20;
}
