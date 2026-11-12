#include "common.h"

void *memset(void *s, s32 c, u32 n);
extern u8 D_0037D0A8[] __attribute__((section(".data")));
extern u8 *D_0039D6E8 __attribute__((section(".data")));
extern s32 D_0039D6EC __attribute__((section(".data")));
extern s32 D_0039D6F0 __attribute__((section(".data")));
extern u8 D_0039D6F8[] __attribute__((section(".data")));

void func_002F9088(void) {
    s32 base;
    s32 temp_a0;
    s32 temp_v0;

    D_0039D6E8 = D_0037D0A8;
    memset(D_0039D6F8, 0, 0x100);
    base = (s32) D_0039D6F8;
    temp_a0 = (base + 3) & ~3;
    temp_v0 = 0x100 - (temp_a0 - base);
    D_0039D6EC = temp_a0;
    D_0039D6F0 = (temp_v0 < 0 ? temp_v0 + 0xF : temp_v0) >> 4;
}
