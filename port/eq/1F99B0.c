#include "common.h"

s32 func_001F96A8();
extern u8 *D_00387930;

/* 0x001F99B0: idx = 0x31 - func_001F96A8(); return table at D_00387930->+0x1C. */
s32 func_001F99B0(unsigned long r_a0) { /* asm: a0 arrive and pass through untouched */
    s32 idx = 0x31 - func_001F96A8(r_a0);
    return *(s16 *)(*(u8 **)(D_00387930 + 0x1C) + idx * 2 + 0x320);
}
