#include "m2c_macros.h"

extern f32 D_00384F30;
extern f32 D_00384F34;
void func_003126C8(void *a0, void *a1);
void sceVu0Normalize(void *a0, void *a1);
s32 func_0020A440(s32 a0);
void func_00208860(s32 a0, void *a1);
s32 func_0020B3D0(s32 a0);
void func_00208DE8(s32 arg0, u8 *arg1, s32 arg2);
void func_00312650(void *a0, void *a1, void *a2);
f32 sceVu0InnerProduct(void *a0, void *a1);
f32 sqrtf(f32 x);
void sceVu0UnitMatrix(void *a0);
f32 EftMath_WrapAngle(f32 angle);
void sceVu0RotMatrixY(void *a0, void *a1, f32 angle);
void sceVu0ApplyMatrix(void *a0, void *a1, void *a2);

/* Orients the unit at arg0+0x38 from the record arg1: its direction (normalized, scaled by up to 1.5) and a
 * Y-rotation matrix from the record's angle, then copies the record's 64-byte block and two floats. */
void Obj_UpdateOrient(u8 *arg0, u8 *arg1) {
    u8 frame[0x70];
    u8 *c;
    u8 *src;
    s32 r;
    s32 i;
    f32 len;
    f32 kf;
    f32 angle;

    c = *(u8 **)(arg0 + 0x38);
    func_003126C8(c + 0x30, arg1 + 0x10);
    sceVu0Normalize(c + 0x30, c + 0x30);
    c[0x58] = arg1[0x48];
    r = func_0020A440(*(s32 *)(c + 0x44));
    c[0x59] = (u8)r;

    if (r != 0) {
        func_00208860(*(s32 *)(c + 0x44), frame + 0x20);
        r = func_0020B3D0(*(s32 *)(c + 0x44));
        func_00208DE8(r, frame, 3);
        func_00312650(frame + 0x10, frame + 0x20, frame);
        len = sceVu0InnerProduct(frame + 0x10, frame + 0x10);
        len = sqrtf(len);
        kf = len * D_00384F30;
        if (1.5f < kf) {
            kf = 1.5f;
        }
        sceVu0UnitMatrix(frame + 0x30);
        angle = (*(f32 *)(arg1 + 0x38) / 180.0f) * D_00384F34 * kf;
        angle = EftMath_WrapAngle(angle);
        sceVu0RotMatrixY(frame + 0x30, frame + 0x30, angle);
        sceVu0ApplyMatrix(c + 0x30, frame + 0x30, c + 0x30);
    }

    src = *(u8 **)(arg1 + 0x4C);
    if (src != NULL) {
        for (i = 0; i < 0x40; i += 8) {
            *(u64 *)(c + 0x180 + i) = *(u64 *)(src + i);
        }
    }
    *(s32 *)(c + 0x174) = *(s32 *)(arg1 + 0x50);
    *(f32 *)(c + 0x48) = *(f32 *)(arg1 + 0x3C);
    *(f32 *)(c + 0x4C) = *(f32 *)(arg1 + 0x40);
    *(f32 *)(c + 0x50) = *(f32 *)(arg1 + 0x44);
}
