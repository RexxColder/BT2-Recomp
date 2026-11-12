#include "common.h"

extern u8 D_003B26B0[] __attribute__((section(".data")));

s32 func_002AD5E8(void) {
    s32 k;

    for (k = 0; k < 5; k++) {
        if (*(s32 *)(D_003B26B0 + 0x58 + k * 0x78) == 0) {
            return k;
        }
    }
    return 5;
}
