#include "common.h"

s32 func_002C8920(u8 *arg0, s32 arg1) {
    u8 *p;
    u32 state;

    p = *(u8 **)(arg0 + 0x1FC0);
    state = *(u32 *)(p + 0x74);
    if (state == 3) {
        return (u32)arg1 == state;
    }
    if (state == 2) {
        return (u32)(arg1 - 2) < 2U;
    }
    return 0;
}
