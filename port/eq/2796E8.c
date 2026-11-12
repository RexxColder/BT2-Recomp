#include "common.h"

void *memset(void *arg0, s32 arg1, s32 arg2);
void sceVu0CopyMatrix(void *arg0, void *arg1);
void sceVu0InversMatrix(void *arg0, void *arg1);
void sceVu0Normalize(void *arg0, void *arg1);
void func_00312490(void *arg0, void *arg1, void *arg2);
void func_00312650(void *arg0, void *arg1, void *arg2);
f32 func_0029DFD0(void *arg0);
extern f32 D_00387080;
extern f32 D_00387084;
extern f32 D_00387088;
extern f32 D_0038708C;
extern s32 gBtlCam;

s32 func_002796E8(s32 arg0) {
    u8 sp[0x40];
    u8 *p = (u8 *)arg0;
    u8 *t3;
    s32 base;
    s32 i;
    s32 r;
    s32 ti;
    f32 f0;
    f32 f1;
    f32 f2;
    f32 f3;
    f32 f5;

    memset(sp, 0, 0x10);
    *(f32 *)(sp + 0x0C) = 1.0f;
    memset(sp + 0x10, 0, 0x10);
    *(f32 *)(sp + 0x1C) = 1.0f;
    memset(sp + 0x20, 0, 0x10);
    *(f32 *)(sp + 0x2C) = 1.0f;
    memset(sp + 0x30, 0, 0x10);
    *(f32 *)(sp + 0x3C) = 1.0f;

    base = gBtlCam + (*(s32 *)(p + 0x90) * 0x300);
    sceVu0CopyMatrix(p + 0x40, p);
    sceVu0InversMatrix(p, (void *)base);
    *(f32 *)(p + 0x34) = 0.0f;
    *(f32 *)(p + 0x74) = 0.0f;
    sceVu0Normalize(sp + 0x20, p + 0x30);
    sceVu0Normalize(sp + 0x30, p + 0x70);
    func_00312490(sp, sp + 0x30, sp + 0x20);
    func_00312650(sp + 0x10, p + 0x70, p + 0x30);
    f5 = func_0029DFD0(sp + 0x10);

    if (1.0f <= f5) {
        if (f5 < 2.5f) {
            *(f32 *)(p + 0x84) = *(f32 *)(p + 0x84) + D_00387080;
        }
        if (2.5f <= f5 && f5 < 4.0f) {
            *(f32 *)(p + 0x84) = *(f32 *)(p + 0x84) - D_00387084;
        }
        if (4.0f < f5) {
            *(f32 *)(p + 0x84) = *(f32 *)(p + 0x84) + D_00387088;
        }
    } else {
        *(f32 *)(p + 0x84) = *(f32 *)(p + 0x84) - D_0038708C;
    }

    f2 = *(f32 *)(p + 0x84);
    if (1.0f < f2) {
        *(f32 *)(p + 0x84) = 1.0f;
        f2 = 1.0f;
    }
    if (f2 < 0.0f) {
        *(f32 *)(p + 0x84) = 0.0f;
        return 0;
    }

    f0 = *(f32 *)(sp + 0x04) * 100.0f;
    *(f32 *)(p + 0x88) = f0;
    f3 = 1.0f;
    if (f3 < f0) {
        *(f32 *)(p + 0x88) = 1.0f;
    }
    f5 = *(f32 *)(p + 0x88);
    if (f5 < -1.0f) {
        *(f32 *)(p + 0x88) = -1.0f;
        f5 = -1.0f;
    }

    i = 0;
    do {
        f3 = (f32)(i << 5);
        f0 = *(f32 *)(p + 0x80) * f2;
        f0 = f0 - f3;
        f1 = (f32)(i + 1) * f5;
        t3 = p + i * 0x30;

        /* truncates toward zero (cvt.w.s), then clamp at 0 */
        ti = (s32)f0;
        r = ti;
        if (r < 0) {
            r = 0;
        }

        i = i + 1;
        *(f32 *)(t3 + 0xB0) = f1;
        *(s32 *)(t3 + 0xB4) = 0;
        *(s32 *)(t3 + 0xB8) = 0;
        *(f32 *)(t3 + 0xBC) = 1.0f;
        *(f32 *)(t3 + 0xC0) = 128.0f;
        *(f32 *)(t3 + 0xC4) = 128.0f;
        *(f32 *)(t3 + 0xC8) = 128.0f;
        *(f32 *)(t3 + 0xCC) = (f32)r;
    } while (i < 2);
    return 1;
}
