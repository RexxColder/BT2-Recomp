#include "common.h"

extern u8 D_003B26B0[] __attribute__((section(".data")));

s32 func_002A7DF8(s32 arg0) {
    if (arg0 == 0) {
        *(s32 *)(D_003B26B0 + 4) = 7;
    }
    return 1;
}
