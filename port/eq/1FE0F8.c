#include "common.h"

void *BtlChar_GetPos(s32 arg0);
s32 BtlObjXf_Update(s32 arg0);
f32 BtlUtil_WrapAngle(f32 arg0);
s32 func_001FA3A8(s32 arg0);
s32 func_00211288(s32 arg0);
s32 func_0023E520(s32 arg0);
f32 fabsf(f32 arg0);
extern f32 D_0038586C;

s32 func_001FE0F8(s32 arg0, s32 arg1) {
    f32 temp_f20;
    f32 temp_wrap;
    s32 temp_s0_2;
    s32 temp_v0;
    s32 var_s3;
    s32 var_v0;
    u8 *temp_s0;
    u8 *temp_pos;

    var_s3 = 0;
    temp_v0 = func_00211288(arg1);
    temp_s0 = (u8 *)BtlChar_GetPos(temp_v0);
    temp_pos = (u8 *)BtlChar_GetPos(temp_v0);
    temp_f20 = BtlUtil_WrapAngle(*(f32 *)(temp_s0 + 0x14) + *(f32 *)(temp_pos + 0x94));
    temp_wrap = BtlUtil_WrapAngle(temp_f20 - *(f32 *)((u8 *)BtlChar_GetPos(arg0) + 0xB4));
    if (fabsf(temp_wrap) < D_0038586C) {
        var_s3 = 1;
    }
    temp_s0_2 = func_001FA3A8(BtlObjXf_Update(temp_v0));
    if (func_0023E520(arg0) != 0x4C) {
        var_v0 = 1;
    } else if (((temp_s0_2 & 0x100000) != 0) && ((temp_s0_2 & 0x01000000) != 0)) {
        var_v0 = 0;
    } else {
        var_v0 = (var_s3 == 0) ? 1 : 0;
    }
    return var_v0;
}
