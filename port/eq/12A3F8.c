#include "common.h"

extern f32 D_00384160;
extern f32 D_00340000[] __attribute__((section(".data")));

/* 0x0012A3F8 (sine of an angle): x = angle reduced into (-P/2, P/2] with P = 2 * D_00384160 (x += P while x < P,
 * x -= P while D_00384160 < x), then the VU0 odd polynomial x + C3 x^3 + C2 x^5 + C1 x^7 + C0 x^9 with the four
 * floats C0..C3 of D_00340000 (vf5.x .. vf5.w). */
f32 func_0012A3F8(f32 arg0) {
    f32 p = D_00384160 + D_00384160;
    f32 x = arg0;
    f32 x2;
    f32 t[4];
    f32 r;
    s32 i;

    while (x < p) {
        x = x + p;
    }
    while (D_00384160 < x) {
        x = x - p;
    }
    x2 = x * x;
    for (i = 0; i < 4; i++) {
        t[i] = D_00340000[i] * x;
        t[i] = t[i] * x2;
    }
    for (i = 0; i < 3; i++) {
        t[i] = t[i] * x2;
    }
    r = x + t[3];
    for (i = 0; i < 2; i++) {
        t[i] = t[i] * x2;
    }
    r = r + t[2];
    t[0] = t[0] * x2;
    r = r + t[1];
    r = r + t[0];
    return r;
}
