#include "common.h"

extern u8 D_0037A530[] __attribute__((section(".data")));

void func_002D20E8(u8 *arg0, s32 *arg1, s32 *arg2) {
    s32 v = *(s32 *)(arg0 + 0x920);

    if (v == 0) {
        *arg1 = 0;
        *arg2 = 0x7512;
        return;
    }
    *arg1 = 0x3E8;
    *arg2 = *(s32 *)(D_0037A530 + v * 4);
}
