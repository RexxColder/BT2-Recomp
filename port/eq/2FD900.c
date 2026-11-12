#include "common.h"

void func_002FD2E8(u8 *arg0, u8 *arg1);
extern u8 D_0037E428[] __attribute__((section(".data")));

s32 func_002FD900(u8 *arg0, s32 arg1, s32 arg2) {
    s32 v;
    s32 cap;

    if (arg0 == NULL) {
        func_002FD2E8(arg0, D_0037E428);
        return 0;
    }
    if (arg2 == 0) {
        *(s32 *)(arg0 + 0xC) = arg1;
    } else if (arg2 == 2) {
        *(s32 *)(arg0 + 0xC) = *(s32 *)(arg0 + 0x8) + arg1;
    } else if (arg2 == 1) {
        *(s32 *)(arg0 + 0xC) = *(s32 *)(arg0 + 0xC) + arg1;
    }
    v = *(s32 *)(arg0 + 0xC);
    *(s32 *)(arg0 + 0x14) = 0;
    cap = *(s32 *)(arg0 + 0x8);
    v = (v >= cap) ? cap : v;
    if (v < 0) {
        v = 0;
    }
    *(s32 *)(arg0 + 0xC) = v;
    return v;
}
