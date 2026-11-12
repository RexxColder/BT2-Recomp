#include "common.h"

u8 *BtlChar_GetPos(s32 arg0);
void BtlOpp_GetDelta(s32 arg0, void *arg1);
f32 BtlUtil_WrapAngle(f32 farg0);
f32 atan2f(f32 farg0, f32 farg1);
f32 fabsf(f32 farg0);
extern f32 D_00385A10;

f32 func_00210A98(s32 arg0) {
    f32 sp[4];
    f32 temp_f20;
    u8 *temp_s0;

    BtlOpp_GetDelta(arg0, sp);
    if ((fabsf(sp[0]) < D_00385A10) && (fabsf(sp[2]) < D_00385A10)) {
        return 0.0f;
    }
    temp_f20 = atan2f(sp[0], sp[2]);
    BtlChar_GetPos(arg0);
    temp_s0 = BtlChar_GetPos(arg0);
    return BtlUtil_WrapAngle(temp_f20 - BtlUtil_WrapAngle(*(f32 *)(temp_s0 + 0x14) + *(f32 *)(temp_s0 + 0x94)));
}
