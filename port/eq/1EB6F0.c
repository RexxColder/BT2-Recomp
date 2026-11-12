#include "common.h"

extern u8 *D_00387908;

void *func_001EB6F0(void) {
    u8 *g;
    u8 *p;
    s32 idx;
    s32 n;

    g = D_00387908;
    idx = *(s32 *)(g + 0x200);
    n = 0;
    for (;;) {
        p = g + idx * 0x10;
        if (*(s32 *)(p + 4) == 0) {
            break;
        }
        idx = idx + 1;
        n = n + 1;
        if (idx >= 0x20) {
            idx = 0;
        }
        if (n >= 0x20) {
            return NULL;
        }
    }
    *(s32 *)(g + 0x200) = idx + 1;
    if (*(s32 *)(g + 0x200) >= 0x20) {
        *(s32 *)(g + 0x200) = 0;
    }
    return p;
}
