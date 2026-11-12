#include "common.h"

extern f32 D_00384774;
s32 func_003126C8(void *arg0, s32 arg1, s32 arg2, s32 arg3);
s32 EftRay_Create(void *arg0);
void *memset(void *, int, unsigned int);

/* 0x00163AD8: builds a 0x60-byte ray argument (EftRay_Create) with a0 at +0x3C, arg2/arg3 converted to
 * ints at +0x48/+0x4C, f12 at +0x20, the constants 600, 7, 30 and D_00384774 at +0x24/+0x28/+0x2C/+0x30,
 * then calls func_003126C8(block, arg1, 0x70, 0x24) and EftRay_Create(block). */
void func_00163AD8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4) {
    u8 fr[0x60];

    memset(fr, 0, 0x10);
    *(f32 *)(fr + 0x20) = arg4;
    *(s32 *)(fr + 0x10) = 0xC0;
    *(s32 *)(fr + 0x14) = 0xC0;
    *(s32 *)(fr + 0x18) = 0xC0;
    *(s32 *)(fr + 0x1C) = 0x70;
    *(f32 *)(fr + 0x24) = 600.0f;
    *(f32 *)(fr + 0x28) = 7.0f;
    *(f32 *)(fr + 0x2C) = 30.0f;
    *(f32 *)(fr + 0x30) = D_00384774;
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
