#include "m2c_macros.h"

void *memcpy(void *dst, void *src, u32 n);
s32 func_00211310(void *obj, s32 a1, s32 a2);
extern u8 *D_003876A0;
extern u8 *D_003876A4;
extern u8 D_0036FA10[] __attribute__((section(".data")));

void func_00211418(void *obj, s32 mask) {
    u8 tbl[0x60];   /* tamano de locales del original (antes 0x54) */
    s32 idx;
    s32 f370;
    s32 f1468;
    s32 bits;
    s32 s0;

    memcpy(tbl, D_0036FA10, 0x40);
    memcpy(tbl + 0x40, D_0036FA10 + 0x40, 0x14);
    if (M2C_FIELD(D_003876A0, s32 *, 0xB8) != 4) {
        return;
    }
    if (func_00211310(obj, 0, 0x400000) == 0) {
        return;
    }
    idx = M2C_FIELD(D_003876A4, s32 *, 0x484);
    if ((u32)idx >= 0x15) {
        return;
    }
    bits = *(s32 *)(tbl + idx * 4);
    f370 = M2C_FIELD(obj, s32 *, 0x370);
    f1468 = M2C_FIELD(obj, s32 *, 0x1468);
    s0 = mask & bits & ~f1468;
    M2C_FIELD(obj, s32 *, 0x370) = f370 | s0;
    M2C_FIELD(obj, s32 *, 0x1468) = f1468 | s0;
    idx = M2C_FIELD(D_003876A4, s32 *, 0x484);
    if ((f1468 | s0) != *(s32 *)(tbl + idx * 4)) {
        return;
    }
    M2C_FIELD(obj, u8 *, 0x1465) = 1;
}
