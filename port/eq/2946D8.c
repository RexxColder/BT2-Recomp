#include "common.h"

f32 ColTri_DistSqPoint(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void ColTri_GetPoint(s32 arg0, s32 arg1, f32 farg0, f32 farg1);

s32 ColSphere_TestTri(s32 arg0, u8 *arg1, s32 arg2) {
    f32 pt[2];
    f32 dist;
    f32 lim;

    dist = ColTri_DistSqPoint((s32)arg1, arg2, (s32)&pt[0], (s32)&pt[1]);
    lim = *(f32 *)(arg1 + 0x14);
    if (lim < dist) {
        return 0;
    }
    ColTri_GetPoint(arg0, arg2, pt[0], pt[1]);
    return 1;
}
