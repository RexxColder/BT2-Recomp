#include "common.h"

extern s32 D_003877B0;

s32 func_00185CD0(void) {
    s32 p;

    if (*(s32 *)(D_003877B0 + 0x79E0) >= 0x96) {
        *(s32 *)(D_003877B0 + 0x79E0) = 0;
    }
    p = D_003877B0 + *(s32 *)(D_003877B0 + 0x79E0) * 0xD0;
    for (;;) {
        *(s32 *)(D_003877B0 + 0x79E0) = *(s32 *)(D_003877B0 + 0x79E0) + 1;
        if (*(u16 *)(p + 0xBE) != 0) {
            p += 0xD0;
            if (*(s32 *)(D_003877B0 + 0x79E0) >= 0x96) {
                *(s32 *)(D_003877B0 + 0x79E0) = 0;
                return 0;
            }
            continue;
        }
        *(s32 *)(p + 0xC0) = 0;
        *(s32 *)(p + 0xC4) = 0;
        return p;
    }
}
