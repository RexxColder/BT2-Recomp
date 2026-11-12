#include "common.h"

extern u8 *D_00387A40;

s32 func_0025E068(void) {
    s32 count = *(s32 *)(D_00387A40 + 0xC);
    u8 *base = (u8 *)*(s32 *)(D_00387A40 + 0x8);
    s32 i;

    for (i = 0; i < count; i++) {
        if (*(s32 *)(base + 0xC + i * 0x1520) == 0) {
            return i;
        }
    }
    return -1;
}
