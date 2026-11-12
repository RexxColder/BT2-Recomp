#include "common.h"

extern f32 D_00387228;
f32 sqrtf(f32 farg0);
f32 sinf(f32 farg0);
f32 cosf(f32 farg0);

void Quat_FromAxisAngle(s32 arg0, f32 farg0, f32 farg1, f32 farg2, f32 farg3) {
    f32 *out;
    f32 len;
    f32 half;
    f32 s;
    f32 inv;

    out = (f32 *)arg0;
    s = farg0 * farg0 + farg1 * farg1;
    s = s + farg2 * farg2;
    len = sqrtf(s);
    if (D_00387228 < len) {
        half = farg3 * 0.5f;
        s = sinf(half);
        inv = 1.0f / len;
        out[2] = farg2 * inv * s;
        out[0] = farg0 * inv * s;
        out[1] = farg1 * inv * s;
        out[3] = cosf(half);
    } else {
        out[0] = 0.0f;
        out[1] = 0.0f;
        out[2] = 0.0f;
        out[3] = 1.0f;
    }
}
