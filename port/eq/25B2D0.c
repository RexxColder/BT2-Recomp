#include "common.h"

void func_003126C8(s32 arg0, s32 arg1);
void sceVu0InversMatrix(s32 arg0, s32 arg1);
void sceVu0ApplyMatrix(s32 arg0, s32 arg1, s32 arg2);
f32 sceVu0InnerProduct(s32 arg0, s32 arg1);
void sceVu0Normalize(s32 arg0, s32 arg1);
void func_00312490(s32 arg0, s32 arg1, s32 arg2);
f32 sqrtf(f32 arg0);
extern u8 D_00386DC0[] __attribute__((section(".data")));
extern u8 D_00386DC4[] __attribute__((section(".data")));
extern u8 D_003764A0[] __attribute__((section(".rodata")));

/* 0x0025B2D0: builds a 4x4 frame (inverse matrix plus five projected points)
 * for the object at a0 from the vector at a1. */
void func_0025B2D0(s32 a0, s32 a1) {
    u8 sp[0xC0];
    s32 s0;
    s32 s1;
    s32 s2;
    s32 s3;
    s32 s4;
    f32 f0;
    f32 f1;
    f32 f2;
    f32 f3;
    f32 f20;
    f32 f21;
    f32 f22;

    s0 = a0;
    s4 = a1;
    s3 = s0 + 0x180;
    func_003126C8(s0 + 0x1F0, a1);

    f1 = *(f32 *)(s0 + 0x210);
    f0 = *(f32 *)D_00386DC0;
    f2 = *(f32 *)(s0 + 0x224);
    if (f1 < f0) {
        f21 = f2 / 1200.0f;
    } else {
        f21 = f2 * 0.001953125f;
    }
    f22 = f21 * f21;

    f20 = 1.0f;
    f2 = sqrtf(f22 + f20);
    f0 = 0.5625f;
    f3 = f20 / f2;
    *(f32 *)(s3 + 0x24) = 0.0f;
    *(f32 *)(s3 + 0x2C) = f20;
    *(f32 *)(s3 + 0x34) = 0.0f;
    *(f32 *)(s3 + 0x3C) = f20;
    f1 = f3 * f21;
    f0 = f22 + f0;
    f2 = sqrtf(f0);
    *(f32 *)(s3 + 0x38) = f3;
    *(f32 *)(s3 + 0x28) = f3;
    *(f32 *)(s3 + 0x20) = f1;
    *(f32 *)(s3 + 0x30) = -f1;

    f0 = f20 / f2;
    f1 = 0.75f;
    *(f32 *)(s3 + 0x6C) = f20;
    *(f32 *)(s3 + 0x40) = 0.0f;
    *(f32 *)(s3 + 0x4C) = f20;
    *(f32 *)(s3 + 0x50) = 0.0f;
    *(f32 *)(s3 + 0x5C) = f20;
    *(s32 *)(s3 + 0x60) = 0;
    *(s32 *)(s3 + 0x64) = 0;
    f3 = f0 * f21;
    *(f32 *)(s3 + 0x68) = f20;
    f1 = f0 * f1;
    f2 = -f3;
    *(f32 *)(s3 + 0x44) = f3;
    *(f32 *)(s3 + 0x58) = f1;
    *(f32 *)(s3 + 0x48) = f1;
    *(f32 *)(s3 + 0x54) = f2;
    sceVu0InversMatrix((s32)&sp[0], s0);
    *(s32 *)&sp[0x30] = 0;
    *(s32 *)&sp[0x34] = 0;
    *(s32 *)&sp[0x38] = 0;

    s0 = s3 + 0x20;
    s1 = 4;
    do {
        sceVu0ApplyMatrix(s0, (s32)&sp[0], s0);
        s1 -= 1;
        f0 = sceVu0InnerProduct(s0, s4);
        f0 = -f0;
        *(f32 *)(s0 + 0xC) = f0;
        s0 += 0x10;
    } while (s1 >= 0);

    s0 = (s32)&sp[0x60];
    s2 = (s32)&sp[0x50];
    s1 = (s32)&sp[0x40];
    f0 = *(f32 *)(s3 + 0x6C);
    f1 = *(f32 *)D_00386DC4;
    f0 = f0 - f1;
    f1 = *(f32 *)(s3 + 0x20);
    f2 = *(f32 *)(s3 + 0x28);
    f20 = 1.0f;
    *(f32 *)(s3 + 0x6C) = f0;
    *(f32 *)&sp[0x50] = f1;
    *(s32 *)&sp[0x40] = *(s32 *)(D_003764A0 + 0);
    *(s32 *)&sp[0x44] = *(s32 *)(D_003764A0 + 4);
    *(f32 *)(s3 + 0) = *(f32 *)(s4 + 0);
    *(s32 *)&sp[0x48] = *(s32 *)(D_003764A0 + 8);
    *(s32 *)&sp[0x4C] = *(s32 *)(D_003764A0 + 12);
    *(f32 *)(s3 + 4) = *(f32 *)(s4 + 8);
    *(f32 *)&sp[0x58] = f2;
    *(f32 *)&sp[0x5C] = f20;
    *(s32 *)&sp[0x54] = 0;
    func_00312490(s0, s2, s1);

    sceVu0Normalize(s0, s0);

    f3 = *(f32 *)(s3 + 0x30);
    f1 = *(f32 *)&sp[0x60];
    s1 = (s32)&sp[0x40];
    f0 = *(f32 *)&sp[0x68];
    s2 = (s32)&sp[0x50];
    f1 = -f1;
    f2 = *(f32 *)(s3 + 0x38);
    f0 = -f0;
    *(f32 *)&sp[0x50] = f3;
    *(f32 *)&sp[0x58] = f2;
    *(f32 *)(s3 + 0x8) = f1;
    *(f32 *)(s3 + 0x14) = f0;
    *(f32 *)&sp[0x5C] = f20;
    *(s32 *)&sp[0x54] = 0;
    func_00312490((s32)&sp[0x60], s2, s1);

    sceVu0Normalize((s32)&sp[0x60], (s32)&sp[0x60]);

    f3 = *(f32 *)(s3 + 0x60);
    f1 = *(f32 *)&sp[0x60];
    f2 = *(f32 *)&sp[0x68];
    f0 = *(f32 *)(s3 + 0x68);
    *(f32 *)(s3 + 0xC) = f1;
    *(f32 *)(s3 + 0x1C) = f0;
    *(f32 *)(s3 + 0x18) = f2;
    *(f32 *)(s3 + 0x10) = f3;
}
