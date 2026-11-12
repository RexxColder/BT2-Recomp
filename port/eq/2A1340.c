#include "common.h"

void *memcpy(void *arg0, const void *arg1, u32 arg2);
extern s32 D_00387EF0;
extern u8 *D_00387EE4;
extern u8 gFontStyle[] __attribute__((section(".data")));

/* 0x002A1340: copy gFontStyle (0x40 bytes) to slot D_00387EF0 of the table at D_00387EE4 (64-byte slots), then
 * D_00387EF0 += 1. */
void func_002A1340(void) {
    u8 *dst = D_00387EE4 + D_00387EF0 * 64;

    memcpy(dst, gFontStyle, 0x40);
    D_00387EF0 = D_00387EF0 + 1;
}
