#include "common.h"

f32 cosf(f32 farg0);
f32 sinf(f32 farg0);
void sceVu0Normalize(s32 arg0);
void sceVu0ApplyMatrix(s32 arg0, s32 arg1, s32 arg2);

void func_001E4020(u8 *arg0, f32 farg0) {
    u8 sp[0x50];
    f32 x;
    f32 y;
    f32 z;
    f32 c1;
    f32 c2;
    f32 c3;
    f32 c4;
    f32 c5;
    f32 c6;
    f32 c7;
    f32 c8;
    f32 c9;
    f32 c10;
    f32 c11;
    f32 c12;
    f32 s1;
    f32 s2;
    f32 s3;
    f32 s4;
    f32 s5;
    f32 s6;

    sceVu0Normalize((s32)(sp + 0x40));
    x = *(f32 *)(sp + 0x40);
    y = *(f32 *)(sp + 0x44);
    z = *(f32 *)(sp + 0x48);

    c1 = cosf(farg0);
    c2 = cosf(farg0);
    *(f32 *)(sp + 0x00) = c1 + x * x * (1.0f - c2);
    c3 = cosf(farg0);
    s1 = sinf(farg0);
    *(f32 *)(sp + 0x04) = x * y * (1.0f - c3) - z * s1;
    c4 = cosf(farg0);
    s2 = sinf(farg0);
    *(f32 *)(sp + 0x08) = x * z * (1.0f - c4) + y * s2;
    *(s32 *)(sp + 0x0C) = 0;
    c5 = cosf(farg0);
    s3 = sinf(farg0);
    *(f32 *)(sp + 0x10) = x * y * (1.0f - c5) + z * s3;
    c6 = cosf(farg0);
    c7 = cosf(farg0);
    *(f32 *)(sp + 0x14) = c6 + y * y * (1.0f - c7);
    c8 = cosf(farg0);
    s4 = sinf(farg0);
    *(f32 *)(sp + 0x18) = y * z * (1.0f - c8) - x * s4;
    *(s32 *)(sp + 0x1C) = 0;
    c9 = cosf(farg0);
    s5 = sinf(farg0);
    *(f32 *)(sp + 0x20) = x * z * (1.0f - c9) - y * s5;
    c10 = cosf(farg0);
    s6 = sinf(farg0);
    *(f32 *)(sp + 0x24) = y * z * (1.0f - c10) + x * s6;
    c11 = cosf(farg0);
    c12 = cosf(farg0);
    *(f32 *)(sp + 0x28) = c11 + z * z * (1.0f - c12);
    *(s32 *)(sp + 0x2C) = 0;
    *(s32 *)(sp + 0x30) = 0;
    *(s32 *)(sp + 0x34) = 0;
    *(s32 *)(sp + 0x38) = 0;
    *(f32 *)(sp + 0x3C) = 1.0f;
    sceVu0ApplyMatrix((s32)arg0, (s32)sp, (s32)arg0);
}
