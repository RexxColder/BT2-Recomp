#include "common.h"

extern u8 D_003B2654[] __attribute__((section(".data")));

void func_002AC480(void) {
    s32 v = *(s32 *)(D_003B2654 + 0x1C);
    *(u8 *)(D_003B2654 + 0x20) = 0;
    *(s32 *)(D_003B2654 + 8) = v;
    *(s32 *)(D_003B2654 + 4) = v;
}
