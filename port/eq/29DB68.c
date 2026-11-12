#include "common.h"

f32 sceVu0InnerProduct(f32 *arg0, f32 *arg1);
f32 sqrtf(f32 arg0);
f32 sinf(f32 arg0);
f32 cosf(f32 arg0);
extern f32 D_003872B8;

/* 0x0029DB68: len = sqrt(dot(arg1, arg1)). When len == 0: arg0 = (0, 0, 0, 1). Else with x = arg2 * D_003872B8 * 0.5:
 * arg0 = (arg1[0], arg1[1], arg1[2]) * sin(x) / len, arg0[3] = cos(x). */
void func_0029DB68(f32 *arg0, f32 *arg1, f32 arg2) {
    f32 len;
    f32 x;
    f32 s;
    f32 c;
    f32 inv;

    len = sqrtf(sceVu0InnerProduct(arg1, arg1));
    if (len == 0.0f) {
        arg0[0] = 0.0f;
        arg0[1] = 0.0f;
        arg0[2] = 0.0f;
        arg0[3] = 1.0f;
        return;
    }
    x = arg2 * D_003872B8 * 0.5f;
    s = sinf(x);
    c = cosf(x);
    inv = 1.0f / len;
    arg0[0] = arg1[0] * inv * s;
    arg0[1] = arg1[1] * inv * s;
    arg0[2] = arg1[2] * inv * s;
    arg0[3] = c;
}
