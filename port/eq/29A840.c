#include "common.h"

extern f32 D_00387254;
extern f32 D_00387258;
f32 sqrtf(f32 farg0);
f32 fabsf(f32 farg0);
s32 func_003126C8(s32 arg0, void *arg1);

s32 Quat_Unpack(s32 arg0, u64 arg1) {
    f32 v[4];
    f32 sum;
    f32 w;
    s32 s1;
    s32 i;

    s1 = (s32)(arg1 >> 60);
    for (i = 0; i < 3; i++) {
        v[i] = ((f32)(s32)(((u32)(arg1 >> (20 * i))) & 0xFFFFF) * D_00387254 - 0.5f) * D_00387258;
    }

    sum = 0.0f;
    for (i = 0; i < 3; i++) {
        sum = sum + v[i] * v[i];
    }
    w = sqrtf(fabsf(1.0f - sum));

    for (i = 3; i > s1; i--) {
        v[i] = v[i - 1];
    }
    v[s1] = w;
    return func_003126C8(arg0, v);
}
