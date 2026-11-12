#include "common.h"

extern f32 D_00385AF8;
extern f32 D_00385AFC;
extern f32 D_00385B00;
extern f32 D_00385B04;
extern f32 D_00385B08;

f32 BtlMove_CalcVerticalSpeed(f32 arg0, f32 arg1) {
    f32 x;
    f32 a;
    f32 b;
    s32 c;
    s32 c2;

    a = 0.0f;
    if (!(0.0f < arg0)) {
        goto L217710;
    }
    x = arg0 - a;
    a = D_00385AF8;
    if (!(x < 0.0f)) {
        goto L217728;
    }
    a = (((1.0f - (-x / a)) * a) - a) + a;
    goto L217778;

L217710:
    x = arg0 - a;
L217714:
    b = D_00385AFC;
    c = (0.0f < x);
    a = a - b;
    if (c) {
        goto L2176E0;
    }
L217728:
    /* fall into the loop head */
L21772C:
    c = (0.0f < x);
    x = x - a;
    if (!c) {
        goto L217714;
    }
    b = D_00385B00;
    c2 = (x < 0.0f);
    a = a + b;
    if (!c2) {
        goto L21772C;
    }
    a = a + (((1.0f - (-x / a)) * b) - b);
    goto L217778;

L2176E0:
    a = a - (((1.0f - (-x / a)) * b) - b);

L217778:
    a = a + arg1;
    if (D_00385B04 < a) {
        a = D_00385B04;
    }
    if (a < D_00385B08) {
        a = D_00385B08;
    }
    return a;
}
