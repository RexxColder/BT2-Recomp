#include "common.h"

extern u8 D_003B26B0[] __attribute__((section(".data")));

void func_002AD380(s32 arg0) {
    s32 idx;
    s32 *p;

    idx = (arg0 < 0 ? arg0 + 0x1F : arg0) >> 5;
    p = (s32 *)(D_003B26B0 + 0x310 + idx * 4);
    if (arg0 < 0x164 || (arg0 >= 0x16B && arg0 != 0x3E8)) {
        *p |= (s32)(1u << (arg0 & 31));
    }
}
