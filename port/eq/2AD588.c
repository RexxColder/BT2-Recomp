#include "common.h"

extern u8 D_003B26B0[] __attribute__((section(".data")));

void *func_002AD588(void) {
    u8 *base;
    u8 *p;
    s32 i;
    s32 v0;
    s32 v1;

    base = D_003B26B0 + 0x58;
    p = base;
    for (i = 4; i >= 0; i--) {
        v0 = *(s32 *)(p + 0x0);
        v1 = (s32)((u32)v0 + 0xFFFF5345U);
        if (v0 != 0) {
            *(s32 *)(p + 0xC) = v1 / 9;
            *(s32 *)(p + 0x10) = v1 % 9;
        }
        p += 0x78;
    }
    return base;
}
