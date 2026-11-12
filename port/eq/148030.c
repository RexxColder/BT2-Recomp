#include "common.h"

extern u8 *D_00387760;

/* 0x00148030 EftShot_GetCurSlot: the word at +0x260 of record arg0 (0x270 bytes each). */
s32 EftShot_GetCurSlot(s32 arg0) {
    u8 *base;

    if (D_00387760 == NULL) {
        return 0;
    }
    base = *(u8 **)(D_00387760 + 4);

    return *(s32 *)(base + arg0 * 0x270 + 0x260);
}
