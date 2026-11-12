#include "common.h"

void ColBox_GetCenter(s32 arg0, f32 *arg1);
void ColBox_GetHalf(s32 arg0, f32 *arg1);
void ColSeg_GetMidpoint(s32 arg0, f32 *arg1);
void func_00312650(f32 *arg0, f32 *arg1, f32 *arg2);
f32 fabsf(f32 arg0);

s32 ColBox_TestSegment(s32 arg0, s32 arg1) {
    f32 cen[4], half[4], mid[4], tv[4];
    f32 eps = 0.0078125f;
    f32 A, B, C;

    ColBox_GetCenter(arg0, cen);
    ColBox_GetHalf(arg0, half);
    ColSeg_GetMidpoint(arg1, mid);
    func_00312650(tv, (f32 *)(arg1 + 0x10), mid);
    func_00312650(mid, mid, cen);

    if (half[0] + fabsf(tv[0]) < fabsf(mid[0])) {
        return 0;
    }
    if (half[1] + fabsf(tv[1]) < fabsf(mid[1])) {
        return 0;
    }
    if (half[2] + fabsf(tv[2]) < fabsf(mid[2])) {
        return 0;
    }
    A = fabsf(tv[2]) + eps;
    B = fabsf(tv[1]) + eps;
    C = fabsf(tv[0]) + eps;
    if (half[1] * A + half[2] * B < fabsf(mid[1] * tv[2] - mid[2] * tv[1])) {
        return 0;
    }
    if (half[0] * A + half[2] * C < fabsf(mid[2] * tv[0] - mid[0] * tv[2])) {
        return 0;
    }
    if (half[0] * B + half[1] * C < fabsf(mid[0] * tv[1] - mid[1] * tv[0])) {
        return 0;
    }
    return 1;
}
