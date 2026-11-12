#include "common.h"

f32 BtlCharApi_GetHeight(s32 arg0);
extern f32 D_00385798;
extern f32 D_0038579C;
extern f32 D_003857A0;
extern f32 D_003857A4;
extern f32 D_003857A8;
extern f32 D_003857AC;

f32 func_001FA4F0(u8 *arg0, s32 arg1) {
    f32 temp_f2;

    temp_f2 = BtlCharApi_GetHeight(*(s32 *)(arg0 + 0x1534));
    if (arg1 == 1) {
        return (temp_f2 * D_003857A0) + D_003857A4;
    }
    if (arg1 == 0) {
        return (temp_f2 * D_00385798) + D_0038579C;
    }
    if (arg1 == 2) {
        return (temp_f2 * D_003857A8) + D_003857AC;
    }
    return 0.0f;
}
