#include "common.h"

s32 func_001F95C0();
extern u8 *D_00387930;

/* 0x001F9940: idx = 0x281 - func_001F95C0(); return table at D_00387930->+0x1C. */
s32 func_001F9940(unsigned long r_a0) { /* asm: a0 arrive and pass through untouched */
    s32 idx = 0x281 - func_001F95C0(r_a0);
    return *(u8 *)(*(u8 **)(D_00387930 + 0x1C) + idx + 8);
}
