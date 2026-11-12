#include "m2c_macros.h"

extern void StgAabb_SetEmpty(s32 arg0);
extern void ColBox_AddPoint(s32 arg0, s32 arg1);
extern s32 func_003126C8(s32 arg0, s32 arg1);

void ColBounds_OfSphere(s32 arg0, s32 arg1) {
    f32 v[4];
    f32 r;

    StgAabb_SetEmpty(arg0);
    func_003126C8((s32)v, arg1);
    r = *(f32 *)(arg1 + 0x10);
    v[0] = v[0] + r;
    v[1] = v[1] + r;
    v[2] = v[2] + r;
    ColBox_AddPoint(arg0, (s32)v);
    func_003126C8((s32)v, arg1);
    r = *(f32 *)(arg1 + 0x10);
    v[0] = v[0] - r;
    v[1] = v[1] - r;
    v[2] = v[2] - r;
    ColBox_AddPoint(arg0, (s32)v);
}
