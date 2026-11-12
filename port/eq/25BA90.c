#include "common.h"

extern u8 D_00388A00[] __attribute__((section(".data")));

void func_0025BA90(void) {
    s32 k;

    for (k = 0; k < 0x10; k++) {
        u8 *base = *(u8 **)D_00388A00;
        u32 w = *(u32 *)(base + k * 4 + 4);

        *(u8 **)(D_00388A00 + 4 + k * 4) = base + ((w >> 2) << 2);
    }
}
