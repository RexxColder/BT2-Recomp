#include "common.h"

extern f32 sqrtf(f32 farg0);
f32 ColLine_DistSqPoint(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

/* 0x00294EF0 ColLine_DistPoint (BT3 name): sqrt of ColLine_DistSqPoint(pt, a, b, out) (the four arguments pass through). */
f32 ColLine_DistPoint(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    f32 d2 = ColLine_DistSqPoint(arg0, arg1, arg2, arg3);

    return sqrtf(d2);
}
