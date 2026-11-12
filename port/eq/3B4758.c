#include "common.h"

s32 func_003B4D50(s32);
extern s32 D_00421384 __attribute__((section(".data")));

s32 func_003B4758(void) {
    return func_003B4D50(D_00421384 + 0x20);
}
