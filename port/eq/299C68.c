#include "common.h"

void sceVu0Normalize();
f32 sceVu0InnerProduct();
void func_00312490();
s32 Quat_SlerpIdentity(s32 arg0, s32 arg1, f32 farg0);
f32 sqrtf(f32 farg0);

void Quat_FromVectors(s32 arg0, s32 arg1, s32 arg2, f32 farg0) {
    f32 v11[4];
    f32 v12[4];
    f32 v13[4];
    f32 *out;
    f32 dot;
    f32 len;
    f32 inv;

    out = (f32 *)arg0;
    sceVu0Normalize(v11, arg1);
    sceVu0Normalize(v12, arg2);
    func_00312490(v13, v11, v12);
    dot = sceVu0InnerProduct(v11, v12);
    len = sqrtf((dot + 1.0f) + (dot + 1.0f));
    inv = 1.0f / len;
    out[3] = len * 0.5f;
    out[2] = v13[2] * inv;
    out[0] = v13[0] * inv;
    out[1] = v13[1] * inv;
    if (farg0 != 1.0f) {
        Quat_SlerpIdentity(arg0, arg0, farg0);
    }
}
