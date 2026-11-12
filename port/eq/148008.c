#include "common.h"

extern u8 *D_00387760;

/* 0x00148008: stores arg1 at +0x260 of record arg0 (0x270 bytes each) of the array at D_00387760 + 4. */
void func_00148008(s32 arg0, s32 arg1) {
    u8 *base;

    if (D_00387760 == NULL) {
        return;
    }
    base = *(u8 **)(D_00387760 + 4);

    *(s32 *)(base + arg0 * 0x270 + 0x260) = arg1;
}
