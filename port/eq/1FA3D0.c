#include "common.h"

f32 BtlCharApi_GetHeight(s32 arg0);
extern f32 D_00385784;
extern f32 D_00385788;
extern f32 D_0038578C;
extern f32 D_00385790;
extern f32 D_00385794;
extern u8 *D_003876A0;

void func_001FA3D0(u8 *arg0, u8 *arg1, s32 arg2) {
    f32 f0;

    f0 = BtlCharApi_GetHeight(*(s32 *)(arg0 + 0x1534)) * 0.5f + 1.0f;
    if (f0 < 10.0f) {
        f0 = 10.0f;
    }
    switch (arg2) {
    case 0:
        f0 = -f0;
        *(f32 *)arg1 = 0.0f;
        *(f32 *)(arg1 + 8) = f0 * D_00385784;
        *(f32 *)(arg1 + 4) = f0 * 1.5f;
        break;
    case 1:
        f0 = -f0;
        *(f32 *)arg1 = 0.0f;
        *(f32 *)(arg1 + 8) = f0 * D_00385788;
        *(f32 *)(arg1 + 4) = f0 + f0;
        break;
    case 2:
        f0 = -f0;
        *(f32 *)arg1 = 0.0f;
        *(f32 *)(arg1 + 8) = f0 * D_00385790;
        *(f32 *)(arg1 + 4) = f0 * D_0038578C;
        break;
    default:
        break;
    }
    if (*(s64 *)(D_003876A0 + 0x4D8) & 2) {
        *(f32 *)arg1 = *(f32 *)arg1 * D_00385794;
        *(f32 *)(arg1 + 4) = *(f32 *)(arg1 + 4) * D_00385794;
        *(f32 *)(arg1 + 8) = *(f32 *)(arg1 + 8) * D_00385794;
    }
}
