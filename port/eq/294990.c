#include "m2c_macros.h"

extern void ColBox_AddPointKeepW(s32 arg0, s32 arg1);
extern s32 func_003126C8(s32 arg0, s32 arg1);

void ColBounds_AddSphere(s32 arg0, s32 arg1) {
    f32 v[4];
    f32 r;

    func_003126C8((s32)v, arg1);
    r = *(f32 *)(arg1 + 0x10);
    v[0] = v[0] + r;
    v[1] = v[1] + r;
    v[2] = v[2] + r;
    ColBox_AddPointKeepW(arg0, (s32)v);
    func_003126C8((s32)v, arg1);
    r = *(f32 *)(arg1 + 0x10);
    v[0] = v[0] - r;
    v[1] = v[1] - r;
    v[2] = v[2] - r;
    ColBox_AddPointKeepW(arg0, (s32)v);
}
