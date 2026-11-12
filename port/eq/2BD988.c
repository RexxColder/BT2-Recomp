#include "common.h"

extern u8 D_00393E50[] __attribute__((section(".data")));

void func_002BD988(void *arg0) {
    u8 *dst;
    u8 *src;

    dst = D_00393E50;
    src = (u8 *)arg0;
    *(s32 *)(dst + 0x0) = *(s32 *)(src + 0x0);
    *(s32 *)(dst + 0x8) = (*(s32 *)(src + 0x8) + 0x1F) & ~0x1F;
    *(s32 *)(dst + 0x4) = *(s32 *)(src + 0x4);
    *(s32 *)(dst + 0xC) = *(s32 *)(src + 0xC);
    *(s32 *)(dst + 0x18) = (*(s32 *)(src + 0x18) + 0x1F) & ~0x1F;
    *(s32 *)(dst + 0x10) = *(s32 *)(src + 0x10);
    *(s32 *)(dst + 0x14) = *(s32 *)(src + 0x14);
}
