#include "m2c_macros.h"

extern u8 *gEftShotFx;
u8 *func_001B5A10(void);
void func_003126C8(void *a0, void *a1);

/* Adds one line to the shot-effect list gEftShotFx (lines at +0x54 head, +0x58 tail, count at +0x8): the line
 * is taken from the pool by func_001B5A10, its geometry comes from the float arguments (length, growth,
 * width, life = f6 * 30 frames) and the alpha pair follows flag 0x8 (fades out to f5) or flag 0x10 (fades in
 * to f5). The two vectors are set by func_003126C8. */
void EftShotFx_AddLine(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3, s32 arg4,
                       f32 f0, f32 f1, f32 f2, f32 f3, f32 f4, f32 f5, f32 f6) {
    u8 *e;
    u8 *g;
    u8 *tail;
    f32 inv;
    f32 life;

    e = func_001B5A10();
    if (e == NULL) {
        return;
    }
    g = gEftShotFx;
    if (*(u8 **)(g + 0x54) == NULL) {
        *(u8 **)(g + 0x54) = e;
        *(u8 **)(e + 0x4C) = NULL;
        *(u8 **)(e + 0x50) = NULL;
    } else {
        *(u8 **)(e + 0x50) = NULL;
        *(u8 **)(e + 0x4C) = *(u8 **)(g + 0x58);
    }

    tail = *(u8 **)(g + 0x58);
    if (tail != NULL) {
        *(u8 **)(tail + 0x50) = e;
    }
    *(u8 **)(g + 0x58) = e;

    func_003126C8(e, arg0);
    func_003126C8(e + 0x10, arg1);

    *(f32 *)(e + 0x20) = f0;
    *(f32 *)(e + 0x24) = f1;
    *(f32 *)(e + 0x28) = f2;
    if (f3 == 0.0f) {
        inv = 0.0f;
    } else {
        inv = 1.0f / f3;
    }
    *(f32 *)(e + 0x2C) = inv;
    life = f6 * 30.0f;
    *(f32 *)(e + 0x30) = f4;
    *(u8 *)(e + 0x44) = (u8)arg2;
    *(u8 *)(e + 0x45) = (u8)arg3;
    *(s32 *)(e + 0x48) = arg4;
    *(f32 *)(e + 0x40) = life;

    if (arg4 & 8) {
        *(f32 *)(e + 0x3C) = f5;
        *(s32 *)(e + 0x34) = 0;
        *(f32 *)(e + 0x38) = f5 / life;
    } else if (arg4 & 0x10) {
        *(f32 *)(e + 0x3C) = 0;
        *(f32 *)(e + 0x34) = f5;
        *(f32 *)(e + 0x38) = f5 / life;
    }

    *(s32 *)(g + 0x8) = *(s32 *)(g + 0x8) + 1;
}
