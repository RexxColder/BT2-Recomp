#include "common.h"

void *memset(void *s, s32 c, u32 n);
extern s32 D_00387970 __attribute__((section(".data")));
extern s32 D_00387974 __attribute__((section(".data")));
extern u8 D_003889E8[] __attribute__((section(".data")));

void func_00247E80(s32 arg0) {
    s32 temp_a0;
    s32 base;

    base = (s32) D_003889E8;
    memset(D_003889E8, 0, 0x14);
    *(s8 *) (base + 0) = 1;
    temp_a0 = arg0 + 0x10;
    *(s16 *) (base + 8) = 0;
    *(s32 *) (base + 4) = temp_a0;
    *(u16 *) (base + 0xA) = *(u16 *) (arg0 + 8);
    *(s32 *) (base + 0xC) = 0;
    D_00387974 = 1;
    D_00387970 = 0;
    *(f32 *) (base + 0x10) = (f32) *(u16 *) (temp_a0 + *(u16 *) (base + 0xA) * 4 - 4);
}
