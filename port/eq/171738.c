#include "common.h"

extern f32 D_003848C8;
s32 func_003126C8(void *arg0, s32 arg1, s32 arg2, s32 arg3);
s32 EftRay_Create(void *arg0);
void *memset(void *, int, unsigned int);

/* 0x00171738: same ray-argument builder as 0x163AD8 (func_00163AD8), with 50.0f at +0x2C and D_003848C8 at +0x30. */
void func_00171738(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4) {
    u8 fr[0x60];

    memset(fr, 0, 0x10);
    *(f32 *)(fr + 0x20) = arg4;
    *(s32 *)(fr + 0x10) = 0xC0;
    *(s32 *)(fr + 0x14) = 0xC0;
    *(s32 *)(fr + 0x18) = 0xC0;
    *(s32 *)(fr + 0x1C) = 0x70;
    *(f32 *)(fr + 0x24) = 600.0f;
    *(f32 *)(fr + 0x28) = 7.0f;
    *(f32 *)(fr + 0x2C) = 50.0f;
    *(f32 *)(fr + 0x30) = D_003848C8;
    *(s32 *)(fr + 0x34) = 1;
    *(s32 *)(fr + 0x38) = 0x24;
    *(s32 *)(fr + 0x3C) = arg0;
    *(s32 *)(fr + 0x40) = 1;
    *(s32 *)(fr + 0x44) = 1;
    *(s32 *)(fr + 0x48) = (s32)(f32)arg2;
    *(s32 *)(fr + 0x4C) = (s32)(f32)arg3;
    fr[0x50] = 1;

    func_003126C8(fr, arg1, 0x70, 0x24);
    EftRay_Create(fr);
}
