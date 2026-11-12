#include "common.h"

void *memcpy(void *dst, const void *src, u32 n);
extern f32 D_0038723C;
extern f32 D_00387240;

/* 0x0029A468: smallest-three quaternion pack of the 16-byte vector at arg0. The largest |component| is
 * dropped (the vector is negated first when that component is negative), the other three are scaled to
 * 10-bit fields 0..2 (clamped to 0..0x3FF) and the dropped index goes to bits 30..31. */
u32 func_0029A468(s32 arg0) {
    f32 v[4];
    f32 m;
    f32 x;
    f32 f;
    s32 t2;
    s32 a2;
    s32 k;
    s32 q;
    u32 res;

    memcpy(v, (const void *)arg0, 16);

    m = (v[0] < 0.0f) ? -v[0] : v[0];
    t2 = 0;
    for (a2 = 1; a2 < 4; a2++) {
        x = (v[a2] < 0.0f) ? -v[a2] : v[a2];
        if (m < x) {
            m = x;
            t2 = a2;
        }
    }

    if (v[t2] < 0.0f) {
        v[0] = -v[0];
        v[1] = -v[1];
        v[2] = -v[2];
        v[3] = -v[3];
    }

    if (t2 < 3) {
        for (k = t2; k < 3; k++) {
            v[k] = v[k + 1];
        }
    }

    res = 0;
    for (k = 0; k < 3; k++) {
        f = v[k] * D_0038723C;
        f = f + 0.5f;
        f = f * D_00387240;
        q = (s32)f;
        if (q < 0) {
            q = 0;
        }
        if (!(q < 0x400)) {
            q = 0x3FF;
        }
        res = res | ((u32)q << (k * 10));
    }
    res = res | ((u32)t2 << 30);
    return res;
}
