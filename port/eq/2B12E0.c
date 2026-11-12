#include "common.h"

extern f32 D_003875DC __attribute__((section(".data")));
extern f32 D_003875E0 __attribute__((section(".data")));
extern f32 D_003875E4 __attribute__((section(".data")));
extern f32 D_003875E8 __attribute__((section(".data")));
extern f32 D_003875EC __attribute__((section(".data")));
extern f32 D_003875F0 __attribute__((section(".data")));
extern f32 D_003875F4 __attribute__((section(".data")));
extern f32 D_003875F8 __attribute__((section(".data")));
extern f32 D_003875FC __attribute__((section(".data")));
extern f32 D_00387600 __attribute__((section(".data")));
extern f32 D_00387604 __attribute__((section(".data")));
extern f32 D_00387608 __attribute__((section(".data")));

/* 12 float constants copied to the stack table each call (tbl[0..11]) */
static const u32 kRateBits[12] = {
    0x3F4CCCCC, 0x3F8CCCCC, 0x3F999999, 0x3FA66666, 0x3FC00000, 0x3FB33333,
    0x3F8CCCCC, 0x3F333333, 0x3F8CCCCC, 0x3F666666, 0x3F999999, 0x3F800000,
};

void func_002B12E0(u8 *obj, s32 mode) {
    f32 tbl[12];
    s32 k;
    f32 x;
    f32 y;
    f32 z;
    f32 f2;
    f32 f3;
    f32 f4;

    __builtin_memcpy(tbl, kRateBits, 48);
    k = *(s32 *)(obj + 0x4);

    if (mode == 0) {
        *(f32 *)(obj + 0x164) = *(f32 *)(obj + 0x164) + tbl[3 * k + 1] * D_003875DC;
    }

    if (mode == 1) {
        f2 = tbl[3 * k] * D_003875E0;
        f3 = tbl[3 * k + 1] * D_003875E4;
        f4 = tbl[3 * k + 2] * D_003875E8;
        *(f32 *)(obj + 0x160) = *(f32 *)(obj + 0x160) + f2;
        *(f32 *)(obj + 0x164) = *(f32 *)(obj + 0x164) + f3;
        *(f32 *)(obj + 0x168) = *(f32 *)(obj + 0x168) - f4;
    }

    x = *(f32 *)(obj + 0x160);
    if (D_003875EC < x) {
        x = x - D_003875F0;
        *(f32 *)(obj + 0x160) = x;
    }
    if (x < D_003875F4) {
        x = x + D_003875F8;
        *(f32 *)(obj + 0x160) = x;
    }

    y = *(f32 *)(obj + 0x164);
    if (D_003875EC < y) {
        y = y - D_003875FC;
        *(f32 *)(obj + 0x164) = y;
    }
    if (y < D_003875F4) {
        y = y + D_00387600;
        *(f32 *)(obj + 0x164) = y;
    }

    z = *(f32 *)(obj + 0x168);
    if (D_003875EC < z) {
        z = z - D_00387604;
        *(f32 *)(obj + 0x168) = z;
    }
    if (z < D_003875F4) {
        z = z + D_00387608;
        *(f32 *)(obj + 0x168) = z;
    }

    *(f32 *)(obj + 0xF0) = __builtin_sinf(*(f32 *)(obj + 0x160));
    *(f32 *)(obj + 0xF4) = __builtin_sinf(*(f32 *)(obj + 0x164));
    *(f32 *)(obj + 0xF8) = __builtin_sinf(*(f32 *)(obj + 0x168));
}
