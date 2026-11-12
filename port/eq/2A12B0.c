#include "common.h"

void *memcpy(void *arg0, const void *arg1, u32 arg2);
extern u8 gFontStyle[] __attribute__((section(".data")));

/* 0x002A12B0: copy the 64-byte block at a0 into gFontStyle. */
void func_002A12B0(u8 *arg0) {
    memcpy(gFontStyle, arg0, 0x40);
}
