#include "common.h"

void func_002088F0(s32 arg0, s32 arg1);
f32 sinf(f32 arg0);
f32 cosf(f32 arg0);
s32 func_00129BB8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 farg0);
void func_00129B28(s32 arg0, s32 arg1, s32 arg2);
void Vec3_Normalize(s32 arg0, s32 arg1);

void func_00183DE0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 farg0) {
    f32 buf[6];
    f32 *vec;

    vec = buf;
    func_002088F0(arg1, (s32)&buf[4]);
    vec[0] = sinf(buf[5]);
    vec[1] = 0.0f;
    vec[2] = cosf(buf[5]);
    vec[3] = 1.0f;
    func_00129BB8((s32)vec, (s32)vec, arg2, arg3, farg0);
    func_00129B28(arg0, arg0, (s32)vec);
    Vec3_Normalize(arg0, arg0);
}
