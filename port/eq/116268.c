#include "common.h"

s32 func_00242828(s32 arg0);
void func_00312650(void *arg0, void *arg1, void *arg2);
f32 sceVu0InnerProduct(void *arg0, void *arg1);
void sceVu0ApplyMatrix(s32 arg0, s32 arg1, s32 arg2);
extern u8 *D_00387A40;
extern f32 D_00383F20;

/* 0x00116268: place the unit (a1) on a path point of the track table row a2: the row's float at +0x9C0 / +0x9C8
   (truncated to int) give a start point, a direction is taken from func_00312650, and when the unit's height a1[0]
   is below the path length the point is pushed along the direction. The matrix transform at a1 + 0x70 gives
   the screen point stored at a1 +0x3C / +0x40; a1 +0x44 gets a code chosen by the return of func_00242828. */
s32 func_00116268(u8 *a1, s32 a2) {
    f32 v16[4];
    f32 v17[4];
    f32 v20[4];
    f32 v23[4];
    f32 v24[4];
    s32 kind;
    s32 code;
    u8 *row;
    f32 v8;
    f32 v9;
    f32 ip;
    f32 len;
    f32 v11;
    f32 v13;
    f32 v15;

    kind = func_00242828((s32)v16);
    if (kind == 0) {
        *(s32 *)(a1 + 0x40) = 0;
        *(f32 *)(a1 + 0x34) = 15.0f;
        *(s32 *)(a1 + 0x38) = 0;
        *(s32 *)(a1 + 0x30) = 0;
        *(s32 *)(a1 + 0x3C) = 0;
        return 0;
    }

    row = (u8 *)((s32)(a2 * 99712) + *(s32 *)D_00387A40);
    v8 = *(f32 *)(row + 0x9C0);
    v17[0] = (f32)(s32)v8;
    v17[1] = 0.0f;
    v9 = *(f32 *)(row + 0x9C8);
    v20[0] = v16[0];
    v20[2] = v16[2];
    v20[3] = 1.0f;
    v17[3] = 1.0f;
    v20[1] = 0.0f;
    v17[2] = (f32)(s32)v9;
    func_00312650((void *)v23, (void *)v20, (void *)v17);
    ip = sceVu0InnerProduct((void *)v23, (void *)v23);
    len = __builtin_sqrtf(__builtin_fabsf(ip));
    v11 = *(f32 *)a1;
    if (v11 < len) {
        v20[2] = v17[2] + (v23[2] * (v11 - 170.0f)) / len;
        v20[0] = v17[0] + (v23[0] * (v11 - 170.0f)) / len;
    }
    sceVu0ApplyMatrix((s32)v24, (s32)(a1 + 0x70), (s32)v20);
    *(s32 *)(a1 + 0x3C) = (s32)v24[0];
    *(s32 *)(a1 + 0x38) = 1;
    *(s32 *)(a1 + 0x40) = (s32)v24[1];

    if (kind == 9) {
        code = 0xF6FF00;
    } else if ((u32)kind < 10) {
        code = (kind == 8) ? 0x4EFF00 : 0x4EC8EC;
    } else if (kind == 10) {
        code = 0xF6FF;
    } else if (kind == 11) {
        code = 0x100B3;
    } else {
        code = 0x4EC8EC;
    }
    *(s32 *)(a1 + 0x44) = code;

    v13 = *(f32 *)(a1 + 0x30);
    *(f32 *)(a1 + 0x34) = 15.0f;
    v15 = v13 + (16.0f - v13) * D_00383F20;
    *(f32 *)(a1 + 0x30) = v15;
    if (15.0f < v15) {
        *(s32 *)(a1 + 0x38) = 0;
        *(s32 *)(a1 + 0x30) = 0;
    }
    return code;
}
