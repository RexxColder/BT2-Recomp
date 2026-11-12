#include "common.h"

/* 0x002E73E0: *(s16 *)(a0 + 0xE4) = -0x80; *(s32 *)(a0 + 0xCC) = 0; *(s16 *)(a0 + 0xE0) = 0;
   *(s16 *)(a0 + 0xE2) = -0x80; tail memset(a0 + 0xD0, 0, 0x10). */
void *func_002E73E0(u8 *a0) {
    *(s16 *)(a0 + 0xE4) = -0x80;
    *(s32 *)(a0 + 0xCC) = 0;
    *(s16 *)(a0 + 0xE0) = 0;
    *(s16 *)(a0 + 0xE2) = -0x80;
    return memset(a0 + 0xD0, 0, 0x10);
}
