#include "m2c_macros.h"

void *memset(void *dst, s32 c, u32 n);
void *memcpy(void *dst, void *src, u32 n);
extern u8 D_003B0F40[] __attribute__((section(".data")));

void func_002A3170(void) {
    u8 *b = D_003B0F40;
    u8 *x = b + 0x1000;

    memset(b, 0, 0x16C0);
    *(s32 *)(b + 0x1604) = -1;
    *(s32 *)(b + 0x1600) = -1;

    *(f32 *)(x + 0x8) = 1.0f;
    *(s32 *)(x + 0xC) = (s32)0x80FFFFFF;
    *(s32 *)(x + 0x14) = 5;
    *(s32 *)(x + 0x24) = 0x40000000;
    *(u16 *)(x + 0x28) = 1;
    *(u16 *)(x + 0x2A) = 2;
    *(u16 *)(x + 0x30) = 0x1FF;
    *(u16 *)(x + 0x32) = 0x1BF;
    *(s32 *)(x + 0x40) = 0;
    *(s32 *)(x + 0x44) = 0;
    *(s32 *)(x + 0x48) = 0;
    *(s32 *)(x + 0x4C) = 0;
    *(s32 *)(x + 0x50) = 0;
    *(s32 *)(x + 0x54) = 0;
    *(f32 *)(x + 0x0) = 1.0f;
    *(f32 *)(x + 0x4) = 1.0f;
    *(s32 *)(x + 0x10) = 2;
    *(s32 *)(x + 0x20) = 2;
    *(s32 *)(x + 0x18) = 0;
    *(s32 *)(x + 0x1C) = 0;
    *(u16 *)(x + 0x2C) = 0;
    *(u16 *)(x + 0x2E) = 0;

    memcpy(b + 0x1058, x, 0x58);
}
