#include "common.h"

void *memset(void *dst, s32 val, u32 n);

void func_0025FBA8(u8 *arg0) {
    u8 *p = arg0 + 0xBD0;

    *(s32 *)(p + 0x28) = *(s32 *)(p + 0x2C);
    *(f32 *)(p + 0x8) = *(f32 *)(p + 0xC);
    *(u16 *)(p + 0x4) = *(u16 *)(p + 0x6);
    memset(arg0 + 0xC00, 0, 0x8E);
}
