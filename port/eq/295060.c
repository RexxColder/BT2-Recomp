#include "common.h"

void ColSeg_NearestOnLine(f32 *a0, f32 *a1, f32 *a2, s32 a3, f32 *a4, f32 *a5, f32 f12);
void func_003126C8(s32 arg0, s32 arg1);

/* Nearest point between a segment (p1 + p2 * t) and a second segment (p3, p4) in the
   parallel case: picks the clamped parameter range and writes the mid point to p6 (p7 holds
   the output pair). Returns 1 on the direct-copy path, 0 otherwise. */
s32 ColSeg_NearestParallel(f32 *p1, f32 *p2, f32 *p3, f32 *p4, s32 p5, f32 *p6, f32 *p7,
                           f32 p8) {
    f32 ts[2];
    f32 pt[4];
    f32 tm_out[4];
    f32 *p3b;
    f32 *p1b;
    f32 v18;
    f32 v20;

    ColSeg_NearestOnLine(p1, p2, p3, 1, p6, ts, p8);
    if (p5 == 1) {
        func_003126C8((s32)p7, (s32)p3);
        return 1;
    }

    p3b = p3 + 4;
    ColSeg_NearestOnLine(p1, p2, p3b, 1, pt, &ts[1], p8);

    if (ts[0] < 0.0f && ts[1] < 0.0f) {
        func_003126C8((s32)p6, (s32)p1);
        if (ts[0] < ts[1]) {
            func_003126C8((s32)p7, (s32)p3b);
        } else {
            func_003126C8((s32)p7, (s32)p3);
        }
        return 0;
    }

    p1b = p1 + 4;
    if (1.0f < ts[0] && 1.0f < ts[1]) {
        func_003126C8((s32)p6, (s32)p1b);
        if (ts[0] < ts[1]) {
            func_003126C8((s32)p7, (s32)p3);
        } else {
            func_003126C8((s32)p7, (s32)p3b);
        }
        return 0;
    }

    v18 = (ts[0] < 0.0f) ? 0.0f : ((ts[0] < 1.0f) ? ts[0] : 1.0f);
    if (ts[1] >= 1.0f) {
        v20 = v18 + 1.0f;
    } else if (ts[1] >= 0.0f) {
        v20 = v18 + ts[1];
    } else {
        v20 = v18 + 0.0f;
    }

    tm_out[0] = v20 * 0.5f;
    p6[0] = p1[0] + tm_out[0] * p2[0];
    p6[1] = p1[1] + tm_out[0] * p2[1];
    p6[2] = p1[2] + tm_out[0] * p2[2];
    ColSeg_NearestOnLine(p3, p4, p6, 1, p7, tm_out, p8);
    return 0;
}
