#include "common.h"

extern u8 D_0038B058[];
extern u8 D_00387D90[];
extern u8 D_00377738[];
extern u8 D_00377748[];
extern u8 D_00377770[];

void func_002788A0(s32 arg0, s32 arg1, s32 arg2);
void func_0026EBC0(s32 arg0, void *arg1, void *arg2);
void func_0026EC48(s32 arg0, void *arg1, void *arg2);
void func_00278A40(s32 arg0, s32 arg1);
s32 func_0026EA58(s32 arg0);

/* 0x00299380: builds the two display-list tables at g+0x20 (base) from the 20-byte entries in the frame copy. */
s32 func_00299380(void) {
    u8 fr[0x60];
    u8 *g;
    u8 *base;
    u8 *src;
    u8 *dst;
    s32 k;
    s32 idx;

    g = D_0038B058;
    func_002788A0(0, 0, *(s32 *)(g + 0x20));

    *(s32 *)(fr + 0x10) = 0;
    *(s32 *)(fr + 0x14) = 0x60;
    *(s32 *)(fr + 0x18) = 0x20;
    *(s32 *)(fr + 0x1C) = 0x80;
    func_0026EBC0(*(s32 *)(g + 0x8), D_00387D90, fr);
    func_0026EC48(*(s32 *)(g + 0x8), fr, fr + 0x10);

    *(s32 *)(fr + 0x10) = 0;
    *(s32 *)(fr + 0x14) = 0x40;
    *(s32 *)(fr + 0x18) = 0x80;
    *(s32 *)(fr + 0x1C) = 0x60;
    func_0026EBC0(*(s32 *)(g + 0x8), D_00377738, fr);
    func_0026EC48(*(s32 *)(g + 0x8), fr, fr + 0x10);

    for (k = 0; k < 40; k++) {
        fr[0x30 + k] = D_00377748[k];
    }

    base = (u8 *)(s32)*(s32 *)(g + 0x20);
    for (k = 0; k <= 1; k++) {
        idx = *(s16 *)(g + 0x50 + 28 * k + 2);
        src = fr + 0x30 + 20 * idx;
        dst = base + 56 * k + 0x244;
        for (idx = 0; idx < 16; idx++) {
            dst[idx] = src[idx];
        }
        for (idx = 0; idx < 4; idx++) {
            dst[16 + idx] = src[16 + idx];
        }
    }

    func_00278A40(*(s32 *)(g + 0xC), *(s32 *)(g + 0x20) + 0x230);

    for (k = 0; k < 40; k++) {
        fr[0x30 + k] = D_00377770[k];
    }

    base = (u8 *)(s32)*(s32 *)(g + 0x20);
    for (k = 0; k <= 6; k++) {
        idx = *(s16 *)(g + 0x28 + 6 * k);
        src = fr + 0x30 + 20 * idx;
        dst = base + 56 * k + 0x84;
        for (idx = 0; idx < 16; idx++) {
            dst[idx] = src[idx];
        }
        for (idx = 0; idx < 4; idx++) {
            dst[16 + idx] = src[16 + idx];
        }
    }

    func_00278A40(*(s32 *)(g + 0xC), *(s32 *)(g + 0x20) + 0x70);
    return func_0026EA58(*(s32 *)(g + 0x8));
}
