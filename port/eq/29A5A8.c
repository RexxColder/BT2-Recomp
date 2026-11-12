#include "common.h"

void *memcpy(void *dst, const void *src, u32 n);
f32 sqrtf(f32 arg0);

extern f32 D_00387244;
extern f32 D_00387248;

/* 0x0029A5A8: unpacks the 32-bit smallest-three quaternion (func_0029A468 packing): bits 30..31 give the dropped
 * index, three 10-bit fields are mapped to ((bits * D_00387244) - 0.5) * D_00387248, the dropped component is
 * sqrt(1 - sum of squares) and goes in at its index (the others shift up). Writes 16 bytes to arg0. */
void func_0029A5A8(s32 arg0, s32 arg1) {
    f32 v[4];
    f32 sum;
    f32 w;
    s32 largest;
    s32 i;
    u32 packed;

    packed = (u32)arg1;
    largest = (s32)(packed >> 30);
    for (i = 0; i < 3; i++) {
        v[i] = (((f32)((packed >> (i * 10)) & 0x3FF) * D_00387244) - 0.5f) * D_00387248;
    }

    sum = 0.0f;
    for (i = 0; i < 3; i++) {
        sum = sum + v[i] * v[i];
    }
    w = sqrtf(1.0f - sum);

    for (i = 3; i > largest; i--) {
        v[i] = v[i - 1];
    }
    v[largest] = w;
    memcpy((void *)arg0, v, 16);
}
