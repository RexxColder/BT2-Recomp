#include "common.h"

extern u8 D_0037B190[] __attribute__((section(".data")));
extern u8 D_0037B1A0[] __attribute__((section(".data")));

void func_002E26B8(u8 *arg0) {
    s32 temp_v0;
    s32 idx;

    if (*(s32 *)(arg0 + 0x118) != 3) {
        temp_v0 = *(s32 *)(arg0 + 0x3C8);
        *(s32 *)(arg0 + 0x3C8) = temp_v0 + 1;
        *(s32 *)(arg0 + 0x3C4) = temp_v0 % 2;
    } else {
        *(s32 *)(arg0 + 0x3C8) = 0;
        *(s32 *)(arg0 + 0x3C4) = 0;
    }
    idx = *(s32 *)(arg0 + 0x114) * 4;
    *(s32 *)(arg0 + 0x320) = *(s32 *)(D_0037B190 + idx);
    *(s32 *)(arg0 + 0x330) = *(s32 *)(D_0037B1A0 + idx);
}
