#include "common.h"

extern f32 D_003840BC;
extern f32 D_003840C0;
extern f32 D_003840C4;
extern f32 D_003840C8;
extern f32 D_003840CC;
extern f32 D_003840D0;
extern f32 D_003840D4;
extern f32 D_003840D8;

f32 cosf(f32 arg0);
f32 sinf(f32 arg0);

void func_00121388(u8 *arg0) {
    u8 *s0 = arg0 + 0x10;
    f32 f1, f20, f2, v;
    s32 k;

    f1 = *(f32 *)(s0 + 0xC) + ((((f32)*(s32 *)(arg0 + 8) * D_003840BC) + 1.0f) * D_003840C0);
    *(f32 *)(s0 + 0xC) = f1;
    if (D_003840C4 < f1) {
        *(f32 *)(s0 + 0xC) = f1 - D_003840C8;
    }
    f20 = cosf(*(f32 *)(s0 + 0xC));
    f2 = -sinf(*(f32 *)(s0 + 0xC));
    if (f20 > 0.0f) {
        f20 = f20 + ((1.0f - f20) * D_003840CC);
    } else {
        f20 = f20 - ((f20 + 1.0f) * D_003840D0);
    }
    if (f2 > 0.0f) {
        f2 = f2 + ((1.0f - f2) * D_003840D4);
    } else {
        f2 = f2 - ((f2 + 1.0f) * D_003840D8);
    }

    v = ((f20 * 0.5f) + 0.5f) * 255.0f;
    k = (s32)v;
    if (v - (f32)k > 0.5f || (v - (f32)k == 0.5f && (k & 1))) {
        k++;
    } else if (v - (f32)k < -0.5f || (v - (f32)k == -0.5f && (k & 1))) {
        k--;
    }
    if (k < 0) {
        k = 0;
    }
    if (k >= 0x100) {
        k = 0xFF;
    }
    arg0[0x10] = (u8)k;

    v = ((f2 * 0.5f) + 0.5f) * 255.0f;
    k = (s32)v;
    if (v - (f32)k > 0.5f || (v - (f32)k == 0.5f && (k & 1))) {
        k++;
    } else if (v - (f32)k < -0.5f || (v - (f32)k == -0.5f && (k & 1))) {
        k--;
    }
    if (k < 0) {
        k = 0;
    }
    if (k >= 0x100) {
        k = 0xFF;
    }
    s0[1] = (u8)k;
}
