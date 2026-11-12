#include "common.h"

/* 0x00129D90 Vec3_Clamp: out.xyz = min(max(in.xyz, lo), hi); out.w = in.w (VU0 vmaxx.xyz / vminix.xyz). */
void Vec3_Clamp(f32 *arg0, f32 *arg1, f32 arg2, f32 arg3) {
    s32 i;

    for (i = 0; i < 3; i++) {
        f32 v = arg1[i];

        if (v < arg2) {
            v = arg2;
        }
        if (v > arg3) {
            v = arg3;
        }
        arg0[i] = v;
    }
    arg0[3] = arg1[3];
}
