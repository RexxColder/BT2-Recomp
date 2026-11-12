#include "common.h"

extern u8 D_003B26B0[] __attribute__((section(".data")));

s32 func_002A7D98(s32 arg0) {
    if (arg0 == 0) {
        *(s32 *)(D_003B26B0 + 4) = 6;
    }
    return 1;
}
