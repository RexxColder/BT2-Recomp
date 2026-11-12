#include "common.h"

s32 func_00126040(s32 arg0);
s32 BtlChar_GetPos(s32 arg0);
f32 fabsf(f32 farg0);
f32 ceilf(f32 farg0);
f32 floorf(f32 farg0);
extern f32 D_003840E4;

f32 func_001216C0(s32 arg0) {
    f32 temp_f20;
    f32 temp_f21;
    f32 temp_f22;
    s32 temp_v0;

    temp_v0 = func_00126040(arg0);
    temp_f22 = D_003840E4;
    temp_v0 = BtlChar_GetPos(temp_v0);
    temp_f20 = fabsf(*(f32 *)(temp_v0 + 0xC4)) / temp_f22;
    temp_f21 = floorf(temp_f20);
    return (temp_f20 + (temp_f20 - temp_f21)) * (ceilf(temp_f20) * 0.5f) * temp_f22;
}
