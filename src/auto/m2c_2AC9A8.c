#include "m2c_macros.h"

extern s32 D_003B2654 __attribute__((section(".data")));

s32 func_002AC9A8(void) {
    return (D_003B2654 & 0x30000) != 0;
}
