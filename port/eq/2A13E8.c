#include "common.h"

void *memcpy(void *arg0, const void *arg1, u32 arg2);
extern s32 D_00387EF0;
extern u8 *D_00387EE4;
extern u8 gFontStyle[] __attribute__((section(".data")));

/* 0x002A13E8: D_00387EF0 -= 1; copy the 64-byte slot at D_00387EE4 + 64 * D_00387EF0 into gFontStyle (the
 * inverse of func_002A1340). */
void func_002A13E8(void) {
    s32 n = D_00387EF0 - 1;

    D_00387EF0 = n;
    memcpy(gFontStyle, D_00387EE4 + n * 64, 0x40);
}
