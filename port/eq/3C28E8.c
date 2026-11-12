#include "common.h"

extern void *D_00421CF4 __attribute__((section(".data")));

s32 func_003C28E8(void) {
    s32 v1 = *(s32 *)((u8 *)D_00421CF4 + 0x1D0);

    return ((v1 < 0 ? v1 + 0xF : v1) >> 4) * 0x24;
}
